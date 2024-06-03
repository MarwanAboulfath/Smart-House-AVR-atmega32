/*
 * DIO_Program.c
 *
 *  Created on: Mar 18, 2024
 *      Author: Marwan
 */


/***************************************************************/
/*                        FILE INCLUSIONS                      */
/***************************************************************/

/***************************LIBRARIES***************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/******************************MCAL*****************************/
#include "DIO_Private.h"
#include "DIO_Interface.h"
#include "DIO_Config.h"


/***************************************************************/
/*                   FUNCTION IMPLEMENTATIONS                  */
/***************************************************************/

/* Set the value HIGH/LOW of a whole specified port */
ReturnType_State_t DIO_u8SetPortValue(u8 copy_u8Port, u8 copy_u8Value)
{
	/* Variable to store return status Ok / Not Ok */
	u8	Local_u8State = E_OK;
	/* Switch case to access specified port number */
	switch(copy_u8Port)
	{
	case DIO_PORTA:
		/* Store value of  Output to PORTA register*/
		PORTA = copy_u8Value;
		break;
		/* Store value of  Output to PORTB register*/
	case DIO_PORTB:
		PORTB = copy_u8Value;
		break;
	case DIO_PORTC:
		/* Store value of  Output to PORTC register*/
		PORTC = copy_u8Value;
		break;
	case DIO_PORTD:
		/* Store value of  Output to PORTD register*/
		PORTD = copy_u8Value;
		break;
	default:
		/* Wrong port entered set return variable to NOT OK*/
		Local_u8State = E_NOK;
		break;
	}
	/* return function status */
	return Local_u8State;
}

/* Set the direction INPUT/OUTPUT of a whole Port */
ReturnType_State_t DIO_u8SetPortDirection(u8 copy_u8Port, u8 copy_u8Direction)
{
	/* Variable to store return status Ok / Not Ok */
	u8	Local_u8State = E_OK;
	/* Switch case to access specified port number */
	switch(copy_u8Port)
	{
	case DIO_PORTA:
		/* Set the port direction to DDRA register*/
		DDRA = copy_u8Direction;
		break;
	case DIO_PORTB:
		/* Set the port direction to DDRB register*/
		DDRB = copy_u8Direction;
		break;
	case DIO_PORTC:
		/* Set the port direction to DDRC register*/
		DDRC = copy_u8Direction;
		break;
	case DIO_PORTD:
		/* Set the port direction to DDRD register*/
		DDRD = copy_u8Direction;
		break;
	default:
		/* Wrong port entered set return variable to NOT OK*/
		Local_u8State = E_NOK;
		break;
	}
	/* return function status */
	return Local_u8State;
}

/* Read the value  of a whole port*/
ReturnType_State_t DIO_u8GetPortValue(u8 copy_u8Port, u8 *copy_u8Variable)
{
	/* Variable to store return status Ok / Not Ok */
	u8 Local_u8Status = E_OK;
	/* Check if copy_u8Variable pointer is not NULL pointer */
	if(NULL_ptr != copy_u8Variable)
	{
		/* Switch case to access specified port number */
		switch(copy_u8Port)
		{
		case DIO_PORTA:
			/* Read Port value from PINA register and store it in location of the passed address */
			*copy_u8Variable = PINA;
			break;
		case DIO_PORTB:
			/* Read Port value from PINB register and store it in location of the passed address */
			*copy_u8Variable = PINB;
			break;
		case DIO_PORTC:
			/* Read Port value from PINC register and store it in location of the passed address */
			*copy_u8Variable = PINC;
			break;
		case DIO_PORTD:
			/* Read Port value from PIND register and store it in location of the passed address */
			*copy_u8Variable = PIND;
			break;
		default:
			/* Wrong port entered set return variable to NOT OK*/
			Local_u8Status = E_NOK;
			break;
		}
	}
	/* copy_u8Variable pointer is NULL pointer */
	else
	{
		/* set return variable to NOT OK NULL PTR */
		Local_u8Status = E_NOK_NULL_PTR;
	}
	/* return function status */
	return Local_u8Status;
}

