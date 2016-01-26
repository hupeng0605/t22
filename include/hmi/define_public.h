
#ifndef __DEFINE_PUBLICE_H__
#define __DEFINE_PUBLICE_H__

#ifndef _T
#ifdef _UNICODE
#define _T(x)		L ## x
#else
#define _T(x)		x
#endif
#endif

/*************************************** һ���������壨BEGIN�� ***************************************/

#ifndef PATH_SEPARATOR
#	if defined(WIN32) || defined(WINCE)
#		define PATH_SEPARATOR	_T("\\")
#	else
#		define PATH_SEPARATOR	"/"
#	endif
#endif

// ָ�밲ȫ���ú�
#ifndef SAFECALL
#define SAFECALL(pObj) pObj == NULL ? NULL : pObj
#endif


/////////////////////////// һ�����·�� ///////////////////////////

// �����ļ����ڵ����·���ļ�����
#define DIR_CONFIG				_T("config")
// UI�ļ����ڵ����·���ļ�����
#define DIR_UI							_T("ui")
// �������ڵ����·���ļ�����
#define DIR_LANGUAGE			_T("language")
// �������ڵ����·���ļ�����
#define DIR_FONT			_T("Font")


/////////////////////////// �������·�� ///////////////////////////


/////////////////////////// �������·�� ///////////////////////////

// ���˵�ģ����Դ�����·���ļ�����
#define DIR_MENU				_T("main")
// RADIOģ����Դ�����·���ļ�����
#define DIR_RADIO				_T("radio")
// USB��SDģ����Դ�����·���ļ�����
#define DIR_MEDIA				_T("media")
// ����ģ����Դ�����·���ļ�����
#define DIR_BT						_T("Bluetooth")
// ����ģ����Դ�����·���ļ�����
#define DIR_SETUP				_T("Setup")
// IPODģ����Դ�����·���ļ�����
#define DIR_IPOD				_T("ipod")

/////////////////////////// �������ƺ궨�� ///////////////////////////
#define FONT_MSYH_TTF							0x00				// ΢���ź�(AVCNϵͳĬ������)
#define FONT_QUARTZ_REGULAR_TTF		0x01				// quartz_regular���壨AVCNʱ����ֵ��ʾ��
//#define FONT_DS_DIGI_TTF						0x02				// DS-DIGI���壨AVCNʱ����ֵ��������Ƶ����ʾ���壩
/////////////////////////// �����ļ����� ///////////////////////////

// ϵͳ�����ļ���
#define FILE_SETTING_CONFIG		_T("sys_setting.ini")

// RADIOģ�������ļ���
#define FILE_RADIO_CONFIG		_T("radio_setting.ini")

//SERVERģ�������ļ���
#define FILE_SERVER_CONFIG		_T("server_setting.ini")

// APP ����汾��(�ڴ�����������ӣ�bug�޸�)
#define	STR_APP_VERSION_PATH 	_T("\\HZcar\\App\\config\\AppVer.ini")

///////////////////////// MX������ض��� ///////////////////////////
// �����ļ���
#define		NAVI_FILE_NAME				_T("MXNavi.exe")
// ������������
#define		NAVI_WINDOW_NAME	_T("MXNavi")
// �����ļ�������
#define		NAVI_FOLDER_NAME		_T("MXNavi")
// �������ھ��
#define		NAVI_WINDOW_HANDLE  FindWindow(NULL, _T("MXNavi"))

// �������п�Э��
#define  WM_NAVI_MIN							RegisterWindowMessage(_T("MX_NAVI_HAS_MINIMUM"))
// �����������ʱ����֪ͨ�Ĵ���
#define  WM_NAVI_HAS_START				RegisterWindowMessage(_T("MX_NAVI_HAS_START"))
// �����˳�ʱ����֪ͨ�Ĵ���
#define  WM_NAVI_HAS_QUIT               RegisterWindowMessage(_T("MX_NAVI_HAS_QUIT"))
// wparam Ϊ 1 ʱ�� GPS ʱ��ͬ����; Ϊ 0 ʱ�� GPS ʱ��ͬ���ر�
#define  WM_CTL_NAVI_GPS_SET_SYSTIME RegisterWindowMessage(_T("WM_CTL_NAVI_GPS_SET_SYSTIME")) 
// wparam ��1 �ָ��������� 2 �ָ������洢 0 ͬʱ�ָ��������ú͵����洢 lParam��������
#define  WM_CTL_NAVI_RECOVER			RegisterWindowMessage(_T("WM_CTL_NAVI_RECOVER")) 


