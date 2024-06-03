/*
 * TWI_Interface.h
 *
 *  Created on: 06-04-2024
 *   Author: Marwan Aboulfath
 *
 */
#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_


/*********************************************************************************/
/*							 TWI ERROR STATES	     							 */
/*********************************************************************************/
typedef enum
{
	NO_ERROR ,
	START_CONDITION_ERROR ,
	REPEATED_START_CONDITION_ERROR,
	ADDRESS_WITH_WRITE_ERROR,
	ADDRESS_WITH_READ_ERROR,
	MSTR_WRITE_DATA_ERROR,
	MSTR_READ_DATA_ERROR,
}TWI_ErrorState;


/*********************************************************************************/
/*							FUNCTIONS PROTOTYPES								 */
/*********************************************************************************/
void TWI_voidInit(void);
TWI_ErrorState TWI_enSendStartCondition(void);
TWI_ErrorState TWI_enSendRepeatedStart(void);
TWI_ErrorState TWI_enSendSlaveAddressWithWriteCmd(u8 Copy_u8SlaveAddress);
TWI_ErrorState TWI_enSendSlaveAddressWithReadCmd(u8 Copy_u8SlaveAddress);
TWI_ErrorState TWI_enSendByte(u8 Copy_u8DataByte);
TWI_ErrorState TWI_enReceiveByteAck(u8 * Copy_pu8ReceiveDataByte);
TWI_ErrorState TWI_enReceiveByteNoAck(u8 * Copy_pu8ReceiveDataByte);
void TWI_voidSendStopCondition(void);



#endif /* TWI_INTERFACE_H_ */
