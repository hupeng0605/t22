#pragma once
#define __DEBUG__
#ifdef __DEBUG__
#define DEBUG1(format,...) printf("FILE: "__FILE__", LINE: %d: "format"/n", __LINE__, ##__VA_ARGS__)
#else 
#define   DEBUG1(format,...)
#endif
#include <iostream>
using namespace std;
#include <Windows.h>
#include <tchar.h>
#include "stdafx_public.h"
#include "define_public.h"
#include "KCListItem.h"
#include "KCScrollCtrl.h"
#include "KCClockCtrlEx.h"
#include <iostream>
#include <list>
#include<string>
#include<utility>
#include<vector>
#include "stdafx_public.h"
#include "BTcore.h"
 #include <fstream>
#include "HCRegSeting.h"
#define SETBTNAME_MAC 1
#define  BTINFOMESSAGE 1
#define  TESTBTCOMMANDQUEUE 1
#define AUTOUPDATACALLHISTORY  1
#define USEFULNUMBERS 1
#define  BTLOGSTATE 0
#define BTMUSIC_NUMBER_STATE 1//����������ǰ��״̬����
#define TESTDAILPROBLEM 0
#define  TESTRESTARTPROTEM  0
#define  TestBTVISION 0
#define  BTSerialPortData 0
//����ͨѶ¼����
#define MAXBTCONTACTNUM   1200
#define MAXBTMISSEDRECORDSNUM   150
#define  MAXBTDAILEDRECORDSNUM   150
#define MAXBTRECEIVEDRECORDSNUM  150
#define MAXBTALLRECORDSNUM  450
#pragma warning(disable:4996)//wcsncpy���棬strncpy���棬mbstowcs����
#pragma warning(disable:4200)//��������
#pragma warning(disable:4100)//����δʹ��
// SETUP����
extern SETUPSETTING g_SetupSetting;
typedef enum
{
	WIN_SYSTEM = 0,
	WIN_MEDIA,
	WIN_CANBUS,
	WIN_OSD,
	WIN_BACKCAR,
} FUNC_WINDOW;
//#define VWM_BT_HFP_STATE (WM_USER + 500)
struct sLangue
{
	HCHAR szContent[50][50];
};

typedef enum
{
	eDIALOGT_BTDIAL		= 0,
	eDIALOGT_BTADDRESSBOOK =1,
	eDIALOGT_BTCALLRECORDS	 ,
	eDIALOGT_BTMUSIC ,
	eDIALOGT_BTCONNECTSETTING,
	eDIALOGT_BTHMI,
	eDIALOGT_UNKNOW
}eDIALOGTYPE;
enum BluetoothEnums
{
	eMAXDIALNUMLEN = 20,
	eMAXBTDIALOGNUM= 5,
	eMAXCMDLEN = 100
};
struct Block 
{
	Block *pNext;
	char Buf[];
};
struct BTCMDList 
{
	Block *pFree;
	Block *pUsed;
	int nTotalFree;
	int nTotal;
	int nBlockSize;
};
struct sPool
{
	BTCMDList *pHead;
};
struct sCommandData 
{
	HUINT nCmdLen;
	HBYTE szCommand[eMAXCMDLEN];
};

typedef enum
{
	eBTPAIRMODE = 0,
	eBTNORMALMODE = 1,
	eBTUNKNOWMODE = 2
}eBTMODE;
typedef enum {
	BT_NONE = 0,
	BT_BC03 = 1,
	BT_BC04 = 2,
	BT_BC5 = 3
} BT_TYPE;
typedef BOOL (*pBTOpen)(BT_TYPE);
typedef BOOL (*pBTClose)(BT_TYPE);

//typedef		BOOL   ( *pSetOverScanRatio )(void *OpenHandle, OVER_SCAN_RATIO Over_Scan_Ratio);
typedef enum
{
	eBTMUSICSTOP = 0,
	eBTMUSICPLAY = 1,
	eBTMUSICPAUSE =2,
	eBTMUSICFF = 3,
	eBYMUSICFB = 4
}eBTMUSICRUNNINGSTATUS;
typedef struct Dialpad_s
{
	HCHAR cDialNum[eMAXDIALNUMLEN];
	INT32 nCurrentLen;
} Dialpad_t;
#define TEXTSIZE			2048//2048
#define dim(a)					sizeof(a) / sizeof(a[0])
#define WM_PORT_READ_DATA			WM_USER + 100
#define WM_PORT_WRITE_DATA		WM_USER + 101
typedef BOOL (*FpCallbackProc)(void* pData, UINT uMsg, WPARAM wParam, LPARAM lParam,void *pthis);
//typedef wstring XString;

// ���ڶ�д��״̬
enum enCommPortState
{
	enPortWrittenOK,
	enPortWrittenOuttime,
	enPortWrittenError,
	enPortReadOK,
	enPortReadOuttime,
	enPortReadError,
};
enum enATCommand
{
	enATCommandBegin = 0,
	enShakeHands,
	enShowAlertParam,
	enSetAlertParam,
	enShowTyreData,
	enSetTyreData,
	enDeleteTyreID,
	enStudyTyreData,
	enATCommandEnd,
};
// ���ڶ�ȡ������
struct PortRetureData 
{
	LPTSTR	pszUnicodeData;		// ���ַ�ָ��
	LPBYTE	pszAnsiData;		// խ�ַ�ָ��
	DWORD dwSize;				// ���ݳ���
};

