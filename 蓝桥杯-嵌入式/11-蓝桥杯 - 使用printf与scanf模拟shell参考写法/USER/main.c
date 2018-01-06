/* Includes ------------------------------------------------------------------*/


#include "config.h"

u32 TimingDelay = 0;

void Delay_Ms(u32 nTime);
void USART_SendString(char *str);



int main(){
	u16 i;
	int input[4];
	char char_temp[21];
	
	LCD_Configuration();
	SYSTick_Configuration();
	RCC_Configuration();
	GPIO_Configuration();
	USART_Configuration();	
	NVIC_Configuration();
	

	LCD_DisplayStringLine(Line1,(u8 *)char_temp);	
	printf("\r\nHello World!\r\n");
	printf("printf function!\r\n");
	printf("This Program can multiply of four number!\r\n");
	while(1){
		printf("%s", "Please input next Number:");
		for(i = 0; i < 3; i++){
			scanf("%d", &input[i]);	printf("\r\n");
			//printf("%d\r\n", input[i]);
			printf("%s", "Please input next Number:");		
		}
		scanf("%d", &input[i]);	printf("\r\n");
		printf("%s:%d * %d * %d * %d = %d\r\n", 
					"Count", 
					input[0], input[1],input[2],input[3],
					input[0]*input[1]*input[2]*input[3]);
		printf("Press any key to next calculate.\r\n");
		
		getchar();printf("\r\n");
	}
}


int fputc(int ch, FILE *f)
{
	USART_SendData(USART2, (uint8_t) ch);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	return ch;
}

int fgetc(FILE *f){
	uint16_t ch;
	while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
	ch = USART_ReceiveData(USART2);
	putchar(ch);
	return (int)ch;
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
