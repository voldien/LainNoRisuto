#include <avr/io.h>

/**
 *	Fuses for the state of the microntroller through out
 *	its life time.
 */
#ifdef __AVR_ATmega328P__
FUSES = {
	.low = FUSE_SUT0 & FUSE_SUT1 & FUSE_CKSEL3 & FUSE_CKSEL2 & FUSE_CKSEL0,
	.high = HFUSE_DEFAULT,
};
#else
FUSES = {
	.low = FUSE_SPIEN & FUSE_CKDIV8 &FUSE_SUT1 & FUSE_CKSEL1,
	.high = HFUSE_DEFAULT,
};
#endif

/**
 *	Data memory lock bit.
 */
LOCKBITS = LB_MODE_1;
