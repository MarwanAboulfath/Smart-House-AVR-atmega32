/*
 * TWI_Program.c
 *
 *  Created on: 06-04-2024
 *   Author: Marwan Aboulfath
 *
 */

/*****************LIB************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

/*****************MCAL***********************/
//#include "../../HAL/LCD/LCD_Interface.h"
#include "TWI_Config.h"
#include "TWI_Private.h"
#include "TWI_Interface.h"


/*********************************************************************************/
/*							FUNCTIONS DEFINITIONS								 */
/*********************************************************************************/
void TWI_voidInit(void)
{
#if TWI_MASTER_SLAVE == MASTER
	#if TWI_SPEED == SPEED_100K
		#if TWI_PRESCALER == TWI_PRESCALER_1
			CLR_BIT(TWSR,TWSR_TWPS0);
			CLR_BIT(TWSR,TWSR_TWPS1);
			TWBR = (((FCPU_CLOCK/SPEED_100K)-16)/2);
		#elif TWI_PRESCALER == TWI_PRESCALER_4
				SET_BIT(TWSR,TWSR_TWPS0);
				CLR_BIT(TWSR,TWSR_TWPS1);
				TWBR = (((FCPU_CLOCK/SPEED_100K)-16)/8);
		#elif TWI_PRESCALER == TWI_PRESCALER_16
				CLR_BIT(TWSR,TWSR_TWPS0);
				SET_BIT(TWSR,TWSR_TWPS1);
				TWBR = (((FCPU_CLOCK/SPEED_100K)-16)/32);
		#elif TWI_PRESCALER == TWI_PRESCALER_64
				SET_BIT(TWSR,TWSR_TWPS0);
				SET_BIT(TWSR,TWSR_TWPS1);
				TWBR = (((FCPU_CLOCK/SPEED_100K)-16)/128);
		#else
			#error "wrong TWI_PRESCALER configuration parameter!"
		#endif

	#elif TWI_SPEED == SPEED_400K
			#if TWI_PRESCALER == TWI_PRESCALER_1
				CLR_BIT(TWSR,TWSR_TWPS0);
				CLR_BIT(TWSR,TWSR_TWPS1);
				TWBR = (((FCPU_CLOCK/SPEED_400K)-16)/2);
			#elif TWI_PRESCALER == TWI_PRESCALER_4
				SET_BIT(TWSR,TWSR_TWPS0);
				CLR_BIT(TWSR,TWSR_TWPS1);
				TWBR = (((FCPU_CLOCK/SPEED_400K)-16)/8);
			#elif TWI_PRESCALER == TWI_PRESCALER_16
				CLR_BIT(TWSR,TWSR_TWPS0);
				SET_BIT(TWSR,TWSR_TWPS1);
				TWBR = (((FCPU_CLOCK/SPEED_400K)-16)/32);
			#elif TWI_PRESCALER == TWI_PRESCALER_64
				SET_BIT(TWSR,TWSR_TWPS0);
				SET_BIT(TWSR,TWSR_TWPS1);
				TWBR = (((FCPU_CLOCK/SPEED_400K)-16)/128);
			#else
				#error "wrong TWI_PRESCALER configuration parameter!"
			#endif
	#else
	#error "wrong TWI_SPEED configuration parameter!"
	#endif

	/* Setting the target address*/
		TWAR = (TARGET_ADDRESS<<1);

	/*Enable Master*/
		TWCR = ((1<<TWCR_TWINT) | (1<<TWCR_TWEN) | (1<<TWCR_TWEA));


#elif TWI_MASTER_SLAVE == SLAVE
		/* Setting the target address*/
		TWAR = (TARGET_ADDRESS<<1);
		//Enable Ack
		SET_BIT(TWCR,TWCR_TWEA);
		/* Enable TWI peripheral */
		SET_BIT(TWCR,TWCR_TWEN);
#else
#error "wrong TWI_MASTER_SLAVE configuration parameter!"
#endif



}

