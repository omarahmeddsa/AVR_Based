                            /**********
                            Memory map 
                            Created Omar*************/
                            /****File Descprtion : This file contains the addresses of registers
                            and it is a common file *********/


#ifndef _MEMORYMAP_H
#define _MEMORYMAP_H
/*************************Dio Memory maps******************/

/*************************Group A******************/
#define DDRA_u8     *((volatile u8 * )0x3A)       
#define PORTA_u8    *((volatile u8 * )0x3B)
#define PINA_u8     *((volatile u8 * )0x39)
/*************************Group B******************/
#define DDRB_u8     *((volatile u8*)0x38)       
#define PORTB_u8    *((volatile u8*)0x38)
#define PINB_u8     *((volatile u8*)0x36)
/*************************Group C******************/
#define DDRC_u8     *((volatile u8*)0x35)     
#define PORTC_u8    *((volatile u8*)0x3B)
#define PINC_u8     *((volatile u8*)0x33)
/*************************Group D******************/
#define DDRD_u8     *((volatile u8*)0x31)       
#define PORTD_u8    *((volatile u8*)0x32)
#define PIND_u8     *((volatile u8*)0x30)
/*PULL UP */
#define  SFIOR   *((volatile u8*)0x50)
#define Null (void*)0
/****************Interrput Memory map**************/

























#endif