#include"core/uart.h"
#include<util/setbaud.h>
#include<avr/io.h>

/*	Serial	*/
void uart_init(void){

	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
	UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);

}

void uart_putchar(const uint8_t c) {
	loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
	UDR0 = c;
}


void uart_putstr(const int8_t* str){
	while(*str != '\0'){
		uart_putchar(*str);
		str++;
	}
}

uint8_t uart_getchar(void) {
    loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
    return UDR0;
}
