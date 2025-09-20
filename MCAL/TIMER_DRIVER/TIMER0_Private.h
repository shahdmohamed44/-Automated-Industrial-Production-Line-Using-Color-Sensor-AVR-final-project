/*
 * TIMER_Private.h
 *
 *  Created on: Sep 4, 2025
 *      Author: SAGDA
 */

#ifndef MCAL_TIMER_DRIVER_TIMER_PRIVATE_H_
#define MCAL_TIMER_DRIVER_TIMER_PRIVATE_H_

#include "../../LIBRARY/standard_types.h"

#define TCCR0   *(( volatile u8 *) 0x53)
#define TCNT0   *(( volatile u8 *) 0x52)
#define TIMSK   *(( volatile u8 *) 0x59)
#define TIFR    *(( volatile u8 *) 0x58)
#define OCR0    *(( volatile u8 *) 0x5C)

//TIMSK REG
#define OCIE0 1
#define TOIE0 0

//TIFR REG
#define OCF0 1
#define TOV0 0

//TCCR0 REG
#define FOC0  7
#define WGM00 6
#define COM01 5
#define COM00 4
#define WGM01 3
#define CS02  2
#define CS01  1
#define CS00  0


#endif /* MCAL_TIMER_DRIVER_TIMER_PRIVATE_H_ */
