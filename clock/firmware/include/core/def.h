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
#ifndef _AVR_CLOCK_DEF_H_
#define _AVR_CLOCK_DEF_H_ 1
#include<avr/io.h>

/*	Set default frequency.	*/
#ifndef F_SCL
	#define F_SCL 100000UL /* SCL frequency	*/
#endif

/*	Set default baud rate.	*/
#ifndef BAUD
	#define BAUD 9600
#endif

#if defined(__AVR_ATmega328P__)
	#define SPIPORTS ( 1<<PD0) | (1 << PD1);
	#define I2CPORTS (1<<PD0) | (1 << PD1);
	#define UARTPORTS (1 << PD0) | (1 << PD1);
	#define BUTTONPORTS (1<<PD0) | (1 << PD1);
	#define pinclk PB0
	#define pindio PB1
	#define DIOPIN PINB
	#define DIODDR DDRB
	#define DIOPORT PORTB
#endif

#endif
