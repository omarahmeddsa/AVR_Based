/*
 * Project_main.c
 *
 *  Created on: Mar 4, 2024
 *      Author: ALHassan Khaled
 */

#include <util/delay.h>
#include "BitMath.h"
#include "STD.h"

#include "DIO_Interface.h"
#include "PushButton_Interface.h"
#include "LED_Interface.h"
#include "Buzzer_Interface.h"
#include "EXTINT_Interface.h"
#include "LCD_Interface.h"
#include "ADC_Interface.h"
#include "Keypad_Interface.h"
/****************************************/
/*modifications*/
/*Interrupt PushButton modifications (Change the mechanism and make the interrupt always on and Check for the PB2) ---->under tests
 *Buzzer for each PushButton ---->under tests
 *No CCS on Reverse Mode     ---->under tests
 *Relay Task
 ****************************************/
/****************************************/

typedef enum{
	E_OFF,
	E_ON
}CCS_E;

typedef enum{
	E_LED_Red,
	E_LED_Green,
	E_LED_Yellow,
	E_LED_Blue
}LED_E;


typedef enum{
	E_BTN_Accreration,
	E_BTN_Break,
	E_BTN_CCS,
	E_BTN_Drive_Mode
}BTN_E;


typedef enum{
	E_Mode_Normal,
	E_Mode_Drive,
	E_Mode_Reverse
}DRIVE_MODE_E;


typedef enum{
	E_PAGE_1=0,
	E_PAGE_2,
	E_PAGE_3
}PAGE_E;


/*--------------------------------------------------------------------------------------------*/
/*Global Variables**/
/*--------------------------------------------------------------------------------------------*/
/*Initial state */

DRIVE_MODE_E g_DriveModeState = E_Mode_Normal;
CCS_E G_CCS_State_Control=E_OFF;
CCS_E G_CCS_State =E_OFF;
CCS_E G_Accelerator_Control = E_OFF;
CCS_E G_Break_Control = E_OFF;
CCS_E G_Voilet_Button_Control = E_OFF;

volatile u8 G_PAGE= E_PAGE_1;
u16 G_Speed ;
u16 G_SpeedLimit = 100;


volatile  u8 Drive_Mode_Counter ;
static u8 relay_state = E_OFF;

static u8 relay_flag = 0 ;


/*--------------------------------------------------------------------------------------------*/
/*   Function Prototypes    */
/*--------------------------------------------------------------------------------------------*/
void Init_Func(void);
void printDriveMode(DRIVE_MODE_E mode);
void printCCRMode(CCS_E mode);
void System(void);

void Drive_Mode (void);
void Menu_On_Screen(u8 page);
void Show_Page(void);
void DriveModeAlert (void);
void Reverse_Mode_Func(void);
void Normal_Mode_Func(void);
void Direct_Mode_Func(void);
void Speed_Limit_Set(void);
void Speed_Limit_Mode(u8 mode);
void Accelerator_Button (void );
void Break_Button (void );
void CCS_Button (void );
void DriveMode_violet_Button(void);
void Display_Speed(void);
void toggle_or_set_relay_Mode(void);
void Speed_alert(void);

void set_relay_Mode(u8 Mode);


/*ISR Function , switch between the drive mode*/
void Driver_Mode_Button(void){

	//	H_LED_Void_LedSetOn(E_LED_Green);

	_delay_ms(30);
	Drive_Mode_Counter++;

	if (Drive_Mode_Counter == 3){

		Drive_Mode_Counter = E_Mode_Normal;
		//H_Buzzer_Void_BuzzerOnce();

	}

	Drive_Mode();

}



/*--------------------------------------------------------------------------------------------*/
/*   Main Function */
/*--------------------------------------------------------------------------------------------*/
int main(void){



	G_PAGE = E_PAGE_1;
	G_Break_Control = E_ON;
	/* Func to init all system*/
	Init_Func();

//	set_relay_Mode(E_ON); // Turn on the relay
//	_delay_ms(500);
//	set_relay_Mode(E_OFF); // Turn off the relay
//	_delay_ms(500);


	Speed_Limit_Mode(E_OFF);
	Menu_On_Screen(G_PAGE);

	while(1){
		System();
		Speed_alert();
		//		Menu_On_Screen(G_PAGE);
	}
}

