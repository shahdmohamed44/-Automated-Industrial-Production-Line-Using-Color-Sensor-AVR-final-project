/*
 * TIMER1_interface.h
 *
 *  Created on: Sep 8, 2025
 *      Author: shahd mohamed
 */

#ifndef MCAL_TIMER_DRIVER_TIMER1_INTERFACE_H_
#define MCAL_TIMER_DRIVER_TIMER1_INTERFACE_H_

#include "../../LIBRARY/macros.h"
#include "../../LIBRARY/standard_types.h"
#include "TIMER_config.h"

#define TIMER1_PRELOAD 0
#define TIMER1_OF_INTERRUPT_ENABLE True
#define TIMER1_CTC_INTERRUPT_ENABLE_A True
#define TIMER1_CTC_INTERRUPT_ENABLE_B True



typedef enum {
    OC1_CTC_NORMAL = 0,
    TOGGLE_OC1,
    CLEAR_OC1,
    SET_OC1
} TIMER1_CTC_MODE_SELECT;



void TIMER1_OF_init(CLOCK_SELECT clock);

void TIMER1_CTC_init(TIMER1_CTC_MODE_SELECT ctc_OC1A, TIMER1_CTC_MODE_SELECT ctc_OC1B,
                     CLOCK_SELECT clock, u16 compValueA, u16 compValueB);

void TIMER1_FAST_PWM_init(FAST_PWM_MODE_SELECT mode_A, FAST_PWM_MODE_SELECT mode_B,
                          CLOCK_SELECT clock, u16 top);

void TIMER1_FAST_PWM_set_dutyCycle_A(u16 dutyCycle);

void TIMER1_FAST_PWM_set_dutyCycle_B(u16 dutyCycle);

void TIMER1_OF_set_cb(void (*cb)(void));
void TIMER1_CTC_set_cb_A(void (*cb)(void));
void TIMER1_CTC_set_cb_B(void (*cb)(void));

#endif /* MCAL_TIMER_DRIVER_TIMER1_INTERFACE_H_ */
