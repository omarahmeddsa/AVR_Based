/*
 * main.c
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

void main (void ){

	u8 D;
	Gobal_interrput_Enbale ( );
	LCD_Init();
	Ultrasonic_Init();

	lCD_SetPostion(0, 0);
	LCD_Send_String("Distance : ");

	while (1){

	D = Ultrasonic_Get_Distance();

		lCD_SetPostion(1,0 );
		LCD_WriteNumber(D);
	}

}
