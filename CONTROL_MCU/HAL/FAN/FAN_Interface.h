/*
 * FAN_Interface.h
 *
 *  Created on: 11-04-2024
 *   Author: Marwan Aboulfath
 *
 */
#ifndef FAN_INTERFACE_H_
#define FAN_INTERFACE_H_

/* Fan Pin Defines*/
#define FAN_PIN_OC0				1
#define FAN_PIN_OC2				2

/* Fan Speed Defines */
#define FAN_SPEED_OFF			1
#define FAN_SPEED_LOW			2
#define FAN_SPEED_MEDIUM		3
#define FAN_SPEED_HIGH			4

/* Fan States Defines */
#define FAN_OFF					0
#define FAN_ON					1


/**************************************************************/
/*					FUNCTIONS PROTOTYPES					  */
/**************************************************************/
void FAN_voidInit(u8 FAN_u8Pin);
void FAN_ON_OFF(u8 FAN_u8Pin, u8 FAN_u8State);
void FAN_voidSetSpeed(u8 FAN_u8Pin, u8 FAN_u8Speed);

#endif /* FAN_INTERFACE_H_ */
