#ifndef _PICO_GRAPHIC_MATH_H_
#define _PICO_GRAPHIC_MATH_H_ 1

#include "cmsis_compiler.h"
#include <arm_acle.h>

#ifndef __SADD16
#define __SADD16(x,y) {x[0] + y[0], x[1] + y[1]}
#endif

#ifndef __SMUAD
#define __SMUAD(x,y) { (x[0] * y[0]) + (x[1] * y[1])}
#endif

typedef int8_t ivec4_8 __attribute__((__vector_size__(4)));	   /*	*/
typedef int16_t ivec2_16 __attribute__((__vector_size__(4)));  /*	*/
typedef int32_t ivec2_32 __attribute__((__vector_size__(8)));  /*	*/

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

inline static int32_t dot_ivec2(const ivec2_32 a, const ivec2_32 b) { return (a[0] * b[0]) + (a[1] * b[1]); }
inline static float dot_vec2(const vec2 *a, const vec2 *b) { return (a->x * b->x) + (a->y * b->y); }

#endif