/*
 * LCD_Config.h
 *
 *  Created on: Aug 19, 2023
 *      Author: omar
 */




#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#define LCD_MODE   _4_Pins

#define _8_PINS_Mode   0
#define _4_PINS_Mode   1

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




#define LCD_Function_Set   0b00111000  											//2-Lines and 5x7
#define LCD_ON_OFF_Display 0b00001100											//Display ON, Cursor OFF
#define LCD_Display_clear  0b00000001
#define LCD_Entry_Set_Mode 0b00000110
#define LCD_First_Raw      0b10000000
#define LCD_Second_Raw     0xc0

#endif /* LCD_CONFIG_H_ */
