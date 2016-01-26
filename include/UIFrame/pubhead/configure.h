#ifndef _CONFIGURE_H__
#define _CONFIGURE_H__

#include "Platform.h"

//����汾�����Ϣ��ֻ�ܿ�һ��
#define EU_VERSION //ŷ�ް�
//#define UK_VERSION// Ӣ����
//#define US_VERSION //������
//#define JP_VERSION	//�ձ���
#define  CH_VERSION
#define JP_VERSION


// ����DEBUG��_DEBUG��
#if defined(ENGINE_EVC) && defined(DEBUG) && !defined(_DEBUG)
#define _DEBUG
#endif
#if defined(ENGINE_VC) && defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif

// ��ʾ������
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   480

#define SCREEN_COLORBIT16	`	// 16λɫ����
//#define SCREEN_COLORBIT24		// 24λɫ����

// �����ַ�����������С
#define BUF_SIZE 256

#ifndef KN_LIB
#ifdef DLL_EXPORTS
#define CYPRESS_DLL_API __declspec(dllexport)
#else
#define CYPRESS_DLL_API __declspec(dllimport)
#endif
#else
#define CYPRESS_DLL_API
#endif
/************************************************************************/
/* �����ļ�·������																												*/
/************************************************************************/
// �����ļ�·��
#define LANGUAGE_CHN _T("HMI\\Language\\chinese_ch.ini") // ���ļ���·��
#define LANGUAGE_TRA _T("HMI\\Language\\tradition_ch.ini") // ���ķ���·��
#ifdef	JP_VERSION
#define LANGUAGE_ENG _T("HMI\\Language\\english_jp.ini") // Ӣ��·��
#else
#define LANGUAGE_ENG _T("HMI\\Language\\english_ch.ini") // Ӣ��·��
#endif
#define LANGUAGE_JAP _T("HMI\\Language\\japanese_jp.ini")	//����·��


/************************************************************************/
/* ��Դ�ļ�·������																												*/
/************************************************************************/
#define RES_DIR _T("HMI\\")   // ��Դ�ļ�Ŀ¼
#define DATA_DIR _T("Data\\")// �����ļ�Ŀ¼
#define CONFIG_DIR _T("Config\\")// �����ļ�Ŀ¼
#define BACKGRND_MAIN_NAME	(_T("Main\\BnkFromUsb.ktc"))

#if 0
#ifndef WINCE
#define USER_DATA_PATH		(_T("D:\\Dev\\Cypress\\CypressDB\\03IMPLEMENT\\0301Code\\Cypress\\Bin\\win32\\"))	// �û��ļ�·��
#else
#define USER_DATA_PATH		(_T("\\NandFlash\\"))	// �û��ļ�·��
#endif
#endif



/************************************************************************/
/* Ӧ�ó���Ĵ��ڱ������������																							*/
/************************************************************************/
#define APP_CLASSNAME_MAIN _T("Main")
#define APP_TITLE_MAIN _T("Main")

#define APP_CLASSNAME_RADIO _T("Radio")
#define APP_TITLE_RADIO _T("Radio")

#define APP_CLASSNAME_MUSIC _T("Music")
#define APP_TITLE_MUSIC _T("Music")

#define APP_CLASSNAME_SIRIUS _T("Sirius")
#define APP_TITLE_SIRIUS _T("Sirius")

#define APP_CLASSNAME_IPOD _T("iPod")
#define APP_TITLE_IPOD _T("iPod")

#define APP_CLASSNAME_AUX _T("AuxIn")
#define APP_TITLE_AUX _T("AuxIn")

//#define APP_CLASSNAME_INFOBAR _T("InfoBar")
#define APP_TITLE_INFOBAR _T("SP_InfoBar")
//#define APP_CLASSNAME_BRIGHTBAR _T("SP_Brightness")
#define APP_TITLE_BRIGHTNESS _T("SP_Brightness")
//#define APP_CLASSNAME_BRIGHTBAR _T("SP_Brightness")
#define APP_TITLE_ANGEL _T("SP_Angle")
//#define APP_CLASSNAME_BRIGHTBAR _T("SP_Brightness")
#define APP_TITLE_TURNINFO _T("SP_TurnInfoBar")
#define APP_CLASSNAME_VOLUMEBAR _T("InfoBar")	// volume bar
#define APP_TITLE_VOLUMEBARBAR _T("InfoBar")

#define APP_CLASSNAME_BLUETOOTH _T("Bluetooth")
#define APP_TITLE_BLUETOOTH _T("Bluetooth")

#define APP_CLASSNAME_INTERNET _T("Internet")
#define APP_TITLE_INTERNET _T("Internet")

#define APP_CLASSNAME_PICTURE _T("Picture")
#define APP_TITLE_PICTURE _T("Picture")

#define APP_CLASSNAME_VIDEO _T("Video")
#define APP_TITLE_VIDEO _T("Video")

