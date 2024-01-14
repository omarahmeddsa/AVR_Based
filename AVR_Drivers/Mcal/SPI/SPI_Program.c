/*
 * SPI_Program.c
 *
 *  Created on: Oct 30, 2023
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
#include "SPI_private.h"
#include "SPI_Config.h"
#include "SPI_Interface.h"



/*********************************Init Function*********************/
void SPI_Init (void ){

#if (Init_mode == Master)
	/* Set MOSI and SCK output, all others input */
	Set_Bit(SPI_SPCR, MSTR);  // Master Mode Selection
	Dio_u8_SetPinDir(SPI_PORT, SPI_MOSI, Dio_PinOutput);
	Dio_u8_SetPinDir(SPI_PORT, SPI_MISO, Dio_PinInput);
	Dio_u8_SetPinDir(SPI_PORT, SPI_SCK, Dio_PinOutput);

	Dio_u8_SetPinDir(SPI_PORT, SPI_SS, Dio_PinInput);
	Dio_u8_SetPinVal(SPI_PORT, SPI_SS, Dio_PinHigh);


	Set_Bit(SPI_SPCR, SPE); // Enable SPI


#elif (Init_mode == Slave)
	/* Set MISO output, all others input */
	Clear_Bit(SPI_SPCR, MSTR); // Slave Mode selection
	Dio_u8_SetPinDir(SPI_PORT, SPI_MOSI, Dio_PinInput);
	Dio_u8_SetPinDir(SPI_PORT, SPI_MISO, Dio_PinOutput);
	Dio_u8_SetPinDir(SPI_PORT, SPI_SCK, Dio_PinInput);

	Dio_u8_SetPinDir(SPI_PORT, SPI_SS, Dio_PinInput);
	Dio_u8_SetPinVal(SPI_PORT, SPI_SS, Dio_PinHigh);
	Set_Bit(SPI_SPCR, SPE);

#endif

#if (Leading_Edge == Rising_Edge)

	Clear_Bit(SPI_SPCR, CPOL);

#elif (Leading_Edge == Falling_Edge	)

	Set_Bit(SPI_SPCR, CPOL);
#endif

#if (Edge_phase == Sample_phase)

	Clear_Bit(SPI_SPCR, CPHA);

#elif (Edge_phase == Setup_phase)

	Set_Bit(SPI_SPCR, CPHA);

#endif

#if (Freq_Scaler == _4F_Hz)

	Clear_Bit(SPI_SPCR,SPR0);
	Clear_Bit(SPI_SPCR , SPR1);
	Clear_Bit(SPI_SPSR, SPI_SPI2X);
#elif (Freq_Scaler == _16F_Hz)

	Set_Bit(SPI_SPCR , SPR0);
	Clear_Bit(SPI_SPCR , SPR1);
	Clear_Bit(SPI_SPSR, SPI_SPI2X);
#elif (Freq_Scaler == _64F_Hz)

	Clear_Bit(SPI_SPCR,SPR0);
	Set_Bit(SPI_SPCR , SPR1);
	Clear_Bit(SPI_SPSR, SPI_SPI2X);

#elif

	Set_Bit(SPI_SPCR , SPR1);
	Set_Bit(SPI_SPCR , SPR0);
	Clear_Bit(SPI_SPSR, SPI_SPI2X);


#endif

	 // SPI Enable


#if (Data_Order == LSB_Order)

	Set_Bit(SPI_SPCR, DORD);

#elif
	Clear_Bit(SPI_SPCR , DORD);
#endif


}


/******************************************Interrputs ***********************/

void SPI_Interrput_Enable (void) {

	Set_Bit(SPI_SPCR, SPIE);
}

void SPI_Interrput_disable (void){

	Clear_Bit(SPI_SPCR, SPIE);
}

/************************************SPI _Functions **************************/

void SPI_SENDByte_SYNC (u8 Data ){

	SPI_SPDR = Data ;

	while (Get_Bit(SPI_SPSR, SPI_SPIF) == 0); // Stuck In this loop if the SPI is sending data nutil the flag is Set


}

u8  SPI_ReciveByte_SYNC (void ) {

	while (Get_Bit(SPI_SPSR, SPI_SPIF) == 0);
	return SPI_SPDR;
}

u8 SPI_Tranciver (u8 data){

	SPI_SPDR = data ;

		while (Get_Bit(SPI_SPSR, SPI_SPIF) == 0);
		return SPI_SPDR;
}


