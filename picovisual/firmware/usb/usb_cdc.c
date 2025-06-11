#include "usb/usb_cdc.h"
#include "bsp/board_api.h"
#include "tusb.h"

//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+

void cdc_task() {
#if CFG_TUD_CDC == 1

	// connected() check for DTR bit
	// Most but not all terminal client set this when making connection
	if (tud_cdc_connected()) {

		// connected and there are data available
		if (tud_cdc_available()) {
			// read data
			char buf[64];
			uint32_t count = tud_cdc_read(buf, sizeof(buf));
			(void)count;

			/*	Send Commands to Internal Engine.	*/

			// Echo back
			// Note: Skip echo by commenting out write() and write_flush()
			// for throughput test e.g
			//    $ dd if=/dev/zero of=/dev/ttyACM0 count=10000

			tud_cdc_write(buf, count);
			tud_cdc_write_flush();
		}
	}
#endif
}

#if CFG_TUD_CDC == 1

// Invoked when cdc when line state changed e.g connected/disconnected
void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts) {
	(void)itf;
	(void)rts;

	// TODO set some indicator
	if (dtr) {
		// Terminal connected
	} else {
		// Terminal disconnected
	}
}

// Invoked when CDC interface received data from host
void tud_cdc_rx_cb(uint8_t itf) { (void)itf; }

#endif