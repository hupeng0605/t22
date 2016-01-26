#include "define.h"
#include "IpodDlg.h"
HINT g_nTotal = 0;
HWND g_hIpodWnd = NULL;
HANDLE g_Mutex = NULL;

CIpodDlg* g_pDlg = NULL; 

HANDLE g_hMonitorIpodEventThread = INVALID_HANDLE_VALUE;
//HANDLE g_hIpodInsert = INVALID_HANDLE_VALUE;
//HANDLE g_hIpodUnplug = INVALID_HANDLE_VALUE;
HANDLE g_Handle[2];
SETUPSETTING g_SetupSetting = {0};
bool g_bContiue = true;
bool static g_bInsert = true;
int  static s_nPlugIn = 0;
static bool s_bCheck = false;
sSongInfo *s_pSong = NULL;
#define APP_CLASSNAME_TEST1  _T("IPOD")
#define APP_TITLE_TEST1	  _T("IPOD")
void MonitorIpodEventThread()
{
	DWORD ret ;
	while(g_bContiue )
	{
		ret = WaitForMultipleObjects(2,g_Handle,false,INFINITE);
        switch (ret)
        {
			case WAIT_OBJECT_0:
				{
				}
				break;
			case WAIT_OBJECT_0 +1:
				{
					CEIPC_UnRegist();
					HWND hServerWnd = ::FindWindow(STR_PROCESSNAME_MANAGE, STR_PROCESSNAME_MANAGE);
					if (hServerWnd)
					{
						::PostMessage(hServerWnd, VWM_SERVER_SRC_CLOSE, IPC_ID_IPOD, NULL);
						IPODDEBEGINFO(L"POSTMSG:: VWM_SERVER_SRC_CLOSE IPC_ID_IPOD");
					}
					g_bContiue = false;
					exit(11);
					//::PostMessage(g_hIpodWnd,WM_USER + 9,0,NULL);
					
				}
				break;
        }
	}
	//	switch (ret)
	//	{
	//		case WAIT_OBJECT_0:
	//		{
	//			if(g_bInsert == true)
	//			{
	//				g_bInsert = false;
	//				IPODDEBEGINFO(L"22222Ipod拔出！");
	//				//::PostMessage(g_hIpodWnd,WM_USER + 2,0,NULL);
	//				::PostMessage(g_hIpodWnd,WM_USER + 9,0,NULL);
	//			}
	//		case WAIT_OBJECT_0 +1:
	//			{
	//				g_bInsert = true;
	//				s_nPlugIn++;
	//				IPODDEBEGINFO(L"22222Ipod插入！");
	//				//::PostMessage(g_hIpodWnd,WM_USER + 2,1,NULL);
	//				g_bContiue = false;
	//			}
	//		}
	//		break;
	//		case WAIT_TIMEOUT:
	//		{
	//		}
	//		break;
	//	}
	//}
}
void CALLBACK UpDataMusicInfo(HWND hwnd,UINT umsg,UINT idEvent,DWORD swTime)
{
	if(hwnd == g_hIpodWnd && idEvent == 100)
	{
		if(g_pDlg != NULL)
		{
			//g_pDlg->UpDataMediaInfo();
			::PostMessage(g_hIpodWnd,WM_USER + 3,0,0);
			UINT nn = SetTimer(g_hIpodWnd,100,1000,UpDataMusicInfo);
			if(nn == 0)
			{
				IPODDEBEGINFO(L"SetTimer error: %d",GetLastError());
			}
		}
	}
}
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
	if( false == ::IsWindow(g_hIpodWnd) ) return;
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
			IPODDEBEGINFO(L"lpIPCEvent->uSize = %d",lpIPCEvent->uSize);
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
				::PostMessage(g_hIpodWnd, WM_USER +1, static_cast<WPARAM>(uSendID), reinterpret_cast<LPARAM>(lpIPCEvent));
			}
			break;
		
		case IPC_U_SYS_CLOSE_PROCESS:
			{
				IPODDEBEGINFO(L"IPC_U_SYS_CLOSE_PROCESS");
				IPODDEBEGINFO(_T("[IPCEventProc] PostMessage(WM_QUIT) \n"));
				::PostMessage(g_hIpodWnd,WM_QUIT,NULL,NULL);	

			}
			break;
		case IPC_U_SERVER_POWER_OFF:
			{
				IPODDEBEGINFO(L"IPC_U_SERVER_POWER_OFF");
				//HCRadioDlg::Instance()->SaveRadioLastMem();
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
	if(message == WM_IPOD_SIGNAL)
	{
		switch (wParam)
		{
		case IPOD_REMOVE:
			{
				//CEIPC_UnRegist();
				//HWND hServerWnd = ::FindWindow(STR_PROCESSNAME_MANAGE, STR_PROCESSNAME_MANAGE);
				//if (hServerWnd)
				//{
				//	::PostMessage(hServerWnd, VWM_SERVER_SRC_CLOSE, IPC_ID_IPOD, NULL);
				//	IPODDEBEGINFO(L"POSTMSG:: VWM_SERVER_SRC_CLOSE IPC_ID_IPOD");
				//}
				//exit(11);

				//if(g_pDlg != NULL)
				//{
				//	//g_pDlg->OnIpodRemove();
				//}
				////PostQuitMessage(10);
				//g_bInsert = false;
			}
			break;
		case IPOD_INSERT:
			{
				g_bInsert = true;
				if(g_pDlg != NULL)
				{
					//g_pDlg->OnIpodreInsert();
				}
			}
			break;
		}
	}
	switch (message)
	{
		case VWM_SETUP_CHANGE_THEME:
		{
			IPODDEBEGINFO(L"VWM_SETUP_CHANGE_THEME:wparam = %d,lparam = %d",wParam,lParam);
			g_SetupSetting.cThemeMode = wParam;
			::PostMessage(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_SERVER_CHANGE_THEME_OK,NULL,NULL);
			SetCurThemeMode(g_SetupSetting.cThemeMode);
			UI_TranslateMsg(KMSG_WND_ACTIVE,NULL,NULL,false);
		}
		break;
		case VWM_SERVER_KET_BTN:
		{
			IPODDEBEGINFO(L"VWM_SERVER_KET_BTN:wparam = %d,lparam = %d",wParam,lParam);
			if(g_pDlg != NULL  && g_bInsert)
			{
				switch (lParam)
				{
					case eKEY_DOWN:
					{
						if(g_pDlg->IsIpodConnect())
						{
							g_pDlg->OnForward(NULL);
						}
					}
					break;
					case eKEY_UP:
					{
						if(g_pDlg->IsIpodConnect())
						{
							g_pDlg->OnBack(NULL);
						}
						
					}
					break;
				case eKEY_PLAY_CONTROL:
					{
						switch (wParam)
						{
							case 0:
							{
								
							}
							break;
							case 1:
							{
								if(g_pDlg->IsIpodConnect())
								{
									//g_pDlg->OnFF(NULL);
								}
								
							}
							break;
							case 2:
							{
								if(g_pDlg->IsIpodConnect())
								{
									//g_pDlg->OnStartRew(NULL);
								}
								
							}
							break;
						}
					}
				}
			}	
		}
		break;
		case 	VWM_SERVER_RESUME_AV:
			{
				IPODDEBEGINFO(L"VWM_SERVER_RESUME_AV:lparam = %d",lParam);
				bool bReady = g_pDlg->IsIpodConnect();
				if( g_bInsert)
				{
					IPODDEBEGINFO(L"222222222222222222");
					switch (lParam)
					{
					case 0:
						{
							//bool bReady = g_pDlg->WaitForIpodReady(5000);
							
							if(bReady)
							{
								g_pDlg->StartPlayIpodMusic();
							}
						}
						break;
					case 1:
						{
							//bool bReady = g_pDlg->WaitForIpodReady(5000);
							if(bReady)
							{
								g_pDlg->PauseIpodMusic();
							}
						}
						break;
					}
				}
				IPODDEBEGINFO(L"__________11111");
			}
			break;
		//case  VWM_IPOD_BACKGROUND://ipod进程前后台切换  wParam 0:由前台切换为后台运行  1:后台切换为前台运行
		//	{
		//		if(g_pDlg != NULL)
		//		{
		//			switch (wParam)
		//			{
		//			case 0:
		//				{
		//					g_pDlg->RunInBackground(true);
		//				}
		//				break;
		//			case 1:
		//				{
		//					g_pDlg->RunInBackground(false);
		//				}
		//				break;
		//			default:
		//				break;
		//			}
		//		}
		//	}
		//	break;
		case WM_USER + 1://串口数据
		{
		}
		break;
		case WM_USER + 2://Ipod是否插入，wparam；0 未插入 1:已插入
		{
			HINT nstate = (HINT)(wParam);
			if(g_pDlg != NULL)
			{
				bool bResult = false;
				if(nstate == 1)
				{
					IPODDEBEGINFO(L"33333Ipod已插入");
					if(s_nPlugIn == 1)
					{
						 bResult = g_pDlg->ConectAndStartPlay();
					}
				     
					if(bResult)
					{
						/*UINT nretTime = SetTimer(g_hWnd,100,1000,UpDataMusicInfo);
						if(nretTime == 0)
						{
							IPODDEBEGINFO(L"SetTimer error: %d",GetLastError());
						}*/
					}
				}
				else
				{
					IPODDEBEGINFO(L"33333Ipod已拔出");
					//KillTimer(g_hWnd,100);
				//	g_pDlg->ClearIpodData();
				}
			}	
		}
		break;
		case WM_USER + 3:
			{
				if(g_pDlg != NULL)
				{
					g_pDlg->UpDataMediaInfo();
				}
			}
			break;
		case WM_USER + 4:
			{
				IPODDEBEGINFO(L"g_bInsert = %d",g_bInsert);
				if(g_pDlg != NULL && g_bInsert)
				{
					g_pDlg->IpodListsAddItem((HCListItem*)wParam,lParam);
					IPODDEBEGINFO(L"IpodListsAddItem:HCListItem = %d,lParam = %d",wParam,lParam);
				}
			}
			break;
		case WM_USER + 5:
			{
				IPODDEBEGINFO(L"Ipod重新插入");
				if(g_pDlg != NULL)
				{
					
				}
			}
			break;
		case WM_USER + 6:
			{
				IPODDEBEGINFO(L"Ipod断开");
				if(g_pDlg != NULL)
				{
					g_pDlg->ClearIpodData();
				}
			}
			break;
		case WM_USER + 7://演唱者照片跟新
			{
				IPODDEBEGINFO(L"演唱者照片跟新,wparam = %d",wParam);
				HINT nn = (HINT)wParam;
				if(g_pDlg != NULL && g_bInsert)
				{
					printf("演唱者照片跟新+++++++++\r\n");
				//	g_pDlg->UpdataArteistPic(wParam);
				}
			}
			break;
		case WM_USER +8://读取数据超时
			{
				CEIPC_UnRegist();
				HWND hServerWnd = ::FindWindow(STR_PROCESSNAME_MANAGE, STR_PROCESSNAME_MANAGE);
				if (hServerWnd)
				{
					::PostMessage(hServerWnd, VWM_SERVER_SRC_CLOSE, IPC_ID_IPOD, NULL);
					IPODDEBEGINFO(L"+++++++POSTMSG:: VWM_SERVER_SRC_CLOSE IPC_ID_IPOD");
				}
				exit(11);
			}
			break;
		case WM_USER + 9:
			{
				CEIPC_UnRegist();
				HWND hServerWnd = ::FindWindow(STR_PROCESSNAME_MANAGE, STR_PROCESSNAME_MANAGE);
				if (hServerWnd)
				{
					::PostMessage(hServerWnd, VWM_SERVER_SRC_CLOSE, IPC_ID_IPOD, NULL);
					IPODDEBEGINFO(L"++++111111++++POSTMSG:: VWM_SERVER_SRC_CLOSE IPC_ID_IPOD");
				}
				exit(11);
			}
		break;
		case WM_USER + 10://Repeat图标更新
			{
				bool bReady = g_pDlg->IsIpodConnect();
				if(g_pDlg != NULL && bReady)
				{
					g_pDlg->UpdataRepeatIcon(ipodctlREPEAT(wParam));
				}
                
			}
			break;
		case WM_USER + 11://Shffle图标跟新
			{
				bool bReady = g_pDlg->IsIpodConnect();
				if(g_pDlg != NULL && bReady)
				{
					g_pDlg->UpdataShuffleIcon(ipodctlSHUFFLE(wParam));
				}
			}
			break;
		case WM_USER + 12:
			{
				bool bReady = g_pDlg->IsIpodConnect();
				if(g_pDlg != NULL && bReady)
				{
					sPlayTime *pPlayTime = (sPlayTime*)(wParam);
					if(pPlayTime != NULL)
					{
						g_pDlg->UpdataPlayingTime(pPlayTime->nPostionTime,pPlayTime->nTotalTime);
						SAFE_DELETE(pPlayTime);
					}
				}
			}
			break;
		case WM_USER + 13:
			{
				bool bReady = g_pDlg->IsIpodConnect();
				if(g_pDlg != NULL && bReady)
				{
				    g_pDlg->UpdataSongInfo(wParam);
				}
			}
			break;
		case WM_USER + 14:
			{
				bool bReady = g_pDlg->IsIpodConnect();
				if(g_pDlg != NULL && bReady)
				{
					g_pDlg->UpdataPlayPauseIcon((ipodctlPLAYSTATUS)wParam);
				}
			}
			break;
		case WM_USER +15:
			{
				IPODDEBEGINFO(L"ShowLoadDataFailed!!!!");
				bool bReady = g_pDlg->IsIpodConnect();
				if(g_pDlg != NULL && bReady)
				{
					g_pDlg->HideIpodPopUP();
				}
			}
			break;
		case WM_USER + 16:
			{
				IPODDEBEGINFO(L"ShowLoadDataFailed!!!!");
				if(g_pDlg != NULL)
				{
					g_pDlg->ShowLoadDataFailed();
				}
			}
			break;
		case WM_USER + 17:
			{
				IPODDEBEGINFO(L"Updata songInfo!!!!");
				bool bReady = g_pDlg->IsIpodConnect();
				if(g_pDlg != NULL && bReady)
				{
					if(wParam != NULL)
					{
						sSongInfo *p = (sSongInfo*)wParam;
						if(p != NULL && s_pSong != NULL)
						{
							memcpy(s_pSong,p,sizeof(sSongInfo));
							g_pDlg->UpdataTrackInfo(s_pSong);
						}
					}
				}
			}
			break;
		default:
		{
			UI_TranslateMsg(message, wParam, lParam, false);
		}
		break;
	}
	return DefWindowProcW(hWnd, message, wParam, lParam);
}


