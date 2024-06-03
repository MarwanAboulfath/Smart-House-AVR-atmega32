/*
 * main.c
 *
 *  Created on: Apr 8, 2024
 *      Author: Marwan
 */

/******************LIB*******************/
#include "LIB/STD_Types.h"
#include "LIB/BIT_MATH.h"

/*****************MCAL*******************/
#include "MCAL/PORT/PORT_Interface.h"
#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/TIMERS/TIMERS_Interface.h"
#include "MCAL/GIE/GIE_Interface.h"
#include "MCAL/EXTI/EXTI_Interface.h"
#include "MCAL/SPI/SPI_Interface.h"
#include "MCAL/USART/USART_Interface.h"

/*****************HAL*******************/
#include "HAL/BUZZER/BUZZER_Interface.h"
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/LED/LED_Interface.h"
#include "HAL/FAN/FAN_Interface.h"
#include "HAL/SWITCH/SWITCH_Interface.h"
/*****************Delay*****************/
#include "util/delay.h"

/* General Macros */
#define NUM_OF_LEDS			8
#define LEDS_PORT			LED_PORTA

#define ROOM_1_FAN			FAN_PIN_OC0
#define ROOM_2_FAN			FAN_PIN_OC2

#define CLOSED				FALSE
#define OPENED				TRUE

#define WRONG_PASSWORD		1
#define CORRECT_PASSWORD	2
#define HOUSE_CLOSED		3
#define STOP_ALARM			4

#define MAX_TRIALS			3

#define NO_DATA				0

#define GET_ROOM_1			1
#define GET_ROOM_2			2

/* Global variables */
u8 Global_u8CheckRoom1 			= FALSE;
u8 Global_u8CheckRoom2 			= FALSE;
u8 Global_u8HouseOpenFlag		= CLOSED;


/******************INTERRUPT HANDLERS********************/
void EXTI0_ROOM1Handler(void)
{
	Global_u8CheckRoom1 = TRUE;
}

void EXTI1_ROOM2Handler(void)
{
	Global_u8CheckRoom2 = TRUE;
}

void EXTI2_ExitHouseHandler(void)
{
	Global_u8HouseOpenFlag = CLOSED;
	/* Turn Off Fan 1&2 */
	FAN_voidSetSpeed(ROOM_1_FAN, FAN_SPEED_OFF);
	FAN_voidSetSpeed(ROOM_2_FAN, FAN_SPEED_OFF);
	_delay_ms(50);
	FAN_ON_OFF(ROOM_1_FAN, FAN_OFF);
	FAN_ON_OFF(ROOM_2_FAN, FAN_OFF);

	/*Send House closed house signal to Entry MCU */
	USART_u8SendData(HOUSE_CLOSED);
	/* Display goodbye Message to user */
	LCD_voidClearScreen();
	LCD_voidSendString((u8*)"Have a nice day!");
	_delay_ms(200);
	LCD_voidClearScreen();
}


/********************MAIN APP **************************/

