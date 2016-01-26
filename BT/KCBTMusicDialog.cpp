#pragma once
#include "KCBTMusicDialog.h"
#include "KHMIBaseHead.h"
#include "KCBTCommand.h"
#include "KCBTDialogManager.h"
HCBTMusicDlg::HCBTMusicDlg()
{
	m_pGrpCtrlBTMusicMiddle = NULL;
	m_pTxtBTMusicBK = NULL;
	m_pTxtBTMusicSong = NULL;
	m_pTxtBTMusicSinger = NULL;
	m_pTxtBTMusicAlbum = NULL;
	m_pBtnBTMusicUp = NULL;
	m_pBtnBTMusicDown = NULL;
	m_pTxtBTMusicPlayPause = NULL;
	m_pTxtBTMusicHandleBK = NULL;
};
HCBTMusicDlg::~HCBTMusicDlg()
{
	SAFE_DELETE(m_pTxtBTMusicHandleBK);
	SAFE_DELETE(m_pTxtBTMusicPlayPause);
	SAFE_DELETE(m_pBtnBTMusicDown);
	SAFE_DELETE(m_pBtnBTMusicUp);
	SAFE_DELETE(m_pTxtBTMusicAlbum);
	SAFE_DELETE(m_pTxtBTMusicSinger);
	SAFE_DELETE(m_pTxtBTMusicSong);
	SAFE_DELETE(m_pTxtBTMusicBK);
	SAFE_DELETE(m_pGrpCtrlBTMusicMiddle);
};
HINT HCBTMusicDlg::OnInit()
{
	HINT  nRet =  HCBluetoothBaseDlg::OnInit();
	//m_pTxtScreen->SetText(L"À¶ÑÀÒôÀÖ");
	m_pGrpCtrlBTMusicMiddle = new HCGroupCtrl;
	if(m_pGrpCtrlBTMusicMiddle != NULL)
	{
		m_pGrpCtrlBTMusicMiddle->SetShow(true);
		AddChild(m_pGrpCtrlBTMusicMiddle);
		//À¶ÑÀÒôÀÖ±³¾°
		m_pTxtBTMusicBK = new HCImageCtrl;
		if(m_pTxtBTMusicBK != NULL)
		{
			m_pTxtBTMusicBK->Create(0,68,800,266);
			m_pTxtBTMusicBK->EnableMsg(false);
			m_pGrpCtrlBTMusicMiddle->AddChild(m_pTxtBTMusicBK);
		}
		m_pTxtMusicSong = new HCTextCtrl;
		if(m_pTxtMusicSong != NULL)
		{
			m_pTxtMusicSong->Create(326,115,64,24);
			m_pTxtMusicSong->EnableMsg(false);
			m_pTxtMusicSong->SetTextStyle(RE_TS_NORMAL);
			m_pTxtMusicSong->SetTextPos(0,0);
			m_pTxtMusicSong->SetFontSize(24,24);
			m_pTxtMusicSong->SetRoll(false);
			m_pTxtMusicSong->SetTxtColor(255,255,255);
			m_pTxtMusicSong->SetText(_T("¸èÇú:"));
			m_pGrpCtrlBTMusicMiddle->AddChild(m_pTxtMusicSong);
		}
		m_pTxtMusicSinger = new HCTextCtrl;
		if(m_pTxtMusicSinger != NULL)
		{
			m_pTxtMusicSinger->Create(326,171,64,24);
			m_pTxtMusicSinger->EnableMsg(false);
			m_pTxtMusicSinger->SetTextStyle(RE_TS_NORMAL);
			m_pTxtMusicSinger->SetTextPos(0,0);
			m_pTxtMusicSinger->SetFontSize(24,24);
			m_pTxtMusicSinger->SetRoll(false);
			m_pTxtMusicSinger->SetTxtColor(255,255,255);
			//m_pTxtMusicSinger->SetText(_T("¸èÊÖ:"));
			m_pGrpCtrlBTMusicMiddle->AddChild(m_pTxtMusicSinger);
		}
		m_pTxtMusicAlbum = new HCTextCtrl;
		if(m_pTxtMusicAlbum != NULL)
		{
			m_pTxtMusicAlbum->Create(326,227,64,24);
			m_pTxtMusicAlbum->EnableMsg(false);
			m_pTxtMusicAlbum->SetTextStyle(RE_TS_NORMAL);
			m_pTxtMusicAlbum->SetTextPos(0,0);
			m_pTxtMusicAlbum->SetFontSize(24,24);
			m_pTxtMusicAlbum->SetRoll(false);
			m_pTxtMusicAlbum->SetTxtColor(255,255,255);
			//m_pTxtMusicAlbum->SetText(_T("×¨¼­:"));
			m_pGrpCtrlBTMusicMiddle->AddChild(m_pTxtMusicAlbum);
		}
		//¸èÇúÎÄ±¾
		m_pTxtBTMusicSong = new HCTextCtrl;
		if(m_pTxtBTMusicSong != NULL)
		{
			m_pTxtBTMusicSong->Create(392,115,338,24);
			m_pTxtBTMusicSong->EnableMsg(true);
			m_pTxtBTMusicSong->SetTextStyle(RE_TS_NORMAL);
			m_pTxtBTMusicSong->SetTextPos(0,0);
			m_pTxtBTMusicSong->SetFontSize(24,24);
			m_pTxtBTMusicSong->SetRoll(true);
			m_pTxtBTMusicSong->SetTxtColor(255,255,255);
			//m_pTxtBTMusicSong->SetText(_T("Î´ÖªÇúÄ¿"));
			m_pGrpCtrlBTMusicMiddle->AddChild(m_pTxtBTMusicSong);
		}
		//¸èÊÖÎÄ±¾
		m_pTxtBTMusicSinger = new HCTextCtrl;
		if(m_pTxtBTMusicSinger != NULL)
		{
			m_pTxtBTMusicSinger->Create(392,171,338,24);
			m_pTxtBTMusicSinger->EnableMsg(true);
			m_pTxtBTMusicSinger->SetTextStyle(RE_TS_NORMAL);
			m_pTxtBTMusicSinger->SetTextPos(0,0);
			m_pTxtBTMusicSinger->SetFontSize(24,24);
			m_pTxtBTMusicSinger->SetRoll(true);
			m_pTxtBTMusicSinger->SetTxtColor(255,255,255);
			//m_pTxtBTMusicSinger->SetText(_T("Î´Öª¸èÊÖ"));
			m_pGrpCtrlBTMusicMiddle->AddChild(m_pTxtBTMusicSinger);
		}
		//×¨¼­ÃûÎÄ±¾
		m_pTxtBTMusicAlbum = new HCTextCtrl;
		if(m_pTxtBTMusicAlbum != NULL)
		{
			m_pTxtBTMusicAlbum->Create(392,227,338,24);
			m_pTxtBTMusicAlbum->EnableMsg(true);
			m_pTxtBTMusicAlbum->SetTextStyle(RE_TS_NORMAL);
			m_pTxtBTMusicAlbum->SetTextPos(0,0);
			m_pTxtBTMusicAlbum->SetFontSize(24,24);
			m_pTxtBTMusicAlbum->SetRoll(true);
			m_pTxtBTMusicAlbum->SetTxtColor(255,255,255);
			//m_pTxtBTMusicAlbum->SetText(_T("Î´Öª×¨¼­"));
			m_pGrpCtrlBTMusicMiddle->AddChild(m_pTxtBTMusicAlbum);
		}
		//À¶ÑÀÒôÀÖ²Ù×÷±³¾°
		m_pTxtBTMusicHandleBK = new HCImageCtrl;
		if(m_pTxtBTMusicHandleBK != NULL)
		{
			m_pTxtBTMusicHandleBK->Create(0,335,800,78);
			m_pTxtBTMusicHandleBK->EnableMsg(false);
			m_pGrpCtrlBTMusicMiddle->AddChild(m_pTxtBTMusicHandleBK);
		}
		//ÉÏÒ»Çú°´Å¥
		m_pBtnBTMusicUp = new HCButton;
		if(m_pBtnBTMusicUp != NULL)
		{
			m_pBtnBTMusicUp->Create(168, 345, 64, 60);
			m_pBtnBTMusicUp->SetCallBack(OnBack,this);
			m_pBtnBTMusicUp->EnableMsg(true);
			m_pGrpCtrlBTMusicMiddle->AddChild(m_pBtnBTMusicUp);
		}	
		//ÏÂÒ»Çú°´Å¥
		m_pBtnBTMusicDown = new HCButton;
		if(m_pBtnBTMusicDown != NULL)
		{
			m_pBtnBTMusicDown->Create(568, 345, 64, 60);
			m_pBtnBTMusicDown->SetCallBack(OnForward,this);
			m_pBtnBTMusicDown->EnableMsg(true);
			m_pGrpCtrlBTMusicMiddle->AddChild(m_pBtnBTMusicDown);
		}
		//²¥·ÅÔÝÍ£°´Å¥
		m_pTxtBTMusicPlayPause = new HCButton;
		if(m_pTxtBTMusicPlayPause != NULL)
		{
			m_pTxtBTMusicPlayPause->Create(368, 345, 64, 60);
			m_pTxtBTMusicPlayPause->EnableMsg(true);
			m_pTxtBTMusicPlayPause->SetCallBack(OnPlayPause,this);
			m_pGrpCtrlBTMusicMiddle->AddChild(m_pTxtBTMusicPlayPause);
		}
		m_pTxtA2DPState = new HCTextCtrl;
		if(m_pTxtA2DPState != NULL)
		{
			m_pTxtA2DPState->Create(300,320,200,30);
			m_pTxtA2DPState->SetFontSize(20,20);
			m_pTxtA2DPState->SetTextStyle(RE_TS_CENTER);
			m_pTxtA2DPState->SetTextPos(100,15);
			//m_pTxtA2DPState->SetText(L"A2DPÎ´Á¬½Ó");
			m_pTxtA2DPState->SetShow(false);
			//AddChild(m_pTxtA2DPState);
		}
		 m_bPlaySend = false;
		 m_bPauseSend = false;
		//SetBTDlgBackGround();
		//ChangeLangue(0);
#if BTMUSIC_NUMBER_STATE
		m_pTxtCurrentPlayNumber = new HCTextCtrl;
		if(m_pTxtCurrentPlayNumber != NULL)
		{
			m_pTxtCurrentPlayNumber->Create(290,270,100,32);
			m_pTxtCurrentPlayNumber->SetFontSize(24,24);
			m_pTxtCurrentPlayNumber->SetTxtColor(255,255,255);
			//  m_pTxtAlbum->SetText(s_pLan[48]);
			//m_pTxtAlbum->SetRollWidth(460);
			m_pTxtCurrentPlayNumber->SetShow(false);
			m_pTxtCurrentPlayNumber->EnableMsg(false);
			m_pGrpCtrlBTMusicMiddle->AddChild(m_pTxtCurrentPlayNumber);
		}
#endif
#if TestBTVISION
		m_pBtnVision = new HCButton;
		if(m_pBtnVision != NULL)
		{
			m_pBtnVision->Create(0, 345, 120, 40);
			m_pBtnVision->EnableMsg(true);
			m_pBtnVision->SetFontSize(24,24);
			m_pBtnVision->SetCallBack(OnPlayPause,this);
			AddChild(m_pBtnVision);
		}
#endif
		SETUPSETTING LSetting;
		KCLastMemory::GetInstance()->GetSetupMemory(LSetting);
		BTDEBUGINFO(L"LSetting.cLang = %d",LSetting.cLang);
		switch (LSetting.cLang)
		{
		case 0:
			{
				ChangeLangue(0);
			}
			break;
		case 1:
			{
				ChangeLangue(1);
			}
			break;
		default:
			break;
		}
	}
	m_pTxtBTMusicPlayPause->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Pause_N.hfp")));
	m_pTxtBTMusicPlayPause->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Pause_A.hfp")));
	m_eBTMusicStatus = eBTMUSICPAUSE;
	return nRet;
}
void HCBTMusicDlg::ChangeLangue(HINT nType)
{
	HCBluetoothBaseDlg::ChangeLangue(nType);

	if(s_pLan != NULL)
	{
		BTDEBUGINFO(L"HCBTMusicDlg::%s,%d",__FUNCTIONW__,nType);
		switch(nType)
		{
			case 0:
			{
				m_pTxtScreen->SetFontSize(24,24);
				m_pTxtMusicSong->SetFontSize(24,24);
				m_pTxtMusicSinger->SetFontSize(24,24);
				m_pTxtMusicAlbum->SetFontSize(24,24);
				m_pTxtBTMusicSong->SetFontSize(24,24);
				m_pTxtBTMusicSinger->SetFontSize(24,24);
				m_pTxtBTMusicAlbum->SetFontSize(24,24);
			}
			break;
			case 1:
			{
				m_pTxtScreen->SetFontSize(18,18);
				m_pTxtMusicSong->SetFontSize(18,18);
				m_pTxtMusicSinger->SetFontSize(18,18);
				m_pTxtMusicAlbum->SetFontSize(18,18);
				m_pTxtBTMusicSong->SetFontSize(18,18);
				m_pTxtBTMusicSinger->SetFontSize(18,18);
				m_pTxtBTMusicAlbum->SetFontSize(18,18);
			}
			break;
			default:
			break;
		}
		sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
		m_pTxtA2DPState->SetText(s_pLan[38]);
		if(p->BTAVRCPData.nA2DPState == 0)
		{
			if(!m_pTxtA2DPState->IsShow())
			{
				m_pTxtA2DPState->SetShow(true);
			}
		}
		else
		{
			if(m_pTxtA2DPState->IsShow())
			{
				m_pTxtA2DPState->SetShow(false);
			}
		}
		m_pTxtScreen->SetText(s_pLan[3]);
		m_pTxtMusicSong->SetText(s_pLan[19]);
		m_pTxtMusicSinger->SetText(s_pLan[20]);
		m_pTxtMusicAlbum->SetText(s_pLan[21]);
		m_pTxtBTMusicSong->SetText(s_pLan[22]);
		m_pTxtBTMusicSinger->SetText(s_pLan[23]);
		m_pTxtBTMusicAlbum->SetText(s_pLan[24]);
	}

}
 HBOOL HCBTMusicDlg::DoMessage(HMessage* msg)
{
		switch( (HINT)msg->msgtype )
		{
			case VWM_SERVER_KEY_ROTATE:
			{
				BTDEBUGINFO(L"VWM_SERVER_KEY_ROTATE,wparam = %d,Iparam = %d",msg->wParam,msg->lParam);
				if (eKEY_VOL == msg->wParam)
				{
					
					SOUNDSETTING seting;
					KCLastMemory::GetInstance()->GetSoundMemory(seting);
					if (0 == seting.uSoundVol)
					{
						//OnPlayMute(NULL);
					}	
				/*	if(msg->lParam == 0)
					{
						BTDEBUGINFO(L"¡ª¡ª¡ª¡ª¡ª¡ª¾²Òô¡ª¡ª¡ª¡ª¡ª¡ª¡ª");
						OnPlayMute(NULL);
					}*/
					else
					{
						sBTCommandData*pData =  CBTCommand::Instance()->GetBTCommandData();
						HCBluetoothBaseDlg* pDlg =  KCBTDialogManager::Instance()->GetCurrentDlg();
						HCBluetoothBaseDlg* pDlgMusic =  KCBTDialogManager::Instance()->GetDlg(eDIALOGT_BTMUSIC);
						SOUNDSETTING seting;
						KCLastMemory::GetInstance()->GetSoundMemory(seting);
						if(pData != NULL && pDlg == pDlgMusic && pDlgMusic != NULL)
						{
							//Sleep(20);
							if(pData->BTHFPData.nHFPState == 2 && pData->BTAVRCPData.nA2DPState == 2 && seting.uSoundVol != 0)
							{
#if TESTBTCOMMANDQUEUE
			//CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketAVRCPAPlayOrPause,NULL);
#else

								HBYTE cCommand  [20] = {0};
								HUINT nCmdlen = strlen("AT+PP\r\n");
								strncpy((char*)cCommand,"AT+PP\r\n",nCmdlen);
								//CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
							}
						}
					}
				}
			}
			break;
		}
		HBOOL bRet = false;
		bRet = KDialogP::DoMessage(msg);
		return bRet;
}
void HCBTMusicDlg::SetBTDlgBackGround()
{
	EnableUpdateRect(false);
	HCBluetoothBaseDlg::SetBTDlgBackGround();
	HCBluetoothBaseDlg::SetBTMSCBK();
//	m_pBtnBTMusic->SetBkgndA(pSource->m_pbtBaseMusicA);
	//À¶ÑÀÒôÀÖ±³¾°
	m_pTxtBTMusicBK->SetBkgndN(GetHMIPath(_T("\\Bluetooth\\Bt_Music\\Bt_Music_Frame.hfp")));
	m_pTxtBTMusicBK->SetOpacity(8);
	//À¶ÑÀÒôÀÖ²Ù×÷±³¾°
	m_pTxtBTMusicHandleBK->SetBkgndN(GetHMIPath(_T("Bluetooth\\Bt_Music\\Bt_Music_Control_Frame.hfp")));
	m_pTxtBTMusicHandleBK->SetOpacity(8);
	//ÉÏÒ»Çú
	m_pBtnBTMusicUp->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Prev_N.hfp")));
	m_pBtnBTMusicUp->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Prev_A.hfp")));
	//ÏÂÒ»Çú
	m_pBtnBTMusicDown->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Next_N.hfp")));
	m_pBtnBTMusicDown->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Next_A.hfp")));
	//ÔÝÍ£
	//m_pTxtBTMusicPlayPause->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Pause_N.hfp")));
	//m_pTxtBTMusicPlayPause->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Pause_A.hfp")));
	EnableUpdateRect(true);
}
void HCBTMusicDlg::OnPlayPause(void* pDlg, void* param)
{
	HCBTMusicDlg* pObj = (HCBTMusicDlg*)pDlg;
	pObj->OnPlayPause(pObj);
}
void HCBTMusicDlg::OnPlayPause(void* pDlg)
{
//#ifdef TESTBTCOMMANDQUEUE
//	CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketA2DPMute,0);
//
//#else
//	HBYTE cCommand[20] = {0};
//	HUINT nCmdlen = 0;
//	nCmdlen = strlen("AT+A2DPMUTE\r\n");
//	strncpy((char*)cCommand,"AT+A2DPMUTE\r\n",nCmdlen);
//	CBTCommand::Instance()->SendData(cCommand,nCmdlen);
//#endif
	//return ;
	SOUNDSETTING seting;
	KCLastMemory::GetInstance()->GetSoundMemory(seting);
	sBTCommandData*pData =  CBTCommand::Instance()->GetBTCommandData();
	{
		if(pData != NULL)
		{
			if(pData->BTAVRCPData.nA2DPState == 2 && seting.uSoundVol == 0)
			{
				::PostMessage(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_TO_SERVER_CANCAL_MUTE,NULL,NULL);
			}
			else
			{
#ifdef  TESTBTCOMMANDQUEUE
				CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketAVRCPAPlayOrPause,NULL);
#else
				HBYTE cCommand  [20] = {0};
				HUINT nCmdlen = strlen("AT+PP\r\n");
				strncpy((char*)cCommand,"AT+PP\r\n",nCmdlen);
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
			}
		}
	}
	
	//if(m_eBTMusicStatus == eBTMUSICPAUSE)
	//{
	//	m_eBTMusicStatus = eBTMUSICPLAY;
	//}
	//else
	//{
	//	m_eBTMusicStatus = eBTMUSICPAUSE;
	//}
}
void HCBTMusicDlg::OnForward(void* pDlg, void* param)
{
	HCBTMusicDlg* pObj = (HCBTMusicDlg*)pDlg;
	pObj->OnForward(pObj);
}
void HCBTMusicDlg::OnForward(void* pDlg)
{

	sBTCommandData* pData =  CBTCommand::Instance()->GetBTCommandData();	

	{
		SOUNDSETTING seting;
		KCLastMemory::GetInstance()->GetSoundMemory(seting);	
		//return;
		if(pData != NULL)
		{
			if((pData->BTAVRCPData.nA2DPState == 2 || pData->BTAVRCPData.nA2DPState == 3) && seting.uSoundVol == 0)
			{
				::PostMessage(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_TO_SERVER_CANCAL_MUTE,NULL,NULL);
			}
		}
	}	


#ifdef  TESTBTCOMMANDQUEUE
	CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketAVRCPANext,NULL);