///////////////////////// OS���пص�Э�� ///////////////////////////
// iPod �豸�����Ϣ
#define		WM_IPOD_SIGNAL		RegisterWindowMessage(_T("WM_IPOD_SIGNAL"))	// wParam: IpodSignal  lParam:NULL

enum IpodSignal
{
	IPOD_INSERT = 0,
	IPOD_REMOVE,
	RESERVE,
};
// OS��������Ϣ
#define		WM_TOUCH_UP_OK     (WM_USER+201)

/////////////////////////// ���� IPC ID ///////////////////////////
#define IPC_ID_MIN		0
// ������� IPC ID
const unsigned char IPC_ID_MANAGE = 1;
// ��ϵͳ�˵����� IPC ID
const unsigned char IPC_ID_MENU = 2;
// ���������� IPC ID
const unsigned char IPC_ID_RADIO = 3;
// USB/SD���� IPC ID
const unsigned char IPC_ID_USBSD = 4;
// �������� IPC ID
const unsigned char IPC_ID_BT = 5;
// Setup���� IPC ID
const unsigned char IPC_ID_SETUP = 6;
// DVD���� IPC ID
const unsigned char IPC_ID_DISC = 7;
// TPMS���� IPC ID
const unsigned char IPC_ID_TPMS = 8;
// CMMB���� IPC ID
const unsigned char IPC_ID_DVBT = 9;
// IPOD���� IPC ID
const unsigned char IPC_ID_IPOD = 10;
// AVIN���� IPC ID
const unsigned char IPC_ID_AVIN = 11;
// CAMERA���� IPC ID
const unsigned char IPC_ID_CAMERA = 12;
// NAVI���� IPC ID
const unsigned char IPC_ID_NAVI = 13;
// Info Bar���� IPC ID
const unsigned char IPC_ID_INFOBAR = 14;

//�ڴ���ӽ���ID
// AirInfo���� IPC ID
const unsigned char IPC_ID_AIRINFO = 15;
//��ӽ���ID���޸Ĵ�ֵ
#define  IPC_ID_MAX		17



/////////////////////////// �������������� ///////////////////////////

// "����" ��������
const TCHAR * const STR_PROCESSNAME_MANAGE = _T("Manage.exe");
// "���˵�" ��������
const TCHAR * const STR_PROCESSNAME_MENU = _T("menu.exe");
// "RADIO" ��������
const TCHAR * const STR_PROCESSNAME_RADIO = _T("radio.exe");
// "USB/SD" ��������
const TCHAR * const STR_PROCESSNAME_USBSD = _T("usbsd.exe");
// "IPOD" ��������
const TCHAR * const STR_PROCESSNAME_IPOD = _T("ipod.exe");
// "BT" ��������
const TCHAR * const STR_PROCESSNAME_BT = _T("bt.exe");
// "SETUP" ��������
const TCHAR * const STR_PROCESSNAME_SETUP = _T("setup.exe");
// "INFO BAR" ��������
const TCHAR * const STR_PROCESSNAME_INFOBAR = _T("infobar.exe");
// "AIR INFO" ��������
const TCHAR * const STR_PROCESSNAME_AIRINFO = _T("airinfo.exe");
// "DISC"��������
const TCHAR * const STR_PROCESSNAME_DISC = _T("disc.exe");
// "Hardware monitor" �������� ����HWMONITOR.exe�������ơ�
const TCHAR * const STR_PROCESSNAME_HWMONITOR = _T("hwmonitor.exe");
// "AVIN"��������
const TCHAR * const STR_PROCESSNAME_AVIN = _T("avin.exe");
// "BackCamera"��������
const TCHAR * const STR_PROCESSNAME_CAM = _T("backcamera.exe");
// "CMMB"��������
const TCHAR * const STR_PROCESSNAME_DTV = _T("dtv.exe");

// ��Ͻ�������
const TCHAR * const STR_PROCESSNAME_DIAG = _T("diagnosticscreen.exe");
// TPMS��������
const TCHAR * const STR_PROCESSNAME_TPMS = _T("tpms.exe");

