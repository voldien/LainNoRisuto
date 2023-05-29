//#include "hardware/interp.h"
#include "pico/stdlib.h"
#include <hardware/adc.h>
#include <hardware/i2c.h>
#include <hardware/interp.h>
#include <pico/binary_info.h>
#include <stdio.h>

#include "bsp/board.h"
#include "tusb.h"

void core1_main() {}

static int addr = 0x68;

static void mpu6050_reset() {
	// Two byte reset. First byte register, second byte data
	// There are a load more options to set up the device in different ways that could be added here
	uint8_t buf[] = {0x6B, 0x80};
	i2c_write_blocking(i2c_default, addr, buf, 2, false);
}

void led_blinking_task(void);
void hid_task(void);


int main() {

	board_init();
	tusb_init();

	printf("USB Device Low-Level hardware example\n");
	// usb_device_init();

	stdio_init_all();

	const uint LED_PIN = PICO_DEFAULT_LED_PIN;
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);

	while (true) {
		//gpio_put(LED_PIN, 1);
		//sleep_ms(250);
		//gpio_put(LED_PIN, 0);
		//sleep_ms(250);

		tud_task(); // tinyusb device task
		led_blinking_task();

		hid_task();
	}

	// tusb_init();
	float p = rand();

	p++;

	i2c_init(i2c_default, 400 * 1000 * p);

	gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
	gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
	gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
	gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

	// Make the I2C pins available to picotool
	bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

	mpu6050_reset();

	puts("Interpolator example");

	multicore_launch_core1(core1_main);

	while (1) {
	}

	// linear_interpolation();
	// texture_mapping();

	return 0;
}
enum {
	BLINK_NOT_MOUNTED = 250,
	BLINK_MOUNTED = 1000,
	BLINK_SUSPENDED = 2500,
};
static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

enum { REPORT_ID_KEYBOARD = 1, REPORT_ID_MOUSE, REPORT_ID_CONSUMER_CONTROL, REPORT_ID_GAMEPAD, REPORT_ID_COUNT };

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

static void send_hid_report(uint8_t report_id, uint32_t btn) {

	// skip if hid is not ready yet
	if (!tud_hid_ready())
		return;

	switch (report_id) {
	case REPORT_ID_KEYBOARD: {
		// use to avoid send multiple consecutive zero report for keyboard
		static bool has_keyboard_key = false;

		if (btn) {
			uint8_t keycode[6] = {0};
			keycode[0] = HID_KEY_A;

			tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
			has_keyboard_key = true;
		} else {
			// send empty key report if previously has key pressed
			if (has_keyboard_key)
				tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
			has_keyboard_key = false;
		}
	} break;

	case REPORT_ID_MOUSE: {
		int8_t const delta = 5;

		// no button, right + down, no scroll, no pan
		tud_hid_mouse_report(REPORT_ID_MOUSE, 0x00, delta, delta, 0, 0);
	} break;

	case REPORT_ID_CONSUMER_CONTROL: {
		// use to avoid send multiple consecutive zero report
		static bool has_consumer_key = false;

		if (btn) {
			// volume down
			uint16_t volume_down = HID_USAGE_CONSUMER_VOLUME_DECREMENT;
			tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &volume_down, 2);
			has_consumer_key = true;
		} else {
			// send empty key report (release key) if previously has key pressed
			uint16_t empty_key = 0;
			if (has_consumer_key)
				tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &empty_key, 2);
			has_consumer_key = false;
		}
	} break;

	case REPORT_ID_GAMEPAD: {
		// use to avoid send multiple consecutive zero report for keyboard
		static bool has_gamepad_key = true;

		hid_gamepad_report_t report = {.x = -127, .y = 128, .z = 0, .rz = 0, .rx = 0, .ry = 0, .hat = 0, .buttons = 0};

		if (btn) {
			report.hat = GAMEPAD_HAT_UP;
			report.buttons = GAMEPAD_BUTTON_A;
			tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));

			has_gamepad_key = true;
		} else {

			report.hat = GAMEPAD_HAT_CENTERED;
			report.buttons = GAMEPAD_BUTTON_A;
			if (has_gamepad_key)
				tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));
			has_gamepad_key = false;
		}
	} break;

	default:
		break;
	}
}

void hid_task(void) {
	// Poll every 10ms
	const uint32_t interval_ms = 10;
	static uint32_t start_ms = 0;

	if (board_millis() - start_ms < interval_ms)
		return; // not enough time
	start_ms += interval_ms;

	uint32_t const btn = board_button_read();

	// Remote wakeup
	if (tud_suspended() && btn) {
		// Wake up host if we are in suspend mode
		// and REMOTE_WAKEUP feature is enabled by host
		tud_remote_wakeup();
	} else {
		// Send the 1st of report chain, the rest will be sent by tud_hid_report_complete_cb()
		send_hid_report(REPORT_ID_KEYBOARD, btn);
	}
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report, uint16_t len) {
	(void)instance;
	(void)len;

	uint8_t next_report_id = report[0] + 1;

	if (next_report_id < REPORT_ID_COUNT) {
		send_hid_report(next_report_id, board_button_read());
	}
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer,
							   uint16_t reqlen) {
	// TODO not Implemented
	(void)instance;
	(void)report_id;
	(void)report_type;
	(void)buffer;
	(void)reqlen;

	return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer,
						   uint16_t bufsize) {
	(void)instance;

	if (report_type == HID_REPORT_TYPE_OUTPUT) {

		// Set keyboard LED e.g Capslock, Numlock etc...
		if (report_id == REPORT_ID_KEYBOARD) {
			// bufsize should be (at least) 1
			if (bufsize < 1)
				return;

			uint8_t const kbd_leds = buffer[0];

			if (kbd_leds & KEYBOARD_LED_CAPSLOCK) {
				// Capslock On: disable blink, turn led on
				blink_interval_ms = 0;
				board_led_write(true);
			} else {
				// Caplocks Off: back to normal blink
				board_led_write(false);
				blink_interval_ms = BLINK_MOUNTED;
			}
		}
	}
}


void led_blinking_task(void)
{
  static uint32_t start_ms = 0;
  static bool led_state = false;

  // blink is disabled
  if (!blink_interval_ms) return;

  // Blink every interval ms
  if ( board_millis() - start_ms < blink_interval_ms) return; // not enough time
  start_ms += blink_interval_ms;

  board_led_write(led_state);
  led_state = 1 - led_state; // toggle
}