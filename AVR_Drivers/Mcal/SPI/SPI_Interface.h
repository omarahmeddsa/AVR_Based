/*
 * SPI_Header.h
 *
 *  Created on: Oct 30, 2023
 *      Author: omar
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void SPI_Init (void );
void SPI_Interrput_Enable (void);
void SPI_Interrput_disable (void);
void SPI_SENDByte_SYNC (u8 Data );
u8  SPI_ReciveByte_SYNC (void );
u8 SPI_Tranciver (u8 data);











typedef enum {

	SPR0,
	SPR1,
	CPHA,
	CPOL,
	MSTR,
	DORD,
	SPE,
	SPIE,


}SPI_REG;



#endif /* SPI_INTERFACE_H_ */