/*************************************** �������̼䴰����Ϣ���壨BEGIN��*****************************/
/*
�����ⲿ��Ϣ       ��������					        ����������
  #define      UWM_IPOD_XXXXXX              (1<<15) + ����IPC_ID_XX+4��<<8�� + 0xXX
  ��ϢID�ĵ�16λΪ1��ʾ���̼����Ϣ��0��ʾ�����ڵ���Ϣ��
  ���ֽڵ�����7���ֽڱ�ʾģ�飬��0x400+����ID��Ϊ���ֽڵ�����7�ֽڣ�
  ���1���ֽڱ�ʾ��Ϣ����
*/
////////////////////���������̵���Ϣ////////////////////
#define		  UWM_FROM_SERVER_BASE			((1<<15) + ((IPC_ID_MANAGE+4)<<8)+0x0)
#define		  UWM_SERVER_CLOSE_VEDIO		(UWM_FROM_SERVER_BASE + 1)      // server֪ͨ���̹ر���Ƶ��Ϣ
#define		  VWM_SHOW_OVERLAY				(UWM_FROM_SERVER_BASE + 2)		// �����������ư�ť��popup��ʾ���Ӳ���Ϣ
#define		  VWM_SERVER_CHANGE_TRACK		(UWM_FROM_SERVER_BASE + 3)		// server֪ͨinfobar�л�������Ϣ��lParam��ԴID
#define		  VWM_SERVER_KEY_ROTATE			(UWM_FROM_SERVER_BASE + 4)		// Ӳ��ť��ť��Ϣ��wParam��1-��������ť��2-��һ����ť��lParam��0-������1-�������ο�����궨��ֵ��
#define		  VWM_SERVER_KET_BTN					(UWM_FROM_SERVER_BASE + 5)		// Ӳ��ť������Ϣ��wParam��0-���£�1-̧��lParam����ť�������ο�����궨��ֵ��GOTO:466
#define		  VWM_SERVER_START_NAVI			(UWM_FROM_SERVER_BASE + 6)		// ֪ͨMAINMENU����NAVI��Ϣ
#define		  VWM_SERVER_EJECT				      (UWM_FROM_SERVER_BASE + 7)		// ֪ͨDISC������Ϣ
#define		  VWM_SERVER_UPDATE_ITEM_STATUS (UWM_FROM_SERVER_BASE + 8)		// ֪ͨMENU����ITEM״̬
#define		  VWM_TO_SERVER_SAVE_OK			(UWM_FROM_SERVER_BASE + 9)		// ����ģ��֪ͨSERVER������ɣ�wParam��ʾ����ID
#define		  VWM_SERVER_CHANGE_THEME_OK	(UWM_FROM_SERVER_BASE + 10)		// ����ģ���л��������֪ͨSERVER
#define		  VWM_SERVER_CHANGE_SRC			(UWM_FROM_SERVER_BASE + 11)		// �л�AVԴʱ֪ͨ��פAVԴ��Ϊ ( WPARAM : FALSE -> ֪ͨ��һ��ԴҪ�л���ȥ�� | TRUE -> ֪ͨ��һ��ԴҪ�л���ȥ�� ; LPARAM ���� )
#define		  VWM_SERVER_KEY_SEEK			(UWM_FROM_SERVER_BASE + 12)		//	Serverת��Seek��ť��Ϣ��wParam:0��Seek+ 1��Seek-��lParam��0-0.8��δ�� 1-0.8�뾭��ʱ 
#define		  VWM_SERVER_ST_SW_MODE			(UWM_FROM_SERVER_BASE + 13)		//	Server�յ�ST-SW��MODE����ʱ�����AVԴ��RadioԴ�򷢴���Ϣ֪ͨRadio����FM1->FM2->AM˳����Դ
#define		  VWM_SERVER_PARKING			(UWM_FROM_SERVER_BASE + 14)		//	Server����Parking��Ϣ�� lParam������0-Parking״̬��1-��Paking״̬
#define		  VWM_SERVER_INIT_PARAM			(UWM_FROM_SERVER_BASE + 15)		//	��Ҫʹ��Send��ʽ���͸�ģ�����л�KCWindow��ģ�鱻�ŵ�ǰ̨��Ϣ��lParam��ʾ����������ͬIPC_U_WND_INITPARAMIPC��Ϣ
#define		  VWM_SERVER_BACK_BOX_STATUS	(UWM_FROM_SERVER_BASE + 16)		//	Server֪ͨBackCamera����״̬����,LPARAM:	1  �����; 0  ����ر� 
#define		  VWM_SERVER_RESUME_AV			(UWM_FROM_SERVER_BASE + 17)		//	��������뿪Camera����BT Callʱ���²��Ż�����ͣAV���ţ�lParam: 1-ֹͣ�� 0-����
#define		  VWM_SERVER_ST_SW_KET_BTN		(UWM_FROM_SERVER_BASE + 18)		//	ST-SW������Ϣ��wParam��KEY_DOWN-���£�KEY_UP-̧��lParam����ť�������ο�����궨��ֵ��
#define		  VWM_SERVER_LOAD_LAST_MEM_OVER (UWM_FROM_SERVER_BASE + 19)		//	Server����Last Memory��ɣ�֪ͨHWMoniteȡLast Memory����.
#define		  VWM_SERVER_GET_CURRENT_AV_SRC	(UWM_FROM_SERVER_BASE + 20)		//	����ģ���ѯ��ǰԴ�����ص�ǰAVԴ��������NAVI����IPC_ID������Ϣֻ�ܲ���Send��ʽ����
#define		  VWM_SERVER_SRC_CLOSE			(UWM_FROM_SERVER_BASE + 21)				//	����ģ������˳���֪ͨServer��wParam��IPC����ID
#define		  VWM_SERVER_BACKCAMERA_STATUS	(UWM_FROM_SERVER_BASE + 22)		//	Server֪ͨBackCamera״̬����,WPARAM 1 BackCamera�����ź�		LPARAM	1  ���뵹��;       0  �˳����� */
#define		  VWM_SERVER_ENTER_NAVI			(UWM_FROM_SERVER_BASE + 23)		//	TServer����NAVI������Ϣ
#define		  VWM_SERVER_ENTER_TSERVER		(UWM_FROM_SERVER_BASE + 24)		//	��NAVI����T-MIND������Ϣ
#define		  VWM_SERVER_ARRIVAL_USB		(UWM_FROM_SERVER_BASE + 25)		//  Server֪ͨUSB��������һ��USB��lparam��USB�˿ںţ����ͨ�������ڴ�ȡֵ
#define		  VWM_SERVER_ACCOFF_ON			(UWM_FROM_SERVER_BASE + 26)		//	֪ͨServer����ACC OFF-ONָ��
#define		  VWM_SERVER_SAVE_LASTMEMORY_REQ (UWM_FROM_SERVER_BASE + 27)	//	����ģ�鱣��Last Memory����lParam:IPC_ID�����ĸ�ģ������� WParam ������֪ͨServer����Bu˲�����ݻ����������� 1:ΪBU˲�� 0Ϊ��Ҫ��ֱ��������

#define		  VWM_SERVER_SET_DIVXCODE		(UWM_FROM_SERVER_BASE + 31)		//	֪ͨSetup��DicxCode���ù� lParam������0-ע���룬1-ע����
#define		  VWM_SERVER_AMS_CLICK			(UWM_FROM_SERVER_BASE + 32)		//	֪ͨ������AMS��ť������
#define		  VWM_SERVER_AM_CLICK			(UWM_FROM_SERVER_BASE + 33)		//	֪ͨ������AM��ť������
#define		  VWM_SERVER_FM_CLICK			(UWM_FROM_SERVER_BASE + 34)		//	֪ͨ������FM��ť������
#define		  VWM_SERVER_USBSD_CHANGE		(UWM_FROM_SERVER_BASE + 35)		//	USB/SD״̬�ı估ʱ֪ͨUSB���̣�WPARAM 1:USB1,2:USB2 3:SD		LPARAM	1  ����       0  �γ�
#define	      VWM_SERVER_NAVI_SAVE_LAST_MEMORY_SUCCESS	(UWM_FROM_SERVER_BASE + 36)	//NAVI����LAst Memory�ɹ�֪ͨServer
#define		  VWM_SERVER_IPOD_REMOVECOMPLETE		(UWM_FROM_SERVER_BASE + 37)	//	Server֪ͨIPOD�豸�Ѿ��γ�

#define		  VWM_SERVER_CHANGE_MODE				(UWM_FROM_SERVER_BASE + 40)		//	֪ͨ���̸ı�Mode  wParam�� Radio��0��AM 1��FM�� USB��0��Audio 1��Video��
#define		  VWM_TO_SERVER_CANCAL_MUTE			(UWM_FROM_SERVER_BASE + 41)				// ֪ͨServer��MCU����ȡ��Mute����ָ��
#define		  VWM_SERVER_UPDATE_TIME					(UWM_FROM_SERVER_BASE + 42)				// ֪ͨ���̸��µ�ǰʱ��
#define		  VWM_SERVER_LANG_SW							(UWM_FROM_SERVER_BASE + 43)				// ֪ͨ���������л�wParam��0-���� 1-Ӣ�� lParam ��������
#define		  VWM_SERVER_BEEP									(UWM_FROM_SERVER_BASE + 44)				// BEEP ����
#define		  VWM_SERVER_BEEP_SW							(UWM_FROM_SERVER_BASE + 45)				// BEEP ʹ�ܿ���
#define		  VWM_SERVER_PEPS_ALARM						(UWM_FROM_SERVER_BASE + 46)				// PEPS ���� wParam��0-���� 1-Ӣ��
#define		  VWM_SERVER_UPDATE_TEMPERATURE	(UWM_FROM_SERVER_BASE + 47)				// ֪ͨ���̸��µ�ǰ�¶�

#define		  VWM_TO_SERVER_ENTER_PLAY_SRC		(UWM_FROM_SERVER_BASE + 50)		//	֪ͨ���������벥��Դ����
#define		  VWM_TO_SERVER_ENTER_DIRECTION_SWITCH (UWM_FROM_SERVER_BASE + 51)		//	֪ͨ���������벥��Դ����
// TopBar����Ϣ
#define		  UWM_TOPBAR_HOME						(UWM_FROM_SERVER_BASE + 80)			// ����home
#define		  UWM_TOPBAR_BACK						(UWM_FROM_SERVER_BASE + 81)			// ������һ��
#define		  UWM_BACK_SRC								(UWM_FROM_SERVER_BASE + 82)			// ������һ��Դ

///////////////////MENU���̵���Ϣ////////////////////
#define		  UWM_FROM_MENU_BASE			((1<<15) + ((IPC_ID_MENU+4)<<8)+0x0)
#define		  UWM_FROM_MENU_START_OK		(UWM_FROM_MENU_BASE + 1)		// Menu����OK������ʱʹ�ã�
#define		  UWM_FROM_MENU_START_DIAG		(UWM_FROM_MENU_BASE + 2)		//	Menu������ϻ���֪ͨServer
#define		  UWM_FROM_MENU_POWER_OFF		(UWM_FROM_MENU_BASE + 3)		//	Menu�˳���ϻ���֪ͨServer����ACC-OFF
#define		  UWM_TO_MENU_UPDATE_DLG			(UWM_FROM_MENU_BASE + 4)		//	Server֪ͨMENU��ǰ����ı�lParam��0 MianMenu 1 ��MediaMenu
#define		  UWM_MENU_SHOW_DIALOG			(UWM_FROM_MENU_BASE + 5)		//	lParam:MENU ����ģʽ��������

///////////////////RADIO���̵���Ϣ////////////////////
#define		  UWM_FROM_RADIO_BASE			((1<<15) + ((IPC_ID_RADIO+4)<<8)+0x0)
#define		  VWM_RADIO_MODE_NEXT			(UWM_FROM_RADIO_BASE + 1)		//	Radioģ�鴦��AMģʽ���յ�ST-SW��MODE������Դ��֪ͨServer�л���USBԴ
#define		  VWM_RADIO_AUTO_SCAN			(UWM_FROM_RADIO_BASE + 2)		//	�Զ���̨
#define		  VWM_RADIO_AVAILABLE_CHANNEL  (UWM_FROM_RADIO_BASE + 3)  //�Ƿ��źŵĵ�̨,wParam 0:�� 1����  lParam:��ǰ���� 0:AM  1:FM
#define		  VWM_RADIO_AREA_CHANGE	  (UWM_FROM_RADIO_BASE + 4)  // ����������ı�



///////////////////USBSD���̵���Ϣ////////////////////
#define		  UWM_FROM_USBSD_BASE			((1<<15) + ((IPC_ID_USBSD+4)<<8)+0x0)
#define		  VWM_USBSD_EXE_EXIT					(UWM_FROM_USBSD_BASE+0x01)		// �˳��ص�Radio

///////////////////BT���̵���Ϣ////////////////////
#define		  UWM_FROM_BT_BASE				((1<<15) + ((IPC_ID_BT+4)<<8)+0x0)
#define		  VWM_BT_HFP_STATE					(UWM_FROM_BT_BASE + 1)			// wParam�������·�330: BT_HFP_STATE ����
#define		  VWM_BT_OPEN_STATE              (UWM_FROM_BT_BASE + 2)        //�������� wParam�� 0 �ر� 1 ��
#define		  VWM_BT_ENTER_MUSICDLG		(UWM_FROM_BT_BASE + 3)			//BT������������
#define		  VWM_BT_PHONE_STATE            (UWM_FROM_BT_BASE + 4)			//wParam:0 �ֻ������� 1�ֻ�δ����  ���� δ֪״̬
#define		  VWM_BT_MUSICDLG_TIMEOUT		(UWM_FROM_BT_BASE + 5)	//�Զ����ӳ�ʱ�˳���������
#define		  VWM_TO_BT_RESET				 	(UWM_FROM_BT_BASE + 6)			//֪ͨ�����ָ���������
#define      VWM_TO_BT_A2DP_DISCONNECT   (UWM_FROM_BT_BASE + 7)      //������A2DP  wparam: 1 A2DP�Ͽ�  0 A2DP���� 

