/**
 *
 */
#ifndef _DIO_H_
#define _DIO_H_ 1
#include<avr/io.h>

/**
 * Initialize DIO protocol.
 */
extern void dio_init(void);

/**
 *
 */
extern void dio_writereg(uint8_t command, const uint8_t* data, uint8_t len);

/**
 *	Write byte.
 */
extern void dio_writeb(const uint8_t b);

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
