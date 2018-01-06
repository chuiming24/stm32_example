/* Includes ------------------------------------------------------------------*/

#include "config.h"



u32 TimingDelay = 0;
u32 number = 0;

void Delay_Ms(u32 nTime);

int main(){
	char char_temp[21];

	
	SysTick_Configuration();	
	RCC_Configuration();
	GPIO_Configuration();
	TIM_Configuration();
	NVIC_Configuration();
	LCD_Configuration();
	while(1){
		sprintf(char_temp, "%s:%ds", "second", number);
		LCD_DisplayStringLine(Line1, (u8 *)char_temp);
	}
}

void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}




/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
