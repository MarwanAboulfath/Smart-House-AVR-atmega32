/*
 * SWITCH_Program.c
 *
 *  Created on: 10-04-2024
 *   Author: Marwan Aboulfath
 *
 */

/******************************************************************/
/*						   FILES INCLUSIONS			    		  */
/******************************************************************/
/*******************************LIB********************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

/******************************MCAL********************************/
#include "../../MCAL/DIO/DIO_Interface.h"


/*******************************HAL********************************/
#include "SWITCH_Config.h"
#include "SWITCH_Interface.h"
#include "SWITCH_Private.h"


/******************************************************************/
/*						FUNCTIONS DEFINITIONS					  */
/******************************************************************/
void SW_voidInit(SW_Type SW_Config)
{
	DIO_u8SetPinDirection(SW_Config.Port,SW_Config.Pin,DIO_PIN_INPUT);

	/*Internal pullup*/
	if(SW_Config.Pull_State == SW_Int_PULL_UP)
	{
		DIO_u8SetPinValue(SW_Config.Port,SW_Config.Pin,DIO_PIN_HIGH);
	}
}

u8 SW_u8GetPressed(SW_Type SW_Config)
{
	u8 Local_u8Result = SW_NOT_PRESSED ;
	u8 Local_u8PinVal = SW_NOT_PRESSED ;

	if((SW_Config.Pull_State==SW_Int_PULL_UP)||(SW_Config.Pull_State==SW_EXT_PULL_UP))
	{
		DIO_u8GetPinValue(SW_Config.Port,SW_Config.Pin,&Local_u8PinVal);
		if(Local_u8PinVal == 0)
		{
			Local_u8Result = SW_PRESSED;
		}
		else if(Local_u8PinVal == 1)
		{
			Local_u8Result = SW_NOT_PRESSED;
		}
	}
	else if(SW_Config.Pull_State==SW_EXT_PULL_DOWN)
	{
		DIO_u8GetPinValue(SW_Config.Port,SW_Config.Pin,&Local_u8PinVal);
				if(Local_u8PinVal == 0)
				{
					Local_u8Result = SW_NOT_PRESSED;
				}
				else if(Local_u8PinVal == 1)
				{
					Local_u8Result = SW_PRESSED;
				}
	}
	else
	{
		/*Don Nothing*/
	}
	return Local_u8Result;
}
