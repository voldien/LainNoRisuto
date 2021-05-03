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
#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_ 1
#include<avr/io.h>

/**
 *	Get current temperature for major and
 *	minor temperature in decimal.
 */
extern void getCurrentTemperaturePart(int8_t* __restrict__ major, uint8_t* __restrict__ minor);

/**
 *	Get current temperature in encoded format.
 */
extern void getCurrentTemperature(uint16_t* temperature);

/**
 *	Read configuration bits of the temperature IC.
 */
extern void readCurrentConfig(uint8_t* config);

/**
 *
 */
extern void writeCurrentConfig(const uint8_t* config);

/**
 *	Check if the dedicated temperature
 *	IC sensor is present.
 *
 *	@Return non-zero if present and valid.
 */
extern uint8_t checkTemperaturePresent(void);

#endif
