
#include "stm32f10x.h"

//1.首先我们有一个列表记录上次是否按下
//2.检测这次按下的按键，对比上次的已经按下，则收集起来。
//3.特殊按键超过2个，普通按键超过6个则不收集。但是继续扫描，对比上次按下则忽略，发现没按下则直接归零。
//4.返回收集值

static u8 tekey[6] = {32, 33, 34, 35, 36, 37};
static u8 keyValue[8] = {0};

void ScanUSBKey(){
	static u16 rowV[8] = {0};
	u8 i, j, k;
	u8 row = 0x01;
	u8 output = 0;
	u8 value = 0xff;
	u8 keyNum = 0;
	u8 tekeyNum = 0;
	
	for(i = 0; i < 8; i++){
		//P2 = ~row;
		//output = ~P3|rowV[i];
		for(j = 0; j < 8; j++){
			if(output &~ 0x01){
				value = i*8+j;
					
			}
			output >>= 1;
		}
		row <<= 1;
	}
}

