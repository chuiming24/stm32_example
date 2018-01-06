#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "stm32f10x.h"

#include <stdio.h>

#include "lcd.h"
#include "led.h"
#include "usmart.h"



void LCD_Configuration(void);
void SYSTick_Configuration(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);
void NVIC_Configuration(void);

#endif
