/*
 * main.c
 *
 *  Created on: Oct 27, 2023
 *      Author: omar
 */

#include "Bit_calc.h"
#include "STD_TYPES.h"
#include "Dio_Private.h"
#include "Dio_Config.h"
#include "Dio_Interface.h"
#include "LCD_Interface.h"
#include "LCD_Config.h"
#include "avr/delay.h"
#include "KPD.h"

#define WrongPasscode 0
#define Welcome       1


u8 Check_Password (u8 * passcode){



	return Welcome;
}


void main (void ){

	Dio_u8_SetPinDir(Group_C, PIN4, Dio_PinOutput);
	Dio_u8_SetPinDir(Group_C, PIN5, Dio_PinOutput);
	Dio_u8_SetPinDir(Group_C, PIN6, Dio_PinOutput);
	u8 x [100] = {0} ;
	LCD_4Bit_Init();
	KPD_Init();

	u8 i;
	while (1) {

	lCD_SetPostion(0, 0);
	LCD_Send_String("Entre Passcode");

	x [i]= KPD_PRESSED();
	if (x[i] != '\0')
	{

		lCD_SetPostion(1, i);
		LCD_Send_String(&x[i]);
		_delay_ms(100);
		lCD_SetPostion(1, i);
		LCD_Send_String("*");
		i++;
	}
	else {

		}


	}
}

