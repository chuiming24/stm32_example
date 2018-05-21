#include "stm32f10x.h"
#include "led.h"


void LED_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIOC->ODR = 0xffff;
	GPIO_SetBits(GPIOD, GPIO_Pin_2);
	GPIO_ResetBits(GPIOD, GPIO_Pin_2);
}

void LED_Control(uint16_t LED,uint8_t LED_Status)
{
	static u16 LED_Bit = 0xffff;
	
	if(LED_Status == 0){
		LED_Bit |= (1<<(8+LED));
		
		GPIO_Write(GPIOC, LED_Bit);
		GPIO_SetBits(GPIOD,GPIO_Pin_2);
		GPIO_ResetBits(GPIOD,GPIO_Pin_2);  
	}        
	else
	{
		LED_Bit &= ~(1<<(8+LED));
		
		GPIO_Write(GPIOC, LED_Bit);
		GPIO_SetBits(GPIOD,GPIO_Pin_2);
		GPIO_ResetBits(GPIOD,GPIO_Pin_2);  
	}
}

