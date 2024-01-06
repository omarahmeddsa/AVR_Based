/*
 * LCD.h
 *
 *  Created on: Jan 6, 2024
 *      Author: omar
 */

#ifndef LCD_H_
#define LCD_H_

/********************************************************
 *
 * Configures For LCD
 *
 -LCD 8-bit Mode
 -LCD 4-bit Mode
 *
 *
 **********************************************************/
/*********************************************************
 *
 * Enums
 *********************************************************/
typedef enum {

	LCD_4Bit_mode,
	LCD_8Bit_mode

}LCD_Config;


#define LCD_CTR_Port Group_B

typedef enum {

	LCD_RS = 5,
	LCD_RW ,
	LCD_ENB ,

}CTR_PINS;




#define  LCD_Data_Port Group_C

typedef enum {

	LCD_D0 = 0,
	LCD_D1 ,
	LCD_D2 ,
	LCD_D3 ,
	LCD_D4 ,
	LCD_D5 ,
	LCD_D6 ,
	LCD_D7 ,

}Data_PINS;



/*********************************************************
 *
 * LCD Mode Configuration
 ********************************************************/
#define LCD_MODE     LCD_8Bit_mode   // LCD Mode

/*************************************************************
 * Macros
 *************************************************************/
//8-bit mode Masks
#define LCD_Function_Set   0b00111000  											//2-Lines and 5x7
#define LCD_ON_OFF_Display 0b00001100											//Display ON, Cursor OFF
#define LCD_Display_clear  0b00000001
#define LCD_Entry_Set_Mode 0b00000110
#define LCD_First_Raw      0b10000000
#define LCD_Second_Raw     0xc0
/*************************************************************
 * Prototypes
 ************************************************************/
void LCD_Send_FallingEdge (void);
void LCD_Send_Data (u8 Copy_u8_Data);
void LCD_Send_Commoand(u8 Copy_u8_Command);
void LCD_Init (void);
void LCD_Display_Clear ();
void lCD_SetPostion (u8 line , u8 x);
void LCD_WriteNumber(u32 Number);


#endif /* LCD_H_ */
