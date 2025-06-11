#ifndef _PICO_GRAPHIC_MATH_H_
#define _PICO_GRAPHIC_MATH_H_ 1
#include <arm_acle.h>

typedef int8_t ivec4_8 __attribute__((__vector_size__(4)));	  /*	*/
typedef int16_t ivec2_16 __attribute__((__vector_size__(4))); /*	*/
typedef uint16_t uvec2_16 __attribute__((__vector_size__(4))); /*	*/

typedef float hpmvec2f __attribute__((__vector_size__(8))); /*	*/

typedef struct vec2_t {
	float x;
	float y;
} vec2;

typedef struct vec3_t {
	float x;
	float y;
	float z;
} vec3;

inline static void squareImaginary(const vec2 *number, vec2 *result) {
	vec2 tmp;
	tmp.x = (number->x * number->x) - (number->y * number->y);
	tmp.y = 2 * number->x * number->y;

	*result = tmp;
}

inline static float dot(const vec2 *a, const vec2 *b) { return (a->x * b->x) + (a->y * b->y); }

#endif