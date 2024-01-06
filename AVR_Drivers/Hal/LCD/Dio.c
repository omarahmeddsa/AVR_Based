/*
 * Dio.c
 *
 *  Created on: Dec 7, 2023
 *      Author: Omar
 */
/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <Dio.c>
 *       Module:  -
 *
 *  Description:  <This File contains API for GPIO Registers  >
 *  
 /*
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Dio.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Macros.h"
#include "Std_Types.h"
#include "Bit_calc.h"
#include "MemoryMap.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void Gobal_interrput_Enbale (void )
{
	Set_Bit(SREG,GobalInterrput_Pin);
}

void Gobal_interrput_Disable (void )
{
	Clear_Bit(SREG,GobalInterrput_Pin);
}
void Dio_u8_SetPortDir(u8 Copy_PortID, u8 Copy_PortDirc){

	if ((Copy_PortID <= Group_D )&& (Copy_PortID >= Group_A)){

		switch (Copy_PortID){

		case Group_A :
			DIO_U8_DDRA = Copy_PortDirc;
			break;

		case Group_B :
			DIO_U8_DDRB = Copy_PortDirc;
			break;

		case Group_C :
			DIO_U8_DDRC = Copy_PortDirc;
			break;

		case Group_D :
			DIO_U8_DDRD = Copy_PortDirc;
			break;
		}
	}
}

void Dio_u8_SetPortValue(u8 Copy_PortID,u8 Copy_PortValue) {

	if ((Copy_PortID <= Group_D )&& (Copy_PortID >= Group_A)){

		switch (Copy_PortID){

		case Group_A :
			DIO_U8_PORTA = Copy_PortValue;
			break;

		case Group_B :
			DIO_U8_PORTB = Copy_PortValue;
			break;

		case Group_C :
			DIO_U8_PORTC = Copy_PortValue;
			break;

		case Group_D :
			DIO_U8_PORTD = Copy_PortValue;
			break;
		}
	}
}

u8 Dio_u8_GetportValue(u8 Copy_PortID) {

	u8 Portvalue;

	if ((Copy_PortID <= Group_D )&& (Copy_PortID >= Group_A)){


		switch (Copy_PortID) {

		case Group_A:
			Portvalue= DIO_U8_PORTA;
			break;

		case Group_B:
			Portvalue= DIO_U8_PORTB;
			break;

		case Group_C:
			Portvalue= DIO_U8_PORTC;
			break;

		case Group_D:
			Portvalue= DIO_U8_PORTD;
			break;
		}
	}
	return Portvalue ;
}


void Dio_u8_SetPinDir(u8 Copy_PortID,u8 Copy_Bit_No ,u8 CopyPinDirc){

	if ((Copy_PortID <= Group_D )&& (Copy_PortID >= Group_A)){

		switch (Copy_PortID){

		case Group_A:
			Assign_Bit(DIO_U8_DDRA,Copy_Bit_No,CopyPinDirc);
			break;

		case Group_B:
			Assign_Bit(DIO_U8_DDRB,Copy_Bit_No,CopyPinDirc);
			break;

		case Group_C:
			Assign_Bit(DIO_U8_DDRC,Copy_Bit_No,CopyPinDirc);
			break;

		case Group_D :
			Assign_Bit(DIO_U8_DDRD,Copy_Bit_No,CopyPinDirc);
			break;
		}
	}
}


void Dio_u8_SetPinVal(u8 Copy_PortID,u8 Copy_Bit_No,u8 CopyPinVal){

	if ((Copy_PortID <= Group_D )&& (Copy_PortID >= Group_A)){

		switch (Copy_PortID){
		case Group_A:
			Assign_Bit(DIO_U8_PORTA,Copy_Bit_No,CopyPinVal);
			break;

		case Group_B:
			Assign_Bit(DIO_U8_PORTB,Copy_Bit_No,CopyPinVal);
			break;

		case Group_C:
			Assign_Bit(DIO_U8_PORTC,Copy_Bit_No,CopyPinVal);
			break;

		case Group_D:
			Assign_Bit(DIO_U8_PORTD,Copy_Bit_No,CopyPinVal);
			break;
		}
	}
}


u8 Dio_u8_GetPinVal(u8 Copy_PortID,u8 Copy_Bit_No){

	u8 BitValue;
	if ((Copy_PortID <= Group_D )&& (Copy_PortID >= Group_A)){

		switch (Copy_PortID){

		case Group_A:
			BitValue = Get_Bit(DIO_U8_PINA,Copy_Bit_No);
			break;

		case Group_B:
			BitValue = Get_Bit(DIO_U8_PINB,Copy_Bit_No);
			break;

		case Group_C:
			BitValue = Get_Bit(DIO_U8_PINC,Copy_Bit_No);
			break;

		case Group_D:
			BitValue = Get_Bit(DIO_U8_PIND,Copy_Bit_No);
			break;

		}
	}
return BitValue;
}

u8 Dio_u8_GetPortDir(u8 Copy_PortID){

	u8 PortDir ;
	if ((Copy_PortID <= Group_D )&& (Copy_PortID >= Group_A)){

		switch (Copy_PortID){

		case Group_A:
			PortDir = DIO_U8_DDRA;
			break;

		case Group_B:
			PortDir = DIO_U8_DDRB;
			break;

		case Group_C:
			PortDir = DIO_U8_DDRC;
			break;

		case Group_D:
			PortDir = DIO_U8_DDRD;
			break;
		}
	}
	return PortDir;
}

u8 Dio_u8_GetPinDir(u8 Copy_PortID,u8 Copy_Bit_NO){

	u8 PinDirc ;
	if ((Copy_PortID <= Group_D )&& (Copy_PortID >= Group_A)){

		switch (Copy_PortID){

		case Group_A:
			PinDirc = Get_Bit(DIO_U8_DDRA,Copy_Bit_NO);
			break ;

		case Group_B:
				PinDirc = Get_Bit(DIO_U8_DDRB,Copy_Bit_NO);
				break ;

		case Group_C:
				PinDirc = Get_Bit(DIO_U8_DDRC,Copy_Bit_NO);
				break ;

		case Group_D:
				PinDirc = Get_Bit(DIO_U8_DDRD,Copy_Bit_NO);
				break ;
		}

		}
	return 0 ;
	}

void Dio_Pullup (u8 CopyPort_ID, u8 Copy_BitNum)
{
	if ((CopyPort_ID <= Group_D )&& (CopyPort_ID >= Group_A)){

		switch (CopyPort_ID){

		case Group_A:

			Dio_u8_SetPinDir(Group_A, Copy_BitNum, Dio_PinInput);
			Dio_u8_SetPinVal(Group_A, Copy_BitNum,Dio_PinHigh);

			break;

		case Group_B:

			Dio_u8_SetPinDir(Group_B, Copy_BitNum, Dio_PinInput);
			Dio_u8_SetPinVal(Group_B, Copy_BitNum,Dio_PinHigh);

			break;

		case Group_C:

			Dio_u8_SetPinDir(Group_C, Copy_BitNum, Dio_PinInput);
			Dio_u8_SetPinVal(Group_C, Copy_BitNum,Dio_PinHigh);

			break;

		case Group_D:

			Dio_u8_SetPinDir(Group_D, Copy_BitNum, Dio_PinInput);
			Dio_u8_SetPinVal(Group_D, Copy_BitNum,Dio_PinHigh);

			break;
		}
	}
}


/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
