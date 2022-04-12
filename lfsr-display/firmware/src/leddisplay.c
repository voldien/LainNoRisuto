/**
 *	The following code is for the TM1637 4 LED segment controller IC.
 */

#include "dio.h"
#include "lfsh-tiny.h"
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

/*	Full */
const uint8_t EEMEM m_brightness = (0x7 | 0x8);
const uint8_t EEMEM digitSeg[] = {
	0b00111111, /* 0 */
	0b00000110, /* 1 */
	0b01011011, /* 2 */
	0b01001111, /* 3 */
	0b01100110, /* 4 */
	0b01101101, /* 5 */
	0b01111101, /* 6 */
	0b00000111, /* 7 */
	0b01111111, /* 8 */
	0b01101111, /* 9 */
	0b01110111, /* A */
	0b01111100, /* b */
	0b00111001, /* C */
	0b01011110, /* d */
	0b01111001, /* E */
	0b01110001	/* F */
};

/**
 *	Registers commands.
 */
#define TM1637_I2C_COMM1 0x40
#define TM1637_I2C_COMM2 0xC0
#define TM1637_I2C_COMM3 0x80

void ledSegmentDisplayDecNumber() {

	uint8_t digits[4];

	/*	First Digit.	*/
	const uint8_t dig0 = (s0 / 1000);
	digits[0] = ledSegmenentDecodeDigit(dig0);

	/*	Second digit.	*/
	const uint8_t dig1 = (s0 / 100) % 10;
	digits[1] = ledSegmenentDecodeDigit(dig1);

	/*	Third digit.	*/
	const uint8_t dig2 = (s0 / 10) % 10;
	digits[2] = ledSegmenentDecodeDigit(dig2);

	/*	Third digit.	*/
	const uint8_t dig3 = s0 % 10;
	digits[3] = ledSegmenentDecodeDigit(dig3);

	/*	*/
	ledSegmenSet(digits);
}

void ledSegmenSet(const uint8_t *segments) {

	const uint8_t length = 4;
	const uint8_t pos = 0;

	cli();

	/*	Start communication.	*/
	dio_start();
	dio_writeb(TM1637_I2C_COMM1);
	dio_stop();

	/*	Write COMM2 + first digit address	*/
	dio_start();
	dio_writeb(TM1637_I2C_COMM2 + (pos & 0x03));

	/*	Write the data bytes	*/
	for (uint8_t k = 0; k < length; k++)
		dio_writeb(segments[k]);

	dio_stop();

	/*	Write COMM3 + brightness	*/
	const uint8_t brightness = eeprom_read_byte(&m_brightness);
	dio_start();
	dio_writeb(TM1637_I2C_COMM3 + brightness);
	dio_stop();

	sei();
}

uint8_t ledSegmenentDecodeDigit(uint8_t digit) {

	const uint8_t *addr = (const uint8_t *)&digitSeg[digit];

	eeprom_busy_wait();

	/*	Read character from eeprom.	 */
	const uint8_t c = eeprom_read_byte(addr);
	return c;
}
