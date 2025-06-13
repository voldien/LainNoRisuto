
#include <stdint.h>

#include "usb/usb_video.h"
#include "bsp/board_api.h"
#include "gfx/gfx.h"
#include "picovisual.h"
#include "pix_format.h"
#include <pico/flash.h>

//--------------------------------------------------------------------+
// USB Video
//--------------------------------------------------------------------+
static uint16_t frame_num = 0;
static uint16_t tx_busy = 0;
static uint16_t interval_ms = 1000 / FRAME_RATE;

static void video_send_frame() {
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

		uint16_t *current = GFX_getFrameBuffer((current_buffer + 1) % FRAME_BUFFER_COUNT);

		uint16_t scan_line[FRAME_HEIGHT];
		for (uint16_t x = 0; x < FRAME_WIDTH; x++) {
			VP8RGB2yuv(&current[x * FRAME_HEIGHT], FRAME_HEIGHT, scan_line);

			tud_video_n_frame_xfer(0, 0, (void *)(uintptr_t)&scan_line, sizeof(scan_line));
		}
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

	uint16_t *current = GFX_getFrameBuffer((current_buffer + 1) % FRAME_BUFFER_COUNT);
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
	frame_num++;
}

int tud_video_commit_cb(uint_fast8_t ctl_idx, uint_fast8_t stm_idx,
						video_probe_and_commit_control_t const *parameters) {
	(void)ctl_idx;
	(void)stm_idx;
	/* convert unit to ms from 100 ns */
	interval_ms = parameters->dwFrameInterval / 10000;
	return VIDEO_ERROR_NONE;
}