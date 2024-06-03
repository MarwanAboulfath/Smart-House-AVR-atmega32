/*
 * STEPPER_Interface.h
 *
 *  Created on: Mar 21, 2024
 *      Author: Marwan
 */

#ifndef HAL_STEPPER_STEPPER_INTERFACE_H_
#define HAL_STEPPER_STEPPER_INTERFACE_H_

/********************** Function Prototypes ********************/
#define NORTH				0
#define EASTERN_NORTH		1
#define EAST				2
#define EASTERN_SOUTH		3
#define SOUTH				4
#define WESTERN_SOUTH		5
#define WEST				6
#define WESTERN_NORTH		7

void STEPPER_Init(void);

void STEPPER_voidRotate(u8 copy_u8Direction);




#endif /* HAL_STEPPER_STEPPER_INTERFACE_H_ */