/*Init Function for LCD BUZZER AND LEDS PUSHBUTTONS*/
void Init_Func(void){

	/*LED-Init*/
	H_LED_Void_LedInit(E_LED_Red);
	//	H_LED_Void_LedInit(E_LED_Green);
	H_LED_Void_LedInit(E_LED_Blue);
	H_LED_Void_LedInit(E_LED_Yellow);
	/*Pushbutton-Init
	 *Make it Pull-Up*/

	H_PushButton_Void_PushButtonInit(PUSH_BUTTON_3);
	M_DIO_Void_SetPinPullUpRes(PD7_PIN,ENABLE);

	 M_DIO_Void_SetPinDirection(PC7_PIN,OUTPUT);



	/*LCD-Init*/
	H_Lcd_Void_LCDInit();
	/*Buzzer-Init*/
	H_Buzzer_Void_BuzzerInit();
	/*ADC Init*/
	M_ADC_Void_ADCInit();
	/*Interrupt Enable*/
	M_EXTINT_Void_EXTINTInit(INT1_CHANNEL);
	M_EXTINT_Void_SetCallBack(INT1_CHANNEL,Driver_Mode_Button);
	GIE_voidEnable();
	M_ADC_Void_ADCInit();
	H_KeyPad_Void_KeyPadInit();

	M_Timer_Void_TimerInit();



}
/*--------------------------------------------------------------------------------------------*/
/*   System Func    */
/*--------------------------------------------------------------------------------------------*/
void System(void){

	switch (g_DriveModeState) {

	case E_Mode_Normal:

		Normal_Mode_Func();

		break;
	case E_Mode_Drive:

		Direct_Mode_Func();

		break;

	case E_Mode_Reverse:

		Reverse_Mode_Func();

		break;
	default:
		break;
	}
}





void printCCRMode(CCS_E mode) {

	H_Lcd_Void_LCDGoTo(LCD_ROW_1,LCD_COL_06);

	switch (mode) {

	case E_OFF:
		H_Lcd_Void_LCDWriteString((u8*)"OFF");

		break;

	case E_ON:
		H_Lcd_Void_LCDWriteString((u8*)"ON ");

		break;

	default:
		break;
	}
}

void Accelerator_Button (void ){
	Display_Speed();
	if (G_Accelerator_Control == E_ON){
		if(!H_PushButton_U8_PushButtonRead(E_BTN_Accreration)){

			H_Buzzer_Void_BuzzerOnce();
			H_LED_Void_LedSetOn(E_LED_Blue);
			G_CCS_State = E_OFF;
			H_LED_Void_LedSetOff(E_LED_Green);
			while(!H_PushButton_U8_PushButtonRead(E_BTN_Accreration));

		}else if (H_PushButton_U8_PushButtonRead(E_BTN_Accreration)){
			H_LED_Void_LedSetOff(E_LED_Blue);
		}

	}
}


void Break_Button (void ){

	u8 KeyPressedValue ;

	if (G_Break_Control == E_ON ){


		KeyPressedValue = H_KeyPad_U8_KeyPadRead();


		if  (KeyPressedValue == '3' ){
			H_LED_Void_LedSetOn(E_LED_Red);
			EXINT1_Enable();

		}
		else if (KeyPressedValue == KEYPAD_RELEASED){
			H_LED_Void_LedSetOff(E_LED_Red);
			EXINT1_Disable();
		}
	}
}




