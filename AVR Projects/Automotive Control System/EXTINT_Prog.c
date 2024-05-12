/*
 * EXTINT_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#include "LED_Interface.h"

#include "EXTINT_Interface.h"
#include "EXTINT_Private.h"


void(*ExtInt0_CallBack)(void);
void(*ExtInt1_CallBack)(void);
void(*ExtInt2_CallBack)(void);

void M_EXTINT_Void_EXTINTInit(u8 Copy_U8_ExtIntChannel)
{
	switch(Copy_U8_ExtIntChannel)
	{
	case INT0_CHANNEL:
#if   EXTINT0_SENSE_CONTROL   ==   EXT_INT_FALLING_EDGE
		CLR_BIT(MCUCR_REG,ISC00_BIT);
		SET_BIT(MCUCR_REG,ISC01_BIT);
#elif EXTINT0_SENSE_CONTROL   ==   EXT_INT_RISING_EDGE
		SET_BIT(MCUCR_REG,ISC00_BIT);
		SET_BIT(MCUCR_REG,ISC01_BIT);
#elif EXTINT0_SENSE_CONTROL   ==   EXT_INT_LOW_LEVEL
		CLR_BIT(MCUCR_REG,ISC00_BIT);
		CLR_BIT(MCUCR_REG,ISC01_BIT);
#elif EXTINT0_SENSE_CONTROL   ==   EXT_INT_ANY_LOGICAL_CHANGE
		SET_BIT(MCUCR_REG,ISC00_BIT);
		CLR_BIT(MCUCR_REG,ISC01_BIT);
#endif
		// to enable int0 local int
		SET_BIT(GICR_REG,INT0_BIT);
		break;
	case INT1_CHANNEL:
#if   EXTINT1_SENSE_CONTROL   ==   EXT_INT_FALLING_EDGE
		CLR_BIT(MCUCR_REG,ISC10_BIT);
		SET_BIT(MCUCR_REG,ISC11_BIT);
#elif EXTINT1_SENSE_CONTROL   ==   EXT_INT_RISING_EDGE
		SET_BIT(MCUCR_REG,ISC10_BIT);
		SET_BIT(MCUCR_REG,ISC11_BIT);
#elif EXTINT1_SENSE_CONTROL   ==   EXT_INT_LOW_LEVEL
		CLR_BIT(MCUCR_REG,ISC10_BIT);
		CLR_BIT(MCUCR_REG,ISC11_BIT);
#elif EXTINT1_SENSE_CONTROL   ==   EXT_INT_ANY_LOGICAL_CHANGE
		SET_BIT(MCUCR_REG,ISC10_BIT);
		CLR_BIT(MCUCR_REG,ISC11_BIT);
#endif
		// to enable int1 local int
		//SET_BIT(GICR_REG,INT1_BIT);
		break;
	case INT2_CHANNEL:
#if   EXTINT2_SENSE_CONTROL   ==   EXT_INT_FALLING_EDGE
		CLR_BIT(MCUCSR_REG,ISC2_BIT);
#elif EXTINT2_SENSE_CONTROL   ==   EXT_INT_RISING_EDGE
		SET_BIT(MCUCSR_REG,ISC2_BIT);
#endif
		// to enable int2 local int
		SET_BIT(GICR_REG,INT2_BIT);
		break;
	default:                                           break;
	}
}

void M_EXTINT_Void_SetCallBack(u8 Copy_U8_ExtIntChannel,void(*Copy_ptr)(void))
{
	switch(Copy_U8_ExtIntChannel)
	{
	case INT0_CHANNEL:ExtInt0_CallBack = Copy_ptr; break;
	case INT1_CHANNEL:ExtInt1_CallBack = Copy_ptr; break;
	case INT2_CHANNEL:ExtInt2_CallBack = Copy_ptr; break;
	default:                                       break;
	}
}
void EXINT1_Enable (void ){
	SET_BIT(GICR_REG,INT1_BIT);
}

void EXINT1_Disable (void ){
	CLR_BIT(GICR_REG,INT1_BIT);
}

ISR(INT0_vect)
{
	ExtInt0_CallBack();
}
ISR(INT1_vect)
{
	ExtInt1_CallBack();
}
ISR(INT2_vect)
{
	ExtInt2_CallBack();
}


void GIE_voidEnable(){
	SET_BIT(SREG,SREG_I);
}

void GIE_voidDisable(){
	CLR_BIT(SREG,SREG_I);
}