#define APP_CLASSNAME_CLOCK _T("Clock")
#define APP_TITLE_CLOCK _T("Clock")

#define APP_CLASSNAME_EQ _T("EQ")
#define APP_TITLE_EQ _T("EQ")

#define APP_CLASSNAME_NAVI _T("NaviSystem")
#define APP_TITLE_NAVI _T("NaviSystem")

#define APP_CLASSNAME_COM   _T("Com")

#define APP_TITLENAME_SEVER     (_T("Server"))
#define APP_CLASSNAME_SERVER    (_T("Server"))

#define APP_TITLENAME_DISC     (_T("Disc"))
#define APP_CLASSNAME_DISC    (_T("Disc"))

#define APP_CLASSNAME_MONITOR	(_T("Monitor"))
#define APP_TITLE_MONITOR	(_T("Monitor"))

#define APP_CLASSNAME_ANTITHEFT (_T("AntiTheft"))
#define APP_TITLE_ANTITHEFT		(_T("AntiTheft"))

/************************************************************************/
/* �����ڴ��ֶζ���                                                     */
/************************************************************************/
#define MEMMAP_STRING_RADIO					(_T("Global\\MEM_STRING_RADIO"))
#define MEMMAP_STRING_DISCAUDIO				(_T("Global\\MEM_STRING_DISCAUDIO"))
#define MEMMAP_STRING_IPODAUDIO				(_T("Global\\MEM_STRING_IPODAUDIO"))
#define MEMMAP_STRING_SIRIUS				(_T("Global\\MEM_STRING_SIRIUS"))
#define MEMMAP_STRING_USBAUDIO				(_T("Global\\MEM_STRING_USBAUDIO"))
#define MEMMAP_STRING_BTAUDIO				(_T("Global\\MEM_STRING_BTAUDIO"))
#define MEMMAP_STRING_DISCVIDEO_FRONT		(_T("Global\\MEM_STRING_DISCVIDEO_FRONT"))
#define MEMMAP_STRING_IPODVIDEO_FRONT		(_T("Global\\MEM_STRING_IPODVIDEO_FRONT"))
#define MEMMAP_STRING_USBVIDEO				(_T("Global\\MEM_STRING_DISCVIDEO"))
#define MEMMAP_STRING_AUX1_FRONT			(_T("Global\\MEM_STRING_AUX1_FRONT"))
#define MEMMAP_STRING_AUX2_FRONT			(_T("Global\\MEM_STRING_AUX2_FRONT"))
#define MEMMAP_STRING_DVBT					(_T("Global\\MEM_STRING_DVBT"))
#define MEMMAP_STRING_NAVI					(_T("Global\\MEM_STRING_NAVI"))
#define MEMMAP_STRING_TEL					(_T("Global\\MEM_STRING_TEL"))
#define MEMMAP_STRING_CAMERA				(_T("Global\\MEM_STRING_CAMERA"))

#define MEMMAP_STRING_DISCVIDEO_REAR		(_T("Global\\MEM_STRING_DISCVIDEO_REAR"))
#define MEMMAP_STRING_IPODVIDEO_REAR		(_T("Global\\MEM_STRING_IPODVIDEO_REAR"))
#define MEMMAP_STRING_AUX1_REAR				(_T("Global\\MEM_STRING_AUX1_REAR"))
#define MEMMAP_STRING_AUX2_REAR				(_T("Global\\MEM_STRING_AUX2_REAR"))
#define MEMMAP_STRING_ZONEOFF				(_T("Global\\MEM_STRING_ZONEOFF"))

//#define MEMMAP_INT_RADIO				(0)
//#define MEMMAP_INT_DISCAUDIO			(1)
//#define MEMMAP_INT_IPODAUDIO			(2)
//#define MEMMAP_INT_SIRIUS				(3)
//#define MEMMAP_INT_USBAUDIO				(4)
//#define MEMMAP_INT_BTAUDIO				(5)
//#define MEMMAP_INT_DISCVIDEO_FRONT		(6)
//#define MEMMAP_INT_IPODVIDEO_FRONT		(7)
//#define MEMMAP_INT_USBVIDEO				(8)
//#define MEMMAP_INT_AUX1_FRONT			(9)
//#define MEMMAP_INT_AUX2_FRONT			(10)
//#define MEMMAP_INT_DVBT					(11)
//#define MEMMAP_INT_NAVI					(12)
//#define MEMMAP_INT_TEL					(13)
//#define MEMMAP_INT_CAMERA				(14)
//			   
//#define MEMMAP_INT_DISCVIDEO_REAR		(15)
//#define MEMMAP_INT_IPODVIDEO_REAR		(16)
//#define MEMMAP_INT_AUX1_REAR			(17)
//#define MEMMAP_INT_AUX2_REAR			(18)
//#define MEMMAP_INT_ZONEOFF				(19)

