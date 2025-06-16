#pragma once
#include <stdbool.h>
#include <stdint.h>

enum : uint32_t {
	LED_INDICATION0 = 0,
	LED_INDICATION1 = 1,
	LED_INDICATION2 = 2,
};

/**
 *
 */
extern void init_indication_led();
/**
 *
 */
extern void indication_led_set(const uint32_t index, const bool state_high_low);