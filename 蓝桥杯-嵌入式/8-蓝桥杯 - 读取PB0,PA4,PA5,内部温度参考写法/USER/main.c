/* Includes ------------------------------------------------------------------*/
//该开发板的ADC在PB0，因此，应该在ADC1的通道8或者ADC2的通道8
//内部温度传感器尽量每次读取间隔超过200ms，或者单独将其作为独立的通道（但是这样就太浪费了），误差是正负1.5（很悲伤的误差）
//该工程请连接扩展版测试

#include "config.h"



u32 TimingDelay = 0;

uint16_t Read_ADC(u8 ch);
void Delay_Ms(u32 nTime);

int main(){
	float adc_temp_float;
	u16 adc_temp;
	char char_temp[21];

	LCD_Configuration();
	SysTick_Configuration();	
	RCC_Configuration();
	GPIO_Configuration();
	ADC_Configuration();
	
	while(1){
		Delay_Ms(200);
		adc_temp = Read_ADC(ADC_Channel_16);
		adc_temp_float = (1.43-adc_temp*3.3/0xfff)*1000/4.35 + 25;
		sprintf(char_temp,"%s%.3f^C","Temp Nunber:",adc_temp_float);
		LCD_DisplayStringLine(Line5,(u8 *)char_temp);		
		
		Delay_Ms(50);
		adc_temp = Read_ADC(ADC_Channel_8);
		adc_temp_float =  adc_temp*3.30/0xfff;
		sprintf(char_temp,"%s%.3f","PB0 Nunber:",adc_temp_float);
		LCD_DisplayStringLine(Line6,(u8 *)char_temp);	
		
		Delay_Ms(50);
		adc_temp = Read_ADC(ADC_Channel_4);
		adc_temp_float =  adc_temp*3.30/0xfff;
		sprintf(char_temp,"%s%.3f","PA4 Nunber:",adc_temp_float);
		LCD_DisplayStringLine(Line7,(u8 *)char_temp);	
		
		Delay_Ms(50);
		adc_temp = Read_ADC(ADC_Channel_5);
		adc_temp_float =  adc_temp*3.30/0xfff;
		sprintf(char_temp,"%s%.3f","PA5 Nunber:",adc_temp_float);
		LCD_DisplayStringLine(Line8,(u8 *)char_temp);	
	}
}

void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}

uint16_t Read_ADC(u8 ch)
{
	uint16_t ADC_VALUE;
	
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);

	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	Delay_Ms(5);
	ADC_VALUE = ADC_GetConversionValue(ADC1);
	
	return ADC_VALUE;
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
