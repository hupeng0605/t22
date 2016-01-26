#include "KCBTAddressBookDialog.h"
#include "KHMIBaseHead.h"
HCBTAddressBookDlg::HCBTAddressBookDlg()
{
	m_pGrpCtrlAddressBookMiddle = NULL;
	m_pTxtAddressBookBK = NULL;
	m_pScrCtrlAddressBook = NULL;
	m_pScrBoxAddressBook = NULL;
	m_pBtnAddressBookUp = NULL;
	m_pBtnAddressBookDown = NULL;
	m_pTxtAddressBookName = NULL;
	m_pTxtAddressBookHandleBK = NULL;
	m_pBtnAddressBookDial = NULL;
	m_pBtnAddressBookDownLoad = NULL;
	m_pBtnAddressBookDelete = NULL;
	m_pBtnAddressBookDeleteAll = NULL;
	m_pGrpCtrlAddressBookNotice = NULL;
	m_pTxtDownLoading = NULL;
   //m_pTxtDownLoaded = NULL;
	m_pTxtNoticeBK = NULL;
	m_pTxtDeviceLine1 =  NULL;
	m_pTxtDeviceLine2 = NULL;
	m_pTxtDeviceLine3 = NULL;
	m_pTxtDeviceLine4 = NULL;
	m_iScrboxAddressBook = -1;
	m_nTotalConcats = 0;
	m_bDowning = false;
	m_bCleared = false;
};

