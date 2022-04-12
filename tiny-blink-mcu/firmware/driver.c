#include "driver.h"
#include "animation.h"
#include <util/delay.h>

volatile uint16_t mframe = 0xFFFF;
volatile int8_t counter;

/**
 * On reversed clock voltage change.
 */
ISR(INT0_vect) {

	/*	Do nothing - Done for next frame.	*/
	if (counter <= 1) {
		counter = 0;
		return;
	}

	/*	Delay 100ns after clock low.	*/
	_delay_loop_1(100);

	/*	Shift high.	*/
	shift_clock_state(1);

	/*	Delay 100ns.	*/
	_delay_loop_1(100);

	/*	Shift low.	*/
	shift_clock_state(0);

	/*	On raise of the signal - shift clock is low.	*/
	/*	Get next bit.	*/
	mframe = (mframe >> 1);
	const uint8_t frame = mframe & 0xFF;

	/*	Write bit value.	*/
	write_bit(frame);

	/*	Decrement counter*/
	counter--;
}

void write_frame(const uint16_t frame) { mframe = frame; }

void frame_done() { counter = NRLED + 1; }

void set_pwm(const uint8_t pwm) { OCR0A = LED_INTENSITY - pwm; }

void clear_register() {
	write_frame(0x0);
	frame_done();
}

void shift_clock_state(const uint8_t state) {

	if (state) {
		/*	Output source mode.
		 */
		DDRB |= (1 << SHIFT_RSHIF);
		PORTB |= (1 << SHIFT_RSHIF);
	} else {
		/*	Low output by high impedance.
		 */
		DDRB |= (1 << SHIFT_RSHIF);
		// DDRB &= ~(1 << SHIFT_RSHIF);
		PORTB &= ~(1 << SHIFT_RSHIF);
	}
}

void write_bit(const uint8_t state) {
	const uint8_t bit = state & 0x1;
	if (bit) {
		/*
		 * High - source output
		 */
		DDRB |= (1 << SHIFT_DIO);
		PORTB |= (1 << SHIFT_DIO);
	} else {
		/**
		 *	Low - sink output.
		 */
		DDRB |= (1 << SHIFT_DIO);
		PORTB &= ~(1 << SHIFT_DIO);
	}
}

void init() {

	cli();

	/**
	 * All port output source mode.
	 * SHIFT_DIO, SHIFT_CLR output IO.
	 *
	 * SHIFT_RCLK input IO.
	 * SHIFT_PMW output sink mode.
	 */
	PORTB = (1 << SHIFT_RCLK) | (0 << SHIFT_DIO) | (0 << SHIFT_RSHIF) | (0 << SHIFT_PWM);
	DDRB = (0 << SHIFT_RCLK) | (0 << SHIFT_DIO) | (0 << SHIFT_RSHIF) | (1 << SHIFT_PWM);

	/**
	 * PWM - pulse with modulation.
	 * Override OCA1 pin and toggle output.
	 * Fast PWM mode
	 * Clock divisor 8.
	 */
	TCCR0A = (0 << COM0A1) | (1 << COM0A0) | (0 << WGM01) | (1 << WGM00);
	TCCR0B = (0 << CS02) | (0 << CS01) | (0 << CS00) | (1 << WGM02);

	/*	External interrupt on signal raise for INT0.	*/
	/*	One clock low.	*/
	GIMSK = (1 << INT0);
	MCUCR |= (1 << ISC01) | (1 << ISC00);

	/*	Sleep during shift register clock high.
	 *  Wake up by the external interrupt.
	 */
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();

	/*	Initialize the PWM.	*/
	set_pwm(LED_INTENSITY);

	shift_clock_state(0);

	// sei();
}

int main() {

	DDRB = 0xff;
	PORTB = 0xff;

	while (1) {
	}

	/*	Init the controller.	*/
	init();

	/*	Frame initialization .	*/
	clear_register();

	while (1) {
		register uint16_t frame;

		/*	Sleep.	*/
		while (counter > 0) {
			sleep_cpu();
		}

		cli();

		/*	Next animation frame.	*/
		frame = cc_get_curr_next_animation_keyframe();

		/*	Write next frame.	*/
		write_frame(frame);

		/*	Enable next frame.	*/
		frame_done();

		// sei();
	}
	return 0;
}
