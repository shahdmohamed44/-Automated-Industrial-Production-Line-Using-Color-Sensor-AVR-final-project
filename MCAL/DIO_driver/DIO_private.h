/*
 * DIO_private.h
 *
 *  Created on: Aug 25, 2025
 *      Author: 11
 */

#ifndef MCAL_DIO_DRIVER_DIO_PRIVATE_H_
#define MCAL_DIO_DRIVER_DIO_PRIVATE_H_

#include "../../LIBRARY/standard_types.h"

#define DDRA *((volatile u8*) 0x3A)
#define DDRB *((volatile u8*) 0x37)
#define DDRC *((volatile u8*) 0x34)
#define DDRD *((volatile u8*) 0x31)

#define PORTA *((volatile u8*) 0x3B)
#define PORTB *((volatile u8*) 0x38)
#define PORTC *((volatile u8*) 0x35)
#define PORTD *((volatile u8*) 0x32)

#define PINA *((volatile u8*) 0x39)
#define PINB *((volatile u8*) 0x36)
#define PINC *((volatile u8*) 0x33)
#define PIND *((volatile u8*) 0x30)


#endif /* MCAL_DIO_DRIVER_DIO_PRIVATE_H_ */
