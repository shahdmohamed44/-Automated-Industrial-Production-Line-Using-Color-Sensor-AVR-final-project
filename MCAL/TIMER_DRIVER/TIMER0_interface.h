/*
 * TIMER_interface.h
 *
 *  Created on: Sep 4, 2025
 *      Author: SAGDA
 */

#ifndef MCAL_TIMER_DRIVER_TIMER_INTERFACE_H_
#define MCAL_TIMER_DRIVER_TIMER_INTERFACE_H_

#include "TIMER_config.h"
#include "../../LIBRARY/standard_types.h"

// /////// TIMER_0 DATA ////////////

#define TIMER0_PRELOAD 0
#define TIMER0_OF_INTERRUPT_ENABLE True
#define TIMER0_CTC_INTERRUPT_ENABLE True
#define TIMER0_FPWM_INTERRUPT_ENABLE True
#define TIMER0_PCPWM_INTERRUPT_ENABLE True




void TIMER0_EXT_COUNT_init(void);

void TIMER0_OF_init(CLOCK_SELECT clock);

void TIMER0_CTC_init(TIMER0_CTC_MODE_SELECT mode, CLOCK_SELECT clock, u8 compValue);

void TIMER0_FAST_PWM_init(FAST_PWM_MODE_SELECT mode, CLOCK_SELECT clock);

void TIMER0_FAST_PWM_set_dutyCycle(u8 dutyCycle);

void TIMER0_PhaseCorrect_PWM_init(PHASE_CORRECT_PWM_MODE_SELECT mode, CLOCK_SELECT clock);
void TIMER0_PHASECORRECT_PWM_set_dutyCycle(u8 dutyCycle);


void TIMER0_OF_set_cb(void (*cb)(void));
void TIMER0_CTC_set_cb(void (*cb)(void));
void TIMER0_FPWM_set_cb(void (*cb)(void));
void TIMER0_PCPWM_set_cb(void (*cb)(void));


// /////// TIMER_1 DATA ////////////

#endif /* MCAL_TIMER_DRIVER_TIMER_INTERFACE_H_ */
