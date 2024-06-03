/*
 * LED_Program.c
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
#include "../../LIB/STD_TYPES.h"


/*************************MCAL************************************/
#include "../../MCAL/DIO/DIO_Interface.h"

/************************LIB*************************************/
#include "LED_Config.h"
#include "LED_Interface.h"
#include "LED_Private.h"


/**************************************************************/
/*					FUNCTIONS DEFINITIONS					  */
/**************************************************************/
void LED_voidInit(LED_Type LED_Configuration)
{

	DIO_u8SetPinDirection( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_OUTPUT );

}


void LED_voidOn  (LED_Type LED_Configuration)
{

	if( LED_Configuration.Active_State == ACTIVE_HIGH ){

		DIO_u8SetPinValue( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_HIGH );

	}else if( LED_Configuration.Active_State == ACTIVE_LOW ){

		DIO_u8SetPinValue( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_LOW  );

	}

}


void LED_voidOff(LED_Type LED_Configuration)
{

	if( LED_Configuration.Active_State == ACTIVE_HIGH ){

		DIO_u8SetPinValue( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_LOW  );

	}else if( LED_Configuration.Active_State == ACTIVE_LOW ){

		DIO_u8SetPinValue( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_HIGH  );

	}

}


void LED_voidToggle( LED_Type LED_Configuration)
{
	DIO_u8TogglePinValue( LED_Configuration.Port , LED_Configuration.Pin );
}
