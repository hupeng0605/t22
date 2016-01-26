#include "HMIDev.h"
#include "KCRadioWindow.h"
#include "stdafx.h"
#define APP_CLASSNAME_TEST1  _T("RADIO")
#define APP_TITLE_TEST1	  _T("RADIO")
HINT g_nTotal = 0;
HWND g_hRadioWnd = NULL;
HANDLE g_Mutex = NULL;
// SETUP配置
SETUPSETTING g_SetupSetting = {0};
// 处理消息
// Function name   : SendProtocolData
// Description     : 发送协议数据给服务程序
// Return type     : void  
// Argument        : const void * pBuff
// Argument        : unsigned __int32 uLen
// 
// Remark          : 
BOOL InstanceStart(void)
{
	g_Mutex =::CreateMutex(NULL, TRUE, APP_TITLE_TEST1);
	if( ERROR_ALREADY_EXISTS == GetLastError() || NULL == g_Mutex )
	{
		if( NULL != g_Mutex )
		{
			::CloseHandle(g_Mutex);
			g_Mutex = NULL;
		}
		return FALSE;
	}
	return TRUE;
}

// APP 实例结束
void InstanceEnd(void)
{
	if( NULL != g_Mutex )
	{
		::CloseHandle(g_Mutex);
		g_Mutex = NULL;
	}
}

// 启动实例化进程控制宏
#define INSTANCE_START		\
	if( FALSE == InstanceStart() ) return -1;	\
	atexit(InstanceEnd);
void RadioExit()
{
	RADIODEBUGINFO(L"%s:beg",__FUNCTIONW__);
	CEIPC_UnRegist();
	if( ::IsWindow(g_hRadioWnd) )
	{
		::DestroyWindow(g_hRadioWnd);
	}
	HCRadioDlg::Instance()->DeleteInstance();
	RadioSource *p= RadioSource::Instance();
	if(p != NULL)
	{
		p->DeleteInstance();
		RADIODEBUGINFO(L"清理资源");
	}
	UnInitPopupSurface();
	//释放
	UIDevRelease();
	// 通知Manage进程退出
	HWND hServerWnd = ::FindWindow(STR_PROCESSNAME_MANAGE, STR_PROCESSNAME_MANAGE);
	if (hServerWnd)
	{
		::PostMessage(hServerWnd, VWM_SERVER_SRC_CLOSE, IPC_ID_RADIO, NULL);
	}
	RADIODEBUGINFO(L"Radio Exit");
	exit(1);
	RADIODEBUGINFO(L"Radio Quit");
}
void __stdcall SendProtocolData(const void * pBuff,unsigned __int32 uLen)
{

}
/*************************************** 回调 ***************************************/
// Function name   : ResponseData
// Description     : 收到应答数据的回调
// Return type     : void  
// Argument        : __int16 nCode
// Argument        : const void * pBuff
// Argument        : unsigned __int32 uLen
// 
// Remark          : 
void __stdcall ResponseData(__int16 nCode,const void * pBuff,unsigned __int32 uLen)
{
}
void __stdcall RecvIPCEvent(__in unsigned char uSendID,__in unsigned short uIPCEvent,__in unsigned long uSize,__in const unsigned char * pData)
{
	if( false == ::IsWindow(g_hRadioWnd) ) return;
	// IPC事件消息结构体
	LPIPCEVENT lpIPCEvent = NULL;
	// 分配一个接收IPC事件数据的空间 释放该空间由接收消息后释放
	lpIPCEvent = new IPCEVENT;
	if (NULL == lpIPCEvent)
	{
		wprintf(_T("[main] RecvIPCEvent lpIPCEvent is NULL \n") );
		return;
	}
	//CEIPC_SendEvent(IPC_ID_MANAGE, )
	memset(lpIPCEvent,0,sizeof(IPCEVENT));
	lpIPCEvent->uIPCEvent = uIPCEvent;
	lpIPCEvent->uSize = uSize;
	if( lpIPCEvent->uSize > 0 )
	{
		lpIPCEvent->pData = new unsigned char[lpIPCEvent->uSize];
		memset(lpIPCEvent->pData,0,lpIPCEvent->uSize);
		memcpy(lpIPCEvent->pData,pData,lpIPCEvent->uSize);
	}
	/*HCHAR arrTxt[1024];
	MultiByteToWideChar(CP_ACP,0,(char*)lpIPCEvent->pData,-1,arrTxt,lpIPCEvent->uSize);
	arrTxt[lpIPCEvent->uSize] = L'\0';
	RADIODEBUGINFO(arrTxt ,L"\r\n");*/
	if(lpIPCEvent->uSize >= 1024)
	{
			RADIODEBUGINFO(L"lpIPCEvent->uSize = %d",lpIPCEvent->uSize);
	}
	else if(lpIPCEvent->uSize >= 0 && lpIPCEvent->uSize < 1024)
	{
		switch (lpIPCEvent->uIPCEvent)
		{
		case IPC_U_SYS_COM_PROTOCOL:
			{
#if INFOMESSAGE
				WCHAR tmpBuf[1024] = {0};
				for (int i = 0; i < lpIPCEvent->uSize; ++i)
				{
					swprintf_s(tmpBuf, 1023, L"%s %02x", tmpBuf, lpIPCEvent->pData[i]);
				}
				RADIODEBUGINFO(L"[%s]%s,uSize=%d,", __FUNCTIONW__,tmpBuf,lpIPCEvent->uSize);
#else
#endif
				::PostMessage(g_hRadioWnd, WM_USER +1, static_cast<WPARAM>(uSendID), reinterpret_cast<LPARAM>(lpIPCEvent));
			}
			break;
		
		case IPC_U_SYS_CLOSE_PROCESS:
			{
				RADIODEBUGINFO(L"IPC_U_SYS_CLOSE_PROCESS");
				HCRadioDlg::Instance()->SaveRadioLastMem();
				RADIODEBUGINFO(_T("[IPCEventProc] PostMessage(WM_QUIT) \n"));
				::PostMessage(g_hRadioWnd,WM_QUIT,NULL,NULL);
				//::PostMessage(g_hWnd, WM_USER +2,NULL,NULL);
				//::PostQuitMessage(0);
				
			}
			break;
		case IPC_U_SERVER_POWER_OFF:
			{
				RADIODEBUGINFO(L"IPC_U_SERVER_POWER_OFF");
				HCRadioDlg::Instance()->SaveRadioLastMem();
				PostMessage(g_hRadioWnd,WM_QUIT,0,0);
				wprintf(L"IPC_U_SERVER_POWER_OFF :radio quit\r\n");
			}
			break;
		default:
			{

			}
			break;
		}
	}
}