#define TPMS_CMD_SIZE			32
struct CmdData
{
	UINT nCmdID;				 // ָ��ID
	UINT nCmdType;		         // ָ������
	UINT nCmdLength;		     // ָ���
	UCHAR szBuffer[TPMS_CMD_SIZE];// ָ�����
};                    
typedef list<CmdData> CMDList;
// ����������Ϣ
struct CmdReturnData
{
	std::string strSendBuffer;
	std::string strRecvBuffer;
};
typedef std::list<CmdReturnData> CmdReturnDataList;
struct BTParam  
{
	bool BTOpen;
	bool BTAutoAnswer;
	bool ConnectLastDevice;
	bool ConnectAfterPhoneIn;
	bool UnconnectOtherDeviceAfterPhoneIn;
	bool UnconnectAfterPhoneOut;
};

enum BTPacketEnums
{
	/* Start of packet bytes */
	eBTPACKETHEAD1     = 0x0D,
	eBTPACKETHEAD2     = 0x0A,
	eBTPACKETHEAD3     = 0x2B ,
	/* end of packet bytes */
	eBTPACKETTAIL1     =0x0D,
	eBTPACKETTAIL2     =0x0A,
	eBTPACKETHEADLEN = 3,
	eBTPACKETTAILLEN = 2,
	MAXTBPACKETBUFFERSIZE = 2048,
	eBTMAXPAYLOADDATALEN = 2048,
	eMAXSYSTEMVERSIONLEN = 20,
	eMAXPAIRDEVICE = 8
};

typedef enum
{
	eSPPPHONESCREENINFO = 0,
	eSPPTOUCHEVENTS = 1,
	eSPPPHONEKEGCONTROL = 2,
	eSPPPHONESYSTEMINFO = 3,
	eSPPSTRETCHSCREEN = 4,
	eSPPPHONEDPI = 5, 
	eSPPHIDCONNECTSTATE = 6,
	eSPPENABLEBACKANDMENU = 7,
	eSPPPHONELOCKINFO = 8,
	eSPPPHONETIME = 9,
	eSPPDAPARAPACKET = 10,
	eSPPRUNSTATE = 11
}eSPPDATATYPE;
typedef enum
{
	eSTATEHEAD1 = 0,
	eSTATEHEAD2,
	eSTATEHEAD3,
	eSTATETAIL1,
	eSTATETAIL2,
	eSTATEFINISHING,
	eSTATEPAYLOADDATA,
	eSTATEFINISH,
	BTPacketParseStateDETECT,
	BTPacketParseStateDETECTBAD,
	BTPacketParseStateLAST = BTPacketParseStateDETECTBAD

}eBTPACKETPARSESTATE;

typedef  enum
{
	eCOMMANDDATA = 0,
	eGATTDATA =1,
	eSPPDATA = 2,
	ePBDNDATA = 3,
	eMEDIAINFODATA = 4,
	eUNKNOWDATATYPE = 99
}eBTPATLOADDATATYPE;
typedef enum
{
  eLANDSCAPE = 0X01,
  eVERTICAL = 0X02
}eSCREENTYPE;
typedef enum
{
	eA2DPNOTCONNECT = 0,
	eA2DPCONNECTTING = 1,
	eA2DPCONNECTED =2,
	eA2DPPLAY = 3,
	eA2DPUNKNOW = 4
}eA2DPSTATE;
typedef enum
{
	eUNKNOWSYS = 0x00,
	eANDRIOD = 0x01,
	eIOS = 0x02,
	eWP = 0x03
}eSYSTEMTYPE;

