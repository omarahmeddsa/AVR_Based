/*
 * KPD.h
 *
 *  Created on: Oct 27, 2023
 *      Author: omar
 */

#ifndef KPD_H_
#define KPD_H_

#define NOTPRESSED 0xff

void KPD_Init (void );
u8  KPD_PRESSED (void );

#define KPD_PORT  Group_D

#define KPD_ROW_INIT  PIN0
#define KPD_ROW_END   PIN3

#define KPD_COL_INIT  PIN4
#define KPD_COL_END   PIN7

#define KPD_Row0  PIN0
#define KPD_Row1  PIN1
#define KPD_Row2  PIN2
#define KPD_Row3  PIN3

#define KPD_Col0  PIN4
#define KPD_Col1  PIN5
#define KPD_Col2  PIN6
#define KPD_Col3  PIN7



#endif /* KPD_H_ */
