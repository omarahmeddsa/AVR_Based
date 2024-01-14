/*
 * EEPROM.c
 *
 *  Created on: Nov 16, 2023
 *      Author: omar
 */


#include "Bit_calc.h"
#include "STD_TYPES.h"
#include "Dio_Private.h"
#include "Dio_Config.h"
#include "Dio_Interface.h"
#include "LCD_Config.h"
#include "LCD_Interface.h"
#include "EEPROM.h"
#include "avr/io.h"


void EEPROM_write(u16 address, u8 data ) {

	EEARL = (u8) address;
	EEARH = (u8) (address >> 8 );

	EEDR = data;

	Set_Bit(EECR, EEMWE);

	Set_Bit(EECR, EEWE);

	while (Get_Bit(EECR, EEWE));


}


u8 EEROM_Read (u16 Address) {


	EEARL = (u8) Address;
	EEARH = (u8) (Address >> 8 );

	Set_Bit(EECR,EERE);

	return EEDR ;

}
