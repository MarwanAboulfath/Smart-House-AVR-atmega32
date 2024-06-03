/*
 * KPD_Interface.h
 *
 *  Created on: Mar 20, 2024
 *      Author: Marwan
 */

#ifndef HAL_KPD_KPD_INTERFACE_H_
#define HAL_KPD_KPD_INTERFACE_H_

/***********************Function prototypes**************************/
void KPD_Init(void);

u8 KPD_u8GetPressed(void);

/****************************MACROS**********************************/

#define NOTPRESSED		0xFF

#endif /* HAL_KPD_KPD_INTERFACE_H_ */
