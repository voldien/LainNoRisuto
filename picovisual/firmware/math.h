#ifndef _PICO_GRAPHIC_MATH_H_
#define _PICO_GRAPHIC_MATH_H_ 1
#include "picovisual.h"
#include <stdint.h>

typedef struct vec2_t {
	float x;
	float y;
} vec2;

typedef struct ivec2_t {
	int32_t x;
	int32_t y;
} ivec2;

inline static void squareImaginary(const vec2 *number, vec2 *result) {
	vec2 tmp;
	tmp.x = (number->x * number->x) - (number->y * number->y);
	tmp.y = 2 * number->x * number->y;

	*result = tmp;
}

inline float dot(const vec2 *a, const vec2 *b) { return (a->x * b->x) + (a->y * b->y); }

#endif