/* Set the value HIGH/LOW of a pin */
ReturnType_State_t DIO_u8SetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Value)
{
	/* Variable to store return status Ok / Not Ok */
	u8 Local_u8Status = E_OK;
	/* Check if pin number is valid between pin 0 and pin 7 */
	if((DIO_PIN0 <= copy_u8Pin) && (DIO_PIN7 >= copy_u8Pin))
	{
		/* Check if selected output level is LOW */
		if(DIO_PIN_LOW == copy_u8Value)
		{
			/* Switch case to access specified port number */
			switch(copy_u8Port)
			{
			case DIO_PORTA:
				/* Clear specified Pin on PORTA register to set value of pin to low */
				CLR_BIT(PORTA,copy_u8Pin);
				break;
			case DIO_PORTB:
				/* Clear specified Pin on PORTB register to set value of pin to low */
				CLR_BIT(PORTB,copy_u8Pin);
				break;
			case DIO_PORTC:
				/* Clear specified Pin on PORTC register to set value of pin to low */
				CLR_BIT(PORTC,copy_u8Pin);
				break;
			case DIO_PORTD:
				/* Clear specified Pin on PORTD register to set value of pin to low */
				CLR_BIT(PORTD,copy_u8Pin);
				break;
			default:
				/* Wrong port entered set return variable to NOT OK*/
				Local_u8Status = E_NOK;
				break;
			}
		}
		/* Check if selected output level is HIGH */
		else if (DIO_PIN_HIGH == copy_u8Value)
		{
			/* Switch case to access specified port number */
			switch(copy_u8Port)
			{
			case DIO_PORTA:
				/* Set specified Pin on PORTA register to set value of pin to low */
				SET_BIT(PORTA,copy_u8Pin);
				break;
			case DIO_PORTB:
				/* Set specified Pin on PORTB register to set value of pin to low */
				SET_BIT(PORTB,copy_u8Pin);
				break;
			case DIO_PORTC:
				/* Set specified Pin on PORTC register to set value of pin to low */
				SET_BIT(PORTC,copy_u8Pin);
				break;
			case DIO_PORTD:
				/* Set specified Pin on PORTD register to set value of pin to low */
				SET_BIT(PORTD,copy_u8Pin);
				break;
			default:
				/* Wrong port entered set return variable to NOT OK*/
				Local_u8Status = E_NOK;
				break;
			}
		}
		else
		{
			/* Wrong pin value entered set return variable to NOT OK*/
			Local_u8Status = E_NOK;
		}
	}
	else
	{
		/* Wrong pin number entered set return variable to NOT OK*/
		Local_u8Status = E_NOK;
	}
	/* return function status */
	return Local_u8Status;
}

/* Toggle Pin Value */
ReturnType_State_t	DIO_u8TogglePinValue(u8 copy_u8Port, u8 copy_u8Pin)
{
	/* Variable to store return status Ok / Not Ok */
		u8 Local_u8Status = E_OK;
		/* Check if pin number is valid between pin 0 and pin 7 */
		if((DIO_PIN0 <= copy_u8Pin) && (DIO_PIN7 >= copy_u8Pin))
		{
				/* Switch case to access specified port number */
				switch(copy_u8Port)
				{
				case DIO_PORTA:
					/* Toggle specified Pin on PORTA register */
					TOGGLE_BIT(PORTA,copy_u8Pin);
					break;
				case DIO_PORTB:
					/* Toggle specified Pin on PORTB register */
					TOGGLE_BIT(PORTB,copy_u8Pin);
					break;
				case DIO_PORTC:
					/* Toggle specified Pin on PORTC register */
					TOGGLE_BIT(PORTC,copy_u8Pin);
					break;
				case DIO_PORTD:
					/* Toggle specified Pin on PORTD register */
					TOGGLE_BIT(PORTD,copy_u8Pin);
					break;
				default:
					/* Wrong port entered set return variable to NOT OK*/
					Local_u8Status = E_NOK;
					break;
				}

		}
		else
		{
			/* Wrong pin number entered set return variable to NOT OK*/
			Local_u8Status = E_NOK;
		}
		/* return function status */
		return Local_u8Status;
}

