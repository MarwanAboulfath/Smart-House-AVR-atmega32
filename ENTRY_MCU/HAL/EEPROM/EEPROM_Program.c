/*
 * EEPROM_Program.c
 *
 *  Created on: 06-04-2024
 *   Author: Marwan Aboulfath
 *
 */


/*****************LIB************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_Types.h"

/*****************MCAL***********************/
#include "../../MCAL/TWI/TWI_Interface.h"

/*****************HAL************************/
//#include "../LCD/LCD_Interface.h"

#include "EEPROM_Config.h"
#include "EEPROM_Interface.h"
#include "EEPROM_Private.h"

/****************delay***********************/
#include "util/delay.h"



/*********************************************************************************/
/*							FUNCTIONS DEFINITIONS								 */
/*********************************************************************************/
void EEPROM_voidInit(void)
{
	TWI_voidInit();
}

void EEPROM_voidSendDataByte(u8 Copy_u8DataByte , u16 Copy_u16Address)
{
	/*local variable for EEPROM address*/
	u8 Local_u8Address;
	//1010 fixed
	//A2 pin configurable (either high or low)
	//last two bits is for page access
	Local_u8Address = (((EEPROM_FIXED_ADDRESS) |(A2_PIN_CONNECTION<<2) |((Copy_u16Address>> 8) & 3)));


	/* 1)Sending start condition on the bus*/
	TWI_enSendStartCondition();

	/* 2)Sending address of EEPROM with target page and write command*/
	TWI_enSendSlaveAddressWithWriteCmd(Local_u8Address);


	/* 3)Sending target location of the EEPROM*/
	TWI_enSendByte((u8)Copy_u16Address);

	/* 4)Sending target data to the specified location*/
	TWI_enSendByte(Copy_u8DataByte);

	/* 5)Sending stop condition*/
	TWI_voidSendStopCondition();
}

u8 EEPROM_u8ReadDataByte(u16 Copy_u16Adderss)
{
	/* Local variable to get read data */
	u8 Local_u8Data;
	/*local variable for EEPROM address*/
	u8 Local_u8Address;

	//1010 fixed
	//A2 pin configurable (either high or low)
	//last two bits is for page access
	Local_u8Address = (((EEPROM_FIXED_ADDRESS) |(A2_PIN_CONNECTION<<2) | ((Copy_u16Adderss >> 8) & 3)));

	/* 1)Sending start condition on the bus*/
	TWI_enSendStartCondition();

	/* 2)Sending address of EEPROM with target page and write command*/
	TWI_enSendSlaveAddressWithWriteCmd(Local_u8Address);

	/* 3)Sending target location of the EEPROM*/
	TWI_enSendByte((u8)Copy_u16Adderss);

	/* 4)Sending repeated start condition*/
	TWI_enSendStartCondition();

	/* 5)Sending address of EEPROM with target page and read command*/
	TWI_enSendSlaveAddressWithReadCmd(Local_u8Address);

	/* 6)Reading from target location*/
	TWI_enReceiveByteNoAck(&Local_u8Data);

	/* 5)Sending stop condition*/
	TWI_voidSendStopCondition();

	return Local_u8Data;
}


