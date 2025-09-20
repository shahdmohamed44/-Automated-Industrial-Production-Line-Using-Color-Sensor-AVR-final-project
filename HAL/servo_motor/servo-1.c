#include "servo-1.h"
#include "../../MCAL/DIO_driver/DIO_interface.h"
#include "../../LIBRARY/macros.h"

#include "../../MCAL/TIMER_DRIVER/TIMER1_interface.h"



void SERVO_init(void)
{
	/* Initialize Timer1 in Fast PWM mode, Non-inverting, TOP=ICR1 */
	TIMER1_FAST_PWM_init(NON_INVERTING_MODE,FAST_PWM_NORMAL,PRESCALER_8,SERVO_TOP_VALUE);


	/* Default angle = 0Â° */
	TIMER1_FAST_PWM_set_dutyCycle_B(SERVO_MIN_PULSE);

}


void SERVO_setAngle( u8 angle)
{
	if (angle > 180) angle = 180;

	u16 duty = SERVO_MIN_PULSE + ((u32)angle * (SERVO_MAX_PULSE - SERVO_MIN_PULSE)) / 180;

	// Servo1  OC1B
	TIMER1_FAST_PWM_set_dutyCycle_B(duty);

}


