
#include "define.h"
//#include"CShareMemory.h"
#include<fstream>
#include<iostream>
using namespace std;
#include "HMIDev.h"
#include "KCBTDialogManager.h"
#include "KCBTCommand.h"
HWND g_hBTWnd = NULL;
HANDLE g_Mutex = NULL;
#define APP_CLASSNAME_TEST1  _T("BT")
#define APP_TITLE_TEST1	  _T("BT")
int g_PreHfpState= 0;
#define TIME_ID_A2DP   1003
#define TIME_ID_FIRST_PLAY   1004
#define  TIME_ID_MUTE   1005
static bool s_bA2DPConn = true;
static bool s_bMute = false;
static bool s_bCheck = false;
static int s_nACCInMusic = 0;
HANDLE g_hBTReset = CreateEvent(NULL,TRUE,false,L"BTRESET");
static int s_Show = 0;
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
// SETUP配置
SETUPSETTING g_SetupSetting = {0};
int g_nRestTime = 0;
static HINT s_nDlg = 0;
	HString appPath;
#if TESTRESTARTPROTEM
ofstream  g_Profile1;
#endif
#if BTLOGSTATE
ofstream  g_Logfile1;
#else
#endif
int g_nTimeCounts = 0;
void FirstPlayBTMusic(HWND hwnd,UINT umsg,UINT idEvent,DWORD swTime)
{
	printf("FirstPlayBTMusic--------------\r\n");
	if(hwnd == g_hBTWnd && idEvent == TIME_ID_FIRST_PLAY)
	{
		HCBTMusicDlg* pObj = static_cast<HCBTMusicDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTMUSIC));
		if(pObj != NULL && s_nACCInMusic==2)
		{
			pObj->SendPP();

			s_nACCInMusic = 3;
		}
		KillTimer(g_hBTWnd,TIME_ID_FIRST_PLAY);
	}
}
void ConnectA2DP(bool bCon)
{
	if(g_hBTWnd != NULL)
	{
		int n = 0;
		if(!bCon)
		{
			n = 1;
		}
		g_nTimeCounts++;
		if(g_nTimeCounts%5 == 0)
		{
			PostMessage(g_hBTWnd,VWM_TO_BT_A2DP_DISCONNECT,n,0);
		}
	}
}
void  A2DPMannageTimer(HWND hwnd,UINT umsg,UINT idEvent,DWORD swTime)
{
	HCBTConnectionssettingDlg* pObj = static_cast<HCBTConnectionssettingDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCONNECTSETTING));
	 if(s_bA2DPConn)
	 {
		pObj->ConnectA2DP(1);
	 }
	 else
	 {
		//pObj->ConnectA2DP(0);
	 }
}
void CALLBACK CheckHDMISignal(HWND hwnd,UINT umsg,UINT idEvent,DWORD swTime)
{
	if(hwnd == g_hBTWnd && idEvent == 10)
	{
		CBTHmiDlg* pBtHMIDlg = (CBTHmiDlg*)(KCBTDialogManager::Instance()->GetBTHMIDlg());
		if(pBtHMIDlg != NULL && s_bCheck)
		{
			pBtHMIDlg->OnCheckForReady(NULL);
		}
		static bool s_bCon = FALSE;
		//ConnectA2DP(s_bCon);
		s_bCon = !s_bCon;

	}
}
void  A2DPMuteMannageTimer(HWND hwnd,UINT umsg,UINT idEvent,DWORD swTime)
{
	if(hwnd == g_hBTWnd && idEvent == TIME_ID_MUTE)
	{
		sBTCommandData*pData =  CBTCommand::Instance()->GetBTCommandData();
		bool bMute  = false;
		if(pData != NULL)
		{
			bMute = pData->BTAVRCPData.bA2DPMute;
		}
		if(bMute != s_bMute && s_bMute == false)
		{
#ifdef TESTBTCOMMANDQUEUE
			CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketA2DPMute,0);
#else
			HBYTE cCommand[20] = {0};
			HUINT nCmdlen = 0;
			nCmdlen = strlen("AT+A2DPMUTE\r\n");
			strncpy((char*)cCommand,"AT+A2DPMUTE\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
		}
	}
}
void CALLBACK SetDlg(HWND hwnd,UINT umsg,UINT idEvent,DWORD swTime)
{
	if(hwnd == g_hBTWnd && idEvent == 15)
	{
		//BTDEBUGINFO(L"CALLBACK SetDlg");
		HWND hServerWnd = ::FindWindow(STR_PROCESSNAME_MANAGE, STR_PROCESSNAME_MANAGE);
		if (hServerWnd  && s_nDlg == 4)
		{
			//::PostMessage(hServerWnd, VWM_BT_MUSICDLG_TIMEOUT, 0, NULL);
			BTDEBUGINFO(L"last mem to music Timeout");
		}
		s_nDlg = 0;
		KillTimer(hwnd,15);
	}
}
LRESULT MyProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static BOOL bActiveApp = FALSE;

	switch (message)
	{
			case UWM_TOPBAR_BACK:
			{
				//UI_TranslateMsg(message, wParam, lParam, false);
					BTDEBUGINFO(L"IPC_ID_MANAGE:UWM_TOPBAR_BACK");
					HWND hServerWnd = CEIPC_GetHWND(IPC_ID_MANAGE);
					if (NULL != hServerWnd)
					{
						::PostMessage(hServerWnd, UWM_TOPBAR_HOME, 0, 0);
					}	
			}
			break;
			case VWM_SERVER_CHANGE_MODE: // wParam: START_BT_DLG_AUDIO 4 iParam 0后台 1前台
				{
					HCBTConnectionssettingDlg* pObj = static_cast<HCBTConnectionssettingDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCONNECTSETTING));
					eDIALOGTYPE eType = KCBTDialogManager::Instance()->GetCurrentDlgType();
					sBTCommandData*pData =  CBTCommand::Instance()->GetBTCommandData();
					BTDEBUGINFO(L"IPC_ID_MANAGE:VWM_SERVER_CHANGE_MODE,wparam = %d,lParam = %d",wParam,lParam);
					if(pData != NULL && pObj != NULL)
					{
						HUINT nState = 0;
						nState = pData->BTHFPData.nHFPState; 
						if(nState != 3 && nState != 4 && nState != 5 && nState != 6)
						{
							bool bConnect = pObj->GetBTConnectstate();
							if(bConnect)
							{
								switch (wParam)
								{
								   case START_BT_DLG_NULL:
									{
										pObj->OnBTDial(NULL);
									}
									break;
								   case START_BT_DLG_DIAL:
									   {
										   if(lParam == 1 && eType == eDIALOGT_BTDIAL)
										   {
											   HWND hServerWnd = CEIPC_GetHWND(IPC_ID_MANAGE);
											   if (NULL != hServerWnd)
											   {
												   ::PostMessage(hServerWnd, UWM_BACK_SRC, 0, 0);
												   BTDEBUGINFO(L"hServerWnd:UWM_BACK_SRC");
											   }
										   }
										   else
										   {
											   pObj->OnBTDial(NULL);
										   }
										   BTDEBUGINFO(L"OnBTDial");
									   }
									   break;
								   case START_BT_DLG_PHONE_BOOK:
									   {
										   pObj->OnAddressBook(NULL);
									   }
									   break;
								   case START_BT_DLG_HISTORY:
									   {
										   pObj->OnCallRecords(NULL);
									   }
									   break;
								   case START_BT_DLG_AUDIO:
									   {
										 //  pObj->OnBTMusic(NULL);
										   KCBTDialogManager::Instance()->ShowDlg(eDIALOGT_BTMUSIC);
										//   pObj->PlayMusicEx();
									   }
									   break;
								   case START_BT_DLG_CONNECT:
									   {
										   pObj->OnConnectionSetting(NULL);
									   }
									   break;
								   case START_BT_DLG_MIRRORLINK:
									   {
											KCBTDialogManager::Instance()->ShowDlg(eDIALOGT_BTHMI);
											CBTHmiDlg* pBtHmiDlg = (CBTHmiDlg*)(KCBTDialogManager::Instance()->GetBTHMIDlg());
											if(pBtHmiDlg != NULL)
											{
												pBtHmiDlg->ShowHMIVidio();
												s_bCheck = TRUE;
											}
									   }
									   break;
								   default:
									   {
											pObj->OnConnectionSetting(NULL);
									   }
									   break;
								}
							}
							else
							{
								if(wParam == START_BT_DLG_MIRRORLINK)
								{
									KCBTDialogManager::Instance()->ShowDlg(eDIALOGT_BTHMI);
									CBTHmiDlg* pBtHmiDlg = (CBTHmiDlg*)(KCBTDialogManager::Instance()->GetBTHMIDlg());
									if(pBtHmiDlg != NULL)
									{
										pBtHmiDlg->ShowHMIVidio();
										s_bCheck = TRUE;
									}
								}
								else
								{
									//pObj->OnConnectionSetting(NULL);
									if(lParam == 1 && eType == eDIALOGT_BTCONNECTSETTING)
									{
										HWND hServerWnd = CEIPC_GetHWND(IPC_ID_MANAGE);
										if (NULL != hServerWnd)
										{
											::PostMessage(hServerWnd, UWM_BACK_SRC, 0, 0);
											BTDEBUGINFO(L"hServerWnd:UWM_BACK_SRC");
										}
									}
									KCBTDialogManager::Instance()->ShowDlg(eDIALOGT_BTCONNECTSETTING);
								}
							}
						}   
					}
				}
				break;
			case VWM_SERVER_BACKCAMERA_STATUS:
				{
					CBTHmiDlg* pBtHMIDlg = (CBTHmiDlg*)(KCBTDialogManager::Instance()->GetBTHMIDlg());
					BTDEBUGINFO(L"IPC_ID_MANAGE:VWM_SERVER_BACKCAMERA_STATUS,wparam = %d",wParam);
					HINT nSingel = HINT(wParam);
					switch (nSingel)
					{
						case 1:
						{
							if(pBtHMIDlg != NULL)
							{
								//pBtHMIDlg->CloseCheckHandle();
							    pBtHMIDlg->CloseHMIVidio();			
							//	KCBTDialogManager::Instance()->HideBTHMIdlg();
							}
						}
						break;
						case 0:
						{
							eDIALOGTYPE eType= KCBTDialogManager::Instance()->GetCurrentDlgType();
							BTDEBUGINFO(L"GetCurrentDlgType() ==%d",eType);
							if(pBtHMIDlg != NULL && eType == eDIALOGT_BTHMI)
							{
								KCBTDialogManager::Instance()->ShowDlg(eDIALOGT_BTHMI);
							}
						}
						break;
					}
				}
				break;
			case WM_USER:
			{
				UI_TranslateMsg(message, wParam, lParam, false);
			}
			break;
			case VWM_SERVER_KET_BTN:
			//UI_TranslateMsg(message,wParam,lParam,true);
			{
				BTDEBUGINFO(L"IPC_ID_MANAGE:VWM_SERVER_KET_BTN,wparam = %d,iparam = %d",wParam,lParam);
				sBTCommandData*pData =  CBTCommand::Instance()->GetBTCommandData();
				if(pData != NULL)
				{
					HUINT nState = 0;
					nState = pData->BTHFPData.nHFPState; 
					if(nState != 3 && nState != 4 && nState != 5 && nState != 6)
					{
						switch(lParam)
						{
						case eKEY_DOWN:
							{
								HCBTMusicDlg* pObj = static_cast<HCBTMusicDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTMUSIC));
								if(pObj != NULL)
								{
									pObj->OnForward(NULL);
								}
							}
							break;
						case eKEY_UP:
							{
								HCBTMusicDlg* pObj = static_cast<HCBTMusicDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTMUSIC));
								if(pObj != NULL)
								{
									pObj->OnBack(NULL);
								}
							}
							break;
					//	case KEY_ST_SW_MUTE:
						//	{
								/*HCBTMusicDlg* pObj = static_cast<HCBTMusicDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTMUSIC));
								if(pObj != NULL)
								{
									pObj->OnPlayMute(pObj,NULL);
								}*/
						//	}
							break;
						default:
							{

							}
							break;
						}	
					}
					else if(nState == 3 || nState == 4 || nState == 5 || nState == 6)
					{
						switch (lParam)
						{
						case eKEY_OFF_HOOK://电话接听
							{
								HCBTDialDlg* pObj = static_cast<HCBTDialDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTDIAL));
								if(pObj != NULL)
								{
									pObj->OnDialNumCall(pObj,NULL);
								}
							}
							break;
						case eKEY_ON_HOOK://电话挂断
							{
								HCBTDialDlg* pObj = static_cast<HCBTDialDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTDIAL));
								if(pObj != NULL)
								{
									pObj->OnDialNumHangUp(pObj,NULL);
								}
							}
							break;
						}
					}
				}	   	
			}
			break;
			case VWM_SETUP_CHANGE_THEME:    // 主题切换
			{
				g_SetupSetting.cThemeMode = wParam;
				::PostMessage(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_SERVER_CHANGE_THEME_OK,NULL,NULL);
				SetCurThemeMode(g_SetupSetting.cThemeMode);
				BTDEBUGINFO(L"IPC_ID_MANAGE:VWM_SETUP_CHANGE_THEME");
				KCBTDialogManager::Instance()->ChangeThemeForAllDlg();
			
			}
			break;
			case  VWM_SETUP_CHANGE_BT_SETING:
			{
				BTSETTING Setting;
				KCLastMemory::GetInstance()->GetBTMemory(Setting);
				CBTCommand*p =  CBTCommand::Instance( );
				BTDEBUGINFO(L"IPC_ID_MANAGE:VWM_SETUP_CHANGE_BT_SETING");
				HCBTConnectionssettingDlg* pObj = static_cast<HCBTConnectionssettingDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCONNECTSETTING));
				if(p != NULL && pObj != NULL)
				{
					if(Setting.uBtOnOff == 0 && (p->GetBTSetting()).uBtOnOff == 1)
					{
						pObj->StartCloseBT();
						//p->CloseBT();
					}
					else if(Setting.uBtOnOff == 1 && (p->GetBTSetting()).uBtOnOff == 0)
					{
						p->OpenBT(1,115200);
					}
					p->SetBTSetting(Setting);
				}
			}
			break;
			case  UWM_SERVER_CLOSE_VEDIO:
				{

					eDIALOGTYPE eType= KCBTDialogManager::Instance()->GetCurrentDlgType();
					switch (wParam)
					{
						case 0:
						{
							
							CBTHmiDlg* pBtHmiDlg = (CBTHmiDlg*)(KCBTDialogManager::Instance()->GetBTHMIDlg());
							if(pBtHmiDlg != NULL && s_bCheck)
							{
								s_bCheck = false;
								//pBtHmiDlg->CloseHMIVidio();
								//pBtHmiDlg->CloseCheckHandle();
								KCBTDialogManager::Instance()->HideBTHMIdlg();
							}
						}
						break;
						case 1:
						{
							   CBTHmiDlg* pBtHmiDlg = (CBTHmiDlg*)(KCBTDialogManager::Instance()->GetBTHMIDlg());
							   if(pBtHmiDlg != NULL  && !s_bCheck)
							   {
								   //pBtHmiDlg->CloseHMIVidio();
								   //pBtHmiDlg->CloseCheckHandle();
								   if(eType == eDIALOGT_BTHMI)
								   {
                                          pBtHmiDlg->ShowHMIVidio();
								   }
								   s_bCheck = TRUE;
							   }
								
						}
						break;
					}
					
					BTDEBUGINFO(L"IPC_ID_MANAGE:UWM_SERVER_CLOSE_VEDIO,WPARAM = %d",wParam);
					//KCBTDialogManager::Instance()->HideBTHMIdlg();
				}
				break;
			case 	VWM_SERVER_RESUME_AV:
				{
					HCBTMusicDlg* pObj = static_cast<HCBTMusicDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTMUSIC));
                    eDIALOGTYPE eCur = KCBTDialogManager::Instance()->GetCurrentDlgType();
					BTDEBUGINFO(L"IPC_ID_MANAGE:VWM_SERVER_RESUME_AV,lParam = %d",lParam);
					printf("IPC_ID_MANAGE:VWM_SERVER_RESUME_AV,lParam = %d\r\n",lParam);
					if(pObj != NULL && eCur != eDIALOGT_BTHMI)
					{
						switch (lParam)
						{
							case 0:
							{
								  pObj->PlayMusic();
								//pObj->PlayMusicEx();
							}
							break;
							case 1:
							{
								pObj->StopMusic();
								//pObj->StopMusicEx();
							}
						}
					}
				}
				break;
				case VWM_SERVER_LANG_SW:	// 通知进行语言切换wParam：0-中文 1-英文 lParam ：无意义
				{
					BTDEBUGINFO(L"VWM_SERVER_LANG_SW,wparam = %d",wParam);
					switch (wParam)
					{
						case 0:
						{
							CBTCommand::Instance()->SetLangue(0);
							KCBTDialogManager::Instance()->ChangeLangeForAllDlg(0);
						}
						break;
						case 1:
						{
							CBTCommand::Instance()->SetLangue(1);
							KCBTDialogManager::Instance()->ChangeLangeForAllDlg(1);
						}
						break;
						default:
						{

						}
						break;
					}
				}
				break;
				case IPC_U_SERVER_POWER_OFF:
					{
						BTDEBUGINFO(L"IPC_U_SERVER_POWER_OFF");
						CBTCommand::Instance()->DisCurrentConnectDevice();
						::PostMessage(g_hBTWnd,WM_QUIT,0,NULL);
					}
					break;
			//case IPC_U_SYS_CLOSE_PROCESS:
			//	{
			//		// 发送退出进程的消息
			//		BTDEBUGINFO(_T("[IPCEventProc] PostMessage(WM_QUIT) \n"));
			//		::PostMessage(g_hWnd1,WM_QUIT,NULL,NULL);
			//	}
			//	break;
				case VWM_TO_BT_RESET:
					{
						if(g_hBTReset != NULL)
						{
							//ResetEvent(g_hBTReset);
						}
						BTDEBUGINFO(L"++++++VWM_TO_BT_RESET++++++\r\n");
						HCBTConnectionssettingDlg* pObj = static_cast<HCBTConnectionssettingDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCONNECTSETTING));
						if(pObj != NULL)
						{
							pObj->ClearDeviceRecord();
							Sleep(500);

						}
					}
					break;
				case VWM_TO_BT_A2DP_DISCONNECT://蓝牙断A2DP  wparam: 2 A2DP断开   1 A2DP静音  0 A2DP连接 
					{
                       wprintf(L"VWM_TO_BT_A2DP_DISCONNECT,wparam = %d,lparam = %d\r\n",wParam,lParam);
						BTDEBUGINFO(L"VWM_TO_BT_A2DP_DISCONNECT,wparam = %d,lparam = %d",wParam,lParam);
						HCBTMusicDlg* pObj = static_cast<HCBTMusicDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTMUSIC));
						if(pObj != NULL)
						{
							switch(wParam)
							{
								case 0:
								{
									KillTimer(g_hBTWnd,TIME_ID_A2DP);
								//	pObj->ConnectA2DP(1);
									if(s_nACCInMusic != 1)
									{
										pObj->PlayMusicEx();
										s_nACCInMusic= 3;
									}
									else
									{
										SetTimer(g_hBTWnd,TIME_ID_FIRST_PLAY,3000,FirstPlayBTMusic);
										printf("SetTimer++++++++++FirstPlayBTMusic++++\r\n");
										s_nACCInMusic = 2;
									}
									
									//pObj->MusicMute(false);
                                  //  pObj->MusicMuteEx(false);
									s_bA2DPConn = true;
									s_bMute = FALSE;
									SetTimer(g_hBTWnd,TIME_ID_A2DP,3000,A2DPMannageTimer);
								}
								break;
								case 1:
								{
									KillTimer(g_hBTWnd,TIME_ID_A2DP);
									pObj->StopMusic();
									//pObj->ConnectA2DP(1);
									s_bA2DPConn = true;
									//pObj->MusicMute(true);
									//pObj->MusicMuteEx(true);
									s_bMute = true;
									SetTimer(g_hBTWnd,TIME_ID_A2DP,3000,A2DPMannageTimer);
								}
								break;
								case 2:
								{
									KillTimer(g_hBTWnd,TIME_ID_A2DP);
									pObj->StopMusic();
									//pObj->ConnectA2DP(0);
									s_bA2DPConn = false;
									//pObj->MusicMute(true);
									SetTimer(g_hBTWnd,TIME_ID_A2DP,3000,A2DPMannageTimer);
								}
								break;
							}
						} 
					}
					break;
		case (WM_USER + 1)://添加设备列表名称
		{
			BTDEBUGINFO(L"设备列表更新");
			HCBTConnectionssettingDlg* pObj = static_cast<HCBTConnectionssettingDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCONNECTSETTING));
