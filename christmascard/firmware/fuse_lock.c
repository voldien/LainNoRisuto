#include <avr/io.h>

/**
 *	Fuses for the state of the microntroller through out
 *	its life time.
 */
FUSES = {
	.low = LFUSE_DEFAULT,
	.high = HFUSE_DEFAULT,
};

/**
 *	Data memory lock bit.
 */
LOCKBITS = LB_MODE_1;