HCBTAddressBookDlg::~HCBTAddressBookDlg()
{
	if(m_pScrBoxAddressBook->GetListItemCount() > 0)
	{
		m_pScrBoxAddressBook->DeleteAllListItems();
	}
	SAFE_DELETE(m_pBtnAddressBookDeleteAll);
	SAFE_DELETE(m_pBtnAddressBookDelete);
	SAFE_DELETE(m_pBtnAddressBookDownLoad);
	SAFE_DELETE(m_pBtnAddressBookDial);
	SAFE_DELETE(m_pTxtAddressBookHandleBK);
	SAFE_DELETE(m_pTxtAddressBookName);
	SAFE_DELETE(m_pBtnAddressBookDown);
	SAFE_DELETE(m_pBtnAddressBookUp);
	SAFE_DELETE(m_pScrBoxAddressBook);
	SAFE_DELETE(m_pScrCtrlAddressBook);
	SAFE_DELETE(m_pTxtAddressBookBK);
	SAFE_DELETE(m_pGrpCtrlAddressBookMiddle);
	SAFE_DELETE(m_pTxtDownLoading);
	SAFE_DELETE(m_pTxtNoticeBK);
	SAFE_DELETE(m_pGrpCtrlAddressBookNotice);
	SAFE_DELETE(m_pTxtDeviceLine1);
	SAFE_DELETE(m_pTxtDeviceLine2);
	SAFE_DELETE(m_pTxtDeviceLine3);
	SAFE_DELETE(m_pTxtDeviceLine4);
	DelTimer(&m_ctDowingTime);
	m_bCleared = false;
};
HINT HCBTAddressBookDlg::OnInit()
{
	//HINT nRet = HCBluetoothBaseDlg::OnInit();
	//m_pTxtScreen->SetText(L"通讯录");
	m_pGrpCtrlAddressBookMiddle = new HCGroupCtrl;
	if(m_pGrpCtrlAddressBookMiddle != NULL)
	{
		AddChild(m_pGrpCtrlAddressBookMiddle);
		//通讯录背景
		m_pTxtAddressBookBK = new HCImageCtrl;
		if(m_pTxtAddressBookBK != NULL)
		{
			m_pTxtAddressBookBK->Create(0,68,640,344);
			m_pTxtAddressBookBK->EnableMsg(false);
			m_pTxtDeviceLine1 = new HCTextCtrl;
			if(m_pTxtDeviceLine1 != NULL)
			{
				m_pTxtDeviceLine1->Create(72,138,526,2);
				
				m_pGrpCtrlAddressBookMiddle->AddChild(m_pTxtDeviceLine1);
			}
			m_pTxtDeviceLine2 = new HCTextCtrl;
			if(m_pTxtDeviceLine2 != NULL)
			{
				m_pTxtDeviceLine2->Create(72,204,526,2);
				m_pGrpCtrlAddressBookMiddle->AddChild(m_pTxtDeviceLine2);
			}
			m_pTxtDeviceLine3 = new HCTextCtrl;
			if(m_pTxtDeviceLine3 != NULL)
			{
				m_pTxtDeviceLine3->Create(72,270,526,2);
				m_pGrpCtrlAddressBookMiddle->AddChild(m_pTxtDeviceLine3);
			}
			m_pTxtDeviceLine4 = new HCTextCtrl;
			if(m_pTxtDeviceLine4 != NULL)
			{
				m_pTxtDeviceLine4->Create(72,336,526,2);
				m_pGrpCtrlAddressBookMiddle->AddChild(m_pTxtDeviceLine4);
			}
			m_pGrpCtrlAddressBookMiddle->AddChild(m_pTxtAddressBookBK);
		}
		//通讯录滚动列表
		m_pScrBoxAddressBook = new HCScrollBox;
		if(m_pScrBoxAddressBook != NULL)
		{
			m_pScrBoxAddressBook->Create(75,75,515,330);
			m_pScrBoxAddressBook->SetShow(true);
			m_pScrBoxAddressBook->SetCallBackClick(OnScrBoxAddressBook,this);
			//m_pScrBoxAddressBook->SetCallBackScrollEnd(OnAddressBookScrollEnd,this);
			m_pScrBoxAddressBook->SetTextColorN(255, 255, 255);//设置字体颜色
			m_pScrBoxAddressBook->SetTextColorA(255, 255, 255);//设置字体颜色
			m_pScrBoxAddressBook->SetFontSize(24, 24);
			AddChild(m_pScrBoxAddressBook);
		}
		//通讯录滑块
		m_pScrCtrlAddressBook = new HCScrollCtrl;
		if(m_pScrCtrlAddressBook != NULL)
		{
			m_pScrCtrlAddressBook->Create(596,100,28,280,1);
			m_pScrCtrlAddressBook->SetBound(0,1);
			m_pScrCtrlAddressBook->SetShow(true);
			//m_pGrpCtrlAddressBookMiddle->AddChild(m_pScrCtrlAddressBook);
			AddChild(m_pScrCtrlAddressBook);
			m_pScrCtrlAddressBook->SetScrollBox(m_pScrBoxAddressBook,5);
		}
		//m_pScrboxChannelStore->SetBkgndN(GetHMIPath(_T("Share\\Share_Function_Frame.hfp")));
		//m_pScrboxChannelStore->SetSliderSurf(GetHMIPath(_T("Radio\\Radio_Storage_A.hfp")));
		//ChannelListsAddChannel();
		//通讯录本向上按钮
		m_pBtnAddressBookUp = new HCButton;
		if(m_pBtnAddressBookUp != NULL)
		{
			m_pBtnAddressBookUp->Create(590, 74, 40, 36);
			m_pBtnAddressBookUp->EnableMsg(true);
			m_pBtnAddressBookUp->SetShow(true);
			//m_pGrpCtrlAddressBookMiddle->AddChild(m_pBtnAddressBookUp);
			AddChild(m_pBtnAddressBookUp);
		}
		//通讯录向下按钮
		m_pBtnAddressBookDown = new HCButton;
		if(m_pBtnAddressBookDown != NULL)
		{
			m_pBtnAddressBookDown->Create(590, 370, 40, 36);
			m_pBtnAddressBookDown->EnableMsg(true);
			m_pBtnAddressBookDown->SetShow(true);
			m_pBtnAddressBookDown->SetCallBack(OnNextPage,this);
			//m_pGrpCtrlAddressBookMiddle->AddChild(m_pBtnAddressBookDown);
			AddChild(m_pBtnAddressBookDown);
			m_pScrCtrlAddressBook->SetAddButton(m_pBtnAddressBookUp,m_pBtnAddressBookDown);
		}
		//姓名文本
		m_pTxtAddressBookName = new HCTextCtrl;
		if(m_pTxtAddressBookName != NULL)
		{
			m_pTxtAddressBookName->Create(0,68,80,344);
			m_pTxtAddressBookName->EnableMsg(true);
			//m_pGrpCtrlAddressBookMiddle->AddChild(m_pTxtAddressBookName);
			AddChild(m_pTxtAddressBookName);
		}
		//电话本操作背景
		m_pTxtAddressBookHandleBK = new HCTextCtrl;
		if(m_pTxtAddressBookHandleBK != NULL)
		{
			m_pTxtAddressBookHandleBK->Create(624,68,176,344);
			m_pTxtAddressBookHandleBK->EnableMsg(false);
			m_pGrpCtrlAddressBookMiddle->AddChild(m_pTxtAddressBookHandleBK);
		}
		//拨打按钮
		m_pBtnAddressBookDial = new HCButton;
		if(m_pBtnAddressBookDial != NULL)
		{
			m_pBtnAddressBookDial->Create(636,75, 152, 64);
			m_pBtnAddressBookDial->EnableMsg(false);
			m_pBtnAddressBookDial->SetTextStyle(RE_TS_CENTER);
			m_pBtnAddressBookDial->SetTextPos(103 ,31);
			m_pBtnAddressBookDial->SetFontSize(24,24);
			//m_pBtnAddressBookDial->SetText(_T("拨打"));
			m_pBtnAddressBookDial->SetCallBack(OnCall,this);
			m_pGrpCtrlAddressBookMiddle->AddChild(m_pBtnAddressBookDial);
		}
		//下载电话本按钮
		m_pBtnAddressBookDownLoad = new HCButton;
		if(m_pBtnAddressBookDownLoad != NULL)
		{
			m_pBtnAddressBookDownLoad->Create(636,142, 152, 64);
			m_pBtnAddressBookDownLoad->EnableMsg(true);
			m_pBtnAddressBookDownLoad->SetTextStyle(RE_TS_CENTER);
			m_pBtnAddressBookDownLoad->SetTextPos(103 ,31);
			m_pBtnAddressBookDownLoad->SetFontSize(24,24);
			m_pBtnAddressBookDownLoad->SetTextColorA(255,255,255);
			m_pBtnAddressBookDownLoad->SetTextColorN(255,255,255);
			m_pBtnAddressBookDownLoad->SetTextColorS(255,255,255);
			//m_pBtnAddressBookDownLoad->SetText(_T("下载"));
			m_pBtnAddressBookDownLoad->SetCallBack(OnDownLoad,this);
			m_pGrpCtrlAddressBookMiddle->AddChild(m_pBtnAddressBookDownLoad);
		}
		//删除按钮
		m_pBtnAddressBookDelete = new HCButton;
		if(m_pBtnAddressBookDelete != NULL)
		{
			m_pBtnAddressBookDelete->Create(636,208, 152, 64);
			m_pBtnAddressBookDelete->EnableMsg(false);
			m_pBtnAddressBookDelete->SetTextStyle(RE_TS_CENTER);
			m_pBtnAddressBookDelete->SetTextPos(103 ,31);
			m_pBtnAddressBookDelete->SetFontSize(24,24);
		//	m_pBtnAddressBookDelete->SetText(_T("删除"));
			m_pBtnAddressBookDelete->SetCallBack(OnDelete,this);
			m_pGrpCtrlAddressBookMiddle->AddChild(m_pBtnAddressBookDelete);
		}
		//全部删除按钮
		m_pBtnAddressBookDeleteAll = new HCButton;
		if(m_pBtnAddressBookDeleteAll != NULL)
		{
			m_pBtnAddressBookDeleteAll->Create(636,274, 152, 64);
			m_pBtnAddressBookDeleteAll->EnableMsg(false);
			m_pBtnAddressBookDeleteAll->SetCallBack(OnDeleteAll,this);
			m_pBtnAddressBookDeleteAll->SetTextStyle(RE_TS_CENTER);
			m_pBtnAddressBookDeleteAll->SetTextPos(103 ,31);
			m_pBtnAddressBookDeleteAll->SetFontSize(24,24);
			//m_pBtnAddressBookDeleteAll->SetText(_T("全部删除"));
			m_pGrpCtrlAddressBookMiddle->AddChild(m_pBtnAddressBookDeleteAll);
		}
	}
	m_pGrpCtrlAddressBookNotice = new HCGroupCtrl;
	if(m_pGrpCtrlAddressBookNotice != NULL)
	{
		m_pGrpCtrlAddressBookNotice->Create(160,140,500,220);
		
		AddChild(m_pGrpCtrlAddressBookNotice);
		m_pTxtNoticeBK = new HCTextCtrl;
		if(m_pTxtNoticeBK != NULL)
		{
			m_pTxtNoticeBK->Create(370,250,56,56);
			m_pTxtNoticeBK->EnableMsg(false);
			m_pGrpCtrlAddressBookNotice->AddChild(m_pTxtNoticeBK);
		}	
		m_pTxtDownLoading = new HCTextCtrl;
		if(m_pTxtDownLoading != NULL)
		{
			m_pTxtDownLoading->Create(240,205,320,30);
			m_pTxtDownLoading->SetFontSize(24,24);
			m_pTxtDownLoading->SetTextStyle(RE_TS_CENTER);
			m_pTxtDownLoading->SetTextPos(160,15);
			m_pTxtDownLoading->EnableMsg(false);
			m_pTxtDownLoading->SetTxtColor(255,255,255);
			//m_pTxtDownLoading->SetText(L"下载中请稍后……");
			m_pGrpCtrlAddressBookNotice->AddChild(m_pTxtDownLoading);
		}
	
		/*m_pTxtDownLoaded = new HCTextCtrl;
		if(m_pTxtDownLoaded != NULL)
		{
			m_pTxtDownLoaded->Create(240,240,300,30);
			m_pTxtDownLoaded->SetFontSize(24,24);
			m_pTxtDownLoaded->EnableMsg(false);
			m_pTxtDownLoaded->SetTxtColor(255,255,255);
			m_pTxtDownLoaded->SetText(L"已下载100条记录");
			m_pGrpCtrlAddressBookNotice->AddChild(m_pTxtDownLoaded);
		}*/
	}
	HINT nRet = HCBluetoothBaseDlg::OnInit();
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
	//ChangeLangue(0);
	//SetBTDlgBackGround();
	 m_nContactDown = 0;
	 m_nAllRecordsDown = 0;
	m_ctUpdataLetter.SetCallBack(UpdataNameLetter,this);
	AddTimer(&m_ctUpdataLetter);
	m_ctDowingTime.SetCallBack(OnDowingTimer,this);
	AddTimer(&m_ctDowingTime);
	m_nDowningTime = 0;
	m_iScrboxAddressBook = -1;
	m_nTotalConcats = 0;
	m_bDowning = false;
	if(m_pGrpCtrlAddressBookNotice != NULL)
	{
		m_pGrpCtrlAddressBookNotice->SetShow(false);
	}
	m_nBeg = -1;
	//	m_ePBAPCstate = ePBAPCSTATEUNCONNECT;
	SetShow(true);
	UpdataNameLetter(NULL);
	return nRet;
}

