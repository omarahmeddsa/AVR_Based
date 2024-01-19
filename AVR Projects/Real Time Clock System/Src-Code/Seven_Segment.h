/*
 * Seven_Segment.h
 *
 *  Created on: Jan 17, 2024
 *      Author: omar
 */

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

/*****************************************************************
 *
 * Macros
 *
 ****************************************************************/



// The two Modes od the Seven Segment
#define Common_Anode      0
#define Common_Cathod     1
// Config
/*****
 * Common_Cathod
** Common_Anode
****** */

#define Seven_Segment_Mode  Common_Cathod
#define Seven_Segment_Dircetion  Group_B
#define Seven_Segment_PORT       DIO_U8_PORTB
/********************************/
void SevenSegment_Init(void);
void SevenSegment_Write ( u8 Number);

#endif /* SEVEN_SEGMENT_H_ */
