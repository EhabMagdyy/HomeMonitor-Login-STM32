/*
 * lcd.h
 *
 *  Created on: Apr 3, 2024
 *      Author: Ehab
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

/******************************          Includes           ******************************/
#include "stm32f4xx_hal.h"

/******************************     Macro Deceleration	   	******************************/
#define LCD_CLEAR                                   0x01
#define LCD_CURSOR_HOME                             0x02

#define LCD_DECREMENT_SHIFT_OFF                     0x04
#define LCD_DECREMENT_SHIFT_ON                      0x05
#define LCD_INCREMENT_SHIFT_OFF                     0x06
#define LCD_INCREMENT_SHIFT_ON                      0x07

#define LCD_DISPLAY_OFF_UNDERLINE_OFF_CURSOR_OFF    0x08
#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF     0x0C
#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON      0x0D
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF      0x0E
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON       0x0F

#define LCD_MOVE_CURSOR_SHIFT_LEFT                  0x10
#define LCD_MOVE_CURSOR_SHIFT_RIGHT                 0x14
#define LCD_SHIFT_DISPLAY_SHIFT_LEFT                0x18
#define LCD_SHIFT_DISPLAY_SHIFT_RIGHT               0x1C

#define LCD_4BIT_MODE_2LINES                        0x28
#define LCD_8BIT_MODE_2LINES                        0x38

#define LCD_CGRAM_START                             0x40
#define LCD_DDRAM_START                             0x80

#define NUMBER_OF_ROWS          2
#define NUMBER_OF_COLOMNS       16

#define ROW1    1
#define ROW2    2

/******************************   Data Types Decelerations  ******************************/
typedef struct
{
	GPIO_TypeDef*     Lcd_Port;
	uint16_t		  RS_Pin;
	uint16_t		  EN_Pin;
	uint16_t		  Data_Pins[4];
} lcd_t;

extern const lcd_t lcd;

/******************************      Software interfaces     ******************************/
void lCD_Init(const lcd_t *lcd);
void LCD_Send_Command(const lcd_t *lcd, uint8_t command);
void LCD_Send_Char(const lcd_t *lcd, uint8_t data);
void LCD_Send_Char_Pos(const lcd_t *lcd, uint8_t row, uint8_t colomn, uint8_t data);
void LCD_Send_String(const lcd_t *lcd, uint8_t *string);
void LCD_Send_String_Pos(const lcd_t *lcd, uint8_t row, uint8_t colomn, uint8_t *string);
void LCD_Send_Custom_Character(const lcd_t *lcd, uint8_t row, uint8_t colomn,
                                                const uint8_t ch[], uint8_t mem_pos);

#endif /* INC_LCD_H_ */
