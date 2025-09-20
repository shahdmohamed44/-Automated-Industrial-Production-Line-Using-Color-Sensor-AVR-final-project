/*
 * Keypad.h
 *
 *  Created on: Aug 28, 2025
 *      Author: shahd mohamed
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "../../LIBRARY/standard_types.h"

#define KEYPAD_ROW_NUM 4
#define KEYPAD_COL_NUM 4

#define KEYPAD_ROW_PORT_ID PORTA_ID
#define KEYPAD_FIRST_ROW_PIN_ID PIN0_ID

#define KEYPAD_COL_PORT_ID PORTA_ID
#define KEYPAD_FIRST_COL_PIN_ID PIN4_ID

#define KEYPAD_BUTTON_PRESSED LOW
#define KEYPAD_BUTTON_REALEASED HIGH

u8 KEYPAD_getPressedKey(void);


#endif /* KEYPAD_H_ */