/************************************************************************/
/* ����Դ��������������																										*/
/************************************************************************/
// Դ��,����������������������
//#define SOURCE_NAME_NULL    _T(" ")
//#define SOURCE_NAME_HDD     _T("HDD")
//#define SOURCE_NAME_USB     _T("USB")
//#define SOURCE_NAME_SD      _T("SD")
//#define SOURCE_NAME_IPOD    _T("IPOD")
//#define SOURCE_NAME_DVD     _T("DVD")
//#define SOURCE_NAME_SETUP   _T("SETUP")
//#define SOURCE_NAME_DES     _T("DES")
// ��Ƶ����Ƶ���ݲ�ͬ��Դ����������
#define SOURCE_PARAM_NULL   (0)
#define SOURCE_PARAM_HDD    (1)
#define SOURCE_PARAM_USB    (2)
#define SOURCE_PARAM_SD     (3)
#define SOURCE_PARAM_IPOD   (4)
#define SOURCE_PARAM_DVD    (5)
#define SOURCE_PARAM_SETUP  (6)
#define SOURCE_PARAM_DES    (7)
#define SOURCE_PARAM_TEL_IN (8)
#define SOURCE_PARAM_AV1	(9)
#define SOURCE_PARAM_AV2	(10)
#define SOURCE_PARAM_TV		(11)
#define SOURCE_PARAM_CAMERA	(12)
#define SOURCE_PARAM_CD     (13)
#define SOURCE_PARAM_HIDE   (14)


// Դ·��,ͨ��KCDeviceName�����������ļ���ȡ
//#define SOURCE_PATH_HDD       _T("\HDD")
//#define SOURCE_PATH_USB       _T("\USB")
//#define SOURCE_PATH_SD        _T("\SD")
//#define SOURCE_PATH_IPOD  _T("\IPOD")

/************************************************************************/
/* exe�ͷ�����ͨ����Ϣ����																									*/
/************************************************************************/
// Ӧ�ó���������������������Ϣ
#define WM_TO_SEVER_BASE            (WM_USER+100)
#define WM_CHANEGLANG_REQ           (WM_TO_SEVER_BASE+1)
#define WM_CHANGEBKGRND_REQ         (WM_TO_SEVER_BASE+2)
#define WM_CHANGETIME_REQ           (WM_TO_SEVER_BASE+3)
#define WM_TRANSAFFECT_REQ          (WM_TO_SEVER_BASE+4)
//#define WM_STARTEXE_REQ               (WM_COPYDATA)           // ��ΪҪ�����ַ�������
#define WM_STARTEXE_REQ             (WM_TO_SEVER_BASE+5)
#define WM_CHANGETIMEFORMAT_REQ     (WM_TO_SEVER_BASE+6)
#define WM_CHANGECLOCKTYPE_REQ      (WM_TO_SEVER_BASE+7)
#define WM_CHANGEDATE_REQ           (WM_TO_SEVER_BASE+8)
#define WM_ACTIVESYNC_REQ           (WM_TO_SEVER_BASE+9)
#define WM_CLOSEEXE_REQ             (WM_TO_SEVER_BASE+10)       // Ӧ�ó���֪ͨ�������Լ��Ѿ��˳���
#define WM_DEBUG_MSG_REQ            (WM_COPYDATA)
#define WM_BACKEXE_REQ				(WM_TO_SEVER_BASE+11)		// Ӧ�ó����л�����̨
// Ӧ�ó�������Ӳ��beep��
#define WM_BEEP_ON_REQ				(WM_TO_SEVER_BASE+12)// Ӳ��Beep��
//#define WM_EXE_TO_FRONT_REQ         (WM_TO_SEVER_BASE+13)

#define WM_BRIGHT_UPDATE_VAL_REQ	(WM_TO_SEVER_BASE+15)

#define WM_POWEROFF_OVER_REQ		(WM_TO_SEVER_BASE+16)
#define WM_FRONT_REAR_CHANGE_REQ	(WM_TO_SEVER_BASE+17)

#define WM_ISLOADFACTROY_REQ		(WM_TO_SEVER_BASE+18) // setting ���͸�sever��
#define WM_ISLOADFACTROY_OK_REQ     (WM_TO_SEVER_BASE+19)// Ӧ�ó����͸�server��
#define WM_DISCERROR_REQ            (WM_TO_SEVER_BASE+20)
#define WM_DISC_TYPE_REQ			(WM_TO_SEVER_BASE+21)	// �Զ������ʱ���ȡ��ý�����ͣ��ı�main�ĵ�ǰԴ

#define WM_CLOSE_VOL_BAR_REQ		(WM_TO_SEVER_BASE+22)	// ����ر�volume bar��Ϣ

