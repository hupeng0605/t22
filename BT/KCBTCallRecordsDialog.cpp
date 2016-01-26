#include "KCBTCallRecordsDialog.h"
#include "KHMIBaseHead.h"
HCBTCallRecordsDlg::HCBTCallRecordsDlg()
{
		m_pGrpCtrlCallRecordsMiddle = NULL;
		m_pTxtCallRecordsBK = NULL;
		m_pScrCtrlCallRecords = NULL;
		m_pScrBoxCallRecords = NULL;
		m_pBtnCallRecordsUp = NULL;
		m_pBtnCallRecordsDown = NULL;
		m_pTxtCallRecordsHandleBK = NULL;
		m_pBtnCallRecordsDial = NULL;
		m_pBtnCallRecordsAllRecords = NULL;
		m_pBtnCallRecordsMissedCalls = NULL;
		m_pBtnCallRecordsDelete = NULL;
		m_pBtnCallRecordsDeleteAll = NULL;
		m_pTxtDeviceLine1 = NULL;
		m_pTxtDeviceLine2 = NULL;
		m_pTxtDeviceLine3 = NULL;
		m_pTxtDeviceLine4 = NULL;
		m_iScrboxCallRecords = -1;
		m_eCallHistory = eALLCALLRECORDS;
		m_bRecordsCleared = false;
};

