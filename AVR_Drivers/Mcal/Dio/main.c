/*
 * main.c
 *
 *  Created on: Dec 5, 2023
 *      Author: omar
 */
#include "Bit_calc.h"
#include "Macros.h"
#include "MemoryMap.h"
#include "STD_TYPES.h"
#include "Dio.h"
#include "avr/delay.h"

int main (void){
	Dio_u8_SetPinDir(Group_A, PIN0, Dio_PinOutput);
	while (1){

	Dio_u8_SetPinVal(Group_A, PIN0, Dio_PinHigh	);
	_delay_ms(1000);
	Dio_u8_SetPinVal(Group_A, PIN0, Dio_PinLow);
	_delay_ms(1000);

	}
}
