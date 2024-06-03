/*
 * main.c
 *
 *  Created on: Apr 11, 2024
 *      Author: Marwan
 */

/******************LIB*******************/
#include "LIB/STD_Types.h"
#include "LIB/BIT_MATH.h"

/*****************MCAL*******************/
#include "MCAL/PORT/PORT_Interface.h"
#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/SPI/SPI_Interface.h"
#include "MCAL/ADC/ADC_Interface.h"

/*****************HAL*******************/
#include "HAL/LM35/LM35_Interface.h"
#include "HAL/LCD/LCD_Interface.h"
/*****************Delay*****************/
#include "util/delay.h"

#include "MCAL/SPI/SPI_Private.h"

/* General Macros */
#define TEMP_1			CHANNEL0
#define TEMP_2			CHANNEL1

#define NO_DATA			0

#define GET_ROOM_1		1
#define GET_ROOM_2		2

/********************MAIN APP **************************/
int main(void)
{
	/* Local Variables */
	u8 Local_u8Temp1Value			= 0;
	u8 Local_u8Temp2Value			= 0;
	u8 Local_u8RecivedControlSignal = 0;
	/************* MODULES INITIALIZATIONS ****************/
	PORT_voidInit();
	LM35_voidInit();
	SPI_voidInit();
	LCD_voidInit();

	LCD_voidSendString((u8*)"TEST");
	_delay_ms(500);

	while(1)
	{
		//Local_u8Temp1Value = (u8)LM35_u16GetTempReading(TEMP_1);
		//Local_u8Temp2Value = (u8)LM35_u16GetTempReading(TEMP_2);

		SPI_u8Tranceive(NO_DATA, &Local_u8RecivedControlSignal);

		if(GET_ROOM_1 == Local_u8RecivedControlSignal)
		{
			Local_u8Temp1Value = (u8)LM35_u16GetTempReading(TEMP_1);
			SPI_voidSlaveSetData(Local_u8Temp1Value);
		}
		else if (GET_ROOM_2 == Local_u8RecivedControlSignal)
		{
			Local_u8Temp2Value = (u8)LM35_u16GetTempReading(TEMP_2);
			SPI_voidSlaveSetData(Local_u8Temp2Value);
		}
		else
		{
			/* Do nothing */
		}

		Local_u8RecivedControlSignal = 0;
	}


}
