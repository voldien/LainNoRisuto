#ifndef _ILI9341_H_
#define _ILI9341_H_
#include "hardware/spi.h"
#include "ili9341_def.h"
#include "pico/stdlib.h"

// convert 8 bit r, g, b values to 16 bit colour (rgb565 format)
#define GFX_RGB565(R, G, B) ((uint16_t)(((R) & 0b11111000) << 8) | (((G) & 0b11111100) << 3) | ((B) >> 3))
#define GFX_GETR(V) ((0b1111100000000000 & V) >> (5 + 6))
#define GFX_GETG(V) ((0b0000011111100000 & V) >> 5)
#define GFX_GETB(V) ((0b0000000000011111 & V))

// Use DMA?
#define USE_DMA 1

#ifdef USE_DMA
extern uint dma_tx;
extern void waitForDMA();
#endif

void LCD_setPins(uint16_t dc, uint16_t cs, int16_t rst, uint16_t sck, uint16_t tx);
void LCD_setSPIperiph(spi_inst_t *s);
void LCD_initDisplay();

void LCD_setRotation(uint8_t m);

void LCD_WritePixel(int x, int y, uint16_t col);
void LCD_WriteBitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *bitmap);

extern void ILI9341_DeSelect();

#endif
