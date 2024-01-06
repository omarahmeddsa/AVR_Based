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
void Push_Button (void){

	static u8 Flag = 0;

	Flag ++;

	if (Flag == 1){
		Timer0_Counter = 0;
		Timer0_TCNT0 = 0 ;

		EXTI_SenseCTRL(Rising_Edge	, INT0);

	}

	if (Flag == 2) {
		EXTI_SenseCTRL(Falling_Edge	, INT0);
		Timer = (Timer0_TCNT0 + ((u32) Timer0_Counter * 256)) /1000;
		Flag = 0 ;



	}


}

void Timer0_OVF (void ){

	Timer0_Counter ++;

}
int main (void){
	/*Timer0 Init */

	Dio_u8_SetPinDir(Group_A, PIN0, Dio_PinOutput);
	Dio_u8_SetPinDir(Group_B, PIN2, Dio_PinOutput);

	Dio_Pullup(LCD_CTR_Port, PIN5);
	Dio_Pullup(LCD_CTR_Port, PIN6);
	Dio_Pullup(LCD_CTR_Port, PIN7);

	Dio_Pullup(Group_D, PIN2);




	/**************** Timer ************************/
	LCD_8_bit_Init();
	Gobal_interrput_Enbale(); 										   // Enable Global Interrupt
	Timer0_OVF_Enable();										      // Compare Match Interrupt Enable

	Timer0_TCNT0 = 0; 											    //Start Counting from 56 , in order to OVF after 200 Reps
	Timer0_init( Timer0_NormalMode , _CLK8_, OC0_Disconnected);    // Init Timer0 Normal mode and F-cpu / 8 Pre-sacler
	Timer0_OVF_Callback(Timer0_OVF)	;													  // Pass the address of the function to the ISR

	EXTI_Init(INT0);										   	 //Enable Interrupt INT0
	EXTI_SenseCTRL(Falling_Edge	, INT0);				    	// Choosing The sense CTRL
	EXTI_Callback_INT(INT0, Push_Button);
	LCD_postion(0, 0);
	LCD_Send_String("Tim");

	while (1){
	}


	return 0 ;
}