LRESULT MyProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//static BOOL bActiveApp = FALSE;
	switch (message)
	{
		case UWM_TOPBAR_BACK:
			{
				UI_TranslateMsg(message, wParam, lParam, false);
				//RADIODEBUGINFO(L"[%s] UWM_TOPBAR_BACK", __FUNCTIONW__);
				RADIODEBUGINFO(L"[%s] UWM_TOPBAR_BACK,wparam = %d,ipram = %d,", __FUNCTIONW__,wParam,lParam);
			}
		break;
		case VWM_RADIO_AREA_CHANGE://收音机区域变化
			{
				RADIODEBUGINFO(L"收音机区域变化");
				HCRadioDlg::Instance()->GetCurrentArea();
				HCRadioDlg::Instance()->SendRadioCommand(eENTERRADIOINTERFACE,0);
			}
			break;
		case WM_USER:		
		UI_TranslateMsg(message, wParam, lParam, false);
		break;
		case VWM_SERVER_KET_BTN:
		UI_TranslateMsg(message,wParam,lParam,true);
		//RADIODEBUGINFO(L"[%s] VWM_SERVER_KET_BTN", __FUNCTIONW__);
		RADIODEBUGINFO(L"[%s] VWM_SERVER_KET_BTN,wparam = %d,ipram = %d,", __FUNCTIONW__,wParam,lParam);
		break;
		case VWM_SETUP_CHANGE_THEME:    // 主题切换
		{
			g_SetupSetting.cThemeMode = wParam;
			::PostMessage(CEIPC_GetHWND(IPC_ID_RADIO),VWM_SERVER_CHANGE_THEME_OK,NULL,NULL);
			SetCurThemeMode(g_SetupSetting.cThemeMode);
			//if( ( TRUE == bActiveApp ) && ( g_uPreThemeMode != g_SetupSetting.cThemeMode ) )
			{
				UI_TranslateMsg(KMSG_WND_ACTIVE,NULL,NULL,false);
			}
		}
		//RADIODEBUGINFO(L"[%s] VWM_SETUP_CHANGE_THEME", __FUNCTIONW__);
		RADIODEBUGINFO(L"[%s] VWM_SETUP_CHANGE_THEME,wparam = %d,ipram = %d,", __FUNCTIONW__,wParam,lParam);
		break;
		case  VWM_SERVER_LANG_SW:
		{
			RADIODEBUGINFO(L"[%s] VWM_SERVER_LANG_SW,wparam = %d,ipram = %d,", __FUNCTIONW__,wParam,lParam);
			switch (wParam)
			{
				case 0:
				{
					HCRadioDlg::Instance()->ChangeLangue(0);
				}
				break;
				case 1:
				{
					HCRadioDlg::Instance()->ChangeLangue(1);
				}
				break;
				default:
				break;
			}
		}
		break;
		case VWM_RADIO_AUTO_SCAN:
			{
				HCRadioDlg::Instance()->OnStartSearch(NULL);
			}
			break;
		case WM_USER +1:
		{
			//RADIODEBUGINFO(L"____%d____",g_nTotal);
			//DWORD dwBegin = ::GetTickCount();
			//RADIODEBUGINFO(L"串口数据");
			HCRadioDlg::Instance()->HandRadioData(((IPCEVENT*)lParam)->pData+1,((IPCEVENT*)lParam)->uSize-1);
			LPIPCEVENT lpIPCEvent = (LPIPCEVENT)lParam;
			SAFE_DELETE_GROUP(lpIPCEvent->pData);
			SAFE_DELETE(lpIPCEvent);
			UI_TranslateMsg(message, wParam, lParam, false);
			//RADIODEBUGINFO(L"HandRadioData %d" , ::GetTickCount()-dwBegin);
		//	SAFE_DELETE_GROUP(((unsigned char*)((IPCEVENT*)lParam)->pData));
		}
		break;
		case WM_USER +2:
			{
				RadioExit();
			}
			break;
		case WM_USER + 50:
		{
			RADIODEBUGINFO(L"发送队列添加数据,wparam = %d,Iparam= %d",wParam,lParam);
			HCRadioDlg::Instance()->SendRadioCommand(eRADIOCOMMANDTYPE(wParam),HINT(lParam));
		}
		break;
	//CBTDialogManager::Instance()->GetDlg()->Updata(())
		default:
		{
			UI_TranslateMsg(message, wParam, lParam, false);
		}
		break;
	}
	return DefWindowProcW(hWnd, message, wParam, lParam);
}
//主程序
HINT APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, HINT nCmdShow)
{
	INSTANCE_START;
//	g_Mutex =::CreateMutex(NULL, TRUE, APP_CLASSNAME_TEST1);
	HINT nParam = 0;
	_stscanf_s(GetCommandLine(),_T("%d"),&nParam);
	nCmdShow = PARAM_SHOW_CMD(nParam);
	RADIODEBUGINFO(L"nCmdShow = %d");
	// HMI 初始化
	if( !UIDevInit(
		SCREEN_WIDTH, SCREEN_HEIGHT,
		hInstance,
		const_cast<HCHAR*>(STR_PROCESSNAME_RADIO),
		const_cast<HCHAR*>(STR_PROCESSNAME_RADIO),
		0,g_hRadioWnd) )
	{
		return 0;
	}
	SetOwnerProc(MyProc);   //注册回调

	::ShowWindow(g_hRadioWnd, nCmdShow);

   //InitPopupSurface(GetHMIPath(_T("")).c_str());
	
	CEIPC_Regist(IPC_ID_RADIO, g_hRadioWnd, RecvIPCEvent);
	GetRESingleton()->ReLoadFont(FONT_MSYH_TTF);
	GetRESingleton()->ReLoadFont(FONT_QUARTZ_REGULAR_TTF);
	 InitPopupSurface(GetHMIPath(_T("")).c_str());
	HCRadioDlg:: Instance()->Create(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,  GetScreen());
	HCRadioDlg::Instance()->SetMyhWnd(g_hRadioWnd);
	HCRadioDlg:: Instance()->SetTransType(0);
	HCRadioDlg:: Instance()->ClearUpdateRect();
	HCRadioDlg:: Instance()->ShowWindow();
	HCRadioDlg:: Instance()->UpdateWindow();
   RADIODEBUGINFO(L"Show Radio Window");

   	::UpdateWindow(g_hRadioWnd);
	// 获取配置信息
	if( NULL != KCLastMemory::GetInstance() )
	{
		// 读取SETUP配置文件
		KCLastMemory::GetInstance()->GetSetupMemory(g_SetupSetting);
	}
	else
	{
		KCLastMemory::GetSetupMemoryDefault(g_SetupSetting);
	}
#ifdef WINCE
	//::CeSetThreadPriority(GetCurrentThread(),/*251*/224);
#endif
	//消息循环
	MSG msg;
	int n = 0;

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
	}
	HBYTE cCommand[10] = {0};
	HUINT nlen = 0;
	cCommand[nlen++] = 0x00;
	cCommand[nlen++] = 0x01;
	cCommand[nlen++] = 0x0B;	
	IPCEVENT *pIpcEvent = new IPCEVENT;
	pIpcEvent->pData = cCommand;
	pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
	pIpcEvent->uSize = nlen;
	HCRadioDlg::Instance()->RadioSendData(IPC_ID_MANAGE,pIpcEvent);
	SAFE_DELETE(pIpcEvent);
	// 注销IPC
	CEIPC_UnRegist();

	if( ::IsWindow(g_hRadioWnd) )
	{
		::DestroyWindow(g_hRadioWnd);
	}
//#if RADIOCOMMANDQUEUE
	//::PostMessage(g_hWnd,WM_USER + 50,eRADIOSTOPAUTOCHANNELSEARCH,0);
//#else
//#endif
	HCRadioDlg::Instance()->DeleteInstance();
	RadioSource *p= RadioSource::Instance();
	if(p != NULL)
	{
		p->DeleteInstance();
		RADIODEBUGINFO(L"清理资源");
	}
	UnInitPopupSurface();
	//释放
	UIDevRelease();
	RADIODEBUGINFO(L"Radio Quit");

	// 通知Manage进程退出
	HWND hServerWnd = ::FindWindow(STR_PROCESSNAME_MANAGE, STR_PROCESSNAME_MANAGE);
	if (hServerWnd)
	{
		::PostMessage(hServerWnd, VWM_SERVER_SRC_CLOSE, IPC_ID_RADIO, NULL);
	}

	return 0;
}
