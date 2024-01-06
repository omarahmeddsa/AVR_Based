/*
 * EXTI.c
 *
 *  Created on: Dec 10, 2023
 *      Author: omar
 */

/********************************************************
 * Includes
 ********************************************************/
#include "MemoryMap.h"
#include "Macros.h"
#include "STD_TYPES.h"
#include "Bit_calc.h"
#include "EXIT.h"
/*********************************************************
 * Definitions
 *********************************************************/

/*********************************************************
 * Global Variables
 **********************************************************/
static void (*INT0_FPTR)(void) = Null;
static void (*INT1_FPTR)(void) = Null;
static void (*INT2_FPTR)(void) = Null;
/***********************************************************
 * Functions Implemantaion
 ************************************************************/

void EXTI_Init (u8 Copy_INTx)
{

		switch ( Copy_INTx){

		case INT0 :
			Set_Bit(EXTI_GICR,INT0);
			break;

		case INT1 :
			Set_Bit(EXTI_GICR,INT1);
			break;

		case INT2 :
			Set_Bit(EXTI_GICR,INT2);
			break;
		}
}

void EXTI_Line_Disable  (u8 Copy_INTx) {

	switch ( Copy_INTx){

			case INT0 :
				Clear_Bit(EXTI_GICR,INT0);
				break;

			case INT1 :
				Clear_Bit(EXTI_GICR,INT1);
				break;

			case INT2 :
				Clear_Bit(EXTI_GICR,INT2);
				break;
			}
}

void EXTI_SenseCTRL (u8 Copy_SenseMode, u8 Copy_Line) {

	switch (Copy_Line){
	case INT0:
		Assign_Bit(EXTI_MCUCR, ISC00,Get_Bit(Copy_SenseMode, 0));
		Assign_Bit(EXTI_MCUCR, ISC01,Get_Bit(Copy_SenseMode, 1));
		break;

	case INT1:
		Assign_Bit(EXTI_MCUCR, ISC10,Get_Bit(Copy_SenseMode, 0));
		Assign_Bit(EXTI_MCUCR, ISC11,Get_Bit(Copy_SenseMode, 1));
		break;

	case INT2 :
		Assign_Bit(EXTI_MCUCR, EXTI_ISC2,Get_Bit(Copy_SenseMode, 0));
		break;
	}
}
/****************************************************************************
 *
 *Callback Function
 ****************************************************************************/

void Callback_INT0 (u8 Init_Line,void (* Local_PTR)(void )){

	switch (Init_Line){

	case INT0 :
	INT0_FPTR = Local_PTR;
	break;

	case INT1 :
	INT1_FPTR = Local_PTR;
	break;

	case INT2 :
	INT2_FPTR = Local_PTR;
	break;

	}

}

/******************************************************************************
 * ISR Functions
*******************************************************************************/

void __vector_1(void)__attribute__((signal));
void __vector_1(){

	if (INT0_FPTR != Null){
		INT0_FPTR();
	}
}

void __vector_2(void)__attribute__((signal));
void __vector_2(){

	if (INT1_FPTR != Null){
		INT1_FPTR();
	}
}

void __vector_3(void)__attribute__((signal));
void __vector_3(){

	if (INT2_FPTR != Null){
		INT2_FPTR();
	}
}