#define WM_CLOSE_INFOBAR_REQ		(WM_TO_SEVER_BASE+23)	// info bar��ʾ��������������������info bar
#define WM_STANDBY_REQ				(WM_TO_SEVER_BASE+24)	// ��������
#define WM_TA_CANCEL_REQ			(WM_TO_SEVER_BASE+25)	// TA cancel����
#define WM_RETURN_CUR_SRC_REQ		(WM_TO_SEVER_BASE+26)	// ���ص���ǰԴ
#define WM_SHOW_MAIN_REQ			(WM_TO_SEVER_BASE+27)	// ��ʾmain menu
#define WM_SETUP_STATUS_REQ			(WM_TO_SEVER_BASE+28)	// �Ƿ���set up����
#define WM_SRC_BTN_STATUS_REQ		(WM_TO_SEVER_BASE+29)	// �����������ϵ�sirius��ť״̬
#define WM_PLAYER_STATUS_REQ		(WM_TO_SEVER_BASE+30)	// ���²�����״̬
#define WM_ANTITHIEF_STS_REQ		(WM_TO_SEVER_BASE+31)	// ֪ͨ��������״̬


// ��Ϣ��sub type
// ����exe����
#define SUB_TYPE_EXE_SEVER      (0)
#define SUB_TYPE_EXE_BT         (1)// ��������
#define SUB_TYPE_EXE_CLOCK      (2)// ʱ�ӳ���
#define SUB_TYPE_EXE_EQ         (3)// EQ���ó���
#define SUB_TYPE_EXE_INTERNET   (4)// �������
#define SUB_TYPE_EXE_MAIN       (5)// ���˵�
#define SUB_TYPE_EXE_MUSIC      (6)// ���ֲ��ų���
#define SUB_TYPE_EXE_PICTURE    (7)// ͼƬ�������
#define SUB_TYPE_EXE_RADIO      (8)// ����������
#define SUB_TYPE_EXE_VIDEO      (9)// ��Ƶ���ų���
#define SUB_TYPE_EXE_NAVI       (10)// ��������
#define SUB_TYPE_EXE_SIRIUS     (11)// ��������������
#define SUB_TYPE_EXE_IPOD       (12)// iPod���ų���
#define SUB_TYPE_EXE_AUX		(13)// Aux����
#define SUB_TYPE_EXE_INFOBAR	(14) // infobar
#define SUB_TYPE_EXE_DISC		(15) // DISC
#define SUB_TYPE_EXE_ZONEOFF    (16) // �رպ�̨
#define SUB_TYPE_EXE_BRIGHTNESS	(17)	// ���ȵ��ںͷ������
#define SUB_TYPE_EXE_ANGEL		(18)
#define SUB_TYPE_EXE_TURNINFO	(19)
#define SUB_TYPE_EXE_VOLUMEBAR	(20)
#define SUB_TYPE_EXE_MONITOR	(21)	// ��Ļ��������
#define SUB_TYPE_EXE_ANTITHIEF	(22)	// �����������


// ͬ��
#define SUB_TYPE_SYNC_START     (1)
#define SUB_TYPE_SYNC_END       (2)


// ���������ظ�Ӧ�ó������Ϣ
#define WM_FROM_SEVER_BASE      (WM_USER+500)
#define WM_CHANGELANG           (WM_FROM_SEVER_BASE+1)
#define WM_CHANGEBKGRND         (WM_FROM_SEVER_BASE+2)
#define WM_CHANGETIME           (WM_FROM_SEVER_BASE+3)
#define WM_TRANSAFFECT          (WM_FROM_SEVER_BASE+4)
#define WM_STARTEXE             (WM_FROM_SEVER_BASE+5)
#define WM_CHANGETIMEFORMAT     (WM_FROM_SEVER_BASE+6)
#define WM_CHANGECLOCKTYPE      (WM_FROM_SEVER_BASE+7)
#define WM_CHANGEDATE           (WM_FROM_SEVER_BASE+8)
#define WM_INIT_BY_PARAM        (WM_FROM_SEVER_BASE+9)

#define WM_CLOSE_VIDEO          (WM_FROM_SEVER_BASE+10)	// �ر���Ƶ����
#define WM_SHOW_VIDEO           (WM_FROM_SEVER_BASE+11)	// ��ʾ��Ƶ����

#define WM_CLOSE_EXE            (WM_FROM_SEVER_BASE+12)	// �رճ���
#define WM_MAIN_UPDATEMEM		(WM_FROM_SEVER_BASE+13)	// Main���³��������ͼ,����ʹ�ø�����Ŀ
#define WM_UPDATE_CUR_SOURCE	(WM_FROM_SEVER_BASE+14)	// main ���µ�ǰԴ
#define WM_MAIN_SOURCEBTN_STS	(WM_FROM_SEVER_BASE+15) // main ����Դ��ť��״̬
#define WM_SHOW_FRONT_REAR_BTN	(WM_FROM_SEVER_BASE+16) // ���ñ�������front��rear��ť��״̬
#define WM_MAIN_EFFECT			(WM_FROM_SEVER_BASE+17) // ֪ͨmain������

