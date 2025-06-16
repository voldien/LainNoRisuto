
#include <pico/time.h>
#include <stdint.h>

#include "bsp/board_api.h"
#include "gfx/gfx.h"
#include "picovisual.h"
#include "pix_format.h"
#include "usb/usb_video.h"
#include <pico/flash.h>
#include <stdio.h>

//--------------------------------------------------------------------+
// USB Video
//--------------------------------------------------------------------+

#if CFG_TUD_VIDEO == 1
static uint16_t frame_num = 0;
static uint16_t tx_busy = 0;
static uint16_t x_index = 0;
static uint16_t interval_ms = 1000 / FRAME_RATE; // TODO: change to micro

uint16_t scan_line[FRAME_HEIGHT];
#endif

static void video_send_frame() {
#if CFG_TUD_VIDEO == 1
	static unsigned start_ms = 0;
	static unsigned already_sent = 0;

	/*  Determine if anyone is request frames.  */
	if (!tud_video_n_streaming(0, 0)) {
		already_sent = 0;
		frame_num = 0;
		return;
	}

	/*	First Send.	*/
	if (!already_sent) {
		already_sent = 1;
		start_ms = board_millis();
	}

	unsigned cur = board_millis();
	if (cur - start_ms < interval_ms) {
		return; // not enough time
	}

	if (tx_busy) {
		return; /*	Wait in till tranmission completed.	*/
	}

	start_ms += interval_ms;
	tx_busy = 1;

	uint16_t *current = GFX_getFrameBuffer((current_buffer + 1) % FRAME_BUFFER_COUNT);
	current = GFX_getFrameBuffer(0);

	for (; x_index < FRAME_WIDTH;) {
		/*	*/
		VP8RGB2yuy2(&current[x_index * FRAME_HEIGHT], FRAME_HEIGHT, (uint8_t *)scan_line);
		printf("line %d\n", x_index);

		if (tud_video_n_frame_xfer(0, 0, (void *)(uintptr_t)&scan_line, sizeof(scan_line))) {
			x_index++;
			return;
		}
	}
#endif
}

void video_task(void *param) {
	(void)param;

	video_send_frame();
}
//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

#if CFG_TUD_VIDEO == 1
void tud_video_frame_xfer_complete_cb(uint_fast8_t ctl_idx, uint_fast8_t stm_idx) {
	(void)ctl_idx;
	(void)stm_idx;

	printf("frame completed\n");

	tx_busy = 0;
	x_index %= FRAME_WIDTH;

	/* flip buffer */
	if (x_index == 0) {
		frame_num++;
	}
}

int tud_video_commit_cb(uint_fast8_t ctl_idx, uint_fast8_t stm_idx,
						video_probe_and_commit_control_t const *parameters) {
	(void)ctl_idx;
	(void)stm_idx;
	/* convert unit to ms from 100 ns */
	interval_ms = parameters->dwFrameInterval / 10000;
	return VIDEO_ERROR_NONE;
}

#endif