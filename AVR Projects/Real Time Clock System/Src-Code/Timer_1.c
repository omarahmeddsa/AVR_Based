/*
 * Timer_1.c
 *
 *  Created on: Jan 4, 2024
 *      Author: omar
 */

/***********************************************************************
 *Description : This driver contains API for Timer_1
 *
 *Modules : GPIO
 *
 ************************************************************************/
#include "Bit_calc.h"
#include "MemoryMap.h"
#include "Macros.h"
#include "STD_TYPES.h"
#include "Dio.h"
#include "Timer_1.h"

/***********************************************************************
 *
 * Global Functions
 *
 ***********************************************************************/
static void (* Timer1_OVF) (void ) =  Null;
static void (* Timer1_OCA) (void ) =  Null;
static void (* Timer1_ICU) (void ) =  Null;
/**************************************************************************
 * Functions
 *
 **************************************************************************/

void Timer_1_Init (Prescaler_Modes scaler, Timer1_Mode Form_Mode,Timer1_OCA_B OCA_MODE,Timer1_OCA_B OCB_MODE){



	//Set The Wave Generation Mode

	switch (Form_Mode){
	case Normal_Mode :
		Clear_Bit(Timer1_TCCR1A, WGM10);
		Clear_Bit(Timer1_TCCR1A, WGM11);
		Clear_Bit(Timer1_TCCR1B, WGM12);
		Clear_Bit(Timer1_TCCR1B, WGM13);
		break;

	case PWM_PhaseCorrect :

		Set_Bit(Timer1_TCCR1A,   WGM10);
		Set_Bit(Timer1_TCCR1A,   WGM11);
		Clear_Bit(Timer1_TCCR1B, WGM12);
		Clear_Bit(Timer1_TCCR1B, WGM13);

		break;

	case CTC_ICR1 :

		Clear_Bit(Timer1_TCCR1A, WGM10);
		Clear_Bit(Timer1_TCCR1A, WGM11);
		Set_Bit(Timer1_TCCR1B,   WGM12);
		Set_Bit(Timer1_TCCR1B,   WGM13);

		break;

	case PWM_Phase_Frequency_Correct_ICR1:

		Clear_Bit(Timer1_TCCR1A, WGM10);
		Clear_Bit(Timer1_TCCR1A, WGM11);
		Clear_Bit(Timer1_TCCR1B, WGM12);
		Set_Bit(Timer1_TCCR1B,   WGM13);

		break;

	case PWM_PhaseCorrect_ICR1:

		Clear_Bit(Timer1_TCCR1A, WGM10);
		Set_Bit(Timer1_TCCR1A,   WGM11);
		Clear_Bit(Timer1_TCCR1B, WGM12);
		Set_Bit(Timer1_TCCR1B,   WGM13);

		break ;

	case FastPWM_ICR1A:

		Clear_Bit(Timer1_TCCR1A, WGM10);
		Set_Bit(Timer1_TCCR1A,   WGM11);
		Set_Bit(Timer1_TCCR1B,   WGM12);
		Set_Bit(Timer1_TCCR1B,   WGM13);

		break ;
	}
	// Set The Pre-scaler
	// The register of the pre-scaler is TCCR1B
	Timer1_TCCR1B &= Timre1_Prescaler_Mask;
	Timer1_TCCR1B |= scaler;

	switch (OCA_MODE){

	case OC_DISCONNECTED:

		Clear_Bit(Timer1_TCCR1A,COM1A0);
		Clear_Bit(Timer1_TCCR1A,COM1A1);

		break;

	case Toggle_OC:

		Set_Bit(Timer1_TCCR1A,COM1A0);
		Clear_Bit(Timer1_TCCR1A,COM1A1);

		break;

	case NonInverting_OC:

		Clear_Bit(Timer1_TCCR1A,COM1A0);
		Set_Bit(Timer1_TCCR1A,COM1A1);

		break;

	case Inverting_OC :

		Set_Bit(Timer1_TCCR1A,COM1A0);
		Set_Bit(Timer1_TCCR1A,COM1A1);

		break ;
	}

	switch (OCB_MODE){

	case OC_DISCONNECTED:

		Clear_Bit(Timer1_TCCR1A,COM1B0);
		Clear_Bit(Timer1_TCCR1A,COM1B1);

		break;

	case Toggle_OC:

		Set_Bit(Timer1_TCCR1A,COM1B0);
		Clear_Bit(Timer1_TCCR1A,COM1B1);

		break;

	case NonInverting_OC:

		Clear_Bit(Timer1_TCCR1A,COM1B0);
		Set_Bit(Timer1_TCCR1A,COM1B1);

		break;

	case Inverting_OC :

		Set_Bit(Timer1_TCCR1A,COM1B0);
		Set_Bit(Timer1_TCCR1A,COM1B1);

		break ;
	}

}
void PWM_Init (void ){


	Timer_1_Init(CLK_8, FastPWM_ICR1A, NonInverting_OC	, OC_DISCONNECTED);


}



