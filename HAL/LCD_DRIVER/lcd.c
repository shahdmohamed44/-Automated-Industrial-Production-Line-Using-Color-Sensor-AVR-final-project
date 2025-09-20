/*
 * lcd.c
 *
 *  Created on: Aug 27, 2025
 *      Author: shahd mohamed
 */
#include <util/delay.h>
#include "lcd.h"
#include "../../MCAL/DIO_driver/DIO_interface.h"
void LCD_sendCommand(u8 command){
	DIO_voidSetPinValue(PORTC_ID,PIN4_ID,PIN_LOW);
	_delay_ms(1);

	DIO_voidSetPinValue(PORTC_ID, PIN5_ID,PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPortValue(LCD_DATA_PORT,command);
	_delay_ms(1);

	DIO_voidSetPinValue(PORTC_ID, PIN5_ID,PIN_LOW);
}
 void LCD_init(void){
	 DIO_voidSetPinDir(PORTC_ID,PIN4_ID,PIN_OUTPUT);
	 DIO_voidSetPinDir(PORTC_ID, PIN5_ID,PIN_OUTPUT);
	_delay_ms(20);
	DIO_vSetPortDir(LCD_DATA_PORT,PORT_OUTPUT);
	LCD_sendCommand(LCD_TWO_LINES_8_BITS_MODE);
	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR_COMMAND);


 }
void_LCD_displatchar(u8 character){
	DIO_voidSetPinValue(PORTC_ID,PIN4_ID,PIN_HIGH);
	_delay_ms(1);

	DIO_voidSetPinValue(PORTC_ID, PIN5_ID,PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPortValue(LCD_DATA_PORT,character);
		_delay_ms(1);
	DIO_voidSetPinValue(PORTC_ID, PIN5_ID,PIN_LOW);

}
void LCD_moveCursor(u8 row, u8 col){
	u8 lcdMemory;
	 switch(row){
	 case 0:
		 lcdMemory =col;
		 break;
	 case 1:
		 lcdMemory = col + 0x40;
		 break;
	 }
	 LCD_sendCommand(lcdMemory | LCD_SET_CURSOR_LOCATION);
}

void LCD_displayString(const u8 *str){
	while(*str != '\0'){
		void_LCD_displatchar(*str);
	        str++;
	    }
}
void LCD_clearScreen(void) {
    LCD_sendCommand(LCD_CLEAR_COMMAND);
    _delay_ms(2);
}


