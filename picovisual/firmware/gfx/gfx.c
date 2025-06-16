#include "pico/stdlib.h"
#include "picovisual.h"
#include "stdarg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gfx.h"

uint16_t GFX_getWidth() { return FRAME_WIDTH; }
uint16_t GFX_getHeight() { return FRAME_HEIGHT; }

uint16_t current_buffer = 0;
const uint32_t frame_size = FRAME_WIDTH * FRAME_HEIGHT * PIXEL_SIZE;

uint16_t __uninitialized_ram() gfxFramebuffer[FRAME_WIDTH * FRAME_HEIGHT * FRAME_BUFFER_COUNT];
static bool gfxFbUpdated = false;

uint16_t *GFX_getCurrentFrameBuffer() { return &gfxFramebuffer[current_buffer]; }

// Declare methods from the display drivers
extern void LCD_WritePixel(int x, int y, uint16_t col);
extern void LCD_WriteBitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *bitmap);

#ifndef swap
#define swap(a, b)                                                                                                     \
	{                                                                                                                  \
		const int16_t t = a;                                                                                           \
		a = b;                                                                                                         \
		b = t;                                                                                                         \
	}
#endif

void GFX_flush() {

	LCD_WriteBitmap(0, 0, GFX_getWidth(), GFX_getHeight(), GFX_getCurrentFrameBuffer());
	gfxFbUpdated = false;
}

void GFX_Update() {
	if (gfxFbUpdated) {
		GFX_flush();
	}
}

void GFX_fillScreen(const uint16_t color) { GFX_fillRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT, color); }

#pragma GCC optimize("O3")
void GFX_fillRect(uint16_t x, uint16_t y, const uint16_t width, const uint16_t height, const uint16_t color) {
	gfxFbUpdated = true;

	// TODO: optionally, using a DMA.
	for (uint16_t y_index = x; y_index < height; y_index++) {

		for (uint16_t x_index = y; x_index < width; x_index++) {

			gfxFramebuffer[(y_index * GFX_getWidth()) + x_index] = color;
		}
	}
}
