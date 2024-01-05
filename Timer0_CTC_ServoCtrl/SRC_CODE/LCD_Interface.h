/*
 * LCD_Interface.h
 *
 *  Created on: Oct 25, 2023
 *      Author: omar
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_Send_Data(u8 Data );
void LCD_Send_Command (u8 Command );
void LCD_Send_FallingEdge ();
void LCD_4Bit_Init (void );
void lCD_SetPostion (u8 line , u8 x);
void LCD_Clear(void);

#endif /* LCD_INTERFACE_H_ */
