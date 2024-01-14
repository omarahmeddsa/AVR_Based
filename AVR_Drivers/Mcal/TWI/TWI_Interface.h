/*
 * TWI_Interface.h
 *
 *  Created on: Nov 4, 2023
 *      Author: omar
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_


typedef enum {

	NullpointerReturned ,
	No_Error,



}TWI_Err;


void TWI_MasterInit (void );

void TWI_SlaveInit (u8 CopyAddress);

u8 TWI_StartCondation(void );

u8 TWI_ReStartCondation (void );

void TWI_StopCondation(void );

u8 TWI_SendSlaveAddress_Write(u8 copyaddress);

u8 TWI_SendSlaveAddress_Read(u8 copyaddress);

u8 TWI_SendDataByte (u8 Copy_Databyte);

TWI_Err TWI_ReadDataByte (u8 * PTR_returned_Data);

u8 TWI_SLAVESendDataByte (u8 Copy_data);

u8 TWI_SLAVEReadDataByte (u8 * PTR_DataByte);




#endif /* TWI_INTERFACE_H_ */