/* Set the direction INPUT/OUTPUT of a pin */
ReturnType_State_t DIO_u8SetPinDirection(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Direction)
{
	/* Variable to store return status Ok / Not Ok */
	u8 Local_u8Status = E_OK;
	/* Check if pin number is valid between pin 0 and pin 7 */
	if((DIO_PIN0 <= copy_u8Pin) && (DIO_PIN7 >= copy_u8Pin))
	{
		/* Check if selected direction level is INPUT */
		if(DIO_PIN_INPUT == copy_u8Direction)
		{
			/* Switch case to access specified port number */
			switch(copy_u8Port)
			{
			case DIO_PORTA:
				/* Clear specified Pin on DDRA register to set direction of pin to input */
				CLR_BIT(DDRA,copy_u8Pin);
				break;
			case DIO_PORTB:
				/* Clear specified Pin on DDRB register to set direction of pin to input */
				CLR_BIT(DDRB,copy_u8Pin);
				break;
			case DIO_PORTC:
				/* Clear specified Pin on DDRC register to set direction of pin to input */
				CLR_BIT(DDRC,copy_u8Pin);
				break;
			case DIO_PORTD:
				/* Clear specified Pin on DDRD register to set direction of pin to input */
				CLR_BIT(DDRD,copy_u8Pin);
				break;
			default:
				/* Wrong port entered set return variable to NOT OK*/
				Local_u8Status = E_NOK;
				break;
			}
		}
		/* Check if selected direction level is OUTPUT */
		else if (DIO_PIN_OUTPUT == copy_u8Direction)
		{
			/* Switch case to access specified port number */
			switch(copy_u8Port)
			{
			case DIO_PORTA:
				/* Set specified Pin on DDRA register to set direction of pin to output */
				SET_BIT(DDRA,copy_u8Pin);
				break;
			case DIO_PORTB:
				/* Set specified Pin on DDRB register to set direction of pin to output */
				SET_BIT(DDRB,copy_u8Pin);
				break;
			case DIO_PORTC:
				/* Set specified Pin on DDRC register to set direction of pin to output */
				SET_BIT(DDRC,copy_u8Pin);
				break;
			case DIO_PORTD:
				/* Set specified Pin on DDRD register to set direction of pin to output */
				SET_BIT(DDRD,copy_u8Pin);
				break;
			default:
				/* Wrong port entered set return variable to NOT OK*/
				Local_u8Status = E_NOK;
				break;
			}
		}
		else
		{
			/* Wrong pin direction entered set return variable to NOT OK*/
			Local_u8Status = E_NOK;
		}
	}
	else
	{
		/* Wrong pin number entered set return variable to NOT OK*/
		Local_u8Status = E_NOK;
	}
	/* return function status */
	return Local_u8Status;
}

/* Read the value  of a specified pin*/
ReturnType_State_t DIO_u8GetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8 *copy_u8Variable)
{
	/* Variable to store return status Ok / Not Ok */
	u8 Local_u8Status = E_OK;
	/* Check if copy_u8Variable pointer is not NULL pointer */
	if(NULL_ptr != copy_u8Variable)
	{
		/* Check if pin number is valid between pin 0 and pin 7 */
		if((DIO_PIN0 <= copy_u8Pin) && (DIO_PIN7 >= copy_u8Pin))
		{
			/* Switch case to access specified port number */
			switch(copy_u8Port)
			{
			case DIO_PORTA:
				/* Get bit value for specified pin from PINA register and store it in location of the passed address */
				*copy_u8Variable = GET_BIT(PINA,copy_u8Pin);
				break;
			case DIO_PORTB:
				/* Get bit value for specified pin from PINB register and store it in location of the passed address */
				*copy_u8Variable = GET_BIT(PINB,copy_u8Pin);
				break;
			case DIO_PORTC:
				/* Get bit value for specified pin from PINC register and store it in location of the passed address */
				*copy_u8Variable = GET_BIT(PINC,copy_u8Pin);
				break;
			case DIO_PORTD:
				/* Get bit value for specified pin from PIND register and store it in location of the passed address */
				*copy_u8Variable = GET_BIT(PIND,copy_u8Pin);
				break;
			default:
				/* Wrong port entered set return variable to NOT OK*/
				Local_u8Status = E_NOK;
				break;
			}
		}
		else
		{
			/* Wrong pin number entered set return variable to NOT OK*/
			Local_u8Status = E_NOK;
		}
	}
	/* copy_u8Variable pointer is NULL pointer */
	else
	{
		/* set return variable to NOT OK NULL PTR */
		Local_u8Status = E_NOK_NULL_PTR;
	}
	/* return function status */
	return Local_u8Status;

}

