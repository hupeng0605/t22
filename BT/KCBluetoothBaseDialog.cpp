
#include "KCBluetoothBaseDialog.h"
#include "KHMIBaseHead.h"
#include "KCBTDialogManager.h"
bool HCBluetoothBaseDlg::s_bConnected = NULL;
HUINT HCBluetoothBaseDlg::s_nPreHFPState = 99;
bool HCBluetoothBaseDlg::s_bDailing = false;
HCBluetoothBaseDlg::HCBluetoothBaseDlg()
{
	m_pGrpCtrlBluetoothBottom = NULL;
	m_pBtnBluetooth = NULL;
	m_pBtnAdressBook = NULL;
	m_pBtnBTDialCallRecords = NULL;
	m_pBtnBTMusic = NULL;
	m_pBtnConnectionSetup = NULL;	
	s_pLan = NULL;
};
HCBluetoothBaseDlg::~HCBluetoothBaseDlg()
{
	SAFE_DELETE(m_pBtnConnectionSetup);
	SAFE_DELETE(m_pBtnBTMusic);
	SAFE_DELETE(m_pBtnBTDialCallRecords);
	SAFE_DELETE(m_pBtnAdressBook);
	SAFE_DELETE(m_pBtnBluetooth);
	SAFE_DELETE(m_pGrpCtrlBluetoothBottom);
};

