/**

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
#ifndef _AVR_CLOCK_H_
#define _AVR_CLOCK_H_ 1
#include"core/debug.h"


/**
 *
 */
#define DISPLAY_NONE 0x0
#define DISPLAY_TIME 0x1
#define DISPLAY_TEMP 0x2
#define DISPLAY_HUI	 0x3

/**
 *
 */
#define STATE_NONE	0x0
#define STATE_RADIO 0x1


/**
 *
 */
#define ERROR_NO_TEMPERATURE_IC 0x5C

/**
 *	Clock global state.
 */
typedef struct avr_clock_state_t{
	uint8_t display;	/*	Display mode.	*/
	uint8_t state;		/*	Internal state flag.	*/
}AVRClockState;

/**
 *
 */
extern volatile AVRClockState gstate;
extern volatile struct queue_t ircommand;

/**
 *
 */
extern void initAVRClock(void);

/**
 *
 */
extern void displayCurrentTime(void);

/**
 *
 */
extern void displayCurrentTemperature(void);

/**
 *
 */
extern void displayErrorCode(const uint16_t error);

/**
 *
 */
extern void displayEmpty(void);

/**
 *
 */
extern void updateDisplay(void);

#endif
