#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Timer0.h"
#include "DIO_int.h"
#include "LCD_int.h"
#include "GIE_int.h"
#include <util/delay.h>
/********************************************
 *macros to make code more portable and readable
 *********************************************/

/*********************************************
 * Define the Devices of SSD which is 4 in our case
 *********************************************/
#define SYSTEM_SSD_DEVICES					(4)
/*********************************************
 * Define the ports of SSD control and Data
 * also define the switches port
 *********************************************/
#define SYSTEM_SSD_DEVICES_CONTROL_PORT		DIO_PORTD
#define SYSTEM_SSD_DATA_PORT				DIO_PORTC
#define SYSTEM_SWITCHES_PORT				DIO_PORTA
/**********************************************
 * Define the places number which is 8 in our simple garage
 **********************************************/
#define SYSTEM_PLACES_NUMBER 				(8)
/**********************************************
 * Define macros to the state of gate 1 and 2 if it opened
 **********************************************/
#define FIRST_GATE_OPENED					(1)
#define SECOND_GATE_OPENED					(1)
/**********************************************
 * None message if there is no empty slot
 **********************************************/
#define NONE_MESSAGE_CODE 					(8)
/**********************************************
 * Enum to define the 4 seven sgements this is done
 * to make code more readable this is our own data type
 **********************************************/
typedef enum {
	FIRST_SSD  = 0,
	SECOND_SSD,
	THIRD_SSD,
	FOURTH_SSD,
} SystemSSD_t;
/**********************************************
 * enum to define the state of our slot if it's avalibale or not avilable
 **********************************************/
typedef enum {
	NOT_AVALIABLE = 0,
	AVALIABLE,
} PlaceState_t;
/**********************************************
 *Common Cathode
 *enum to define the numbers in SSD this number is being represented according to
 *enum which led would be illuminate to make the corrosponding number
 **********************************************/
typedef enum {
	ZERO_C = 0b00111111,
	ONE_C = 0b00000110,
	TWO_C = 0b01011011,
	THREE_C = 0b01001111,
	FOUR_C = 0b01100110,
	FIVE_C = 0b01101101,
	SIX_C = 0b01111101,
	SEVEN_C = 0b00000111,
	EIGHT_C = 0b11111111,
	NINE_C  = 0b01101111
} SSD_NumbersCathode;

/**********************************************
 * this is array of type SSD_NumbersCathode that we've decleared
 * it carries the numbers with relative to it's index
 * so index 0 carry number 0 in seven segement
 * index 1 caary number 1 in seven segment
 * and so on
 * static keyword to make it static in this file only
 **********************************************/
static const SSD_NumbersCathode CGS_u8SSD_Nums[10] = {ZERO_C, ONE_C, TWO_C, THREE_C, FOUR_C, FIVE_C, SIX_C, SEVEN_C, EIGHT_C, NINE_C};
/**********************************************
 *ths is the array that caary the best direction for every slot in garage relative to gate 1
 **********************************************/
static u8 *firstGateMessages[9]  = {"FL1L1", "FR1R1", "FL2R1", "FR1L1", "SL1L1", "SR1R1", "SL2R1", "SR1L1", "None"};
/**********************************************
 *ths is the array that caary the best direction for every slot in garage relative to gate 2
 **********************************************/
static u8 *secondGateMessages[9] = {"SL1L1", "SR1R1", "SL2R1", "SR1L1", "FL1L1", "FR1R1", "FL2R1", "FR1L1", "None"};
/**************************************************************
 * set intial value to the sortest path index relative to first gate
 * it will be updated shortly
 **************************************************************/
static s8 shortestPathIndexFirstGate  = NONE_MESSAGE_CODE;
/**************************************************************
 * set intial value to the sortest path index relative to Second gate
 * it will be updated shortly
 **************************************************************/
static s8 shortestPathIndexSecondGate = NONE_MESSAGE_CODE;
/**************************************************************
 *define array of type SystemSSD_t that would carry the value of first and scond
 *and third and fourth ssd only
 *this array would carry the 4 seven segement data
 **************************************************************/
