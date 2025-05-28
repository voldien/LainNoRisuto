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
#include"dio.h"
#include<avr/io.h>

/**
 * Display current s0 value to the display.
 */
extern void ledSegmentDisplayDecNumber();

/**
 * Send LED segment set to the display via
 * DIO/CLK pin.
 */
extern void ledSegmenSet(const uint8_t* segments);

/**
 * Get segment encoded of character.
 * @Return
 */
extern uint8_t ledSegmenentDecodeDigit(uint8_t digit);

#endif
