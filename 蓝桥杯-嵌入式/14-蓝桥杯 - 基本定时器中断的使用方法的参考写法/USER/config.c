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
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

}

void GPIO_Configuration(){

}

void TIM_Configuration(){
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
  TIM_TimeBaseStructure.TIM_Period = 50000;
  TIM_TimeBaseStructure.TIM_Prescaler = 71;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* Prescaler configuration */
  TIM_PrescalerConfig(TIM3, 71, TIM_PSCReloadMode_Immediate);	
	
	TIM_ITConfig(TIM3,TIM_IT_Update, ENABLE);	

	TIM_Cmd(TIM3, ENABLE);

}

void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
	
  /* Enable the TIM3 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);

}
