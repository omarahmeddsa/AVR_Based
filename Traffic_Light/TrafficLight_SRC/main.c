/*
 * main.c
 *
 *  Created on: Dec 10, 2023
 *      Author: omar
 */
/********************************************************************************************************************
 * Name : Traffic Lights
 * Description :  This Traffic Light has 3 modes , to switch between them we use Push button
 * Micro_controller : Atmega 32 , 8 HZ
 * *****************************************************************/



/******************************************************************
 * Includes
 *******************************************************************/
#include "MemoryMap.h"
#include "STD_TYPES.h"
#include "Macros.h"
#include "avr/delay.h"
#include "Bit_calc.h"
#include "Dio.h"
#include "EXIT.h"
/******************************************************************
 * Definitions
 *******************************************************************/
#define  RED_Light     PIN0
#define  Yellow_Light  PIN1
#define  Green_Light   PIN2

/******************************************************************
 * prototypes
 *******************************************************************/
void Mode_1 ();
void Mode_2 ();
void Mode_3 ();
int main ()	;

/********************************************************************
 * Global Functions
 ********************************************************************/
volatile u8 flag ;
/******************************************************************
 * Implementation
 *******************************************************************/


/*******************************************************************
 *
 *
 * The three modes Functions
 *
 *
 *******************************************************************/
void Mode_1 (){
	Gobal_interrput_Enbale() ;
	for (u8 i = 0 ; i < 5 ; i ++){

		Dio_u8_SetPinVal(Group_A, RED_Light, Dio_PinHigh);
		Dio_u8_SetPinVal(Group_A, Yellow_Light, Dio_PinHigh);
		Dio_u8_SetPinVal(Group_A, Green_Light, Dio_PinLow);

		_delay_ms(500);

		Dio_u8_SetPinVal(Group_A, RED_Light, Dio_PinLow);
		Dio_u8_SetPinVal(Group_A, Yellow_Light, Dio_PinHigh);
		Dio_u8_SetPinVal(Group_A, Green_Light, Dio_PinHigh);

		_delay_ms(500);

		Dio_u8_SetPinVal(Group_A, RED_Light, Dio_PinHigh);
		Dio_u8_SetPinVal(Group_A, Yellow_Light, Dio_PinLow);
		Dio_u8_SetPinVal(Group_A, Green_Light, Dio_PinHigh);

		_delay_ms(500);

		Dio_u8_SetPinVal(Group_A, RED_Light, Dio_PinLow);
		Dio_u8_SetPinVal(Group_A, Yellow_Light, Dio_PinLow);
		Dio_u8_SetPinVal(Group_A, Green_Light, Dio_PinLow);


	}

}

void Mode_2 (){

	for (u8 i = 0 ; i < 5 ; i++){

		Dio_u8_SetPinVal(Group_A, RED_Light, Dio_PinHigh);
		Dio_u8_SetPinVal(Group_A, Yellow_Light, Dio_PinLow);
		Dio_u8_SetPinVal(Group_A, Green_Light, Dio_PinLow);

		_delay_ms(500);

		Dio_u8_SetPinVal(Group_A, RED_Light, Dio_PinLow);
		Dio_u8_SetPinVal(Group_A, Yellow_Light, Dio_PinHigh);
		Dio_u8_SetPinVal(Group_A, Green_Light, Dio_PinLow);

		_delay_ms(500);

		Dio_u8_SetPinVal(Group_A, RED_Light, Dio_PinLow);
		Dio_u8_SetPinVal(Group_A, Yellow_Light, Dio_PinLow);
		Dio_u8_SetPinVal(Group_A, Green_Light, Dio_PinHigh);

		_delay_ms(500);

		Dio_u8_SetPinVal(Group_A, RED_Light, Dio_PinLow);
		Dio_u8_SetPinVal(Group_A, Yellow_Light, Dio_PinLow);
		Dio_u8_SetPinVal(Group_A, Green_Light, Dio_PinLow);


	}
}

void Mode_3 (){


	for (u8 i = 0 ; i < 5 ; i++){
		Dio_u8_SetPinVal(Group_A, RED_Light, Dio_PinHigh);
		Dio_u8_SetPinVal(Group_A, Yellow_Light, Dio_PinHigh);
		Dio_u8_SetPinVal(Group_A, Green_Light, Dio_PinHigh);

		_delay_ms(1000);

		Dio_u8_SetPinVal(Group_A, RED_Light, Dio_PinLow);
		Dio_u8_SetPinVal(Group_A, Yellow_Light, Dio_PinLow);
		Dio_u8_SetPinVal(Group_A, Green_Light, Dio_PinLow);

		_delay_ms(1000);
	}
}

/*******************************************************************
 *
 *
 * The ISR Function that increment the the flag each time the Button is pushed
 *
 *
 *******************************************************************/
void TrafficLight_ISR (void){

	flag ++;
	if (flag == 1){

		/*Mode  1*/
		Mode_1();

	}

	else if (flag == 2){

		/*Mode 2*/
		Mode_2();

	}

	else if (flag == 3){

		/*mode 3 */

		flag = 0;
		Mode_3();

	}
}

/*******************************************************************
 *
 *
 * Init Function
 *
 *
 *******************************************************************/
int main (void){

	Gobal_interrput_Enbale();

	Dio_u8_SetPinDir(Group_A, PIN0, Dio_PinOutput);
	Dio_u8_SetPinDir(Group_A, PIN1, Dio_PinOutput);
	Dio_u8_SetPinDir(Group_A, PIN2, Dio_PinOutput);

	/*PullUP API*/
	Dio_Pullup(Group_D, PIN2);
	/*Line Init*/
	EXTI_Init(INT0);
	/*Sense Control */
	EXTI_SenseCTRL(Falling_Edge, INT0);
	/*CallBack Function t the ISR*/
	Callback_INT0(INT0,TrafficLight_ISR);

	while (1){


		}


	return 0 ;
}