#else
	HBYTE cCommand  [20] = {0};
	HUINT nCmdlen = strlen("AT+FWD\r\n");
	strncpy((char*)cCommand,"AT+FWD\r\n",nCmdlen);
	CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
	BTDEBUGINFO(L"[HCBTMusicDlg::OnForward] end");
}
void HCBTMusicDlg::OnBack(void* pDlg, void* param)
{
	HCBTMusicDlg* pObj = (HCBTMusicDlg*)pDlg;
	pObj->OnBack(pObj);
}
void HCBTMusicDlg::OnBack(void* pDlg)
{
	sBTCommandData*pData =  CBTCommand::Instance()->GetBTCommandData();
	{
		if(pData != NULL)
		{
			SOUNDSETTING seting;
			KCLastMemory::GetInstance()->GetSoundMemory(seting);
			if((pData->BTAVRCPData.nA2DPState == 2 || pData->BTAVRCPData.nA2DPState == 3) && seting.uSoundVol == 0)
			{
				::PostMessage(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_TO_SERVER_CANCAL_MUTE,NULL,NULL);
			}
		}
	}
#ifdef  TESTBTCOMMANDQUEUE
	CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketAVRCPAPrevious,NULL);
#else
	HBYTE cCommand[20] = {0};
	HUINT nCmdlen = strlen("AT+BACK\r\n");
	strncpy((char*)cCommand,"AT+BACK\r\n",nCmdlen);
	CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
	//HBYTE  cc[100] = {0};
	//nCmdlen =  strlen("\r\n+PBSTAT=2\r\n");
	//strncpy((char*)cc,"\r\n+PBSTAT=2\r\n",nCmdlen);
	//PortRetureData* pp = new PortRetureData;
