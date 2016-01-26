#include "KCBTDialogManager.h"
#include "khmibasehead.h "
KCBTDialogManager* KCBTDialogManager::s_pBTdialogManger = NULL;
KCBTDialogManager* KCBTDialogManager::Instance()
{
	if(NULL == s_pBTdialogManger)
	{
		s_pBTdialogManger = new KCBTDialogManager;
		if(NULL == s_pBTdialogManger)
		{
			wprintf(_T("KCBTDialogManager::Instance() failed \n"));
			//exit(1);
		}
	}
	return s_pBTdialogManger;
}
void KCBTDialogManager::DeleteInstance()
{
	if(s_pBTdialogManger != NULL)
	{
		SAFE_DELETE(s_pBTdialogManger);
	}
}
 KCBTDialogManager::KCBTDialogManager()
{
	m_eCurrentDlgType = eDIALOGT_UNKNOW;
	for(HINT i = 0;i < eMAXBTDIALOGNUM;i++)
	{
		m_pBTDialog[i] = NULL;
	}
	m_ePreDlgType = eDIALOGT_UNKNOW;
	m_pBTHMIDlg = NULL;
	m_bBTHMIDlg = false;
	//m_pBTCurrentDlg = NULL;
}
KCBTDialogManager::~KCBTDialogManager()
{
	HCBluetoothBaseDlg *pCurrent = NULL;
	pCurrent = GetCurrentDlg();
	for(int i = 0;i < eMAXBTDIALOGNUM;i ++)
	{
		if(pCurrent != m_pBTDialog[i] && m_pBTDialog[i] != NULL)
		{
			SAFE_DELETE(m_pBTDialog[i]);
		}
	}
	SAFE_DELETE(m_pBTHMIDlg);
	if(pCurrent != NULL)
	{
		SAFE_DELETE(pCurrent);
	}
}

