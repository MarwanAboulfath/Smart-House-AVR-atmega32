/*
 * USART_Interface.h
 *
 *  Created on: Apr 1, 2024
 *      Author: Marwan
 */

#ifndef MCAL_USART_USART_INTERFACE_H_
#define MCAL_USART_USART_INTERFACE_H_

void USART_voidInit (void);

u8   USART_u8SendData (u8 Copy_u8Data);

u8   USART_u8RecevieData (u8 * Copy_u8ReceviedData) ;

u8   USART_u8SendStringSynch (const u8 * Copy_pchString);
u8   USART_u8SendStringAsynch (const u8 * Copy_pchString , void (* NotificationFunc)(void)) ;

u8   USART_u8ReceiveBufferSynch (u8 * Copy_pchString , u32 Copy_uint32BufferSize) ;
u8   USART_u8ReceiveBufferAsynch (u8 * Copy_pchString , u32 Copy_uint32BufferSize , void (* NotificationFunc)(void)) ;

#endif /* MCAL_USART_USART_INTERFACE_H_ */
