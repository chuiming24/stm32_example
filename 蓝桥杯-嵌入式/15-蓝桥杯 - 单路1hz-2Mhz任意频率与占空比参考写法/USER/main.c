/* Includes ------------------------------------------------------------------*/

#include "config.h"

//TIM1_ETR PA12 PE7
//TIM1_CH1 PA8 PE9
//TIM1_CH2 PA9 PE11
//TIM1_CH3 PA10 PE13
//TIM1_CH4 PA11 PE14
//TIM1_BKIN PB12 PA6 PE15
//TIM1_CH1N PB13	PA7 PE8
//TIM1_CH2N PB14	PB0 PE10
//TIM1_CH3N PB15 PB1 PE12

//TIM2_CH1_ETR	PA0 PA15 PA0 PA15
//TIM2_CH2 PA1 PB3 PA1 PB3
//TIM2_CH3 PA2 PB10
//TIM2_CH4 PA3 PB11

//TIM3_CH1 PA6 PB4 PC6
//TIM3_CH2 PA7 PB5 PC7
//TIM3_CH3 PB0 PC8
//TIM3_CH4 PB1 PC9

//TIM4_CH1 PB6 PD12
//TIM4_CH2 PB7 PD13
//TIM4_CH3 PB8 PD14
//TIM4_CH4 PB9 PD15



u32 TimingDelay = 0;
u32 number = 0;

extern u32 pwm_FQ;	//1-1Mhz
extern u32 pwm_ChanOne_Pulse;		//0-100

void Delay_Ms(u32 nTime);

int main(){
	char char_temp[21];

	
	SysTick_Configuration();	
	RCC_Configuration();
	GPIO_Configuration();
	TIM_Configuration();
	USART_Configuration();
	NVIC_Configuration();
	LCD_Configuration();
	
	sprintf(char_temp, "%s", "  Please input the ");
	LCD_DisplayStringLine(Line5, (u8 *)char_temp);

	sprintf(char_temp, "%s", "data through serial");
	LCD_DisplayStringLine(Line6, (u8 *)char_temp);
	
	sprintf(char_temp, "%s", "port by the computer");
	LCD_DisplayStringLine(Line7, (u8 *)char_temp);

	sprintf(char_temp, "%s", "        ----from TT");
	LCD_DisplayStringLine(Line9, (u8 *)char_temp);
	
	LCD_SetBackColor(White);
	LCD_SetTextColor(Blue);	
	
	while(1){
		LCD_DisplayStringLine(Line0, (u8 *)"The pwn in PA1.      ");
		
		LCD_DisplayStringLine(Line1, (u8 *)"                     ");
		
		sprintf(char_temp, "%s:%dHz            ", "pwn_FQ", pwm_FQ);
		LCD_DisplayStringLine(Line2, (u8 *)char_temp);
		
		sprintf(char_temp, "%s:%d/100            ", "pwn_Pulse", pwm_ChanOne_Pulse);
		LCD_DisplayStringLine(Line3, (u8 *)char_temp);
		
		printf("%s", "Please input pwm_FQ Number:");
		scanf("%d", &pwm_FQ);
		printf("%d\r\n", pwm_FQ);

		printf("%s", "Please input pwm_ChanOne_Pulse Number:");
		scanf("%d", &pwm_ChanOne_Pulse);		
		printf("%d\r\n", pwm_ChanOne_Pulse);
		
		TIM_Configuration();
		printf("Sussessful.\r\n");
			
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
	return (int)ch;
}


void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}





/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
