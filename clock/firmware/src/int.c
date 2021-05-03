#include"core/uart.h"
#include"avrclock.h"
#include<stdio.h>
#include<avr/io.h>
#include<avr/interrupt.h>
#include<avr/sleep.h>

ISR(USART_RX_vect){
	/*	Receive command.	*/
	uart_getchar();
	//scanf("");
}

ISR(TIMER2_OVF_vect){
	/*	Internal update loop.	*/

	uart_putstr("button1");
	//sleep_disable();
}

ISR(PCINT2_vect){
	//if(PIND & (1 << PIND4))
//	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
//	sleep_cpu();

	uart_putstr("button0");

	sleep_disable();
}


ISR(WDT_vect){

}

ISR(INT0_vect){

	/*	Get bit state.	*/

}


ISR(INT1_vect){

}


typedef void(*ADCcallback)(uint16_t adc);
static ADCcallback adcCallback[8] = {
	NULL,
};

ISR(ADC_vect){

	/*	Iterate through each valid */
//	uint8t_t char adcl = ADCL;
//	uint8t_t char adch = ADCH;
//	uint16t_t adcVal = (adch << 8) | adcl;

//	ADMUX = (B01000000 | currentAdcChannel);   // Vcc reference, select current channel
}
