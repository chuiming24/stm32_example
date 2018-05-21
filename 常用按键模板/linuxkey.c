#include <linuxkey.h>

static KEY_ENUM KeyValueBuffer[BUTTON_BUFFER_LENGTH];
static unsigned char KeyValueLength = 0;
static BUTTON_T s_AllPowerkey[BUTTON_NUMBER];
static unsigned char s_AllPowerkeyLength = 0;

void Powerkey_Add(BUTTON_T *_pBtn);
void Button_Detect(BUTTON_T *_pBtn);
void Pannelkey_Push(KEY_ENUM KeyVlue);

void Powerkey_Add(BUTTON_T *_pBtn)
{
	if(s_AllPowerkeyLength < BUTTON_NUMBER){
		s_AllPowerkey[s_AllPowerkeyLength] = *_pBtn;
		s_AllPowerkeyLength++;
	}
}


//����˵��: ������а�����10MS ����һ��
void Pannelkey_Polling(void)
{
	unsigned char i;
	for(i = 0; i < BUTTON_NUMBER; i++)
		Button_Detect(&s_AllPowerkey[i]);                /* ������еİ��� */
}


BUTTON_T*  PanakeyVar_Init(BUTTON_T *_pBtn, unsigned char (*IsKeyDownUser)(), KEY_ENUM keyDownValue, KEY_ENUM keyUpValue,KEY_ENUM keyLongValue)
{
	/* ��ʼ��USER����������֧�ְ��¡����𡢳��� */
	_pBtn->IsKeyDownFunc = IsKeyDownUser;                /* �жϰ������µĺ��� */
	_pBtn->FilterTime = BUTTON_FILTER_TIME;              /* �����˲�ʱ�� */
	_pBtn->LongTime = BUTTON_LONG_TIME;                  /* ����ʱ�� */
	_pBtn->Count = _pBtn->FilterTime / 2;            /* ����������Ϊ�˲�ʱ���һ�� */
	_pBtn->State = 0;                                    /* ����ȱʡ״̬��0Ϊδ���� */
	_pBtn->KeyCodeDown = keyDownValue;                 /* �������µļ�ֵ���� */
	_pBtn->KeyCodeUp =keyUpValue;                      /* ��������ļ�ֵ���� */
	_pBtn->KeyCodeLong = keyLongValue;                 /* �������������µļ�ֵ���� */
	_pBtn->RepeatSpeed = 0;                              /* �����������ٶȣ�0��ʾ��֧������ */
	_pBtn->RepeatCount = 0;                              /* ���������� */
	
	return _pBtn;
}

/*
*********************************************************************************************************
*        �� �� ��: bsp_DetectButton
*        ����˵��: ���һ��������������״̬�����뱻�����Եĵ��á�
*        ��    �Σ������ṹ����ָ��
*        �� �� ֵ: ��
*********************************************************************************************************
*/
void Button_Detect(BUTTON_T *_pBtn)
{
	if (_pBtn->IsKeyDownFunc()) {
		if (_pBtn->Count < _pBtn->FilterTime) {
			_pBtn->Count = _pBtn->FilterTime;
		} else if(_pBtn->Count < 2 * _pBtn->FilterTime) {
			_pBtn->Count++;
		} else {
			if (_pBtn->State == 0) {
				_pBtn->State = 1;

				/* ���Ͱ�ť���µ���Ϣ */
				if (_pBtn->KeyCodeDown > 0) {
					/* ��ֵ���밴��FIFO */
					Pannelkey_Push(_pBtn->KeyCodeDown);// ��¼�������±�־���ȴ��ͷ�

				}
			}

			if (_pBtn->LongTime > 0) {
				if (_pBtn->LongCount < _pBtn->LongTime) {
					/* ���Ͱ�ť�������µ���Ϣ */
					if (++_pBtn->LongCount == _pBtn->LongTime) {
						/* ��ֵ���밴��FIFO */
						Pannelkey_Push(_pBtn->KeyCodeLong);

					}
				} else {
					if (_pBtn->RepeatSpeed > 0) {
						if (++_pBtn->RepeatCount >= _pBtn->RepeatSpeed) {
							_pBtn->RepeatCount = 0;
							/* ��������ÿ��10ms����1������ */
							Pannelkey_Push(_pBtn->KeyCodeDown);

						}
					}
				}
			}
		}
	} else {
		if(_pBtn->Count > _pBtn->FilterTime) {
			_pBtn->Count = _pBtn->FilterTime;
		} else if(_pBtn->Count != 0) {
			_pBtn->Count--;
		} else {
			if (_pBtn->State == 1) {
				_pBtn->State = 0;

				/* ���Ͱ�ť�������Ϣ */
				if (_pBtn->KeyCodeUp > 0) { /*�����ͷ�*/
					/* ��ֵ���밴��FIFO */
					Pannelkey_Push(_pBtn->KeyCodeUp);

				}
			}
		}

		_pBtn->LongCount = 0;
		_pBtn->RepeatCount = 0;
	}
}


void Pannelkey_Push(KEY_ENUM KeyVlue)
{
	if(KeyValueLength < BUTTON_BUFFER_LENGTH){
		KeyValueBuffer[KeyValueLength] = KeyVlue;
		KeyValueLength++;
	}
	// ����һ������ ���밴��ֵ
}

KEY_ENUM Pannelkey_Pull(void)
{
	if(KeyValueLength != 0){
		KeyValueLength--;
		return KeyValueBuffer[KeyValueLength];
	}else{
		return KEY_NONE;
	}
}
