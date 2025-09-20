/*
 * interface.h
 *
 *  Created on: Sep 2, 2025
 *      Author: shahd mohamed
 */

#ifndef MCAL_ADC_INTERFACE_H_
#define MCAL_ADC_INTERFACE_H_
#include "private.h"
#include "../../LIBRARY/standard_types.h"

// ---------------- Vref Options ----------------
#define VREF_AVCC   0   // AVCC with external capacitor at AREF pin (5V)
#define VREF_256    1   // Internal 2.56V reference with external capacitor

// ---------------- Prescaler Options ----------------
#define DIV_2    2
#define DIV_4    4
#define DIV_8    8
#define DIV_16   16
#define DIV_32   32
#define DIV_64   64
#define DIV_128  128

#define interrupt DISABLE

typedef enum{
 DISABLE, ENABLE
}INT_STATE;

void ADC_INIT(u8 Vref,u8 Division_factor);
u16 ADC_readChannel(u8 channel);



#endif /* MCAL_ADC_INTERFACE_H_ */
