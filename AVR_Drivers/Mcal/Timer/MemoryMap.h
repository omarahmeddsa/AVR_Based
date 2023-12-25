                            /**********
                            Memory map 
                            Created Omar*************/
                            /****File Descprtion : This file contains the addresses of registers
                            and it is a common file *********/


#ifndef _MEMORYMAP_H
#define _MEMORYMAP_H
/*******************************************************************
 * STATUS REGISTER
 ******************************************************************/
#define SREG   *((volatile u8 *)0x5F)

/*******************************************************************************************************************/
/*************************Dio Memory maps******************/

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
/****************Interrput Memory map***************/

#define EXTI_GICR  * ((volatile u8 *)0x5B)   // Set The Interrputs
#define EXTI_GIFR  * ((volatile u8 *)0x5A)	// Flags
#define EXTI_MCUCR * ((volatile u8 *)0x55) // Sense Control PINS

/*****************Timer Register ********************/

#define Timer0_TCCR0 *((volatile u8 *)0x53) // Timer0 register to set the pre_scaler and the mode
#define Timer0_OCR0  *((volatile u8 *)0x5C) // Timer0 Output compare  Unit
#define Timer0_TIFR  *((volatile u8 *)0x58) // TImer0 Flag
#define Timer0_TCNT0 *((volatile u8 *)0x52) // Timer0 compare  Register
#define Timer0_TIMSK * ((volatile u8 *)0x59) // TImer0 Interrupt Mask
/********************ADC*****************************/




















#endif