//void CCS_Button(void) {
//
//	static u8 Flag = 0 ;
//	u8 KeyPressedValue ;
//
//	if (G_CCS_State_Control == E_ON ){
//
//
//		KeyPressedValue = H_KeyPad_U8_KeyPadRead();
//
//
//		if  (KeyPressedValue == '2' ){
//
//			Flag ++;
//			if (Flag == 1){
//
//				H_LED_Void_LedSetOn(E_LED_Green);
//				G_CCS_State  = E_ON;
//
//			}
//
//			else if (Flag == 2) {
//				H_LED_Void_LedSetOff(E_LED_Green);
//				G_CCS_State  = E_OFF;
//				Flag = 0;
//			}
//		}
//
//		else if(G_CCS_State_Control == E_OFF){
//			// Turn on green LED and beep once
//			H_LED_Void_LedSetOff(E_LED_Green);
//			G_CCS_State = E_OFF;
//		}
//
//
//
//	}
//
//}


void CCS_Button(void) {

	static u8 Flag = 0 ;
	u8 KeyPressedValue ;

	if (G_CCS_State_Control == E_ON ){


		KeyPressedValue = H_KeyPad_U8_KeyPadRead();


		if  (KeyPressedValue == '2' ){

			Flag++;
			if (Flag == 1){

				//				H_LED_Void_LedSetOn(E_LED_Green);
				G_CCS_State  = E_ON;


			}

			else if (Flag == 2) {
				//				H_LED_Void_LedSetOff(E_LED_Green);
				G_CCS_State  = E_OFF;
				Flag = 0;
			}
		}
	}

	else if(G_CCS_State_Control == E_OFF){
		// Turn on green LED and beep once
		//		H_LED_Void_LedSetOff(E_LED_Green);
		G_CCS_State = E_OFF;
	}



}


/*Alert Function for any wrong access */
void DriveModeAlert(void){

	H_Buzzer_Void_BuzzerOnce();
	H_LED_Void_LedSetOn(E_LED_Yellow);
	_delay_ms(1000);
	H_LED_Void_LedSetOff(E_LED_Yellow);
	_delay_ms(1000);
}

void DriveMode_violet_Button(void){

	if (G_Voilet_Button_Control == E_ON){
		if(!(H_PushButton_U8_PushButtonRead(E_BTN_Drive_Mode))){
			DriveModeAlert();
			while(!H_PushButton_U8_PushButtonRead(E_BTN_Drive_Mode));

		}
	}

}

/*--------------------------------------------------------------------------------------------*/
/*   Normal Func    */
/*--------------------------------------------------------------------------------------------*/

void Normal_Mode_Func(void){
	/*CCS Control is OFF*/
	G_CCS_State_Control = E_OFF;
	G_Accelerator_Control = E_ON;
	G_Break_Control = E_ON;
	Show_Page();
	//	Speed_Limit_Mode(E_OFF);

	//	Speed_Limit_Set();
	Break_Button();			/*Break function with interrupt*/
	CCS_Button();


}


/*--------------------------------------------------------------------------------------------*/
/*   Drive Func    */
/*--------------------------------------------------------------------------------------------*/

void Direct_Mode_Func(void){
	//	/*CCS Control is OFF*
	G_CCS_State_Control = E_OFF;
	G_Accelerator_Control = E_ON;
	G_Break_Control = E_ON;
	Show_Page();

	Display_Speed();
	Speed_Limit_Set();
	Break_Button();			/*Break function with interrupt*/
	CCS_Button();

	//	relay_Mode(u8 Mode);
	//	Menu_On_Screen(E_PAGE_3);
	//	if((page == E_PAGE_3) && (g_DriveModeState ==  E_Mode_Drive) ){
	//
	//			Speed_Limit_Set();
	//			}else{
	//				Speed_Limit_Mode(E_OFF);
	//			}



}

/*--------------------------------------------------------------------------------------------*/
/*   Reverse Func    */
/*--------------------------------------------------------------------------------------------*/

void Reverse_Mode_Func(void){

	/*CCS Control is OFF*/
	G_CCS_State_Control = E_OFF;
	G_Accelerator_Control = E_ON;
	G_Break_Control = E_ON;
	Show_Page();

	//	Speed_Limit_Set();


	Break_Button();			/*Break function with interrupt*/
	CCS_Button();





}


