#include"core/spi.h"
#include<avr/io.h>


void spi_init(void){
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0) | (1 << SPIE);
}

void spi_fastwrite(uint8_t c){

	/*Wait until transmission complete	*/
	while(!(SPSR & (1<<SPIF) ));

	SPDR = c;
}

uint8_t spi_putchar(uint8_t c){

	SPDR = c;

	/*Wait until transmission complete	*/
	while(!(SPSR & (1<<SPIF) ));

	/* Return received data	*/
	return SPDR;
}
