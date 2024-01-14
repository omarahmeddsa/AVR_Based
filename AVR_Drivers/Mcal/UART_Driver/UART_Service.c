/*
 * UART_Service.c
 *
 *  Created on: Oct 12, 2023
 *      Author: omar
 */


#include "Bit_calc.h"
#include "STD_TYPES.h"
#include "Dio_Private.h"
#include "Dio_Interface.h"
#include "UART_private.h"
#include "UART_Interface.h"
#include "UART_Config.h"
#include "UART_Services.h"

/****************************Gobal Variables *******************************************/

	static u8 * Asyn_SendStr ;
	static u8 * Asyn_RecStr ;

/****************************Functions *************************************************/

void UART_SendStr (u8 * Str) {

	u8 i = 0;
	while (Str [i] != '\0') {
		USART_SendByte(Str[i]);
		i++;
	}
}

void UART_ReciveStr (u8 * Str){

	u8 i = 0 ;

	Str [i] = USART_ReciveByte();

	while (Str [i] != '#'){

		i++;
		Str [i] = USART_ReciveByte();
	}

	Str [i] = '\0';
}

										/********************UART Protocols *******************/


void UART_SEND_Protocol (u8 * Str){

	u8 i = 0 ; u8 lens = 0; u8 sum = 0 ;

	while (Str [lens] != '\0'){

		sum +=  Str[lens];
		lens++;
}
	USART_SendByte(lens);

	while (Str [i] != '\0'){

		USART_SendByte(Str[i]);
		i++;
	}

	USART_SendByte((u8 ) sum );
	USART_SendByte((u8)(sum >> 8));
}

u8 UART_Recive_Protocol (u8 * Str)

	{

		u8 i=0 ,lens=0,firstbyte=0,secondbyte=0;
		u16 sum_send=0,sum_calc=0;
		lens=USART_ReciveByte();



		for(i=0;i<lens;i++)
		{
			Str[i]=USART_ReciveByte();

			sum_calc+=Str[i];

		}

		firstbyte  = USART_ReciveByte();
		secondbyte = USART_ReciveByte();
		sum_send=firstbyte|(secondbyte<<8);

		if(lens==i)
			/*Lens is a variable we will recive the number of letters on, i is counter we made
			*/
			return 1;
		else
			return 0;
	}
/******************************** SEND using Interrput service routine *****************/

void UART_SendStr_Async (u8 * Str ){

	Asyn_SendStr = Str ;

	USART_SendByte(Str [0]);

	UART_TX_Callback (TX_FUNC);

	TX_Interrput_Enable();


}

static void TX_FUNC(void ){

	static u8 i = 1;

	if (Asyn_SendStr [i] != '\0'){

		USART_SendByte_NOBlock(Asyn_SendStr [i]);

		i++;
	}
	else {

		i = 1 ;

		TX_Interrput_Disable();

	}

}
/********************************Recveing Data using interrput *******************************/

void  UART_RecStr_Async (u8 * Str ){

	Asyn_RecStr = Str;
	RX_Interrput_Enbale ();
	UART_RX_Callback(RX_FUNC);


}



static void RX_FUNC(void ) {

	static u8 i = 0;
		Asyn_RecStr [i] =  USART_RecByte_NOBlock ();
		i++ ;




}
