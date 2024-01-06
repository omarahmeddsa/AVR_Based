/*
 * main.c
 *
 *  Created on: Jan 4, 2024
 *      Author: omar
 */
#include "Bit_calc.h"
#include "MemoryMap.h"
#include "Macros.h"
#include "STD_TYPES.h"
#include "Dio.h"
#include "EXIT.h"
#include "Timer_1.h"

/*************************************************************************************************
 * Description : The purpose of this project is to CTRL a servo  motor angle  using PWM
 *
 *	Modules : GPIO , External Interrupt , Timer 1 Fast PWM with ICR1 is the top value  Mode
 *
 *	Components : Two Servo Motor ,  Two push button , Check LED , Oscilloscope
 *
 *	push button 1 Controls the angle of servo A by changing the OCRA value, push button 2 Controls
-the angle of servo B by changing the OCRB value
 ************************************************************************************************************/


// ISR For push Button 1

int main (void ){
	
	
	while (1){
		
	}
}