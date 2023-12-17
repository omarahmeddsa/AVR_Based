#ifndef _RTOS_PRIVATE_H
#define _RTOS_PRIVATE_H
/******************************************************************
 * enum to define the state of the current task suspsended or running
 *******************************************************************/
typedef enum
{
	Suspended,
	Running
}RunState;

/********************************************************
 * this is struct to store the task information
 *******************************************************/

typedef struct
{
	void (*TaskHandler)(void)    ;
	u8        Periodicity        ;
	u8        FirstDelay         ;
	RunState  TaskRunState       ;
}Task;
/***********************************
 * this is scheculer prototype
 **********************************/
static void Scheduler(void);

#endif