static SystemSSD_t systemSSDs[SYSTEM_SSD_DEVICES];
/*************************************************************
 * delcelare array of type placestate that is carry avilable and not avilable
 * of 8 length this array would carry intillay avilabale
 ************************************************************/
static PlaceState_t places[SYSTEM_PLACES_NUMBER] = {1, 1, 1, 1, 1, 1, 1, 1};
/*************************************************************
 * variable that would carry the total avibale places
 ************************************************************/
static u8 totalAvailablePlaces;
/*************************************************************
 * flags of gate 1 and 2 that is it's raisen up indicate that the gate is opened
 ************************************************************/
static u8 firstGateOpenedFlag  = 0;
static u8 secondGateOpenedFlag = 0;
/*************************************************************
 * first task this task if responsible of managing the seven segment display
 * it will turn on only one and off the previous one frequently
 * each time it's called it will do this task
 ************************************************************/
void SevenSegmentsDisplayTask(void) {
	/*************************************************************
	 * start by setting prevssd to the first ssd becaue it will be first one
	 ************************************************************/
	static SystemSSD_t prevSSD = FIRST_SSD;
	/*************************************************************
	 * this is equation to get the current SSD everytime
	 ************************************************************/
	SystemSSD_t	currentSSD = (prevSSD + 1) % (SYSTEM_SSD_DEVICES);
	/* Disable previous SSD */
	DIO_vSetPinVal(SYSTEM_SSD_DEVICES_CONTROL_PORT, prevSSD, DIO_HIGH);
	/* Enable Current SSD */
	DIO_vSetPinVal(SYSTEM_SSD_DEVICES_CONTROL_PORT, currentSSD, DIO_LOW);
	/* Write data to the seven segment port */
	DIO_vSetPinVal(SYSTEM_SSD_DATA_PORT, DIO_PIN0, GET_BIT(CGS_u8SSD_Nums[systemSSDs[currentSSD]], 0));
	DIO_vSetPinVal(SYSTEM_SSD_DATA_PORT, DIO_PIN1, GET_BIT(CGS_u8SSD_Nums[systemSSDs[currentSSD]], 1));
	DIO_vSetPinVal(SYSTEM_SSD_DATA_PORT, DIO_PIN2, GET_BIT(CGS_u8SSD_Nums[systemSSDs[currentSSD]], 2));
	DIO_vSetPinVal(SYSTEM_SSD_DATA_PORT, DIO_PIN3, GET_BIT(CGS_u8SSD_Nums[systemSSDs[currentSSD]], 3));
	DIO_vSetPinVal(SYSTEM_SSD_DATA_PORT, DIO_PIN4, GET_BIT(CGS_u8SSD_Nums[systemSSDs[currentSSD]], 4));
	DIO_vSetPinVal(SYSTEM_SSD_DATA_PORT, DIO_PIN5, GET_BIT(CGS_u8SSD_Nums[systemSSDs[currentSSD]], 5));
	DIO_vSetPinVal(SYSTEM_SSD_DATA_PORT, DIO_PIN6, GET_BIT(CGS_u8SSD_Nums[systemSSDs[currentSSD]], 6));

	/* Set current SSD to the previous variable for the next call */
	prevSSD = currentSSD;
}
/*************************************************************
 * Second task that would manage the problem of places (slots)
 * and it will manage the gates also
 * this is to manage all sensors in our system which in our case
 * would be dip switches
 ************************************************************/
