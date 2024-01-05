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
#include "LCD_Config.h"
#include "LCD_Interface.h"
#include "EXIT.h"
#include "Timer.h"
/**************************************************************************************
 * The project description
 * ************************************************************************************
 * The purpose of this application is to measure how long a push button is pressed
 *
 * Modules used : Dio Driver , Timer0 , EXternal Interrupt Driver , LCD_4Bit_Driver
 *
 * Description : In this project Timer0 Normal mode is used to generate PWM with OC0 Disconnected
 *
 * The DutyC
 *
 *
 ****************************************************************************************************/
/**********************************************************************************************
 *
 * Global Variables
 *
 ***********************************************************************************************/
volatile u16 Timer0_Counter;
volatile u32 Timer ;

/******************************************************************************************************
 *
 * ISR Function
 *****************************************************************************************************/

void ServoPWM_CTRL (void ){

	static int Counter;
	Counter++;

	if (Counter == 20){

		Dio_u8_SetPinVal(Group_A, PIN0, Dio_PinLow);


	}

	else if (Counter == 200){
		Dio_u8_SetPinVal(Group_A, PIN0, Dio_PinHigh);

	}

}


int main (void){
	/*Timer0 Init */

	Dio_u8_SetPinDir(Group_A, PIN0, Dio_PinOutput);





	Dio_u8_SetPinVal(Group_A, PIN0, Dio_PinHigh);

	/**************** Timer ************************/

	Gobal_interrput_Enbale(); 										   // Enable Global Interrupt
	Timer0_OC_Enable();										      // Compare Match Interrupt Enable

	Timer0_OCR0 = 99;
	Timer0_init( Timer0_CTC , _CLK8_, OC0_Disconnected);    // Init Timer0 Normal mode and F-cpu / 8 Pre-sacler
	Timer0_OC_CallBack(ServoPWM_CTRL);							  // Pass the address of the function to the ISR




	while (1){
	}


	return 0 ;
}
