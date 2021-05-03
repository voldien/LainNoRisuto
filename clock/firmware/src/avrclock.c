#include"core/def.h"
#include"core/i2c.h"
#include"core/uart.h"
#include"core/adc.h"
#include"avrclock.h"

#include"clock.h"
#include"temperature.h"
#include"leddisplay.h"

#include<avr/interrupt.h>
#include<avr/builtins.h>
#include<avr/cpufunc.h>
#include<avr/sleep.h>
#include<avr/delay.h>
#include<avr/eeprom.h>
#include<avr/wdt.h>

volatile AVRClockState gstate = { 0 };
const AVRClockState EEMEM defautstate = {
	.display = DISPLAY_TEMP,
	.state = 0
};

void initAVRClock(void){

	cli();

	/*	Initialize I2C.	*/
	i2c_init(i2c_compute_br(F_CPU, F_SCL, 2));
	i2c_dint();

	/*	Initialize UART.	*/
	uart_init();

	/*	Enable external pin interrupt.	*/
	EIMSK |= (1 << INT1) | (1 << INT0);
	EICRA = (1 << ISC01) | (0 <<  ISC00) | (1 << ISC11) | (0 <<  ISC10);

	/*	IR pin change.	*/
	PCIFR |= (1 << PCIF2);
	PCICR |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT20);

	/*	Enable ADC.	*/
	adc_init();

	/*	Enable UART HUI.	*/

	/*	Sleep mode.	*/
	//set_sleep_mode(SLEEP_MODE_ADC);

	/*	Enable time overflow and interrupt.	*/
	ASSR = (1<<AS2);
	TIMSK2 = (1 << TOIE2);
	TIFR2 = (1 << TOV2);

	/*	ADC pins.	*/
	DDRC &= ~((1 << DDC5) | (1 << DDC4));
	PORTC |= (1 << PORTC4) | (1 << PORTC5);

	/*	*/
	DDRC &= ~((1 << DDC0) | (1 << DDC1));
	PORTC |= (1 << PORTC0) | (1 << PORTC0);

	irInit();

	/*	Initialize DIO and each components.	*/
	dio_init(&DIOPIN, &DIODDR, &DIOPORT, pindio, pinclk);
	ledSegmentInit();

	/*	Load init state - saved on the EEPROM.	*/
	eeprom_read_block((void*)&gstate, (const void*)&defautstate, sizeof(defautstate));

	setClockEnable();
	displayEmpty();
	/*	Check if temperature device is present.	*/
	while (!checkTemperaturePresent()){
		displayErrorCode(ERROR_NO_TEMPERATURE_IC);
		uart_putstr("No temperature device!");
		sleep_enable();
		sleep_cpu();
	}

	sei();
}

void displayCurrentTime(void){

	CurrentDayTime time;

	getClockCurrentDayTime(&time);
	logprintf("%d . %d . %d\n", time.sec, time.min, time.hour );

	/*	*/
	const uint16_t curtime = (time.hour * 100 + time.sec);

	cli();
	ledSegmentDisplayDecNumber(curtime, 0, 0, 4, 0);
	sei();
}

void displayCurrentTemperature(void){

	int8_t deg;
	uint8_t degpart;
	const uint8_t celius = ledSegmenentDecodeDigit(0xC);

	getCurrentTemperaturePart(&deg, &degpart);
	logprintf("temperature : %d.%d\n", deg, degpart);
	const uint16_t curdeg = (deg * 10 + degpart);

	/*	*/
	cli();
	ledSegmentDisplayDecNumber(curdeg, 0, 0, 3, 0);
	ledSegmenSet(&celius, 1, 3);
	sei();
}

void displayErrorCode(const uint16_t error){

	/*	*/
	cli();
	ledSegmentDisplayDecNumber(error, 0, 0, 3, 0);
	sei();
}

void displayEmpty(void){
	const uint8_t buf[4] = {0};
	cli();
	ledSegmenSet(buf, 0, sizeof(buf) / sizeof(buf[0]));
	sei();
}
