/* �����˲�ʱ��50ms, ��λ10ms
 *ֻ��������⵽50ms״̬�������Ϊ��Ч����������Ͱ��������¼�
 */
#define BUTTON_FILTER_TIME         5
#define BUTTON_LONG_TIME         300                /* ����1�룬��Ϊ�����¼� */
#define BUTTON_BUFFER_LENGTH			16
#define BUTTON_NUMBER							 2


typedef enum {
	KEY_NONE = 0,                        /* 0 ��ʾ�����¼� */

	KEY_DOWN_Power,                        /* ���������� */
	KEY_UP_Power,                        /* ���������� */
	KEY_LONG_Power,                        /* ���������� */
	
	KEY_DOWN_User,                        /* ���������� */
	KEY_UP_User,                        /* ���������� */
	KEY_LONG_User,                        /* ���������� */

} KEY_ENUM;

/*
        ÿ��������Ӧ1��ȫ�ֵĽṹ�������
        ���Ա������ʵ���˲��Ͷ��ְ���״̬�������
*/
typedef struct {
	/* ������һ������ָ�룬ָ���жϰ����ַ��µĺ��� */
	unsigned char  (*IsKeyDownFunc)(void); /* �������µ��жϺ���,1��ʾ���� */

	unsigned char  Count;                        /* �˲��������� */
	unsigned char  FilterTime;                /* �˲�ʱ��(���255,��ʾ2550ms) */
	unsigned short LongCount;                /* ���������� */
	unsigned short LongTime;                /* �������³���ʱ��, 0��ʾ����ⳤ�� */
	unsigned char   State;                        /* ������ǰ״̬�����»��ǵ��� */
	KEY_ENUM  KeyCodeUp;                /* ��������ļ�ֵ����, 0��ʾ����ⰴ������ */
	KEY_ENUM  KeyCodeDown;        /* �������µļ�ֵ����, 0��ʾ����ⰴ������ */
	KEY_ENUM  KeyCodeLong;        /* ���������ļ�ֵ����, 0��ʾ����ⳤ�� */
	unsigned char  RepeatSpeed;        /* ������������ */
	unsigned char  RepeatCount;        /* �������������� */
} BUTTON_T;




void Powerkey_Add(BUTTON_T *_pBtn);
BUTTON_T*  PanakeyVar_Init(BUTTON_T *_pBtn, unsigned char (*IsKeyDownUser)(), KEY_ENUM keyDownValue, KEY_ENUM keyUpValue,KEY_ENUM keyLongValue);

void Panakey_Init(void);
void Pannelkey_Polling(void);
KEY_ENUM Pannelkey_Pull(void);
