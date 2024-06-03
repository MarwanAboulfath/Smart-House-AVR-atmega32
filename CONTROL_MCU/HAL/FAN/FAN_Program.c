/*
 * FAN_Program.c
 *
 *  Created on: 11-04-2024
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
#include "../../MCAL/TIMERS/TIMERS_Interface.h"

/************************LIB*************************************/
#include "FAN_Interface.h"
#include "FAN_Config.h"
#include "FAN_Private.h"


/**************************************************************/
/*					FUNCTIONS DEFINITIONS					  */
/**************************************************************/

// FAN_PIN_OC0
// FAN_PIN_OC2

void FAN_voidInit(u8 FAN_u8Pin)
{
	/* Check if FAN connected on OC0 */
	if(FAN_PIN_OC0 == FAN_u8Pin)
	{
		/* Initialize TIMER0 */
		TIMER0_voidInit();

	}
	/* Check if FAN connected on OC2 */
	else if(FAN_PIN_OC2 == FAN_u8Pin)
	{
		/* Initialize TIMER2 */
		TIMER2_voidInit();

	}
	else
	{

	}
	/* Turn Off Timer Prescaler To Turn Off FANS initially */
	TIMER0_voidSetPrescaler(TIMER0_NO_CLOCK_SOURCE);
	TIMER2_voidSetPrescaler(TIMER2_NO_CLOCK_SOURCE);
}




void FAN_ON_OFF(u8 FAN_u8Pin, u8 FAN_u8State)
{
	if(FAN_PIN_OC0 == FAN_u8Pin)
	{
		if(FAN_ON == FAN_u8State)
		{
			TIMER0_voidSetPrescaler(TIMER0_DIVISION_FACTOR_1024);
		}
		else
		{
			TIMER0_voidSetPrescaler(TIMER0_NO_CLOCK_SOURCE);
		}
	}
	else if (FAN_PIN_OC2 == FAN_u8Pin)
	{
		if(FAN_ON == FAN_u8State)
		{
			TIMER2_voidSetPrescaler(TIMER2_DIVISION_FACTOR_1024);
		}
		else
		{
			TIMER2_voidSetPrescaler(TIMER2_NO_CLOCK_SOURCE);
		}
	}
	else
	{

	}
}

void FAN_voidSetSpeed(u8 FAN_u8Pin, u8 FAN_u8Speed)
{
	if(FAN_PIN_OC0 == FAN_u8Pin)
	{
		switch(FAN_u8Speed)
		{

		case FAN_SPEED_OFF:
			TIMER0_voidSetFastPWM(FAN_PWM_SPEED_OFF);
			break;

		case FAN_SPEED_LOW:
			TIMER0_voidSetFastPWM(FAN_PWM_SPEED_LOW);
			break;

		case FAN_SPEED_MEDIUM:
			TIMER0_voidSetFastPWM(FAN_PWM_SPEED_MEDIUM);
			break;

		case FAN_SPEED_HIGH:
			TIMER0_voidSetFastPWM(FAN_PWM_SPEED_HIGH);
			break;

		default:
			break;

		}
	}
	else if(FAN_PIN_OC2 == FAN_u8Pin)
	{
		switch(FAN_u8Speed)
		{

		case FAN_SPEED_OFF:
			TIMER2_voidSetFastPWM(FAN_PWM_SPEED_OFF);
			break;

		case FAN_SPEED_LOW:
			TIMER2_voidSetFastPWM(FAN_PWM_SPEED_LOW);
			break;

		case FAN_SPEED_MEDIUM:
			TIMER2_voidSetFastPWM(FAN_PWM_SPEED_MEDIUM);
			break;

		case FAN_SPEED_HIGH:
			TIMER2_voidSetFastPWM(FAN_PWM_SPEED_HIGH);
			break;

		default:
			break;

		}
	}
	else
	{

	}
}
