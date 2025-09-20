#ifndef HAL_SERVO_H_
#define HAL_SERVO_H_

#include "../../LIBRARY/standard_types.h"


#define SERVO_TOP_VALUE   39999
#define SERVO_MIN_PULSE   2000
#define SERVO_MAX_PULSE   4000


/* Initialize Servo motor on OC1A (PD5) */
void SERVO_init(void);

/* Set Servo angle (0° → 180°) */
void SERVO_setAngle( u8 angle);

#endif /* HAL_SERVO_H_ */