//	pp->dwSize = nCmdlen;
//	pp->pszAnsiData= cc;
	//sBTPacketDataBuffer *p =  CBTCommand::Instance()->CreatBTEmptyPacket();
	//CBTCommand::Instance()->ReadSerialData(p,WM_PORT_READ_DATA,enPortReadOK,(LPARAM)pp);
	//SAFE_DELETE(pp);
}
HINT HCBTMusicDlg::UpDataMediaInfo(void)
{
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	if(p != NULL && p->BTAVRCPData.sAVRCPMusicINFO.nGetData > 0)
	{
		HCHAR szTemp[50] = {0};
		memset(szTemp,0,sizeof(szTemp));
		//wcsncpy(szTemp,L"¸èÇú:",3);
		wcsncpy(szTemp,p->BTAVRCPData.sAVRCPMusicINFO.szMusicTitle,30);
		m_pTxtBTMusicSong->SetText(szTemp);
		memset(szTemp,0,sizeof(szTemp));
		//wcsncpy(szTemp,L"¸èÊÖ:",3);
		wcsncpy(szTemp,p->BTAVRCPData.sAVRCPMusicINFO.szMusicArtist,30);
		m_pTxtBTMusicSinger->SetText(szTemp);
		memset(szTemp,0,sizeof(szTemp));
		//wcsncpy(szTemp,L"×¨¼­:",3);
		wcsncpy(szTemp,p->BTAVRCPData.sAVRCPMusicINFO.szMusicAlbum,30);
		m_pTxtBTMusicAlbum->SetText(szTemp);
		BTDEBUGINFO(L"nCur = %d,nTol = %d",p->BTAVRCPData.sAVRCPMusicINFO.nCurNum,p->BTAVRCPData.sAVRCPMusicINFO.nTolNum);
#if BTMUSIC_NUMBER_STATE
		if(p->BTAVRCPData.sAVRCPMusicINFO.nGetData >= 2 && p->BTAVRCPData.sAVRCPMusicINFO.nCurNum > 0 && p->BTAVRCPData.sAVRCPMusicINFO.nCurNum <= p->BTAVRCPData.sAVRCPMusicINFO.nTolNum)
		{
			HCHAR szCurrentNum[15] = {0};
			wsprintf(szCurrentNum,L"%s/%s",p->BTAVRCPData.sAVRCPMusicINFO.szMusicNumber,p->BTAVRCPData.sAVRCPMusicINFO.szMusicTotalNumber);
			m_pTxtCurrentPlayNumber->SetText(szCurrentNum);
			if(!m_pTxtCurrentPlayNumber->IsShow())
			{
				m_pTxtCurrentPlayNumber->SetShow(true);
			}
		}
		else
		{
			if(m_pTxtCurrentPlayNumber->IsShow())
			{
				m_pTxtCurrentPlayNumber->SetText(false);
			}
		}
#endif
	}
	return 0;
}
HINT HCBTMusicDlg::UpDataPlayState(eBTMUSICRUNNINGSTATUS ePlayState)
{
	m_eBTMusicStatus = ePlayState;
	switch (ePlayState)
	{
		case eBTMUSICPLAY:
		{
			m_pTxtBTMusicPlayPause->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Play_N.hfp")));
			m_pTxtBTMusicPlayPause->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Play_A.hfp")));
			if(m_pTxtA2DPState->IsShow())
			{
				m_pTxtA2DPState->SetShow(false);
			}
		}
		break;
		case eBTMUSICPAUSE:
		{
			m_pTxtBTMusicPlayPause->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Pause_N.hfp")));
			m_pTxtBTMusicPlayPause->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Pause_A.hfp")));
			if(m_pTxtA2DPState->IsShow())
			{
				m_pTxtA2DPState->SetShow(false);
			}
		}
		break;
		case eBTMUSICSTOP:
		{
			if(!m_pTxtA2DPState->IsShow())
			{
				m_pTxtA2DPState->SetShow(true);
			}
			m_pTxtBTMusicPlayPause->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Pause_N.hfp")));
			m_pTxtBTMusicPlayPause->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Pause_A.hfp")));
		}
		break;
		default:
		break;
	}
	m_bPauseSend = false;
	m_bPlaySend = false;
	return 0;
}
void HCBTMusicDlg::OnPlayMute(void* pDlg, void* param)
{
	HCBTMusicDlg* pObj = (HCBTMusicDlg*)pDlg;
	pObj->OnPlayMute(pObj);
}
void HCBTMusicDlg::OnPlayMute(void* pDlg)
{
	sBTCommandData*pData = CBTCommand::Instance()->GetBTCommandData();
	if(pData != NULL)
	{
		if(pData->BTAVRCPData.nA2DPState == 3)
		{
#ifdef  TESTBTCOMMANDQUEUE
			CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketAVRCPAPlayOrPause,NULL);
#else
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+PP\r\n");
			strncpy((char*)cCommand,"AT+PP\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
		}
	}
}

