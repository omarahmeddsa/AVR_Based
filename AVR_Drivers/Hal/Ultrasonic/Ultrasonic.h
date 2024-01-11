/*
 * Ultrasonic.h
 *
 *  Created on: Jan 11, 2024
 *      Author: omar
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/**********************************************************
 * Macros
 *********************************************************/
#define Trigger_Group  Group_B
#define Trigger_PIN    PIN0
#define ECO_Group	   Group_D
#define ECO_PIN        PIN6
/**********************************************************
 * Prototype
 *********************************************************/
void Ultrasonic_Init (void );
static void Timer_OVF (void);
static void Timer_ICU (void);

#endif /* ULTRASONIC_H_ */
