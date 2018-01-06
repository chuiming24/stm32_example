/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"
#include <stdio.h>
#include "delay.h"

#include "lcd.h"

#include "gui.h"
#include "GUIDemo.h"
int main(){
	delay_init();
	NVIC_Configuration();
	uart_init(9600);	 	//串口初始化为9600	
	LCD_Init();
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//使能CRC时钟，否则STemWin不能使用 
	WM_SetCreateFlags(WM_CF_MEMDEV);
	GUI_Init();

	GUI_SetBkColor(GUI_BLUE);
	GUI_SetColor(GUI_YELLOW);
	GUI_Clear();
	
	GUI_SetFont(&GUI_Font24B_ASCII);
	GUI_DispStringAt("Hello, Word!", 0, 0);
	
	while(1);
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
