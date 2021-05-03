/**
 *
 */
#ifndef _DIO_H_
#define _DIO_H_ 1
#include"def.h"
#include<avr/io.h>

/**
 * Initialize DIO protocol.
 */
extern void dio_init( volatile uint8_t* __restrict__ pinreg,
		volatile uint8_t* __restrict__ dreg,
		volatile uint8_t* __restrict__ portreg,
		uint8_t dio,
		uint8_t clk);

/**
 *
 */
extern void dio_writereg(uint8_t command, const uint8_t* data, uint8_t len);

/**
 *	Write byte.
 */
extern void dio_writeb(const uint8_t b);

/**
 *
 */
extern void dio_write(const uint8_t* data, uint8_t len);

/**
 *	Start communication.
 */
extern void dio_start(void);

/**
 *	Stop communiation.
 */
extern void dio_stop(void);

/**
 *
 */
extern void dio_delay(void);

#endif
