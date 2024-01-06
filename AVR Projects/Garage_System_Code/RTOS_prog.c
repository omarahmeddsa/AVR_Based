#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Timer0.h"
#include "RTOS_interface.h"
#include "RTOS_config.h"
#include "RTOS_private.h"

/***********************************************
 * this is array of struct type to store the tasks
 ***********************************************/
Task SystemTasks[MAX_NUM_OF_TASKS] = {0};
/***********************************************
 * this is array of timming to store the time of tasks
 ***********************************************/
u8   TaskTiming [MAX_NUM_OF_TASKS];

/********************************************
 * this function is to start the operatng system by
 * calling the schedular every certain time
 * this time s being calculated by timer 0
 * that is operating in CTC mood
 *********************************************/
void RTOS_voidStartOS(void)
{
	TIMER_ZERO_SetInterval_CTC_Asynch(TickTime, Scheduler);
}
/**********************************************
 *the function is to create the task this tasks contain 4 inputs
 *the fisrt handler that is what this task do
 *the second is preiodicity that is the timme that this taskis called periodcily
 *the thirs if priority which offer the priorty of this task with other tasks
 *that means which one would be excuted firstly
 *********************************************/
u8 RTOS_u8CreateTask (  void(*Copy_Handler)(void) , u8 Copy_u8Periodicity, u8 Copy_u8Priority , u8 Copy_FirstD  )
{
	u8 Local_ErrorState = 0;
	
	/* Verify that the priority index within the correct range */
	if (Copy_u8Priority < MAX_NUM_OF_TASKS)
	{
		/***********************************************
		 * check if the task of this priorty is already empty
		 * if its empty go on and fill it with data
		 **********************************************/
		if (SystemTasks[Copy_u8Priority].TaskHandler == 0)
		{
			/***********************************************
			 * fill the data of task struct in the array ofstructres and task timming
			 **********************************************/
			SystemTasks[Copy_u8Priority].TaskHandler  = Copy_Handler;
			SystemTasks[Copy_u8Priority].Periodicity  = Copy_u8Periodicity;
			TaskTiming [Copy_u8Priority]              = Copy_FirstD;
			SystemTasks[Copy_u8Priority].TaskRunState = Running;
		}
		
		else
		{
			/***********************************************
			 * if The required priority is alread reserved return this error state
			 **********************************************/
			Local_ErrorState = 2;
		}
	}
	
	else
	{
		/***********************************************
		 * wring priorty and return back this error state
		 **********************************************/
		Local_ErrorState = 1;
		
	}
	
	return Local_ErrorState;
}

/***********************************************
 * schedular implementation that will be called every tick time
 **********************************************/
static void Scheduler(void)
{
	/***********************************************
	 * local counter to loop by it
	 **********************************************/
	u8 Local_Counter=0;
	
	/***********************************
	 * Loop on all Taks
	 ***********************************/
	for (Local_Counter =0; Local_Counter < MAX_NUM_OF_TASKS; Local_Counter++)
	{
		/****************************************************
		 * Is there a registered task ... ?
		 ***************************************************/
		if (SystemTasks[Local_Counter].TaskHandler != 0)
		{
		/***********************************************
		 *check if this task is running
		 **********************************************/
			if (SystemTasks[Local_Counter].TaskRunState == Running )
			{
				/***************************************
				 * if its the time of the task to be executed
				 **************************************/
				if (TaskTiming[Local_Counter] == 0)
				{
					/****************************************
					 * Run the task
					 ***************************************/
					SystemTasks[Local_Counter].TaskHandler();
				
					/****************************************
					 * Reload the periodicity
					 ***************************************/
					TaskTiming[Local_Counter] = SystemTasks[Local_Counter].Periodicity;
				}
			
				else 
				{
					TaskTiming[Local_Counter]--;
				}
			}
		}
	}
}


