/*
 * LCD_Interface.h
 *
 *  Created on: Aug 19, 2023
 *      Author: omar
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


void LCD_8_bit_Init ();
void LCD_Send_Data (u8 Copy_u8_Data);
void LCD_Send_Commoand(u8 Copy_u8_Command);
void LCD_Display_Clear ();
void LCD_Send_FallingEdge () ;
void LCD_Send_String (const u8 * Copy_StringPTR);
void LCD_postion (u8 line, u8 x);
void LCD_WriteNumber(u32 Number);
#endif /* LCD_INTERFACE_H_ */
