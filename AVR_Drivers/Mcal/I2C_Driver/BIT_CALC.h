/*
 * BIT_CALC.h
 *
 *  Created on: May 5, 2023
 *      Author: abdo
 */

#ifndef BIT_CALC_H_
#define BIT_CALC_H_

#define Set_Bit(Var,Bit_No) (Var) |= (1<<(Bit_No))
#define Clear_Bit(Var,Bit_No) (Var) &= (~(1<<(Bit_No)))
#define Toggle_Bit(Var,Bit_No) (Var) ^= (1<<(Bit_No))
#define Get_Bit(Var,Bit_No) (((Var)>>(Bit_No)) & (1))
#define Assign_Bit(Var,Bit_No,Value) do{ if((Value) == 1) Set_Bit(Var,Bit_No);\
	else Clear_Bit(Var,Bit_No);} while(0)

#endif /* BIT_CALC_H_ */
