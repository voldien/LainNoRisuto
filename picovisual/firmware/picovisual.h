#include <stdint.h>
#ifndef _PICO_VISUAL_GRAPHIC_
#define _PICO_VISUAL_GRAPHIC_ 1
#include "graphic_math.h"
#include <pico.h>

/*  VIDEO Settings */
#define FRAME_WIDTH 320lu
#define FRAME_HEIGHT 240lu
#define FRAME_RATE 60u
#define PIXEL_DEPTH 16lu
#define FRAME_BUFFER_COUNT 2lu
#define PIXEL_SIZE (PIXEL_DEPTH / 8)

extern uint8_t __uninitialized_ram() scratchpad[2 * (FRAME_WIDTH * FRAME_HEIGHT) / 8];

typedef struct mandelbrot_settings_t {
	vec2 pos;
	vec2 mousePos;
	float zoom; /*  */
	float c;	/*  */
	float ci;
	int nrSamples;
} MandelBrotSettings;

typedef struct game_of_life_settings_t {
	vec2 pos;
	vec2 mousePos;
	float zoom; /*  */
	float c;	/*  */
	float ci;
} GameOfLifeSettings;

enum PicoVisual {
	PICO_VISUAL_MANDELBROT = 1,
	PICO_VISUAL_GAME_OF_LIFE = 2,
};

typedef struct settings_t {
	uint16_t current_visual;
	union {
		MandelBrotSettings mandel;
		GameOfLifeSettings gof;
	} v_settings;
} VisualSettings;

extern VisualSettings __not_in_flash() pico_visual_settings;

extern void begin_next_frame();
extern void end_next_frame();

/*
 *
 */
extern void game_of_life(uint32_t y_start, uint32_t y_end);

/*
 *
 */
extern void mandelbrot(uint32_t y_start, uint32_t y_end);

#endif