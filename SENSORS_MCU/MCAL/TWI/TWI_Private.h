/*
 * TWI_Private.h
 *
 *  Created on: 06-04-2024
 *   Author: Marwan Aboulfath
 *
 */
#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_


/*********************************************************************************/
/*							REGISTERS AND BITS									 */
/*********************************************************************************/
/*TWCR Register*/
#define TWCR		*((volatile u8*) 0x56)
#define TWCR_TWINT               7
#define TWCR_TWEA                6
#define TWCR_TWSTA               5
#define TWCR_TWSTO               4
#define TWCR_TWWC                3
#define TWCR_TWEN                2
#define TWCR_TWIE                0


/*TWSR Register*/
#define TWSR		*((volatile u8*) 0x21)
#define TWSR_TWPS1               1
#define TWSR_TWPS0               0


/*TWAR Register*/
#define TWAR		*((volatile u8*) 0x22)
#define TWAR_TWGCE               0


/*TWDR Register*/
#define TWDR        *((volatile u8*) 0x23)

/*TWBR Register*/
#define TWBR        *((volatile u8*) 0x20)



/*********************************************************************************/
/*								PRIVATE MACROS									 */
/*********************************************************************************/
#define STATUS_MASK              0xF8
#define FCPU_CLOCK               8000000



#define START_ACK                0x08
#define REP_START_ACK            0x10
#define SLAVE_ADD_AND_WR_ACK     0x18
#define SLAVE_ADD_AND_RD_ACK     0x40
#define MSTR_WR_BYTE_ACK         0x28
#define MSTR_RD_BYTE_WITH_ACK    0x50
#define MSTR_RD_BYTE_WITH_NACK   0x58
#define SLAVE_ADD_RCVD_RD_REQ    0xA8
#define SLAVE_ADD_RCVD_WR_REQ    0x60
#define SLAVE_DATA_RECEIVED      0x80
#define SLAVE_BYTE_TRANSMITTED   0xB8


#define MASTER					1
#define SLAVE					2

#define SPEED_100K				1000000
#define SPEED_400K				4000000

#define TWI_PRESCALER_1			1
#define TWI_PRESCALER_4			2
#define TWI_PRESCALER_16		3
#define TWI_PRESCALER_64		4





#endif /* TWI_PRIVATE_H_ */
