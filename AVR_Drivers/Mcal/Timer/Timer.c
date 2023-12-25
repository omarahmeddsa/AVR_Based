/*
 * Timer.c
 *
 *  Created on: Dec 18, 2023
 *      Author: omar
 */
/***************************************************************************************
 * Micro_controller : At-mega 32 8-bit
 * Module : Timers
 * Description : This module contain Functions to help interface with Timer0 and Timer1 Register
 *
 *******************************************************************************************/

/***************************************************************************************
 * Includes
 *
 ***************************************************************************************/

#include "Bit_calc.h"
#include "STD_TYPES.h"
#include "Macros.h"
#include "MemoryMap.h"
#include "Dio.h"
#include "Timer.h"

/****************************************************************************************
 * Definitions
 *
 ****************************************************************************************/

/*****************************************************************************************
 * Implementation
 *
 ****************************************************************************************/
void Timer0_init (Timer0_Mode Mode , Timer0_Prescaler Scaler, OC0_Mode mode){

	switch (Mode){

	case Timer0_NormalMode :

		Clear_Bit(Timer0_TCCR0,WGM00);
		Clear_Bit(Timer0_TCCR0, WGM01);

		break ;

	case Timer0_PWM_PhaseCorrect :

		Set_Bit(Timer0_TCCR0 , WGM00);
		Clear_Bit(Timer0_TCCR0, WGM01);

		break;

	case Timer0_CTC :

		Clear_Bit(Timer0_TCCR0 , WGM00);
		Set_Bit(Timer0_TCCR0 , WGM01);

		break;

	case Timer0_FastPWM :

		 Set_Bit(Timer0_TCCR0 , WGM00);
		 Set_Bit(Timer0_TCCR0 , WGM01);

		break ;
	}
	/**Setting the Pre-scaler of the Clk**/

	Timer0_TCCR0 &= 0xF8;
	Timer0_TCCR0 |= Scaler;

	switch (mode) {

	case OC0_Disconnected:

		Clear_Bit(Timer0_TCCR0 , COM00);
		Clear_Bit(Timer0_TCCR0 , COM01);

		break;

	case Toggle_OC0 :

		Set_Bit(Timer0_TCCR0 , COM00);
		Clear_Bit(Timer0_TCCR0 , COM01);

		break ;

	case NonInverting_OC0 :

		Clear_Bit(Timer0_TCCR0 , COM00);
		Set_Bit(Timer0_TCCR0 , COM01);

		break;

	case Inverting_OC0 :

		Set_Bit(Timer0_TCCR0 , COM00);
		Set_Bit(Timer0_TCCR0 , COM01);

		break;
	}
}

void Timer0_OVF_Enable (void){

	Set_Bit(Timer0_TIMSK , Timer0_TOIE0);
}

void Timer0_OVF_Disable (void){

	Clear_Bit(Timer0_TIMSK , Timer0_TOIE0);
}

void Timer0_OC_Enable (void){

	Set_Bit(Timer0_TIMSK , Timer0_OCIE0);

}

void Timer0_OC_Disable (void){

	Clear_Bit(Timer0_TIMSK , Timer0_OCIE0);

}
