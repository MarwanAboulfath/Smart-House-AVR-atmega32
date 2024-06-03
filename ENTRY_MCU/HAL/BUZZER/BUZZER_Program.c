/*
 * BUZZER_Program.c
 *
 *  Created on: 10-04-2024
 *   Author: Marwan Aboulfath
 *
 */


/****************************************************************/
/*                    FILES INCLUSIONS							*/
/****************************************************************/
/************************LIB*************************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_Types.h"


/*************************MCAL************************************/
#include "../../MCAL/DIO/DIO_Interface.h"

/************************LIB*************************************/
#include "BUZZER_Config.h"
#include "BUZZER_Interface.h"
#include "BUZZER_Private.h"


/**************************************************************/
/*					FUNCTIONS DEFINITIONS					  */
/**************************************************************/
void BUZ_voidInit( BUZ_Type BUZ_Configuration)
{

	DIO_u8SetPinDirection( BUZ_Configuration.Port , BUZ_Configuration.Pin ,DIO_PIN_OUTPUT);

}


void BUZ_voidOn  ( BUZ_Type BUZ_Configuration )
{

	if( BUZ_Configuration.Active_State == ACTIVE_HIGH ){

		DIO_u8SetPinValue( BUZ_Configuration.Port , BUZ_Configuration.Pin , DIO_PIN_HIGH );

	}else if( BUZ_Configuration.Active_State == ACTIVE_LOW ){

		DIO_u8SetPinValue( BUZ_Configuration.Port , BUZ_Configuration.Pin , DIO_PIN_LOW  );

	}

}


void BUZ_voidOff ( BUZ_Type BUZ_Configuration )
{

	if( BUZ_Configuration.Active_State == ACTIVE_HIGH ){

		DIO_u8SetPinValue( BUZ_Configuration.Port , BUZ_Configuration.Pin , DIO_PIN_LOW  );

	}else if( BUZ_Configuration.Active_State == ACTIVE_LOW ){

		DIO_u8SetPinValue( BUZ_Configuration.Port , BUZ_Configuration.Pin , DIO_PIN_HIGH  );

	}

}


void BUZ_voidToggle( BUZ_Type BUZ_Configuration)
{
	DIO_u8TogglePinValue  ( BUZ_Configuration.Port , BUZ_Configuration.Pin);
}