typedef enum
{
  ePBAPCSTATEUNCONNECT = 0,
  ePBAPCSTATECONNECTING = 1,
  ePBAPCSTATECONNECTED = 2,
  ePBAPCSTATEDOWNING = 3,
  ePBAPCSTATEDOWNED = 4,
  ePBAPCSTATEDOWNINGBOOK = 5,
  ePBAPCSTATEDOWNINGINCOMMINGCALL = 6,
  ePBAPCSTATEDOWNINGOUTGOINGCALL = 7,
  ePBAPCSTATEDOWNINGMISSEDCALL = 8,
  ePBAPCSTATEDOWNINGCALLHISTORY = 9,
  ePBAPCSTATEUNKNOW = 99
}ePBAPCSTATE;
struct  sSystemInfo
{
	eSYSTEMTYPE eType;
	HBYTE cSystem[eMAXSYSTEMVERSIONLEN+1];
};
struct sPostion
{
	int x;
	int y;
};
struct sMyPhoneInfo 
{
	HINT PhoneWidth;
	HINT PhoneHight;
	HINT iAvailableCeWidth;//�����õ�CE���
	HINT iAvailableCeHight;//�������õ�CE�߶�
	HINT iMaxAvailableCeWidth;//���CEx����
	HINT iMaxAvailableCeHight;//���CEy����
	HINT iMinAvailableCeWidth;//��СCEx����
	HINT iMinAvailableCeHight;//��СCEy����
	HBYTE PhoneTime[20];
	bool bPhoneLocked;
	bool bEnableHomeBackKey;
	eSCREENTYPE PhoneScreen;
	sSystemInfo PhoneSysInfo;
};
/* Session Service Type */
typedef enum
{
	/* ͨ������*/
	BTPacketUnknowDataType,
	BTPacketReadSoftVersion  = 1, /* ��ȡ����汾*/
	BTPacketReadLocalDeviceAddress  = 2, /* ��ȡ�����豸��ַ */
	BTPacketReadLocalDeviceName   = 3, /* ��ȡ�����豸����*/
	BTPacketSetLocalDeviceName,/* ���ñ����豸����*/
	BTPacketListPairDevice,/* �г�����б����8��*/
	BTPacketDeletePairDeviceList,/* ɾ��ĳ������ȫ������豸�б�*/
	BTPacketConnectDeviceInPairList,/* ��������е��豸*/
	BTPacketUpVolume,/* ����+1*/
	BTPacketDownVolume,/* ����-1*/
	BTPacketReadPairPassword,/* ��ȡ�������*/
	BTPacketSetPairPassword,/* �����������*/
	BTPacketEnterPairMode,    /* */
	BTPacketExitPairMode,
	BTPacketEnterTestMode, /* ��ȡ�������*/
	BTPacketLoadFailSafeDefaults ,/* �ָ���������*/
	BTPacketSoftRestart,/* ������*/
	BTPacketDisconnectCurrentConnection,/* �Ͽ���ǰ����*/
	BTPacketInitialize,/* ��ʼ��*/
	BTPacketPairResult,/* ��Խ��*/
	BTPacketSendCurrentDeviceList,/* ��������б�*/
	BTPacketHighlightDevicesinPairList,/* ������ʾ����б�*/
	BTPacketPairStateEnd,/* ���״̬����*/
	/* SPPָ�� ��׿*/
	BTPacketSPPAcquireSSPState,/* ��ȡSSP����״̬*/
	BTSPPDisConnetSPP,
	BTPacketSPPConnectPhoneAndPCActive,/* ���������ֻ���PC*/
	BTPacketSPPDisconnectHID,/* �Ͽ�HID����*/
	BTPacketSPPSendDataToBT,/* �������ݸ�����*/
	BTPacketSPPConnectStateNotice,/* SPP����״̬֪ͨ*/
	BTPacketSPPSendDataToMCU,/* �������ݸ�MCU*/
	/* BLE GATTָ�� IOS*/
	BTPacketGATTAcquireGATTState,/* ��ȡGATT����״̬*/
	BTPacketGATTSendDataToBT,/* �������ݸ�����*/
	BTPacketGATTConnetStateNotice, /* GATT����״̬֪ͨ*/
	BTPacketGATTSendDatatoMCU,/* �������ݸ�MCU*/
	/* HFPָ�����¼�*/
	BTPacketHFPAcqureHFPState,/* ��ȡHFP״̬*/
	BTPacketHFPAnswerCallWhenBeCalled,/* ����ʱ�����绰*/
	BTPacketHFPRejectPhoneWhenCalling,/* ����ʱ�ܽӵ绰*/
	BTPacketHFPDialTheNumber,/* ��ͨ��״̬�²����绰*/
	BTPacketHFPSendDTMFWhenCalling,/* ͨ��״̬�·���DTMF*/
	BTPacketHFPSwitchVoiceBetweenPhoneAndDevice,/* �ֻ����豸���л�����*/
	BTPacketHFPMICMute,/* MIC����*/
	//BTPacketHFPSendDTMFWhenCalling,/* ��ȡ�����豸����*/
	BTPacketHFPRedial,/* �ز�*/
	BTPacketHFPDealCallWhenCalling,/* ͨ���д�������*/
	BTPacketHFPVoiceCall,
	BTPacketHFPStateNotice,/* HFP״̬֪ͨ*/
	BTPacketHFPBeCalled,/* ����*/
	BTPacketHFPInCallNumber,/* �������*/
	BTPacketHFPThirdPartyCallNumber,/* ����������*/
	BTPacketHFPVoiceState,/* ����״̬*/
	/* A2DPָ��¼�*/
	BTPacketA2DPAquireA2DPState,/* ��ȡA2DP״̬*/
	BTPacketA2DPConnectAVRCP,/* ����AVRCP*/
	BTPacketA2DPDisconnectA2DPAndAVRCP,/* �Ͽ�A2DP��AVRCP*/
	BTPacketA2DPState,/* A2DP֪ͨ״̬*/
    BTPacketGetA2DPMute,//��ȡ����״̬
	BTPacketA2DPMute,/* A2DP����״̬*/
	BTPacketCancelA2DPMute,//ȡ������
	/* AVRCPָ����¼�*/
	BTPacketAVRCPAcquireAVRCPState,/* ��ȡAVRCP״̬*/
	BTPacketAVRCPAPlayOrPause,/* ���ź���ͣ*/
	BTPacketAVRCPAStopPlay,/* ֹͣ����*/
	BTPacketAVRCPANext,/* ��һ��*/
	BTPacketAVRCPAPrevious,/* ��һ��*/
	BTPacketAVRCPAVRCPStateNotice,/* AVRCP״̬֪ͨ*/
	BTPacketAVRCPAPlayState,/* ����״̬*/
	BTPacketAVRCPAMusicInformation,/* ������Ϣ*/
	/* PBAPCָ��¼�*/
	BTPacketPBAPCAquirePBAPCState,/* ��ȡPBAP״̬*/
	BTPacketPBAPCSetUpPBAPConnection,/* ����PBAP����*/
	BTPacketPBAPCDisconnectPBAP,/* �Ͽ�PBAP����*/
	BTPacketPBAPCDownPhoneBook,/* ���ص绰��*/
	BTPacketPBAPCCancelDownPhoneBook,/* ȡ�����ص绰��*/
	BTPacketPBAPCStateNotice,/* PBAPC״̬֪ͨ*/
	BTPacketPBAPCPPhoneBookdata,/* ���ص绰������*/
	BTPacketPBAPCDownloadeComplete,/* �������*/
	/* �������*/
	BTPacketHIDAcequireHIDState,/* ��ȡHID����״̬*/
	BTPacketHIDConnectPhoneAndPCActive, /* ���������ֻ���PC*/
	BTPacketHIDDisconnectHID, /* �Ͽ�����*/
	BTPacketHIDMCUSendDataToHID, /* MCU�������ݸ�����*/
	BTPacketHIDCUSendDataToHID,
	BTPacketHIDKCUSendDataToHID,
	BTPacketHIDConnectNotice,/* HID����״̬֪ͨ*/
	/*��������*/
} BTPacketDataType_t;
typedef pair<string,string> PairDevice;