void HCBTAddressBookDlg::SetBTDlgBackGround()
{
		EnableUpdateRect(false);
		HCBluetoothBaseDlg::SetBTDlgBackGround();
		HCBluetoothBaseDlg::SetBTABBK();
		 sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
		 if(pSource != NULL)
		 {
			m_pTxtAddressBookBK->SetBkgndN(pSource->m_pbtBkLeft);
			m_pTxtAddressBookBK->SetOpacity(8);
		    m_pTxtDeviceLine1->SetBkgndN(pSource->m_pbtLine);
			m_pTxtDeviceLine2->SetBkgndN(pSource->m_pbtLine);
			m_pTxtDeviceLine3->SetBkgndN(pSource->m_pbtLine);
			m_pTxtDeviceLine4->SetBkgndN(pSource->m_pbtLine);
			m_pBtnAddressBookDown->SetBkgndN(pSource->m_pbtDownN);
			m_pBtnAddressBookDown->SetBkgndA(pSource->m_pbtDownA);
			m_pBtnAddressBookUp->SetBkgndN(pSource->m_pbtUpN);
			m_pBtnAddressBookUp->SetBkgndA(pSource->m_pbtUpA);
			m_pScrCtrlAddressBook->SetBkgndN(pSource->m_pbtBarN);
			m_pScrCtrlAddressBook->SetBkgndA(pSource->m_pbtBarA);
			m_pScrCtrlAddressBook->SetBkgndD(pSource->m_pbtBarD);
			m_pScrCtrlAddressBook->SetBkgndF(pSource->m_pbtBarF);
			m_pTxtAddressBookHandleBK->SetBkgndN(pSource->m_pbtBkRight);
			m_pTxtNoticeBK->SetBkgndN(NULL);
		 }
         //m_pBtnAdressBook->SetBkgndA(pSource->m_pbtBaseAddressbookA);
		//通讯录背景
		m_pScrBoxAddressBook->EnableScrollLine(true,66,NULL/*pSource->m_pbtLine*/);
		//通讯录滑块
		//m_pScrCtrlAddressBook->SetBkgndN(GetHMIPath(_T("Share\\Share_Slide_N.hfp")));
		//m_pScrCtrlAddressBook->SetBkgndA(GetHMIPath(_T("Share\\Share_Slide_Bar.hfp")));
		//m_pScrCtrlAddressBook->SetBkgndD(GetHMIPath(_T("Share\\Share_Slide_A.hfp")));
		////m_pScrCtrlAddressBook->SetBkgndF(GetHMIPath(_T("Share\\Share_Slide_A.hfp")));
		//m_pScrCtrlAddressBook->SetBkgndF(GetHMIPath(_T("Share\\Share_Slide_Bar.hfp")));
		////通讯录向上按钮
		//m_pBtnAddressBookUp->SetBkgndN(GetHMIPath(_T("Share\\Share_Front_N.hfp")));
		//m_pBtnAddressBookUp->SetBkgndA(GetHMIPath(_T("Share\\Share_Front_A.hfp")));
		////通讯录向下按钮
		//m_pBtnAddressBookDown->SetBkgndN(GetHMIPath(_T("Share\\Share_Last_N.hfp")));
		//m_pBtnAddressBookDown->SetBkgndA(GetHMIPath(_T("Share\\Share_Last_A.hfp")));
		//通讯录姓名背景
		UpdataNameLetter(NULL);
		//m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_A.hfp")));
		//电话本操作背景
		m_pGrpCtrlAddressBookNotice->SetBackGround(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Info_Frame.hfp")));
		//拨打按钮
		//m_pBtnAddressBookDial->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_D.hfp")));
		m_pBtnAddressBookDial->SetBkgndA(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_A.hfp")));
		//下载电话本按钮
		m_pBtnAddressBookDownLoad->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_Download_N.hfp")));
		m_pBtnAddressBookDownLoad->SetBkgndA(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_Download_A.hfp")));
		//删除按钮
		if(m_iScrboxAddressBook >= 0)
		{
			m_pBtnAddressBookDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_N.hfp")));
			m_pBtnAddressBookDial->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_N.hfp")));
		}
		else
		{
			m_pBtnAddressBookDial->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_D.hfp")));
			m_pBtnAddressBookDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
		}
		
		m_pBtnAddressBookDelete->SetBkgndA(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_A.hfp")));
		//全部删除按钮
		if(m_pScrBoxAddressBook->GetListItemCount() > 0)
		{
             m_pBtnAddressBookDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_N.hfp")));
		}
		else
		{
			m_pBtnAddressBookDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
		}
		m_pBtnAddressBookDeleteAll->SetBkgndA(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_A.hfp")));
		EnableUpdateRect(false);
		//提示背景
}
void HCBTAddressBookDlg::OnCall(void* pDlg, void* param)
{
	HCBTAddressBookDlg* pObj = (HCBTAddressBookDlg*)pDlg;
	pObj->OnCall(pObj);
}
void HCBTAddressBookDlg::OnCall(void* pDlg)
{
	//HBYTE cCommand[50] = {0};
	//memset(cCommand,0,sizeof(cCommand));
	//HINT nCmdlen = strlen("AT+PBDOWN=1\r\n");
	//strncpy((char*)cCommand,"AT+PBDOWN=1\r\n",nCmdlen);
	//CBTCommand::Instance()->SendData(cCommand,nCmdlen);
	////CBTCommand::Instance()->GetBTCommandData()->PBAPCData.ePBAPCState = ePBAPCSTATEDOWNINGBOOK;
	//CBTCommand::Instance()->SetPBDACState(ePBAPCSTATEDOWNINGBOOK);
	HCListItemBase *pListItemSelect = m_pScrBoxAddressBook->GetSelectListItem();
	HINT iSelectIndex = -1; 
	if(pListItemSelect != NULL && s_bDailing == false)
	{
		iSelectIndex = m_pScrBoxAddressBook->GetListItemIndex(pListItemSelect);
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
				CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHIDCUSendDataToHID,pBlock);
			}
#else
			CBTCommand::Instance()->SendData(cCommand,nCmdLen + nwLen +1);
#endif
		}
	}
}

void HCBTAddressBookDlg::OnAddressBookScrollEnd(void* pDlg, HBOOL bScrollUp)
{
	HCBTAddressBookDlg* pObj = (HCBTAddressBookDlg*)pDlg;
	pObj->OnAddressBookScrollEnd(bScrollUp);
}
void HCBTAddressBookDlg::OnAddressBookScrollEnd(HBOOL bScrollUp)
{
	BTDEBUGINFO(L"OnAddressBookScrollEnd");
}
void HCBTAddressBookDlg::OnNextPage(void* pDlg, void* param)
{
	HCBTAddressBookDlg* pObj = (HCBTAddressBookDlg*)pDlg;
	pObj->OnNextPage(pObj);
}
void HCBTAddressBookDlg::OnNextPage(void* pDlg)
{
  BTDEBUGINFO(L"nextPage");
}
void HCBTAddressBookDlg::OnDownLoad(void* pDlg, void* param)
{
	HCBTAddressBookDlg* pObj = (HCBTAddressBookDlg*)pDlg;
	pObj->OnDownLoad(pObj);
}
void HCBTAddressBookDlg::OnDownLoad(void* pDlg)
{
	HBYTE cCommand[50] = {0};
	HUINT nCmdlen =0;
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	HINT nState = 0;
	if(p != NULL)
	{
		nState = p->PBAPCData.ePBAPCState;
	}
	if(m_bDowning == false)
	{
		//CBTCommand::Instance()->SetPBDACState(ePBAPCSTATEDOWNINGOUTGOINGCALL);
		CBTCommand::Instance()->SetPBDACState(ePBAPCSTATEDOWNINGBOOK);
		if(nState < 2)
		{
#ifdef  TESTBTCOMMANDQUEUE
			CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketPBAPCSetUpPBAPConnection,NULL);
#else
			nCmdlen = strlen("AT+PBCONN\r\n");
			memset(cCommand,0,50);
			strncpy((char*)cCommand,"AT+PBCONN\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
		}
		else if(nState == 2)
		{
#ifdef  TESTBTCOMMANDQUEUE
			CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketPBAPCAquirePBAPCState,NULL);
#else
			nCmdlen = strlen("AT+PBSTAT\r\n");
			memset(cCommand,0,50);
			strncpy((char*)cCommand,"AT+PBSTAT\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
		}
	//	m_pBtnAddressBookDownLoad->SetText(L"取消");
		StartDown();
		m_pBtnAddressBookDownLoad->SetText(s_pLan[13]);
		m_bDowning = true;
	}
	else
	{
		//CBTCommand::Instance()->SetPBDACState(ePBAPCSTATEDOWNINGBOOK);
		if(nState == 3)
		{
#ifdef  TESTBTCOMMANDQUEUE
			CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketPBAPCCancelDownPhoneBook,NULL);
#else
			nCmdlen = strlen("AT+PBABORT\r\n");
			memset(cCommand,0,50);
			strncpy((char*)cCommand,"AT+PBABORT\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
		}
        Sleep(5);
		nState = p->PBAPCData.ePBAPCState;
		if(nState > 0)
		{
#ifdef  TESTBTCOMMANDQUEUE
			CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketPBAPCDisconnectPBAP,NULL);
#else
			nCmdlen = strlen("AT+PBDISC\r\n");
			memset(cCommand,0,50);
			strncpy((char*)cCommand,"AT+PBDISC\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
		}
	//	m_pBtnAddressBookDownLoad->SetText(L"下载");
		m_pBtnAddressBookDownLoad->SetText(s_pLan[6]);
		m_bDowning = false;
		if(m_ctDowingTime.IsActive())
		{
			m_ctDowingTime.StopTimer();
		}
		m_pGrpCtrlAddressBookNotice->SetShow(false);
	}
	//cCommand  [50] = {0};
	//Sleep(500);
	//memset(cCommand,0,sizeof(cCommand));
	// nCmdlen = strlen("AT+PBDOWN=1\r\n");
	//strncpy((char*)cCommand,"AT+PBDOWN=1\r\n",nCmdlen);
	//CBTCommand::Instance()->SendData(cCommand,nCmdlen);
}
void HCBTAddressBookDlg::OnDelete(void* pDlg, void* param)
{
	HCBTAddressBookDlg* pObj = (HCBTAddressBookDlg*)pDlg;
	pObj->OnDelete(pObj);
}
void HCBTAddressBookDlg::OnDelete(void* pDlg)
{
	/*HBYTE cCommand[50] = {0};
	HUINT nCmdlen = strlen("AT+SLDN=BTforHP\r\n");
	strncpy((char*)cCommand,"AT+SLDN=BTforHP\r\n",nCmdlen);
	CBTCommand::Instance()->SendData(cCommand,nCmdlen);*/
	if(m_iScrboxAddressBook >= 0)
	{
		HCListItemBase *pListItemSelect =m_pScrBoxAddressBook->GetItemAt(m_iScrboxAddressBook);
		if(pListItemSelect != NULL)
		{
			m_pScrBoxAddressBook->DeleteListItem(pListItemSelect);
			sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
			if(p != NULL)
			{
				HUINT nTotal = p->PBAPCData.sPBAPCPhoneBook.nTotalContact;
				if(nTotal > 0)
				{
					sContact *pt = p->PBAPCData.sPBAPCPhoneBook.arrContact;
					if(pt != NULL && nTotal > (m_iScrboxAddressBook + 1))
					{
						memset(p->PBAPCData.sPBAPCPhoneBook.arrContact[m_iScrboxAddressBook].szName,0,sizeof(p->PBAPCData.sPBAPCPhoneBook.arrContact[m_iScrboxAddressBook].szName));
						memset(p->PBAPCData.sPBAPCPhoneBook.arrContact[m_iScrboxAddressBook].szTelNumber.PhoneNumber,0,sizeof(p->PBAPCData.sPBAPCPhoneBook.arrContact[m_iScrboxAddressBook].szTelNumber.PhoneNumber));
						for(HINT i = m_iScrboxAddressBook + 1; i < nTotal; i++)
						{
							memcpy(pt[i-1].szName,pt[i].szName,sizeof(pt[i].szName));
							memcpy(pt[i-1].szName,pt[i].szTelNumber.PhoneNumber,sizeof(pt[i].szTelNumber.PhoneNumber));
						}
						memset(pt[nTotal-1].szName,0,sizeof(pt[nTotal-1].szName));
						memset(pt[nTotal-1].szTelNumber.PhoneNumber,0,sizeof(pt[nTotal-1].szTelNumber.PhoneNumber));
					}
					p->PBAPCData.sPBAPCPhoneBook.nTotalContact -= 1;
					m_nTotalConcats = p->PBAPCData.sPBAPCPhoneBook.nTotalContact;
					NameListGroup* pNameGrp = CBTCommand::Instance()->GetNameListGrpp();
					HINT iResult = CBTCommand::Instance()->GetLetterFromNameGrp(m_iScrboxAddressBook,CBTCommand::Instance()->GetNameListGrp());
					if(iResult >= 0 && iResult <= 26)
					{
						if(pNameGrp->szCount[iResult] > 0)
						{
							pNameGrp->szCount[iResult]--;
						}
						if(pNameGrp->szTotalCount[iResult] > 0)
						{
							pNameGrp->szTotalCount[iResult]--;
						}
						CBTCommand::Instance()->TotalCountNameGrp((*pNameGrp),iResult,26);
						if(pNameGrp->nTotalContact > 0)
						{
							pNameGrp->nTotalContact--;
						}
					}
					BTDEBUGINFO(L"count[iResult] = %d,Totalcount[iResult] = %d,iResult = %d",pNameGrp->szCount[iResult],pNameGrp->szTotalCount[iResult],iResult);
					m_iScrboxAddressBook = -1;
					m_pBtnAddressBookDelete->EnableMsg(false);
					m_pBtnAddressBookDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
					m_pBtnAddressBookDial->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_D.hfp")));
					m_pBtnAddressBookDial->EnableMsg(false);
					if(m_nTotalConcats > 0)
					{
						m_pBtnAddressBookDeleteAll->EnableMsg(true);
						m_pBtnAddressBookDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_N.hfp")));
						//m_pScrCtrlAddressBook->SetBound(0,(m_nTotalConcats-1)/6);
					}
					else
					{
						m_pBtnAddressBookDeleteAll->EnableMsg(false);
						m_pBtnAddressBookDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
					//	m_pScrCtrlAddressBook->SetBound(0,1);
					}
				}
			}
		}
	}
}
void HCBTAddressBookDlg::OnDeleteAll(void* pDlg, void* param)
{
	HCBTAddressBookDlg* pObj = (HCBTAddressBookDlg*)pDlg;
	pObj->OnDeleteAll(pObj);
}
void HCBTAddressBookDlg::OnDeleteAll(void* pDlg)
{
	/*HBYTE cCommand[50] = {0};
	HUINT nCmdlen = strlen("AT+GLDN\r\n");
	strncpy((char*)cCommand,"AT+GLDN\r\n",nCmdlen);
	CBTCommand::Instance()->SendData(cCommand,nCmdlen);*/
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	HUINT nTotal = p->PBAPCData.sPBAPCPhoneBook.nTotalContact;
	if(p != NULL )
	{
		m_pScrBoxAddressBook->DeleteAllListItems();
		sContact *pt = p->PBAPCData.sPBAPCPhoneBook.arrContact;
		if(pt != NULL)
		{
			for(HINT i = 0; i < nTotal;i++)
			{
				memset(pt[i].szName,0,sizeof(pt[i].szName));
				memset(pt[i].szTelNumber.PhoneNumber,0,sizeof(pt[i].szTelNumber.PhoneNumber));
			}
		}
		p->PBAPCData.sPBAPCPhoneBook.nTotalContact = 0;
	}
	m_pScrCtrlAddressBook->SetValue(0);
	m_pScrCtrlAddressBook->SetBound(0,1); 
	m_iScrboxAddressBook = -1;
	m_nTotalConcats = 0;
	m_pBtnAddressBookDial->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_D.hfp")));
	m_pBtnAddressBookDial->EnableMsg(false);
	m_pBtnAddressBookDelete->EnableMsg(false);
	m_pBtnAddressBookDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
	m_pBtnAddressBookDeleteAll->EnableMsg(false);
	m_pBtnAddressBookDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
}

void HCBTAddressBookDlg::OnDowingTimer(void* pDlg, void* param)
{
	HCBTAddressBookDlg* pObj = (HCBTAddressBookDlg*)pDlg;
	pObj->OnDowingTimer(pObj);
}
void HCBTAddressBookDlg::StartDown()
{
	if(m_ctDowingTime.IsActive())
	{
		m_ctDowingTime.StopTimer();
	}
	m_pTxtNoticeBK->SetBkgndN(NULL);
	if(s_pLan != NULL)
	{
		m_pTxtDownLoading->SetText(s_pLan[37]);
	}
	m_nContactDown = 0;
	m_nAllRecordsDown = 0;
	if(!m_pGrpCtrlAddressBookNotice->IsShow())
	{
		m_pGrpCtrlAddressBookNotice->SetShow(true);
	}
}
void HCBTAddressBookDlg::OnDowingTimer(void* pDlg)
{  
	if(m_ctDowingTime.IsActive())
	{
		m_ctDowingTime.StopTimer();
	}
	m_ctDowingTime.SetTime(35);
	//m_ctDowingTime.StartTimer();
	/*wchar_t szTemp[50] = {0};
	wsprintf(szTemp,L"%s%d",s_pLan[18],);*/
	m_pTxtDownLoading->SetText(s_pLan[18]);
	 sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
	 if(pSource != NULL)
	 {
		 switch (m_nDowningTime)
		 {
		 case 0:
			 {
			
				 m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[0]);
			 }
			 break;
		 case 1:
			 {
				 m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[3]);
			 }
			 break;
		 case 2:
			 {
				 m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[6]);
			 }
			 break;
		 case 3:
			 {
				 m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[9]);
			 }
			 break;
		 case 4:
			 {
				 m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[4]);
			 }
			 break;
		 case 5:
			 {
				 m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[5]);
			 }
			 break;
		 case 6:
			 {
				 m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[6]);
			 }
			 break;
		 case 7:
			 {
				 m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[7]);
			 }
			 break;
		 case 8:
			 {
				 m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[8]);
			 }
			 break;
		 case 9:
			 {
				 m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[9]);
			 }
			 break;
		 case 10:
			 {
				 m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[10]);
			 }
			 break;
		 case 11:
			 {
				 m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[11]);
			 }
			 break;
		 default:
			 break;
	 }
	
	}
	m_nDowningTime++;
	m_nDowningTime %= 4;
	if(!m_pGrpCtrlAddressBookNotice->IsShow())
	{
		m_pGrpCtrlAddressBookNotice->SetShow(true);
	}
	// BTDEBUGINFO(L"Costtime = %d",GetTickCount() - nowtime);
}
 void HCBTAddressBookDlg::OnScrBoxAddressBook(void* pDlg, void* param)
{
	HCBTAddressBookDlg* pObj = (HCBTAddressBookDlg*)pDlg;
	pObj->OnScrBoxAddressBook(pObj);
}

