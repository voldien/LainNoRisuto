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
#ifndef _LB_ANIMATION_H_
#define _LB_ANIMATION_H_ 1
#include<stddef.h>
#include<avr/pgmspace.h>

#define NRANIM 16		/*	*/
#define NRANIMENTRY 32	/*	*/
#define LEDRES 4		/*	*/

/**
 *	Animation clip, containing a
 *	section of animation key frames.
 */
struct animation_t{
	uint8_t ani[NRANIMENTRY / 2];	/*	16 Animation frames.	*/
};

/**
 * Animation key frames.
 */
extern const struct animation_t PROGMEM ani[NRANIM];

/**
 * Global animation variable.
 */
extern volatile uint8_t curanim;
extern volatile uint8_t curaniindex;

/**
 *	Create macro for creating
 *	animation block.
 */
#define CREATE_ANIMIATION(x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,						\
						x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32)				\
	{																									\
		((uint8_t)(x1 << 4)  | (uint8_t)(x2 & 0xF) ), ((uint8_t)(x3 << 4)  | (uint8_t)(x4  & 0xF)),		\
		((uint8_t)(x5 << 4)  | (uint8_t)(x6 & 0xF) ), ((uint8_t)(x7 << 4)  | (uint8_t)(x8  & 0xF)),		\
		((uint8_t)(x9 << 4)  | (uint8_t)(x10 & 0xF)), ((uint8_t)(x11 << 4) | (uint8_t)(x12 & 0xF)),		\
		((uint8_t)(x13 << 4) | (uint8_t)(x14 & 0xF)), ((uint8_t)(x15 << 4) | (uint8_t)(x16 & 0xF)),		\
																										\
		((uint8_t)(x17 << 4)  | (uint8_t)(x18 & 0xF) ), ((uint8_t)(x19 << 4) | (uint8_t)(x20 & 0xF)),	\
		((uint8_t)(x21 << 4)  | (uint8_t)(x22 & 0xF) ), ((uint8_t)(x23 << 4) | (uint8_t)(x24 & 0xF)),	\
		((uint8_t)(x25 << 4)  | (uint8_t)(x26 & 0xF)),  ((uint8_t)(x27 << 4) | (uint8_t)(x28 & 0xF)),	\
		((uint8_t)(x29 << 4)  | (uint8_t)(x30 & 0xF)),  ((uint8_t)(x31 << 4) | (uint8_t)(x32 & 0xF))	\
	}																									\

/**
 *
 */
extern void init_animation(void);

extern uint8_t intp(uint8_t a, uint8_t b, uint8_t t);

/**
 *
 */
extern const uint8_t get_curr_next_animation_keyframe(void);

/**
 *	Reset and set next animation.
 */
extern void reset_for_next_animation(void);


#endif
