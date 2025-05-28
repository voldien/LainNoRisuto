/**
	Simple LEDboard MCU driver firmware.
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
#ifndef _LED_BOARD_FIRMWARE_H_
#define _LED_BOARD_FIRMWARE_H_ 1
#include "animation.h"
#include <avr/pgmspace.h>
#include <stddef.h>

/**
 *	Global.
 */
#define SPEED 0

/**
 * Constants.
 */
#define LED_PIN PB0	   /*	PWM.	*/
#define BUTTON_PIN PB1 /*	INT0.	*/

/**
 *
 */
extern const uint8_t mspeed;

/**
 *	Global variable.
 */
extern volatile uint16_t matime;
extern volatile uint16_t mitime;

/**
 * Initialize the controller.
 */
extern void init();

/**
 *
 */
extern void set_ledpwm(const uint8_t pwm);

#endif
