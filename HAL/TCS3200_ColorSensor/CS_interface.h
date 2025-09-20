/*
 * CS_interface.h
 *
 *  Created on: Sep 13, 2025
 *      Author: SAGDA
 */

#ifndef HAL__TCS3200_COLORSENSOR_CS_INTERFACE_H_
#define HAL__TCS3200_COLORSENSOR_CS_INTERFACE_H_

#include "../../LIBRARY/standard_types.h"
#include "../../MCAL/TIMER_DRIVER/TIMER0_Private.h"
#include "../../MCAL/TIMER_DRIVER/TIMER0_interface.h"
#include "../../MCAL/TIMER_DRIVER/TIMER2_interface.h"

extern volatile u8 msCounter;
extern volatile u8 colorStage;
extern volatile u16 R, G, B;
extern volatile u8 newRGBReady;
extern volatile u16 TIME_SORT;

typedef enum {
	POWER_DOWN,TWO_PERCENT,TWENTY_PERCENT,HUNDRED_PERCENT
}SCALING;


typedef enum {
	RED, GREEN, BLUE, CLEAR
}SENSED_COLOR;

void ColorSensor_Timer2Callback(void) ;



void CS_INIT(void); // in normal i must take an argument the port and pin of OE

void FreqScaling (SCALING scale); //in normal i must take an argument the port and pin of S0,S1

void ColorSelect (SENSED_COLOR color); //in normal i must take an argument the port and pin of S2 ,S3

u8 SensingObject(void);

#endif /* HAL__TCS3200_COLORSENSOR_CS_INTERFACE_H_ */
