
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stdio.h"
#include "lcd.h"
#include "led.h"

//LCDλ��PC0-PC15����LED�����λ�������ż�˵����
//LEDλ��PC8-PC15���ߵ�ƽ�𣬵͵�ƽ��������573��PD2��������

u32 TimingDelay = 0;

void Delay_Ms(u32 nTime);


int  main(){
	//��ʼ��LCD, LED, �δ�ʱ��
	STM3210B_LCD_Init();
	LED_Init();
	SysTick_Config(SystemCoreClock /1000);
	
	//���������������屳������ɫ
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	
	//������ʾ��
	LCD_DisplayStringLine(Line4 ,(u8 *)"    Hello,world.   ");
	Delay_Ms(500);
	
	while(1){
	
		LED_Control(LED1,1);
		LCD_DisplayStringLine(Line4 ,(u8 *)"    Open led1.   ");
		Delay_Ms(500);
		
		LED_Control(LED3,1);
		LCD_DisplayStringLine(Line4 ,(u8 *)"    Open led3.   ");
		Delay_Ms(500);
		
		LED_Control(LED3,0);
		LCD_DisplayStringLine(Line4 ,(u8 *)"    Close led3.   ");
		Delay_Ms(500);			
		
		LED_Control(LED1,0);
		LCD_DisplayStringLine(Line4 ,(u8 *)"    Close led1.   ");
		Delay_Ms(500);			
	}
	
}




void Delay_Ms(u32 nTime){
	TimingDelay = nTime;
	while(TimingDelay != 0);
}



/************************END OF FILE**********************/
