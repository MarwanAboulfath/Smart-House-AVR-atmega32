/*
 * LCD_Interface.h
 *
 *  Created on: Mar 19, 2024
 *      Author: Marwan
 */

#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_

/****************************POSITIONS*********************/

#define LCD_ROW0				0
#define LCD_ROW1				1

#define LCD_COLUMN0				0
#define LCD_COLUMN1				1
#define LCD_COLUMN2				2
#define LCD_COLUMN3				3
#define LCD_COLUMN4				4
#define LCD_COLUMN5				5
#define LCD_COLUMN6				6
#define LCD_COLUMN7				7
#define LCD_COLUMN8				8
#define LCD_COLUMN9				9
#define LCD_COLUMN10			10
#define LCD_COLUMN11			11
#define LCD_COLUMN12			12
#define LCD_COLUMN13			13
#define LCD_COLUMN14			14
#define LCD_COLUMN15			15



/******************************* MODES*********************/
#define LCD_FOUR_BIT			1
#define LCD_EIGHT_BIT			2

/************************** FUNCTION PROTOTYPES ***************/

void LCD_voidInit(void);

void LCD_voidSendCommand(u8 copy_u8Command);

void LCD_voidSendData(u8 copy_u8Data);

void LCD_voidSendString(const u8* copy_pu8String);

void LCD_voidSetPosition(u8 copy_u8XPosition,u8 copy_u8YPosition);

void LCD_voidSendNumber(s64 copy_s32Number);

void LCD_voidSendCustomCharacter(u8* copy_pu8CharacterArray,u8 copy_u8PatternNumber,u8 copy_u8XPosition,u8 copy_u8YPosition);

void LCD_voidClearScreen(void);




#endif /* HAL_LCD_LCD_INTERFACE_H_ */