///*Function get reading from pot ADC */
//u16 Print_Speed(void){
//	u16 Speed = M_ADC_U16_ADCRead(ADC_CHANNEL_0); // Read ADC value from channel A0
//	// Scale the ADC value to represent distance
//	Speed = (300 * Speed) /511;
//	return Speed;
//}

void Drive_Mode (void){

	switch (Drive_Mode_Counter){

	case 0 :
		g_DriveModeState = E_Mode_Normal;
		printDriveMode(g_DriveModeState);

		break ;

	case 1 :
		g_DriveModeState = E_Mode_Drive;
		printDriveMode(g_DriveModeState);
		break ;

	case 2 :
		g_DriveModeState =E_Mode_Reverse;
		printDriveMode(g_DriveModeState);
		break ;

	default :
		break;

	}


}




void Menu_On_Screen(u8 page){

	//	u8 flag=0;

	//	static u8 flag= E_OFF;
	H_Lcd_Void_LCDClear();


	//	if(G_PAGE == E_PAGE_1){
	//
	//		H_Lcd_Void_LCDGoTo(LCD_ROW_1,LCD_COL_01);
	//		H_Lcd_Void_LCDWriteString((u8*)"Gear Box: ");
	//
	//		H_LED_Void_LedToggle(E_LED_Red);
	//		H_Lcd_Void_LCDGoTo(LCD_ROW_4,LCD_COL_16);		/*page number 1*/
	//		H_Lcd_Void_LCDWriteString((u8*)"[1/3]");
	//		printDriveMode(g_DriveModeState);
	//		Show_Page();
	//
	//	}else if(G_PAGE == E_PAGE_2){
	//		H_Lcd_Void_LCDGoTo(LCD_ROW_1,LCD_COL_01);
	//		H_Lcd_Void_LCDWriteString((u8*)"CCS ");
	//
	//
	//		printCCRMode(G_CCS_State);
	//		CCS_Button();
	//
	//		H_Lcd_Void_LCDGoTo(LCD_ROW_4,LCD_COL_16);		/*page number 2*/
	//		H_Lcd_Void_LCDWriteString((u8*)"[2/3]");
	//
	//		Show_Page();
	//	}else if(G_PAGE == E_PAGE_3){
	//
	//		H_Lcd_Void_LCDGoTo(LCD_ROW_1,LCD_COL_02);
	//		H_Lcd_Void_LCDWriteString((u8*)"Speed");
	//
	//		H_Lcd_Void_LCDGoTo(LCD_ROW_1,LCD_COL_09);
	//		H_Lcd_Void_LCDWriteString((u8*)"Speed limit");
	//
	//
	//		H_Lcd_Void_LCDGoTo(LCD_ROW_1,LCD_COL_08);
	//		H_Lcd_Void_LCDWriteString((u8*)"|");
	//		H_Lcd_Void_LCDGoTo(LCD_ROW_2,LCD_COL_08);
	//		H_Lcd_Void_LCDWriteString((u8*)"|");
	//		H_Lcd_Void_LCDGoTo(LCD_ROW_3,LCD_COL_08);
	//		H_Lcd_Void_LCDWriteString((u8*)"|");
	//		H_Lcd_Void_LCDGoTo(LCD_ROW_4,LCD_COL_08);
	//		H_Lcd_Void_LCDWriteString((u8*)"|");
	//
	//
	//		H_Lcd_Void_LCDGoTo(LCD_ROW_4,LCD_COL_16);		/*page number 3*/
	//		H_Lcd_Void_LCDWriteString((u8*)"[3/3]");
	//
	//
	//		Speed_Limit_Set();
	//		//		G_CCS_State_Control = E_ON;
	//
	//		//		Direct_Mode_Func();
	//
	//		//		if(E_OFF == flag){
	//		////			Speed_Limit_Mode(E_OFF);		/*Make it Off for the first time*/
	//		//			flag++;
	//		//		}else{
	//		//
	//		//		}
	//
	//		//		printDriveMode(E_Mode_Drive);
	//		//		if((page == E_PAGE_3) && (g_DriveModeState ==  E_Mode_Drive) ){
	//		//
	//		//		Speed_Limit_Set();
	//		//		}else{
	//		//			Speed_Limit_Mode(E_OFF);
	//		//		}
	//		Display_Speed();
	//
	//		Show_Page();
	//	}



	switch (page) {

	case E_PAGE_1:

		H_Lcd_Void_LCDGoTo(LCD_ROW_1,LCD_COL_01);
		H_Lcd_Void_LCDWriteString((u8*)"Gear Box: ");

		H_LED_Void_LedToggle(E_LED_Red);
		H_Lcd_Void_LCDGoTo(LCD_ROW_4,LCD_COL_16);		/*page number 1*/
		H_Lcd_Void_LCDWriteString((u8*)"[1/3]");
		printDriveMode(g_DriveModeState);

		break;

	case E_PAGE_2:
		H_Lcd_Void_LCDGoTo(LCD_ROW_1,LCD_COL_01);
		H_Lcd_Void_LCDWriteString((u8*)"CCS ");


		printCCRMode(G_CCS_State);
		CCS_Button();

		H_Lcd_Void_LCDGoTo(LCD_ROW_4,LCD_COL_16);		/*page number 2*/
		H_Lcd_Void_LCDWriteString((u8*)"[2/3]");
		break;

	case E_PAGE_3:
		//		do{

		H_Lcd_Void_LCDGoTo(LCD_ROW_1,LCD_COL_02);
		H_Lcd_Void_LCDWriteString((u8*)"Speed");

		H_Lcd_Void_LCDGoTo(LCD_ROW_1,LCD_COL_09);
		H_Lcd_Void_LCDWriteString((u8*)"Speed limit");


		H_Lcd_Void_LCDGoTo(LCD_ROW_1,LCD_COL_08);
		H_Lcd_Void_LCDWriteString((u8*)"|");
		H_Lcd_Void_LCDGoTo(LCD_ROW_2,LCD_COL_08);
		H_Lcd_Void_LCDWriteString((u8*)"|");
		H_Lcd_Void_LCDGoTo(LCD_ROW_3,LCD_COL_08);
		H_Lcd_Void_LCDWriteString((u8*)"|");
		H_Lcd_Void_LCDGoTo(LCD_ROW_4,LCD_COL_08);
		H_Lcd_Void_LCDWriteString((u8*)"|");


		H_Lcd_Void_LCDGoTo(LCD_ROW_4,LCD_COL_16);		/*page number 3*/
		H_Lcd_Void_LCDWriteString((u8*)"[3/3]");


		Speed_Limit_Set();
		Display_Speed();

		//		G_CCS_State_Control = E_ON;

		//		Direct_Mode_Func();

		//		if(E_OFF == flag){
		////			Speed_Limit_Mode(E_OFF);		/*Make it Off for the first time*/
		//			flag++;
		//		}else{
		//
		//		}

		//		printDriveMode(E_Mode_Drive);
		//		if((page == E_PAGE_3) && (g_DriveModeState ==  E_Mode_Drive) ){
		//
		//		Speed_Limit_Set();
		//		}else{
		//			Speed_Limit_Mode(E_OFF);
		//		}
		//			Display_Speed();

		//			Show_Page();

		//		}while(G_PAGE == E_PAGE_2 );

		break;

	default:
		break;
	}

}



