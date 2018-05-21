/* 按键滤波时间50ms, 单位10ms
 *只有连续检测到50ms状态不变才认为有效，包括弹起和按下两种事件
 */
#define BUTTON_FILTER_TIME         5
#define BUTTON_LONG_TIME         300                /* 持续1秒，认为长按事件 */
#define BUTTON_BUFFER_LENGTH			16
#define BUTTON_NUMBER							 2


typedef enum {
	KEY_NONE = 0,                        /* 0 表示按键事件 */

	KEY_DOWN_Power,                        /* 按键键按下 */
	KEY_UP_Power,                        /* 按键键弹起 */
	KEY_LONG_Power,                        /* 按键键长按 */
	
	KEY_DOWN_User,                        /* 按键键按下 */
	KEY_UP_User,                        /* 按键键弹起 */
	KEY_LONG_User,                        /* 按键键长按 */

} KEY_ENUM;

/*
        每个按键对应1个全局的结构体变量。
        其成员变量是实现滤波和多种按键状态所必须的
*/
typedef struct {
	/* 下面是一个函数指针，指向判断按键手否按下的函数 */
	unsigned char  (*IsKeyDownFunc)(void); /* 按键按下的判断函数,1表示按下 */

	unsigned char  Count;                        /* 滤波器计数器 */
	unsigned char  FilterTime;                /* 滤波时间(最大255,表示2550ms) */
	unsigned short LongCount;                /* 长按计数器 */
	unsigned short LongTime;                /* 按键按下持续时间, 0表示不检测长按 */
	unsigned char   State;                        /* 按键当前状态（按下还是弹起） */
	KEY_ENUM  KeyCodeUp;                /* 按键弹起的键值代码, 0表示不检测按键弹起 */
	KEY_ENUM  KeyCodeDown;        /* 按键按下的键值代码, 0表示不检测按键按下 */
	KEY_ENUM  KeyCodeLong;        /* 按键长按的键值代码, 0表示不检测长按 */
	unsigned char  RepeatSpeed;        /* 连续按键周期 */
	unsigned char  RepeatCount;        /* 连续按键计数器 */
} BUTTON_T;




void Powerkey_Add(BUTTON_T *_pBtn);
BUTTON_T*  PanakeyVar_Init(BUTTON_T *_pBtn, unsigned char (*IsKeyDownUser)(), KEY_ENUM keyDownValue, KEY_ENUM keyUpValue,KEY_ENUM keyLongValue);

void Panakey_Init(void);
void Pannelkey_Polling(void);
KEY_ENUM Pannelkey_Pull(void);
