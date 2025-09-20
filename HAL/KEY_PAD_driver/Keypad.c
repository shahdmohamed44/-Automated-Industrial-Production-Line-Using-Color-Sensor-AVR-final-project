/*
 * Keypad.c
 *
 *  Created on: Aug 28, 2025
 *      Author: shahd mohamed
 */
#include "Keypad.h"
#include "../../MCAL/DIO_driver/DIO_interface.h"
#include <util/delay.h>
#include "../../LIBRARY/standard_types.h"


u8 row,col;

static u8 buttons[4][4] = {
		{1,2,3,'A'},
		{4,5,6,'B'},
		{7,8,9,'C'},
		{'*',0,'#','D'}
};
u8 KEYPAD_getPressedKey(void){
	DIO_voidSetPinDir(PORTA_ID,PIN0_ID,PIN_INPUT);
	DIO_voidSetPinDir(PORTA_ID,PIN0_ID+1,PIN_INPUT);
	DIO_voidSetPinDir(PORTA_ID,PIN0_ID+2,PIN_INPUT);
	DIO_voidSetPinDir(PORTA_ID,PIN0_ID+3,PIN_INPUT);

	DIO_voidSetPinDir(PORTA_ID,PIN0_ID+4,PIN_INPUT);
	DIO_voidSetPinDir(PORTA_ID,PIN0_ID+5,PIN_INPUT);
	DIO_voidSetPinDir(PORTA_ID,PIN0_ID+6,PIN_INPUT);
	DIO_voidSetPinDir(PORTA_ID,PIN0_ID+7,PIN_INPUT);


	DIO_voidSetPinValue(PORTA_ID,PIN0_ID ,PIN_OUTPUT);
	DIO_voidSetPinValue(PORTA_ID,PIN0_ID+1 ,PIN_OUTPUT);
	DIO_voidSetPinValue(PORTA_ID,PIN0_ID+2 ,PIN_OUTPUT);
	DIO_voidSetPinValue(PORTA_ID,PIN0_ID+3 ,PIN_OUTPUT);
	DIO_voidSetPinValue(PORTA_ID,PIN0_ID+4 ,PIN_OUTPUT);
	DIO_voidSetPinValue(PORTA_ID,PIN0_ID+5 ,PIN_OUTPUT);
	DIO_voidSetPinValue(PORTA_ID,PIN0_ID+6 ,PIN_OUTPUT);
	DIO_voidSetPinValue(PORTA_ID,PIN0_ID+7 ,PIN_OUTPUT);

	while(1){
		for(row = 0; row < PORTA_ID; row++){
			DIO_voidSetPinDir(PORTA_ID,PIN0_ID + row,PIN_OUTPUT);
			DIO_voidSetPinValue(PORTA_ID,PIN0_ID + row,PIN_OUTPUT);
			for(col= 0; col < PORTA_ID; col++){
				if(DIO_readPin(PORTA_ID,PIN4_ID + col)== LOW){
					return buttons[row][col];
				}
			}
			DIO_voidSetPinDir(PORTA_ID,PIN0_ID + row,PIN_INPUT);
			_delay_ms(10);
		}
	}

}





