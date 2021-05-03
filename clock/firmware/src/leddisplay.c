/**
 *	The following code is for the TM1637 4 LED segment controller IC.
 */

#include"leddisplay.h"
#include"core/dio.h"
#include"core/debug.h"
#include<avr/pgmspace.h>

volatile uint8_t m_brightness = (0x7 | 0x8);
const uint8_t PROGMEM digitSeg[] = {
	0b00111111,		/* 0 */
	0b00000110,		/* 1 */
	0b01011011,    /* 2 */
	0b01001111,    /* 3 */
	0b01100110,    /* 4 */
	0b01101101,    /* 5 */
	0b01111101,    /* 6 */
	0b00000111,    /* 7 */
	0b01111111,    /* 8 */
	0b01101111,    /* 9 */
	0b01110111,    /* A */
	0b01111100,    /* b */
	0b00111001,    /* C */
	0b01011110,    /* d */
	0b01111001,    /* E */
	0b01110001     /* F */
};

/**
 *	Registers commands.
 */
#define TM1637_I2C_COMM1	0x40
#define TM1637_I2C_COMM2	0xC0
#define TM1637_I2C_COMM3	0x80

void ledSegmentInit(void){
	ledSegmenIntensity(0x7, 0x1);
}

void ledSegmenIntensity(uint8_t brightness, uint8_t on) {
	m_brightness = (brightness & 0x7) | (on ? 0x08 : 0x00);
	logprintf("Intensity - %d.\n", brightness & 0x7);
}

void ledSegmentDisplayDecNumber(uint16_t dec, uint8_t dots, uint8_t leading_zero, uint8_t length, uint8_t pos){

	uint8_t digits[4];
	const static uint16_t divisors[] = { 1, 10, 100, 1000 };
	uint8_t leading = 1;

	/*	*/
	for(int8_t k = 0; k < 4; k++) {

		uint16_t divisor = divisors[(4 - 1) - k];
		uint16_t d = dec / divisor;
		uint8_t digit = 0;

		if (d == 0) {
			if (leading_zero || !leading || (k == 3))
				digit = ledSegmenentDecodeDigit(d);
			else
				digit = 0;
		}
		else {
			digit = ledSegmenentDecodeDigit(d);
			dec -= d * divisor;
			leading = 0;
		}

		// Add the decimal point/colon to the digit
		digit |= (dots & 0x80);
		dots <<= 1;

		digits[k] = digit;
	}

	ledSegmenSet(digits + (4 - length), length, pos);
}

void ledSegmenSet(const uint8_t* __restrict__ segments, uint8_t length, uint8_t pos) {

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
	dio_start();
	dio_writeb(TM1637_I2C_COMM3 + (m_brightness & 0xF));
	dio_stop();
}

uint8_t ledSegmenentDecodeDigit(uint8_t digit){
	const uint16_t* addr = (const uint16_t*)&digitSeg[digit & 0xf];
	return pgm_read_byte_near(addr);
}
