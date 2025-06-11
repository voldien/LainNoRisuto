#include "animation.h"
#include <avr/interrupt.h>

volatile uint8_t curanim;
volatile uint8_t g_curkeyframe;

void cc_init_animation() {
	curanim = 0;
	g_curkeyframe = 0;
}

uint8_t cc_get_curr_animation_keyframe(const uint8_t r, const uint8_t c) {

	const uint8_t keyframe = g_curkeyframe;

	// const uint8_t offset = index / 2;
	uint8_t rowoffset = r * RGBRES;
	uint8_t coloffset = c / RGBRES;
	const uint8_t keyoffset = rowoffset + coloffset;

	const uint16_t *addr = (const uint16_t *)&animations[curanim][keyframe][keyoffset];

	/*	Load RGB.	*/
	register struct rgb_t rgb;
	const uint16_t value = pgm_read_word(addr);
	rgb.green2_blue5 = value >> 8;
	rgb.red5_3green = value & 0xFF;

	/*	Inflate RGB value.	*/
	const uint8_t red = rgb.red5_3green & COLORRES;
	const uint8_t green = rgb.red5_3green >> COLORBIT | (rgb.green2_blue5 & 0b11);
	const uint8_t blue = ((rgb.green2_blue5 >> 2) & COLORRES) & COLORRES;

	/*	Create simple table.	*/
	const uint8_t infrgb[3] = {red, green, blue};

	/*	Compute final.	*/
	return infrgb[c % RGBRES] * 8;
}

void cc_next_frame() {

	/*	Update .	*/
	cli();
	g_curkeyframe++;
	g_curkeyframe = g_curkeyframe % NRKEYFRAME;
	sei();
}

const uint8_t cc_next_animation_ready() { return g_curkeyframe == (NRKEYFRAME - 1); }


inline void cc_reset_for_next_animation() {
	cli();
	curanim = (curanim + 1) % NRANIM;
	g_curkeyframe = 0;
	sei();
}