void HCBTAddressBookDlg::OnScrBoxAddressBook(void* pDlg)
{
	HCListItemBase *pListItemSelect = m_pScrBoxAddressBook->GetSelectListItem();
	HINT iSelectIndex = -1;
	if(pListItemSelect != NULL)
	{
		 iSelectIndex = m_pScrBoxAddressBook->GetListItemIndex(pListItemSelect);
	}
	if(m_iScrboxAddressBook == iSelectIndex)
	{
		OnCall(this);
	}
	else 
	{
		m_iScrboxAddressBook = iSelectIndex;
	}
	if(m_iScrboxAddressBook >= 0)
	{
		m_pScrBoxAddressBook->SetSelectListItem(m_iScrboxAddressBook, false);
		m_pBtnAddressBookDial->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_N.hfp")));
		m_pBtnAddressBookDial->EnableMsg(true);
		m_pBtnAddressBookDelete->EnableMsg(true);
		m_pBtnAddressBookDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_N.hfp")));
		m_pBtnAddressBookDeleteAll->EnableMsg(true);
		m_pBtnAddressBookDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_N.hfp")));

	}
	else
	{
		m_pBtnAddressBookDelete->EnableMsg(false);
		m_pBtnAddressBookDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
		m_pBtnAddressBookDial->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Answer_D.hfp")));
		m_pBtnAddressBookDial->EnableMsg(false);
	}
}
HCListItem* HCBTAddressBookDlg::CreatContactItem(HCHAR *pName,HCHAR *pPhoneNumber)
{
	if(pPhoneNumber != NULL && pName != NULL)
	{
		HCHAR pTemp[50] ;
		memset(pTemp,0,sizeof(pTemp));
		HCListItem* pTempListItemContact = new HCListItem;
		//mbstowcs(pTemp,(char*)pName,30) ;
		//wcsncpy(pTemp,pName,10);
		////memcpy(pTemp,pName,10);
		//for(HINT i = 0;i<= 10;i++)
		//{
		//	if(pTemp[i] == (L'\0') )
		//	{
		//		pTemp[i] = L' ';
		//	}
		//}
		//wcsncpy(pTemp+10,pPhoneNumber,30);
		////memcpy(pTemp+10,pPhoneNumber,30);
		//pTemp[41] =L'\0';
		HCTextCtrl *p= new HCTextCtrl;
		p->Create(0,0,230,66);
		memset(pTemp,0,sizeof(pTemp));
		wcsncpy(pTemp,pName,10);
		p->SetText(pTemp);
		p->SetTextPos(0,18);
		p->SetFontSize(24,24);
		p->SetTxtColor(255,255,255);
		p->EnableMsg(false);
		p->SetRoll(true);
		p->SetRollWidth(180);
		//p->SetTextStyle()
		pTempListItemContact->AddBaseCtrl((HCBaseCtrl*)p);

		HCTextCtrl *pp= new HCTextCtrl;
		pp->Create(240,0,300,66);
		memset(pTemp,0,sizeof(pTemp));
		wcsncpy(pTemp,pPhoneNumber,30);
		pp->SetText(pTemp);
		pp->SetTextPos(0,18);
		pp->SetFontSize(24,24);
		pp->EnableMsg(false);
		pp->SetTxtColor(255,255,255);
		pp->SetRoll(true);
		pp->SetRollWidth(280);
		pTempListItemContact->AddBaseCtrl((HCBaseCtrl*)pp);
		pTempListItemContact->Create(515 , 66, NULL, NULL);
		pTempListItemContact->SetEnableRoll(true, 1);
		pTempListItemContact->SetFontPos(5);
		//pTempListItemContact->SetRollWidth(400);
	    //pTempListItemContact->SetIcon(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Frame_N.hfp")));
		//	pTempListItemContact->SetIconPos(0,2);
		//pTemp[30] =L'0';
		//pTempListItemContact->SetText(pTemp);
		pTempListItemContact->SetCanFocus(true);
		 sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
		 if(pSource != NULL)
		 {
			 pTempListItemContact->SetBkgndA(pSource->m_pbtItemSelected);
			 pTempListItemContact->SetBkgndF(pSource->m_pbtItemSelected);
		 }
		
		return pTempListItemContact;
	}
	return NULL;
}

