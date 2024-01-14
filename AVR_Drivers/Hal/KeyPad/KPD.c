/*
 * KPD.c
 *
 *  Created on: Oct 27, 2023
 *      Author: omar
 */




#include "Bit_calc.h"
#include "STD_TYPES.h"
#include "Dio_Private.h"
#include "Dio_Config.h"
#include "Dio_Interface.h"
#include "LCD_Interface.h"
#include "LCD_Config.h"
#include "avr/delay.h"
#include "KPD.h"


u8 KPD_u8Buttons[4][4] = { {'7','8','9','/'}, /* Row0 */
						   {'4','5','6','*'}, /* Row1 */
						   {'1','2','3','-'}, /* Row2 */
						   {'?','0','=','+'}  /* Row3 */};


void KPD_Init (void ) {

	Dio_u8_SetPinDir(KPD_PORT, KPD_Row0, Dio_PinInput);
	Dio_u8_SetPinDir(KPD_PORT, KPD_Row1, Dio_PinInput);
	Dio_u8_SetPinDir(KPD_PORT, KPD_Row2, Dio_PinInput);
	Dio_u8_SetPinDir(KPD_PORT, KPD_Row3, Dio_PinInput);

	Dio_u8_SetPinVal(KPD_PORT, KPD_Row0, Dio_PinHigh);
	Dio_u8_SetPinVal(KPD_PORT, KPD_Row1, Dio_PinHigh);
	Dio_u8_SetPinVal(KPD_PORT, KPD_Row2, Dio_PinHigh);
	Dio_u8_SetPinVal(KPD_PORT, KPD_Row3, Dio_PinHigh);

	Dio_u8_SetPinDir(KPD_PORT, KPD_Col0, Dio_PinOutput);
	Dio_u8_SetPinDir(KPD_PORT, KPD_Col1, Dio_PinOutput);
	Dio_u8_SetPinDir(KPD_PORT, KPD_Col2, Dio_PinOutput);
	Dio_u8_SetPinDir(KPD_PORT, KPD_Col3, Dio_PinOutput);

	Dio_u8_SetPinVal(KPD_PORT, KPD_Col0, Dio_PinHigh);
	Dio_u8_SetPinVal(KPD_PORT, KPD_Col1, Dio_PinHigh);
	Dio_u8_SetPinVal(KPD_PORT, KPD_Col2, Dio_PinHigh);
	Dio_u8_SetPinVal(KPD_PORT, KPD_Col3, Dio_PinHigh);

}

u8 KPD_PRESSED (void ) {

	u8 Loc_Returndata = '\0';
	u8 Loc_Getpressed ;
	u8 Row_Count ;
	u8 Col_count ;

	for (Col_count = KPD_COL_INIT ;Col_count  < KPD_COL_END +1  ; Col_count ++ ){

		Dio_u8_SetPinVal(KPD_PORT, Col_count, Dio_PinLow);

		for (Row_Count = KPD_ROW_INIT ; Row_Count < KPD_ROW_END +1 ; Row_Count ++ ){


			Loc_Getpressed = Dio_u8_GetPinVal(KPD_PORT, Row_Count);

			if (Loc_Getpressed == 0){
				_delay_ms(50);
				Loc_Getpressed = Dio_u8_GetPinVal(KPD_PORT, Row_Count);
				if (Loc_Getpressed == 0){
					Loc_Returndata = KPD_u8Buttons [Row_Count - KPD_ROW_INIT][Col_count - KPD_COL_INIT];
				}
				Loc_Getpressed = Dio_u8_GetPinVal(KPD_PORT, Row_Count);
				while (Dio_PinLow == Loc_Getpressed){
					Loc_Getpressed = Dio_u8_GetPinVal(KPD_PORT, Row_Count);
				}
				break ;
			}
		}
		Dio_u8_SetPinVal(KPD_PORT, Col_count, Dio_PinHigh);

	}
	return Loc_Returndata;



}
