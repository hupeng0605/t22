#pragma  once
#include "stdafx_public.h"
#include "define_public.h"
#include "KCSwitchButton.h"
#include "radiocore.h"
#define RADIOCOMMANDQUEUE 1
#define INFOMESSAGE  1
#define MAXSTORECHANNEL  20 
#define RADIO_CHANNEL_ITEM_WIDTH  116
#define RADIO_CHANNEL_ITEM_HEIGHT 66
#define HI_BYTE(X) (((X) >> 8) & 0xFF)
#define LO_BYTE(X) ((X) & 0xFF)

#include<iostream>
#include<ctime>
using namespace std;
#pragma warning(disable:4996)//wcsncpy警告，strncpy警告，mbstowcs警告
#pragma warning(disable:4200)//柔性数组
// SETUP配置
extern SETUPSETTING g_SetupSetting;
struct sLangue
{
	HCHAR szContent[50][50];
};
typedef enum
{	
	eAM = 0,
	eFM = 1,
	//eFM2 =2,
}eRadioType_t;
typedef enum
{
	eENTERRADIOINTERFACE = 0x00,
	eRADIOCHANNELCHANGE = 0X01,
	eRADIOAMFMCHANNGE = 0X02,
	eRADIOCHANNELSEARCH = 0X03,
	eRADIOON  = 0X04,
	eRADIOCHANNELSTORE = 0X05,
	eRADIOADJUST = 0X06,
	eRADIOAUTOCHANNELSEARCH = 0X07,
	eRADIOSCAN = 0X08,
	eRADIOCHANNNELLISTS = 0X09,
	eRADIOCHANNNELADJUST = 0X0A,
	eRADIOSTOPAUTOCHANNELSEARCH = 0X0B,
	eRADIOBASS = 0x0c,
	eRADIOTERBLE = 0x0d,
	eRADIOSRS = 0x0e,
	eRADIOUNKNOW  = 0x99
}eRADIOCOMMANDTYPE;
typedef enum
{
	eCOMMANDPARSEHEADSYN = 0,
	eRADIOCOMMANDPARSEDATALENGTH = 1,
	eRADIOCOMMANDPARSEID,
	eRADIOCOMMANDPARSETYPE,
	eRADIOCOMMANDPARSEDATA,
	eRADIOCOMMANDPARSECHECKSUM,
	eRADIOCOMMANDPARSEFINISH,
	eRADIOCOMMANDPARSEDETECT,
	eRADIOCOMMANDPARSEDETECTBAD,
} eRADIOCOMMANDPARSESTATE;
enum eRADIOCOMMANDENUMS
{
	eCOMMANDHEAD = 0XF0,
	eRADIOCOMMANDSYN=0x01,
	eRADIOCOMMANDHEADLEN = 4,
	eRADIOCOMMANDCHECKSUMLEN =1,
	eRADIOCOMMANDIDLEN = 1,
	eRADIOCOMMANDTYPELEN = 1,
	eRADIOCOMMANDMAXPLAYLOADLEN = 256
};

typedef struct  
{
	HBYTE CommandHead;
	HBYTE  RadioCommandLen;
	HBYTE  RadioCommandSYN;
	HBYTE  RadioCommandType;
	HBYTE  RadioPlayLoadData[ ];
}sRadioCommand;

typedef struct  
{
	eRADIOCOMMANDTYPE eCommandType;
	eRADIOCOMMANDPARSESTATE eState;
	HUINT nCurrentLen;
	HUINT nBufferLen;
	HUINT nPacketLen;
	sRadioCommand   *pRadioCommand;
}sRadioCommandPacket;

typedef enum
{
	eRADIONARMAL = 0,
	eRADIOCHANNELSREACHING = 1,
	eRADIOAUTOSTORE,
	eRADIOSCANSTATE,
	eRADIOMUTE =4,
	//eRADIOSCAN = 3,
	eRARIOERROR = 5
}eRADIOWORKSTATE;
typedef enum
{
   eCHANNNELSEARCHINGFB = 0X00,
   eSTSTATEFB = 0X01,
   eAMFMSTATEFB = 0X02,
   eCHANNELSTORESTATEFB = 0X03,
   eCHANNELCHANGESTATEFB = 0X04,
   eUKNOWSTATEFB =0X05
}eRADIOFEEDBACKSTATE;

struct sRadioSourceGroup 
{
	IReSurface* pSelectedItem;
	IReSurface* pAmScale;
	IReSurface* pFmScale;
	IReSurface* pNotice;
	IReSurface* pCannelN;
	IReSurface* pCannelA;
	IReSurface* pNum0;
	IReSurface* pNum1;
	IReSurface* pNum2;
	IReSurface* pNum3;
	IReSurface* pNum4;
	IReSurface* pNum5;
	IReSurface* pNum6;
	IReSurface* pNum7;
	IReSurface* pNum8;
	IReSurface* pNum9;
	IReSurface* pNumDot;
	IReSurface* pNumNull;
};