HCBTCallRecordsDlg::~HCBTCallRecordsDlg()
{
	if(m_pScrBoxCallRecords->GetListItemCount() > 0)
	{
		m_pScrBoxCallRecords->DeleteAllListItems();
	}
	SAFE_DELETE(m_pTxtDeviceLine1);
	SAFE_DELETE(m_pTxtDeviceLine2);
	SAFE_DELETE(m_pTxtDeviceLine3);
	SAFE_DELETE(m_pTxtDeviceLine4);
	SAFE_DELETE(m_pBtnCallRecordsDeleteAll);
	SAFE_DELETE(m_pBtnCallRecordsDelete);
	SAFE_DELETE(m_pBtnCallRecordsMissedCalls);
	SAFE_DELETE(m_pBtnCallRecordsAllRecords);
	SAFE_DELETE(m_pBtnCallRecordsDial);
	SAFE_DELETE(m_pTxtCallRecordsHandleBK);
	SAFE_DELETE(m_pBtnCallRecordsDown);
	SAFE_DELETE(m_pBtnCallRecordsUp);
	SAFE_DELETE(m_pScrBoxCallRecords);
	SAFE_DELETE(m_pScrCtrlCallRecords);
	SAFE_DELETE(m_pTxtCallRecordsBK);
	SAFE_DELETE(m_pGrpCtrlCallRecordsMiddle);
	m_bRecordsCleared = false;
};
HINT HCBTCallRecordsDlg::OnInit()
{
	//通话记录中部
	HINT  nRet =  HCBluetoothBaseDlg::OnInit();
	//HCBluetoothBaseDlg::SetBTDlgBackGround();
	//m_pTxtScreen->SetText(L"通话记录");
	m_pGrpCtrlCallRecordsMiddle = new HCGroupCtrl;
	if(m_pGrpCtrlCallRecordsMiddle != NULL)
	{
		m_pGrpCtrlCallRecordsMiddle->SetShow(true);
		AddChild(m_pGrpCtrlCallRecordsMiddle);
		//通话记录背景
		m_pTxtCallRecordsBK = new HCImageCtrl;
		if(m_pTxtCallRecordsBK != NULL)
		{
			m_pTxtCallRecordsBK->Create(0,68,640,344);
			m_pTxtCallRecordsBK->EnableMsg(false);
			m_pTxtDeviceLine1 = new HCTextCtrl;
			if(m_pTxtDeviceLine1 != NULL)
			{
				m_pTxtDeviceLine1->Create(30,138,526,2);
				m_pTxtDeviceLine1->EnableMsg(false);
				m_pGrpCtrlCallRecordsMiddle->AddChild(m_pTxtDeviceLine1);
			}
			m_pTxtDeviceLine2 = new HCTextCtrl;
			if(m_pTxtDeviceLine2 != NULL)
			{
				m_pTxtDeviceLine2->Create(30,204,526,2);
				m_pTxtDeviceLine2->EnableMsg(false);
				m_pGrpCtrlCallRecordsMiddle->AddChild(m_pTxtDeviceLine2);
			}
			m_pTxtDeviceLine3 = new HCTextCtrl;
			if(m_pTxtDeviceLine3 != NULL)
			{
				m_pTxtDeviceLine3->Create(30,270,526,2);
				m_pTxtDeviceLine3->EnableMsg(false);
				m_pGrpCtrlCallRecordsMiddle->AddChild(m_pTxtDeviceLine3);
			}
			m_pTxtDeviceLine4 = new HCTextCtrl;
			if(m_pTxtDeviceLine4 != NULL)
			{
				m_pTxtDeviceLine4->Create(30,336,526,2);
				m_pTxtDeviceLine4->EnableMsg(false);
				m_pGrpCtrlCallRecordsMiddle->AddChild(m_pTxtDeviceLine4);
			}
			m_pGrpCtrlCallRecordsMiddle->AddChild(m_pTxtCallRecordsBK);
		}
		//通话记录滑块
		m_pScrCtrlCallRecords= new HCScrollCtrl;
		if(m_pScrCtrlCallRecords != NULL)
		{
			m_pScrCtrlCallRecords->Create(596,100,28,280,1);
			m_pScrCtrlCallRecords->SetBound(0,1);
			//m_pScrCtrlCallRecords->SetShow(false);
			//m_pGrpCtrlCallRecordsMiddle->AddChild(m_pScrCtrlCallRecords);
			AddChild(m_pScrCtrlCallRecords);
		}
		//通话记录滚动列表
		m_pScrBoxCallRecords = new HCScrollBox;
		if(m_pScrBoxCallRecords != NULL)
		{
			m_pScrBoxCallRecords->Create(15,75,582,330);
			//m_pScrBoxCallRecords->SetShow(false);
			m_pScrBoxCallRecords->SetTextColorN(255, 255, 255);//设置字体颜色
			m_pScrBoxCallRecords->SetTextColorA(255, 255, 255);//设置字体颜色
			m_pScrBoxCallRecords->SetFontSize(24, 24);//设置字体的大小
			m_pScrBoxCallRecords->SetCallBackClick(OnScrBoxCallRecords,this);
			//m_pScrboxChannelStore->SetBkgndN(GetHMIPath(_T("Share\\Share_Function_Frame.hfp")));
			//m_pScrboxChannelStore->SetSliderSurf(GetHMIPath(_T("Radio\\Radio_Storage_A.hfp")));
			//ChannelListsAddChannel();
			m_pScrBoxCallRecords->EnableScrollLine(true,66,NULL);
			m_pScrCtrlCallRecords->SetScrollBox(m_pScrBoxCallRecords,5);
			AddChild(m_pScrBoxCallRecords);
		}
		//通话记录本向上按钮
		m_pBtnCallRecordsUp = new HCButton;
		if(m_pBtnCallRecordsUp != NULL)
		{
			m_pBtnCallRecordsUp->Create(590, 74, 40, 36);
			m_pBtnCallRecordsUp->EnableMsg(true);
			m_pBtnCallRecordsUp->SetShow(true);
			//m_pGrpCtrlCallRecordsMiddle->AddChild(m_pBtnCallRecordsUp);
			AddChild(m_pBtnCallRecordsUp);
		}
		//通话记录向下按钮
		m_pBtnCallRecordsDown= new HCButton;
		if(m_pBtnCallRecordsDown != NULL)
		{
			m_pBtnCallRecordsDown->Create(590, 370, 40, 36);
			m_pBtnCallRecordsDown->EnableMsg(true);
			m_pBtnCallRecordsDown->SetShow(true);
			//m_pGrpCtrlCallRecordsMiddle->AddChild(m_pBtnCallRecordsDown);
			AddChild(m_pBtnCallRecordsDown);
			m_pScrCtrlCallRecords->SetAddButton(m_pBtnCallRecordsUp,m_pBtnCallRecordsDown);
		}
		//通话记录操作背景
		m_pTxtCallRecordsHandleBK = new HCImageCtrl;
		if(m_pTxtCallRecordsHandleBK != NULL)
		{
			m_pTxtCallRecordsHandleBK->Create(624,68,176,344);
			m_pTxtCallRecordsHandleBK->EnableMsg(false);
			m_pGrpCtrlCallRecordsMiddle->AddChild(m_pTxtCallRecordsHandleBK);
		}
		//拨打按钮
		m_pBtnCallRecordsDial = new HCButton;
		if(m_pBtnCallRecordsDial != NULL)
		{
			m_pBtnCallRecordsDial->Create(636,75, 152, 64);
			m_pBtnCallRecordsDial->EnableMsg(false);
			m_pBtnCallRecordsDial->SetCallBack(OnCall,this);
			m_pBtnCallRecordsDial->SetTextStyle(RE_TS_CENTER);
			m_pBtnCallRecordsDial->SetTextPos(103 ,31);
			m_pBtnCallRecordsDial->SetFontSize(24,24);
			//m_pBtnCallRecordsDial->SetText(_T("拨打"));
			m_pGrpCtrlCallRecordsMiddle->AddChild(m_pBtnCallRecordsDial);
		}
		//全部按钮
		m_pBtnCallRecordsAllRecords = new HCButton;
		if(m_pBtnCallRecordsAllRecords != NULL)
		{
			m_pBtnCallRecordsAllRecords->Create(636,142, 152, 64);
			m_pBtnCallRecordsAllRecords->EnableMsg(true);
			m_pBtnCallRecordsAllRecords->SetCallBack(OnAllRecords,this);
			m_pBtnCallRecordsAllRecords->SetTextStyle(RE_TS_CENTER);
			m_pBtnCallRecordsAllRecords->SetTextPos(103 ,31);
			m_pBtnCallRecordsAllRecords->SetFontSize(24,24);
			//m_pBtnCallRecordsAllRecords->SetText(_T("全部"));
			m_pGrpCtrlCallRecordsMiddle->AddChild(m_pBtnCallRecordsAllRecords);
		}
		//未接按钮
		m_pBtnCallRecordsMissedCalls = new HCButton;
		if(m_pBtnCallRecordsMissedCalls != NULL)
		{
			m_pBtnCallRecordsMissedCalls->Create(636,208, 152, 64);
			m_pBtnCallRecordsMissedCalls->EnableMsg(true);
			m_pBtnCallRecordsMissedCalls->SetCallBack(OnMissedCall,this);
			m_pBtnCallRecordsMissedCalls->SetTextStyle(RE_TS_CENTER);
			m_pBtnCallRecordsMissedCalls->SetTextPos(103 ,31);
			m_pBtnCallRecordsMissedCalls->SetFontSize(24,24);
			//m_pBtnCallRecordsMissedCalls->SetText(_T("未接"));
			m_pGrpCtrlCallRecordsMiddle->AddChild(m_pBtnCallRecordsMissedCalls);
		}
		//删除按钮
		m_pBtnCallRecordsDelete = new HCButton;
		if(m_pBtnCallRecordsDelete != NULL)
		{
			m_pBtnCallRecordsDelete->Create(636,274, 152, 64);
			m_pBtnCallRecordsDelete->EnableMsg(false);
			m_pBtnCallRecordsDelete->SetCallBack(OnDelete,this);
			m_pBtnCallRecordsDelete->SetTextStyle(RE_TS_CENTER);
			m_pBtnCallRecordsDelete->SetTextPos(103 ,31);
			m_pBtnCallRecordsDelete->SetFontSize(24,24);
			//m_pBtnCallRecordsDelete->SetText(_T("删除"));
			m_pGrpCtrlCallRecordsMiddle->AddChild(m_pBtnCallRecordsDelete);
		}
		//全部删除按钮
		m_pBtnCallRecordsDeleteAll = new HCButton;
		if(m_pBtnCallRecordsDeleteAll != NULL)
		{
			m_pBtnCallRecordsDeleteAll->Create(636,341, 152, 64);
			m_pBtnCallRecordsDeleteAll->EnableMsg(false);
			m_pBtnCallRecordsDeleteAll->SetCallBack(OnDeleteAll,this);
			m_pBtnCallRecordsDeleteAll->SetTextStyle(RE_TS_CENTER);
			m_pBtnCallRecordsDeleteAll->SetTextPos(103 ,31);
			m_pBtnCallRecordsDeleteAll->SetFontSize(24,24);
			//m_pBtnCallRecordsDeleteAll->SetText(_T("全部删除"));
			m_pGrpCtrlCallRecordsMiddle->AddChild(m_pBtnCallRecordsDeleteAll);
		}	
		//ChangeLangue(0);
		//m_nRecordsType = 0;
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
		m_eCallHistory = eUNKNOWCALLTYPE;
		m_iScrboxCallRecords = -1;
		UpDataRecords(false);
		//SetBTDlgBackGround();	
		SetShow(true);
	}
	return nRet;
}
void HCBTCallRecordsDlg::ChangeLangue(HINT nType)
{
	HCBluetoothBaseDlg::ChangeLangue(nType);
	if(s_pLan != NULL)
	{
		BTDEBUGINFO(L"HCBTCallRecordsDlg::%s,%d",__FUNCTIONW__,nType);
		switch (nType)
		{
			case 0:
			{
				//m_pBtnCallRecordsDial->SetFontSize(18,18);
				m_pBtnCallRecordsDial->SetFontSize(24,24);
				m_pBtnCallRecordsAllRecords->SetFontSize(24,24);
				m_pBtnCallRecordsMissedCalls->SetFontSize(24,24);
				m_pBtnCallRecordsDelete->SetFontSize(24,24);
				m_pBtnCallRecordsDeleteAll->SetFontSize(24,24);
			}
			break;
			case 1:
			{
				m_pBtnCallRecordsDial->SetFontSize(18,18);
				m_pBtnCallRecordsAllRecords->SetFontSize(18,18);
				m_pBtnCallRecordsMissedCalls->SetFontSize(18,18);
				m_pBtnCallRecordsDelete->SetFontSize(18,18);
				m_pBtnCallRecordsDeleteAll->SetFontSize(18,18);
			}
			break;
			default:
			break;
		}
		m_pTxtScreen->SetText(s_pLan[2]);
		m_pBtnCallRecordsDial->SetText(s_pLan[5]);
		m_pBtnCallRecordsAllRecords->SetText(s_pLan[9]);
		m_pBtnCallRecordsMissedCalls->SetText(s_pLan[10]);
		m_pBtnCallRecordsDelete->SetText(s_pLan[7]);
		m_pBtnCallRecordsDeleteAll->SetText(s_pLan[8]);
	}
}
void HCBTCallRecordsDlg::SetBTDlgBackGround()
{	
	HCBluetoothBaseDlg::SetBTDlgBackGround();
	HCBluetoothBaseDlg::SetBTCRBK();
//	m_pBtnBTDialCallRecords->SetBkgndN(pSource->m_pbtBaseCallRecordsA);
	//通话记录背景	
	 sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
	 if(pSource != NULL)
	 {
			m_pTxtCallRecordsBK->SetBkgndN(pSource->m_pbtBkLeft);
			m_pTxtCallRecordsBK->SetOpacity(8);
			m_pTxtCallRecordsHandleBK->SetBkgndN(pSource->m_pbtBkRight);
			m_pTxtCallRecordsHandleBK->SetOpacity(8);
			m_pTxtDeviceLine1->SetBkgndN(pSource->m_pbtLine);
			m_pTxtDeviceLine2->SetBkgndN(pSource->m_pbtLine);
			m_pTxtDeviceLine3->SetBkgndN(pSource->m_pbtLine);
			m_pTxtDeviceLine4->SetBkgndN(pSource->m_pbtLine);
			m_pScrCtrlCallRecords->SetBkgndN(pSource->m_pbtBarN);
			m_pScrCtrlCallRecords->SetBkgndA(pSource->m_pbtBarA);
			m_pScrCtrlCallRecords->SetBkgndD(pSource->m_pbtBarD);
			m_pScrCtrlCallRecords->SetBkgndF(pSource->m_pbtBarF);
			m_pBtnCallRecordsUp->SetBkgndN(pSource->m_pbtUpN);
			m_pBtnCallRecordsUp->SetBkgndA(pSource->m_pbtUpA);
			m_pBtnCallRecordsDown->SetBkgndN(pSource->m_pbtDownN);
			m_pBtnCallRecordsDown->SetBkgndA(pSource->m_pbtDownA);
	 }
	
	////通话记录滑块
	//m_pScrCtrlCallRecords->SetBkgndN(GetHMIPath(_T("Share\\Share_Slide_N.hfp")));
	//m_pScrCtrlCallRecords->SetBkgndA(GetHMIPath(_T("Share\\Share_Slide_Bar.hfp")));
	//m_pScrCtrlCallRecords->SetBkgndD(GetHMIPath(_T("Share\\Share_Slide_A.hfp")));
	//m_pScrCtrlCallRecords->SetBkgndF(GetHMIPath(_T("Share\\Share_Slide_Bar.hfp")));
	////通话记录向上按钮
	//m_pBtnCallRecordsUp->SetBkgndN(GetHMIPath(_T("Share\\Share_Front_N.hfp")));
	//m_pBtnCallRecordsUp->SetBkgndA(GetHMIPath(_T("Share\\Share_Front_A.hfp")));
	////通话记录向下按钮
	//m_pBtnCallRecordsDown->SetBkgndN(GetHMIPath(_T("Share\\Share_Last_N.hfp")));
	//m_pBtnCallRecordsDown->SetBkgndA(GetHMIPath(_T("Share\\Share_Last_A.hfp")));
	////操作背景

	//拨打按钮
	//m_pBtnCallRecordsDial->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_D.hfp")));
	m_pBtnCallRecordsDial->SetBkgndA(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_A.hfp")));
	//全部按钮
	//m_pBtnCallRecordsAllRecords->SetBkgndN(GetHMIPath(_T("Bluetooth\\Records\\Records_All_N.hfp")));
	m_pBtnCallRecordsAllRecords->SetBkgndA(GetHMIPath(_T("Bluetooth\\Records\\Records_All_A.hfp")));
	//未接电话按钮
	//m_pBtnCallRecordsMissedCalls->SetBkgndN(GetHMIPath(_T("Bluetooth\\Records\\Records_Missed_N.hfp")));
	m_pBtnCallRecordsMissedCalls->SetBkgndA(GetHMIPath(_T("Bluetooth\\Records\\Records_Missed_A.hfp")));
	//删除按钮
	if(m_iScrboxCallRecords >= 0)
	{
		m_pBtnCallRecordsDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_N.hfp")));
		m_pBtnCallRecordsDial->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_N.hfp")));
	}
	else
	{
		m_pBtnCallRecordsDial->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_D.hfp")));
		m_pBtnCallRecordsDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
	}
	//m_pBtnCallRecordsDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
	m_pBtnCallRecordsDelete->SetBkgndA(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_A.hfp")));
	if(m_pScrBoxCallRecords->GetListItemCount() > 0)
	{
		m_pBtnCallRecordsDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_N.hfp")));
	}
	else
	{
		m_pBtnCallRecordsDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
	}
	//全部删除按钮
	//m_pBtnCallRecordsDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
	m_pBtnCallRecordsDeleteAll->SetBkgndA(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_A.hfp")));
}

HCListItem* HCBTCallRecordsDlg::CreatCallHistoryItem(sCallHistory *pCallHistory)
{
	if(pCallHistory != NULL)
	{
		HCHAR pTemp[65] ;
		memset(pTemp,0,sizeof(pTemp));
		HCListItem* pTempListItemCallHistory = new HCListItem;
		/*wcsncpy(pTemp,pCallHistory->szContact.szName,10);
		wcsncpy(pTemp+10,pCallHistory->szContact.szTelNumber.PhoneNumber,30);
		for(HINT i = 0;i<= 40;i++)
		{
			if(pTemp[i] == (L'\0') )
			{
				pTemp[i] = L' ';
			}
		}
		wcsncpy(pTemp + 40,pCallHistory->szPhoneTime,20);
		pTemp[60] = L'\0';*/
		HCTextCtrl* pIcon = new HCTextCtrl;
		pIcon->Create(0,0,48,60);
		pIcon->EnableMsg(false);
		sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
		if(pSource != NULL)
		{
			switch (pCallHistory->eCallType)
			{


			case eMISSEDCALL:
				{
					pIcon->SetBkgndN(pSource->m_pbtMissedCall);
				}
				break;
			case eINCOMMINGCALL:
				{
					pIcon->SetBkgndN(pSource->m_pbtCallIn);
				}
				break;
			case eOUTGOINGCALL:
				{
				}
			default:
				{
					pIcon->SetBkgndN(pSource->m_pbtCallOut);
				}
				break;	
			}
		}
		HCTextCtrl* p1 = new HCTextCtrl;
		p1->Create(48,0,150,56);
		memset(pTemp,0,sizeof(pTemp));
		wcsncpy(pTemp,pCallHistory->szContact.szName,10);
		p1->SetText(pTemp);
		p1->SetTextPos(0,16);
		p1->SetFontSize(24,24);
		p1->SetTxtColor(255,255,255);
		p1->EnableMsg(false);
		p1->SetTextStyle(RE_TS_NORMAL);
		pTempListItemCallHistory->AddBaseCtrl((HCBaseCtrl*)p1);
		HCTextCtrl* p2 = new HCTextCtrl;
		p2->Create(218,0,250,56);
		memset(pTemp,0,sizeof(pTemp));
		wcsncpy(pTemp,pCallHistory->szContact.szTelNumber.PhoneNumber,30);
		p2->SetText(pTemp);
		p2->SetTextPos(0,16);
		p2->EnableMsg(false);
		p2->SetFontSize(24,24);
		p2->SetTxtColor(255,255,255);
		p2->SetTextStyle(RE_TS_NORMAL);
		pTempListItemCallHistory->AddBaseCtrl((HCBaseCtrl*)p2);

		//HCTextCtrl* p3 = new HCTextCtrl;
		//p3->Create(418,0,162,56);
		//memset(pTemp,0,sizeof(pTemp));
		////wcsncpy(pTemp,pCallHistory->szPhoneTime,20);
		//HINT i = 0;
		//HINT j = 0; 
		//for( i = 0; i < 4;i++)
		//{
		//	pTemp[j] = pCallHistory->szPhoneTime[i];
		//	j++;
		//}
		//pTemp[j] = L'年';
		//j++;
		//if(pCallHistory->szPhoneTime[i] == L'0')
		//{
		//	i++;
		//	pTemp[j] = pCallHistory->szPhoneTime[i];
		//	j++;
		//	i++;
		//}
		//else
		//{
		//	pTemp[j] = pCallHistory->szPhoneTime[i];
		//	j++;
		//	i++;
		//	pTemp[j] = pCallHistory->szPhoneTime[i];
		//	j++;
		//	i++;
		//}
		//pTemp[j] = L'月';
		//j++;
		//if(pCallHistory->szPhoneTime[i] == L'0')
		//{
		//	i++;
		//	pTemp[j] = pCallHistory->szPhoneTime[i];
		//	j++;
		//	i++;
		//}
		//else
		//{
		//	pTemp[j] = pCallHistory->szPhoneTime[i];
		//	j++;
		//	i++;
		//	pTemp[j] = pCallHistory->szPhoneTime[i];
		//	j++;
		//	i++;
		//}
		//pTemp[j] = L'日';
		//i++;
		//j++;
		//if(pCallHistory->szPhoneTime[i] == L'0')
		//{
		//	i++;
		//	pTemp[j] = pCallHistory->szPhoneTime[i];
		//	j++;
		//	i++;
		//}
		//else
		//{
		//	pTemp[j] = pCallHistory->szPhoneTime[i];
		//	j++;
		//	i++;
		//	pTemp[j] = pCallHistory->szPhoneTime[i];
		//	j++;
		//	i++;
		//}
		//pTemp[j] = L':';
		//j++;
		//pTemp[j] = pCallHistory->szPhoneTime[i];
		//j++;
		//i++;
		//pTemp[j] = pCallHistory->szPhoneTime[i];
		//j++;
		//i++;
		//pTemp[j] = L'\0';
		/*p3->SetText(pTemp+5);
		p3->SetTextPos(0,16);
		p3->SetFontSize(24,24);
		p3->EnableMsg(false);
		p3->SetTextStyle(RE_TS_NORMAL | RE_TS_SHADOW);
		p3->SetTxtColor(255,255,255);
		pTempListItemCallHistory->AddBaseCtrl((HCBaseCtrl*)p3);*///通话记录时间
		pTempListItemCallHistory->AddBaseCtrl((HCBaseCtrl*)pIcon);
		pTempListItemCallHistory->Create(515 , 66, NULL, NULL);
		pTempListItemCallHistory->SetEnableRoll(true, 1);
		pTempListItemCallHistory->SetFontPos(5);
		pTempListItemCallHistory->SetRollWidth(400);
		//pTempListItemCallHistory->SetText(pTemp);
		pTempListItemCallHistory->SetCanFocus(true);
//		sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
		if(pSource != NULL)
		{
			pTempListItemCallHistory->SetBkgndA(pSource->m_pbtItemSelected);
			pTempListItemCallHistory->SetBkgndF(pSource->m_pbtItemSelected);
		}
		return pTempListItemCallHistory;
	}
	return NULL;
}


void HCBTCallRecordsDlg::OnCall(void* pDlg, void* param)
{
	HCBTCallRecordsDlg* pObj = (HCBTCallRecordsDlg*)pDlg;
	pObj->OnCall(pObj);
}
void HCBTCallRecordsDlg::OnCall(void* pDlg)
{
	HCListItemBase *pListItemSelect = m_pScrBoxCallRecords->GetSelectListItem();
	HINT iSelectIndex = -1; 
	if(pListItemSelect != NULL && s_bDailing == false)
	{
		iSelectIndex = m_pScrBoxCallRecords->GetListItemIndex(pListItemSelect);
		((HCListItem*)(pListItemSelect))->GetBaseCtrlVec();
		HINT nNum = ((HCListItem*)(pListItemSelect))->GetBaseCtrlCount();
		if(nNum >= 2)
		{
			HCBaseCtrl* pTxt = ((HCListItem*)(pListItemSelect))->GetBaseCtrlVec()[1];
			HString stTxt = ((HCTextCtrl*)pTxt)->GetText();
			HCHAR* p = &stTxt[0]; 
			HUINT nCmdLen = strlen("AT+HFDIAL=");
			HBYTE cCommand[100] = {0};
			strncpy((char*)cCommand,"AT+HFDIAL=",nCmdLen);
			int nwLen = WideCharToMultiByte(CP_ACP,NULL,p,-1,NULL,0,NULL,NULL);
			WideCharToMultiByte(CP_ACP,NULL,p,-1,(char*)(cCommand+nCmdLen),nwLen-1,NULL,NULL);
			cCommand[nCmdLen+nwLen-1] ='\r';
			cCommand[nCmdLen+nwLen ] ='\n';
			::PostMessage(CBTCommand::Instance()->GetMyHandel(),WM_USER + 25,0,0);
#ifdef TESTBTCOMMANDQUEUE
			Block *pBlock = CCommandPool::Intance()->PoolNew();
			if(pBlock != NULL)
			{
				sCommandData* pt = (sCommandData*)(pBlock->Buf);
				memset(pt,0,sizeof(sCommandData));
				memcpy(pt->szCommand,cCommand,nCmdLen + nwLen +1);
				pt->nCmdLen = nCmdLen + nwLen +1;
				CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPDialTheNumber,pBlock);
			}
#else
			CBTCommand::Instance()->SendData(cCommand,nCmdLen + nwLen +1);	
#endif
		}
	}

}
void HCBTCallRecordsDlg::OnScrBoxCallRecords(void* pDlg, void* param)
{
	HCBTCallRecordsDlg* pObj = (HCBTCallRecordsDlg*)pDlg;
	pObj->OnScrBoxCallRecords(pObj);
}
void HCBTCallRecordsDlg::OnScrBoxCallRecords(void* pDlg)
{
	HCListItemBase *pListItemSelect = m_pScrBoxCallRecords->GetSelectListItem();
	sBTCommandData* p = CBTCommand::Instance()->GetBTCommandData();
	HUINT n = 0;
	HUINT nNew = 0;
	if(p != NULL)
	{
		switch (m_eCallHistory)
		{
			case  eMISSEDCALL:
			{
				n = p->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall;
#if AUTOUPDATACALLHISTORY
				nNew = p->PBAPCData.sPBAPCPhoneBook.nNewMissed;
#else
#endif
			}
			break;
			case  eINCOMMINGCALL:
			{
				n = p->PBAPCData.sPBAPCPhoneBook.nTotalIncomeCall;
#if AUTOUPDATACALLHISTORY
				nNew = p->PBAPCData.sPBAPCPhoneBook.nNewInCome;
#else
#endif
			}
			break;
			case  eOUTGOINGCALL:
			{
				n = p->PBAPCData.sPBAPCPhoneBook.nOutGoingCall;
#if AUTOUPDATACALLHISTORY
				nNew = p->PBAPCData.sPBAPCPhoneBook.nNewOutGoing;
#else
#endif
			}
			break;
			case  eALLCALLRECORDS:
			{
				n = p->PBAPCData.sPBAPCPhoneBook.nCombinationCall;
#if AUTOUPDATACALLHISTORY
				nNew = p->PBAPCData.sPBAPCPhoneBook.nNewCallHistory;
#else
#endif
			}
			break;
			default:
			{
			}
			break;
		}
		n += nNew;
	}
	HINT iSelectIndex = -1;
	if(pListItemSelect != NULL)
	{
		iSelectIndex = m_pScrBoxCallRecords->GetListItemIndex(pListItemSelect);
	}
	if(m_iScrboxCallRecords == iSelectIndex)
	{
		OnCall(this);
	}
	else 
	{
		m_iScrboxCallRecords = iSelectIndex;
	}
	if(m_iScrboxCallRecords >= 0)
	{
		m_pScrBoxCallRecords->SetSelectListItem(m_iScrboxCallRecords, false);
		m_pBtnCallRecordsDial->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_N.hfp")));
	    m_pBtnCallRecordsDelete->EnableMsg(true);
		m_pBtnCallRecordsDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_N.hfp")));
		m_pBtnCallRecordsDial->EnableMsg(true);
	}
	else
	{
		m_pBtnCallRecordsDelete->EnableMsg(false);
		m_pBtnCallRecordsDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
		m_pBtnCallRecordsDial->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_D.hfp")));
		m_pBtnCallRecordsDial->EnableMsg(false);
		m_iScrboxCallRecords = -1;
	}
	if(n > 0)
	{
		m_pBtnCallRecordsDeleteAll->EnableMsg(true);
		m_pBtnCallRecordsDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_N.hfp")));
	}
	else
	{
		m_pBtnCallRecordsDeleteAll->EnableMsg(false);
		m_pBtnCallRecordsDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
	}
}
void HCBTCallRecordsDlg::AddCallRecordsItem(void)
{
	sBTCommandData* p = CBTCommand::Instance()->GetBTCommandData();
	if(p != NULL)
	{
		HUINT nNewTol = 0;
		HUINT nNewMiss = 0;
		HUINT nICome = 0;
		HUINT nOutGo = 0;
#if AUTOUPDATACALLHISTORY
		nNewTol = p->PBAPCData.sPBAPCPhoneBook.nNewCallHistory;
		nNewMiss = p->PBAPCData.sPBAPCPhoneBook.nNewMissed;
		nICome = p->PBAPCData.sPBAPCPhoneBook.nNewInCome;
		nOutGo = p->PBAPCData.sPBAPCPhoneBook.nNewOutGoing;
#else
#endif
		switch(m_eCallHistory)
		{
		case  eMISSEDCALL:
			{
				m_pScrBoxCallRecords->DeleteAllListItems();
				m_pScrCtrlCallRecords->SetValue(0);
				m_pScrCtrlCallRecords->SetBound(0,1);
				if(p != NULL)
				{
					HUINT n  = p->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall;
					if((n + nNewMiss) > 0)
					{
						m_bRecordsCleared = false;
						m_pScrCtrlCallRecords->SetBound(0,(n + nNewMiss-1)/5);
#if AUTOUPDATACALLHISTORY
						if(nNewMiss > 0)
						{
							for(HUINT j = nNewMiss; j > 0;j--)
							{
								if(p->PBAPCData.sPBAPCPhoneBook.arrNewMissedCall[j-1].eCallType == eMISSEDCALL)
								{
									HCListItem* pTem = CreatCallHistoryItem(&p->PBAPCData.sPBAPCPhoneBook.arrNewMissedCall[j-1]);
									if(pTem != NULL)
									{
										m_pScrBoxCallRecords->AddListItem(pTem);
									}		
								}
							}
						}	
#else
#endif
						if(n > 0)
						{
							for(HUINT i = 0;i < n;i++)
							{
								HCListItem* pTem = CreatCallHistoryItem(&p->PBAPCData.sPBAPCPhoneBook.arrMissedCall[i]);
								if(pTem != NULL)
								{
									m_pScrBoxCallRecords->AddListItem(pTem);
								}		
							}
						}		
					}
				}
			}
			break;
		case eINCOMMINGCALL:
			{
				m_pScrBoxCallRecords->DeleteAllListItems();
				m_pScrCtrlCallRecords->SetValue(0);
				m_pScrCtrlCallRecords->SetBound(0,1);
			//	sBTCommandData* p = CBTCommand::Instance()->GetBTCommandData();
				if(p != NULL)
				{
					HUINT n  = p->PBAPCData.sPBAPCPhoneBook.nTotalIncomeCall;
					if(n + nICome > 0)
					{
						m_bRecordsCleared = false;
						m_pScrCtrlCallRecords->SetBound(0,(n + nICome - 1)/5);
#if AUTOUPDATACALLHISTORY
						if(nICome > 0)
						{
							for(HUINT j = nICome; j > 0;j--)
							{
								if(p->PBAPCData.sPBAPCPhoneBook.arrNewInComeCall[j-1].eCallType == eINCOMMINGCALL)
								{
									HCListItem* pTem = CreatCallHistoryItem(&p->PBAPCData.sPBAPCPhoneBook.arrNewInComeCall[j-1]);
									if(pTem != NULL)
									{
										m_pScrBoxCallRecords->AddListItem(pTem);
									}		
								}
							}
						}	
#else
#endif
						if(n > 0)
						{
							for(HUINT i = 0;i < n;i++)
							{
								HCListItem* pTem = CreatCallHistoryItem(&p->PBAPCData.sPBAPCPhoneBook.arrIncomeCall[i]);
								if(pTem != NULL)
								{
									m_pScrBoxCallRecords->AddListItem(pTem);
								}		
							}
						}
					}
				}
			}
			break;
		case eOUTGOINGCALL:
			{
				m_pScrBoxCallRecords->DeleteAllListItems();
				m_pScrCtrlCallRecords->SetValue(0);
				m_pScrCtrlCallRecords->SetBound(0,1);
				//sBTCommandData* p = CBTCommand::Instance()->GetBTCommandData();
				if(p != NULL )
				{
					HUINT n  = p->PBAPCData.sPBAPCPhoneBook.nOutGoingCall;
					if(n + nNewTol > 0 )
					{
						m_bRecordsCleared =  false;
						m_pScrCtrlCallRecords->SetBound(0,(n + nOutGo - 1)/5);
#if AUTOUPDATACALLHISTORY
						if(nOutGo > 0)
						{
							for(HUINT j = nOutGo; j > 0;j--)
							{
								if(p->PBAPCData.sPBAPCPhoneBook.arrNewOutGoingCall[j-1].eCallType == eOUTGOINGCALL)
								{
									HCListItem* pTem = CreatCallHistoryItem(&p->PBAPCData.sPBAPCPhoneBook.arrNewOutGoingCall[j-1]);
									if(pTem != NULL)
									{
										m_pScrBoxCallRecords->AddListItem(pTem);
									}		
								}
							}
						}	
#else
#endif
						if(n > 0)
						{
							for(HUINT i = 0;i < n;i++)
							{
								HCListItem* pTem = CreatCallHistoryItem(&p->PBAPCData.sPBAPCPhoneBook.arrOutGoingCall[i]);
								if(pTem != NULL)
								{
									m_pScrBoxCallRecords->AddListItem(pTem);
								}		
							}

						}
					}	
				}
			}
			break;
		case eALLCALLRECORDS:
			{
				m_pScrBoxCallRecords->DeleteAllListItems();
				m_pScrCtrlCallRecords->SetValue(0);
				m_pScrCtrlCallRecords->SetBound(0,1);
				//sBTCommandData* p = CBTCommand::Instance()->GetBTCommandData();
				if(p != NULL)
				{
					HUINT n  = p->PBAPCData.sPBAPCPhoneBook.nCombinationCall;	
					if((nNewTol + n) > 0)
					{		
						m_bRecordsCleared = false;
						m_pScrCtrlCallRecords->SetBound(0,(n + nNewTol-1)/5);
#if AUTOUPDATACALLHISTORY
						if(nNewTol > 0)
						{
							for(int j = nNewTol; j > 0;j--)
							{
								HCListItem* pTem = CreatCallHistoryItem(&p->PBAPCData.sPBAPCPhoneBook.arrNewCallHistory[j-1]);
								if(pTem != NULL)
								{
									m_pScrBoxCallRecords->AddListItem(pTem);
								}		
							}
						}
#else
#endif
						if(n > 0)
						{
							//m_pScrCtrlCallRecords->SetBound(0,(n-1)/5);
							for(HUINT i = 0;i < n;i++)
							{
								HCListItem* pTem = CreatCallHistoryItem(&p->PBAPCData.sPBAPCPhoneBook.arrCombinationCall[i]);
								if(pTem != NULL)
								{
									m_pScrBoxCallRecords->AddListItem(pTem);
								}		
							}

						}
					}
				}
			}
			break;
		default:
			{

			}
			break;
		}
	
	}
	m_iScrboxCallRecords = -1;
	m_pBtnCallRecordsDial->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_D.hfp")));
	m_pBtnCallRecordsDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
	if(m_pScrBoxCallRecords->GetListItemCount() > 0)
	{
		m_pBtnCallRecordsDeleteAll->EnableMsg(true);
		m_pBtnCallRecordsDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_N.hfp")));
	}
	else
	{
		m_pBtnCallRecordsDeleteAll->EnableMsg(false);
		m_pBtnCallRecordsDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
	}
}
void HCBTCallRecordsDlg::OnAllRecords(void* pDlg, void* param)
{
	HCBTCallRecordsDlg* pObj = (HCBTCallRecordsDlg*)pDlg;
	pObj->OnAllRecords(pObj);
}
void HCBTCallRecordsDlg::OnAllRecords(void* pDlg)
{
	m_eCallHistory = eALLCALLRECORDS;
	AddCallRecordsItem();
}
void HCBTCallRecordsDlg::OnMissedCall(void* pDlg, void* param)
{
	HCBTCallRecordsDlg* pObj = (HCBTCallRecordsDlg*)pDlg;
	pObj->OnMissedCall(pObj);
}
void HCBTCallRecordsDlg::OnMissedCall(void* pDlg)
{
	m_eCallHistory = eMISSEDCALL;
	AddCallRecordsItem();
}
void HCBTCallRecordsDlg::OnDelete(void* pDlg, void* param)
{
	HCBTCallRecordsDlg* pObj = (HCBTCallRecordsDlg*)pDlg;
	pObj->OnDelete(pObj);
}
void HCBTCallRecordsDlg::OnDelete(void* pDlg)
{
	if(m_iScrboxCallRecords >= 0)
	{
		HCListItemBase *pListItemSelect =m_pScrBoxCallRecords->GetItemAt(m_iScrboxCallRecords);
		if(pListItemSelect != NULL)
		{
			m_pScrBoxCallRecords->DeleteListItem(pListItemSelect);
			sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
			if(p != NULL && m_eCallHistory == eALLCALLRECORDS)
			{
				HINT nNew = 0;
#if AUTOUPDATACALLHISTORY
				nNew = p->PBAPCData.sPBAPCPhoneBook.nNewCallHistory;
				sCallHistory *ptNew = NULL;
				ptNew = p->PBAPCData.sPBAPCPhoneBook.arrNewCallHistory;
#else
#endif
				HUINT nTotal = p->PBAPCData.sPBAPCPhoneBook.nCombinationCall;
				nTotal += nNew;
				if(nTotal > 0)
				{
					sCallHistory *pt = p->PBAPCData.sPBAPCPhoneBook.arrCombinationCall;
					if((m_iScrboxCallRecords + 1) >nNew)
					{
						if(pt != NULL && nTotal > (m_iScrboxCallRecords + 1))
						{
							memset(pt[m_iScrboxCallRecords - nNew].szContact.szName,0,sizeof(pt[m_iScrboxCallRecords - nNew].szContact.szName));
							memset(pt[m_iScrboxCallRecords - nNew].szContact.szTelNumber.PhoneNumber,0,sizeof(pt[m_iScrboxCallRecords - nNew].szContact.szTelNumber.PhoneNumber));
							memset(pt[m_iScrboxCallRecords - nNew].szPhoneTime,0,sizeof(pt[m_iScrboxCallRecords - nNew].szPhoneTime));
							for(HINT i = m_iScrboxCallRecords + 1 - nNew; i < nTotal - nNew; i++)
							{
								memcpy(pt[i-1].szContact.szName,pt[i].szContact.szName,sizeof(pt[i].szContact.szName));
								memcpy(pt[i-1].szContact.szTelNumber.PhoneNumber,pt[i].szContact.szTelNumber.PhoneNumber,sizeof(pt[i].szContact.szTelNumber.PhoneNumber));
								memcpy(pt[i-1].szPhoneTime,pt[i].szPhoneTime,sizeof(pt[i].szPhoneTime));
								memset(pt[i].szContact.szName,0,sizeof(pt[i].szContact.szName));
								memset(pt[i].szContact.szTelNumber.PhoneNumber,0,sizeof(pt[i].szContact.szTelNumber.PhoneNumber));
								memset(pt[i].szPhoneTime,0,sizeof(pt[i].szPhoneTime));				
							}
							memset(pt[nTotal - nNew - 1].szContact.szName,0,sizeof(pt[nTotal - nNew -1].szContact.szName));
							memset(pt[nTotal - nNew - 1].szContact.szTelNumber.PhoneNumber,0,sizeof(pt[nTotal - nNew - 1].szContact.szTelNumber.PhoneNumber));
							memset(pt[nTotal - nNew - 1].szPhoneTime,0,sizeof(pt[nTotal - nNew - 1].szPhoneTime));

						}
						else
						{
							memset(pt[nTotal- nNew - 1].szContact.szName,0,sizeof(pt[nTotal - nNew -1].szContact.szName));
							memset(pt[nTotal - nNew - 1].szContact.szTelNumber.PhoneNumber,0,sizeof(pt[nTotal - nNew -1].szContact.szTelNumber.PhoneNumber));
							memset(pt[nTotal - nNew - 1].szPhoneTime,0,sizeof(pt[nTotal - nNew -1].szPhoneTime));
						}
						p->PBAPCData.sPBAPCPhoneBook.nCombinationCall -= 1;
					}
#if AUTOUPDATACALLHISTORY 
					else
					{
						if(ptNew != NULL && (m_iScrboxCallRecords ) == 0 && nNew > 0)
						{
							memset(ptNew[nNew-1].szContact.szName,0,sizeof(ptNew[nNew-1].szContact.szName));
							memset(ptNew[nNew-1].szContact.szTelNumber.PhoneNumber,0,sizeof(ptNew[nNew-1].szContact.szTelNumber.PhoneNumber));
							memset(ptNew[nNew-1].szPhoneTime,0,sizeof(ptNew[nNew-1].szPhoneTime));
						}
						else if(ptNew != NULL && (m_iScrboxCallRecords + 1) < nNew && nNew > 0)
						{
							m_iScrboxCallRecords = nNew - m_iScrboxCallRecords -1;
							memset(&ptNew[m_iScrboxCallRecords],0,sizeof(ptNew[m_iScrboxCallRecords]));
							for(int j = m_iScrboxCallRecords + 1;j < nNew;j ++)
							{
								memcpy(&ptNew[j - 1],&ptNew[j],sizeof(ptNew[j - 1]));
								memset(&ptNew[j],0,sizeof(ptNew[j]));
							}
							memset(&ptNew[nNew - 1],0,sizeof(ptNew[nNew - 1]));
						}
						p->PBAPCData.sPBAPCPhoneBook.nNewCallHistory -= 1;
						nNew = p->PBAPCData.sPBAPCPhoneBook.nNewCallHistory;
					}
#else
#endif
					//m_pScrCtrlCallRecords->SetBound(0,(p->PBAPCData.sPBAPCPhoneBook.nCombinationCall - 1)/6 +1);
					m_iScrboxCallRecords = -1;
					m_pBtnCallRecordsDelete->EnableMsg(false);
					m_pBtnCallRecordsDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
					m_pBtnCallRecordsDial->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_D.hfp")));
					m_pBtnCallRecordsDial->EnableMsg(false);
					if((p->PBAPCData.sPBAPCPhoneBook.nCombinationCall + nNew)> 0)
					{
						m_pBtnCallRecordsDeleteAll->EnableMsg(true);
						m_pBtnCallRecordsDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_N.hfp")));
						//m_pScrCtrlCallRecords->SetBound(0,p->PBAPCData.sPBAPCPhoneBook.nCombinationCall);
					}
					else
					{
						m_pBtnCallRecordsDeleteAll->EnableMsg(false);
						m_pBtnCallRecordsDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
						m_pScrCtrlCallRecords->SetBound(0,1);
					}
				}
			}
			else if(p != NULL && m_eCallHistory == eMISSEDCALL)
			{
				HINT nNew = 0;
#if AUTOUPDATACALLHISTORY
				nNew = p->PBAPCData.sPBAPCPhoneBook.nNewMissed;
				sCallHistory *ptNew = NULL;
				ptNew = p->PBAPCData.sPBAPCPhoneBook.arrNewMissedCall;
#else
#endif
				HUINT nTotal = p->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall;
				nTotal += nNew;
				if(nTotal > 0)
				{
					sCallHistory *pt = p->PBAPCData.sPBAPCPhoneBook.arrMissedCall;
					if((m_iScrboxCallRecords + 1) >nNew)
					{
						if(pt != NULL && nTotal > (m_iScrboxCallRecords + 1))
						{
							memset(pt[m_iScrboxCallRecords - nNew].szContact.szName,0,sizeof(pt[m_iScrboxCallRecords - nNew].szContact.szName));
							memset(pt[m_iScrboxCallRecords - nNew].szContact.szTelNumber.PhoneNumber,0,sizeof(pt[m_iScrboxCallRecords - nNew].szContact.szTelNumber.PhoneNumber));
							memset(pt[m_iScrboxCallRecords - nNew].szPhoneTime,0,sizeof(pt[m_iScrboxCallRecords - nNew].szPhoneTime));
							for(HINT i = m_iScrboxCallRecords  - nNew + 1; i < nTotal - nNew; i++)
							{
								memcpy(pt[i-1].szContact.szName,pt[i].szContact.szName,sizeof(pt[i].szContact.szName));
								memcpy(pt[i-1].szContact.szTelNumber.PhoneNumber,pt[i].szContact.szTelNumber.PhoneNumber,sizeof(pt[i].szContact.szTelNumber.PhoneNumber));
								memcpy(pt[i-1].szPhoneTime,pt[i].szPhoneTime,sizeof(pt[i].szPhoneTime));
							}
							memset(pt[nTotal - nNew - 1].szContact.szName,0,sizeof(pt[nTotal  - nNew -1].szContact.szName));
							memset(pt[nTotal - nNew - 1].szContact.szTelNumber.PhoneNumber,0,sizeof(pt[nTotal - nNew - 1].szContact.szTelNumber.PhoneNumber));
							memset(pt[nTotal - nNew - 1].szPhoneTime,0,sizeof(pt[nTotal - nNew - 1].szPhoneTime));

						}
						else
						{
							memset(pt[nTotal  - nNew - 1].szContact.szName,0,sizeof(pt[nTotal - nNew - 1].szContact.szName));
							memset(pt[nTotal  - nNew - 1].szContact.szTelNumber.PhoneNumber,0,sizeof(pt[nTotal - nNew - 1].szContact.szTelNumber.PhoneNumber));
							memset(pt[nTotal  - nNew - 1].szPhoneTime,0,sizeof(pt[nTotal  - nNew - 1].szPhoneTime));
						}
						p->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall -= 1;
					}
#if AUTOUPDATACALLHISTORY 
				else
				{
					if(ptNew != NULL && (m_iScrboxCallRecords + 1) == nNew && nNew > 0)
					{
						memset(ptNew[nNew-1].szContact.szName,0,sizeof(ptNew[nNew-1].szContact.szName));
						memset(ptNew[nNew-1].szContact.szTelNumber.PhoneNumber,0,sizeof(ptNew[nNew-1].szContact.szTelNumber.PhoneNumber));
						memset(ptNew[nNew-1].szPhoneTime,0,sizeof(ptNew[nNew-1].szPhoneTime));
					}
					else if(ptNew != NULL && (m_iScrboxCallRecords + 1) < nNew && nNew > 0)
					{
						memset(&ptNew[m_iScrboxCallRecords],0,sizeof(ptNew[m_iScrboxCallRecords]));
						for(int j = m_iScrboxCallRecords + 1;j < nNew;j ++)
						{
							memcpy(&ptNew[j - 1],&ptNew[j],sizeof(ptNew[j - 1]));
							memset(&ptNew[j],0,sizeof(ptNew[j]));
						}
						memset(&ptNew[nNew - 1],0,sizeof(ptNew[nNew - 1]));
					}
					p->PBAPCData.sPBAPCPhoneBook.nNewCallHistory -= 1;
					nNew = p->PBAPCData.sPBAPCPhoneBook.nNewCallHistory;
				}
#else
#endif
				
					//m_pScrCtrlCallRecords->SetBound(0,(p->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall - 1)/6+1);
					m_iScrboxCallRecords = -1;
					m_pBtnCallRecordsDelete->EnableMsg(false);
					m_pBtnCallRecordsDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
					m_pBtnCallRecordsDial->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_D.hfp")));
					m_pBtnCallRecordsDial->EnableMsg(false);
					if((p->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall + nNew)> 0)
					{
						m_pBtnCallRecordsDeleteAll->EnableMsg(true);
						m_pBtnCallRecordsDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_N.hfp")));
						//m_pScrCtrlCallRecords->SetBound(0,(p->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall-1)/6);
					}
					else
					{
						m_pBtnCallRecordsDeleteAll->EnableMsg(false);
						m_pBtnCallRecordsDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
						m_pScrCtrlCallRecords->SetBound(0,1);
					}
				}
			}
		}
	}
}
void HCBTCallRecordsDlg::OnDeleteAll(void* pDlg, void* param)
{
	HCBTCallRecordsDlg* pObj = (HCBTCallRecordsDlg*)pDlg;
	pObj->OnDeleteAll(pObj);
}
void HCBTCallRecordsDlg::OnDeleteAll(void* pDlg)
{
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	HUINT n = 0;
	sCallHistory *pt = NULL;
#if AUTOUPDATACALLHISTORY
	HUINT nNew = 0;
	sCallHistory *ptNew = NULL;
#else
#endif
	//HUINT *pTtotal = NULL;
	if(p != NULL)
	{
		switch (m_eCallHistory)
		{
			case  eMISSEDCALL:
			{
				n = p->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall;
				pt = p->PBAPCData.sPBAPCPhoneBook.arrMissedCall;
				p->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall = 0;
#if AUTOUPDATACALLHISTORY
				 nNew = p->PBAPCData.sPBAPCPhoneBook.nNewMissed;
				 ptNew = p->PBAPCData.sPBAPCPhoneBook.arrNewMissedCall;
				 p->PBAPCData.sPBAPCPhoneBook.nNewMissed = 0;
#else
#endif
			}
			break;
			case  eINCOMMINGCALL:
			{
#if AUTOUPDATACALLHISTORY
				nNew = p->PBAPCData.sPBAPCPhoneBook.nNewInCome;
				ptNew = p->PBAPCData.sPBAPCPhoneBook.arrNewInComeCall;
				p->PBAPCData.sPBAPCPhoneBook.nNewInCome = 0;
#else
#endif
				n = p->PBAPCData.sPBAPCPhoneBook.nTotalIncomeCall;
				pt = p->PBAPCData.sPBAPCPhoneBook.arrIncomeCall;
				p->PBAPCData.sPBAPCPhoneBook.nTotalIncomeCall = 0;
			}
			break;
			case  eOUTGOINGCALL:
			{
#if AUTOUPDATACALLHISTORY
				nNew = p->PBAPCData.sPBAPCPhoneBook.nNewOutGoing;
				ptNew = p->PBAPCData.sPBAPCPhoneBook.arrNewOutGoingCall;
				p->PBAPCData.sPBAPCPhoneBook.nNewOutGoing = 0;
#else
#endif
				n = p->PBAPCData.sPBAPCPhoneBook.nOutGoingCall;
				pt = p->PBAPCData.sPBAPCPhoneBook.arrOutGoingCall;
				p->PBAPCData.sPBAPCPhoneBook.nOutGoingCall = 0;
			}
			break;
			case  eALLCALLRECORDS:
			{
#if AUTOUPDATACALLHISTORY
				nNew = p->PBAPCData.sPBAPCPhoneBook.nNewCallHistory;
				ptNew = p->PBAPCData.sPBAPCPhoneBook.arrNewCallHistory;
				p->PBAPCData.sPBAPCPhoneBook.nNewCallHistory = 0;
#else
#endif
				n = p->PBAPCData.sPBAPCPhoneBook.nCombinationCall;
				p->PBAPCData.sPBAPCPhoneBook.nCombinationCall = 0;
				pt = p->PBAPCData.sPBAPCPhoneBook.arrCombinationCall;
			}
			break;
			default:
			{

			}
			break;
		}
	}
	if(p != NULL)
	{
		m_pScrBoxCallRecords->DeleteAllListItems();
#if AUTOUPDATACALLHISTORY
		for(HUINT j = 0;j < nNew;j++)
		{
			/*memset(ptNew[j].szContact.szName,0,sizeof(ptNew[j].szContact.szName));
			memset(ptNew[j].szContact.szTelNumber.PhoneNumber,0,sizeof(ptNew[j].szContact.szTelNumber.PhoneNumber));
			memset(ptNew[j].szPhoneTime,0,sizeof(ptNew[j].szPhoneTime));*/
			memset(&ptNew[j],0,sizeof(ptNew[j]));
		}
#else
#endif
		if(pt != NULL)
		{
			for(HINT i = 0; i < n;i++)
			{
				memset(pt[i].szContact.szName,0,sizeof(pt[i].szContact.szName));
				memset(pt[i].szContact.szTelNumber.PhoneNumber,0,sizeof(pt[i].szContact.szTelNumber.PhoneNumber));
				memset(pt[i].szPhoneTime,0,sizeof(pt[i].szPhoneTime));
			}
		}
		//p->PBAPCData.sPBAPCPhoneBook.nCombinationCall = 0;
	}
	m_pScrCtrlCallRecords->SetValue(0);
	m_pScrCtrlCallRecords->SetBound(0,1);
	m_iScrboxCallRecords = -1;
	m_pBtnCallRecordsDelete->EnableMsg(false);
	m_pBtnCallRecordsDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
	m_pBtnCallRecordsDeleteAll->EnableMsg(false);
	m_pBtnCallRecordsDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
	m_pBtnCallRecordsDial->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_D.hfp")));
	m_pBtnCallRecordsDial->EnableMsg(false);
}
void HCBTCallRecordsDlg::UpDataRecords(bool bDowned)
{
     if(bDowned)
	 {
		 m_pBtnCallRecordsAllRecords->EnableMsg(true);
		 m_pBtnCallRecordsAllRecords->SetBkgndN(GetHMIPath(_T("Bluetooth\\Records\\Records_All_N.hfp")));
		 m_pBtnCallRecordsMissedCalls->EnableMsg(true);
		 m_pBtnCallRecordsMissedCalls->SetBkgndN(GetHMIPath(_T("Bluetooth\\Records\\Records_Missed_N.hfp")));
	 }
	 else
	 {
		 m_pBtnCallRecordsAllRecords->EnableMsg(false);
		 m_pBtnCallRecordsAllRecords->SetBkgndN(GetHMIPath(_T("Bluetooth\\Records\\Records_All_D.hfp")));
		 m_pBtnCallRecordsMissedCalls->EnableMsg(false);
		 m_pBtnCallRecordsMissedCalls->SetBkgndN(GetHMIPath(_T("Bluetooth\\Records\\Records_Missed_D.hfp")));
	 }
}

void HCBTCallRecordsDlg::DeleteAllItems()
{
   if(m_pScrBoxCallRecords != NULL)
   {
	  HINT n = m_pScrBoxCallRecords->GetListItemCount();
	  if(n > 0)
	  {
		  
		  m_pScrBoxCallRecords->DeleteAllListItems();
		  m_pScrCtrlCallRecords->SetValue(0);
		  m_pScrCtrlCallRecords->SetBound(0,1);
	  }
   }
}
void HCBTCallRecordsDlg::ClearRecordsData()
{
	if(!m_bRecordsCleared)
	{
		OnDeleteAll(NULL);
		UpDataRecords(false);
		m_bRecordsCleared = true;
	}
}
void HCBTCallRecordsDlg::AutoUpDataRecords()
{
	switch (m_eCallHistory)
	{
		case eMISSEDCALL:
		{
			OnMissedCall(NULL);
		}
		break;
		case eINCOMMINGCALL:
		{

		}
		break;
		case eOUTGOINGCALL:
		{

		}
		break;
		case eALLCALLRECORDS:
		{
			OnAllRecords(NULL);
		}
		break;
		default:
		{

		}
		break;
	}
}
void HCBTCallRecordsDlg::RequreSource()
{
	if(m_bSourceRealse == true)
	{
		EnableUpdateRect(false);
//		sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str(),eDIALOGT_BTCALLRECORDS,0);
		HCBTCallRecordsDlg::SetBTDlgBackGround();
		m_bSourceRealse = false;
		EnableUpdateRect(true);
		BTDEBUGINFO(L"HCBTCallRecordsDlg::%s",__FUNCTIONW__);
	}
}
void HCBTCallRecordsDlg::ReleaseSource()
{
	if(m_bSourceRealse == false)
	{
		EnableUpdateRect(false);
		btSource::Instance()->ReleaseBtSource(eDIALOGT_BTCALLRECORDS);
		m_bSourceRealse = true;
		EnableUpdateRect(true);
		BTDEBUGINFO(L"HCBTCallRecordsDlg::%s",__FUNCTIONW__);
	}
}