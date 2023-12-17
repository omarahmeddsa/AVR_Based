#ifndef RTOS_INTERFACE_H
#define RTOS_INTERFACE_H

/*********************************************************
 function descreption
 this function create task to be added in schadeular
 it takes the function handler and priodcity and priority and the first delat of thie task
 *********************************************************/
u8 RTOS_u8CreateTask (  void(*Copy_Handler)(void) , u8 Copy_u8Periodicity, u8 Copy_u8Priority , u8 Copy_FirstD  );
/**********************************************************
function descreption
this function is to start the operation system
*********************************************************/
void RTOS_voidStartOS(void);



#endif
