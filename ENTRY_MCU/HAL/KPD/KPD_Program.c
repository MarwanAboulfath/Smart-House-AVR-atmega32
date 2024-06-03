/*
 * KPD_Program.c
 *
 *  Created on: Mar 20, 2024
 *      Author: Marwan
 */



/*********************************************************/
/*			  	FILES INCLUSIONS						 */
/*********************************************************/

/**************************LIB****************************/

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include <util/delay.h>

/**************************MCAL***************************/
#include "../../MCAL/DIO/DIO_Interface.h"

/**************************HAL****************************/
#include "KPD_Config.h"
#include "KPD_Interface.h"
#include "KPD_Private.h"

/*******************Function Definitions*******************/


void KPD_Init(void)
{
	/*Connect pull up for rows pins*/
	DIO_u8ConnectPullUp(KPD_PORT,KPD_R0,DIO_PIN_HIGH);
	DIO_u8ConnectPullUp(KPD_PORT,KPD_R1,DIO_PIN_HIGH);
	DIO_u8ConnectPullUp(KPD_PORT,KPD_R2,DIO_PIN_HIGH);
	DIO_u8ConnectPullUp(KPD_PORT,KPD_R3,DIO_PIN_HIGH);

	/*Connect column pins as output high*/
	DIO_u8SetPinDirection(KPD_PORT,KPD_C0,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(KPD_PORT,KPD_C1,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(KPD_PORT,KPD_C2,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(KPD_PORT,KPD_C3,DIO_PIN_OUTPUT);

	DIO_u8SetPinValue(KPD_PORT,KPD_C0,DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT,KPD_C1,DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT,KPD_C2,DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT,KPD_C3,DIO_PIN_HIGH);
}

u8 KPD_u8GetPressed(void)
{
	u8 Local_u8Col;
	u8 Local_u8Row;
	u8 Local_u8ReturnData = NOTPRESSED;
	u8 Local_u8GetPressed;

	for(Local_u8Col = KPD_COL_INIT; Local_u8Col < KPD_COL_END + 1; Local_u8Col++)
	{
		DIO_u8SetPinValue(KPD_PORT, Local_u8Col, DIO_PIN_LOW);
		for(Local_u8Row = KPD_ROW_INIT; Local_u8Row < KPD_ROW_END + 1; Local_u8Row++)
		{
			DIO_u8GetPinValue(KPD_PORT, Local_u8Row, &Local_u8GetPressed);
			/*If Local_u8GetPressed , So this row is pressed*/
			if(Local_u8GetPressed == 0)
			{
				_delay_ms(50);
				DIO_u8GetPinValue(KPD_PORT, Local_u8Row, &Local_u8GetPressed);
				if(Local_u8GetPressed == 0)
				{
					Local_u8ReturnData = KPD_u8Buttons[Local_u8Row - KPD_ROW_INIT][Local_u8Col - KPD_COL_INIT];
				}

				while(DIO_PIN_LOW == Local_u8GetPressed)
				{
					DIO_u8GetPinValue(KPD_PORT, Local_u8Row, &Local_u8GetPressed);
				}
				break;
			}
		}
		DIO_u8SetPinValue(KPD_PORT, Local_u8Col, DIO_PIN_HIGH);
	}

	return Local_u8ReturnData;
}