TWI_ErrorState TWI_enSendStartCondition(void)
{
	/* Local enum object for error checking */
	TWI_ErrorState Local_enErrorState = NO_ERROR;

	/* Send Start Condition on the bus*/
	//SET_BIT(TWCR,TWCR_TWSTA);

	/* Clearing flag to perform the required action */
	//SET_BIT(TWCR,TWCR_TWINT);

	TWCR = (1<<TWCR_TWINT)|(1<<TWCR_TWSTA)|(1<<TWCR_TWEN);

	/* Polling till interrupt flag is raised again (end of action) */
	while((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/* Checking for action ID */
	if((TWSR & STATUS_MASK) != START_ACK)
	{
		Local_enErrorState = START_CONDITION_ERROR;
	}
	else
	{
		/* Do nothing */
	}

	return Local_enErrorState;
}

TWI_ErrorState TWI_enSendRepeatedStart(void)
{
	/* Local enum object for error checking */
	TWI_ErrorState Local_enErrorState = NO_ERROR;

	/* 1) Send Start Condition on the bus*/
	//SET_BIT(TWCR,TWCR_TWSTA);

	//SET_BIT(TWCR,TWCR_TWEN);

	/* 2) Clearing flag to perform the required action*/
	//SET_BIT(TWCR,TWCR_TWINT);

	TWCR = (1<<TWCR_TWINT)|(1<<TWCR_TWSTA)|(1<<TWCR_TWEN);

	/* 3) Polling till interrupt flag is raised again (end of action)*/
	while((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/* 4) Checking for action ID*/
	/*if((TWSR & STATUS_MASK) != REP_START_ACK)
	{
		Local_enErrorState = REPEATED_START_CONDITION_ERROR;
	}
	else
	{
		/Do nothing/
	}*/

	return Local_enErrorState;
}

TWI_ErrorState TWI_enSendSlaveAddressWithWriteCmd(u8 Copy_u8SlaveAddress)
{
	/* Local enum object for error checking */
	TWI_ErrorState Local_enErrorState = NO_ERROR;

	/* 1) Setting address packet to data register to be sent*/
	TWDR = (Copy_u8SlaveAddress<<1);

	//while(1);
	/* write Operation */
	//CLR_BIT(TWDR,0);

	/* 2) Clear start condition bit*/
	//CLR_BIT(TWCR,TWCR_TWSTA);

	//SET_BIT(TWCR,TWCR_TWEN);

	/* 3) Clearing flag to perform the required action*/
	//SET_BIT(TWCR,TWCR_TWINT);
	TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWEN);

	/* 4) Polling till interrupt flag is raised again (end of action)*/
	while((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/* 5) Checking for action ID*/
	if((TWSR & STATUS_MASK) != SLAVE_ADD_AND_WR_ACK)
	{
		Local_enErrorState = ADDRESS_WITH_WRITE_ERROR;
	}
	else
	{
		/*Do nothing*/
	}

	/*return from this function*/
	return Local_enErrorState ;

}

TWI_ErrorState TWI_enSendSlaveAddressWithReadCmd(u8 Copy_u8SlaveAddress)
{
	/* Local enum object for error checking */
	TWI_ErrorState Local_enErrorState = NO_ERROR;
	/* 1) Setting address packet to data register to be sent*/
	TWDR = ((Copy_u8SlaveAddress<< 1)|(0x01));

	/* Read Operation */
	//SET_BIT(TWDR,0);

	/* 2) Clear start condition bit*/
	//CLR_BIT(TWCR,TWCR_TWSTA);

	/* 3) Clearing flag to perform the required action*/
	//SET_BIT(TWCR,TWCR_TWINT);

	TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWEN);

	/* 4) Polling till interrupt flag is raised again (end of action)*/
	while((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/* 5) Checking for action ID*/
	if((TWSR & STATUS_MASK) != SLAVE_ADD_AND_WR_ACK)
	{
		Local_enErrorState = ADDRESS_WITH_READ_ERROR;
	}
	else
	{
		/*Do nothing*/
	}

	/*return from this function*/
	return Local_enErrorState ;
}

TWI_ErrorState TWI_enSendByte(u8 Copy_u8DataByte)
{
	/* Local enum object for error checking */
	TWI_ErrorState Local_enErrorState = NO_ERROR;

	/* 1) Setting data byte to get transmitter*/
	TWDR = Copy_u8DataByte;

	/* 2) Clearing flag to perform the required action*/
	//SET_BIT(TWCR,TWCR_TWINT);

	//SET_BIT(TWCR,TWCR_TWEN);

	TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWEN) ;

	/* 3) Polling till interrupt flag is raised again (end of action)*/
	while((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/* 4) Checking for action ID*/
	if((TWSR & STATUS_MASK) != MSTR_WR_BYTE_ACK)
	{
		Local_enErrorState = MSTR_WRITE_DATA_ERROR;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_enErrorState;
}

TWI_ErrorState TWI_enReceiveByteAck(u8 * Copy_pu8ReceivedDataByte)
{
	/* Local enum object for error checking */
	TWI_ErrorState Local_enErrorState = NO_ERROR;

	/* 1) Clearing flag to allow slave sending data*/
	//SET_BIT(TWCR,TWCR_TWINT);
	TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWEN) | (1<<TWCR_TWEA);
	/* 2) Polling till interrupt flag is raised again (end of action)*/
	while((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/* 3) Checking for action ID*/
	if((TWSR & STATUS_MASK) != MSTR_RD_BYTE_WITH_ACK)
	{
		Local_enErrorState = MSTR_READ_DATA_ERROR;
	}
	else
	{
		/* 4) Getting received data*/
		*Copy_pu8ReceivedDataByte = TWDR;
	}

	return Local_enErrorState;
}

TWI_ErrorState TWI_enReceiveByteNoAck(u8 * Copy_pu8ReceiveDataByte)
{
	/* Local enum object for error checking */
	TWI_ErrorState Local_enErrorState = NO_ERROR;

	/* 1) Setting the acknowledge bit */
	CLR_BIT(TWCR,TWCR_TWEA);

	/* 2) Clearing flag to allow slave sending data*/
	//SET_BIT(TWCR,TWCR_TWINT);

	TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWEN);

	/* 3) Polling till interrupt flag is raised again (end of action)*/
	while((GET_BIT(TWCR,TWCR_TWINT)) == 0);

	/* 4) Checking for action ID*/
	if((TWSR & STATUS_MASK) != MSTR_RD_BYTE_WITH_NACK)
	{
		Local_enErrorState = MSTR_READ_DATA_ERROR;
	}
	else
	{
		/* 4) Getting received data*/
		*Copy_pu8ReceiveDataByte = TWDR;
	}

	return Local_enErrorState;
}

void TWI_voidSendStopCondition(void)
{
	/* Generating stop condition on the bus */
	//SET_BIT(TWCR,TWCR_TWSTO);

	/* Clearing flag to perform the required action */
	//SET_BIT(TWCR,TWCR_TWINT) ;

	TWCR = (1<<TWCR_TWINT)|(1<<TWCR_TWEN)|(1<<TWCR_TWSTO);
}