void Show_Page(void){
	u8 KeyVal;
	KeyVal = H_KeyPad_U8_KeyPadRead();


	if('8' == KeyVal ){
		if(G_PAGE < 3){
			Menu_On_Screen(G_PAGE);
			G_PAGE++;
		}else{
			G_PAGE = E_PAGE_1;
		}
	}

}



void printDriveMode(DRIVE_MODE_E mode) {

	H_Lcd_Void_LCDGoTo(LCD_ROW_2,LCD_COL_05);

	switch (mode) {
	case E_Mode_Drive:
		H_Lcd_Void_LCDWriteString((u8*)" N  R (D) ");
		break;
	case E_Mode_Normal:
		H_Lcd_Void_LCDWriteString((u8*)"(N) R  D ");
		break;
	case E_Mode_Reverse:
		H_Lcd_Void_LCDWriteString((u8*)" N (R) D ");
		break;
	default:
		break;
	}
}

void Speed_Limit_Mode(u8 mode){
	H_Lcd_Void_LCDGoTo(LCD_ROW_2,LCD_COL_12);
	H_Lcd_Void_LCDWriteString((u8*)"           ");
	H_Lcd_Void_LCDGoTo(LCD_ROW_2,LCD_COL_12);

	if(E_OFF == mode){
		set_relay_Mode(E_OFF); // Ensure the relay is off
		H_Lcd_Void_LCDWriteString((u8*)"OFF   ");


	}else if(E_ON == mode){
		/*H_Lcd_Void_LCDWriteString((u8)"ON");*/   	/*print the value not "ON "*/
		H_Lcd_Void_LCDWriteNumber(G_SpeedLimit);
	}
}

