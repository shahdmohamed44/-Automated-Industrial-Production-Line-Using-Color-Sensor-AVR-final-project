/*
 * DIO_program.c
 *
 *  Created on: Aug 25, 2025
 *      Author: SAGDA
 */

#include "../../LIBRARY/standard_types.h"
#include "DIO_interface.h"
#include "DIO_private.h"
#include "../../LIBRARY/macros.h"
//done
void DIO_vSetPortDir(u8 Copy_u8PortNum,u8 Copy_u8PortDirection){

	if (Copy_u8PortNum>=4){
		return;
	}
	else {
		switch (Copy_u8PortNum) {

		case PORTA_ID : DDRA = Copy_u8PortDirection; break;
		case PORTB_ID : DDRB = Copy_u8PortDirection; break;
		case PORTC_ID : DDRC = Copy_u8PortDirection; break;
		case PORTD_ID : DDRD = Copy_u8PortDirection; break;

		}
	}
}

//done
void DIO_voidSetPinDir(u8 Copy_u8PortNum,u8 Copy_u8PinNum,u8 Copy_u8PinDirection){

	if ( (Copy_u8PortNum>=4) | (Copy_u8PinNum>=8)){
		return;
	}
	else {
		if (Copy_u8PinDirection == PIN_INPUT) {
			switch (Copy_u8PortNum) {

			case PORTA_ID : CLEAR_BIT(DDRA,Copy_u8PinNum); break;
			case PORTB_ID : CLEAR_BIT(DDRB,Copy_u8PinNum); break;
			case PORTC_ID : CLEAR_BIT(DDRC,Copy_u8PinNum); break;
			case PORTD_ID : CLEAR_BIT(DDRD,Copy_u8PinNum); break;

			}

		}
		else {
			switch (Copy_u8PortNum) {

			case PORTA_ID : SET_BIT(DDRA,Copy_u8PinNum); break;
			case PORTB_ID : SET_BIT(DDRB,Copy_u8PinNum); break;
			case PORTC_ID : SET_BIT(DDRC,Copy_u8PinNum); break;
			case PORTD_ID : SET_BIT(DDRD,Copy_u8PinNum); break;
			}
		}
	}
}



//done
void DIO_voidSetPortValue(u8 Copy_u8PortNum,u8 Copy_u8PortValue){

	if (Copy_u8PortNum>=4){
		return;
	}
	else {
		switch (Copy_u8PortNum) {

		case PORTA_ID : PORTA = Copy_u8PortValue; break;
		case PORTB_ID : PORTB = Copy_u8PortValue; break;
		case PORTC_ID : PORTC = Copy_u8PortValue; break;
		case PORTD_ID : PORTD = Copy_u8PortValue; break;

		}
	}
}

//done
void DIO_voidSetPinValue(u8 Copy_u8PortNum,u8 Copy_u8PinNum,u8 Copy_u8PinValue){

	if ((Copy_u8PortNum>=4) | (Copy_u8PinNum>=8)){
		return;
	}
	else {
		if (Copy_u8PinValue ==1){

			switch (Copy_u8PortNum) {

			case PORTA_ID : SET_BIT(PORTA,Copy_u8PinNum); break;
			case PORTB_ID : SET_BIT(PORTB,Copy_u8PinNum); break;
			case PORTC_ID : SET_BIT(PORTC,Copy_u8PinNum); break;
			case PORTD_ID : SET_BIT(PORTD,Copy_u8PinNum); break;
			}
		}
		else {
			switch (Copy_u8PortNum) {

			case PORTA_ID : CLEAR_BIT(PORTA,Copy_u8PinNum); break;
			case PORTB_ID : CLEAR_BIT(PORTB,Copy_u8PinNum); break;
			case PORTC_ID : CLEAR_BIT(PORTC,Copy_u8PinNum); break;
			case PORTD_ID : CLEAR_BIT(PORTD,Copy_u8PinNum); break;

			}
		}
	}
}

//done
void DIO_voidTogglePin(u8 Copy_u8PortNum,u8 Copy_u8PinNum){

	if ((Copy_u8PortNum>=4) | (Copy_u8PinNum>=8)){
		return ;
	}
	else {
		switch (Copy_u8PortNum) {

		case PORTA_ID : TOGGLE_BIT(PORTA,Copy_u8PinNum); break;
		case PORTB_ID : TOGGLE_BIT(PORTB,Copy_u8PinNum); break;
		case PORTC_ID : TOGGLE_BIT(PORTC,Copy_u8PinNum); break;
		case PORTD_ID : TOGGLE_BIT(PORTD,Copy_u8PinNum); break;

		}
	}
}


//done
u8 DIO_readPin(u8 Copy_u8PortNum,u8 Copy_u8PinNum){

	if ((Copy_u8PortNum>=4) | (Copy_u8PinNum>=8)){
		return 0 ;
	}
	else {

		switch (Copy_u8PortNum) {

		case PORTA_ID : return  BIT_IS_SET(PORTA,Copy_u8PinNum); break;
		case PORTB_ID : return  BIT_IS_SET(PORTB,Copy_u8PinNum); break;
		case PORTC_ID : return  BIT_IS_SET(PORTC,Copy_u8PinNum); break;
		case PORTD_ID : return  BIT_IS_SET(PORTD,Copy_u8PinNum); break;

		}
	}
}


//done
u8 DIO_readPort(u8 Copy_u8PortNum){

	if (Copy_u8PortNum>=4){
		return 0 ;
	}
	else {
		switch (Copy_u8PortNum) {

		case PORTA_ID : return PORTA; break;
		case PORTB_ID : return PORTB; break;
		case PORTC_ID : return PORTC; break;
		case PORTD_ID : return PORTD; break;
		}
	}
}







