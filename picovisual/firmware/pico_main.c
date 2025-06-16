#include "graphic_math.h"
#include "graphic_pico_def.h"
#include "pico/util/queue.h"
#include <hardware/gpio.h>
#include <hardware/structs/io_bank0.h>
#include <stdint.h>

#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "pico/time.h"

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
#include "usb/usb_video.h"

#include "bsp/board.h"
#include "bsp/board_api.h"
#include "hardware/clocks.h"
#include "hardware/watchdog.h"
#include "tusb.h"

bool repeating_timer_callback(__unused struct repeating_timer *t) {
	watchdog_update();
	return true;
}

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
	GFX_fillScreen(BACKGROUND);
	GFX_flush();

	// gpio_set_function(TFT_LED, GPIO_FUNC_PWM);
	//// Figure out which slice we just connected to the LED pin
	// uint slice_num = pwm_gpio_to_slice_num(TFT_LED);
	//
	//// Mask our slice's IRQ output into the PWM block's single interrupt line,
	//// and register our interrupt handler
	// pwm_clear_irq(slice_num);
	// pwm_set_irq_enabled(slice_num, true);
	//// irq_set_exclusive_handler(PWM_DEFAULT_IRQ_NUM(), on_pwm_wrap);
	//// irq_set_enabled(PWM_DEFAULT_IRQ_NUM(), true);
	//
	//// Get some sensible defaults for the slice configuration. By default, the
	//// counter is allowed to wrap over its maximum range (0 to 2**16-1)
	// pwm_config config = pwm_get_default_config();
	//// Set divider, reduces counter clock to sysclock/this value
	// pwm_config_set_clkdiv(&config, 4.f);
	//// Load the configuration into our PWM slice, and set it running.
	// pwm_init(slice_num, &config, true);
}

void core1_entry() {

	while (1) {

		mandelbrot(GFX_getHeight() / 2, GFX_getHeight());
		// game_of_life(GFX_getHeight() / 2, GFX_getHeight());

		engine_update_usb();
		// sleep_ms(5);
	}
}

#define GPIO_BUTTON0_PIN 15

void gpio_callback(uint gpio, uint32_t events) { gpio_get(GPIO_BUTTON0_PIN); }

struct repeating_timer timer;
void init_everything() {

	/*	*/
	set_sys_clock_khz(PLL_SYS_KHZ, true);

	/*	Init Console.	*/
	stdio_init_all();

	board_init();

	/*	*/
	{
		if (watchdog_enable_caused_reboot()) {
			printf("Rebooted by Watchdog!\n");

		} else {
			printf("Clean boot\n");
		}

		watchdog_enable(-500, 1);
		watchdog_update();

		/* setup alarm for watchdog. */
		add_repeating_timer_ms(-250, repeating_timer_callback, NULL, &timer);
	}

	/*	*/
	tusb_init();
	/* */
	if (board_init_after_tusb) {
		board_init_after_tusb();
	}

	tud_task();

	/*	Setup Buttons.	*/
	gpio_init(GPIO_BUTTON0_PIN);
	gpio_set_dir(GPIO_BUTTON0_PIN, false);
	gpio_set_function(GPIO_BUTTON0_PIN, GPIO_FUNC_NULL);
	gpio_set_irq_enabled_with_callback(GPIO_BUTTON0_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

	// int rc = pico_led_init();

	InitializeDisplay(BACKGROUND);

	multicore_launch_core1(core1_entry);
}

void welcome_screen() {

	GFX_fillScreen(0);

	puts("Welcome Display display...");
	const int width = GFX_getWidth();
	const int height = GFX_getHeight();

	/*	*/
	for (int16_t x_index = 0; x_index < width; x_index++) {
		for (int16_t y_index = 0; y_index < height; y_index++) {
			/*	*/
			gfxFramebuffer[(y_index * width) + x_index] = GFX_RGB565(0, 0, 0);
		}
	}

	GFX_flush();
}

int main() {

	/*	Init Internal Console Backend.	*/
	init_everything();

	/*	*/
	welcome_screen();

	/*	*/
	while (true) {

		printf("frame");
		/*	Run Current Select Visual.	*/
		begin_next_frame();
		mandelbrot(0, GFX_getHeight() / 2);
		GFX_flush();
		end_next_frame();
	}

	return 0;
}
