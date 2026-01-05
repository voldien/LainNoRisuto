#include "tiny-blink-driver.h"
#include "animation.h"
#include "tiny-blink-def.h"
#include <assert.h>
#include <avr/cpufunc.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <stdint.h>
#include <util/delay.h>

const uint8_t EEMEM brightness = 255;

uint8_t push_counter_button = 0;
uint8_t play_mode = PLAY_MODE_OUT_ENABLED | PLAY_MODE_AUTO_NEXT_ANIMATION;

// TODO: gamma correction
inline uint8_t gamma_correction(const uint8_t level) { return level; }

inline void shift_latch_state(const uint8_t state) {

	if (state) {
		/*	Output source mode.
		 */
		SHIFT_LATCH_DREG |= (1 << SHIFT_LATCH_PIN);
		SHIFT_LATCH_REG |= (1 << SHIFT_LATCH_PIN);
	} else {
		/*	Low output by high impedance.
		 */
		SHIFT_LATCH_DREG |= (1 << SHIFT_LATCH_PIN);
		SHIFT_LATCH_REG &= ~(1 << SHIFT_LATCH_PIN);
	}
}

inline void shift_clock_state(const uint8_t state) {

	if (state) {
		/*	Output source mode.
		 */
		SHIFT_RCLK_DREG |= (1 << SHIFT_RCLK_PIN);
		SHIFT_RCLK_REG |= (1 << SHIFT_RCLK_PIN);
	} else {
		/*	Low output by high impedance.
		 */
		SHIFT_RCLK_DREG |= (1 << SHIFT_RCLK_PIN);
		SHIFT_RCLK_REG &= ~(1 << SHIFT_RCLK_PIN);
	}
}

inline void write_bit(const uint8_t state) {
	const uint8_t bit = state & 0x1;

	if (bit) {
		/*
		 * High - source output
		 */
		SHIFT_DIO_DREG |= (1 << SHIFT_DIO_PIN);
		SHIFT_DIO_REG |= (1 << SHIFT_DIO_PIN);
	} else {
		/**
		 *	Low - sink output.
		 */
		SHIFT_DIO_DREG |= (1 << SHIFT_DIO_PIN);
		SHIFT_DIO_REG &= ~(1 << SHIFT_DIO_PIN);
	}
}

inline void shift_oe_state(const uint8_t output_enabled) {

	if (output_enabled) {
		SHIFT_OE_REG &= ~(1 << SHIFT_OE_PIN);
	} else {
		SHIFT_OE_REG |= (1 << SHIFT_OE_PIN);
	}
}

inline uint8_t push_button_pressed() {
	/*	High => Not Pressed.	*/
	/*	Low => Pressed.	*/
	return (PUSH_BUTTON_IREG & (1 << PUSH_BUTTON_PIN)) == 0;
}

inline void playmode_toggle_output() {
	shift_oe_state(!(play_mode & PLAY_MODE_OUT_ENABLED));
	play_mode ^= PLAY_MODE_OUT_ENABLED;
}

/**
 * On reversed clock voltage change.
 */
