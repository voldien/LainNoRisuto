#include "driver.h"
#include "animation.h"
#include <assert.h>
#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/delay.h>

// FUSES = {
// 	.low = FUSE_SUT0 | FUSE_CKSEL3 | FUSE_CKSEL2 | FUSE_CKSEL0,
// 	.high = (FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_SPIEN),
// 	.extended = EFUSE_DEFAULT,
// };

// TODO: gamma correction
// TODO: Define Each Signal Port Register and Index
// PWM - OE Define Each Signal Port Register and Index

inline uint8_t gamma_correction(uint8_t level) { return level; }

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

void check_button_and_next(); //  __attribute__ ((naked));
void check_button_and_next() {
	const uint8_t button = (PUSH_BUTTON_IREG & PUSH_BUTTON_PIN);
	if (button) {
		reset_for_next_animation();
	}
}

/**
 * On reversed clock voltage change.
 */
ISR(PCINT0_vect) {
	/*	*/
	const uint8_t button = (PUSH_BUTTON_IREG & PUSH_BUTTON_PIN);
	if (button) {
		curanim = (curanim + 1) % NRANIM;
		curaniindex = 0;
	}
	// check_button_and_next();
}

uint8_t push_button = 0;
ISR(TIMER0_OVF_vect) {
	const uint8_t button = (PUSH_BUTTON_IREG & PUSH_BUTTON_PIN);

	if (button) {
		push_button++;
		if (push_button == 2) {
			set_sleep_mode(SLEEP_MODE_IDLE);
		}
	} else {
		push_button = 0;
	}
}

void set_pwm(const uint8_t pwm) { OCR0A = LED_INTENSITY - pwm; }

void init() {

	cli();

	/*TODO: prescular.	*/
	clock_prescale_set(clock_div_128);
	wdt_enable(WDTO_500MS);

	power_adc_disable();

	/**
	 * All port output source mode.
	 * SHIFT_DIO_PIN, SHIFT_CLR output IO.
	 *
	 * SHIFT_RCLK_PIN input IO.
	 * SHIFT_PMW output sink mode.
	 */
	SHIFT_OE_REG |= (1 << SHIFT_RCLK_PIN);
	SHIFT_RCLK_REG &= ~(0 << SHIFT_RCLK_PIN);
	SHIFT_DIO_REG &= ~(0 << SHIFT_DIO_PIN);
	SHIFT_LATCH_REG &= ~(0 << SHIFT_RCLK_PIN);

	// TODO:
	DDRB = (0 << SHIFT_RCLK_PIN) | (0 << SHIFT_DIO_PIN) | (0 << SHIFT_LATCH_PIN) | (1 << SHIFT_OE_PIN);

	/**
	 * PWM - pulse with modulation.
	 * Override OCA1 pin and toggle output.
	 * Fast PWM mode
	 * Clock divisor 8.
	 */
	//TCCR0A = (0 << COM0A1) | (1 << COM0A0) | (0 << WGM01) | (1 << WGM00);
	//TCCR0B = (0 << CS02) | (0 << CS01) | (0 << CS00) | (1 << WGM02);

	// GIMSK0 = (1 << INT0);
	// MCUCR |= (1 << ISC01) | (1 << ISC00);

	/*	Enable Pin Down Change.	*/
	// PCICR |= (1 << PCIE0);	 /*	*/
	// PCMSK0 |= (1 << PCINT0); /*	*/

	// sleep_enable();
	sei();
}

#define SPEED_FACTOR 3

int main() {

	/*	Init the controller.	*/
	init();

	_delay_loop_1(256);

	shift_latch_state(0);
	shift_clock_state(0);

	uint16_t testCount = 0;
	while (1) {
		wdt_reset();

		/*	Next animation frame.	*/

		uint16_t current_frame =  cc_get_curr_next_animation_keyframe();

		for (uint8_t i = 0; i < 15; i++) {

			uint8_t bit = (current_frame) >> i;

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
		shift_latch_state(1);
		_delay_loop_1(128);

		/*	*/
		shift_latch_state(0);
		_delay_loop_1(128);

		testCount++;
		continue;
	}
}
