/*
 * main_project.c
 *
 *  Created on: Sep 13, 2025
 *      Author: shahd mohamed
 */

#include "HAL/KEY_PAD_driver/Keypad.h"
#include "HAL/LCD_DRIVER/lcd.h"
#include "MCAL/DIO_driver/DIO_interface.h"
#include "LIBRARY/standard_types.h"
#include "LIBRARY/macros.h"
#include "HAL/TCS3200_ColorSensor/CS_interface.h"
#include <util/delay.h>
#include <stdlib.h>  //  itoa convert to numbers
#include "HAL/DC_motor/dc_motor-1.h"
#include "HAL/servo_motor/servo-1.h"
#include "MCAL/EEPROM_DRIVER/24C16N_interface.h"

#include <avr/interrupt.h>

u16 *TOTAL_TIME;
u8 redBin = 0;
u8 greenBin = 0;
u8 blueBin = 0;
u8 counter_red = 0;
u8 counter_green = 0;
u8 counter_Blue = 0;
u8 error = 0;
u8 error_counting =0;
u8 error_color =0;
// KEYPAD CONTROL
void stop(void);
void running(void);
void pause(void);

void displayMenu(void);

// check color and moving motors according to the sensed object in this function
void Moving(u8 color);
void setBin(u8 choose_bin,u8 pt) ;


// emergency button
u8 putton_stop(u8 status);

MotorDriver_t motor1 = {
		.portNum = PORTD_ID,
		.IN1_pinNum = PIN6_ID,
		.motor_prescaler = 64
};

