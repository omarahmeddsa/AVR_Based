/*
 * main.c
 *
 *  Created on: Oct 8, 2023
 *      Author: omar
 */

#include "Bit_calc.h"
#include "STD_TYPES.h"
#include "Dio_Private.h"
#include "Dio_Interface.h"
#include "UART_private.h"
#include "UART_Interface.h"
#include "UART_Config.h"
#include "UART_Services.h"
#include "LCD_Private.h"
#include "LCD_Config.h"
#include "LCD_Interface.h"
#include "avr/delay.h"



int main() {

	u8 Data [100] = {0} ;

	Dio_u8_SetPinDir(Group_B, PIN5, Dio_PinOutput);
	Dio_u8_SetPinDir(Group_B, PIN6, Dio_PinOutput);
	Dio_u8_SetPinDir(Group_B, PIN7, Dio_PinOutput);
	LCD_Init();
	USART_Init();
	Global_interrput_Enable();
	UART_SendStr_Async("Omar");





	while (1){


		/*_delay_ms(200);
		LCD_postion (0 , 0);
		LCD_WriteNumber(i);
		i ++ ;
		if (i == 10 ){

			i = 0 ;
		}*/

	}

}
