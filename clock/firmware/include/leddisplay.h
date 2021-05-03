/**

    Copyright (C) 2018  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the Gdio_writebNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _LED_DISPLAY_H_
#define _LED_DISPLAY_H_ 1
#include"core/dio.h"
#include<avr/io.h>

/**
 *	Initialize the LED segment display.
 */
extern void ledSegmentInit(void);

/**
 *	Set display intensity.
 *
 *	\brightness from 0 - 8.
 *
 *	\on
 */
extern void ledSegmenIntensity(uint8_t brightness, uint8_t on);

/**
 *
 */
extern void ledSegmentDisplayDecNumber(uint16_t dec, uint8_t dots, uint8_t leading_zero, uint8_t length, uint8_t pos);

/**
 *
 */
extern void ledSegmentDisplayDecHexdecimal(uint16_t dec, uint8_t dots, uint8_t leading_zero, uint8_t length, uint8_t pos);

/**
 *
 */
extern void ledSegmenSet(const uint8_t* __restrict__ segments, uint8_t length,
        uint8_t pos);

/**
 *	Get segment encoded of character.
 *	@Return
 */
extern uint8_t ledSegmenentDecodeDigit(uint8_t digit);

#endif
