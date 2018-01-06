#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "stm32f10x.h"
#include "lcd.h"
#include <stdio.h>

extern __IO uint16_t ADCConvertedValue;

void LCD_Configuration(void);
void SysTick_Configuration(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void DMA_Configuration(void);
void ADC_Configuration(void);



#endif
