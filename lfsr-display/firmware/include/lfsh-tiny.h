/**
	LFSR - Linear feedback shift register random
	number generator board.
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
#ifndef _LFSH_TINY_H_
#define _LFSH_TINY_H_ 1
#include<avr/io.h>
#include<avr/eeprom.h>
#include<avr/interrupt.h>
#include<avr/sleep.h>
#include<avr/pgmspace.h>
#include<avr/fuse.h>
#include"dio.h"
#include"leddisplay.h"

/**
 * Description for each pin associated with the microcontroller
 * Attiny13A.
 *
 * PB0 - CLK
 * PB1 - DIO
 * PB2 - Seed Button
 * PB3 - Next Button
 * PB4 - Seed Input Reference
 * PB5 - Floating
 */

/*	Button pins.	*/
#define seedPin (1 << PINB2)
#define nextPin (1 << PINB3)
#define SeedRefPin (1 << PINB4)

/**
 * Stored seed random number generator.
 */
typedef struct seed_buffer{
	uint16_t s0;
}Seed;
extern Seed EEMEM seed;

/**
 * Random seed value.
 */
extern volatile uint16_t s0;
extern volatile uint16_t s1;

/**
 * Compute next random number
 */
extern void lfsr_pngr(void);

/**
 * Compute next seed value.
 */
extern void next_seed0(void);

#endif