typedef struct
{
	HCHAR PhoneNumber[31];
}sTelNumber;
typedef struct
{
	eBTPACKETPARSESTATE eState ;
	HUINT nDatalen ;
	eBTPATLOADDATATYPE eDataType;
	//HUINT nPayloadDataLen;
	HUINT nCurrentDataLen;
	HBYTE pDataBuffer[ ];
} sBTPacketDataBuffer;
typedef struct  
{
	HBYTE cCommand[eMAXCMDLEN];
	HUINT nCommendLen;
	HUINT nSend;
	DWORD nProtuceTime;
	DWORD nSendTime;
}sCommamdItem;

typedef struct  
{
	HBYTE szMacAddress[13];
	HBYTE szDeviceName[31];
}sDeviceINFO;
typedef struct 
{
	HBYTE szVersion[31];
	HBYTE  szPairCode[31];
	sDeviceINFO LocaLDeviceINFO;
} sLocalDvice;
//������Ϣ
typedef struct  
{
	HCHAR szMusicNumber[5];
	HCHAR szMusicTotalNumber[5];
	HCHAR szMusicTitle[31];
	HCHAR szMusicArtist[31];
	HCHAR szMusicAlbum[31];
	HCHAR szMusicGenre[31];
	HCHAR szMusicPlayingTime[31];
	HINT nGetData;//��������:0 ������ 1 �������������� ר����Ϣ 2 ��1���������⣬���������������͵�ǰ������  
	HINT nCurNum;//��ǰ���ڲ�����
	HINT nTolNum;//�б��������
}sMusicINFO;
typedef struct 
{
	//HCHAR szName[10];
	HCHAR szName[20];
	sTelNumber szTelNumber;
}sContact;
struct sUsefulContact
{
	sContact szUsefulNum[200];
	sContact szEnUsefulNum[200];
	unsigned int  nTolNum;
};
typedef enum
{
	eMISSEDCALL = 0,
	eINCOMMINGCALL = 1,
	eOUTGOINGCALL = 2,
	eALLCALLRECORDS = 3,
	eUNKNOWCALLTYPE
}eCALLHISTORY;
typedef struct  
{
	sContact szContact;
	HCHAR szPhoneTime[20];
	eCALLHISTORY eCallType;
}sCallHistory;

typedef struct
{
	HUINT nTotalContact;
	HUINT nTotalIncomeCall;
	HUINT nOutGoingCall;
	HUINT nTotalMissedCall;
	HUINT nCombinationCall;
	sContact arrContact[MAXBTCONTACTNUM];
	sCallHistory arrIncomeCall[MAXBTRECEIVEDRECORDSNUM];
	sCallHistory arrOutGoingCall[MAXBTDAILEDRECORDSNUM];
	sCallHistory arrMissedCall[MAXBTMISSEDRECORDSNUM];
	sCallHistory arrCombinationCall[MAXBTALLRECORDSNUM];
#if AUTOUPDATACALLHISTORY
	HUINT nNewCallHistory;
	HUINT nNewInCome;
	HUINT nNewOutGoing;
	HUINT nNewMissed;
	sCallHistory arrNewCallHistory[60];
	sCallHistory arrNewInComeCall[20];
	sCallHistory arrNewMissedCall[20];
	sCallHistory arrNewOutGoingCall[20];
#else
#endif
}sPhoneBook;
 
