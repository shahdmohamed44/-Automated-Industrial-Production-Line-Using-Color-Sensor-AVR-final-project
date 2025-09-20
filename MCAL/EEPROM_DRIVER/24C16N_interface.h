/*
 * 24C16N_interface.h
 *
 *  Created on: Sep 15, 2025
 *      Author: SAGDA
 */

#ifndef MCAL_EEPROM_DRIVER_24C16N_INTERFACE_H_
#define MCAL_EEPROM_DRIVER_24C16N_INTERFACE_H_

/* user defined data types library*/
#include "../../LIBRARY/standard_types.h"

/* constant definitions */
#define ERROR   0
#define SUCCESS 1

#define EEPROM_ADDR 0x50 // 1010XXXX

/* Function Prototypes */

/* function write one 1 byte in specified address in EEPROM using TWI */
void EEPROM_writeByte(u16 u16addr,u8 u8data);


/* function read one 1 byte in specified address in EEPROM using TWI */
u8 EEPROM_readByte(u16 u16addr,u8 *u8data);


void EEPROM_WriteString(u16 u16addr,  u8 *str);

void EEPROM_ReadString(u16 u16addr,  u8 *str);

#endif /* MCAL_EEPROM_DRIVER_24C16N_INTERFACE_H_ */
