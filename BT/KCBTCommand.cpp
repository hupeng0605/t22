#pragma once
#include"KCBTCommand.h"
//#include "CStrConvertor.h"
#include "KCBTDialogManager.h"
#include <iostream>
#include<fstream>
#include <ctime>
#include <Winbase.h>
//#include "HCRegSeting.h"
//using namespace std;
CBTCommand* CBTCommand::s_pBTCommand = NULL;
CBTCommand* CBTCommand::Instance( )
{
	if(NULL == s_pBTCommand)
		s_pBTCommand = new CBTCommand;
	if(NULL == s_pBTCommand)
	{
		wprintf(_T("s_pSerialPort::Instance() failed \n"));
		//exit(1);
	}
	return s_pBTCommand;
}
void CBTCommand::DeleteInstance()
{
	SAFE_DELETE(s_pBTCommand);
}
void CBTCommand::SetLangue(HINT nType)
{
	if(nType == 0 || nType == 1)
	{
		m_nCurrentLangue = nType;
	}
}
HINT CBTCommand::GetLangue()
{
   return m_nCurrentLangue;
}
sPostion CBTCommand::CEPotionToPhonePotion(sPostion Postion,int nWidth,int nHight)
{
	sPostion tepm;
	tepm.x = 0;
	tepm.y = 0;
	if(nWidth > 0  && nHight > 0)
	{
		tepm.x = nWidth*Postion.x/SCREEN_WIDTH;
		tepm.y = nHight*(Postion.y)/SCREEN_HEIGHT;
	}
	return tepm;
}
int  CBTCommand::CExToPhonex(int x,int nWidth)
{
	if(m_pPhoneInfo != NULL)
	{
		if(nWidth > 0)
		{
			return (nWidth*x/(m_pPhoneInfo->iAvailableCeWidth));
		}
	}
	return 0;
}
int  CBTCommand::CEyToPhoney(int y,int nHight)
{
	if(nHight > 0)
	{
		 return (nHight*y/(m_pPhoneInfo->iAvailableCeHight));
	}
	return 0;
}
int CBTCommand::GetMaxCeAviablex(int nAvailbleWidth)
{
	int miny = 0;
	if(nAvailbleWidth > 0)
	{
		miny = (SCREEN_WIDTH + nAvailbleWidth)/2;
		if(m_pPhoneInfo != NULL)
		{
			m_pPhoneInfo->iMaxAvailableCeWidth = miny;
		}
	}
	return miny;
}
int CBTCommand::GetMinCeAviablex(int nAvailbleWidth)
{
	int minX = 0;
	if(nAvailbleWidth > 0)
	{
		minX = (SCREEN_WIDTH - nAvailbleWidth)/2;
		if(m_pPhoneInfo != NULL)
		{
			m_pPhoneInfo->iMinAvailableCeWidth = minX;
		}
	}
	return minX;
}
int CBTCommand::GetMaxCeAviabley(int nAvailbleHight)
{
	int miny = 0;
	if(nAvailbleHight > 0)
	{
		miny = (SCREEN_HEIGHT + nAvailbleHight)/2;
		if(m_pPhoneInfo != NULL)
		{
			m_pPhoneInfo->iMaxAvailableCeHight = miny;
		}
	}
	return miny;
}
int CBTCommand::GetMinCeAviabley(int nAvailbleHight)
{
	int miny = 0;
	if(nAvailbleHight > 0)
	{
		miny = (SCREEN_HEIGHT - nAvailbleHight)/2;
		if(m_pPhoneInfo != NULL)
		{
			m_pPhoneInfo->iMinAvailableCeHight = miny;
		}
	}
	return miny;
}
bool CBTCommand::IsPositionAvaiable(int x,int y,int nAvaibleWidth,int nAvaiblHight)
{
	if(x >= 0 && y >= 0 && nAvaiblHight >0 && nAvaibleWidth > 0)
	{
		int x1 =CexToCeAviablex(x,nAvaibleWidth);
		int y1 =CeyToCeAviabley(y,nAvaiblHight);
		if((x1 <0) || (y1 < 0))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	return false;
}
int CBTCommand::CexToCeAviablex(int nCex,int nAvailbleWidth)//负数不在有效区域内   计算有效地CE x坐标
{
	if((nCex >= 0) && (nAvailbleWidth > 0) && (nAvailbleWidth <= SCREEN_WIDTH))
	{
		int minX = (SCREEN_WIDTH - nAvailbleWidth)/2;
		int maxX = (SCREEN_WIDTH + nAvailbleWidth)/2;
		if(nCex >= minX && nCex <= maxX)
		{
			return (nCex - minX);
		}
	}
	return -1;
}
int CBTCommand::CeyToCeAviabley(int nCey,int nAvailbleHight)//负数不在有效区域内  计算有效地CE y坐标
{
	if((nCey >= 0) && (nAvailbleHight > 0) && (nAvailbleHight <= SCREEN_HEIGHT))
	{
		int miny = (SCREEN_HEIGHT - nAvailbleHight)/2;
		int maxy = (SCREEN_HEIGHT + nAvailbleHight)/2;
		if(nCey >= miny && nCey <= maxy)
		{
			return (nCey - miny);
		}
	}
	return -1;
}
 CBTCommand::CBTCommand()
{
	 m_pPacket = NULL;//解析数据包Buffer
	m_pBTCommandData = NULL;
	m_pSystemInfo = NULL;
//	m_pDeviceINFO = NULL;
	m_eScreenType = eLANDSCAPE;
	m_ePBAPCState = ePBAPCSTATEUNKNOW;
	m_bBTOpen = false;
	m_pPhoneInfo = NULL;
	m_bBookDataBeCleared = true; 
	m_nCurrentLangue = 0;
	m_DriverDll = NULL;
	m_bMacGet = false;
	memset(&m_sBtParam,0,sizeof(m_sBtParam));
}
CBTCommand::~CBTCommand()
{
	UnInitPort();
	SAFE_DELETE(m_pPacket);
	SAFE_DELETE(m_pBTCommandData);
	SAFE_DELETE(m_pSystemInfo);
   //SAFE_DELETE_GROUP(m_pDeviceINFO);
	SAFE_DELETE(m_pSystemInfo);
	SAFE_DELETE(m_pRestPBDNData);
	if(m_DriverDll != NULL)
	{
		FreeLibrary(m_DriverDll);
	}
	//SAFE_DELETE(s_pBTCommand);
	//DeleteCriticalSection(&m_csSendData);
}
void CBTCommand::ResetBTGeneralData(sBTGeneralData *pData)
{
	if(pData != NULL)
	{
		pData->nPairResult = 0;
		pData->nPairState = 3;
		pData->nSPK = 0;
		pData->nTotalPairDevice = 0;
		pData->nPairingState = 99;
		for(int i= 0; i < 8; i++)
		{
			memset(pData->arrPairDevice[i].szDeviceName,0,sizeof(pData->arrPairDevice[i].szDeviceName));
			memset(pData->arrPairDevice[i].szMacAddress,0,sizeof(pData->arrPairDevice[i].szMacAddress));
		}
		memset(pData->CurrentPairDevice.szDeviceName,0,sizeof(pData->CurrentPairDevice.szDeviceName));
		memset(pData->CurrentPairDevice.szMacAddress,0,sizeof(pData->CurrentPairDevice.szMacAddress));
		memset(pData->LoaclDeviceINFO.szPairCode,0,sizeof(pData->LoaclDeviceINFO.szPairCode));
		memset(pData->LoaclDeviceINFO.szPairCode,0,sizeof(pData->LoaclDeviceINFO.szVersion));
		memset(pData->LoaclDeviceINFO.LocaLDeviceINFO.szDeviceName,0,sizeof(pData->LoaclDeviceINFO.LocaLDeviceINFO.szDeviceName));
		memset(pData->LoaclDeviceINFO.LocaLDeviceINFO.szMacAddress,0,sizeof(pData->LoaclDeviceINFO.LocaLDeviceINFO.szMacAddress));
	}
}
void CBTCommand::ResetBTSPPData(sBTSPPData* pData)
{
	if(pData != NULL)
	{
		pData->nConnectPhoneInitiative = 0;
		pData->nSPPState = 0;
		memset(pData->arrSPPPayloadData,0,sizeof(pData->arrSPPPayloadData));
	}
}
void CBTCommand::ResetBTHFPData(sBTHFPData *pData)
{
	if(pData != NULL)
	{
		pData->bHFPAuto = true;
		pData->bHFPMute = false;
		pData->nHFPState = 0;
		pData->nVoicePosition = 0;
//		memset(pData->sCallInNum.PhoneNumber,0,sizeof(pData->sCallInNum.PhoneNumber));
		memset(pData->sDialNum.PhoneNumber,0,sizeof(pData->sDialNum.PhoneNumber));
		memset(pData->sSecondCallInNum.PhoneNumber,0,sizeof(pData->sSecondCallInNum.PhoneNumber));
		memset(&(pData->sCurrentCall),0,sizeof(pData->sCurrentCall));
	}
}
void CBTCommand::ResetGATTData(sBTGATTData *pData)
{
	if(pData != NULL)
	{
		pData->nGATTState = 0;
		memset(pData->arrGATTPayloadData,0,sizeof(pData->arrGATTPayloadData));
	}
}
void CBTCommand::ResetBTHIDData(sBTHIDData *pData)
{
	if(pData != NULL)
	{
		pData->nHIDState = 0;
		pData->sHIDMouse.cButtonKey = 0;
		pData->sHIDMouse.cWheelOffset = 0;
		pData->sHIDMouse.nXOffset = 0;
		pData->sHIDMouse.nYOffice = 0;
	}
}
void CBTCommand::ResetContactData(sContact *pData)
{
	if(pData != NULL)
	{
		memset(pData->szName,0,sizeof(pData->szName));
		memset(pData->szTelNumber.PhoneNumber,0,sizeof(pData->szTelNumber.PhoneNumber));
	}
}
void CBTCommand::ResetCallHistoryData(sCallHistory *pData)
{
	if(pData != NULL)
	{
		ResetContactData(&pData->szContact);
		memset(pData->szPhoneTime,0,sizeof(pData->szPhoneTime));
		pData->eCallType = eALLCALLRECORDS;
	}
}
void CBTCommand::ResetBTAVRCPData(sBTAVRCPData *pData)
{
	if(pData != NULL)
	{
		pData->nA2DPState = 0;
		pData->eAVRCPPlayState = eBTMUSICSTOP;
		pData->nAVRCPState = 0;
		pData->bA2DPMute = false;
		memset(pData->sAVRCPMusicINFO.szMusicNumber,0,sizeof(pData->sAVRCPMusicINFO.szMusicNumber))	;
		memset(pData->sAVRCPMusicINFO.szMusicTotalNumber,0,sizeof(pData->sAVRCPMusicINFO.szMusicTotalNumber));
		memset(pData->sAVRCPMusicINFO.szMusicAlbum,0,sizeof(pData->sAVRCPMusicINFO.szMusicAlbum));
		memset(pData->sAVRCPMusicINFO.szMusicArtist,0,sizeof(pData->sAVRCPMusicINFO.szMusicArtist));
		memset(pData->sAVRCPMusicINFO.szMusicGenre,0,sizeof(pData->sAVRCPMusicINFO.szMusicGenre));
		memset(pData->sAVRCPMusicINFO.szMusicPlayingTime,0,sizeof(pData->sAVRCPMusicINFO.szMusicPlayingTime));
		memset(pData->sAVRCPMusicINFO.szMusicTitle,0,sizeof(pData->sAVRCPMusicINFO.szMusicTitle));
		pData->sAVRCPMusicINFO.nGetData = 0;
		pData->sAVRCPMusicINFO.nCurNum = 0;
		pData->sAVRCPMusicINFO.nTolNum = 0;
	}
}
void CBTCommand::ResetBTPBAPCData(sBTPBAPCData *pData)
{
	if(pData != NULL)
	{
		pData->ePBAPCState = ePBAPCSTATEUNCONNECT;
		for(int i = 0;i < MAXBTCONTACTNUM;i++)
		{
			ResetContactData(&pData->sPBAPCPhoneBook.arrContact[i]);
			//ResetContactData(&pData->sPBAPCPhoneBook.arrContact[i + 400]);
			//ResetContactData(&pData->sPBAPCPhoneBook.arrContact[i + 800]);
			//ResetCallHistoryData(&pData->sPBAPCPhoneBook.arrIncomeCall[i]);
		//	ResetCallHistoryData(&pData->sPBAPCPhoneBook.arrMissedCall[i]);
			//ResetCallHistoryData(&pData->sPBAPCPhoneBook.arrOutGoingCall[i]);
			//ResetCallHistoryData(&pData->sPBAPCPhoneBook.arrCombinationCall[i]);
			//ResetCallHistoryData(&pData->sPBAPCPhoneBook.arrCombinationCall[i + 400]);
			//ResetCallHistoryData(&pData->sPBAPCPhoneBook.arrCombinationCall[i + 800]);
		}
		for(int i = 0;i < MAXBTMISSEDRECORDSNUM;i++)
		{
			ResetCallHistoryData(&pData->sPBAPCPhoneBook.arrIncomeCall[i]);
			ResetCallHistoryData(&pData->sPBAPCPhoneBook.arrMissedCall[i]);
			ResetCallHistoryData(&pData->sPBAPCPhoneBook.arrOutGoingCall[i]);
			//ResetCallHistoryData(&pData->sPBAPCPhoneBook.arrCombinationCall[i]);
		}
		for(int i = 0; i < MAXBTALLRECORDSNUM;i++)
		{
			ResetCallHistoryData(&pData->sPBAPCPhoneBook.arrCombinationCall[i]);
		}
		for(int j = 0; j < 20;j++)
		{
			ResetCallHistoryData(&pData->sPBAPCPhoneBook.arrNewCallHistory[j]);
			ResetCallHistoryData(&pData->sPBAPCPhoneBook.arrNewCallHistory[j + 20]);
			ResetCallHistoryData(&pData->sPBAPCPhoneBook.arrNewCallHistory[j + 40]);
			ResetCallHistoryData(&pData->sPBAPCPhoneBook.arrNewInComeCall[j]);
			ResetCallHistoryData(&pData->sPBAPCPhoneBook.arrNewOutGoingCall[j]);
			ResetCallHistoryData(&pData->sPBAPCPhoneBook.arrNewMissedCall[j]);		
		}
		pData->sPBAPCPhoneBook.nNewCallHistory = 0; 
		pData->sPBAPCPhoneBook.nCombinationCall = 0;
		pData->sPBAPCPhoneBook.nOutGoingCall = 0;
		pData->sPBAPCPhoneBook.nTotalContact = 0;
		pData->sPBAPCPhoneBook.nTotalIncomeCall = 0;
		pData->sPBAPCPhoneBook.nTotalMissedCall = 0;
#if AUTOUPDATACALLHISTORY
		pData->sPBAPCPhoneBook.nNewInCome = 0;
		pData->sPBAPCPhoneBook.nNewMissed = 0;
		pData->sPBAPCPhoneBook.nNewOutGoing = 0;
#endif
	}
}
void CBTCommand::ResetBTCommandData(sBTCommandData * pData)
{
	if(pData != NULL)
	{
		ResetBTAVRCPData(&pData->BTAVRCPData);
		ResetGATTData(&pData->BTGATTData);
		ResetBTGeneralData(&pData->BTGeneralData);
		ResetBTHFPData(&pData->BTHFPData);
		ResetBTHIDData(&pData->BTHIDData);
		ResetBTSPPData(&pData->BTSPPData);
		ResetBTPBAPCData(&pData->PBAPCData);
#if USEFULNUMBERS
		for(int i = 0;i <200;i++)
		{
			memset(pData->BTUsefulNumData.szUsefulNum,0,sizeof(pData->BTUsefulNumData.szUsefulNum));
			pData->BTUsefulNumData.nTolNum = 0;
		}
#else
#endif
	}
}
NameListGroup CBTCommand::GetNameListGrp()
{
	return m_szNameList;
}
NameListGroup* CBTCommand::GetNameListGrpp()
{
	return &m_szNameList;
}
 void CBTCommand::ResetNameListGrp(NameListGroup &NameGrp)
 {
	 EnterCriticalSection(&m_csNameList);
   for(int i = 0;i < 27; i++)
   {
	   if(!NameGrp.pContact[i].empty())
	   {
		  NameGrp.pContact[i].clear();
	   }	
	    NameGrp.szCount[i] = 0;
		NameGrp.szTotalCount[i] = 0;
   }
   NameGrp.nTotalContact = 0;
   LeaveCriticalSection(&m_csNameList);
 }
void CBTCommand::SetMyhWnd(HWND hhand)
{
	m_hWnd = hhand;
}
HINT CBTCommand::OnInit(DWORD dwPort, DWORD dwBaudRate)
{	
#ifdef WINCE
	/*HINSTANCE hDll;
	pBTOpen pfun = NULL;
	hDll = LoadLibraryW(L"\\Windows\\DriverAPI.dll");
	if(hDll != INVALID_HANDLE_VALUE)
	{
		pfun = (pBTOpen)GetProcAddress(hDll,_T("BluetoothOpen"));
	}
	if(hDll == INVALID_HANDLE_VALUE)
	{
		BTDEBUGINFO(L"hDll is null ERROR(%d)",GetLastError());
	}
	if(pfun == NULL)
	{
		BTDEBUGINFO(L"pfun is null");
	}
	if(pfun != NULL)
	{
		 pfun(BT_NONE);
	}
	FreeLibrary(hDll);
	pfun = NULL ;*/
	/*DWORD retshm = m_sBtParam.Open(L"BtParam",1024);
	BTParam sTemp;
	if(retshm == 0)
	{
		BTDEBUGINFO(L"打开共享内存失败");
	}
	else
	{
		int isize = sizeof(sTemp); 
		memset(&sTemp,0,sizeof(sTemp));
		m_sBtParam.Read(&sTemp,sizeof(sTemp),0);
	}*/
	//m_bBTOpen = true;
    m_hBTReset = NULL;
	m_hBTReset = CreateEvent(NULL,TRUE,false,L"BTRESET");
#if BTSerialPortData
	// m_BTSerialDataLogfile;
	HString appPath;
	HCHAR		szPath[MAX_PATH] = {0};
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	appPath += szPath;
	HINT nPos = (HINT)appPath.rfind(_T('\\'));
	if(nPos == -1)
	{
		wprintf(L"[HCSourceBase::GetExePath] exe path error ");
		return false;
	}
	appPath = appPath.substr(0, nPos+1);
	appPath += L"..\\Config\\BTSerialDataLogfile.txt";
	m_BTSerialDataLogfile.open(appPath.c_str(),ios::app);
#endif
	CloseBT();
	InitializeCriticalSection(&m_csNameList);
	m_bBTOpen = false;
	m_pPacket = CreatBTEmptyPacket();
	ResetBTPacket(m_pPacket);
	m_pSystemInfo = new sSystemInfo;
	m_ePBAPCState = ePBAPCSTATEUNKNOW;
	m_pBTCommandData = new sBTCommandData;
	ResetBTCommandData(m_pBTCommandData);
	m_pRestPBDNData = new sRestOfPacketData;
	m_pRestPBDNData->nDataLen = 0;
	memset(m_pRestPBDNData->szData,0,sizeof(m_pRestPBDNData->szData));
	//m_hWnd = NULL;
	memset(&m_sBtParam,0,sizeof(m_sBtParam));
	//m_ePBAPCState = ePBAPCSTATEUNKNOW;
	//m_pDeviceINFO = new sDeviceINFO[eMAXPAIRDEVICE];
	//CBTCommand::Instance( )->RegisterProc(ReadSerialData,WriteSerialData,m_pPacket);
	//CBTCommand::Instance( )->InitPort(dwPort,dwBaudRate);
	m_bBTOpen = false;
#if USEFULNUMBERS
	HUINT nTolNum = 0;
	nTolNum = ReadUsefulNum(&(m_pBTCommandData->BTUsefulNumData),200);
	BTDEBUGINFO(L"从文件中读取%d条记录",nTolNum);
#else
#endif
	ReadBtParamFromSHM();
	BTSETTING Setting;
	KCLastMemory::GetInstance()->GetBTMemory(Setting);
	m_sBTSetting = Setting;
	m_pPhoneInfo = new sMyPhoneInfo;
	if(m_pPhoneInfo != NULL)
	memset(m_pPhoneInfo,0,sizeof(sMyPhoneInfo));
	m_bMyPhoneInfoCleared = true;
	ReadDeviceNameFromFile();
	//if(Setting.uBtOnOff == 1)
	{
		OpenBT(dwPort,dwBaudRate);
	}
	m_bInHDMI = false;
#endif
	return 0;
}

int CBTCommand::ReadUsefulNum(sUsefulContact *pUsefulContact,HUINT nMax)
{
	if(pUsefulContact == NULL)
	{
		BTDEBUGINFO(L"pUsefulContact = null");
		return 0;
	}
	char buffer[256] = {0};
	char name[30] = {0};
	char enName[30] = {0};
	char number[70] = {0};
	char *p= NULL;
	char  *pend = NULL;
	for(int i = 0; i < nMax;i ++)
	{
		memset(&pUsefulContact->szUsefulNum[i],0,sizeof(pUsefulContact->szUsefulNum[i]));
		memset(&pUsefulContact->szEnUsefulNum[i],0,sizeof(pUsefulContact->szEnUsefulNum[i]));
	}
	pUsefulContact->nTolNum = 0;
	int nIndex = 0;
	//FILE* pFile = _wfopen(L"\\HZcar\\786sdk (armv4i)_debug\\UsefulNumbers.txt", L"r+");
	//if (NULL != pFile)
	//{
	//	BTDEBUGINFO(L"_wfopen succ!!!!");
	//	 fclose( pFile );
	//}
	//else
	//{
	//	BTDEBUGINFO(L"_wfopen ERROR(%d)!!!!", GetLastError());
	//}
	HString appPath;
	HCHAR		szPath[MAX_PATH] = {0};
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	appPath += szPath;
	HINT nPos = (HINT)appPath.rfind(_T('\\'));
	if(nPos == -1)
	{
		wprintf(L"[HCSourceBase::GetExePath] exe path error ");
		return false;
	}
	appPath = appPath.substr(0, nPos+1);
	appPath += L"..\\Config\\UsefulNumbers.txt";
    //wcsncpy() 
	ifstream examplefile1 (appPath.c_str()/*L"\\HZcar\\786sdk (armv4i)_debug\\UsefulNumbers.txt"*/);
	if (! examplefile1.is_open())
	{
		BTDEBUGINFO(L"can not open UsefulNumbers.txt");
		return 1;
		//exit (1); 
	}
	while (! examplefile1.eof() ) {
		memset(buffer,0,sizeof(buffer));
		memset(name,0,sizeof(name));
		memset(number,0,sizeof(number));
		memset(enName,0,sizeof(enName));
		examplefile1.getline (buffer,100);
		p = buffer;
		while((*p) != '^')
		{
			p++;
		}
		if(p != number && (p-buffer > 0) && (p-buffer < 19))
		{
			memcpy(name,buffer,p-buffer);
		}
		while((*p) == '^')
		{
			p++;
		}
		pend = p;
		while ((*pend) != '^')
		{
			pend++;
		}
		if(p != NULL && pend != NULL  && (pend - p) < 19 && (pend - p) > 0)
		{
			memcpy(number,p,pend - p);
		}
		p = pend;
		while((*p) == '^')
		{
			p++;
		}
		pend = p;
		while ((*pend) != '^')
		{
			pend++;
		}
		if(p != NULL && pend != NULL  && (pend - p) < 30 && (pend - p) > 0)
		{
			memcpy(enName,p,pend - p);
		}
		MultiByteToWideChar(CP_ACP,0,name,20,pUsefulContact->szUsefulNum[nIndex].szName,20);
		MultiByteToWideChar(CP_ACP,0,number,30,pUsefulContact->szUsefulNum[nIndex].szTelNumber.PhoneNumber,30);
		MultiByteToWideChar(CP_ACP,0,enName,36,pUsefulContact->szEnUsefulNum[nIndex].szName,20);
		MultiByteToWideChar(CP_ACP,0,number,30,pUsefulContact->szEnUsefulNum[nIndex].szTelNumber.PhoneNumber,30);
		nIndex ++;
	}
	pUsefulContact->nTolNum = nIndex;
	examplefile1.close();
	return nIndex;
}
sBTPacketDataBuffer* CBTCommand::CreatBTEmptyPacket()
{
	sBTPacketDataBuffer * pPacket = (sBTPacketDataBuffer*) new HBYTE[sizeof(sBTPacketDataBuffer) +eBTMAXPAYLOADDATALEN] ;
	ResetBTPacket(pPacket);
	return pPacket;
}
void CBTCommand::ResetBTPacket(sBTPacketDataBuffer * pPacket)
{
	if(pPacket != NULL)
	{
		pPacket->eState = eSTATEHEAD1;
		pPacket->nCurrentDataLen = 0;
		pPacket->nDatalen = 0;
		pPacket->eDataType = eUNKNOWDATATYPE;
		memset(pPacket->pDataBuffer,0,eBTMAXPAYLOADDATALEN);
	}
}
sBTCommandData* CBTCommand::GetBTCommandData(void)
{
	return m_pBTCommandData;
}
sBTPacketDataBuffer* CBTCommand::GetBTPacketBuffer(void)
{
	return m_pPacket;
}
eBTPATLOADDATATYPE CBTCommand::JudgeDataType(sBTPacketDataBuffer * pPacket)
{
	
	if(pPacket != NULL)
	{
		if(CompareChar((HBYTE*)"GATTDATA=",pPacket->pDataBuffer,9) == 9)
		{
		
			return eGATTDATA;
		}
		if(CompareChar((HBYTE*)"SPPDATA=",pPacket->pDataBuffer,8) == 8)
		{
			
			return eSPPDATA;
		}
		if(CompareChar((HBYTE*)"PBDNDATA=",pPacket->pDataBuffer,9) == 9)
		{
			return ePBDNDATA;
		}
		if(CompareChar((HBYTE*)"MEDIAINFO=",pPacket->pDataBuffer,10) == 10)
		{
			return eMEDIAINFODATA;
		}
	}
	return eUNKNOWDATATYPE;	
}

HUINT CBTCommand::ParsePacketStep1(HBYTE *pBuffer,HUINT nBufferlen,sBTPacketDataBuffer *pPacketDataBuffer)
{
	HUINT  nTatalLen = 0;
	if((pBuffer != NULL) && (pPacketDataBuffer != NULL) && nBufferlen > 0)
	{
		HBYTE *pt = pBuffer;
		HBYTE *ptEnd = pBuffer + nBufferlen;
		while(pt < ptEnd && pPacketDataBuffer->eState <eSTATEFINISH)
		{
			switch(pPacketDataBuffer->eState)
			{
			case eSTATEHEAD1 :
				{
					ResetBTPacket(pPacketDataBuffer);
					if((*pt) == eBTPACKETHEAD1)
					{
						pPacketDataBuffer->eState = eSTATEHEAD2;
					}
					nTatalLen++;
					pt++;
				}
				break;
			case  eSTATEHEAD2:
				{
					if((*pt) == eBTPACKETHEAD2)
					{
						pPacketDataBuffer->eState = eSTATEHEAD3;
						nTatalLen++;
						pt++;
					}
					else
					{
						ResetBTPacket(pPacketDataBuffer);
					}

				}
				break;
			case eSTATEHEAD3:
				{
					if((*pt) == eBTPACKETHEAD3)
					{
						pPacketDataBuffer->eState = eSTATETAIL1;
						nTatalLen++;
						pt++;
					}
					else
					{
						//pPacketDataBuffer->eState = eSTATEHEAD1;
						ResetBTPacket(pPacketDataBuffer);
					}
				}
				break;
			case eSTATETAIL1:
				{
					HUINT nBytesToCopy = 0;
					HBYTE *pCopy = pt; 
					while((*pt) != eBTPACKETTAIL1 && pt < ptEnd)
					{
						nBytesToCopy ++;
						pt++;
						nTatalLen++;
					}
					if(nBytesToCopy > 0 && pPacketDataBuffer->pDataBuffer != NULL)
					{
						memcpy(pPacketDataBuffer->pDataBuffer+pPacketDataBuffer->nDatalen,pCopy,nBytesToCopy);
						pPacketDataBuffer->nDatalen += nBytesToCopy;
					}
					if(pt < ptEnd && (*pt) == eBTPACKETTAIL1)
					{
						pPacketDataBuffer->eState = eSTATETAIL2;
						pt++;
						nTatalLen++;
					}	
				}
				break;
			case eSTATETAIL2:
				{
					if((*pt) == eBTPACKETTAIL2)
					{
						pPacketDataBuffer->eState = eSTATEFINISHING;
						nTatalLen++;
						pt++;
						eBTPATLOADDATATYPE eType =JudgeDataType(pPacketDataBuffer);
						//if((*pt) == eSTATEHEAD3 && eType == eUNKNOWDATATYPE)
						if((*pt) == eBTPACKETHEAD3 && eType == eUNKNOWDATATYPE)
						{
							pt ++;
							nTatalLen ++;
							ResetBTPacket(pPacketDataBuffer);
							pPacketDataBuffer->eState = eSTATETAIL1;
						}
						else if( eType != eUNKNOWDATATYPE)
						{
							//HUINT nLen = pPacketDataBuffer->pDataBuffer[pPacketDataBuffer->nDatalen-1]-'0';
							HUINT nLen = 0;
							HUINT nBaseData = 1;
							HBYTE *pTemp= pPacketDataBuffer->pDataBuffer + pPacketDataBuffer->nDatalen-1 ;
							while(pTemp != NULL && (*pTemp) != '=' && (*pTemp) >= '0' && (*pTemp) <= '9')
							{
								nLen += (*pTemp -'0') * nBaseData;
								nBaseData *=10;
								pTemp--;
							}
							ResetBTPacket(pPacketDataBuffer);
							pPacketDataBuffer->eDataType = eType;
							pPacketDataBuffer->nDatalen = nLen;
							pPacketDataBuffer->nCurrentDataLen = 0;
							pPacketDataBuffer->eState = eSTATEPAYLOADDATA;
						}
						else
						{
							pPacketDataBuffer->nCurrentDataLen = pPacketDataBuffer->nDatalen;
							pPacketDataBuffer->eState = eSTATEFINISH;
							pPacketDataBuffer->eDataType = eCOMMANDDATA;
						}
					}
					else
					{
						//pPacketDataBuffer->eState = eSTATEHEAD1;
						ResetBTPacket(pPacketDataBuffer);
					}
				}
				break;
			case  eSTATEFINISHING:
				{
					eBTPATLOADDATATYPE eType =JudgeDataType(pPacketDataBuffer);
					if((*pt) == eSTATEHEAD3 && eType == eUNKNOWDATATYPE)
					{
						pt ++;
						nTatalLen ++;
						ResetBTPacket(pPacketDataBuffer);
						pPacketDataBuffer->eState = eSTATETAIL1;
					}
					else if( eType != eUNKNOWDATATYPE)
					{
						//HUINT nLen = pPacketDataBuffer->pDataBuffer[pPacketDataBuffer->nDatalen-1]-'0';
						HUINT nLen = 0;
						HUINT nBaseData = 1;
						HBYTE *pTemp= pPacketDataBuffer->pDataBuffer + pPacketDataBuffer->nDatalen-1 ;
						while(pTemp != NULL && (*pTemp) != '=' && (*pTemp) >= '0' && (*pTemp) <= '9')
						{
							nLen += (*pTemp -'0') * nBaseData;
							nBaseData *=10;
							pTemp--;
						}
						ResetBTPacket(pPacketDataBuffer);
						pPacketDataBuffer->eDataType = eType;
						pPacketDataBuffer->nDatalen = nLen;
						pPacketDataBuffer->nCurrentDataLen = 0;
						pPacketDataBuffer->eState = eSTATEPAYLOADDATA;
					}
					else
					{
						pPacketDataBuffer->nCurrentDataLen = pPacketDataBuffer->nDatalen;
						pPacketDataBuffer->eState = eSTATEFINISH;
						pPacketDataBuffer->eDataType = eCOMMANDDATA;
					}
				}
				break;
			case  eSTATEPAYLOADDATA:
				{
					HUINT nBytesToCopy = pPacketDataBuffer->nDatalen - pPacketDataBuffer->nCurrentDataLen;
					HUINT nBytesLeft = ptEnd - pt ;
					HBYTE *pCopy = pt;
					if(nBytesLeft < nBytesToCopy)
					{
						nBytesToCopy = nBytesLeft;
					}
					if(nBytesToCopy > 0)
					{
						memcpy(pPacketDataBuffer->pDataBuffer+pPacketDataBuffer->nCurrentDataLen,pCopy,nBytesToCopy);
						pt +=nBytesToCopy;
						nTatalLen += nBytesToCopy;
						pPacketDataBuffer->nCurrentDataLen += nBytesToCopy;
					}
					if(pPacketDataBuffer->nCurrentDataLen == pPacketDataBuffer->nDatalen)
					{
						pPacketDataBuffer->eState = eSTATEFINISH;
					}
				}
				break;
			case eSTATEFINISH:
				{
					return nTatalLen;
				}
				break;
			default:
				break;
			}
		}
	}
	return nTatalLen;
}

HUINT CBTCommand::CompareChar(HBYTE *str1,HBYTE *str2,HUINT len)
{
	HUINT n=0;
	while(n < len && str1[n] == str2[n])
		n++;
	return n;
}

HUINT CBTCommand::ParsePacketCommand(sBTPacketDataBuffer *pPacketDataBuffer)
{
	if(pPacketDataBuffer != NULL)
	{
		HBYTE *pt = pPacketDataBuffer->pDataBuffer;
		HUINT nParseLen = 0;
	
			switch (*pt)
			{
			case 'G':
				{
					if(*(pt + 1) == 'V' && *(pt + 2) == 'E' && *(pt + 3) == 'R' &&*(pt + 4) == '='  && pPacketDataBuffer->nDatalen > 5)
					{
						nParseLen += 5;
						HandleReadSoftVersion(pPacketDataBuffer,nParseLen);
						break;
					}
					if(*(pt + 1) == 'L' && *(pt + 2) == 'B' && *(pt + 3) == 'A' &&*(pt + 4) == '='  && pPacketDataBuffer->nDatalen > 5)
					{
						nParseLen += 5;
						HandleReadLocalAddress(pPacketDataBuffer,nParseLen);
						break;
					}
					if(*(pt + 1) == 'L' && *(pt + 2) == 'D' && *(pt + 3) == 'N' &&*(pt + 4) == '='  && pPacketDataBuffer->nDatalen > 5)
					{
						nParseLen += 5;
						HandleReadLocalDeviceName(pPacketDataBuffer,nParseLen);
						break;
					}
					if(*(pt + 1) == 'F' && *(pt + 2) == 'P' && *(pt + 3) == 'C' &&*(pt + 4) == '='  && pPacketDataBuffer->nDatalen > 5)
					{
						nParseLen += 5;
						HandleReadPairedCode(pPacketDataBuffer,nParseLen);
						break;
					}
					if(*(pt + 1) == 'A' && *(pt + 2) == 'T' && *(pt + 3) == 'T' &&*(pt + 4) == 'S'  && *(pt + 5) == 'T' && *(pt + 6) == 'A' && *(pt + 7) == 'T' && *(pt + 8) == '=' && pPacketDataBuffer->nDatalen > 9)
					{
						nParseLen = 8;
						HandleGetGATT(pPacketDataBuffer,nParseLen);
						break;
					}
				}
				break;
			case 'S':
				{
					nParseLen +=1;
					if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"LDN=",4) == 4)
					{
						nParseLen +=4; 
						HandleSetLocalDeviceName(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"PK=",3) == 3)
					{
						nParseLen += 3;
						HandleCurrentSPK(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"FPC=",4) == 4)
					{
						nParseLen += 4;
						HandleSetPairCode(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"PPSTAT=",7) == 7)
					{
						nParseLen += 7;
						HandleGetSPPState(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"PPCONN=",7) == 7)
					{
						nParseLen += 7;
						HandleConnectPhoneInitiative(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"PPDISC=",7) == 7)
					{
						nParseLen += 7;
						HandleDisconnectHID(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"PP=",3) == 3)
					{
						nParseLen += 3;
						HandleSPP(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"PPDATA=",7) == 7)
					{
						nParseLen += 7;
						HandleSendSPPData(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"TOP=",4) == 4)
					{
						nParseLen += 4;
						HandleSTOP(pPacketDataBuffer,nParseLen);
						break;
					}
				}
				break;
			case 'L':
				{
					nParseLen +=1;
					if(CompareChar(pPacketDataBuffer->pDataBuffer,(HBYTE*)"LSPD=",5) == 5)
					{
						nParseLen += 4;
						HandelPairedLists(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer,(HBYTE*)"LSPDSTART=",10) == 10)
					{
						nParseLen += 9;
						HandelPairedListsStart(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer,(HBYTE*)"LSPDEND",7) == 7)
					{
						nParseLen += 6;
						HandelPairedListsEnd(pPacketDataBuffer,nParseLen);
						break;
					}
				}
				break;
			case 'D':
				{
					nParseLen += 1;
					if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"LPD=",4) == 4)
					{
						nParseLen += 4;
						HandleDeletePairedDevices( pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"SCA=",4) == 4)
					{
						nParseLen += 3;
						HandleDisConnectCurrentDevice(pPacketDataBuffer,nParseLen);
						break;
					}
				}
				break;
			case 'A':
				{
					nParseLen += 1;
					if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"2DPSTAT=",8) == 8)
					{
						nParseLen += 8;
						HandleA2DPState(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"2DPCONN=",8) == 8)
					{
						nParseLen += 8;
						HandleConnectA2DP( pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"2DPDISC=",8) == 8)
					{
						nParseLen += 8;
						HandleDisconnectA2DP(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"VRCPSTAT=",9) == 9)
					{
						nParseLen += 9;
						HandleConnectAVRCP(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"2DPMUTE=",8) == 8)
					{
                        nParseLen += 8;
						HandleA2DPMute(pPacketDataBuffer,nParseLen);
						break;
					}
				}
				break;
			case 'H':
				{
					nParseLen += 1;
					if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"FPSTAT=",7) == 7)
					{
						nParseLen += 7;
						HandleHFPState(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"FDIAL=",6) == 6)
					{
						nParseLen += 6;
						HandleHFPDial(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"FANSW=",6) == 6)
					{
						nParseLen += 6;
						HandleHFPAnswer(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"FPAUDO=",7) == 7)
					{
						nParseLen += 7;
						HandleHFPAudo(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"FDTMF=",6) == 6)
					{
						nParseLen += 6;
						HandleHFPDTMF(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"FMUTE=",6) == 6)
					{
						nParseLen += 6;
						HandleHFPMute(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"FBLDN=",6) == 6)
					{
						nParseLen += 6;
						HandleHFPRecall(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"FMCALL=",7) == 7)
					{
						nParseLen += 7;
						HandleHFPDealIncomeCall(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"FRING",5) == 5)
					{
						nParseLen += 5;
						HandleHFPIncomeCall(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"FPCLID=",7) == 7)
					{
						nParseLen += 7;
						HandleHFPIncomeCallNum(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"IDSTAT=",7) == 7)
					{
						nParseLen += 7;
						HandleHIDState(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"IDDISC=",7) == 7)
					{
						nParseLen += 7;
						HandleHIDDISC(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"ID=",3) == 3)
					{
						nParseLen += 3;
						HandleHID(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"FCCWA=",6) == 6)
					{
						nParseLen += 6;
						HandleHFPSecNum(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"FCHUP=",6) == 6)
					{
						nParseLen += 6;
						HandleHFPHangUp(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"FPOCID=",7) == 7)
					{
						nParseLen += 7;
						HandleHFPOutGoingCall(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"IDHOME=",7) == 7)
					{
						nParseLen += 7;
						HandHIDHome(pPacketDataBuffer,nParseLen);
						break;
					}
				}
				break;
			case 'E':
				{
					nParseLen += 1;
					if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"PRM=",4) == 4)
					{
						nParseLen += 4;
						HandleEnterPairMode(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"UTM=",4) == 4)
					{
						nParseLen += 4;
						HandleEnterTestMode(pPacketDataBuffer,nParseLen);
						break;
					}
				}
				break;
			case 'F':
				{
					nParseLen += 1;
				    if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"ACT=",4) == 4)
					{
						nParseLen += 4;
						HandleLoadFactoryDefaults(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"WD=",3) == 3)
					{
						nParseLen += 3;
						HandleFWD(pPacketDataBuffer,nParseLen);
						break;
					}
				}
				break;
			case 'I':
				{
					nParseLen += 1;
					if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"NIT=",3) == 3)
					{
						nParseLen += 3;
						HandleInit(pPacketDataBuffer,nParseLen);
						break;
					}
				}
				break;
			case 'P':
				{
					nParseLen += 1;
					if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"BDNEND",6) == 6)
					{
						nParseLen += 6;
						HandlePBDNEND(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"BSTAT=",6) == 6)
					{
						nParseLen += 6;
						HandlePBState(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"LAYSTAT=",8) == 8)
					{
						nParseLen += 8;
						HandleAVRCPPlayState(pPacketDataBuffer,nParseLen);
						break;
					}
					else if (CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"BCONN=",6) == 6)
					{
						nParseLen += 6;
						HandlePABConn(pPacketDataBuffer,nParseLen);
						break;
					}
					else if (CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"BDISC=",6) == 6)
					{
						nParseLen += 6;
						HandlePBDISC(pPacketDataBuffer,nParseLen);
						break;
					}
					else if (CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"BABROT=",7) == 7)
					{
						nParseLen += 7;
						HandleCannelDownload(pPacketDataBuffer,nParseLen);
						break;
					}
					else if (CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"AIR=",4) == 4)
					{
						nParseLen += 4;
						HandlePairResult(pPacketDataBuffer,nParseLen);
						break;
					}
					else if (CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"p=",2) == 2)
					{
						nParseLen += 2;
						HandlePP(pPacketDataBuffer,nParseLen);
						break;
					}
					else if (CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"REND=",5) == 5)
					{
						nParseLen += 5;
						HandlePairEnd(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"AIRING=",7) == 7)
					{
						nParseLen += 7;
						HandlePairState(pPacketDataBuffer,nParseLen);
						break;
					}

				}
				break;
			case 'B':
				{
					nParseLen += 1;
					if (CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"LE=",3) == 3)
					{
						nParseLen += 3;
						HandleBLE(pPacketDataBuffer,nParseLen);
						break;
					}
					else if (CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"ACK=",4) == 4)
					{
						nParseLen += 4;
						HandleBACK(pPacketDataBuffer,nParseLen);
						break;
					}
				}
				break;
			case 'M':
				{
					nParseLen += 1;
					if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"EDIAINFOSTART",13) == 13)
					{
						nParseLen += 13;
						HandleMediaInfoStart(pPacketDataBuffer,nParseLen);
						break;
					}
					else if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"EDIAINFOEND",11) == 11)
					{
						nParseLen += 11;
						HandleMediaInfoEnd(pPacketDataBuffer,nParseLen);
						break;
					}
				}
				break;
			case 'C':
				{
					nParseLen += 1;
					if(CompareChar(pPacketDataBuffer->pDataBuffer+1,(HBYTE*)"CDA=",4) == 4)
					{
						nParseLen += 4;
						HandleCurrentConnectDevice(pPacketDataBuffer,nParseLen);
						break;
					}
				}
				break;
			default:
				nParseLen ++;
				break;
			}
	}
	return 0;
}
 HUINT CBTCommand::ParsePacketPayloadData(sBTPacketDataBuffer *pPacketDataBuffer)
 {

	 if(pPacketDataBuffer != NULL && pPacketDataBuffer ->eState == eSTATEFINISH)
	 {
		switch(pPacketDataBuffer->eDataType)
		{
			case eCOMMANDDATA:
			{
				ParsePacketCommand(pPacketDataBuffer);		
			}
			break;
			case eGATTDATA:
			{
				ParsePacketGATTData(pPacketDataBuffer);
			}
			break;
			case eSPPDATA:
			{
				ParsePacketSPPData(pPacketDataBuffer);
			}
				break;
			case ePBDNDATA:
			{
					ParsePacketPBDNData(pPacketDataBuffer);
			}
				break;
			case eMEDIAINFODATA:
			{
					ParsePacketMEDIAINFOData(pPacketDataBuffer);
			}
				break;
			case eUNKNOWDATATYPE:
			{
					//cout<<"unknow datatype"<<endl;
					HandleErrorData(pPacketDataBuffer);
					//if(pPacketDataBuffer != NULL)
						//ResetBTPacket(pPacketDataBuffer);
			}
			break;
			default:
			{
				HandleErrorData(pPacketDataBuffer);
				//if(pPacketDataBuffer != NULL)
					//ResetBTPacket(pPacketDataBuffer);
			}
			break;
		}
	 }
	
	 return 0;
 }
