/*
 * Timer.h
 *
 *  Created on: Dec 18, 2023
 *      Author: omar
 */

#ifndef TIMER_H_
#define TIMER_H_
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#define Timer0_TOIE0 0
#define Timer0_OCIE0 1

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Enums
 **********************************************************************************************************************/
typedef enum {

	Timer0_NormalMode,
	Timer0_PWM_PhaseCorrect,
	Timer0_CTC,
	Timer0_FastPWM,

}Timer0_Mode ;

typedef enum {

	CS00,
	CS01,
	CS02,
	WGM01,
	COM00,
	COM01,
	WGM00,
	FOC0,

}TCCR0_Pins;

typedef enum {
	NoclkSrc,
	NOPrescaling,
	_CLK8_,
	_ClK64_ ,
	_CLK256_,
	_CLK1024_,
	Falling_EDGE_,
	Rising_EDGE_,

}Timer0_Prescaler;


typedef enum {
	OC0_Disconnected,
	Toggle_OC0,
	NonInverting_OC0,
	Inverting_OC0,

}OC0_Mode ;
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* TIMER_H_ */