///////////////////SETUP���̵���Ϣ////////////////////
#define		  UWM_FROM_SETUP_BASE			((1<<15) + ((IPC_ID_SETUP+4)<<8)+0x0)
#define		  VWM_SETUP_DONE				(UWM_FROM_SETUP_BASE + 1)	//	SETUP֪ͨSERVER��Ҫ����LAST MODEL
#define		  VWM_SETUP_CHANGE_THEME		(UWM_FROM_SETUP_BASE + 2)	//	SETUP�л�������Ϣ��lParam������ʾ�����
#define		  VWM_SETUP_ENABLE_BACK_PLAY	(UWM_FROM_SETUP_BASE + 3)	//	SETUP��̨����������Ϣ��lParam��0���ã�1�����ú�̨����
#define		  VWM_SETUP_ENABLE_BEEP			(UWM_FROM_SETUP_BASE + 4)	//	SETUP��������BEEP����Ϣ��lParam:0 ���ã�1������
#define		  VWM_SETUP_ENABLE_CAMERA		(UWM_FROM_SETUP_BASE + 5)	//	SETUP�������õ�������ͷ��Ϣ��lParam:0 ���ã�1������
#define		  VWM_SETUP_ENABLE_PLAY_RULE	(UWM_FROM_SETUP_BASE + 6)	//	SETUP�����������й�����Ϣ��lParam:0 ���ã�1������
#define       VWM_SETUP_SET_BRT_CONTRAST    (UWM_FROM_SETUP_BASE + 7)   //	SETUP����LCD���ȶԱȶ���Ϣ wParam������1-���ȣ�2-�Աȶȣ� lParam������1~15����levelֵ
#define		  VWM_SETUP_LOADFACTORY			(UWM_FROM_SETUP_BASE + 8)	//	�ָ���������
#define		  VWM_SETUP_DISPLAY_USB_VIDEO	(UWM_FROM_SETUP_BASE + 9)	//  ֪ͨUSB��Display�����´���Ƶ�� lParam������1--�򿪣�0--�ر�
#define		  VWM_SETUP_CHANGE_BT_SETING		(UWM_FROM_SETUP_BASE + 10)		//	֪ͨ���̸ı�bt.EXE setup����bt���÷����仯����LastMemory��ȡ������Ϣ
#define		  VWM_SETUP_UPDATE_TIME				(UWM_FROM_SETUP_BASE + 11)			// ֪ͨserver������ǰϵͳʱ��
#define		  VWM_SETUP_SCREEN_OFF				(UWM_FROM_MENU_BASE + 12)		//	����֪ͨManage wParam : 0-���� 1-����  lParam:NULL



///////////////////DISC���̵���Ϣ////////////////////
#define		  UWM_FROM_DISC_BASE			((1<<15) + ((IPC_ID_DISC+4)<<8)+0x0)

///////////////////TPMS���̵���Ϣ////////////////////
#define		  UWM_FROM_TPMS_BASE			((1<<15) + ((IPC_ID_TPMS+4)<<8)+0x0)
#define		  VWM_TPMS_DEVICE_STATUS		(UWM_FROM_TPMS_BASE + 1)	//	TPMS֪ͨ״̬�仯��lParam��0-TPMS������1-TPMS�쳣
#define		  VWM_TPMS_RETURN_LAST_SCREEN	(UWM_FROM_TPMS_BASE + 2)	//	֪ͨServer��TPMS���淵�ص���һ��������Ϣ
#define		  VWM_TPMS_ENTER_SETUP			(UWM_FROM_TPMS_BASE + 3)	//	֪ͨ����TPMS�����û���
#define		  VWM_TPMS_MATCH_START			(UWM_FROM_TPMS_BASE + 4)	//	֪ͨTPMSģ�鷢����̥ƥ������
#define		  VWM_TPMS_MATCH_DATA_A			(UWM_FROM_TPMS_BASE + 5)	//	TPMS��̥ƥ��ɹ��󣬸���ϻ�������ݣ�A���֣�
#define		  VWM_TPMS_MATCH_DATA_B			(UWM_FROM_TPMS_BASE + 6)	//	TPMS��̥ƥ��ɹ��󣬸���ϻ�������ݣ�B���֣�
#define		  VWM_TPMS_EXIST				(UWM_FROM_TPMS_BASE + 7)	//  ֪ͨMainMenu TPMSģ�����
#define		  VWM_TPMS_MATCH_TIMEOUT		(UWM_FROM_TPMS_BASE + 8)	//  TPMSģ��֪ͨ��ϻ�����̥ƥ�䳬ʱ

///////////////////DVBT���̵���Ϣ////////////////////
#define		  UWM_FROM_DVBT_BASE			((1<<15) + ((IPC_ID_DVBT+4)<<8)+0x0)