void HCBTAddressBookDlg::AddAddressBookItem(void)
{
	//HCHAR *pTemp = new HCHAR [31];
	CBTCommand::Instance()->TotalCountNameGrp(CBTCommand::Instance()->GetNameListGrp());
	NameListGroup pp ;
	//memset(&pp,0,sizeof(pp));
	pp = CBTCommand::Instance()->GetNameListGrp();
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	if(p != NULL)
	{
		HUINT ntotalnum = pp.nTotalContact;//p->PBAPCData.sPBAPCPhoneBook.nTotalContact;
		m_nTotalConcats = ntotalnum;
		m_pScrBoxAddressBook->DeleteAllListItems();
		m_pScrCtrlAddressBook->SetValue(0);
		m_pScrCtrlAddressBook->SetBound(0,1);
	/*if(ntotalnum > 0)
	{
		if(m_ePBAPCstate == ePBAPCSTATECONNECTED)
		{
			m_pScrBoxAddressBook->DeleteAllListItems();
			m_nTotalConcats = 0;
		}
		else if(m_ePBAPCstate == ePBAPCSTATEDOWNING)
		{
			for(HUINT i = 0;i < ntotalnum;i++)
			{
				HCListItemBase *pItem = CreatContactItem(CBTCommand::Instance()->GetBTCommandData()->PBAPCData.sPBAPCPhoneBook.arrContact[i].szName,CBTCommand::Instance()->GetBTCommandData()->PBAPCData.sPBAPCPhoneBook.arrContact[i].szTelNumber.PhoneNumber);
				m_pScrBoxAddressBook->AddListItem(pItem);
			}
		}
	}
	m_ePBAPCstate = CBTCommand::Instance()->GetBTCommandData()->PBAPCData.ePBAPCState;*/
		if(ntotalnum > 0)
		{
			m_pScrCtrlAddressBook->SetBound(0,(ntotalnum-1)/5);
		/*	for(HUINT i = 0;i < ntotalnum;i++)
			{
				HCListItemBase *pItem = CreatContactItem(p->PBAPCData.sPBAPCPhoneBook.arrContact[i].szName,p->PBAPCData.sPBAPCPhoneBook.arrContact[i].szTelNumber.PhoneNumber);
				m_pScrBoxAddressBook->AddListItem(pItem);
				m_pBtnAddressBookDeleteAll->EnableMsg(true);
				m_pBtnAddressBookDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_N.hfp")));
			}*/
			for(int i = 0;i < 27;i++)
			{
				if(!(pp.pContact[i]).empty())
				{
					NameList::iterator itbeg = (pp.pContact[i]).begin();
					NameList::iterator itend = (pp.pContact[i]).end();
					NameList::iterator it = itbeg;
					for( it = itbeg ;it != itend;it++)
					{
						//if((pp.pContact[i]).at(j) != NULL)
						//{
							//HCListItemBase *pItem = CreatContactItem(p->PBAPCData.sPBAPCPhoneBook.arrContact[i].szName,p->PBAPCData.sPBAPCPhoneBook.arrContact[i].szTelNumber.PhoneNumber);
							HCListItemBase *pItem = CreatContactItem((*it)->szName,(*it)->szTelNumber.PhoneNumber);
							m_pScrBoxAddressBook->AddListItem(pItem);
						//}		
					}
				}
			}
			m_pBtnAddressBookDeleteAll->EnableMsg(true);
			m_pBtnAddressBookDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_N.hfp")));
			m_bCleared = false;
		}
		else
		{
			m_pBtnAddressBookDeleteAll->EnableMsg(false);
			m_pBtnAddressBookDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
			m_pScrCtrlAddressBook->SetBound(0,1);
		}
	
	}
	m_pScrBoxAddressBook->SetShow(true);
}
void HCBTAddressBookDlg::SetNotice(ePBAPCSTATE eState)
{
	HUINT nTotal= 0;
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	if(p != NULL)
	{
		switch (eState)
		{
			case ePBAPCSTATEDOWNINGBOOK:
			{
				m_pTxtDownLoading->SetText(L"正在下载电话本");
				nTotal = p->PBAPCData.sPBAPCPhoneBook.nTotalContact;
			}
			break;
			case ePBAPCSTATEDOWNINGINCOMMINGCALL:
			{
				m_pTxtDownLoading->SetText(L"正在下载来电记录");
				nTotal = p->PBAPCData.sPBAPCPhoneBook.nTotalIncomeCall;
			}
			break;
			case ePBAPCSTATEDOWNINGOUTGOINGCALL:
			{
				m_pTxtDownLoading->SetText(L"正在下载已拨电话记录");
				nTotal = p->PBAPCData.sPBAPCPhoneBook.nTotalIncomeCall;
			}
			break;
			case ePBAPCSTATEDOWNINGMISSEDCALL:
			{
				m_pTxtDownLoading->SetText(L"正在下载未接电话记录");
				nTotal = p->PBAPCData.sPBAPCPhoneBook.nTotalMissedCall;
			}
			break;
			case ePBAPCSTATEDOWNINGCALLHISTORY:
			{
				m_pTxtDownLoading->SetText(L"正在下载全部通话记录");
				nTotal = p->PBAPCData.sPBAPCPhoneBook.nCombinationCall;
			}
			break;
			default:
			{

			}
			break;
		}
		HCHAR szTxt[20] = {0};
		wsprintf(szTxt,L"已下载%d条记录",nTotal);
//		m_pTxtDownLoaded->SetText(szTxt);
		SetNoticeShow(true);
	}
}

