/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>

/**
//��Ƶ���໷ϵͳʱ��˳��

	ϵͳʱ�ӿ���ͨ��HSE����HSI��HSI���Զ�����2��HSE�����ѡ�񲻳���2��
	Ȼ��ͨ��PLLMUL���б�Ƶ����2��Ƶ��16��Ƶ��������߲��ܳ���72�������ⲿ���72���ڲ����64
	���Ž���SW����ѡ�񣬴�ʱ����ֱ��ѡ��HSI,HSE����PLLΪSYSCLK��Ҳ����ϵͳʱ��
	ϵͳʱ��ͨ��Ԥ��ƵAHB���HCLK�����Դ�1��512����ѡ��
	Ȼ��APB1���з�ƵPCLK1�����裬����ѡ���1��16��Ƶ���������36
	Ȼ��APB2���з�ƵPCLK2�����裬����ѡ���1��16��Ƶ���������72
		APB2��ƵΪ1����TIM1-8Ƶ��ΪPCLK2��������ΪPCLK2*2
	ADC��ƵΪAPB2/2��4��6��8���������Ϊ14������һ��Ϊ4

**/

//������ʹ�ÿ⺯������ʱ�ӳ�ʼ�� , ע�����Ҫ����RCC��misc�⣬��Ҫ����flash�⺯��

//ԭ��Ϊ�Ĵ������г�ʼ��������û��дHSEʧ�ܵ�HSI���֡�

//�ù����Ѿ��Կ��Դ��ĳ�ʼ������ע�ͣ�����������º���
extern void SystemInit();

//��ΪHSI��ʼ���������Ƶ��Ϊ64����ʱҪע��ϵͳ�δ�ʱ��������
void SysTInit(u16 sysClock)
{
	//��ʼ��ΪAHB��8��Ƶ
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	
	//��Ϊ72��һ���δ�ʱ��ʱ��Ϊ8/(72M)�룬Ϊ64��Ϊ8/(64M)��
	if(sysClock == 72){
		//��ʱSystemCoreClock�궨��Ϊ72������Ϊ72000 000/8/1000 = 9000��8/(72M)  *9000 = 1΢��
		SysTick_Config(SystemCoreClock / 1000);
	}else if(sysClock == 64){
		//Ϊ64000000/8/1000 = 8000��8/(64M)  *8000 = 1΢��
		SysTick_Config(64000000  / 1000);	
	}
}

int main(){
	u16 nCount = 0;
	ErrorStatus HSEStartUpStatus;
	//����ʱ������
	RCC_DeInit();
	//���Դ��ⲿ����
	RCC_HSEConfig(RCC_HSE_ON);
	//�ȴ��ⲿ�������
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET &&
		nCount++ < HSE_STARTUP_TIMEOUT);
	//��ѯ�ⲿ�����Ƿ����
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus == SUCCESS)
	{
		//flash��ȡ���壬����
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		//flash��ʱ���ȴ���ȡ��ɣ���ΪCPU���й��죩
		FLASH_SetLatency(FLASH_Latency_2);
		
		//-------------------
		//����AHBϵͳʱ��
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
			//  AHB�����ⲿ�洢��ʱ�ӣ���HCLK���з�Ƶ
		
		//����APB2��ϵͳʱ��
		RCC_PCLK2Config(RCC_HCLK_Div1);
			//	APB2����AD,IO,�߼���ʱ��������1����PCLK2���з�Ƶ
		
		//����APB1��ϵͳʱ��
		RCC_PCLK2Config(RCC_HCLK_Div2);
			//	APB1����DA,USB,SPI,I2C,CAN,����2345,��ͨTIM����PCLK1���з�Ƶ
		
		//����ADC��Ƶ
		RCC_ADCCLKConfig(RCC_PCLK2_Div4);
		
		// Flash 2 wait state
		*(vu32 *)0x40022000 = 0x01;
		
		//��Ƶ����
		//PLLCLK = 8MHZ *9 = 72MHZ
		RCC_PLLConfig (RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		//PLLCLK = 8MHZ/2 *16 = 64MHZ
		//RCC_PLLConfig (RCC_PLLSource_HSE_Div2, RCC_PLLMul_16);

		//����PPL
		RCC_PLLCmd(ENABLE);
		
		//�ȴ�PLL����
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		//��PLL����Ϊϵͳʱ��Դ
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		//�ȴ�ϵͳʱ��Դ������
		while(RCC_GetSYSCLKSource() != 0x08);
		
		//��ʼ���δ�ʱ��
		SysTInit(72);
	}
	//HSE��ʼ��ʧ�ܣ����ʼ���ڲ�HSI
	else
	{
		RCC_HSEConfig(RCC_HSE_OFF);
		RCC_DeInit();
		
		//���ڲ�����
		RCC_HSICmd(ENABLE);
		nCount = 0;
		while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET && nCount++ < HSE_STARTUP_TIMEOUT);
		
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
		
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div2); 
		
		//PLLCLK = 8MHZ/2 *16 = 64MHZ
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16);
		
		RCC_PLLCmd(ENABLE);
		
		//��PLL����Ϊϵͳʱ��Դ
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		//�ȴ�ϵͳʱ��Դ������
		while(RCC_GetSYSCLKSource() != 0x08);		
		
		//��ʼ���δ�ʱ��
		SysTInit(64);
		
	}
	while(1){
		
	}
}
/******END OF FILE****/
