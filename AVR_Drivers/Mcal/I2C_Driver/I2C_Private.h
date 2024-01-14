/*
 * I2C_Private.h
 *
 *  Created on: Jun 23, 2023
 *      Author: karim
 */

#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

#define TWAR *((volatile u8*)0x22)
#define TWBR *((volatile u8*)0x20)
#define TWCR *((volatile u8*)0x56)
#define TWDR *((volatile u8*)0x23)
#define TWSR *((volatile u8*)0x21)

#endif /* I2C_PRIVATE_H_ */