void HCBTAddressBookDlg::SetNoticeShow(bool bShow)
{
	if(m_pGrpCtrlAddressBookNotice != NULL)
	{
		m_pGrpCtrlAddressBookNotice->SetShow(bShow);
	}
	if(bShow)
	{
		//m_pBtnAddressBookDownLoad->EnableMsg(false);
		m_bDowning = true;
	}
	else
	{
		if(m_ctDowingTime.IsActive())
		{
			m_ctDowingTime.StopTimer();
		}
		m_nDowningTime = 0;
		m_pBtnAddressBookDownLoad->EnableMsg(true);
		//m_pBtnAddressBookDownLoad->SetText(L"下载");
		m_pBtnAddressBookDownLoad->SetText(s_pLan[6]);
		m_bDowning = false;
	}
}
void  HCBTAddressBookDlg::DeleteAllItems()
{
	if(m_pScrBoxAddressBook != NULL)
	{
		HINT n = m_pScrBoxAddressBook->GetListItemCount();
		if(n >0)
		{
			m_pScrBoxAddressBook->DeleteAllListItems();
			m_pScrCtrlAddressBook->SetValue(0);
			m_pScrCtrlAddressBook->SetBound(0,1);
		}
	}
}
void HCBTAddressBookDlg::ClearBookData()
{
	if(!m_bCleared)
	{
		if(m_bDowning)
		{
			OnDownLoad(NULL);
		}
		OnDeleteAll(NULL);
		m_bCleared = true;
	}
}
void HCBTAddressBookDlg::ClearBookDataEx()
{
	OnDeleteAll(NULL);
	m_bCleared = true;
}
void HCBTAddressBookDlg::ChangeLangue(HINT nType)
{
	//SetLangue(nType);
	HCBluetoothBaseDlg::ChangeLangue(nType);
	if(s_pLan != NULL)
	{
		BTDEBUGINFO(L"HCBTAddressBookDlg::%s,%d",__FUNCTIONW__,nType);
		switch (nType)
		{
			case 0:
			{
				m_pBtnAddressBookDial->SetFontSize(24,24);
				m_pBtnAddressBookDownLoad->SetFontSize(24,24);
				m_pBtnAddressBookDelete->SetFontSize(24,24);
				m_pBtnAddressBookDeleteAll->SetFontSize(24,24);
				m_pTxtDownLoading->SetFontSize(24,24);
				for (size_t i=0;i<(sizeof(m_pTxt_Popup_Infor)/sizeof(m_pTxt_Popup_Infor[0]));i++)
				{
					//m_pTxt_Popup_Infor[i] = new HCTextCtrl;
					if( NULL != m_pTxt_Popup_Infor[i] )
					{
						m_pTxt_Popup_Infor[i]->SetFontSize(24,24);
					}
				}
			}
			break;
			case 1:
			{
				m_pBtnAddressBookDial->SetFontSize(18,18);
				m_pBtnAddressBookDownLoad->SetFontSize(18,18);
				m_pBtnAddressBookDelete->SetFontSize(18,18);
				m_pBtnAddressBookDeleteAll->SetFontSize(18,18);
				m_pTxtDownLoading->SetFontSize(18,18);
				for (size_t i=0;i<(sizeof(m_pTxt_Popup_Infor)/sizeof(m_pTxt_Popup_Infor[0]));i++)
				{
					//m_pTxt_Popup_Infor[i] = new HCTextCtrl;
					if( NULL != m_pTxt_Popup_Infor[i] )
					{
						m_pTxt_Popup_Infor[i]->SetFontSize(18,18);
					}
				}
			}
			break;
			default:
			break;
		}
		m_pTxtScreen->SetText(s_pLan[1]);
		m_pBtnAddressBookDial->SetText(s_pLan[5]);
		//m_pBtnAddressBookDownLoad->SetText(s_pLan[6]);
		m_pBtnAddressBookDelete->SetText(s_pLan[7]);
		m_pBtnAddressBookDeleteAll->SetText(s_pLan[8]);
		m_pTxtDownLoading->SetText(s_pLan[18]);
		if(m_bDowning == false)
		{
			m_pBtnAddressBookDownLoad->SetText(s_pLan[6]);
		}
		else
		{
			m_pBtnAddressBookDownLoad->SetText(s_pLan[13]);
		}
	}
}
void HCBTAddressBookDlg::RequreSource()
{
	if(m_bSourceRealse == true)
	{
		sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str(),eDIALOGT_BTADDRESSBOOK,0);
		EnableUpdateRect(false);
		HCBTAddressBookDlg::SetBTDlgBackGround();
		m_bSourceRealse = false;
		EnableUpdateRect(false);
		BTDEBUGINFO(L"HCBTAddressBookDlg::%s",__FUNCTIONW__);
	}
}
void HCBTAddressBookDlg::ReleaseSource()
{
	/*
	m_pTxtAddressBookBK->SetBkgndN(NULL);
	m_pTxtDeviceLine1->SetBkgndN(NULL);
	m_pTxtDeviceLine2->SetBkgndN(NULL);
	m_pTxtDeviceLine3->SetBkgndN(NULL);
	m_pTxtDeviceLine4->SetBkgndN(NULL);
	m_pBtnAddressBookDown->SetBkgndN(NULL);
	m_pBtnAddressBookDown->SetBkgndA(NULL);
	m_pBtnAddressBookUp->SetBkgndN(NULL);
	m_pBtnAddressBookUp->SetBkgndA(NULL);
	m_pScrCtrlAddressBook->SetBkgndN(NULL);
	m_pScrCtrlAddressBook->SetBkgndA(NULL);
	m_pScrCtrlAddressBook->SetBkgndD(NULL);
	m_pScrCtrlAddressBook->SetBkgndF(NULL);
	m_pTxtAddressBookHandleBK->SetBkgndN(NULL);
	m_pTxtNoticeBK->SetBkgndN(NULL);
	*/
//通讯录背景
//m_pScrBoxAddressBook->EnableScrollLine(true,66,NULL/*pSource->m_pbtLine*/);
	
	if(m_bSourceRealse == false)
	{
		EnableUpdateRect(false);
		//m_pTxtAddressBookName->SetBkgndN(NULL);
		m_pTxtAddressBookBK->SetBkgndN(NULL);
		//电话本操作背景
		m_pGrpCtrlAddressBookNotice->SetBackGround(NULL);
		//拨打按钮
		m_pBtnAddressBookDial->SetBkgndN(NULL);
		m_pBtnAddressBookDial->SetBkgndA(NULL);
		//下载电话本按钮
		m_pBtnAddressBookDownLoad->SetBkgndN(NULL);
		m_pBtnAddressBookDownLoad->SetBkgndA(NULL);
		//删除按钮
		m_pBtnAddressBookDelete->SetBkgndN(NULL);
		m_pBtnAddressBookDelete->SetBkgndA(NULL);
		//全部删除按钮
		m_pBtnAddressBookDeleteAll->SetBkgndN(NULL);
		m_pBtnAddressBookDeleteAll->SetBkgndA(NULL);
		btSource::Instance()->ReleaseBtSource(eDIALOGT_BTADDRESSBOOK);
		m_bSourceRealse = true;
		EnableUpdateRect(true);
		BTDEBUGINFO(L"HCBTAddressBookDlg::%s",__FUNCTIONW__);
	}
}

