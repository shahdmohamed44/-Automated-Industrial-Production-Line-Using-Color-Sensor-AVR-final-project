/*
 *      Author: ASKER
 *      Created on: Aug 31, 2025
 *      File name: motorDriver.h
 *      Description:
 *      		L298/L293 motor driver declaration
 */


#ifndef HAL_DC_MOTOR_DRIVER_INCLUDE_MOTORDRIVER_H_
#define HAL_DC_MOTOR_DRIVER_INCLUDE_MOTORDRIVER_H_
#include "../../MCAL/DIO_driver/DIO_interface.h"
#include "../../LIBRARY/standard_types.h"
#include "../../LIBRARY/macros.h"
#include "../../MCAL/TIMER_DRIVER/TIMER1_interface.h"

#define sTop 0
#define RUNNING 1
#define Pause 2


#define TIMER1_TOP 2499 /* 2499 -> in case 8mhz and pre-scaler = 64 */

/* timer used declaration */
//typedef enum{
//	 TIMER1A, TIMER1B
//}TIMER_NUM;

/* timer used declaration */
typedef enum{
	CW, STOP
}MOTOR_STATE;

/* motor driver data type declaration */
typedef struct{
	u8 portNum;
	u8 IN1_pinNum;
	CLOCK_SELECT motor_prescaler;
	//TIMER_NUM timer;
}MotorDriver_t;

void MOTOR_DRIVER_init(const MotorDriver_t* motor);

/* Initialize motor pins in case timer 1 */
//void MOTOR_DRIVER_init1(const MotorDriver_t* motor1, const MotorDriver_t* motor2);

/* motors take speed as percentage from 0% -> 100% */
/* set motor speed */
void MOTOR_DRIVER_setSpeed(const MotorDriver_t* motor, MOTOR_STATE state,u8 speed);


#endif /* HAL_DC_MOTOR_DRIVER_INCLUDE_MOTORDRIVER_H_ */
