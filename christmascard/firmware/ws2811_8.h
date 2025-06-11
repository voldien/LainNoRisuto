//
// Copyright (c) 2013 Danny Havenith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

/**
 * Library for bit-banging data to WS2811 led controllers.
 * This file contains two implementations of the send() function for ws2811 controllers.
 *
 * The first implementation, send() expects an array of GRB-values and will send those
 * to the given output pin.
 *
 * The second implementation send_sparse() expects an array filled with blocks of LEDS,
 * interspersed with zero LED values.
 */

#ifndef WS2811_96_H_
#define WS2811_96_H_ 1
#include <avr/io.h>
#include <util/delay_basic.h>

#define WS2811_PORT PORTB

struct rgb {

	uint8_t green;
	uint8_t red;
	uint8_t blue;
};

extern void ws2811_send(const void *values, const uint16_t array_size, const uint8_t bit);

#endif /* WS2811_96_H_ */
