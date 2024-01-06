/*
 * LCD.c
 *
 *  Created on: Jan 6, 2024
 *      Author: omar
 */


#include "Bit_calc.h"
#include "Macros.h"
#include "STD_TYPES.h"
#include "MemoryMap.h"
#include "util/delay.h"
#include "Dio.h"
#include "LCD.h"

/****************************************************************
 *
 * The purpose of this Driver is to interface with LCD
 *
 * LCD has two modes
 * 8-bit
 * 4-bit
 *
 * To choose one of them, the value of the LCD_mode should be changed between
 *
 * -LCD 8-bit Mode
 * -LCD 4-bit Mode
 *
 *****************************************************************/

/************************************************************************
 *
 * Implementation
 *
 *************************************************************************/
void LCD_Send_FallingEdge () {

	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_ENB, Dio_PinHigh);
	_delay_ms (2);

	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_ENB, Dio_PinLow);
	_delay_ms (2);

}
void LCD_Send_Data (u8 Copy_u8_Data) {

#if LCD_MODE == LCD_8Bit_mode

	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_RS, Dio_PinHigh);
	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_RW, Dio_PinLow);
	Dio_u8_SetPortValue(LCD_Data_Port, Copy_u8_Data);
	LCD_Send_FallingEdge();


#elif LCD_MODE == LCD_4Bit_mode

	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_RS, Dio_PinHigh);
	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_RW, Dio_PinLow);
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D0, Get_Bit(Copy_u8_Data));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D1, Get_Bit(Copy_u8_Data,5));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D2, Get_Bit(Copy_u8_Data,6));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D3, Get_Bit(Copy_u8_Data,7));
	LCD_Send_FallingEdge();
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D0, Get_Bit(Copy_u8_Data,0));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D1, Get_Bit(Copy_u8_Data,1));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D2, Get_Bit(Copy_u8_Data,2));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D3, Get_Bit(Copy_u8_Data,3));
	LCD_Send_FallingEdge();


#endif

}

void LCD_Send_Commoand(u8 Copy_u8_Command){


#if LCD_MODE == LCD_8Bit_mode

	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_RS, Dio_PinLow);
	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_RW, Dio_PinLow);
	Dio_u8_SetPortValue(LCD_Data_Port, Copy_u8_Command);
	LCD_Send_FallingEdge();


#elif LCD_MODE == LCD_4Bit_mode

	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_RS, Dio_PinLow);
	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_RW, Dio_PinLow);

	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D0, Get_Bit(Copy_u8_Command,4));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D1, Get_Bit(Copy_u8_Command,5));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D2, Get_Bit(Copy_u8_Command,6));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D3, Get_Bit(Copy_u8_Command,7));

	LCD_Send_FallingEdge();

	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D0, Get_Bit(Copy_u8_Command,0));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D1, Get_Bit(Copy_u8_Command,1));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D2, Get_Bit(Copy_u8_Command,2));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D3, Get_Bit(Copy_u8_Command,3));

	LCD_Send_FallingEdge();


#endif

}

void LCD_Display_Clear (){

	LCD_Send_Commoand(LCD_Display_clear);
	_delay_ms(20);

}

void LCD_Init (void){

#if LCD_MODE == LCD_8Bit_mode

	_delay_ms(50);

	Dio_u8_SetPortDir(LCD_Data_Port, Dio_PortHigh);
	LCD_Send_Commoand(LCD_Function_Set);

	_delay_us(50);

	LCD_Send_Commoand(LCD_ON_OFF_Display);

	_delay_us(50);

	LCD_Display_Clear();

	LCD_Send_Commoand(LCD_Entry_Set_Mode);




#elif LCD_MODE == LCD_4Bit_mode

	Dio_u8_SetPinDir(LCD_CTR_Port, LCD_RS, Dio_PinOutput);
	Dio_u8_SetPinDir(LCD_CTR_Port, LCD_RW, Dio_PinOutput);
	Dio_u8_SetPinDir(LCD_CTR_Port, LCD_ENB, Dio_PinOutput);
	_delay_ms(50);
	LCD_Send_Command(0x33);
	_delay_ms(1);
	LCD_Send_Command(0x02);
	_delay_ms(1);
	LCD_Send_Command(0x28);
	_delay_ms(1);
	LCD_Send_Command(0x0c);
	_delay_ms(1);
	LCD_Send_Command(0x01);
	_delay_ms(30);
	LCD_Send_Command(0x06);
	LCD_Send_Command(0x80);


#endif

}


void lCD_SetPostion (u8 line , u8 x)

{

		if ((line >= 2 ) || (x >=15)){

			LCD_Send_Commoand (0x80);
		}

		if (line == 0){

			LCD_Send_Commoand(0x80 + x);

		}
		else if (line == 1) {

			LCD_Send_Commoand(0xC0 + x);

		}
	}

void LCD_Send_String (u8 *PtrStr){
u8 StrIterator = 0  ;

	while (PtrStr [StrIterator] != '\0') {

		LCD_Send_Data(PtrStr[StrIterator]);

		StrIterator ++;

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

