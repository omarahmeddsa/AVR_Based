/*
 * main.c
 *
 *  Created on: Nov 16, 2023
 *      Author: omar
 */

#include "Bit_calc.h"
#include "STD_TYPES.h"
#include "Dio_Private.h"
#include "Dio_Config.h"
#include "Dio_Interface.h"
#include "LCD_Config.h"
#include "LCD_Interface.h"
#include "EEPROM.h"
#include "avr/io.h"


int main (){

	u8 x ;
	LCD_4Bit_Init();


	EEPROM_write(0x20, 'O');

	x = EEROM_Read(0x20);


	lCD_SetPostion(0, 0);
	LCD_Send_Data(x);


	while (1){



	}
	return 0;
}
