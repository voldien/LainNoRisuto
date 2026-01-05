#ifndef VC_JOYSTICK_
#define VC_JOYSTICK_ 1

#include <stdint.h>

#define ANALOG_ADC_PINS ADC_BASE_PIN
#define ANALOG_ADC_COUNT 4
 
extern int16_t get_joystic_axis(const uint16_t index);

#endif