void GetPlacesStatus(void) {
	/*************************************************************
	 * decleare local variable but they are static to gate 1 and the flat of it
	 ************************************************************/
	static u8 Gate1;
	static u8 flagGate1 = 1;

	/*************************************************************
	 * decleare local variable but they are static to gate 2 and the flat of it
	 ************************************************************/
	static u8 Gate2;
	static u8 flagGate2 = 1;
	/*************************************************************
	 * get the switches values to see if they are avilable or not
	 ************************************************************/
	places[0] = DIO_u8GetPinVal(SYSTEM_SWITCHES_PORT, 0);
	places[1] = DIO_u8GetPinVal(SYSTEM_SWITCHES_PORT, 1);
	places[2] = DIO_u8GetPinVal(SYSTEM_SWITCHES_PORT, 2);
	places[3] = DIO_u8GetPinVal(SYSTEM_SWITCHES_PORT, 3);
	places[4] = DIO_u8GetPinVal(SYSTEM_SWITCHES_PORT, 4);
	places[5] = DIO_u8GetPinVal(SYSTEM_SWITCHES_PORT, 5);
	places[6] = DIO_u8GetPinVal(SYSTEM_SWITCHES_PORT, 6);
	places[7] = DIO_u8GetPinVal(SYSTEM_SWITCHES_PORT, 7);
	/*************************************************************
	 *getting data of gates pins
	 ************************************************************/
	Gate1 = DIO_u8GetPinVal(SYSTEM_SSD_DATA_PORT, 7);
	Gate2 = DIO_u8GetPinVal(SYSTEM_SSD_DEVICES_CONTROL_PORT, 7);
	/************************************************
	 * gate 1 dealing with the flag and process it to deal only with the raising edge
	 * of the gate switch
	 ********************************************/
	if(Gate1 == DIO_LOW && flagGate1 == 1) {
		firstGateOpenedFlag = 1;
		flagGate1 = 0;
	}
	else if(Gate1 == DIO_HIGH){
		flagGate1 = 1;
	}
	/************************************************
	 * gate 2 dealing with the flag and process it to deal only with the raising edge
	 * of the gate switch
	 ********************************************/
	if(Gate2 == DIO_LOW && flagGate2 == 1) {
		secondGateOpenedFlag = 1;
		flagGate2 = 0;
	}
	else if(Gate2 == DIO_HIGH) {
		flagGate2 = 1;
	}
	/***************************************************
	 * update the array of seven segment values according to the slot status
	 * so we sum up the total slots in each sub plane
	 ***************************************************/
	systemSSDs[FIRST_SSD]   = places[0] + places[2];
	systemSSDs[SECOND_SSD]  = places[1] + places[3];
	systemSSDs[THIRD_SSD]   = places[4] + places[6];
	systemSSDs[FOURTH_SSD]  = places[5] + places[7];

	/****************************************
	 * calculating total places
	 ***************************************/
	/* Calculating the total available places */
	totalAvailablePlaces = systemSSDs[FIRST_SSD] + systemSSDs[SECOND_SSD] + systemSSDs[THIRD_SSD]  + systemSSDs[FOURTH_SSD];
}
/*******************************************************
 * third task is about LCD display
 * it manage the display info in the LCD
 * this task will output normaly the total avilable places
 * and avilable places in each subplane
 * if gate 1 raising edge is detected or gate 2 raising edge
 * it will raise the shortest path for some seconds
 ******************************************************/
