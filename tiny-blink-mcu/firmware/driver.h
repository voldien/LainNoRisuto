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
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

/**
 * Push Button Registers and Pin
 *
 */
#define PUSH_BUTTON_REG PORTB
#define PUSH_BUTTON_DREG DDRB
#define PUSH_BUTTON_IREG PINB
#define PUSH_BUTTON_PIN PB1

/**
 * Shift Registers Output Enabled
 * Pin and Registers.
 */
#define SHIFT_OE_REG PORTB /*		*/
#define SHIFT_OE_DREG DDRB /*		*/
#define SHIFT_OE_PIN PB2   /*		*/
#define SHIFT_OE_PWM_REG OCR0B

/**
 * Shift Register Shift Clock Pin
 * and Registers
 */
#define SHIFT_RCLK_REG PORTB /*	 	*/
#define SHIFT_RCLK_DREG DDRB /*	 	*/
#define SHIFT_RCLK_PIN PB3	 /*	 	*/

/**
 * Shift Registers Serial Data Pin
 * and Registers
 */
#define SHIFT_DIO_REG PORTB /*		*/
#define SHIFT_DIO_DREG DDRB /*		*/
#define SHIFT_DIO_PIN PB4	/*		*/

/**
 * Shift Registers Latch (Flush Data to Output) Pin
 * and Register
 */
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

#define SPEED_FACTOR 3

/**
 * @brief Control the Running Mode of
 * the board.
 */
#define PLAY_MODE_OUT_ENABLED 0x1
#define PLAY_MODE_AUTO_NEXT_ANIMATION 0x02

/**
 * @brief
 *
 */
extern uint8_t play_mode;
extern uint8_t push_counter_button;

/**
 *	Initialize the controller.
 */
extern inline void init() __attribute__((always_inline));

/**
 *	Set PWM of the shift output pin.
 */
extern void set_pwm(const uint8_t pwm);

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

/**
 * @brief
 *
 */
extern inline void playmode_toggle_output() __attribute__((always_inline));

#endif
