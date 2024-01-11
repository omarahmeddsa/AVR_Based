/*
 * Ultrasonic.c
 *
 *  Created on: Jan 11, 2024
 *      Author: omar
 */

#include "Bit_calc.h"
#include "Macros.h"
#include "MemoryMap.h"
#include "STD_TYPES.h"
#include "util/delay.h"
#include "Dio.h"
#include "Timer_1.h"
#include "Ultrasonic.h"
#include "LCD.h"
/*************************************************************
 * Global Variables
 ************************************************************/
static volatile u16 Time1,Time2 , Flag=0  , Counter=0;

/**********************************************************
 * Function Implementation
 *********************************************************/

static void Timer_OVF (void){

	Counter ++ ;

}

static void Timer_ICU (void){

	//lCD_SetPostion(1, 0);
	//LCD_WriteNumber(Counter);
	if (Flag  == 0 ){

		Flag = 1;
		Counter = 0 ;
		Time1 = Timer1_u16_TCNT1;
		Counter = 0 ;

		ICU_Init(Falling_Edge);


	}
	else if (Flag == 1){
		Flag = 2;
		Time2 = Timer1_u16_TCNT1;
		ICU_Init(Rising_Edge);

		Timer1_ICU_DIS();
		Timer1_OVF_DIS();

	}

}


void Ultrasonic_Init (void ){

	Timer_1_Init(CLK_8, Normal_Mode, OC_DISCONNECTED, OC_DISCONNECTED);
	Timer1_OVF_Callback(Timer_OVF);
	Timer1_ICU_Callback(Timer_ICU);

}

u8 Ultrasonic_Get_Distance (void){
	u8 Distance ;
    u16 time ;
	Dio_u8_SetPinDir(Trigger_Group, Trigger_PIN, Dio_PinOutput);
	Dio_u8_SetPinDir(ECO_Group, ECO_PIN, Dio_PinInput);

	Dio_u8_SetPinVal(Trigger_Group, Trigger_PIN, Dio_PinHigh);
	_delay_us(10);
	Dio_u8_SetPinVal(Trigger_Group, Trigger_PIN, Dio_PinLow);

	ICU_Init(Rising_Edge);

	Timer1_ICU_ENB();
	Timer1_OVF_ENB();


	while  (Flag < 2);
		time = (Time2 - Time1 )  + ((u32)Counter* 65535) ;
		Distance = time / 58;
		ICU_Init(Rising_Edge);
		/*lCD_SetPostion(1, 7);
		LCD_WriteNumber(Time2);
		lCD_SetPostion(1, 0);
		LCD_WriteNumber(Time1);*/
		Timer1_ICU_DIS();



	return Distance;
}