HINT APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, HINT nCmdShow)
{
	INSTANCE_START
	//g_Mutex =::CreateMutex(NULL, TRUE, APP_CLASSNAME_TEST1);
	HINT nParam = 0;
	_stscanf_s(GetCommandLine(),_T("%d"),&nParam);
	nCmdShow = PARAM_SHOW_CMD(nParam);
	// HMI 初始化
	if( !UIDevInit(
		SCREEN_WIDTH, SCREEN_HEIGHT,
		hInstance,
		const_cast<HCHAR*>(STR_PROCESSNAME_IPOD),
		const_cast<HCHAR*>(STR_PROCESSNAME_IPOD),
		0,g_hIpodWnd) )
	{
		return 0;
	}
	::ShowWindow(g_hIpodWnd, nCmdShow);
	::UpdateWindow(g_hIpodWnd);
	SetOwnerProc(MyProc);   //注册回调
	CEIPC_Regist(IPC_ID_IPOD, g_hIpodWnd, RecvIPCEvent);
	GetRESingleton()->ReLoadFont(FONT_MSYH_TTF);
	GetRESingleton()->ReLoadFont(FONT_QUARTZ_REGULAR_TTF);
	InitPopupSurface(GetHMIPath(_T("")).c_str());
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
	s_pSong = new sSongInfo;
	memset(s_pSong,0,sizeof(sSongInfo));
	 g_pDlg = new CIpodDlg;
	if(g_pDlg != NULL)
	{
		g_pDlg->Create(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetScreen());	
		g_pDlg->SetTransType(0);
		g_pDlg->ClearUpdateRect();
		g_pDlg->ShowWindow();
		g_pDlg->UpdateWindow();
	}
	g_pDlg->SetMyHandle(g_hIpodWnd);
	g_Handle[0] = CreateEvent( NULL, false, FALSE, TEXT("_IPOD_UAC_CNNT_"));
	////g_hIpodInsert = CreateEvent( NULL, false, FALSE, TEXT("_IPOD_UAC_CNNT_"));
	//if(g_Handle[0] == NULL)
	//{
	//	IPODDEBEGINFO(L"CreateEvent:_IPOD_UAC_CNNT_:Lasterror = %d",GetLastError());
	//}
	//else
	//{
	//	IPODDEBEGINFO(L"CreateEvent:_IPOD_UAC_CNNT_:Sucess");
	//}
	g_Handle[1] = CreateEvent( NULL, FALSE, FALSE, TEXT("_IPOD_UAC_EXIT_"));
	////g_hIpodUnplug = CreateEvent( NULL, FALSE, FALSE, TEXT("_IPOD_UAC_EXIT_"));
	//if(g_Handle[1] == NULL)
	//{
	//	IPODDEBEGINFO(L"CreateEvent:_IPOD_UAC_EXIT_:Lasterror = %d",GetLastError());
	//}
	//else
	//{
	//	IPODDEBEGINFO(L"CreateEvent:_IPOD_UAC_EXIT_:Sucess ");
	//}
	g_hMonitorIpodEventThread = CreateThread(NULL,0,((LPTHREAD_START_ROUTINE)MonitorIpodEventThread),NULL,0,NULL);
	if(g_hMonitorIpodEventThread == NULL)
	{
		IPODDEBEGINFO(L"CreateThread::MonitorIpodEventThread: error = %d",GetLastError());
	}
	g_pDlg->ConectAndStartPlay();

	/*UINT nretTime = SetTimer(g_hWnd,100,1000,UpDataMusicInfo);
	if(nretTime == 0)
	{
		IPODDEBEGINFO(L"SetTimer error: %d",GetLastError());
	}*/
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
	}

	// 注销IPC
	CEIPC_UnRegist();

	if( ::IsWindow(g_hIpodWnd) )
	{
		::DestroyWindow(g_hIpodWnd);
	}

	UnInitPopupSurface();
	//释放
	UIDevRelease();
	IPODDEBEGINFO(L"IPOD Quit");
   g_bContiue = false;
  DWORD DD =  WaitForSingleObject(g_hMonitorIpodEventThread,3000);
  switch(DD)
  {
		case WAIT_OBJECT_0:
		{

		}
		break;
		case WAIT_TIMEOUT:
		{

		}
		break;
  }
  CloseHandle(g_Handle[0]);
  CloseHandle(g_Handle[1]);
  CloseHandle(g_hMonitorIpodEventThread);
	// 通知Manage进程退出
	HWND hServerWnd = ::FindWindow(STR_PROCESSNAME_MANAGE, STR_PROCESSNAME_MANAGE);
	if (hServerWnd)
	{
		::PostMessage(hServerWnd, VWM_SERVER_SRC_CLOSE, IPC_ID_IPOD, NULL);
	}

	return 0;
}