//			bool bHdmi = KCBTDialogManager::Instance()->IsBTHMIDlgShow();
			if(pObj != NULL)
			{
				//pObj->SetNoticeShowHide();
				pObj->AddPairedDevice();
			}	
		}
		break;
		case (WM_USER + 2)://通讯录添加记录
		{
			BTDEBUGINFO(L"通讯录更新");
			HCBTAddressBookDlg* pObj = static_cast<HCBTAddressBookDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTADDRESSBOOK));
			HCBTCallRecordsDlg* pObjR = static_cast<HCBTCallRecordsDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCALLRECORDS));
			if(pObj != NULL && pObjR != NULL)
			{
				pObj->AddAddressBookItem();
				pObjR->OnAllRecords(NULL);
			}	
		}
		break;
		case (WM_USER + 3)://更新蓝牙音乐信息
		{
			BTDEBUGINFO(L"蓝牙音乐信息更新");
			HCBTMusicDlg* pObj = static_cast<HCBTMusicDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTMUSIC));
			if(pObj != NULL)
			{
				pObj->UpDataMediaInfo();
			}		
		}
		break;
		case  (WM_USER + 4)://更新蓝牙音乐播放状态
		{
			BTDEBUGINFO(L"蓝牙音乐播放状态更新,wparam = %d",wParam);
			HCBTMusicDlg* pObj = static_cast<HCBTMusicDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTMUSIC));
	
			if(pObj != NULL)
			{
				pObj->UpDataPlayState(static_cast<eBTMUSICRUNNINGSTATUS>(wParam));
			}
