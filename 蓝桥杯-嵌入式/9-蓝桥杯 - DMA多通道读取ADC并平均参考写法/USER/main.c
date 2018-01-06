/* Includes ------------------------------------------------------------------*/
//该开发板的ADC在PB0，因此，应该在ADC1的通道8或者ADC2的通道8

#include "config.h"



u32 TimingDelay = 0;

void Delay_Ms(u32 nTime);
void setFilter(void);

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
		
		setFilter();
		
		adc_temp = After_filter[0]*3.30/0xfff;
		sprintf(char_temp,"%s%.3f","PB0 Nunber:",adc_temp);
		LCD_DisplayStringLine(Line5,(u8 *)char_temp);		

		adc_temp = After_filter[1]*3.30/0xfff;
		sprintf(char_temp,"%s%.3f","PA4 Nunber:",adc_temp);
		LCD_DisplayStringLine(Line6,(u8 *)char_temp);		

		adc_temp = After_filter[2]*3.30/0xfff;
		sprintf(char_temp,"%s%.3f","PA5 Nunber:",adc_temp);
		LCD_DisplayStringLine(Line7,(u8 *)char_temp);		
	}
}

void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}

void setFilter()
{
	int i = 0;
	int sum = 0;
	u8 count;
	for(i=0;i<adc_M;i++){
		for ( count=0;count<adc_N;count++){
			sum += AD_Value[count][i];
		}
		After_filter[i]=sum/adc_N;
		sum=0;
	}
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
