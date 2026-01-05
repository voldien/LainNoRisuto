#include "animation.h"
#include "christmascard.h"
#include "ws2811/ws2811_8.h"
#include <assert.h>
#include <avr/boot.h>
#include <avr/builtins.h>
#include <avr/common.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <util/delay.h>

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

ISR(INT0_vect) { cc_reset_for_next_animation(); }

inline void cc_init_buttons() {

	/*	Setup Button Pin - Reset.	*/
	PUSH_BUTTON0_REG |= (1 << PUSH_BUTTON0_PIN);   /*	Set High to Enable Pull Resistor Mode.*/
	PUSH_BUTTON0_DREG &= ~(1 << PUSH_BUTTON0_PIN); /*	Input Mode.	*/

	/*	Setup Button Pin - Next.	*/
	PUSH_BUTTON1_REG |= (1 << PUSH_BUTTON1_PIN);   /*	Set High to Enable Pull Resistor Mode.*/
	PUSH_BUTTON1_DREG &= ~(1 << PUSH_BUTTON1_PIN); /*	Input Mode.	*/

	/*	Enable interrupt.	*/
	/*	External interrupt invoked on volt drop.	*/
	// MCUCR |= (1 << ISC00) | (1 << ISC01);
	// GICR |= (1 << INT0);
}

inline void cc_init_ledcontrollers() {

	/*	Output and enable pin for ws2811.	*/
	WS2811_DREG |= WS2811_IN;

	/*	Set Shift output enable as output (source).	*/
	SHIFT_OE_DREG |= (1 << SHIFT_OE_PIN);
	/*	Enable Output By Default.	*/
	shift_oe_state(1);
}

inline void cc_init_time2ovf() {
	/*
	TIMSK |= ( 1 << TOIE2);
	*/
	/*	Enable time overflow and interrupt.	*/
	/*
	ASSR = (1<<AS2);
	TIMSK = (1 << TOIE2);
	TCCR2 |= (1 << CS02);
	TIFR = (1 << TOV2);
	*/
}

// TODO: set the shift registers to specific value.
void cc_set_row(const uint8_t row_index) {
	const uint8_t delay_factor = 1;

	/*	Set all rows to sink.	 */
	for (uint8_t i = 0; i < 8; i++) {
		/*	Write Data Signal.	*/
		write_bit(i == row_index ? 1 : 0);
		_delay_loop_1(64 * delay_factor);

		/*	Shift Clock to shift the current Bits.	*/
		shift_clock_state(1);
		_delay_loop_1(48 * delay_factor);

		/*	Shift Clock Low -> Stop Shift Bites.	*/
		shift_clock_state(0);
		_delay_loop_1(48 * delay_factor);
	}
}

void cc_set_col(const uint8_t d[9]) {

	cli();
	ws2811_send(d, 3, WS2811_PIN);
	sei();
}

void cc_display_next_keyframe() {
	uint8_t i, j;

	/*	*/
	for (j = 0; j < NUMROWS; j++) {
		uint8_t buf[9];

		/*	Fetch row data.	*/
		for (i = 0; i < NUMCOL; i++) {
			buf[i] = cc_get_curr_animation_keyframe(j, i);
		}

		/*	gamma correct.	*/

		cc_set_col(buf);
		cc_set_row(j);

		//_delay_ms(1000);
		_delay_us(30);
	}
	//_delay_us(15);
}

void cc_select_led_controller() {
	DDRA |= (1 << PA6);
	PORTA |= (1 << PA6);
}

void init_system() {
	/*	Disable interrupt intill
	 *	the initialization part is done.*/
	cli();

	/*	Use internal pull up resistor */
	MCUCR &= ~(1 << PUD);

	/*	Enable all required components of the MCU.	*/
	cc_init_ledcontrollers();

	/*	*/
	cc_init_buttons();

	/*	*/
	cc_init_animation();

	/*	*/
	cc_init_time2ovf();

	/*	*/
	cc_select_led_controller();

	/*	*/
#if F_CPU == 16000000 && 0
	clock_prescale_set(clock_div_2);
#endif

	sleep_enable();
	set_sleep_mode(SLEEP_MODE_IDLE);

	sei();
}

int main() {

	init_system();

	/*	main logic.	*/
	while (1) {
		uint8_t i = 0;
		const uint8_t frame_refresh_count = 144; /*	How long the display will be lit.	*/

		/*	Refresh the LED n number of times.	*/
		for (i = 0; i < frame_refresh_count; i++) {
			cc_display_next_keyframe();
		}

		/*	Change to next animation.*/
		if (cc_next_animation_ready()) {
			cc_reset_for_next_animation();
			continue;
		}

		/*	Next frame.	*/
		cc_next_frame();
	}

	return 0;
}
