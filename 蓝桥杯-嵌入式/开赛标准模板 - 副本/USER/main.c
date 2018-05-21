
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stdio.h"
#include "lcd.h"
#include "led.h"
#include "key.h"

//LCD位于PC0-PC15，与LED共享高位，其他脚见说明书
//LED位于PC8-PC15，高电平灭，低电平亮，采用573在PD2进行锁存

u32 TimingDelay = 0;

void Delay_Ms(u32 nTime);


#define DEBUG_STAT 1
void debug(void);

#define SYSTEM_STAT 1


int  main(){
	//初始化LCD, LED, 滴答定时器
	STM3210B_LCD_Init();
	LED_Init();
	SysTick_Config(SystemCoreClock /1000);
	KEY_Init();
	
	//清屏，并设置字体背景和颜色
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	
	//测试显示屏
	LCD_DisplayStringLine(Line4 ,(u8 *)"    Hello,world.   ");
	Delay_Ms(500);
	
	while(1){
		if(DEBUG_STAT){
			debug();
		}
		else{
			switch(SYSTEM_STAT){
				case 1:
					break;
			}
		}
		
	}
	
}


void debug(){
u16 key_temp = 0;
u8 char_temp[20] = {0};
	
	while(1){
		switch(DEBUG_STAT){
			case 1:
				LED_Control(LED1,1);
				LCD_DisplayStringLine(Line4 ,(u8 *)"    Open led1.   ");
				Delay_Ms(1000);
				
				LED_Control(LED3,1);
				LCD_DisplayStringLine(Line4 ,(u8 *)"    Open led3.   ");
				Delay_Ms(1000);
				
				LED_Control(LED3,0);
				LCD_DisplayStringLine(Line4 ,(u8 *)"    Close led3.   ");
				Delay_Ms(1000);			
				
				LED_Control(LED1,0);
				LCD_DisplayStringLine(Line4 ,(u8 *)"    Close led1.   ");
				Delay_Ms(1000);		
				break;
			case 2:
				key_temp = ScanKey();
				if(key_temp != 0xff)
					sprintf((char *)char_temp, "%u", key_temp);
				LCD_DisplayStringLine(Line4 ,(u8 *)char_temp);
				break;
		}
	}
}


void Delay_Ms(u32 nTime){
	TimingDelay = nTime;
	while(TimingDelay != 0);
}



/************************END OF FILE**********************/
