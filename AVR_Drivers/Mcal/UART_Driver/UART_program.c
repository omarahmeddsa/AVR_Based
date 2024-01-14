/*
 * UART_program.c
 *
 *  Created on: Oct 8, 2023
 *      Author: omar
 */

#include "Bit_calc.h"
#include "STD_TYPES.h"
#include "Dio_Private.h"
#include "Dio_Interface.h"
#include "UART_private.h"
#include "UART_Interface.h"
#include "UART_Config.h"

/*****************************************Varibales *********************/
static void (*UART_TX_Ptr) (void )= Null;
static void (*UART_RX_Ptr) (void )= Null;

/*********************************Buad Rate array ********/
const u16 BaudRateArray[Total_speed][Total_Freq][Total_Baud]=
		 {{{103, 51, 25, 16, 12,  8},{207,103, 51, 34, 25, 16},{416,207,103, 68 ,51, 34}},
		  {{207,103, 51, 34, 25, 16},{416,207,103, 68 ,51, 34},{832,416,207,138,103, 68}}};


void USART_Init(void ){

	u8 UCSRC_Var = 0 ;
	u16 UBRR_Var = 0 ;
	/*************************** The speed Config *******************************/
	#if (Speed_Mode == Normal_speed)

		Clear_Bit(UCSRA,U2X_PIN);

	#elif (Speed_Mode == Double_speed)

		Set_Bit (UCSRA, U2X_PIN);

	#endif

	/**************************** Character Size Congig *************************/
		Set_Bit(UCSRC_Var, URSEL_PIN);

	#if (Character_size == _5_bit_Data)

		Clear_Bit(UCSRC_Var, UCSZ0_PIN);
		Clear_Bit(UCSRC_Var, UCSZ1_PIN);
		Clear_Bit(UCSRB, UCSZ2_PIN);

	#elif (Character_size == _6_bit_Data)
		Set_Bit(UCSRC_Var, UCSZ0_PIN);
		Clear_Bit(UCSRC_Var, UCSZ1_PIN);
		Clear_Bit(UCSRB, UCSZ2_PIN);

	#elif (Character_size == _7_bit_Data)
		Clear_Bit(UCSRC_Var, UCSZ0_PIN);
		Set_Bit(UCSRC_Var, UCSZ1_PIN);
		Clear_Bit(UCSRB, UCSZ2_PIN);

	#elif (Character_size == _8_bit_Data)
		Set_Bit(UCSRC_Var, UCSZ0_PIN);
		Set_Bit(UCSRC_Var, UCSZ1_PIN);
		Clear_Bit(UCSRB, UCSZ2_PIN);

	#elif (Character_size == _9_bit_Data)
		Set_Bit(UCSRC_Var, UCSZ0_PIN);
		Set_Bit(UCSRC_Var, UCSZ1_PIN);
		Set_Bit(UCSRB, UCSZ2_PIN);

	#endif

	/********************************* Stops Bits ********************************/

	#if (Stop_Bit == Stop_1_Bit)

		Clear_Bit(UCSRC_Var, USBS_PIN);

	#else
		Set_Bit (UCSRC_Var, USBS_PIN);

	#endif

	/*********************************Synch Mode *********************************/


	#if (Sync_mode == Aysnchronous_opreation)

		Clear_Bit(UCSRC_Var, UMSEL_PIN);
	#else
		Set_Bit(UCSRC_Var, UMSEL_PIN);

	#endif

	/********************************Parity Mode**********************************/

	#if (parity_Mode == parity_Disabled)

		Clear_Bit(UCSRC_Var, UPM0_PIN);
		Clear_Bit(UCSRC_Var, UPM1_PIN);

	#elif	(parity_Mode == parity_EVEN)

		Clear_Bit(UCSRC_Var, UPM0_PIN);
		Set_Bit(UCSRC_Var, UPM1_PIN);

	#elif	(parity_Mode == parity_Odd)

		Set_Bit(UCSRC_Var, UPM0_PIN);
		Set_Bit(UCSRC_Var, UPM1_PIN);


	#endif

	/********************** Set one to URSEL bit to UARSC ************************/


	UCSRC = UCSRC_Var;

	/***** Now the config of URSC is finshed****************/


	/************************************** Write The Baud Rate on UBRR Reg *****************/

	UBRR_Var = BaudRateArray[Speed_Mode][F_cpu][Baud_Rate];

	UBRRH = (u8)(UBRR_Var>>8);
	UBRRL = (u8)(UBRR_Var);

	/************************************ENBALBE Transmitter and Recvier ********************/

	Set_Bit(UCSRB,TXEN_PIN );
	Set_Bit(UCSRB, RXEN_PIN);


}




 	 	 	 	 	 	 /*******************Sending and Reciveing data with polling Functions ***********************/

void USART_SendByte(u8 Data ) {


	while (Get_Bit(UCSRA ,UDRE_PIN) == 0 ) ;

		UDR = Data ;

}

u8   USART_ReciveByte (void ){


	while (Get_Bit(UCSRA ,RXC_PIN) == 0) ;
		return UDR;
}
/**********************Interrput*****************/
void USART_SendByte_NOBlock (u8 Data){

		UDR = Data ;

}

u8  USART_RecByte_NOBlock (void){


	return UDR ;
}

/********************************UART interrput  **********************************/


void RX_Interrput_Enbale (void ){

	Set_Bit(UCSRB , RXCIE_PIN);

}

void RX_Interrput_Disable (void ){

	Clear_Bit(UCSRB , RXCIE_PIN);

}

void TX_Interrput_Enable(void ){

	Set_Bit(UCSRB , TXCIE_PIN);

}

void TX_Interrput_Disable(void ){

	Clear_Bit(UCSRB , TXCIE_PIN);

}

void Buffer_Interrput_Enable (void ){

	Set_Bit(UCSRB , UDRIE_PIN);
}

void Buffer_Interrput_Disable (void ){
	Clear_Bit(UCSRB , UDRIE_PIN);

}
/*****************************Callback functions **********************************/

void UART_TX_Callback (void (*Local_Ptr)(void )) {

	UART_TX_Ptr = Local_Ptr;

}

void UART_RX_Callback (void (*Local_Ptr)(void )) {

	UART_RX_Ptr = Local_Ptr;

}
/************************ISR **********************************************/


void __vector_15(void)__attribute__((signal));
void __vector_15(){

	if (UART_TX_Ptr != Null) {
		UART_TX_Ptr() ;
	}
}


void __vector_13(void)__attribute__((signal));
void __vector_13(){

	if (UART_RX_Ptr != Null) {
		UART_RX_Ptr() ;
	}
}