void HCBTMusicDlg::ClearMusicInfo()
{
	CBTCommand* p = CBTCommand::Instance();
	if(m_pTxtBTMusicPlayPause != NULL && m_pTxtBTMusicAlbum != NULL && m_pTxtBTMusicSinger != NULL && m_pTxtBTMusicSong != NULL && p != NULL)
	{
		//m_pTxtBTMusicAlbum->SetText(L"Î´Öª×¨¼­");
		//m_pTxtBTMusicSong->SetText(L"Î´ÖªÇúÄ¿");
		//m_pTxtBTMusicSinger->SetText(L"Î´Öª¸èÊÖ");
		m_pTxtBTMusicSong->SetText(s_pLan[22]);
		m_pTxtBTMusicSinger->SetText(s_pLan[23]);
		m_pTxtBTMusicAlbum->SetText(s_pLan[24]);
		m_pTxtBTMusicPlayPause->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Pause_N.hfp")));
		m_pTxtBTMusicPlayPause->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Pause_A.hfp")));
#if BTMUSIC_NUMBER_STATE
		m_pTxtCurrentPlayNumber->SetText(L" ");
		if(m_pTxtCurrentPlayNumber->IsShow())
		{
			m_pTxtCurrentPlayNumber->SetShow(false);
		}
#endif
		bool bMute = p->GetBTCommandData()->BTAVRCPData.bA2DPMute;
		p->ResetBTAVRCPData(&((p->GetBTCommandData())->BTAVRCPData));
		p->GetBTCommandData()->BTAVRCPData.bA2DPMute = bMute;
		m_bPlaySend = false;
		m_bPauseSend = false;
	}
}
void HCBTMusicDlg::StopMusic()
{
	sBTCommandData*pData =  CBTCommand::Instance()->GetBTCommandData();
	if(pData != NULL)
	{
		
		//if(pData->BTHFPData.nHFPState == 2 && pData->BTAVRCPData.nA2DPState == 3 && !m_bPauseSend)
		if(pData->BTHFPData.nHFPState == 2 && pData->BTAVRCPData.eAVRCPPlayState == eBTMUSICPLAY && !m_bPauseSend)
		{
#ifdef  TESTBTCOMMANDQUEUE
			CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketAVRCPAPlayOrPause,NULL);
#else
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+PP\r\n");
			strncpy((char*)cCommand,"AT+PP\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
			m_bPauseSend = true;
		}
	}
}
void HCBTMusicDlg::PlayMusic()
{
	sBTCommandData*pData =  CBTCommand::Instance()->GetBTCommandData();
	if(pData != NULL)
	{
		//if(pData->BTHFPData.nHFPState == 2 && pData->BTAVRCPData.nA2DPState == 2 && !m_bPlaySend)
		if(pData->BTHFPData.nHFPState == 2 && pData->BTAVRCPData.eAVRCPPlayState !=  eBTMUSICPLAY && !m_bPlaySend)
		{
#ifdef  TESTBTCOMMANDQUEUE
			CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketAVRCPAPlayOrPause,NULL);
#else
			HBYTE cCommand[20] = {0};
			HUINT nCmdlen = strlen("AT+PP\r\n");
			strncpy((char*)cCommand,"AT+PP\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
			m_bPlaySend = true;
		}
	}
}
void HCBTMusicDlg::RequreSource()
{
	if(m_bSourceRealse == true)
	{
		HCBTMusicDlg::SetBTDlgBackGround();
		m_bSourceRealse = false;
		BTDEBUGINFO(L"HCBTMusicDlg::%s",__FUNCTIONW__);
	}
	
}
void HCBTMusicDlg::ReleaseSource()
{
	if(m_bSourceRealse == false)
	{
		EnableUpdateRect(false);
		m_pTxtBTMusicBK->SetBkgndN(NULL);
		//À¶ÑÀÒôÀÖ²Ù×÷±³¾°
		m_pTxtBTMusicHandleBK->SetBkgndN(NULL);
		//ÉÏÒ»Çú
		m_pBtnBTMusicUp->SetBkgndN(NULL);
		m_pBtnBTMusicUp->SetBkgndA(NULL);
		//ÏÂÒ»Çú
		m_pBtnBTMusicDown->SetBkgndN(NULL);
		m_pBtnBTMusicDown->SetBkgndA(NULL);
		EnableUpdateRect(true);
		m_bSourceRealse = true;
		BTDEBUGINFO(L"HCBTMusicDlg::%s",__FUNCTIONW__);
	}
	//ÔÝÍ£
	//m_pTxtBTMusicPlayPause->SetBkgndN(NULL);
	//m_pTxtBTMusicPlayPause->SetBkgndA(NULL);
}
#if TestBTVISION
void HCBTMusicDlg::OnGetBtVision(void* pDlg, void* param)
{
	HCBTMusicDlg* pObj = (HCBTMusicDlg*)pDlg;
	pObj->OnGetBtVision(pObj);
}
void HCBTMusicDlg::OnGetBtVision(void* pDlg)
{
#ifdef  TESTBTCOMMANDQUEUE
	CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketReadSoftVersion,NULL);
