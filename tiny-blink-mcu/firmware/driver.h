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
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <inttypes.h>
#include <stdint.h>


#define PUSH_BUTTON_REG PORTB
#define PUSH_BUTTON_DREG DDRB
#define PUSH_BUTTON_IREG PINB
#define PUSH_BUTTON_PIN PB1
/**
 * Pin Registers.
 */
#define SHIFT_OE_REG PORTB
#define SHIFT_OE_DREG DDRB
#define SHIFT_OE_PIN PB2 /*	OC0A - LED intensity regulator.	*/

#define SHIFT_RCLK_REG PORTB /*	INT0 - Clock inverse.	*/
#define SHIFT_RCLK_DREG DDRB /*	INT0 - Clock inverse.	*/
#define SHIFT_RCLK_PIN PB3	 /*	INT0 - Clock inverse.	*/

#define SHIFT_DIO_REG PORTB /*	Data Input IO pin.	*/
#define SHIFT_DIO_DREG DDRB /*	Data Input IO pin.	*/
#define SHIFT_DIO PB4		/*	Data Input IO pin.	*/

#define SHIFT_LATCH_REG PORTB
#define SHIFT_LATCH_DREG DDRB
#define SHIFT_LATCH_PIN PB0 /*	Shift clock.	*/

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
extern volatile uint16_t mframe; /*	Current frame.	*/
extern volatile int8_t counter;	 /*	Current LED index in the frame.	*/

/**
 * Initialize the controller.
 */
extern void init();

/**
 *
 */
extern void clear_register();

/**
 * Set PWM of the shift output pin.
 */
extern void set_pwm(const uint8_t pwm);

/**
 * @brief 
 * 
 */
extern inline void shift_latch_state(const uint8_t state) __attribute__((always_inline));

/**
 * @brief 
 * 
 */
extern inline void shift_clock_state(const uint8_t state) __attribute__((always_inline));

/**
 * @brief 
 * 
 */
extern inline void write_bit(const uint8_t state) __attribute__((always_inline));

/**
 * Write frame to the shift register.
 */
extern void write_frame(const uint16_t frame);

/**
 * Reset the frame to first key.
 */
extern void frame_done();

#endif
