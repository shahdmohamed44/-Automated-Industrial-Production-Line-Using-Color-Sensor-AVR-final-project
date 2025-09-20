/*
 * TIMER0_program.c
 *
 * Created on: Sep 4, 2025
 * Author: SAGDA
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../LIBRARY/macros.h"
#include "TIMER0_interface.h"
#include "../external_interrupt/interface.h"
#include "TIMER0_private.h"


//PTR TO FUNC INITATE

void (*TIMER_OF_cb)(void) =  NULL_PTR;
void (*TIMER_CTC_cb)(void) =  NULL_PTR;
void (*TIMER_FPWM_cb)(void) =  NULL_PTR;
void (*TIMER_PCPWM_cb)(void) =  NULL_PTR;


// CLOCK GENERAL SELECT
static void TIMER0_clockSelect(CLOCK_SELECT clock);

void TIMER0_clockSelect(CLOCK_SELECT clock){
	switch(clock){
	case NO_CLOCK:
		CLEAR_BIT(TCCR0, CS02);
		CLEAR_BIT(TCCR0, CS01);
		CLEAR_BIT(TCCR0, CS00);
		break;
	case NO_PRESCALER:
		CLEAR_BIT(TCCR0, CS02);
		CLEAR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS00);
		break;

	case PRESCALER_8:
		CLEAR_BIT(TCCR0, CS02);
		SET_BIT(TCCR0, CS01);
		CLEAR_BIT(TCCR0, CS00);
		break;

	case PRESCALER_64:
		CLEAR_BIT(TCCR0, CS02);
		SET_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS00);
		break;

	case PRESCALER_256:
		SET_BIT(TCCR0, CS02);
		CLEAR_BIT(TCCR0, CS01);
		CLEAR_BIT(TCCR0, CS00);
		break;

	case PRESCALER_1024:
		SET_BIT(TCCR0, CS02);
		CLEAR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS00);
		break;
	}
}

//COUNTER MODE
void TIMER0_EXT_COUNT_init(void){

	TCNT0=0; // CLEAR COUNTER

	// EXT_CLK RISING EDGE
	SET_BIT(TCCR0,CS02);
	SET_BIT(TCCR0,CS01);
	SET_BIT(TCCR0,CS00);

	//FALLING EDGE
//	SET_BIT(TCCR0,CS02);
//	SET_BIT(TCCR0,CS01);
//	CLEAR_BIT(TCCR0,CS00);
}


// OVERFLOW MODE
void TIMER0_OF_init(CLOCK_SELECT clock){
	TCNT0 = TIMER0_PRELOAD;
	SET_BIT(TCCR0, FOC0);
	CLEAR_BIT(TCCR0, WGM01);
	CLEAR_BIT(TCCR0, WGM00);

	TIMER0_clockSelect(clock);

#if (TIMER0_OF_INTERRUPT_ENABLE == True)
	SET_BIT(TIMSK, TOIE0);
	EXT_interrupt_GIE_state(1);
#else
	while( BIT_IS_CLEAR(TIFR, TOV0) );
	SET_BIT(TIFR, TOV0);
	TCNT0 = 0;
#endif

}

// COMPARE MATCH MODE
void TIMER0_CTC_init(TIMER0_CTC_MODE_SELECT mode, CLOCK_SELECT clock, u8 compValue){

	TCNT0 = TIMER0_PRELOAD;
	OCR0 = compValue;

	SET_BIT(TCCR0, FOC0);
	SET_BIT(TCCR0, WGM01);
	CLEAR_BIT(TCCR0, WGM00);

	switch(mode){
	case OC0_CTC_NORTMAL:
		CLEAR_BIT(TCCR0, COM01);
		CLEAR_BIT(TCCR0, COM00);
		break;
	case TOGGLE_OC0:
		CLEAR_BIT(TCCR0, COM01);
		SET_BIT(TCCR0, COM00);
		break;
	case CLEAR_OC0:
		SET_BIT(TCCR0, COM01);
		CLEAR_BIT(TCCR0, COM00);
		break;
	case SET_OC0:
		SET_BIT(TCCR0, COM01);
		SET_BIT(TCCR0, COM00);
		break;
	}

	TIMER0_clockSelect(clock);

#if(TIMER0_CTC_INTERRUPT_ENABLE == True)
	SET_BIT(TIMSK, OCIE0);
	EXT_interrupt_GIE_state(1);
#else
	while(BIT_IS_CLEAR(TIFR, OCF0));
	SET_BIT(TIFR, OCF0);
#endif
}


//FAST PWM MODE
void TIMER0_FAST_PWM_init(FAST_PWM_MODE_SELECT mode, CLOCK_SELECT clock){

	TCNT0 = TIMER0_PRELOAD;
	OCR0 = 0;
	CLEAR_BIT(TCCR0, FOC0);
	SET_BIT(TCCR0, WGM01);
	SET_BIT(TCCR0, WGM00);

	switch(mode){
	case FAST_PWM_NORMAL:
		CLEAR_BIT(TCCR0, COM01);
		CLEAR_BIT(TCCR0, COM00);
		break;
	case NON_INVERTING_MODE:
		SET_BIT(TCCR0, COM01);
		CLEAR_BIT(TCCR0, COM00);
		break;
	case INVERTING_MODE:
		SET_BIT(TCCR0, COM01);
		SET_BIT(TCCR0, COM00);
		break;
	}

	TIMER0_clockSelect(clock);
	//INTERRUPT MODE
#if(TIMER0_FPWM_INTERRUPT_ENABLE == True)
	SET_BIT(TIMSK, OCIE0);
	EXT_interrupt_GIE_state(1);
#else
	while(BIT_IS_CLEAR(TIFR, OCF0));
	SET_BIT(TIFR, OCF0);
#endif



}

void TIMER0_FAST_PWM_set_dutyCycle(u8 dutyCycle){
	TCNT0 = TIMER0_PRELOAD;
	OCR0 = dutyCycle;
}

// PHASE CORRECT PWM MODE
void TIMER0_PhaseCorrect_PWM_init(PHASE_CORRECT_PWM_MODE_SELECT mode, CLOCK_SELECT clock){
	TCNT0 = TIMER0_PRELOAD;
	OCR0 = 0;
	CLEAR_BIT(TCCR0, FOC0);
	CLEAR_BIT(TCCR0, WGM01);
	SET_BIT(TCCR0, WGM00);

	switch(mode){
	case PHASE_CORRECT_PWM_NORMAL:
		CLEAR_BIT(TCCR0, COM01);
		CLEAR_BIT(TCCR0, COM00);
		break;
	case CLEAR_UPCOUNTING_MODE:
		SET_BIT(TCCR0, COM01);
		CLEAR_BIT(TCCR0, COM00);
		break;
	case SET_UPCOUNTING_MODE:
		SET_BIT(TCCR0, COM01);
		SET_BIT(TCCR0, COM00);
		break;
	}

	TIMER0_clockSelect(clock);
	//INTERRUPT MODE
#if(TIMER0_PCPWM_INTERRUPT_ENABLE == True)
	SET_BIT(TIMSK, OCIE0);
	EXT_interrupt_GIE_state(1);
#else
	while(BIT_IS_CLEAR(TIFR, OCF0));
	SET_BIT(TIFR, OCF0);
#endif

}

void TIMER0_PHASECORRECT_PWM_set_dutyCycle(u8 dutyCycle){
	OCR0 = dutyCycle;
}

// CALLING BACK FUNCS
void TIMER0_OF_set_cb(void (*cb)(void)){
	if(cb != NULL_PTR) TIMER_OF_cb = cb;
}
void TIMER0_CTC_set_cb(void (*cb)(void)){
	if(cb != NULL_PTR) TIMER_CTC_cb = cb;
}
void TIMER0_FPWM_set_cb(void (*cb)(void)){
	if(cb != NULL_PTR) TIMER_FPWM_cb = cb;
}
void TIMER0_PCPWM_set_cb(void (*cb)(void)){
	if(cb != NULL_PTR) TIMER_PCPWM_cb = cb;
}

ISR(TIMER0_COMP_vect){
#if(TIMER0_ALLOW_NESTING_INTERRUPT == True)
	EXT_interrupt_GIE_state(ENABLE);
#endif
	if(TIMER_CTC_cb != NULL_PTR) {
		TIMER_CTC_cb();
	}
	if(TIMER_FPWM_cb != NULL_PTR) {
		TIMER_FPWM_cb();
	}
	if(TIMER_PCPWM_cb != NULL_PTR) {
		TIMER_PCPWM_cb();
	}
}

ISR(TIMER0_OVF_vect){
#if(TIMER0_ALLOW_NESTING_INTERRUPT == True)
	EXT_interrupt_GIE_state(ENABLE);
#endif
	if(TIMER_OF_cb != NULL_PTR) {
		TIMER_OF_cb();
	}
}