HINT HCBluetoothBaseDlg::OnInit()
{
	SetFocusLineWidth(0);
	HINT nRet = KDialogP::OnInit();
	InitPopupCtrl();
	InitHeadCtrl();
//	 sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
	//SetBTMode(eBTNORMALMODE);
	m_pTxtBottomBk = new HCImageCtrl;
	if(m_pTxtBottomBk != NULL)
	{
		m_pTxtBottomBk->Create(0,412,800,68);
		m_pTxtBottomBk->EnableMsg(false);
		AddChild(m_pTxtBottomBk);
	}
	m_pGrpCtrlBluetoothBottom = new HCGroupCtrl;
	if(m_pGrpCtrlBluetoothBottom != NULL)
	{
		m_pGrpCtrlBluetoothBottom->Create(0,412,800,68);
		AddChild(m_pGrpCtrlBluetoothBottom);
		//À¶ÑÀ²¦ºÅÎÄ±¾
	
		m_pBtnBluetooth = new HCButton;
		if(m_pBtnBluetooth != NULL)
		{
			m_pBtnBluetooth->Create(0,420, 160, 60);
			m_pBtnBluetooth->SetTextStyle(RE_TS_CENTER);
			m_pBtnBluetooth->SetTextPos(80,46);
			m_pBtnBluetooth->SetFontSize(16,16);
			//m_pBtnBluetooth->SetText(_T("À¶ÑÀ²¦ºÅ"));
			m_pBtnBluetooth->SetTextColorN(255,255,255);
		   m_pBtnBluetooth->SetTextColorA(255,255,255);
			//m_pBtnBluetooth->SetTextColorS(255,255,255);
			//m_pBtnBluetooth->EnableMsg(true);
			m_pBtnBluetooth->SetCallBack(OnBTDial,this);
			m_pGrpCtrlBluetoothBottom->AddChild(m_pBtnBluetooth);
		}
		//Í¨Ñ¶Â¼°´Å¥
		m_pBtnAdressBook = new HCButton;
		if(m_pBtnAdressBook != NULL)
		{
			m_pBtnAdressBook->Create(160,420, 160, 60);
			//m_pBtnAdressBook->EnableMsg(true);
			m_pBtnAdressBook->SetTextStyle(RE_TS_CENTER);
			m_pBtnAdressBook->SetTextPos(82,46);
			m_pBtnAdressBook->SetFontSize(16,16);
			///m_pBtnAdressBook->SetText(_T("Í¨Ñ¶Â¼"));
			m_pBtnAdressBook->SetTextColorN(255,255,255);
			m_pBtnAdressBook->SetTextColorA(255,255,255);
			//m_pBtnAdressBook->SetTextColorS(255,255,255);
			m_pBtnAdressBook->SetCallBack(OnAddressBook,this);
			m_pGrpCtrlBluetoothBottom->AddChild(m_pBtnAdressBook);
		}
		
		//Í¨»°¼ÇÂ¼°´Å¥
		m_pBtnBTDialCallRecords = new HCButton;
		if(m_pBtnBTDialCallRecords != NULL)
		{
			m_pBtnBTDialCallRecords->Create(320,422, 160, 60);
			m_pBtnBTDialCallRecords->EnableMsg(true);
			m_pBtnBTDialCallRecords->SetTextStyle(RE_TS_CENTER);
			m_pBtnBTDialCallRecords->SetTextPos(80,46);
			m_pBtnBTDialCallRecords->SetFontSize(16,16);
			//m_pBtnBTDialCallRecords->SetText(_T("Í¨»°¼ÇÂ¼"));
			m_pBtnBTDialCallRecords->SetTextColorN(255,255,255);
			m_pBtnBTDialCallRecords->SetTextColorA(255,255,255);
			//m_pBtnBTDialCallRecords->SetTextColorS(255,255,255);
			m_pBtnBTDialCallRecords->SetCallBack(OnCallRecords,this);
			m_pGrpCtrlBluetoothBottom->AddChild(m_pBtnBTDialCallRecords);
		}
		//À¶ÑÀÒôÀÖ°´Å¥
		m_pBtnBTMusic = new HCButton;
		if(m_pBtnBTMusic != NULL)
		{
			m_pBtnBTMusic->Create(480,422, 160, 60);
			m_pBtnBTMusic->EnableMsg(true);
			m_pBtnBTMusic->SetTextStyle(RE_TS_CENTER);
			m_pBtnBTMusic->SetTextPos(80,46);
			m_pBtnBTMusic->SetFontSize(16,16);
			//m_pBtnBTMusic->SetText(_T("À¶ÑÀÒôÀÖ"));
			m_pBtnBTMusic->SetTextColorN(255,255,255);
			m_pBtnBTMusic->SetTextColorA(255,255,255);
			//m_pBtnBTMusic->SetTextColorS(255,255,255);
			m_pBtnBTMusic->SetCallBack(OnBTMusic,this);
			m_pGrpCtrlBluetoothBottom->AddChild(m_pBtnBTMusic);
		}

		//Á¬½ÓÉèÖÃ°´Å¥
		m_pBtnConnectionSetup = new HCButton;
		if(m_pBtnConnectionSetup != NULL)
		{
			m_pBtnConnectionSetup->Create(640,420, 160, 60);
			m_pBtnConnectionSetup->SetTextStyle(RE_TS_CENTER);
			m_pBtnConnectionSetup->SetTextPos(80,46);
			m_pBtnConnectionSetup->SetFontSize(16,16);
			//m_pBtnConnectionSetup->SetText(_T("Á¬½ÓÉèÖÃ"));
			m_pBtnConnectionSetup->SetTextColorN(255,255,255);
			m_pBtnConnectionSetup->SetTextColorA(255,255,255);
			//m_pBtnConnectionSetup->SetTextColorS(255,255,255);
			m_pBtnConnectionSetup->SetCallBack(OnConnectionSetting,this);
			m_pGrpCtrlBluetoothBottom->AddChild(m_pBtnConnectionSetup);
			m_pGrpCtrlBluetoothBottom->SetShow(true);
		}
		//HCBluetoothBaseDlg::SetBTDlgBackGround();
	}
   // UpdataBTBottomState();
	//HCBluetoothBaseDlg::ChangeLangue(0);
	//s_bDailing = false;
	
	m_bSourceRealse = true;
	SETUPSETTING LSetting;
	KCLastMemory::GetInstance()->GetSetupMemory(LSetting);
	BTDEBUGINFO(L"HCBluetoothBaseDlg::LSetting.cLang = %d",LSetting.cLang);
	switch (LSetting.cLang)
	{
	case 0:
		{
			HCBluetoothBaseDlg::ChangeLangue(0);
		}
		break;
	case 1:
		{
			HCBluetoothBaseDlg::ChangeLangue(1);
		}
		break;
	default:
		break;
	}
	return nRet;
};

