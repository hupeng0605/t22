#pragma once
#include "BTHmi.h"
#include "KCBTDialogManager.h"
CBTHmiDlg::CBTHmiDlg( )
{
	m_pTxtBk = NULL;
	m_bPhoneReady = false;
	m_bBTConneted = false;
	m_bBTHIDConnected = false;
	m_bBTSPPConnected = false;
	m_hAVD = INVALID_HANDLE_VALUE;
	m_HandleCheck = INVALID_HANDLE_VALUE;
	m_bPositionInZero = false;
	m_nBackToZero = 0;
	m_PosCurrentCePostion.x = 0;
	m_PosCurrentCePostion.y = 0;
	m_bHMIShow = false;
	m_nHMIState = 100;
	 m_pUnInitCameraPreview = NULL;
	 m_pReleaseCameraPreviewRsc = NULL;
	 m_pStopCameraPreview = NULL;
}
CBTHmiDlg::~CBTHmiDlg( )
{
	SAFE_DELETE(m_pTxtBk);
	m_bPhoneReady = false;
	m_bBTConneted = false;
	m_bBTHIDConnected = false;
	m_bBTSPPConnected = false;
	m_bHMIShow = false;
	m_HandleCheck = INVALID_HANDLE_VALUE;
	if(m_hDll != NULL)
	{
		//FreeLibrary(m_hDll);
	}
}
HINT CBTHmiDlg::OnInit()
{
	m_pTxtBk = new HCTextCtrl;
	m_bBTNoticeShow = false;
	 sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
	if(pSource != NULL)
	{
		if(m_pTxtBk != NULL)
		{
			m_pTxtBk->Create(0,0,800,480);
			if(pSource->m_pbtHmiBk != NULL)
			{
				//m_pTxtBk->SetBkgndN(pSource->m_pbtHmiBk);
				//ChangeLanguage(0);
			}
			m_pTxtBk->SetShow(true);
			AddChild(m_pTxtBk);
		}
	}
	m_nHMIState = 100;
	m_bPhoneReady = false;
	m_bBTConneted = false;
	m_bBTHIDConnected = false;
	m_bBTSPPConnected = false;
	m_bSourceRealse = true;
	m_hAVD = INVALID_HANDLE_VALUE;
	//m_HandelTemp = INVALID_HANDLE_VALUE;
//	AddTimer(&m_ctTimeToBackToZero);
	//m_ctTimeToBackToZero.SetCallBack(BackToZero,this);
	//AddTimer(&m_ctSingel);
	//m_ctSingel.SetCallBack(OnCheckForReady,this);
	m_nBackToZero = 100;
	m_nCout = 0;
	m_ctNotice.SetCallBack(OnBTNoticeShow,this);
	AddTimer(&m_ctNotice);
	m_PosCurrentCePostion.x = 0;
	m_PosCurrentCePostion.y = 0;
	m_bHMIShow = false;
	m_pGetCameraSignalStatus = NULL;
	m_HandleCheck = INVALID_HANDLE_VALUE;
	//m_hDll = NULL;
	//m_pGetCameraSignalStatus = NULL;
	m_hDll = NULL;
//	AddTimer(&m_ctStateManage);
	//m_ctStateManage.SetCallBack(StateMange,this);
	//m_hDll = LoadLibraryW(L"\\Windows\\DriverAPI.dll");
	m_hDll = CBTCommand::Instance()->GetDriverDLL();
	//HINSTANCE hDll = LoadLibrary(TEXT("\\Windows\\DriverAPI.dll"));
	pClearLayeredWindowBuffer pFun = NULL; 
	if(m_hDll != NULL)
	{
		pFun=  (pClearLayeredWindowBuffer)GetProcAddress(m_hDll,_T("ClearLayeredWindowBuffer")); 
	}
	if(pFun != NULL)
	{
		pFun(m_hAVD,WIN_MEDIA);
		BTDEBUGINFO(L"ClearLayeredWindowBuffer success!");
	}
	if(m_hDll != NULL)
	{
		m_pGetCameraSignalStatus = (pGetCameraSignalStatus)GetProcAddress(m_hDll,_T("GetCameraSignalStatus"));
		m_pInitCameraPreview = (pInitCameraPreview)GetProcAddress(m_hDll,_T("InitCameraPreview"));
		m_pRequestCameraPreviewRsc = (pRequestCameraPreviewRsc)GetProcAddress(m_hDll,_T("RequestCameraPreviewRsc"));
		m_pSetCameraPreviewChannel =  ( pSetCameraPreviewChannel )GetProcAddress(m_hDll,_T("SetCameraPreviewChannel"));  
		m_pInitLayeredWindow = (pInitLayeredWindow)GetProcAddress(m_hDll,_T("InitLayeredWindow"));
		m_pRequestLayeredWindowRsc =(pRequestLayeredWindowRsc)GetProcAddress(m_hDll,_T("RequestLayeredWindowRsc")); 
		m_pGetLayeredWindowPhyFreBuffer = (pGetLayeredWindowPhyFreBuffer)GetProcAddress(m_hDll,_T("GetLayeredWindowPhyFreBuffer"));
		m_pSetLayeredWindowPosition = (pSetLayeredWindowPosition)GetProcAddress(m_hDll,_T("SetLayeredWindowPosition"));
		m_pSetLayeredWindowAlpha = (pSetLayeredWindowAlpha)GetProcAddress(m_hDll,_T("SetLayeredWindowAlpha"));
		m_pSetLayeredWindowColorKey = (pSetLayeredWindowColorKey)GetProcAddress(m_hDll,_T("SetLayeredWindowColorKey"));
		m_pOpenLayeredWindow = (pOpenLayeredWindow)GetProcAddress(m_hDll,_T("OpenLayeredWindow"));
		 m_pUnInitCameraPreview = (pUnInitCameraPreview)GetProcAddress(m_hDll,_T("UnInitCameraPreview"));
		 m_pReleaseCameraPreviewRsc = (pReleaseCameraPreviewRsc)GetProcAddress(m_hDll,_T("ReleaseCameraPreviewRsc"));
		 m_pStopCameraPreview = (pStopCameraPreview)GetProcAddress(m_hDll,_T("StopCameraPreview"));
		if(m_pInitCameraPreview == NULL || m_pGetCameraSignalStatus == NULL)
		{
			BTDEBUGINFO(L"m_pInitCameraPreview|m_pGetCameraSignalStatus = NULL");

		}
	}
	//FreeLibrary(hDll);
	if(m_pInitCameraPreview != NULL)
	{
		if(m_HandleCheck == INVALID_HANDLE_VALUE)
		{
			//m_HandleCheck = m_pInitCameraPreview();
			//m_pRequestCameraPreviewRsc(m_HandleCheck);
			//m_pSetCameraPreviewChannel(m_HandleCheck,CAM_PRE_VGA);
		}
	}
	//ShowHMIVidio();
	//OnCheckForReady(NULL);
	return 0;
}

