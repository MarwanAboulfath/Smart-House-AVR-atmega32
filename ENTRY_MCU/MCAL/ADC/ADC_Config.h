/*
 * ADC_Config.h
 *
 *  Created on: Mar 25, 2024
 *      Author: Marwan
 */

#ifndef MCAL_ADC_ADC_CONFIG_H_
#define MCAL_ADC_ADC_CONFIG_H_


/*
 * Options:
 * 1.AREFF
 * 2.AVCC
 * 3.VOLT_2_56
 */
#define ADC_REF_SELECTION              	VOLT_2_56


/*
 * Options:
 * 1.LEFT
 * 2.RIGHT
 */
#define ADC_ADJUST_RESULT					RIGHT

/*
 *Options:
 * 1- ENABLE
 * 2- DISABLE
 */

#define ADC_AUTO_TRIGGER_ENABLE				DISABLE


/*
 *Options:
 * 1- ENABLE
 * 2- DISABLE
 */
#define ADC_INTERRUPT_ENABLE				DISABLE

/*
 * 1- DIVISION_FACTOR_2
 * 2- DIVISION_FACTOR_4
 * 3- DIVISION_FACTOR_8
 * 4- DIVISION_FACTOR_16
 * 5- DIVISION_FACTOR_32
 * 6- DIVISION_FACTOR_64
 * 7- DIVISION_FACTOR_128
  */

#define ADC_PRESCALER				DIVISION_FACTOR_64





/*
 * Options:
 * 1.CHANNEL0
 * 2.CHANNEL1
 * 3.CHANNEL2
 * 4.CHANNEL3
 * 5.CHANNEL4
 * 6.CHANNEL5
 * 7.CHANNEL6
 * 8.CHANNEL7
 */
#define ADC_CHANNEL						CHANNEL0




#endif /* MCAL_ADC_ADC_CONFIG_H_ */
