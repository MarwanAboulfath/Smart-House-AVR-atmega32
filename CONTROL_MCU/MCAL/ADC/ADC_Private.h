/*
 * ADC_Private.h
 *
 *  Created on: Mar 25, 2024
 *      Author: Marwan
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

#define ADMUX              (*((volatile u8*)(0x27)))
#define ADCSRA             (*((volatile u8*)(0x26)))
#define ADCH               (*((volatile u8*)(0x25)))
#define ADCL               (*((volatile u8*)(0x24)))
#define SFIOR              (*((volatile u8*)(0x50)))

/* ADMUX_REG BITS */
#define REFS1              7
#define REFS0              6
#define ADLAR              5
#define MUX4               4
#define MUX3               3
#define MUX2               2
#define MUX1               1
#define MUX0               0

/* ADCSRA_REG BITS */
#define ADEN               7
#define ADSC               6
#define ADATE              5
#define ADIF               4
#define ADIE			   3
#define ADPS2              2
#define ADPS1              1
#define ADPS0              0

/*****************PRIVATE MACROS************************/
/*ADC_REF_SELECTION*/
#define AREFF				1
#define AVCC				2
#define VOLT_2_56			3

/*ADC_ADJUST_RESULT*/
#define LEFT				1
#define RIGHT				2

#define ENABLE				1
#define DISABLE				2

/******** ADC prescaler macros ************/


/*ADC_PRESCALER*/
#define DIVISION_FACTOR_2					0b00000000
#define DIVISION_FACTOR_4					0b00000010
#define DIVISION_FACTOR_8					0b00000011
#define DIVISION_FACTOR_16					0b00000100
#define DIVISION_FACTOR_32					0b00000101
#define DIVISION_FACTOR_64					0b00000110
#define DIVISION_FACTOR_128					0b00000111

/* ADC prescaler macros */
#define ADC_PRESCALER_RESET_MASK			0b11111000

#define ADC_PRESCALER_RESET_MACRO()			ADCSRA &= ADC_PRESCALER_RESET_MASK

#define ADC_PRESCALER_SET(MASK)				ADCSRA |= MASK

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