void CBTHmiDlg::ShowHMIVidio()
{
	BTDEBUGINFO(L"%s",__FUNCTIONW__);
	/*m_hDll = NULL;
	m_hDll = LoadLibraryW(L"\\Windows\\DriverAPI.dll");
	HINSTANCE hDll = LoadLibrary(TEXT("\\Windows\\DriverAPI.dll"));
	pClearLayeredWindowBuffer pFun = NULL; 
	if(hDll != INVALID_HANDLE_VALUE)
	{
		pFun=  (pClearLayeredWindowBuffer)GetProcAddress(hDll,_T("ClearLayeredWindowBuffer")); 
	}
	if(pFun != NULL)
	{
		pFun(m_hAVD,WIN_MEDIA);
		BTDEBUGINFO(L"ClearLayeredWindowBuffer success!");
	}

	if(m_hDll != NULL)
	{
		m_pGetCameraSignalStatus = (pGetCameraSignalStatus)GetProcAddress(m_hDll,_T("GetCameraSignalStatus"));
		m_pInitCameraPreview = (pInitCameraPreview)GetProcAddress(m_hDll,_T("InitCameraPreview"));
		if(m_pInitCameraPreview == NULL || m_pGetCameraSignalStatus == NULL)
		{
			BTDEBUGINFO(L"m_pInitCameraPreview|m_pGetCameraSignalStatus = NULL");
		
		}
	}*/
	//RequreSource();
	if(!(m_pTxtBk->IsShow()))
	{
		m_pTxtBk->SetShow(true);
	}
	OpenCheckHandle();
#ifdef  TESTBTCOMMANDQUEUE
	//CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketA2DPDisconnectA2DPAndAVRCP,NULL);
#else 
	HBYTE cCommand  [20] = {0};
	HUINT nCmdlen = strlen("AT+A2DPDISC\r\n");
	strncpy((char*)cCommand,"AT+A2DPDISC\r\n",nCmdlen);
	CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
  if(m_hAVD == INVALID_HANDLE_VALUE)
  {
	  m_hAVD = CreateFile( L"SCA0:",
		  GENERIC_READ | GENERIC_WRITE,
		  FILE_SHARE_READ | FILE_SHARE_WRITE,
		  NULL,
		  OPEN_EXISTING,
		  FILE_ATTRIBUTE_NORMAL,
		  NULL );
	  BTDEBUGINFO(L"CreateFile:SCA0");
	 // m_hAVD = m_HandleCheck;
  }
	  if(m_hAVD == INVALID_HANDLE_VALUE)
	  {
			BTDEBUGINFO(L"m_hAVD 文件创建失败！");
	  }
	  else
	  {
		  SetDisplayMute(m_hAVD,SCA_DEST_MAIN,TRUE);
		  DWORD dd = 0;
		  DWORD dwBytesReturned = 0;
		  SCA_CHANGE_WINDOW_CONFIG stChangeWin;
		  memset(&stChangeWin, 0, sizeof(SCA_CHANGE_WINDOW_CONFIG));
		  stChangeWin.enSrcType = SCA_SRC_VGA;
		  stChangeWin.enDestType = SCA_DEST_MAIN ;
		  stChangeWin.stWinConfig.bDispWin = TRUE;
		  stChangeWin.stWinConfig.stDispWin.x  = 0;
		  stChangeWin.stWinConfig.stDispWin.y  = 0;
		  stChangeWin.stWinConfig.stDispWin.width =  800;
		  stChangeWin.stWinConfig.stDispWin.height=  480;
		  stChangeWin.bImmediateUpdate = true;
		  if(DeviceIoControl(m_hAVD, IOCTL_SCA_CHANGE_WINDOW, (LPVOID)&stChangeWin, sizeof(SCA_CHANGE_WINDOW_CONFIG), NULL, 0, &dwBytesReturned, 0) == FALSE)
		  {
			  BTDEBUGINFO(L"IOCTL_SCA_CHANGE_WINDOW FAIL !\n");
			  DWORD dd = GetLastError();
			  BTDEBUGINFO(L"IOCTL_SCA_CHANGE_WINDOW FAIL:%d",dd);
		  }
			SCA_CONNECT_CONFIG stConnectCfg;
		  memset(&stConnectCfg, 0, sizeof(SCA_CONNECT_CONFIG));
		  stConnectCfg.bAutoDetect     = TRUE;
		  stConnectCfg.enSrcType       = SCA_SRC_VGA;
		  stConnectCfg.enDestType      = SCA_DEST_MAIN;
		  stConnectCfg.enPriType       = SCA_DISP_PRI_NORMAL;
		  stConnectCfg.lpEvtConnetName =L"_SCA_CONNECT_V0";
		  if(DeviceIoControl(m_hAVD, IOCTL_SCA_SOURCE_CONNECT, (LPVOID)&stConnectCfg, sizeof(SCA_CONNECT_CONFIG), NULL, 0, &dwBytesReturned, 0) == FALSE)
		  {
			  BTDEBUGINFO(_T("IOCTL_SCA_SOURCE_CONNECT FAIL !\n"));
			  dd = GetLastError();
			  BTDEBUGINFO(L"IOCTL_SCA_SOURCE_CONNECT FAIL:%d",dd);
		  }
		  SetDisplayMute(m_hAVD,SCA_DEST_MAIN,FALSE);
		  SCA_COLOR_KEY stClrKey;
		  stClrKey.View = 0;
		  //stClrKey.u8R = MSTAR_COLOR_KEY_R;
		 // stClrKey.u8G = MSTAR_COLOR_KEY_G;
		  //stClrKey.u8B = MSTAR_COLOR_KEY_B;
		  stClrKey.u8R = 0x18;
		  stClrKey.u8G = 0x30;
		  stClrKey.u8B = 0x18;
		  stClrKey.Benable = TRUE;
		 dwBytesReturned = 0;
		  if(DeviceIoControl(m_hAVD, IOCTL_SCA_SET_COLOR_Key, (LPVOID)&stClrKey, sizeof(SCA_COLOR_KEY),
			  NULL, 0, &dwBytesReturned, NULL) == FALSE)//访问设备驱动程序
		  {
			  BTDEBUGINFO(L"IOCTL_SCA_SET_COLOR_Key FAIL !\n");
			  dd = GetLastError();
			  BTDEBUGINFO(L"IOCTL_SCA_SET_COLOR_Key FAIL:%d",dd);
		  }
		 // SCA_COLOR_KEY stClrKey;
		  stClrKey.View = 1;
	/*	stClrKey.u8R = MSTAR_COLOR_KEY_R;
		  stClrKey.u8G = MSTAR_COLOR_KEY_G;
		  stClrKey.u8B = MSTAR_COLOR_KEY_B;*/
		  stClrKey.u8R = 0x18;
		  stClrKey.u8G = 0x30;
		  stClrKey.u8B = 0x18;
		  stClrKey.Benable = TRUE;
		  dwBytesReturned = 0;
		  if(DeviceIoControl(m_hAVD, IOCTL_SCA_SET_COLOR_Key, (LPVOID)&stClrKey, sizeof(SCA_COLOR_KEY),
			  NULL, 0, &dwBytesReturned, NULL) == FALSE)//访问设备驱动程序
		  {
			  BTDEBUGINFO(L"IOCTL_SCA_SET_COLOR_Key FAIL !\n");
			  dd = GetLastError();
			  BTDEBUGINFO(L"IOCTL_SCA_SET_COLOR_Key FAIL:%d",dd);
		  }
	  }
	  sBTCommandData *pBtData= CBTCommand::Instance()->GetBTCommandData();
	  if(pBtData != NULL)
	  {
//#ifdef  TESTBTCOMMANDQUEUE
//			 CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketSPPAcquireSSPState,NULL);
//#else 
//			  HBYTE cCommand[20] ={0};
//			  HINT nCmdlen = 0;	
//			  nCmdlen = strlen("AT+SPPSTAT\r\n");
//			  strncpy((char*)cCommand,"AT+SPPSTAT\r\n",nCmdlen);
//			  CBTCommand::Instance()->SendData(cCommand,nCmdlen);
//#endif
	  }
	/*if(m_ctTimeToBackToZero.IsActive())
	  {
		  m_ctTimeToBackToZero.StopTimer();
	  }
	  m_ctTimeToBackToZero.SetTime(m_nBackToZero);
	  m_ctTimeToBackToZero.StartTimer();*/
	  m_bHMIShow = true;
	/*  if(m_ctStateManage.IsActive())
	  {
		  m_ctStateManage.StopTimer();
	  }
	  StateMange(NULL);*/
	 // m_ctStateManage.SetTime(100);
	//  m_ctStateManage.StartTimer();
  //HBYTE cCommand  [50] = {0};
  //HUINT nCmdlen =0;
  //sBTCommandData* pBTData = CBTCommand::Instance()->GetBTCommandData();
  //if(pBTData->BTHFPData.nHFPState >=2 && pBTData->BTSPPData.nSPPState == 0)
  //{
	 // nCmdlen = strlen("AT+SPPCONN\r\n");
	 // strncpy((char*)cCommand,"AT+SPPCONN\r\n",nCmdlen);
	 // CBTCommand::Instance()->SendData(cCommand,nCmdlen);
  //}
	  BTDEBUGINFO(L"%s:m_HandleCheck = %d",__FUNCTIONW__,m_HandleCheck);
}
void CBTHmiDlg::CloseHMIVidio()
{
	/*if(m_ctStateManage.IsActive())
	{
		m_ctStateManage.StopTimer();
	}*/
	CloseCheckHandle();
#ifdef  TESTBTCOMMANDQUEUE
	//CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketA2DPConnectAVRCP,NULL);
#else 
	HBYTE cCommand  [20] = {0};
	HUINT nCmdlen = strlen("AT+A2DPCONN\r\n");
	strncpy((char*)cCommand,"AT+A2DPCONN\r\n",nCmdlen);
	CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
	if(m_hAVD != INVALID_HANDLE_VALUE)
	{
		SetDisplayMute(m_hAVD,SCA_DEST_MAIN,TRUE);
		DisConnectAutoDetct(m_hAVD,SCA_DEST_MAIN);
		HINSTANCE hDll = LoadLibrary(TEXT("\\Windows\\DriverAPI.dll"));
		pClearLayeredWindowBuffer pFun = NULL; 
		if(hDll != INVALID_HANDLE_VALUE)
		{
			pFun=  (pClearLayeredWindowBuffer)GetProcAddress(hDll,_T("ClearLayeredWindowBuffer")); 
		}
		if(pFun != NULL)
		{
			//pFun(m_hAVD,WIN_MEDIA);
			BTDEBUGINFO(L"ClearLayeredWindowBuffer success!");
		}
	//	FreeLibrary(hDll);
		CloseHandle(m_hAVD);
		//CloseHandle(m_HandleCheck);
	  /*if(m_ctTimeToBackToZero.IsActive())
		{
			m_ctTimeToBackToZero.StopTimer();
		}*/
		//m_HandleCheck = INVALID_HANDLE_VALUE;
		m_hAVD = INVALID_HANDLE_VALUE;
	}
	m_bHMIShow = false;
	//m_pGetCameraSignalStatus = NULL;
	//m_pInitCameraPreview = NULL;
	if(!(m_pTxtBk->IsShow()))
	{
		m_pTxtBk->SetShow(true);
	}
	//bool bTimeActive = m_ctSingel.IsActive();
	//BTDEBUGINFO(L"bTimeActive = %d",bTimeActive);
    ReleaseSource();
	BTDEBUGINFO(L"%s",__FUNCTIONW__);
}
//HBOOL CBTHmiDlg::DoMessage(HMessage* msg)
//{
//	HBOOL bRet = false;
//	if(msg != NULL)
//	{
//		bRet = HDialogBase::DoMessage(msg);
//		if(!bRet)
//		{
//			switch((HINT)msg->msgtype)
//			{
//				case WM_USER:
//				{
//
//				}
//				break;
//				default:
//				{
//			
//				}
//				break;
//
//			}
//		}
//	}
//	return bRet;
//}
void CBTHmiDlg::SetSPPConnected(bool bConnected)
{
		m_bBTSPPConnected = bConnected;
}
void CBTHmiDlg::SetHIDConnected(bool bConnected)
{
	m_bBTSPPConnected = bConnected;
}
void CBTHmiDlg::SetDisplayMute(HANDLE hDeviceFile, SCA_DEST_TYPE eDestType, BOOL bMuteOn)
{
	SCA_DISPLAY_MUTE_CONFIG stDisplayMuteCfg;
	DWORD	dwBytesReturned;
	stDisplayMuteCfg.bEn = bMuteOn;
	stDisplayMuteCfg.enDestType = eDestType;
	if(DeviceIoControl (hDeviceFile, IOCTL_SCA_DISPLAY_MUTE,
		&stDisplayMuteCfg, sizeof(SCA_DISPLAY_MUTE_CONFIG),
		NULL, 0, &dwBytesReturned, 0) == FALSE)
	{
		BTDEBUGINFO(_T("IOCTL_SCA_DISPLAY_MUTE FAIL !\n"));
		DWORD dd = GetLastError();
		BTDEBUGINFO(L"IOCTL_SCA_DISPLAY_MUTE FAIL:%d",dd);
	}
}
void CBTHmiDlg::DisConnectAutoDetct(HANDLE hDeviceFile, SCA_DEST_TYPE enCurDest)
{
	DWORD dwBytesReturned;
	SCA_CONNECT_CONFIG stConnectCfg;
	memset(&stConnectCfg, 0, sizeof(SCA_CONNECT_CONFIG));
	stConnectCfg.bAutoDetect = TRUE;
	stConnectCfg.enSrcType   =SCA_SRC_VGA;
	stConnectCfg.enDestType  = enCurDest;
	BTDEBUGINFO(L"\r\nDeviceIoControl():hDeviceFile = %d,IOCTL_SCA_SOURCE_DISCONNECT,stConnectCfg:stConnectCfg.bAutoDetect = true,stConnectCfg.enSrcType = %d,stConnectCfg.enDestType  = %d\r\n",(int)hDeviceFile,(int)stConnectCfg.enSrcType,(int)stConnectCfg.enDestType);
	if(DeviceIoControl(hDeviceFile, IOCTL_SCA_SOURCE_DISCONNECT, (LPVOID)&stConnectCfg, sizeof(SCA_CONNECT_CONFIG), NULL, 0, &dwBytesReturned, 0) == FALSE)
	{
		BTDEBUGINFO(_T("IOCTL_SCA_SOURCE_DISCONNECT FAIL !\n"));
		DWORD dd = GetLastError();
		BTDEBUGINFO(L"IOCTL_SCA_SOURCE_DISCONNECT FAIL:%d",dd);
	}
}