typedef struct
{
	HINT nXOffset;
	HINT nYOffice;
	HBYTE cWheelOffset;
	HBYTE cButtonKey;
}sMouseClick;
typedef struct
{
	sLocalDvice LoaclDeviceINFO;//�����������
	sLocalDvice ZotyeDeviceINFO;
	sDeviceINFO arrPairDevice[8];//����б�
	sDeviceINFO CurrentPairDevice;
	HUINT nSPK;//����ֵ
	//HBYTE* m_pPairCode;//�������
	//eSCREENTYPE eScreenType;
	//sSystemInfo* m_pSystemInfo;
	HUINT nTotalPairDevice;
	HUINT nPairState;
	HUINT nPairResult;
	HUINT nPairingState;
}sBTGeneralData;
typedef struct 
{
	HUINT nSPPState;
	HUINT nConnectPhoneInitiative;
	HBYTE arrSPPPayloadData[256];
}sBTSPPData;
typedef struct  
{
	HUINT nGATTState;
	HBYTE arrGATTPayloadData[256];
}sBTGATTData;
typedef struct  
{
	HUINT nHFPState;
	sTelNumber sDialNum;
	//sTelNumber sCallInNum;
	sCallHistory sCurrentCall;
	sTelNumber sSecondCallInNum;
	HUINT nVoicePosition;//0�ڳ��� 1 �ֻ�
	bool bHFPMute;
	bool bHFPAuto;
}sBTHFPData;
typedef struct 
{
	//A2DP�¼����
	HUINT nA2DPState;
	//AVRCP�¼����
	HUINT nAVRCPState;
	eBTMUSICRUNNINGSTATUS eAVRCPPlayState;
	bool bA2DPMute;
	sMusicINFO sAVRCPMusicINFO;
}sBTAVRCPData;
typedef struct
{
	ePBAPCSTATE ePBAPCState;
	sPhoneBook sPBAPCPhoneBook;
}sBTPBAPCData;
typedef struct  
{
	//HID�¼����� 
	HUINT nHIDState;
	sMouseClick sHIDMouse;
}sBTHIDData;
typedef struct  
{
	sBTGeneralData BTGeneralData;
	sBTSPPData BTSPPData;
	sBTGATTData BTGATTData;
	sBTHFPData BTHFPData;
	sBTAVRCPData BTAVRCPData;
	sBTPBAPCData PBAPCData;
	sBTHIDData BTHIDData;
#if USEFULNUMBERS
	sUsefulContact BTUsefulNumData;
#else
#endif
}sBTCommandData;

struct sRestOfPacketData 
{
	HBYTE szData[4096];
	HUINT nDataLen;
};
struct sbtSourceGroup 
{
	IReSurface *m_pbtBkgnd;
	IReSurface *m_pbtBaseDailN;
	IReSurface *m_pbtBaseDailA;
	IReSurface *m_pbtBaseAddressbookA;
	IReSurface *m_pbtBaseCallRecordsA;
	IReSurface *m_pbtBaseMusicA;
	IReSurface *m_pbtBaseConnectStepA;
	IReSurface *m_pbtBaseAddressbookN;
	IReSurface *m_pbtBaseCallRecordsN;
	IReSurface *m_pbtBaseMusicN;
	IReSurface *m_pbtBaseConnectStepN;
	IReSurface *m_pbtBkLeft;
	IReSurface *m_pbtBkRight;
	IReSurface *m_pbtItemSelected;
	IReSurface *m_pbtLine;
	IReSurface *m_pbtCallIn;
	IReSurface *m_pbtCallOut;
	IReSurface *m_pbtMissedCall;
	IReSurface *m_pbtUpN;
	IReSurface *m_pbtUpA;
	IReSurface *m_pbtDownA;
	IReSurface *m_pbtDownN;
	IReSurface *m_pbtBarN;
	IReSurface *m_pbtBarA;
	IReSurface *m_pbtBarF;
	IReSurface *m_pbtBarD;
	IReSurface *m_pbtConnectIconN;
	IReSurface *m_pbtConnectIconA;
	IReSurface *m_pbtBottom;
	IReSurface *m_pDownProcess[12];
	IReSurface *m_pbtHmiBk;
	IReSurface *m_pbtHmiBkEn;
	IReSurface *pbtHDMIBTNOTICECH;
	IReSurface *pbtHDMIBTNOTICEEN;
};
typedef list<sContact*> NameList;
struct NameListGroup
{
	NameList   pContact[27];
	int szCount[27];
	int szTotalCount[27];
	HINT nTotalContact;
};
typedef list<int> ContactList;
struct  ContactListGroup
{
	ContactList   ContactListGrp[27];
	int szCount[27];
	int szTotalCount[27];
	HINT nTotalContact;
};



#define FILE_DEVICE_VIDEO               0x00000023

