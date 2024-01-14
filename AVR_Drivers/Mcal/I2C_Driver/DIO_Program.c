/*
 * DIO_Program.c
 *
 *  Created on: May 9, 2023
 *      Author: user
 */

#include "STD_TYPES.h"
#include "BIT_CALC.h"
#include "DIO_Config.h"
#include "DIO_Interface.h"
#include "DIO_Private.h"
#include <avr/delay.h>



u8 DIO_U8_Set_Pin_Value(u8 Copy_U8_Port_ID, u8 Copy_U8_Pin_ID, u8 Copy_U8_Pin_Val){
	if((Copy_U8_Pin_ID >=PIN0) && (Copy_U8_Pin_ID <=PIN7) && (Copy_U8_Port_ID <= GROUP_D) && (Copy_U8_Port_ID >= GROUP_A)){
		if((Copy_U8_Pin_Val == HIGH) || (Copy_U8_Pin_Val == LOW )){
			switch (Copy_U8_Port_ID){
			case GROUP_A:
				Assign_Bit(DIO_U8_PORTA,Copy_U8_Pin_ID,Copy_U8_Pin_Val);
				break;
			case GROUP_B:
				Assign_Bit(DIO_U8_PORTB,Copy_U8_Pin_ID,Copy_U8_Pin_Val);
				break;
			case GROUP_C:
				Assign_Bit(DIO_U8_PORTC,Copy_U8_Pin_ID,Copy_U8_Pin_Val);
				break;
			case GROUP_D:
				Assign_Bit(DIO_U8_PORTD,Copy_U8_Pin_ID,Copy_U8_Pin_Val);
				break;

			}
		}
		else{
			return INVALID_PIN_VALUE;
		}
	}
	else{
		return INVALID_PIN_ID;
	}
	return Success;
}


u8 DIO_U8_Get_Pin_Value(u8 Copy_U8_Port_ID, u8 Copy_U8_Pin_ID){
	u8 pin_value;
	if ((Copy_U8_Port_ID <= GROUP_D) && (Copy_U8_Port_ID >= GROUP_A)){
		if((Copy_U8_Pin_ID >=PIN0) && (Copy_U8_Pin_ID <=PIN7) ){
			switch(Copy_U8_Port_ID){
			case GROUP_A:
				pin_value = Get_Bit(DIO_U8_PINA,Copy_U8_Pin_ID);
				break;
			case GROUP_B:
				pin_value = Get_Bit(DIO_U8_PINB,Copy_U8_Pin_ID);
				break;
			case GROUP_C:
				pin_value = Get_Bit(DIO_U8_PINC,Copy_U8_Pin_ID);
				break;
			case GROUP_D:
				pin_value = Get_Bit(DIO_U8_PIND,Copy_U8_Pin_ID);
				break;
			}
		}
		else{
			return INVALID_PIN_ID;
		}
	}
	else{
		return INVALID_PORT_ID;
	}
	return pin_value;
}

u8 DIO_U8_Set_Pin_Direction(u8 Copy_U8_Port_ID, u8 Copy_U8_Pin_ID, u8 Copy_U8_Pin_Dir){
	if( (Copy_U8_Port_ID <= GROUP_D) && (Copy_U8_Port_ID >= GROUP_A)){
		if((Copy_U8_Pin_ID >=PIN0) && (Copy_U8_Pin_ID <=PIN7)){
			switch (Copy_U8_Port_ID){
			case GROUP_A:
				Assign_Bit(DIO_U8_DDRA,Copy_U8_Pin_ID,Copy_U8_Pin_Dir);
				break;
			case GROUP_B:
				Assign_Bit(DIO_U8_DDRB,Copy_U8_Pin_ID,Copy_U8_Pin_Dir);
				break;
			case GROUP_C:
				Assign_Bit(DIO_U8_DDRC,Copy_U8_Pin_ID,Copy_U8_Pin_Dir);
				break;
			case GROUP_D:
				Assign_Bit(DIO_U8_DDRD,Copy_U8_Pin_ID,Copy_U8_Pin_Dir);
				break;
			}
		}
		else{
			return INVALID_PIN_ID;
		}

	}
	else{
		return INVALID_PORT_ID;
	}
	return Success;

}