HUINT CBTCommand::ParsePacketGATTData(sBTPacketDataBuffer *pPacketDataBuffer)
{
	if(pPacketDataBuffer != NULL )
	{
		
	}
	return 0;
}
 HUINT CBTCommand::ParsePacketSPPData(sBTPacketDataBuffer *pPacketDataBuffer)
 {
	 if(pPacketDataBuffer != NULL )
	 {
		 HBYTE *pt = pPacketDataBuffer->pDataBuffer;
		// HBYTE *ptEnd = pPacketDataBuffer->pDataBuffer + pPacketDataBuffer->nDatalen;
		 HBYTE cCheck = CalcChecksum(pt+1,pPacketDataBuffer->nCurrentDataLen - 2);
		 BTDEBUGINFO(L"cCheck = %d,*pt = %d",cCheck,(*pt));
		 if((*pt) == 0x0B && cCheck == *(pt + (pPacketDataBuffer->nCurrentDataLen - 1)))
		 {
			 switch(*(pt+1))
			 {
				case 0x02:
				{
					HandleSPPPhoneScreenInfo(pPacketDataBuffer);
				}
				break;
				case 0x12:
				{
					HandleSPPPhoneTouchEvents(pPacketDataBuffer);
				}
				break;
				case 0x13:
				{
					HandleSPPPhoneKeyControl(pPacketDataBuffer);
				}
					break;
				case 0x17:
					{
						HandleSPPPhoneSystemInfo(pPacketDataBuffer);
					}
					break;
				case 0x21:
					{
						HandleSPPPhoneStreachScreen(pPacketDataBuffer);
					}
					break;
				case 0x22:
					{
						HandleSPPPhoneDPI(pPacketDataBuffer);
					}
					break;
				case 0x23:
					{
						HandleSPPPhoneHIDConnectState(pPacketDataBuffer);
					}
					break;
				case 0x24:
					{
						HandleSPPPhoneEnableBackAndMenu(pPacketDataBuffer);
					}
					break;
				case 0x25:
					{
						HandleSPPPhoneLockInfo(pPacketDataBuffer);
					}
					break;
				case 0x26:
					{
						HandleSPPPhoneTime(pPacketDataBuffer);
					}
					break;
				case 0x27:
					{
						HandleSPPDAParaPacket(pPacketDataBuffer);
					}
					break;
				case 0x28:
					{
						HandleSPPRunState(pPacketDataBuffer);
					}
					break;
				default:
					break;
			 }
		 }
	 }
	 return 0;
 }
 HUINT CBTCommand::ParsePacketPBDNData(sBTPacketDataBuffer *pPacketDataBuffer)
 {
	  sBTCommandData *pTempData = GetBTCommandData();
	 if(pPacketDataBuffer != NULL && m_pRestPBDNData != NULL && pTempData != NULL && pPacketDataBuffer->nCurrentDataLen > 0)
	 {
		 HBYTE *pCardBeg = NULL;
		 HBYTE *pCardEnd =  NULL;
		 memcpy(m_pRestPBDNData->szData + m_pRestPBDNData->nDataLen,pPacketDataBuffer->pDataBuffer,pPacketDataBuffer->nDatalen);
		 m_pRestPBDNData->nDataLen = m_pRestPBDNData->nDataLen + pPacketDataBuffer->nDatalen;
		 HBYTE *pt = m_pRestPBDNData->szData;
		 HBYTE *ptEnd = m_pRestPBDNData->szData + m_pRestPBDNData->nDataLen;
		 pCardEnd = pCardBeg = pt;
		 HBYTE *pRestData = pCardEnd;
		switch (m_ePBAPCState)
		{
			case ePBAPCSTATEDOWNINGBOOK:
			{
				 HUINT nNum = 0;
				do {
						pCardBeg =(HBYTE*)strstr((char*)pCardBeg,"BEGIN:VCARD");
						if(pCardBeg != NULL)
						{
							pCardEnd = (HBYTE*)strstr((char*)pCardBeg,"END:VCARD");
						}
						if(pCardEnd != NULL && pCardBeg != NULL && pCardBeg < pCardEnd)
						{
							HUINT nIndex = pTempData->PBAPCData.sPBAPCPhoneBook.nTotalContact;
							if(nIndex < MAXBTCONTACTNUM)
							{
								bool res = FindContactname(pCardBeg,pCardEnd,&(pTempData->PBAPCData.sPBAPCPhoneBook.arrContact[nIndex]));
								if(!res)
								{
									BTDEBUGINFO(L"Not Find Name!");
									swprintf_s(pTempData->PBAPCData.sPBAPCPhoneBook.arrContact[nIndex].szName,10,L"%s",L"<未知号码>");
								}
								if(true)
								{		
									nNum = FindContactPhoneNum(pCardBeg,pCardEnd,&(pTempData->PBAPCData.sPBAPCPhoneBook.arrContact[nIndex]));
									if(nNum > 0)
									{
										AddContactToList(&pTempData->PBAPCData.sPBAPCPhoneBook.arrContact[nIndex],m_szNameList);
									}
									if(nNum > 1 )
									{
										for(HINT i = 1; i < nNum;i++)
										{
											memcpy(pTempData->PBAPCData.sPBAPCPhoneBook.arrContact[nIndex + i].szName,pTempData->PBAPCData.sPBAPCPhoneBook.arrContact[nIndex].szName,sizeof(pTempData->PBAPCData.sPBAPCPhoneBook.arrContact[nIndex].szName));
											AddContactToList(&pTempData->PBAPCData.sPBAPCPhoneBook.arrContact[nIndex + i],m_szNameList);
										}
									}
								}
								pTempData->PBAPCData.sPBAPCPhoneBook.nTotalContact = nNum +nIndex;
							}
						pCardBeg = pCardEnd + strlen("END:VCARD");
						pRestData = pCardBeg;
						}
					}
					while (pCardBeg < ptEnd && pCardBeg != NULL && pCardEnd != NULL);	
					::PostMessage(m_hWnd,WM_USER + 24,WPARAM(m_ePBAPCState),pTempData->PBAPCData.sPBAPCPhoneBook.nTotalContact);
				 if(pTempData->PBAPCData.sPBAPCPhoneBook.nTotalContact == MAXBTCONTACTNUM )
				 {
					 HBYTE cCommand[20] = {0};
					 HUINT nCmdlen = strlen("AT+PBABORT\r\n");
					 strncpy((char*)cCommand,"AT+PBABORT\r\n",nCmdlen);
#ifdef  TESTBTCOMMANDQUEUE
					 CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketPBAPCCancelDownPhoneBook,NULL);
#else
					 CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
				 }
			}
			break;
			case ePBAPCSTATEDOWNINGINCOMMINGCALL:
			{
				HINT nNum = 0;
				sCallHistory *pHistory =NULL;
				do {
						 nNum = pTempData->PBAPCData.sPBAPCPhoneBook.nTotalIncomeCall;
						 pHistory= &pTempData->PBAPCData.sPBAPCPhoneBook.arrIncomeCall[nNum];
						 if(nNum >= 0 && pHistory != NULL)
						 {
							 pCardBeg =(HBYTE*)strstr((char*)pCardBeg,"BEGIN:VCARD");
							 if(pCardBeg != NULL)
							 {
								 pCardEnd = (HBYTE*)strstr((char*)pCardBeg,"END:VCARD");
							 }
							 if(pCardEnd != NULL && pCardBeg != NULL && pCardBeg < pCardEnd)
							 {
								 HINT	nn =FindContactPhoneNum(pCardBeg,pCardEnd,&pHistory[0].szContact);
								 if(nn == 1 && pTempData->PBAPCData.sPBAPCPhoneBook.nTotalIncomeCall < MAXBTRECEIVEDRECORDSNUM)
								 {
								 bool res = FindContactname(pCardBeg,pCardEnd,&pHistory[0].szContact);
								 if(!res)
								 {
									 BTDEBUGINFO(L"Not Find Name!");
									 swprintf_s(pHistory->szContact.szName,10,L"%s",L"<未知号码>");
								 }
									 FindCallHistoryTime(pCardBeg,pCardEnd,pHistory);
									 //BTDEBUGINFO(L"num:%s,Time:%s",pHistory[nNum].szContact.szTelNumber.PhoneNumber,pHistory[nNum].szPhoneTime);
									 pTempData->PBAPCData.sPBAPCPhoneBook.nTotalIncomeCall += nn;
									 pHistory[0].eCallType = eINCOMMINGCALL;
								 }
								 pCardBeg = pCardEnd + strlen("END:VCARD");
								 pRestData = pCardBeg;
							 }
						 }
				}
				while (pCardBeg < ptEnd && pCardBeg != NULL && pCardEnd != NULL);
				 ::PostMessage(m_hWnd,WM_USER + 24,WPARAM(m_ePBAPCState), pTempData->PBAPCData.sPBAPCPhoneBook.nTotalIncomeCall);
				 if(pTempData->PBAPCData.sPBAPCPhoneBook.nTotalIncomeCall == MAXBTRECEIVEDRECORDSNUM )
				 {
					 HBYTE cCommand[20] = {0};
					 HUINT nCmdlen = strlen("AT+PBABORT\r\n");
					 strncpy((char*)cCommand,"AT+PBABORT\r\n",nCmdlen);
#ifdef  TESTBTCOMMANDQUEUE
					 CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketPBAPCCancelDownPhoneBook,NULL);
#else
					 CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
				 }
			}
			break;
			case ePBAPCSTATEDOWNINGOUTGOINGCALL:
			{
				HINT nNum = 0;
				sCallHistory *pHistory =NULL;
				do {
						nNum = pTempData->PBAPCData.sPBAPCPhoneBook.nOutGoingCall;
						pHistory = &pTempData->PBAPCData.sPBAPCPhoneBook.arrOutGoingCall[nNum];
						if(nNum >= 0 && pHistory != NULL)
						{
							pCardBeg =(HBYTE*)strstr((char*)pCardBeg,"BEGIN:VCARD");
							if(pCardBeg != NULL)
							{
								pCardEnd = (HBYTE*)strstr((char*)pCardBeg,"END:VCARD");
							}
							if(pCardEnd != NULL && pCardBeg != NULL && pCardBeg < pCardEnd)
							{
								HINT	nn =FindContactPhoneNum(pCardBeg,pCardEnd,&pHistory[0].szContact);
								if(nn == 1 && pTempData->PBAPCData.sPBAPCPhoneBook.nOutGoingCall < MAXBTDAILEDRECORDSNUM)
								{
									 bool res = FindContactname(pCardBeg,pCardEnd,&pHistory[0].szContact);
									 if(!res)
									 {
										 BTDEBUGINFO(L"Not Find Name!");
										 swprintf_s(pHistory->szContact.szName,10,L"%s",L"<未知号码>");
									 }
									FindCallHistoryTime(pCardBeg,pCardEnd,pHistory);
									//BTDEBUGINFO(L"num:%s,Time:%s",pHistory[nNum].szContact.szTelNumber.PhoneNumber,pHistory[nNum].szPhoneTime);
									pTempData->PBAPCData.sPBAPCPhoneBook.nOutGoingCall += nn;
									pHistory[0].eCallType = eOUTGOINGCALL;
								}
								pCardBeg = pCardEnd + strlen("END:VCARD");
								pRestData = pCardBeg;
						}
					}
				}
				while (pCardBeg < ptEnd && pCardBeg != NULL && pCardEnd != NULL);
				::PostMessage(m_hWnd,WM_USER + 24,WPARAM(m_ePBAPCState), pTempData->PBAPCData.sPBAPCPhoneBook.nOutGoingCall);
				if(pTempData->PBAPCData.sPBAPCPhoneBook.nOutGoingCall == MAXBTDAILEDRECORDSNUM )
				{
					HBYTE cCommand[20] = {0};
					HUINT nCmdlen = strlen("AT+PBABORT\r\n");
					strncpy((char*)cCommand,"AT+PBABORT\r\n",nCmdlen);
#ifdef  TESTBTCOMMANDQUEUE
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketPBAPCCancelDownPhoneBook,NULL);
#else
					CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
				}
			}
			break;
			case ePBAPCSTATEDOWNINGMISSEDCALL:
			{
				HINT nNum = 0;
				sCallHistory *pHistory = NULL;
				do {
						nNum = pTempData->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall;
						pHistory = &(pTempData->PBAPCData.sPBAPCPhoneBook.arrMissedCall[nNum]);
						if(pHistory != NULL && nNum >= 0)
						{
							pCardBeg =(HBYTE*)strstr((char*)pCardBeg,"BEGIN:VCARD");
							if(pCardBeg != NULL)
							{
								pCardEnd = (HBYTE*)strstr((char*)pCardBeg,"END:VCARD");
							}
							if(pCardEnd != NULL && pCardBeg != NULL && pCardBeg < pCardEnd)
							{
								HINT	nn =FindContactPhoneNum(pCardBeg,pCardEnd,&pHistory[0].szContact);
								if(nn == 1 && pTempData->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall < MAXBTMISSEDRECORDSNUM)
								{
									bool res = FindContactname(pCardBeg,pCardEnd,&pHistory[0].szContact);
									if(!res)
									{
										BTDEBUGINFO(L"Not Find Name!");
										swprintf_s(pHistory->szContact.szName,10,L"%s",L"<未知号码>");
									}
									FindCallHistoryTime(pCardBeg,pCardEnd,pHistory);
									//BTDEBUGINFO(L"num:%s,Time:%s",pHistory[nNum].szContact.szTelNumber.PhoneNumber,pHistory[nNum].szPhoneTime);
									pTempData->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall += nn;
									pHistory[0].eCallType = eMISSEDCALL;
								}
								pCardBeg = pCardEnd + strlen("END:VCARD");
								pRestData = pCardBeg;
							}
						}
					}
					while (pCardBeg < ptEnd && pCardBeg != NULL && pCardEnd != NULL);
					 ::PostMessage(m_hWnd,WM_USER + 24,WPARAM(m_ePBAPCState), pTempData->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall);
					 if(pTempData->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall == MAXBTMISSEDRECORDSNUM )
					 {
						 HBYTE cCommand[20] = {0};
						 HUINT nCmdlen = strlen("AT+PBABORT\r\n");
						 strncpy((char*)cCommand,"AT+PBABORT\r\n",nCmdlen);
#ifdef  TESTBTCOMMANDQUEUE
						 CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketPBAPCCancelDownPhoneBook,NULL);
#else
						 CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
					 }
			}
			break;
			case ePBAPCSTATEDOWNINGCALLHISTORY:
			{
				HINT nNum = 0;
				HINT nMissedNum = 0;
				sCallHistory *pHistory = NULL;
				sCallHistory *pMissedCall = NULL;
				do {
						nNum = pTempData->PBAPCData.sPBAPCPhoneBook.nCombinationCall;
						pHistory = &pTempData->PBAPCData.sPBAPCPhoneBook.arrCombinationCall[nNum];
						nMissedNum = pTempData->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall;
						pMissedCall = &pTempData->PBAPCData.sPBAPCPhoneBook.arrMissedCall[nMissedNum];
						if(pHistory != NULL)
						{
							pCardBeg =(HBYTE*)strstr((char*)pCardBeg,"BEGIN:VCARD");
							if(pCardBeg != NULL)
							{
								pCardEnd = (HBYTE*)strstr((char*)pCardBeg,"END:VCARD");
							}
							if(pCardEnd != NULL && pCardBeg != NULL && pCardBeg < pCardEnd)
							{
								HBYTE *pReceive = NULL;
								HBYTE *pDial  = NULL;
								HBYTE *pMiss = NULL;
								pReceive = (HBYTE*)strstr((char*)pCardBeg,"RECEIVED");
								pDial = (HBYTE*)strstr((char*)pCardBeg,"DIALED");
								pMiss = (HBYTE*)strstr((char*)pCardBeg,"MISSED");
							
								HINT	nn =FindContactPhoneNum(pCardBeg,pCardEnd,&pHistory[0].szContact);
								if(nn == 1 && pTempData->PBAPCData.sPBAPCPhoneBook.nCombinationCall < MAXBTALLRECORDSNUM)
								{
									bool res = FindContactname(pCardBeg,pCardEnd,&pHistory[0].szContact);
									if(!res)
									{
										BTDEBUGINFO(L"Not Find Name!");
										swprintf_s(pHistory->szContact.szName,10,L"%s",L"<未知号码>");
									}
									FindCallHistoryTime(pCardBeg,pCardEnd,pHistory);
									//BTDEBUGINFO(L"num:%s,Time:%s",pHistory[nNum].szContact.szTelNumber.PhoneNumber,pHistory[nNum].szPhoneTime);
									pTempData->PBAPCData.sPBAPCPhoneBook.nCombinationCall += nn;
									if(pDial != NULL && pDial < pCardEnd)
									{
										pHistory[0].eCallType = eOUTGOINGCALL;
									}
									if(pReceive != NULL && pReceive < pCardEnd)
									{
										pHistory[0].eCallType = eINCOMMINGCALL;
									}
									if(pMiss != NULL && pReceive < pCardEnd)
									{
										pHistory[0].eCallType = eMISSEDCALL;
									}
									/*if(pHistory[0].eCallType == eMISSEDCALL && pTempData->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall < 400)
									{
										bool res = FindContactname(pCardBeg,pCardEnd,&pMissedCall[0].szContact);
										{
											if(!res)
											{
												BTDEBUGINFO(L"Not Find Name!");
												swprintf_s(pMissedCall->szContact.szName,10,L"%s",L"<未知号码>");
											}
										}
										FindCallHistoryTime(pCardBeg,pCardEnd,pMissedCall);
										FindContactPhoneNum(pCardBeg,pCardEnd,&pMissedCall[0].szContact);
										pMissedCall[0].eCallType = eMISSEDCALL;
										pTempData->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall += 1;
									}*/
								}
								pCardBeg = pCardEnd + strlen("END:VCARD");
								pRestData = pCardBeg;
							}
						}
					}	
				while (pCardBeg < ptEnd && pCardBeg != NULL && pCardEnd != NULL);
				::PostMessage(m_hWnd,WM_USER + 24,WPARAM(m_ePBAPCState), pTempData->PBAPCData.sPBAPCPhoneBook.nCombinationCall);
				if(pTempData->PBAPCData.sPBAPCPhoneBook.nCombinationCall == MAXBTALLRECORDSNUM )
				{
					HBYTE cCommand[20] = {0};
					HUINT nCmdlen = strlen("AT+PBABORT\r\n");
					strncpy((char*)cCommand,"AT+PBABORT\r\n",nCmdlen);
#ifdef  TESTBTCOMMANDQUEUE
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketPBAPCCancelDownPhoneBook,NULL);
#else
					CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
				}
			}
			break;
			default:
			{
			}
			break;
		}
		HUINT nRestLen = ptEnd - pRestData ;
		//if(nRestLen > 2047)
		if(pRestData > ptEnd)
		{
			BTDEBUGINFO(L"nRestLen too big");
			m_pRestPBDNData->nDataLen = 0;
			memset(m_pRestPBDNData->szData,0,4096);
		}
		 else if(nRestLen > 0 && nRestLen < 2048)
		{
			for(HINT i = 0; i< nRestLen ;i++)
			{
				m_pRestPBDNData->szData[i] = pRestData[i];
			}
			m_pRestPBDNData->nDataLen = nRestLen;
			memset(m_pRestPBDNData->szData + m_pRestPBDNData->nDataLen,0,4096-m_pRestPBDNData->nDataLen);
		}
		else
		{
			m_pRestPBDNData->nDataLen = 0;
			memset(m_pRestPBDNData->szData,0,4096);
		}
		
	    BTDEBUGINFO(L"联系人:%d,已拨电话:%d,来电:%d,未接:%d,全部通话:%d",pTempData->PBAPCData.sPBAPCPhoneBook.nTotalContact,pTempData->PBAPCData.sPBAPCPhoneBook.nOutGoingCall,pTempData->PBAPCData.sPBAPCPhoneBook.nTotalIncomeCall,pTempData->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall,pTempData->PBAPCData.sPBAPCPhoneBook.nCombinationCall);
	 }
	 // BTDEBUGINFO(L"%s:beg",__FUNCTIONW__);
	// ::PostMessage(m_hWnd,WM_USER+6,WPARAM(m_ePBAPCState),NULL);
	  return 0;
 }

 HUINT CBTCommand::ParsePacketMEDIAINFOData(sBTPacketDataBuffer *pPacketDataBuffer)
 {
	 HUINT nLen=0;
	 if(pPacketDataBuffer != NULL && pPacketDataBuffer->nDatalen > 3 && m_pBTCommandData != NULL)
	 {
		 int iCharId = (pPacketDataBuffer->pDataBuffer)[1] + (((pPacketDataBuffer->pDataBuffer)[2])<<8);
		 BTDEBUGINFO(L"Media Type:%d ,CharSetId:%d",pPacketDataBuffer->pDataBuffer[0],iCharId);
		 switch(pPacketDataBuffer->pDataBuffer[0])
		 {			
			 {
		 case 0x01:
			 {
				 memset(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicTitle,0,sizeof(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicTitle));
				 HUINT n = MultiByteToWideChar(CP_UTF8,0,(LPCSTR)pPacketDataBuffer->pDataBuffer +3, pPacketDataBuffer->nDatalen-3,m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicTitle,sizeof(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicTitle));
				 m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicTitle[n] = L'\0';
				 m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.nGetData = 1;
			 }
			 break;
		 case 0x02:
			 {
				 memset(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicArtist,0,sizeof(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicArtist));
				 HUINT n = MultiByteToWideChar(CP_UTF8,0,(LPCSTR)pPacketDataBuffer->pDataBuffer +3,pPacketDataBuffer->nDatalen-3,m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicArtist,sizeof(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicArtist));
				 m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicArtist[n] = L'\0';
				  m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.nGetData = 1;
			 }
			 break;
		 case 0x03:
			 {
				 memset(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicAlbum,0,sizeof(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicAlbum));
				 HUINT n = MultiByteToWideChar(CP_UTF8,0,(LPCSTR)pPacketDataBuffer->pDataBuffer +3,pPacketDataBuffer->nDatalen-3,m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicAlbum,sizeof(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicAlbum));
				 m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicAlbum[n] = L'\0';
				  m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.nGetData = 1;
			 }
			 break;
		 case 0x04:
			 {
				/* HBYTE szTemp[10] = {0};
				 szTemp[0] = '-';
				 szTemp[1] = '1';*/
				// if(CompareChar(pPacketDataBuffer->pDataBuffer +3,(HBYTE*)"-1",2)  != 2)
				 {
					 memset(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicNumber,0,sizeof(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicNumber));
					 HUINT n = MultiByteToWideChar(CP_UTF8,0,(LPCSTR)pPacketDataBuffer->pDataBuffer +3,pPacketDataBuffer->nDatalen-3,m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicNumber,sizeof(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicNumber));
					 m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicNumber[n] = L'\0';
					 string sCurNum((char*)(pPacketDataBuffer->pDataBuffer +3));
				   if(sCurNum.size() > 0 && sCurNum.size() < 5)
				   {
						 m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.nCurNum = atoi(sCurNum.c_str());
				   }
				 }
				
				BTDEBUGINFO(L"szMusicNumber:%s",m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicNumber);
			 }
			 break;
		 case 0x05:
			 {
				 memset(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicTotalNumber,0,sizeof(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicTotalNumber));
				//if(CompareChar(pPacketDataBuffer->pDataBuffer +3,(HBYTE*)"0" ,1)  != 1 /*&& CompareChar(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicNumber,HBYTE("-1") ,2)  != 2*/)
				{
				 HUINT n = MultiByteToWideChar(CP_UTF8,0,(LPCSTR)pPacketDataBuffer->pDataBuffer +3,pPacketDataBuffer->nDatalen-3,m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicTotalNumber,sizeof(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicTotalNumber));
				 m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicTotalNumber[n] = L'\0';
				  m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.nGetData = 2;
				  string sTolNum((char*)(pPacketDataBuffer->pDataBuffer +3));
				  if(sTolNum.size() > 0 && sTolNum.size() < 5)
				  {
					  m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.nTolNum = atoi(sTolNum.c_str());
				  }
				}
				 BTDEBUGINFO(L"szMusicTotalNumber:%s",m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicTotalNumber);
			 }
			 break;
		 case 0x06:
			 {
				 memset(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicGenre,0,sizeof(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicGenre));
				 HUINT n = MultiByteToWideChar(CP_UTF8,0,(LPCSTR)pPacketDataBuffer->pDataBuffer +3,pPacketDataBuffer->nDatalen-3,m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicGenre,sizeof(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicGenre));
				 m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicGenre[n] = L'0';
			 }
			 break;
		 case 0x07:
			 {
				 memset(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicPlayingTime,0,sizeof(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicPlayingTime));
				 HUINT n = MultiByteToWideChar(CP_UTF8,0,(LPCSTR)pPacketDataBuffer->pDataBuffer +3,pPacketDataBuffer->nDatalen-3,m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicPlayingTime,sizeof(m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicPlayingTime));
				 m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicPlayingTime[n] = L'\0';
				 BTDEBUGINFO(L"szMusicPlayingTime:%s",m_pBTCommandData->BTAVRCPData.sAVRCPMusicINFO.szMusicPlayingTime);
			 }
			 break;
		 default:
			 break;
			 }	
		 }
	 }
	 return nLen;
 }