#if TESTDAILPROBLEM
			pObj1->UpdataTestHFP();
#else
#endif
		}
		break;
		case (WM_USER + 5)://HFP状态更新
		{
	//		sBTCommandData*pData =  CBTCommand::Instance()->GetBTCommandData();	
#if BTLOGSTATE
			HINT nState = static_cast<HINT>(wParam);
			g_Logfile1<<GetTickCount()<<"           "<<" nHFP = "<<nState<<endl;
#else
#endif 
			
			HCBTMusicDlg* pMusic = static_cast<HCBTMusicDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTMUSIC));
			HCBTDialDlg* pObj = static_cast<HCBTDialDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTDIAL));
			HCBTCallRecordsDlg* pObjRecords = static_cast<HCBTCallRecordsDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCALLRECORDS));
			HCBTAddressBookDlg* pObjBook = static_cast<HCBTAddressBookDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTADDRESSBOOK));
			//bool bBTHMISgow = KCBTDialogManager::Instance()->IsBTHMIDlgShow();
			HCBTConnectionssettingDlg* pObjc = static_cast<HCBTConnectionssettingDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCONNECTSETTING));
#if TESTDAILPROBLEM
			pObj->UpdataTestHFP();
#else
#endif
			if(pObj != NULL)
			{
				HINT nparam = static_cast<HINT>(wParam);
				pObj->UpdataTextShow(nparam);//拨号键盘显示信息更新
				BTDEBUGINFO(L"HFP状态更新,HFP = %d",nparam);
				pObj->UpDataKeyBoard(static_cast<HINT>(wParam));//拨号键盘状态更新	
				pObj->UpdataBTBottomState(nparam);
				pObjc->UpdataByHFPState(nparam);//更新蓝牙连接状态，更新图标
				if(nparam == 2)
				{
					//KillTimer(g_hBTWnd,TIME_ID_MUTE);
					//SetTimer(g_hBTWnd,TIME_ID_MUTE,3000,A2DPMuteMannageTimer);
					pObjc->StopDeadTimer();
				
					
				}
				DWORD dwRet = 0;

				if((g_PreHfpState == 3 || g_PreHfpState == 4 || g_PreHfpState == 5 || g_PreHfpState == 6) && wParam == 0 )
				{
					//::PostMessage(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_BT_HFP_STATE,7,NULL);
					::SendMessageTimeout(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_BT_HFP_STATE,7,NULL,SMTO_NORMAL,500,&dwRet);
					BTDEBUGINFO(L"IPC_ID_MANAGE::VWM_BT_HFP_STATE= 7");
				}
				if(wParam != 1)
				{
					if(wParam != 7)
					{
						::PostMessage(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_BT_HFP_STATE,wParam,NULL);
					}
					else
					{
                       ::SendMessageTimeout(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_BT_HFP_STATE,7,NULL,SMTO_NORMAL,500,&dwRet);
					}
					g_PreHfpState = (int)wParam;
					BTDEBUGINFO(L"IPC_ID_MANAGE::VWM_BT_HFP_STATE= %d",wParam);
				}
				if(nparam == 7)
				{
					pObj->SetDailingState(true);
					KCBTDialogManager::Instance()->ShowPreDlg();//通话结束返回上一个界面
					pObj->ClearKeyBoardNum();
					pObj->SetDailingState(false);
				}
				if(nparam == 0)
				{
						KillTimer(g_hBTWnd,TIME_ID_MUTE);
						if(pObjBook != NULL && pObjRecords != NULL && pObj != NULL && pMusic != NULL) 
						{
							/*pObjRecords->DeleteAllItems();
							pObjRecords->UpDataRecords(false);*/
							pObjRecords->ClearRecordsData();
							pObjBook->ClearBookData();
							pObj->ClearKeyBoardNum();
							pMusic->ClearMusicInfo();
						}
						CBTCommand::Instance()->ClearBookData();
						CBTCommand::Instance()->ClearMyPhoneData();
				}

				if(s_nDlg == 4 && nparam == 2)
				{
					s_nACCInMusic = 1;
					if(s_Show != SW_HIDE)
					{
						pMusic->OnBTMusic(NULL);
					}
					else
					{
						KCBTDialogManager::Instance()->ShowDlg(eDIALOGT_BTMUSIC);
						SetTimer(g_hBTWnd,TIME_ID_FIRST_PLAY,3000,FirstPlayBTMusic);
						s_nACCInMusic = 2;
					}

					//pMusic->PlayMusicEx();
					//SetTimer(g_hBTWnd,TIME_ID_FIRST_PLAY,3000,FirstPlayBTMusic);
					BTDEBUGINFO(L"last mem to music");
					s_nDlg = 0;
					//KCBTDialogManager::Instance()->ShowDlg(eDIALOGT_BTMUSIC);
				}
				/*switch (nparam)
				{
					 case 0:
					{
						 pObjc->UpDataIconUnconnect();
					 }
					 case 1:
					 {
						 pObjc->SetBTConected(false);
						 pObj->OnConnectionSetting(NULL);
					 }
				    break;
					 case 5:
					 {
						 pObj->StartCountCallDuration();
						 pObjc->SetBTConected(true);
					 }
					 break;
					 case 2:
					 case 3:
					 case 4:
					 {
							pObj->StopCountCallDuration();
					 }
					 case 6:
					{
					    pObjc->SetBTConected(true);
					}
					break;
					default:
					break;
				}
				pObjc->UpdataBTBottomState();*/
			}
		}
		break;
		case (WM_USER + 6)://更新下载记录条数
		{
			BTDEBUGINFO(L"更新下载记录数目");
			HCBTAddressBookDlg* pObj = static_cast<HCBTAddressBookDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTADDRESSBOOK));
			if(pObj != NULL)
			{
				pObj->SetNotice(static_cast<ePBAPCSTATE>(wParam));
			}
		}
		break;
		case (WM_USER + 7)://电话本和通话记录下载结束
		{
				BTDEBUGINFO(L"电话本通讯录下载结束更新状态");
				HCBTCallRecordsDlg *pObc = static_cast<HCBTCallRecordsDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCALLRECORDS));
				HCBTAddressBookDlg* pObj = static_cast<HCBTAddressBookDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTADDRESSBOOK));
				if(pObj != NULL)
				{
					pObj->SetNoticeShow(false);
				}
				if(pObc != NULL)
				{
					pObc->UpDataRecords(true);
				}
		}
		break;
		case (WM_USER + 8):
		{
			HCBTConnectionssettingDlg* pObj = static_cast<HCBTConnectionssettingDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCONNECTSETTING));
			if(pObj != NULL)
			{
				//pObj->SetNoticeShow((HUINT)wParam);
			}
		}
		break;
		case (WM_USER + 9)://获得当前连接设备信息
		{
			BTDEBUGINFO(L"当前连接设备信息");
			HCBTAddressBookDlg *pObc = static_cast<HCBTAddressBookDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTADDRESSBOOK));
			HCBTConnectionssettingDlg* pObj = static_cast<HCBTConnectionssettingDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCONNECTSETTING));
			if(pObj != NULL)
			{
				if(pObj->IsPairPageShow())
				{
					pObj->OnEnterPairPage(NULL);
				}
				//pObj->SetNoticeSuccess();
				pObj->SetBTConected(true);
				pObj->UpdataBTBottomState();
				pObc->StartDown();
				pObc->StartDownBookData();
			}
		}
		break;
		case (WM_USER + 10)://来电，去电号码显示
		{
			BTDEBUGINFO(L"来电去电号码显示");
			HCBTDialDlg* pObj = static_cast<HCBTDialDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTDIAL));
			sContact *pContact = (sContact*)wParam;
			if(pObj != NULL && pContact != NULL)
			{
				//pObj->UpDataKeyBoardNum();
				pObj->UpDataKeyBoardNum(pContact);
				if(pContact !=NULL)
				{
					delete pContact;
				}
				KCBTDialogManager::Instance()->JumpToDlg(eDIALOGT_BTDIAL);
			}
		}
		break;
		case (WM_USER + 11):
		{
			//HCBTConnectionssettingDlg* pObj = static_cast<HCBTConnectionssettingDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCONNECTSETTING));
			//if(pObj != NULL)
			//{
			//	pObj->SetBTConected(false);
			//	pObj->OnConnectionSetting(NULL);
			//	pObj->UpdataBTBottomState();
			////pObj->UpDataKeyBoard(static_cast<HINT>(wParam));
			//}
		}
	    break;
		case (WM_USER + 12)://下载电话本和通话记录中
			{
				BTDEBUGINFO(L"下载电话本和通话记录中");
				HCBTAddressBookDlg* pObj = static_cast<HCBTAddressBookDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTADDRESSBOOK));
				HCBTCallRecordsDlg *pObc = static_cast<HCBTCallRecordsDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCALLRECORDS));
				if(pObj != NULL)
				{
					pObj->ClearBookDataEx();
					//pObj->OnDowingTimer(NULL);
				}
				if(pObc != NULL)
				{
					pObc->UpDataRecords(false);
					pObc->ClearRecordsData();
				}
			}
			break;
		case (WM_USER + 13):// 关闭蓝牙信息
			{
				BTDEBUGINFO(L"关闭蓝牙信息");
				HCBTConnectionssettingDlg* pObj = static_cast<HCBTConnectionssettingDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCONNECTSETTING));
				if(pObj != NULL)
				{
					pObj->StartCloseBT();
				}
			}
			break;
		case (WM_USER + 14):// 打开蓝牙信息
			{
				BTDEBUGINFO(L"打开蓝牙信息");
				CBTCommand *p = CBTCommand::Instance();
				if(p != NULL)
				{
					p->OpenBT(1,115200);
				}
			}
			break;
