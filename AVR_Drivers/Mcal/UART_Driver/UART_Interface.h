/*
 * UART_Interface.h
 *
 *  Created on: Oct 8, 2023
 *      Author: omar
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void USART_Init (void );
void USART_SendByte(u8 Data );
u8   USART_ReciveByte (void );
u8   USART_Recive_NoBlocking (u8 * Data );
void UART_TX_Callback (void (*Local_Ptr)(void )) ;
static void TX_FUNC(void );
void UART_SendStr_Async (u8 * Str ) ;
static void RX_FUNC(void ) ;
void  UART_RecStr_Async (u8 * Str );
u8  USART_RecByte_NOBlock (void);
void UART_RX_Callback (void (*Local_Ptr)(void )) ;
void RX_Interrput_Enbale (void );
void TX_Interrput_Enable(void );
void USART_SendByte_NOBlock(u8 Data);
void TX_Interrput_Disable(void );











/************************************************PINS***********************/
// UCSRA pins
#define MPCP_PIN  0
#define U2X_PIN   1
#define PE_PIN    2
#define DOR_PIN   3
#define FE_PIN    4
#define UDRE_PIN  5
#define TXC_PIN   6
#define RXC_PIN   7
// UCSRB pins
#define TXB8_PIN  	0
#define RXB8_PIN    1
#define UCSZ2_PIN   2
#define TXEN_PIN    3
#define RXEN_PIN    4
#define UDRIE_PIN   5
#define TXCIE_PIN   6
#define RXCIE_PIN   7
// UCSRC pins
#define UCPOL_PIN  	0
#define UCSZ0_PIN   1
#define UCSZ1_PIN   2
#define USBS_PIN    3
#define UPM0_PIN    4
#define UPM1_PIN    5
#define UMSEL_PIN   6
#define URSEL_PIN   7



#endif /* UART_INTERFACE_H_ */
