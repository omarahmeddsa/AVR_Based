/*
 * LDR_Interface.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_

/*--------------------------------------------------------------------------------------------*/
/*   INCLUDES   */
/*--------------------------------------------------------------------------------------------*/
#include "STD.h"
#include "DIO_Interface.h"
#include <util/delay.h>





/*--------------------------------------------------------------------------------------------*/
/* LCD Cursor */
/*--------------------------------------------------------------------------------------------*/
typedef enum{
	LCD_ROW_1,
	LCD_ROW_2,
	LCD_ROW_3,
	LCD_ROW_4

}LCD_ROW;

typedef enum{
	LCD_COL_01,
	LCD_COL_02,
	LCD_COL_03,
	LCD_COL_04,
    LCD_COL_05,
	LCD_COL_06,
	LCD_COL_07,
	LCD_COL_08,
	LCD_COL_09,
	LCD_COL_10,
	LCD_COL_11,
	LCD_COL_12,
	LCD_COL_13,
	LCD_COL_14,
	LCD_COL_15,
	LCD_COL_16,
	LCD_COL_17,
	LCD_COL_18,
	LCD_COL_19,
	LCD_COL_20
}LCD_COL;


/*--------------------------------------------------------------------------------------------*/
/*   PROTOTYPES   */
/*--------------------------------------------------------------------------------------------*/
void H_Lcd_Void_LCDInit(void);
void H_Lcd_Void_LCDWriteCharacter(u8);
void H_Lcd_Void_LCDWriteCommand(u8);
void H_Lcd_Void_LCDWriteString(u8*);
void H_Lcd_Void_LCDClear(void);
void H_Lcd_Void_LCDWriteNumber(s32);
void H_Lcd_Void_LCDGoTo(u8,u8);

#endif /* HAL_LCD_LCD_INTERFACE_H_ */