#if AUTOUPDATACALLHISTORY
		case (WM_USER + 15)://更新通话记录按钮图标
		{
			BTDEBUGINFO(L"更新通话记录按钮图标");
			HCBTCallRecordsDlg *pObc = static_cast<HCBTCallRecordsDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCALLRECORDS));
			if(pObc != NULL)
			{
				pObc->UpDataRecords(true);
			}
		}
       break;	
#else
#endif
		case(WM_USER + 16)://spp状态变化
			{
				/*BTDEBUGINFO(L"SPP状态变化,nSPPState = %d",wParam);
				HUINT nSPPState = HUINT(wParam);
				CBTHmiDlg* pBtHMIDlg = (CBTHmiDlg*)(KCBTDialogManager::Instance()->GetBTHMIDlg());
				if(pBtHMIDlg != NULL)
				{
					switch (nSPPState)
					{
						case 0:
						{
							pBtHMIDlg->SetSPPConnected(false);
						}
						break;
						case 2:
						{
							pBtHMIDlg->SetSPPConnected(true);
						}
						break;
						default:
						break;
					}	
				}*/
			}
			break;
		case(WM_USER + 17)://HID状态变化
			{
				/*BTDEBUGINFO(L"更新HID状态变化,wparam = %d",wParam);
				HUINT nHIDState = HUINT(wParam);
				CBTHmiDlg* pBtHMIDlg = (CBTHmiDlg*)(KCBTDialogManager::Instance()->GetBTHMIDlg());
				if(pBtHMIDlg != NULL)
				{
					switch (nHIDState)
					{
						case 0:
						{
							pBtHMIDlg->SetHIDConnected(false);
						}
						break;
						case 2:
						{
							pBtHMIDlg->SetHIDConnected(true);
						}
						break;
					default:
					break;
				}	
			}*/
		}
			break;
		case(WM_USER + 18)://坐标归零
			{
				BTDEBUGINFO(L"坐标归零");
				CBTHmiDlg* pBtHMIDlg = (CBTHmiDlg*)(KCBTDialogManager::Instance()->GetBTHMIDlg());
				if(pBtHMIDlg != NULL)
				{
					pBtHMIDlg->BackToZero(NULL);
				}
			}
			break;
