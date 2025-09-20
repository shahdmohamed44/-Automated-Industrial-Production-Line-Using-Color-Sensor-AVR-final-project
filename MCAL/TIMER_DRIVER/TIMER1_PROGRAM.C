/*
 * Timer1.c
 *
 * Created on: Sep 8, 2025
 * Author: shahd mohamed
 */


#include "TIMER1_interface.h"
#include "TIMER1_private.h"

// Global callback pointers
static void (*of_cb)(void) = NULL_PTR;
static void (*ctcA_cb)(void) = NULL_PTR;
static void (*ctcB_cb)(void) = NULL_PTR;

void TIMER1_OF_init(CLOCK_SELECT clock) {
    // Normal mode
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = TIMER1_PRELOAD;

    if (TIMER1_OF_INTERRUPT_ENABLE) {
        SET_BIT(TIMSK, TOIE1);
    }

    // Select clock
    TCCR1B |= clock;
}

void TIMER1_CTC_init(TIMER1_CTC_MODE_SELECT ctc_OC1A,
                     TIMER1_CTC_MODE_SELECT ctc_OC1B,
                     CLOCK_SELECT clock,
                     u16 compValueA,
                     u16 compValueB) {
    // CTC Mode with OCR1A/B
    TCCR1A = 0;
    TCCR1B = 0;

    // Compare values
    OCR1A = compValueA;
    OCR1B = compValueB;

    // Configure OC1A behavior
    switch (ctc_OC1A) {
    case OC1_CTC_NORMAL:
        CLEAR_BIT(TCCR1A, COM1A1);
        CLEAR_BIT(TCCR1A, COM1A0);
        break;
    case TOGGLE_OC1:
        CLEAR_BIT(TCCR1A, COM1A1);
        SET_BIT(TCCR1A, COM1A0);
        break;
    case CLEAR_OC1:
        SET_BIT(TCCR1A, COM1A1);
        CLEAR_BIT(TCCR1A, COM1A0);
        break;
    case SET_OC1:
        SET_BIT(TCCR1A, COM1A1);
        SET_BIT(TCCR1A, COM1A0);
        break;
    }

    // Configure OC1B behavior
    switch (ctc_OC1B) {
    case OC1_CTC_NORMAL:
        CLEAR_BIT(TCCR1A, COM1B1);
        CLEAR_BIT(TCCR1A, COM1B0);
        break;
    case TOGGLE_OC1:
        CLEAR_BIT(TCCR1A, COM1B1);
        SET_BIT(TCCR1A, COM1B0);
        break;
    case CLEAR_OC1:
        SET_BIT(TCCR1A, COM1B1);
        CLEAR_BIT(TCCR1A, COM1B0);
        break;
    case SET_OC1:
        SET_BIT(TCCR1A, COM1B1);
        SET_BIT(TCCR1A, COM1B0);
        break;
    }

    if (TIMER1_CTC_INTERRUPT_ENABLE_A) {
        SET_BIT(TIMSK, OCIE1A);
    }
    if (TIMER1_CTC_INTERRUPT_ENABLE_B) {
        SET_BIT(TIMSK, OCIE1B);
    }

    // Enable CTC mode (WGM12=1)
    SET_BIT(TCCR1B, WGM12);

    // Select clock
    TCCR1B |= clock;
}

void TIMER1_FAST_PWM_init(FAST_PWM_MODE_SELECT mode_A,
                          FAST_PWM_MODE_SELECT mode_B,
                          CLOCK_SELECT clock,
                          u16 top) {
    // Fast PWM with ICR1 as TOP
    TCCR1A = 0;
    TCCR1B = 0;

    ICR1 = top;

    // OC1A mode
    switch (mode_A) {
    case FAST_PWM_NORMAL:
        CLEAR_BIT(TCCR1A, COM1A1);
        CLEAR_BIT(TCCR1A, COM1A0);
        break;
    case NON_INVERTING_MODE:
        SET_BIT(TCCR1A, COM1A1);
        CLEAR_BIT(TCCR1A, COM1A0);
        break;
    case INVERTING_MODE:
        SET_BIT(TCCR1A, COM1A1);
        SET_BIT(TCCR1A, COM1A0);
        break;
    }

    // OC1B mode
    switch (mode_B) {
    case FAST_PWM_NORMAL:
        CLEAR_BIT(TCCR1A, COM1B1);
        CLEAR_BIT(TCCR1A, COM1B0);
        break;
    case NON_INVERTING_MODE:
        SET_BIT(TCCR1A, COM1B1);
        CLEAR_BIT(TCCR1A, COM1B0);
        break;
    case INVERTING_MODE:
        SET_BIT(TCCR1A, COM1B1);
        SET_BIT(TCCR1A, COM1B0);
        break;
    }

    // Fast PWM mode 14: WGM13=1, WGM12=1, WGM11=1, WGM10=0
    SET_BIT(TCCR1B, WGM13);
    SET_BIT(TCCR1B, WGM12);
    SET_BIT(TCCR1A, WGM11);
    CLEAR_BIT(TCCR1A, WGM10);

    // Select clock
    TCCR1B |= clock;
}

void TIMER1_FAST_PWM_set_dutyCycle_A(u16 dutyCycle) {

    OCR1A = dutyCycle;
}

void TIMER1_FAST_PWM_set_dutyCycle_B(u16 dutyCycle) {

    OCR1B = dutyCycle;
}

void TIMER1_OF_set_cb(void (*cb)(void)) {
    of_cb = cb;
}
void TIMER1_CTC_set_cb_A(void (*cb)(void)) {
    ctcA_cb = cb;
}
void TIMER1_CTC_set_cb_B(void (*cb)(void)) {
    ctcB_cb = cb;
}

// ================== ISRs ==================

ISR(TIMER1_OVF_vect) {
    if (of_cb) of_cb();
}

ISR(TIMER1_COMPA_vect) {
    if (ctcA_cb) ctcA_cb();
}

ISR(TIMER1_COMPB_vect) {
    if (ctcB_cb) ctcB_cb();
}