u8 DIO_U8_Set_Port_Direction(u8 Copy_U8_Port_ID,u8 Copy_U8_Port_Dir){
	if((Copy_U8_Port_ID <= GROUP_D) && (Copy_U8_Port_ID >= GROUP_A)){
		switch(Copy_U8_Port_ID){
		case GROUP_A:
			DIO_U8_DDRA = Copy_U8_Port_Dir;
			break;
		case GROUP_B:
			DIO_U8_DDRB = Copy_U8_Port_Dir;
			break;
		case GROUP_C:
			DIO_U8_DDRC = Copy_U8_Port_Dir;
			break;
		case GROUP_D:
			DIO_U8_DDRD = Copy_U8_Port_Dir;
			break;
		}
	}
	else{
		return INVALID_PORT_ID;
	}
	return Success;
}

u8 DIO_U8_Set_Port_Value(u8 Copy_U8_Port_ID,u8 Copy_U8_Port_Value){   //lw 3aiz a4t8al 3la al value bta3t al port kolo;
	if((Copy_U8_Port_ID <= GROUP_D) && (Copy_U8_Port_ID >= GROUP_A)){
		switch(Copy_U8_Port_ID){
		case GROUP_A:
			DIO_U8_PORTA = Copy_U8_Port_Value;
			break;
		case GROUP_B:
			DIO_U8_PORTB = Copy_U8_Port_Value;
			break;
		case GROUP_C:
			DIO_U8_PORTC = Copy_U8_Port_Value;
			break;
		case GROUP_D:
			DIO_U8_PORTD = Copy_U8_Port_Value;
			break;
		}
	}
	else{
		return INVALID_PORT_ID;
	}

	return Success;
}

u8 DIO_U8_Get_Pin_Direction(u8 Copy_U8_Port_ID, u8 Copy_U8_Pin_ID ){
	u8 Pin_direction;

	if ((Copy_U8_Port_ID <= GROUP_D) && (Copy_U8_Port_ID >= GROUP_A)){
		switch(Copy_U8_Port_ID){
		case GROUP_A:
			Pin_direction = Get_Bit(DIO_U8_DDRA,Copy_U8_Pin_ID);
			break;
		case GROUP_B:
			Pin_direction = Get_Bit(DIO_U8_DDRB,Copy_U8_Pin_ID);
			break;
		case GROUP_C:
			Pin_direction = Get_Bit(DIO_U8_DDRC,Copy_U8_Pin_ID);
			break;
		case GROUP_D:
			Pin_direction = Get_Bit(DIO_U8_DDRD,Copy_U8_Pin_ID);
			break;
		}
	}
	else{
		return INVALID_PORT_ID;
	}
	return Pin_direction;
}

u8 DIO_U8_Get_Port_Direction(u8 Copy_U8_Port_ID){
	u8 port_direction;
	if((Copy_U8_Port_ID <= GROUP_D) && (Copy_U8_Port_ID >= GROUP_A)){
		switch(Copy_U8_Port_ID){
		case GROUP_A:
			port_direction = DIO_U8_DDRA;
			break;
		case GROUP_B:
			port_direction = DIO_U8_DDRB;
			break;
		case GROUP_C:
			port_direction = DIO_U8_DDRC;
			break;
		case GROUP_D:
			port_direction = DIO_U8_DDRD;
			break;

		}
	}
	else{
		return INVALID_PORT_ID;
	}

	return port_direction;
}


// get port value_U8_PINB = port_direction

u8 DIO_U8_Get_Port_Value(u8 Copy_U8_Port_ID,u8* Copy_U8_Port_Value){
	if((Copy_U8_Port_ID <= GROUP_D) && (Copy_U8_Port_ID >= GROUP_A)){
		switch(Copy_U8_Port_ID){
			case GROUP_A:
				*Copy_U8_Port_Value = DIO_U8_PINA;
				break;
			case GROUP_B:
				*Copy_U8_Port_Value = DIO_U8_PINB;
				break;
			case GROUP_C:
				*Copy_U8_Port_Value = DIO_U8_PINC;
				break;
			case GROUP_D:
				*Copy_U8_Port_Value = DIO_U8_PIND;
				break;
		}

	}
	else{
		return INVALID_PORT_ID;
	}
	return 0;
}