#ifdef  AUTOUPDATACALLHISTORY
			case WM_USER + 19://新增电话记录更新，0全部 1未接 2 拨出 3已接
			{
				BTDEBUGINFO(L"新增电话记录更新，0全部 1未接 2 拨出 3已接");
				HCBTCallRecordsDlg *pObc = static_cast<HCBTCallRecordsDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCALLRECORDS));
				if(pObc != NULL)
				{
					pObc->UpDataRecords(true);
					pObc->AutoUpDataRecords();
				}
			}
			break;
#else
#endif
			case WM_USER + 20:
			{
			    HCBTDialDlg* pObj = static_cast<HCBTDialDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTDIAL));
				if(pObj != NULL)
				{
					switch (wParam)
					{
					case 0:
						{
							//BTDEBUGINFO(L"声音切换至手机");
							pObj->ChangeVoicePoisition(0);
						}
						break;
					case 1:
						{
							//BTDEBUGINFO(L"声音切换至车机");
							pObj->ChangeVoicePoisition(1);
						}
						break;
					}
				}
			}
			break;
			case WM_USER + 21:
				{
					s_nDlg = 0;

					/////
					/*HCBTDialDlg* pObj = static_cast<HCBTDialDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTDIAL));
					if(pObj != NULL)
					{
						pObj->SetVoiceToPhone();
					}
					HCBTMusicDlg* pObjMusic = static_cast<HCBTMusicDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTMUSIC));
					if(pObjMusic != NULL)
					{
						pObjMusic->StopMusic();
					}
					Sleep(3);
					CBTCommand::Instance()->DisCurrentConnectDevice();
					::PostMessage(g_hBTWnd,WM_QUIT,0,NULL);
					wprintf(L"IPC_U_SERVER_POWER_OFF :BT quit\r\n");*/
				}
				break;
			case WM_USER + 23://手机端取消下载 0：电话本取消下载  1：全部通话记录取消下载
				{
				//	HCBTCallRecordsDlg* pObjRecords = static_cast<HCBTCallRecordsDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCALLRECORDS));
					HCBTAddressBookDlg* pObjBook = static_cast<HCBTAddressBookDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTADDRESSBOOK));
					if(pObjBook != NULL)
					{
						pObjBook->CancelByPhone();
					}
				}
				break;
			case WM_USER + 24://更新下载通讯录数据  Wparam:5 通讯录 6 来电  7 已拨电话 8 未接电话  9 所有通话记录  Iparam:记录数目
				{
					//wprintf(L"Updata Down Num:Type = %d,Num = %d\r\n",wParam,lParam);
					BTDEBUGINFO(L"Updata Down Num:Type = %d,Num = %d\r\n",wParam,lParam);
					HCBTAddressBookDlg* pObjBook = static_cast<HCBTAddressBookDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTADDRESSBOOK));
					if(pObjBook != NULL)
					{
						pObjBook->UpDateDownLoad(wParam,lParam);
					}
				}
				break;
			case WM_USER + 25://启动拨号恢复定时器
				{
					BTDEBUGINFO(L"______StartCallTimer______");
					  HCBTDialDlg* pObj = static_cast<HCBTDialDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTDIAL));
					  if(pObj != NULL)
					  {
							pObj->StartCallTimer();
					  }
				}
				break;
			case WM_USER + 26:
				{
#if TestBTVISION
					HCBTMusicDlg* pMusic = static_cast<HCBTMusicDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTMUSIC));
					if(pMusic != NULL)
					{
						pMusic->UpdateVision();
						//pMusic->UpdateBtName();
					}
