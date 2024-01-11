/*
 * ADC.c
 *
 *  Created on: Jan 8, 2024
 *      Author: omar
 */
#include "MemoryMap.h"
#include "Macros.h"
#include "STD_TYPES.h"
#include "Bit_calc.h"
#include "util/delay.h"
#include "LCD.h"
#include "Dio.h"
#include "ADC.h"
/*****************************************************************
 *
 * ADC Driver Atmega 32
 */

/**********************************************************************
 *
 * Global Variable
 *********************************************************************/
static void (*ADC_Conversion)(void ) = Null ;

/*********************************************************************
 * Implemantion
 **********************************************************************/
void ADC_Init (Reference_Selection type , Prescaler scaler , Analog_Channel channel,ADC_Trigger_source Src){
	 // Accessing the Enum
	// Choose the Voltage Reference of the ADC
	switch (type){

	case AREF :
		Clear_Bit(ADMUX_u8 , REFS0);
		Clear_Bit(ADMUX_u8 , REFS1);
		break ;
	case AVCC:
		Set_Bit(ADMUX_u8 , REFS0);
		Clear_Bit(ADMUX_u8 , REFS1);
		break;

	case Internal_2Volt :
		Set_Bit(ADMUX_u8 , REFS0);
		Set_Bit(ADMUX_u8 , REFS1);
		break;
	}

	// choose between Left or Right Adjust

	Clear_Bit(ADMUX_u8, ADLAR);  // Right Adjusted


	switch (scaler){

	case Division_2 :
		Set_Bit(ADCSRA_u8, ADPS0);
		Clear_Bit(ADCSRA_u8 ,ADPS1);
		Clear_Bit(ADCSRA_u8 , ADPS2);
		break;
	case Division_4 :
		Clear_Bit(ADCSRA_u8, ADPS0);
		Set_Bit(ADCSRA_u8 ,ADPS1);
		Clear_Bit(ADCSRA_u8 , ADPS2);
		break;
	case Division_8 :
		Set_Bit(ADCSRA_u8, ADPS0);
		Set_Bit(ADCSRA_u8 ,ADPS1);
		Clear_Bit(ADCSRA_u8 , ADPS2);
		break;
	case Division_16 :
		Clear_Bit(ADCSRA_u8, ADPS0);
		Clear_Bit(ADCSRA_u8 ,ADPS1);
		Set_Bit(ADCSRA_u8 , ADPS2);
		break;
	case Division_32 :
		Set_Bit(ADCSRA_u8, ADPS0);
		Clear_Bit(ADCSRA_u8 ,ADPS1);
		Set_Bit(ADCSRA_u8 , ADPS2);
		break;
	case Division_64 :
		Clear_Bit(ADCSRA_u8, ADPS0);
		Set_Bit(ADCSRA_u8 ,ADPS1);
		Set_Bit(ADCSRA_u8 , ADPS2);
		break;
	case Division_128 :
		Set_Bit(ADCSRA_u8, ADPS0);
		Set_Bit(ADCSRA_u8 , ADPS1);
		Set_Bit(ADCSRA_u8 , ADPS2);
		break;
	}

	// Set the pre-scaler
	ADMUX_u8 &= ADMUX_Mask;
	ADMUX_u8 |= channel;

	switch (Src){

	case Free_Running_mode:

		Clear_Bit(SFIOR_u8, ADTS0);
		Clear_Bit(SFIOR_u8, ADTS1);
		Clear_Bit(SFIOR_u8, ADTS2);

		break;

	case Analog_Comp :

		Set_Bit(SFIOR_u8, ADTS0);
		Clear_Bit(SFIOR_u8, ADTS1);
		Clear_Bit(SFIOR_u8, ADTS2);
		break;

	case EXTI0 :
		Clear_Bit(SFIOR_u8, ADTS0);
		Set_Bit  (SFIOR_u8, ADTS1);
		Clear_Bit(SFIOR_u8, ADTS2);
		break;

	case Timer0_Comp :
		Set_Bit(SFIOR_u8, ADTS0);
		Set_Bit  (SFIOR_u8, ADTS1);
		Clear_Bit(SFIOR_u8, ADTS2);
		break;

	case Timer0_OVF :
		Clear_Bit(SFIOR_u8, ADTS0);
		Clear_Bit(SFIOR_u8, ADTS1);
		Set_Bit(SFIOR_u8, ADTS2);
		break ;

	case Timer1_CompB :
		Set_Bit(SFIOR_u8, ADTS0);
		Clear_Bit(SFIOR_u8, ADTS1);
		Set_Bit(SFIOR_u8, ADTS2);
		break ;

	case Timer1_ICU:
		Set_Bit(SFIOR_u8, ADTS0);
		Set_Bit  (SFIOR_u8, ADTS1);
		Set_Bit(SFIOR_u8, ADTS2);
		break ;
	}
}


u16  ADC_GetResult_ASync( Analog_Channel channel){

	u16 Result = 0 ;
	// Set the pre-scaler
	ADMUX_u8 &= ADMUX_Mask;
	ADMUX_u8 |= channel;

	Set_Bit (ADCSRA_u8 , ADSC);

	Result =  (ADCL_u8 )|(((u16)ADCH_u8 )<< 8);

	return Result;
}
u16  ADC_GetResult_Sync(Analog_Channel channel){


   u16 Result =0;
	// Set the pre-scaler
	ADMUX_u8 &= ADMUX_Mask;
	ADMUX_u8 |= channel;

	Set_Bit (ADCSRA_u8 , ADSC);

	//while (Get_Bit(ADCSRA_u8, ADSC));

	while ((Get_Bit(ADCSRA_u8 , ADIF))==0);


	Set_Bit(ADCSRA_u8,ADIF);
	Result =  (ADCL_u8 )|(((u16)ADCH_u8 )<< 8);



	return Result;
}

/******************************************************
 * Enables
 ******************************************************/
void ADC_Enable(void ){

	Set_Bit(ADCSRA_u8 , ADEN);

}

void ADC_Disable(void ){

	Clear_Bit(ADCSRA_u8 , ADEN);

}

void ADC_Start_Conversion(void){

	Set_Bit(ADCSRA_u8, ADSC);
}

void  ADC_AutoTriggerEnable (void){
	Set_Bit(ADCSRA_u8 , ADATE);
}

void  ADC_AutoTriggerDisable (void){
	Clear_Bit(ADCSRA_u8 , ADATE);
}

void  ADC_InterruptEnable (void){

	Set_Bit(ADCSRA_u8 , ADIE);

}

void  ADC_InterruptDisable (void){
	Clear_Bit(ADCSRA_u8 , ADIE);
}
/****************************************************
 *
 * Service Function
 *****************************************************/
u16 ADC_Output_Calc(u16 MAX_Value , u16 MIN_Value, Analog_Channel channel){
	// this function for mapping the value of the ADC- output
	u16  ADC_Output  ;
	u16 Result;
	ADC_Output = ADC_GetResult_ASync(channel);

	Result  = ((MAX_Value - MIN_Value) * ADC_Output ) / 1024;


	return Result;
}
/*********************************************************************
 * Callback Function
 ********************************************************************/
void ADC_CallBack(void (* Local_PTR)(void)){

	ADC_Conversion = Local_PTR ;

}

/*************************************************************************
 * ISR
 ************************************************************************/
void __vector_16(void)__attribute__((signal));
void __vector_16(){

	if (ADC_Conversion != Null){
		ADC_Conversion();
	}
}
