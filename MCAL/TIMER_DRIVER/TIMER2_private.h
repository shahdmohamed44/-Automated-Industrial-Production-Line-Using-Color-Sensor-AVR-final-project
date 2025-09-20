/*
 * TIMER2_private.h
 *
 *  Created on: Sep 13, 2025
 *      Author: SAGDA
 */

#ifndef MCAL_TIMER_DRIVER_TIMER2_PRIVATE_H_
#define MCAL_TIMER_DRIVER_TIMER2_PRIVATE_H_

#include "../../LIBRARY/standard_types.h"

#define TCCR2   *(( volatile u8*) 0x45)
#define TCNT2   *(( volatile u8*) 0x44)
#define TIMSK   *(( volatile u8*) 0x59)
#define TIFR    *(( volatile u8*) 0x58)
#define OCR2    *(( volatile u8*) 0x43)
#define ASSR    *(( volatile u8*) 0x42)

//TIMSK REG
#define OCIE2 7
#define TOIE2 6

//TIFR REG
#define OCF2 7
#define TOV2 6

//ASSR REG
#define AS2    3
#define TCN2UB 2
#define OCR2UB 1
#define TCR2UB 0

//TCCR2 REG
#define FOC2  7
#define WGM20 6
#define COM21 5
#define COM20 4
#define WGM21 3
#define CS22  2
#define CS21  1
#define CS20  0

#endif /* MCAL_TIMER_DRIVER_TIMER2_PRIVATE_H_ */