void HCBluetoothBaseDlg::ChangeTheme( HBYTE uType )
{
	// ÉèÖÃ±³¾°
	btSource *p = btSource::Instance(); 
	if(p != NULL)
	{
		
	    p->ChangeBKGndSource(GetHMIPath(_T("")).c_str());
		sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
		if(pSource != NULL && pSource->m_pbtBkgnd != NULL)
		{
			SetBackGround(pSource->m_pbtBkgnd);
		}
	}
	m_uThemeMode =  GetCurThemeMode();
   //KCLastMemory::GetInstance()->GetSetupMemory(g_SetupSetting);
 //SetBackGround(GetHMIPath((HCHAR*)&g_SetupSetting.szBkgndPath));
}


void HCBluetoothBaseDlg::SetBTDlgBackGround()
{
	sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
    //SetBackGround(GetHMIPath(_T("Share\\Share_Bak.hfp")));
	//KCLastMemory::GetInstance()->GetSetupMemory(g_SetupSetting);
	//SetBackGround(GetHMIPath((HCHAR*)&g_SetupSetting.szBkgndPath));
	if(pSource != NULL)
	{
		EnableUpdateRect(false);
		SetBackGround(pSource->m_pbtBkgnd);
		//m_pGrpCtrlBluetoothBottom->SetBackGround(pSource->m_pbtBottom);
		m_pTxtBottomBk->SetBkgndN(pSource->m_pbtBottom);
		m_pTxtBottomBk->SetOpacity(8);
		//µ×À¸±³¾°
		//m_pTxtBootmBK->SetBkgndN(GetHMIPath(_T("Share\\Share_Frame_Bottom 02.hfp")));
		//À¶ÑÀ²¦ºÅ±³¾°
		m_pBtnBluetooth->SetBkgndN(pSource->m_pbtBaseDailN);
		//m_pBtnBluetooth->SetBkgndA(pSource->m_pbtBaseDailA);
		//m_pBtnBluetooth->SetBkgndF(pSource->m_pbtBaseDailA);
		//Í¨Ñ¶Â¼±³¾°
		m_pBtnAdressBook->SetBkgndN(pSource->m_pbtBaseAddressbookN);
		//m_pBtnAdressBook->SetBkgndA(pSource->m_pbtBaseAddressbookA);
		//m_pBtnAdressBook->SetBkgndF(pSource->m_pbtBaseAddressbookA);
		//Í¨»°¼ÇÂ¼±³¾°
		m_pBtnBTDialCallRecords->SetBkgndN(pSource->m_pbtBaseCallRecordsN);
		//m_pBtnBTDialCallRecords->SetBkgndA(pSource->m_pbtBaseCallRecordsA);
		//m_pBtnBTDialCallRecords->SetBkgndF(pSource->m_pbtBaseCallRecordsA);
		//À¶ÑÀÒôÀÖ±³¾°
		m_pBtnBTMusic->SetBkgndN(pSource->m_pbtBaseMusicN);
		//m_pBtnBTMusic->SetBkgndA(pSource->m_pbtBaseMusicA);
		//m_pBtnBTMusic->SetBkgndF(pSource->m_pbtBaseMusicA);
		//Á¬½ÓÉèÖÃ±³¾°
		m_pBtnConnectionSetup->SetBkgndN(pSource->m_pbtBaseConnectStepN);
		//m_pBtnConnectionSetup->SetBkgndA(pSource->m_pbtBaseConnectStepA);
		//m_pBtnConnectionSetup->SetBkgndF(pSource->m_pbtBaseConnectStepA);
		EnableUpdateRect(true);
	}
}

