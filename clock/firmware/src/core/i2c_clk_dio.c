/*	TODO add credit from original */
#include"core/dio.h"
#include<avr/delay.h>
#include<avr/pgmspace.h>
#include<avr/eeprom.h>

volatile static uint8_t gdio;
volatile static uint8_t gclk;
volatile uint8_t* PIN;
volatile uint8_t* DDR;
volatile uint8_t* PORT;
#define DIOPINR *PIN
#define DIODDRR *DDR
#define DIOPORTR *PORT

void dio_init( volatile uint8_t* __restrict__ pinreg,
		volatile uint8_t* __restrict__ dreg,
		volatile uint8_t* __restrict__ portreg,
		uint8_t dio,
		uint8_t clk){

	/*	Copy pin */
	gdio = (1 << dio);
	gclk = (1 << clk);

	/*	*/
	PIN = pinreg;
	DDR = dreg;
	PORT = portreg;

	/*	Default pin states.	*/
	DIOPORTR |= (gclk | gdio);		/*	Enable ports.	*/
	DIODDRR &= ~(gclk | gdio);		/*	Input mode.	*/
	DIOPINR |= (gclk | gdio);		/*	Default value.	*/
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

void dio_write(const uint8_t* data, uint8_t len) {
	uint8_t i;

	/*	Write each byte.	*/
	for (i = 0; i < len; i++)
		dio_writeb(data[i]);
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
	const uint8_t sleep = 50;
	_delay_us(sleep);
}
