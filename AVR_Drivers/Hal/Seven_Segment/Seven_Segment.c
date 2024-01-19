/*
 * Seven_Segment.c
 *
 *  Created on: Jan 17, 2024
 *      Author: omar
 */


#include "MemoryMap.h"
#include "STD_TYPES.h"
#include "Macros.h"
#include "Bit_calc.h"
#include "Dio.h"
#include "Seven_Segment.h"


void SevenSegment_Init (void){


	Dio_u8_SetPortDir(Seven_Segment_Dircetion, Dio_PortOutput);

}

void SevenSegment_Write ( u8 Number){



	#if Seven_Segment_Mode == Common_Cathod
	u8 arr[]={0b01111110 ,// 0
              0b00110000 , // 1
			 0b01101101 , // 2
			 0b01111001,  // 3
			 0b00110011,  // 4
			 0b01011011,  // 5
			 0b01011111 , // 6
			 0b01110000 , // 7
             0b01111111,  // 8
			 0b01111011}; // 9



	Seven_Segment_PORT = arr[Number];

	#else if Seven_Segment_Mode == Common_Anode
			u8 array [] =				  {0b10000000 , // display '0'
	                                      0b1100111 , // display '1'
	                                      0b1001001, // display '2'
	                                      0b1000011, // display '3'
	                                      0b1100110, // display '4'
	                                      0b1010010, // display '5'
	                                      0b1010000, // display '6'
	                                      0b1000111, // display '7'
	                                      0b1000000, // display '8'
	                                      0b1000110}; // display '9'
			Seven_Segment_PORT = array[Number];

	#endif
}
