/*
 * Dio_Private.h
 *
 *  Created on: Jul 3, 2023
 *      Author: omar
 */

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

// Define GROUP A Registers

#define DIO_U8_DDRA *((volatile u8*)0x3A)
#define DIO_U8_PORTA *((volatile u8*)0x3B)
#define DIO_U8_PINA *((volatile u8*)0x39)

// Define GROUP B Registers

#define DIO_U8_DDRB *((volatile u8*)0x37)
#define DIO_U8_PORTB *((volatile u8*)0x38)
#define DIO_U8_PINB *((volatile u8*)0x36)


// Define GROUP C Registers

#define DIO_U8_DDRC *((volatile u8*)0x34)
#define DIO_U8_PORTC *((volatile u8*)0x35)
#define DIO_U8_PINC *((volatile u8*)0x33)


// Define GROUP D Registers

#define DIO_U8_DDRD *((volatile u8*)0x31)
#define DIO_U8_PORTD *((volatile u8*)0x32)
#define DIO_U8_PIND *((volatile u8*)0x30)

// SREG
#define SREG *((volatile u8*)0x5F)


#endif /* DIO_PRIVATE_H_ */
