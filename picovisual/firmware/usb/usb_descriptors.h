#ifndef USB_DESCRIPTORS_H_
#define USB_DESCRIPTORS_H_ 1

/*  VIDEO Settings */
// #define FRAME_WIDTH 240u
// #define FRAME_HEIGHT 320u
// #define FRAME_RATE 30u

//--------------------------------------------------------------------+
// Configuration Descriptor
//--------------------------------------------------------------------+

enum {
#if CFG_TUD_VIDEO == 1
	ITF_1_NUM_VIDEO_CONTROL,
	ITF_1_NUM_VIDEO_STREAMING,
#endif
#if CFG_TUD_CDC == 1
	ITF_NUM_CDC,
	ITF_NUM_CDC_DATA,
#endif

	ITF_1_NUM_TOTAL /*  */
};
#endif /* USB_DESCRIPTORS_H_ */