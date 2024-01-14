/*
 * TWI_private.h
 *
 *  Created on: Nov 4, 2023
 *      Author: omar
 */

#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_

#define   TWI_U8_TWCR     *((volatile u8 *)0x56)
#define   TWI_U8_TWBR     *((volatile u8 *)0x20)
#define   TWI_U8_TWSR     *((volatile u8 *)0x21)
#define   TWI_U8_TWDR     *((volatile u8 *)0x23)
#define   TWI_U8_TWAR     *((volatile u8 *)0x22)



/*TWSR register */
#define TWI_TWPS0  0
#define TWI_TWPS1  1
#define TWI_TWS3   2
#define TWI_TWS4   3
#define TWI_TWS5   4
#define TWI_TWS6   5
#define TWI_TWS7   6
/* TWCR */
#define TWI_TWIE0  0
#define TWI_TWEN   2
#define TWI_TWWC   3
#define TWI_TWSTO  4
#define TWI_TWSTA  5
#define TWI_TWEA   6
#define TWI_TWINT  7
/*TWDR*/
#define TWI_TWD0   0
#define TWI_TWD1   1
#define TWI_TWD2   2
#define TWI_TWD3   3
#define TWI_TWD4   4
#define TWI_TWD5   5
#define TWI_TWD6   6
#define TWI_TWD7   7


/*ACK Code */
#define TWI_START_ACK            0x08
#define TWI_REP_START_ACk        0x10
#define TWI_MT_SLA_W_ACK         0x18
#define TWI_MT_SLA_R_ACK         0x40
#define TWI_MT_DATA_ACK          0x28
#define TWI_MR_DATA_ACK          0x50
#define TWI_MR_DATA_NACK         0x58
#define SLAVE_BYTE_TRANSMITTED   0xB8 /* means that the written byte is transmitted */
#define SLAVE_DATA_RECEIVED      0x80 /* means that a byte is received */

#endif /* TWI_PRIVATE_H_ */