int main() {
	// LCD 4,5 port D, PORTC for data 4,5,6,7
	// key pad port c 0,1,2,3
	SERVO_init();

	CS_INIT();
	FreqScaling(TWENTY_PERCENT);

	//connect the output pin of sesnor to portD pin4 (timer0)


	TIMER2_CTC_init(OC2_CTC_NORMAL, PRESCALER_64, 124);

	TIMER2_CTC_set_cb(ColorSensor_Timer2Callback);

	sei();

	ColorSelect (RED); // START with red photodiodes


	LCD_init();
	LCD_clearScreen();





	MOTOR_DRIVER_init(& motor1);


	u8 counter = 0;

	u8 status = 0;

	u8 choose_bin=0;



	//PORT_A BELONG TO SAGDA'S SENSOR

	//KEYBAD
	DIO_vSetPortDir(PORTA_ID,PORT_INPUT);

	//IR pins
	DIO_voidSetPinDir(PORTD_ID, PIN0_ID, PIN_INPUT);
	DIO_voidSetPinDir(PORTD_ID, PIN1_ID, PIN_INPUT);
	DIO_voidSetPinDir(PORTD_ID, PIN2_ID, PIN_INPUT);
	DIO_voidSetPinDir(PORTD_ID, PIN3_ID, PIN_INPUT);

	// leds
	DIO_voidSetPinDir(PORTB_ID, PIN6_ID, PIN_OUTPUT); //RED LED
	DIO_voidSetPinDir(PORTB_ID, PIN7_ID, PIN_OUTPUT); //GREEN LED

	//putton
	DIO_voidSetPinDir(PORTC_ID, PIN3_ID, PIN_INPUT);

	//buzzer
	DIO_voidSetPinDir(PORTC_ID, PIN2_ID, PIN_OUTPUT);

//	//lcd  data
//	DIO_voidSetPinDir(PORTC_ID, PIN4_ID, PIN_OUTPUT);
//	DIO_voidSetPinDir(PORTC_ID, PIN5_ID, PIN_OUTPUT);
//	DIO_voidSetPinDir(PORTC_ID, PIN6_ID, PIN_OUTPUT);
//	DIO_voidSetPinDir(PORTC_ID, PIN7_ID, PIN_OUTPUT);
//	//LCD CTRL
//	DIO_voidSetPinDir(PORTD_ID, PIN6_ID, PIN_OUTPUT);
//	DIO_voidSetPinDir(PORTD_ID, PIN7_ID, PIN_OUTPUT);
//
//	//SENSOR
//	DIO_voidSetPinDir(PORTB_ID, PIN1_ID, PIN_OUTPUT);
//	DIO_voidSetPinDir(PORTB_ID, PIN2_ID, PIN_OUTPUT);
//	DIO_voidSetPinDir(PORTB_ID, PIN3_ID, PIN_OUTPUT);
//	DIO_voidSetPinDir(PORTB_ID, PIN4_ID, PIN_OUTPUT);
//	DIO_voidSetPinDir(PORTB_ID, PIN5_ID, PIN_OUTPUT);



	displayMenu();


	//servo
	DIO_voidSetPinDir(PORTD_ID, PIN5_ID, PIN_OUTPUT);



	while (1) {

		u8 color = SensingObject();


		u8 pt = KEYPAD_getPressedKey();
		Moving(color);
		if (pt == START) {
			running();
			DIO_voidSetPinValue(PORTA_ID, PIN5_ID, PIN_HIGH);
			DIO_voidSetPinValue(PORTA_ID, PIN6_ID, PIN_LOW);
			DIO_voidSetPinValue(PORTA_ID, PIN7_ID, PIN_LOW);

			// INDICATE RUNNING
			status = RUNNING ;// start motors, counting, reset counter


		}
		else if (pt == PAUSE) {
			pause();
			DIO_voidSetPinValue(PORTA_ID, PIN6_ID, PIN_HIGH);
			DIO_voidSetPinValue(PORTA_ID, PIN5_ID, PIN_LOW);
			DIO_voidSetPinValue(PORTA_ID, PIN7_ID, PIN_LOW);


			// INDICATE PAUSE
			status = Pause; //stop motors only
		}


		else if (pt == Stop) {
			stop();
			DIO_voidSetPinValue(PORTA_ID, PIN7_ID, PIN_HIGH);
			DIO_voidSetPinValue(PORTA_ID, PIN5_ID, PIN_LOW);
			DIO_voidSetPinValue(PORTA_ID, PIN6_ID, PIN_LOW);
			counter=0;
			counter_Blue=0;
			counter_green=0;
			counter_red=0;

			//INDICATE STOP
			status = sTop; //stop motors, reset counter
		}


		else if (pt == Reset) {
			counter = 0;
		}
		else if (pt == Red || pt == Green || pt == Blue) {
			LCD_clearScreen();
			LCD_displayString("A=bin1, B=bin2, C=bin3");
			choose_bin=pt;
			_delay_ms(3000);
			LCD_clearScreen();
			displayMenu();

		}

		else if (pt == COUNT) {
			char buffer[10];

			LCD_clearScreen();

			//check ovrwrite condition
			LCD_displayString("objects=");
			itoa(counter, buffer, 10);
			LCD_displayString(buffer);
			LCD_moveCursor(1,0);

			LCD_displayString(" red=");
			itoa(counter_red, buffer, 10);
			LCD_displayString(buffer);
			_delay_ms(2000);

			LCD_clearScreen();

			LCD_displayString(" green=");
			itoa(counter_green, buffer, 10);
			LCD_displayString(buffer);
			LCD_moveCursor(1,0);

			LCD_displayString(" Blue=");
			itoa(counter_Blue, buffer, 10);
			LCD_displayString(buffer);

			_delay_ms(3000);
			LCD_clearScreen();

			displayMenu();

		}
		else if (pt == STATUS) {
			if (status == RUNNING) {
				LCD_displayString("running");
				_delay_ms(2000);
				displayMenu();

			}
			else if (status == Pause) {
				LCD_displayString("pausing");
				_delay_ms(2000);
				displayMenu();
			}
			else if (status == sTop) {
				LCD_displayString("STOP!");
				_delay_ms(2000);
				displayMenu();
			}
		}

		if (pt == 'A') {
			setBin(choose_bin,pt);
		}
		else if (pt == 'B') {
			// bin2
			setBin(choose_bin,pt);

		}
		else if (pt == 'C') {
			// bin3
			setBin(choose_bin,pt);

		}


		// memory EEPROM

		// SENDING TIME OF spend sORTING
		*TOTAL_TIME= TIME_SORT*165; // close to real not accurate 100%
		EEPROM_WriteString(0x02, TOTAL_TIME);

		//sending total number of object sorted
		// could put a number of sorted color
		EEPROM_writeByte(0x00,counter);

		//


		//first IR

		if (DIO_readPin(PORTD_ID, PIN0_ID)==PIN_HIGH){
			counter =counter+1;
		}

		if (counter !=counter_Blue+counter_green+ counter_red){
			LCD_displayString("error in counting");
			error_counting=error_counting+1;

		}
		//sending error number to eeprom
		EEPROM_writeByte(0x01,error);
		EEPROM_writeByte(0x03,error_counting);



		//check errors
		//
		//        if (cheack_error(PORTA_ID, PIN3_ID, 2) == 1) {
		//            counter_Blue = counter_Blue + 1;
		//        }
		//        else {
		//            LCD_displayString("error in sorting");
		//            //STOP TRACK MOTOR
		//            stop();
		//        }
		//
		//        if (cheack_error(PORTA_ID, PIN2_ID, 1) == 1) {
		//        	counter_green = counter_green + 1;
		//        }
		//        else {
		//            LCD_displayString("error in sorting");
		//            //STOP TRACK MOTOR
		//            stop();
		//        }
		//        if (cheack_error(PORTA_ID, PIN1_ID, 0) == 1) {
		//            counter_red = counter_red + 1;
		//        }
		//        else {
		//            LCD_displayString("error in sorting");
		//            //STOP TRACK MOTOR
		//            stop();
		//        }

		if (putton_stop(status) == sTop) {//0
			stop();
			status = putton_stop(status);

		}
	}

	return 0;
}