///////////////////IPOD���̵���Ϣ////////////////////
#define		  UWM_FROM_IPOD_BASE			((1<<15) + ((IPC_ID_IPOD+4)<<8)+0x0)
#define		  VWM_IPOD_DEVICE_STATUS		(UWM_FROM_IPOD_BASE + 1)		//	iPod����γ�״̬�ı���Ϣ, wParam�� 0-ϵͳ���й�����״̬��1-ϵͳ����ʱ״̬��lParam������0-�γ���1-����

///////////////////AUXIN���̵���Ϣ////////////////////
#define		  UWM_FROM_AUXIN_BASE			((1<<15) + ((IPC_ID_AVIN+4)<<8)+0x0)


///////////////////CAMERA���̵���Ϣ////////////////////
#define		  UWM_FROM_CAMERA_BASE			((1<<15) + ((IPC_ID_CAMERA+4)<<8)+0x0)

///////////////////NAVI���̵���Ϣ////////////////////
#define		  UWM_FROM_NAVI_BASE			((1<<15) + ((IPC_ID_NAVI+4)<<8)+0x0)
#define		  VWM_RETURN_MAINMENU			(UWM_FROM_NAVI_BASE + 1)		// ��NAVI���淵�ص���������Ϣ
#define		  VWM_RETURN_SETUP				(UWM_FROM_NAVI_BASE + 2)		// ��NAVI���淵�ص�ϵͳ���ý�����Ϣ


/*************************************** ��尴����Ϣ�궨��**********************************/

//VWM_SHOW_OVERLAY��ϢwParam������ʾ��һ��overlay
#define  OVERLAY_BUTTON			0x00			// ���ư�ť���Ӳ�
#define  OVERLAY_AIRINFO		0x01			// �յ���Ϣ���Ӳ�
#define  OVERLAY_VOLUME			0x02			// ���������Ӳ�

/*************************************** ö�ٶ��� ***************************************/

typedef enum BT_HFP_STATE
{
	STATE_BT_HFP_READY									= 0,	// ����״̬(δ����״̬)
	STATE_BT_HFP_CONNECTING						= 1,	// ��������״̬
	STATE_BT_HFP_CONNECTED						= 2,	// �Ѿ�����״̬
	STATE_BT_HFP_CALLINCOMING					= 3,	// ����״̬
	STATE_BT_HFP_CALLOUTGOING					= 4,	// ȥ��״̬
	STATE_BT_HFP_CALLACTIVE							= 5,	// ���н���(ͨ����״̬)
	STATE_BT_HFP_THREEPARTY			                = 6,  // ����ͨ��״̬
	STATE_BT_HFP_CALLSTOP							    = 7, // ͨ������
	STATE_BT_HFP_DISCONNECTING                 = 8,  // �Ͽ�����״̬
}BT_HFP_STATE;

/*************************************** �������̼䴰����Ϣ���壨END��*****************************/


/*************************************** �����������������궨�� ��BEGIN��**************************/

///////////// BU-ON/ACC-ON ������������ /////////////
#define START_IGNORE	0		//	���ԣ����ǵ�һ����������
#define START_BU_ON		1		//	BU�ϵ�
#define START_ACC_ON	2		//	ACC�ϵ�

#define PARAM_BUACC_CMD(nParam)			((nParam & 0xC0000000)>>30)

///////////// ��ʾ/���� ������������ /////////////
#define PARAM_SHOW_CMD(nParam)			((0x000E0000 == ( nParam & 0x000E0000 ) ) ? SW_HIDE : SW_SHOW )


///////////// RADIO ����ģʽ�������� /////////////
#define START_RADIO_BAND_NULL	0
#define START_RADIO_BAND_AM		1
#define START_RADIO_BAND_FM		2

#define PARAM_RADIO_BAND_CMD(nParam)	((nParam & 0x38000000)>>27)

///////////// BT ����ģʽ�������� /////////////
#define START_BT_DLG_NULL			0
#define START_BT_DLG_DIAL				1
#define START_BT_DLG_PHONE_BOOK		2
#define START_BT_DLG_HISTORY		3
#define START_BT_DLG_AUDIO			4
#define START_BT_DLG_CONNECT		5
#define START_BT_DLG_MIRRORLINK	6

#define PARAM_BT_DLG_CMD(nParam)	(nParam & 0x000000FF)

///////////// media ����ģʽ�������� /////////////
#define START_MEDIA_DLG_NULL			0
#define START_MEDIA_DLG_AUDIO		1
#define START_MEDIA_DLG_VIDEO			2
#define START_MEDIA_DLG_PICTURE		3
#define START_MEDIA_DLG_EBOOK		4
#define START_MEDIA_DLG_MENU			5

#define PARAM_MEDIA_DLG_CMD(nParam)  (nParam & 0x000000FF)


/*************************************** �����������������궨�� ��END��**************************/


