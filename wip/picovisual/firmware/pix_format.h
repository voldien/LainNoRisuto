#pragma once
#include "graphic_math.h"
#include <stddef.h>
#include <stdint.h>

// These constants are 14b fixed-point version of ITU-R BT.601 constants.
#define kYScale 19077 // 1.164 = 255 / 219
#define kVToR 26149	  // 1.596 = 255 / 112 * 0.701
#define kUToG 6419	  // 0.391 = 255 / 112 * 0.886 * 0.114 / 0.587
#define kVToG 13320	  // 0.813 = 255 / 112 * 0.701 * 0.299 / 0.587
#define kUToB 33050	  // 2.018 = 255 / 112 * 0.886
#define kRCst (-kYScale * 16 - kVToR * 128 + YUV_HALF2)
#define kGCst (-kYScale * 16 + kUToG * 128 + kVToG * 128 + YUV_HALF2)
#define kBCst (-kYScale * 16 - kUToB * 128 + YUV_HALF2)

#define YUV_FIX 0
static inline int VP8ClipUV(int uv, int rounding) {
	uv = (uv + rounding + (128 << (YUV_FIX + 2))) >> (YUV_FIX + 2);
	return ((uv & ~0xff) == 0) ? uv : (uv < 0) ? 0 : 255;
}

#define USE_YUVj
#ifndef USE_YUVj
static inline int VP8RGBToY(int r, int g, int b, int rounding) {
	const int luma = 16839 * r + 33059 * g + 6420 * b;
	return (luma + rounding + (16 << YUV_FIX)) >> YUV_FIX; // no need to clip
}

static inline int VP8RGBToU(int r, int g, int b, int rounding) {
	const int u = -9719 * r - 19081 * g + 28800 * b;
	return VP8ClipUV(u, rounding);
}

static inline int VP8RGBToV(int r, int g, int b, int rounding) {
	const int v = +28800 * r - 24116 * g - 4684 * b;
	return VP8ClipUV(v, rounding);
}
#else

static inline int VP8RGBToY(int r, int g, int b, int rounding) {
	return (76284 * r + 150493 * g + 29681 * b) >> 16;

	const int luma = (19595 * r) + (38470 * g) + ((long)(7471 * b));
	return (luma + rounding) >> YUV_FIX; // no need to clip
}
static inline int VP8RGBToU(int r, int g, int b, int rounding) {
	const int u = -11058 * r - 21710 * g + 32768 * b;
	return VP8ClipUV(u, rounding);
}
static inline int VP8RGBToV(int r, int g, int b, int rounding) {
	const int v = 32768 * r - 27439 * g - 5329 * b;
	return VP8ClipUV(v, rounding);
}

#endif // USE_YUVj

static inline void color16to24(const uint16_t color565, uint8_t *dst) {
	dst[0] = (color565 >> 8) & 0xF8;
	dst[0] |= (dst[0] >> 5);

	dst[1] = (color565 >> 3) & 0xFC;
	dst[1] |= (dst[1] >> 6);

	dst[2] = (color565 << 3) & 0xF8;
	dst[2] |= (dst[2] >> 5);
}

#define HPM_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define HPM_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define HPM_CLAMP(a, min, max) (HPM_MIN((max), HPM_MAX((min), (a))))

void VP8RGB2yuy2(const uint16_t *color, const uint16_t pixels, uint8_t *result_yuy) {

	for (uint16_t y_index = 0; y_index < pixels / 2; y_index++) {

		uint8_t p0[4];
		color16to24(color[(y_index * 2) + 0], (uint8_t *)&p0[0]);
		uint8_t p1[4];
		color16to24(color[(y_index * 2) + 1], (uint8_t *)&p1[0]);

		int u = (-18542 * (int)p0[0] - 36614 * (int)p0[1] + 55248 * (int)p0[2] + 128) >> 8;
		int v = (11780 * (int)p0[0] - 94454 * (int)p0[1] + 112396 * (int)p0[2] + 128) >> 8;

		u = HPM_CLAMP(u, 0, 255);
		v = HPM_CLAMP(v, 0, 255);

		/*	[Y, U0, Y1, V0]*/
		result_yuy[0] = VP8RGBToY(p0[0], p0[1], p0[2], 0);
		result_yuy[1] = u;
		result_yuy[2] = VP8RGBToY(p1[0], p1[1], p1[2], 0);
		result_yuy[3] = v;
	}
}
