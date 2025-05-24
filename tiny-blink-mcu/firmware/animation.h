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
#ifndef _TINY_BLINK_ANIMATION_H_
#define _TINY_BLINK_ANIMATION_H_ 1
#include <avr/pgmspace.h>
#include <stddef.h>

/**
 * Animation settings. Need to
 * be in a power of two for better
 * performance.
 */
#define NRANIM 8
#define NRANIMENTRY 32
#define PWMRESOLUTION 4

/**
 *	Animation clip, containing a
 *	section of animation key frames.
 */
struct animation_t {
	uint16_t ani[NRANIMENTRY]; /*	32 Animation key frames.	*/
};

/**
 * Animation chunk and controller
 * variables.
 */
extern const struct animation_t PROGMEM ani[NRANIM];
extern uint8_t curanim;
extern uint8_t curaniindex;

/**
 * Create single frame
 */
#define CREATE_FRAME(x1)                                                                                               \
	(((x1 & 0x1) << 0) | ((x1 & 0x2) << 1) | ((x1 & 0x4) << 2) | ((x1 & 0x8) << 3) | ((x1 & 0x10) << 4) |         \
	 ((x1 & 0x20) << 5) | ((x1 & 0x40) << 6) | ((x1 & 0x80) << 7) | ((x1 & 0x100) << 8) | ((x1 & 0x200) << 9) |       \
	 ((x1 & 0x400) << 10) | ((x1 & 0x800) << 11) | ((x1 & 0x1000) << 12) | ((x1 & 0x2000) << 13) | ((x1 & 0x4000) << 14) |  \
	 ((x1 & 0x8000) << 15))

/**
 * Create PWM value.
 */
#define CREATE_PWM_VALUE(pwm, frameindex) (pwm << 16) << (frameindex % 4) * 2

/**
 *
 */
#define GET_PWM_VALUE(x, index) (x) >> ((index % 4) * 2)

/**
 *
 */
#define GET_PWM_8VALUE(x, index) GET_PWM_VALUE(x, index) * 8u

/**
 *	Create macro for creating
 *	animation block.
 */
#define CREATE_ANIMIATION(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20,   \
						  x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32)                                  \
	{                                                                                                                  \
		{                                                                                                              \
			CREATE_FRAME(x1), CREATE_FRAME(x2), CREATE_FRAME(x3), CREATE_FRAME(x4), CREATE_FRAME(x5),                  \
				CREATE_FRAME(x6), CREATE_FRAME(x7), CREATE_FRAME(x8), CREATE_FRAME(x9), CREATE_FRAME(x10),             \
				CREATE_FRAME(x11), CREATE_FRAME(x12), CREATE_FRAME(x13), CREATE_FRAME(x14), CREATE_FRAME(x15),         \
				CREATE_FRAME(x16), CREATE_FRAME(x17), CREATE_FRAME(x18), CREATE_FRAME(x19), CREATE_FRAME(x20),         \
				CREATE_FRAME(x21), CREATE_FRAME(x22), CREATE_FRAME(x23), CREATE_FRAME(x24), CREATE_FRAME(x25),         \
				CREATE_FRAME(x26), CREATE_FRAME(x27), CREATE_FRAME(x28), CREATE_FRAME(x29), CREATE_FRAME(x30),         \
				CREATE_FRAME(x31), CREATE_FRAME(x32)                                                                   \
		}                                                                                                              \
	}

/**
 * Get current animation key frame.
 */
extern uint16_t cc_get_curr_next_animation_keyframe();

/**
 *	Reset and set next animation.
 */
extern inline void reset_for_next_animation() __attribute__((always_inline));

#endif
