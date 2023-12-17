#ifndef MCAL_DIO_INT_H
#define MCAL_DIO_INT_H
/*******************************************************/
/*
 * define macros to atmega32 ports
 */
#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3
/*******************************************************/
/*
 * define macros to atmega pin numbers
 */
#define DIO_PIN0  0
#define DIO_PIN1  1
#define DIO_PIN2  2
#define DIO_PIN3  3
#define DIO_PIN4  4
#define DIO_PIN5  5
#define DIO_PIN6  6
#define DIO_PIN7  7
/*******************************************************/
/*
 * define macros to output mood
 */
#define DIO_OUTPUT 1
#define DIO_INPUT  0
/*******************************************************/
/*
 * define macros for high and low moodes
 */
#define DIO_HIGH   1
#define DIO_LOW    0
/*******************************************************/
/*
 * function declerations for DIO driver
 */
/*******************************************************/
/*******************************************************
function decription
this function takes port no and pin not and direction mood
then process to this specific moood
********************************************************/
void DIO_vSetPinDir(u8 A_u8PortNo, u8 A_u8PinNo, u8 A_u8Dir);
/*******************************************************
function decription
this function takes port no and pin not and output mood
then process to this specific moood
********************************************************/
void DIO_vSetPinVal(u8 A_u8PortNo, u8 A_u8PinNo, u8 A_u8Val);
/*******************************************************
function decription
this function takes port no and pin not and return the value
of the specific in in this port
********************************************************/
u8 DIO_u8GetPinVal(u8 A_u8PortNo, u8 A_u8PinNo);
/*******************************************************
function decription
this function takes port no and direction mood
then process to this specific mood
********************************************************/
void DIO_vSetPortDir(u8 A_u8PortNo, u8 A_u8Dir);
/*******************************************************
function decription
this function takes port no and direction value
then process to this specific moood
********************************************************/
void DIO_vSetPortVal(u8 A_u8PortNo, u8 A_u8Val);
/*******************************************************
function decription
this function takes port no return back the value of the whole port
********************************************************/
u8 DIO_u8GetPortVal(u8 A_u8PortNo);


#endif
