#include"core/def.h"

/*	TODO remove according to the design!	*/
#include"core/adc.h"

#include"avrclock.h"
#include"clock.h"
#include"temperature.h"
#include"leddisplay.h"

#include<avr/interrupt.h>
#include<avr/builtins.h>
#include<avr/cpufunc.h>
#include<avr/sleep.h>

int main(void){

	/*	*/
	initAVRClock();

	/*	Main loop.	*/
	while(1){

		/*	Display.	*/
		switch(gstate.display){
		case DISPLAY_TEMP:
			displayCurrentTemperature();
			break;
		case DISPLAY_HUI:
			break;
		default:
		case DISPLAY_TIME:
			displayCurrentTime();
			break;
		}

		/*	Sleep in till an interrupt is issued.	*/
		sleep_enable();
		sleep_cpu();

		/*	Read current display value.		*/
		const uint8_t nrIntensity = (1024 / 8);
		ledSegmenIntensity(adc_read(0) / nrIntensity, 0x1);

		/*	*/
		if(gstate.state & STATE_RADIO){
			/*	Frequency.	*/
			//adc_read(1);

			/*	Volume.	*/
			//adc_read(2);
		}
	}

	return 0;
}
