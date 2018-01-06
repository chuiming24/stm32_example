#include "stm32f10x.h"
#include <stdio.h>

void LedInit(void);

int main(void)
{
	unsigned int i;
	LedInit();
  while (1)
  {
		GPIO_SetBits(GPIOC, GPIO_Pin_8);
		GPIO_SetBits(GPIOD, GPIO_Pin_2);
		GPIO_ResetBits(GPIOD, GPIO_Pin_2);

		for(i = 0x3fffff; i > 0; i--);

		GPIO_ResetBits(GPIOC, GPIO_Pin_8);
		GPIO_SetBits(GPIOD, GPIO_Pin_2);
		GPIO_ResetBits(GPIOD, GPIO_Pin_2);		
		
		for(i = 0x3fffff; i > 0; i--);
  }
}


void LedInit(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_All;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
