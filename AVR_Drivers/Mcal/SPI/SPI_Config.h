/*
 * SPI_Config.h
 *
 *  Created on: Oct 30, 2023
 *      Author: omar
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

						/*********************************SPI Config *************************************/
#define Init_mode   	 Master
#define Leading_Edge   Rising_Edge
#define Edge_phase	   Sample_phase
#define Freq_Scaler		_16F_Hz
#define Data_Order		LSB_Order
						/***********************definiations**********************************/
#define Master 1
#define Slave  0


#define Rising_Edge 1
#define Falling_Edge 0

#define Sample_phase 1
#define Setup_phase 0

#define _4F_Hz   0
#define _16F_Hz  1
#define _64F_Hz  2
#define _128F_Hz 3


#define LSB_Order 1
#define MSB_Order 0



#define SPI_PORT  Group_B

#define SPI_SS	  PIN4
#define SPI_MOSI  PIN5
#define SPI_MISO  PIN6
#define SPI_SCK   PIN7

#define SPI_SPIF  7
#define SPI_WCOl  6
#define SPI_SPI2X 0
#endif /* SPI_CONFIG_H_ */
