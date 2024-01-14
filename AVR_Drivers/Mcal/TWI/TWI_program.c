/*
 * TWI_program.c
 *
 *  Created on: Nov 4, 2023
 *      Author: omar
 */


#include "Bit_calc.h"
#include "STD_TYPES.h"
#include "Dio_Private.h"
#include "Dio_Config.h"
#include "Dio_Interface.h"
#include "TWI_private.h"
#include "TWI_Config.h"
#include "TWI_Interface.h"


u8 TWI_StartCondation (void ) {

	TWI_U8_TWCR = (1<< TWI_TWINT) | (1<< TWI_TWSTA)| (1 << TWI_TWEN);

	/*According to the manual TWINT for clearing the flag
	 * TWSTA for sending start condiation
	 * TWEN for enabling the TWI*/
	/*Polling over the flag */
	while (Get_Bit(TWI_U8_TWCR, TWI_TWINT)== 0);

	return 0 ;
}


void TWI_MasterInit (void ) {

	/*To Set The freq to 10KHZ
	 * we put the Value TWBR to 98 (0x62) */

	TWI_U8_TWBR = 98;

	/*Enable I2C*/

	Set_Bit(TWI_U8_TWCR, TWI_TWEN);

	/*Set prescaler to 1*/

	Clear_Bit(TWI_U8_TWSR , TWI_TWPS0);
	Clear_Bit(TWI_U8_TWSR , TWI_TWPS1);

}

u8 TWI_SendSlaveAddress_Write(u8 copyaddress) {

	/*the 7 bits is the address form bit 1 to bit 7
	 * and LSB bit for the operation R/W*/
	/*So we shift the address to the left */
	TWI_U8_TWDR = copyaddress << 1 ;

	/*Clear the flag and Enable The TWI*/
	Set_Bit(TWI_U8_TWCR , TWI_TWINT);
	Set_Bit(TWI_U8_TWCR , TWI_TWEN);

	/*Polling over the flag */
	while (Get_Bit(TWI_U8_TWCR, TWI_TWINT)== 0);

	return 0 ;
}

u8 TWI_SendSlaveAddress_Read(u8 copyaddress) {

	TWI_U8_TWDR = copyaddress << 1 ;
	Set_Bit(TWI_U8_TWDR, TWI_TWD0);

	/*Clear the flag and Enable The TWI*/
	Set_Bit(TWI_U8_TWCR , TWI_TWINT);
	Set_Bit(TWI_U8_TWCR , TWI_TWEN);
	/*Polling over the flag */
	while (Get_Bit(TWI_U8_TWCR, TWI_TWINT)== 0);

	return 0 ;
}

u8 TWI_SendDataByte (u8 Copy_Databyte) {

	/*Read the data in the register */
	TWI_U8_TWDR = Copy_Databyte;

	/*clear the Flag and enable the TWI*/
	Set_Bit(TWI_U8_TWCR, TWI_TWINT);/*Flag */
	Set_Bit(TWI_U8_TWCR , TWI_TWEN);/*Enable TWI*/

	/*Polling over Function*/

	while (Get_Bit(TWI_U8_TWCR, TWI_TWINT)== 0);

	return 0 ;
}

TWI_Err TWI_ReadDataByte (u8 * PTR_returned_Data) {

	/*Check the pointer*/
	u8 local_error = No_Error;
	TWI_U8_TWCR = (1<<TWI_TWEN) | (1<<TWI_TWINT);

	while (Get_Bit(TWI_U8_TWCR ,TWI_TWINT) == 0);

	if (PTR_returned_Data == Null){
		return NullpointerReturned;
	}
	else{
	/*Clear Flag */

	* PTR_returned_Data = TWI_U8_TWDR ;

	}
	return local_error ;
}


void TWI_SlaveInit (u8 CopyAddress) {

	/*Set the address of the slave */
	TWI_U8_TWAR = CopyAddress <<1 ;

	/*Enabe ACK  */

	Set_Bit(TWI_U8_TWCR, TWI_TWEA);


	/*Enable TWI*/
	Set_Bit(TWI_U8_TWCR, TWI_TWEN);
}

void TWI_StopCondation(void ) {
	/*Set stop bit on TWCR reg */
	Set_Bit(TWI_U8_TWCR,TWI_TWSTO);

	/*Clear Flag*/

	Set_Bit(TWI_U8_TWCR, TWI_TWINT);


}

