#include "joystick.h"
#include "hardware/adc.h"
#include <stdint.h>

int16_t get_joystic_axis(const uint16_t index) {
	const uint16_t adc_max = (1 << 12) - 1u;
	const uint16_t adc_half_max = (1 << 11);

	/*	*/
	adc_select_input(index);
	const uint16_t value = adc_read();

	/*	*/
	const int16_t v = ((int16_t)value) - adc_half_max;
	const int16_t dead_span = 0;
	/*	*/
	return v + dead_span;
}