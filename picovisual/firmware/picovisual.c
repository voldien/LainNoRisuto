#include "picovisual.h"
#include<pico.h>

Settings __not_in_flash() ubo = {
	.nrSamples = 16,
	.c = -2,
	.ci = -2,
	.zoom = 2,
};
