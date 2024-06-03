/*
 * LCD_Program.c
 *
 *  Created on: Mar 19, 2024
 *      Author: Marwan
 */

/***************************************************************/
/*                        FILE INCLUSIONS                      */
/***************************************************************/

/***************************LIBRARIES***************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

/******************************MCAL*****************************/
#include "../../MCAL/DIO/DIO_Interface.h"

/******************************HAL*****************************/
#include "LCD_Config.h"
#include "LCD_Interface.h"
#include "LCD_Private.h"

#include "util/delay.h"

/************************** FUNCTION DEFINITIONS ***************/

void LCD_voidInit(void)
{
	/************Set the control pins to be output**********/
	DIO_u8SetPinDirection(LCD_CTRL_PORT,LCD_EN_PIN,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(LCD_CTRL_PORT,LCD_RW_PIN,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(LCD_CTRL_PORT,LCD_RS_PIN,DIO_PIN_OUTPUT);

	/*Waiting for more than 30ms*/
	_delay_ms(40);

#if LCD_MODE == LCD_EIGHT_BIT
	DIO_u8SetPortDirection(LCD_DATA_PORT,DIO_PORT_OUTPUT);

	/*Send the function set command: N->1 (2 lines) ,F-> 0 (5*7 char font)*/
	LCD_voidSendCommand(0x38);

	/*delay 39 us*/
//	_delay_us(40);

	/*Display ON/OFF control*/
	LCD_voidSendCommand(0x0C);


	/*delay 39 us*/
	//_delay_us(40);

	/*Display clear control*/
	LCD_voidSendCommand(0x01);



#elif LCD_MODE == LCD_FOUR_BIT
	DIO_u8SetPortDirection(LCD_DATA_PORT,0b1111);

	LCD_voidSendCommand(0x28);

	/*delay 39 us*/
	_delay_us(40);

	/*Display ON/OFF control*/
	LCD_voidSendCommand(0x0C);

	/*delay 39 us*/
	_delay_us(40);

	/*Display clear control*/
	LCD_voidSendCommand(0x01);

#else
#error "Wrong LCD_MODE Configuration parameter"
#endif
}




void LCD_voidSendCommand(u8 copy_u8Command)
{
	/*Set the RS pin to be low*/
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,DIO_PIN_LOW);

	/*Set the RW pin to be low*/
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,DIO_PIN_LOW);

#if LCD_MODE == LCD_EIGHT_BIT
	DIO_u8SetPortValue(LCD_DATA_PORT,copy_u8Command);

	//DIO_u8SetPortValue(LCD_DATA_PORT,copy_u8Command );

#elif LCD_MODE == LCD_FOUR_BIT
	DIO_u8SetPortValue(LCD_DATA_PORT,(copy_u8Command &0xF0));

	/*set the EN pin to high: 1 to read, waiting 2 msec and then make it low again*/
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,DIO_PIN_HIGH);

	/*Wait 2 msec*/
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,DIO_PIN_LOW);

	DIO_u8SetPortValue(LCD_DATA_PORT,((copy_u8Command<<4)&0xF0));


#else
#error "Wrong LCD_MODE Configuration parameter"
#endif

	/*set the EN pin to high: 1 to read, waiting 2 msec and then make it low again*/
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,DIO_PIN_HIGH);

	/*Wait 2 msec*/
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,DIO_PIN_LOW);

}

void LCD_voidSendData(u8 copy_u8Data)
{
	/*Set the RS pin to be low*/
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,DIO_PIN_HIGH);

	/*Set the RW pin to be low*/
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,DIO_PIN_LOW);

#if LCD_MODE == LCD_EIGHT_BIT
	DIO_u8SetPortValue(LCD_DATA_PORT,copy_u8Data);


#elif LCD_MODE == LCD_FOUR_BIT
	DIO_u8SetPortValue(LCD_DATA_PORT,(copy_u8Data &0xF0));

	/*set the EN pin to high: 1 to read, waiting 2 msec and then make it low again*/
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,DIO_PIN_HIGH);

	/*Wait 2 msec*/
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,DIO_PIN_LOW);

	DIO_u8SetPortValue(LCD_DATA_PORT,((copy_u8Data<<4)&0xF0));


#else
#error "Wrong LCD_MODE Configuration parameter"
#endif

	/*set the EN pin to high: 1 to read, waiting 2 msec and then make it low again*/
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,DIO_PIN_HIGH);

	/*Wait 2 msec*/
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,DIO_PIN_LOW);

}

void LCD_voidSendString(const u8* copy_pu8String)
{
	for(u8 local_u8Iterator = 0; copy_pu8String[local_u8Iterator] != '\0';local_u8Iterator++)
	{
		LCD_voidSendData(copy_pu8String[local_u8Iterator]);
	}
}


void LCD_voidSetPosition(u8 copy_u8XPosition,u8 copy_u8YPosition)
{
	u8 Local_u8Address = 0;
	if(copy_u8XPosition == LCD_ROW0)
	{
		Local_u8Address = copy_u8YPosition;
	}
	else if(copy_u8XPosition == LCD_ROW1)
	{
		Local_u8Address = copy_u8YPosition + DDRAM_OFFSET;
	}
	else
	{

	}

	SET_BIT(Local_u8Address,7);
	LCD_voidSendCommand(Local_u8Address);
}