void CBTHmiDlg::Draw( IReSurface* pSurface )
{
	if (NULL == pSurface)
	{
		return;
	}
	if( GetUpdateRectVector().empty() )
	{
		kn_rect c = kn_rect(0,0,m_width,m_height);
		//InvalidateRect(kn_rect(0,0,m_width,m_height));
		InvalidateRect(c);
	}
	if (m_pTxtBk->IsShow())
	{
		int x = 0;
		int y = 0;
		m_pTxtBk->GetPosition(x,y);
		m_pTxtBk->DrawBaseCtrl(pSurface, x, y);
	}
	else
	{
		//RECOLOR corBG(MSTAR_COLOR_KEY_R, MSTAR_COLOR_KEY_G, MSTAR_COLOR_KEY_B);
		//RECOLOR corBG(8, 8, 8);
		RECOLOR corBG(0x18, 0x30, 0x18);
		pSurface->FillSolidRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,corBG);
	}
}
HBOOL CBTHmiDlg::DoMessage(HMessage *msg)
{
	sMyPhoneInfo *pinfo = CBTCommand::Instance()->GetMyPhoneInfo();
	HBOOL bRet = false;
	sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(NULL);
	sBTCommandData *pdata = CBTCommand::Instance()->GetBTCommandData();
	HINT nHfp = pdata->BTHFPData.nHFPState;
    if(msg != NULL && pinfo != NULL && m_bHMIShow)
	{
		bRet = HDialogBase::DoMessage(msg);
		if(!(pinfo->bPhoneLocked))
		{
			switch((HINT)msg->msgtype )
			{
			case KMSG_LBBUTTONDOWN:
				if(nHfp < 2 && pSource != NULL && m_nHMIState == 1)
				{
					BTDEBUGINFO(L"pSource->pbtHDMIBTNOTICECH = %d",pSource->pbtHDMIBTNOTICECH);
					m_pTxtBk->SetBkgndN(pSource->pbtHDMIBTNOTICECH);
					if(!m_pTxtBk->IsShow())
					{
						m_pTxtBk->SetShow(true);
					}

					m_bBTNoticeShow = true;
					if(m_ctNotice.IsActive())
					{
						m_ctNotice.StopTimer();
					}
					m_ctNotice.SetTime(200);
					m_ctNotice.StartTimer();
				}
			case KMSG_MOUSEMOVE:
			case KMSG_LBBUTTONUP:
				{
					/*HBYTE cCommand[50] = {0};
					HINT nlen = strlen("HID=6\r\n");
					strncpy((char*)cCommand,"HID=6\r\n",nlen);*/
					/*cCommand[nlen++] = 0x0a;
					cCommand[nlen++] = 0x12;
					cCommand[nlen++] = 0x05;*/
					//int x1 = 0;
					//int y1 =0;
					//x1 = msg->mousex - m_PosCurrentCePostion.x;
					//y1 = msg->mousey - m_PosCurrentCePostion.y;
					//int xx = CBTCommand::Instance()->CExToPhonex(x1,CBTCommand::Instance()->GetMyPhoneInfo()->PhoneWidth);
				   //int yy = CBTCommand::Instance()->CEyToPhoney(y1,CBTCommand::Instance()->GetMyPhoneInfo()->PhoneHight);
					if(m_pTxtBk->IsShow())
					{
						return true;
					}
					bool bResult = SendCEPositionToPhone(msg->mousex,msg->mousey,msg->msgtype);
					//BTDEBUGINFO(L"SendToPhone: x = %d, y = %d,type = %d",xx,yy,(int)msg->msgtype);
					if(bResult)
					{
						m_PosCurrentCePostion.x = msg->mousex;
						m_PosCurrentCePostion.y = msg->mousey;
					}
					else
					{
						m_PosCurrentCePostion.x = pinfo->iMaxAvailableCeWidth;//pinfo->iMinAvailableCeWidth;
						m_PosCurrentCePostion.y = pinfo->iMaxAvailableCeHight;//pinfo->iMinAvailableCeHight;
					}
					if(msg->msgtype == KMSG_LBBUTTONUP)
					{
						BackToZero(NULL);
					}		
					/*cCommand[nlen++] = HIBYTE(xx);
					cCommand[nlen++] = LOBYTE(xx);
					cCommand[nlen++] = HIBYTE(yy);
					cCommand[nlen++] = LOBYTE(yy);
					cCommand[nlen++] = 0;
					switch(msg->msgtype)
					{
					case KMSG_LBBUTTONUP:
						{
							cCommand[nlen++] = 0x00;
						}
						break;
					case KMSG_LBBUTTONDOWN:
						{
							cCommand[nlen++] = 0x00;
						}*/
					bRet = true;
					}
					break;
				default:
				break;
				}
			}
		}	
	return bRet;
}
void CBTHmiDlg::SendPhonePosition(int x,int y,char Type)//type:按键类型
{
		HBYTE cCommand[50] = {0};
		HINT nlen = strlen("HIDp=6\r\n");
		strncpy((char*)cCommand,"HIDp=6\r\n",nlen);
		cCommand[nlen++] = LOBYTE(x);
		cCommand[nlen++] = HIBYTE(x);
		cCommand[nlen++] = LOBYTE(y);
		cCommand[nlen++] = HIBYTE(y);
		cCommand[nlen++] = 0;
		cCommand[nlen++] =(HBYTE)Type;
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
		/*if(m_ctTimeToBackToZero.IsActive())
			{
				m_ctTimeToBackToZero.StopTimer();
			}
			m_ctTimeToBackToZero.SetTime(m_nBackToZero);
			m_ctTimeToBackToZero.StartTimer();
		*/
		BTDEBUGINFO(L"SendPhonePosition::x = %d ,y = %d ,Ctype = %d",x,y,Type);
}
bool CBTHmiDlg::SendCEPositionToPhone(int x,int y,KMESSAGETYPE eType)
{
	CBTCommand* p = CBTCommand::Instance();
	if(p != NULL)
	{
		HBYTE cCommand[50] = {0};
		//HINT nlen = strlen("HID=6\r\n");
		//strncpy((char*)cCommand,"HID=6\r\n",nlen);
		HINT nlen = strlen("HIDp=6\r\n");
		strncpy((char*)cCommand,"HIDp=6\r\n",nlen);
		int x1 = p->CexToCeAviablex(x,p->GetMyPhoneInfo()->iAvailableCeWidth);
		int y1 = p->CeyToCeAviabley(y,p->GetMyPhoneInfo()->iAvailableCeHight);	
		if((x1 <0) || (y1 < 0))
		{
			return false;
		}
		int x0 = p->CexToCeAviablex(m_PosCurrentCePostion.x,p->GetMyPhoneInfo()->iAvailableCeWidth);
		int y0 = p->CeyToCeAviabley(m_PosCurrentCePostion.y,p->GetMyPhoneInfo()->iAvailableCeHight);
		int dx = x1-x0;
		int dy = y1 -y0;
		//m_PosCurrentCePostion.x = x;
		//m_PosCurrentCePostion.y = y;
		int xx = p->CExToPhonex(dx,p->GetMyPhoneInfo()->PhoneWidth);
		int yy = p->CEyToPhoney(dy,p->GetMyPhoneInfo()->PhoneHight);
		cCommand[nlen++] = LOBYTE(xx);
		cCommand[nlen++] = HIBYTE(xx);
		cCommand[nlen++] = LOBYTE(yy);
		cCommand[nlen++] = HIBYTE(yy);
		cCommand[nlen++] = 0;
		switch(eType)
		{
			case KMSG_LBBUTTONUP:
			{
				cCommand[nlen++] = 0x00;
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
				/*if(m_ctTimeToBackToZero.IsActive())
				{
					m_ctTimeToBackToZero.StopTimer();
				}
					m_ctTimeToBackToZero.SetTime(m_nBackToZero);
					m_ctTimeToBackToZero.StartTimer();*/
				BTDEBUGINFO(L"SendPhonePosition::x = %d ,y = %d ,Ctype = %d",xx,yy,(HINT)eType);
				m_bPositionInZero = false;
			}
			break;
			case  KMSG_MOUSEMOVE:
			case KMSG_LBBUTTONDOWN:
			{
				cCommand[nlen++] = 0x01;
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
			/*	if(m_ctTimeToBackToZero.IsActive())
				{
					m_ctTimeToBackToZero.StopTimer();
				}*/
				/*	m_ctTimeToBackToZero.SetTime(m_nBackToZero);
					m_ctTimeToBackToZero.StartTimer();*/
				BTDEBUGINFO(L"SendPhonePosition::x = %d ,y = %d ,Ctype = %d",xx,yy,(HINT)eType);
				m_bPositionInZero = false;
				return true;
			}
			break;
			default:
			break;
		}
	}
	return false;
}
void CBTHmiDlg::BackToZero(void* pDlg, void* param)
{
	CBTHmiDlg* pObj = (CBTHmiDlg*)pDlg;
	pObj->BackToZero(pObj);
}
void CBTHmiDlg::BackToZero(void* pDlg)
{
	sMyPhoneInfo *pinfo = CBTCommand::Instance()->GetMyPhoneInfo();
   if(!m_bPositionInZero && pinfo != NULL)
   {
	  /* if(m_ctTimeToBackToZero.IsActive())
	   {
		   m_ctTimeToBackToZero.StopTimer();
	   }
	   m_ctTimeToBackToZero.SetTime(m_nBackToZero);
	   m_ctTimeToBackToZero.StartTimer();*/
	 //  SendPhonePosition(-3000,-2500,0x00);
	   //m_PosCurrentCePostion.x = pinfo->iMinAvailableCeWidth;
	   //m_PosCurrentCePostion.y = pinfo->iMinAvailableCeHight;
	   //SendPhonePosition(3000,2500,0x00);
	   SendPhonePosition(2*pinfo->PhoneWidth,2*pinfo->PhoneHight,0x00);
	   m_PosCurrentCePostion.x = pinfo->iMaxAvailableCeWidth;
	   m_PosCurrentCePostion.y = pinfo->iMaxAvailableCeHight;
	   m_bPositionInZero = true;
	   BTDEBUGINFO(L"BackToZero:x = %d, y = %d",m_PosCurrentCePostion.x,m_PosCurrentCePostion.y);
   }
}
void CBTHmiDlg::StateMange(void* pDlg, void* param)
{
	CBTHmiDlg* pObj = (CBTHmiDlg*)pDlg;
	pObj->StateMange(pObj);
}
 void CBTHmiDlg::StateMange(void* pDlg)//每隔一秒确认HID，SPP，A2DP状态，确保HID，SPP连接，A2DP断开
{
	/*if(m_ctStateManage.IsActive())
	{
		m_ctStateManage.StopTimer();
	}*/
	m_nCout++;
	sBTCommandData *pData = CBTCommand::Instance()->GetBTCommandData();
	HINT nHIDState,nSPPState,nA2DPState;
	HINT nHFPState;
	if(pData != NULL)
	{
		if(m_bHMIShow)
		{
			nHIDState = pData->BTHIDData.nHIDState;
			if(nHIDState == 0 && m_nCout%3 == 0)
			{
#ifdef  TESTBTCOMMANDQUEUE
				CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHIDConnectPhoneAndPCActive,NULL);
#else 
				HBYTE cCommand[30] ={0};
				HINT nCmdlen = 0;	
				nCmdlen = strlen("AT+HIDCONN\r\n");
				strncpy((char*)cCommand,"AT+HIDCONN\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
			}
			nSPPState = pData->BTSPPData.nSPPState;
			if(nSPPState == 0 && m_nCout%3 == 0)
			{
#ifdef  TESTBTCOMMANDQUEUE
				CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketSPPConnectPhoneAndPCActive,NULL);
#else 
				HBYTE cCommand[30] ={0};
				HINT nCmdlen = 0;	
				nCmdlen = strlen("AT+SPPCONN\r\n");
				strncpy((char*)cCommand,"AT+SPPCONN\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
			}
			nA2DPState = pData->BTAVRCPData.nA2DPState;
			if(nA2DPState != 0 && m_nCout%3 == 0 && m_nHMIState == 1)
			{
#ifdef  TESTBTCOMMANDQUEUE
				CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketA2DPDisconnectA2DPAndAVRCP,NULL);
#else 
				HBYTE cCommand[30] ={0};
				HINT nCmdlen = 0;	
				nCmdlen = strlen("AT+A2DPDISC\r\n");
				strncpy((char*)cCommand,"AT+A2DPDISC\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
			}
			if(nSPPState == 2 && nHIDState == 2)
			{
				int xx = CBTCommand::Instance()->GetMyPhoneInfo()->iAvailableCeWidth;
				int yy = CBTCommand::Instance()->GetMyPhoneInfo()->iAvailableCeHight;
				if(xx== 0 || yy == 0)
				{
					HBYTE cCommand[50] = {0};
					HUINT nCmdlen =0;
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
			}
		}
		else
		{
			
			nHIDState = pData->BTHIDData.nHIDState;
			if(nHIDState == 2)
				{
#ifdef  TESTBTCOMMANDQUEUE
					//CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHIDDisconnectHID,NULL);
#else 
					HBYTE cCommand[30] ={0};
					HINT nCmdlen = 0;	
					nCmdlen = strlen("AT+HIDDISC\r\n");
					strncpy((char*)cCommand,"AT+HIDDISC\r\n",nCmdlen);
					CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
				}
				nSPPState = pData->BTSPPData.nSPPState;
				if(nSPPState == 2 )
				{
#ifdef  TESTBTCOMMANDQUEUE
					//CBTCommand::Instance()->SendBTCommandBlockToQueue(BTSPPDisConnetSPP,NULL);
#else 
					HBYTE cCommand[30] ={0};
					HINT nCmdlen = 0;	
					nCmdlen = strlen("AT+SPPDISC\r\n");
					strncpy((char*)cCommand,"AT+SPPDISC\r\n",nCmdlen);
					CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
				}
				nA2DPState = pData->BTAVRCPData.nA2DPState;
				nHFPState = pData->BTHFPData.nHFPState;
				if((nA2DPState == 0) && (m_nCout%5 == 0) && (nHFPState == 2))
				{
#ifdef  TESTBTCOMMANDQUEUE
					//CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketA2DPConnectAVRCP,NULL);
#else 
					HBYTE cCommand[30] ={0};
					HINT nCmdlen = 0;	
					nCmdlen = strlen("AT+A2DPCONN\r\n");
					strncpy((char*)cCommand,"AT+A2DPCONN\r\n",nCmdlen);
					CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
				}
		}
	}
	//m_ctStateManage.SetTime(100);
	//m_ctStateManage.StartTimer();
}
bool CBTHmiDlg::SetBackToZeroTime(int nTime)
{
	if(nTime >= 30)
	{
		m_nBackToZero = nTime;
		return true;
	}
	return false;
}
void CBTHmiDlg::StartBackToZeroTimer()
{
	//if(m_ctTimeToBackToZero.IsActive())
	//{
	//	m_ctTimeToBackToZero.StopTimer();
	//}
	//m_ctTimeToBackToZero.SetTime(m_nBackToZero);
	//m_ctTimeToBackToZero.StartTimer();
}
void CBTHmiDlg::OnCheckForReady(void* pDlg, void* param)
{
	CBTHmiDlg* pObj = (CBTHmiDlg*)pDlg;
	pObj->OnCheckForReady(pObj);
}
void CBTHmiDlg::OnCheckForReady(void* pDlg)
{
	/*if(m_ctSingel.IsActive())
	{
		m_ctSingel.StopTimer();
	}
	m_ctSingel.SetTime(50);
	m_ctSingel.StartTimer();*/
	/*SCA_CONNECT_CONFIG stConnectCfg;
	memset(&stConnectCfg, 0, sizeof(SCA_CONNECT_CONFIG));
	stConnectCfg.bAutoDetect     = TRUE;
	stConnectCfg.enSrcType       = SCA_SRC_VGA;
	stConnectCfg.enDestType      = SCA_DEST_MAIN;
	stConnectCfg.enPriType       = SCA_DISP_PRI_NORMAL;
	stConnectCfg.lpEvtConnetName =L"_SCA_CONNECT_V0";
	DWORD dd = 0;
	DWORD dwBytesReturned = 0;
	if(DeviceIoControl(m_HandleCheck, IOCTL_SCA_SOURCE_CONNECT, (LPVOID)&stConnectCfg, sizeof(SCA_CONNECT_CONFIG), NULL, 0, &dwBytesReturned, 0) == FALSE)
	{
		BTDEBUGINFO(_T("IOCTL_SCA_SOURCE_CONNECT FAIL !\n"));
		dd = GetLastError();
		BTDEBUGINFO(L"IOCTL_SCA_SOURCE_CONNECT FAIL:%d",dd);
	}*/
   StateMange(NULL);
	HUINT nHFPState = 0;
	if(m_pGetCameraSignalStatus != NULL)
	{
		DWORD nSignel = 0;
		if(m_HandleCheck != INVALID_HANDLE_VALUE)
		{
			nSignel = m_pGetCameraSignalStatus(m_HandleCheck);
			//BTDEBUGINFO(L"%s:m_HandleCheck = %d,m_hAVD = %d,nSignel = %d",__FUNCTIONW__,m_HandleCheck,m_hAVD,nSignel);
		}
		if(nSignel== 1)
		{
			if(m_bPhoneReady == false)
			{
				sBTCommandData *pData = NULL;
				pData = CBTCommand::Instance()->GetBTCommandData();
				if(pData != NULL)
				{
					nHFPState = pData->BTHFPData.nHFPState;
				}
				if(nHFPState != 3 && nHFPState != 4 && nHFPState != 5 && nHFPState != 6)
				{
					//KCBTDialogManager::Instance()->ShowDlg(eDIALOGT_BTHMI);
				}	
			}
			if(m_pTxtBk->IsShow() && m_bHMIShow == true && m_bBTNoticeShow == false)
			{
				m_pTxtBk->SetShow(false);
			}
			if(m_nHMIState != 1)
			{
				::PostMessage(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_BT_PHONE_STATE,WPARAM(1),NULL);
				BTDEBUGINFO(L"VWM_BT_PHONE_STATE:1");
			}
			m_nHMIState = nSignel;
			m_bPhoneReady = true;
		}
		else
		{
			SETUPSETTING LSetting;
			KCLastMemory::GetInstance()->GetSetupMemory(LSetting);
			sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(NULL);
			//  sBTSourceGroup *pSource= BTSource::Instance()->GetBTSource(GetHMIPath(_T("")).c_str(),eBTDLGHDMI,LSetting.cLang);
			if(pSource != NULL)
			{
				switch (LSetting.cLang)
				{
				case 0:
			  {
				  m_pTxtBk->SetBkgndN(pSource->m_pbtHmiBk);
			  }
			  break;
				case 1:
					{
						m_pTxtBk->SetBkgndN(pSource->m_pbtHmiBkEn);
					}
					break;
				default:
					break;
				}
		}
			if(!(m_pTxtBk->IsShow()))
			{
				m_pTxtBk->SetShow(true);
			}
			if(m_nHMIState != 0)
			{
				::PostMessage(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_BT_PHONE_STATE,WPARAM(0),NULL);
				BTDEBUGINFO(L"VWM_BT_PHONE_STATE:0");
			}
			m_nHMIState = nSignel;
			m_bPhoneReady = false;
		}
	}
}
sPostion CBTHmiDlg::GetAvailableArea(int CeWidth,int CeHight,int PhoneWidth,int PhoneHight)
{
	sPostion AvailableArea = {SCREEN_WIDTH,SCREEN_HEIGHT};
	if(CeWidth > 0 && CeHight > 0 && PhoneWidth > 0 && PhoneHight > 0)
	{
		int n = 0;
		n = (CeWidth*PhoneHight) - (CeHight*PhoneWidth);
		if(n == 0)
		{
			return AvailableArea;
		}
		else if(n > 0)
		{
			AvailableArea.x = PhoneWidth*CeHight/PhoneHight;
		}
		else if(n < 0)
		{
			AvailableArea.y = PhoneHight*CeWidth/PhoneWidth;
		}
	}
	return AvailableArea;
}
void CBTHmiDlg::OpenHMI()
{
//	bool ret = false;
//	DWORD nSignel = 0;
	m_bHMIShow = true;
	unsigned int *videophy_addr = NULL;
	WINSIZE VideoModeParam = {0,0,800,480};
	if(m_pInitCameraPreview != NULL && m_pRequestCameraPreviewRsc != NULL && m_pSetCameraPreviewChannel != NULL && m_pSetCameraPreviewChannel != NULL)
	{
		m_HandleCheck = m_pInitCameraPreview();
		if(m_HandleCheck == INVALID_HANDLE_VALUE)
		{
			BTDEBUGINFO(L"m_HandleCheck = INVALID_HANDLE_VALUE");
		}
		else
		{
			m_pRequestCameraPreviewRsc(m_HandleCheck);
			m_pSetCameraPreviewChannel(m_HandleCheck,CAM_PRE_VGA);
			m_HandelTemp = m_pInitLayeredWindow();
			if(m_HandelTemp == INVALID_HANDLE_VALUE || m_HandelTemp == NULL)
			{
				BTDEBUGINFO(L"m_HandelTemp = INVALID_HANDLE_VALUE");
			}
			m_pRequestLayeredWindowRsc(m_HandelTemp,WIN_MEDIA);
			videophy_addr =m_pGetLayeredWindowPhyFreBuffer(m_HandelTemp,WIN_MEDIA);
			m_pSetLayeredWindowPosition(m_HandelTemp,WIN_MEDIA,VideoModeParam);
			m_pSetLayeredWindowAlpha(m_HandelTemp,WIN_MEDIA,10);
			PARAMCKEY mCKeyParam = {0,TRUE,TRUE};
			m_pSetLayeredWindowColorKey(m_HandelTemp,WIN_MEDIA,mCKeyParam);
			m_pOpenLayeredWindow(m_HandelTemp,WIN_MEDIA);
			OnCheckForReady(NULL);
		}
	}
}
void CBTHmiDlg::CloseHMI()
{

}
void CBTHmiDlg::ChangeLanguage(HINT nType)
{
   if(m_pTxtBk != NULL)
   {
	  //HINT nn=  CBTCommand::Instance()->GetLangue();
	  sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
	   SETUPSETTING LSetting;
	   KCLastMemory::GetInstance()->GetSetupMemory(LSetting);
	  if(pSource != NULL)
	  {
		  switch (LSetting.cLang)
		  {
			  case 0:
			  {
				  m_pTxtBk->SetBkgndN(pSource->m_pbtHmiBk);
			  }
			  break;
			  case 1:
				{
					 m_pTxtBk->SetBkgndN(pSource->m_pbtHmiBkEn);
				}
				break;
			  default:
				  break;
		  }
	  }
   }
}
void CBTHmiDlg::OpenCheckHandle()
{
	BTDEBUGINFO(L"%s",__FUNCTIONW__);
	if(m_pInitCameraPreview != NULL)
	{
		if(m_HandleCheck == INVALID_HANDLE_VALUE)
		{
			m_HandleCheck = m_pInitCameraPreview();
			m_pRequestCameraPreviewRsc(m_HandleCheck);
			m_pSetCameraPreviewChannel(m_HandleCheck,CAM_PRE_VGA);
			
			BTDEBUGINFO(L"m_HandleCheck = %d",m_HandleCheck);
		}
	}
}
void CBTHmiDlg::CloseCheckHandle()
{
	BTDEBUGINFO(L"%s",__FUNCTIONW__);
	if(m_pInitCameraPreview != NULL)
	{
		if(m_HandleCheck != INVALID_HANDLE_VALUE)
		{
			m_pStopCameraPreview(m_HandleCheck);
			m_pReleaseCameraPreviewRsc(m_HandleCheck);
			m_pUnInitCameraPreview(m_HandleCheck); 
			m_HandleCheck = INVALID_HANDLE_VALUE;
			BTDEBUGINFO(L"m_HandleCheck = INVALID_HANDLE_VALUE");

		}
	}
}
void CBTHmiDlg::RequreSource()
{
	if(m_bSourceRealse == true)
	{
		SETUPSETTING LSetting;
		KCLastMemory::GetInstance()->GetSetupMemory(LSetting);
		 sbtSourceGroup *pSource=btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str(),eDIALOGT_BTHMI,(HINT)(LSetting.cLang));
		if(pSource != NULL)
		{
			EnableUpdateRect(false);
			switch (LSetting.cLang)
			{
			case 0:
				{
					BTDEBUGINFO(L"CBTHmiDlg::%,m_pbtHmiBk = %d",pSource->m_pbtHmiBk);
					m_pTxtBk->SetBkgndN(pSource->m_pbtHmiBk);
				}
				break;
			case 1:
				{
					BTDEBUGINFO(L"CBTHmiDlg::%,m_pbtHmiBkEn = %d",pSource->m_pbtHmiBkEn);
					m_pTxtBk->SetBkgndN(pSource->m_pbtHmiBkEn);
				}
				break;
			default:
				break;
			}
			EnableUpdateRect(true);
		}
		m_bSourceRealse = false;
		BTDEBUGINFO(L"%s,m_bSourceRealse = %d",__FUNCTIONW__,m_bSourceRealse);
	}
}
void CBTHmiDlg::ReleaseSource()
{
	if(m_bSourceRealse == false)
	{
		EnableUpdateRect(false);
		if(m_pTxtBk != NULL)
		{
			m_pTxtBk->SetBkgndN(NULL);
		}
		EnableUpdateRect(true);
		btSource::Instance()->ReleaseBtSource(eDIALOGT_BTHMI);
		m_bSourceRealse = true;
	}
	BTDEBUGINFO(L"%s,m_bSourceRealse = %d",__FUNCTIONW__,m_bSourceRealse);
}
void CBTHmiDlg::OnBTNoticeShow(void * pThis,void * pParam)
{
	CBTHmiDlg* pObj = (CBTHmiDlg*)pThis;
	pObj->OnBTNoticeShow(pObj);
}
void CBTHmiDlg::OnBTNoticeShow(void * pParam)
{
	SETUPSETTING LSetting;
	KCLastMemory::GetInstance()->GetSetupMemory(LSetting);
	sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(NULL);
	if(m_ctNotice.IsActive())
	{
		m_ctNotice.StopTimer();
	}
	if(m_pTxtBk->IsShow() && m_nHMIState == 1)
	{
		m_pTxtBk->SetShow(false);
	}
	if(pSource != NULL)
	{
		switch (LSetting.cLang)
		{
		case 0:
			{
				m_pTxtBk->SetBkgndN(pSource->m_pbtHmiBk);
			}
			break;
		case 1:
			{
				m_pTxtBk->SetBkgndN(pSource->m_pbtHmiBkEn);
			}
			break;
		default:
			break;
		}
	}
	m_bBTNoticeShow = false;
}