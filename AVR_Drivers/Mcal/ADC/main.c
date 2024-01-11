/*
 * main.c
 *
 *  Created on: Jan 8, 2024
 *      Author: omar
 */

#include "MemoryMap.h"
#include "Macros.h"
#include "STD_TYPES.h"
#include "Bit_calc.h"
#include "Dio.h"
#include "Timer.h"
#include "ADC.h"
#include "LCD.h"

void ADC_Calc(void);
volatile u16 ADC_Output ;
volatile u16 Result;

void Read_ADC (void){

	ADC_Calc();



}
void main (void ){

	LCD_Init();

	Gobal_interrput_Enbale();

	ADC_Enable();

	ADC_Init(AVCC, Division_128, ADC0,Free_Running_mode);

	ADC_AutoTriggerDisable();

	ADC_InterruptEnable();

	ADC_CallBack( Read_ADC );








	lCD_SetPostion(0, 0);

	LCD_Send_String("Result:");

	while (1){

		ADC_Start_Conversion();



	}
}

void ADC_Calc(void){

	u16 Result;

	Result = ADC_Output_Calc(100,0, ADC0);

	lCD_SetPostion(1, 0);

	LCD_WriteNumber(Result);

}


