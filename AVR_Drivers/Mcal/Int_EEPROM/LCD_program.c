/*
 * LCD_program.c
 *
 *  Created on: Oct 25, 2023
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

void LCD_Send_FallingEdge () {

	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_ENB, Dio_PinHigh);
	_delay_ms (2);

	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_ENB, Dio_PinLow);
	_delay_ms (2);

}



void LCD_Send_Data(u8 Data ){

	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_RS, Dio_PinHigh);
	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_RW, Dio_PinLow);
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D0, Get_Bit(Data,4));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D1, Get_Bit(Data,5));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D2, Get_Bit(Data,6));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D3, Get_Bit(Data,7));
	LCD_Send_FallingEdge();
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D0, Get_Bit(Data,0));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D1, Get_Bit(Data,1));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D2, Get_Bit(Data,2));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D3, Get_Bit(Data,3));
	LCD_Send_FallingEdge();

}

void LCD_Send_Command (u8 Command ){

	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_RS, Dio_PinLow);
	Dio_u8_SetPinVal(LCD_CTR_Port, LCD_RW, Dio_PinLow);

	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D0, Get_Bit(Command,4));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D1, Get_Bit(Command,5));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D2, Get_Bit(Command,6));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D3, Get_Bit(Command,7));

	LCD_Send_FallingEdge();

	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D0, Get_Bit(Command,0));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D1, Get_Bit(Command,1));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D2, Get_Bit(Command,2));
	Dio_u8_SetPinVal(LCD_Data_Port, LCD_D3, Get_Bit(Command,3));

	LCD_Send_FallingEdge();

}

void LCD_4Bit_Init (void ){

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

}


void lCD_SetPostion (u8 line , u8 x)

{

		if ((line >= 2 ) || (x >=15)){

			LCD_Send_Command (0x80);
		}

		if (line == 0){

			LCD_Send_Command(0x80 + x);

		}
		else if (line == 1) {

			LCD_Send_Command(0xC0 + x);

		}
	}



void LCD_Send_String (u8 *PtrStr){
u8 StrIterator = 0  ;

	while (PtrStr [StrIterator] != '\0') {
		LCD_Send_Data(PtrStr[StrIterator]);
		StrIterator ++;
	}

}

void LCD_WriteNumber(u16 Number)
{
	u8 i=0,arr[10],j;

	if(Number==0)
	LCD_Send_Data('0');
	else{
			while(Number )
			{
				arr[i]=Number%10+'0';
				Number/=10;
				i++;
			}
			for(j=i ;j>0 ;j--)
			{
				LCD_Send_Data(arr[j-1]);
			}
	   }
}

void LCD_WriteNumber2(u16 Number)
{
	LCD_Send_Data(Number%10000/1000+'0');
	LCD_Send_Data(Number%1000/100+'0');
	LCD_Send_Data(Number%100/10+'0');
	LCD_Send_Data(Number%10/1+'0');
}
void LCD_Clear(void)
{

	LCD_Send_Command(0x01);

}