#define IOCTL_SCA_SOURCE_CONNECT                CTL_CODE(FILE_DEVICE_VIDEO, 0x01, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_YPBPR_VGA_MODE_PARSING        CTL_CODE(FILE_DEVICE_VIDEO, 0x02, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_GET_MODE                      CTL_CODE(FILE_DEVICE_VIDEO, 0x03, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_SET_TIMING_WINDOW             CTL_CODE(FILE_DEVICE_VIDEO, 0x04, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_SET_MVOP                      CTL_CODE(FILE_DEVICE_VIDEO, 0x05, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_CVBSO_SET_TIMING_WINDOW       CTL_CODE(FILE_DEVICE_VIDEO, 0x06, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_DISPLAY_MUTE                  CTL_CODE(FILE_DEVICE_VIDEO, 0x07, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_CVBSO_MUTE                    CTL_CODE(FILE_DEVICE_VIDEO, 0x08, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_DISPLAY_WINDOW_ON_OFF         CTL_CODE(FILE_DEVICE_VIDEO, 0x09, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_SET_MVOP_BASE_ADDR            CTL_CODE(FILE_DEVICE_VIDEO, 0x0A, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_SET_COLOR_Key                 CTL_CODE(FILE_DEVICE_VIDEO, 0x0B, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_CHANGE_WINDOW                 CTL_CODE(FILE_DEVICE_VIDEO, 0x0C, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_SET_PICTURE                   CTL_CODE(FILE_DEVICE_VIDEO, 0x0D, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_GET_PICTURE                   CTL_CODE(FILE_DEVICE_VIDEO, 0x0E, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_GET_MVOP_BASE_ADDR            CTL_CODE(FILE_DEVICE_VIDEO, 0x0F, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_E_UI_WINDOW_ON_OFF            CTL_CODE(FILE_DEVICE_VIDEO, 0x10, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_E_UI_FlipBuffer               CTL_CODE(FILE_DEVICE_VIDEO, 0x11, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_SCA_SWITCH_CVBS_IN                CTL_CODE(FILE_DEVICE_VIDEO, 0x12, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_SWITCH_WINCE_IN               CTL_CODE(FILE_DEVICE_VIDEO, 0x13, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_CALIBRATION					CTL_CODE(FILE_DEVICE_VIDEO, 0x14, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_LOAD_ADC_SETTING				CTL_CODE(FILE_DEVICE_VIDEO, 0x15, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_SET_OUTPUT_TIMING				CTL_CODE(FILE_DEVICE_VIDEO, 0x16, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_SOURCE_DISCONNECT             CTL_CODE(FILE_DEVICE_VIDEO, 0x17, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_SET_CONSTALPHA_VALUE			CTL_CODE(FILE_DEVICE_VIDEO, 0x18, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_GET_DISP_PATH_CONFIG          CTL_CODE(FILE_DEVICE_VIDEO, 0x19, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_GET_ACE_INFO                  CTL_CODE(FILE_DEVICE_VIDEO, 0x1A, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_RW_REGISTER                   CTL_CODE(FILE_DEVICE_VIDEO, 0x1B, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_GET_DLC_CONFIG                CTL_CODE(FILE_DEVICE_VIDEO, 0x1C, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_DIP_CONNECT               CTL_CODE(FILE_DEVICE_VIDEO, 0x1D, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_SET_WIN_ONTOP                CTL_CODE(FILE_DEVICE_VIDEO, 0x1E, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_CHK_PATCH_YPBPR_CVBSO			CTL_CODE(FILE_DEVICE_VIDEO, 0x1F, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SCA_INIT_HW_WIN					CTL_CODE(FILE_DEVICE_VIDEO, 0x20, METHOD_BUFFERED, FILE_ANY_ACCESS)


#define IOCTL_AVD_SOURCE_CONNECT                CTL_CODE(FILE_DEVICE_VIDEO, 0x101, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_AVD_CHECK_VIDEO_STANDARD          CTL_CODE(FILE_DEVICE_VIDEO, 0x102, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_AVD_CHECK_VIDEO_DETECT_STATE      CTL_CODE(FILE_DEVICE_VIDEO, 0x103, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef enum
{
	SCA_VE_OUTPUT_NTSC,
	SCA_VE_OUTPUT_PAL,
}SCA_VE_OUTPUT_STD;

typedef enum
{
	SCA_DEST_MAIN   = 0,
	SCA_DEST_SUB    = 1,
	SCA_DEST_MAIN_1 = 2,
	SCA_DEST_MAIN_2 = 3,
	SCA_DEST_SUB_2  = 4,
	SCA_DEST_CVBSO  = 5,
	SCA_DEST_HDMITx = 6,
	SCA_DEST_NUM,
}SCA_DEST_TYPE;

typedef enum
{
	SCA_SRC_VGA,
	SCA_SRC_VGA_SOG,
	SCA_SRC_YPBPR,
	SCA_SRC_CVBS,
	SCA_SRC_CVBS2,
	SCA_SRC_CVBS3,
	SCA_SRC_SVIDEO,	// Add S-video input source //
	SCA_SRC_DTV,
	SCA_SRC_SC0_VOP,
	SCA_SRC_SC1_VOP,
	SCA_SRC_SC2_VOP,
	SCA_SRC_BT656,
	SCA_SRC_BT656_1,
	SCA_SRC_DUMMY,	// add dummy input source to occupy destination
	SCA_SRC_NUM,
}SCA_SRC_TYPE;


typedef enum
{
	SCA_DISP_PRI_NONE   = 0,
	SCA_DISP_PRI_NORMAL = 1,
	SCA_DISP_PRI_CAR_BACK = 2,
}SCA_DISP_PRIORITY_TYPE;

typedef struct
{
	SCA_SRC_TYPE enSrcType;
	SCA_DEST_TYPE enDestType;
	BOOL bAutoDetect;
	SCA_DISP_PRIORITY_TYPE enPriType;
	LPTSTR	      lpEvtConnetName;
	DWORD         dwUID;
}SCA_CONNECT_CONFIG, *PSCA_CONNECT_CONFIG;

typedef struct
{
	unsigned short  x;
	unsigned short  y;    ///<start y of the window
	unsigned short  width;
	unsigned short  height;
} SCA_WINDOW_TYPE;

typedef struct
{
	BOOLEAN bSrcWin;
	BOOLEAN bCropWin;
	BOOLEAN bDispWin;
	SCA_WINDOW_TYPE stSrcWin;
	SCA_WINDOW_TYPE stCropWin;
	SCA_WINDOW_TYPE stDispWin;
}SCA_WINDOW_CONFIG;

typedef struct
{
	BOOL bEn;
	SCA_DEST_TYPE enDestType;
}SCA_DISPLAY_MUTE_CONFIG;

typedef struct
{
	SCA_SRC_TYPE enSrcType;
	SCA_DEST_TYPE enDestType;
	SCA_WINDOW_CONFIG stWinConfig;
	BOOL bImmediateUpdate;
}SCA_CHANGE_WINDOW_CONFIG;

