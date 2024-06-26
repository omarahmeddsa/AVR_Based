/*
 * EXTINT_Interface.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef MCAL_EXTINT_EXTINT_INTERFACE_H_
#define MCAL_EXTINT_EXTINT_INTERFACE_H_
/***************************************************************************************/
/*                                     INCLUDES                                        */
/***************************************************************************************/
#include "EXTINT_Config.h"
#include "BitMath.h"
#include "STD.h"
#include <avr/interrupt.h>
/***************************************************************************************/
/*                                     DEFINES                                         */
/***************************************************************************************/
#define INT0_CHANNEL           0
#define INT1_CHANNEL           1
#define INT2_CHANNEL           2
/***************************************************************************************/
/*                                    PROTOTYPES                                       */
/***************************************************************************************/
void M_EXTINT_Void_EXTINTInit(u8);
void M_EXTINT_Void_SetCallBack(u8,void(*)(void));
void GIE_voidEnable(void);
void GIE_voidDisable(void );
void EXINT1_Enable (void );
void EXINT1_Disable (void );

#endif /* MCAL_EXTINT_EXTINT_INTERFACE_H_ */