void HCBluetoothBaseDlg::OnAddressBook(void *pDlg,void *pa)
{
	HCBluetoothBaseDlg * pObj =(HCBluetoothBaseDlg*)pDlg;
	pObj->OnAddressBook(pObj);
}
void HCBluetoothBaseDlg::OnAddressBook(void *pDlg)
{
	KCBTDialogManager* p = KCBTDialogManager::Instance();
	if(p != NULL)
	{
		p->ShowDlg(eDIALOGT_BTADDRESSBOOK);
	}	
}
void HCBluetoothBaseDlg::OnBTDial(void *pDlg,void *pa)
{
	HCBluetoothBaseDlg * pObj =(HCBluetoothBaseDlg*)pDlg;
	if(pObj != NULL)
	{
		pObj->OnBTDial(pObj);
	}
}
void HCBluetoothBaseDlg::OnBTDial(void *pDlg)
{
	KCBTDialogManager* p = KCBTDialogManager::Instance();
	if(p != NULL)
	{
		p->ShowDlg(eDIALOGT_BTDIAL);
	}	
}
void HCBluetoothBaseDlg::OnCallRecords(void *pDlg,void *pa)
{
	HCBluetoothBaseDlg * pObj =(HCBluetoothBaseDlg*)pDlg;
	if(pObj != NULL)
	{
		pObj->OnCallRecords(pObj);
	}
}
void HCBluetoothBaseDlg::OnCallRecords(void *pDlg)
{
	//HBYTE cCommand  [20] = {0};
	//HUINT nCmdlen = strlen("AT+PBSTAT\r\n");
	//	strncpy((char*)cCommand,"AT+PBSTAT\r\n",nCmdlen);
	//	CBTCommand::Instance()->SendData(cCommand,nCmdlen);
	KCBTDialogManager* p = KCBTDialogManager::Instance();
	if(p != NULL)
	{
		p->ShowDlg(eDIALOGT_BTCALLRECORDS);
	}	
	//KCBTDialogManager::Instance()->ShowDlg(eDIALOGT_BTCALLRECORDS);
}
void HCBluetoothBaseDlg::OnBTMusic(void *pDlg,void *pa)
{
	HCBluetoothBaseDlg * pObj =(HCBluetoothBaseDlg*)pDlg;
	if(pObj != NULL)
	{
		pObj->OnBTMusic(pObj);
	}
}
void HCBluetoothBaseDlg::OnBTMusic(void *pDlg)
{
	KCBTDialogManager* p = KCBTDialogManager::Instance();
	if(p != NULL)
	{
		eDIALOGTYPE eType = p->GetCurrentDlgType();
		if(eType != eDIALOGT_BTMUSIC)
		{
			::PostMessage(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_BT_ENTER_MUSICDLG,NULL,NULL);
			 p->ShowDlg(eDIALOGT_BTMUSIC);
		}	
	}	
  
}
void HCBluetoothBaseDlg::SendPP()
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
void HCBluetoothBaseDlg::PlayMusicEx()
{
	sBTCommandData*pData =  CBTCommand::Instance()->GetBTCommandData();
	if(pData != NULL)
	{
		printf("++++++++++Send PP ++++++++++++nA2DPState = %d\r\n",pData->BTAVRCPData.nA2DPState);
		if(pData->BTHFPData.nHFPState == 2 && pData->BTAVRCPData.nA2DPState != 3)
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
void HCBluetoothBaseDlg::OnConnectionSetting(void *pDlg,void *pa)
{
	HCBluetoothBaseDlg * pObj =(HCBluetoothBaseDlg*)pDlg;
	if(pObj != NULL)
	{
		pObj->OnConnectionSetting(pObj);
	}	
}
void HCBluetoothBaseDlg::OnConnectionSetting(void *pDlg)
{
	/*if(m_eBTMode == eBTNORMALMODE)
	{
		SetBTMode(eBTPAIRMODE);
	}
	else
	{
		SetBTMode(eBTNORMALMODE);
	}*/
	KCBTDialogManager* p = KCBTDialogManager::Instance();
	if(p != NULL)
	{
	    eDIALOGTYPE eType = 	p->GetCurrentDlgType();
		bool bHMIShow= KCBTDialogManager::Instance()->IsBTHMIDlgShow();
		if(!bHMIShow && eType != eDIALOGT_BTCONNECTSETTING)
		{
			p->ShowDlg(eDIALOGT_BTCONNECTSETTING);
		}
	}	
	//HCBluetoothBaseDlg * pObj =(HCBluetoothBaseDlg*)pDlg;
	//KCBTDialogManager::Instance()->ShowDlg(eDIALOGT_BTCONNECTSETTING);
}
void HCBluetoothBaseDlg::SetBTABBK()
{
	sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
	if(pSource != NULL)
	{
		m_pBtnAdressBook->SetBkgndN(pSource->m_pbtBaseAddressbookA);
	}
}
void HCBluetoothBaseDlg::SetBTCRBK()
{
	sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
	if(pSource != NULL)
	{
	     m_pBtnBTDialCallRecords->SetBkgndN(pSource->m_pbtBaseCallRecordsA);
	}
}
void HCBluetoothBaseDlg::SetBTCSBK()
{
	sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
	if(pSource != NULL)
	{
		m_pBtnConnectionSetup->SetBkgndN(pSource->m_pbtBaseConnectStepA);
	}
}
void HCBluetoothBaseDlg::SetBTDLBK()
{
	sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
	if(pSource != NULL)
	{
		m_pBtnBluetooth->SetBkgndN(pSource->m_pbtBaseDailA);
	}
}
void HCBluetoothBaseDlg::SetBTMSCBK()
{
	sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
	if(pSource != NULL)
	{
		m_pBtnBTMusic->SetBkgndN(pSource->m_pbtBaseMusicA);
	}
}
void HCBluetoothBaseDlg::SetPreHFPState(HUINT nState)
{
	if(nState >= 0)
	{
		s_nPreHFPState = nState;
	}
}
HUINT HCBluetoothBaseDlg::GetPreHFPState(void )
{
  return s_nPreHFPState;
}
void HCBluetoothBaseDlg::SetBTMode(eBTMODE eMode)
{
	if(eMode == eBTPAIRMODE)
	{
		//HBYTE cCommand  [20] = {0};
		//HUINT nCmdlen = strlen("AT+EPRM=0\r\n");
		//strncpy((char*)cCommand,"AT+EPRM=0\r\n",nCmdlen);
		//CBTCommand::Instance()->SendData(cCommand,nCmdlen);	
	}
	else
	{
		//HBYTE cCommand  [20] = {0};
		//HUINT nCmdlen = strlen("AT+EPRM=1\r\n");
		//strncpy((char*)cCommand,"AT+EPRM=1\r\n",nCmdlen);
		//CBTCommand::Instance()->SendData(cCommand,nCmdlen);
	}
	m_eBTMode = eMode;
}
bool HCBluetoothBaseDlg::SetBTConected(bool bConnect)
{
	s_bConnected = bConnect;
	return s_bConnected;
}
bool HCBluetoothBaseDlg::GetBTConnectstate(void)
{
	return s_bConnected;
}
void HCBluetoothBaseDlg::SetDlgBkGnd()
{
	sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
	if(pSource != NULL && pSource->m_pbtBkgnd != NULL)
	{
		SetBackGround(pSource->m_pbtBkgnd);
	}
   m_uThemeMode =  GetCurThemeMode();
}
 void HCBluetoothBaseDlg::UpdataBTBottomState(HINT nState)
 {
	  sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
	if(pSource != NULL)
	{
        switch(nState)
		{
			case  0:
			case  1:
			case  2:
			//case  7:
			{
				m_pBtnAdressBook->SetTextColorN(255,255,255);
				m_pBtnAdressBook->SetBkgndN(pSource->m_pbtBaseAddressbookN);
				m_pBtnAdressBook->EnableMsg(true);
				m_pBtnBTDialCallRecords->SetBkgndN(pSource->m_pbtBaseCallRecordsN);
				m_pBtnBTDialCallRecords->SetTextColorN(255,255,255);
				m_pBtnBTDialCallRecords->EnableMsg(true);
				m_pBtnConnectionSetup->SetBkgndN(pSource->m_pbtBaseConnectStepN);
				m_pBtnConnectionSetup->SetTextColorN(255,255,255);
				m_pBtnConnectionSetup->EnableMsg(true);
				m_pBtnBluetooth->SetBkgndN(pSource->m_pbtBaseDailA);
				m_pBtnBluetooth->SetTextColorN(255,255,255);
				m_pBtnBluetooth->EnableMsg(true);
				m_pBtnBTMusic->SetBkgndN(pSource->m_pbtBaseMusicN);
				m_pBtnBTMusic->SetTextColorN(255,255,255);
				m_pBtnBTMusic->EnableMsg(true);
			}
			break;
			case 3:
			case 4:
			case 5:
			case 6:
			{
				m_pBtnAdressBook->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Booklist_D.hfp")));
				m_pBtnAdressBook->SetTextColorN(127,127,127);
				m_pBtnAdressBook->EnableMsg(false);
				m_pBtnBTDialCallRecords->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Records_D.hfp")));
				m_pBtnBTDialCallRecords->SetTextColorN(127,127,127);
				m_pBtnBTDialCallRecords->EnableMsg(false);
				m_pBtnConnectionSetup->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Connection_D.hfp")));
				m_pBtnConnectionSetup->SetTextColorN(127,127,127);
				m_pBtnConnectionSetup->EnableMsg(false);
				m_pBtnBluetooth->SetBkgndN(pSource->m_pbtBaseDailA);
				m_pBtnBluetooth->SetTextColorN(255,255,255);
				m_pBtnBluetooth->EnableMsg(true);
				m_pBtnBTMusic->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Music_D.hfp")));
				m_pBtnBTMusic->SetTextColorN(127,127,127);
				m_pBtnBTMusic->EnableMsg(false);
			}
			break;
		}
    }
 }

 void HCBluetoothBaseDlg::UpdataBTBottomState(void)
 {
	 sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
	 if(s_bConnected == true && pSource != NULL)
	 {
		 m_pBtnAdressBook->SetTextColorN(255,255,255);
		 m_pBtnAdressBook->SetBkgndN(pSource->m_pbtBaseAddressbookN);
		 m_pBtnAdressBook->EnableMsg(true);
		 m_pBtnBTDialCallRecords->SetBkgndN(pSource->m_pbtBaseCallRecordsN);
		 m_pBtnBTDialCallRecords->SetTextColorN(255,255,255);
		 m_pBtnBTDialCallRecords->EnableMsg(true);
		 m_pBtnConnectionSetup->SetBkgndN(pSource->m_pbtBaseConnectStepA);
		 m_pBtnConnectionSetup->SetTextColorN(255,255,255);
		 m_pBtnConnectionSetup->EnableMsg(true);
		 m_pBtnBluetooth->SetBkgndN(pSource->m_pbtBaseDailN);
		 m_pBtnBluetooth->SetTextColorN(255,255,255);
		 m_pBtnBluetooth->EnableMsg(true);
		 m_pBtnBTMusic->SetBkgndN(pSource->m_pbtBaseMusicN);
		 m_pBtnBTMusic->SetTextColorN(255,255,255);
		 m_pBtnBTMusic->EnableMsg(true);
	 }
	 else
	 {
		 m_pBtnAdressBook->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Booklist_D.hfp")));
		 m_pBtnAdressBook->SetTextColorN(127,127,127);
		 m_pBtnAdressBook->EnableMsg(false);
		 m_pBtnBTDialCallRecords->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Records_D.hfp")));
		 m_pBtnBTDialCallRecords->SetTextColorN(127,127,127);
		 m_pBtnBTDialCallRecords->EnableMsg(false);
		 m_pBtnConnectionSetup->SetBkgndN(pSource->m_pbtBaseConnectStepA);
		 m_pBtnConnectionSetup->SetTextColorN(255,255,255);
		 m_pBtnConnectionSetup->EnableMsg(true);
		 m_pBtnBluetooth->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Dial_D.hfp")));
		 m_pBtnBluetooth->SetTextColorN(127,127,127);
		 m_pBtnBluetooth->EnableMsg(false);
		 m_pBtnBTMusic->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Music_D.hfp")));
		 m_pBtnBTMusic->SetTextColorN(127,127,127);
		 m_pBtnBTMusic->EnableMsg(false);
	 }
 }
 void HCBluetoothBaseDlg::OnBtnHome(void* pParam)
 {
	/* sBTCommandData* pData = CBTCommand::Instance()->GetBTCommandData();
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
	 }*/
	 sBTCommandData* pData = CBTCommand::Instance()->GetBTCommandData();
	 HINT nHFPState = 0;
	 if(pData != NULL)
	 {
		 nHFPState = pData->BTHFPData.nHFPState;
	 }
	 if(nHFPState != 3 && nHFPState != 4 && nHFPState != 5 && nHFPState != 6)
	 {
		KDialogP::OnBtnHome(pParam);
	 }	 
 }
 void HCBluetoothBaseDlg::OnBtnBackPrevious(void* pParam)
 {
	 DWORD nCostTime = GetTickCount();
	 sBTCommandData* pData = CBTCommand::Instance()->GetBTCommandData();
	  HINT nHFPState = 0;
	 if(pData != NULL)
	 {
//		 if(pData->BTAVRCPData.nA2DPState == 3)
//		 {
//#ifdef  TESTBTCOMMANDQUEUE
//			 CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketAVRCPAPlayOrPause,NULL);
//#else
//			 HBYTE cCommand  [20] = {0};
//			 HUINT nCmdlen = strlen("AT+PP\r\n");
//			 strncpy((char*)cCommand,"AT+PP\r\n",nCmdlen);
//			 CBTCommand::Instance()->SendData(cCommand,nCmdlen);
//#endif
//		 }
		 nHFPState = pData->BTHFPData.nHFPState;
	 }
	 HWND hServerWnd = CEIPC_GetHWND(IPC_ID_MANAGE);
	 eDIALOGTYPE eCurrentDlgType = KCBTDialogManager::Instance()->GetCurrentDlgType();
	 if(nHFPState != 3 && nHFPState != 4 && nHFPState != 5 && nHFPState != 6)
	 {
		 if(NULL != hServerWnd)
		 {
			 //if(eCurrentDlgType == eDIALOGT_BTCONNECTSETTING)
			// {
				 ::PostMessage(hServerWnd, UWM_TOPBAR_HOME, 0, 0);
			// }
			// else
			// {
				// OnConnectionSetting(NULL);
			 //}
		 }
	 }	
	 nCostTime = GetTickCount() - nCostTime;
	 BTDEBUGINFO(L"nCostTime = %d",nCostTime);
 }
 void HCBluetoothBaseDlg::ChangeLangue(HINT nType)
 {
	SetLangue(nType);
	if(s_pLan != NULL)
	{
		m_pBtnBluetooth->SetText(s_pLan[0]);
		m_pBtnAdressBook->SetText(s_pLan[1]);
		m_pBtnBTDialCallRecords->SetText(s_pLan[2]);
		m_pBtnBTMusic->SetText(s_pLan[3]);
		m_pBtnConnectionSetup->SetText(s_pLan[4]);
	}
 }
 void HCBluetoothBaseDlg::SetLangue(HINT nType)
 {
	sLangue* pCh = btSource::Instance()->GetBTChLange();
	sLangue* pEn = btSource::Instance()->GetBTEnLange();
	switch (nType)
	{
		case 0:
		{
			if(pCh != NULL)
			{
				s_pLan = pCh->szContent;
			}
		}
		break;
		case 1:
		{
			if(pEn != NULL)
			{
				s_pLan = pEn->szContent;
			}
		}
		break;
		default:
		{

		}
		break;
	}
 }
 void HCBluetoothBaseDlg::RequreSource()
 {
	
 }
void HCBluetoothBaseDlg::ReleaseSource()
 {

 }
bool HCBluetoothBaseDlg::IsDailing()
 {
	return s_bDailing;
 }
void HCBluetoothBaseDlg::SetDailingState(bool bDail)
{
	s_bDailing = bDail;
}
void HCBluetoothBaseDlg::ConnectA2DP(int nConnect)
{
	sBTCommandData *pData = CBTCommand::Instance()->GetBTCommandData();
	HINT nHFPState,nA2DPState;
	nA2DPState = pData->BTAVRCPData.nA2DPState;
	nHFPState = pData->BTHFPData.nHFPState;
	if(nConnect == 1)
	{
		if((nA2DPState < 2) && (nHFPState == 2))
		{
#ifdef  TESTBTCOMMANDQUEUE
			CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketA2DPConnectAVRCP,NULL);
#else 
			HBYTE cCommand[30] ={0};
			HINT nCmdlen = 0;	
			nCmdlen = strlen("AT+A2DPCONN\r\n");
			strncpy((char*)cCommand,"AT+A2DPCONN\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
		}
	}
	else if(nConnect == 0 && nA2DPState > 0)
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
}

void HCBluetoothBaseDlg::StopMusicEx()
{
	sBTCommandData *pData = CBTCommand::Instance()->GetBTCommandData();
	if(pData != NULL)
	{
		if(pData->BTHFPData.nHFPState == 2 || pData->BTHFPData.nHFPState == 7)
		{
#ifdef  TESTBTCOMMANDQUEUE
			CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketAVRCPAStopPlay,NULL);
#else
			HBYTE cCommand  [20] = {0};
			HUINT nCmdlen = strlen("AT+STOP\r\n");
			strncpy((char*)cCommand,"AT+STOP\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
		}
	}
}