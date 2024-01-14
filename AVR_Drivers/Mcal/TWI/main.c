/*
 * main.c
 *
 *  Created on: Nov 4, 2023
 *      Author: omar
 */

/*IN this Project we are communicating between Atmega 32 and  PCF8574 (IC) as the Slave  */

#include "Bit_calc.h"
#include "STD_TYPES.h"
#include "Dio_Private.h"
#include "Dio_Config.h"
#include "Dio_Interface.h"
#include "TWI_private.h"
#include "TWI_Config.h"
#include "TWI_Interface.h"
#include "avr/delay.h"

#define SLAVE_PCF8574_Address 0x20

int main (void ){

	TWI_MasterInit();
	TWI_StartCondation();
	TWI_SendSlaveAddress_Write (SLAVE_PCF8574_Address); /*the adress of the slave */

	while (1){

		TWI_SendDataByte('O');
		_delay_ms(1000);
		TWI_SendDataByte(0x00);
		_delay_ms(1000);

	}

	return 0 ;
}
