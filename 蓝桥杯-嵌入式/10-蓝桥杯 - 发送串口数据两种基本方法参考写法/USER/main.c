/* Includes ------------------------------------------------------------------*/


//�ù�����ʾ������ض���ʵ��΢��printf��ʹ���Լ��Լ�д��String Send����ʹ��
//��stm32F1��72MƵ���У���������ʸ���38400���Ƽ�ʹ���Լ���д��send��������Ϊprintf�����Ĵ����ٶ��Ѿ���ʼ����ƿ����
#include "config.h"

u32 TimingDelay = 0;

void Delay_Ms(u32 nTime);
void USART_SendString(char *str);

char char_temp[21];

int main(){
	
	LCD_Configuration();
	SYSTick_Configuration();
	RCC_Configuration();
	GPIO_Configuration();
	USART_Configuration();	
	

	LCD_DisplayStringLine(Line1,(u8 *)char_temp);	
	printf("Hello World!\r\n");
	printf("printf function!\r\n");
	USART_SendString("Welcome to taotao home\r\n");
	USART_SendString("sendString function\r\n");
	while(1){
		
	}
}


int fputc(int ch, FILE *f)
{
	USART_SendData(USART2, (uint8_t) ch);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	return ch;
}


void USART_SendString(char *str)
{
    uint8_t index = 0;
    
    do
    {
        USART_SendData(USART2,str[index]);
        while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET);
        index++;        
    }
    while(str[index] != 0);  //����ַ���������־
    
}

void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
