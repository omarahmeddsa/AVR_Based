/*
 * UART_private.h
 *
 *  Created on: Oct 8, 2023
 *      Author: omar
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_



#define UBRRL    (*(volatile u8*)0x29)

/* USART Control and Status Register B */
#define UCSRB   (*(volatile u8*)0x2A)

/* USART Control and Status Register A */
#define UCSRA    (*(volatile u8*)0x2B)

/* USART I/O Data Register */
#define UDR       (*(volatile u8*)0x2C)

/* USART Baud Rate Register High */
#define UBRRH    (*(volatile u8*)0x40)

/* USART Control and Status Register C */
#define UCSRC     (*(volatile u8*)0x40)


#endif /* UART_PRIVATE_H_ */
