#include"lfsh-tiny.h"
#include"leddisplay.h"
#include"dio.h"

__fuse_t FUSEMEM fuse = {
		.low = LFUSE_DEFAULT,
		.high = HFUSE_DEFAULT
};

Seed EEMEM seed = {
	.s0 = 6378
};

/*	*/
volatile uint16_t s0;
volatile uint16_t s1;

void lfsr_pngr(void){
	/*	Primitive polynomial.	*/
	/*	p_0 + p_1x^1 + p_3x^3 + p_5x^5 + x^16.	*/

	/*	Feedback on index = [0, 1, 3, 5].	*/
	s0 = (s0 >> 0x01U) ^ (-(s0 & 0x01U) & 0xB400U);

	s0 %= 10000;
}

void next_seed0(void){
	s0 = s1 % 10000;
	eeprom_write_word(&seed.s0, s0);
}

static void timer_compare_callback(void){

	/*	Check if pressed if pin is low.	*/
	if((PINB & nextPin) == 0)
		lfsr_pngr();

	/*	Disable interrupt..	*/
	sleep_disable();
}

/*	Listen to compare based on the button being pressed.	*/
ISR(TIM0_COMPA_vect){
	timer_compare_callback();
	/*	Check if pressed if pin is low.	*/
//	if((PINB & nextPin) == 0)
//		lfsr_pngr();

	/*	Disable interrupt..	*/
//	sleep_disable();
}

static void timer_ovf_callback(void){
	TIFR0 = (1 << TOV0);  // shouldn't be needed according to the documentation, but is (perhaps the ISR is too short without it?)

	sleep_disable();
	/*	Enable and start ADC conversation.	*/
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADIF) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	lfsr_pngr();
    sleep_disable();
}

ISR(TIM0_OVF_vect){
	timer_ovf_callback();
}

static void pin_down_callback(void){

	/*	Both pins high implies no button is pressed.	*/
	if((PINB & seedPin) == seedPin
			|| (PINB & nextPin) == nextPin){
		/*	Disable pin.	*/
	    TIMSK0 &= ~(1 << OCIE0A);
	}

	/*	Both pins are not equal implies either one is pressed.	*/
	if((PINB & seedPin) != (PINB & nextPin)){

		/*	Reset timer and enable interrupt.	*/
		TIMSK0 |= (1 << OCIE0A);
		TCNT0 = 0;

		/*	If seed pin is low.	*/
		if((PINB & seedPin) == 0)
			next_seed0();
	}

}

ISR(PCINT0_vect){
	pin_down_callback();
}

ISR(ADC_vect){

	/*	Compute 10-bit ADC value.	*/
	const uint8_t adcl = ADCL;
	const uint8_t adch = ADCH;
	uint16_t adcVal = (adch << 8) | adcl;

	/*	*/
	s1 = adcVal;
}

void init_firmware(void){

	const uint8_t digit[4] = {0, 0, 0, 0};

	cli();

	/*	*/
	eeprom_busy_wait();
	s0 = eeprom_read_word(&seed.s0);

    TCCR0A = 0;	/*	set entire TCCR0A register to 0	*/
    TCCR0B = 0;	/*	same for TCCR0B	*/
    TCNT0  = 0;	/*	initialize counter value to 0	*/

    // set compare match register for 200khz increments
    OCR0A = 92;// = (20*10^6) / (200000*1) - 1 (must be <256 for 8 bit timer)
    OCR0B = 128;

    /*	Turn on CTC Mode.	*/
    TCCR0A |= (0 << WGM02) | (1 << WGM01) | (0 << WGM00);

    /*	Compare mode.	*/
    TCCR0A |= (1 << COM0A0) | (1 << COM0A1) | (0 << COM0B0) | (0 << COM0B1);

    /* 10^-1/(1/4*10^6) = 10^-1*4*10^6 => 4*10^5/10^3 = 400.	*/
    TCCR0B |= (1 << CS02) | (0 << CS01) | (1 << CS00);

    /* Enable timer compare interrupt	*/
    TIMSK0 = (1 << OCIE0A) | (1 << TOIE0);

	/*	Enable pin change interrupt.	*/
	GIMSK = (1 << PCIE);
	PCMSK = (1 << PCINT3) | (1 << PCINT2);  // set PCINT0 to trigger an interrupt on state change

	/*	Enable ADC.	*/
	ADMUX = (0 << REFS0) | (0 << ADLAR) | (1 << MUX1) | (0 << MUX0);
	ADCSRB = 0; // Analog Input bank 1
	ADCSRA = (1 << ADEN) | (1 << ADIF) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	/*	Enable IO ports.	*/
    DDRB = (0 <<PORTB4) | ( 0 << PORTB3) | (0 << PORTB5)| ( 1 << PORTB0) | (1 << PORTB1) | (0 << PORTB2);
    PORTB = (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB4) | (1 << PORTB5) | (1 << PORTB3) | (0 << PORTB2);

    /*	*/
	dio_init();

	ledSegmenSet(digit);

	sei();
}


int main(void){

	init_firmware();

	/*	*/
	while(1){
		/*	Display current led;*/
		ledSegmentDisplayDecNumber();
		/*		*/
		set_sleep_mode(SLEEP_MODE_IDLE);
		sleep_enable();
		sleep_cpu();

		dio_delay();
	}
	return 0;
}