void LCD_Display(void) {
	/*************************************************************
	 * first getting the shortest path index from gate 1 and gate 2
	 *************************************************************/
	/* Getting the shortest path */
	//intial values
	static u8 L_u8LcdStateFlag = 0;
	static u8 L_u8Counter = 0;
	s8 i;
	shortestPathIndexFirstGate  = NONE_MESSAGE_CODE;
	shortestPathIndexSecondGate = NONE_MESSAGE_CODE;
	/**************************************************
	 * GATE 1
	 * for loop to check for the nearset avilable place
	 * this method is following priorty base algorithm for our slots
	 * linear search
	 **************************************************/
	for(i = 0; i < SYSTEM_PLACES_NUMBER; i++) {
		if(places[i] == AVALIABLE) {
			shortestPathIndexFirstGate = i;
			break;
		}
	}
	/***************************************************
	 * GATE 2
	 * for loop to check for the nearset avilable place
	 * this method is following priorty base algorithm for our slots
	 * linear search
	 **************************************************/
	for(i = SYSTEM_PLACES_NUMBER - 1; i >= 0; i--) {
		if(places[i] == AVALIABLE) {
			shortestPathIndexSecondGate = i;
			break;
		}
	}
	/*****************************************************
	 * update the shortest path index because it will be reversed to the original
	 * arrangement
	 ****************************************************/
	shortestPathIndexSecondGate = SYSTEM_PLACES_NUMBER - i - 1;

	/*************************************************
	 * this will appear if the flag of gate 1 is raisen up it will
	 * output those messages for some seconds
	 *************************************************/
	if(firstGateOpenedFlag == 1) {
		L_u8Counter++;
		HLCD_vClearScreen();
		HLCD_vSendString("Gate1 Welcome");
		HLCD_vGoToRowCol(1, 0);
		HLCD_vSendString("SP:");
		HLCD_vSendString(firstGateMessages[shortestPathIndexFirstGate]);
		if(L_u8Counter == 4) {
			firstGateOpenedFlag = 0;
			L_u8Counter = 0;
		}
	}
	/*************************************************
	 * this will appear if the flag of gate 2 is raisen up it will
	 * output those messages for some seconds
	 *************************************************/
	else if(secondGateOpenedFlag == 1) {
		L_u8Counter++;
		HLCD_vClearScreen();
		HLCD_vSendString("Gate2 Welcome");
		HLCD_vGoToRowCol(1, 0);
		HLCD_vSendString("SP:");
		HLCD_vSendString(secondGateMessages[shortestPathIndexSecondGate]);
		if(L_u8Counter == 4) {
			secondGateOpenedFlag = 0;
			L_u8Counter = 0;
		}
	}
	/***************************************
	 * this will appear if no flag is raisen up normally
	 * it would appear those messages
	 ***************************************/
	else {
		HLCD_vClearScreen();
		HLCD_vSendString("T=");
		HLCD_vSendData('0' + totalAvailablePlaces);
		HLCD_vGoToRowCol(1, 0);
		HLCD_vSendString("F=");
		HLCD_vSendData(systemSSDs[FIRST_SSD] + systemSSDs[SECOND_SSD] + '0');
		HLCD_vSendString(", S=");
		HLCD_vSendData(systemSSDs[THIRD_SSD] + systemSSDs[FOURTH_SSD] + '0');
	}
}


int main(void) {
	/******************************************
	 * intilization step for ssd data port pins
	 *****************************************/
	DIO_vSetPortDir(SYSTEM_SSD_DATA_PORT, 0xFF);
	/***********************************************
	 * intilization for timer zero that will be used in schedular
	 **********************************************/
	TIMERZERO_vInit();
	/***********************************************
	 * intilizing LCD to be used later on
	 **********************************************/
	HLCD_vInit();
	/***********************************************
	 * intilizing control port
	 **********************************************/
	DIO_vSetPortDir(DIO_PORTD, 0xFF);
	/*********************************************
	 *intliziing system switches PORT
	 ********************************************/
	DIO_vSetPortDir(SYSTEM_SWITCHES_PORT, 0x00);
	/********************************************
	 * Activating pull up resistor for switches
	 *******************************************/
	DIO_vSetPortVal(SYSTEM_SWITCHES_PORT, 0xFF);
	/***********************************************
	 *enable global interrupt
	 **********************************************/
	GIE_vEnable();
	/***********************************************
	 * creating our taks
	 * with peridocity 8,207,402
	 * and priority 0,1,2
	 * First delay 2,1,4
	 **********************************************/
	RTOS_u8CreateTask(SevenSegmentsDisplayTask, 8, 0, 2);
	RTOS_u8CreateTask(GetPlacesStatus, 207, 1, 1);
	RTOS_u8CreateTask(LCD_Display , 402, 2, 4);
	/***********************************************
	 * starting our operating system
	 **********************************************/
	RTOS_voidStartOS();

	while(1) {
		//empty because we run real time operating system

	}

	return 0;
}
