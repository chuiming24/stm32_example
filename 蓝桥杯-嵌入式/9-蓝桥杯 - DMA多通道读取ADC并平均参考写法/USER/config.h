#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "stm32f10x.h"
#include "lcd.h"
#include <stdio.h>

#define adc_N 50 //每个通道采集50次
#define adc_M 3 //为3个通道
extern vu16 AD_Value[adc_N][adc_M];
extern vu16 After_filter[adc_M]; //存放求平均值之后的结果

void LCD_Configuration(void);
void SysTick_Configuration(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void DMA_Configuration(void);
void ADC_Configuration(void);



#endif
