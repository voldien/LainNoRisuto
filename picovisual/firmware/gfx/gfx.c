#include "malloc.h"
#include "pico/stdlib.h"
#include "stdarg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gfx.h"

#define GFX_BLACK 0x0000
#define GFX_WHITE 0xFFFF

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

	LCD_WriteBitmap(0, 0, GFX_getHeight(), GFX_getHeight(), gfxFramebuffer);

	gfxFbUpdated = false;
}

void GFX_Update() {
	if (gfxFbUpdated) {
		GFX_flush();
	}
}


void GFX_fillScreen(const uint16_t color) { GFX_fillRect(0, 0, GFX_getHeight(), GFX_getHeight(), color); }

#pragma GCC optimize ("O3")
void GFX_fillRect(int16_t x, int16_t y, const int16_t w, const int16_t h, const uint16_t color) {

	//TODO: optionally, using a DMA.
	for (int16_t y_index = y; y_index < h; y_index++) {
		for (int16_t x_index = x; x_index < w; x_index++) {

			gfxFramebuffer[(y_index * GFX_getHeight()) + x_index] = color;
		}
	}

	gfxFbUpdated = true;
}