#endif	
				}
				break;
			case WM_USER+27:
				{
					BTDEBUGINFO(L"UpdateDevName");
#if SETBTNAME_MAC
			HCBTConnectionssettingDlg* pObj = static_cast<HCBTConnectionssettingDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCONNECTSETTING));
			if(pObj != NULL)
			{
				pObj->UpdateDevName();
			}
#endif
				}
				break;
		case WM_USER + 50://蓝牙发送队列添加数据数据
			{
				BTDEBUGINFO(L"蓝牙发送队列添加数据数据:Type = %d,pblock = %d",wParam,lParam);
				CBTCommand::Instance()->SendBTCommandBlock((BTPacketDataType_t)wParam,(Block*)lParam);
			}
			break;
		case WM_USER + 222:
			{

			}
			break;
#if TESTRESTARTPROTEM
		case WM_USER +51:
		{
			HCBTConnectionssettingDlg* pObj = static_cast<HCBTConnectionssettingDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTCONNECTSETTING));
			if(pObj != NULL)
			{
				switch (wParam)//0更新启动次数 1清除启动次数
				{
				case 0:
					{
						pObj->UpdataRestTime(g_nRestTime);
					}
					break;
				case 1:
					{
						if(DeleteFile(appPath.c_str()))
						{
							printf("Remove sucess\r\n");
							g_nRestTime = 0;
						}
					}
					break;
				}
			}
		}
		break;
