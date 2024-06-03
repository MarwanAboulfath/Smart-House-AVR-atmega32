/*
 * ADC_Program.c
 *
 *  Created on: Mar 25, 2024
 *      Author: Marwan
 */
/***************************************************************/
/*                        FILE INCLUSIONS                      */
/***************************************************************/

/*******************************LIB*****************************/
#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_MATH.h"
/******************************MCAL*****************************/
#include "ADC_Config.h"
#include "ADC_Interface.h"
#include "ADC_Private.h"




/*********************FUNCTIONS IMPLEMENTATION*****************/

/******************FUNCTIONS DEFINITIONS*****************/
void ADC_voidInit(void)
{
#if ADC_REF_SELECTION == AREFF
	CLR_BIT(ADMUX, REFS0);
	CLR_BIT(ADMUX, REFS1);
#elif ADC_REF_SELECTION == AVCC
	SET_BIT(ADMUX, REFS0);
	CLR_BIT(ADMUX, REFS1);

#elif ADC_REF_SELECTION == VOLT_2_56
	SET_BIT(ADMUX, REFS0);
	SET_BIT(ADMUX, REFS1);

#else
#error "ADC_REF_SELECTION error configuration parameter!"

#endif

	/***************Challenge: Make configurations***************/

#if ADC_ADJUST_RESULT == LEFT
	SET_BIT(ADMUX, ADLAR);
#elif ADC_ADJUST_RESULT == RIGHT
	CLR_BIT(ADMUX, ADLAR);
#else
#error "ADC_ADJUST_RESULT error configuration parameter!"
#endif


#if ADC_AUTO_TRIGGER_ENABLE == ENABLE
	SET_BIT(ADCSRA, ADATE);
#elif ADC_AUTO_TRIGGER_ENABLE == DISABLE
	/*clear AUTO trigger ADC, so the ADC conversion will start only when you call:  ADC_convert_read() */
	CLR_BIT(ADCSRA, ADATE);
#else
#error "ADC_AUTO_TRIGGER_ENABLE error configuration parameter!"
#endif


#if ADC_INTERRUPT_ENABLE == ENABLE
	SET_BIT(ADCSRA, ADIE);
#elif ADC_INTERRUPT_ENABLE == DISABLE
	/*disable ADC interrupt: */
	CLR_BIT(ADCSRA, ADIE);
#else
#error "ADC_INTERRUPT_ENABLE error configuration parameter!"
#endif

	/* Set prescaler value */
	ADC_PRESCALER_RESET_MACRO();
	ADC_PRESCALER_SET(ADC_PRESCALER);


//#if ADC_PRESCALER == DIVISION_FACTOR_2
//
//#elif ADC_PRESCALER == DIVISION_FACTOR_4
//
//#elif ADC_PRESCALER == DIVISION_FACTOR_8
//
//#elif ADC_PRESCALER == DIVISION_FACTOR_16
//
//#elif ADC_PRESCALER == DIVISION_FACTOR_32
//
//#elif ADC_PRESCALER == DIVISION_FACTOR_64
//	/*set pre-scaler to be: (F_CPU/64) = (8000000/64) = 125 KHz */
//	CLR_BIT(ADCSRA, ADPS0);
//	SET_BIT(ADCSRA, ADPS1);
//	SET_BIT(ADCSRA, ADPS2);
//
//#elif ADC_PRESCALER == DIVISION_FACTOR_128
//
//#else
//#error "ADC_PRESCALER error configuration parameter!"
//#endif


	/*enable ADC peripheral in MCU*/
	SET_BIT(ADCSRA, ADEN);
}



u16 ADC_u16GetConversionReading(u8 copy_u8Channel)
{
	u16 ADC_data = 0;

	if(copy_u8Channel == CHANNEL0)
	{
		/*select input channel to pin PA0*/
		CLR_BIT(ADMUX, MUX0);
		CLR_BIT(ADMUX, MUX1);
		CLR_BIT(ADMUX, MUX2);
		CLR_BIT(ADMUX, MUX3);
		CLR_BIT(ADMUX, MUX4);
	}

	else if(copy_u8Channel == CHANNEL1)
	{
		/*select input channel to pin PA1*/
		SET_BIT(ADMUX, MUX0);
		CLR_BIT(ADMUX, MUX1);
		CLR_BIT(ADMUX, MUX2);
		CLR_BIT(ADMUX, MUX3);
		CLR_BIT(ADMUX, MUX4);
	}

	else if(copy_u8Channel == CHANNEL2)
	{
		/*select input channel to pin PA2*/
		CLR_BIT(ADMUX, MUX0);
		SET_BIT(ADMUX, MUX1);
		CLR_BIT(ADMUX, MUX2);
		CLR_BIT(ADMUX, MUX3);
		CLR_BIT(ADMUX, MUX4);
	}

	else if(copy_u8Channel == CHANNEL3)
	{

		/*select input channel to pin PA3*/
		SET_BIT(ADMUX, MUX0);
		SET_BIT(ADMUX, MUX1);
		CLR_BIT(ADMUX, MUX2);
		CLR_BIT(ADMUX, MUX3);
		CLR_BIT(ADMUX, MUX4);
	}

	else if(copy_u8Channel == CHANNEL4)
	{
		/*select input channel to pin PA4*/
		CLR_BIT(ADMUX, MUX0);
		CLR_BIT(ADMUX, MUX1);
		SET_BIT(ADMUX, MUX2);
		CLR_BIT(ADMUX, MUX3);
		CLR_BIT(ADMUX, MUX4);
	}

	else if(copy_u8Channel == CHANNEL5)
	{

		/*select input channel to pin PA5*/
		SET_BIT(ADMUX, MUX0);
		CLR_BIT(ADMUX, MUX1);
		SET_BIT(ADMUX, MUX2);
		CLR_BIT(ADMUX, MUX3);
		CLR_BIT(ADMUX, MUX4);
	}

	else if(copy_u8Channel == CHANNEL6)
	{

		/*select input channel to pin PA6*/
		CLR_BIT(ADMUX, MUX0);
		SET_BIT(ADMUX, MUX1);
		SET_BIT(ADMUX, MUX2);
		CLR_BIT(ADMUX, MUX3);
		CLR_BIT(ADMUX, MUX4);
	}
	else if(copy_u8Channel == CHANNEL7)
	{

		/*select input channel to pin PA7*/
		SET_BIT(ADMUX, MUX0);
		SET_BIT(ADMUX, MUX1);
		SET_BIT(ADMUX, MUX2);
		CLR_BIT(ADMUX, MUX3);
		CLR_BIT(ADMUX, MUX4);
	}

	/*start conversion:*/
	SET_BIT(ADCSRA, ADSC);
	/*wait until conversion ended*/
	while(GET_BIT(ADCSRA, ADSC) == 1)
	{
		//wait until ADSC bit becomes zero
	}
	/*after conversion is finished, read data from ADCL then ADCH*/
	ADC_data = ADCL;
	ADC_data |= (ADCH << 8);

	/*return ADC data*/
	return ADC_data;
}