BOOL CBTCommand::ReadSerialData(void* pData, UINT uMsg, WPARAM wParam, LPARAM lParam,void *pthis)
{
	//BTDEBUGINFO(L"[%s]Enter",__FUNCTIONW__);
	CBTCommand* pCBTCommand = (CBTCommand*)pthis;
	pCBTCommand->ReadSerialData( pData, uMsg, wParam, lParam);
	//BTDEBUGINFO(L"[%s]Exit",__FUNCTIONW__);
	return 0;
}
BOOL CBTCommand::WriteSerialData(void* pData, UINT uMsg, WPARAM wParam, LPARAM lParam,void *pthis)
{
	CBTCommand* pCBTCommand = (CBTCommand*)pthis;
	pCBTCommand->WriteSerialData(pData, uMsg, wParam, lParam);
	return 0;
}
BOOL CBTCommand::ReadSerialData(void* pData, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HUINT nTolParseLen = 0;
#if   BTINFOMESSAGE
	HCHAR arrTxt[2048] = {0};
	HINT n = MultiByteToWideChar(CP_ACP,0,(char*)((PortRetureData*)lParam)->pszAnsiData,-1,NULL,0);
	MultiByteToWideChar(CP_ACP,0,(char*)((PortRetureData*)lParam)->pszAnsiData,((PortRetureData*)lParam)->dwSize,arrTxt,((PortRetureData*)lParam)->dwSize);
	arrTxt[((PortRetureData*)lParam)->dwSize] = L'\0';
	BTDEBUGINFO(L"[%s]%s,uSize=%d,n=%d",__FUNCTIONW__,arrTxt,((PortRetureData*)lParam)->dwSize,n);
#else
#endif
#if BTSerialPortData
	char szTemp[2048] = {0};
	if(((PortRetureData*)lParam)->dwSize > 0)
	{
		memcpy(szTemp,(char*)((PortRetureData*)lParam)->pszAnsiData,((PortRetureData*)lParam)->dwSize);
		szTemp[2047] = 0;
		if(m_BTSerialDataLogfile.is_open())
		{
			m_BTSerialDataLogfile<<GetTickCount() <<"        ReadSerialData:"<<szTemp<<endl;
		}
	}
#endif
	if(uMsg == WM_PORT_READ_DATA)
	{
		switch(wParam)
		{
		case enPortReadOK:
			{
				do
				{
					HUINT nParseLen = 0;
					nParseLen = ParsePacketStep1(((PortRetureData*)lParam)->pszAnsiData+nTolParseLen,((PortRetureData*)lParam)->dwSize-nTolParseLen,(sBTPacketDataBuffer*)pData);
					if(BTPacketParseComplete((sBTPacketDataBuffer*)pData))
					{
						ParsePacketPayloadData((sBTPacketDataBuffer*)pData);
						ResetBTPacket((sBTPacketDataBuffer*)pData);
					}
					nTolParseLen += nParseLen;
				}
				while(nTolParseLen<((PortRetureData*)lParam)->dwSize);
			}
			break;
		case enPortReadError:
			{
				BTDEBUGINFO(L"COM ERROR:%s",__FUNCTIONW__);
				//HandelReadError();
			}
			break;
		default:
			break;
		}
		return 0;
	}
	//BTDEBUGINFO(L"[%s]Exit",__FUNCTIONW__);
	return 1;
}
BOOL CBTCommand::WriteSerialData(void* pData, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
bool CBTCommand::BTPacketParseComplete(sBTPacketDataBuffer *pPacketDataBuffer)
{
	
	if(pPacketDataBuffer != NULL)
	{
		if(pPacketDataBuffer->eState >= eSTATEFINISH)
		{
		   //BTDEBUGINFO(L"%s,nLen= %d,nCurrentLen=%d",__FUNCTIONW__,pPacketDataBuffer->nDatalen,pPacketDataBuffer->nCurrentDataLen);
#if BTINFOMESSAGE
		//	if(pPacketDataBuffer->eDataType != ePBDNDATA)
			{
				HCHAR arrTxt[2048] = {0};
				MultiByteToWideChar(CP_ACP,0,(char*)pPacketDataBuffer->pDataBuffer,pPacketDataBuffer->nDatalen,arrTxt,pPacketDataBuffer->nDatalen);
				arrTxt[pPacketDataBuffer->nDatalen] = L'\0';
				BTDEBUGINFO(L"[%s]%s,eDataType=%d,uSize=%d,ncurrentLen=%d",__FUNCTIONW__,arrTxt,pPacketDataBuffer->eDataType,pPacketDataBuffer->nDatalen,pPacketDataBuffer->nCurrentDataLen);
			}   
#else
#endif
		return true;
		}	
	}
	return false;
}

HUINT CBTCommand::HandleReadSoftVersion(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
	if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos)
	{
		HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		if(nLen > 0  && m_pBTCommandData != NULL)
		{
			memset(m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.szVersion,0,sizeof(m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.szVersion));
			memcpy(m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.szVersion,pPacketDataBuffer->pDataBuffer + nPos,nLen) ;
			m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.szVersion[nLen] = '\0';
			KCBTVersion *pBTVersion = KCBTVersion::GetInstance();
			if(pBTVersion != NULL)
			{
				pBTVersion->SetBTVersion((char*)(m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.szVersion));
			}
#if TestBTVISION
		PostMessage(m_hWnd,WM_USER + 26,0,0);
#endif
			return nLen;
		}
	}
	return 0;
}
HUINT CBTCommand::HandleReadLocalAddress(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
	if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos+1)
	{	  
		HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		if(nLen == 2)
		{

		}
		else 
		{
			if(pPacketDataBuffer->pDataBuffer[nPos] == '0' && pPacketDataBuffer->pDataBuffer[nPos+1] == ',')
				{
					HUINT nByesToCopy = nLen - 2;
					if(nByesToCopy >0 && m_pBTCommandData != NULL)
					{
						m_bMacGet = true;
						memcpy(m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.LocaLDeviceINFO.szMacAddress,pPacketDataBuffer->pDataBuffer + nPos+2,nLen) ;
						m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.LocaLDeviceINFO.szMacAddress[nLen] = '\0';
					}
				}
			}
		return nLen;
		}	
	return 0;
}

