#include <linuxkey.h>

//�Ƿ��а������½ӿں���
unsigned char  IsKeyDownPower(void)
{
	if ( 0 ) 
		return 1;
	return 0;
}

//�Ƿ��а������½ӿں���
unsigned char  IsKeyDownUser(void)
{
	if (0 ) 
		return 1;
	return 0;
}

void  PanakeyHard_Init(void)
{
	BUTTON_T s_Powerkey;
	s_Powerkey = *(PanakeyVar_Init(&s_Powerkey, IsKeyDownPower, KEY_DOWN_Power, KEY_UP_Power, KEY_LONG_Power));
	Powerkey_Add(&s_Powerkey);
	
	s_Powerkey = *(PanakeyVar_Init(&s_Powerkey, IsKeyDownUser, KEY_DOWN_User, KEY_UP_User, KEY_LONG_User));
	Powerkey_Add(&s_Powerkey);
	
}

//void PanakeyVar_Init(void){
//	
//}


void Panakey_Init(void)
{
	PanakeyHard_Init();                /* ��ʼ���������� */
	//PanakeyVar_Init();                /* ��ʼ������Ӳ�� */
}

