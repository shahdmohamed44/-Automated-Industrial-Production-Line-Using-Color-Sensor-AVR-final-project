/*
 * private.h
 *
 *  Created on: Sep 1, 2025
 *      Author: shahd mohamed
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_PRIVATE_H_
#define MCAL_EXTERNAL_INTERRUPT_PRIVATE_H_

#include "../../LIBRARY/standard_types.h"

#define SREG *((volatile u8*) 0x5F) // for i bit
#define GICR *((volatile u8*) 0x5B)
#define GIFR *((volatile u8* )0x5A)
#define MCUCR *((volatile u8*)0x55) // acive rising,falling of int0,int1
#define MCUCSR *((volatile u8*)0x54) // acive rising,falling int2
#define INT0 6
#define INT1 7
#define INT2 5
#define ISC2 6
#define ISC11 3
#define ISC10 2
#define ISC01 1
#define ISC00 0
#define IBIT 7


#endif /* MCAL_EXTERNAL_INTERRUPT_PRIVATE_H_ */
