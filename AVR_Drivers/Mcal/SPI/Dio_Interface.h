/*
 * Dio_Interface.h
 *
 *  Created on: Jul 3, 2023
 *      Author: omar
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

														// Functions Prototypes


void Dio_u8_SetPortDir(u8 Copy_PortID, u8 CopyPortDirc);  	  /*Set all the pins in the selected Port to Input or Output*/
void Dio_u8_SetPortValue(u8 Copy_PortID, u8 Copy_PortValue);  /*Set all the pins in the selected Port to High or Low*/
u8 Dio_u8_GetPortValue(u8 Copy_PortID);
void Dio_u8_SetPinDir(u8 Copy_PortID,u8 Copy_Bit_No ,u8 CopyPinDirc);
void Dio_u8_SetPinVal(u8 Copy_PortID,u8 Copy_Bit_No,u8 CopyPinVal);
u8 Dio_u8_GetPinVal(u8 Copy_PortID,u8 Copy_Bit_No);
u8 Dio_u8_GetPortDir(u8 Copy_PortID);
u8 Dio_u8_GetPinDir(u8 Copy_PortID,u8 Copy_Bit_NO);
void Gobal_interrput_Enbale (void );
void Gobal_interrput_Disable (void );
																/*Macros*/
//
#define ENBALBE 1
#define DISABLE 0
//Pin Direction
#define Dio_PinInput  0
#define Dio_PinOutput 1

//Port Direction
#define Dio_PortInput  0
#define Dio_PortOutput 0xFF

//Port value
#define Dio_PortHigh 0xFF
#define Dio_PortLow 0

//Pin value
#define Dio_PinHigh 1
#define Dio_PinLow 0

// Groups Macros
#define Group_A 0
#define Group_B 1
#define Group_C 2
#define Group_D 3

// Port Macros
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3


// Pin Macros
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
/*Definations*/

/*Status Reg*/
#define GobalInterrput_Pin 7



#define Null (void*)0



#endif /* DIO_INTERFACE_H_ */