#else
	HBYTE cCommand  [20] = {0};
	HUINT nCmdlen = strlen("AT+GVER\r\n");
	strncpy((char*)cCommand,"AT+GVER\r\n",nCmdlen);
	CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
	HBYTE cCommand[50] = {0};
	HUINT nCmdlen = strlen("AT+SLDN=");
	strncpy((char*)cCommand,"AT+SLDN=",nCmdlen);
	strncpy((char*)(cCommand + nCmdlen),(char*)(CBTCommand::Instance()->GetBTCommandData()->BTGeneralData.ZotyeDeviceINFO.LocaLDeviceINFO.szDeviceName),15);
	nCmdlen += 15;
	strncpy((char*)cCommand + nCmdlen,"\r\n",2);
	nCmdlen += 2;
	BTDEBUGINFO(L"ChangeName:Zotye AudioXXXX");
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

void HCBTMusicDlg::UpdateVision()
{
	sBTCommandData* pdata =CBTCommand::Instance()->GetBTCommandData();
	if(m_pBtnVision != NULL && pdata != NULL)
	{
		wchar_t szTemp[50] = {0};
		 MultiByteToWideChar(CP_ACP,0,(char*)pdata->BTGeneralData.LoaclDeviceINFO.szVersion,40,szTemp,50);
		 szTemp[49] = 0;
		 m_pBtnVision->SetText(szTemp);
	}
}

