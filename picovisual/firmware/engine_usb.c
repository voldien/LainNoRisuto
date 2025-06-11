#include "engine_usb.h"
#include "device/usbd.h"
#include "usb/usb_cdc.h"
#include "usb/usb_descriptors.h"
#include "usb/usb_video.h"

#include "bsp/board.h"
#include "bsp/board_api.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"
#include "tusb.h"
#include <stdio.h>

extern void audio_task();
extern void audio_control_task();

void init_engine_usb() {

	// engine_update_usb();
	tud_task();
}

void engine_update_usb() {
	tud_task_ext(1, false);

	cdc_task();
	
	video_task(NULL);
}

void tud_mount_cb() {
	/*	*/
}

// Invoked when device is unmounted
void tud_umount_cb() {
	/*	Init USB to listen to as a joystick.	*/

	/*	Init USB to use Storage.	*/
	printf("TUD Umount");
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en) {
	(void)remote_wakeup_en;
	printf("TUD Suspend");
	
	tud_remote_wakeup();
}

// Invoked when usb bus is resumed
void tud_resume_cb() {
	printf("TUD continue");

	//	blink_interval_ms = tud_mounted() ? BLINK_MOUNTED : BLINK_NOT_MOUNTED;
}
