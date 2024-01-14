/*
 * I2C_Program.c
 *
 *  Created on: Jun 23, 2023
 *      Author: karim
 */
#include "STD_TYPES.h"
#include "BIT_CALC.h"
#include "I2C_Private.h"


void I2C_Master_Init(){

	TWSR = 0b00000000; //20 khz
	TWBR = 192;

}

u8 I2C_start(u8 slave_Address){

	 TWCR = 0b11100100; //start condition and enable I2C and clear flag enable acknowledge bit for master

	 while(Get_Bit(TWCR,7)==0);
	 u8 status = (TWSR & 0xF8); // mask 0b11111000 in hexa
	 if(status != 0x08){
		 return 1; // use macro defined for error value
	 }

	 Clear_Bit(TWCR,5);

	 //use function slave address select to select slave address read or write --optional--
	 TWDR = slave_Address;
	 Set_Bit(TWCR, 7); // clear flag  to start the next operation
	 while(Get_Bit(TWCR,7)==0);
	  status = (TWSR & 0xF8); // mask 0b11111000 in hexa
	 if(status != 0x18){
		 return 2; // use macro defined for error value
	   }else if(status == 0x20){
		 return 3;
	   }else if (status == 0x38){
		 return 4;
	   }

	 return 0; //success //another function for repeated start only difference in status

 }

u8 I2C_repeated_start(u8 slave_Address){

	 TWCR = 0b11100100; //start condition and enable I2C and clear flag enable acknowledge bit for master

	 while(Get_Bit(TWCR,7)==0);
	 u8 status = (TWSR & 0xF8); // mask 0b11111000 in hexa
	 if(status != 0x10){
		 return 1; // use macro defined for error value
	 }

	 Clear_Bit(TWCR,5);

	 //use function slave address select to select slave address read or write --optional--
	 TWDR = slave_Address;

	 // handles receive status

	 Set_Bit(TWCR, 7); // clear flag  to start the next operation
	 while(Get_Bit(TWCR,7)==0);
	  status = (TWSR & 0xF8); // mask 0b11111000 in hexa
	 if(status != 0x40){
		 return 2; // use macro defined for error value
	   }else if(status == 0x48){
		 return 3;
	   }else if (status == 0x38){
		 return 4;
	   }

	 return 0; //success //another function for repeated start only difference in status

 }


u8 I2C_Master_Transmit(u8 data ){

	TWDR = data; // load data in register

	Set_Bit(TWCR,7); // clear flag to start next job which is data transfer in frame
	while(Get_Bit(TWCR,7)==0);
	 u8 status = (TWSR & 0xF8); // mask 0b11111000 in hexa
	 if(status == 0x28) return 1;
	 else if(status == 0x30) return 2;
	 else if (status == 0x38) return 3;

	 return 0; //success

}

u8 I2C_Master_Receive_Ack(){

	Set_Bit(TWCR,6);// ENABLE ACKNOWLEDGEMENT
	Set_Bit(TWCR,7); // NEXT step and clear flag

	while(Get_Bit(TWCR,7)==0);
	u8 status = (TWSR & 0xF8); // mask 0b11111000 in hexa
		 if(status == 0x50) return TWDR;

}
u8 I2C_Master_Receive_NOT_Ack(){

	Clear_Bit(TWCR,6);// ENABLE ACKNOWLEDGEMENT
	Set_Bit(TWCR,7); // NEXT step and clear flag

	while(Get_Bit(TWCR,7)==0);
	u8 status = (TWSR & 0xF8); // mask 0b11111000 in hexa
		 if(status == 0x58) return TWDR;
}

void I2C_Stop(){


	Set_Bit(TWCR,4);//STOP
	Set_Bit(TWCR,7); //clear flag

	while(Get_Bit(TWCR,4)==1); // wait for the stop condition to finish

}


void I2C_Slave_Init(u8 slave_Address){

	TWAR = slave_Address;
	TWCR = 0b11000100; // enable i2c -- clear flag  - enable acknowledgment


}



u8 I2C_Slave_Transmit(u8 data ){

	TWDR = data; // load data in register

	Set_Bit(TWCR,7); // clear flag to start next job which is data transfer in frame
	while(Get_Bit(TWCR,7)==0);
	 u8 status = (TWSR & 0xF8); // mask 0b11111000 in hexa
	 if(status == 0xB8) return 1;
	 else if(status == 0xC0) return 2;
	 else if (status == 0xC8) return 3;

	 return 0; //success

}


I2C_Slave_Listen(){
	while(1){
	while(Get_Bit(TWCR,7) == 0);
	 u8 status = (TWSR & 0xF8);
	 if(status == 0x60|| status == 0x68)return 1; // case recieve from master
	 if(status == 0xA8 || status == 0xB0)return 2; // case transmit to master
	 if(status == 0x70|| status == 0x78)return 3; // case recieve from master general call
	}
}