int main(void)
{
	/* Switch configuration parameters */
	SW_Type	Alarm_StopButton = {
			DIO_PORTB,
			DIO_PIN1,
			SW_EXT_PULL_DOWN
	};

	/* LEDs configuration parameters */
	LED_Type	Local_LEDsConfig[NUM_OF_LEDS] =
	{
			{ LEDS_PORT, LED_PIN0, ACTIVE_HIGH },
			{ LEDS_PORT, LED_PIN1, ACTIVE_HIGH },
			{ LEDS_PORT, LED_PIN2, ACTIVE_HIGH },
			{ LEDS_PORT, LED_PIN3, ACTIVE_HIGH },
			{ LEDS_PORT, LED_PIN4, ACTIVE_HIGH },
			{ LEDS_PORT, LED_PIN5, ACTIVE_HIGH },
			{ LEDS_PORT, LED_PIN6, ACTIVE_HIGH },
			{ LEDS_PORT, LED_PIN7, ACTIVE_HIGH }
	};

	u8 Local_u8LedsIterator = 0;
	/* Buzzer configuration parameters */
	BUZ_Type	Local_BUZZERConfig = {BUZ_PORTB, BUZ_PIN0, ACTIVE_HIGH};

	/* Local Variables */
	u8 Local_u8DoorLockRecivedData 	= 0;
	u8 Local_u8WrongPasswordEntries = 0;
	u8 Local_u8Room1Temp   			= 0;
	u8 Local_u8Room2Temp   			= 0;
	u8 Local_u8IgnoredData 			= 0;

	/************* MODULES INITIALIZATIONS ****************/
	PORT_voidInit();
	GIE_voidEnable();
	EXTI_voidInit();
	SPI_voidInit();
	USART_voidInit();

	BUZ_voidInit(Local_BUZZERConfig);
	LCD_voidInit();
	FAN_voidInit(ROOM_1_FAN);
	FAN_voidInit(ROOM_2_FAN);

	SW_voidInit(Alarm_StopButton);
	while(NUM_OF_LEDS > Local_u8LedsIterator)
	{
		LED_voidInit(Local_LEDsConfig[Local_u8LedsIterator]);
		Local_u8LedsIterator++;
	}

	/* Set call back functions */
	EXTI_u8Int0SetCallBack(EXTI0_ROOM1Handler);
	EXTI_u8Int1SetCallBack(EXTI1_ROOM2Handler);
	EXTI_u8Int2SetCallBack(EXTI2_ExitHouseHandler);


	while(1)
	{

		while(CLOSED == Global_u8HouseOpenFlag)
		{
			/* House is closed and all functionalities are unavailable */
			LCD_voidSetPosition(LCD_ROW0,LCD_COLUMN0);
			/* Display house closed message */
			LCD_voidSendString((u8*)"House Closed");

			/* Receive door lock status from ENTRY MCU */
			USART_u8RecevieData(&Local_u8DoorLockRecivedData);

			/* If status is WRONG_PASSWORD increment Wrong password entries counter */
			if (WRONG_PASSWORD == Local_u8DoorLockRecivedData)
			{
				Local_u8WrongPasswordEntries++;
			}
			/* If status is CORRECT_PASSWORD execute unlock routine */
			else if(CORRECT_PASSWORD == Local_u8DoorLockRecivedData)
			{
				/* Reset Wrong password entries counter */
				Local_u8WrongPasswordEntries = 0;
				/* Set House open flag to OPENED */
				Global_u8HouseOpenFlag = OPENED;
				/* Clear LCD display */
				LCD_voidClearScreen();
			}
			else
			{
				/* Do nothing */
			}
			/* Reset Received status from ENTRY MCU */
			Local_u8DoorLockRecivedData = 0;

			/* Check if user entered wrong password 3 times */
			if(MAX_TRIALS <= Local_u8WrongPasswordEntries)
			{
				/* Set Alarm and Leds on until Alarm stop button is pressed and wait for STOP ALARM button */
				/* Display "Alarm ON" message on LCD */
				LCD_voidSetPosition(LCD_ROW1, LCD_COLUMN0);
				LCD_voidSendString((u8*)"ALARM ON!");
				while(SW_u8GetPressed(Alarm_StopButton) != SW_PRESSED)
				{
					DIO_u8SetPortValue(LEDS_PORT, DIO_PORT_HIGH);
					BUZ_voidOn(Local_BUZZERConfig);
					_delay_ms(200);
					DIO_u8SetPortValue(LEDS_PORT, DIO_PORT_LOW);
					BUZ_voidOff(Local_BUZZERConfig);
					_delay_ms(200);
				}
				/* Delete "Alarm ON" message from LCD */
				LCD_voidSetPosition(LCD_ROW1, LCD_COLUMN0);
				LCD_voidSendString((u8*)"                ");
				/* Reset Wrong password entries counter */
				Local_u8WrongPasswordEntries = 0;
				/* Send stop alarm status to ENTRY MCU */
				USART_u8SendData(STOP_ALARM);
			}
			else
			{
				/* Do nothing */
			}

		}

		while(OPENED == Global_u8HouseOpenFlag)
		{
			/* House is open and all functionalities are available */
			LCD_voidSetPosition(LCD_ROW0,LCD_COLUMN0);
			LCD_voidSendString((u8*)"Select Room");

			if(TRUE == Global_u8CheckRoom1)
			{
				/* Send Get Room 1 message to Sensors MCU */
				SPI_u8Tranceive(GET_ROOM_1, &Local_u8IgnoredData);

				/* Delay until Slave sets Temp value in buffer */
				_delay_ms(50);

				/* Receive Room 1 temperature from Sensors MCU */
				SPI_u8Tranceive(NO_DATA, &Local_u8Room1Temp);

				/* Display Room 1 temperature value on LCD */
				LCD_voidClearScreen();
				LCD_voidSendString((u8*)"Room 1 Temp: ");
				LCD_voidSendNumber(Local_u8Room1Temp);

				/* Set cursor to second line */
				LCD_voidSetPosition(LCD_ROW1,LCD_COLUMN0);
				/* Set fan speed according to temperature of room 1 */
				if((14 <= Local_u8Room1Temp) && (20 > Local_u8Room1Temp))
				{
					/* Turn Fan 1 on */
					FAN_ON_OFF(ROOM_1_FAN, FAN_ON);
					/* Set Fan on Low Speed */
					FAN_voidSetSpeed(ROOM_1_FAN, FAN_SPEED_LOW);
					/* Display Fan speed on LCD */
					LCD_voidSendString((u8*)"Fan Speed LOW");
				}
				else if ((20 <= Local_u8Room1Temp) && (30 > Local_u8Room1Temp))
				{
					/* Turn Fan 1 on */
					FAN_ON_OFF(ROOM_1_FAN, FAN_ON);
					/* Set Fan on Medium Speed */
					FAN_voidSetSpeed(ROOM_1_FAN, FAN_SPEED_MEDIUM);
					/* Display Fan speed on LCD */
					LCD_voidSendString((u8*)"Fan Speed MEDIUM");
				}
				else if (30 <= Local_u8Room1Temp)
				{
					/* Turn Fan 1 on */
					FAN_ON_OFF(ROOM_1_FAN, FAN_ON);
					/* Set Fan on High Speed */
					FAN_voidSetSpeed(ROOM_1_FAN, FAN_SPEED_HIGH);
					/* Display Fan speed on LCD */
					LCD_voidSendString((u8*)"Fan Speed HIGH");
				}
				else
				{
					/* Turn Off Fan 1 */
					FAN_voidSetSpeed(ROOM_1_FAN, FAN_SPEED_OFF);
					_delay_ms(50);
					FAN_ON_OFF(ROOM_1_FAN, FAN_OFF);
					/* Display Fan speed on LCD */
					LCD_voidSendString((u8*)"Fan STOPPED");
				}
				/* Keep display ON for 2s */
				_delay_ms(1000);
				/* Clear screen */
				LCD_voidClearScreen();
				/* Reset Check room flag */
				Global_u8CheckRoom1 = FALSE;
			}
			else if (TRUE == Global_u8CheckRoom2)
			{
				/* Send Get Room 2 message to Sensors MCU */
				SPI_u8Tranceive(GET_ROOM_2, &Local_u8IgnoredData);

				/* Delay until Slave sets Temp value in buffer */
				_delay_ms(50);

				/* Receive Room 2 temperature from Sensors MCU */
				SPI_u8Tranceive(NO_DATA, &Local_u8Room2Temp);

				/* Display Room 2 temperature value on LCD */
				LCD_voidClearScreen();
				LCD_voidSendString((u8*)"Room 2 Temp: ");
				LCD_voidSendNumber(Local_u8Room2Temp);

				/* Set cursor to second line */
				LCD_voidSetPosition(LCD_ROW1,LCD_COLUMN0);
				/* Set fan speed according to temperature of room 2 */
				if((14 <= Local_u8Room2Temp) && (20 > Local_u8Room2Temp))
				{
					/* Turn Fan 2 on */
					FAN_ON_OFF(ROOM_2_FAN, FAN_ON);
					/* Set Fan on Low Speed */
					FAN_voidSetSpeed(ROOM_2_FAN, FAN_SPEED_LOW);
					/* Display Fan speed on LCD */
					LCD_voidSendString((u8*)"Fan Speed LOW");
				}
				else if ((20 <= Local_u8Room2Temp) && (30 > Local_u8Room2Temp))
				{
					/* Turn Fan 2 on */
					FAN_ON_OFF(ROOM_2_FAN, FAN_ON);
					/* Set Fan on Medium Speed */
					FAN_voidSetSpeed(ROOM_2_FAN, FAN_SPEED_MEDIUM);
					/* Display Fan speed on LCD */
					LCD_voidSendString((u8*)"Fan Speed MEDIUM");
				}
				else if (30 <= Local_u8Room2Temp)
				{
					/* Turn Fan 2 on */
					FAN_ON_OFF(ROOM_2_FAN, FAN_ON);
					/* Set Fan on High Speed */
					FAN_voidSetSpeed(ROOM_2_FAN, FAN_SPEED_HIGH);
					/* Display Fan speed on LCD */
					LCD_voidSendString((u8*)"Fan Speed HIGH");
				}
				else
				{
					/* Turn Off Fan 2 */
					FAN_voidSetSpeed(ROOM_2_FAN, FAN_SPEED_OFF);
					_delay_ms(50);
					FAN_ON_OFF(ROOM_2_FAN, FAN_OFF);
					/* Display Fan speed on LCD */
					LCD_voidSendString((u8*)"Fan STOPPED");
				}
				/* Keep display ON for 2s */
				_delay_ms(1000);
				/* Clear screen */
				LCD_voidClearScreen();
				/* Reset Check room flag */
				Global_u8CheckRoom2 = FALSE;
			}

		}

	}

	return 0;
}
