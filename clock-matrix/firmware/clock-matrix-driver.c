#include "clock-matrix-driver.h"
#include "ws2811_8.h"
#include <assert.h>
#include <avr/boot.h>
#include <avr/builtins.h>
#include <avr/common.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <cstdint>
#include <util/delay.h>

inline void shift_latch_state(const uint8_t state) {

	if (state) {
		/*
		 *	Output source mode.
		 */
		SHIFT_LATCH_DREG |= (1 << SHIFT_LATCH_PIN);
		SHIFT_LATCH_REG |= (1 << SHIFT_LATCH_PIN);
	} else {
		/*
		 * Low output by high impedance.
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

void cc_init_buttons() {
	/*	Output and enable pin for next button.	*/
	PORTD |= BUTTON_NEXT;
	DDRD |= BUTTON_NEXT;

	/*	Enable interrupt.	*/
	/*	External interrupt invoked on volt drop.	*/
	MCUCR |= (1 << ISC00) | (1 << ISC01);
	GICR |= (1 << INT0);
}

void cc_init_ledcontrollers() {

	/*	Output and enable pin for ws2811.	*/
	DDRB |= WS2811_IN;

	/*	Output rows.	*/
	ROWDPORT |= ROWALL;
}

void cc_init_time2ovf() {
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

void cc_set_row(const uint8_t r) {

	/*	Set all rows to sink.	 */
	ROWPORT &= ~ROWALL;
	ROWDPORT |= ROWALL;

	/*	Set specified row to source mode.	*/
	if (r == 0) {
		ROWPORT |= ROW0;
	} else if (r == 1) {
		ROWPORT |= ROW1;
	} else if (r == 2) {
		ROWPORT |= ROW2;
	} else if (r == 3) {
		ROWPORT |= ROW3;
	}
}

void cc_set_col(const uint8_t d[9]) {

	cli();
	ws2811_send(d, 3, WS2811_PIN);
	sei();
}

void display_next_clock_state() {
	uint8_t i, j;

	/*	*/
	for (j = 0; j < NUMROWS; j++) {
		uint8_t buf[9];

		/*	Fetch row data.	*/
		for (i = 0; i < NUMCOL; i++) {
			buf[i] = cc_get_curr_animation_keyframe(j, i);
		}

		cc_set_col(buf);
		cc_set_row(j);

		//_delay_ms(1000);
		_delay_us(30);
	}
	//_delay_us(15);
}

void cc_select_led_controller() {
	DDRC |= (1 << PC6);
	PORTC |= (1 << PC6);
}

void	init_i2c(){}

void 	init_clock(){}

void init_system() {
	/*	Disable interrupt intill
	 *	the initialization part is done.*/
	cli();

#if F_CPU == 16000000 && 0
	clock_prescale_set(clock_div_2);
#endif

	/*	Enable all required components of the MCU.	*/
	cc_init_ledcontrollers();

	/*	*/
	cc_init_time2ovf();

	/*	*/
	cc_select_led_controller();

	init_i2c();

	init_clock();

	sleep_enable();
	set_sleep_mode(SLEEP_MODE_IDLE);

	sei();
}

int main() {

	init_system();

	/*	main logic.	*/
	while (1) {
		uint8_t i = 0;
		const uint8_t it = 144; /*	How long the display will be lit.	*/

		/*	Refresh the LED n number of times.	*/
		for (i = 0; i < it; i++) {
			display_next_clock_state();
		}
	}

	return 0;
}
