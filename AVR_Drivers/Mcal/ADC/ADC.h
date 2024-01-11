/*
 * ADC.h
 *
 *  Created on: Jan 8, 2024
 *      Author: omar
 */

#ifndef ADC_H_
#define ADC_H_
/*************************************************************
 * Enums
 *************************************************************/


typedef enum {

	Free_Running_mode,
	Analog_Comp,
	EXTI0,
	Timer0_Comp,
	Timer0_OVF,
	Timer1_CompB,
	Timer1_ICU



}ADC_Trigger_source ;
typedef enum {

	AREF,
	AVCC,
	Internal_2Volt = 3,

}Reference_Selection;

typedef enum {

	MUX0,
	MUX1,
	MUX2,
	MUX3,
	MUX4,
	ADLAR,
	REFS0,
	REFS1

}ADMUX_PINS;

typedef enum {

	ADPS0,
	ADPS1,
	ADPS2,
	ADIE,
	ADIF,
	ADATE,
	ADSC,
	ADEN

}ADCSRA_PINS;



typedef enum {

	Division_2,
	Division_4,
	Division_8,
	Division_16,
	Division_32,
	Division_64,
	Division_128

}Prescaler;

typedef enum {

	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7,
	ADC0_ADC0_10,
	ADC1_ADC0_10,
	ADC0_ADC0_200

}Analog_Channel ;
/****************************************
 * Macros
 ****************************************/
#define ADMUX_Mask 0b11100000
#define ADC_Auto_trigger   DISABLE
#define ADC_Trigger_SRC	   Free_Running_mode
/****************************************
 * prototypes
 *****************************************/

void ADC_Init (Reference_Selection type , Prescaler scaler , Analog_Channel channel,ADC_Trigger_source Src);
u16 ADC_Output_Calc(u16 MAX_Value , u16 MIN_Value, Analog_Channel channel);
void ADC_Enable(void );
void ADC_Disable(void );
void ADC_Start_Conversion(void);
void ADC_AutoTriggerEnable (void);
void  ADC_AutoTriggerDisable (void);
void  ADC_InterruptEnable (void);
void  ADC_InterruptDisable (void);
void ADC_CallBack(void (* Local_PTR)(void));
u16  ADC_GetResult_ASync( Analog_Channel channel);
u16  ADC_GetResult_Sync(Analog_Channel channel);

#endif /* ADC_H_ */
