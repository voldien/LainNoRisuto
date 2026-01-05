/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "bsp/board_api.h"
#include "class/cdc/cdc.h"
#include "class/hid/hid_device.h"
#include "class/video/video.h"
#include "device/usbd.h"
#include "gfx/gfx.h"
#include <string.h>

#include "usb_descriptors.h"

//--------------------------------------------------------------------+
// String Descriptors
//--------------------------------------------------------------------+

// String Descriptor Index
enum {
	STRID_LANGID = 0,
	STRID_MANUFACTURER,
	STRID_PRODUCT,
	STRID_SERIAL,
#if CFG_TUD_VIDEO == 1
	STRID_UVC_CONTROL,
	STRID_UVC_STREAMING,
#endif
	STRID_CDC_CONTROL,
	STRID_CDC_STREAMING,
};

// array of pointer to string descriptors
char const *string_desc_arr[] = {
	(const char[]){0x09, 0x04}, // 0: is supported language is English (0x0409)
	"Neko",						// 1: Manufacturer
	"PicoGraphic",				// 2: Product
	"123456",					// 3: Serials, should use chip ID
#if CFG_TUD_VIDEO == 1
	"Video Control", //
	"Video Stream",	 //
#endif
	"CDC",		//
	"CDC Data", //
};

static uint16_t desc_str[32];

// Invoked when received GET STRING DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
	(void)langid;
	size_t chr_count = 0;

	switch (index) {
	case STRID_LANGID:
		memcpy(&desc_str[1], string_desc_arr[0], 2);
		chr_count = 1;
		break;

	case STRID_SERIAL:
		chr_count = board_usb_get_serial(desc_str + 1, 32);
		break;

	default:
		// Note: the 0xEE index string is a Microsoft OS 1.0 Descriptors.
		// https://docs.microsoft.com/en-us/windows-hardware/drivers/usbcon/microsoft-defined-usb-descriptors

		if (!(index < sizeof(string_desc_arr) / sizeof(string_desc_arr[0]))) {
			return NULL;
		}

		const char *str = string_desc_arr[index];

		// Cap at max char
		chr_count = strlen(str);
		size_t const max_count = (sizeof(desc_str) / sizeof(desc_str[0])) - 1; // -1 for string type
		if (chr_count > max_count) {
			chr_count = max_count;
		}

		// Convert ASCII string into UTF-16
		for (size_t i = 0; i < chr_count; i++) {
			desc_str[1 + i] = str[i];
		}
		break;
	}

	// first byte is length (including header), second byte is string type
	desc_str[0] = (uint16_t)((TUSB_DESC_STRING << 8) | (2 * chr_count + 2));

	return desc_str;
}

// #include "usb_descriptors.h"

/* A combination of interfaces must have a unique product id, since PC will save device driver after the first plug.
 * Same VID/PID with different interface e.g MSC (first), then CDC (later) will possibly cause system error on PC.
 *
 * Auto ProductID layout's Bitmap:
 *   [MSB]         HID | MSC | CDC          [LSB]
 */
#define _PID_MAP(itf, n) ((CFG_TUD_##itf) << (n))
#define USB_PID                                                                                                        \
	(0x4000 | _PID_MAP(CDC, 0) | _PID_MAP(MSC, 1) | _PID_MAP(HID, 2) | _PID_MAP(MIDI, 3) | _PID_MAP(VENDOR, 4))

#define USB_VID 0xCafe
#define USB_BCD 0x0200

//--------------------------------------------------------------------+
// Device Descriptors
//--------------------------------------------------------------------+

tusb_desc_device_t const desc_device = {
	.bLength = sizeof(tusb_desc_device_t),
	.bDescriptorType = TUSB_DESC_DEVICE, /*  */
	.bcdUSB = USB_BCD,					 /*  */

	.bDeviceClass = 0,						   /*  */
	.bDeviceSubClass = MISC_SUBCLASS_COMMON,   /*  */
	.bDeviceProtocol = MISC_PROTOCOL_IAD,	   /*  */
	.bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE, /*  */

	.idVendor = USB_VID,  /*  */
	.idProduct = USB_PID, /*  */
	.bcdDevice = 0x0100,  /*  */

	.iManufacturer = 0x01, /*  Description Index.	*/
	.iProduct = 0x02,	   /*  Description Index.*/
	.iSerialNumber = 0x03, /*  Description Index.*/

	.bNumConfigurations = 0x01 /*  */
};

