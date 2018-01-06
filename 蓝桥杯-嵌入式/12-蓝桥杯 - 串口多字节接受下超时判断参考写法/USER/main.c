/* Includes ------------------------------------------------------------------*/


#include "config.h"

u32 TimingDelay = 0;
extern u16 usart2_ready_buf_len;
extern u8 usart2_ready_buf[65];
extern u8 usart2_ready_buf_ok;

void Delay_Ms(u32 nTime);
void USART_SendString(char *str);



int main(){
	char char_temp[21] = "Welcome to TT home!";
	
	LCD_Configuration();
	SYSTick_Configuration();
	RCC_Configuration();
	GPIO_Configuration();
	USART_Configuration();	
	NVIC_Configuration();
	

	LCD_DisplayStringLine(Line1,(u8 *)char_temp);	
	printf("\r\nHello World!\r\n");
	printf("printf function!\r\n");
	while(1){
		if(usart2_ready_buf_ok){
			usart2_ready_buf_ok = 0;
			printf("%s", usart2_ready_buf);
		}
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
    while(str[index] != 0);  //检查字符串结束标志
    
}

void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
