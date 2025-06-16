#ifndef PICO_VISUAL_GRAPHIC_DRIVER_
#define PICO_VISUAL_GRAPHIC_DRIVER_

#include "pico/stdlib.h"
#include "picovisual.h"
#include <stdint.h>

extern uint16_t GFX_getWidth();
extern uint16_t GFX_getHeight();

extern uint16_t current_buffer;
extern const uint32_t frame_size;
extern uint16_t __uninitialized_ram() gfxFramebuffer[FRAME_WIDTH * FRAME_HEIGHT * FRAME_BUFFER_COUNT];

inline static uint16_t *GFX_getFrameBuffer(const uint16_t index) { return &gfxFramebuffer[frame_size * index]; }
extern uint16_t *GFX_getCurrentFrameBuffer();

void GFX_fillRect(uint16_t x, uint16_t y, const uint16_t w, const uint16_t h, const uint16_t color);
void GFX_fillScreen(const uint16_t color);

void GFX_flush();
void GFX_Update();

#endif
