/*
 * EXIT.h
 *
 *  Created on: Dec 10, 2023
 *      Author: omar
 */

#ifndef EXIT_H_
#define EXIT_H_

/*******************************************************************
 * Functions Prototypes
 *******************************************************************/
void EXTI_Init (u8 Copy_INTx) ;
void EXTI_Line_Disable  (u8 Copy_INTx) ;
void EXTI_SenseCTRL (u8 Copy_SenseMode, u8 Copy_Line);
void EXTI_Callback_INT (u8 Init_Line,void (* Local_PTR)(void ));

#endif /* EXIT_H_ */