void HCBTMusicDlg::UpdateBtName()
{
	sBTCommandData* pdata =CBTCommand::Instance()->GetBTCommandData();
	if(m_pBtnVision != NULL && pdata != NULL)
	{
		wchar_t szTemp[50] = {0};
		MultiByteToWideChar(CP_ACP,0,(char*)pdata->BTGeneralData.LoaclDeviceINFO.LocaLDeviceINFO.szDeviceName,40,szTemp,50);
		szTemp[49] = 0;
		m_pBtnVision->SetText(szTemp);
	}
}
#endif
void HCBTMusicDlg::MusicMute(bool bMute)
{
	sBTCommandData* pdata =CBTCommand::Instance()->GetBTCommandData();
	bool bA2DPMute = false;
	if(pdata != NULL)
	{
		 bA2DPMute = pdata->BTAVRCPData.bA2DPMute ;
	}
	HBYTE cCommand[50] = {0};
	HUINT nCmdlen = 0;
	BTDEBUGINFO(L"bMute = %d,bA2DPMute = %d\r\n",bMute,bA2DPMute);
	if(bMute != bA2DPMute)
	{	
#ifdef TESTBTCOMMANDQUEUE
	CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketA2DPMute,0);
#else
		nCmdlen = strlen("AT+A2DPMUTE\r\n");
		strncpy((char*)cCommand,"AT+A2DPMUTE\r\n",nCmdlen);
		CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
	}
}

void HCBTMusicDlg::MusicMuteEx(bool bMute)
{
	sBTCommandData* pdata =CBTCommand::Instance()->GetBTCommandData();
	bool bA2DPMute = false;
	if(pdata != NULL)
	{
		bA2DPMute = pdata->BTAVRCPData.bA2DPMute ;
	}
	HBYTE cCommand[50] = {0};
	HUINT nCmdlen = 0;
	BTDEBUGINFO(L"bMute = %d,bA2DPMute = %d\r\n",bMute,bA2DPMute);
	if(bMute != bA2DPMute)
	{	
#ifdef TESTBTCOMMANDQUEUE
		if(bMute)
		{
            CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketA2DPMute,0);
		}
		else
		{
            CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketCancelA2DPMute,0);
		}
#else
		nCmdlen = strlen("AT+A2DPMUTE\r\n");
		strncpy((char*)cCommand,"AT+A2DPMUTE\r\n",nCmdlen);
		CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
	}
}