/*****************************************************************************************
 ****************** @file           : keypad.h		         	      ********************
 ****************** @author         : Ehab Magdy Abdallah             ********************
 ****************** @brief          : interface file Keypad           ********************
******************************************************************************************/

#ifndef KEYPAD_KEYPAD_H_
#define KEYPAD_KEYPAD_H_

/******************************          Includes           ******************************/
#include "stm32f4xx_hal.h"

#define KEYPAD_ROWS     4
#define KEYPAD_COLOUMNS 3

/******************************   Data Types Decelerations  ******************************/
typedef struct{
	GPIO_TypeDef*     keypadRows_Port[KEYPAD_ROWS];
	uint16_t		  keypadRows_Pin[KEYPAD_ROWS];
	GPIO_TypeDef*     keypadCols_Port[KEYPAD_COLOUMNS];
	uint16_t		  keypadCols_Pin[KEYPAD_COLOUMNS];
}keypad_t;

extern const keypad_t keypad;

/******************************      Software intefaces      ******************************/
uint8_t keypad_Read_Value(const keypad_t *keypad);

#endif /* KEYPAD_KEYPAD_H_ */