#define WM_LOADFACTROY          (WM_FROM_SEVER_BASE+18)
#define WM_RESTAR               (WM_FROM_SEVER_BASE+19) 

#define WM_CLOSE_VOL_BAR		(WM_FROM_SEVER_BASE+20) // �ر�volume bar��Ϣ
#define WM_CHANGE_USB_VOLUME	(WM_FROM_SEVER_BASE+21) // ����USB������
#define WM_NOTIFY_MAIN_BACKGRND	(WM_FROM_SEVER_BASE+22)	// ֪ͨmain menu����̨��
#define WM_DISCONNECTA2DP		(WM_FROM_SEVER_BASE+23)	// ֪ͨ�����ж�A2DP
#define WM_DISCONNECT_DISC		(WM_FROM_SEVER_BASE+24) // ����Ͽ�disc����
#define WM_SHOW_DATE			(WM_FROM_SEVER_BASE+25)
#define WM_UPDATE_CAMERA_STS	(WM_FROM_SEVER_BASE+26) // ���µ���״̬
#define WM_PLAYER_STATUS		(WM_FROM_SEVER_BASE+27) // ���²�����״̬
#define WM_ANTITHIEF_PASSWORD	(WM_FROM_SEVER_BASE+28) // ����������Ϣ



/************************************************************************/
/* ��������OSͨ����Ϣ����																									*/
/************************************************************************/
// ���������ܵ���OS����Ϣ,��Ҫ���ݿͻ�����Ϣ��������Ӧ�ó�����Ҫ����
#define WM_OS_MSG_BASE_RECEIVE              (WM_USER+5000)
#define WM_OS_MSG_DEVICE_RECEIVE			(WM_OS_MSG_BASE_RECEIVE+7)// �豸������Ϣ

// ���������ܵ�OS����Ϣ��ת����Ӧ�ó������Ϣ��Ӧ�ó���Ҫ����
#define WM_OS_MSG_BASE              (WM_USER+1000)
#define WM_OS_MSG_DEVICE			(WM_OS_MSG_BASE+7)// �豸������Ϣ

#define OS_MSG_DEVICE_WPARAM_USB	(1)
#define OS_MSG_DEVICE_WPARAM_SD		(2)
#define OS_MSG_DEVICE_WPARAM_IPOD	(3)
#define OS_MSG_DEVICE_LPARAM_IN		(1)
#define OS_MSG_DEVICE_LPARAM_OUT	(0)


/************************************************************************/
/* ��������Ӳ��ťͨ�ŵ���Ϣ����																							*/
/************************************************************************/
// ���������ܵ���Ӳ��ť����Ϣ��Ӧ�ó�����Ҫ����
#define WM_HARD_MSG_BASE_RECEIVE            (WM_USER+5500)
//#define WM_HARD_MSG_START_RECEIVE           (WM_HARD_MSG_BASE_RECEIVE+1)    // ���ػ�       ���ػ���ť
//#define WM_HARD_MSG_FMAM_RECEIVE            (WM_HARD_MSG_BASE_RECEIVE+2)    // FM/AM        FM/AM�����л�
//#define WM_HARD_MSG_DVD_RECEIVE             (WM_HARD_MSG_BASE_RECEIVE+3)    // DVD          ����DVD�����ݰ�ť
//#define WM_HARD_MSG_SRC_RECEIVE             (WM_HARD_MSG_BASE_RECEIVE+4)    // SRC          Դ�л�
//#define WM_HARD_MSG_NAV_RECEIVE             (WM_HARD_MSG_BASE_RECEIVE+5)    // NAV          ���뵼�������ݰ�ť
//#define WM_HARD_MSG_PREV_RECEIVE            (WM_HARD_MSG_BASE_RECEIVE+6)    // |<<          ��������IPOD����Ϊ��һ���������������ǰ�Ƶ�ʼ�С��������
//#define WM_HARD_MSG_NEXT_RECEIVE            (WM_HARD_MSG_BASE_RECEIVE+7)    // >>|          ��������IPOD����Ϊ��һ���������������ǰ�Ƶ�����ӷ�������
//#define WM_HARD_MSG_BT_RECEIVE              (WM_HARD_MSG_BASE_RECEIVE+8)    // BT           �������������ݰ�ť
//#define WM_HARD_MSG_EQ_RECEIVE              (WM_HARD_MSG_BASE_RECEIVE+9)    // EQ           ����EQ�����ݰ�ť
//#define WM_HARD_MSG_SETUP_RECEIVE           (WM_HARD_MSG_BASE_RECEIVE+10)   // Setup        �������ý����ݰ�ť
//#define WM_HARD_MSG_TTS_RECEIVE             (WM_HARD_MSG_BASE_RECEIVE+11)   // ��������     �������Ű�ť
//#define WM_HARD_MSG_REPEAT_RECEIVE          (WM_HARD_MSG_BASE_RECEIVE+12)   // Repeat       �����ظ���ť
//#define WM_HARD_MSG_MENU_RECEIVE            (WM_HARD_MSG_BASE_RECEIVE+13)   // MENU         �������˵���ť
//#define WM_HARD_MSG_MUTE_RECEIVE            (WM_HARD_MSG_BASE_RECEIVE+14)   // MUTE         ������ť
//#define WM_HARD_MSG_ASPS_RECEIVE            (WM_HARD_MSG_BASE_RECEIVE+15)   // AS/PS        �Զ��洢�ͽ�Ŀ����
//#define WM_HARD_MSG_DES_RECEIVE             (WM_HARD_MSG_BASE_RECEIVE+16)   // DES          ��ͼ����Ŀ�ĵؿ�ݰ�ť
//#define WM_HARD_MSG_VOL_RECEIVE             (WM_HARD_MSG_BASE_RECEIVE+17)   // VOL          ������ť
//#define WM_HARD_MSG_SMARTDIAL_RECEIVE       (WM_HARD_MSG_BASE_RECEIVE+18)   // SMART DIAL   �ƶ�������ť
//#define WM_HARD_MSG_DIRECTION_RECEIVE		(WM_HARD_MSG_BASE_RECEIVE+19)
//#define WM_HARD_MSG_LIGHT_RECEIVE			(WM_HARD_MSG_BASE_RECEIVE+20)
//#define WM_HARD_MSG_TENKEY_RECEIVE			(WM_HARD_MSG_BASE_RECEIVE+21)
//#define WM_HADR_KEY_MSG_RECEIVE				(WM_HARD_MSG_BASE_RECEIVE+22)	// ң��������尴ť


