#include "driver.h"
#include "animation.h"
#include <assert.h>
#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <util/delay.h>

uint8_t push_counter_button = 0;
uint8_t brightness;
uint8_t play_mode = 0;

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

inline void shift_oe_state(const uint8_t state) {

	if (state) {
		SHIFT_OE_DREG |= (1 << SHIFT_OE_PIN);
		SHIFT_OE_REG |= (1 << SHIFT_OE_PIN);
	} else {
		SHIFT_OE_DREG &= ~(1 << SHIFT_OE_PIN);
		SHIFT_OE_REG &= ~(1 << SHIFT_OE_PIN);
	}
}

void check_button_and_next(); //  __attribute__ ((naked));
void check_button_and_next() {
	const uint8_t button = !(PUSH_BUTTON_IREG & PUSH_BUTTON_PIN);
	if (button) {
		reset_for_next_animation();
	}
}

/**
 * On reversed clock voltage change.
 */
#ifdef __AVR_ATmega328P__
ISR(PCINT2_vect) {
#else
ISR(PCINT0_vect) {
#endif
	const uint8_t button = !(PUSH_BUTTON_IREG & PUSH_BUTTON_PIN);

	if (button) {
		curanim = (curanim + 1) % NRANIM;
		curaniindex = 0;
	}
}

ISR(TIMER0_OVF_vect) {
	const uint8_t button = (PUSH_BUTTON_IREG & PUSH_BUTTON_PIN);

	if (button) {
		push_counter_button++;
		if (push_counter_button >= 2) {

			/*	Setup Default Values.	*/
			shift_oe_state(0);


			/*	*/
			// set_sleep_mode(SLEEP_MODE_PWR_SAVE);
			// wdt_disable();
			// sleep_enable();
			// sleep_mode();
		}
	} else {
		push_counter_button = 0;
	}
}

const uint16_t MAX_PWM_VALUE = 65535U;
void set_pwm(const uint8_t pwm) { SHIFT_OE_PWM_REG = 0xFFFF - 0x10ff; }

void init() {

	cli();

	/*	Set Prescular on the MCU to reduce power.	*/
	clock_prescale_set(clock_div_128);

	/*	*/
	wdt_enable(WDTO_500MS);

	/*	*/
	power_adc_disable();

	/*	Setup Button Pin.	*/
	PUSH_BUTTON_REG |= (0 << PUSH_BUTTON_REG);
	PUSH_BUTTON_DREG |= (0 << PUSH_BUTTON_REG);

	/*	Setup Default Values.	*/
	shift_oe_state(1);

	/*	PWM - SHIFT OE.	*/
	// TCCR1A = 1 << WGM11 | 1 << COM1A1 | 1 << COM1B1; // set on top, clear OC on compare match
	// TCCR1B = 1 << CS10 | 1 << WGM12 | 1 << WGM13;	 // clk/1, mode 14 fast PWM
	// ICR1 = 0xFFFF;

	/*	Setup Timer Overflow.	*/
	TCNT0 = 0;
	TCCR0B = (1 << CS02) | (0 << CS01) | (1 << CS00) | (0 << WGM02);
	TIMSK0 |= (1 << TOIE0);

/*	Enable Pin Down Change.	*/
#ifdef __AVR_ATmega328P__
	PCICR |= (1 << PCIE2);	  /*	Enable PIN interrupt 0	*/
	PCMSK2 |= (1 << PCINT16); /*	Mask PIN to Listen on to invoke Interrupt.*/
#elif defined(__AVR_ATtiny13A__)
	GIMSK |= (1 << INT0) | (1 << PCIE);
	MCUCR |= (1 << ISC01) | (1 << ISC00);
#endif

	sei();
}

#define SPEED_FACTOR 3

int main() {

	/*	Init the controller.	*/
	init();

	_delay_loop_1(255u);

	shift_latch_state(0);
	shift_clock_state(0);

	while (1) {

		/*	*/
		wdt_reset();
		// set_pwm(gamma_correction(brightness));

		/*	Next animation frame.	*/
		const uint16_t current_frame = cc_get_curr_next_animation_keyframe();
		/*	*/
		for (uint8_t i = 0; i < 15; i++) {

			const uint8_t bit = (current_frame) >> i;

			/*	Write Data Signal.	*/
			write_bit(bit);
			_delay_loop_1(64);

			/*	Shift Clock to shift the current BIts.	*/
			shift_clock_state(1);
			_delay_loop_1(32);

			/*	Shift Clock Low -> */
			shift_clock_state(0);
			_delay_loop_1(32);
		}

		/*	*/
		_delay_loop_1(32);

		/*	Latch the current result in the shift buffer to the output buffer.	*/
		shift_latch_state(1);
		_delay_loop_1(128);

		/*	*/
		shift_latch_state(0);
		_delay_loop_1(128);

		continue;
	}
}
