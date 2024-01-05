/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <Macros>
 *       Module:  -
 *
 *  Description:  <definiations and enums >     
 *  
 *********************************************************************************************************************/
#ifndef _MACROS_H
#define _MACROS_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Definitions 
 *********************************************************************************************************************/
 
 /*****************************************************************************
 **Genral Definitions
 ******************************************************************************/
#define ENBALBE 1
#define DISABLE 0
//Pin Direction
#define Dio_PinInput  0
#define Dio_PinOutput 1

//Port Direction
#define Dio_PortInput  0
#define Dio_PortOutput 0xFF

//Port value
#define Dio_PortHigh 0xFF
#define Dio_PortLow 0

//Pin value
#define Dio_PinHigh 1
#define Dio_PinLow 0



/********************************************************************************
*GPIO Registers
********************************************************************************/
/*Dio Defintions*/
// Groups Macros
#define Group_A 0
#define Group_B 1
#define Group_C 2
#define Group_D 3
// Port Macros
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
// Pin Macros
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
/*Definations*/
#define Null (void*)0
#define GobalInterrput_Pin 7

/*******************************************************************************************************************/

// Interrputs Definiations


/**********************************************************************************************************************
 * Enums
 *********************************************************************************************************************/

/*External Interrputs Enums*/

#define EXTI_ISC2 6
// Interrput error enms
typedef enum {
	No_ERROR,
	INTX_ERROR,
	Sense_Ctrl,
}EXTI_ERROR;

// INT _ Pins triger
typedef enum
{
	INT2 = 5,
	INT0,
	INT1,
}INTx;

typedef enum {

	Low_Level,
	Any_Change,
	Falling_Edge,
	Rising_Edge,

}SenseCtrl;

/*MCUCR Pins*/
typedef enum
{
	ISC00,
	ISC01,
	ISC10,
	ISC11,
}MCUCR_PINS;

// TIMSk Register
typedef enum {

	Timer0_TOIE0,
	Timer0_OCIE0,
	TOIE1,
	OCIE1B,
	OCIE1A,
	TICIE1,
	TOIE2,
	OCIE2
}TIMSK;
/**********************************************************************************************************************
 * Structs 
 *********************************************************************************************************************/



 
#endif  /*Macros */

/**********************************************************************************************************************
 *  END OF FILE: Macros
 *********************************************************************************************************************/