#ifdef __AVR_ATmega328P__
ISR(PCINT2_vect) {
#else
ISR(PCINT0_vect) {
#endif
	const uint8_t button = push_button_pressed();

	// if (button) {
	// 	/*	If disabled, Enable */
	// 	if (!(play_mode & PLAY_MODE_OUT_ENABLED)) {
	// 		playmode_toggle_output();
	// 	}
	// }

	if (button) {
		curanim = (curanim + 1) % NRANIM;
		curaniindex = 0;
	}
}
#ifdef __AVR_ATmega328P__
ISR(TIMER0_OVF_vect) {
#else
ISR(TIM0_OVF_vect) {
#endif

	const uint8_t button = push_button_pressed();

	if (button) {
		push_counter_button++;

		if (push_counter_button == 3) { /*	Based on How Fast the timer invokes the interrupt.	*/

			/*	Swap Output Mode.	*/
			playmode_toggle_output();

			/*	 TODO: Add Support for Sleep During Output Disabled.	*/
			/*
			set_sleep_mode(SLEEP_MODE_PWR_SAVE);
			wdt_disable();
			sleep_mode();
			*/
		}
	} else {
		push_counter_button = 0; /*	Reset Counter.	*/
	}
}

// const uint16_t MAX_PWM_VALUE = 65535U;
// void set_pwm(const uint8_t pwm) { SHIFT_OE_PWM_REG = 0xFFFF - 0x10ff; }

inline void init_system() {

	/*	Set Prescular on the MCU to reduce power.	*/
#ifdef __AVR_ATmega328P__
	clock_prescale_set(clock_div_128); /* 16Mhz / 128 = 125 kHz	*/
#elif defined(__AVR_ATtiny13A__)	   /*	Attiny13A	*/
	clock_prescale_set(clock_div_8); /*		(9.6 / 8) / 8 = 150 kHz  */
#elif defined(__AVR_ATtiny11A__)	   /*	Attiny11A	*/
	clock_prescale_set(clock_div_8); /*		(9.6 / 8) / 8 = 150 kHz  */
#endif

/*	*/
#ifdef __AVR_ATmega328P__
	wdt_enable(WDTO_500MS);
#endif

	/*	*/
	power_adc_disable();

	/*	Use internal pull up resistor */
	MCUCR &= ~(1 << PUD);

	/*	Setup Button Pin.	*/
	PUSH_BUTTON_REG |= (1 << PUSH_BUTTON_PIN);	 /*	Set High to Enable Pull Resistor Mode.*/
	PUSH_BUTTON_DREG &= ~(1 << PUSH_BUTTON_PIN); /*	Input Mode.	*/

	/*	Set Shift output enable as output (source).	*/
	SHIFT_OE_DREG |= (1 << SHIFT_OE_PIN);
	/*	Enable Output By Default.	*/
	shift_oe_state(1);

	/*	PWM - SHIFT OE.	*/ // NOTE: optionally
	// TCCR1A = 1 << WGM11 | 1 << COM1A1 | 1 << COM1B1; // set on top, clear OC on compare match
	// TCCR1B = 1 << CS10 | 1 << WGM12 | 1 << WGM13;	 // clk/1, mode 14 fast PWM
	// ICR1 = 0xFFFF;

	/*	Setup Timer Overflow and interrupt enabled.	*/
	TCNT0 = 0;														 /*	Set Init timer value.	*/
	TCCR0B = (1 << CS02) | (0 << CS01) | (0 << CS00) | (0 << WGM02); /*	Set Timer clock prescalar.	*/
	TIMSK0 |= (1 << TOIE0);											 /*	Enable Overflow interrupt.	*/

/*	Enable Pin Down Change.	*/
#ifdef __AVR_ATmega328P__
	PCICR |= (1 << PCIE2);	  /*	Enable PIN interrupt 0	*/
	PCMSK2 |= (1 << PCINT16); /*	Mask PIN to Listen on to invoke Interrupt.*/
#elif defined(__AVR_ATtiny13A__)
	GIMSK |= (1 << PCIE);
	// MCUCR |= (1 << ISC01) | (1 << ISC00);
	PCMSK |= (1 << PCINT4);
#endif

	sei();
}

int main() {

	/*	Init the controller.	*/
	init_system();
	const uint8_t delay_factor = 1;
	while (1) {

		/*	Reset WatchDog Counter.	*/
#ifdef __AVR_ATmega328P__
		wdt_reset();
#endif

		/*	Next animation frame.	*/
		const uint16_t current_frame = cc_get_curr_next_animation_keyframe();

		/*	Latch Low to stop reading from the shift buffer.	*/
		shift_latch_state(0);
		_delay_loop_1(32 * delay_factor);
		_delay_loop_1(128 * delay_factor);

		/*	*/
		uint8_t i;
		for (i = 0; i < NRLED; i++) {

			const uint8_t bit = ((current_frame) >> i) & 0xFF;

			/*	Write Data Signal.	*/
			write_bit(bit);
			_delay_loop_1(64 * delay_factor);

			/*	Shift Clock to shift the current Bits.	*/
			shift_clock_state(1);
			_delay_loop_1(48 * delay_factor);

			/*	Shift Clock Low -> Stop Shift Bites.	*/
			shift_clock_state(0);
			_delay_loop_1(48 * delay_factor);
		}

		/*	Latch the current result in the shift buffer to the output buffer.	*/
		shift_latch_state(1);
		_delay_loop_1(128 * delay_factor);
		write_bit(0);

		continue;
	}
}
