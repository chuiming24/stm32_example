/* Includes ------------------------------------------------------------------*/
//该开发板的ADC在PB0，因此，应该在ADC1的通道8或者ADC2的通道8

#include "config.h"



u32 TimingDelay = 0;

void Delay_Ms(u32 nTime);

int main(){
	float adc_temp;
	char char_temp[21];

	LCD_Configuration();
	SysTick_Configuration();	
	RCC_Configuration();
	GPIO_Configuration();
	DMA_Configuration();
	ADC_Configuration();
	
	
	while(1){
		Delay_Ms(100);
		adc_temp = ADCConvertedValue*3.30/0xfff;
		sprintf(char_temp,"%s%.3f","ADC Nunber:",adc_temp);
		LCD_DisplayStringLine(Line7,(u8 *)char_temp);		
	}
}

void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}



/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