//void Speed_Limit_Set(void){
//	u8 key;
//	static u8 flag = E_OFF; // Initialize flag to E_OFF and make it static so its value persists between function calls
//
//	H_Lcd_Void_LCDGoTo(LCD_ROW_2,LCD_COL_10);
//	key = H_KeyPad_U8_KeyPadRead();
//	//	_delay_ms(100);
//	if('1' == key){
//		if((G_SpeedLimit >= 0) &&  (G_SpeedLimit < 200) ){
//			G_SpeedLimit += 5;
//
//		}else if(G_SpeedLimit == 200){
//			G_SpeedLimit =200;
//		}
//
//
////		H_Lcd_Void_LCDWriteNumber(G_SpeedLimit);
//
//	} else if('7' == key){
//
//		if(G_SpeedLimit < 200  ){
//			G_SpeedLimit -= 5;
//
//		}else if(G_SpeedLimit == 0){
//			G_SpeedLimit = 0;
//		}
//
//		G_SpeedLimit -= 5;
//		H_Lcd_Void_LCDWriteNumber(G_SpeedLimit);
//		H_Lcd_Void_LCDWriteString((u8*)" ");
//
//
//	} else if('4' == key){
//		if(flag == E_OFF){
//			Speed_Limit_Mode(E_ON);
//			flag = E_ON; // Set flag to E_ON when switching the mode
//		} else {
//			Speed_Limit_Mode(E_OFF);
//			flag = E_OFF; // Set flag back to E_OFF when switching the mode
//		}
//	} else {
//		/* Do Nothing */
//	}
//}




void Speed_Limit_Set(void){
	u8 key;
	static u8 flag = E_OFF; // Initialize flag to E_OFF and make it static so its value persists between function calls

	H_Lcd_Void_LCDGoTo(LCD_ROW_2,LCD_COL_12);
	key = H_KeyPad_U8_KeyPadRead();
	// _delay_ms(100); // Optional delay, not needed here
	if('1' == key){
		if((G_SpeedLimit >= 0) && (G_SpeedLimit < 100)){
			G_SpeedLimit += 5;
		} else {
			/*Do Nothing*/
		}

		H_Lcd_Void_LCDWriteNumber(G_SpeedLimit);
		H_Lcd_Void_LCDWriteString((u8*)"       ");


	} else if('7' == key){
		if(G_SpeedLimit >= 5){
			G_SpeedLimit -= 5;
		} else{
			/*Do Nothing*/
		}

		H_Lcd_Void_LCDWriteNumber(G_SpeedLimit);
		H_Lcd_Void_LCDWriteString((u8*)"       ");


	} else if('4' == key){
		if(flag == E_OFF){
			Speed_Limit_Mode(E_ON);
			flag = E_ON; // Set flag to E_ON when switching the mode
			relay_flag = 0 ;
		} else {
			Speed_Limit_Mode(E_OFF);
			flag = E_OFF; // Set flag back to E_OFF when switching the mode
			relay_flag = 1 ;
		}
	} else {
		/* Do Nothing */
	}
}

