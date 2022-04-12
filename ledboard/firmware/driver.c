#include "ledboard.h"
#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>

const uint8_t mspeed = (1 << SPEED); /*	*/

/**
 *	Interrupt for button pressed.
 */
ISR(INT0_vect) { reset_for_next_animation(); }

void init() {

	cli();

	/**
	 * Initialize PINS states.
	 * Button Input mode
	 * LED output source mode.
	 */
	DDRB = (1 << LED_PIN) | (0 << BUTTON_PIN);	/*	Data direction.	*/
	PORTB = (1 << LED_PIN) | (1 << BUTTON_PIN); /*	Enable ports.	*/

	/**
	 * Mode: fast PWM.
	 * Frequency: 9.6 MHZ / 8
	 *
	 */
	TCCR0B = (1 << WGM02) | (1 << CS02) | (0 << CS01) | (1 << CS00); /*	*/
	TCCR0A = (1 << WGM01) | (1 << WGM00);

	/**
	 * Override port and toggle on OCRA pin.
	 */
	TCCR0A |= (0 << COM0A1) | (1 << COM0A0);

	/*	*/
	// TIMSK0 = (1 << OCIE0B); /*	Enable timer counter interrupts.	*/
	// OCR0B = 255;

	/*	*/
	set_ledpwm(255);

	/*	Enable INT0 interrupt for the button.	*/
	GIMSK = (0 << PCIE) | (1 << INT0);	  /*	Enable INT0 interrupts.	*/
	MCUCR |= (1 << ISC01) | (1 << ISC00); /*	Trigger INTO on rising edge - button pressed.	*/

	/*	*/
	// set_sleep_mode(SLEEP_MODE_IDLE);
	// sleep_enable();

	/*	*/
	init_animation();

	/*	Enable global interrupts.	*/
	sei();
	/*	SREG |= (1 << SREG_I) */
}

void set_ledpwm(const uint8_t pwm) { OCR0A = pwm; }

int main() {

	/*	*/
	init();

	while (1) {
		/*	*/
		set_ledpwm(get_curr_next_animation_keyframe());

		/*	*/
		_delay_ms(16);
		// sleep_cpu();
	}

	return 0;
}
