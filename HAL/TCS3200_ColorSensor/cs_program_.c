/*
 * CS_program.c
 *
 *  Created on: Sep 13, 2025
 *      Author: SAGDA
 */
#include "avr/io.h"
#include "CS_interface.h"
#include "../../LIBRARY/macros.h"
#include "../../MCAL/DIO_driver/DIO_interface.h"
#include "../../LIBRARY/standard_types.h"


#include <util/delay.h>
//PORTB pins 0:4 are pinoutput direction

volatile u8 msCounter = 0;
volatile u8 colorStage = 0;
volatile u16 R=0, G=0, B=0;
volatile u8 newRGBReady = 0;
volatile u16 TIME_SORT=0;


void CS_INIT(void){

	CLEAR_BIT(PORTB,PIN5_ID); // OE
	TIMER0_EXT_COUNT_init();

}


void FreqScaling (SCALING scale){

	switch (scale) {

	case POWER_DOWN:
		CLEAR_BIT(PORTB,PIN4_ID); //S0
		CLEAR_BIT(PORTB,PIN3_ID); //S1
		break;

	case TWO_PERCENT:
		CLEAR_BIT(PORTB,PIN4_ID); //S0
		SET_BIT(PORTB,PIN3_ID); //S1
		break;

	case TWENTY_PERCENT :
		SET_BIT(PORTB,PIN4_ID); //S0
		CLEAR_BIT(PORTB,PIN3_ID); //S1
		break;

	case HUNDRED_PERCENT :
		SET_BIT(PORTB,PIN4_ID); //S0
		SET_BIT(PORTB,PIN3_ID); //S1
		break;
	}

}


void ColorSelect (SENSED_COLOR color){

	switch (color){

	case RED :
		CLEAR_BIT(PORTB,PIN2_ID); //S2
		CLEAR_BIT(PORTB,PIN1_ID); //S3
		break;

	case BLUE :
		CLEAR_BIT(PORTB,PIN2_ID); //S2
		SET_BIT(PORTB,PIN1_ID); //S3
		break;

	case GREEN :
		SET_BIT(PORTB,PIN2_ID); //S2
		SET_BIT(PORTB,PIN1_ID); //S3
		break;

	case CLEAR :
		SET_BIT(PORTB,PIN2_ID); //S2
		CLEAR_BIT(PORTB,PIN1_ID); //S3
		break;

	}

}

void ColorSensor_Timer2Callback(void) {
    msCounter++;
    if(msCounter >= 50) {
        u16 count = TCNT0;
        TCNT0 = 0;
        msCounter = 0;

        if(colorStage == 0) {
        	R = count;
        	ColorSelect(G);
        	colorStage = 1;
        	_delay_ms(5);
        }
        else if(colorStage == 1) {
        	G = count;
        	ColorSelect(BLUE);
        	colorStage = 2;
        	_delay_ms(5);
        }
        else if(colorStage == 2) {
        	B = count;
        	ColorSelect(RED);
        	colorStage = 0;
        	_delay_ms(5);
        	newRGBReady = 1;
        	TIME_SORT+=1;
        }
    }
}

u8 SensingObject(void){

	 if(newRGBReady) {
	        newRGBReady = 0;
	        u32 sum = (u32)(R+G+B);
	        if(sum == 0) return 0xFF;

	        float Rn = (float)(R/sum);
	        float Gn = (float)(G/sum);
	        float Bn = (float)(B/sum);

	        if(Rn > Gn && Rn > Bn) return RED;
	        if(Gn > Rn && Gn > Bn) return GREEN;
	        if(Bn > Rn && Bn > Gn) return BLUE;
	        return 0xFF;
	    }
	    return 0xFF;

}

//Use a presence sensor (IR beam, photodiode)
//
//Place one extra sensor to detect when an object actually arrives under the TCS3200.
//
//Start the color sensing cycle only when an object is present.
//
//This avoids “empty” cycles.
