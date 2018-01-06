/* ------------------------------------------------------------------*/
// �˹��̵ĺ궨�壬����λ���Լ���ȡ������ʹ��stm32�ĳ�����Ժ�51��ͨ�����������ֲ
/* ------------------------------------------------------------------*/
//λ����ʽ��A Ϊ ����Ĵ���GPIOx->�ĵ�ַ��
//  ((A-0x40000000)*8+n)*4 
//= 0x42000000+ (A-0x40000000)*32 + n*4
/* ------------------------------------------------------------------*/



#include "stm32f10x.h"
#include <stdio.h>

//λ���궨��
#define BITBAND_REG(Reg,Bit) (*((uint32_t volatile*)(0x42000000u + (((uint32_t)&(Reg) - (uint32_t)0x40000000u)<<5) + (((uint32_t)(Bit))<<2))))
//����궨��
#define LED1 BITBAND_REG(GPIOC->ODR,8)
#define LED2 BITBAND_REG(GPIOC->ODR,9)
#define LED_LE BITBAND_REG(GPIOD->ODR,2)
//�����궨��
#define RB1	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define RB2	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define RB3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define RB4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)

u32 TimingDelay;
void Delay_Ms(u32 nTime);
void LED_Init(void);
void Key_Init(void);


int main(){
	LED_Init();
	Key_Init();
	SysTick_Config(SystemCoreClock / 1000);
	while(1){
		if(RB1 == 0){
			//����
			Delay_Ms(10);		
			if(RB1 == 0){	
				//ֱ���ͷŲŴ�������
				while(RB1 == 0);
				LED1 = 0;
				LED_LE = 1;
				LED_LE = 0;	
			}
		}
		if(RB2 == 0){
			Delay_Ms(10);
			if(RB2 == 0){	
				while(RB2 == 0);
				LED1 = 1;
				LED_LE = 1;
				LED_LE = 0;	
			}
		}
		if(RB3 == 0){
			Delay_Ms(10);
			if(RB3 == 0){	
				while(RB3 == 0);
				LED2 = 1;
				LED_LE = 1;
				LED_LE = 0;	
			}
		}
		if(RB4 == 0){
			Delay_Ms(10);
			if(RB4 == 0){
				while(RB4 == 0);
				LED2 = 0;
				LED_LE = 1;
				LED_LE = 0;	
			}
		}
	}
}

void LED_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIOC->ODR = 0xffff;
	GPIO_SetBits(GPIOD, GPIO_Pin_2);
	GPIO_ResetBits(GPIOD, GPIO_Pin_2);
}

void Key_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    //B1��B2������������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_8; // 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //B3��B4������������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void Delay_Ms(u32 nTime){
	TimingDelay = nTime;
	while(TimingDelay != 0);
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
