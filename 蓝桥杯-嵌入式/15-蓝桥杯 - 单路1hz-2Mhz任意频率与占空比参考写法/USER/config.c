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
  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

}

void GPIO_Configuration(){
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  /* Configure USART2 Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  /* Configure USART3 Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  //GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
}


u32 pwm_FQ = 3000;	//1-1Mhz
u32 pwm_ChanOne_Pulse = 30;		//0-100
void TIM_Configuration(){
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	
	u32 temp32;
	u32 uhFre;
	u16 uhPeriod;
	u16 uhPrecaler;
	u16 uhChanOnePulse;
	
	if (pwm_FQ >= 4000){
		uhFre = pwm_FQ;
		uhPrecaler = 1;
	}else{
		uhFre = 4000;
		uhPrecaler = 4000/pwm_FQ;
		uhFre = uhPrecaler * pwm_FQ;
	}
	
	temp32 = (SystemCoreClock/uhFre);
	if(temp32 > 65535){
		temp32 = 65535;
	}
	uhPeriod = (u16)temp32;
	
	if(pwm_ChanOne_Pulse > 100){
		pwm_ChanOne_Pulse = 100;
	}
	uhChanOnePulse = uhPeriod * pwm_ChanOne_Pulse /100;
	
  TIM_TimeBaseStructure.TIM_Period = uhPeriod - 1;
  TIM_TimeBaseStructure.TIM_Prescaler = uhPrecaler - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);



  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = uhChanOnePulse;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC2Init(TIM2, &TIM_OCInitStructure);	
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	

//	TIM_CtrlPWMOutputs(TIM2, ENABLE);

//	/* Channel 2 and 3 Configuration in PWM mode */
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
//	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
//	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
//	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
//	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;	
//	TIM_OC2Init(TIM2, &TIM_OCInitStructure);

//	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
//	TIM_OC3Init(TIM2, &TIM_OCInitStructure);

	//TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);	

	TIM_Cmd(TIM2, ENABLE);
	
	TIM_CtrlPWMOutputs(TIM2, ENABLE);

}

void USART_Configuration(void){
	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &USART_InitStructure);

	USART_ClearFlag(USART2,USART_FLAG_TC);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART2, ENABLE);	
}

void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
	
  /* Enable the TIM3 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);

}
