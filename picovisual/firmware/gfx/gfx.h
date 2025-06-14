#ifndef PICO_VISUAL_GRAPHIC_DRIVER_
#define PICO_VISUAL_GRAPHIC_DRIVER_

#include "pico/stdlib.h"
#include "picovisual.h"
#include <stdint.h>

inline static uint16_t GFX_getWidth() { return FRAME_WIDTH; }
inline static uint16_t GFX_getHeight() { return FRAME_HEIGHT; }

extern uint16_t current_buffer;
extern const uint32_t frame_size;
extern uint16_t __uninitialized_ram() gfxFramebuffer[FRAME_WIDTH * FRAME_HEIGHT * FRAME_BUFFER_COUNT];

inline static uint16_t *GFX_getFrameBuffer(const uint16_t index) { return &gfxFramebuffer[frame_size * index]; }
inline static uint16_t *GFX_getCurrentFrameBuffer();

void GFX_fillRect(int16_t x, int16_t y, const int16_t w, const int16_t h, const uint16_t color);
void GFX_fillScreen(const uint16_t color);

void GFX_flush();
void GFX_Update();

#endif