// CONSIDER THE STATUES NUM
void stop(void) {
	// stop motors
	MOTOR_DRIVER_setSpeed(& motor1 , STOP,1);
	TOTAL_TIME=0;

}

void pause(void) {
	MOTOR_DRIVER_setSpeed(& motor1 , STOP,1);

}
// pause motors

void running(void) {
	// start motors
	MOTOR_DRIVER_setSpeed( & motor1 , CW,1);




}

void displayMenu(void){
	LCD_clearScreen();
	LCD_displayString("1=start  4=pause");
	LCD_moveCursor(1,0);
	LCD_displayString("7=stop  2=count 5=status");
	_delay_ms(1000);
	LCD_clearScreen();
	LCD_displayString("*=reset 3=Red 6=Green 9=Blue");
}

//u8 cheack_error(u8 Copy_u8PortNum, u8 Copy_u8PinNum, u8 color) {
//    u8 reading = DIO_readPin(Copy_u8PortNum, Copy_u8PinNum);
//    u8 object=SensingObject();
//    if (reading == 1 && object ==color) {
//        return 1;
//    }
//    else {
//        return 0;
//    }
//}

u8 putton_stop(u8 status) {

	if (DIO_readPin(PORTC_ID, PIN3_ID) == PIN_LOW) {
		status = sTop;
	}
	return status;
}

void setBin(u8 choose_bin,u8 pt) {
	// choose_bin --> 3,6,9
	// pt --> A,B,C

	if (choose_bin == Red) {      // Red
		redBin = pt;
	} else if (choose_bin == Green) { // Green
		greenBin = pt;
	}
	else if (choose_bin ==Blue){
		blueBin = pt;
	}

}



void Moving(u8 color) {
	if (color == RED) {
		if (redBin == 'A') {
			SERVO_setAngle( 90);
			if (DIO_readPin(PORTD_ID, PIN1_ID)==PIN_HIGH){
				counter_red =counter_red+1;
			}
			else {
				LCD_displayString("error in sorting");
				error = error+1;
			}
			_delay_ms(2000);
			SERVO_setAngle(0);
		}


		else if (redBin == 'B') {
			SERVO_setAngle(180);
			if (DIO_readPin(PORTD_ID, PIN2_ID)==PIN_HIGH){
				counter_red =counter_red+1;
			}
			else {
				LCD_displayString("error in sorting");
				error = error+1;

			}
			_delay_ms(2000);
			SERVO_setAngle( 0);
		}



		else if (redBin =='C'){
			if (DIO_readPin(PORTD_ID, PIN3_ID)==PIN_HIGH){
				counter_red =counter_red+1;
			}
			else{
				LCD_displayString("error in sorting");
				error = error+1;


			}


		}
	}
	else if (color == GREEN) {

		if (greenBin == 'A') {
			SERVO_setAngle(90);
			_delay_ms(2000);
			if (DIO_readPin(PORTD_ID, PIN1_ID)==PIN_HIGH){
				counter_green =counter_green+1;
			}
			else {
				LCD_displayString("error in sorting");
				error = error+1;

			}
			SERVO_setAngle(0);
		}


		else if (greenBin == 'B') {
			SERVO_setAngle(180);
			if (DIO_readPin(PORTD_ID, PIN1_ID)==PIN_HIGH){
				counter_green =counter_green+1;
			}
			else {
				LCD_displayString("error in sorting");
				error = error+1;

			}
			_delay_ms(2000);
			SERVO_setAngle(0);
		}


		else if (greenBin == 'C'){
			if (DIO_readPin(PORTD_ID, PIN3_ID)==PIN_HIGH){
				counter_green =counter_green+1;
			}
			else{
				LCD_displayString('error in sorting');
				error = error+1;


			}


		}
	}


	else if (color == BLUE) {
		if (blueBin == 'A') {
			SERVO_setAngle(90);
			if (DIO_readPin(PORTD_ID, PIN1_ID)==PIN_HIGH){
				counter_Blue =counter_Blue+1;
			}
			else {
				LCD_displayString("error in sorting");
				error = error+1;

			}
			_delay_ms(2000);
			SERVO_setAngle(0);
		}


		else if (blueBin == 'B') {
			SERVO_setAngle(90);
			if (DIO_readPin(PORTD_ID, PIN1_ID)==PIN_HIGH){
				counter_Blue =counter_Blue+1;
			}
			else {
				LCD_displayString("error in sorting");
				error = error+1;

			}
			_delay_ms(2000);
			SERVO_setAngle(0);

		}

		else if (blueBin == 'C'){

			if (DIO_readPin(PORTD_ID, PIN3_ID)==PIN_HIGH){
				counter_Blue =counter_Blue+1;
			}
			else{
				LCD_displayString("error in sorting");
				error = error+1;


			}


		}

	}
	else{
		LCD_displayString("error in color");
		error_color=error_color+1;

	}
}