// Invoked when received GET DEVICE DESCRIPTOR
// Application return pointer to descriptor
uint8_t const *tud_descriptor_device_cb(void) { return (uint8_t const *)&desc_device; }

//--------------------------------------------------------------------+
// CDC Descriptor
//--------------------------------------------------------------------+

#if CFG_TUSB_MCU == OPT_MCU_LPC175X_6X || CFG_TUSB_MCU == OPT_MCU_LPC177X_8X || CFG_TUSB_MCU == OPT_MCU_LPC40XX
// LPC 17xx and 40xx endpoint type (bulk/interrupt/iso) are fixed by its number
// 0 control, 1 In, 2 Bulk, 3 Iso, 4 In, 5 Bulk etc ...
#define EPNUM_CDC_NOTIF 0x81
#define EPNUM_CDC_OUT 0x02
#define EPNUM_CDC_IN 0x82

#elif CFG_TUSB_MCU == OPT_MCU_CXD56
// CXD56 USB driver has fixed endpoint type (bulk/interrupt/iso) and direction (IN/OUT) by its number
// 0 control (IN/OUT), 1 Bulk (IN), 2 Bulk (OUT), 3 In (IN), 4 Bulk (IN), 5 Bulk (OUT), 6 In (IN)
#define EPNUM_CDC_NOTIF 0x83
#define EPNUM_CDC_OUT 0x02
#define EPNUM_CDC_IN 0x81

#elif defined(TUD_ENDPOINT_ONE_DIRECTION_ONLY)
// MCUs that don't support a same endpoint number with different direction IN and OUT defined in tusb_mcu.h
//    e.g EP1 OUT & EP1 IN cannot exist together
#define EPNUM_CDC_NOTIF 0x81
#define EPNUM_CDC_OUT 0x02
#define EPNUM_CDC_IN 0x83

#else
/*	*/
#define EPNUM_CDC_NOTIF 0x81
#define EPNUM_CDC_OUT 0x02
#define EPNUM_CDC_IN 0x82

/*	*/
#define EPNUM_MSC_OUT 0x03
#define EPNUM_MSC_IN 0x83

#endif

//---------------------------------
// Video Capture Report Descriptor
//---------------------------------------

/* Time stamp base clock. It is a deprecated parameter. */
#define UVC_CLOCK_FREQUENCY 30000000

/* video capture path */
#define UVC_ENTITY_CAP_INPUT_TERMINAL 0x01
#define UVC_ENTITY_CAP_OUTPUT_TERMINAL 0x02

// Select appropriate endpoint number
#if TU_CHECK_MCU(OPT_MCU_LPC175X_6X, OPT_MCU_LPC177X_8X, OPT_MCU_LPC40XX)
// LPC 17xx and 40xx endpoint type (bulk/interrupt/iso) are fixed by its number
// 0 control, 1 In, 2 Bulk, 3 Iso, 4 In, 5 Bulk etc ...
#define EPNUM_VIDEO_IN (CFG_TUD_VIDEO_STREAMING_BULK ? 0x82 : 0x83)
#elif TU_CHECK_MCU(OPT_MCU_NRF5X)
// nRF5x ISO can only be endpoint 8
#define EPNUM_VIDEO_IN (CFG_TUD_VIDEO_STREAMING_BULK ? 0x81 : 0x88)
#elif TU_CHECK_MCU(OPT_MCU_MAX32650, OPT_MCU_MAX32666, OPT_MCU_MAX32690, OPT_MCU_MAX78002)
#define EPNUM_VIDEO_IN 0x88
#else
#define EPNUM_VIDEO_IN 0x88
#endif

#if defined(CFG_EXAMPLE_VIDEO_READONLY) && !defined(CFG_EXAMPLE_VIDEO_DISABLE_MJPEG)
#define USE_MJPEG 1
#else
#define USE_MJPEG 0
#endif

#define USE_ISO_STREAMING (!CFG_TUD_VIDEO_STREAMING_BULK)

typedef struct TU_ATTR_PACKED {
	tusb_desc_interface_t itf;
	tusb_desc_video_control_header_1itf_t header;
	tusb_desc_video_control_camera_terminal_t camera_terminal;
	tusb_desc_video_control_output_terminal_t output_terminal;
} uvc_control_desc_t;