/* Activate or deactivate the pull up resistor of a pin */
ReturnType_State_t	DIO_u8ConnectPullUp(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8ConnectPullUp)
{
	/* Variable to store return status Ok / Not Ok */
	ReturnType_State_t Local_u8Status = E_OK;

	/* Check if pin number is valid between pin 0 and pin 7 */
	if((copy_u8Port <= DIO_PORTD) && (copy_u8Pin <= DIO_PIN7))
	{
		/* clear PUD pin in SFIOR register to activate the pull up resistor feature */
		CLR_BIT(SFIOR, PUD);

		/* Switch case to access specified port number */
		switch(copy_u8Port)
		{
		case DIO_PORTA:
			/* Check if copy_u8ConnectPullUp value is HIGH to activate pull up resistor */
			if(DIO_PIN_HIGH==copy_u8ConnectPullUp)
			{
				/* set pin direction as input */
				CLR_BIT(DDRA, copy_u8Pin);
				/* set pin value in PORTA to activate Pull up resistor */
				SET_BIT(PORTA, copy_u8Pin);
			}
			/* Check if copy_u8ConnectPullUp value is LOW to deactivate pull up resistor */
			else
			{
				/* clear pin value in PORTA to de-activate Pull up resistor */
				CLR_BIT(PORTA, copy_u8Pin);
			}
			break;
		case DIO_PORTB:
			/* Check if copy_u8ConnectPullUp value is HIGH to activate pull up resistor */
			if(DIO_PIN_HIGH==copy_u8ConnectPullUp)
			{
				/* set pin direction as input */
				CLR_BIT(DDRB, copy_u8Pin);
				/* set pin value in PORTB to activate Pull up resistor */
				SET_BIT(PORTB, copy_u8Pin);
			}
			/* Check if copy_u8ConnectPullUp value is LOW to deactivate pull up resistor */
			else
			{
				/* clear pin value in PORTB to de-activate Pull up resistor */
				CLR_BIT(PORTB, copy_u8Pin);
			}
			break;
		case DIO_PORTC:
			/* Check if copy_u8ConnectPullUp value is HIGH to activate pull up resistor */
			if(DIO_PIN_HIGH==copy_u8ConnectPullUp)
			{
				/* set pin direction as input */
				CLR_BIT(DDRC, copy_u8Pin);
				/* set pin value in PORTC to activate Pull up resistor */
				SET_BIT(PORTC, copy_u8Pin);
			}
			/* Check if copy_u8ConnectPullUp value is LOW to deactivate pull up resistor */
			else
			{
				/* clear pin value in PORTC to de-activate Pull up resistor */
				CLR_BIT(PORTC, copy_u8Pin);
			}
			break;
		case DIO_PORTD:
			/* Check if copy_u8ConnectPullUp value is HIGH to activate pull up resistor */
			if(DIO_PIN_HIGH==copy_u8ConnectPullUp)
			{
				/* set pin direction as input */
				CLR_BIT(DDRD, copy_u8Pin);
				/* set pin value in PORTD to activate Pull up resistor */
				SET_BIT(PORTD, copy_u8Pin);
			}
			/* Check if copy_u8ConnectPullUp value is LOW to deactivate pull up resistor */
			else
			{
				/* clear pin value in PORTC to de-activate Pull up resistor */
				CLR_BIT(PORTD, copy_u8Pin);
			}
			break;
			/* wrong port */
		default:
			/* Wrong port entered set return variable to NOT OK*/
			Local_u8Status = E_NOK;
			break;
		}
	}
	/* Wrong pin number entered set return variable to NOT OK*/
	else
	{
		Local_u8Status = E_NOK;
	}
	/* return function status */
	return Local_u8Status;
}