//
//void Speed_Limit_Set(void){
//    u8 key;
//    static u8 flag = E_OFF; // Initialize flag to E_OFF and make it static so its value persists between function calls
//
//    H_Lcd_Void_LCDGoTo(LCD_ROW_2,LCD_COL_10);
//    key = H_KeyPad_U8_KeyPadRead();
//    // _delay_ms(100); // Optional delay, not needed here
//    if('1' == key){
//        if((G_Speed >= 0) && (G_Speed < 200)){
//            G_Speed += 5;
//        } else if(G_Speed == 200){
//            G_Speed = 200; // Unnecessary, but left for consistency
//        }
//
//        H_Lcd_Void_LCDWriteNumber(G_Speed);
//		H_Lcd_Void_LCDWriteString((u8*)" ");
//
//
//    } else if('7' == key){
//        if(G_Speed > 0){
//            G_Speed -= 5;
//        } else if(G_Speed == 0){
//            G_Speed = 0; // Unnecessary, but left for consistency
//        }
//
//
//        H_Lcd_Void_LCDWriteNumber(G_Speed);
//		H_Lcd_Void_LCDWriteString((u8*)" ");
//
//
//    } else if('4' == key){
//        if(flag == E_OFF){
//            Speed_Limit_Mode(E_ON);
//            flag = E_ON; // Set flag to E_ON when switching the mode
//        } else {
//            Speed_Limit_Mode(E_OFF);
//            flag = E_OFF; // Set flag back to E_OFF when switching the mode
//        }
//    } else {
//        /* Do Nothing */
//    }
//}


///*Function get reading from pot ADC */
void  Display_Speed(void){
	G_Speed = M_ADC_U16_ADCRead(ADC_CHANNEL_0); // Read ADC value from channel A0
	H_Lcd_Void_LCDGoTo(LCD_ROW_4,LCD_COL_05);
	H_Lcd_Void_LCDWriteNumber(G_Speed);

	// Scale the ADC value to represent distance
	// Map ADC value from 0-1023 to 0-300
	G_Speed = (200 * (u32)G_Speed) /1023;
	H_Lcd_Void_LCDGoTo(LCD_ROW_2,LCD_COL_03);
	H_Lcd_Void_LCDWriteNumber(G_Speed);




}


//void Display_Speed(void){
//    uint16_t adc_reading = M_ADC_U16_ADCRead(ADC_CHANNEL_0); // Read ADC value from channel A0
//    // Map ADC value from 0-1023 to 0-300
//    G_Speed = ((u32)adc_reading * 300) / 1023;
//
//    H_Lcd_Void_LCDGoTo(LCD_ROW_2, LCD_COL_05);
//    H_Lcd_Void_LCDWriteNumber(G_Speed);
//}



// Define a variable to keep track of the current state of the relay
//static u8 relay_state = E_OFF;

// Function to toggle the relay mode
void toggle_or_set_relay_Mode(void) {
	if (relay_state == E_OFF) {
		relay_state = E_ON;
		M_DIO_Void_SetPinValue(PC7_PIN, HIGH);
	} else {
		relay_state = E_OFF;
		M_DIO_Void_SetPinValue(PC7_PIN, LOW);
	}
}

// Function to set the relay mode directly
void set_relay_Mode(u8 Mode) {
	if (Mode == E_OFF) {
		M_DIO_Void_SetPinValue(PC7_PIN, LOW);
	} else if (Mode == E_ON) {
		M_DIO_Void_SetPinValue(PC7_PIN, HIGH);
	}
}

void Speed_alert(void) {
	if ((G_Speed > G_SpeedLimit) && (relay_flag == 0)) {
		set_relay_Mode(E_ON); // Turn on the relay
		_delay_ms(250);
		set_relay_Mode(E_OFF); // Turn off the relay
		_delay_ms(250);
	} else {
		set_relay_Mode(E_OFF); // Ensure the relay is off
	}
}



