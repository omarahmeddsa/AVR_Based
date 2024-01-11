/*
 * main.c
 *
 *  Created on: Jan 6, 2024
 *      Author: omar
 */

#include "Bit_calc.h"
#include "Macros.h"
#include "MemoryMap.h"
#include "STD_TYPES.h"
#include "Dio.h"
#include "LCD.h"




int main (void ){




	LCD_Init();

	lCD_SetPostion(0, 0);

	LCD_Send_String("Omar");

	lCD_SetPostion(1, 0);

	LCD_WriteNumber(252525);




	while (1){

	}

	return 0 ;
}
