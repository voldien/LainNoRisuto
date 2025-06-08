#ifndef _PICO_GRAPHIC_
#define _PICO_GRAPHIC_ 1
#include "math.h"
#include <pico.h>
#include <stdint.h>

typedef struct settings_t {
	vec2 pos;
	vec2 mousePos;
	float zoom; /*  */
	float c;	/*  */
	float ci;
	int nrSamples;
} Settings;

extern Settings __not_in_flash() ubo;

#endif