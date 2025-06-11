
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usb/usb_video.h"

#include "bsp/board_api.h"
#include "drivers/ili9341.h"
#include "gfx/gfx.h"
#include "tusb.h"
#include "usb_descriptors.h"
#include <pico/flash.h>

//--------------------------------------------------------------------+
// USB Video
//--------------------------------------------------------------------+
static unsigned frame_num = 0;
static unsigned tx_busy = 0;
static unsigned interval_ms = 1000 / FRAME_RATE;

static inline uint32_t convert_2_pixel(const uint32_t pixel2) {

	const uint8_t R1 = GFX_GETR(pixel2 & 0xffff);
	const uint8_t R2 = GFX_GETR(pixel2 >> 8);
	const uint8_t B1 = GFX_GETB(pixel2 & 0xffff);
	const uint8_t B2 = GFX_GETB(pixel2 >> 8);
	const uint8_t G1 = GFX_GETG(pixel2 & 0xffff);
	const uint8_t G2 = GFX_GETG(pixel2 >> 8);

	// Lumen
	uint16_t subY0 = (0.299f * R1) + (0.587f * G1) + (0.114f * B1);
	uint16_t subY1 = (0.299f * R2) + (0.587f * G2) + (0.114f * B2);

	return subY0 << 16 || subY1 << 8;
}

void convert_2_yuv() {

	for (uint16_t y = 0; y < GFX_getHeight(); y++) {

		for (uint16_t x = 0; x < GFX_getWidth(); x += 2) {
			const uint8_t R1 = GFX_GETR(gfxFramebuffer[(y * GFX_getWidth()) + x + 0]);
			const uint8_t R2 = GFX_GETR(gfxFramebuffer[(y * GFX_getWidth()) + x + 1]);
			const uint8_t B1 = GFX_GETB(gfxFramebuffer[(y * GFX_getWidth()) + x + 0]);
			const uint8_t B2 = GFX_GETB(gfxFramebuffer[(y * GFX_getWidth()) + x + 1]);
			const uint8_t G1 = GFX_GETG(gfxFramebuffer[(y * GFX_getWidth()) + x + 0]);
			const uint8_t G2 = GFX_GETG(gfxFramebuffer[(y * GFX_getWidth()) + x + 1]);

			uint8_t subY0 = (0.299f * R1) + (0.587f * G1) + (0.114f * B1);
			uint8_t subY1 = (0.299f * R2) + (0.587f * G2) + (0.114f * B2);

			gfxFramebuffer[(y * GFX_getWidth()) + x + 0] = subY0 << 8;
			gfxFramebuffer[(y * GFX_getWidth()) + x + 1] = subY1 << 8;
		}
	}
}

static void video_send_frame(void) {
	static unsigned start_ms = 0;
	static unsigned already_sent = 0;

	/*  Determine if anyone thing is request frames.  */
	if (!tud_video_n_streaming(0, 0)) {
		already_sent = 0;
		frame_num = 0;
		return;
	}

	if (!already_sent) {
		already_sent = 1;
		tx_busy = 1;
		start_ms = board_millis();

		uint16_t *current = GFX_getFrameBuffer((current_buffer + 1) % 2);
		// convert_2_yuv();
		tud_video_n_frame_xfer(0, 0, (void *)(uintptr_t)current, FRAME_WIDTH * FRAME_HEIGHT * 2);
	}

	unsigned cur = board_millis();
	if (cur - start_ms < interval_ms) {
		return; // not enough time
	}

	if (tx_busy) {
		return;
	}
	
	start_ms += interval_ms;
	tx_busy = 1;

	tud_video_n_frame_xfer(0, 0, (void *)(uintptr_t)&gfxFramebuffer[0], FRAME_WIDTH * FRAME_HEIGHT * 16 / 8);
}

void video_task(void *param) {
	(void)param;
	video_send_frame();
}

void tud_video_frame_xfer_complete_cb(uint_fast8_t ctl_idx, uint_fast8_t stm_idx) {
	(void)ctl_idx;
	(void)stm_idx;
	tx_busy = 0;

	/* flip buffer */
	++frame_num;
}

int tud_video_commit_cb(uint_fast8_t ctl_idx, uint_fast8_t stm_idx,
						video_probe_and_commit_control_t const *parameters) {
	(void)ctl_idx;
	(void)stm_idx;
	/* convert unit to ms from 100 ns */
	interval_ms = parameters->dwFrameInterval / 10000;
	return VIDEO_ERROR_NONE;
}