#ifndef MCAL_GIE_GIE_INT_H_
#define MCAL_GIE_GIE_INT_H_
/*************************************************************
 * this file is to enable the global interrupt or disable it to
 * control the interrupt enable or disable
 *************************************************************/
#define SREG (*((volatile u8*)(0x5F)))
/*******************************************************
function decription
enable the glocal interrupt
********************************************************/
void GIE_vEnable(void);
/*******************************************************
function decription
disable the glocal interrupt
********************************************************/
void GIE_vDisable(void);

#endif /* MCAL_GIE_GIE_INT_H_ */