void ICU_Init (u8 Copy_Trigger_Edge){

	switch (Copy_Trigger_Edge){

	case Rising_Edge :

		Set_Bit(Timer1_TCCR1B , ICES1);

		break;


	case Falling_Edge:

		Clear_Bit(Timer1_TCCR1B , ICES1);

		break;

	}

}


/*******************************
 * Enables
 ******************************/
void Timer1_OVF_ENB (void){

	Set_Bit(Timer0_TIMSK, TOIE1);

}

void Timer1_OVF_DIS (void){

	Clear_Bit(Timer0_TIMSK, TOIE1);
}

void Timer1_OCA_ENB (void){

	Set_Bit(Timer0_TIMSK, OCIE1A);
}

void Timer1_OCA_DIS (void){

	Set_Bit(Timer0_TIMSK, OCIE1B);
}

void Timer1_OCB_ENB (void ){

	Set_Bit(Timer0_TIMSK, OCIE1B);

}


void Timer1_OCB_DIS (void ){

	Clear_Bit(Timer0_TIMSK, OCIE1B);

}

void Timer1_ICU_ENB (void){

	Set_Bit(Timer0_TIMSK , TICIE1);

}

void Timer1_ICU_DIS (void){

	Clear_Bit(Timer0_TIMSK , TICIE1);

}

/*******************************************
 * Callback Functions
 *******************************************/

void Timer1_OVF_Callback (void (*Local_PTR)(void)){

	Timer1_OVF = Local_PTR ;

}

void TImer1_OCA_Callback (void (*Local_PTR)(void)){

	Timer1_OCA = Local_PTR;

}

void Timer1_ICU_Callback (void (*Local_PTR)(void)){

	Timer1_ICU = Local_PTR;
}

/*************************************************
 *
 * ISR
 **************************************************/

void __vector_6(void)__attribute__((signal));
void __vector_6(){

	if (Timer1_ICU!= Null){

		Timer1_ICU ();
	}
}

void __vector_7(void)__attribute__((signal));
void __vector_7(){

	if (Timer1_OCA!= Null){

		Timer1_OCA ();
	}
}

void __vector_9(void)__attribute__((signal));
void __vector_9(){

	if (Timer1_OVF!= Null){

		Timer1_OVF ();
	}
}


/*Service Function*/
void PWM_Freq_KHZ (u16 Freq, u8 DutyCycle){

	u16 TimeInMicro ;
	TimeInMicro = 1000 / Freq ;

	if (TimeInMicro == 0)
	{

	}

	else if (TimeInMicro >= 1){

		Timer1_u16_ICR1 = TimeInMicro - 1 ;
	}
	else {
		Timer1_u16_ICR1 = 0;
	}

	if (DutyCycle <=100){

		Timer1_u16_OCR1A = (((DutyCycle /100) * TimeInMicro) -1);
	}
}

