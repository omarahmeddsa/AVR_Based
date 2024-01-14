/*
 * UART_Services.h
 *
 *  Created on: Oct 12, 2023
 *      Author: omar
 */

#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

// Functions

void UART_SendStr (u8 * Str);
void UART_ReciveStr (u8 * Str);
void UART_SEND_Protocol (u8 * Str);
u8 UART_Recive_Protocol (u8 * Str);

#endif /* UART_SERVICES_H_ */
