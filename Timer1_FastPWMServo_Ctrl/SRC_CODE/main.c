/*
 * main.c
 *
 *  Created on: Jan 4, 2024
 *      Author: omar
 */
#include "Bit_calc.h"
#include "MemoryMap.h"
#include "Macros.h"
#include "STD_TYPES.h"
#include "Dio.h"
#include "EXIT.h"
#include "Timer_1.h"

/*************************************************************************************************
 * Description : The purpose of this project is to CTRL a servo  motor angle  using PWM
 *
 *	Modules : GPIO , External Interrupt , Timer 1 Fast PWM with ICR1 is the top value  Mode
 *
 *	Components : Two Servo Motor ,  Two push button , Check LED , Oscilloscope
 *
 *	push button 1 Controls the angle of servo A by changing the OCRA value, push button 2 Controls
-the angle of servo B by changing the OCRB value
 ************************************************************************************************************/


// ISR For push Button 1

void ServoA_PushButton (void ){
	static u8 Flag ;



	if (Flag == 0 ){

		Timer1_u16_OCR1A = 999; // angle 0

		Flag = 1 ;
	}

	else if (Flag ==1){


		Timer1_u16_OCR1A = 1499;  // angle 90
		Flag = 2 ;
	}

	else if (Flag == 2){

		Timer1_u16_OCR1A = 1999;  // angle 180
		Flag = 0 ;

	}

}

// ISR For push Button 2

void ServoB_PushButton (void ){

	static u8 Flag ;

	Toggle_Bit(DIO_U8_PORTA,PIN0);

	if (Flag == 0 ){

		Timer1_u16_OCR1B = 999;   // angle 0

		Flag = 1 ;
	}

	else if (Flag ==1){


		Timer1_u16_OCR1B = 1249;  // angle 45
		Flag = 2 ;
	}

	else if (Flag == 2){

		Timer1_u16_OCR1B = 1749;  // angle 135
		Flag = 0 ;

	}

}





void main (void ){

	// Enable Interrupt
	Gobal_interrput_Enbale();

	// Set Direction of PIN0 DDRA as check
	Dio_u8_SetPinDir(Group_A, PIN0, Dio_PinOutput);


	//Enable PullUp on  INT0 Pin
	Dio_Pullup(Group_D, PIN2);
	Dio_Pullup(Group_D, PIN3);


	// Init INT0 (PushButton 1 )
	EXTI_Init(INT0);
	EXTI_SenseCTRL(Falling_Edge, INT0);   // The trigger edge is falling edge
	Callback_INT0(INT0, ServoA_PushButton);

	// Init INT0 (PushButton 2 )
	EXTI_Init(INT1);
	EXTI_SenseCTRL(Falling_Edge, INT1);  // The trigger edge is falling edge
	Callback_INT0(INT1, ServoB_PushButton);





	/*However,note that the Data Direction Register (DDR) bit
	 * corresponding to the OC1A or OC1B pin
	 * must be set in order to enable the output driver*/
	Dio_u8_SetPinDir(Group_D, PIN4, Dio_PinOutput);
	Dio_u8_SetPinDir(Group_D, PIN5, Dio_PinOutput);

	Timer1_u16_ICR1  = 19999;

	// Timer 1 Init

	Timer_1_Init(CLK_8, FastPWM_ICR1A, NonInverting_OC, NonInverting_OC);

	while (1){

	}



}
