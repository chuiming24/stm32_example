#include "stm32f10x.h"
#include "key.h"

extern KeyFlag;

//按键宏定义
#define RB1	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define RB2	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define RB3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define RB4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)
#define PRESS_KEY RB1 == 0 || RB2 == 0 || RB3 == 0 || RB4 == 0

void KEY_Init(void){
    GPIO_InitTypeDef  GPIO_InitStructure;
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    //B1、B2按键引脚配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_8; // 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //B3、B4按键引脚配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_Init(GPIOB, &GPIO_InitStructure);	
}

u32 ScanKey(){
	static u8 KeyStat = 0;
	static u16 KeyCount = 0;
	u8 KeyValue = 0xff;
	
	if(KeyFlag){
		switch(KeyStat){
			case 0:		//检测按下
				if(PRESS_KEY){
					KeyStat = 1;
				}	
			case 1:		//消抖
				if(PRESS_KEY){
					KeyStat = 2;
				}else{
					KeyStat = 0;
				}
			case 2:		//短按
				if(PRESS_KEY){
					if(RB1 == 0) KeyValue = 1;
					if(RB2 == 0) KeyValue = 2;
					if(RB3 == 0) KeyValue = 3;
					if(RB4 == 0) KeyValue = 4;
					KeyStat = 3;
				}else{
					KeyStat = 5;
				}	
			case 3:		//长按前奏
				if(PRESS_KEY){
					KeyCount++;
					if(KeyCount == 100){
						KeyCount = 0;
						KeyStat = 4;
					}
				}else{
					KeyCount = 0;
					KeyStat = 0;
				}		
			case 4:		//长按中
				if(PRESS_KEY){
					if(RB1 == 0) KeyValue = 5;
					if(RB2 == 0) KeyValue = 6;
					if(RB3 == 0) KeyValue = 7;
					if(RB4 == 0) KeyValue = 8;
				}else{
					KeyStat = 5;
				}						
			case 5:		//键释放
				if(PRESS_KEY){
					
				}else{
					KeyStat = 0;
				}				
				
		}
	}
	return KeyValue;
} 