typedef struct TU_ATTR_PACKED {
	tusb_desc_interface_t itf;
	tusb_desc_video_streaming_input_header_1byte_t header;

#if USE_MJPEG
	tusb_desc_video_format_mjpeg_t format;
	tusb_desc_video_frame_mjpeg_continuous_t frame;
#else
	tusb_desc_video_format_uncompressed_t format;
	tusb_desc_video_frame_uncompressed_continuous_t frame;
#endif

	tusb_desc_video_streaming_color_matching_t color;

#if USE_ISO_STREAMING
	// For ISO streaming, USB spec requires to alternate interface
	tusb_desc_interface_t itf_alt;
#endif

	tusb_desc_endpoint_t ep;
} uvc_streaming_desc_t;

typedef struct TU_ATTR_PACKED {

	tusb_desc_configuration_t config;
	tusb_desc_interface_assoc_t iad;

	#if CFG_TUD_VIDEO == 1
	uvc_control_desc_t video_control;
	uvc_streaming_desc_t video_streaming;
	#endif

	/*	*/
	uint8_t cdc_config[TUD_CDC_DESC_LEN];
} uvc_cfg_desc_t;

const uvc_cfg_desc_t __in_flash()

	desc_fs_configuration = {
		.config = {.bLength = sizeof(tusb_desc_configuration_t),
				   .bDescriptorType = TUSB_DESC_CONFIGURATION,

				   .wTotalLength = sizeof(uvc_cfg_desc_t),
				   .bNumInterfaces = ITF_1_NUM_TOTAL,
				   .bConfigurationValue = 1,
				   .iConfiguration = 0,
				   .bmAttributes = TU_BIT(7),
				   .bMaxPower = 100 / 2},
#if CFG_TUD_VIDEO == 1
		.iad = {.bLength = sizeof(tusb_desc_interface_assoc_t),
				.bDescriptorType = TUSB_DESC_INTERFACE_ASSOCIATION,

				.bFirstInterface = ITF_1_NUM_VIDEO_CONTROL,
				.bInterfaceCount = 2,
				.bFunctionClass = TUSB_CLASS_VIDEO,
				.bFunctionSubClass = VIDEO_SUBCLASS_INTERFACE_COLLECTION,
				.bFunctionProtocol = VIDEO_ITF_PROTOCOL_UNDEFINED,
				.iFunction = 0},

		.video_control = {.itf = {.bLength = sizeof(tusb_desc_interface_t),
								  .bDescriptorType = TUSB_DESC_INTERFACE,

								  .bInterfaceNumber = ITF_1_NUM_VIDEO_CONTROL,
								  .bAlternateSetting = 0,
								  .bNumEndpoints = 0,
								  .bInterfaceClass = TUSB_CLASS_VIDEO,
								  .bInterfaceSubClass = VIDEO_SUBCLASS_CONTROL,
								  .bInterfaceProtocol = VIDEO_ITF_PROTOCOL_15,
								  .iInterface = STRID_UVC_CONTROL},
						  .header = {.bLength = sizeof(tusb_desc_video_control_header_1itf_t),
									 .bDescriptorType = TUSB_DESC_CS_INTERFACE,
									 .bDescriptorSubType = VIDEO_CS_ITF_VC_HEADER,

									 .bcdUVC = VIDEO_BCD_1_50,
									 .wTotalLength = sizeof(uvc_control_desc_t) -
													 sizeof(tusb_desc_interface_t), // CS VC descriptors only
									 .dwClockFrequency = UVC_CLOCK_FREQUENCY,
									 .bInCollection = 1,
									 .baInterfaceNr = {ITF_1_NUM_VIDEO_STREAMING}},
						  .camera_terminal = {.bLength = sizeof(tusb_desc_video_control_camera_terminal_t),
											  .bDescriptorType = TUSB_DESC_CS_INTERFACE,
											  .bDescriptorSubType = VIDEO_CS_ITF_VC_INPUT_TERMINAL,

											  .bTerminalID = UVC_ENTITY_CAP_INPUT_TERMINAL,
											  .wTerminalType = VIDEO_ITT_CAMERA,
											  .bAssocTerminal = 0,
											  .iTerminal = 0,
											  .wObjectiveFocalLengthMin = 0,
											  .wObjectiveFocalLengthMax = 0,
											  .wOcularFocalLength = 0,
											  .bControlSize = 3,
											  .bmControls = {0, 0, 0}},
						  .output_terminal = {.bLength = sizeof(tusb_desc_video_control_output_terminal_t),
											  .bDescriptorType = TUSB_DESC_CS_INTERFACE,
											  .bDescriptorSubType = VIDEO_CS_ITF_VC_OUTPUT_TERMINAL,

											  .bTerminalID = UVC_ENTITY_CAP_OUTPUT_TERMINAL,
											  .wTerminalType = VIDEO_TT_STREAMING,
											  .bAssocTerminal = 0,
											  .bSourceID = UVC_ENTITY_CAP_INPUT_TERMINAL,
											  .iTerminal = 0}},

		.video_streaming = {.itf = {.bLength = sizeof(tusb_desc_interface_t),
									.bDescriptorType = TUSB_DESC_INTERFACE,

									.bInterfaceNumber = ITF_1_NUM_VIDEO_STREAMING,
									.bAlternateSetting = 0,
									.bNumEndpoints = CFG_TUD_VIDEO_STREAMING_BULK, // bulk 1, iso 0
									.bInterfaceClass = TUSB_CLASS_VIDEO,
									.bInterfaceSubClass = VIDEO_SUBCLASS_STREAMING,
									.bInterfaceProtocol = VIDEO_ITF_PROTOCOL_15,
									.iInterface = STRID_UVC_STREAMING},
							.header = {.bLength = sizeof(tusb_desc_video_streaming_input_header_1byte_t),
									   .bDescriptorType = TUSB_DESC_CS_INTERFACE,
									   .bDescriptorSubType = VIDEO_CS_ITF_VS_INPUT_HEADER,

									   .bNumFormats = 1,
									   .wTotalLength = sizeof(uvc_streaming_desc_t) - sizeof(tusb_desc_interface_t) -
													   sizeof(tusb_desc_endpoint_t) -
													   (USE_ISO_STREAMING ? sizeof(tusb_desc_interface_t)
																		  : 0), // CS VS descriptors only
									   .bEndpointAddress = EPNUM_VIDEO_IN,
									   .bmInfo = 0,
									   .bTerminalLink = UVC_ENTITY_CAP_OUTPUT_TERMINAL,
									   .bStillCaptureMethod = 0,
									   .bTriggerSupport = 0,
									   .bTriggerUsage = 0,
									   .bControlSize = 1,
									   .bmaControls = {0}},
							.format =
								{

									.bLength = sizeof(tusb_desc_video_format_uncompressed_t),
									.bDescriptorType = TUSB_DESC_CS_INTERFACE,
									.bDescriptorSubType = VIDEO_CS_ITF_VS_FORMAT_UNCOMPRESSED,
									.bFormatIndex = 1, // 1-based index
									.bNumFrameDescriptors = 1,
									.guidFormat = {TUD_VIDEO_GUID_YUY2},
									.bBitsPerPixel = 16,

									.bDefaultFrameIndex = 1,
									.bAspectRatioX = 0,
									.bAspectRatioY = 0,
									.bmInterlaceFlags = 0,
									.bCopyProtect = 0},
							.frame = {.bLength = sizeof(tusb_desc_video_frame_uncompressed_continuous_t),
									  .bDescriptorType = TUSB_DESC_CS_INTERFACE,
									  .bDescriptorSubType = VIDEO_CS_ITF_VS_FRAME_UNCOMPRESSED,

									  /*	*/
									  .bFrameIndex = 1, // 1-based index
									  .bmCapabilities = 0,
									  .wWidth = FRAME_WIDTH,
									  .wHeight = FRAME_HEIGHT,
									  .dwMinBitRate = FRAME_WIDTH * FRAME_HEIGHT * 16 * 1,
									  .dwMaxBitRate = FRAME_WIDTH * FRAME_HEIGHT * 16 * FRAME_RATE,
									  .dwMaxVideoFrameBufferSize = FRAME_WIDTH * FRAME_HEIGHT * (16 / 8),
									  .dwDefaultFrameInterval = 10000000 / FRAME_RATE,
									  .bFrameIntervalType = 0, // continuous
									  .dwFrameInterval =
										  {
											  10000000 / FRAME_RATE, // min
											  10000000,				 // max
											  10000000 / FRAME_RATE	 // step
										  }},
							.color = {.bLength = sizeof(tusb_desc_video_streaming_color_matching_t),
									  .bDescriptorType = TUSB_DESC_CS_INTERFACE,
									  .bDescriptorSubType = VIDEO_CS_ITF_VS_COLORFORMAT,

									  .bColorPrimaries = VIDEO_COLOR_PRIMARIES_BT709,
									  .bTransferCharacteristics = VIDEO_COLOR_XFER_CH_BT709,
									  .bMatrixCoefficients = VIDEO_COLOR_COEF_SMPTE170M},

#if USE_ISO_STREAMING
							.itf_alt = {.bLength = sizeof(tusb_desc_interface_t),
										.bDescriptorType = TUSB_DESC_INTERFACE,

										.bInterfaceNumber = ITF_1_NUM_VIDEO_STREAMING,
										.bAlternateSetting = 1,
										.bNumEndpoints = 1,
										.bInterfaceClass = TUSB_CLASS_VIDEO,
										.bInterfaceSubClass = VIDEO_SUBCLASS_STREAMING,
										.bInterfaceProtocol = VIDEO_ITF_PROTOCOL_15,
										.iInterface = STRID_UVC_STREAMING},
#endif

							.ep = {.bLength = sizeof(tusb_desc_endpoint_t),
								   .bDescriptorType = TUSB_DESC_ENDPOINT,

								   .bEndpointAddress = EPNUM_VIDEO_IN,
								   .bmAttributes =
									   {
										   .xfer = CFG_TUD_VIDEO_STREAMING_BULK ? TUSB_XFER_BULK
																				: TUSB_XFER_ISOCHRONOUS,
										   .sync = CFG_TUD_VIDEO_STREAMING_BULK ? 0 : 1 // asynchronous
									   },
								   .wMaxPacketSize = CFG_TUD_VIDEO_STREAMING_BULK ? 64
																				  : CFG_TUD_VIDEO_STREAMING_EP_BUFSIZE,
								   .bInterval = 1}},
#endif
		.cdc_config = {TUD_CDC_DESCRIPTOR(ITF_NUM_CDC, 4, EPNUM_CDC_NOTIF, 8, EPNUM_CDC_OUT, EPNUM_CDC_IN, 64)},
	};

