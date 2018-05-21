
#include "stm32f10x.h"

//1.����������һ���б��¼�ϴ��Ƿ���
//2.�����ΰ��µİ������Ա��ϴε��Ѿ����£����ռ�������
//3.���ⰴ������2������ͨ��������6�����ռ������Ǽ���ɨ�裬�Ա��ϴΰ�������ԣ�����û������ֱ�ӹ��㡣
//4.�����ռ�ֵ

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

