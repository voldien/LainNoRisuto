#include"ledboard.h"
#include<avr/lock.h>
#include<avr/fuse.h>
#include<avr/io.h>

/**
 *	Fuses for the state of the microntroller through out
 *	its life time.
 */
FUSES =
{
	.low = (FUSE_CKSEL0 & FUSE_SUT0 & FUSE_CKDIV8 & FUSE_SPIEN),
	.high = HFUSE_DEFAULT,
};

/**
 *	Data memory lock bit.
 */
LOCKBITS = LB_MODE_1;
