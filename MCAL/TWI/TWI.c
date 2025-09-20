/*
 * TWI.c
 *  Created on: Sep 11, 2025
 *      Author: shahd mohamed
 */


#include "TWI.h"
#include "../../LIBRARY/macros.h"
#include "../../LIBRARY/standard_types.h"
#include "private.h"

void TWI_init(u8 prescaller){
	SET_BIT(TWCR,TWEN);

	//ADDRESS
	TWAR = 0X02; // CHANGE ACCORDING TO SLAVE ADRESS

	//SPEED
	TWBR = 0X02;

	switch(prescaller){
	case 1:
		CLEAR_BIT(TWSR,TWPS1);
		CLEAR_BIT(TWSR,TWPS0);
		break;
	case 4:
		CLEAR_BIT(TWSR,TWPS1);
		SET_BIT(TWSR,TWPS0);
		break;

	case 16:
		SET_BIT(TWSR,TWPS1);
		CLEAR_BIT(TWSR,TWPS0);
		break;

	case 64:
		SET_BIT(TWSR,TWPS1);
		SET_BIT(TWSR,TWPS0);
		break;

	}


}

void TWI_start(void){
	SET_BIT(TWCR,TWSTA);
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);

	while (BIT_IS_CLEAR(TWCR,TWINT));
}


void TWI_stop(void){
	SET_BIT(TWCR,TWEN);
	SET_BIT(TWCR,TWSTO);
	SET_BIT(TWCR,TWINT);

}

void TWI_writeByte(u8 data){
	TWDR = data;
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	while (BIT_IS_CLEAR(TWCR,TWINT)){

	}

}
u8 TWI_readByteWithACK(void){
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	SET_BIT(TWCR,TWEA);

	while (BIT_IS_CLEAR(TWCR,TWINT));

	return TWDR;
}

u8 TWI_readByteWithNACK(void){
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);

	while (BIT_IS_CLEAR(TWCR,TWINT));

	return TWDR;
}


u8 TWI_getStatus(void){
    u8 status = TWSR & 0xF8;
    return status;

}








