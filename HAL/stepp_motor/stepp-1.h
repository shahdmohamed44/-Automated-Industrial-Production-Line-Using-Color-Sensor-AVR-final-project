///*
// * stepp.h
// *
// *  Created on: Sep 14, 2025
// *      Author: ASKER
// */
//
//
//
//#ifndef HAL_STEPPER_MOTOR_DRIVER_INCLUDE_STEPPER_H_
//#define HAL_STEPPER_MOTOR_DRIVER_INCLUDE_STEPPER_H_
//
//#include "../../LIB/std_types.h"
//
//#define MAX_STEPS_PER_REV 200
//
//
///* stepper motor state declaration */
//typedef enum{
//	STEPPER_CW, STEPPER_CCW, STEPPER_STOP
//}STEPPER_STATE;
//
///* stepper motor mode declaration */
//typedef enum{
//	FULL_STEP = 4, HALF_STEP = 8
//}STEPPER_MODE;
//
///* stepper motor data type declaration */
//typedef struct{
//	u8 portNum;
//	u8 mask;
//	u16 delay; /* best practice to be 100 mills */
//	STEPPER_MODE mode;
//}Stepper_t;
//
///* initialize stepper motor pins */
//void STEPPER_init(const Stepper_t* stepper);
//
///* stepper motor start action in steps  */
//void STEPPER_move_steps(const Stepper_t* stepper, STEPPER_STATE state, u16 steps);
//
//#endif /* HAL_STEPPER_MOTOR_DRIVER_INCLUDE_STEPPER_H_ */
