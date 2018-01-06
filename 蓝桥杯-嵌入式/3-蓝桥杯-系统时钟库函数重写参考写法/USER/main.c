/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>

/**
//高频锁相环系统时钟顺序

	系统时钟可以通过HSE或者HSI（HSI会自动除以2，HSE则可以选择不除以2）
	然后通过PLLMUL进行倍频，从2倍频到16倍频，但是最高不能超过72，所以外部最高72，内部最高64
	接着进入SW进行选择，此时可以直接选择HSI,HSE或者PLL为SYSCLK，也就是系统时钟
	系统时钟通过预分频AHB输出HCLK，可以从1到512进行选择
	然后APB1进行分频PCLK1到外设，可以选择从1到16分频，但是最高36
	然后APB2进行分频PCLK2到外设，可以选择从1到16分频，但是最高72
		APB2分频为1，则TIM1-8频率为PCLK2，否则则为PCLK2*2
	ADC分频为APB2/2，4，6，8，但是最大为14，所以一般为4

**/

//以下是使用库函数进行时钟初始化 , 注意除了要包含RCC，misc外，还要包含flash库函数

//原库为寄存器进行初始化，并且没有写HSE失败的HSI部分。

//该工程已经对库自带的初始化进行注释，可以详见以下函数
extern void SystemInit();

//若为HSI初始化，则最大频率为64，此时要注意系统滴答定时器的设置
void SysTInit(u16 sysClock)
{
	//初始化为AHB的8分频
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	
	//当为72则一个滴答定时器时间为8/(72M)秒，为64则为8/(64M)秒
	if(sysClock == 72){
		//此时SystemCoreClock宏定义为72，所以为72000 000/8/1000 = 9000，8/(72M)  *9000 = 1微妙
		SysTick_Config(SystemCoreClock / 1000);
	}else if(sysClock == 64){
		//为64000000/8/1000 = 8000，8/(64M)  *8000 = 1微妙
		SysTick_Config(64000000  / 1000);	
	}
}

int main(){
	u16 nCount = 0;
	ErrorStatus HSEStartUpStatus;
	//重置时钟设置
	RCC_DeInit();
	//尝试打开外部晶振
	RCC_HSEConfig(RCC_HSE_ON);
	//等待外部晶振就绪
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET &&
		nCount++ < HSE_STARTUP_TIMEOUT);
	//查询外部晶振是否就绪
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus == SUCCESS)
	{
		//flash读取缓冲，加速
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		//flash延时，等待读取完成（因为CPU运行过快）
		FLASH_SetLatency(FLASH_Latency_2);
		
		//-------------------
		//设置AHB系统时钟
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
			//  AHB负责外部存储器时钟，由HCLK进行分频
		
		//设置APB2的系统时钟
		RCC_PCLK2Config(RCC_HCLK_Div1);
			//	APB2负责AD,IO,高级定时器，串口1，由PCLK2进行分频
		
		//设置APB1的系统时钟
		RCC_PCLK2Config(RCC_HCLK_Div2);
			//	APB1负责DA,USB,SPI,I2C,CAN,串口2345,普通TIM，由PCLK1进行分频
		
		//设置ADC分频
		RCC_ADCCLKConfig(RCC_PCLK2_Div4);
		
		// Flash 2 wait state
		*(vu32 *)0x40022000 = 0x01;
		
		//倍频设置
		//PLLCLK = 8MHZ *9 = 72MHZ
		RCC_PLLConfig (RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		//PLLCLK = 8MHZ/2 *16 = 64MHZ
		//RCC_PLLConfig (RCC_PLLSource_HSE_Div2, RCC_PLLMul_16);

		//启动PPL
		RCC_PLLCmd(ENABLE);
		
		//等待PLL启动
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		//将PLL设置为系统时钟源
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		//等待系统时钟源的启动
		while(RCC_GetSYSCLKSource() != 0x08);
		
		//初始化滴答定时器
		SysTInit(72);
	}
	//HSE初始化失败，则初始化内部HSI
	else
	{
		RCC_HSEConfig(RCC_HSE_OFF);
		RCC_DeInit();
		
		//打开内部晶振
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
		
		//将PLL设置为系统时钟源
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		//等待系统时钟源的启动
		while(RCC_GetSYSCLKSource() != 0x08);		
		
		//初始化滴答定时器
		SysTInit(64);
		
	}
	while(1){
		
	}
}
/******END OF FILE****/
