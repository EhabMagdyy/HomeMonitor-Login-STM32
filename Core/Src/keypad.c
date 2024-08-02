/*****************************************************************************************
 ****************** @file           : keypad.c		         	      ********************
 ****************** @author         : Ehab Magdy Abdallah             ********************
 ****************** @brief          : interface file Keypad           ********************
******************************************************************************************/

/******************************          Includes           ******************************/
#include "keypad.h"

/******************************  Data Types Decelerations   ******************************/
const keypad_t keypad =
{
    .keypadRows_Port[0] = GPIOB,
	.keypadRows_Port[1] = GPIOB,
	.keypadRows_Port[2] = GPIOB,
	.keypadRows_Port[3] = GPIOB,
    .keypadRows_Pin[0] = GPIO_PIN_3,
	.keypadRows_Pin[1] = GPIO_PIN_4,
	.keypadRows_Pin[2] = GPIO_PIN_5,
	.keypadRows_Pin[3] = GPIO_PIN_6,

    .keypadCols_Port[0] = GPIOB,
    .keypadCols_Port[1] = GPIOB,
    .keypadCols_Port[2] = GPIOB,
    .keypadCols_Pin[0] = GPIO_PIN_7,
    .keypadCols_Pin[1] = GPIO_PIN_8,
    .keypadCols_Pin[2] = GPIO_PIN_9,
};

static const uint8_t keypad_matrix[KEYPAD_ROWS][KEYPAD_COLOUMNS] = {
																	{'1','2','3'},
																	{'4','5','6'},
																	{'7','8','9'},
																	{'*','0','#'}
};

/******************************      Software interfaces    ******************************/
uint8_t keypad_Read_Value(const keypad_t *keypad)
{
	uint8_t keypad_value = 0;

	if(NULL != keypad)
	{
		uint8_t pin_state = 0;

		for(uint8_t rows = 0 ; (rows < KEYPAD_ROWS) && (0 == keypad_value) ; rows++)
		{
			HAL_GPIO_WritePin(keypad->keypadRows_Port[rows], keypad->keypadRows_Pin[rows], GPIO_PIN_SET);
			for(uint8_t col = 0 ; (col < KEYPAD_COLOUMNS) && (0 == keypad_value) ; col++)
			{
				pin_state = HAL_GPIO_ReadPin(keypad->keypadCols_Port[col], keypad->keypadCols_Pin[col]);

				if(GPIO_PIN_SET == pin_state)
				{
					keypad_value = keypad_matrix[rows][col];
					while(GPIO_PIN_SET == HAL_GPIO_ReadPin(keypad->keypadCols_Port[col], keypad->keypadCols_Port[col]));
				}
				else { /* Do Nothing */ }
			}

			HAL_GPIO_WritePin(keypad->keypadRows_Port[rows], keypad->keypadRows_Pin[rows], GPIO_PIN_RESET);
		}
	}
	else { /* Do Nothing */ }

	return keypad_value;
}
