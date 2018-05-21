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


//功能说明: 检测所有按键。10MS 调用一次
void Pannelkey_Polling(void)
{
	unsigned char i;
	for(i = 0; i < BUTTON_NUMBER; i++)
		Button_Detect(&s_AllPowerkey[i]);                /* 检测所有的按键 */
}


BUTTON_T*  PanakeyVar_Init(BUTTON_T *_pBtn, unsigned char (*IsKeyDownUser)(), KEY_ENUM keyDownValue, KEY_ENUM keyUpValue,KEY_ENUM keyLongValue)
{
	/* 初始化USER按键变量，支持按下、弹起、长按 */
	_pBtn->IsKeyDownFunc = IsKeyDownUser;                /* 判断按键按下的函数 */
	_pBtn->FilterTime = BUTTON_FILTER_TIME;              /* 按键滤波时间 */
	_pBtn->LongTime = BUTTON_LONG_TIME;                  /* 长按时间 */
	_pBtn->Count = _pBtn->FilterTime / 2;            /* 计数器设置为滤波时间的一半 */
	_pBtn->State = 0;                                    /* 按键缺省状态，0为未按下 */
	_pBtn->KeyCodeDown = keyDownValue;                 /* 按键按下的键值代码 */
	_pBtn->KeyCodeUp =keyUpValue;                      /* 按键弹起的键值代码 */
	_pBtn->KeyCodeLong = keyLongValue;                 /* 按键被持续按下的键值代码 */
	_pBtn->RepeatSpeed = 0;                              /* 按键连发的速度，0表示不支持连发 */
	_pBtn->RepeatCount = 0;                              /* 连发计数器 */
	
	return _pBtn;
}

/*
*********************************************************************************************************
*        函 数 名: bsp_DetectButton
*        功能说明: 检测一个按键。非阻塞状态，必须被周期性的调用。
*        形    参：按键结构变量指针
*        返 回 值: 无
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

				/* 发送按钮按下的消息 */
				if (_pBtn->KeyCodeDown > 0) {
					/* 键值放入按键FIFO */
					Pannelkey_Push(_pBtn->KeyCodeDown);// 记录按键按下标志，等待释放

				}
			}

			if (_pBtn->LongTime > 0) {
				if (_pBtn->LongCount < _pBtn->LongTime) {
					/* 发送按钮持续按下的消息 */
					if (++_pBtn->LongCount == _pBtn->LongTime) {
						/* 键值放入按键FIFO */
						Pannelkey_Push(_pBtn->KeyCodeLong);

					}
				} else {
					if (_pBtn->RepeatSpeed > 0) {
						if (++_pBtn->RepeatCount >= _pBtn->RepeatSpeed) {
							_pBtn->RepeatCount = 0;
							/* 常按键后，每隔10ms发送1个按键 */
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

				/* 发送按钮弹起的消息 */
				if (_pBtn->KeyCodeUp > 0) { /*按键释放*/
					/* 键值放入按键FIFO */
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
	// 定义一个队列 放入按键值
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
