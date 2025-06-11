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
#ifndef _CC_ANIMATION_H_
#define _CC_ANIMATION_H_ 1
#include "christmascard.h"
#include <avr/pgmspace.h>
#include <stddef.h>

/**
 * Animations constants.
 */
#define NRANIM 8	  /*	Number of animations.	*/
#define NRKEYFRAME 32 /*	Number of key frames.	*/
#define RGBRES 3	  /*	RGB LED resolutions.	*/

/**
 * WS2811 data structure.
 * | 3 first green | 5 bit red| 0
 * |     | 5 bit blue | 2 - g | 8
 */
struct rgb_t {
	/*	Compressed RGB.	*/
	uint8_t red5_3green;
	uint8_t green2_blue5;
};

/**
 * Animation key frames.
 */
extern const struct rgb_t PROGMEM animations[NRANIM][NRKEYFRAME][NUMROWS * RGBRES];

/**
 * Global animation variable.
 */
extern volatile uint8_t curanim;
extern volatile uint8_t g_curkeyframe;

/**
 *	Create RGB value compressed.
 */
#define COLORBIT 5
#define COLORRES 0x1F
#define CREATE_RGB_VALUE(b, g, r)											\
{																			\
	(((r & COLORRES) >> 0u) | ((g & COLORRES) << COLORBIT)) & 0xFF,			\
	((((g & COLORRES) >> 2u) & 0b11) | ((b & COLORRES) << 2u)) & 0xFF		\
																			\
}																			


/*	Create single animation frame.	*/
#define CREATE_RGBK_KEY_FRAME(x1,x2,x3,x4,x5,x6,x7,x8,						\
							x9,x10,x11,x12)									\
{																			\
	x1, x2, x3,																\
	x4, x5, x6,																\
	x7, x8, x9,																\
	x10,x11, x12															\
}																			\


/**
 * Create animation.
 */
#define CREATE_ANIMATION(x1,x2,x3,x4,x5,x6,x7,x8,										\
						x9,x10,x11,x12,x13,x14,x15,x16,									\
						x17,x18,x19,x20,x21,x22,x23,x24,								\
						x25,x26,x27,x28,x29,x30,x31,x32)								\
{																						\
																						\
	x1, x2, x3, x4, x5, x6, x7, x8,														\
	x9, x10,x11, x12, x13, x14, x15,													\
	x16, x17, x18, x19, x20, x21, x22,													\
	x23, x24, x25, x26, x27, x28, x29, x30,x31, x32										\
																						\
}

/**
 * Initialize animation.
 */
extern void cc_init_animation();

/**
 * Get current key frame row and column values.
 */
extern uint8_t cc_get_curr_animation_keyframe(const uint8_t r, const uint8_t c);

/**
 * Change to next key frame.
 */
extern void cc_next_frame();

/**
 * Check if next animation is ready.
 */
extern const uint8_t cc_next_animation_ready();

/**
 *	Reset and set next animation.
 */
extern inline void cc_reset_for_next_animation() __attribute__((always_inline));

#endif
