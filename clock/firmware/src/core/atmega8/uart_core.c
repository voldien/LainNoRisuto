#include"uart.h"
#include<util/setbaud.h>
#include<avr/io.h>

void uart_init(void){

	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;

	//UCSRB = _BV(UCS) | _BV(UCSZ00);
	UCSRA = _BV(RXEN) | _BV(TXEN) | _BV(RXCIE);

}

void uart_putchar(uint8_t c) {
    //loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */

	//loop_until_bit_is_set(UCSR0A, TXC0);	/* Wait until transmission ready. */
	loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
	UDR = c;
}

void uart_putstr(const uint8_t* st){
	while(*st != '\0'){
		uart_putchar(*st);
		st++;
	}
}

uint8_t uart_getchar(void) {
    loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
    return UDR0;
}
