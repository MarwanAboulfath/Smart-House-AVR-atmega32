/*
 * EXTI_Interface.h
 *
 *  Created on: Mar 24, 2024
 *      Author: Marwan
 */

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

/*********************GENERAL MACROS**********************************/




/*********************FUNCTIONS PROTOTYPES******************************/
void EXTI_voidInit (void);

void EXTI0_voidInit(void);

void EXTI0_voidDeInit(void);

void EXTI1_voidInit(void);

void EXTI1_voidDeInit(void);


u8 EXTI_u8SetInt0SenseControl (u8 Copy_u8SenseControl);
u8 EXTI_u8SetInt1SenseControl (u8 Copy_u8SenseControl);
u8 EXTI_u8SetInt2SenseControl (u8 Copy_u8SenseControl);
u8 EXTI_u8Int0SetCallBack (void (*Copy_pvNotificationFunction) (void));
u8 EXTI_u8Int1SetCallBack (void (*Copy_pvNotificationFunction) (void));
u8 EXTI_u8Int2SetCallBack (void (*Copy_pvNotificationFunction) (void));

#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
