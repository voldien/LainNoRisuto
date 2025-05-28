/**
	Simple Christmascard MCU driver.
	Copyright (C) 2017  Valdemar Lindberg

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
#include <stdio.h>

/**
 *	constant global attributes.
 */
#define ROW0 (1 << PB2)
#define ROW1 (1 << PB1)
#define ROW2 (1 << PB5)
#define ROW3 (1 << PB4)
#define ROWALL (ROW0 | ROW1 | ROW2 | ROW3)
#define ROWPORT PORTB
#define ROWDPORT DDRB
#define NUMROWS 4
#define NUMCOL 8

/**
 *
 */
#define BUTTON_NEXT (1 << PD2)
#define WS2811_PIN PB3
#define WS2811_IN (1 << WS2811_PIN)

/**
 *	Animation and LED.
 */
extern void cc_set_row(const uint8_t r);	  /*	Set current enabled row.	*/
extern void cc_set_col(const uint8_t *d);	  /*	Update LED driver with 8 bytes for current row.	*/
extern void cc_display_next_keyframe();	  /*	Display next current key frame.	*/
extern void cc_select_led_controller();	  /*	Select LED controller.	*/
extern void cc_select_flash_controller(); /*	Select Flash Controller.	*/

/**
 *	Button, controller and timers.
 */
extern void cc_init_nextanibutton();  /*	Initialize next animation button interrupt.	*/
extern void cc_init_ledcontrollers(); /*	Initialize LED controller.	*/
extern void cc_init_time2ovf();		  /*	Enable timer overflow interrupt for update.	*/

#endif