/*	PICO does not support.	*/
#if TUD_OPT_HIGH_SPEED
// Per USB specs: high speed capable device must report device_qualifier and other_speed_configuration
uint8_t const desc_configuration[] = {
	// Config number, interface count, string index, total length, attribute, power in mA

	TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 150),

#if CFG_TUD_CDC == 1
	// Interface number, string index, EP notification address and size, EP data address (out, in) and size.
	TUD_CDC_DESCRIPTOR(ITF_NUM_CDC, 4, EPNUM_CDC_NOTIF, 8, EPNUM_CDC_OUT, EPNUM_CDC_IN, 64),
#endif

#if CFG_TUD_VIDEO == 1

#endif
}; /*  */

// other speed configuration
uint8_t desc_other_speed_config[CONFIG_TOTAL_LEN];

// device qualifier is mostly similar to device descriptor since we don't change configuration based on speed
tusb_desc_device_qualifier_t const desc_device_qualifier = {.bLength = sizeof(tusb_desc_device_qualifier_t),
															.bDescriptorType = TUSB_DESC_DEVICE_QUALIFIER,
															.bcdUSB = USB_BCD,

															.bDeviceClass = 0x00,
															.bDeviceSubClass = 0x00,
															.bDeviceProtocol = 0x00,

															.bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,
															.bNumConfigurations = 0x01,
															.bReserved = 0x00};

// Invoked when received GET DEVICE QUALIFIER DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete.
// device_qualifier descriptor describes information about a high-speed capable device that would
// change if the device were operating at the other speed. If not highspeed capable stall this request.
uint8_t const *tud_descriptor_device_qualifier_cb(void) { return (uint8_t const *)&desc_device_qualifier; }

// Invoked when received GET OTHER SEED CONFIGURATION DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
// Configuration descriptor in the other speed e.g if high speed then this is for full speed and vice versa
uint8_t const *tud_descriptor_other_speed_configuration_cb(uint8_t index) {
	(void)index; // for multiple configurations

	// other speed config is basically configuration with type = OHER_SPEED_CONFIG
	memcpy(desc_other_speed_config, desc_configuration, CONFIG_TOTAL_LEN);
	desc_other_speed_config[1] = TUSB_DESC_OTHER_SPEED_CONFIG;

	// this example use the same configuration for both high and full speed mode
	return desc_other_speed_config;
}

#endif // highspeed

uint8_t const *tud_descriptor_configuration_cb(uint8_t index) {
	(void)index; // for multiple configurations
	return (uint8_t const *)&desc_fs_configuration;
}
