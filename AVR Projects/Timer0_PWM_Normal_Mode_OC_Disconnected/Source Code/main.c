/*
 * main.c
 *
 *  Created on: Dec 5, 2023
 *      Author: omar
 */
#include "Bit_calc.h"
#include "Macros.h"
#include "MemoryMap.h"
#include "STD_TYPES.h"
#include "Dio.h"
#include "avr/delay.h"
#include "Timer.h"


/**************************************************************************************
 * The project description
 * ************************************************************************************
 * The purpose of this project is to generate PWM in normal Mode Timer 0 without using OC0 Pin
 *
 * Modules used : Dio Driver , Timer0
 *
 * Description : In this project Timer0 Normal mode is used to generate PWM with OC0 Disconnected
 *
 * The DutyCycle of PWM is 20%
 *
 *
 ****************************************************************************************************/


/******************************************************************************************************
 *
 * ISR Function
 *****************************************************************************************************/
void Timer0 (void){
	static u32 Flag ;
	Flag ++ ;
	Timer0_TCNT0 = 56;
	/*******************************************************************
	 *
	 * Flag == 1 ,  means 1 Overflow
	 *
	 *******************************************************************/

	if (Flag == 4) {

		Dio_u8_SetPinVal(Group_A, PIN0, Dio_PinHigh);

	}
	if (Flag == 5){


		Dio_u8_SetPinVal(Group_A, PIN0, Dio_PinLow);

		Flag = 0;
	}
}

int main (void){
	/*Timer0 Init */
	Dio_u8_SetPinDir(Group_A, PIN0, Dio_PinOutput);
	Dio_u8_SetPinDir(Group_B, PIN2, Dio_PinOutput);

	/**************** Timer ************************/
	Gobal_interrput_Enbale(); 										 // Enable Global Interrupt
	Timer0_OVF_Enable ();  											// Over Flow Interrupt
	Timer0_TCNT0 = 56; 											   //Start Counting from 56 , in order to OVF after 200 Reps
	Timer0_init( Timer0_NormalMode , _CLK8_, OC0_Disconnected);   // Init Timer0 Normal mode and F-cpu / 8 Pre-sacler
	Timer0_OVF_Callback(Timer0); 								 // Pass the address of the function to the ISR


	while (1){
	}

	return 0 ;
}
