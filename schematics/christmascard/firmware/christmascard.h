/**
	Simple Christmascard MCU driver.
	Copyright (C) 2017 Valdemar Lindberg

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _CHRISTMAS_CARD_H_
#define _CHRISTMAS_CARD_H_ 1

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

/**
 *	constant global attributes.
 */
#define NUMROWS 4
#define NUMCOL 8

extern void init_system();

/**
 *	Animation and LED.
 */
extern void cc_set_row(const uint8_t row_index); /*	Set current enabled row.	*/
extern void cc_set_col(const uint8_t *d);		 /*	Update LED driver with 8 bytes for current row.	*/
extern void cc_display_next_keyframe();			 /*	Display next current key frame.	*/
extern void cc_select_led_controller();			 /*	Select LED controller.	*/
extern void cc_select_flash_controller();		 /*	Select Flash Controller.	*/

/**
 *	Button, controller and timers.
 */
extern inline void cc_init_nextanibutton()
	__attribute__((always_inline)); /*	Initialize next animation button interrupt.	*/
extern inline void cc_init_ledcontrollers() __attribute__((always_inline)); /*	Initialize LED controller.	*/
extern inline void cc_init_time2ovf() __attribute__((always_inline)); /*	Enable timer overflow interrupt for update.
																	   */

/**
 * @brief true => Pressed, false => Not-Pressed
 */
extern inline uint8_t push_buton_pressed() __attribute__((always_inline));

/**
 * Set Latch Signal High (1) Low (0)
 */
extern inline void shift_latch_state(const uint8_t state) __attribute__((always_inline));

/**
 * Set Shift Clock Signal High (1) Low (0)
 */
extern inline void shift_clock_state(const uint8_t state) __attribute__((always_inline));

/*
 * Set Serial Data Signal High (1) Low (0)
 */
extern inline void write_bit(const uint8_t state_lsb) __attribute__((always_inline));

/**
 *	Set output. true => Enabled, false => Disabled
 */
extern inline void shift_oe_state(const uint8_t output_enabled) __attribute__((always_inline));

#endif
