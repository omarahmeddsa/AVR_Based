#ifndef LCD_INT_H
#define LCD_INT_H
/**************************************
 define macros to the data port of LCD
 **************************************/
#define LCD_PORT_DATA		DIO_PORTB
/**************************************
 define macros to the Control port of LCD
 **************************************/
#define LCD_PORT_CONTROL 	DIO_PORTD
/************************************
 define the pin numbers for the control
 ************************************/
#define RS_PIN 				DIO_PIN4
#define RW_PIN 				DIO_PIN5
#define E_PIN 				DIO_PIN6
/************************************/


/*******************************************************
function decription
LCD intilization according to data sheet steps
********************************************************/
void HLCD_vInit(void);
/*******************************************************
function decription
this function send command to the LCD
********************************************************/
void HLCD_vSendCommand(u8 A_u8Cmd);
/*******************************************************
function decription
this function send the data to LCD
********************************************************/
void HLCD_vSendData(u8 A_u8Data);
/*******************************************************
function decription
this function send string to LCD
********************************************************/
void HLCD_vSendString(u8 *PA_u8String);
/*******************************************************
function decription
this function send clear command to LCD
********************************************************/
void HLCD_vClearScreen(void);
/*******************************************************
function decription
this function takes row and col of LCD and go to this specefic row and col
********************************************************/
void HLCD_vGoToRowCol(u8 A_u8Row, u8 A_u8Col);

#endif