// ���������ܵ�Ӳ��ť����Ϣ��ת����Ӧ�ó������Ϣ��Ӧ�ó���Ҫ����
#define WM_HARD_MSG_BASE            (WM_USER+1500)
#define WM_HARD_MSG_START           (WM_HARD_MSG_BASE+1)    // ���ػ�       ���ػ���ť
//#define WM_HARD_MSG_FMAM            (WM_HARD_MSG_BASE+2)    // FM/AM        FM/AM�����л�
//#define WM_HARD_MSG_DVD             (WM_HARD_MSG_BASE+3)    // DVD          ����DVD�����ݰ�ť
//#define WM_HARD_MSG_SRC             (WM_HARD_MSG_BASE+4)    // SRC          Դ�л�
//#define WM_HARD_MSG_NAV             (WM_HARD_MSG_BASE+5)    // NAV          ���뵼�������ݰ�ť
//#define WM_HARD_MSG_PREV            (WM_HARD_MSG_BASE+6)    // |<<          ��������IPOD����Ϊ��һ���������������ǰ�Ƶ�ʼ�С��������
//#define WM_HARD_MSG_NEXT            (WM_HARD_MSG_BASE+7)    // >>|          ��������IPOD����Ϊ��һ���������������ǰ�Ƶ�����ӷ�������
//#define WM_HARD_MSG_BT              (WM_HARD_MSG_BASE+8)    // BT           �������������ݰ�ť
//#define WM_HARD_MSG_EQ              (WM_HARD_MSG_BASE+9)    // EQ           ����EQ�����ݰ�ť
//#define WM_HARD_MSG_SETUP           (WM_HARD_MSG_BASE+10)   // Setup        �������ý����ݰ�ť
//#define WM_HARD_MSG_TTS             (WM_HARD_MSG_BASE+11)   // ��������     �������Ű�ť
//#define WM_HARD_MSG_REPEAT          (WM_HARD_MSG_BASE+12)   // Repeat       �����ظ���ť
//#define WM_HARD_MSG_MENU            (WM_HARD_MSG_BASE+13)   // MENU         �������˵���ť
//#define WM_HARD_MSG_MUTE            (WM_HARD_MSG_BASE+14)   // MUTE         ������ť
//#define WM_HARD_MSG_ASPS            (WM_HARD_MSG_BASE+15)   // AS/PS        �Զ��洢�ͽ�Ŀ����
//#define WM_HARD_MSG_DES             (WM_HARD_MSG_BASE+16)   // DES          ��ͼ����Ŀ�ĵؿ�ݰ�ť
#define WM_HARD_MSG_VOL             (WM_HARD_MSG_BASE+17)   // VOL          ������ť
#define WM_HARD_MSG_SMARTDIAL       (WM_HARD_MSG_BASE+18)   // SMART DIAL   �ƶ�������ť
#define WM_HARD_MSG_DIRECTION		(WM_HARD_MSG_BASE+19)
#define WM_HARD_MSG_LIGHT			(WM_HARD_MSG_BASE+20)	// ���ȵ���
#define WM_HARD_MSG_TENKEY			(WM_HARD_MSG_BASE+21)
#define WM_HARD_MSG_ANGLE			(WM_HARD_MSG_BASE+22)

