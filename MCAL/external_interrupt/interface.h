/*
 *      Author: shahd moamed
 *      Created on: sept 1, 2025
 *      File name: EXT_interrupt.h
 *      Description:
 *         Function declaration to handle AVR ATmega32 Interrupts
 */

#ifndef MCAL_EXT_INTERRUPT_DRIVER_INCLUDE_EXT_INTERRUPT_H_
#define MCAL_EXT_INTERRUPT_DRIVER_INCLUDE_EXT_INTERRUPT_H_

#include "../../LIBRARY/macros.h"
#include "../../LIBRARY/standard_types.h"

/* External interrupt handler definition */
#define EXT_INTERRUPT(INT,STATE,CONTROL) EXT_##INT##_init(STATE,CONTROL)

#define ALLOW_NESTING_INTERRUPT FALSE

/* Interrupt state data type declaration */
typedef enum{
 LOW_LEVEL, ANY_CHANGE, FALLING_EDGE, RISING_EDGE
}INT_CONTROL;

/*  */


/* Enable/Disable GIE bit in SREG register */
void EXT_interrupt_GIE_state(u8 state);

/* initialize interrupt 0 */
void EXT_INT0_init(u8 state, INT_CONTROL ctrl);

/* initialize interrupt 1 */
void EXT_INT1_init(u8 state, INT_CONTROL ctrl);

/* initialize interrupt 2 */
void EXT_INT2_init(u8 state, INT_CONTROL ctrl);

/* function set callback function to call in interrup0 ISR  */
void EXT_int0_set_cb( void (*cb)(void) );

/* function set callback function to call in interrup1 ISR  */
void EXT_int1_set_cb( void (*cb)(void) );

/* function set callback function to call in interrup2 ISR  */
void EXT_int2_set_cb( void (*cb)(void) );

#endif /* MCAL_EXT_INTERRUPT_DRIVER_INCLUDE_EXT_INTERRUPT_H_ */