void LCD_voidSendNumber(s64 copy_s32Number)
{
	u64 reversed = 1;
	if (copy_s32Number == 0)
	{
		LCD_voidSendData('0');
	}
	else
	{
		if(copy_s32Number <0)
		{
			LCD_voidSendData('-');
			copy_s32Number *=-1;
		}
		else
		{
			while(copy_s32Number!= 0)
			{
				reversed = (reversed*10) + (copy_s32Number%10);
				copy_s32Number/=10;
			}
			while(reversed != 1)
			{
				LCD_voidSendData(reversed%10 +'0');
				reversed/=10;
			}
		}
	}
}

void LCD_voidSendCustomCharacter(u8* copy_pu8CharacterArray,u8 copy_u8PatternNumber,u8 copy_u8XPosition,u8 copy_u8YPosition)
{
	u8 Local_u8CGRAMAddress = 0 ,Local_u8LoopCounter;

	/*Calculating CGRAM Address*/
	Local_u8CGRAMAddress = copy_u8PatternNumber*8;

	/*Make the 6th bit from address to be high and sending cmd to LCD*/
	SET_BIT(Local_u8CGRAMAddress,6);

	LCD_voidSendCommand(Local_u8CGRAMAddress);

	for(Local_u8LoopCounter = 0; Local_u8LoopCounter<8 ; Local_u8LoopCounter++)
	{
		LCD_voidSendData(copy_pu8CharacterArray[Local_u8LoopCounter]);
	}
	LCD_voidSetPosition( copy_u8XPosition,copy_u8YPosition);

	/*Displaying the pattern from CGRAM*/
	LCD_voidSendData(copy_u8PatternNumber);
}

void LCD_voidClearScreen(void)
{
	LCD_voidSendCommand(0x01);
}































//
//void LCD_voidInit(void)
//{
//	/***************Set control pins as output**********/
//	DIO_u8SetPinDirection(LCD_CTRL_PORT, LCD_EN_PIN, DIO_PIN_OUTPUT);
//	DIO_u8SetPinDirection(LCD_CTRL_PORT, LCD_RW_PIN, DIO_PIN_OUTPUT);
//	DIO_u8SetPinDirection(LCD_CTRL_PORT, LCD_RS_PIN, DIO_PIN_OUTPUT);
//
//	/* Delay more than 30ms */
//	_delay_ms(40);
//
//#if LCD_MODE == LCD_EIGHT_BIT
//	DIO_u8SetPortDirection(LCD_DATA_PORT, DIO_PORT_OUTPUT);
//
//	/*Send function set command : N->1   & F->0*/
//	LCD_voidSendCommand(0x38);
//
//
//
//
//#elif LCD_MODE == LCD_FOUR_BIT
//
//
//#else
//#error "Wrong LCD Mode Configuration parameter"
//
//#endif
//}
//
//void LCD_voidSendCommand(u8 copy_u8Command)
//{
//	/* Set the RS pin to low */
//	DIO_u8SetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, DIO_PIN_LOW);
//
//	/* Set the RW pin to low */
//	DIO_u8SetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, DIO_PIN_LOW);
//
//#if LCD_MODE == LCD_EIGHT_BIT
//	DIO_u8SetPortValue (LCD_DATA_PORT, DIO_PORT_OUTPUT, copy_u8Command);
//
//#elif LCD_MODE == LCD_FOUR_BIT
//	DIO_u8SetPortValue(LCD_DATA_PORT, (copy_u8Command & 0xF0));
//
//	/* set EN pin to high to read , waiting 2ms and then make it low again */
//	DIO_u8SetPinValue(LCD_DATA_PORT, LCD_EN_PIN, DIO_PIN_HIGH);
//
//	/* wait for 2ms */
//	_delay_ms(2);
//
//	DIO_u8SetPinValue(LCD_DATA_PORT, LCD_EN_PIN, DIO_PIN_LOW);
//
//	DIO_u8SetPortValue (LCD_DATA_PORT, DIO_PORT_OUTPUT, ((copy_u8Command<<4)&0xF0));
//
//
//#else
//#error "Wrong LCD Mode Configuration parameter"
//
//#endif
//
//	/* set EN pin to high to read , waiting 2ms and then make it low again */
//		DIO_u8SetPinValue(LCD_DATA_PORT, LCD_EN_PIN, DIO_PIN_HIGH);
//
//		/* wait for 2ms */
//		_delay_ms(2);
//
//		DIO_u8SetPinValue(LCD_DATA_PORT, LCD_EN_PIN, DIO_PIN_LOW);
//}
//
//void LCD_voidSendData(u8 copy_u8Data)
//{
//
//}
//
//void LCD_voidSendString(const u8* copy_pu8String)
//{
//
//}
//
//void LCD_voidSetPosition(u8 copy_u8XPosition, u8 copy_u8XPosition)
//{
//
//}
//
//void LCD_voidSendNumber(s32 copy_s32Number)
//{
//
//}