HUINT	CBTCommand::HandleReadLocalDeviceName(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
	if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos)
	{
		HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		if(nLen == 2)
		{

		}	
		else 
		{
			if(pPacketDataBuffer->pDataBuffer[nPos] == '0' && pPacketDataBuffer->pDataBuffer[nPos+1] == ',')
			{
				HUINT nByesToCopy = nLen - 2;
				if(nByesToCopy >0 && m_pBTCommandData != NULL)
				{
					memset(m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.LocaLDeviceINFO.szDeviceName,0,sizeof(m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.LocaLDeviceINFO.szDeviceName));
					memcpy(m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.LocaLDeviceINFO.szDeviceName,pPacketDataBuffer->pDataBuffer + nPos + 2,nByesToCopy) ;
					m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.LocaLDeviceINFO.szDeviceName[nByesToCopy] = '\0';
#if SETBTNAME_MAC
					static char *pLocalName = new char[40];
					if(pLocalName != NULL && m_bMacGet)
					{
						memset(pLocalName,0,40);
						int nNameLen = sizeof("Zotye Audio");
						memcpy(pLocalName,"Zotye Audio",nNameLen);
						memcpy(pLocalName+nNameLen-1,m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.LocaLDeviceINFO.szMacAddress+8,4);
						if(CompareChar((HBYTE*)(m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.LocaLDeviceINFO.szDeviceName),(HBYTE*)(pLocalName),15) != 15)
						{
							HBYTE cCommand[50] = {0};
							HUINT nCmdlen = strlen("AT+SLDN=");
							strncpy((char*)cCommand,"AT+SLDN=",nCmdlen);
							strncpy((char*)(cCommand + nCmdlen),(char*)(pLocalName),15);
							nCmdlen += 15;
							strncpy((char*)cCommand + nCmdlen,"\r\n",2);
							nCmdlen += 2;
							BTDEBUGINFO(L"ChangeName:Zotye AudioXXXX");
							Block *pBlock = CCommandPool::Intance()->PoolNew();
							if(pBlock != NULL)
							{
								sCommandData* pt = (sCommandData*)(pBlock->Buf);
								memset(pt,0,sizeof(sCommandData));
								memcpy(pt->szCommand,cCommand,nCmdlen);
								pt->nCmdLen = nCmdlen;
								CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketSetLocalDeviceName,pBlock);
							}
						}
						/*HString strTemp;
						strTemp.append(strTire.c_str());
						strTemp.append(strWarning.c_str());
						HCRegSeting::SetRegValueStr(_T("SoftWare\\Hzcar\\App\\TPMS"), _T("TPMSWarning"), (LPBYTE)strTemp.c_str());*/
						WCHAR szTemp[100] = {0};
						WCHAR szTemp22[100] = {0};
						int ntotal = 0;
						ntotal = MultiByteToWideChar(CP_UTF8,0,(char*)pLocalName,-1,szTemp,30);
						szTemp[ntotal] =L'\0';
						HCRegSeting::SetRegValueStr(_T("SoftWare\\Hzcar\\App\\BT"), _T("BTNAME"), (LPBYTE)szTemp);
					/*	bool bRet = false;
						bRet = HCRegSeting::GetRegValueStr(_T("SoftWare\\Hzcar\\App\\BT"), _T("BTNAME"), (LPBYTE)szTemp22);
						if(bRet)
						{
							wprintf(L"GetRegValueStr::%s\r\n",szTemp22);
						}*/
						if(m_hWnd != NULL)
						{
							PostMessage(m_hWnd,WM_USER+27,0,0);
						}
					}
#else
					if(CompareChar((HBYTE*)(m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.LocaLDeviceINFO.szDeviceName),(HBYTE*)(m_pBTCommandData->BTGeneralData.ZotyeDeviceINFO.LocaLDeviceINFO.szDeviceName),15) != 15)
					{
						HBYTE cCommand[50] = {0};
						HUINT nCmdlen = strlen("AT+SLDN=");
						strncpy((char*)cCommand,"AT+SLDN=",nCmdlen);
						strncpy((char*)(cCommand + nCmdlen),(char*)(m_pBTCommandData->BTGeneralData.ZotyeDeviceINFO.LocaLDeviceINFO.szDeviceName),15);
						nCmdlen += 15;
						strncpy((char*)cCommand + nCmdlen,"\r\n",2);
						nCmdlen += 2;
						BTDEBUGINFO(L"ChangeName:Zotye AudioXXXX");
						Block *pBlock = CCommandPool::Intance()->PoolNew();
						if(pBlock != NULL)
						{
							sCommandData* pt = (sCommandData*)(pBlock->Buf);
							memset(pt,0,sizeof(sCommandData));
							memcpy(pt->szCommand,cCommand,nCmdlen);
							pt->nCmdLen = nCmdlen;
							CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketSetLocalDeviceName,pBlock);
						}

						//CBTCommand::Instance()->SendData(cCommand,nCmdlen);

					}	
#endif

				}
			}
		}
       return nLen;
	}
	return 0;
}
HUINT CBTCommand::HandleReadPairedCode(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
	if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos+1)
	{	  
		HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		if(nLen == 2)
		{
			//if(pPacketDataBuffer->pDataBuffer[nPos] ==' 1' && pPacketDataBuffer->pDataBuffer[nPos+1] == ',')
			//	;//cout<<"失败"<<endl;
		}
		else 
		{
			if(pPacketDataBuffer->pDataBuffer[nPos] == '0' && pPacketDataBuffer->pDataBuffer[nPos+1] == ',')
			{
				HUINT nByesToCopy = nLen - 2;
				if(nByesToCopy >0)
				{
					memset(m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.szPairCode,0,sizeof(m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.szPairCode));
					memcpy(m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.szPairCode,pPacketDataBuffer->pDataBuffer + nPos+2,nByesToCopy);
                    if(CompareChar(m_pBTCommandData->BTGeneralData.LoaclDeviceINFO.szPairCode,(HBYTE*)"0000",4) == 4)
					{
						BTDEBUGINFO(L"Code :0000");
					}
					else
					{
						HBYTE cCommand[50] = {0};
						HUINT nCmdlen = strlen("AT+SFPC=0000\r\n");
						strncpy((char*)cCommand,"AT+SLDN=0000\r\n",nCmdlen);
						BTDEBUGINFO(L"ChangeCode:0000");
#ifdef TESTBTCOMMANDQUEUE
						Block *pBlock = CCommandPool::Intance()->PoolNew();
						if(pBlock != NULL)
						{
							sCommandData* pt = (sCommandData*)(pBlock->Buf);
							memset(pt,0,sizeof(sCommandData));
							memcpy(pt->szCommand,cCommand,nCmdlen);
							pt->nCmdLen = nCmdlen;
							CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketSetLocalDeviceName,pBlock);
						}
#else
						CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
					}
					//HBYTE *pPairedCode = new HBYTE[nByesToCopy + 1];
					//memcpy(pPairedCode,pPacketDataBuffer->pDataBuffer + nPos+2,nByesToCopy);
					//pPairedCode[nByesToCopy] = '\0';
					//SAFE_DELETE_GROUP(pPairedCode);
				}
			}
		}
		return nLen;
	}	
	return 0;
}
HUINT CBTCommand::HandleGetGATT(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
	if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos)
	{
		HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		if(nLen == 1 )
		{
			switch (pPacketDataBuffer->pDataBuffer[nPos])
			{
			case '0':
				{
					//cout<<"设置成功"<<endl;
				}
				break;
			case '1':
				{
					//cout<<"失败"<<endl;
				}
				break;
			case '2':
				{
					//cout<<"参数不合法"<<endl;
				}
				break;
			case  '3':
				{
					//cout<<"未连接"<<endl;
				}
				break;
			default:
				break;
			}
		}

	return nLen;
	}
	return 0;
}
HUINT CBTCommand::HandleSetLocalDeviceName(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
	if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos)
	{
		HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		if(nLen == 1)
		{
			switch (pPacketDataBuffer->pDataBuffer[nPos])
			{
			case '0':
				{
					//cout<<"设置成功"<<endl;
				}
				break;
			case '1':
				{
					//cout<<"失败"<<endl;
				}
				break;
			case '2':
				{
					//cout<<"参数不合法"<<endl;
				}
				break;
			case  '3':
				{
					//cout<<"未连接"<<endl;
				}
				break;
			default:
				break;
			}
		}		
	return nLen;
	}
	return 0;
}

HUINT CBTCommand::HandleCurrentSPK(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)    //未完成
{
	if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos)
	{
		HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		if(nLen <= 2 && nLen >0)
		{
			m_pBTCommandData->BTGeneralData.nSPK = 0;
			for(int i= 0;i < nLen;i++)
			{
				m_pBTCommandData->BTGeneralData.nSPK = (10*m_pBTCommandData->BTGeneralData.nSPK);
				m_pBTCommandData->BTGeneralData.nSPK += (HUINT)(pPacketDataBuffer->pDataBuffer[nPos+i]-'0');
			}	
		}
		return nLen;
	}
	return 0;
}

HUINT CBTCommand::HandleSetPairCode(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
	if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos)
	{
		HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		if(nLen == 1)
		{
			switch (pPacketDataBuffer->pDataBuffer[nPos])
			{
			case '0':
				{	
					m_pBTCommandData->BTGeneralData.nPairState = 0;
					//cout<<"设置成功"<<endl;
				}
				break;
			case '1':
				{
					m_pBTCommandData->BTGeneralData.nPairState = 1;
					//cout<<"失败"<<endl;
				}
				break;
			case '2':
				{
					m_pBTCommandData->BTGeneralData.nPairState = 1;
					//cout<<"参数不合法"<<endl;
				}
				break;
			case  '3':
				{
					m_pBTCommandData->BTGeneralData.nPairState = 3;
					//cout<<"未连接"<<endl;
				}
				break;
			default:
				break;
			}	
		}
		return nLen;
	}
	return 0;
}

HUINT CBTCommand::HandleGetSPPState(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
	if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos)
	{
		HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		if(nLen == 1)
		{
			switch (pPacketDataBuffer->pDataBuffer[nPos])
			{
			case '0':
				{
					m_pBTCommandData->BTSPPData.nSPPState = 0;
					//cout<<"设置成功"<<endl;
				}
				break;
			case '1':
				{
					m_pBTCommandData->BTSPPData.nSPPState = 1;
					//cout<<"失败"<<endl;
				}
				break;
			case '2':
				{
					HBYTE cCommand  [50] = {0};
					HUINT nCmdlen =0;
					m_pBTCommandData->BTSPPData.nSPPState = 2;
					if(m_pBTCommandData->BTHIDData.nHIDState == 0)
					{
//#ifdef  TESTBTCOMMANDQUEUE
//						CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHIDConnectPhoneAndPCActive,NULL);
//#else
//						nCmdlen = strlen("AT+HIDCONN\r\n");
//						strncpy((char*)cCommand,"AT+HIDCONN\r\n",nCmdlen);
//						CBTCommand::Instance()->SendData(cCommand,nCmdlen);
//#endif
					}
					Sleep(1);
					memset(cCommand,0,sizeof(cCommand));
					strncpy((char*)cCommand,"SPP=4\r\n",nCmdlen);
					nCmdlen = strlen("SPP=4\r\n");
					cCommand[nCmdlen++] = 0x0a;
					cCommand[nCmdlen++] = 0x22;
					cCommand[nCmdlen++] = 0x00;
					cCommand[nCmdlen++] = 0x22;
#ifdef TESTBTCOMMANDQUEUE
					Block *pBlock = CCommandPool::Intance()->PoolNew();
					if(pBlock != NULL)
					{
						sCommandData* pt = (sCommandData*)(pBlock->Buf);
						memset(pt,0,sizeof(sCommandData));
						memcpy(pt->szCommand,cCommand,nCmdlen);
						pt->nCmdLen = nCmdlen;
						CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
					}
#else
					CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
					memset(cCommand,0,sizeof(cCommand));
					Sleep(1);
					strncpy((char*)cCommand,"SPP=4\r\n",nCmdlen);
					nCmdlen = strlen("SPP=4\r\n");
					cCommand[nCmdlen++] = 0x0a;
					cCommand[nCmdlen++] = 0x17;
					cCommand[nCmdlen++] = 0x00;
					cCommand[nCmdlen++] = 0x17;
#ifdef TESTBTCOMMANDQUEUE
					Block *pBlock1 = CCommandPool::Intance()->PoolNew();
					if(pBlock != NULL)
					{
						sCommandData* pt1 = (sCommandData*)(pBlock1->Buf);
						memset(pt1,0,sizeof(sCommandData));
						memcpy(pt1->szCommand,cCommand,nCmdlen);
						pt1->nCmdLen = nCmdlen;
						CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock1);
					}
#else
					CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
					memset(cCommand,0,sizeof(cCommand));
					Sleep(1);
					strncpy((char*)cCommand,"SPP=4\r\n",nCmdlen);
					nCmdlen = strlen("SPP=4\r\n");
					cCommand[nCmdlen++] = 0x0a;
					cCommand[nCmdlen++] = 0x02;
					cCommand[nCmdlen++] = 0x00;
					cCommand[nCmdlen++] = 0x02;
#ifdef TESTBTCOMMANDQUEUE
					Block *pBlock2 = CCommandPool::Intance()->PoolNew();
					if(pBlock != NULL)
					{
						sCommandData* pt2 = (sCommandData*)(pBlock2->Buf);
						memset(pt2,0,sizeof(sCommandData));
						memcpy(pt2->szCommand,cCommand,nCmdlen);
						pt2->nCmdLen = nCmdlen;
						CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock2);
					}
#else
					CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
				}
				break;
			case  '3':
				{
					m_pBTCommandData->BTSPPData.nSPPState = 3;
					//cout<<"未连接"<<endl;
				}
				break;
			default:
				break;
			}
			//::PostMessage(m_hWnd,WM_USER + 16,HINT(m_pBTCommandData->BTSPPData.nSPPState),NULL);
		}
		return nLen;
	}
	return 0;
}
HUINT CBTCommand::HandleConnectPhoneInitiative(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
	if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos)
	{
		HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		if(nLen == 1)
		{
			switch (pPacketDataBuffer->pDataBuffer[nPos])
			{
			case '0':
				{
					//cout<<"设置成功"<<endl;
				}
				break;
			case '1':
				{
					//cout<<"失败"<<endl;
				}
				break;
			case '2':
				{
					//cout<<"参数不合法"<<endl;
				}
				break;
			case  '3':
				{
					//cout<<"未连接"<<endl;
				}
				break;
			default:
				break;
			}	
		}
		return nLen;
	}
	return 0;
}
HUINT CBTCommand::HandleDisconnectHID(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
	if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos)
	{
		HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		if(nLen == 1)
		{
			switch (pPacketDataBuffer->pDataBuffer[nPos])
			{
			case '0':
				{
					//cout<<"设置成功"<<endl;
				}
				break;
			case '1':
				{
					//cout<<"失败"<<endl;
				}
				break;
			case '2':
				{
					//cout<<"参数不合法"<<endl;
				}
				break;
			case  '3':
				{
					//cout<<"未连接"<<endl;
				}
				break;
			default:
				break;
			}
		}
		return nLen;
	}
	return 0;
}

HUINT CBTCommand::HandleSPP(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
	if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos)
	{
		HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		if(nLen == 1)
		{
			switch (pPacketDataBuffer->pDataBuffer[nPos])
			{
			case '0':
				{
					//cout<<"设置成功"<<endl;
				}
				break;
			case '1':
				{
					//cout<<"失败"<<endl;
				}
				break;
			case '2':
				{
					//cout<<"参数不合法"<<endl;
				}
				break;
			case  '3':
				{
					//cout<<"为连接"<<endl;
				}
				break;
			default:
				break;
			}
		}
		return nLen;
	}
	return 0;
}

HUINT CBTCommand::HandleSendSPPData(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)//未完成
{
	return 0;
}

HUINT CBTCommand::HandleSTOP(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
	if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos)
	{
		HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		if(nLen == 1)
		{
			switch (pPacketDataBuffer->pDataBuffer[nPos])
			{
			case '0':
				{
					//cout<<"设置成功"<<endl;
				}
				break;
			case '1':
				{
					//cout<<"失败"<<endl;
				}
				break;
			case '2':
				{
					//cout<<"参数不合法"<<endl;
				}
				break;
			case  '3':
				{
					//cout<<"为连接"<<endl;
				}
				break;
			default:
				break;
			}
		}
	    return nLen;
	}
	return 0;
}
HUINT CBTCommand::HandelPairedLists(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
	if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos)
	{
		HBYTE  i = (pPacketDataBuffer->pDataBuffer[nPos] - '0');
		HUINT nLen = pPacketDataBuffer->nDatalen - nPos ;
		bool bIsConnected = false;
		if(nLen >= 3 )
		{
			if(pPacketDataBuffer->pDataBuffer[nPos] >= '0' && pPacketDataBuffer->pDataBuffer[nPos] < eMAXPAIRDEVICE+'0' && pPacketDataBuffer->pDataBuffer[nPos + 1] == ','  )
			{
				HUINT nBytesToCopy = 0;
				while(pPacketDataBuffer->pDataBuffer[nPos +2 + nBytesToCopy] != ',' )
				{
					
					nBytesToCopy ++;
				}
				//sDeviceINFO* pt= m_pDeviceINFO +(pPacketDataBuffer->pDataBuffer[nPos] - '0');
				if(nBytesToCopy > 0)
				{
					//BTDEBUGINFO(L"nBytesToCopy= %d",nBytesToCopy);
					memset(m_pBTCommandData->BTGeneralData.arrPairDevice[i].szMacAddress,0,sizeof(m_pBTCommandData->BTGeneralData.arrPairDevice[i].szMacAddress));
					memcpy(m_pBTCommandData->BTGeneralData.arrPairDevice[i].szMacAddress,pPacketDataBuffer->pDataBuffer+7,nBytesToCopy);
					if(strcmp((char*)(m_pBTCommandData->BTGeneralData.arrPairDevice[i].szMacAddress),(char*)(m_pBTCommandData->BTGeneralData.CurrentPairDevice.szMacAddress)) == 0)
					{
						bIsConnected = true;
					}
				//	memcpy(pt->cMacAddress,pPacketDataBuffer->pDataBuffer+2,nBytesToCopy);
					//pt->cMacAddress[nBytesToCopy +1] = '\0';
					m_pBTCommandData->BTGeneralData.arrPairDevice[i].szMacAddress[nBytesToCopy] = '\0';
				}
				HUINT nNameBytesToCopy = nLen -5 -nBytesToCopy;
				if(nNameBytesToCopy > 0)
				{
					//BTDEBUGINFO(L"nNameBytesToCopy= %d,nDatalen=%d",nNameBytesToCopy,pPacketDataBuffer->nDatalen);
					memset(m_pBTCommandData->BTGeneralData.arrPairDevice[i].szDeviceName,0,sizeof(m_pBTCommandData->BTGeneralData.arrPairDevice[i].szDeviceName));
					memcpy(m_pBTCommandData->BTGeneralData.arrPairDevice[i].szDeviceName,pPacketDataBuffer->pDataBuffer+pPacketDataBuffer->nDatalen-1-nNameBytesToCopy,nNameBytesToCopy);
					m_pBTCommandData->BTGeneralData.arrPairDevice[i].szDeviceName[nNameBytesToCopy] = '\0';
					if(bIsConnected == true)
					{
						memset(m_pBTCommandData->BTGeneralData.CurrentPairDevice.szDeviceName,0,sizeof(m_pBTCommandData->BTGeneralData.CurrentPairDevice.szDeviceName));
						memcpy(m_pBTCommandData->BTGeneralData.CurrentPairDevice.szDeviceName,m_pBTCommandData->BTGeneralData.arrPairDevice[i].szDeviceName,nNameBytesToCopy+1);
					}
					//memcpy(pt->cDeviceName,pPacketDataBuffer->pDataBuffer+2+ nBytesToCopy,nNameBytesToCopy);
				//	pt->cDeviceName[nNameBytesToCopy +1] = '\0';
				}
			}
		}
		return nLen;
	}
	return 0;
}

HUINT	CBTCommand::HandelPairedListsStart(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
	if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos)
	{
		HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		m_pBTCommandData->BTGeneralData.nTotalPairDevice = (HUINT)(pPacketDataBuffer->pDataBuffer[nPos]-'0');
		//cout<<"有"<<(int)(pPacketDataBuffer->pDataBuffer[nPos]-'0')<<"个配对设备"<<endl;
		return nLen;
	}
	return 0;
}
HUINT	CBTCommand::HandelPairedListsEnd(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
	if(NULL != m_hWnd)
	{
		::PostMessage(m_hWnd, WM_USER +1, NULL, NULL);
	}
//	(HCBTConnectionssettingDlg*)(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCONNECTSETTING))->AddPairedDevice();
	return 0;
}
HUINT CBTCommand::HandleDeletePairedDevices(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
	if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos)
	{
		HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		if(pPacketDataBuffer->pDataBuffer[nPos] == '0' && pPacketDataBuffer->pDataBuffer[nPos] == '1')
		{
			HUINT nBytesToCopy = nLen - 2;
			if(nBytesToCopy > 0)
			{
//				sDeviceINFO *pt = m_pDeviceINFO;
					if(CompareChar(pPacketDataBuffer->pDataBuffer + 2,(HBYTE*)"000000000000",12))
					{
						m_pBTCommandData->BTGeneralData.nTotalPairDevice = 0;
						for(HUINT i = 0;i < eMAXPAIRDEVICE;i++)
						{
							memset(m_pBTCommandData->BTGeneralData.arrPairDevice[i].szMacAddress,0,sizeof(m_pBTCommandData->BTGeneralData.arrPairDevice[i].szMacAddress));
							memset(m_pBTCommandData->BTGeneralData.arrPairDevice[i].szDeviceName,0,sizeof(m_pBTCommandData->BTGeneralData.arrPairDevice[i].szDeviceName));
							//	memset((pt+i)->cDeviceName,0,sizeof(m_pDeviceINFO->cDeviceName));
						//	memset((pt+i)->cMacAddress,0,sizeof(m_pDeviceINFO->cMacAddress));
						}
					}
					else
					{
						for(HUINT i = 0;i < eMAXPAIRDEVICE;i++)
						{	
							//if(CompareChar(pPacketDataBuffer->pDataBuffer + 2,(pt+i)->cMacAddress,nBytesToCopy))
							//{
								//memset((pt+i)->cDeviceName,0,sizeof(m_pDeviceINFO->cDeviceName));
								//memset((pt+i)->cMacAddress,0,sizeof(m_pDeviceINFO->cMacAddress));
						  //	}
						}
					}				
			}
		}
		return nLen;
	}	
	return 0;
}
 HUINT CBTCommand::HandleDisConnectCurrentDevice(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	 //::PostMessage(m_hWnd,WM_USER + 13,NULL,NULL);
	 return 0;
 }
 HUINT CBTCommand::HandleA2DPState(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 { 
	 if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos)
	 {
		 HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		 if(nLen >= 1)
		 {
			 switch (pPacketDataBuffer->pDataBuffer[nPos])
			 {
			 case '0':
				 {
					 m_pBTCommandData->BTAVRCPData.nA2DPState = 0;
					 m_pBTCommandData->BTAVRCPData.eAVRCPPlayState = eBTMUSICSTOP;
					// m_eA2DPState = eA2DPNOTCONNECT;	
				 }
				 break;
			 case '1':
				 {
					  m_pBTCommandData->BTAVRCPData.nA2DPState = 1;
					   m_pBTCommandData->BTAVRCPData.eAVRCPPlayState = eBTMUSICSTOP;
					// m_eA2DPState = eA2DPCONNECTTING;
				 }
				 break;
			 case '2':
				 {
					  m_pBTCommandData->BTAVRCPData.nA2DPState = 2;
					   m_pBTCommandData->BTAVRCPData.eAVRCPPlayState = eBTMUSICPAUSE;
					// m_eA2DPState = eA2DPCONNECTED;
				 }
				 break;
			 case  '3':
				 {
					  m_pBTCommandData->BTAVRCPData.nA2DPState = 3;
					   m_pBTCommandData->BTAVRCPData.eAVRCPPlayState = eBTMUSICPLAY;
					// m_eA2DPState = eA2DPPLAY;
				 }
				 break;
			 default:
				// m_eA2DPState = eA2DPUNKNOW;
				  m_pBTCommandData->BTAVRCPData.eAVRCPPlayState = eBTMUSICSTOP;
				 break;
			 }
		 }
		 ::PostMessage(m_hWnd,WM_USER +4,WPARAM(m_pBTCommandData->BTAVRCPData.eAVRCPPlayState),NULL);
		 return nLen;
	 }	 
	 return 0;
 }
 HUINT CBTCommand::HandleConnectA2DP(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	 if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos)
	 {
		 HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		 if(nLen >= 1)
		 {
			 switch (pPacketDataBuffer->pDataBuffer[nPos])
			 {
			 case '0':
				 {
					  m_pBTCommandData->BTAVRCPData.nA2DPState = 0;
					// m_eA2DPState = eA2DPNOTCONNECT;
					//cout<<"A2DP连接成功"<<endl;
				 }
				 break;
			 case '1':
				 {
					  m_pBTCommandData->BTAVRCPData.nA2DPState = 1;
					// m_eA2DPState = eA2DPCONNECTTING;
				 }
				 break;
			 case '2':
				 {
					  m_pBTCommandData->BTAVRCPData.nA2DPState = 2;
					// m_eA2DPState = eA2DPCONNECTED;
				 }
				 break;
			 case  '3':
				 {
					  m_pBTCommandData->BTAVRCPData.nA2DPState = 3;
					// m_eA2DPState = eA2DPPLAY
				 }
				 break;
			 default:
				// m_eA2DPState = eA2DPUNKNOW;
				 break;
			 }
		 }
		 return nLen;
	 } 
	 return 0;
 }
 HUINT CBTCommand::HandleDisconnectA2DP(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	return 0;
 }
 HUINT CBTCommand::HandleConnectAVRCP(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	 if(pPacketDataBuffer !=NULL && pPacketDataBuffer->nDatalen > nPos)
	 {
		 HUINT nLen = pPacketDataBuffer->nDatalen - nPos;
		 if(nLen >= 1)
		 {
			 switch (pPacketDataBuffer->pDataBuffer[nPos])
			 {
			 case '0':
				 {
//					 m_pBTCommandData->BTAVRCPData.eAVRCPPlayState = 0;
					 // m_eA2DPState = eA2DPNOTCONNECT;
					// cout<<"A2DP断开成功"<<endl;
				 }
				 break;
			 case '1':
				 {
					//  m_pBTCommandData->BTAVRCPData.nA2DPState = 1;
					 // m_eA2DPState = eA2DPCONNECTTING;
				 }
				 break;
			 case '2':
				 {
				//	  m_pBTCommandData->BTAVRCPData.nA2DPState = 2;
					 // m_eA2DPState = eA2DPCONNECTED;
				 }
				 break;
			 case  '3':
				 {
				//	  m_pBTCommandData->BTAVRCPData.nA2DPState = 3;
					 // m_eA2DPState = eA2DPPLAY
				 }
				 break;
			 default:
				 // m_eA2DPState = eA2DPUNKNOW;
				 break;
			 }
		 }
		 return nLen;
	 }
	 return 0;
 }