#define WM_HADR_KEY_MSG				(WM_HARD_MSG_BASE+22)	// ң��������尴ť
#define WM_HARD_KEY_EJECT			(WM_HARD_MSG_BASE+23)	// ����

// ���Ӱ��������ϵİ�ť��ͨ�绰����Ϣ
#define WM_HARD_MSG_SEND				(WM_HARD_MSG_BASE+24)// SEND
#define WM_HARD_MSG_END					(WM_HARD_MSG_BASE+25)// END
#define WM_HARD_MSG_SENDEND				(WM_HARD_MSG_BASE+26)// SEND END


typedef enum
{
	KEY_MUTE        = 0x01,     //MUTE
	KEY_PLAY        = 0x02,     //PLAY/PAISE
	KEY_NEXT        = 0x03,		//��һ��>>|
	KEY_PREVIOUS    = 0x04,		//��һ��|<<
	KEY_EJECT       = 0x05,        //����
	KEY_SOURCE      = 0x06,     //SRC ��
	KEY_SET	        = 0x0c,		// ����set up
	KEY_BAND        = 0x0d,		// band�л�
	KEY_UP 		    = 0x12,		// ���Ϸ����
	KEY_DOWN 	    = 0x13,		// ���·����
	KEY_LEFT 	    = 0x14,		// �������
	KEY_RIGHT 		= 0x15,		// ���ҷ����
	KEY_0           = 0x17,     //���ּ�
	KEY_1           = 0x18,
	KEY_2           = 0x19,
	KEY_3           = 0x1a,
	KEY_4           = 0x1b,
	KEY_5           = 0x1c,
	KEY_6           = 0x1d,
	KEY_7           = 0x1e,
	KEY_8           = 0x1f,
	KEY_9           = 0x20,
	KEY_MENU        = 0x23,		// menu
	KEY_STOPBAND	= 0x24,		// play pause long press
	KEY_ANGLE   	= 0x26,		// changel dvd angle
	KEY_TILT		= 0x8b,	// ������Ļ����б��
	KEY_TITLE       = 0x27,
	KEY_AUDIO       = 0x28,
	KEY_SUBTITLE 	= 0x29,
	KEY_ROOT        = 0x2a,
	KEY_ZOOM        = 0x2b,
	KEY_FAST_REW 	= 0x2c,		//����
	KEY_FAST_FF 	= 0x2d,		//���
	KEY_POWER_OFF 	= 0x35,		//�ػ�
	KEY_ENTER 		= 0x36,  
	KEY_SEARCH      = 0x37,
	KEY_NEXT_PLUS	= 0x39,
	KEY_PREV_PLUS	= 0x3a,
	KEY_BACK 		= 0x52,
	KEY_TAG			= 0x66,
	KEY_ISR_LONG    = 0x6a,
	KEY_PIC         = 0x89 ,  
	KEY_REPEAT      = 0x30,
	KEY_AF          = 0xa9,
	KEY_SHUFFLE     = 0x2F,//0xd4,
	KEY_PRT_LONG    = 0xbd,
	KEY_RDM			= 0xFF, // key_shuffle,
	KEY_SEND		= 0x5E,
	KEY_END			= 0x5F,
	KEY_SEND_END	= 0x6D ,
	KEY_SMART_CW 	= 0x39,		//˳ʱ����ת
	KEY_SMART_CCW 	= 0x3a,	    //��ʱ����ת
	KEY_SMART_CLICK = 0x3b,	    //����
	KEY_SMART_HOLD 	= 0x3c,	    //����
	KEY_TEL			= 0x41,		//TEL
	KEY_STAR   ,
	KEY_WELL,
	KEY_DEL,
	KEY_CALL,
	KEY_HANGUP,
	KEY_CANCEL,
	KEY_PLAUS
}LPARAM_KEYCODE;


/************************************************************************/
/* ͻ���¼�����																														*/
/************************************************************************/
// ���������ܵ��Ľ����¼�����Ϣ��Ӧ�ó�����Ҫ����
#define WM_URGENT_MSG_BASE_RECEIVE				(WM_USER+6000)
#define WM_URGENT_MSG_TEL_IN_RECEIVE			(WM_URGENT_MSG_BASE_RECEIVE+1)
#define WM_URGENT_MSG_DISCLOADING_RECEIVE		(WM_URGENT_MSG_BASE_RECEIVE+2)
#define WM_URGENT_MSG_DISCLOADFINISH_RECEIVE	(WM_URGENT_MSG_BASE_RECEIVE+3)


