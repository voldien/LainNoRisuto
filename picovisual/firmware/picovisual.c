#include "picovisual.h"
#include "drivers/ili9341.h"
#include "gfx/gfx.h"
#include <pico.h>
#include <stddef.h>
#include <stdint.h>

uint8_t __uninitialized_ram() scratchpad[2 * (FRAME_WIDTH * FRAME_HEIGHT) / 8];

VisualSettings __not_in_flash() pico_visual_settings = {
	.current_visual = PICO_VISUAL_MANDELBROT,

	.v_settings.mandel.nrSamples = 16,
	.v_settings.mandel.c = -2,
	.v_settings.mandel.ci = -2,
	.v_settings.mandel.zoom = 2,
};

void begin_next_frame() {
	/*	*/
}
void end_next_frame() { current_buffer = (current_buffer + 1) % FRAME_BUFFER_COUNT; }

static inline uint16_t get_cell_value(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height) {

	const uint16_t memory_offset = ((x / 8) * width) + (y / 8);

	const uint16_t bit_offset = y % 8;

	return (scratchpad[memory_offset] & (1 << bit_offset)) >> bit_offset;
}

void game_of_life(uint32_t y_start, uint32_t y_end) {

	const uint16_t w = GFX_getWidth();
	const uint16_t h = GFX_getHeight();

	uint8_t *gof = scratchpad;

	/*	Cell Alive lookup table.	*/
	const uint16_t GOFLUT[9] = {0, 0, 1, 1, 0, 0, 0, 0, 0};
	/*	Cell Dead lookup table.	*/
	const uint16_t GOFLUTDEAD[9] = {0, 0, 0, 1, 0, 0, 0, 0, 0};

	const uint16_t KernelAliveMatrix[9] = {1, 1, 1, 1, 0, 1, 1, 1, 1};

	/*	Custom color for each possible neighbor combination.	*/
	const uint16_t color[9] = {GFX_RGB565(0, 0, 0),	  GFX_RGB565(0, 255, 0), GFX_RGB565(0, 255, 0),
							   GFX_RGB565(0, 255, 0), GFX_RGB565(0, 255, 0), GFX_RGB565(0, 255, 0),
							   GFX_RGB565(0, 255, 0), GFX_RGB565(0, 255, 0), GFX_RGB565(0, 0, 0)};

	uint16_t sum = 0;
	const uvec2_16 image_size = {FRAME_WIDTH, FRAME_HEIGHT};

	for (volatile int16_t x_index = 0; x_index < w; x_index++) {
		for (volatile int16_t y_index = y_start; y_index < y_end; y_index++) {

			const ivec2_16 pixel_coords = {x_index, y_index};
			const uint32_t current_cell = get_cell_value(x_index, y_index, image_size[0], image_size[1]);

			/*	*/
			for (int16_t y = -1; y <= 1; y++) {
				for (int16_t x = -1; x <= 1; x++) {

					const ivec2_16 kernel_offset = {x, y};

					/*	index  (x + 1) + ((y + 1) * 3);	*/
					const ivec2_16 one = {1, 1};
					const uvec2_16 no = (uvec2_16)__sadd16((uint32_t)kernel_offset, (uint32_t)one);
					const uvec2_16 _1_3 = {1, 3};
					const uint32_t lut_index = __smuad((uint32_t)no, (uint32_t)_1_3);

					/*	Compute neighbor cell, wrap around edge.	*/
					ivec2_16 offsetCordinate = (ivec2_16)__sadd16((int32_t)pixel_coords, (int32_t)kernel_offset);
					offsetCordinate[0] %= w;
					offsetCordinate[1] %= h;

					uint16_t kernel_cell =
						get_cell_value(offsetCordinate[0], offsetCordinate[1], image_size[0], image_size[1]);

					sum += kernel_cell * KernelAliveMatrix[lut_index];
				}
			}

			/*	Compute if cell is alive.	*/
			const uint IsDeadCell = current_cell == 0 ? 1 : 0;

			/*	Sum of cell alive state and dead cell state.	*/
			const uint result = (GOFLUT[sum] * current_cell) + ((uint32_t)GOFLUTDEAD[sum] * IsDeadCell);

			const uint16_t finalColor = color[sum];

			gfxFramebuffer[(y_index * w) + x_index] = finalColor;

			/*	*/
		}
	}
}

void mandelbrot(uint32_t y_start, uint32_t y_end) {

	const uint16_t w = GFX_getWidth();
	const uint16_t h = GFX_getHeight();

	MandelBrotSettings *mandel_settings = &pico_visual_settings.v_settings.mandel;

	mandel_settings->c += 0.0001f;
	mandel_settings->ci += 0.0001f;

	const float lthreadhold = 2.0;

	const float wInverse = mandel_settings->zoom * (1.0f / (float)FRAME_WIDTH);
	const float hInverse = mandel_settings->zoom * (1.0f / (float)FRAME_HEIGHT);

	for (volatile int16_t x_index = 0; x_index < w; x_index++) {
		for (volatile int16_t y_index = y_start; y_index < y_end; y_index++) {

			for (uint16_t chunk = 0; chunk < 4; chunk++) {
			}

			/*  */
			const vec2 uv = {x_index * wInverse, y_index * hInverse};

			const vec2 c = {mandel_settings->c, mandel_settings->ci};
			vec2 z = {0, 0};

			const float max_range = lthreadhold * lthreadhold;
			uint32_t i = 0;
			for (; i < mandel_settings->nrSamples; i++) {

				squareImaginary(&z, &z);

				z.x += c.x;
				z.y += c.y;
				z.x += uv.x;
				z.y += uv.y;

				/*  */
				if (dot(&z, &z) > max_range) {
					break;
				}
			}

			if (i >= 1) {
				// const float interpolate = (i / (float)samples);

				const uint8_t r = (i << 4) + (i * 4);  // * 255;
				const uint8_t g = ((i << 4) + i) >> 1; // * 255;
				const uint8_t b = ((i << 4) - i) >> 1; // * 255;

				gfxFramebuffer[(y_index * w) + x_index] = GFX_RGB565(r, g, b);
			} else {
				gfxFramebuffer[(y_index * w) + x_index] = 0;
			}
		}
	}
}