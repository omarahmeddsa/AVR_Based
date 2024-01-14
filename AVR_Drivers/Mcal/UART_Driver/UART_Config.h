/*
 * UART_Config.h
 *
 *  Created on: Oct 8, 2023
 *      Author: omar
 */

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

												//******USART Config
#define F_cpu 			 _8_MHZ
#define	Speed_Mode		Normal_speed
#define Baud_Rate		Baud_9600
#define Character_size  _8_bit_Data
#define Stop_Bit		Stop_1_Bit
#define	parity_Mode		parity_Disabled
#define Sync_mode		Aysnchronous_opreation
// CPU_Freqs
#define _4_MHZ 0
#define _8_MHZ 1
#define _16_MHZ 2
#define Total_Freq	3
							//F_Speed**************************
#define Normal_speed 0
#define Double_speed 1
#define Total_speed  2
							//Character size***************************
#define _5_bit_Data 0
#define _6_bit_Data 1
#define _7_bit_Data 2
#define _8_bit_Data 3
#define _9_bit_Data 4

							// Baud Rate *******************************/
#define Baud_2400   0
#define Baud_2800   1
#define Baud_9600   2
#define Baud_1440   3
#define Baud_1920   4
#define Baud_2880   5
#define Total_Baud  6


							// Stop Bit Select******************
#define Stop_1_Bit 	0
#define Stop_2_Bit  1

							// parity Mode **********************
#define parity_Disabled 0
#define parity_EVEN     1
#define parity_Odd      2
							// Sync_mode ***********************
#define Aysnchronous_opreation 0
#define synchronous_opreation 1


#endif /* UART_CONFIG_H_ */
