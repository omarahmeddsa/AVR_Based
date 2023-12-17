#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "LCD_int.h"
#include "DIO_int.h"
#include <util/delay.h>

/*********************************************
 function implementation
 this function send the command to the LCD
 ********************************************/
void HLCD_vSendCommand(u8 A_u8Cmd) {
	/* Control RS and RW Pins */
	DIO_vSetPinVal(LCD_PORT_CONTROL, RS_PIN, DIO_LOW);
	DIO_vSetPinVal(LCD_PORT_CONTROL, RW_PIN, DIO_LOW);
	
	/* Write Command on the data pins */
	DIO_vSetPinVal(LCD_PORT_CONTROL, E_PIN, DIO_HIGH);
	_delay_us(100);
	DIO_vSetPortVal(LCD_PORT_DATA, A_u8Cmd);
	_delay_us(100);
	DIO_vSetPinVal(LCD_PORT_CONTROL, E_PIN, DIO_LOW);
	_delay_us(100);
	
}
/*********************************************
 function implementation
 this function send the data the LCD
 ********************************************/
void HLCD_vSendData(u8 A_u8Data) {
	/* Control RS and RW Pins */
	DIO_vSetPinVal(LCD_PORT_CONTROL, RS_PIN, DIO_HIGH);
	DIO_vSetPinVal(LCD_PORT_CONTROL, RW_PIN, DIO_LOW);
	
	/* Write Command on the data pins */
	DIO_vSetPinVal(LCD_PORT_CONTROL, E_PIN, DIO_HIGH);
	_delay_us(100);
	DIO_vSetPortVal(LCD_PORT_DATA, A_u8Data);
	_delay_us(100);
	DIO_vSetPinVal(LCD_PORT_CONTROL, E_PIN, DIO_LOW);
	_delay_us(100);

}
/*********************************************
 function implementation
 this function is to intilitze the LCD
 ********************************************/
void HLCD_vInit(void) {
	/* set Directionof data port pins and control port pins */
	DIO_vSetPortDir(LCD_PORT_DATA, 0xFF);
	DIO_vSetPinDir(LCD_PORT_CONTROL, RS_PIN, DIO_OUTPUT);
	DIO_vSetPinDir(LCD_PORT_CONTROL, RW_PIN, DIO_OUTPUT);
	DIO_vSetPinDir(LCD_PORT_CONTROL, E_PIN, DIO_OUTPUT);

	HLCD_vSendCommand(0x38); // FUNCTION SET COMMAND.
	HLCD_vSendCommand(0b00001100); // DISPLAY COMMAND
	HLCD_vSendCommand(0x01); // CLEAR COMMAND
}
/*********************************************
 function implementation
 this function send the string to LCD
 ********************************************/
void HLCD_vSendString(u8 *PA_u8String) {
	/*
	 * local varibaable to be counteed in while loop
	 */
	u8 L_u8I = 0;

	while(PA_u8String[L_u8I] != '\0') {
		/*
		 * loop tell see the null character and then stops
		 */
		HLCD_vSendData(PA_u8String[L_u8I]);
		L_u8I++;
	}
}
/*********************************************
 function implementation
 this function clear the LCD by sending clearing command to it
 ********************************************/
void HLCD_vClearScreen(void) {
	HLCD_vSendCommand(0x01);
}
/*********************************************
 function implementation
 this function takes row and col and then put cursior in this location
 ********************************************/
void HLCD_vGoToRowCol(u8 A_u8Row, u8 A_u8Col) {
	/*
	 * local variable to store the address
	 */
	u8 L_u8Address;
	/*
	 * switch case to see the row number
	 */
	switch(A_u8Row) {
	/*
	 * if zero execute this expression and if 1 excute this expression
	 */
		case 0:
			L_u8Address = A_u8Col + 0x00;
			break;
		case 1:
			L_u8Address = A_u8Col + 0x40;
			break;
	}
	/*
	 * send command after all
	 */
	HLCD_vSendCommand(L_u8Address | 0b10000000);
}

