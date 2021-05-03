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
#ifndef _CLOCK_H_
#define _CLOCK_H_ 1
#include<avr/io.h>

/**
 *
 */
typedef struct current_date_time_t{
	uint8_t day;	/*	*/
	uint8_t date;	/*	*/
	uint8_t year;	/*	*/
}CurrentDateTime;

/**
 *
 */
typedef struct current_day_time_t{
	uint8_t sec;	/*	*/
	uint8_t min;	/*	*/
	uint8_t hour;	/*	*/
}CurrentDayTime;

/**
 *
 */
typedef struct clock_settings_t{
	uint8_t control;	/*	*/
}ClockControlSettings;

/**
 *
 */
extern void setClockEnable(void);

/**
 * Get current day time.
 */
extern void getClockCurrentDayTime(CurrentDayTime* time);

/**
 * Get current date.
 */
extern void getClockCurrentDate(CurrentDateTime* pdate);

/**
 * Set control attribute of the IC.
 */
extern void setClockControl(ClockControlSettings* control);

#endif
