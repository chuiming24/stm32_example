/* Includes ------------------------------------------------------------------*/
//�ÿ������ADC��PB0����ˣ�Ӧ����ADC1��ͨ��8����ADC2��ͨ��8
//�ڲ��¶ȴ���������ÿ�ζ�ȡ�������200ms�����ߵ���������Ϊ������ͨ��������������̫�˷��ˣ������������1.5���ܱ��˵���
//�ù�����������չ�����

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
