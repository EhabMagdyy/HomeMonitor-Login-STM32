/*
 * lcd.c
 *
 *  Created on: Apr 3, 2024
 *      Author: Ehab
 */

#include <stdint.h>
#include "lcd.h"

extern TIM_HandleTypeDef htim10;  // Enable a timer, adjust its Frequency to (1MHz) to get a tick each 1us.

/* Generate a MicroSecond delay */
static void Delay_US(uint16_t delay)
{
	__HAL_TIM_SET_COUNTER(&htim10, 0);
	while(__HAL_TIM_GET_COUNTER(&htim10) < delay);
}

static void LCD_Send_4bit(const lcd_t *lcd, uint8_t data);
static void LCD_Send_Enable_Signal(const lcd_t *lcd);
static void LCD_Set_Cursor(const lcd_t *lcd, uint8_t row, uint8_t colomn);

const lcd_t lcd =
{
		.Lcd_Port = GPIOA,
		.RS_Pin = GPIO_PIN_0,
		.EN_Pin = GPIO_PIN_1,
		.Data_Pins[0] = GPIO_PIN_2,
		.Data_Pins[1] = GPIO_PIN_3,
		.Data_Pins[2] = GPIO_PIN_4,
		.Data_Pins[3] = GPIO_PIN_5,
};

void lCD_Init(const lcd_t *lcd)
{
	if(NULL != lcd)
	{
		HAL_Delay(40);
		LCD_Send_Command(lcd, 0x3);
		HAL_Delay(1);
		LCD_Send_Command(lcd, 0x2);
		HAL_Delay(1);
		LCD_Send_Command(lcd, 0x2);  //4 bit mode
		HAL_Delay(1);

        LCD_Send_Command(lcd, LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        HAL_Delay(3);
    	LCD_Send_Command(lcd, LCD_CLEAR);
    	HAL_Delay(3);
    	LCD_Send_Command(lcd, LCD_4BIT_MODE_2LINES);
    	HAL_Delay(3);
	}
	else{ /* Do Nothing */ }
}

void LCD_Send_Command(const lcd_t *lcd, uint8_t command)
{
	if(NULL != lcd)
	{
        HAL_GPIO_WritePin(lcd->Lcd_Port, lcd->RS_Pin, GPIO_PIN_RESET);
        LCD_Send_4bit(lcd, command >> 4);
        LCD_Send_Enable_Signal(lcd);
        LCD_Send_4bit(lcd, command);
        LCD_Send_Enable_Signal(lcd);
	}
	else{ /* Do Nothing */ }
}

void LCD_Send_Char(const lcd_t *lcd, uint8_t data)
{
	if(NULL != lcd)
	{
		HAL_GPIO_WritePin(lcd->Lcd_Port, lcd->RS_Pin, GPIO_PIN_SET);
        LCD_Send_4bit(lcd, data >> 4);
        LCD_Send_Enable_Signal(lcd);
        LCD_Send_4bit(lcd, data);
        LCD_Send_Enable_Signal(lcd);
        Delay_US(50);
	}
	else{ /* Do Nothing */ }
}

void LCD_Send_Char_Pos(const lcd_t *lcd, uint8_t row, uint8_t colomn, uint8_t data)
{
	if(NULL != lcd)
	{
		LCD_Set_Cursor(lcd, row, colomn);
		LCD_Send_Char(lcd, data);
	}
	else{ /* Do Nothing */ }
}

void LCD_Send_String(const lcd_t *lcd, uint8_t *string)
{
	if(NULL != lcd && NULL != string)
	{
        do{
        	LCD_Send_Char(lcd, *string);
        } while(*(++string));
	}
	else{ /* Do Nothing */ }
}

void LCD_Send_String_Pos(const lcd_t *lcd, uint8_t row, uint8_t colomn, uint8_t *string)
{
	if(NULL != lcd && NULL != string)
	{
		LCD_Set_Cursor(lcd, row, colomn);
		LCD_Send_String(lcd, string);
	}
	else{ /* Do Nothing */ }
}

void LCD_Send_Custom_Character(const lcd_t *lcd, uint8_t row, uint8_t colomn,
                                                const uint8_t ch[], uint8_t mem_pos)
{
	if(NULL != lcd)
	{
		LCD_Send_Command(lcd, (LCD_CGRAM_START + (mem_pos * 8)));
        for(uint8_t char_index = 0 ; char_index < 8 ; char_index++){
        	LCD_Send_Char(lcd, ch[char_index]);
        }
        LCD_Send_Char_Pos(lcd, row, colomn, mem_pos);
	}
	else{ /* Do Nothing */ }
}

static void LCD_Send_4bit(const lcd_t *lcd, uint8_t data)
{
    if(NULL != lcd)
    {
        for(uint8_t line_pins = 0 ; line_pins < 4 ; line_pins++)
        {
        	HAL_GPIO_WritePin(lcd->Lcd_Port, lcd->Data_Pins[line_pins], (data >> line_pins) & 0x01);
        }
    }
    else{ /* Do Nothing */ }
}

static void LCD_Send_Enable_Signal(const lcd_t *lcd)
{
    if(NULL != lcd)
    {
        HAL_GPIO_WritePin(lcd->Lcd_Port, lcd->EN_Pin, GPIO_PIN_SET);
        Delay_US(5);
        HAL_GPIO_WritePin(lcd->Lcd_Port, lcd->EN_Pin, GPIO_PIN_RESET);
    }
    else{ /* Do Nothing */ }
}

static void LCD_Set_Cursor(const lcd_t *lcd, uint8_t row, uint8_t colomn)
{
    if(NULL != lcd && row <= NUMBER_OF_ROWS && colomn <= NUMBER_OF_COLOMNS)
    {
        colomn--;
        switch(row)
        {
            case ROW1: LCD_Send_Command(lcd, (0x80 + colomn));  break;
            case ROW2: LCD_Send_Command(lcd, (0xc0 + colomn));  break;
            default:                                            break;
        }
        Delay_US(50);
    }
}
