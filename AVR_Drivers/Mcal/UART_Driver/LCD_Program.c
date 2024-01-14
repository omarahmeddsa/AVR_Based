/*
 * LCD_Program.c
 *
 *  Created on: Aug 19, 2023
 *      Author: omar
 */


#include "Bit_calc.h"
#include "STD_TYPES.h"
#include "avr/delay.h"
#include "Dio_Private.h"
#include "Dio_Interface.h"
#include "LCD_Config.h"
#include "LCD_Interface.h"


void LCD_Send_FallingEdge () {

	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_ENB, Dio_PinHigh);
	_delay_ms (2);

	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_ENB, Dio_PinLow);
	_delay_ms (2);

}



void LCD_Send_Data (u8 Copy_u8_Data) { 											// Sending Data

	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_RS, Dio_PinHigh);
	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_RW, Dio_PinLow);
	Dio_u8_SetPortValue(LCD_Data_Port, Copy_u8_Data);
	LCD_Send_FallingEdge();

}

void LCD_Send_Commoand(u8 Copy_u8_Command) {

	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_RS, Dio_PinLow);
	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_RW, Dio_PinLow);
	Dio_u8_SetPortValue(LCD_Data_Port, Copy_u8_Command);
	LCD_Send_FallingEdge();

}


void LCD_Display_Clear (){

	LCD_Send_Commoand(LCD_Display_clear);
	_delay_ms(20);

}


void LCD_Init () {

	_delay_ms(50);

	Dio_u8_SetPortDir(LCD_Data_Port, Dio_PortHigh);
	LCD_Send_Commoand(LCD_Function_Set);

	_delay_us(50);

	LCD_Send_Commoand(LCD_ON_OFF_Display);

	_delay_us(50);

	LCD_Display_Clear();

	LCD_Send_Commoand(LCD_Entry_Set_Mode);


}

void LCD_Send_String (const u8 * Copy_StringPTR) {

	u8 Local_Iter = 0;

	while (Copy_StringPTR [Local_Iter] != '\0') {
		LCD_Send_Data(Copy_StringPTR [Local_Iter]);
		Local_Iter ++ ;

		}

	}
void LCD_postion (u8 line, u8 x) {

	if ((line >= 2 ) || (x >=15)){

		LCD_Send_Commoand(LCD_First_Raw);
	}

	if (line == 0){

		LCD_Send_Commoand(LCD_First_Raw + x);

	}
	else if (line == 1) {

		LCD_Send_Commoand(LCD_Second_Raw + x);

	}
}

void LCD_WriteNumber(u32 Number)
{
	u8 i=0,arr[10],j;
	if(Number==0)
	LCD_Send_Data('0');
	else{
			while(Number)
			{
				arr[i]=Number%10+'0';
				Number/=10;
				i++;
			}
			for(j=i;j>0;j--)
			{
				LCD_Send_Data(arr[j-1]);
			}
	   }
}
