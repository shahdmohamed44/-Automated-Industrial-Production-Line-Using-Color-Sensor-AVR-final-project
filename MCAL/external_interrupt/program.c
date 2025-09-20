#include "private.h"
#include "interface.h"
#include <avr/interrupt.h>
#include "../../LIBRARY/macros.h"
#include "../../LIBRARY/standard_types.h"
#include <stdio.h>
#include <stdlib.h>


// Pointers to callback functions
void (*int0_cb)(void) = NULL;
void (*int1_cb)(void) = NULL;
void (*int2_cb)(void) = NULL;

void EXT_INT0_init(u8 state, INT_CONTROL ctrl){
    if (state == 1){
        SET_BIT(MCUCR, ISC00);
        SET_BIT(MCUCR, ISC01);
    }
    else{
        CLEAR_BIT(MCUCR, ISC00);
        CLEAR_BIT(MCUCR, ISC01);
    }
}

void EXT_INT1_init(u8 state, INT_CONTROL ctrl){
    if (state == 1){
        SET_BIT(MCUCR, ISC10);
        SET_BIT(MCUCR, ISC11);
    }
    else{
        CLEAR_BIT(MCUCR, ISC10);
        CLEAR_BIT(MCUCR, ISC11);
    }
}

void EXT_INT2_init(u8 state, INT_CONTROL ctrl){
    if (state == 1){
        SET_BIT(MCUCSR, ISC2);
    }
    else{
        CLEAR_BIT(MCUCSR, ISC2);
    }
}


//////////////////////////////////////////////////////
void EXT_int0_set_cb(void (*cb)(void)){
    if (cb != NULL) {
        int0_cb = cb;
    }
}
void EXT_int1_set_cb(void (*cb)(void)){
    if (cb != NULL) {
        int1_cb = cb;
    }
}
void EXT_int2_set_cb(void (*cb)(void)){
    if (cb != NULL) {
        int2_cb = cb;
    }
}
//////////////////////////////////////////////////////

void EXT_interrupt_GIE_state(u8 state){
    if (state == 1){
        sei();
    }
    else{
        cli();
    }
}
ISR(INT0_VECT){
	(*int0_cb)();


}
ISR(INT1_VECT){
	(*int1_cb)();

}
ISR(INT2_VECT){
	(*int2_cb)();

}
