#include"core/adc.h"
#include<avr/io.h>

void adc_init(void){

	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	/*	*/
	ADCSRA |= (1 << ADIE);
}

uint16_t adc_read(const uint8_t ch){

	/*	Clear channel.	*/
	ADMUX &= 0xf0;
	/*	Set current channel.	*/
	ADMUX |= ch;

	/*	Start reading.	*/
	ADCSRA |= (1 << ADSC);

	/*	Wait in till reading is complete.	*/
	while ( (ADCSRA & _BV(ADSC)) );

	/*	*/
	ADCSRA|=(1<<ADIF);
	/*ADCSRA|=(1<<ADIF);	*/
	return ADC;
}