#endif
		default:
		{
			UI_TranslateMsg(message, wParam, lParam, true);
		}
		break;
	}
	return DefWindowProcW(hWnd, message, wParam, lParam);
}

void __stdcall RecvIPCEvent(__in unsigned char uSendID,__in unsigned short uIPCEvent,__in unsigned long uSize,__in const unsigned char * pData)
{
	if( false == ::IsWindow(g_hBTWnd) ) return;
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
	switch (lpIPCEvent->uIPCEvent)
	{
	    case IPC_U_SYS_COM_PROTOCOL:
			{
				::PostMessage(g_hBTWnd, WM_USER , static_cast<WPARAM>(uSendID), reinterpret_cast<LPARAM>(lpIPCEvent));
			}
			break;
		case IPC_U_SYS_CLOSE_PROCESS:
			{
				BTDEBUGINFO(_T("[IPCEventProc] PostMessage(WM_QUIT) \n"));
				//::PostMessage(g_hWnd1,WM_QUIT,NULL,NULL);
				::PostQuitMessage(5);
			}
			break;
		case IPC_U_WND_TOBACK:
			{
				BTDEBUGINFO(L"%s,IPCEvent = IPC_U_WND_TOBACK",__FUNCTIONW__);
				//KCBTDialogManager::Instance()->ReleaseCurrentSource();
			}
			break;
		case IPC_U_WND_INITPARAM:
			{
				BTDEBUGINFO(L"%s,IPCEvent = IPC_U_WND_INITPARAM",__FUNCTIONW__);
				//KCBTDialogManager::Instance()->RequreCurrentSource();
			}
			break;
		case IPC_U_SERVER_POWER_OFF:
			{
				BTDEBUGINFO(L"IPC_U_SERVER_POWER_OFF");
				HCBTDialDlg* pObj = static_cast<HCBTDialDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTDIAL));
				if(pObj != NULL)
				{
					pObj->SetVoiceToPhone();
				}
				HCBTMusicDlg* pObjMusic = static_cast<HCBTMusicDlg*>(KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTMUSIC));
				if(pObjMusic != NULL)
				{
					pObjMusic->StopMusic();
				}
				Sleep(3);
				CBTCommand::Instance()->DisCurrentConnectDevice();
				::PostMessage(g_hBTWnd,WM_QUIT,0,NULL);
				wprintf(L"IPC_U_SERVER_POWER_OFF :BT quit\r\n");
			}
			break;
		default:
			{
			}
		break;
	}
}

