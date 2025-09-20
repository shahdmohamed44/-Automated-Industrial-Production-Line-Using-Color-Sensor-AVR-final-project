/*
 *      Author:ASKER
 *      Created on: Aug 31, 2025
 *      File name: motorDriver.c
 *      Description:
 *      		L298/L293 motor driver implementation
 */
#include "../../MCAL/DIO_driver/DIO_interface.h"
#include "../../LIBRARY/standard_types.h"
#include "../../LIBRARY/macros.h"

#include "dc_motor-1.h"




/* Generalize function to initialize motor pins */
 void MOTOR_DRIVER_init(const MotorDriver_t* motor){

	 DIO_voidSetPinDir(motor -> portNum, motor -> IN1_pinNum, PIN_OUTPUT);


	/* ensure that motor is off at start */
	 DIO_voidSetPinValue(motor -> portNum, motor -> IN1_pinNum, LOW);

	 TIMER1_FAST_PWM_init(NON_INVERTING_MODE,NON_INVERTING_MODE,PRESCALER_64,TIMER1_TOP);
	 TIMER1_FAST_PWM_set_dutyCycle_A(0);
}



/* Initialize motor pins in case timer 1 */
//void MOTOR_DRIVER_init1(const MotorDriver_t* motor1, const MotorDriver_t* motor2){
//
//	MOTOR_DRIVER_init(motor1);
//	MOTOR_DRIVER_init(motor2);
//
//	TIMER1_FAST_PWM_init(NON_INVERTING_MODE, NON_INVERTING_MODE, PRESCALER_64, TIMER1_TOP);
//	TIMER1_FAST_PWM_set_dutyCycle_A(0);
//	TIMER1_FAST_PWM_set_dutyCycle_B(0);
//}

/* set motor speed*/
void MOTOR_DRIVER_setSpeed(const MotorDriver_t* motor, MOTOR_STATE state,u8 speed){
    if(speed>100)speed=100;
	u16 dutyCycle = 0;

		dutyCycle =((u16) ((u32)speed*TIMER1_TOP) / 100);

        TIMER1_FAST_PWM_set_dutyCycle_A(dutyCycle);



	switch(state){
	case CW:
		DIO_voidSetPinValue(motor -> portNum, motor -> IN1_pinNum, HIGH);

		break;


	case STOP:
		DIO_voidSetPinValue(motor -> portNum, motor -> IN1_pinNum, LOW);

		break;

	}
}
