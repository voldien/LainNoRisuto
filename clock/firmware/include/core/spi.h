
#ifndef _CORE_SPI_H_
#define _CORE_SPI_H_ 1
#include<avr/io.h>

/**
 *
 */
extern void spi_init(void);

/**
 *
 */
extern void spi_fastwrite(uint8_t c);
extern uint8_t spi_fastread(void);
extern uint8_t spi_putchar(uint8_t c);

#endif