void KCBTDialogManager::CreateAllBTDlg()
{
	CreateBTDlg(eDIALOGT_BTDIAL);
	CreateBTDlg(eDIALOGT_BTADDRESSBOOK);
	CreateBTDlg(eDIALOGT_BTCALLRECORDS);
	CreateBTDlg(eDIALOGT_BTMUSIC);
	CreateBTDlg(eDIALOGT_BTCONNECTSETTING);
	CreateBTHMIDlg();
}
eDIALOGTYPE KCBTDialogManager::GetCurrentDlgType(void)
{
	return m_eCurrentDlgType;
}
void KCBTDialogManager::ChangeThemeForAllDlg()
{
	IReSurface* pBkSource = NULL;
	if(m_pBTDialog[eDIALOGT_BTDIAL] != NULL)
	{
		 pBkSource =  m_pBTDialog[eDIALOGT_BTDIAL]->GetBackGround(); 
	     m_pBTDialog[eDIALOGT_BTDIAL]->ChangeTheme(0);
	}
	if(m_pBTDialog[eDIALOGT_BTADDRESSBOOK] != NULL)
	{
		m_pBTDialog[eDIALOGT_BTADDRESSBOOK]->SetDlgBkGnd();
	}
	if(m_pBTDialog[eDIALOGT_BTCALLRECORDS] != NULL)
	{
		m_pBTDialog[eDIALOGT_BTCALLRECORDS]->SetDlgBkGnd();
	}
	if(m_pBTDialog[eDIALOGT_BTMUSIC] != NULL)
	{
		m_pBTDialog[eDIALOGT_BTMUSIC]->SetDlgBkGnd();
	}
	if(m_pBTDialog[eDIALOGT_BTCONNECTSETTING] != NULL)
	{
		m_pBTDialog[eDIALOGT_BTCONNECTSETTING]->SetDlgBkGnd();
	}
	SAFE_DELETE(pBkSource);
}
void KCBTDialogManager::ChangeLangeForAllDlg(HINT nType)
{
	for(HINT i = 0;i < eMAXBTDIALOGNUM;i++)
	{
		if(m_pBTDialog[i] != NULL)
		{
			m_pBTDialog[i]->ChangeLangue(nType);
		}
	}
	if(m_pBTHMIDlg != NULL)
	{
		((CBTHmiDlg*)m_pBTHMIDlg)->ChangeLanguage(nType);
	}
};
HCBluetoothBaseDlg* KCBTDialogManager::CreateBTDlg(eDIALOGTYPE InterfaceType)
{
	HCBluetoothBaseDlg* pDialog = NULL;
	switch(InterfaceType)
	{
	case eDIALOGT_BTDIAL:
		{
			pDialog = new HCBTDialDlg;
		
		}
		break;
	case eDIALOGT_BTADDRESSBOOK:
		{
			pDialog = new HCBTAddressBookDlg;

		}
		break;
	case eDIALOGT_BTCALLRECORDS:
		{
			pDialog = new HCBTCallRecordsDlg;
		}
		break;
	case eDIALOGT_BTMUSIC:
		{
			pDialog = new HCBTMusicDlg;
		}
		break;
	case eDIALOGT_BTCONNECTSETTING: 
		{
			pDialog = new HCBTConnectionssettingDlg;

		}
		break;

	case eDIALOGT_UNKNOW: 
		{
			
		}
		break;	
	}
	if( NULL != pDialog)
	{
		m_pBTDialog[InterfaceType] = pDialog;
		pDialog->Create(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetScreen());	
	}
	else
	{
		wprintf(_T("KCBTDialogManager::CreateBTDlg failed\n"));
	}
		
	return pDialog;
}
HDialogBase* KCBTDialogManager::CreateBTHMIDlg()
{
    if(m_pBTHMIDlg == NULL)
	{
		m_pBTHMIDlg = new CBTHmiDlg;
        if(m_pBTHMIDlg == NULL)
		{
			wprintf(_T("KCBTDialogManager::CreateBTHMIDlg failed\n"));
		}
		else
		{
			m_pBTHMIDlg->Create(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetScreen());
			 //m_pBTDialog[eDIALOGT_BTHMI] = m_pBTHMIDlg;
		}
	}
	return m_pBTHMIDlg;
}
/*
void KCBTDialogManager::SetShow(eDIALOGTYPE InterfaceType)
{
	
	switch (InterfaceType)
	{
		case BTDialInterface:
			{
				m_pBTDialog[1]->SetShow(false);
				m_pBTDialog[2]->SetShow(false);
				m_pBTDialog[3]->SetShow(false);
				m_pBTDialog[4]->SetShow(false);
				m_pBTDialog[0]->SetShow(true);
			}
			break;
		case AddressBookInterface:
			{
				m_pBTDialog[0]->SetShow(false);
				m_pBTDialog[2]->SetShow(false);
				m_pBTDialog[3]->SetShow(false);
				m_pBTDialog[4]->SetShow(false);
				m_pBTDialog[1]->SetShow(true);
			}
			break;
		case CallRecordsInterface:
			{
				m_pBTDialog[1]->SetShow(false);
				m_pBTDialog[0]->SetShow(false);
				m_pBTDialog[3]->SetShow(false);
				m_pBTDialog[4]->SetShow(false);
				m_pBTDialog[2]->SetShow(true);
			}
			break;
		case BTMusicInterface:
			{
				m_pBTDialog[1]->SetShow(false);
				m_pBTDialog[2]->SetShow(false);
				m_pBTDialog[0]->SetShow(false);
				m_pBTDialog[4]->SetShow(false);
				m_pBTDialog[3]->SetShow(true);
			}
			break;
		case ConnectionSettingsInterface:
			{
				m_pBTDialog[1]->SetShow(false);
				m_pBTDialog[2]->SetShow(false);
				m_pBTDialog[3]->SetShow(false);
				m_pBTDialog[0]->SetShow(false);
				m_pBTDialog[4]->SetShow(true);
			}
			break;
		case eDIALOGT_UNKNOW:
			{
				
			}
			break;
	

	}
}
*/
HCBluetoothBaseDlg* KCBTDialogManager::GetDlg( eDIALOGTYPE eDialogType )
{

	return m_pBTDialog[eDialogType];
}
eDIALOGTYPE KCBTDialogManager::GetDlgID( HCBluetoothBaseDlg* pDialog )
{
	if(pDialog == NULL)
		return eDIALOGT_UNKNOW;
	for(HINT i = 0;i < sizeof(m_pBTDialog)/sizeof(m_pBTDialog[0]);i++)
	{
		if (pDialog == m_pBTDialog[i])
		{
			return (eDIALOGTYPE)i;
		}
	}
	return eDIALOGT_UNKNOW;
}

