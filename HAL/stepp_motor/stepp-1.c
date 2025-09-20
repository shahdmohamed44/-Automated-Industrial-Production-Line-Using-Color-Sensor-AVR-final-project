///*
// * stepp.c
// *
// *  Created on: Sep 14, 2025
// *      Author: ASKER
// */
//
//
//#include "../../MCAL/DIO_driver/DIO_interface.h"
//#include "../../LIBRARY/standard_types.h"
//#include "../../LIBRARY/macros.h"
//#include "../../MCAL/TIMER_DRIVER/TIMER0_Private.h"
//#include "../../MCAL/TIMER_DRIVER/TIMER0_interface.h"
//#include "../../MCAL/TIMER_DRIVER/TIMER1_interface.h"
//#include "../../MCAL/TIMER_DRIVER/TIMER2_interface.h"
//#include "stepp-1.h"
//#include <util/delay.h>
//
//static u8 STEPPER_fullStepSequence[4] = {12, 6, 3, 9};
//static u8 STEPPER_halfStepSequence[8] = {12, 4, 6, 2, 3, 1, 9, 8};
//
///* initialize stepper motor pins */
//void STEPPER_init(const Stepper_t* stepper){
//	GPIO_setupPortDirectionMasked(stepper -> portNum, stepper -> mask, stepper -> mask);
//	/* ensure stepper is stopped */
//
//		GPIO_writePortMasked(stepper -> portNum, stepper -> mask, stepper -> mask);
//
//}
//
///* stepper motor start action  */
//void STEPPER_move_steps(const Stepper_t* stepper, STEPPER_STATE state, u16 steps){
//	u8 i;
//	sint8 j; /* signed to prevent over flow in case < 0 */
//	switch(stepper -> mode){
//	case FULL_STEP:
//		if(state == STEPPER_CW){
//			for(i = 0; i < steps; i++){
//				for(j = 0; j < FULL_STEP; j++){
//
//						GPIO_writePortMasked(stepper -> portNum, ~STEPPER_fullStepSequence[j], stepper -> mask);
//
//					_delay_ms(stepper -> delay);
//				}
//			}
//		}
////		else if(state == STEPPER_CCW){
////			for(i = 0; i < steps; i++){
////				for(j = FULL_STEP - 1; j >= 0; j--){
////
////						GPIO_writePortMasked(stepper -> portNum, ~STEPPER_fullStepSequence[j], stepper -> mask);
////
////					_delay_ms(stepper -> delay);
////				}
////			}
////		}
//		break;
//
//	case HALF_STEP:
//		if(state == STEPPER_CW){
//			for(i = 0; i < steps; i++){
//				for(j = 0; j < HALF_STEP; j++){
//
//						GPIO_writePortMasked(stepper -> portNum, ~STEPPER_halfStepSequence[j], stepper -> mask);
//
//					_delay_ms(stepper -> delay);
//				}
//			}
//		}
////		else if(state == STEPPER_CCW){
////			for(i = 0; i < steps; i++){
////				for(j = HALF_STEP - 1; j >= 0; j--){
////
////						GPIO_writePortMasked(stepper -> portNum, ~STEPPER_halfStepSequence[j], stepper -> mask);
////
////					_delay_ms(stepper -> delay);
////				}
////			}
////		}
//		break;
//	}
//}
