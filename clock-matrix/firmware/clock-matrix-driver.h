/**
	Tiny blink animation firmware
	Copyright (C) 2018  Valdemar Lindberg

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
#ifndef _CLOCK_MATRIX_DRIVER_H_
#define _CLOCK_MATRIX_DRIVER_H_ 1

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include"i2c.h"

#ifdef E2END
#include <avr/eeprom.h>
#endif

/**
 * Push Button Registers and Pin
 *
 */
#define PUSH_BUTTON_REG PORTB
#define PUSH_BUTTON_DREG DDRB
#define PUSH_BUTTON_IREG PINB
#define PUSH_BUTTON_PIN PB4

/**
 * Shift Registers Output Enabled (SNx4HC595)
 * Pin and Registers.
 */
#define SHIFT_OE_REG PORTB /*		*/
#define SHIFT_OE_DREG DDRB /*		*/
#define SHIFT_OE_PIN PB0   /*		*/
#define SHIFT_OE_PWM_REG OCR0B

/**
 * Shift Register Shift Clock Pin (SNx4HC595)
 * and Registers  (RCLK)
 */
#define SHIFT_RCLK_REG PORTB /*	 	*/
#define SHIFT_RCLK_DREG DDRB /*	 	*/
#define SHIFT_RCLK_PIN PB1	 /*	 	*/

/**
 * Shift Registers Serial Data Pin (SNx4HC595)
 * and Registers
 */
#define SHIFT_DIO_REG PORTB /*		*/
#define SHIFT_DIO_DREG DDRB /*		*/
#define SHIFT_DIO_PIN PB2	/*		*/

/**
 * Shift Registers Latch (Flush Data to Output) Pin (SNx4HC595)
 * and Register  (SRCLR)
 */
#define SHIFT_LATCH_REG PORTB
#define SHIFT_LATCH_DREG DDRB
#define SHIFT_LATCH_PIN PB3 /*	Shift clock.	*/

extern void init_i2c();

extern void init_clock();

#endif
