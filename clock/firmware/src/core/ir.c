#include"core/ir.h"


void irInit(void){
    /* Set INT0 to trigger on any edge */
    EICRA |= _BV(ISC00);
    /* Set PD2 to input */
    DDRD &= ~_BV(PD2);

    /* Reset Timer1 Counter */
    TCCR1A = 0;
    /* Enable Timer1 in normal mode with /8 clock prescaling */
    /* One tick is 500ns with 16MHz clock */
    TCCR1B = _BV(CS11);
}
