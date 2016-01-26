
#pragma once

/*ͨ��ʧ�ܱ�ʾ*/
#define COMM_RESULT_ERR		0xFF
/*ͨ�ųɹ���ʾ*/
#define COMM_RESULT_SUC 0

/////////////////////////// ö������ ///////////////////////////

/*����ID*/
typedef enum 
{
	COM_0				= 0,				// COM0
	COM_1				,					// COM1
	COM_2				,					// COM2
	COM_3				,					// COM3
	COM_14			= 0x0E,			// COM14
}eComID;

/*����λ*/
typedef enum
{
	BITS_5 = 5,				// 5λ
	BITS_6,					// 6λ
	BITS_7,					// 7λ
	BITS_8					// 8λ
}eBits;

/*��żЧ��*/
typedef enum
{
	PAR_NONE = 0,			// ��
	PAR_ODD,				// ��Ч��
	PAR_EVEN,				// żЧ��
	PAR_MARK,				// ���
	PAR_SPACE				// �ո�
}eParity;

/*ֹͣλ*/
typedef enum
{
	STOP_1 = 0,				// 1λ
	STOP_15,				// 1.5λ
	STOP_2					// 2λ
}eStopBit;

/*���͡��������ݽṹ��*/
typedef struct tagCom_Protocol_Head
{
	UINT8 nRet; 					/*���ؽ��*/
	UINT8 nCodeType;		/*�ֱ�*/
}COMRECVHEAD,*LPCOMRECVHEAD;


// CodeType���Ͷ���
enum eCodeType
{
	// 785-->MCU����
	e785CODETYPE_MTR785				= 0x00,					// Mstar785����
	e785CODETYPE_RADIO					= 0x01,					// ����������
	e785CODETYPE_BTPHONE				= 0x02,					// �����绰����
	e785CODETYPE_SOUND					= 0x03,					// ��������
	e785CODETYPE_BACKLIGHT			= 0x04,					// �������
	e785CODETYPE_WHEEL					= 0x05,					// �̿ؽ���
	e785CODETYPE_TV							= 0x06,					// ���ӽ���
	e785CODETYPE_MENU					= 0x07,					// �������˵� 
	e785CODETYPE_VER						= 0x08,					// ��ѯ����汾 
	e785CODETYPE_SKIN						= 0x09,					// ����Ƥ������ 
	e785CODETYPE_TPMS					= 0x0A,					// ̥ѹ������
	e785CODETYPE_INITSETUP			= 0x0B,					// ��ʼ�����ý���
	e785CODETYPE_TIMESETUP			= 0x0C,					// ʱ�����ý���
	e785CODETYPE_IVI						= 0x0D,					// IVI ���� 
	e785CODETYPE_NAVI						= 0x0E,					// �������� 
	e785CODETYPE_CAMRY					= 0x10,					// CAMRY ԭ����Ϣ 
	e785CODETYPE_BACKCAR				= 0x11,					// ��������
	e785CODETYPE_ZOTYE						= 0x13,					// ��̩ԭ������

	// MCU-->785����
	eMCUCODETYPE_HARDWAREKEY		= 0x80,					// ������Ϣ 
	eMCUCODETYPE_TPMS					= 0x81,					// ̥ѹ״̬���� 
	eMCUCODETYPE_RADIO					= 0x82,					// ������״̬����
	eMCUCODETYPE_BT							= 0x83,					// ����״̬���� 
	eMCUCODETYPE_OTHER					= 0x84,					// ����״̬���� 
	eMCUCODETYPE_AIRCON				= 0x85,					// ԭ���յ�������Ϣ 
	eMCUCODETYPE_CAMR					= 0x86,					// CAMR ԭ����Ϣ  
	eMCUCODETYPE_ZOTYE					= 0x87,					// ��̩ԭ����Ϣ 
};




