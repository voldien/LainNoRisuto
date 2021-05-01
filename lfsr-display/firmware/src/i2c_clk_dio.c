/*	TODO add credit from original */
#include"dio.h"
#include<avr/delay.h>
#include<avr/pgmspace.h>
#include<avr/eeprom.h>

/*	TODO fix!	*/
#define gdio (1 << PORTB1)
#define gclk (1 << PORTB0)
#define DIOPINR PINB
#define DIODDRR DDRB
#define DIOPORTR PORTB

void dio_init(void){

	/*	Default pin states.	*/
	DIOPORTR |= (gclk | gdio);		/*	Enable ports.	*/
	DIODDRR &= ~(gclk | gdio);		/*	Input mode.	*/
	DIOPINR |= (gclk | gdio);		/*	Default value.	*/
	dio_delay();
}

void dio_writeb(const uint8_t b) {
	uint8_t i;
	uint8_t d = b;

	/*	Iterate through each bit.	*/
	for (i = 0; i < 8; i++) {
		/*	Set clock LOW.	*/
		DIODDRR |= gclk;
		dio_delay();

		/*	Assign */
		const uint8_t bit = (d & 0x1);
		if(bit != 0)
			DIODDRR &= ~gdio;
		else
			DIODDRR |= gdio;

		dio_delay();

		/*	Set clock low.	*/
		DIODDRR &= ~gclk;
		dio_delay();
		d = (d >> 1);
	}

	/*	*/
	DIODDRR |= gclk;
	DIODDRR &= ~gdio;
	dio_delay();

	/*	ACK.	*/
	DIODDRR &= ~gclk;
	dio_delay();
	const uint8_t ack = (DIOPINR & gdio);
	if (ack)
		DIODDRR |= gdio;

	/*	Set clock low.	*/
	dio_delay();
	DIODDRR |= gclk;
	dio_delay();
}

void dio_start(void) {

	/*	Enable data pin output.	*/
	/*	dio output	*/
	DIODDRR |= gdio;
	dio_delay();
}

void dio_stop(void) {

	/*	DIO output.	*/
	DIODDRR |= gdio;
	dio_delay();

	/*	CLK input.	*/
	DIODDRR &= ~gclk;
	dio_delay();

	/*	DIO input.	*/
	DIODDRR &= ~gdio;
	dio_delay();
}

void dio_delay(void) {

	uint8_t y;
	const uint8_t sleep = 0xFF;

	/*	Cheap sleep but not as reliable.	*/
	for(y = 0; y < sleep; y++)
			continue;

	/*	Cheap sleep but not as reliable.	*/
	for(y = 0; y < 16; y++)
			continue;
}