///////////// IPOD��USB�����������ƺ궨�� ////////
#define _MUTEX_AUDIO_USB_CHANNEL_NAME_	_T("_audio_usb_channel_")		


/*************************************** ��Ƶ����ɫ�궨��**********************************/
#define VIDEO_BAR_BG_ALPHA		0
#define VIDEO_BAR_BG_COLOR_R	0x18/*20*/
#define VIDEO_BAR_BG_COLOR_G	0x08/*10*/
#define VIDEO_BAR_BG_COLOR_B	0x18/*30*/

//  ��ӳ�������ö��
enum FT_CAR_TYPE
{
	CAR_TYPE_INVALID = -1,			// �Ƿ�����
	CAR_TYPE_NORMAL,				// ��ͨ����(785ƽ̨)
	CAR_TYPE_ZOTYE,					// ��̩T22
	CAR_TYPE_LEXUS,					// �׿���˹
	CAR_TYPE_RAV4,
	CAR_TYPE_REZI,						// ��־
	CAR_TYPE_HIGHLANDER,			// ������
	CAR_TYPE_SOC,						// ˹��³
};
// 

/*************************************** ��尴����Ϣ�궨��**********************************/
// һ�㳵�Ͱ�������
enum eKeyTypeNomal
{
	eKEY_ACCOFF						= 0x00,			// 
	eKEY_UP								= 0x01,			// ��һ���� 
	eKEY_DOWN							= 0x02,		// ��һ����	
	eKEY_MENU							= 0x03,			// �ص��������
	eKEY_RADIO							= 0x04,		// ��������
	eKEY_VOL								= 0x05,		// ������(�����ڷ��� 40��0 ��ʾ����	)
	eKEY_MODE							= 0x07,			// ģʽ�л�(�˰��������������� MP3�Ƚ�����л�)
	eKEY_TFT								= 0x08,			// ���Ʊ���(С���ź�)
	eKEY_MEDIA							= 0x09,
	eKEY_BACK							= 0x0B,			// ����һ���˵�
	eKEY_OFF_HOOK					= 0x0C,			//	�����绰������
	eKEY_ON_HOOK					= 0x0D,			//	�����绰�Ҷϼ�
	//eKEY_FF								= 0x0E,			// �����
	//eKEY_FB								= 0x0F,			// ���˼�
	eKEY_PLAY_CONTROL			= 0x0E,				// ���ſ���(0x00:�������� 0x01:��� 0x02:����)
	eKEY_SCAN							= 0x10,			// Scan �� 
	eKEY_CALL							= 0x11,			// 
	eKEY_NAVI							= 0x15,			// ������
	eKEY_SETUP							= 0x16,			// ���ü� 
	eKEY_PWROFF						= 0x17,			// ���߼� 
	eKEY_PWRON						= 0x18,			// ������
	eKEY_ACCON						= 0x1A,			// ����
	eKEY_DIRECTION					= 0x2C,			// �����(���ϡ����¡����ϡ�����)
	eKEY_ROTATE_SMART			= 0x2D,			// ������ť
};

// ע���ACC״̬�궨��
#define  ACC_ON							0x01
#define  ACC_OFF						0x02

// ע���PWR״̬�궨��
#define  PWR_ON						0x01
#define  PWR_OFF						0x02

//��ť��Ϣ��������������ť����Ϣ�Ķ���
#define  KEY_ROTATE_VOLUME		0x00				// ��������ť
#define  KEY_ROTATE_SMART			0x01					// ��һ����ť(Smart)

// ��ť��ת����״̬
#define  KEY_SPIN_LEFT					0x00				// ����(��ʱ��)
#define  KEY_SPIN_RIGHT				0x01				// ����(˳ʱ��)
#define  KEY_SPIN_DOWN				0x02				// ��ť����
#define  KEY_SPIN_UP						0x03				// ��ţ̌��
#define  KEY_SPIN_LONG_PRESS    0x04

// �������λ
#define  KEY_DIRECTION_TOPLEFT				0x01			// ���ϰ���
#define  KEY_DIRECTION_BOTTOMLEFT		0x02			// ���°���
#define  KEY_DIRECTION_TOPRIGHT			0x03			// ���ϰ���
#define  KEY_DIRECTION_BOTTOMRIGHT	0x04			// ���°���

//Ӳ��ť��Ϣ���ͣ��������º�̧��
#define KEY_DOWN					0x00				// Ӳ��ť����
#define KEY_UP						0x01				// Ӳ��ţ̌��
#define KEY_LONG_PRESS		0x02				// Ӳ��ť����

/*************************************** �ṹ�嶨�� ***************************************/

#endif /*__DEFINE_PUBLICE_H__*/