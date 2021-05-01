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
#ifndef _TINY_BLINK_H_
#define _TINY_BLINK_H_ 1
#include<avr/io.h>
#include<avr/interrupt.h>
#include<avr/pgmspace.h>
#include<avr/sleep.h>

/**
 * Pin Registers.
 */
#define SHIFT_PWM PB0	/*	OC0A - LED intensity regulator.	*/
#define SHIFT_RCLK PB1	/*	INT0 - Clock inverse.	*/
#define SHIFT_DIO PB2	/*	Data Input IO pin.	*/
#define SHIFT_RSHIF PB3	/*	Shift clock.	*/

/**
 * Number of physical LEDs.
 */
#define NRLED 16

/**
 * Default intensity value [0, 255].
 */
#define LED_INTENSITY 255

/**
 * Internal frame and counter.
 */
extern volatile uint16_t mframe;	/*	Current frame.	*/
extern volatile int8_t counter;		/*	Current LED index in the frame.	*/

/**
 * Initialize the controller.
 */
extern void init(void);

/**
 *
 */
extern void clear_register(void);

/**
 * Set PWM of the shift output pin.
 */
extern void set_pwm(const uint8_t pwm);

/**
 *
 */
extern void shift_clock_state(const uint8_t state);

/**
 *
 */
extern void write_bit(const uint8_t state);

/**
 * Write frame to the shift register.
 */
extern void write_frame(const uint16_t frame);

/**
 * Reset the frame to first key.
 */
extern void frame_done(void);

#endif