typedef enum
{
	AVD_SRC_CVBS,
	AVD_SRC_SVIDEO,	// Add s-video input source //
	AVD_SRC_NUM,
}AVD_SRC_TYPE;

typedef struct
{
	AVD_SRC_TYPE enSrcType;
}AVD_CONNECT_CONFIG;

typedef struct
{
	SCA_SRC_TYPE enSrcType;
	unsigned short u16H_CapStart;
	unsigned short u16H_CapSize;
	unsigned short u16V_CapStart;
	unsigned short u16V_CapSize;
	unsigned short u16InputVFreq;
	BOOLEAN bHDuplicate;
	BOOLEAN bSrcInterlace;
	SCA_VE_OUTPUT_STD enVideoStd;
}SCA_VE_CONFIG;

typedef struct
{
	BOOL bMainEn;
	BOOL bSubEn;
}SCA_DISPLAY_WINDOW_ON_OFF_CONFIG;

typedef struct
{
	int View;
	BYTE u8R;
	BYTE u8G;
	BYTE u8B;
	BOOL Benable;
}SCA_COLOR_KEY;

typedef struct {
	int iView;
	BYTE  u8AlphaValue;
}SCA_CONSTANT_ALPHA_SETTING,*PSCA_CONSTANT_ALPHA_SETTING;

typedef struct
{
	SCA_DEST_TYPE enDestType;
	SCA_WINDOW_CONFIG stWinConfig;
}SCA_HW_WIN_CONFIG_INIT;

typedef enum
{
	APP_SRC_MM = 0,
	APP_SRC_CVBS =1,
	APP_SRC_YPBPR =2,
	APP_SRC_VGA =3,
	APP_SRC_BT656 =4,
	APP_SRC_VGA_SOG =5,
	APP_SRC_NUM,
}APP_SOURCE_TYPE;

#define MSTAR_COLOR_KEY_R   16
#define MSTAR_COLOR_KEY_G   4
#define MSTAR_COLOR_KEY_B   8
typedef struct 
{
	BOOL isUsed;
	APP_SOURCE_TYPE enAppSrcType;
	SCA_SRC_TYPE enScaSrcType;
	SCA_WINDOW_TYPE  stDispWin;
}SCA_DEST_RESOURCE;
typedef struct
{
	BOOL                   bChanged;
	BOOL                   bDisConnect;
	SCA_DISP_PRIORITY_TYPE enPriType;
	SCA_DEST_TYPE          enDestType;
	SCA_SRC_TYPE           enSrcType;
	DWORD				   dwUID;
}SCA_DISP_PATH_CONFIG;

typedef struct
{
	BOOL EventWndDestory;
	HANDLE EventWaitThreadClose;
	//int stActive; //0 deactive 1  active 2 accept
	DWORD dwConnectUID[SCA_DEST_NUM];
	WORD  wLastClicked;
} sca_test_status ;
DWORD Wait_Change_Event(PVOID pParms);
typedef enum{
	CAM_PRE_NONE,
	CAM_PRE_BACKCAR = 1,
	CAM_PRE_DVB_T= 2,
	CAM_PRE_DVD  = 3,
	CAM_PRE_AUX  = 4,
	CAM_PRE_CMMB = 5,
	CAM_PRE_CDC  = 6,
	CAM_PRE_IPOD = 7,
	CAM_PRE_AUX2 = 8,
	CAM_PRE_AUX3 = 9,
	CAM_PRE_VGA  = 10,
} CAM_PRE_CHANNEL;
typedef struct _PREVIEWSIZE
{
	unsigned int uiWidth;
	unsigned int uiHeight;

} PREVIEW_INFO, *PPREVIEW_INFO;
typedef struct _SATURATION
{
	unsigned char  uchSaturationCb;
	unsigned char  uchSaturationCr;
}SATURATION;

typedef enum
{
	DISP_1BPP = 0,
	DISP_2BPP,
	DISP_4BPP,
	DISP_8BPP_PAL,
	DISP_8BPP_NOPAL,
	DISP_16BPP_565,
	DISP_16BPP_A555,
	DISP_16BPP_I555,
	DISP_18BPP_666,
	DISP_18BPP_A665,
	DISP_19BPP_A666,
	DISP_24BPP_888,
	DISP_24BPP_A887,
	DISP_32BPP_A888,
	DISP_25BPP_A888
} DISP_BPP_MODE;
typedef struct
{
	unsigned char Over_Scan_Ratio_H;
	unsigned char Over_Scan_Ratio_V;
	SCA_SRC_TYPE	SrcType;
}OVER_SCAN_RATIO;

typedef struct
{
	unsigned int Over_Scan_Expend_X;
	unsigned int Over_Scan_Expend_Y;
	SCA_SRC_TYPE	SrcType;
}OVER_SCAN_EXPEND;
typedef struct
{
	DWORD dwColorKey ;
	BOOL  bOnOff;
	BOOL  bBlend;
}PARAMCKEY;

typedef struct _WINSIZE
{
	unsigned int uiStartPointX;
	unsigned int uiStartPointY;
	unsigned int uiWidth;
	unsigned int uiHeight;
} WINSIZE, *PWINSIZE;