HBYTE CBTCommand::CalcChecksum(HBYTE *pBuffer,HUINT nLen)
{
	HBYTE cchecksum = 0;
	if(pBuffer != NULL && nLen > 0)
	{
		HBYTE *pBufferEnd = pBuffer +nLen;
		while(pBuffer != pBufferEnd)
		{
			cchecksum += *pBuffer;
			pBuffer++;
		}
		//cchecksum = (HBYTE)(0x100 - cchecksum);
	}
	return cchecksum;
}
HUINT CBTCommand::HandleSPPPhoneScreenInfo(sBTPacketDataBuffer *pPacketDataBuffer)
{
	if(pPacketDataBuffer != NULL && m_pPhoneInfo != NULL)
	{
		HBYTE *pt = pPacketDataBuffer->pDataBuffer;
		switch (pt[3])
		{
		case 0x01:
			{
				m_pPhoneInfo->PhoneScreen = eLANDSCAPE;
			}
			break;
		case 0x02:
			{
				m_pPhoneInfo->PhoneScreen = eVERTICAL;
			}
			break;
		default:
			break;
		}
	}
	return 0;
}
HUINT CBTCommand::HandleSPPPhoneKeyControl(sBTPacketDataBuffer *pPacketDataBuffer)
{
	if(pPacketDataBuffer->pDataBuffer != NULL)
	{
		switch (pPacketDataBuffer->pDataBuffer[3])
		{
		case 0x01:
			{
				if(pPacketDataBuffer->pDataBuffer[4] == 0x00)
				{
					HandleSPPHomeKeyUp();
				}
				else
				{
					if (pPacketDataBuffer->pDataBuffer[4] == 0x01)
					{
						HandleSPPHomeKeyDown();
					}			
				}
			}
			break;
		case 0x02:
			{
				if(pPacketDataBuffer->pDataBuffer[4] == 0x00)
				{
					HandleSPPMenuKeyUp();
				}
				else
				{
					if (pPacketDataBuffer->pDataBuffer[4] == 0x01)
					{
						HandleSPPMenuKeyDown();
					}			
				}
			}
			break;
		case 0x03:
			{
				if(pPacketDataBuffer->pDataBuffer[4] == 0x00)
				{
					HandleSPPBackKeyUp();
				}
				else
				{
					if (pPacketDataBuffer->pDataBuffer[4] == 0x01)
					{
						HandleSPPBackKeyDown();
					}			
				}
			}
			break;
		case 0x04:
			{
				if(pPacketDataBuffer->pDataBuffer[4] == 0x00)
				{
					HandleSPPNextKeyUp();
				}
				else
				{
					if (pPacketDataBuffer->pDataBuffer[4] == 0x01)
					{
						HandleSPPNextKeyDown();
					}			
				}
			}
			break;
		case 0x05:
			{
				if(pPacketDataBuffer->pDataBuffer[4] == 0x00)
				{
					HandleSPPPreviousKeyUp();
				}
				else
				{
					if (pPacketDataBuffer->pDataBuffer[4] == 0x01)
					{
						HandleSPPPreviousKeyDown();
					}			
				}
			}
			break;
		}
	}
	return 0;
}
HUINT CBTCommand::HandleSPPPhoneTouchEvents(sBTPacketDataBuffer *pPacketDataBuffer)
{	
	return 0;
}
HUINT CBTCommand::HandleSPPPhoneSystemInfo(sBTPacketDataBuffer *pPacketDataBuffer)
{
	if(pPacketDataBuffer != NULL)
	{
		HBYTE *pt = pPacketDataBuffer->pDataBuffer;
		if(pPacketDataBuffer != NULL && pt[2] == 0x04 && m_pPhoneInfo != NULL)
		{
			if(pt[3] == 0x01)
			{
				m_pPhoneInfo->PhoneSysInfo.eType = eANDRIOD;
			}
			else if(pt[3] == 0x02)
			{
				m_pPhoneInfo->PhoneSysInfo.eType = eIOS;
			}
			HBYTE cTemp[10] = {0};
			cTemp[0] = pt[4] +'0';
			cTemp[1] = pt[5] +'0';
			cTemp[2] = pt[6] +'0';
			memset(m_pPhoneInfo->PhoneSysInfo.cSystem,0,sizeof(m_pPhoneInfo->PhoneSysInfo.cSystem));
			m_pPhoneInfo->PhoneSysInfo.cSystem[1] = m_pSystemInfo->cSystem[3] ='.';
			m_pPhoneInfo->PhoneSysInfo.cSystem[0] = cTemp[0];
			m_pPhoneInfo->PhoneSysInfo.cSystem[2] = cTemp[1];
			m_pPhoneInfo->PhoneSysInfo.cSystem[4] = cTemp[2];
			m_pPhoneInfo->PhoneSysInfo.cSystem[5] = '\0';
		}
	}
	return 0;
}
HUINT CBTCommand::HandleSPPPhoneStreachScreen(sBTPacketDataBuffer *pPacketDataBuffer)
{
	return 0;
}
HUINT CBTCommand::HandleSPPPhoneDPI(sBTPacketDataBuffer *pPacketDataBuffer)
{
	if(pPacketDataBuffer != NULL && (pPacketDataBuffer->pDataBuffer)[2] == 0x04 && m_pPhoneInfo != NULL)
	{
		HBYTE *pt = ((pPacketDataBuffer->pDataBuffer) + 3);
		HINT nValue = 0;
	    if(pt != NULL)
		{
			nValue =((*pt)<<8) + (*(pt+1));
			m_pPhoneInfo->PhoneWidth = nValue;
			nValue = 0;
			nValue = (*(pt +2)<<8) + *(pt+3);
			m_pPhoneInfo->PhoneHight = nValue;
			GetAvailableArea(SCREEN_WIDTH,SCREEN_HEIGHT,m_pPhoneInfo->PhoneWidth,m_pPhoneInfo->PhoneHight);
			GetMaxCeAviablex(m_pPhoneInfo->iAvailableCeWidth);
			GetMinCeAviablex(m_pPhoneInfo->iAvailableCeWidth);
			GetMaxCeAviabley(m_pPhoneInfo->iAvailableCeHight);
			GetMinCeAviabley(m_pPhoneInfo->iAvailableCeHight);
		}
		BTDEBUGINFO(L"PhoneInfo:W = %d,H = %d,AvailableCeWidth = %d,iAvailableCeHight = %d,iMaxAvailableCeWidth = %d,iMaxAvailableCeHight = %d,iMinAvailableCeWidth = %d,iMinAvailableCeHight = %d",m_pPhoneInfo->PhoneWidth,m_pPhoneInfo->PhoneHight,m_pPhoneInfo->iAvailableCeWidth,m_pPhoneInfo->iAvailableCeHight,m_pPhoneInfo->iMaxAvailableCeWidth,m_pPhoneInfo->iMaxAvailableCeHight,m_pPhoneInfo->iMinAvailableCeWidth,m_pPhoneInfo->iMinAvailableCeHight);
		if(m_pPhoneInfo->PhoneWidth > 0 && m_pPhoneInfo->PhoneHight > 0 && m_pBTCommandData->BTHIDData.nHIDState == 2)
		{
			m_bMyPhoneInfoCleared = false;
			::PostMessage(m_hWnd,WM_USER + 18,NULL,NULL);//获取手机分辨率
		}
	}
	/*HBYTE cCommand[50] = {0};
	HINT nlen = strlen("AT+HIDHOME=");
	strncpy((char*)cCommand,"AT+HIDHOME=",nlen);
	cCommand[nlen++] = LOBYTE(3000);
	cCommand[nlen++] = HIBYTE(3000);
	cCommand[nlen++] = ',';
	cCommand[nlen++] = LOBYTE(2500);
	cCommand[nlen++] = HIBYTE(2500);
	cCommand[nlen++] = '\r';
	cCommand[nlen++] = '\n';*/
	HBYTE cCommand[50] = {0};
	HINT nlen = strlen("AT+HIDHOME=");
	strncpy((char*)cCommand,"AT+HIDHOME=",nlen);
	int nHomex = 2*m_pPhoneInfo->PhoneWidth;
	int nHomey = 2*m_pPhoneInfo->PhoneHight;
	//cCommand[nlen++] = LOBYTE(3000);
	//cCommand[nlen++] = HIBYTE(3000);
	cCommand[nlen++] = HIBYTE(nHomex);
	cCommand[nlen++] = LOBYTE(nHomex);
	cCommand[nlen++] = ',';
	cCommand[nlen++] = HIBYTE(nHomey);
	cCommand[nlen++] = LOBYTE(nHomey);
	//cCommand[nlen++] = LOBYTE(2500);
	//cCommand[nlen++] = HIBYTE(2500);
	cCommand[nlen++] = '\r';
	cCommand[nlen++] = '\n';
#ifdef TESTBTCOMMANDQUEUE
	Block *pBlock = CCommandPool::Intance()->PoolNew();
	if(pBlock != NULL)
	{
		sCommandData* pt = (sCommandData*)(pBlock->Buf);
		memset(pt,0,sizeof(sCommandData));
		memcpy(pt->szCommand,cCommand,nlen);
		pt->nCmdLen = nlen;
		CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHIDCUSendDataToHID,pBlock);
	}
#else
	CBTCommand::Instance()->SendData(cCommand,nlen);
#endif
	return 0;
}
HUINT CBTCommand::HandleSPPPhoneHIDConnectState(sBTPacketDataBuffer *pPacketDataBuffer)
{
	if(pPacketDataBuffer != NULL)
	{
		HBYTE *pt = pPacketDataBuffer->pDataBuffer;
		if(pt != NULL && pt[2] == 0x00)
		{
			HBYTE cCommand[50] = {0};
			HUINT nCmdlen = strlen("SPP=5\r\n");
			strncpy((char*)cCommand,"SPP=5\r\n",nCmdlen);
			cCommand[nCmdlen++] = 0x0a;
			cCommand[nCmdlen++] = 0x23;
			cCommand[nCmdlen++] = 0x01;
			if(m_pBTCommandData->BTHIDData.nHIDState == 0 && m_pBTCommandData->BTHIDData.nHIDState == 1)
			{
				cCommand[nCmdlen++] = 0x02;
			}
			else if(m_pBTCommandData->BTHIDData.nHIDState == 2)
			{
				cCommand[nCmdlen++] = 0x01;
			}
			cCommand[nCmdlen++] = 0x25;
#ifdef TESTBTCOMMANDQUEUE
			Block *pBlock = CCommandPool::Intance()->PoolNew();
			if(pBlock != NULL)
			{
				sCommandData* pt = (sCommandData*)(pBlock->Buf);
				memset(pt,0,sizeof(sCommandData));
				memcpy(pt->szCommand,cCommand,nCmdlen);
				pt->nCmdLen = nCmdlen;
				CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
			}
#else
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
		}
	}
	return 0;
}
HUINT CBTCommand::HandleSPPPhoneEnableBackAndMenu(sBTPacketDataBuffer *pPacketDataBuffer)
{
	if(pPacketDataBuffer != NULL)
	{
		HBYTE *pt = pPacketDataBuffer->pDataBuffer;
		if(pt != NULL && pt[2] == 0x01 && m_pPhoneInfo != NULL)
		{
			if(pt[3] == 0x01)
			{
				m_pPhoneInfo->bEnableHomeBackKey = true;
			}
			else
			{
				m_pPhoneInfo->bEnableHomeBackKey = false;
			}
		}
	}
	return 0;
}
HUINT CBTCommand::HandleSPPPhoneLockInfo(sBTPacketDataBuffer *pPacketDataBuffer)
{
   	if(pPacketDataBuffer != NULL && (pPacketDataBuffer->pDataBuffer)[2] == 0x01 && m_pPhoneInfo != NULL)
	{
		if((pPacketDataBuffer->pDataBuffer)[3] == 0x01)
		{
			m_pPhoneInfo->bPhoneLocked = true;
		}
		else
		{
			m_pPhoneInfo->bPhoneLocked = false;
		}
	}
	return 0;
}
HUINT CBTCommand::HandleSPPPhoneTime(sBTPacketDataBuffer *pPacketDataBuffer)
{
	HBYTE *pt = pPacketDataBuffer->pDataBuffer;
	if(pt != NULL && pt[2] == 0x06 && m_pPhoneInfo != NULL)
	{
		memset(m_pPhoneInfo->PhoneTime,0,sizeof(m_pPhoneInfo->PhoneTime));
		m_pPhoneInfo->PhoneTime[0] = '2';
		m_pPhoneInfo->PhoneTime[1] = '0';
		m_pPhoneInfo->PhoneTime[2] = pt[3]/10 +'0';
		m_pPhoneInfo->PhoneTime[3] = pt[3]%10 +'0';
		m_pPhoneInfo->PhoneTime[4] = pt[4]/10 +'0';
		m_pPhoneInfo->PhoneTime[5] = pt[4]%10 +'0';
		m_pPhoneInfo->PhoneTime[6] = pt[5]/10 +'0';
		m_pPhoneInfo->PhoneTime[7] = pt[5]%10 +'0';
		m_pPhoneInfo->PhoneTime[8] = pt[6]/10 +'0';
		m_pPhoneInfo->PhoneTime[9] = pt[6]%10 +'0';
		m_pPhoneInfo->PhoneTime[10] = pt[7]/10 +'0';
		m_pPhoneInfo->PhoneTime[11] = pt[7]%10 +'0';
		m_pPhoneInfo->PhoneTime[12] = pt[8]/10 +'0';
		m_pPhoneInfo->PhoneTime[13] = pt[8]%10 +'0';
	}
	return 0;
}
HUINT CBTCommand::HandleSPPDAParaPacket(sBTPacketDataBuffer *pPacketDataBuffer)
{
	return 0;
}
HUINT CBTCommand::HandleSPPRunState(sBTPacketDataBuffer *pPacketDataBuffer)
{
	return 0;
}
HUINT CBTCommand::HandleSPPHomeKeyUp(void)
{
	return 0;
}
HUINT CBTCommand::HandleSPPHomeKeyDown(void)
{
	return 0;
}
HUINT CBTCommand::HandleSPPMenuKeyUp(void)
{
	return 0;
}
HUINT CBTCommand::HandleSPPMenuKeyDown(void)
{
	return 0;
}
HUINT CBTCommand::HandleSPPBackKeyUp(void)
{
	return 0;
}
HUINT CBTCommand::HandleSPPBackKeyDown(void)
{
	return 0;
}
HUINT CBTCommand::HandleSPPNextKeyUp(void)
{
	return 0;
}
HUINT CBTCommand::HandleSPPNextKeyDown(void)
{
	return 0;
}
HUINT CBTCommand::HandleSPPPreviousKeyUp(void)
{
	return 0;
}
HUINT CBTCommand::HandleSPPPreviousKeyDown(void)
{
	return  0;
}

HUINT  CBTCommand::HandleErrorData(sBTPacketDataBuffer *pPacketDataBuffer)
{
	BTDEBUGINFO(L"UnKnow Type Data");
	return 0;
}
HUINT CBTCommand::HandlePBDNEND(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
//	sBTCommandData* p = GetBTCommandData();
	if(pPacketDataBuffer != NULL && nPos > 0)
	{
		//if( p->PBAPCData.ePBAPCState == ePBAPCSTATEDOWNINGBOOK)
	//	{
		switch (m_ePBAPCState)
		{
			case ePBAPCSTATEDOWNINGBOOK:
			{
				BTDEBUGINFO(L"联系人下载结束");
				memset(m_pRestPBDNData->szData,0,sizeof(m_pRestPBDNData->szData));
				m_pRestPBDNData->nDataLen = 0;
			//	::PostMessage(m_hWnd, WM_USER +2, NULL, NULL);
				HBYTE cCommand  [20] = {0};
				Sleep(20);
				m_bBookDataBeCleared = false;
				//m_ePBAPCState = ePBAPCSTATEDOWNINGINCOMMINGCALL;
				m_ePBAPCState = ePBAPCSTATEDOWNINGMISSEDCALL;
				HUINT nCmdlen = strlen("AT+PBDOWN=4\r\n");
				strncpy((char*)cCommand,"AT+PBDOWN=4\r\n",nCmdlen);
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock = CCommandPool::Intance()->PoolNew();
				if(pBlock != NULL)
				{
					sCommandData* pt = (sCommandData*)(pBlock->Buf);
					memset(pt,0,sizeof(sCommandData));
					memcpy(pt->szCommand,cCommand,nCmdlen);
					pt->nCmdLen = nCmdlen;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
			//	
			}
			break;
			case ePBAPCSTATEDOWNINGINCOMMINGCALL:
			{
				BTDEBUGINFO(L"来电记录下载结束");
				m_bBookDataBeCleared = false;
				memset(m_pRestPBDNData->szData,0,sizeof(m_pRestPBDNData->szData));
				m_pRestPBDNData->nDataLen = 0;
				HBYTE cCommand  [20] = {0};
				Sleep(25);
				HUINT nCmdlen = strlen("AT+PBDOWN=3\r\n");
				strncpy((char*)cCommand,"AT+PBDOWN=3\r\n",nCmdlen);
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock1 = CCommandPool::Intance()->PoolNew();
				if(pBlock1 != NULL)
				{
					sCommandData* pt1 = (sCommandData*)(pBlock1->Buf);
					memset(pt1,0,sizeof(sCommandData));
					memcpy(pt1->szCommand,cCommand,nCmdlen);
					pt1->nCmdLen = nCmdlen;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock1);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
				m_ePBAPCState = ePBAPCSTATEDOWNINGOUTGOINGCALL;
				//m_ePBAPCState = ePBAPCSTATEDOWNINGMISSEDCALL;
			}
			break;
			case ePBAPCSTATEDOWNINGOUTGOINGCALL:
			{
				BTDEBUGINFO(L"去电记录下载结束");
				m_bBookDataBeCleared = false;
				memset(m_pRestPBDNData->szData,0,sizeof(m_pRestPBDNData->szData));
				m_pRestPBDNData->nDataLen = 0;
				HBYTE cCommand  [20] = {0};
				Sleep(25);
				HUINT nCmdlen = strlen("AT+PBDOWN=5\r\n");
				strncpy((char*)cCommand,"AT+PBDOWN=5\r\n",nCmdlen);
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock2 = CCommandPool::Intance()->PoolNew();
				if(pBlock2 != NULL)
				{
					sCommandData* pt2 = (sCommandData*)(pBlock2->Buf);
					memset(pt2,0,sizeof(sCommandData));
					memcpy(pt2->szCommand,cCommand,nCmdlen);
					pt2->nCmdLen = nCmdlen;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock2);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
				//m_ePBAPCState = ePBAPCSTATEDOWNINGMISSEDCALL;
				m_ePBAPCState = ePBAPCSTATEDOWNINGCALLHISTORY;
			}
			break;
			case ePBAPCSTATEDOWNINGMISSEDCALL:
			{
				BTDEBUGINFO(L"未接电话下载结束");
				m_bBookDataBeCleared = false;
				memset(m_pRestPBDNData->szData,0,sizeof(m_pRestPBDNData->szData));
				m_pRestPBDNData->nDataLen = 0;
				HBYTE cCommand  [20] = {0};
				Sleep(25);
				HUINT nCmdlen = strlen("AT+PBDOWN=5\r\n");
				strncpy((char*)cCommand,"AT+PBDOWN=5\r\n",nCmdlen);
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock3 = CCommandPool::Intance()->PoolNew();
				if(pBlock3 != NULL)
				{
					sCommandData* pt3 = (sCommandData*)(pBlock3->Buf);
					memset(pt3,0,sizeof(sCommandData));
					memcpy(pt3->szCommand,cCommand,nCmdlen);
					pt3->nCmdLen = nCmdlen;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock3);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
				m_ePBAPCState = ePBAPCSTATEDOWNINGCALLHISTORY;
			}
			break;
			case ePBAPCSTATEDOWNINGCALLHISTORY:
			{
				BTDEBUGINFO(L"所有电话下载结束");
				m_bBookDataBeCleared = false;
				memset(m_pRestPBDNData->szData,0,sizeof(m_pRestPBDNData->szData));
				m_pRestPBDNData->nDataLen = 0;
				HBYTE cCommand  [20] = {0};
				::PostMessage(m_hWnd, WM_USER +2, NULL, NULL);
				Sleep(20);
				::PostMessage(m_hWnd,WM_USER + 7,NULL,NULL);
				Sleep(20);
				HUINT nCmdlen = strlen("AT+PBDISC\r\n");
				strncpy((char*)cCommand,"AT+PBDISC\r\n",nCmdlen);
#ifdef  TESTBTCOMMANDQUEUE
				CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketPBAPCDisconnectPBAP,NULL);
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
				m_ePBAPCState = m_pBTCommandData->PBAPCData.ePBAPCState;
				//m_ePBAPCState = ePBAPCSTATEUNKNOW
			}
			break;
			default:
			{
			}
			break;
		}	
		//}
		/*HBYTE cCommand  [20] = {0};
		HUINT nCmdlen = strlen("AT+PBDISC\r\n");
		strncpy((char*)cCommand,"AT+PBDISC\r\n",nCmdlen);
		CBTCommand::Instance()->SendData(cCommand,nCmdlen);*/
	}
	return 0;
}
void CBTCommand::SendCommand(queue<sCommamdItem*> queCommand)
{
	while(1)
	{
		WaitForSingleObject(m_eveCMDQUE,INFINITE);
		while(!queCommand.empty())
		{
			if(queCommand.front()->nSend < 3 )
			{

				CBTCommand::Instance()->SendData(queCommand.front()->cCommand,strlen((char*)queCommand.front()->cCommand));
				//ResetEvent(m_eveCommand);
				DWORD result = WaitForSingleObject(m_eveCommand,1000);
				if(result == WAIT_TIMEOUT)
				{
					queCommand.front()->nSend++;
				
					//queCommand.front().nProtuceTime = GetTickCount();
				}
				else
				{
					DeleteCommandItem(queCommand);
					//WaitForSingleObject(m_semCommand,INFINITE);
				}
			}
			else
			{
				DeleteCommandItem(queCommand);
				//WaitForSingleObject(m_semCommand,INFINITE);
			}
		}
	}
}
 void CBTCommand::AddCommand(sCommamdItem* pItem,queue<sCommamdItem*> queCommand)
 {
	 EnterCriticalSection(&m_crsCommand);
	 queCommand.push(pItem);
	 LeaveCriticalSection(&m_crsCommand);
	 SetEvent(m_eveCMDQUE);
 }

 HINT CBTCommand::FindContactPhoneNum(HBYTE *pBeg,HBYTE *pEnd,sContact* pContact)
 {
	 int i = 0;
	 if(pBeg != NULL && pEnd != NULL && pContact != NULL && pBeg < pEnd)
	 {
		 HBYTE *pt = pBeg;
		 HBYTE *pNumBeg = pBeg;
		 do 
		 {
			 pt =(HBYTE*)strstr((char*)pNumBeg,"TEL;");
			 if(pt == NULL)
			 {
                   pt =(HBYTE*)strstr((char*)pNumBeg,"TEL");
			 }
			 if(pt != NULL)
			 {
				 while(pt != NULL && pt <= pEnd && (*pt) != ':')
				 {
					 pt++;
				 }
				 HBYTE *pPhoneNumBeg = pt+1;
				 //HBYTE *pPhoneNumend = NULL;
				 if(pt != NULL)
				 {
					 while((pt +1) <= pEnd && (*pt !='\r') && (*(pt+1) !='\n'))
					 {
						 pt++;
					 }
				 }
				 if(pt < pEnd)
				 {
					 HUINT nlen = pt - pPhoneNumBeg ;
					// BTDEBUGINFO(L"nlen = %d",nlen);
					 HBYTE szTxt[30] = {0};
					 HUINT ii = 0;
					 HUINT j = 0 ;
					 for( ii = 0,j = 0 ; j < nlen ;j++)
					 {
						// if(pPhoneNumBeg[j] != '-')
						 if(pPhoneNumBeg[j] != '-' && pPhoneNumBeg[j] != ' ')//去除空格和-
						 {
							 if(ii < 29)
							 {
								 szTxt[ii] = pPhoneNumBeg[j];
								 ii++;
							 }
							
						 }
					 }
					 //sBTCommandData *pData= new sBTCommandData;
					 if(nlen <30  && pContact !=NULL && nlen >0)
					 {
						 bool bLegal = IsNumberLegal(szTxt,ii);
						 memset((pContact+i)->szTelNumber.PhoneNumber,0,sizeof((pContact + i)->szTelNumber.PhoneNumber));
						 if(bLegal)
						 {
							 MultiByteToWideChar(CP_ACP,0,(char*)szTxt,-1,(pContact + i)->szTelNumber.PhoneNumber,ii);
						 }
						 else
						 {
							 swprintf_s((pContact+i)->szTelNumber.PhoneNumber,10,L"%s",L"< 未知号码>");
						 }
						 i++;
					 }
					 pNumBeg = pt +2;
				 }
				 else
				 {
					 return i;
				 }
			 }
		 } while (pNumBeg < pEnd  && pNumBeg != NULL && pt != NULL /*&& (m_pBTCommandData->PBAPCData.sPBAPCPhoneBook.nTotalContact + i) < 400*/);
	 }
	 return i;
 }
 bool CBTCommand::FindContactname(HBYTE *pBeg,HBYTE *pEnd,sContact* pContact)
 {
	 if(pBeg != NULL && pEnd != NULL && pContact != NULL && pBeg < pEnd)
	 {
		 HBYTE *pt =(HBYTE*)strstr((char*)pBeg,"\r\nFN");
		 if(pt == NULL)
		 {
			pt =(HBYTE*)strstr((char*)pBeg,"\r\nN;");
		 }
		 if(pt != NULL)
		 {
			 HBYTE *pEncoding = (HBYTE*)strstr((char*)pBeg,"ENCODING=QUOTED-PRINTABLE");
			 while(pt != NULL && pt <= pEnd && (*pt) != ':')
			 {
				 pt++;
			 }
			 HBYTE *pNameBeg = pt+1;
			 if(pt != NULL)
			 {
				 while((pt +1) <= pEnd && (*pt !='\r') && (*(pt+1) !='\n'))
				 {
					 pt++;
				 }
			 }
			 if(pt < pEnd)
			 {
				 HINT nlen = pt - pNameBeg;
				 HBYTE *ptemp = pNameBeg; 
				 if(nlen >= 0 && nlen <30  && pContact !=NULL && pEncoding == NULL)
				 {
					 HBYTE szPhoneName[20] = {0};
					 HUINT i = 0;
					 for(int n = 0;(n < nlen) && (n< 19);n++)
					 {
						 if((*ptemp) != ';')
						 {
							 szPhoneName[i++] = *ptemp;
						 }
						 ptemp++;
					 }
					 szPhoneName[i++] ='\0';
					 memset(pContact->szName,0,sizeof(pContact->szName));
					 if(nlen > 0)
					 {
						 int ntotal =MultiByteToWideChar(CP_UTF8,0,(char*)szPhoneName,-1,pContact->szName,10);
						 if(ntotal>0 && ntotal<10)
							 pContact->szName[ntotal]=L'\0';
						 pContact->szName[10] = L'\0';
					 }
					 return true;
				 }
				 else if (nlen >= 0 && nlen < 200  && pContact !=NULL && pEncoding != NULL)
				 {
					 HBYTE szPhoneName[90] = {0};
					 HUINT i = 0;
					 for(int n = 0;(n < nlen)&&(n< 89);n++)
					 {
						 if((*ptemp) != ';' )
						 {
							 szPhoneName[i++] = *ptemp;
						 }
						 ptemp++;
					 }
					 char cName[10] =  {0};
					  memset(pContact->szName,0,sizeof(pContact->szName));
					  if(nlen > 0)
					  {
						  DecodeQuoted((char*)szPhoneName,cName,i);
						  int ntotal =MultiByteToWideChar(CP_UTF8,0,(char*)cName,-1,pContact->szName,10);
						  if(ntotal>0 && ntotal<10)
							  pContact->szName[ntotal]=L'\0';
						  pContact->szName[9] = L'\0';
						  BTDEBUGINFO(L"name:%s",pContact->szName);
					  }
					 return true;
				 }
				 else
				 {
					 return false;
				 }

			 }
			 else
			 {
				 return false;
			 }
		 }
	 }
	 return false;
 }
 int CBTCommand::DecodeQuoted(const char* pSrc,  char* pDst, int nSrcLen) 
 { 
	 int nDstLen; // 输出的字符计数 
	 int i; 

	 i = 0; 
	 nDstLen = 0; 

	 while (i < nSrcLen) 
	 { 
		 if (strncmp(pSrc, "=\r\n ", 3) == 0) // 软回车，跳过 
		 { 
			 pSrc += 3; 
			 i += 3; 
		 } 
		 else 
		 { 
			 if (*pSrc == '=') // 是编码字节 
			 { 
				 sscanf(pSrc, "=%02X ", pDst); 
				 //    wcout<<*((HCHAR*)pDst);
				 pDst++; 
				 pSrc += 3; 
				 i += 3; 
			 } 
			 else // 非编码字节 
			 { 
				 *pDst++ = (unsigned char)*pSrc++; 
				 i++; 
			 } 

			 nDstLen++; 
		 } 
	 } 
	 // 输出加个结束符 
	 *pDst = '\0 '; 
	 return nDstLen; 
 } 
