#include "graphic_math.h"
#include "pico/util/queue.h"
#include <stdint.h>

#include "drivers/ili9341.h"
#include "engine_usb.h"
#include "joystick.h"
#include "pico/stdlib.h"
#include "picovisual.h"
#include <gfx/gfx.h>
#include <stdio.h>

#include "pico/multicore.h"

#include "device/usbd.h"
#include "usb/usb_cdc.h"
#include "usb/usb_descriptors.h"
#include "usb/usb_video.h"

#include "bsp/board.h"
#include "bsp/board_api.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"
#include "hardware/watchdog.h"
#include "tusb.h"

// Perform initialisation
int pico_led_init() {
#if defined(PICO_DEFAULT_LED_PIN)
	// A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
	// so we can use normal GPIO functionality to turn the led on and off
	gpio_init(PICO_DEFAULT_LED_PIN);

	gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
	return PICO_OK;
#elif defined(CYW43_WL_GPIO_LED_PIN)
	// For Pico W devices we need to initialise the driver etc
	return cyw43_arch_init();
#endif
}

// Turn the led on or off
void pico_set_led(bool led_on) {
#if defined(PICO_DEFAULT_LED_PIN)
	// Just set the GPIO on or off
	gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#elif defined(CYW43_WL_GPIO_LED_PIN)
	// Ask the wifi "driver" to set the GPIO on or off
	cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
}

void InitializeDisplay(uint16_t color) {
	// Initialize display
	puts("Initializing display...");

	LCD_setPins(TFT_DC, TFT_CS, TFT_RST, TFT_SCLK, TFT_MOSI);

	LCD_initDisplay();
	LCD_setRotation(TFT_ROTATION);
	GFX_setClearColor(BACKGROUND);
	GFX_clearScreen();
	GFX_flush();
}

void core1_entry() {
	while (1) {

		mandelbrot(GFX_getHeight() / 2, GFX_getHeight());
		game_of_life(GFX_getHeight() / 2, GFX_getHeight());

		engine_update_usb();
		// sleep_ms(5);
	}
}

bool repeating_timer_callback(__unused struct repeating_timer *t) {
	watchdog_update();
	return true;
}

void init_engine() {

	/*	*/
	set_sys_clock_khz(PLL_SYS_KHZ, true);

	/*	Init Console.	*/
	stdio_init_all();

	board_init();

	/*	*/
	tusb_init();
	/*	*/
	if (board_init_after_tusb) {
		board_init_after_tusb();
	}

	tud_task();

	/*	*/
	{
		if (watchdog_enable_caused_reboot()) {
			printf("Rebooted by Watchdog!\n");

		} else {
			printf("Clean boot\n");
		}
		watchdog_update();

		/* setup alarm for watchdog. */
		struct repeating_timer timer;
		add_repeating_timer_ms(-75, repeating_timer_callback, NULL, &timer);
	}

	int rc = pico_led_init();

	InitializeDisplay(BACKGROUND);

	multicore_launch_core1(core1_entry);
}

void welcome_screen() {
	const int w = GFX_getWidth();
	const int h = GFX_getHeight();

	/*	*/
	for (volatile int16_t x_index = 0; x_index < w; x_index++) {
		for (volatile int16_t y_index = 0; y_index < h; y_index++) {
			/*	*/
			gfxFramebuffer[(y_index * w) + x_index] = GFX_RGB565(0, 0, 0);
		}
	}

	GFX_flush();
}

int main() {

	/*	Init Internal Console Backend.	*/
	init_engine();

	welcome_screen();

	while (true) {

		mandelbrot(0, GFX_getHeight() / 2);

		GFX_flush();

		//
		watchdog_update();

		// TODO: Move
		waitForDMA();
	}

	return 0;
}
