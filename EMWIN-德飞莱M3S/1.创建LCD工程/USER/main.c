/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"
#include <stdio.h>
#include "delay.h"

#include <lcd.h>

int main(){
	delay_init();
	NVIC_Configuration();
	uart_init(9600);	 	//串口初始化为9600	
	LCD_Init();
	
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"M3S STM32");	
	while(1){
		LCD_ShowString(30,130,200,16,16,"01234567890");	   
		Draw_Circle(100,180,25);			
	}
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