sCommamdItem* CBTCommand::CreatCommandItem(HBYTE *cCMD,HUINT nlen)
{
	if(cCMD != NULL && nlen > 0 && nlen < eMAXCMDLEN)
	{
		sCommamdItem *p = new sCommamdItem;
		memset(p->cCommand,0,sizeof(p->cCommand));
		memcpy(p->cCommand,cCMD,nlen);
		p->nCommendLen = nlen;
		p->nProtuceTime = GetTickCount();
		p->nSend = 0;
		p->nSendTime = p->nProtuceTime; 
		return p;
	}
	else 
	{
		return FALSE;
	}	
}
HINT CBTCommand::DownAddressBook()
{
	HBYTE cCommand  [50] = {0};
	HUINT nCmdlen = strlen("AT+PBCONN\r\n");
	strncpy((char*)cCommand,"AT+PBCONN\r\n",nCmdlen);
	//CBTCommand::Instance()->SendData(cCommand,nCmdlen);
	sCommamdItem* pItem = CreatCommandItem(cCommand,nCmdlen);
	AddCommand(pItem,m_quepCommand);
	DWORD rel= WaitForSingleObject(m_eveReadyToDown,10000);
	if(rel == WAIT_TIMEOUT)
	{
		AddDisPBDACommand(m_quepCommand);
		return 1;
	}
	else
	{
		memset(cCommand,0,sizeof(cCommand));
		nCmdlen = strlen("AT+PBDOWN=1\r\n");
		strncpy((char*)cCommand,"AT+PBDOWN=1\r\n",nCmdlen);
		pItem = CreatCommandItem(cCommand,nCmdlen);
		AddCommand(pItem,m_quepCommand);
		rel = WaitForSingleObject(m_eveDownComplete,40000);
		{
			if(rel == WAIT_TIMEOUT)
			{
				AddDisPBDACommand(m_quepCommand);
				return 2;
			}
			else
			{
				memset(cCommand,0,sizeof(cCommand));
				nCmdlen = strlen("AT+PBDOWN=2\r\n");
				strncpy((char*)cCommand,"AT+PBDOWN=2\r\n",nCmdlen);
				pItem = CreatCommandItem(cCommand,nCmdlen);
				AddCommand(pItem,m_quepCommand);
				rel = WaitForSingleObject(m_eveDownComplete,40000);
				{
					if(rel == WAIT_TIMEOUT)
					{
						AddDisPBDACommand(m_quepCommand);
						return 3;
					}
					else
					{
						memset(cCommand,0,sizeof(cCommand));
						nCmdlen = strlen("AT+PBDOWN=3\r\n");
						strncpy((char*)cCommand,"AT+PBDOWN=3\r\n",nCmdlen);
						pItem = CreatCommandItem(cCommand,nCmdlen);
						AddCommand(pItem,m_quepCommand);
						rel = WaitForSingleObject(m_eveDownComplete,40000);
						{
							if(rel == WAIT_TIMEOUT)
							{
								AddDisPBDACommand(m_quepCommand);
								return 4;
							}
							else
							{
								memset(cCommand,0,sizeof(cCommand));
								nCmdlen = strlen("AT+PBDOWN=4\r\n");
								strncpy((char*)cCommand,"AT+PBDOWN=4\r\n",nCmdlen);
								pItem = CreatCommandItem(cCommand,nCmdlen);
								AddCommand(pItem,m_quepCommand);
								rel = WaitForSingleObject(m_eveDownComplete,40000);
								{
									if(rel == WAIT_TIMEOUT)
									{
										AddDisPBDACommand(m_quepCommand);
										return 5;
									}
									else
									{
										memset(cCommand,0,sizeof(cCommand));
										nCmdlen = strlen("AT+PBDOWN=5\r\n");
										strncpy((char*)cCommand,"AT+PBDOWN=5\r\n",nCmdlen);
										pItem = CreatCommandItem(cCommand,nCmdlen);
										AddCommand(pItem,m_quepCommand);
										rel = WaitForSingleObject(m_eveDownComplete,40000);
										if(rel ==WAIT_TIMEOUT)
										{
											AddDisPBDACommand(m_quepCommand);
											return 5;
										}
										else
										{
											return 0;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void CBTCommand::AddDisPBDACommand(queue<sCommamdItem*> queCommand)
{
	HBYTE cCommand  [50] = {0};
	HUINT nCmdlen = strlen("AT+PBDISC\r\n");
	strncpy((char*)cCommand,"AT+PBDISC\r\n",nCmdlen);
	//CBTCommand::Instance()->SendData(cCommand,nCmdlen);
	sCommamdItem* pItem = CreatCommandItem(cCommand,nCmdlen);
	AddCommand(pItem,queCommand);
}
 bool CBTCommand::DeleteCommandItem(queue<sCommamdItem*> queCommand)
 {
	if(!queCommand.empty())
	{
		EnterCriticalSection(&m_crsCommand);
		sCommamdItem* pTem = queCommand.front();
		if(pTem != NULL)
		{
			queCommand.pop();
			SAFE_DELETE(pTem);
		}
		LeaveCriticalSection(&m_crsCommand);
		return true;
	}
	return false;
 }
 HUINT CBTCommand::HandlePBState(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	 if(pPacketDataBuffer != NULL && nPos > 0)
	 {
		 sBTCommandData* p = GetBTCommandData();
		 if(p != NULL && pPacketDataBuffer->pDataBuffer[nPos] >='0' && pPacketDataBuffer->pDataBuffer[nPos] <='9' )
		 {
			 switch (pPacketDataBuffer->pDataBuffer[nPos])
			 {
				case '0':
				 {
					 if(m_ePBAPCState == ePBAPCSTATEDOWNINGBOOK || m_ePBAPCState == ePBAPCSTATEDOWNINGMISSEDCALL || m_ePBAPCState == ePBAPCSTATEDOWNINGCALLHISTORY)
					 {
						 ::PostMessage(m_hWnd,WM_USER +23,int(m_ePBAPCState),NULL);//手机端取消下载
						 m_ePBAPCState = ePBAPCSTATEUNKNOW;
					 }
					p->PBAPCData.ePBAPCState = ePBAPCSTATEUNCONNECT;
				 }
				 break;
				case '1':
				 {
					 p->PBAPCData.ePBAPCState = ePBAPCSTATECONNECTING;
				 }
				 break;
				case '2':
				 {
						// p->PBAPCData.ePBAPCState = ePBAPCSTATECONNECTED;
						 if(m_ePBAPCState == ePBAPCSTATEDOWNINGBOOK && p != NULL)
						 {
							 ResetBTPBAPCData(&p->PBAPCData);
							 ResetNameListGrp(m_szNameList);
							 HBYTE cCommand[50] = {0};
							 memset(cCommand,0,sizeof(cCommand));
							 HINT nCmdlen = strlen("AT+PBDOWN=1\r\n");
							 strncpy((char*)cCommand,"AT+PBDOWN=1\r\n",nCmdlen);
#ifdef TESTBTCOMMANDQUEUE
							 Block *pBlock = CCommandPool::Intance()->PoolNew();
							 if(pBlock != NULL)
							 {
								 sCommandData* pt = (sCommandData*)(pBlock->Buf);
								 memset(pt,0,sizeof(sCommandData));
								 memcpy(pt->szCommand,cCommand,nCmdlen);
								 pt->nCmdLen = nCmdlen;
								 CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
							 }
#else
							 CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
							// m_ePBAPCState = ePBAPCSTATEDOWNINGMISSEDCALL;
							 //CBTCommand::Instance()->GetBTCommandData()->PBAPCData.ePBAPCState = ePBAPCSTATEDOWNINGBOOK;
							 // CBTCommand::Instance()->SetPBDACState(ePBAPCSTATEDOWNINGBOOK);
						 }
						 p->PBAPCData.ePBAPCState = ePBAPCSTATECONNECTED;
					/*HBYTE cCommand[50] = {0};
					 memset(cCommand,0,sizeof(cCommand));
					 HINT nCmdlen = strlen("AT+PBDOWN=1\r\n");
					 strncpy((char*)cCommand,"AT+PBDOWN=1\r\n",nCmdlen);
					 CBTCommand::Instance()->SendData(cCommand,nCmdlen);*/
				 }
				 break;
				case '3':
				 {
					 p->PBAPCData.ePBAPCState = ePBAPCSTATEDOWNING;
					 if(m_ePBAPCState==ePBAPCSTATEDOWNINGBOOK)
					 {
						 ::PostMessage(m_hWnd,WM_USER + 12,NULL,NULL);
					 }
				 }
				 break;
				default:
				 {
					 p->PBAPCData.ePBAPCState = ePBAPCSTATEUNKNOW;
				 }
				 break;
			 }
		 }
	 }
	 return 0;
 }
 HUINT CBTCommand::FindCallHistoryTime(HBYTE *pBeg,HBYTE *pEnd,sCallHistory *pCallHistory)
 {
	 if(pBeg != NULL && pEnd != NULL && pBeg < pEnd && pCallHistory != NULL)
	 {
		 HBYTE *pt = (HBYTE*)strstr((char*)pBeg,"DATETIME;");
		 if(pt != NULL)
		 {
			 while(pt != NULL && pt <= pEnd && (*pt) != ':')
			 {
				 pt++;
			 }
			 HBYTE *pTimeBeg = pt+1;
			 if(pt != NULL)
			 {
				 while((pt +1) <= pEnd && (*pt !='\r') && (*(pt+1) !='\n'))
				 {
					 pt++;
				 }
				 if(pt < pEnd)
				 {
					 HINT nlen = pt - pTimeBeg;
					 if(nlen > 0 && nlen <30  && pCallHistory !=NULL )
					 {
						 memset(pCallHistory->szPhoneTime,0,sizeof(pCallHistory->szPhoneTime));
						 MultiByteToWideChar(CP_ACP,0,(char*)pTimeBeg,nlen,pCallHistory->szPhoneTime,nlen);
						 pCallHistory->szPhoneTime[nlen] = L'\0';
						 return 1;
					 }
				 }
			 }
		 }
	 }
	 return 0;
 }
 bool CBTCommand::FindNameFromAddressBookByNum(sContact *pBookBeg,HUINT nTotal,sContact *p)
 {
	 bool bret = false;
	 if(pBookBeg != NULL && nTotal > 0 && p !=NULL)
	 {
		for(int i = 0;i < nTotal;i++)
		{
		  bret = ComparePhoneNum(&(pBookBeg[i].szTelNumber),&(p->szTelNumber));
          if(bret)
		  {
			  memset(p->szName,0,sizeof(p->szName));
			  memcpy(p->szName,pBookBeg[i].szName,sizeof(p->szName));
			 return true;
		  }
		}
		return false;
	 }
	 return false;
 }
  bool CBTCommand::ComparePhoneNum(sTelNumber* pNum1,sTelNumber* pNum2)
  {
	  if(pNum1 != NULL && pNum2 != NULL)
	  {
		  wchar_t *p1= pNum1->PhoneNumber;
		  wchar_t *p2 = pNum2->PhoneNumber;
		  while((*p1) != L'\0' && (*p2) != L'\0' && (*p1) == (*p2))
		  {
			  p1++;
			  p2++;
			  if((*(p1)) == L'\0' && (*(p2)) == L'\0')
			  {
				  return true;
			  }
		  }
	  }
	  return false;
  }
 //HUINT CBTCommand::FindCallHistory(HBYTE *pBeg,HBYTE *pEnd,sCallHistory *pCallHistory,HUINT &nTotal)
 //{
	// sBTCommandData *pTempData = GetBTCommandData();
	// if(m_pRestPBDNData != NULL && pBeg != NULL && pEnd != NULL && pBeg < pEnd && pTempData != NULL)
	// {
	//	 sCallHistory *pHistory = pTempData->PBAPCData.sPBAPCPhoneBook.arrIncomeCall;
	//	 do {
	//		 pCardBeg =(HBYTE*)strstr((char*)pCardBeg,"BEGIN:VCARD");
	//		 if(pCardBeg != NULL)
	//		 {
	//			 pCardEnd = (HBYTE*)strstr((char*)pCardBeg,"END:VCARD");
	//		 }
	//		 if(pCardEnd != NULL && pCardBeg != NULL && pCardBeg < pCardEnd)
	//		 {
	//			 HINT	nn =FindContactPhoneNum(pCardBeg,pCardEnd,&pHistory[nNum].szContact);
	//			 if(nn == 1)
	//			 {
	//				 FindContactname(pCardBeg,pCardEnd,&pHistory[nNum].szContact);
	//				 FindCallHistoryTime(pCardBeg,pCardEnd,&pHistory[nNum]);
	//				 //BTDEBUGINFO(L"num:%s,Time:%s",pHistory[nNum].szContact.szTelNumber.PhoneNumber,pHistory[nNum].szPhoneTime);
	//			 }
	//			 pCardBeg = pCardEnd + strlen("END:VCARD");
	//			 pRestData = pCardBeg;
	//		 }
	//	 }
	//	 while (pCardBeg < ptEnd && pCardBeg != NULL && pCardEnd != NULL);
	// } 
 //}
 void CBTCommand::SetPBDACState(ePBAPCSTATE eState)
 {
	 m_ePBAPCState = eState;
 }

 HUINT CBTCommand::HandleMediaInfoStart(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	if(pPacketDataBuffer != NULL && nPos > 0 && m_pBTCommandData != NULL)
	{
		//ResetBTAVRCPData(&m_pBTCommandData->BTAVRCPData);
		sBTAVRCPData *pData = &(m_pBTCommandData->BTAVRCPData);
		if(pData != NULL)
		{
			memset(pData->sAVRCPMusicINFO.szMusicNumber,0,sizeof(pData->sAVRCPMusicINFO.szMusicNumber))	;
			memset(pData->sAVRCPMusicINFO.szMusicTotalNumber,0,sizeof(pData->sAVRCPMusicINFO.szMusicTotalNumber));
			memset(pData->sAVRCPMusicINFO.szMusicAlbum,0,sizeof(pData->sAVRCPMusicINFO.szMusicAlbum));
			memset(pData->sAVRCPMusicINFO.szMusicArtist,0,sizeof(pData->sAVRCPMusicINFO.szMusicArtist));
			memset(pData-> sAVRCPMusicINFO.szMusicGenre,0,sizeof(pData->sAVRCPMusicINFO.szMusicGenre));
			memset(pData->sAVRCPMusicINFO.szMusicPlayingTime,0,sizeof(pData->sAVRCPMusicINFO.szMusicPlayingTime));
			memset(pData->sAVRCPMusicINFO.szMusicTitle,0,sizeof(pData->sAVRCPMusicINFO.szMusicTitle));
			pData->sAVRCPMusicINFO.nGetData = 0;
			pData->sAVRCPMusicINFO.nCurNum = 0;
			pData->sAVRCPMusicINFO.nTolNum = 0;
		}
	}
	return 0;
 }

 HUINT CBTCommand::HandleMediaInfoEnd(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	 if(pPacketDataBuffer != NULL && nPos > 0 && m_pBTCommandData != NULL && m_hWnd != NULL)
	 {
		  ::PostMessage(m_hWnd,WM_USER + 3,NULL,NULL);
	 }
	 return 0;
 }
 HUINT CBTCommand::HandleAVRCPPlayState(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	 sBTCommandData* p = GetBTCommandData();
	 if(pPacketDataBuffer != NULL && nPos > 0 && m_pBTCommandData != NULL && m_hWnd != NULL && p != NULL)
	 {
		switch (pPacketDataBuffer->pDataBuffer[nPos])
		{
			case '0':
			{
				m_pBTCommandData->BTAVRCPData.eAVRCPPlayState = eBTMUSICSTOP;
			}
			break;
			case '1':
			{
				m_pBTCommandData->BTAVRCPData.eAVRCPPlayState = eBTMUSICPLAY;
			}
			break;
			case '2':
			{
				m_pBTCommandData->BTAVRCPData.eAVRCPPlayState = eBTMUSICPAUSE;
			}
			break;
			default:
			{
				m_pBTCommandData->BTAVRCPData.eAVRCPPlayState = eBTMUSICSTOP;
			}
			break;
		}
		 ::PostMessage(m_hWnd,WM_USER +4,WPARAM(m_pBTCommandData->BTAVRCPData.eAVRCPPlayState),NULL);
	//	::PostMessage(m_hWnd,WM_USER +4,WPARAM(m_pBTCommandData->BTAVRCPData.eAVRCPPlayState),NULL);
		return 0;
	 }
	 return 1;
 }
 HUINT CBTCommand::HandleA2DPMute(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	 if(pPacketDataBuffer != NULL && nPos > 0 && m_pBTCommandData != NULL && m_hWnd != NULL &&m_pBTCommandData != NULL)
	 {
		 switch (pPacketDataBuffer->pDataBuffer[nPos])
		 {
			case '0':
			 {
				m_pBTCommandData->BTAVRCPData.bA2DPMute = false;
			 }
			 break;
			case '1':
			{
				m_pBTCommandData->BTAVRCPData.bA2DPMute = true;
			}
			break;
		 }
	 }
	 return 0;
 }
 HUINT CBTCommand::HandlePABConn(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	  sBTCommandData* p = GetBTCommandData();
	 if(pPacketDataBuffer != NULL && nPos > 0 && p != NULL)
	 {
		switch (pPacketDataBuffer->pDataBuffer[nPos])
		{
			case '0':
			{
				
				return 0;
			}
			break;
			case '1':
			{	
			}
			break;
			default:
			break;
		}
	 }
	 return 1;
 }
  HUINT CBTCommand::HandleHFPState(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	  bool bRealState = true;
	  sBTCommandData* p = GetBTCommandData();
	  if(pPacketDataBuffer != NULL && nPos > 0 && p != NULL)
	  {
#if AUTOUPDATACALLHISTORY
		  HUINT index =p->PBAPCData.sPBAPCPhoneBook.nNewCallHistory; 
		  HUINT indMissed = p->PBAPCData.sPBAPCPhoneBook.nNewMissed;
		  HUINT indInCome =  p->PBAPCData.sPBAPCPhoneBook.nNewInCome;
		  HUINT indOutGo =  p->PBAPCData.sPBAPCPhoneBook.nNewOutGoing;
		  sCallHistory *pHistory = NULL;
		  sCallHistory *pMissed = NULL;
		  sCallHistory *pInCome = NULL;
		  sCallHistory *pOutgo = NULL;
		  if(index >= 0 && index < 60 && indInCome >= 0 && indInCome < 20  && indMissed >= 0 && indMissed < 20 && indOutGo >= 0 && indOutGo < 20)
		  {
			   pHistory = &p->PBAPCData.sPBAPCPhoneBook.arrNewCallHistory[index];
			   pMissed = &p->PBAPCData.sPBAPCPhoneBook.arrNewMissedCall[indMissed];
			   pInCome = &p->PBAPCData.sPBAPCPhoneBook.arrNewInComeCall[indInCome];
			   pOutgo = &p->PBAPCData.sPBAPCPhoneBook.arrNewOutGoingCall[indOutGo];
		  }
#else
#endif
		  switch (pPacketDataBuffer->pDataBuffer[nPos])
		  {
			case '0':
			{	
				p->BTHFPData.nHFPState = 0;  
				memset(p->BTGeneralData.CurrentPairDevice.szDeviceName,0,sizeof(p->BTGeneralData.CurrentPairDevice.szDeviceName));
				memset(p->BTGeneralData.CurrentPairDevice.szMacAddress,0,sizeof(p->BTGeneralData.CurrentPairDevice.szMacAddress));
				//::PostMessage(m_hWnd,WM_USER + 11,(WPARAM)0,NULL);
			 }
			 break;
			 case '1':
			 {
				p->BTHFPData.nHFPState = 1;
				//::PostMessage(m_hWnd,WM_USER + 11,(WPARAM)1,NULL);
			 }
			 break;
			 case '2':
			 {
				
				 if(p->BTHFPData.nHFPState == 5 || p->BTHFPData.nHFPState == 6 || p->BTHFPData.nHFPState == 3 ||  p->BTHFPData.nHFPState == 4)
				 {
					//   p->BTHFPData.nHFPState = 2;
					 ::PostMessage(m_hWnd,WM_USER + 5,WPARAM(7),NULL);
#if AUTOUPDATACALLHISTORY
					 if(m_pBTCommandData != NULL && index < 60)
					 {
						
						// p->PBAPCData.sPBAPCPhoneBook.nNewCallHistory++;
						 switch (p->BTHFPData.nHFPState)
						 {
						 case  3:
							 {
								 if(pHistory != NULL && index < 60 && index >= 0)
								 {
									 memset(pHistory->szContact.szTelNumber.PhoneNumber,0,sizeof(pHistory->szContact.szTelNumber.PhoneNumber));
									 memcpy(pHistory->szContact.szTelNumber.PhoneNumber,p->BTHFPData.sCurrentCall.szContact.szTelNumber.PhoneNumber,sizeof(pHistory->szContact.szTelNumber.PhoneNumber));
									 memcpy(pHistory->szContact.szName,p->BTHFPData.sCurrentCall.szContact.szName,sizeof(pHistory->szContact.szName));
									 pHistory->eCallType = eMISSEDCALL;
									 p->PBAPCData.sPBAPCPhoneBook.nNewCallHistory++;
									// ::PostMessage(m_hWnd,WM_USER + 19,0,NULL);//全部新增
								 }	 
								 if(pMissed != NULL && indMissed < 20 && indMissed >= 0)
								 {
									 memset(pMissed->szContact.szTelNumber.PhoneNumber,0,sizeof(pMissed->szContact.szTelNumber.PhoneNumber));
									 memcpy(pMissed->szContact.szTelNumber.PhoneNumber,p->BTHFPData.sCurrentCall.szContact.szTelNumber.PhoneNumber,sizeof(pMissed->szContact.szTelNumber.PhoneNumber));
									 memcpy(pMissed->szContact.szName,p->BTHFPData.sCurrentCall.szContact.szName,sizeof(pMissed->szContact.szName));
									 pMissed->eCallType = eMISSEDCALL;
									 p->PBAPCData.sPBAPCPhoneBook.nNewMissed++;
									 ::PostMessage(m_hWnd,WM_USER + 19,1,NULL);//未接新增
								 }		
							 }
							 break;
						 case 4:
							 {
								 if(pHistory != NULL && index < 60 && index >= 0)
								 {
									 memset(pHistory->szContact.szTelNumber.PhoneNumber,0,sizeof(pHistory->szContact.szTelNumber.PhoneNumber));
									 memcpy(pHistory->szContact.szTelNumber.PhoneNumber,p->BTHFPData.sCurrentCall.szContact.szTelNumber.PhoneNumber,sizeof(pHistory->szContact.szTelNumber.PhoneNumber));
									 memcpy(pHistory->szContact.szName,p->BTHFPData.sCurrentCall.szContact.szName,sizeof(pHistory->szContact.szName));
									 pHistory->eCallType = eOUTGOINGCALL;
									 p->PBAPCData.sPBAPCPhoneBook.nNewCallHistory++;
								 }	 
								 if(pOutgo != NULL && indOutGo < 20 && indOutGo >= 0)
								 {
									 memset(pOutgo->szContact.szTelNumber.PhoneNumber,0,sizeof(pOutgo->szContact.szTelNumber.PhoneNumber));
									 memcpy(pOutgo->szContact.szTelNumber.PhoneNumber,p->BTHFPData.sCurrentCall.szContact.szTelNumber.PhoneNumber,sizeof(pOutgo->szContact.szTelNumber.PhoneNumber));
									 memcpy(pOutgo->szContact.szName,p->BTHFPData.sCurrentCall.szContact.szName,sizeof(pOutgo->szContact.szName));
									 pOutgo->eCallType = eOUTGOINGCALL;
									 p->PBAPCData.sPBAPCPhoneBook.nNewOutGoing++;
									  ::PostMessage(m_hWnd,WM_USER + 19,2,NULL);//拨出新增
								 }
							 }
							 break;
						 case 5:
							 {
								 if(pHistory != NULL && index < 60 && index >= 0)
								 {
									 memset(pHistory->szContact.szTelNumber.PhoneNumber,0,sizeof(pHistory->szContact.szTelNumber.PhoneNumber));
									 memcpy(pHistory->szContact.szTelNumber.PhoneNumber,p->BTHFPData.sCurrentCall.szContact.szTelNumber.PhoneNumber,sizeof(pHistory->szContact.szTelNumber.PhoneNumber));
									 memcpy(pHistory->szContact.szName,p->BTHFPData.sCurrentCall.szContact.szName,sizeof(pHistory->szContact.szName));
									// pHistory->eCallType = eMISSEDCALL;
									 p->PBAPCData.sPBAPCPhoneBook.nNewCallHistory++;
									//  ::PostMessage(m_hWnd,WM_USER + 19,0,NULL);
								 }	 
								 if(pOutgo != NULL && indOutGo < 20 && indOutGo >= 0 && pOutgo->eCallType == eOUTGOINGCALL)
								 {
									 memset(pOutgo->szContact.szTelNumber.PhoneNumber,0,sizeof(pOutgo->szContact.szTelNumber.PhoneNumber));
									 memcpy(pOutgo->szContact.szTelNumber.PhoneNumber,p->BTHFPData.sCurrentCall.szContact.szTelNumber.PhoneNumber,sizeof(pOutgo->szContact.szTelNumber.PhoneNumber));
									 memcpy(pOutgo->szContact.szName,p->BTHFPData.sCurrentCall.szContact.szName,sizeof(pOutgo->szContact.szName));
									 p->PBAPCData.sPBAPCPhoneBook.nNewOutGoing++;
									  ::PostMessage(m_hWnd,WM_USER + 19,2,NULL);//新增拨出
								 }
								 if(pInCome != NULL && indInCome < 20 && indInCome >= 0 && pInCome->eCallType == eINCOMMINGCALL)
								 {
									 memset(pInCome->szContact.szTelNumber.PhoneNumber,0,sizeof(pInCome->szContact.szTelNumber.PhoneNumber));
									 memcpy(pInCome->szContact.szTelNumber.PhoneNumber,p->BTHFPData.sCurrentCall.szContact.szTelNumber.PhoneNumber,sizeof(pInCome->szContact.szTelNumber.PhoneNumber));
									 memcpy(pOutgo->szContact.szName,p->BTHFPData.sCurrentCall.szContact.szName,sizeof(pOutgo->szContact.szName));
									 p->PBAPCData.sPBAPCPhoneBook.nNewInCome++;	 
									  ::PostMessage(m_hWnd,WM_USER + 19,3,NULL);//新增已接
								 }
							 }
							 break;
						 case 6:
							 {
							 }
							 break;
						 default:
							 {
							 }
							 break;
						 }
						 ::PostMessage(m_hWnd,WM_USER + 15,NULL,NULL);//通讯录更新
#else
#endif		
					 }		
				 }
				 p->BTHFPData.nHFPState = 2;
				 //::PostMessage(m_hWnd,WM_USER + 11,(WPARAM)2,NULL);
			 }
			 break;
			 case '3':
			{
#if AUTOUPDATACALLHISTORY
				if(p->BTHFPData.nHFPState == 2)
				{
					if(m_pBTCommandData != NULL &&index >= 0 && index < 60 && indInCome >= 0 && indInCome < 20  && indMissed >= 0 && indMissed < 20 && indOutGo >= 0 && indOutGo < 20 && pHistory != NULL && pMissed != NULL && pInCome != NULL && pOutgo != NULL)
					{
						//写来电时间
						memset(pHistory,0,sizeof(pHistory));
						memset(pMissed,0,sizeof(pMissed));
						memset(pInCome,0,sizeof(pInCome));
						//p->PBAPCData.sPBAPCPhoneBook.nNewCallHistory++;
						//pHistory->eCallType = eINCOMMINGCALL;
						//写入通话记录时间
					}
				}
#else
#endif
				p->BTHFPData.nHFPState = 3;
				//::PostMessage(m_hWnd,WM_USER + 11,(WPARAM)3,NULL);
			}
			break;
			case '4':
			{
#if AUTOUPDATACALLHISTORY
				 if(p->BTHFPData.nHFPState == 2)
				 {
					 if(m_pBTCommandData != NULL && index < 60 && index >= 0 && pHistory != NULL && indOutGo >= 0 && indOutGo < 20 && pOutgo != NULL)
					 {
						 //写拨号时间
						 memset(pHistory,0,sizeof(pHistory));
						/* memset(pHistory->szContact.szTelNumber.PhoneNumber,0,sizeof(pHistory->szContact.szTelNumber.PhoneNumber));
						 memcpy(pHistory->szContact.szTelNumber.PhoneNumber,p->BTHFPData.sCallInNum.PhoneNumber,sizeof(pHistory->szContact.szTelNumber.PhoneNumber));*/
						 pHistory->eCallType = eOUTGOINGCALL;
						/*  p->PBAPCData.sPBAPCPhoneBook.nNewOutGoing++;*/
						  memset(pOutgo,0,sizeof(pOutgo));
						  //memset(pHistory->szContact.szTelNumber.PhoneNumber,0,sizeof(pHistory->szContact.szTelNumber.PhoneNumber));
						  //memcpy(pHistory->szContact.szTelNumber.PhoneNumber,p->BTHFPData.sCallInNum.PhoneNumber,sizeof(pHistory->szContact.szTelNumber.PhoneNumber));
						 pOutgo->eCallType = eOUTGOINGCALL;
						  //p->PBAPCData.sPBAPCPhoneBook.nNewOutGoing++;
						// p->PBAPCData.sPBAPCPhoneBook.nNewCallHistory++;
					 }
				 }
#else
#endif
				p->BTHFPData.nHFPState = 4;
				//::PostMessage(m_hWnd,WM_USER + 11,(WPARAM)4,NULL);
			}
			break;
			case '5':
			{
#if AUTOUPDATACALLHISTORY
				if(p->BTHFPData.nHFPState == 3)
				{
					if(pHistory != NULL )
					{
						//memset(pHistory->szContact.szTelNumber.PhoneNumber,0,sizeof(pHistory->szContact.szTelNumber.PhoneNumber));
						pHistory->eCallType = eINCOMMINGCALL;
						//memcpy(pHistory->szContact.szTelNumber.PhoneNumber,p->BTHFPData.sCallInNum.PhoneNumber,sizeof(pHistory->szContact.szTelNumber.PhoneNumber));
					//	p->PBAPCData.sPBAPCPhoneBook.nNewCallHistory++;
					}
					if(pInCome != NULL)
					{
						//memset(pInCome->szContact.szTelNumber.PhoneNumber,0,sizeof(pInCome->szContact.szTelNumber.PhoneNumber));
					//	memcpy(pInCome->szContact.szTelNumber.PhoneNumber,p->BTHFPData.sCallInNum.PhoneNumber,sizeof(pInCome->szContact.szTelNumber.PhoneNumber));
						pInCome->eCallType = eINCOMMINGCALL;
					}
					//p->PBAPCData.sPBAPCPhoneBook.nNewInCome++;
				}
#else
#endif
				if(p->BTHFPData.nHFPState != 2)
				{
					p->BTHFPData.nHFPState = 5;
				}
				else
				{
					bRealState = false;
				}
				
				//::PostMessage(m_hWnd,WM_USER + 11,(WPARAM)5,NULL);
			}
			break;
			case '6':
			{
				p->BTHFPData.nHFPState = 6;
				//::PostMessage(m_hWnd,WM_USER + 11,(WPARAM)6,NULL);
			}
			break;
		  default:
			  break;
		  }
	  }
	  if(bRealState)
	  {
			 ::PostMessage(m_hWnd,WM_USER +5,WPARAM(p->BTHFPData.nHFPState),NULL);
	  }
	 
	//  ::PostMessage(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_BT_HFP_STATE,WPARAM(p->BTHFPData.nHFPState),NULL);
	  BTDEBUGINFO(L"IPC_ID_MANAGE:VWM_BT_HFP_STATE--%d",p->BTHFPData.nHFPState);
	  return 1;
  }
  HUINT CBTCommand::HandleHFPDial(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
		  if(pPacketDataBuffer != NULL && nPos > 0)
		  {
				switch (pPacketDataBuffer->pDataBuffer[nPos])
				{
					case '0':
					{
				
					}
					break;
					case '1':
					{
						//::MessageBox(NULL,L"拨号失败",L"提示",NULL);
					}
					break;
					default:
					break;
				}
				return 0;
		  }
	return 1;
  }

  HUINT CBTCommand::HandleHIDState(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	  if(pPacketDataBuffer != NULL && nPos > 0 && m_pBTCommandData != NULL)
	  {
		  switch(pPacketDataBuffer->pDataBuffer[nPos])
		  {
		  case '0':
			  {
				  m_pBTCommandData->BTHIDData.nHIDState = 0;
			  }
			  break;
		  case '1':
			  {
				    m_pBTCommandData->BTHIDData.nHIDState = 1;
			  }
			  break;
		  case '2':
			  {
				    m_pBTCommandData->BTHIDData.nHIDState = 2;
			  }
			  break;
		  default:
			  break;
		  }
		//  ::PostMessage(m_hWnd,WM_USER + 17,WPARAM( m_pBTCommandData->BTHIDData.nHIDState),NULL);
	  }
	   return 0;
 }
  HUINT CBTCommand::HandleHIDDISC(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	  return 0;
  }
  HUINT CBTCommand::HandleHID(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	  return 0;
  }
  HUINT CBTCommand::HandHIDHome(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	  if(pPacketDataBuffer != NULL && nPos > 0 && m_pBTCommandData != NULL)
	  {
		  switch(pPacketDataBuffer->pDataBuffer[nPos])
		  {
		  case '0':
				 {
					 BTDEBUGINFO(L"HIDHOME 设置成功");
				 }
				 break;
		  case '1':
			  {
				  BTDEBUGINFO(L"HIDHOME 设置失败");
			  }
			  break;
		  }
	  }
	  return 0;
  }
  HUINT CBTCommand::HandleHFPAnswer(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	  return 0;
  }
  HUINT CBTCommand::HandleHFPAudo(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	 if(pPacketDataBuffer != NULL && nPos > 0 && m_pBTCommandData != NULL)
	 {
		 switch (pPacketDataBuffer->pDataBuffer[nPos])
		 {
			 case '0':
			 {
				m_pBTCommandData->BTHFPData.nVoicePosition = 0;
				::PostMessage(m_hWnd,WM_USER + 20,0,NULL);//声音切换至手机
			 }
			 break;
			 case '1':
			{
				m_pBTCommandData->BTHFPData.nVoicePosition = 1;
				::PostMessage(m_hWnd,WM_USER + 20,1,NULL);//声音切换至车机
			}
			break;
			 default:
				 break;
		 }
	 }
	  return 0;
  }
  HUINT CBTCommand::HandleHFPDTMF(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	  return 0;
  }
  HUINT CBTCommand::HandleHFPMute(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	  return 0;
  }
  HUINT CBTCommand::HandleHFPRecall(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	  return 0;
  }
  HUINT CBTCommand::HandleHFPDealIncomeCall(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	  return 0;
  }
  HUINT CBTCommand::HandleHFPIncomeCall(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
//	  ReadBtParamFromSHM();
//	  BTSETTING Setting;
//	  KCLastMemory::GetInstance()->GetBTMemory(Setting);
//	  m_sBTSetting = Setting;
//	 // bAutoAnswer = GetValueFromShareMem();
//	 // m_sBtParam.BTAutoAnswer = true;
//	  if(Setting.uBtAutoReceive == 1)
//	  {
//		  HBYTE cCommand[50] = {0};
//		  //memset(cCommand,0,sizeof(cCommand));
//		  BTDEBUGINFO(L"Setting.uBtAutoReceive == 1");
//		  HINT nCmdlen = strlen("AT+HFANSW\r\n");
//		  strncpy((char*)cCommand,"AT+HFANSW\r\n",nCmdlen);
//#ifdef  TESTBTCOMMANDQUEUE
//		  CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPAnswerCallWhenBeCalled,NULL);
//#else
//		  CBTCommand::Instance()->SendData(cCommand,nCmdlen);
//#endif
//	  }
	  return 0;
  }
  HUINT CBTCommand::HandleHFPIncomeCallNum(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	  if(pPacketDataBuffer != NULL && nPos > 0 && m_pBTCommandData != 0)
	  {
		  HINT nCopy = pPacketDataBuffer->nDatalen - nPos;
		  if(nCopy > 0 && nCopy < 30)
		  {
			  bool bret = false;
			 // memset(m_pBTCommandData->BTHFPData.sCurrentCall.szContact.szTelNumber.PhoneNumber,0,sizeof(m_pBTCommandData->BTHFPData.sCurrentCall.szContact.szTelNumber.PhoneNumber));
			  memset(&(m_pBTCommandData->BTHFPData.sCurrentCall),0,sizeof(m_pBTCommandData->BTHFPData.sCurrentCall));
			  MultiByteToWideChar(CP_ACP,0,(char*)(pPacketDataBuffer->pDataBuffer + nPos),30,m_pBTCommandData->BTHFPData.sCurrentCall.szContact.szTelNumber.PhoneNumber,30);
			 bret = FindNameFromAddressBookByNum(m_pBTCommandData->PBAPCData.sPBAPCPhoneBook.arrContact,m_pBTCommandData->PBAPCData.sPBAPCPhoneBook.nTotalContact,&(m_pBTCommandData->BTHFPData.sCurrentCall.szContact));
#if USEFULNUMBERS
			 if(!bret)
			 {
				 SETUPSETTING LSetting;
				 KCLastMemory::GetInstance()->GetSetupMemory(LSetting);
				 BTDEBUGINFO(L"LSetting.cLang = %d",LSetting.cLang);
				 switch (LSetting.cLang)
				 {
					case 0:
					 {
						  bret = FindNameFromAddressBookByNum(m_pBTCommandData->BTUsefulNumData.szUsefulNum,m_pBTCommandData->BTUsefulNumData.nTolNum,&(m_pBTCommandData->BTHFPData.sCurrentCall.szContact));
					 }
					 break;
					case 1:
					{
						 bret = FindNameFromAddressBookByNum(m_pBTCommandData->BTUsefulNumData.szEnUsefulNum,m_pBTCommandData->BTUsefulNumData.nTolNum,&(m_pBTCommandData->BTHFPData.sCurrentCall.szContact));
					}
					break;
					default:
					break;
				 }
				
			 }
#else
#endif
			 if(!bret)
			 {
				 swprintf_s(m_pBTCommandData->BTHFPData.sCurrentCall.szContact.szName,10,L"%s",L"<未知号码>");
			 }
			sContact *pContact = new sContact;
			if(pContact != NULL)
			{
				 memcpy(pContact,&m_pBTCommandData->BTHFPData.sCurrentCall.szContact,sizeof(sContact));
				 ::PostMessage(m_hWnd,WM_USER + 10,(WPARAM)pContact,NULL);
			}
		  }
	  }
	  return 0;
  }
  HUINT CBTCommand::HandleHFPSecNum(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	  return 0;
  }
HUINT CBTCommand::HandleHFPOutGoingCall(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
{
	return	HandleHFPIncomeCallNum(pPacketDataBuffer,nPos);
}
  HUINT CBTCommand::HandleHFPHangUp(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	   if(pPacketDataBuffer != NULL && nPos > 0 && m_pBTCommandData != 0 && m_hWnd != 0)
	   {
		   switch (pPacketDataBuffer->pDataBuffer[nPos])
		   {
				case '0':
				{
					//::PostMessage(m_hWnd,WM_USER + 5,WPARAM(7),NULL);
					//Sleep(100);
					//::PostMessage(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_BT_HFP_STATE,WPARAM(7),NULL);
				}
				break;
				case '1':
				{
				}
				break;
				default:
				break;
		   }
	   }
	  return 0;
  }
  HUINT CBTCommand::HandleEnterPairMode(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	  if(pPacketDataBuffer != NULL && nPos > 0)
	  {
			switch(pPacketDataBuffer->pDataBuffer[nPos])
			{
				case '0':
				{
					::PostMessage(m_hWnd,WM_USER + 8,WPARAM(0),NULL);
				}
				break;
				case '1':
				{
					::PostMessage(m_hWnd,WM_USER + 8,WPARAM(1),NULL);
				}
				default:
				break;
			}
	  }
	return 0;
  }
  HUINT CBTCommand::HandleEnterTestMode(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	return 0;
  }
  HUINT CBTCommand::HandleLoadFactoryDefaults(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	return 0;
  }
  HUINT CBTCommand::HandleFWD(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
  {
	return 0;
  }
 HUINT CBTCommand::HandleInit(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	return 0;
 }
 HUINT CBTCommand::HandleBLE(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	 return 0;
 }
 HUINT CBTCommand::HandleBACK(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	 return 0;
 }
 HUINT CBTCommand::HandlePP(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	 return 0;
 }
 HUINT CBTCommand::HandlePairResult(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	return 0;
 }
 HUINT CBTCommand::HandlePairEnd(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	return 0;
 }
 HUINT CBTCommand::HandlePairState(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	if(pPacketDataBuffer != NULL && nPos > 0 && m_pBTCommandData != NULL)
	{
		 if(pPacketDataBuffer->pDataBuffer[nPos] >='0' && pPacketDataBuffer->pDataBuffer[nPos] <='9' )
		 {
			 if(m_pBTCommandData != NULL)
			 {
				 m_pBTCommandData->BTGeneralData.nPairingState = pPacketDataBuffer->pDataBuffer[nPos] - '0';
				 BTDEBUGINFO(L"nPairingState = %d",m_pBTCommandData->BTGeneralData.nPairingState);
			 }
		 }
	}
	return 0;
 }
 HUINT CBTCommand::HandlePBDISC(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	 return 0;
 }
 HUINT CBTCommand::HandleCannelDownload(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	 return 0;
 }
 HUINT CBTCommand::HandleCurrentConnectDevice(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos)
 {
	 if(pPacketDataBuffer != NULL && nPos > 0 && m_pBTCommandData != NULL)
	 {
		// memset(m_pBTCommandData->BTGeneralData.CurrentPairDevice.szDeviceName,0,sizeof(m_pBTCommandData->BTGeneralData.CurrentPairDevice.szDeviceName));
		 memset(m_pBTCommandData->BTGeneralData.CurrentPairDevice.szMacAddress,0,sizeof(m_pBTCommandData->BTGeneralData.CurrentPairDevice.szMacAddress));
		 memcpy(m_pBTCommandData->BTGeneralData.CurrentPairDevice.szMacAddress,pPacketDataBuffer->pDataBuffer + nPos,12);
		 ::PostMessage(m_hWnd,WM_USER + 9,NULL,NULL)	;
		 return 0;
	 }
	 return 1;
 }
 bool CBTCommand::ReadBtParamFromSHM()
 {
	 bool bret = false;
	 bret = true;
	 m_sBtParam.BTOpen = true;
	 return bret;
 }
 HINT CBTCommand::OpenBT(DWORD dwPort, DWORD dwBaudRate)
 {
	// if(m_bBTOpen == false)
	 {
		 //RegisterProc(ReadSerialData,WriteSerialData,m_pPacket);
		// HINSTANCE hDll;
		 pBTClose pClose = NULL;
		 pBTOpen pfun = NULL;
		 if(m_DriverDll == NULL)
		 {
				m_DriverDll  = LoadLibraryW(L"\\Windows\\DriverAPI.dll");
		 }
	
		 if(m_DriverDll != NULL)
		 {
			 pClose = (pBTClose)GetProcAddress(m_DriverDll,_T("BluetoothClose"));

			 if(pClose != NULL)
			 {
				/*pClose(BT_NONE);
				Sleep(500);*/
			 }
			 pfun = (pBTOpen)GetProcAddress(m_DriverDll,_T("BluetoothOpen"));
			 if(pfun != NULL)
			 {
				 pfun(BT_NONE);

				 pfun = NULL ;
			 }
			 else
			 {
				 BTDEBUGINFO(L"pfun is null");
				 return 1;
			 }
			 //FreeLibrary(hDll);
		 }
		 else
		 {
			 BTDEBUGINFO(L"hDll is null ERROR(%d)",GetLastError());
			 return 1;
		 }
		 CBTCommand* pObj= CBTCommand::Instance( );
		 if(pObj != NULL)
		 {
			 pObj->RegisterProc(ReadSerialData,WriteSerialData,m_pPacket);
			 pObj->InitPort(dwPort,dwBaudRate);
			 m_bBTOpen = true;
			 Sleep(100);
			 BTDEBUGINFO(L"蓝牙打开成功!");
			  ::PostMessage(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_BT_OPEN_STATE,WPARAM(1),NULL);//wParam: 1 蓝牙打开成功 0蓝牙关闭成功
			 return 0;
		 }
	 }
	 return 1;
 }
 HINT CBTCommand::LowBTPower()
{
	pBTClose pClose = NULL;
	pBTOpen pfun = NULL;
	if(m_DriverDll == NULL)
	{
		m_DriverDll  = LoadLibraryW(L"\\Windows\\DriverAPI.dll");
	}
	if(m_DriverDll != NULL)
	{
		pClose = (pBTClose)GetProcAddress(m_DriverDll,_T("BluetoothClose"));

		if(pClose != NULL)
		{
			pClose(BT_NONE);
			Sleep(500);
		}
	}
	return 0;
}

 HINT CBTCommand::UpBTPower()
 {
     pBTOpen pfun = NULL;
		 if(m_DriverDll == NULL)
		 {
				m_DriverDll  = LoadLibraryW(L"\\Windows\\DriverAPI.dll");
		 }
	
		 if(m_DriverDll != NULL)
		 {
			 pfun = (pBTOpen)GetProcAddress(m_DriverDll,_T("BluetoothOpen"));
			 if(pfun != NULL)
			 {
				 pfun(BT_NONE);

				 pfun = NULL ;
			 }
			 else
			 {
				 BTDEBUGINFO(L"pfun is null");
				 return 1;
			 }
		 }
		 else
		 {
			 BTDEBUGINFO(L"hDll is null ERROR(%d)",GetLastError());
			 return 1;
		 }
		 return 0;
 }
 HINT  CBTCommand::CloseBT()
 {
	 if(m_bBTOpen == true)
	 {
//		 HINSTANCE hDll;
		 pBTClose pfun = NULL;
		 if(m_DriverDll == NULL)
		 {
			 m_DriverDll = LoadLibraryW(L"\\Windows\\DriverAPI.dll");
		 }
		 if(m_DriverDll != NULL)
		 {
			 pfun = (pBTOpen)GetProcAddress(m_DriverDll,_T("BluetoothClose"));
			 if(pfun != NULL)
			 {
				 pfun(BT_NONE);
				 pfun = NULL ;
				 UnInitPort();
				 m_bBTOpen = false;
				 BTDEBUGINFO(L"蓝牙关闭成功！");
				 ::PostMessage(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_BT_OPEN_STATE,WPARAM(0),NULL);//蓝牙关闭成功
				 // FreeLibrary(hDll);
				 return 0;
			 }
			 else
			 {
				 BTDEBUGINFO(L"pfun is null");
				 return 1;
			 }	
		 }
		 else
		 {
			 BTDEBUGINFO(L"hDll is null ERROR(%d)",GetLastError());
			 return 1;
		 }
	 }
	 return 1;
 }
 void CBTCommand::ClearBookData()
{
	if(!m_bBookDataBeCleared)
	{
			ResetNameListGrp(m_szNameList);
			ResetBTPBAPCData(&(m_pBTCommandData->PBAPCData));
			m_bBookDataBeCleared = true;
	}
}
 void CBTCommand::ClearMyPhoneData()
 {
	if(m_pPhoneInfo != NULL && (!m_bMyPhoneInfoCleared))
	{
		memset(m_pPhoneInfo,0,sizeof(sMyPhoneInfo));
		m_bMyPhoneInfoCleared = true;
	}
 }
 void CBTCommand::MessageBtclose()
 {
	 if(m_bBTOpen == true)
	 {
		 ::PostMessage(m_hWnd,WM_USER + 13,NULL,NULL);
	 }
	 else
	 {
		 ::PostMessage(m_hWnd,WM_USER + 14,NULL,NULL);
	 }
 }
void CBTCommand::AddContactToList(sContact *pContact,NameListGroup &ListGrp)
{
    if(pContact != NULL)
	{
		char szCName[20] = {0};
		HINT nn = 0;
		nn = WideCharToMultiByte(CP_ACP,0,pContact->szName,1,szCName,10,NULL,NULL);
	   szCName[20] = '\0';
		if(nn == 0)
		{
			BTDEBUGINFO(L"err = %d",GetLastError());
		}
        string ss(szCName);
		string nameletter ;
		if(ss.size() >= 2)
		{
			BTDEBUGINFO(L"ss[0] = %d,ss[1] = %d",ss.at(0),ss.at(1));
		}
		else if(ss.size() == 1)
		{
			BTDEBUGINFO(L"ss[0] = %d",ss.at(0));
		}
	    else if(ss.size() == 0)
		{
			BTDEBUGINFO(L"ss is empty");
		}
		nameletter = GetLetter(ss);
		//BTDEBUGINFO(L"name : %s,nameLetter:%s",pContact->szName,nameletter);
		EnterCriticalSection(&m_csNameList);
		ListGrp.nTotalContact++;
		if (nameletter.empty())
		{
		}
		switch (nameletter.at(0))
		{
		case 'A':
		case 'a':
			{
				ListGrp.pContact[1].push_back(pContact);
				ListGrp.szCount[1]++;
			}
			break;
		case 'b':
		case 'B':
			{
				ListGrp.pContact[2].push_back(pContact);
				ListGrp.szCount[2]++;
			}
			break;
		case 'c':
		case 'C':
			{
				ListGrp.pContact[3].push_back(pContact);
				ListGrp.szCount[3]++;
			}
			break;
		case 'd':
		case 'D':
			{
				ListGrp.pContact[4].push_back(pContact);
				ListGrp.szCount[4]++;
			}
			break;
		case 'e':
		case 'E':
			{
				ListGrp.pContact[5].push_back(pContact);
				ListGrp.szCount[5]++;
			}
			break;
		case 'f':
		case 'F':
			{
				ListGrp.pContact[6].push_back(pContact);
				ListGrp.szCount[6]++;
			}
			break;
		case 'g':
		case 'G':
			{
				ListGrp.pContact[7].push_back(pContact);
				ListGrp.szCount[7]++;
			}
			break;
		case 'h':
		case 'H':
			{
				ListGrp.pContact[8].push_back(pContact);
				ListGrp.szCount[8]++;
			}
			break;
		case 'i':
		case 'I':
			{
				ListGrp.pContact[9].push_back(pContact);
				ListGrp.szCount[9]++;
			}
			break;
		case 'j':
		case 'J':
			{
				ListGrp.pContact[10].push_back(pContact);
				ListGrp.szCount[10]++;
			}
			break;
		case 'k':
		case 'K':
			{
				ListGrp.pContact[11].push_back(pContact);
				ListGrp.szCount[11]++;
			}
			break;
		case 'l':
		case 'L':
			{
				ListGrp.pContact[12].push_back(pContact);
				ListGrp.szCount[12]++;
			}
			break;
		case 'm':
		case 'M':
			{
				ListGrp.pContact[13].push_back(pContact);
				ListGrp.szCount[13]++;
			}
			break;
		case 'n':
		case 'N':
			{
				ListGrp.pContact[14].push_back(pContact);
				ListGrp.szCount[14]++;
			}
			break;
		case 'o':
		case 'O':
			{
				ListGrp.pContact[15].push_back(pContact);
				ListGrp.szCount[15]++;
			}
			break;
		case 'p':
		case 'P':
			{
				ListGrp.pContact[16].push_back(pContact);
				ListGrp.szCount[16]++;
			}
			break;
		case 'q':
		case 'Q':
			{
				ListGrp.pContact[17].push_back(pContact);
				ListGrp.szCount[17]++;
			}
			break;
		case 'r':
		case 'R':
			{
				ListGrp.pContact[18].push_back(pContact);
				ListGrp.szCount[18]++;
			}
			break;
		case 's':
		case 'S':
			{
				ListGrp.pContact[19].push_back(pContact);
				ListGrp.szCount[19]++;
			}
			break;
		case 't':
		case 'T':
			{
				ListGrp.pContact[20].push_back(pContact);
				ListGrp.szCount[20]++;
			}
			break;
		case 'u':
		case 'U':
			{
				ListGrp.pContact[21].push_back(pContact);
				ListGrp.szCount[21]++;
			}
			break;
		case 'v':
		case 'V':
			{
				ListGrp.pContact[22].push_back(pContact);
				ListGrp.szCount[22]++;
			}
			break;
		case 'w':
		case 'W':
			{
				ListGrp.pContact[23].push_back(pContact);
				ListGrp.szCount[23]++;
			}
			break;
		case 'x':
		case 'X':
			{
				ListGrp.pContact[24].push_back(pContact);
				ListGrp.szCount[24]++;
			}
			break;
		case 'y':
		case 'Y':
			{
				ListGrp.pContact[25].push_back(pContact);
				ListGrp.szCount[25]++;
			}
			break;
		case 'z':
		case 'Z':
			{
				ListGrp.pContact[26].push_back(pContact);
				ListGrp.szCount[26]++;
			}
			break;
		default:
			{
				ListGrp.pContact[0].push_back(pContact);
				ListGrp.szCount[0]++;
			//	BTDEBUGINFO(L"name : %s,nameLetter:%s",pContact->szName,nameletter);
				BTDEBUGINFO(L"NameLetter:???????");
			}
			break;
		}
		LeaveCriticalSection(&m_csNameList);
	}	
	//BTDEBUGINFO(L"^^22222^^");
}
  void CBTCommand::SetBTSetting(BTSETTING setting)
  {
	  m_sBTSetting = setting;
  }
  BTSETTING CBTCommand::GetBTSetting()
  {
    return m_sBTSetting;
  }
  sMyPhoneInfo* CBTCommand::GetMyPhoneInfo()
  {
	  return m_pPhoneInfo;
  }
  void CBTCommand::GetAvailableArea(int CeWidth,int CeHight,int PhoneWidth,int PhoneHight)
  {
	  sPostion AvailableArea = {SCREEN_WIDTH,SCREEN_HEIGHT};
	  if(CeWidth > 0 && CeHight > 0 && PhoneWidth > 0 && PhoneHight > 0 && m_pPhoneInfo != NULL)
	  {
		  int n = 0;
		  n = (CeWidth*PhoneHight) - (CeHight*PhoneWidth);
		  if(n == 0)
		  {
			  //return AvailableArea;
			  AvailableArea.x = CeWidth;
			  AvailableArea.y = CeHight;
		  }
		  else if(n > 0)
		  {
			  AvailableArea.x = PhoneWidth*CeHight/PhoneHight;
		  }
		  else if(n < 0)
		  {
			  AvailableArea.y = PhoneHight*CeWidth/PhoneWidth;
		  }
		  m_pPhoneInfo->iAvailableCeWidth = AvailableArea.x;
		  m_pPhoneInfo->iAvailableCeHight = AvailableArea.y;
	  }
	 // return AvailableArea;
  }
 int CBTCommand::SendBTCommand(BTPacketDataType_t eType,sCommandData *pData)
{
	switch(eType)
	{
		case BTPacketReadSoftVersion:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+GVER\r\n");
			strncpy((char*)cCommand,"AT+GVER\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
		case BTPacketReadLocalDeviceAddress:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+GLBA\r\n");
			strncpy((char*)cCommand,"AT+GLBA\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
		case BTPacketReadLocalDeviceName:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+GLDN\r\n");
			strncpy((char*)cCommand,"AT+GLDN\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
		case BTPacketSetLocalDeviceName:
			{
			//	HBYTE cCommand[eMAXCMDLEN] = {0};
			//	HUINT nCmdlen = 0;
				if(pData != NULL)
				{
					if(pData != NULL && pData->nCmdLen > 0)
					{
						CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
					}
				} 	
			}
			break;
		case BTPacketListPairDevice:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+LSPD\r\n");
				strncpy((char*)cCommand,"AT+LSPD\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketDeletePairDeviceList:
			{
				if(pData != NULL && pData->nCmdLen > 0)
				{
					CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
				}
			}
			break;
		case BTPacketConnectDeviceInPairList:
			{
				if(pData != NULL && pData->nCmdLen > 0)
				{
					CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
				}
			}
		break;
		case BTPacketUpVolume:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+VUP\r\n");
				strncpy((char*)cCommand,"AT+VUP\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketDownVolume:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+VDN\r\n");
				strncpy((char*)cCommand,"AT+VDN\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketReadPairPassword:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+GFPC\r\n");
				strncpy((char*)cCommand,"AT+GFPC\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketSetPairPassword:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+SFPC\r\n");
				strncpy((char*)cCommand,"AT+SFPC\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketEnterPairMode:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+EPRM=1\r\n");
				strncpy((char*)cCommand,"AT+EPRM=1\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketExitPairMode:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+EPRM=0\r\n");
				strncpy((char*)cCommand,"AT+EPRM=0\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketEnterTestMode:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+EUTM\r\n");
				strncpy((char*)cCommand,"AT+EUTM\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketLoadFailSafeDefaults:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+FACT\r\n");
				strncpy((char*)cCommand,"AT+FACT\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketSoftRestart:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+BOOT\r\n");
				strncpy((char*)cCommand,"AT+BOOT\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketDisconnectCurrentConnection:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+DSCA\r\n");
				strncpy((char*)cCommand,"AT+DSCA\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketInitialize:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+DSCA\r\n");
				strncpy((char*)cCommand,"AT+DSCA\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketSPPAcquireSSPState:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+SPPSTAT\r\n");
				strncpy((char*)cCommand,"AT+SPPSTAT\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketSPPConnectPhoneAndPCActive:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+SPPCONN\r\n");
				strncpy((char*)cCommand,"AT+SPPCONN\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTSPPDisConnetSPP:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+SPPDISC\r\n");
				strncpy((char*)cCommand,"AT+SPPDISC\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketSPPSendDataToBT:
			{
				if(pData != NULL && pData->nCmdLen > 0)
				{
					CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
				}
			}
			break;
		case BTPacketGATTAcquireGATTState:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+GATTSTAT\r\n");
				strncpy((char*)cCommand,"AT+GATTSTAT\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketGATTSendDataToBT:
			{
				if(pData != NULL && pData->nCmdLen > 0)
				{
					CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
				}
			}
			break;
		case BTPacketHFPAcqureHFPState:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+HFPSTAT\r\n");
				strncpy((char*)cCommand,"AT+HFPSTAT\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketHFPAnswerCallWhenBeCalled:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+HFANSW\r\n");
				strncpy((char*)cCommand,"AT+HFANSW\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketHFPRejectPhoneWhenCalling:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+HFCHUP\r\n");
				strncpy((char*)cCommand,"AT+HFCHUP\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketHFPDialTheNumber:
			{
				if(pData != NULL && pData->nCmdLen > 0)
				{
					CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
				}
			}
			break;
		case BTPacketHFPSendDTMFWhenCalling:
			{
				if(pData != NULL && pData->nCmdLen > 0)
				{
					CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
				}
			}
			break;
		case BTPacketHFPSwitchVoiceBetweenPhoneAndDevice:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+HFADTS\r\n");
				strncpy((char*)cCommand,"AT+HFADTS\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketHFPMICMute:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+HFMUTE\r\n");
				strncpy((char*)cCommand,"AT+HFMUTE\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketHFPRedial:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+HFBLDN\r\n");
				strncpy((char*)cCommand,"AT+HFBLDN\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketHFPDealCallWhenCalling:
			{
				if(pData != NULL && pData->nCmdLen > 0)
				{
					CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
				}
			}
			break;
		case BTPacketHFPVoiceCall:
			{
				if(pData != NULL && pData->nCmdLen > 0)
				{
					CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
				}
			}
			break;
		case BTPacketA2DPAquireA2DPState:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+A2DPSTAT\r\n");
				strncpy((char*)cCommand,"AT+A2DPSTAT\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketA2DPConnectAVRCP:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+A2DPCONN\r\n");
				strncpy((char*)cCommand,"AT+A2DPCONN\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketA2DPDisconnectA2DPAndAVRCP:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+A2DPDISC\r\n");
				strncpy((char*)cCommand,"AT+A2DPDISC\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketAVRCPAcquireAVRCPState:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+AVRCPSTAT\r\n");
				strncpy((char*)cCommand,"AT+AVRCPSTAT\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketAVRCPAPlayOrPause:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+PP\r\n");
				strncpy((char*)cCommand,"AT+PP\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketAVRCPAStopPlay:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+STOP\r\n");
				strncpy((char*)cCommand,"AT+STOP\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketAVRCPANext:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+FWD\r\n");
				strncpy((char*)cCommand,"AT+FWD\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketAVRCPAPrevious:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+BACK\r\n");
				strncpy((char*)cCommand,"AT+BACK\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketPBAPCAquirePBAPCState:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+PBSTAT\r\n");
				strncpy((char*)cCommand,"AT+PBSTAT\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketPBAPCSetUpPBAPConnection:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+PBCONN\r\n");
				strncpy((char*)cCommand,"AT+PBCONN\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketPBAPCDisconnectPBAP:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+PBDISC\r\n");
				strncpy((char*)cCommand,"AT+PBDISC\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketPBAPCDownPhoneBook:
			{
				if(pData != NULL && pData->nCmdLen > 0)
				{
					CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
				}
			}
			break;
		case BTPacketPBAPCCancelDownPhoneBook:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+PBABORT\r\n");
				strncpy((char*)cCommand,"AT+PBABORT\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketHIDAcequireHIDState:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+HIDSTAT\r\n");
				strncpy((char*)cCommand,"AT+HIDSTAT\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketHIDConnectPhoneAndPCActive:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+HIDCONN\r\n");
				strncpy((char*)cCommand,"AT+HIDCONN\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketHIDDisconnectHID:
			{
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+HIDDISC\r\n");
				strncpy((char*)cCommand,"AT+HIDDISC\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			}
			break;
		case BTPacketHIDKCUSendDataToHID:
		case BTPacketHIDCUSendDataToHID:
		case BTPacketHIDMCUSendDataToHID:
			{
				if(pData != NULL && pData->nCmdLen > 0)
				{
					CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
				}
			}
			break;
		default:
			{
				BTDEBUGINFO(L"%s : Bad Param",__FUNCTIONW__);
			}
	}
	return 0;
}
int CBTCommand::SendBTCommandBlock(BTPacketDataType_t eType,Block *pBlock)
{
	if(pBlock == NULL)
	{
		switch(eType)
	{
	case BTPacketReadSoftVersion:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+GVER\r\n");
			strncpy((char*)cCommand,"AT+GVER\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketReadLocalDeviceAddress:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+GLBA\r\n");
			strncpy((char*)cCommand,"AT+GLBA\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketReadLocalDeviceName:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+GLDN\r\n");
			strncpy((char*)cCommand,"AT+GLDN\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	//case BTPacketSetLocalDeviceName:
	//	{
	//		HBYTE cCommand[eMAXCMDLEN] = {0};
	//		HUINT nCmdlen = 0;
	//		if(pData != NULL)
	//		{
	//			if(pData != NULL && pData->nCmdLen > 0)
	//			{
	//				CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
	//			}
	//		} 	
	//	}
	//	break;
	case BTPacketListPairDevice:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+LSPD\r\n");
			strncpy((char*)cCommand,"AT+LSPD\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	//case BTPacketDeletePairDeviceList:
	//	{
	//		if(pData != NULL && pData->nCmdLen > 0)
	//		{
	//			CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
	//		}
	//	}
	//	break;
	/*case BTPacketConnectDeviceInPairList:
		{
			if(pData != NULL && pData->nCmdLen > 0)
			{
				CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
			}
		}
		break;*/
	case BTPacketUpVolume:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+VUP\r\n");
			strncpy((char*)cCommand,"AT+VUP\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketDownVolume:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+VDN\r\n");
			strncpy((char*)cCommand,"AT+VDN\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketReadPairPassword:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+GFPC\r\n");
			strncpy((char*)cCommand,"AT+GFPC\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketSetPairPassword:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+SFPC\r\n");
			strncpy((char*)cCommand,"AT+SFPC\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketEnterPairMode:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+EPRM=1\r\n");
			strncpy((char*)cCommand,"AT+EPRM=1\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketExitPairMode:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+EPRM=0\r\n");
			strncpy((char*)cCommand,"AT+EPRM=0\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketEnterTestMode:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+EUTM\r\n");
			strncpy((char*)cCommand,"AT+EUTM\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketLoadFailSafeDefaults:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+FACT\r\n");
			strncpy((char*)cCommand,"AT+FACT\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketSoftRestart:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+BOOT\r\n");
			strncpy((char*)cCommand,"AT+BOOT\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketDisconnectCurrentConnection:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+DSCA\r\n");
			strncpy((char*)cCommand,"AT+DSCA\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketInitialize:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+DSCA\r\n");
			strncpy((char*)cCommand,"AT+DSCA\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketSPPAcquireSSPState:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+SPPSTAT\r\n");
			strncpy((char*)cCommand,"AT+SPPSTAT\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketSPPConnectPhoneAndPCActive:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+SPPCONN\r\n");
			strncpy((char*)cCommand,"AT+SPPCONN\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTSPPDisConnetSPP:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+SPPDISC\r\n");
			strncpy((char*)cCommand,"AT+SPPDISC\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	//case BTPacketSPPSendDataToBT:
	//	{
	//		if(pData != NULL && pData->nCmdLen > 0)
	//		{
	//			CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
	//		}
	//	}
	//	break;
	case BTPacketGATTAcquireGATTState:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+GATTSTAT\r\n");
			strncpy((char*)cCommand,"AT+GATTSTAT\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	//case BTPacketGATTSendDataToBT:
	//	{
	//		if(pData != NULL && pData->nCmdLen > 0)
	//		{
	//			CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
	//		}
	//	}
	//	break;
	case BTPacketHFPAcqureHFPState:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+HFPSTAT\r\n");
			strncpy((char*)cCommand,"AT+HFPSTAT\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketHFPAnswerCallWhenBeCalled:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+HFANSW\r\n");
			strncpy((char*)cCommand,"AT+HFANSW\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketHFPRejectPhoneWhenCalling:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+HFCHUP\r\n");
			strncpy((char*)cCommand,"AT+HFCHUP\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	//case BTPacketHFPDialTheNumber:
	//	{
	//		if(pData != NULL && pData->nCmdLen > 0)
	//		{
	//			CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
	//		}
	//	}
	//	break;
	//case BTPacketHFPSendDTMFWhenCalling:
	//	{
	//		if(pData != NULL && pData->nCmdLen > 0)
	//		{
	//			CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
	//		}
	//	}
	//	break;
	case BTPacketHFPSwitchVoiceBetweenPhoneAndDevice:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+HFADTS\r\n");
			strncpy((char*)cCommand,"AT+HFADTS\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketHFPMICMute:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+HFMUTE\r\n");
			strncpy((char*)cCommand,"AT+HFMUTE\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketHFPRedial:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+HFBLDN\r\n");
			strncpy((char*)cCommand,"AT+HFBLDN\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	//case BTPacketHFPDealCallWhenCalling:
	//	{
	//		if(pData != NULL && pData->nCmdLen > 0)
	//		{
	//			CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
	//		}
	//	}
	//	break;
	//case BTPacketHFPVoiceCall:
	//	{
	//		if(pData != NULL && pData->nCmdLen > 0)
	//		{
	//			CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
	//		}
	//	}
	//	break;
	case BTPacketA2DPAquireA2DPState:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+A2DPSTAT\r\n");
			strncpy((char*)cCommand,"AT+A2DPSTAT\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketA2DPConnectAVRCP:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+A2DPCONN\r\n");
			strncpy((char*)cCommand,"AT+A2DPCONN\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketA2DPDisconnectA2DPAndAVRCP:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+A2DPDISC\r\n");
			strncpy((char*)cCommand,"AT+A2DPDISC\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketAVRCPAcquireAVRCPState:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+AVRCPSTAT\r\n");
			strncpy((char*)cCommand,"AT+AVRCPSTAT\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketAVRCPAPlayOrPause:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+PP\r\n");
			strncpy((char*)cCommand,"AT+PP\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketAVRCPAStopPlay:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+STOP\r\n");
			strncpy((char*)cCommand,"AT+STOP\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketAVRCPANext:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+FWD\r\n");
			strncpy((char*)cCommand,"AT+FWD\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketAVRCPAPrevious:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+BACK\r\n");
			strncpy((char*)cCommand,"AT+BACK\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketPBAPCAquirePBAPCState:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+PBSTAT\r\n");
			strncpy((char*)cCommand,"AT+PBSTAT\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketPBAPCSetUpPBAPConnection:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+PBCONN\r\n");
			strncpy((char*)cCommand,"AT+PBCONN\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketPBAPCDisconnectPBAP:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+PBDISC\r\n");
			strncpy((char*)cCommand,"AT+PBDISC\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	//case BTPacketPBAPCDownPhoneBook:
	//	{
	//		if(pData != NULL && pData->nCmdLen > 0)
	//		{
	//			CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
	//		}
	//	}
	//	break;
	case BTPacketPBAPCCancelDownPhoneBook:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+PBABORT\r\n");
			strncpy((char*)cCommand,"AT+PBABORT\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketHIDAcequireHIDState:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+HIDSTAT\r\n");
			strncpy((char*)cCommand,"AT+HIDSTAT\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketHIDConnectPhoneAndPCActive:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+HIDCONN\r\n");
			strncpy((char*)cCommand,"AT+HIDCONN\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketHIDDisconnectHID:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+HIDDISC\r\n");
			strncpy((char*)cCommand,"AT+HIDDISC\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketA2DPMute:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+A2DPMUTE=1\r\n");
			strncpy((char*)cCommand,"AT+A2DPMUTE=1\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketCancelA2DPMute:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+A2DPMUTE=0\r\n");
			strncpy((char*)cCommand,"AT+A2DPMUTE=0\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case BTPacketGetA2DPMute:
		{
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+A2DPMUTE\r\n");
			strncpy((char*)cCommand,"AT+A2DPMUTE\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		break;
	case	BTPacketSetLocalDeviceName:
	case BTPacketDeletePairDeviceList:
	case BTPacketConnectDeviceInPairList:
	case BTPacketSPPSendDataToBT:
	case BTPacketGATTSendDataToBT:
	case BTPacketHFPDialTheNumber:
	case BTPacketHFPSendDTMFWhenCalling:
	case BTPacketHFPDealCallWhenCalling:
	case BTPacketHFPVoiceCall:
	case BTPacketPBAPCDownPhoneBook:
	//case BTPacketSetLocalDeviceName:
	case BTPacketHIDKCUSendDataToHID:
	case BTPacketHIDCUSendDataToHID:
	case BTPacketHIDMCUSendDataToHID:
		{
			//if(pData != NULL && pData->nCmdLen > 0)
			if(pBlock != NULL)
			{
				sCommandData *pData = (sCommandData *)(pBlock->Buf);
				CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
				if(pBlock != NULL)
				{
					CCommandPool::Intance()->PoolDelete(pBlock);
				}
			}
		}
		break;
	default:
		{
			BTDEBUGINFO(L"%s : Bad Param",__FUNCTIONW__);
		}
	}
	}
	else
	{
		sCommandData *pData = (sCommandData *)(pBlock->Buf);
		CBTCommand::Instance()->SendData(pData->szCommand,pData->nCmdLen);
		if(pBlock != NULL)
		{
			CCommandPool::Intance()->PoolDelete(pBlock);
		}
	}
	return 0;
}
void CBTCommand::SendBTCommandToQueue(BTPacketDataType_t eType,sCommandData *pData)
{
  if(m_hWnd != NULL)
  {
	  PostMessage(m_hWnd,WM_USER + 50,(WPARAM)eType,(LPARAM)pData);//发送BT命令
  }
}
void CBTCommand::SendBTCommandBlockToQueue(BTPacketDataType_t eType,Block *pBlock)
{
	if(m_hWnd != NULL)
	{
		PostMessage(m_hWnd,WM_USER + 50,(WPARAM)eType,(LPARAM)pBlock);//发送BT命令
	}
}
void CBTCommand::ReadDeviceNameFromFile()
{
	HString appPath;
	HCHAR	 szPath[MAX_PATH] = {0};
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	appPath += szPath;
	HINT nPos = (HINT)appPath.rfind(_T('\\'));
	if(nPos == -1)
	{
		wprintf(L"[HCSourceBase::GetExePath] exe path error ");
		//return false;
	}
	appPath = appPath.substr(0, nPos+1);
	appPath += L"..\\Config\\ZoyteBTName.txt";
	char szName[100] = {0};
	ifstream examplefile2(appPath.c_str());
	if(examplefile2.is_open())
	{
		int nLine = 0;
		while (! examplefile2.eof()) 
		{
			nLine++;
			memset(szName,0,sizeof(szName));
			examplefile2.getline (szName,100);
			if(m_pBTCommandData != NULL)
			{
				switch (nLine)
				{
					case 1:
					{
						memset(m_pBTCommandData->BTGeneralData.ZotyeDeviceINFO.LocaLDeviceINFO.szDeviceName,0,sizeof(m_pBTCommandData->BTGeneralData.ZotyeDeviceINFO.LocaLDeviceINFO.szDeviceName));
						memcpy(m_pBTCommandData->BTGeneralData.ZotyeDeviceINFO.LocaLDeviceINFO.szDeviceName,szName,30);
					}
					break;
					case 2:
					{
						memset(m_pBTCommandData->BTGeneralData.ZotyeDeviceINFO.szPairCode,0,sizeof(m_pBTCommandData->BTGeneralData.ZotyeDeviceINFO.szPairCode));
						memcpy(m_pBTCommandData->BTGeneralData.ZotyeDeviceINFO.szPairCode,szName,30);
					}
					break;
					default:
					break;
				}
			}
		}
		examplefile2.close();
	}
	else
	{
		ofstream examplefile (appPath.c_str());
		if (examplefile.is_open()) 
		{
			srand(static_cast<unsigned>(GetTickCount()));
			int nRandNum = 1000+(rand()%9000); 
			memset(szName,0,sizeof(szName));
			HINT nlen = strlen("Zotye Audio");
			memcpy(szName,"Zotye Audio",nlen);
			_itoa(nRandNum,szName + nlen,10);
			if(m_pBTCommandData != NULL)
			{
				memset(m_pBTCommandData->BTGeneralData.ZotyeDeviceINFO.LocaLDeviceINFO.szDeviceName,0,sizeof(m_pBTCommandData->BTGeneralData.ZotyeDeviceINFO.LocaLDeviceINFO.szDeviceName));
				memcpy(m_pBTCommandData->BTGeneralData.ZotyeDeviceINFO.LocaLDeviceINFO.szDeviceName,szName,30);
			}
			examplefile <<szName<<endl;
			memset(szName,0,sizeof(szName));
			for(int ii = 0;ii< 4;ii++)
			{
				szName[ii] = '0';
			}
			if(m_pBTCommandData != NULL)
			{
				memset(m_pBTCommandData->BTGeneralData.ZotyeDeviceINFO.szPairCode,0,sizeof(m_pBTCommandData->BTGeneralData.ZotyeDeviceINFO.szPairCode));
				memcpy(m_pBTCommandData->BTGeneralData.ZotyeDeviceINFO.szPairCode,szName,30);
			}
			examplefile <<szName;
			examplefile.close();
		}
	}
}
HINSTANCE CBTCommand::GetDriverDLL()
 {
	 return m_DriverDll;
 }
void CBTCommand::SaveBTLastMem()
{
	BTSETTING Setting = {0};

}
void CBTCommand::DisCurrentConnectDevice()
 {
	 BTDEBUGINFO(L"断开蓝牙连接");
	if(m_pBTCommandData != NULL)
	{
		if(m_pBTCommandData->BTHFPData.nHFPState >= 2)
		{
			HBYTE cCommand[30] = {0};
			HINT nlen = strlen("AT+DSCA\r\n");
			strncpy((char*)cCommand,"AT+DSCA\r\n",nlen);
			CBTCommand *p= CBTCommand::Instance();
			if(p != NULL)
			{
#ifdef  TESTBTCOMMANDQUEUE
				CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketDisconnectCurrentConnection,NULL);
#else
				p->SendData(cCommand,nlen);
#endif
			}
		}
	}
 }
HWND CBTCommand::GetMyHandel()
 {
	return m_hWnd;
 }
HINT CBTCommand::GetLetterFromNameGrp(HINT index,NameListGroup &sNameGrp)
{
	HINT iResult = 0;
	if(index >= 0 && (index +1) <= m_szNameList.nTotalContact)
	{
		for(int i = 0;i < 27;i++)
		{
			if((index + 1) <= m_szNameList.szTotalCount[i])
			{
				return i;
			}
		}
	}
	return iResult;
}
void CBTCommand::TotalCountNameGrp(NameListGroup &sNameGrp)
{
	//int temp = 0;
	m_szNameList.szTotalCount[0] = m_szNameList.szCount[0];
	for(int i = 0;i < 26;i++)
	{
		m_szNameList.szTotalCount[i+1] =	m_szNameList.szTotalCount[i] + m_szNameList.szCount[i+1];
		//BTDEBUGINFO(L"count[%d] = %d,Totalcount[%d] = %d",i,m_szNameList.szCount[i],i,m_szNameList.szTotalCount[i]);
	}
	//BTDEBUGINFO(L"count[26] = %d,Totalcount[26] = %d",m_szNameList.szCount[26],m_szNameList.szTotalCount[26]);
}
void CBTCommand::TotalCountNameGrp(NameListGroup &sNameGrp,HINT nBeg,HINT nEnd)
{
	if(nBeg >= 0 && nEnd <= 26 && nBeg < nEnd)
	{
		//int i = nBeg
		for(int i = nBeg;i < nEnd -1;i++)
		{
			m_szNameList.szTotalCount[i +1 ] =	m_szNameList.szTotalCount[i] + m_szNameList.szCount[i+1];
			//BTDEBUGINFO(L"count[%d] = %d,Totalcount[%d] = %d",i,m_szNameList.szCount[i],i,m_szNameList.szTotalCount[i]);
		}
	}
}
HINT CBTCommand::GetListGrpIndex(HINT iStart,HINT &nCurrentList)
{
	nCurrentList = 0;
	HINT nIndexInList = 0;
	if(iStart > m_szNameList.nTotalContact)
	{
		nCurrentList = -1;
	}
	else
	{
		HINT nTotal = 0;
		HINT nNumber = m_szNameList.pContact[nCurrentList].size();
		while (iStart > (nTotal + nNumber))
		{
			nTotal += nNumber;
			nCurrentList++;
			nNumber = m_szNameList.pContact[nCurrentList].size();
		}
		nIndexInList = iStart - nTotal;
	}
	BTDEBUGINFO(L"iStart = %d,nCurrentList = %d,nIndexInList = %d", iStart,nCurrentList,nIndexInList);
	return nIndexInList;
}

void CBTCommand::SetHDMI(bool bIN)
{
	m_bInHDMI = bIN;
}
bool CBTCommand::GetHDMI()
{
	return m_bInHDMI;
}
bool CBTCommand::IsNumberLegal(HBYTE *pBeg,HINT nLen)
{
	if(pBeg != NULL && nLen > 0)
	{
		for(HINT n = 0; n < nLen;n++)
		{
			if((*(pBeg + n)) == ' ' || (*(pBeg + n)) == '-' || (*(pBeg + n)) == '*' || (*(pBeg + n)) == '+' || (*(pBeg + n) >= '0' && *(pBeg + n) <= '9') || *(pBeg + n) == '#' || *(pBeg + n) == 0)
			{
				n++;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	return false;
}
void CBTCommand::SendGetBTInfo()
{
#ifdef  TESTBTCOMMANDQUEUE
	CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketReadLocalDeviceAddress,NULL);
	CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketReadLocalDeviceName,NULL);
	CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketReadPairPassword,NULL);
	CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketReadSoftVersion,NULL);
	CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketListPairDevice,NULL);
#else
	HBYTE cCommand[20] = {0};
	HUINT nCmdlen = strlen("AT+GLDN\r\n");
	strncpy((char*)cCommand,"AT+GLDN\r\n",nCmdlen);
	CBTCommand::Instance()->SendData(cCommand,nCmdlen);
	nCmdlen = strlen("AT+GFPC\r\n");
	strncpy((char*)cCommand,"AT+GFPC\r\n",nCmdlen);
	CBTCommand::Instance()->SendData(cCommand,nCmdlen);
	nCmdlen = strlen("AT+GVER\r\n");
	strncpy((char*)cCommand,"AT+GVER\r\n",nCmdlen);
	CBTCommand::Instance()->SendData(cCommand,nCmdlen);
	nCmdlen = strlen("AT+LSPD\r\n");
	strncpy((char*)cCommand,"AT+LSPD\r\n",nCmdlen);
	CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
}