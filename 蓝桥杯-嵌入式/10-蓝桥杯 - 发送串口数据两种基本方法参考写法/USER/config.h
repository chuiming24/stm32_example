#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "stm32f10x.h"
#include "lcd.h"
#include <stdio.h>

void LCD_Configuration(void);
void SYSTick_Configuration(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);

#endif
