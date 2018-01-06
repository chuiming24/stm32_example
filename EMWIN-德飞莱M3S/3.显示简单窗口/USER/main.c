/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"
#include <stdio.h>
#include "delay.h"

#include "lcd.h"

#include "gui.h"
#include "GUIDemo.h"

extern WM_HWIN CreateFramewin(void);

void SKIN_Set(void)  //����Ĭ��Ƥ��
{
   BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);  // Sets the default skin for new widgets
   PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX); // ������Ƥ��
   CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
   HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
   FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
}

WM_HWIN hPage[2];

int main(){
	delay_init();
	NVIC_Configuration();
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600	
	LCD_Init();
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//ʹ��CRCʱ�ӣ�����STemWin����ʹ�� 
	//WM_SetCreateFlags(WM_CF_MEMDEV);
	GUI_Init();


	SKIN_Set();  								//����Ĭ��Ƥ��
	GUI_SetFont(&GUI_Font16_ASCII);
	
	hPage[0] = CreateFramewin();						//��������
	//GUI_Delay(10);
	WM_SetFocus(hPage[0]);
	
	while(1){
		GUI_Exec();
		delay_ms(1000);
		GUI_SendKeyMsg(GUI_KEY_TAB, 1); 
	}
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
