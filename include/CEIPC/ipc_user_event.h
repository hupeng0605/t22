

#ifndef __IPC_USER_EVENT_H__
#define __IPC_USER_EVENT_H__

#ifndef TCHAR
#	if defined(_UNICODE) || defined(UNICODE)
#		define TCHAR wchar_t
#	else
#		define TCHAR char
#	endif
#endif

#include "ceipc_event.h"

/*************************************** �¼�ID���� ***************************************/

/*---------------- IPC �¼����Ͷ��� ------------------------------------- ��Ӧ����Ľṹ�� -------------*/


// IPC�û��Զ���ϵͳ�¼���ʼID ֻ����ʶ �޾����¼�����
#define IPC_EVENT_USER_SYS_BEGIN	(IPC_EVENT_USER + 0x01)

// ����һ������IPC�¼�
#define IPC_U_SYS_START_PROCESS		(IPC_EVENT_USER_SYS_BEGIN + 0x01)	// STARTPROCESS

// �ر�һ������IPC�¼�
#define IPC_U_SYS_CLOSE_PROCESS		(IPC_EVENT_USER_SYS_BEGIN + 0x02)	// NULL

// ���ʻ��������л�
#define IPC_U_SYS_CHANGE_LANGUAGE	(IPC_EVENT_USER_SYS_BEGIN + 0x03)	// LANGUAGECHANGE

// �ı�ģʽIPC�¼�
#define IPC_U_SYS_CHANGE_PATTERN	(IPC_EVENT_USER_SYS_BEGIN + 0x04)	// PATTERNCHANGE

//SERVER֪ͨһ�����̵���̨����
#define IPC_U_WND_TOBACK			(IPC_EVENT_USER_SYS_BEGIN + 0x10)	// TOBACKPROCESS
//SERVER֪ͨһ�����̵�ǰ̨����
#define IPC_U_WND_INITPARAM			(IPC_EVENT_USER_SYS_BEGIN + 0x11)	// BACKINITPARAM
//SERVER֪ͨ���̹ر�IPC��Ϣ
#define IPC_U_WND_CLOSE_EXE			(IPC_EVENT_USER_SYS_BEGIN + 0x12)	// CLOSEEXE
//SERVER֪ͨ��������������Ϣ
#define IPC_U_PLAY_BLUETOOTH_AUDIO	(IPC_EVENT_USER_SYS_BEGIN + 0x13)	// PLAYBLUETOOTHAUDIO
// SEVRER֪ͨ����ģ��ػ�
#define	IPC_U_SERVER_POWER_OFF		(IPC_EVENT_USER_SYS_BEGIN + 0x14)		
// SERVER֪ͨ����ģ��BU OFF����Ҫ�ر�IO�Ⱥ�ʱ����
#define	IPC_U_SERVER_BU_OFF			(IPC_EVENT_USER_SYS_BEGIN + 0x15)	
//IPC��Ϣ֪ͨ��Ļ������4:3����16:9
#define	IPC_U_SYS_ASPECT_RATIO_CHANGE   (IPC_EVENT_USER_SYS_BEGIN + 0x16)
//==POWER KEY MUTE IPC��Ϣ���� add by shenjinke 2011.12.6
#define IPC_U_SYS_POWER_MUTE_CHANGE   (IPC_EVENT_USER_SYS_BEGIN + 0x17)

//SERVER֪ͨһ������˯�ߣ��磺ͨ�������� ��Ҫ����Դ��ͣ��
#define IPC_U_WND_SLEEP				(IPC_EVENT_USER_SYS_BEGIN + 0x18)
//SERVER֪ͨһ�����̿�ʼ�������磺ͨ������ ��Ҫ����Դ�ָ����ţ�
#define IPC_U_WND_WAKEUP			(IPC_EVENT_USER_SYS_BEGIN + 0x19)

// ����Э��IPC�¼�
#define IPC_U_SYS_COM_PROTOCOL		(IPC_EVENT_USER_SYS_BEGIN + 0xA0)	// BUFFERTRANS

// IPC�ڲ�ϵͳ�¼�����ID ֻ����ʶ �޾����¼�����
#define IPC_EVENT_USER_SYS_END	(0x00FF)


// ���Դ�ӡIPC�¼�
#define IPC_DEBUG_INFOR				(IPC_EVENT_USER + 0x0FFF)			// DEBUGINFOR



/*************************************** �¼������ṹ�嶨�� ***************************************/

///////////////////////// �ڲ�ϵͳ�¼��ṹ�� /////////////////////////

// �������̽ṹ��
typedef struct tagStartProcess
{
	tagStartProcess(void) { memset(this,0,sizeof(tagStartProcess)); }
	unsigned char uIPC_ID;		// ���� IPC ID
	TCHAR Argument[64];			// �������
	unsigned char bActiveShow;	// ����ý��������� �Ƿ񼤻���ʾ
	unsigned char bCloseSalf;	// ����������̳ɹ��Ƿ�رշ����ߵĽ���
}STARTPROCESS,*LPSTARTPROCESS;

// �����Խṹ��
typedef struct tagLanguageChange
{
	unsigned short uLang;			// ��������
}LANGUAGECHANGE,*LPLANGUAGECHANGE;

// ģʽ�ṹ��
typedef struct tagPatternChange
{
	tagPatternChange(void) { memset(this,0,sizeof(tagPatternChange)); }
	unsigned char uPattern;			// �л�ģʽ����
}PATTERNCHANGE,*LPPATTERNCHANGE;

// ���ݴ���ṹ��
typedef struct tagBufferTrans
{
	tagBufferTrans(void) { memset(this,0,sizeof(tagBufferTrans)); }
	unsigned long uSize;			// Ҫ����Ĵ�С
	unsigned char buff[1024];		// ���BUFF
}BUFFERTRANS,*LPBUFFERTRANS;

// ���Դ�ӡ�ṹ��
typedef struct tagDebugInfor
{
	tagDebugInfor(void) { memset(this,0,sizeof(tagDebugInfor)); }
	TCHAR strInfor[2048];
}DEBUGINFOR,*LPDEBUGINFOR;


typedef struct tagKeyMsg
{
	WORD event;
	BYTE index;
	BYTE vary;
/*
 * FT_KEY_BTN_DOWN = 0x10,		��ť���£��仯ʱ���ͣ�	[BYTE] ������ţ�0~15
 * FT_KEY_BTN_UP = 0x11,		��ť�ͷţ��仯ʱ���ͣ�	[BYTE] ������ţ�0~15
 * FT_KEY_SPIN_DOWN = 0x12,		��ť��ת	[BYTE] ��ť��ţ�0~1
 * FT_KEY_SPIN_UP = 0x13		��ť��ת	[BYTE] ��ť��ţ�0~1
 */
} KEYMSG, *LPKEYMSG;

//server��ʾ���Ӳ㹲���ڴ�ͷ�Ľṹ
typedef struct _tagShowOverlay
{
	int dst_x;
	int dst_y;
	int copy_width;
	int copy_height;
	int src_width_byte;
	int src_height;
	BOOL bUseColorKey;
	DWORD dwColorKey;
}ShowOverlay;
#endif	/*__IPC_USER_EVENT_H__*/