void HCBTAddressBookDlg::StartDownBookData()
{
		//CBTCommand::Instance()->SetPBDACState(ePBAPCSTATEDOWNINGOUTGOINGCALL);
		CBTCommand::Instance()->SetPBDACState(ePBAPCSTATEDOWNINGBOOK);
#ifdef  TESTBTCOMMANDQUEUE
		CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketPBAPCSetUpPBAPConnection,NULL);
#else
		HBYTE cCommand[50] = {0};
		HUINT nCmdlen =0;
		nCmdlen = strlen("AT+PBCONN\r\n");
		strncpy((char*)cCommand,"AT+PBCONN\r\n",nCmdlen);
		CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
		//	m_pBtnAddressBookDownLoad->SetText(L"取消");
		m_pBtnAddressBookDownLoad->SetText(s_pLan[13]);
		m_bDowning = true;
}
void HCBTAddressBookDlg::CancelByPhone()
{
	m_bDowning = false;
	m_pBtnAddressBookDownLoad->SetText(s_pLan[6]);
	if(m_ctDowingTime.IsActive())
	{
		m_ctDowingTime.StopTimer();
	}
	m_pGrpCtrlAddressBookNotice->SetShow(false);
	SetPopupInfor(s_pLan[36]);
	ShowPopup(PT_NOR, 100);
}
void HCBTAddressBookDlg::UpdataNameLetter(void* pDlg, void* param)
{
	HCBTAddressBookDlg* pObj = (HCBTAddressBookDlg*)pDlg;
	pObj->UpdataNameLetter(pObj);
}
void HCBTAddressBookDlg::UpdataNameLetter(void* pDlg)
{
	if(m_ctUpdataLetter.IsActive())
	{
		m_ctUpdataLetter.StopTimer();
	}
	HINT nBeg = m_pScrBoxAddressBook->GetStarIndex();
	HINT nEnd = m_pScrBoxAddressBook->GetEndIndex();
	HINT nCurrent =  m_pScrCtrlAddressBook->GetValue();
	
	HINT iResult = CBTCommand::Instance()->GetLetterFromNameGrp(nBeg,CBTCommand::Instance()->GetNameListGrp());
	HINT ntotal = m_pScrBoxAddressBook->GetListItemCount();
	if(iResult != m_nBeg || (HINT)m_nTotalConcats != ntotal)
	{
		BTDEBUGINFO(L"nbeg = %d, nend = %d,nCurrent = %d,iResult = %d,ntotal = %d",nBeg,nEnd,nCurrent,iResult,ntotal);
		switch (iResult)
		{
			case 0:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_A.hfp")));
			}
			break;
		case 1:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_A.hfp")));
			}
			break;
		case 2:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_B.hfp")));
			}
			break;
		case 3:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_C.hfp")));
			}
			break;
		case 4:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_D.hfp")));
			}
			break;
		case 5:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_E.hfp")));
			}
			break;
		case 6:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_F.hfp")));
			}
			break;
		case 7:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_G.hfp")));
			}
			break;
		case 8:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_H.hfp")));
			}
			break;
		case 9:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_I.hfp")));
			}
			break;
		case 10:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_J.hfp")));
			}
			break;
		case 11:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_K.hfp")));
			}
			break;
		case 12:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_L.hfp")));
			}
			break;
		case 13:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_M.hfp")));
			}
			break;
		case 14:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_N.hfp")));
			}
			break;
		case 15:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_O.hfp")));
			}
			break;
		case 16:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_P.hfp")));
			}
			break;
		case 17:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_Q.hfp")));
			}
			break;
		case 18:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_R.hfp")));
			}
			break;
		case 19:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_S.hfp")));
			}
			break;
		case 20:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_T.hfp")));
			}
			break;
		case 21:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_U.hfp")));
			}
			break;
		case 22:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_V.hfp")));
			}
			break;
		case 23:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_W.hfp")));
			}
			break;
		case 24:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_X.hfp")));
			}
			break;
		case 25:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_Y.hfp")));
			}
			break;
		case 26:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_Z.hfp")));
			}
			break;
		default:
			{
				m_pTxtAddressBookName->SetBkgndN(GetHMIPath(_T("Bluetooth\\Booklist\\Booklist_A.hfp")));
			}
			break;
		}
	}
    m_nBeg = iResult;
	m_nTotalConcats = ntotal;
	m_ctUpdataLetter.SetTime(100);
	m_ctUpdataLetter.StartTimer();
}
HBOOL HCBTAddressBookDlg::DoMessage(HMessage *msg)
{
	HBOOL bRet = false;

    if(msg != NULL)
	{
		bRet = HCBluetoothBaseDlg::DoMessage(msg);
		if(true)
		{
			switch((HINT)msg->msgtype )
			{
				case KMSG_LBBUTTONDOWN:
				{
					if(msg->mousex >= 0 && msg->mousex <75 && msg->mousey >=(42 +80) && msg->mousey<= (301+80))
					{
						BTDEBUGINFO(L"msg->mousex = %d,msg->mousey =%d",msg->mousex,msg->mousey);
						HINT iResult = GetLetterIndex(msg->mousey - 80);
						BTDEBUGINFO(L"iResult = %d",iResult);
						if(iResult >= 0 && iResult <= 26)
						{
							NameListGroup sNameGrp = CBTCommand::Instance()->GetNameListGrp();
							HINT nTotal = m_pScrBoxAddressBook->GetListItemCount();
							HINT nCurrent = sNameGrp.szTotalCount[iResult];
							BTDEBUGINFO(L"nTotal = %d,nCurrent = %d",nTotal,nCurrent);
							if(nCurrent <= nTotal)
							{
								//m_pScrCtrlAddressBook->SetValue((nCurrent-1)/5);
								m_pScrCtrlAddressBook->SetValueEx((nCurrent-1)/5,true);
							}
						}
					}
				}
				break;
				case KMSG_MOUSEMOVE:
				case KMSG_LBBUTTONUP:
				{
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
HINT HCBTAddressBookDlg::GetLetterIndex(HINT nPos)
{
	HINT iIndex = -1;
	if(nPos >= 42 && nPos <= 301)
	{
		iIndex = (nPos - 42)/10;
		return iIndex + 1;
	}
	else
	{
		return -1;
	}
}

void HCBTAddressBookDlg::UpDateDownLoad(HINT nState,HINT nNum)//nstate :0下载启动 1联系人 2:已接电话 3:已拨电话 4：未接电话 5全部记录 nNum:数目 6:电话本下载结束 7:手机端取消下载
{
	BTDEBUGINFO(L"%s:nState = %d,nNum = %d",__FUNCTIONW__,nState,nNum);
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	if(p->BTHFPData.nHFPState >= 2)
	{
		switch (nState)
		{
		case 0:
			{
				
			}
			break;
		case 1:
			{
				
			}
			break;
		case 2:
			{

			}
			break;
		case 3:
			{

			}
			break;
		case 4:
			{

			}
			break;
		case 5:
			{
				m_nAllRecordsDown = nNum;
				OnDowingTimer(NULL);
				wchar_t szTemp[50] = {0};
				swprintf(szTemp,L"%s%d",s_pLan[39],nNum);
				m_pTxtDownLoading->SetText(szTemp);
			}
			break;
		case 6:
			{
				
			}
			break;
		case 7:
			{
				
			}
			break;
		case 8:
			{
				m_nContactDown = nNum;
				OnDowingTimer(NULL);
				wchar_t szTemp[50] = {0};
				swprintf(szTemp,L"%s%d",s_pLan[41],nNum);
				m_pTxtDownLoading->SetText(szTemp);
			}
			break;
		case 9:
			{
				m_nContactDown = nNum;
				OnDowingTimer(NULL);
				wchar_t szTemp[50] = {0};
				swprintf(szTemp,L"%s%d",s_pLan[40],nNum);
				m_pTxtDownLoading->SetText(szTemp);
			}
			break;
		default:
			break;
		}
	}
}
