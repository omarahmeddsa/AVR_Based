/*
 * LED_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */


#include "LED_Interface.h"


void H_LED_Void_LedInit(u8 Copy_U8_Led)
{
	switch(Copy_U8_Led)
	{
	case LED0:
		M_DIO_Void_SetPinDirection(LED0_PIN,OUTPUT);
		break;
	case LED1:
		M_DIO_Void_SetPinDirection(LED1_PIN,OUTPUT);
		break;
	case LED2:
		M_DIO_Void_SetPinDirection(LED2_PIN,OUTPUT);
		break;
	case LED3:
		M_DIO_Void_SetPinDirection(LED3_PIN,OUTPUT);
		break;
	default:
		break;
	}
}
void H_LED_Void_LedSetOn(u8 Copy_U8_Led)
{
	switch(Copy_U8_Led)
	{
	case LED0: M_DIO_Void_SetPinValue(LED0_PIN,HIGH); break;
	case LED1: M_DIO_Void_SetPinValue(LED1_PIN,HIGH); break;
	case LED2: M_DIO_Void_SetPinValue(LED2_PIN,HIGH); break;
	case LED3: M_DIO_Void_SetPinValue(LED3_PIN,HIGH); break;
	default:                                          break;
	}
}
void H_LED_Void_LedSetOff(u8 Copy_U8_Led)
{
	switch(Copy_U8_Led)
	{
	case LED0: M_DIO_Void_SetPinValue(LED0_PIN,LOW); break;
	case LED1: M_DIO_Void_SetPinValue(LED1_PIN,LOW); break;
	case LED2: M_DIO_Void_SetPinValue(LED2_PIN,LOW); break;
	case LED3: M_DIO_Void_SetPinValue(LED3_PIN,LOW); break;
	default:                                         break;
	}
}


void H_LED_Void_LedToggle(u8 Copy_U8_Led)
{
    u8 current_state = M_DIO_Void_GetPinValue(Copy_U8_Led);

    if (current_state == HIGH)
    {
        H_LED_Void_LedSetOff(Copy_U8_Led);
    }
    else if (current_state == LOW)
    {
        H_LED_Void_LedSetOn(Copy_U8_Led);
    }
}

