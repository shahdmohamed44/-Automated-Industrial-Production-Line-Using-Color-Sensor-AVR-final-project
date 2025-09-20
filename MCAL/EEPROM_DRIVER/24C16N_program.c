/*
 * 24C16N_program.c
 *
 *  Created on: Sep 15, 2025
 *      Author: SAGDA
 */


#include "../../LIBRARY/macros.h"
#include "../TWI/TWI.h"
#include "24C16N_interface.h"
#include <util/delay.h>


/* function write one 1 byte in specified address in EEPROM using TWI */
void EEPROM_writeByte(u16 u16addr,u8 u8data){
	u8 ctrl = EEPROM_ADDR | ((u16addr >> 8) & 0x07); // include A10..A8
	u8 lowAddr = u16addr & 0xFF;

	TWI_init(64);
	TWI_start();
	TWI_writeByte(ctrl << 1);
	TWI_writeByte(lowAddr);
	TWI_writeByte(u8data);
	TWI_stop();
	_delay_ms(5); // wait write cycle

}


/* function read one 1 byte in specified address in EEPROM using TWI */
u8 EEPROM_readByte(u16 u16addr,u8 *u8data){

	u8 ctrl = EEPROM_ADDR | ((u16addr >> 8) & 0x07);
	u8 lowAddr = u16addr & 0xFF;

	TWI_init(64);
	TWI_Start();
	TWI_writeByte(ctrl << 1); //write mode
	TWI_writeByte(lowAddr);

	TWI_start();
	TWI_writeByte((ctrl << 1) | 1); // Read mode
	*u8data = TWI_readByteWithNACK();
	TWI_stop();

	return *u8data;

}

void EEPROM_WriteString(u16 u16addr,  u8 *str){
	while(*str != '\0'){
		EEPROM_writeByte(u16addr,*str);
		str++;
		u16addr++;
	}
	EEPROM_writeByte(u16addr,'#');
}


void EEPROM_ReadString(u16 u16addr,  u8 *str){
	EEPROM_readByte(u16addr,str);
	while(*str != '#'){
		str++;
		u16addr++;
		EEPROM_readByte(u16addr,*str);
	}
	*str = '\0';

}

/*
 project main {


 //  log error occurrences into EEPROM for performance analysis.
	 *
  to shahd , may send the number of errors done and their type according to a string defines each one when occurred
  (the function of log is used directly the line after an error occurred )
	 *
	 *

 }
	 */











	//void UART_sendString(const u8 *str){
	//	while(*str != "/0"){
	//		UART_sendByte(*str);
	//		        str++;
	//
	//		    }
	//	UART_sendByte("#");
	//
	//}
	//
	//
	//void UART_receiveString(u8 *str){
	//
	//	UART_receiveByte(str);
	//	while(*str != '#'){
	//		str++;
	//	    UART_receiveByte(*str);
	//	}
	//	*str = '\0';
	//}
