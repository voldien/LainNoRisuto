

#pragma once

// Pin definitions for the LCD
#define TFT_SCLK 2		  /*   GPIO    */
#define TFT_MOSI 3		  /*   GPIO    */
#define TFT_MISO 255	  // Not required, used for DC...
#define TFT_DC 11		  /*   GPIO    */
#define TFT_RST 12		  /*   GPIO    */
#define TFT_CS 10		  /*   GPIO    */
#define TFT_LED 13		  /*   GPIO    */
#define TFT_BACKLIGHT 255 // hardwired to 3.3v

#define TFT_ROTATION 2

#define BACKGROUND 0x1052
#define FOREGROUND 0x73BF

#define PLL_SYS_KHZ (150 * 1000)