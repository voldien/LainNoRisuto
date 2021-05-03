
#ifndef _UART_CORE_H_
#define _UART_CORE_H_ 1
#include"def.h"
#include<avr/io.h>

/*	Serial - UART	*/
extern void uart_init(void);

/**
 * Write one character to serial.
 */
extern void uart_putchar(const uint8_t c);

/**
 * Write character string to serial.
 */
extern void uart_putstr(const int8_t* str);

/**
 * Read character from serial.
 */
extern uint8_t uart_getchar(void);

#endif
