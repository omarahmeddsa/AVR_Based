/*
 * LED_Interface.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef LED_LED_INTERFACE_H_
#define LED_LED_INTERFACE_H_

#include "LED_Config.h"
#include "STD.h"
#include "DIO_Interface.h"

#define LED0        0
#define LED1        1
#define LED2        2
#define LED3        3

void H_LED_Void_LedInit(u8);
void H_LED_Void_LedSetOn(u8);
void H_LED_Void_LedSetOff(u8);
void H_LED_Void_LedToggle(u8);

#endif /* LED_LED_INTERFACE_H_ */
