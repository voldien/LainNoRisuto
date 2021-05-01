#include"animation.h"

volatile uint8_t curanim = 0;
volatile uint8_t curaniindex = 0;

/*	Animation.	*/
const struct animation_t PROGMEM ani[NRANIM]  = {
	CREATE_ANIMIATION(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6,
					  5, 4, 3, 2, 1, 0, 0),
	CREATE_ANIMIATION(15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
					  15, 15, 15, 15, 15, 15, 15),
	CREATE_ANIMIATION(15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15,
					  0, 15, 0),
	CREATE_ANIMIATION(0, 2, 4, 8, 10, 12, 14, 15, 0, 2, 4, 8, 10, 12, 14, 15, 0, 2, 4, 8, 10, 12, 14, 15, 0, 2, 4, 8, 10,
					  12, 14, 15),
	CREATE_ANIMIATION(0, 2, 4, 8, 10, 12, 14, 15, 14, 12, 10, 8, 6, 4, 2, 0, 0, 2, 4, 8, 10, 12, 14, 15, 14, 12, 10, 8, 6,
					  4, 2, 0),
	CREATE_ANIMIATION(0, 2, 8, 15, 8, 2, 0, 0, 2, 8, 15, 8, 2, 0, 0, 0, 0, 2, 8, 15, 8, 2, 0, 0, 2, 8, 15, 8, 2, 0, 0, 0),

	/*	TODO next!	*/
	CREATE_ANIMIATION(15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
					  15, 15, 15, 15, 15, 15, 15),
	CREATE_ANIMIATION(15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15,
					  0, 15, 0),
	CREATE_ANIMIATION(0, 2, 4, 8, 10, 12, 14, 15, 0, 2, 4, 8, 10, 12, 14, 15, 0, 2, 4, 8, 10, 12, 14, 15, 0, 2, 4, 8, 10,
					  12, 14, 15),
	CREATE_ANIMIATION(0, 2, 4, 8, 10, 12, 14, 15, 14, 12, 10, 8, 6, 4, 2, 0, 0, 2, 4, 8, 10, 12, 14, 15, 14, 12, 10, 8, 6,
					  4, 2, 0),
	CREATE_ANIMIATION(0, 2, 8, 15, 8, 2, 0, 0, 2, 8, 15, 8, 2, 0, 0, 0, 0, 2, 8, 15, 8, 2, 0, 0, 2, 8, 15, 8, 2, 0, 0, 0),

	CREATE_ANIMIATION(0, 2, 8, 15, 8, 2, 0, 0, 2, 8, 15, 8, 2, 0, 0, 0, 0, 2, 8, 15, 8, 2, 0, 0, 2, 8, 15, 8, 2, 0, 0, 0),

	CREATE_ANIMIATION(15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
					  15, 15, 15, 15, 15, 15, 15),
	CREATE_ANIMIATION(15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15,
					  0, 15, 0),
	CREATE_ANIMIATION(0, 2, 4, 8, 10, 12, 14, 15, 0, 2, 4, 8, 10, 12, 14, 15, 0, 2, 4, 8, 10, 12, 14, 15, 0, 2, 4, 8, 10,
					  12, 14, 15),
	CREATE_ANIMIATION(0, 2, 4, 8, 10, 12, 14, 15, 14, 12, 10, 8, 6, 4, 2, 0, 0, 2, 4, 8, 10, 12, 14, 15, 14, 12, 10, 8, 6,
					  4, 2, 0),
	CREATE_ANIMIATION(0, 2, 8, 15, 8, 2, 0, 0, 2, 8, 15, 8, 2, 0, 0, 0, 0, 2, 8, 15, 8, 2, 0, 0, 2, 8, 15, 8, 2, 0, 0, 0),
};

void init_animation(void){
	curanim = 0;
	curaniindex = 0;
}

uint8_t intp(uint8_t a, uint8_t b, uint8_t t){
	return a + (a - b);
}


const uint8_t get_curr_next_animation_keyframe(void){

	const uint8_t index = curaniindex;

	const uint8_t offset = index / 2;

	const uint16_t* addr = (const uint16_t*)&ani[curanim].ani[offset];
	register uint8_t p = pgm_read_byte(addr);

	/*	Extract value.	*/
	if(index % 2 == 0)
		p = (p >> LEDRES) & 0xF;
	else
		p = p & 0xF;

	/*	Update.	*/
	curaniindex++;
	curaniindex %= NRANIMENTRY;

	register const uint8_t factor = (1 << LEDRES);

	/*	[0,15] * (2^4) + [0,15]	*/
	return p * factor + p;
}


void reset_for_next_animation(void){
	curanim = (curanim + 1) % NRANIM;
	curaniindex = 0;
}
