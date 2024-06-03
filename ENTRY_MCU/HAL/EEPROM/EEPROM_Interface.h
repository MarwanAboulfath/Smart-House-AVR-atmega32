/*
 * EEPROM_Interface.h
 *
 *  Created on: 06-04-2024
 *   Author: Marwan Aboulfath
 *
 */
#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_



/*********************************************************************************/
/*							FUNCTIONS PROTOTYPES								 */
/*********************************************************************************/
void EEPROM_voidInit(void);
void EEPROM_voidSendDataByte(u8 Copy_u8DataByte , u16 Copy_u16Address);
u8 EEPROM_u8ReadDataByte(u16 Copy_u16Adderss);




#endif /* EEPROM_INTERFACE_H_ */
