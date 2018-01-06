#include "config.h"

void LCD_Configuration(){
	STM3210B_LCD_Init();
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);	
}

void SysTick_Configuration(){
	SysTick_Config(SystemCoreClock/1000);
}

void RCC_Configuration(){
	RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
}

void GPIO_Configuration(){
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);	
}

void ADC_Configuration(){
	ADC_InitTypeDef ADC_InitStructure;
	
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC2, &ADC_InitStructure);	
	
	ADC_RegularChannelConfig(ADC2, ADC_Channel_8, 1, ADC_SampleTime_13Cycles5);

	ADC_Cmd(ADC2, ENABLE);   
	
  ADC_ResetCalibration(ADC2);
  while(ADC_GetResetCalibrationStatus(ADC2));

  ADC_StartCalibration(ADC2);
  while(ADC_GetCalibrationStatus(ADC2));

}