HCBluetoothBaseDlg* KCBTDialogManager::ShowDlg(eDIALOGTYPE eDialogType)
{

	if (eDialogType < eDIALOGT_BTDIAL || eDialogType > eDIALOGT_BTHMI/*eDIALOGT_BTCONNECTSETTING*/)
	{
		return NULL;
	}
	eDIALOGTYPE ePreType = eDIALOGT_UNKNOW;
	ePreType= GetCurrentDlgType();
	//if(m_ePreDlgType != ePreType || m_ePreDlgType == eDIALOGT_UNKNOW)
	//{
		m_ePreDlgType = ePreType;
		if(eDialogType == eDIALOGT_BTHMI)
		{
			//CreateBTHMIDlg();
			m_eCurrentDlgType = eDialogType;
			ShowBTHMIDlg();
			return NULL;
		}
		
		if (NULL == GetDlg(eDialogType))
		{
			m_pBTDialog[eDialogType] = CreateBTDlg(eDialogType);
		}
		if(m_pBTDialog[eDialogType] != NULL)
		{

			HideBTHMIdlg();
			m_pBTDialog[eDialogType]->RequreSource();
			m_pBTDialog[eDialogType]->SetTransType(0);
			m_pBTDialog[eDialogType]->ClearUpdateRect();
			m_pBTDialog[eDialogType]->ShowWindow();
			m_pBTDialog[eDialogType]->UpdateWindow();
			KCStatusIcon::GetInstance()->SetBtDialog(eDialogType +1);
			BTDEBUGINFO(L"SetBtDialog:eType = %d",(eDialogType +1));
		}
	//}
	m_eCurrentDlgType = eDialogType;
	ReleaseUncurrentSource();
	BTDEBUGINFO(L"%s :m_eCurrentDlgType = %d,m_ePreDlgType = %d",__FUNCTIONW__,m_eCurrentDlgType,m_ePreDlgType);
	return m_pBTDialog[eDialogType];
}
/*
HUINT KCBTDialogManager::SendData(const HBYTE *pdata,HUINT nDataLen)
{
	HUINT nSendDataLen = 0;
	return nSendDataLen;
}
*/
void KCBTDialogManager::JumpToDlg(eDIALOGTYPE eDialogType)
{
	if (eDialogType < eDIALOGT_BTDIAL || eDialogType > eDIALOGT_BTHMI/*eDIALOGT_BTCONNECTSETTING*/)
	{
		return;
	}
	eDIALOGTYPE ePreType = eDIALOGT_UNKNOW;
	ePreType= GetCurrentDlgType();
	//KCStatusIcon::GetInstance()->SetBtDialog(eDialogType);
	if(ePreType != eDIALOGT_BTDIAL)
	{
		m_ePreDlgType = ePreType;
	}
	if(eDialogType == eDIALOGT_BTHMI)
	{
		m_eCurrentDlgType = eDialogType;
		ShowBTHMIDlg();
		return;
	}
	if (NULL == GetDlg(eDialogType))
	{
		m_pBTDialog[eDialogType] = CreateBTDlg(eDialogType);
	}
	if(m_pBTDialog[eDialogType] != NULL)
	{
		HideBTHMIdlg();
		m_pBTDialog[eDialogType]->RequreSource();
		m_pBTDialog[eDialogType]->SetTransType(0);
		m_pBTDialog[eDialogType]->ClearUpdateRect();
		m_pBTDialog[eDialogType]->ShowWindow();
		m_pBTDialog[eDialogType]->UpdateWindow();
		KCStatusIcon::GetInstance()->SetBtDialog(eDialogType + 1);
		BTDEBUGINFO(L"SetBtDialog:eType = %d",(eDialogType + 1));
	}
	m_eCurrentDlgType = eDialogType;
	ReleaseUncurrentSource();
	BTDEBUGINFO(L"%s :m_eCurrentDlgType = %d,m_ePreDlgType = %d",__FUNCTIONW__,m_eCurrentDlgType,m_ePreDlgType);
}
HCBluetoothBaseDlg* KCBTDialogManager::ShowPreDlg()
{
		return ShowDlg(m_ePreDlgType);
}
HDialogBase* KCBTDialogManager::ShowBTHMIDlg()
{
	if(m_pBTHMIDlg == NULL)
	{
	    CreateBTHMIDlg();
	}
	if(m_pBTHMIDlg != NULL)
	{
		((CBTHmiDlg*)m_pBTHMIDlg)->RequreSource();
		//((CBTHmiDlg*)m_pBTHMIDlg)->ShowHMIVidio();
		//((CBTHmiDlg*)m_pBTHMIDlg)->OpenHMI();
		m_pBTHMIDlg->SetTransType(0);
		m_pBTHMIDlg->ClearUpdateRect();
		m_pBTHMIDlg->ShowWindow();
		m_pBTHMIDlg->UpdateWindow();
		KCStatusIcon::GetInstance()->SetBtDialog( eDIALOGT_BTHMI + 1);
		BTDEBUGINFO(L"SetBtDialog:eType = %d",(eDIALOGT_BTHMI + 1));
		m_bBTHMIDlg = true;
	}
	ReleaseUncurrentSource();
	sBTCommandData *pBtData= CBTCommand::Instance()->GetBTCommandData();
	if(pBtData != NULL)
	{
		if(pBtData->BTHFPData.nHFPState == 2 && pBtData->BTSPPData.nSPPState == 0)
		{
			 HBYTE cCommand[20] ={0};
			 HINT nCmdlen = 0;	
			nCmdlen = strlen("AT+SPPCONN\r\n");
			strncpy((char*)cCommand,"AT+SPPCONN\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		}
		HINT nHFPState,nA2DPState;
		nA2DPState = pBtData->BTAVRCPData.nA2DPState;
		nHFPState = pBtData->BTHFPData.nHFPState;
#ifdef  TESTBTCOMMANDQUEUE
		//CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketA2DPDisconnectA2DPAndAVRCP,NULL);
#else 
		HBYTE cCommand[30] ={0};
		HINT nCmdlen = 0;	
		nCmdlen = strlen("AT+A2DPDISC\r\n");
		strncpy((char*)cCommand,"AT+A2DPDISC\r\n",nCmdlen);
		CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
	}
	BTDEBUGINFO(L"%s :m_eCurrentDlgType = %d,m_ePreDlgType = %d",__FUNCTIONW__,m_eCurrentDlgType,m_ePreDlgType);
	return m_pBTHMIDlg;
}
bool KCBTDialogManager::IsBTHMIDlgShow()
{
  if(m_pBTHMIDlg !=NULL && m_bBTHMIDlg == true)
  {
	  return true;
  }
  return false;
}
HCBluetoothBaseDlg* KCBTDialogManager::GetCurrentDlg()
{
	return GetDlg(m_eCurrentDlgType);
}
void KCBTDialogManager::HideBTHMIdlg()
{
	if(m_pBTHMIDlg != NULL)
	{	
		if(m_bBTHMIDlg)
		{
			((CBTHmiDlg*)m_pBTHMIDlg)->CloseHMIVidio();
//			m_eCurrentDlgType != eDIALOGT_BTHMI;
			//((CBTHmiDlg*)m_pBTHMIDlg)->CloseHMI();

			m_bBTHMIDlg = false;
		}
	}
}
HDialogBase* KCBTDialogManager::GetBTHMIDlg()
{
	return m_pBTHMIDlg;
}
void KCBTDialogManager::ReleaseUncurrentSource()
{
	for(HINT i = 0;i < eMAXBTDIALOGNUM;i++)
	{
		if(m_eCurrentDlgType != i && m_pBTDialog[i] != NULL)
		{
			m_pBTDialog[i]->ReleaseSource();
		}
	}
	if(m_eCurrentDlgType != eDIALOGT_BTHMI)
	{
		if(m_pBTHMIDlg != NULL)
		{
			((CBTHmiDlg*)m_pBTHMIDlg)->ReleaseSource();
		}
	}
}
void KCBTDialogManager::ReleaseCurrentSource()
{
	if(m_eCurrentDlgType < eDIALOGT_UNKNOW && m_eCurrentDlgType >= eDIALOGT_BTDIAL)
	{
		if(m_eCurrentDlgType != eDIALOGT_BTHMI)
		{
			if(m_pBTDialog[m_eCurrentDlgType] != NULL)
			{
				m_pBTDialog[m_eCurrentDlgType]->ReleaseSource();
			}
		}
		else if(m_eCurrentDlgType == eDIALOGT_BTHMI)
		{
			((CBTHmiDlg*)m_pBTHMIDlg)->ReleaseSource();
		}
	}
}
void KCBTDialogManager::RequreCurrentSource()
{
	ShowDlg(m_eCurrentDlgType);
}