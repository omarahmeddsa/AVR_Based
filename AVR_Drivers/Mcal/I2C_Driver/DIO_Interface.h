/*
 * DIO_Interface.h
 *
 *  Created on: May 9, 2023
 *      Author: user
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


u8 DIO_U8_Set_Pin_Value(u8 Copy_U8_Port_ID, u8 Copy_U8_Pin_ID, u8 Copy_U8_Pin_Val);
u8 DIO_U8_Set_Port_Value(u8 Copy_U8_Port_ID,u8 Copy_U8_Port_Value);


u8 DIO_U8_Set_Pin_Direction(u8 Copy_U8_Port_ID, u8 Copy_U8_Pin_ID, u8 Copy_U8_Pin_Dir);
u8 DIO_U8_Set_Port_Direction(u8 Copy_U8_Port_ID,u8 Copy_U8_Port_Dir);


u8 DIO_U8_Get_Pin_Value(u8 Copy_U8_Port_ID, u8 Copy_U8_Pin_ID);
u8 DIO_U8_Get_Port_Value(u8 Copy_U8_Port_ID,u8* Copy_U8_Port_Value);

u8 DIO_U8_Get_Pin_Direction(u8 Copy_U8_Port_ID, u8 Copy_U8_Pin_ID );
u8 DIO_U8_Get_Port_Direction(u8 Copy_U8_Port_ID);




// port define
#define GROUP_A 0
#define GROUP_B 1
#define GROUP_C 2
#define GROUP_D 3


// pin define
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

//pin direction define
#define INPUT 0
#define OUTPUT 1

//pin value define
#define LOW 0
#define HIGH 1

//invalid for error define
#define INVALID_PIN_VALUE 250
#define INVALID_PIN_ID 255
#define INVALID_PORT_ID 245


// warning no returning in non void function
#define Success 0



#endif /* DIO_INTERFACE_H_ */