typedef struct
{
	SCA_DEST_TYPE enDestType;
}SCA_SET_ONTOP_WIN_CONFIG;
typedef struct
{
	SCA_DEST_TYPE enDestType ;
	BOOL enMain ;
	BOOL enSub  ;
}MAIN_SUB_BLACK_STATE;
//typedef bool   (*pClearLayeredWindowBuffer)(void *OpenHandle,FUNC_WINDOW iFuncWin);
//typedef DWORD (*pGetCameraSignalStatus)(void *OpenHandle);
//typedef HANDLE(*pInitCameraPreview)(void);
//typedef		BOOL   ( *pRequestCameraPreviewRsc )(void *OpenHandle);
typedef 	HANDLE ( *pInitCameraPreview )(void);
typedef		BOOL   ( *pUnInitCameraPreview )(void *OpenHandle);
typedef		BOOL   ( *pRequestCameraPreviewRsc )(void *OpenHandle);
typedef		BOOL   ( *pReleaseCameraPreviewRsc )(void *OpenHandle);
typedef		BOOL   ( *pSetCameraPreviewChannel )(void *OpenHandle,CAM_PRE_CHANNEL  Channel);
typedef		BOOL   ( *pStartCameraPreview )(void *OpenHandle,PREVIEW_INFO  CamProInfo);
typedef		BOOL   ( *pStopCameraPreview )(void *OpenHandle);
typedef		BOOL   ( *pGetCameraPreviewFrame )(void *OpenHandle, PBYTE OutBuf); 
typedef		BOOL   ( *pSetCameraSaturation )(void *OpenHandle,SATURATION  stSaturation);
typedef		BOOL   ( *pSetCameraBrightness )(void *OpenHandle,unsigned char  uchBrightness); 
typedef		BOOL   ( *pSetCameraContrast )(void *OpenHandle,unsigned char  uchContrast); 
typedef		BOOL   ( *pSetCameraHue)(void *OpenHandle,unsigned char  uchHue);
typedef		DWORD   ( *pGetCameraSignalStatus )(void *OpenHandle); 
typedef		BOOL   ( *pSetCameraFlip )(void *OpenHandle,DWORD dwFlip);
typedef		BOOL   ( *pSetOverScanRatio )(void *OpenHandle, OVER_SCAN_RATIO Over_Scan_Ratio);
typedef		BOOL   ( *pSetOverScanExpend )(void *OpenHandle, OVER_SCAN_EXPEND Over_Scan_Expend);
typedef		DWORD   ( *pGet_BackCar_Signal )(void); 
typedef		DWORD   ( *pOpen_GOP0_Win )(BOOL bOpen); 
typedef		BOOL   ( *pGetDisplayPara_785 )(char *BrightNess, char *Contrast , char *Hue ,char *Saturation, char *SharpNess); 
typedef		BOOL   ( *pSetDisplayPara_785 )(char BrightNess, char Contrast , char Hue ,char Saturation, char SharpNess); 
typedef		BOOL   ( *pSCA_LoadAdcSetting_default )(void); 
typedef		BOOL   ( *pSCA_LoadAdcSetting_dlink )(unsigned short RedGain, unsigned short GreenGain, unsigned short BlueGain);  



/*************************Display���API************************/
typedef 		void			*			( *pInitLayeredWindow )(void);
typedef			BOOL   					( *pUnInitLayeredWindow )(void *OpenHandle);
typedef			BOOL   					( *pRequestLayeredWindowRsc )(void *OpenHandle,FUNC_WINDOW iFuncWin);
typedef			BOOL   					( *pReleaseLayeredWindowRsc )(void *OpenHandle,FUNC_WINDOW iFuncWin);
typedef			BOOL						( *pSetLayeredWindowBPPMode )(void *OpenHandle,FUNC_WINDOW iFuncWin,DISP_BPP_MODE BPPMode);
typedef			BOOL						( *pSetLayeredWindowPosition )(void *OpenHandle,FUNC_WINDOW iFuncWin,WINSIZE stWinModeParam);
typedef			BOOL						( *pSetLayeredWindowColorKey )(void *OpenHandle,FUNC_WINDOW iFuncWin,PARAMCKEY stCKeyParam);
typedef			BOOL						( *pSetLayeredWindowAlpha )(void *OpenHandle,FUNC_WINDOW iFuncWin,unsigned char uchAlpha);
typedef			BOOL						( *pSetLayeredWindowFrameBuffer )(void *OpenHandle,FUNC_WINDOW iFuncWin);
typedef			BOOL						( *pOpenLayeredWindow )(void *OpenHandle,FUNC_WINDOW iFuncWin);
typedef			BOOL						( *pCloseLayeredWindow )(void *OpenHandle,FUNC_WINDOW iFuncWin);
typedef			unsigned int *	( *pAllocLayeredWindowBuffer )(void *OpenHandle,FUNC_WINDOW iFuncWin);
typedef			BOOL						( *pFreeLayeredWindowBuffer )(void *OpenHandle,FUNC_WINDOW iFuncWin);
typedef			unsigned int *	( *pGetLayeredWindowPhyFreBuffer )(void *OpenHandle,FUNC_WINDOW iFuncWin);
typedef			BOOL						( *pClearLayeredWindowBuffer )(void *OpenHandle,FUNC_WINDOW iFuncWin);
typedef			BOOL						( *pGetMainSubBlackState )(HANDLE hDeviceFile ,MAIN_SUB_BLACK_STATE *WindowState);
typedef			BOOL						( *pSetMainSubBlack )(HANDLE hDeviceFile ,MAIN_SUB_BLACK_STATE *WindowState);

typedef			BOOL						( *pAdjustBacklight )(unsigned char uchBlVal);