/*
 * Timer_1.h
 *
 *  Created on: Jan 4, 2024
 *      Author: omar
 */

#ifndef TIMER_1_H_
#define TIMER_1_H_

/********************************************
 * Macros
 *Macro like Object
 ******************************************/
#define Timre1_Prescaler_Mask 0b11111000
/*********************************************
 * Timer_1 Enums
 ********************************************/
typedef enum {

	NoClk_Src,/**< NoClk_Src */
	CLK_1,    /**< CLK_1 */
	CLK_8,    /**< CLK_8 */
	CLK_64,   /**< CLK_64 */
	CLK_256,  /**< CLK_256 */
	CLK_1024  /**< CLK_1024 */
}Prescaler_Modes;

typedef enum {
	Normal_Mode,
	PWM_PhaseCorrect,
	CTC_ICR1,
	PWM_Phase_Frequency_Correct_ICR1,
	PWM_PhaseCorrect_ICR1,
	FastPWM_ICR1A
}Timer1_Mode;

typedef enum {
	 WGM10,
	 WGM11,
	 FOC1B,
	 FOC1A,
	 COM1B0,
	 COM1B1,
	 COM1A0,
	 COM1A1
}Timer_1_TCCR1A;

typedef enum {
	CS10,
	CS11,
	CS12,
	WGM12,
	WGM13,
	// Revered Pin
	ICES1 = 6,
	ICNC1


}Timer_1_TCCR1B;

typedef enum {

	OC_DISCONNECTED,
	Toggle_OC,
	NonInverting_OC,
	Inverting_OC

}Timer1_OCA_B;


/*********************************************
 * Function Prototype
 *********************************************/
void Timer_1_Init (Prescaler_Modes scaler, Timer1_Mode Form_Mode,Timer1_OCA_B OCA_MODE,Timer1_OCA_B OCB_MODE);
void PWM_Freq_KHZ (u16 Freq, u8 DutyCycle);
void Timer1_OVF_Callback (void (*Local_PTR)(void));
void ICU_Init (u8 Copy_Trigger_Edge);
/*******************
 * Enbale Functions
 *******************/
void Timer1_OVF_ENB (void);
void Timer1_OVF_DIS (void);
void Timer1_OCA_ENB (void);
void Timer1_OCA_DIS (void);
void Timer1_OCB_ENB (void);
void Timer1_OCB_DIS (void);
void Timer1_ICU_ENB (void);
void Timer1_ICU_DIS (void);


#endif /* TIMER_1_H_ */
