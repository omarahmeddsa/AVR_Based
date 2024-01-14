/*
 * EEPROM.h
 *
 *  Created on: Nov 16, 2023
 *      Author: omar
 */

#ifndef EEPROM_H_
#define EEPROM_H_

void EEPROM_write(u16 address,  u8 data );

u8 EEROM_Read (u16 Address);

#endif /* EEPROM_H_ */
