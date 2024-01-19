/*
 * main.c
 *
 *  Created on: Jan 17, 2024
 *      Author: omar
 */
#include "MemoryMap.h"
#include "STD_TYPES.h"
#include "Macros.h"
#include "Bit_calc.h"
#include "Dio.h"
#include "Seven_Segment.h"
#include "util/delay.h"
#include "Timer_1.h"
#include "Timer.h"
#include "KPD.h"
#include "LCD.h"
#include "util/delay.h"
/*******************************************
 * Function prototypes
 ******************************************/
void Set_Clock (void);
/****************************************
 * Global Variables
****************************************/
volatile u8 Sec; // Seconds Counter
u8 array [100] = {0}; // The inputs are save at this array
u8 min_Clock = 0; // Minutes Counter
u8 Hrs = 0 ; // Hours Counter
/*****************************************************
 * Implementation
 *****************************************************/


void Clock (void){

// The Function of ISR Timer 0
/** This Function Check the Input of the keypad each 1000 micro_seconds
 * Check the Input of the keypad each 1000 micro_seconds
 * Increase the Sec Counter and Min Counter and Hours Counter
 * Put 0 Zero in each counter when its period ended
 **/
	static u16 flag ;
	static u16 KPD_Counter ;

	flag ++ ;

	KPD_Counter ++;

		if (KPD_Counter == 1000){
			Set_Clock();
			KPD_Counter = 0;
		}
		if (flag == 10000){
			Sec ++;
			flag = 0;
			}
		else if (Sec >= 60){

			min_Clock ++;
			Sec = 0;
			}

		else if (min_Clock >= 60){

			Hrs ++;
			min_Clock = 0;
			}

		else if (Hrs >= 24){
			Hrs = 0;
		}
}

void Set_Clock (void){

/****************
 * This Function check the inputs of Key Pad
 * and update the clock set with it to adjust it
 */

		array [0] = KPD_PRESSED();

		if (array [0] != '\0'){

			if (array [0] == '1'){


				lCD_SetPostion(1, 0);

				LCD_WriteNumber(1);

				_delay_ms(500);

				LCD_Display_Clear();


				lCD_SetPostion(0, 0);
				LCD_Send_String("Set Hrs");

				do {
					array [1] = KPD_PRESSED();

				} while (array [1] == '\0');


					lCD_SetPostion(1, 0);
					LCD_Send_String(&array[1]);

				_delay_ms(500);

				do {
					array [2] = KPD_PRESSED();

					} while (array [2] == '\0');



					lCD_SetPostion(1, 1);
					LCD_Send_String(&array[2]);



				_delay_ms(100);

				LCD_Display_Clear();

				lCD_SetPostion(0, 0);
				LCD_Send_String("Set Min");

				do {
					array [3] = KPD_PRESSED();

				} while (array [3] == '\0');

				lCD_SetPostion(1, 0);
				LCD_Send_String(&array[3]);



				_delay_ms(500);

				do {
					array [4] = KPD_PRESSED();

				} while (array [4] == '\0');



					lCD_SetPostion(1, 1);
					LCD_Send_String(&array[4]);


				_delay_ms(500);

				LCD_Display_Clear();
				lCD_SetPostion(0, 0);
				LCD_Send_String("The Clock");
				Hrs = ((array[1] -48)* 10)+ (array[2] - 48);
				lCD_SetPostion(1, 0);
				LCD_WriteNumber(Hrs);

				lCD_SetPostion(1, 2);
				LCD_Send_Data(':');

				min_Clock = ((array[3] -48)* 10)+ (array[4] - 48);
				lCD_SetPostion(1, 3);
				LCD_WriteNumber(min_Clock);
				_delay_ms(100);


				Sec = 0 ;
				LCD_Display_Clear();
				lCD_SetPostion(0, 0);
				LCD_Send_String("Click one to Set Clock");
				}

				else {
					Real_Time_CLK();
				}

			}
			else {
				Real_Time_CLK();

			}


}




void Real_Time_CLK (void){

	/******************************
	 * This is the mormal Clock Mode
	 */

	Clear_Bit(DIO_U8_PORTA,0);
    Set_Bit(DIO_U8_PORTA , 1);
	Set_Bit(DIO_U8_PORTA , 2);
	Set_Bit(DIO_U8_PORTA , 3);
	Set_Bit(DIO_U8_PORTA , 4);
	Set_Bit(DIO_U8_PORTA , 5);
	SevenSegment_Write(Sec%10);
	_delay_ms(5);

	Set_Bit(DIO_U8_PORTA,0);
	Clear_Bit(DIO_U8_PORTA,1);
	Set_Bit(DIO_U8_PORTA , 2);
	Set_Bit(DIO_U8_PORTA , 3);
	Set_Bit(DIO_U8_PORTA , 4);
	Set_Bit(DIO_U8_PORTA , 5);
	SevenSegment_Write(Sec / 10);
	_delay_ms(5);

	Set_Bit(DIO_U8_PORTA,0);
    Set_Bit(DIO_U8_PORTA , 1);
	Clear_Bit(DIO_U8_PORTA ,2);
	Set_Bit(DIO_U8_PORTA , 3);
	Set_Bit(DIO_U8_PORTA , 4);
	Set_Bit(DIO_U8_PORTA , 5);
	SevenSegment_Write(min_Clock%10);
	_delay_ms(5);

	Set_Bit(DIO_U8_PORTA,0);
	Set_Bit(DIO_U8_PORTA,1);
	Set_Bit(DIO_U8_PORTA , 2);
	Clear_Bit(DIO_U8_PORTA , 3);
	Set_Bit(DIO_U8_PORTA , 4);
	Set_Bit(DIO_U8_PORTA , 5);
	SevenSegment_Write(min_Clock / 10);
	_delay_ms(5);


	Set_Bit(DIO_U8_PORTA,0);
    Set_Bit(DIO_U8_PORTA , 1);
	Set_Bit(DIO_U8_PORTA ,2);
	Set_Bit(DIO_U8_PORTA , 3);
	Clear_Bit(DIO_U8_PORTA , 4);
	Set_Bit(DIO_U8_PORTA , 5);
	SevenSegment_Write(Hrs%10);
	_delay_ms(5);

	Set_Bit(DIO_U8_PORTA,0);
	Set_Bit(DIO_U8_PORTA,1);
	Set_Bit(DIO_U8_PORTA , 2);
	Set_Bit(DIO_U8_PORTA , 3);
	Set_Bit(DIO_U8_PORTA , 4);
	Clear_Bit(DIO_U8_PORTA , 5);
	SevenSegment_Write(Hrs / 10);
	_delay_ms(5);

}

void main (void ){


	LCD_Init();
	KPD_Init();
	Gobal_interrput_Enbale();
	SevenSegment_Init();

	lCD_SetPostion(0, 0);
	LCD_Send_String("Click one to Set Clock");


	/*********************
	 * Timer 0 init
	 *********************/
	Timer0_init(Timer0_CTC, CLK_8, OC0_Disconnected);
	Dio_u8_SetPortDir(Group_A, Dio_PortOutput);
	Timer0_OCR0 = 99;						// To make 100 micro-sec each over-flow
	Timer0_OC_Enable();
	Timer0_OC_CallBack(Clock);



	while (1){

		// Calling Clock system Function
		Real_Time_CLK();

	}
}



