#include "stdio.h"

/****************************************************************************************
 * 
 * Descrpition : This project aims to design a system for a car 
 * The system of the Vechile contains a temprature Controller and Engine Temprature Controller and Speed Controller and Sensors 
 * 
******************************************************************************************/


/****DEfiniations****/
#define State_ON 1 
#define State_OFF 0
/****Bouns Question***/

/************************************************************************************************************************************
*The directive below enable us to choose to turn the engine Temprature controller ON or OFF 
*If the user choose  State off the Controller will not excute any instructions related to Engine temprature Controller and vica-versa 
**************************************************************************************************************************************/
/*Options 
*State_ON
*State_OFF
*/
#define WITH_ENGINE_TEMP_CONTROLLER State_OFF 

/********ENUMS**********/
typedef enum {

	Turn_ON_the_Vehicle_Engine = 'a',    /*****Enum For The Vechile Engine Statment******/
	Turn_OFF_the_Vehicle_Engine ,
	Quit_the_System
}Vechile_Engine_Statment;

typedef enum {
	 Green = 'g',
	 Oragne = 'o',
	 Red    =  'r'
}Sensor_Value;

/*************Global Variables**************/
int Vechile_speed;
int AC_Temp;
int Room_Temp;
int AC_state;

int Engine_Temp;
int Engine_Temp_CTRL ;
int Engine_TempContller_State;
int Engine_State;

int Couter ;

/*****************Implemenation***************/



void Display_Function (){
	printf("\n");
	if (Engine_State ){

		printf("Engine Is ON\n");
	}

	else printf("Engine Is OFF\n");

	if (AC_state ){

		printf("AC is ON\n");

	}

	else{ printf("AC is OFF\n");}

	printf("Vechile Speed = %d\n", Vechile_speed);
	printf("Room Temparture = %d\n", AC_Temp);

	if (Engine_Temp_CTRL)
	printf("The Engine Temparture Controller State is ON");

	else {
		printf("The Engine Temparture Controller State is OFF\n");
	}

	printf("Engine Temparture = %d\n", Engine_Temp_CTRL);



}

int Set_Engine_Temp (){
/***********
 * If the State OFF the Instructions Below will not be excuted 
 * *************/
#if WITH_ENGINE_TEMP_CONTROLLER == State_ON 

printf("Entre Engine Temp\n");
scanf (" %d", &Engine_Temp);
printf("\n");

if ((Engine_Temp < 100 ) || (Engine_Temp > 150))
{
	printf("Engine Temprature Controller ON\n");
	Engine_Temp_CTRL = 125 ;	
}
else {
printf("Engine Temprature Controller OFF\n");
Engine_TempContller_State = State_OFF;}

	return Engine_TempContller_State;
#else 
	printf("\n");
	Engine_TempContller_State = State_OFF;
	printf("Wrong, The Controller Is OFF\n");

#endif
}

int Set_Room_Temp (){

	
	
	printf ("Entre The Room Temprature\n");
	scanf(" %d", &Room_Temp);
	printf("\n");

	if ((Room_Temp < 10) || (Room_Temp > 30)){
		
		printf("Turning ON AC\n");
		AC_Temp = 20 ;
		AC_state = State_ON;
		}
		
		else {
		printf("Turning AC OFF\n");
		AC_state = State_OFF;
		}
	return AC_state;
}


void Traffic_Light ( ){

	char Sensor_Read;
	printf("\n");
	printf("Entre the Traffic Light Color, Should Choose between (r,o,g) ,known that r for Red ....etc\n");
	scanf(" %c", &Sensor_Read);
	printf("\n");

	switch (Sensor_Read){
		
		case Green:
		Vechile_speed = 100 ;
		printf("The Vechile Speed is = %d Km/hr\n", Vechile_speed);
		break;

		case Oragne:
		Vechile_speed = 30 ;
		printf("The Vechile Speed is = %d Km/hr\n", Vechile_speed);
		break;

		case Red:
		Vechile_speed = 0 ;
		printf("The Vechile Speed is = %d Km/hr\n", Vechile_speed);
		break;

	}
		
}


void Sensors_Set_Menu(){

	/**Local Variables**/
	char Set_Menu;
	int x;
	/*************Pre-procesor*********/
 	#if WITH_ENGINE_TEMP_CONTROLLER == State_ON				
 	x = 3;
 	#else
	x= 2;	
 	#endif
	
	printf("\n");
	for (int i = 0 ; i < x ; i ++){	
	char *array []= 
	{"a.Turn off the engine"
	,"b.Set the traffic light color"
	,"c.Set the room temperature (Temperature Sensor)"
	,"d.Set the engine temperature (Engine Temperature Sensor)"};
	

		printf("\n");

		for (int i = 0 ; i < 4 ; ++i){

			printf("%s\n", array[i]);

	}

	
	scanf(" %c", &Set_Menu);
	printf("\n");

	switch (Set_Menu){
	case 'a':
	Start_Menu();
	break ;

	case 'b':
	Traffic_Light();
	break;

	case 'c':
	Set_Room_Temp();
	break;

	case 'd':
	Set_Engine_Temp();
	break;
	}
	}

}


void Start_Menu (){
		
		char State;
		
		printf("a.Turn on the vehicle engine\n");
		printf("b.Turn off the vehicle engine\n");
		printf("c.Quit the system\n");
		scanf(" %c", &State);
		printf("\n");


		switch (State) {
			case Turn_ON_the_Vehicle_Engine :
			printf("The Engine state is ON\n");
			Engine_State = State_ON;
			Sensors_Set_Menu();
			break;

			case Turn_OFF_the_Vehicle_Engine :
			printf("The Engine state is OFF\n");
			Engine_State = State_OFF;
			break;

			case Quit_the_System :
			printf("Quit the system\n");
			Start_Menu();
			break;	


}
}

void main (void ){
	/******ENUMS init**********/
	
	/*******Varibles init******/
	

	/********Super Loop********/
	
	while (1){
	
	printf("\n");
	printf("Welcome to the Vechile System\n");
	Start_Menu();
	
	if ((Vechile_speed == 30) && (!Set_Room_Temp())){

		AC_state = State_ON;
		AC_Temp = ((Room_Temp * (5/4))+1);
	}

	#if WITH_ENGINE_TEMP_CONTROLLER == State_ON 
	if ((Vechile_speed == 30 ) && (!Set_Engine_Temp())){

		Engine_State = State_ON;
		Engine_Temp_CTRL = ((Engine_Temp * (5/4))+1);

	}
	#else
		Engine_State = State_OFF;
		Engine_Temp_CTRL = 0;
	#endif 
	Display_Function ();
	}
}