// ���������ܵ������¼�����Ϣ��ת����Ӧ�ó������Ϣ��Ӧ�ó���Ҫ����
#define WM_URGENT_MSG_BASE                  (WM_USER+2000)
#define WM_URGENT_MSG_TEL_IN                (WM_URGENT_MSG_BASE+1)  // �յ�������Ϣ
#define WM_URGENT_MSG_DISCLOADING			(WM_URGENT_MSG_BASE+2)
#define WM_URGENT_MSG_DISCLOADFINISH		(WM_URGENT_MSG_BASE+3)
#define WM_URGENT_MSG_TEL_OFF               (WM_URGENT_MSG_BASE+4)  // �յ��Ҷ���Ϣ


#define WM_MESSAGE_UART						(WM_USER +121) 
#define WM_MESSAGE_GETDLLCOMMAND			(WM_USER+133)

/************************************************************************/
/* Rearͨ���¼�����																														*/
/************************************************************************/
#define WM_MESSAGE_REAR_BASE				(WM_USER+6500)
#define WM_MESSAGE_REAR_OPEN				(WM_MESSAGE_REAR_BASE+1)
#define WM_MESSAGE_REAR_CLOSE				(WM_MESSAGE_REAR_BASE+2)


#define WM_PROCESS_BASE						(WM_USER+7000)
#define WM_BTMSG_PAIR						(WM_PROCESS_BASE+1)	// ���������Ϣ
#define WM_IPODMSG							(WM_PROCESS_BASE+2)	// ipod��Ϣ
#define WM_BTMSG_READPB						(WM_PROCESS_BASE+3)	// ���绰��
#define WM_BTMSG_READPN						(WM_PROCESS_BASE+4)	// ���绰����
#define WM_BTMSG_DEVICEINFO					(WM_PROCESS_BASE+5)	// device info
#define WM_BTMSG_CONNECTSUCCESS				(WM_PROCESS_BASE+6) // ���ӳɹ�
#define WM_BTMSG_DISCONNECTSUCCESS			(WM_PROCESS_BASE+7)	// �Ͽ��ɹ�
#define WM_BTMSG_DIALSTATE					(WM_PROCESS_BASE+8)	// ͨ��״̬
#define WM_BTMSG_UPDATEID3					(WM_PROCESS_BASE+9)	// ����ID3
#define WM_BTMSG_INQUIRYADD					(WM_PROCESS_BASE+10)// �����豸
#define WM_BTMSG_CLOSEWND					(WM_PROCESS_BASE+11)// �رմ���
#define WM_DISCMSG							(WM_PROCESS_BASE+12)// Disc��Ϣ
#define WM_BTMSG_MULTICALL					(WM_PROCESS_BASE+13)// ͨ����
#define	WM_BTMSG_MODULEINFO					(WM_PROCESS_BASE+14)// ����ģ����Ϣ
#define WM_BTMSG_CHANGEPB					(WM_PROCESS_BASE+15)// ���µ绰��
#define WM_BTMSG_UPDATEWND					(WM_PROCESS_BASE+16)// �������½���
#define WM_BTMSG_PLAYSTATUS					(WM_PROCESS_BASE+17)// ���²���״̬
#define WM_RADIO_UPDATE_FREQ				(WM_PROCESS_BASE+18) //����������Ƶ��
#define WM_BTMSG_SEARCHPHONEBOOK			(WM_PROCESS_BASE+19)// ���ٶ�λ�绰��




#define WM_HDRADIO_EVENT					(WM_PROCESS_BASE+20)// HD radio�ĸ���UI��Ϣ
#define WM_MESSAGE_AntiTheft				(WM_PROCESS_BASE+21)


/************************************************************************/
/* Ӳ��״̬֪ͨ�¼�����																														*/
/************************************************************************/
#define WM_HARDWARE_SYS_BASE						(WM_USER+7500)
#define	WM_HARDWARE_SYS_INFO						(WM_HARDWARE_SYS_BASE+1)
#define WM_HARDWARE_NAVI_INFO						(WM_HARDWARE_SYS_BASE+2)
#define WM_NAVI_INFO_BTN_DOWN_REQ					(WM_HARDWARE_SYS_BASE+3)

#define WM_VIDEO_IN_MSG								(WM_HARDWARE_SYS_BASE+4)
#define VIDEOIN_DVBT		(1)
#define VIDEOIN_CAMERA		(2)
#define VIDEOIN_AUX1		(3)
#define VIDEOIN_AUX2		(4)

#define WM_PARKING_MSG								(WM_HARDWARE_SYS_BASE+5)
#define WM_TA_CANCEL_STS							(WM_HARDWARE_SYS_BASE+6)

#define WM_UPDATE_PTY_LANG				(WM_USER+7900)

/************************************************************************/
/* �Զ�������Ϣ															*/
/************************************************************************/
#define WM_CUR_EXE_REQ							(WM_USER+8000)

#endif // _CONFIGURE_H__