//主程序
HINT APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, HINT nCmdShow)
{
	DWORD nCostTime = GetTickCount();
	CBTCommand *pComand=CBTCommand::Instance(); 
	if(pComand != NULL)
	{
		pComand->LowBTPower();
	}
	wprintf(L"[wWinMain] Begin\r\n");
	//g_Mutex =::CreateMutex(NULL, TRUE, APP_CLASSNAME_TEST1);
	INSTANCE_START
	HINT nParam = 0;
	_stscanf_s(GetCommandLine(),_T("%d"),&nParam);
	nCmdShow = PARAM_SHOW_CMD(nParam);
	s_Show = nCmdShow;
	BTDEBUGINFO(L"nCmdShow = %d",nCmdShow);
	HINT nDlg = PARAM_BT_DLG_CMD(nParam);
	BTDEBUGINFO(L"nDlg = %d",nDlg);
	s_nDlg = nDlg;
//	HINT nDlgType =	PARAM_BT_DLG_CMD(nParam);	
	// HMI 初始化
	if( !UIDevInit(
		SCREEN_WIDTH, SCREEN_HEIGHT,
		hInstance,
		const_cast<HCHAR*>(STR_PROCESSNAME_BT),
		const_cast<HCHAR*>(STR_PROCESSNAME_BT),
		0,
		g_hBTWnd) )
	{
		return 0;
	}
	::ShowWindow(g_hBTWnd, nCmdShow);
	SetOwnerProc(MyProc);   //注册回调
	// 注册IPC
	//移到后面
	CEIPC_Regist(IPC_ID_BT, g_hBTWnd, RecvIPCEvent);
	//	切换字体
	GetRESingleton()->ReLoadFont(FONT_MSYH_TTF);
	GetRESingleton()->ReLoadFont(FONT_QUARTZ_REGULAR_TTF);
	InitPopupSurface(GetHMIPath(_T("")).c_str());
	KCBTDialogManager* pObj =  KCBTDialogManager::Instance();

	
	btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
	if(pComand != NULL)
	{
		pComand->SetMyhWnd(g_hBTWnd);
		pComand->OnInit(1,115200);
		nCostTime = GetTickCount() - nCostTime;
		BTDEBUGINFO(L"%s,CostTime1 = %d",__FUNCTIONW__,nCostTime);
		nCostTime = GetTickCount();
	}
	if(pObj != NULL)
	{
	   pObj->CreateAllBTDlg();
		pComand->SendGetBTInfo();
		pObj->ShowDlg(eDIALOGT_BTCONNECTSETTING);
	
		nCostTime = GetTickCount() - nCostTime;
		BTDEBUGINFO(L"%s,CostTime2 = %d",__FUNCTIONW__,nCostTime);
		nCostTime = GetTickCount();
		//pObj->ShowBTHMIDlg();
	}	 
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
	//::ShowWindow(g_hBTWnd, nCmdShow);
	::UpdateWindow(g_hBTWnd);
	//CEIPC_Regist(IPC_ID_BT, g_hBTWnd, RecvIPCEvent);
	//s_nDlg = 4;
	if(s_nDlg == 4)
	{
		BTDEBUGINFO(L"s_nDlg == 4");
		UINT nrett = SetTimer(g_hBTWnd,15,10000,SetDlg);
		if(nrett == 0)
		{
			BTDEBUGINFO(L"SetTimer error: %d",GetLastError());
		}
	}
	nCostTime = GetTickCount() - nCostTime;
	BTDEBUGINFO(L"%s,CostTime3 = %d",__FUNCTIONW__,nCostTime);
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
#if BTLOGSTATE
	appPath += L"..\\Config\\BTLog.txt";
	g_Logfile1.open(appPath.c_str(),ios::app);
#else
#endif
#if TESTRESTARTPROTEM
	 char buffer[256] = {0};
	 char buffer1[256] = {0};
	 char Num[20] ={0};
	  ifstream examplefile1;
	  int i1,j1;
	  i1= j1 = 0;
	  int nn = 0;
	appPath += L"..\\Config\\BTPro.txt";
	examplefile1.open(appPath.c_str());
	if(!examplefile1)
	{
		printf("File Not Exsit\r\n");
		g_nRestTime = 1;
	}
	else
	{
		while (! examplefile1.eof() ) 
		{
			memset(buffer,0,sizeof(buffer));
			examplefile1.getline(buffer,100);
			if(buffer[0] == 'T')
			{
				memset(buffer1,0,sizeof(buffer1));
				memcpy(buffer1,buffer,100);
			}
			//nn++;
		//cout<<"====="<<nn<<endl;
		}
		while (buffer1[i1] != '^')
		{
			i1++;
				cout<<"i= "<<i1<<endl;
		}
		j1 = i1 + 1;
		while (buffer1[j1] != '^')
		{
			j1++;
			cout<<"j = "<<j1<<endl;
		}
		if(i1 < j1 && i1 > 0 && (j1-i1)  < 10)
		{
			memcpy(Num,buffer1+i1+1,j1-i1-1);
		}
		g_nRestTime = atoi(Num) + 1;
		cout << "666++++"<<g_nRestTime<<endl;
		examplefile1.close();
	}
	g_Profile1.open(appPath.c_str(),ios::app);
	char Temm[200] = {0};
	//sprintf(Temm,"Totol^%d^^^^%d\n",g_nRestTime,GetTickCount());
	//g_Profile1.write(Temm);
	g_Profile1<<"Total^"<<g_nRestTime<<"^^^^"<<GetTickCount()<<endl;
	//g_Profile1<<"Total^"<<g_nRestTime<<"^^^^"<<GetTickCount()<<endl;
	g_Profile1.close();
#endif
	//消息循环
	MSG msg;
	UINT nretTime = SetTimer(g_hBTWnd,10,1000,CheckHDMISignal);
	if(nretTime == 0)
	{
		BTDEBUGINFO(L"SetTimer error: %d",GetLastError());
	}
	DWORD dwClickDownTime = GetTickCount();
	while(GetMessage(&msg, NULL, 0, 0))
	{
		eDIALOGTYPE  eDlgType = KCBTDialogManager::Instance()->GetCurrentDlgType();
		if(GetTickCount() - dwClickDownTime >= 800 && msg.message == WM_LBUTTONDOWN && ((eDlgType == eDIALOGT_BTADDRESSBOOK) || (eDlgType == eDIALOGT_BTCALLRECORDS)))
		{
			dwClickDownTime = GetTickCount();
		}
		else if(msg.message == WM_LBUTTONDOWN && GetTickCount() - dwClickDownTime < 800 && ((eDlgType == eDIALOGT_BTADDRESSBOOK) || (eDlgType == eDIALOGT_BTCALLRECORDS)))
		{
            continue;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	CEIPC_UnRegist();
	CBTCommand::DeleteInstance();
	KCBTDialogManager::Instance()->DeleteInstance();
	btSource::Instance()->DeleteInstance();
	//UnInitPopupSurface();
	//释放
	UIDevRelease();
	KillTimer(g_hBTWnd,10);
	KillTimer(g_hBTWnd,15);
	HWND hServerWnd = ::FindWindow(STR_PROCESSNAME_MANAGE, STR_PROCESSNAME_MANAGE);
	HWND hBtUpateWnd = ::FindWindow(L"BTAPP.exe", L"BTAPP.exe");
	if(hBtUpateWnd != NULL)
	{
			::PostMessage(hBtUpateWnd, WM_USER + 1000, 0, NULL);
			
	}
	//printf("+++++++++++++VWM_SERVER_SRC_CLOSE+++++IPC_ID_BT++++++\r\n");
	if (hServerWnd)
	{
		::PostMessage(hServerWnd, VWM_SERVER_SRC_CLOSE, IPC_ID_BT, NULL);
	}

	return 0;
}