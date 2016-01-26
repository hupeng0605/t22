#include "KCRadioWindow.h"
#include "KHMIBaseHead.h"
//#include "KCRadioCommand.h"
#pragma once
HCRadioDlg* HCRadioDlg::s_pRadioDlg = NULL;
//*HCHAR[50] HCRadioDlg::s_pLan =  NULL;
HCRadioDlg* HCRadioDlg::Instance()
{
	if(NULL == s_pRadioDlg)
	{
		s_pRadioDlg = new HCRadioDlg;
		if(NULL == s_pRadioDlg)
		{
			
		}
	}
	return s_pRadioDlg;
}
HCRadioDlg::HCRadioDlg()
{
	m_pGrpCtrlRadioBottom = NULL;
	m_pTxtBootmBK = NULL;
	m_pBtnPrevious = NULL ;
	m_pBtnNext = NULL;
	m_pBtnScan = NULL;
//	m_pTxtscan = NULL;
	m_pBtnChannelAutoSearch = NULL;
	//m_pTxtChannelAutoSearch = NULL;
	m_pGrpCtrlRadioMiddle = NULL;
	m_bshow = true;
    m_pTxtChannelStoreBK = NULL;
	m_pScrctrlChannelStore = NULL;
	m_pScrboxChannelStore = NULL;
	m_pBtnChannelStoreUp = NULL;
	m_pBtnChannelStoreDown = NULL;
	m_pTxtSTstate = NULL;
	m_pTxtRadioMessage = NULL;
	m_pBtnTopScale = NULL;
	m_pBtnBottomScale = NULL;
	m_pTxtRadioCurrentValue = NULL;
	m_pTxtRadioType = NULL;
	m_pTxtRadioUnit = NULL;
	m_pSliderChannelScan = NULL;
	m_pTxtAMFMBK = NULL;
	//m_pGrpNotice = NULL;
//	m_pBtnCannel = NULL;
//	m_pBtnConfirm = NULL;
//	m_pTxtNotice1 = NULL;
	//m_pTxtNotice2  = NULL;
	//清单
	/*m_pTxtChannnelListsBK = NULL;
	m_pScrctrlChannnelLists = NULL;
	m_pScrboxChannnelLists = NULL;
	m_pBtnChannnelListsUp = NULL;
	m_pBtnChannnelListsDown = NULL;*/
	//数据相关
	memset(m_cRadioCurrentFMValue,0,sizeof(m_cRadioCurrentFMValue));
    memset(m_cRadioCurrentAMValue,0,sizeof(m_cRadioCurrentFMValue));
	//HUINT n= sizeof(m_cRadioCurrentFMValue);
	//m_bChannnelListsShow = false;
    m_eRadioType = eFM;
	m_eRadioWorkState = eRADIONARMAL;
	m_pTxtSTstate = NULL;
	m_pTxtRadioMessage = NULL;
	m_bNoticeShow = false;
	m_bAutoSearch = false;
};
void HCRadioDlg::DeleteInstance()
{
	if(s_pRadioDlg != NULL)
	{
		SAFE_DELETE(s_pRadioDlg);
	}
};
HCRadioDlg::~HCRadioDlg()
{
	SAFE_DELETE(m_pTxtBootmBK);
	SAFE_DELETE(m_pBtnPrevious);
	SAFE_DELETE(m_pBtnNext);
	SAFE_DELETE(m_pBtnScan);
	SAFE_DELETE(m_pBtnChannelAutoSearch);
	SAFE_DELETE(m_pTxtChannelStoreBK);
	SAFE_DELETE(m_pScrctrlChannelStore);
	SAFE_DELETE(m_pScrboxChannelStore);
	SAFE_DELETE(m_pBtnChannelStoreUp);
	SAFE_DELETE(m_pBtnChannelStoreDown);
	SAFE_DELETE(m_pBtnTopScale);
	SAFE_DELETE(m_pBtnBottomScale);
	SAFE_DELETE(m_pTxtRadioCurrentValue);
	SAFE_DELETE(m_pTxtRadioType);
	SAFE_DELETE(m_pTxtRadioUnit);
	SAFE_DELETE(m_pSliderChannelScan);
	SAFE_DELETE(m_pSwBtAMFM);
	SAFE_DELETE(m_pTxtAMFMBK);
	SAFE_DELETE(m_pTxtSTstate);
	SAFE_DELETE(m_pTxtRadioMessage);
	SAFE_DELETE(m_pGrpCtrlRadioBottom);
	SAFE_DELETE(m_pGrpCtrlRadioMiddle);
	SAFE_DELETE_GROUP(m_pAMStoredChannnel);
	SAFE_DELETE_GROUP(m_pFMStoredChannnel);
	DelTimer(&m_ctRefrench);
}
//初始化
HINT HCRadioDlg::OnInit()
{
	DWORD dTime = GetTickCount();
	//HINT nRet = HDialogBase::OnInit();
	HINT nRet = KDialogP::OnInit();
	m_bshow = true;
	m_bST = false;
	m_bNoticeShow = false;
	m_bAutoSearch = false;
	m_eRadioType = eFM;
	m_pFMStoredChannnel = new HUINT[20];
	m_pAMStoredChannnel = new HUINT[20];
	m_nCurrentArea = 0;
	 m_nPreFMValue = -1;
	 m_nPreAMValue = -1;
	if(m_pFMStoredChannnel != NULL && m_pAMStoredChannnel != NULL)
	{
		for(int i = 0;i < 20;i++)
		{
			m_pFMStoredChannnel[i]= 0;
			m_pAMStoredChannnel[i]= 0;
		}
	}
	//ReadRadioLastMem();
	if(m_pTxtRadioCurrentValue != NULL)
	{
		//m_pTxtRadioCurrentValue->SetText(m_cRadioCurrentFMValue);
	}
	if(m_pSliderChannelScan != NULL)
	{
		//m_pSliderChannelScan->SetValue(m_nCurrentFMValue);
	}
	m_dwNowTime = GetTickCount();
	m_iScrboxChannelStore = -1;
	HINT nTotal = RadioSource::Instance()->ReadLangeContent(400);
	if(nTotal > 0)
	{
		RADIODEBUGINFO(L"获取语言数据成功");
	}
	else
	{
		RADIODEBUGINFO(L"获取语言数据失败");
		exit(20);
	}
	//InitPopupCtrl();
	InitHeadCtrl();
//	m_pTxtScreen->SetText(L"收音机");
	sRadioSourceGroup *pSource = RadioSource::Instance()->GetRadioSource(GetHMIPath(_T("")).c_str());
	KCLastMemory::GetInstance()->GetSetupMemory(g_SetupSetting);
	SetBackGround(GetHMIPath((HCHAR*)&g_SetupSetting.szBkgndPath));
	SetFocusLineWidth(0);
	if(pSource != NULL)
	{
		m_pSliderChannelScan = new HCSlideCtrl;
		if(m_pSliderChannelScan != NULL)
		{
			m_pSliderChannelScan->Create(190,130,586,222,0,0);
			m_pSliderChannelScan->EnableMsg(true);
			//m_pSliderChannelScan->SetBound(860,1080);
			m_pSliderChannelScan->SetBkgndA(GetHMIPath(_T("Radio\\Radio_Pointer.hfp")));
			m_pSliderChannelScan->SetDotgndA(GetHMIPath(_T("Radio\\Radio_Pointer.hfp")));
			m_pSliderChannelScan->EnableMoveSlider(true);
			m_pSliderChannelScan->EnableClickSlider(true);
			m_pSliderChannelScan->SetCallBackMouseMove(OnRadioMouseMove,this);
			m_pSliderChannelScan->SetCallBackMouseDown(OnRadioMouseDown,this);
			m_pSliderChannelScan->SetCallBackMouseUp(OnRadioMouseUp,this);
			AddChild(m_pSliderChannelScan);
		}
		//   收音机中部组合  
		m_pGrpCtrlRadioMiddle = new HCGroupCtrl;
		if(m_pGrpCtrlRadioMiddle != NULL && pSource != NULL)
		{
			m_pGrpCtrlRadioMiddle->Create(164,173,636,136);
			m_pGrpCtrlRadioMiddle->EnableMsg(false);
			m_pGrpCtrlRadioMiddle->SetBackGround(GetHMIPath(_T("Radio\\Radio_Play_Stations_Frame.hfp")));
			AddChild(m_pGrpCtrlRadioMiddle);
			m_pTxtChannelStoreBK = new HCTextCtrl;
			if(m_pTxtChannelStoreBK != NULL)
			{
				m_pTxtChannelStoreBK->Create(0,68,176,344);
				m_pTxtChannelStoreBK->EnableMsg(false);
				m_pTxtChannelStoreBK->SetBkgndN(GetHMIPath(_T("Share\\Share_Function_Frame.hfp")));
				m_pGrpCtrlRadioMiddle->AddChild(m_pTxtChannelStoreBK);
			}
			m_pScrboxChannelStore = new HCScrollBox;
			if(m_pScrboxChannelStore != NULL)
			{
				m_pScrboxChannelStore->Create(14,74,120,330);
				m_pScrboxChannelStore->SetTextColorN(255, 255, 255);//设置字体颜色
				m_pScrboxChannelStore->SetTextColorA(255, 255, 255);//设置字体颜色
				//m_pScrboxChannelStore->SetFontSize(24, 24);//设置字体的大小
				m_pScrboxChannelStore->SetFontSize(20, 24);//设置字体的大小
				bool bb = m_pScrboxChannelStore->EnableScrollLine(true,RADIO_CHANNEL_ITEM_HEIGHT,NULL);
				if(bb == false)
				{
					RADIODEBUGINFO(L"set failed");
				}
				else
				{
					RADIODEBUGINFO(L"set success");
				}
				m_pScrboxChannelStore->SetCallBackClick(OnScrboxChannelStore,this);
				m_pScrboxChannelStore->SetCallBackLongPress(OnScrboxChannelStoreLong,this);
				ChannelStoreAddChannel();
				AddChild(m_pScrboxChannelStore);	
			}
			//滚动条
			m_pScrctrlChannelStore = new HCScrollCtrl;
			if(m_pScrctrlChannelStore != NULL)
			{
				m_pScrctrlChannelStore->Create(132,100,28,280,1);
				m_pScrctrlChannelStore->SetBound(0,3);
				m_pScrctrlChannelStore->SetBkgndN(GetHMIPath(_T("Share\\Share_Slide_N.hfp")));
				m_pScrctrlChannelStore->SetBkgndA(GetHMIPath(_T("Share\\Share_Slide_Bar.hfp")));
				m_pScrctrlChannelStore->SetBkgndD(GetHMIPath(_T("Share\\Share_Slide_A.hfp")));
				m_pScrctrlChannelStore->SetBkgndF(GetHMIPath(_T("Share\\Share_Slide_Bar.hfp")));
				m_pScrctrlChannelStore->SetScrollBox(m_pScrboxChannelStore,5);
				AddChild(m_pScrctrlChannelStore);
			}
			//滑动条向上按钮
			m_pBtnChannelStoreUp = new HCButton;
			if(m_pBtnChannelStoreUp != NULL)
			{
				m_pBtnChannelStoreUp->Create(126, 72, 40, 36);
				m_pBtnChannelStoreUp->EnableMsg(true);
				m_pBtnChannelStoreUp->SetBkgndN(GetHMIPath(_T("Share\\Share_Front_N.hfp")));
				m_pBtnChannelStoreUp->SetBkgndA(GetHMIPath(_T("Radio\\Radio_Front_A.hfp")));
				AddChild(m_pBtnChannelStoreUp);
			}
			//滑动条向下按钮
			m_pBtnChannelStoreDown = new HCButton;
			if(m_pBtnChannelStoreDown != NULL)
			{
				m_pBtnChannelStoreDown->Create(126, 372, 40, 36);
				m_pBtnChannelStoreDown->EnableMsg(true);
				m_pBtnChannelStoreDown->SetBkgndN(GetHMIPath(_T("Share\\Share_Last_N.hfp")));
				m_pBtnChannelStoreDown->SetBkgndA(GetHMIPath(_T("Radio\\Radio_Last_A.hfp")));
				AddChild(m_pBtnChannelStoreDown);
				m_pScrctrlChannelStore->SetAddButton(m_pBtnChannelStoreUp,m_pBtnChannelStoreDown);
			}
			//中部右侧上标尺
			m_pBtnTopScale = new HCButton;
			if(m_pBtnTopScale != NULL)
			{
				m_pBtnTopScale->Create(166,73,634,56);
				m_pBtnTopScale->EnableMsg(true);
				m_pBtnTopScale->SetBkgndN(pSource->pFmScale);
				m_pGrpCtrlRadioMiddle->AddChild(m_pBtnTopScale);
			}
			//中部右侧下标尺
			m_pBtnBottomScale = new HCButton;
			if(m_pBtnBottomScale != NULL)
			{
				m_pBtnBottomScale->Create(166,351,634,56);
				m_pBtnBottomScale->EnableMsg(false);
				m_pBtnBottomScale->SetBkgndN(GetHMIPath(_T("Radio\\Radio_Scale.hfp")));
				m_pGrpCtrlRadioMiddle->AddChild(m_pBtnBottomScale);
			}
			//当前调频值
			m_pTxtRadioCurrentValue = new HCTextCtrl;
			if(m_pTxtRadioCurrentValue != NULL)
			{
				m_pTxtRadioCurrentValue->Create(360,180,240,80);
				m_pGrpCtrlRadioMiddle->AddChild(m_pTxtRadioCurrentValue);
				m_pTxtRadioCurrentValue->SetTextStyle(RE_TS_CENTER);
				m_pTxtRadioCurrentValue->SetFont(GetRESingleton()->GetFont(FONT_QUARTZ_REGULAR_TTF));
				//m_pTxtRadioCurrentValue->SetFont(GetRESingleton()->GetFont(3));
				m_pTxtRadioCurrentValue->SetTextColorN(255,255,255);
				m_pTxtRadioCurrentValue->SetTextPos(120,50/*436,66*/);
				m_pTxtRadioCurrentValue->SetFontSize(96,96);
				//m_pTxtRadioCurrentValue->SetText(L"96.8");
				m_pTxtRadioCurrentValue->EnableMsg(false);
				m_pTxtRadioCurrentValue->SetShow(false);
			}	
			//FM/AM文本
			m_pTxtRadioType = new HCTextCtrl;
			if(m_pTxtRadioType != NULL)
			{
				m_pTxtRadioType->Create(275,254,80,40);
				m_pTxtRadioType->EnableMsg(false);
				m_pTxtRadioType->SetTextStyle(RE_TS_RIGHT);
				m_pTxtRadioType->SetTextPos(-20,0);
				m_pTxtRadioType->SetFontSize(36,36);
			//	m_pTxtRadioType->SetText(L"FM");
				m_pGrpCtrlRadioMiddle->AddChild(m_pTxtRadioType);
			}
			//ST状态文本
			m_pTxtSTstate = new HCTextCtrl;
			if(m_pTxtSTstate != NULL)
			{
				//m_pTxtSTstate->Create(280,225,80,30);
				m_pTxtSTstate->Create(275,225,80,30);
				m_pTxtSTstate->EnableMsg(false);
				//m_pTxtSTstate->SetTextStyle(RE_TS_NORMAL);
				m_pTxtSTstate->SetTextStyle(RE_TS_CENTER);
				m_pTxtSTstate->SetTextPos(40,15);
				m_pTxtSTstate->SetFontSize(24,24);
				//m_pTxtSTstate->SetText(L"立体声");
				m_pTxtSTstate->SetText(L" ");
				m_pGrpCtrlRadioMiddle->AddChild(m_pTxtSTstate);
			}
			m_pTxtAvailableChannel = new HCTextCtrl;
			if(m_pTxtAvailableChannel != NULL)
			{
				m_pTxtAvailableChannel->Create(240,192,150,30);
				m_pTxtAvailableChannel->EnableMsg(false);
				m_pTxtAvailableChannel->SetTextStyle(RE_TS_CENTER);
				m_pTxtAvailableChannel->SetTextPos(75,15);
				m_pTxtAvailableChannel->SetFontSize(24,24);
				m_pTxtAvailableChannel->SetText(L" ");
				m_pGrpCtrlRadioMiddle->AddChild(m_pTxtAvailableChannel);
			}
			//播放器状态信息显示
			m_pTxtRadioMessage = new HCTextCtrl;
			if(m_pTxtRadioMessage != NULL)
			{
				m_pTxtRadioMessage->Create(620,225,100,30);
				m_pTxtRadioMessage->EnableMsg(false);
				m_pTxtRadioMessage->SetTextStyle(RE_TS_NORMAL);
				m_pTxtRadioMessage->SetTextPos(0,0);
				m_pTxtRadioMessage->SetFontSize(24,24);
				//m_pTxtRadioMessage->SetText(L" ");
				//m_pTxtRadioMessage->SetText(s_pLan[8]);
				//m_pTxtRadioMessage->SetShow(false);
				m_pGrpCtrlRadioMiddle->AddChild(m_pTxtRadioMessage);
			}
			//MHZ文本
			m_pTxtRadioUnit =  new HCTextCtrl;
			if(m_pTxtRadioUnit != NULL)
			{
				m_pTxtRadioUnit->Create(620,254,100,40);
				m_pTxtRadioUnit->EnableMsg(false);
				m_pTxtRadioUnit->SetTextStyle(RE_TS_RIGHT);
				m_pTxtRadioUnit->SetTextPos(-35,0);
				m_pTxtRadioUnit->SetFontSize(36,36);
				//m_pTxtRadioUnit->SetText(L"MHz");
				m_pGrpCtrlRadioMiddle->AddChild(m_pTxtRadioUnit);
			}
		}
		//radio底边栏
		m_pGrpCtrlRadioBottom = new HCGroupCtrl;
		if(m_pGrpCtrlRadioBottom != NULL)
		{
			m_pGrpCtrlRadioBottom->Create(0,412,800,68);
			AddChild(m_pGrpCtrlRadioBottom);
		}
		//底栏背景
		m_pTxtBootmBK = new HCImageCtrl;
		if(m_pTxtBootmBK != NULL)
		{
			m_pTxtBootmBK->Create(0,412,800,68);
			m_pTxtBootmBK->EnableMsg(false);
			m_pTxtBootmBK->SetBkgndN(GetHMIPath(_T("Share\\Share_Frame_Bottom 02.hfp")));
			m_pTxtBootmBK->SetOpacity(8);
			m_pGrpCtrlRadioBottom->AddChild(m_pTxtBootmBK);
		}
		//扫描按钮
		m_pBtnScan = new HCButton;
		if(m_pBtnScan != NULL)
		{
			m_pBtnScan->Create(172,420, 134, 60);
			m_pBtnScan->EnableMsg(true);
			m_pBtnScan->SetTextColorN(255,255,255);
			m_pBtnScan->SetTextStyle(RE_TS_CENTER);
			m_pBtnScan->SetTextPos(84,28);
			m_pBtnScan->SetFontSize(24,24);
			m_pBtnScan->SetTextColorN(255,255,255);
			m_pBtnScan->SetTextColorA(0,0,255);
			m_pBtnScan->SetTextColorS(255,255,255);
		//	m_pBtnScan->SetText(L"扫描");
			m_pBtnScan->SetBkgndN(GetHMIPath(_T("Radio\\Radia_Scan_N.hfp")));
			m_pBtnScan->SetBkgndA(GetHMIPath(_T("Radio\\Radia_Scan_A.hfp")));
			m_pBtnScan->SetCallBack(OnScan,this);
			m_pGrpCtrlRadioBottom->AddChild(m_pBtnScan);
		}
		//自动搜台按钮
		m_pBtnChannelAutoSearch = new HCButton;
		if(m_pBtnChannelAutoSearch != NULL)
		{
			m_pBtnChannelAutoSearch->Create(494,420, 160, 60);
			m_pBtnChannelAutoSearch->EnableMsg(true);
			m_pBtnChannelAutoSearch->SetTextColorN(255,255,255);
			m_pBtnChannelAutoSearch->SetTextColorA(0,0,255);
			m_pBtnChannelAutoSearch->SetTextColorS(255,255,255);
			m_pBtnChannelAutoSearch->SetTextColorN(255,255,255);
			m_pBtnChannelAutoSearch->SetTextStyle(RE_TS_CENTER);
			m_pBtnChannelAutoSearch->SetFontSize(24,24);
			m_pBtnChannelAutoSearch->SetTextPos(64,28);
			//m_pBtnChannelAutoSearch->SetText(L"自动存台");
			if(s_pLan != NULL)
			{
				m_pBtnChannelAutoSearch->SetText(s_pLan[2]);
			}
			m_pBtnChannelAutoSearch->SetBkgndA(GetHMIPath(_T("Radio\\Radio_Conserve_A.hfp")));
			m_pBtnChannelAutoSearch->SetBkgndN(GetHMIPath(_T("Radio\\Radio_Conserve_N.hfp")));
			m_pBtnChannelAutoSearch->SetCallBack(OnChannelAutoSearch,this);
			m_pGrpCtrlRadioBottom->AddChild(m_pBtnChannelAutoSearch);
		}
		//向前按钮
		m_pBtnPrevious = new HCButton;
		if(m_pBtnPrevious != NULL)
		{
			m_pBtnPrevious->Create(0,420, 172, 60);
			m_pBtnPrevious->EnableMsg(true);
			m_pBtnPrevious->SetBkgndA(GetHMIPath(_T("Radio\\Radia_Step_Back_A.hfp")));
			m_pBtnPrevious->SetBkgndN(GetHMIPath(_T("Radio\\Radia_Step_Back_N.hfp")));
			//m_pBtnPrevious->SetCallBack(OnRadioDown,this);
			m_pBtnPrevious->SetCallBack(OnNextSearch,this);
			//m_pBtnPrevious->SetCallBackLongPress(OnNextSearch,this);
			m_pGrpCtrlRadioBottom->AddChild(m_pBtnPrevious);
			//AddChild(m_pBtnPrevious);
		}
		//向后按钮
		m_pBtnNext = new HCButton;
		if(m_pBtnNext != NULL)
		{
			m_pBtnNext->Create(654,420,146,60);
			m_pBtnNext->EnableMsg(true);
			m_pBtnNext->SetBkgndA(GetHMIPath(_T("Radio\\Radia_Step_Up_A.hfp")));
			m_pBtnNext->SetBkgndN(GetHMIPath(_T("Radio\\Radia_Step_Up_N.hfp")));
			//m_pBtnNext->SetCallBack(OnRadioUp,this);
			//m_pBtnNext->SetCallBackLongPress(OnPreSearch,this);
			m_pBtnNext->SetCallBack(OnPreSearch,this);
			m_pGrpCtrlRadioBottom->AddChild(m_pBtnNext);
		}
		//AMFM按钮背景
		m_pTxtAMFMBK = new HCImageCtrl;
		if(m_pTxtAMFMBK != NULL)
		{
			m_pTxtAMFMBK->Create(306,420, 188, 60);
			m_pTxtAMFMBK->EnableMsg(false);
			m_pTxtAMFMBK->SetBkgndN(GetHMIPath(_T("Radio\\Radio_AM_FM_Frame.hfp")));
			m_pTxtAMFMBK->SetOpacity(8);
			m_pGrpCtrlRadioBottom->AddChild(m_pTxtAMFMBK);
		}
		m_pSwBtAMFM = new HCSwitchButton;
		if(m_pSwBtAMFM != NULL)
		{
			m_pSwBtAMFM->Create(316,420, 175, 60);
			m_pSwBtAMFM->SetButtonBkgndN(GetHMIPath(_T("Radio\\Radio_AM_FM_A.hfp")));
			TEXT_ITEM_VEC vecText;
			m_pSwBtAMFM->SetBtnNum(2);
			m_pSwBtAMFM->SetBtnOffset(-5,0);
			m_pSwBtAMFM->SetFontSize(24,24);
			vecText.push_back(_T("AM"));
			vecText.push_back(_T("FM"));
			m_pSwBtAMFM->SetVecText(vecText);
			m_pSwBtAMFM->SetTextColorA(255,255,255);
			//m_pSwBtAMFM->SetCallBackCheck(OnAMFM,this);
			//m_pSwBtAMFM->SetEnableTran(true);
			m_pSwBtAMFM->SetCallBackMove(OnAMFMMoveEnd,this);
			m_pSwBtAMFM->SetCallBack(OnAMFMUp,this);
			
			
			//m_pSwBtAMFM->SetButtonIndex(1);
			m_pSwBtAMFM->SetButtonBkgndA(GetHMIPath(_T("Radio\\Radio_AM_FM_A.hfp")));
			//AddChild(m_pSwBtAMFM);
			m_pGrpCtrlRadioBottom->AddChild(m_pSwBtAMFM);
		}

			m_pGrpCurrentFM = new HCGroupCtrl;
			if(m_pGrpCurrentFM != NULL)
			{
				m_pGrpCurrentFM->Create(306,202,210,78);
				AddChild(m_pGrpCurrentFM);
				m_pGrpCurrentFM->EnableMsg(false);
				m_pTxtFM0 = new HCTextCtrl;
				if(m_pTxtFM0 != NULL)
				{
					m_pTxtFM0->Create(527,202,48,78);
					m_pGrpCurrentFM->AddChild(m_pTxtFM0);
				}
				m_pTxtDot = new HCTextCtrl;
				if(m_pTxtDot != NULL)
				{
					m_pTxtDot->Create(509,202,18,78);
					m_pTxtDot->SetBkgndN(pSource->pNumDot);
					m_pGrpCurrentFM->AddChild(m_pTxtDot);
				}
				m_pTxtFM1 = new HCTextCtrl;
				if(m_pTxtFM1 != NULL)
				{
					m_pTxtFM1->Create(461,202,48,78);
					m_pGrpCurrentFM->AddChild(m_pTxtFM1);
				}
				m_pTxtFM2 = new HCTextCtrl;
				if(m_pTxtFM2 != NULL)
				{
					m_pTxtFM2->Create(413,202,48,78);
					m_pGrpCurrentFM->AddChild(m_pTxtFM2);
				}
				m_pTxtFM3 = new HCTextCtrl;
				if(m_pTxtFM3 != NULL)
				{
					m_pTxtFM3->Create(365,202,48,78);
					m_pGrpCurrentFM->AddChild(m_pTxtFM3);
				}
				m_pTxtFM4 = new HCTextCtrl;
				if(m_pTxtFM4 != NULL)
				{
					m_pTxtFM4->Create(575,202,48,78);
					m_pGrpCurrentFM->AddChild(m_pTxtFM4);
				}
				m_pGrpCurrentFM->SetShow(false);
			}
			m_pGrpCurrentAM = new HCGroupCtrl;
			if(m_pGrpCurrentAM !=NULL)
			{
				m_pGrpCurrentAM->Create(383,202,192,78);
				AddChild(m_pGrpCurrentAM);
				m_pGrpCurrentAM->EnableMsg(false);
				m_pTxtAM0 = new HCTextCtrl;
				if(m_pTxtAM0 != NULL)
				{
					m_pTxtAM0->Create(527,202,48,78);
					m_pGrpCurrentAM->AddChild(m_pTxtAM0);
				}
				m_pTxtAM1 = new HCTextCtrl;
				if(m_pTxtAM1 != NULL)
				{
					m_pTxtAM1->Create(479,202,48,78);
					m_pGrpCurrentAM->AddChild(m_pTxtAM1);
				}
				m_pTxtAM2 = new HCTextCtrl;
				if(m_pTxtAM2 != NULL)
				{
					m_pTxtAM2->Create(431,202,48,78);
					m_pGrpCurrentAM->AddChild(m_pTxtAM2);
				}
				m_pTxtAM3 = new HCTextCtrl;
				if(m_pTxtAM3 != NULL)
				{
					m_pTxtAM3->Create(383,202,48,78);
					m_pGrpCurrentAM->AddChild(m_pTxtAM3);
				}
				m_pGrpCurrentAM->SetShow(false);
			}	
		//	m_pGrpNotice = new HCGroupCtrl;
		////	if(m_pGrpNotice != NULL)
		//	{
		//		//m_pGrpNotice->Create(159,140,500,220);
			//m_pGrpNotice->SetBackGround(pSource->pNotice);
		//		AddChild(m_pGrpNotice);
		//		m_pTxtNotice1 = new HCTextCtrl;
		//		if(m_pTxtNotice1 != NULL)
		//		{
		//			m_pTxtNotice1->Create(159,180,500,30);
		//			m_pTxtNotice1->EnableMsg(false);
		//			m_pTxtNotice1->SetTextStyle(RE_TS_CENTER);
		//			m_pTxtNotice1->SetTextPos(250,15);
		//			m_pTxtNotice1->SetTxtColor(255,255,255);
		//			m_pTxtNotice1->SetFontSize(24,24);
		//			//m_pTxtNotice1->SetText(_T("是否执行自动存台?"));
		//			m_pGrpNotice->AddChild(m_pTxtNotice1);
		//		}
				//m_pTxtNotice2 = new HCTextCtrl;
				//if(m_pTxtNotice2 != NULL)
				//{
				//	m_pTxtNotice2->Create(159,220,500,30);
				//	m_pTxtNotice2->EnableMsg(false);
				//	m_pTxtNotice2->SetTextStyle(RE_TS_CENTER);
				//	m_pTxtNotice2->SetTextPos(250,15);
				//	m_pTxtNotice2->SetTxtColor(255,255,255);
				//	m_pTxtNotice2->SetFontSize(24,24);
				//	//m_pTxtNotice2->SetText(_T("自动存台将会覆盖所有台!"));
				//	m_pGrpNotice->AddChild(m_pTxtNotice2);
				//}
				//m_pBtnConfirm = new HCButton;
				//if(m_pBtnConfirm != NULL)
				//{
				//	m_pBtnConfirm->Create(260,275, 124, 60);
				//	m_pBtnConfirm->EnableMsg(true);
				//	m_pBtnConfirm->SetBkgndA(pSource->pCannelA);
				//	m_pBtnConfirm->SetBkgndN(pSource->pCannelN);
				//	m_pBtnConfirm->SetCallBack(OnConfirm,this);
				//	m_pBtnConfirm->SetTextStyle(RE_TS_CENTER);
				//	m_pBtnConfirm->SetTextPos(64 ,27);
				//	m_pBtnConfirm->SetTextColorN(255,255,255);
				//	m_pBtnConfirm->SetFontSize(24,24);
				//	//m_pBtnConfirm->SetText(_T("确认"));
				//	m_pGrpNotice->AddChild(m_pBtnConfirm);
				//}
				//m_pBtnCannel = new HCButton;
				//if(m_pBtnCannel != NULL)
				//{
				//	m_pBtnCannel->Create(424,275, 124, 60);
				//	m_pBtnCannel->EnableMsg(true);
				//	//m_pBtnCannel->SetCallBackLongPress(OnUpSearch,this);
				//	m_pBtnCannel->SetBkgndA(pSource->pCannelA);
				//	m_pBtnCannel->SetBkgndN(pSource->pCannelN);
				//	m_pBtnCannel->SetCallBack(OnCannel,this);
				//	m_pBtnCannel->SetTextStyle(RE_TS_CENTER);
				//	m_pBtnCannel->SetTextPos(64 ,27);
				//	m_pBtnCannel->SetTextColorN(255,255,255);
				//	m_pBtnCannel->SetFontSize(24,24);
				//	//m_pBtnCannel->SetText(_T("取消"));
				//	m_pGrpNotice->AddChild(m_pBtnCannel);
				//	m_pGrpNotice->SetShow(false);
				//}
		//UpDataRadioLisitem(m_eRadioType);
	}
	m_ctRefrench.SetCallBack(OnStartSearch,this);
	AddTimer(&m_ctRefrench);
	UpDataRadioSource();
	//ChangeLangue(0);
	//SetBackGround(GetHMIPath(_T("Share\\Share_Bak.hfp")));
	HBYTE pSend[10] ={0};
	unsigned nlen = 0;
	pSend[nlen++] = 0x00;
	pSend[nlen++] = 0x01;
	pSend[nlen++] = 0x00;
	IPCEVENT *pIPCevent = new IPCEVENT;
	pIPCevent->uIPCEvent =IPC_U_SYS_COM_PROTOCOL;
	pIPCevent->uSize = nlen;
	pIPCevent->pData = pSend;
	RadioSendData(IPC_ID_MANAGE,pIPCevent);
	SAFE_DELETE(pIPCevent);
	 dTime = GetTickCount() - dTime;
	 RADIODEBUGINFO(L"%s:CostTime = %d",__FUNCTIONW__,dTime);
	return nRet;
}
void HCRadioDlg::OnBtnDown(void *p, void *pParam)
{
	HCRadioDlg* pDlg = (HCRadioDlg*)p;
	pDlg->OnBtnDown(pParam);
}
void HCRadioDlg::OnBtnDown(void* pParam)
{
}
void HCRadioDlg::OnScan(void* pDlg, void*)
{
	if(pDlg != NULL)
	{
		HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
		pObj->OnScan(pObj);
	}
}
void HCRadioDlg::OnScan(void* pDlg)
{
	if(m_bAutoSearch == true)
	{
		m_bAutoSearch = false;
		//m_pBtnChannelAutoSearch->SetText(L"自动存台");
		if(s_pLan != NULL)
		{
			m_pBtnChannelAutoSearch->SetText(s_pLan[2]);
		}	
	}
#if RADIOCOMMANDQUEUE
	::PostMessage(m_hWnd,WM_USER + 50,eRADIOSCAN,NULL);
#else
	HBYTE  pSendData[10] = {0};
	HUINT nlen = 0;
	pSendData[nlen++] = 0x00;
	pSendData[nlen++] =0x01;
	pSendData[nlen++] = 0x08;
	IPCEVENT *pIPCevent = new IPCEVENT;
	pIPCevent->uIPCEvent =IPC_U_SYS_COM_PROTOCOL;
	pIPCevent->uSize = nlen;
	pIPCevent->pData = pSendData;
	RadioSendData(IPC_ID_MANAGE,pIPCevent);
	SAFE_DELETE(pIPCevent);
#endif
	/*SAFE_DELETE(pIPCevent);*/
	/*for(int i = 850; i < 1089; i++)
	{
		m_eRadioType = eFM;
		m_eRadioWorkState = eRADIOCHANNELSREACHING;
		m_nCurrentFMValue = i;
		UpData();
	}*/
	//m_eRadioWorkState = eRADIOCHANNELSREACHING;
 // HBYTE *ctest = new HBYTE[20];
	//memset(ctest,0,20);
//	ctest[0]=0x01;ctest[1]=0x00;ctest[2]=0xff;ctest[3]=0x24;ctest[4]=0x01;ctest[5]=0x00;ctest[6]=0x0f;ctest[7]=0x01;ctest[8]=0x0f;ctest[9]=0x00;ctest[10]=0xff;ctest[11]=0x02;ctest[12]=0x3f;ctest[13]=0x00;ctest[14]=0xff;ctest[15]=0x00;ctest[16]=0x04;ctest[17]=0x04;ctest[18]=0xff;ctest[19]=0x00;
	//pObj->HandRadioData(ctest,18);
	 //HCHAR *Value = new HCHAR[6];
	//memset(Value,0,12);
	//pObj->m_pScrboxChannelStore->GetItemAt(1)->SetText(Value);
	//DWORD newtime1=GetTickCount();
	//cout<<"%%%%data init cost time:%%%%"<<newtime1-oldtime1<<endl;
	/*
	for(int i = 0;i < 6;i++)
	{  
		if(Value != NULL && pObj->m_pFM2StoredChannnel != NULL )
		{
			cout<<"m_pFM2StoredChannnel["<<i<<"]="<<m_pFM2StoredChannnel[i]<<endl;
		//	m_pFM2StoredChannnel[i]=0;
			swprintf_s(Value,12,L"%u",pObj->m_pFM2StoredChannnel[i]);
			pObj->m_pScrboxChannelStore->GetItemAt(i+12)->SetText(Value);
			pObj->m_pScrboxChannnelLists->GetItemAt(i+6)->SetText(Value);
		}
	}
	*/
//	DWORD newtime=GetTickCount();
//	cout<<"pObj->m_pScrboxChannelStore->GetItemAt(i)->SetText(Value) cost time"<<newtime-newtime1<<endl;
	//cout<<"~~~~~on scan cost time:~~~~~"<<newtime - oldtime<<endl;
	//RADIODEBUGINFO(_T("[HCRadioDlg::OnScan(void* pDlg)]  Exit\n") );
	//::MessageBox(NULL, L"adfasdf", L"asdf", NULL);
}
/*
void HCRadioDlg::OnAM(void* pDlg, void* param)
{
	RADIODEBUGINFO(_T("[HCRadioDlg::OnAM(void* pDlg, void* param)]  Enter\n") );
	HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	pObj->OnAM(pObj);
	RADIODEBUGINFO(_T("[HCRadioDlg::OnAM(void* pDlg, void* param)]  Exit\n") );
}
*/
void HCRadioDlg::OnAM(void)
{
	//m_eRadioType = eAM;
//	HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	
//#if 0
//	/*while(1)
//	{
//		static int  i = 875;
//		//m_pSliderChannelScan->SetValue(i);
//		WCHAR szBuf[10] = {0};
//		swprintf_s(szBuf, sizeof(szBuf)/2, L"%d.%d",i/10,i%10);
//		m_pTxtRadioCurrentValue->SetText(szBuf);
//		m_pTxtRadioMessage->SetText(L"正在搜台");
//		++i;
//		if (i == 1080)
//		{
//			m_pTxtRadioMessage->SetText(L" ");
//			break;
//		}
//		//::Sleep(100);
//	}*/
//#else
#if RADIOCOMMANDQUEUE
	::PostMessage(m_hWnd,WM_USER + 50,eRADIOAMFMCHANNGE,80);
#else
	DWORD dwLen = 0;
	HBYTE cCommand[10] = {0};
	cCommand[dwLen++] = 0x00;
	cCommand[dwLen++] = 0x01;
	cCommand[dwLen++] = 0x02;
	cCommand[dwLen++] = 0x80;
	IPCEVENT *pIPCevent = new IPCEVENT;
	pIPCevent->pData = cCommand;
	pIPCevent->uSize = dwLen;
	pIPCevent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
	//SendData(cCommand,1);
	RadioSendData(IPC_ID_MANAGE,pIPCevent);
	SAFE_DELETE(pIPCevent);
#endif
	m_pSwBtAMFM->SetButtonIndex(0);
}
/*
void HCRadioDlg::OnFM(void* pDlg, void* param)
{
	RADIODEBUGINFO(_T("[HCRadioDlg::OnFM(void* pDlg, void* param)]  Enter\n") );
	if(pDlg != NULL)
	{
		HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
		pObj->OnFM(pObj);
	}

	RADIODEBUGINFO(_T("[HCRadioDlg::OnFM(void* pDlg, void* param)]  Exit\n") );
}
*/
void HCRadioDlg::OnFM(void)
{
	//m_eRadioType = eFM;
//	m_pBtnTopScale->SetBkgndN(pSource->pFmScale);
	//m_pSliderChannelScan->SetBound(850,1089);
	//HINT nCurrentValue = pObj->m_pSliderChannelScan->GetValue();
	//pObj->m_pBtnAM->SetBkgndN(GetHMIPath(_T("Radio\\Radio_AM_FM_Frame.hfp")));
	//pObj->m_pTxtAMFMBK->SetBkgndN(GetHMIPath(_T("Radio\\Radio_AM_FM_Frame.hfp")));
	//pObj->m_pBtnFM->SetBkgndN(GetHMIPath(_T("Radio\\Radio_AM_FM_A.hfp")));
	//swprintf_s(m_cRadioCurrentFMValue,sizeof(m_cRadioCurrentFMValue)/2,L"%d.%d",m_nCurrentFMValue/10,m_nCurrentFMValue%10);
	//m_pTxtRadioCurrentValue->SetText(m_cRadioCurrentFMValue);
	//m_pTxtRadioUnit->SetText(L"MHz");
	//m_pTxtRadioType->SetText(L"FM");
#if RADIOCOMMANDQUEUE
	::PostMessage(m_hWnd,WM_USER + 50,eRADIOAMFMCHANNGE,0);
#else
	HBYTE cCommand[10] ={0};
	HUINT nlen = 0;
	cCommand[nlen++] = 0x00;
	cCommand[nlen++] = 0x01;
	cCommand[nlen++] = 0x02;
	cCommand[nlen++] = 0x00;
	IPCEVENT *pIPCevent = new IPCEVENT;
	pIPCevent->pData = cCommand;
	pIPCevent->uSize = nlen;
	pIPCevent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
	RadioSendData(IPC_ID_MANAGE,pIPCevent);
	SAFE_DELETE(pIPCevent);
#endif
}
void HCRadioDlg::OnRadioMouseMove(void* pDlg, void* param)
{
	HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	pObj->OnRadioMouseMove(pObj);
}
void HCRadioDlg::OnRadioMouseMove(void* pDlg)
{	
	HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	HINT nCurrentValue = pObj->m_pSliderChannelScan->GetValue();

	if(m_eRadioType == eAM)
	{
		m_nCurrentAMValue = nCurrentValue;
		memset(m_cRadioCurrentAMValue,0,sizeof(m_cRadioCurrentAMValue));
		swprintf_s(m_cRadioCurrentAMValue,6,L"%d",nCurrentValue);
		//m_pTxtRadioCurrentValue->SetText(m_cRadioCurrentFMValue);
		UpDataCurrentValue();
		m_pTxtRadioType->SetText(L"AM");
		/*HBYTE cCommand[10] ={0};
		HUINT nlen = 0;
		cCommand[nlen++] = 0x00;
		cCommand[nlen++] = 0x01;
		cCommand[nlen++] = 0x0a;
		cCommand[nlen++] = HI_BYTE(nCurrentValue);
		cCommand[nlen++] = LO_BYTE(nCurrentValue);
		IPCEVENT *pIpcEvent = new IPCEVENT;
		pIpcEvent->pData = cCommand;
		pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
		pIpcEvent->uSize = nlen;
	    RadioSendData(IPC_ID_MANAGE,pIpcEvent);
		SAFE_DELETE(pIpcEvent);*/
	}
	else
	{
		m_nCurrentFMValue = nCurrentValue;
		memset(m_cRadioCurrentFMValue,0,sizeof(m_cRadioCurrentFMValue));
		swprintf_s(m_cRadioCurrentFMValue,sizeof(m_cRadioCurrentFMValue)/2,L"%d.%d",m_nCurrentFMValue/10,m_nCurrentFMValue%10);	
	//	swprintf_s(m_cRadioCurrentFMValue,6,L"%d.%d",nCurrentValue/10,nCurrentValue%10);
		//m_pTxtRadioCurrentValue->SetText(m_cRadioCurrentFMValue);
		UpDataCurrentValue();
		m_pTxtRadioType->SetText(L"FM");
	/*	HBYTE cCommand[10] = {0};
		HUINT nlen = 0;
		cCommand[nlen++] = 0x00;
		cCommand[nlen++] = 0x01;
		cCommand[nlen++] = 0x0a;
		cCommand[nlen++] = HI_BYTE(nCurrentValue*10);
		cCommand[nlen++] = LO_BYTE(nCurrentValue*10);
		IPCEVENT *pIpcEvent = new IPCEVENT;
		pIpcEvent->pData = cCommand;
		pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
		pIpcEvent->uSize = nlen;
		RadioSendData(IPC_ID_MANAGE,pIpcEvent);
		SAFE_DELETE(pIpcEvent);*/
	}
}
void HCRadioDlg::OnRadioMouseDown(void* pDlg, void* param)
{
	HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	pObj->OnRadioMouseDown(pObj);	
}
void HCRadioDlg::OnRadioMouseDown(void* pDlg)
{
	//HWND hm = FindWindow(STR_PROCESSNAME_MANAGE,STR_PROCESSNAME_MANAGE);
	//if(hm != NULL)
	//{
	//	PostMessage(hm,WM_PAINT,1,0);
	//	::ShowWindow( hm, SW_SHOW); 
	//	SetForegroundWindow(hm);
	//	::UpdateWindow(hm);
	//}
 //   return;
	if(m_bAutoSearch == true)
	{
		m_bAutoSearch = false;
		if(s_pLan != NULL)
		{
			m_pBtnChannelAutoSearch->SetText(s_pLan[2]);
		}
		//m_pBtnChannelAutoSearch->SetText(L"自动存台");
	}
	HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	HINT nCurrentValue = pObj->m_pSliderChannelScan->GetValue();
	if(m_eRadioType == eFM)
	{
		if(m_nCurrentArea != 1)
		{
			nCurrentValue = nCurrentValue * 10;
		}
		switch (m_nCurrentArea)
		{
			case 0:
			{
				if(nCurrentValue <8750)
				{
					nCurrentValue = 8750;
				}
				else if(nCurrentValue > 10800)
				{
					nCurrentValue = 10800;
				}
			}
			break;
			case 1:
			{
				if(nCurrentValue <8750)
				{
					nCurrentValue = 8750;
				}
				else if(nCurrentValue > 10800)
				{
					nCurrentValue = 10800;
				}
			}
			break;
			case 2:
			{
				if(nCurrentValue <8790)
				{
					nCurrentValue = 8790;
				}
				else if(nCurrentValue > 10790)
				{
					nCurrentValue = 10790;
				}
			}
			break;
		}
		nCurrentValue = AdjustValue(nCurrentValue,eFM,m_nCurrentArea);
	}
	else
	{
		switch (m_nCurrentArea)
		{
			case 0:
			{
				if(nCurrentValue >1620)
				{
					nCurrentValue = 1620;
				}
				else if(nCurrentValue < 531)
				{
					nCurrentValue = 531;
				}
			}
			break;
			case 1:
			{
				if(nCurrentValue >1611)
				{
					nCurrentValue = 1611;
				}
				else if(nCurrentValue < 522)
				{
					nCurrentValue = 522;
				}
			}
			break;
			case 2:
			{
				if(nCurrentValue >1710)
				{
					nCurrentValue = 1710;
				}
				else if(nCurrentValue < 530)
				{
					nCurrentValue = 530;
				}
			}
			break;
		}
		//nCurrentValue = AdjustValue(nCurrentValue);
		nCurrentValue = AdjustValue(nCurrentValue,eAM,m_nCurrentArea);
	}
		HUINT nlen = 0;
		HBYTE cCommand[10] ={0};
		cCommand[nlen++] = 0x00;
		cCommand[nlen++] = 0x01;
		cCommand[nlen++] = 0x0a;
		cCommand[nlen++] = HI_BYTE(nCurrentValue);
		cCommand[nlen++] = LO_BYTE(nCurrentValue);
#if RADIOCOMMANDQUEUE
		::PostMessage(m_hWnd,WM_USER + 50,eRADIOCHANNNELADJUST,nCurrentValue);
#else
		IPCEVENT *pIpcEvent = new IPCEVENT;
		pIpcEvent->pData = cCommand;
		pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
		pIpcEvent->uSize =nlen;
		RadioSendData(IPC_ID_MANAGE,pIpcEvent);
		SAFE_DELETE(pIpcEvent);
#endif
}
void HCRadioDlg::OnRadioMouseUp(void* pDlg, void* param)
{
	HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	pObj->OnRadioMouseUp(pObj);
}
void HCRadioDlg::OnRadioMouseUp(void* pDlg)
{
	HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	HINT nCurrentValue = pObj->m_pSliderChannelScan->GetValue();
	if(m_eRadioType == eFM)
	{
		if(m_nCurrentArea != 1)
		{
			nCurrentValue = nCurrentValue * 10;
		}
		switch (m_nCurrentArea)
		{
		case 0:
			{
				if(nCurrentValue <8750)
				{
					nCurrentValue = 8750;
				}
				else if(nCurrentValue > 10800)
				{
					nCurrentValue = 10800;
				}
			}
			break;
		case 1:
			{
				if(nCurrentValue <8750)
				{
					nCurrentValue = 8750;
				}
				else if(nCurrentValue > 10800)
				{
					nCurrentValue = 10800;
				}
			}
			break;
		case 2:
			{
				if(nCurrentValue <8790)
				{
					nCurrentValue = 8790;
				}
				else if(nCurrentValue > 10790)
				{
					nCurrentValue = 10790;
				}
			}
			break;
		}
		nCurrentValue = AdjustValue(nCurrentValue,eFM,m_nCurrentArea);
	}
	else
	{
		switch (m_nCurrentArea)
		{
		case 0:
			{
				if(nCurrentValue >1620)
				{
					nCurrentValue = 1620;
				}
				else if(nCurrentValue < 531)
				{
					nCurrentValue = 531;
				}
			}
			break;
		case 1:
			{
				if(nCurrentValue >1611)
				{
					nCurrentValue = 1611;
				}
				else if(nCurrentValue < 522)
				{
					nCurrentValue = 522;
				}
			}
			break;
		case 2:
			{
				if(nCurrentValue >1710)
				{
					nCurrentValue = 1710;
				}
				else if(nCurrentValue < 530)
				{
					nCurrentValue = 530;
				}
			}
			break;
		}
		//nCurrentValue = AdjustValue(nCurrentValue);
		nCurrentValue = AdjustValue(nCurrentValue,eAM,m_nCurrentArea);
	}
		HUINT nlen = 0;
		HBYTE cCommand[10] ={0};
		cCommand[nlen++] = 0x00;
		cCommand[nlen++] = 0x01;
		cCommand[nlen++] = 0x0a;
		cCommand[nlen++] = HI_BYTE(nCurrentValue);
		cCommand[nlen++] = LO_BYTE(nCurrentValue);
#if RADIOCOMMANDQUEUE
		::PostMessage(m_hWnd,WM_USER + 50,eRADIOCHANNNELADJUST,nCurrentValue);
#else
		IPCEVENT *pIpcEvent = new IPCEVENT;
		pIpcEvent->pData = cCommand;
		pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
		pIpcEvent->uSize =nlen;
		RadioSendData(IPC_ID_MANAGE,pIpcEvent);
		SAFE_DELETE(pIpcEvent);
#endif
}
void HCRadioDlg::OnScrboxChannelStore(void* pDlg, void* param)
{
	HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	pObj->OnScrboxChannelStore(pObj);
}
void HCRadioDlg::OnScrboxChannelStore(void* pDlg)
{
	if(m_bAutoSearch == true)
	{
		m_bAutoSearch = false;
		//m_pBtnChannelAutoSearch->SetText(L"自动存台");
		if(s_pLan != NULL)
		{
			m_pBtnChannelAutoSearch->SetText(s_pLan[2]);
		}
	}
	HCListItemBase *pListItemSelect = m_pScrboxChannelStore->GetSelectListItem();
	HINT iSelectIndex = m_pScrboxChannelStore->GetListItemIndex(pListItemSelect);
	HUINT nValue = 0;
	/*
	if(m_iScrboxChannelStore == iSelectIndex)
	{
		HString	sLisitem= pListItemSelect->GetText();
		if (sLisitem[0] == L'存')
		{
			if(m_eRadioType == eAM)
			{
				*(m_pAMStoredChannnel + iSelectIndex) = nValue;
				HUINT nlen = 0;
				HBYTE cCommand[10] ={0};
				cCommand[nlen++] = 0x00;
				cCommand[nlen++] = 0x01;
				cCommand[nlen++] = 0x05;
				cCommand[nlen++] = iSelectIndex+ 1;
				//cCommand[nlen++] = LO_BYTE(nValue);
				IPCEVENT *pIpcEvent = new IPCEVENT;
				pIpcEvent->pData = cCommand;
				pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
				pIpcEvent->uSize =nlen;
				RadioSendData(IPC_ID_MANAGE,pIpcEvent);
				SAFE_DELETE(pIpcEvent);
				//UpDataLisitem(m_pScrboxChannelStore,m_pAMStoredChannnel,eAM);
			}
			else
			{
				*(m_pFMStoredChannnel + iSelectIndex) = nValue;
				HUINT nlen = 0;
				HBYTE cCommand[10] ={0};
				cCommand[nlen++] = 0x00;
				cCommand[nlen++] = 0x01;
				cCommand[nlen++] = 0x05;
				cCommand[nlen++] =0x80+iSelectIndex+1;
				//cCommand[nlen++] = LO_BYTE(nValue*10);
				IPCEVENT *pIpcEvent = new IPCEVENT;
				pIpcEvent->pData = cCommand;
				pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
				pIpcEvent->uSize =nlen;
				RadioSendData(IPC_ID_MANAGE,pIpcEvent);
				//UpDataLisitem(m_pScrboxChannelStore,m_pFMStoredChannnel,eFM);
			}
			
		}	
		else
		{
			if(m_eRadioType == eAM)
			{
				nValue = *(m_pAMStoredChannnel + iSelectIndex) ;
				HUINT nlen = 0;
				HBYTE cCommand[10] ={0};
				cCommand[nlen++] = 0x00;
				cCommand[nlen++] = 0x01;
				cCommand[nlen++] = 0x0a;
				cCommand[nlen++] = HI_BYTE(m_nCurrentAMValue);
				cCommand[nlen++] = LO_BYTE(m_nCurrentAMValue);
				IPCEVENT *pIpcEvent = new IPCEVENT;
				pIpcEvent->pData = cCommand;
				pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
				pIpcEvent->uSize =nlen;
				RadioSendData(IPC_ID_MANAGE,pIpcEvent);
				//swprintf_s(m_cRadioCurrentAMValue,6,L"%d",m_nCurrentAMValue );
				//m_pTxtRadioCurrentValue->SetText(m_cRadioCurrentAMValue);
				//m_pSliderChannelScan->SetValue(m_nCurrentAMValue);
			}
			else
			{
				nValue = *(m_pFMStoredChannnel + iSelectIndex);
				HUINT nlen = 0;
				HBYTE cCommand[10] ={0};
				cCommand[nlen++] = 0x00;
				cCommand[nlen++] = 0x01;
				cCommand[nlen++] = 0x0a;
				cCommand[nlen++] = HI_BYTE(nValue*10);
				cCommand[nlen++] = LO_BYTE(nValue*10);
				IPCEVENT *pIpcEvent = new IPCEVENT;
				pIpcEvent->pData = cCommand;
				pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
				pIpcEvent->uSize =nlen;
				RadioSendData(IPC_ID_MANAGE,pIpcEvent);
				//swprintf_s(m_cRadioCurrentFMValue,6,L"%d.%d",m_nCurrentFMValue/10, m_nCurrentFMValue%10);
				//m_pTxtRadioCurrentValue->SetText(m_cRadioCurrentFMValue);
				//m_pSliderChannelScan->SetValue(m_nCurrentFMValue);
			}
		}
	}
	else 
	{
		m_iScrboxChannelStore = iSelectIndex;
	}
	*/
	if(m_pScrctrlChannelStore != NULL)
	{
		/*int Index = m_pScrctrlChannelStore->GetValue();
		printf("Index = %d+++++++++++++\r\n",m_pScrctrlChannelStore->GetValue());
		m_pScrctrlChannelStore->SetValueEx((Index + 1)%4,true);*/

	}
		HString	sLisitem= pListItemSelect->GetText();
		if (sLisitem[0] == L'存')
		{
			return;
		}

	if(m_eRadioType == eAM)
	{
		nValue = *(m_pAMStoredChannnel + iSelectIndex) ;
		HUINT nlen = 0;
		HBYTE cCommand[10] ={0};
		cCommand[nlen++] = 0x00;
		cCommand[nlen++] = 0x01;
		cCommand[nlen++] = 0x0a;
		cCommand[nlen++] = HI_BYTE(nValue);
		cCommand[nlen++] = LO_BYTE(nValue);
#if RADIOCOMMANDQUEUE
		::PostMessage(m_hWnd,WM_USER + 50,eRADIOCHANNNELADJUST,nValue);
#else
		IPCEVENT *pIpcEvent = new IPCEVENT;
		pIpcEvent->pData = cCommand;
		pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
		pIpcEvent->uSize =nlen;
		RadioSendData(IPC_ID_MANAGE,pIpcEvent);
		SAFE_DELETE(pIpcEvent);
#endif
	}
	else
	{
		nValue = *(m_pFMStoredChannnel + iSelectIndex) ;
		if(m_nCurrentArea != 1)
		{
			nValue = nValue*10;
		}
		HUINT nlen = 0;
		HBYTE cCommand[10] ={0};
		cCommand[nlen++] = 0x00;
		cCommand[nlen++] = 0x01;
		cCommand[nlen++] = 0x0a;
		cCommand[nlen++] = HI_BYTE(nValue);
		cCommand[nlen++] = LO_BYTE(nValue);
#if RADIOCOMMANDQUEUE
		::PostMessage(m_hWnd,WM_USER + 50,eRADIOCHANNNELADJUST,nValue);
#else
		IPCEVENT *pIpcEvent = new IPCEVENT;
		pIpcEvent->pData = cCommand;
		pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
		pIpcEvent->uSize =nlen;
		RadioSendData(IPC_ID_MANAGE,pIpcEvent);
		SAFE_DELETE(pIpcEvent);
#endif
	}
	if(m_iScrboxChannelStore >= 0)
	{
		m_pScrboxChannelStore->SetSelectListItem(m_iScrboxChannelStore, false);
	}
}
void HCRadioDlg::OnScrboxChannelStoreLong(void* pDlg,void* param)
{
	HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	pObj->OnScrboxChannelStoreLong(pObj);
}
void HCRadioDlg::OnScrboxChannelStoreLong(void* pDlg)
{
	if(m_bAutoSearch == true)
	{
		m_bAutoSearch = false;
		//m_pBtnChannelAutoSearch->SetText(L"自动存台");
		if(s_pLan != NULL)
		{
			m_pBtnChannelAutoSearch->SetText(s_pLan[2]);
		}
	}
	HCListItemBase *pListItemSelect = m_pScrboxChannelStore->GetSelectListItem();
	HINT iSelectIndex = m_pScrboxChannelStore->GetListItemIndex(pListItemSelect);
	if(m_eRadioType == eFM)
	{
		HUINT nlen = 0;
		HBYTE cCommand[10] ={0};
		cCommand[nlen++] = 0x00;
		cCommand[nlen++] = 0x01;
		cCommand[nlen++] = 0x05;
		cCommand[nlen++] = iSelectIndex+ 1 + 0x80;
#if RADIOCOMMANDQUEUE
		::PostMessage(m_hWnd,WM_USER + 50,eRADIOCHANNELSTORE,iSelectIndex+ 1 + 0x80);
#else
		IPCEVENT *pIpcEvent = new IPCEVENT;
		pIpcEvent->pData = cCommand;
		pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
		pIpcEvent->uSize =nlen;
		RadioSendData(IPC_ID_MANAGE,pIpcEvent);
		SAFE_DELETE(pIpcEvent);	
#endif
		*(m_pFMStoredChannnel+iSelectIndex) =m_nCurrentFMValue;
		HCHAR pCtemp[10] = {0};
		if(pListItemSelect != NULL )
		{
			if(*(m_pFMStoredChannnel+iSelectIndex) == 0)
			{
				m_pScrboxChannelStore->GetItemAt(iSelectIndex)->SetText(L"存储");
			}
			else
			{
				memset(pCtemp,0,sizeof(pCtemp));
				int nLeft = 0;
				if(m_nCurrentArea != 1)
				{
					swprintf_s(pCtemp,6,L"%d.%d",(*(m_pFMStoredChannnel+iSelectIndex))/10,(*(m_pFMStoredChannnel+iSelectIndex))%10);
				}
				else if(m_nCurrentArea == 1)
				{
					nLeft = *(m_pFMStoredChannnel+iSelectIndex)%100;
					if(nLeft >= 10)
					{
						swprintf_s(pCtemp,8,L"%d.%d",(*(m_pFMStoredChannnel+iSelectIndex))/100,(*(m_pFMStoredChannnel+iSelectIndex))%100);
					}
					else if(nLeft < 10)
					{
						swprintf_s(pCtemp,8,L"%d.0%d",(*(m_pFMStoredChannnel+iSelectIndex))/100,(*(m_pFMStoredChannnel+iSelectIndex))%100);
					}
					
				}
				m_pScrboxChannelStore->GetItemAt(iSelectIndex)->SetText(pCtemp);
			}
		}	
	}
	else
	{
		HUINT nlen = 0;
		HBYTE cCommand[10] = {0};
		cCommand[nlen++] = 0x00;
		cCommand[nlen++] = 0x01;
		cCommand[nlen++] = 0x05;
		cCommand[nlen++] = iSelectIndex+ 1;
#if RADIOCOMMANDQUEUE
		::PostMessage(m_hWnd,WM_USER + 50,eRADIOCHANNELSTORE,iSelectIndex+ 1);
#else
		IPCEVENT *pIpcEvent = new IPCEVENT;
		pIpcEvent->pData = cCommand;
		pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
		pIpcEvent->uSize =nlen;
		RadioSendData(IPC_ID_MANAGE,pIpcEvent);
		SAFE_DELETE(pIpcEvent);
#endif
		*(m_pAMStoredChannnel+iSelectIndex) =m_nCurrentAMValue;
		HCHAR pCtemp[7] = {0};
		if(pListItemSelect != NULL )
		{
			if(*(m_pAMStoredChannnel+iSelectIndex) == 0)
			{
				m_pScrboxChannelStore->GetItemAt(iSelectIndex)->SetText(L"存储");
			}
			else
			{
				memset(pCtemp,0,sizeof(pCtemp));
				swprintf_s(pCtemp,6,L"%d",*(m_pAMStoredChannnel+iSelectIndex));
				m_pScrboxChannelStore->GetItemAt(iSelectIndex)->SetText(pCtemp);
			}
		}
		
	}
}
void HCRadioDlg::StoreChannel()
{
}
void HCRadioDlg::UpDataRadioLisitem(eRadioType_t eRadioType)
{
	if(eRadioType == eFM)
	{
		UpDataLisitem(m_pScrboxChannelStore,m_pFMStoredChannnel,eFM);
		//UpDataLisitem(m_pScrboxChannnelLists,m_pFMChannnelLists,eFM);
	}
	else
	{
		UpDataLisitem(m_pScrboxChannelStore,m_pAMStoredChannnel,eAM);
		//UpDataLisitem(m_pScrboxChannnelLists,m_pAMChannnelLists,eAM);
	}
}
void HCRadioDlg::UpDataSelectRadioListem()
{
	if(m_eRadioType == eFM)
	{
		HUINT i = IsStored(m_pFMStoredChannnel,m_nCurrentFMValue);
		if(i > 0 && i <=20)
		{
			//JumpToCurrentValueIndex(i);
			m_pScrboxChannelStore->SetSelectListItem(i-1, false);
			
			//m_pScrctrlChannelStore->SetValue((i-1)/5);
		}
		else
		{
			//JumpToCurrentValueIndex(i);
			m_pScrboxChannelStore->SetSelectListItem(-1, false);
			
		}
	}
	else
	{
		HUINT i = IsStored(m_pAMStoredChannnel,m_nCurrentAMValue);
		if(i > 0 && i <=20)
		{
			m_pScrboxChannelStore->SetSelectListItem(i-1, false);
			//m_pScrctrlChannelStore->SetValue((i-1)/5);
		}
		else
		{
			m_pScrboxChannelStore->SetSelectListItem(-1, false);
		}
	}
}
void HCRadioDlg::UpDataLisitem(HCScrollBox *pScrllBox,HUINT *pArr,eRadioType_t eRadioType)
{
	if(pScrllBox != NULL && pArr != NULL)
	{
		bool bNoChannnel = true;
		HCHAR pCtemp[10] = {0};
		if(pCtemp == NULL)
			return ;
		HINT nItemCount = pScrllBox->GetListItemCount();
		if(m_nCurrentArea == 0 || m_nCurrentArea == 2)
		{
		for(HINT i= 0; i < nItemCount;i++)
		{
			if(pScrllBox->GetItemAt(i) != NULL && (pArr+i) != NULL)
			if(*(pArr+i) == 0)
			{
				//pScrllBox->GetItemAt(i)->SetText(L"存储");
				pScrllBox->GetItemAt(i)->SetText(s_pLan[12]);
			}
			else if(eRadioType == eAM)
			{
				bNoChannnel = false;
				memset(pCtemp,0,sizeof(pCtemp));
				swprintf_s(pCtemp,8,L"%d",*(pArr+i) );
				pScrllBox->GetItemAt(i)->SetText(pCtemp);
			}
			else
			{
				memset(pCtemp,0,sizeof(pCtemp));
				swprintf_s(pCtemp,8,L"%d.%d",(*(pArr+i))/10,(*(pArr+i))%10);
				bNoChannnel = false;
				/*else
				{
						swprintf_s(pCtemp,6,L"%d",(*(pArr+i))/10);
				}*/
				pScrllBox->GetItemAt(i)->SetText(pCtemp);
			}	
		}
		}
		else if(m_nCurrentArea == 1)
		{
			for(HINT i= 0; i < nItemCount;i++)
		{
			if(pScrllBox->GetItemAt(i) != NULL && (pArr+i) != NULL)
			if(*(pArr+i) == 0)
			{
				//pScrllBox->GetItemAt(i)->SetText(L"存储");
				pScrllBox->GetItemAt(i)->SetText(s_pLan[12]);

			}
			else if(eRadioType == eAM)
			{
				bNoChannnel = false;
				memset(pCtemp,0,sizeof(pCtemp));
				swprintf_s(pCtemp,8,L"%d",*(pArr+i) );
				pScrllBox->GetItemAt(i)->SetText(pCtemp);
			}
			else
			{
				memset(pCtemp,0,sizeof(pCtemp));
				int nLeft = (*(pArr+i))%100;
				if(nLeft >= 10)
				{
					swprintf_s(pCtemp,8,L"%d.%d",(*(pArr+i))/100,(*(pArr+i))%100);
				}
				else
				{
					swprintf_s(pCtemp,8,L"%d.0%d",(*(pArr+i))/100,(*(pArr+i))%100);
				}
				
				bNoChannnel = false;
				/*else
				{
						swprintf_s(pCtemp,6,L"%d",(*(pArr+i))/10);
				}*/
				pScrllBox->GetItemAt(i)->SetText(pCtemp);
			}	
		}
		}   
		if(bNoChannnel)
		{
			//m_pTxtAvailableChannel->SetText(s_pLan[9]);//无有效电台
			m_pTxtAvailableChannel->SetText(L" ");
		//	::PostMessage(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_RADIO_AVAILABLE_CHANNEL,HINT(0),(HINT)eRadioType);	
			RADIODEBUGINFO(L"VWM_RADIO_AVAILABLE_CHANNEL:wParam = 0,eRadioType = %d",eRadioType);
		}
		else
		{
			//m_pTxtAvailableChannel->SetText(L"无有效电台");
			m_pTxtAvailableChannel->SetText(L" ");
		//	::PostMessage(CEIPC_GetHWND(IPC_ID_MANAGE),VWM_RADIO_AVAILABLE_CHANNEL,HINT(1),(HINT)eRadioType);	
			RADIODEBUGINFO(L"VWM_RADIO_AVAILABLE_CHANNEL:wParam = 1,eRadioType = %d",eRadioType);
		}
	}
}
void HCRadioDlg::ChannelStoreAddChannel()
{
	sRadioSourceGroup *pSource=RadioSource::Instance()->GetRadioSource(GetHMIPath(_T("")).c_str()); 
	if(pSource != NULL)
	{
		for (HINT i = 0; i < MAXSTORECHANNEL;i++)
		{
			HCListItem* pTempListItemChannel = new HCListItem;
			pTempListItemChannel->Create(RADIO_CHANNEL_ITEM_WIDTH, RADIO_CHANNEL_ITEM_HEIGHT, NULL, _T("存储"));
			//pTempListItemChannel->SetEnableRoll(true, 1);
			pTempListItemChannel->SetTextStyle(RE_TS_CENTER);
			pTempListItemChannel->SetTextCenter(true);
			pTempListItemChannel->SetYPos(-9);
			pTempListItemChannel->SetText(_T("存储"));
			pTempListItemChannel->SetCanFocus(true);
			pTempListItemChannel->SetBkgndA(pSource->pSelectedItem);
			pTempListItemChannel->SetBkgndF(pSource->pSelectedItem);
			m_pScrboxChannelStore->AddListItem(pTempListItemChannel);
		}
	}
}
void HCRadioDlg::OnChannelAutoSearch(void* pDlg, void* param)
{
	HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	pObj->OnChannelAutoSearch(pObj);
}
void HCRadioDlg::OnChannelAutoSearch(void* pDlg)
{
	   if(m_bNoticeShow == FALSE  &&m_bAutoSearch ==false)
	   {
		   //m_pGrpCtrlRadioMiddle->EnableMsg(false);
		   //m_pGrpCtrlRadioBottom->EnableMsg(false);
		   //m_pScrboxChannelStore->EnableMsg(false);
		   //m_pTxt_Popup_Cover->SetShow(true);
		   UpDataRadioCtrlMessage(false);
		  // m_pGrpNotice->SetShow(true);
		   if(m_ctRefrench.IsActive())
		   {
			   m_ctRefrench.StopTimer();
		   }
		   m_ctRefrench.SetTime(200);
		   m_ctRefrench.StartTimer();
		   m_bNoticeShow = true;
		  // m_pTxtAvailableChannel->SetText(L"自动存储");
		   m_pTxtAvailableChannel->SetText(s_pLan[11]);
	   }
	   else
	   {
		  // m_pGrpCtrlRadioMiddle->EnableMsg(true);
		//   m_pTxt_Popup_Cover->SetShow(true);
		   /*m_pGrpCtrlRadioBottom->EnableMsg(true);
		   m_pScrboxChannelStore->EnableMsg(true);*/
		   //m_pGrpNotice->SetShow(true);
			UpDataRadioCtrlMessage(true);
#if RADIOCOMMANDQUEUE
		   ::PostMessage(m_hWnd,WM_USER + 50,eRADIOSTOPAUTOCHANNELSEARCH,0);
#else
		   HBYTE cCommand[10] = {0};
		   HUINT nlen = 0;
		   cCommand[nlen++] = 0x00;
		   cCommand[nlen++] = 0x01;
		   cCommand[nlen++] = 0x0B;	
		   IPCEVENT *pIpcEvent = new IPCEVENT;
		   pIpcEvent->pData = cCommand;
		   pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
		   pIpcEvent->uSize = nlen;
		   RadioSendData(IPC_ID_MANAGE,pIpcEvent);
		   SAFE_DELETE(pIpcEvent);
#endif
		   m_bAutoSearch = false;
		   //m_pBtnChannelAutoSearch->SetText(L"自动存台");
		   if(s_pLan != NULL)
		   {
			   m_pBtnChannelAutoSearch->SetText(s_pLan[2]);
		   }
	   }
}
HBOOL HCRadioDlg::DoMessage( HMessage* msg )
{
	if (NULL == msg)
	{
		return false;
	}
	HBOOL bRet = KDialogP::DoMessage(msg);

	switch(msg->msgtype)
	{
		case UWM_TOPBAR_BACK:
		{
			HWND hServerWnd = CEIPC_GetHWND(IPC_ID_MANAGE);
			if (NULL != hServerWnd)
			{
				::PostMessage(hServerWnd, UWM_TOPBAR_HOME, 0, 0);
			}	
		}
		break;
		case VWM_SERVER_KET_BTN:
			{
				switch((eKeyTypeNomal)(msg->lParam))
				{
				  case eKEY_UP:
					{
						OnNextSearch(NULL);
					}
					break;
				    case eKEY_DOWN:
					{
						OnPreSearch(NULL);
					}
					break;
					case eKEY_PLAY_CONTROL:
					{
						switch (msg->wParam)
						{
							case 0:
							{

							}
							break;
							case 1:
							{
								OnRadioUp(NULL);
							}
							break;
							case 2:
							{
								OnRadioDown(NULL);
							}
							break;
							default:
							break;
						}
					}
					break;
				//	case eKEY_FF:
				//	{
					//	OnRadioUp(NULL);
					//}
					//break;
					////case eKEY_FB:
				//	{
						//OnRadioDown(NULL);
				//	}
					//break;
					default:
					break;
				}
			}
			break;	
			case VWM_SERVER_CHANGE_MODE:
			{
				if(m_eRadioType == eFM)
				{
					OnAM();
				}
				else
				{
					OnFM();
				}
			}
			break;
	default:
	{
	}
	break;
	}
	return bRet;
}
void HCRadioDlg::ChangeTheme( HBYTE uType )
{
	// 设置背景
	KCLastMemory::GetInstance()->GetSetupMemory(g_SetupSetting);
	SetBackGround(GetHMIPath((HCHAR*)&g_SetupSetting.szBkgndPath));
	//SetDlgBkGnd();
	m_uThemeMode =  GetCurThemeMode();
}
eRADIOFEEDBACKSTATE HCRadioDlg::ParseRadioFeedBackStateType(HBYTE *cCommand)
{
	if(cCommand != NULL)
	{
		switch(*cCommand)
		{
		case 0x00:
			{
				return eCHANNNELSEARCHINGFB;
			}
			break;
		case 0x01:
			{
				return eSTSTATEFB;
			}
			break;
		case 0x02:
			{
				return eAMFMSTATEFB;
			}
			break;
		case 0x03:
			{
				return eCHANNELSTORESTATEFB;
			}
			break;
		case 0x04:
			{
				return eCHANNELCHANGESTATEFB;
			}
			break;
		default :
			return eUKNOWSTATEFB;
			break;
		}
	}
	return eUKNOWSTATEFB;
}
eRADIOCOMMANDTYPE  HCRadioDlg::ParseRadioCommandType(HBYTE *cCommand)
{
	if(cCommand != NULL)
	{
		switch((*cCommand))
		{
		case   0x00 :
			{
				return eENTERRADIOINTERFACE;
			}
			break;
		case   0x01 :
			{
				return eRADIOCHANNELCHANGE;
			}
			break;
		case   0x02 :
			{
				return eRADIOAMFMCHANNGE;
			}
			break;
		case   0x03 :
			{
				return eRADIOCHANNELSEARCH;
			}
			break;
		case   0x04 :
			{
				return eRADIOON;
			}
			break;
		case   0x05 :
			{
				return eRADIOCHANNELSTORE;
			}
			break;
		case   0x06 :
			{
				return eRADIOADJUST;
			}
			break;
		case   0x07 :
			{
				return eRADIOAUTOCHANNELSEARCH;
			}
			break;
		case   0x08 :
			{
				return eRADIOSCAN;
			}
			break;
		case   0x09 :
			{
				return eRADIOCHANNNELLISTS;
			}
			break;
		case   0x0A :
			{
				return eRADIOCHANNNELADJUST;
			}
			break;
		case   0x0B :
			{
				return eRADIOSTOPAUTOCHANNELSEARCH;
			}
			break;
		default :
			{
				return eRADIOUNKNOW;
			}
			break;
		}
	}
	return eRADIOUNKNOW;
}
HINT HCRadioDlg::HandRadioData(HBYTE *cCommand,HUINT nLen)
{
	if(cCommand != NULL && nLen >1)
	{
		if( *cCommand == 0x01)
		{
			cCommand++;
			eRADIOCOMMANDTYPE eCMDType = ParseRadioCommandType(cCommand);
			switch (eCMDType)
			{
			case  eENTERRADIOINTERFACE :
				{	
					RADIODEBUGINFO(L"eCMDType = eENTERRADIOINTERFACE");
					HandelEnterRadioInterface(cCommand,nLen-1);
				}
				break;
			case  eRADIOCHANNELCHANGE :
				{
					RADIODEBUGINFO(L"eCMDType = eRADIOCHANNELCHANGE");
					HandelRadioChannelChange(cCommand,nLen-1);
				}
				break;
			case  eRADIOAMFMCHANNGE :
				{
					RADIODEBUGINFO(L"eCMDType = eRADIOAMFMCHANNGE");
					HandelRadioAMFMChange(cCommand,nLen-1);
				}
				break;
			case  eRADIOCHANNELSEARCH :
				{
					RADIODEBUGINFO(L"eCMDType = eRADIOCHANNELSEARCH");
					HandelRadioChannelSearch(cCommand,nLen-1);
				}
				break;
			case  eRADIOON :
				{
					RADIODEBUGINFO(L"eCMDType = eRADIOON");
					HandelRadioOn(cCommand,nLen-1);
				}
				break;
			case  eRADIOCHANNELSTORE :
				{
					RADIODEBUGINFO(L"eCMDType = eRADIOCHANNELSTORE");
					HandelRadioChannelStore(cCommand,nLen-1);
				}
				break;
			case  eRADIOADJUST :
				{
					RADIODEBUGINFO(L"eCMDType = eRADIOADJUST");
					HandelRadioAdjust(cCommand,nLen-1);
				}
				break;
			case  eRADIOAUTOCHANNELSEARCH :
				{
					RADIODEBUGINFO(L"eCMDType = eRADIOAUTOCHANNELSEARCH");
					HandelRadioAutoSearch(cCommand,nLen-1);
				}
				break;
			case  eRADIOSCAN :
				{
					RADIODEBUGINFO(L"eCMDType = eRADIOSCAN");
					HandelRadioScan(cCommand,nLen-1);
				}
				break;
			case  eRADIOCHANNNELLISTS :
				{
					RADIODEBUGINFO(L"eCMDType = eRADIOCHANNNELLISTS");
					HandelRadioChannelLists(cCommand,nLen-1);
				}
				break;
			case  eRADIOCHANNNELADJUST :
				{
					RADIODEBUGINFO(L"eCMDType = eRADIOCHANNNELADJUST");
					HandelRadioChannelAdjust(cCommand,nLen-1);
				}
				break;
			case  eRADIOSTOPAUTOCHANNELSEARCH :
				{
					RADIODEBUGINFO(L"eCMDType = eRADIOSTOPAUTOCHANNELSEARCH");
					HandelRadioStopAutoSearch(cCommand,nLen-1);
				}
				break;
			default:
				break;
			}
		}
		if((*cCommand) == 0x82)
		{
			cCommand++;
			eRADIOFEEDBACKSTATE eStateFb = ParseRadioFeedBackStateType(cCommand);
			switch(eStateFb)
			{
			case eCHANNNELSEARCHINGFB:
				{
					//RADIODEBUGINFO(L"eCMDType = eCHANNNELSEARCHINGFB");
					HandelChannelSearchingFB(cCommand,nLen-1);
				}
				break;
			case eSTSTATEFB:
				{
					RADIODEBUGINFO(L"eCMDType = eSTSTATEFB");
					HandelSTStateFB(cCommand,nLen-1);
				}
				break;
			case eAMFMSTATEFB:
				{
					RADIODEBUGINFO(L"eCMDType = eAMFMSTATEFB");
					HandelAMFMStateFB(cCommand,nLen-1);
				}
				break;
			case eCHANNELSTORESTATEFB:
				{
					RADIODEBUGINFO(L"eCMDType = eCHANNELSTORESTATEFB");
					HandelChannelStoreFB(cCommand,nLen-1);
				}
				break;
			case eCHANNELCHANGESTATEFB:
				{
					RADIODEBUGINFO(L"eCMDType = eCHANNELCHANGESTATEFB");
					HandelChannelChangeStateFB(cCommand,nLen-1);
				}
				break;
			case eUKNOWSTATEFB:
				break;
			default:
				break;
			}
		}
	}
	UpData();
	return 0;
}
void  HCRadioDlg::HandelEnterRadioInterface(HBYTE *cCommand,HUINT nLen)
{
	m_eRadioWorkState = eRADIONARMAL;
	GetCurrentArea();
	if(nLen > 44 && cCommand != NULL)
	{
		HBYTE* pt =cCommand+1;
		HBYTE* ptEnd =cCommand +44;
		HUINT *pAutoStroedChannelBeg = NULL;
		if(nLen > 44 && (*pt) == 0xff)
		{
			pt++;
			if((*ptEnd) > 0x00 && (*ptEnd) < 0x80 )
			{
				m_eRadioType = eAM ;
				pAutoStroedChannelBeg = m_pAMStoredChannnel;
				m_nCurrentAMValue = HUINT(*pt)<<8;
				pt++;
				m_nCurrentAMValue +=HUINT(*pt);
				pt++;
			}
			else if((*ptEnd) > 0x80)
			{
				m_eRadioType = eFM ;
				m_nCurrentFMValue = HUINT(*pt)<<8;
				pt++;
				m_nCurrentFMValue +=HUINT(*pt);
				pt++;
				if(m_nCurrentArea != 1)
				{
					m_nCurrentFMValue =m_nCurrentFMValue/10;
				}
				pAutoStroedChannelBeg = m_pFMStoredChannnel;
			}
			else 
			{
				pt++;
				pt++;
			}
			if(pAutoStroedChannelBeg != NULL)
			{
				for(int i =0;i < 20;i++)
				{
					pAutoStroedChannelBeg[i] = (HUINT(*pt))<<8;
					pt++;
					pAutoStroedChannelBeg[i] += (HUINT(*pt));
					pt++;
					if(m_eRadioType == eFM)
					{
						if(m_nCurrentArea != 1)
						{
							pAutoStroedChannelBeg[i]=pAutoStroedChannelBeg[i]/10;
						}
					}
				}
			}
		}	
	}
	sRadioSourceGroup *pSource=RadioSource::Instance()->GetRadioSource(GetHMIPath(_T("")).c_str()); 
	if(pSource != NULL)
	{
		if(m_eRadioType == eFM)
		{
			m_pBtnTopScale->SetBkgndN(pSource->pFmScale);
			switch (m_nCurrentArea)
			{
				case 0:
				{
					   m_pSliderChannelScan->SetBound(860,1080);
				}
				break;
				case  1:
					{
						m_pSliderChannelScan->SetBound(8600,10800);
					}
				break;
				case 2:
					{
						m_pSliderChannelScan->SetBound(860,1080);
					}
					break;
			}
			
			m_pTxtRadioUnit->SetText(L"MHz");
			m_pTxtRadioType->SetText(L"FM");
		}
		else
		{
			m_pBtnTopScale->SetBkgndN(pSource->pAmScale);
			
			switch (m_nCurrentArea)
			{
			case 0:
				{
					m_pSliderChannelScan->SetBound(531,1631);
				}
				break;
			case  1:
				{
					m_pSliderChannelScan->SetBound(531,1631);
				}
				break;
			case 2:
				{
					m_pSliderChannelScan->SetBound(531,1631);
				}
				break;
			}
			m_pTxtRadioUnit->SetText(L"KHz");
			m_pTxtRadioType->SetText(L"AM");
		}
	}
	UpDataRadioLisitem(m_eRadioType);
	m_bAutoSearch = false;
	//m_pBtnChannelAutoSearch->SetText(L"自动存台");
	if(s_pLan != NULL)
	{
		m_pBtnChannelAutoSearch->SetText(s_pLan[2]);
	}
	UpDataCurrentValue();
}
void  HCRadioDlg::HandelRadioChannelChange(HBYTE *cCommand,HUINT nLen)
{
}
void HCRadioDlg::HandelRadioAMFMChange(HBYTE *cCommand,HUINT nLen)
{
	HandelEnterRadioInterface(cCommand,nLen);
}
void HCRadioDlg::HandelRadioChannelSearch(HBYTE *cCommand,HUINT nLen)
{
}
void HCRadioDlg::HandelRadioOn(HBYTE *cCommand,HUINT nLen)
{
}
void HCRadioDlg::HandelRadioChannelStore(HBYTE *cCommand,HUINT nLen)
{
}
void HCRadioDlg::HandelRadioAdjust(HBYTE *cCommand,HUINT nLen)
{
	HBYTE *pt = cCommand;
	if( cCommand != NULL && nLen > 3 && (*(pt+1) == 0xff))
	{
		pt = cCommand +2;
		if(m_eRadioType == eFM)
		{
			m_nCurrentFMValue = HUINT((*pt)<<8 );
			pt++;
			m_nCurrentFMValue +=HUINT((*pt));
			if(m_nCurrentArea != 1)
			{
				m_nCurrentFMValue = m_nCurrentFMValue/10;
			}
		}
		if(m_eRadioType == eAM)
		{
			m_nCurrentAMValue = HUINT((*pt)<<8 );
			pt++;
			m_nCurrentAMValue +=HUINT((*pt));
		}
	}
}
void HCRadioDlg::HandelRadioAutoSearch(HBYTE *cCommand,HUINT nLen)
{
}
void HCRadioDlg::HandelRadioScan(HBYTE *cCommand,HUINT nLen)
{
}
void HCRadioDlg::HandelRadioChannelLists(HBYTE *cCommand,HUINT nLen)
{
	HandelEnterRadioInterface(cCommand,nLen);
}
void HCRadioDlg::HandelRadioChannelAdjust(HBYTE *cCommand,HUINT nLen)
{
}
void HCRadioDlg::HandelRadioStopAutoSearch(HBYTE *cCommand,HUINT nLen)
{
}
void HCRadioDlg::HandelChannelSearchingFB(HBYTE *cCommand,HUINT nLen)
{
	
	if(cCommand != NULL && nLen >=4)
	{
		HBYTE *pt = cCommand +1;
		HUINT *pCurrentValue = GetCurrentRadioValueAddress();
		/*HUINT nValue = 0;
		 nValue = HUINT((*pt)<<8) + HUINT(*(pt + 1));
		 RADIODEBUGINFO(L"%s,nValue = %d,m_eRadioType = %d",__FUNCTIONW__,nValue,m_eRadioType);*/
		if(pCurrentValue !=  NULL)
		{
			if(m_eRadioType == eFM)
			{
				
				// if(nValue >= 8750 && nValue <= 10800)
				 {
					 *pCurrentValue = HUINT(*pt)<<8;
					 pt++; 
					 *pCurrentValue +=  HUINT(*pt);
					 if(m_eRadioType == eFM)
					 {
						 if(m_nCurrentArea != 1)
						 {
							(*pCurrentValue) = (*pCurrentValue)/10;
						 }	 
					 }
				 }
			}
			else
			{
				//if(nValue >= 531 && nValue <= 1631)
				{
					*pCurrentValue = HUINT(*pt)<<8;
					pt++; 
					*pCurrentValue +=  HUINT(*pt);
				}
			}
			
		}	
		pt = cCommand + 3;
		if((*pt) == 0x00)
		{
			m_eRadioWorkState = eRADIONARMAL;
		}
		else if((*pt) == 0x01)
		{
			m_eRadioWorkState = eRADIOCHANNELSREACHING;	
		}
		else if((*pt) == 0x03)
		{
			m_eRadioWorkState = eRADIOAUTOSTORE;
		}
		else if((*pt) == 0x02)
		{
			m_eRadioWorkState = eRADIOSCANSTATE;
		}
		RADIODEBUGINFO(L"m_eRadioWorkState = %d",m_eRadioWorkState);
	}
}
void HCRadioDlg::HandelSTStateFB(HBYTE *cCommand,HUINT nLen)
{
	if(cCommand != NULL && nLen >=0)
	{
		HBYTE *pt = cCommand +1;
		
		if(((*pt) & 0x01) == 0 )
		{
			m_bST = false;
		}
		else
		{
			m_bST = true;
		}
	}
}
void HCRadioDlg::HandelAMFMStateFB(HBYTE *cCommand,HUINT nLen)
{
	if(cCommand != NULL && nLen >43)
	{
		HBYTE *pt = cCommand +1;//当前频率
		HBYTE *ptEnd = cCommand +43;
		HUINT *pStroedChannelBeg = NULL;
		if((*ptEnd) > 0x00 && (*ptEnd) < 0x80)
		{
			m_eRadioType = eAM;
			pStroedChannelBeg = m_pAMStoredChannnel;
			m_nCurrentAMValue = HUINT(*pt)<<8;
			pt++;
			m_nCurrentAMValue +=HUINT(*pt);
			pt++;
		}
		else if ((*ptEnd) >= 0x80 && (*ptEnd) < 0xff)
		{
			m_eRadioType = eFM;
			pStroedChannelBeg = m_pFMStoredChannnel;
			m_nCurrentFMValue = HUINT(*pt)<<8;
			pt++;
			m_nCurrentFMValue +=HUINT(*pt);
			pt++;
			if(m_nCurrentArea != 1)
			{
				m_nCurrentFMValue = m_nCurrentFMValue/10;
			}
		}
		else 
		{
			pt++;
			pt++;
		}
		if(pStroedChannelBeg != NULL)
		{
			for(int i =0;i < 20;i++)
			{
				pStroedChannelBeg[i] = (HUINT(*pt))<<8;
				pt++;
				pStroedChannelBeg[i] += (HUINT(*pt));
				pt++;
				if(m_eRadioType == eFM && m_nCurrentArea != 1)
				{
					pStroedChannelBeg[i] /= 10;
				}
			}
		}
		sRadioSourceGroup *pSource = RadioSource::Instance()->GetRadioSource(GetHMIPath(_T("")).c_str());
		if(pSource != NULL)
		{
			if(m_eRadioType == eFM)
			{
				m_pBtnTopScale->SetBkgndN(pSource->pFmScale);
			}
			else
			{
				m_pBtnTopScale->SetBkgndN(pSource->pAmScale);
			}
		}
		UpDataRadioLisitem(m_eRadioType);
		
		m_bAutoSearch = false;
		//m_pBtnChannelAutoSearch->SetText(L"自动存台");
		if(s_pLan != NULL)
		{
			m_pBtnChannelAutoSearch->SetText(s_pLan[2]);
		}
		//UpdataRadioWindow();
	}	
}
void HCRadioDlg::HandelChannelStoreFB(HBYTE *cCommand,HUINT nLen)
{
	HINT index  = -1;
	if(cCommand != NULL && nLen >3)
	{
		HBYTE *pt = cCommand +1;
		HUINT *pChannelStore = NULL;
		if((*pt) > 0x00 && (*pt) < 0x80)
		{
			m_eRadioType = eAM;
			index = (*pt) - 0x01;
			pChannelStore = m_pAMStoredChannnel+((*pt) - 0x01);
		}

		else if(*pt > 0x80 && *pt < 0xff)
		{
			m_eRadioType = eFM;
			index = (*pt) - 0x81;
			pChannelStore = m_pFMStoredChannnel+((*pt) - 0x81);
		}
		if(pChannelStore != NULL)
		{
			pt = cCommand+2;
			*pChannelStore =((HUINT) (*pt))<<8;
			pt++;
			(*pChannelStore) += (HUINT)(*pt);
			if(m_eRadioType == eFM)
			{
				if(m_nCurrentArea != 1)
				{
					(*pChannelStore) /= 10;
				}
				
			}

			HCHAR pCtemp[9] = {0};
		   
				if(m_pScrboxChannelStore->GetItemAt(index) != NULL )
					if(*(pChannelStore) == 0)
					{
						m_pScrboxChannelStore->GetItemAt(index)->SetText(L"存储");
					}
					else if(m_eRadioType == eAM)
					{
						memset(pCtemp,0,sizeof(pCtemp));
						swprintf_s(pCtemp,6,L"%d",*(pChannelStore) );
						m_pScrboxChannelStore->GetItemAt(index)->SetText(pCtemp);
					}
					else
					{
						memset(pCtemp,0,sizeof(pCtemp));
						/*if((*pChannelStore)%10 != 0)
						{*/
						if(m_nCurrentArea != 1)
						{
							swprintf_s(pCtemp,8,L"%d.%d",(*pChannelStore)/10,(*pChannelStore)%10);
						}
						else
						{
							swprintf_s(pCtemp,8,L"%d.%-2d",(*pChannelStore)/100,(*pChannelStore)%100);
						}
							
					/*	}
						else
						{
							swprintf_s(pCtemp,6,L"%d",(*pChannelStore)/10);
						}*/
						m_pScrboxChannelStore->GetItemAt(index)->SetText(pCtemp);
					}
			//UpDataRadioLisitem(m_eRadioType);
		}
	//UpdataRadioWindow();
	}
}
void HCRadioDlg::HandelChannelChangeStateFB(HBYTE *cCommand,HUINT nLen)
{
	sRadioSourceGroup *pSource = RadioSource::Instance()->GetRadioSource(GetHMIPath(_T("")).c_str());
	if(cCommand != NULL && nLen >3 && pSource != NULL)
	{
		HBYTE *pt = cCommand +3;
		HUINT *pCurrent = NULL;
		if((*pt) > 0x00 && (*pt) < 0x80)
		{
			if(m_eRadioType == eFM)
			{
				m_pBtnTopScale->SetBkgndN(pSource->pAmScale);
			}
			m_eRadioType = eAM;
			pCurrent = &m_nCurrentAMValue;
		}

		else if(*pt > 0x80 && *pt < 0xff)
		{
			if(m_eRadioType == eAM)
			{
				m_pBtnTopScale->SetBkgndN(pSource->pFmScale);
			}
			m_eRadioType = eFM;
			pCurrent = &m_nCurrentFMValue;
		}
		//pCurrent = GetCurrentRadioValueAddress();
		if(pCurrent != NULL)
		{
			pt = cCommand + 1;
			(*pCurrent) = (HUINT(*pt))<<8;
			pt++;
			(*pCurrent) +=  (HUINT(*pt));
			//UpdataRadioWindow();
			if(m_eRadioType == eFM)
			{
				(*pCurrent) /= 10; 
			}
		}	
	}	
}
void HCRadioDlg::UpData(void)
{
	UpdataRadioWindow();
    //UpDataRadioLisitem(m_eRadioType);
	UpDataSelectRadioListem();
	//Sleep(0);
	//UpdateWindow();
}
 HUINT* HCRadioDlg::GetCurrentRadioValueAddress()
{
	if(m_eRadioType == eAM)
		return &m_nCurrentAMValue;
	if(m_eRadioType == eFM)
		return &m_nCurrentFMValue;
	else
		return NULL;
}
void HCRadioDlg::UpdataRadioWindow()
{
	//if((GetTickCount() - m_dwNowTime) > 60 )
	//{
		//RADIODEBUGINFO(L"m_eRadioType = %d",m_eRadioType);
	//if(m_eRadioWorkState != eRADIOCHANNELSREACHING)
	if(m_eRadioWorkState == eRADIONARMAL)
	{
		m_pBtnChannelAutoSearch->SetTextColorN(255,255,255);
		m_pBtnScan->SetTextColorN(255,255,255);
		//EnableUpdateRect(false);
		if(m_eRadioType == eAM)
		{
			m_pSliderChannelScan->SetValue(m_nCurrentAMValue);
			memset(m_cRadioCurrentAMValue,0,sizeof(m_cRadioCurrentAMValue));
			swprintf_s(m_cRadioCurrentAMValue,sizeof(m_cRadioCurrentAMValue)/2,L"%d",m_nCurrentAMValue);
			UpDataCurrentValue();
			//m_pTxtRadioUnit->SetText(L"KHz");
			//m_pTxtRadioType->SetText(L"AM");
			m_pSwBtAMFM->SetButtonIndex(0);
			//RADIODEBUGINFO(L"%s,m_nCurrentAMValue = %d m_eRadioWorkState = %d",__FUNCTIONW__,m_nCurrentAMValue,m_eRadioWorkState);
		}
		else
		{
			m_pSliderChannelScan->SetValue(m_nCurrentFMValue);
			memset(m_cRadioCurrentFMValue, 0, sizeof(m_cRadioCurrentFMValue));
			swprintf_s(m_cRadioCurrentFMValue,sizeof(m_cRadioCurrentFMValue)/2,L"%d.%d",m_nCurrentFMValue/10,m_nCurrentFMValue%10);
			UpDataCurrentValue();	
			//RADIODEBUGINFO(L"[HCRadioDlg::UpdataRadioWindow] m_nCurrentFMValue(%d) %s" ,m_nCurrentFMValue,m_cRadioCurrentFMValue);
			//m_pTxtRadioUnit->SetText(L"MHz");
			//m_pTxtRadioType->SetText(L"FM");
			m_pSwBtAMFM->SetButtonIndex(1);
		//	RADIODEBUGINFO(L"%s,m_nCurrentFMValue = %d,m_eRadioWorkState = %d",__FUNCTIONW__,m_nCurrentFMValue,m_eRadioWorkState);
			//	m_pSliderChannelScan->Invalidate();
		}
		if(m_bST == true && m_eRadioType == eFM)
		{
			//m_pTxtSTstate->SetText(L"ST");
			m_pTxtSTstate->SetText(s_pLan[10]);
		}
		else
		{
			m_pTxtSTstate->SetText(L" ");
		}
		if(m_eRadioWorkState == eRADIOCHANNELSREACHING)
		{
			if(s_pLan != NULL)
			{
				//RADIODEBUGINFO(L"正在搜台");
				m_pTxtRadioMessage->SetText(s_pLan[8]);
			/*	if(!(m_pTxtRadioMessage->IsShow()))
				{
					m_pTxtRadioMessage->SetShow(true);
				}*/
			}
			//m_pTxtRadioMessage->SetText(L"正在搜台");
		}
		else
		{
			m_pTxtRadioMessage->SetText(L" ");
			/*if(m_pTxtRadioMessage->IsShow())
			{
				m_pTxtRadioMessage->SetShow(false);
			}*/
		}
		m_dwNowTime = GetTickCount();
		//EnableUpdateRect(true);
	}
	else
	{
		if((GetTickCount() - m_dwNowTime) > 100)
		{
			//EnableUpdateRect(false);
			if(m_eRadioType == eAM)
			{
				m_pSliderChannelScan->SetValue(m_nCurrentAMValue);
				memset(m_cRadioCurrentAMValue,0,sizeof(m_cRadioCurrentAMValue));
				swprintf_s(m_cRadioCurrentAMValue,sizeof(m_cRadioCurrentAMValue)/2,L"%d",m_nCurrentAMValue);
				UpDataCurrentValue();
				//m_pTxtRadioUnit->SetText(L"KHz");
				//m_pTxtRadioType->SetText(L"AM");
				m_pSwBtAMFM->SetButtonIndex(0);
				//RADIODEBUGINFO(L"%s,m_nCurrentAMValue = %d,m_eRadioWorkState = %d",__FUNCTIONW__,m_nCurrentAMValue,m_eRadioWorkState);
			}
			else
			{
				m_pSliderChannelScan->SetValue(m_nCurrentFMValue);
				memset(m_cRadioCurrentFMValue, 0, sizeof(m_cRadioCurrentFMValue));
				swprintf_s(m_cRadioCurrentFMValue,sizeof(m_cRadioCurrentFMValue)/2,L"%d.%d",m_nCurrentFMValue/10,m_nCurrentFMValue%10);
				UpDataCurrentValue();	
				//RADIODEBUGINFO(L"[HCRadioDlg::UpdataRadioWindow] m_nCurrentFMValue(%d) %s" ,m_nCurrentFMValue,m_cRadioCurrentFMValue);
				//m_pTxtRadioUnit->SetText(L"MHz");
				//m_pTxtRadioType->SetText(L"FM");
				m_pSwBtAMFM->SetButtonIndex(1);
				//RADIODEBUGINFO(L"%s,m_nCurrentFMValue = %d,m_eRadioWorkState = %d",__FUNCTIONW__,m_nCurrentFMValue,m_eRadioWorkState);
				//	m_pSliderChannelScan->Invalidate();
			}
			if(m_bST == true && m_eRadioType == eFM)
			{
				m_pTxtSTstate->SetText(s_pLan[10]);
			}
			else
			{
				m_pTxtSTstate->SetText(L" ");
			}
			if(m_eRadioWorkState == eRADIOCHANNELSREACHING)
			{
				if(s_pLan != NULL)
				{
					//RADIODEBUGINFO(L"正在搜台");
					m_pTxtRadioMessage->SetText(s_pLan[8]);
					/*if(!(m_pTxtRadioMessage->IsShow()))
					{
						m_pTxtRadioMessage->SetShow(true);
					}*/
				}
				//m_pTxtRadioMessage->SetText(L"正在搜台");
			}
			else if(m_eRadioWorkState == eRADIOAUTOSTORE)
			{
				m_pTxtRadioMessage->SetText(s_pLan[11]);
			}
			else if(m_eRadioWorkState == eRADIOSCANSTATE)
			{
				m_pTxtRadioMessage->SetText(s_pLan[1]);
			}
			else
			{
				m_pTxtRadioMessage->SetText(L" ");
			}
			//EnableUpdateRect(true);
		}
	}
	 // m_eRadioWorkState = eRADIONARMAL;
}
void HCRadioDlg::OnRadioUp(void* pDlg, void* param)
{
	HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	pObj->OnRadioUp(pObj);
}
void HCRadioDlg::OnRadioUp(void* pDlg)
{
	/*if(m_nCurrentLange == 0)
	{
		ChangeLangue(1);
	}
	else
	{
		ChangeLangue(0);
	}*/
	//	HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	/*
		if(m_eRadioType == eFM)
		{
			m_nCurrentFMValue +=1;
			if(m_nCurrentFMValue >= 1080)
				m_nCurrentFMValue = 1080;
			m_pSliderChannelScan->SetValue(m_nCurrentFMValue);
			swprintf_s(m_cRadioCurrentFMValue,sizeof(m_cRadioCurrentFMValue)/2,L"%d.%d",m_nCurrentFMValue/10,m_nCurrentFMValue%10);
			m_pTxtRadioCurrentValue->SetText(m_cRadioCurrentFMValue);
			HBYTE cCommand[10] = {0};
			unsigned long nlen = 0;
			cCommand[nlen++]= 0x00;
			cCommand[nlen++]= 0x01;
			cCommand[nlen++] = 0x0a;
			cCommand[nlen++] = HI_BYTE(m_nCurrentFMValue*10);
			cCommand[nlen++] = LO_BYTE(m_nCurrentFMValue*10);
			//SendProtocolData(cCommand,3);
			IPCEVENT *pIpcEvent = new IPCEVENT;
			pIpcEvent->pData = cCommand;
			pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
			pIpcEvent->uSize = nlen;
			RadioSendData(IPC_ID_MANAGE,pIpcEvent);
			SAFE_DELETE(pIpcEvent);
		}
		else
		{
			m_nCurrentAMValue += 9;
			if(m_nCurrentAMValue >= 1602)
				m_nCurrentAMValue = 1602;
			m_pSliderChannelScan->SetValue(m_nCurrentAMValue);
			swprintf_s(m_cRadioCurrentAMValue,sizeof(m_cRadioCurrentAMValue)/2,L"%d",m_nCurrentAMValue);
			m_pTxtRadioCurrentValue->SetText(m_cRadioCurrentAMValue);
			*/
			if(m_bAutoSearch == true)
			{
				m_bAutoSearch = false;
				//m_pBtnChannelAutoSearch->SetText(L"自动存台");
				if(s_pLan != NULL)
				{
					m_pBtnChannelAutoSearch->SetText(s_pLan[2]);
				}
			}
#if RADIOCOMMANDQUEUE
			::PostMessage(m_hWnd,WM_USER + 50,eRADIOADJUST,0);
#else
			unsigned long nlen = 0;
			HBYTE cCommand[10] = {0};
			cCommand[nlen++] = 0x00;
			cCommand[nlen++] = 0x01;
			cCommand[nlen++] = 0x06;
			cCommand[nlen++] = 0x00;
			//	cCommand[nlen++] = HI_BYTE(m_nCurrentAMValue);
			//cCommand[nlen++] = LO_BYTE(m_nCurrentAMValue);
			IPCEVENT *pIpcEvent = new IPCEVENT;
			pIpcEvent->pData = cCommand;
			pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
			pIpcEvent->uSize = nlen;
			RadioSendData(IPC_ID_MANAGE,pIpcEvent);
			SAFE_DELETE(pIpcEvent);
#endif
		//}
}
void HCRadioDlg::OnRadioDown(void* pDlg, void* param)
{
	HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	pObj->OnRadioDown(pObj);
}
void HCRadioDlg::OnRadioDown(void* pDlg)
{
	/*
	if(m_eRadioType == eFM)
	{
		m_nCurrentFMValue -=1;
		if(m_nCurrentFMValue <= 870)
		{
			m_nCurrentFMValue = 870;
		}
		m_pSliderChannelScan->SetValue(m_nCurrentFMValue);
		swprintf_s(m_cRadioCurrentFMValue,sizeof(m_cRadioCurrentFMValue)/2,L"%d.%d",m_nCurrentFMValue/10,m_nCurrentFMValue%10);
		m_pTxtRadioCurrentValue->SetText(m_cRadioCurrentFMValue);
		HBYTE cCommand[10] = {10};
		*/
	//	unsigned long nlen = 0;
		//cCommand[nlen++] = 0x00;
		//cCommand[nlen++] = 0x01;
		//cCommand[nlen++] = 0x0a;
		//cCommand[nlen++] = HI_BYTE(m_nCurrentFMValue*10);
		//cCommand[nlen++] = LO_BYTE(m_nCurrentFMValue*10);
		if(m_bAutoSearch == true)
		{
			m_bAutoSearch = false;
			//m_pBtnChannelAutoSearch->SetText(L"自动存台");
			if(s_pLan != NULL)
			{
				m_pBtnChannelAutoSearch->SetText(s_pLan[2]);
			}
		}
#if RADIOCOMMANDQUEUE
		::PostMessage(m_hWnd,WM_USER + 50,eRADIOADJUST,1);
#else
		unsigned long nlen = 0;
		HBYTE cCommand[10] = {0};
		cCommand[nlen++] = 0x00;
		cCommand[nlen++] = 0x01;
		cCommand[nlen++] = 0x06;
		cCommand[nlen++] = 0x01;
		//SendProtocolData(cCommand,3);
		IPCEVENT *pIpcEvent = new IPCEVENT;
		pIpcEvent->pData = cCommand;
		pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
		pIpcEvent->uSize = nlen;
		RadioSendData(IPC_ID_MANAGE,pIpcEvent);
		SAFE_DELETE(pIpcEvent);
#endif
	/*
	}
	else
	{
		m_nCurrentAMValue -= 9;
		if(m_nCurrentAMValue <= 531)
		{
			m_nCurrentAMValue = 531;
		}
		m_pSliderChannelScan->SetValue(m_nCurrentAMValue);
		swprintf_s(m_cRadioCurrentAMValue,sizeof(m_cRadioCurrentAMValue)/2,L"%d",m_nCurrentAMValue);
		m_pTxtRadioCurrentValue->SetText(m_cRadioCurrentAMValue);
		unsigned long nlen = 0;
		HBYTE cCommand[10] = {};
		cCommand[nlen++] = 0x00;
		cCommand[nlen++] = 0x01;
		cCommand[nlen++] = 0x0a;
		cCommand[nlen++] = HI_BYTE(m_nCurrentAMValue);
		cCommand[nlen++] = LO_BYTE(m_nCurrentAMValue);
		IPCEVENT *pIpcEvent = new IPCEVENT;
		pIpcEvent->pData = cCommand;
		pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
		pIpcEvent->uSize = nlen;
		RadioSendData(IPC_ID_MANAGE,pIpcEvent);
		SAFE_DELETE(pIpcEvent);	
	}
	*/
}
void HCRadioDlg::OnScrboxChannelLists(void* pDlg,void* param)
{
	HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	pObj->OnScrboxChannelLists(pObj);
}
void HCRadioDlg::OnScrboxChannelLists(void* pDlg)
{
	/*
//	HCListItemBase *pListItemSelect = m_pScrboxChannnelLists->GetSelectListItem();
	HINT iSelectIndex = m_pScrboxChannnelLists->GetListItemIndex(pListItemSelect);
	if(m_iScrctrlChannnelLists == iSelectIndex)
	{
		HString	sLisitem= pListItemSelect->GetText();
		if (sLisitem[0] == L'存')
		{
			if(m_eRadioType == eAM)
			{
				*(m_pAMChannnelLists + iSelectIndex) = m_nCurrentAMValue;

				//UpDataLisitem(m_pScrboxChannnelLists,m_pAMChannnelLists,eAM);
			}
			else
			{
				*(m_pFMChannnelLists + iSelectIndex) = m_nCurrentFMValue;

				//UpDataLisitem(m_pScrboxChannnelLists,m_pFMChannnelLists,eFM);
			}

		}	
		else
		{
			if(m_eRadioType == eAM)
			{
				m_nCurrentAMValue = *(m_pAMChannnelLists + iSelectIndex) ;
				swprintf_s(m_cRadioCurrentAMValue,6,L"%d",m_nCurrentAMValue );
				m_pTxtRadioCurrentValue->SetText(m_cRadioCurrentAMValue);
				m_pSliderChannelScan->SetValue(m_nCurrentAMValue);
			}
			else
			{
				m_nCurrentFMValue = *(m_pFMChannnelLists + iSelectIndex);
				swprintf_s(m_cRadioCurrentFMValue,6,L"%d.%d",m_nCurrentFMValue/10, m_nCurrentFMValue%10);
				m_pTxtRadioCurrentValue->SetText(m_cRadioCurrentFMValue);
				m_pSliderChannelScan->SetValue(m_nCurrentFMValue);
			}
		}
	}
	else 
	{
		m_iScrctrlChannnelLists = iSelectIndex;
	}
	if(m_iScrctrlChannnelLists >= 0)
	{
		m_pScrboxChannnelLists->SetSelectListItem(m_iScrctrlChannnelLists, false);
	}
	*/
}

void HCRadioDlg::RadioSendData(__in unsigned char uID,__in LPIPCEVENT pIPCevent)
{
	if(pIPCevent != NULL && pIPCevent->pData != NULL && pIPCevent->uSize >0)
	{
#if INFOMESSAGE
		WCHAR tmpBuf[1024] = {0};
		for (int i = 0; i < pIPCevent->uSize; ++i)
		{
			swprintf_s(tmpBuf, 1023, L"%s %02x", tmpBuf, pIPCevent->pData[i]);
		}
		RADIODEBUGINFO(L"[%s]%s,uSize=%d",__FUNCTIONW__,tmpBuf,pIPCevent->uSize);
#else
#endif
		CEIPC_SendEvent(uID,pIPCevent);
		RADIODEBUGINFO(L"++++++++++++++++++++");
	}
}
void HCRadioDlg::OnAMFM(HINT nPos)
{
	if(m_bAutoSearch == true)
	{
		m_bAutoSearch = false;
		//m_pBtnChannelAutoSearch->SetText(L"自动存台");
		if(s_pLan != NULL)
		{
			m_pBtnChannelAutoSearch->SetText(s_pLan[2]);
		}
	}
	if(nPos == 0)
	{
		OnFM();
	}
	if(nPos == 1)
	{
		OnAM();
	}
}
 void HCRadioDlg::OnAMFM(void *pDlg,HINT nPos)
{
	HCRadioDlg *pObj = static_cast<HCRadioDlg*>(pDlg);
	pObj->OnAMFM(nPos);
}

 void HCRadioDlg::OnConfirm(void* pDlg, void* param)
 {
	 HCRadioDlg *pObj = static_cast<HCRadioDlg*>(pDlg);
	 pObj->OnConfirm(pObj);
 }
 void HCRadioDlg::OnConfirm(void* pDlg)
 {
#if RADIOCOMMANDQUEUE
	 ::PostMessage(m_hWnd,WM_USER + 50,eRADIOAUTOCHANNELSEARCH,0);
#else
	 HBYTE cCommand[10] = {0};
	 HUINT nlen = 0;
	 cCommand[nlen++] = 0x00;
	 cCommand[nlen++] = 0x01;
	 cCommand[nlen++] = 0x07;	
	 IPCEVENT *pIpcEvent = new IPCEVENT;
	 pIpcEvent->pData = cCommand;
	 pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
	 pIpcEvent->uSize = nlen;
	 RadioSendData(IPC_ID_MANAGE,pIpcEvent);
	 SAFE_DELETE(pIpcEvent);
#endif
	 //m_pGrpCtrlRadioMiddle->EnableMsg(true);
	// m_pGrpCtrlRadioBottom->EnableMsg(true);
	// m_pScrboxChannelStore->EnableMsg(true);
	 UpDataRadioCtrlMessage(true);
	 m_bAutoSearch = true;
	 //m_pBtnChannelAutoSearch->SetText(L"停止搜台");
	 if(s_pLan != NULL)
	 {
		 m_pBtnChannelAutoSearch->SetText(s_pLan[7]);
	 }
	// m_pGrpNotice->SetShow(false);
	 m_bNoticeShow = false;
 }
void HCRadioDlg::OnCannel(void* pDlg, void* param)
 {
	 HCRadioDlg *pObj = static_cast<HCRadioDlg*>(pDlg);
	 pObj->OnCannel(pObj);
 }
 void HCRadioDlg::OnCannel(void* pDlg)
 {
	// m_pGrpCtrlRadioMiddle->EnableMsg(false);
	//m_pGrpCtrlRadioBottom->EnableMsg(true);
	//m_pScrboxChannelStore->EnableMsg(true);
	  UpDataRadioCtrlMessage(true);
	// m_pGrpNotice->SetShow(false);
	 m_bNoticeShow = false;
 }
 HUINT HCRadioDlg::IsStored(HUINT *pChannel,HUINT uChannelValue)
 {
	 if(pChannel != NULL && uChannelValue > 0)
	 {
		HUINT nStored = 0;
		HUINT i = 0;
		while(pChannel[i] != uChannelValue && i < 20)
		{
			i++;
		}
		if(i == 20)
		{
			return 0;
		}
		else
		{
			return (i + 1);
		}
	 }
	 return 0;
 }
 void HCRadioDlg::UpDataRadioCtrlMessage(bool bAble)
 {
		if(bAble)
		{
			//m_pGrpCtrlRadioMiddle->EnableMsg(true);
			m_pScrctrlChannelStore->EnableMsg(true);
			m_pScrboxChannelStore->EnableMsg(true);
			m_pSliderChannelScan->EnableMsg(true);
			m_pGrpCtrlRadioBottom->EnableMsg(true);
		}
		else
		{
			m_pScrctrlChannelStore->EnableMsg(false);
			m_pScrboxChannelStore->EnableMsg(false);
			m_pSliderChannelScan->EnableMsg(false);
			//m_pGrpCtrlRadioMiddle->EnableMsg(false);
			m_pGrpCtrlRadioBottom->EnableMsg(false);
		}
 }
 void HCRadioDlg::OnPreSearch(void* pDlg, void* param)
 {
	 HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	 pObj->OnPreSearch(pObj);
 }
 void HCRadioDlg::OnPreSearch(void* pDlg)
 {
	 if(m_bAutoSearch == true)
	 {
		 m_bAutoSearch = false;
		 //m_pBtnChannelAutoSearch->SetText(L"自动存台");
		 if(s_pLan != NULL)
		 {
			 m_pBtnChannelAutoSearch->SetText(s_pLan[2]);
		 }
	 }
#if RADIOCOMMANDQUEUE
	 ::PostMessage(m_hWnd,WM_USER + 50,eRADIOCHANNELSEARCH,0);
#else
	 unsigned long nlen = 0;
	 HBYTE cCommand[10] = {0};
	 cCommand[nlen++] = 0x00;
	 cCommand[nlen++] = 0x01;
	 cCommand[nlen++] = 0x03;
	 cCommand[nlen++] = 0x00;
	 //SendProtocolData(cCommand,3);
	 IPCEVENT *pIpcEvent = new IPCEVENT;
	 pIpcEvent->pData = cCommand;
	 pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
	 pIpcEvent->uSize = nlen;
	 RadioSendData(IPC_ID_MANAGE,pIpcEvent);
	 SAFE_DELETE(pIpcEvent);
#endif
 }
 void HCRadioDlg::OnNextSearch(void* pDlg, void* param)
 {
	 HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	 pObj->OnNextSearch(pObj);
 }
 void HCRadioDlg::OnNextSearch(void* pDlg)
 {
	 if(m_bAutoSearch == true)
	 {
		 m_bAutoSearch = false;
		 //m_pBtnChannelAutoSearch->SetText(L"自动存台");
		 if(s_pLan != NULL)
		 {
			 m_pBtnChannelAutoSearch->SetText(s_pLan[2]);
		 }
	 }
#if RADIOCOMMANDQUEUE
	 ::PostMessage(m_hWnd,WM_USER + 50,eRADIOCHANNELSEARCH,0x01);
#else
	 unsigned long nlen = 0;
	 HBYTE cCommand[10] = {0};
	 cCommand[nlen++] = 0x00;
	 cCommand[nlen++] = 0x01;
	 cCommand[nlen++] = 0x03;
	 cCommand[nlen++] = 0x01;
	 //SendProtocolData(cCommand,3);
	 IPCEVENT *pIpcEvent = new IPCEVENT;
	 pIpcEvent->pData = cCommand;
	 pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
	 pIpcEvent->uSize = nlen;
	 RadioSendData(IPC_ID_MANAGE,pIpcEvent);
	 SAFE_DELETE(pIpcEvent);
#endif
 }
 void HCRadioDlg::SetDlgBkGnd()
 {
	ChangeTheme(0);
	 m_uThemeMode =  GetCurThemeMode();
 }
 void HCRadioDlg::SendRadioCommand(eRADIOCOMMANDTYPE eType,HINT iData)
 {
	 unsigned long nlen = 0;
	 HBYTE cCommand[20] = {0};
	 IPCEVENT   IpcEvent;
	 memset(&IpcEvent,0,sizeof(IpcEvent));
	 switch (eType)
	 {
	 case eENTERRADIOINTERFACE:
		 {
			 cCommand[nlen++] = 0x00;
			 cCommand[nlen++] = 0x01;
			 cCommand[nlen++] = 0x00;
			 IpcEvent.pData = cCommand;
			 IpcEvent.uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
			 IpcEvent.uSize = nlen;
		 }
		 break;
	 case eRADIOCHANNELCHANGE:
		 {
		 }
		 break;
	 case eRADIOAMFMCHANNGE:
		 {
			 cCommand[nlen++] = 0x00;
			 cCommand[nlen++] = 0x01;
			 cCommand[nlen++] = 0x02;
			 if(iData == 0)
			 {
				 cCommand[nlen++] = 0x00;
			 }
			 else
			 {
				 cCommand[nlen++] = 0x80;
			 }
			 IpcEvent.pData = cCommand;
			 IpcEvent.uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
			 IpcEvent.uSize = nlen;
		 }
		 break;
	 case eRADIOCHANNELSEARCH://0 上搜 1下搜
		 {
			 cCommand[nlen++] = 0x00;
			 cCommand[nlen++] = 0x01;
			 cCommand[nlen++] = 0x03;
			 if(iData == 0)
			 {
				 cCommand[nlen++] = 0x00;
			 }
			 else
			 {
				 cCommand[nlen++] = 0x01;
			 }
			 IpcEvent.pData = cCommand;
			 IpcEvent.uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
			 IpcEvent.uSize = nlen;
		 }
		 break;
	 case eRADIOON://0关收音机 1开收音机
		 {
			 cCommand[nlen++] = 0x00;
			 cCommand[nlen++] = 0x01;
			 cCommand[nlen++] = 0x04;
			 if(iData == 0)
			 {
				 cCommand[nlen++] = 0x00;
			 }
			 else
			 {
				 cCommand[nlen++] = 0x01;
			 }
			 IpcEvent.pData = cCommand;
			 IpcEvent.uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
			 IpcEvent.uSize = nlen;
		 }
		 break;
	 case eRADIOCHANNELSTORE:
		 {
			 cCommand[nlen++] = 0x00;
			 cCommand[nlen++] = 0x01;
			 cCommand[nlen++] = 0x05;
			 if(m_eRadioType == eFM)
			 {
				 cCommand[nlen++] = iData;
			 }
			 else
			 {
				 cCommand[nlen++] = iData;
			 }
			 IpcEvent.pData = cCommand;
			 IpcEvent.uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
			 IpcEvent.uSize = nlen;
		 }
		 break;
	 case eRADIOADJUST://0 向上微调 1 向下微调
		 {
			 cCommand[nlen++] = 0x00;
			 cCommand[nlen++] = 0x01;
			 cCommand[nlen++] = 0x06;
			 if(iData == 0)
			 {
				 cCommand[nlen++] = 0x00;
			 }
			 else
			 {
				 cCommand[nlen++] = 0x01;
			 }
			 IpcEvent.pData = cCommand;
			 IpcEvent.uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
			 IpcEvent.uSize = nlen;
		 }
		 break;
	 case eRADIOAUTOCHANNELSEARCH:
		 {
			 cCommand[nlen++] = 0x00;
			 cCommand[nlen++] = 0x01;
			 cCommand[nlen++] = 0x07;
			 IpcEvent.pData = cCommand;
			 IpcEvent.uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
			 IpcEvent.uSize = nlen;
		 }
		 break;
	 case eRADIOSCAN:
		 {
			 cCommand[nlen++] = 0x00;
			 cCommand[nlen++] = 0x01;
			 cCommand[nlen++] = 0x08;
			 IpcEvent.pData = cCommand;
			 IpcEvent.uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
			 IpcEvent.uSize = nlen;
		 }
		 break;
	 case eRADIOCHANNNELLISTS:
		 {
			 cCommand[nlen++] = 0x00;
			 cCommand[nlen++] = 0x01;
			 cCommand[nlen++] = 0x09;
			 IpcEvent.pData = cCommand;
			 IpcEvent.uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
			 IpcEvent.uSize = nlen;
		 }
		 break;
	 case eRADIOCHANNNELADJUST:
		 {
			 cCommand[nlen++] = 0x00;
			 cCommand[nlen++] = 0x01;
			 cCommand[nlen++] = 0x0a;
			 cCommand[nlen++] = HI_BYTE(iData);
			 cCommand[nlen++] = LO_BYTE(iData);
			 IpcEvent.pData = cCommand;
			 IpcEvent.uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
			 IpcEvent.uSize = nlen;
		 }
		 break;
	 case eRADIOSTOPAUTOCHANNELSEARCH:
		 {
			 cCommand[nlen++] = 0x00;
			 cCommand[nlen++] = 0x01;
			 cCommand[nlen++] = 0x0B;
			 IpcEvent.pData = cCommand;
			 IpcEvent.uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
			 IpcEvent.uSize = nlen;
		 }
		 break;
	/*	case eRADIOBASS:
		 {
			 cCommand[nlen++] = 0x00;
			 cCommand[nlen++] = 0x03;
			 cCommand[nlen++] = 0x02;
			 cCommand[nlen++] = (LO_BYTE)iData;
			 IpcEvent.pData = cCommand;
			 IpcEvent.uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
			 IpcEvent.uSize = nlen;
		 }
		 break;
		case eRADIOTERBLE:
		{
			cCommand[nlen++] = 0x00;
			cCommand[nlen++] = 0x03;
			cCommand[nlen++] = 0x01;
			cCommand[nlen++] = (LO_BYTE)iData;
			IpcEvent.pData = cCommand;
			IpcEvent.uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
			IpcEvent.uSize = nlen;
		}
		break;
		case eRADIOSRS:
		{
			cCommand[nlen++] = 0x00;
			cCommand[nlen++] = 0x03;
			cCommand[nlen++] = 0x03;
			cCommand[nlen++] = (LO_BYTE)iData;
			IpcEvent.pData = cCommand;
			IpcEvent.uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
			IpcEvent.uSize = nlen;
		}
		break;*/
		default:
		 {
			 RADIODEBUGINFO(L"Wrong Radio Command Type!");
		 }
		 break;
	 }
	 if(IpcEvent.pData != NULL && IpcEvent.uSize < 20)
	 {
		 RadioSendData(IPC_ID_MANAGE,&IpcEvent);
	 }
 }
 void HCRadioDlg::PostMessageToWin(HUINT msg,HINT nparam)
 {
	 ::PostMessage(m_hWnd,msg,nparam,NULL);
 }
 void HCRadioDlg::SetMyhWnd(HWND hhand)
 {
	 m_hWnd = hhand;
 }
 void HCRadioDlg::SetLangue(HINT nType)
 {
	 sLangue* pEn =RadioSource::Instance()->GetRadioEnLange();
	 sLangue* pCh =RadioSource::Instance()->GetRadioChLange();
	switch (nType)
	{
		case 0:
		{
			if(pCh != NULL)
			{
				s_pLan = pCh->szContent;
				m_nCurrentLange = 0;
			}
			else
			{
				RADIODEBUGINFO(L"获取中文失败");
			}
		}
		break;
		case 1:
		{
			if(pEn != NULL)
			{
				s_pLan = pEn->szContent;
				m_nCurrentLange = 1;
			}
			else
			{
				RADIODEBUGINFO(L"获取英文失败");
			}
		}
		break;
		default:
		{
			RADIODEBUGINFO(L"%s:wrong param= %d",__FUNCTIONW__,nType);
		}
		break;
	}
 }
 void HCRadioDlg::ChangeLangue(HINT nType)
 {
	SetLangue(nType);
	if(s_pLan != NULL)
	{
		switch (nType)
		{
			case 0:
			{
				m_pBtnScan->SetFontSize(24,24);
//				m_pTxtNotice1->SetFontSize(24,24);
		//		m_pTxtNotice2->SetFontSize(24,24);
				m_pBtnChannelAutoSearch->SetFontSize(24,24);
//				m_pBtnConfirm->SetFontSize(24,24);
				//m_pBtnCannel->SetFontSize(24,24);
				m_pTxtAvailableChannel->SetFontSize(24,24);
			}
			break;
			case 1:
			{
				m_pBtnScan->SetFontSize(20,20);
		//		m_pTxtNotice1->SetFontSize(20,20);
		//		m_pTxtNotice2->SetFontSize(20,20);
				m_pBtnChannelAutoSearch->SetFontSize(20,20);
			//	m_pBtnConfirm->SetFontSize(20,20);
			//	m_pBtnCannel->SetFontSize(20,20);
				m_pTxtAvailableChannel->SetFontSize(30,30);
			}
			break;
			default:
			break;
		}
		m_pTxtScreen->SetText(s_pLan[0]);
		m_pBtnScan->SetText(s_pLan[1]);
		 if(m_bAutoSearch == true)
		 {
			 m_pBtnChannelAutoSearch->SetText(s_pLan[7]);
			 m_pTxtRadioMessage->SetText(s_pLan[8]);
		 }
		 else
		 {
			 m_pBtnChannelAutoSearch->SetText(s_pLan[2]);
			//m_pTxtRadioMessage->SetShow(false);
			 m_pTxtRadioMessage->SetText(L" ");
		 }
		 HINT nLen = m_pTxtAvailableChannel->GetText().length();
		 switch (nLen)
		 {
			 case 4:
			{
				m_pTxtAvailableChannel->SetText(s_pLan[11]);
			 }
			break;
			 case 5:
			 {
				 //m_pTxtAvailableChannel->SetText(s_pLan[9]);//无有效电台
				 m_pTxtAvailableChannel->SetText(L" ");
			 }
			 break;
			 default:
			 {
				  m_pTxtAvailableChannel->SetText(L" ");
			 }
			 break;
		 }
		 if(m_bST == true && m_eRadioType == eFM)
		 {
			 //m_pTxtSTstate->SetText(L"ST");
			 m_pTxtSTstate->SetText(s_pLan[10]);
		 }
		 else
		 {
			 m_pTxtSTstate->SetText(L" ");
		 }
	//	m_pTxtNotice1->SetText(s_pLan[5]);
	//	m_pTxtNotice2->SetText(s_pLan[6]);
//		m_pBtnConfirm->SetText(s_pLan[3]);
	//	m_pBtnCannel->SetText(s_pLan[4]);
	}
	m_nCurrentLange = nType;
	UpDataRadioLisitem(m_eRadioType);
	//UpdateWindow();
 }
 void HCRadioDlg::UpDataRadioSource()
 {
	  //RADIOSETTING setting;
	 GetCurrentArea();
	  SETUPSETTING LSetting;
	  memset(&LSetting,0,sizeof(LSetting));
	  KCLastMemory::GetInstance()->GetSetupMemory(LSetting);
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
	ReadRadioLastMem();
	sRadioSourceGroup *pSource=RadioSource::Instance()->GetRadioSource(GetHMIPath(_T("")).c_str()); 
	if(pSource != NULL)
	{
		if(m_eRadioType == eFM)
		{
			m_pBtnTopScale->SetBkgndN(pSource->pFmScale);
			if(m_nCurrentArea != 1)
			{
				m_pSliderChannelScan->SetBound(860,1080);
			}
			else
			{
				m_pSliderChannelScan->SetBound(8600,10800);
			}
			m_pTxtRadioUnit->SetText(L"MHz");
			m_pTxtRadioType->SetText(L"FM");
		}
		else
		{
			m_pBtnTopScale->SetBkgndN(pSource->pAmScale);
			m_pSliderChannelScan->SetBound(531,1631);
			m_pTxtRadioUnit->SetText(L"KHz");
			m_pTxtRadioType->SetText(L"AM");
		}
	}
	UpData();
	UpDataRadioLisitem(m_eRadioType);
	m_bAutoSearch = false;
	if(s_pLan != NULL)
	{
		m_pBtnChannelAutoSearch->SetText(s_pLan[2]);
	}
 }
void HCRadioDlg::SaveRadioLastMem()
{
	 RADIOSETTING setting;
	 if(m_pFMStoredChannnel != NULL && m_pFMStoredChannnel != NULL)
	 {
		 for(int i = 0; i < 20;i++)
		 {
			 (setting.uFMPreset[i]) =(unsigned short)(*(m_pFMStoredChannnel + i));
			(setting.uAMPreset[i]) =(unsigned short)(*(m_pAMStoredChannnel + i));
		 }
		// m_nCurrentFMValue = (unsigned short)(setting.uLastFM);
		 setting.uLastFM = (unsigned short)m_nCurrentFMValue;
		 setting.uLastAM = (unsigned short)m_nCurrentAMValue;
		// m_nCurrentFMValue = (unsigned short)(setting.uLastAM);
		 if(m_eRadioType == eFM)
		 {
			 setting.uLastBand = 0;
		 }
		 else
		 {
			 setting.uLastBand = 1;
		 }
	 }
	 RADIODEBUGINFO(L"%s:setting.uLastFM = %d,setting.uLastAM = %d, setting.uLastBand = %d,m_nCurrentFMValue = %d,m_nCurrentAMValue = %d,",__FUNCTIONW__,setting.uLastFM,setting.uLastAM,setting.uLastBand,m_nCurrentFMValue,m_nCurrentAMValue);
	 KCLastMemory::GetInstance()->SetRadioMemory(setting);
}
void HCRadioDlg::ReadRadioLastMem()
{
	RADIOSETTING setting;
	KCLastMemory::GetInstance()->GetRadioMemory(setting);
	if(m_pFMStoredChannnel != NULL && m_pAMStoredChannnel != NULL)
	{
		for(int i = 0; i < 20;i++)
		{
			*(m_pFMStoredChannnel + i) =(HUINT)(setting.uFMPreset[i]);
			*(m_pAMStoredChannnel + i) = (HUINT)(setting.uAMPreset[i]);
		}
		m_nCurrentFMValue = (HUINT)setting.uLastFM;
		m_nCurrentAMValue = (HUINT)setting.uLastAM;
		if(setting.uLastBand == 0)
		{
			m_eRadioType = eFM;
		}
		else
		{
			m_eRadioType = eAM;
		}
	}
	RADIODEBUGINFO(L"%s,Last mem:m_eRadioType = %d,m_nCurrentFMValue = %d,m_nCurrentAMValue = %d,uLastFM = %d,uLastAM = %d",__FUNCTIONW__,m_eRadioType,m_nCurrentFMValue,m_nCurrentAMValue,setting.uLastFM,setting.uLastAM);
}
void HCRadioDlg::UpDataCurrentValue()
{
	switch (m_eRadioType)
	{
		case eAM:
		{
			//m_nPreAMValue = m_nCurrentAMValue;
			if(m_eRadioWorkState ==  eRADIONARMAL)
			{
				RADIODEBUGINFO(L"%s:m_eRadioType = %d,nCurrentValue = %d",__FUNCTIONW__,m_eRadioType,m_nCurrentAMValue);
			}
		    if(m_pGrpCurrentFM->IsShow())
			{
				m_pGrpCurrentFM->SetShow(false);
			}
			HUINT n = 0;
			if(m_nCurrentAMValue == 0)
			{
				if(m_pGrpCurrentFM->IsShow())
				{
					m_pGrpCurrentAM->SetShow(false);
				}	
			}
			else if(m_nCurrentAMValue > 0/* && m_nCurrentAMValue >= 531 && m_nCurrentAMValue <= 1602*/)
			{
				 if(m_nCurrentAMValue >= 1000)
				{
				n = m_nCurrentAMValue/1000;
				SetTxtValue(m_pTxtAM3,n);
			/*	if(!m_pTxtAM3->IsShow())
				{
					m_pTxtAM3->SetShow(true);
				}	*/
				}
				else
				{
			    SetTxtValue(m_pTxtAM3,10);
			/*	if(m_pTxtAM3->IsShow())
				{
					m_pTxtAM3->SetShow(false);
				}*/
				}
				 n = m_nCurrentAMValue%10;
				SetTxtValue(m_pTxtAM0,n);
				n = m_nCurrentAMValue%100/10;
				SetTxtValue(m_pTxtAM1,n);
				n = m_nCurrentAMValue/100%10;
				SetTxtValue(m_pTxtAM2,n);
				if(!(m_pGrpCurrentAM->IsShow()))
				{
					m_pGrpCurrentAM->SetShow(true);
				}
			}
			//m_pGrpCurrentAM->Invalidate();
		}
		break;
		case eFM:
		{
			//m_nPreFMValue = m_nCurrentFMValue;
			if(m_eRadioWorkState ==  eRADIONARMAL)
			{
				RADIODEBUGINFO(L"%s:m_eRadioType = %d,nCurrentValue = %d",__FUNCTIONW__,m_eRadioType,m_nCurrentFMValue);
			}
			if(m_pGrpCurrentAM->IsShow())
			{
				m_pGrpCurrentAM->SetShow(false);
			}
			if(m_nCurrentFMValue == 0)
			{
				if(m_pGrpCurrentFM->IsShow())
				{
					m_pGrpCurrentFM->SetShow(false);
				}
			}
			else if( m_nCurrentFMValue > 0 /*&& m_nCurrentFMValue >= 875 && m_nCurrentFMValue <= 1080*/)
			{
				if(m_nCurrentArea  != 1)
				{
					HUINT n = m_nCurrentFMValue%10;
					SetTxtValue(m_pTxtFM0,n);
					n = m_nCurrentFMValue%100/10;
					SetTxtValue(m_pTxtFM1,n);
					n = m_nCurrentFMValue/100%10;
					SetTxtValue(m_pTxtFM2,n);

					if(m_nCurrentFMValue >= 1000)
					{
						n = m_nCurrentFMValue/1000;
						SetTxtValue(m_pTxtFM3,n);
						if(!m_pTxtFM3->IsShow())
						{
							m_pTxtFM3->SetShow(true);
						}	
					}
					else
					{
						SetTxtValue(m_pTxtFM3,10);
						//m_pTxtFM3->SetShow(false);
					}
					SetTxtValue(m_pTxtFM4,10);
					if(!(m_pGrpCurrentFM->IsShow()))
					{
						m_pGrpCurrentFM->SetShow(true);
					}
				}
				else
				{
					RADIODEBUGINFO(L"%s:m_nCurrentFMValue = %d",__FUNCTIONW__,m_nCurrentFMValue);
					HUINT n = m_nCurrentFMValue%10;
					SetTxtValue(m_pTxtFM4,n);
					n = m_nCurrentFMValue%100/10;
					SetTxtValue(m_pTxtFM0,n);
					n = m_nCurrentFMValue%1000/100;
					SetTxtValue(m_pTxtFM1,n);
					n = m_nCurrentFMValue/1000%10;
					SetTxtValue(m_pTxtFM2,n);
					//if(m_nCurrentFMValue >= 1000)
					//{
					//	n = m_nCurrentFMValue/1000%10;
					//	SetTxtValue(m_pTxtFM3,n);
					//	if(!m_pTxtFM3->IsShow())
					//	{
					//		m_pTxtFM3->SetShow(true);
					//	}	
					//}
					//else
					//{
					//	SetTxtValue(m_pTxtFM3,10);
					//	//m_pTxtFM3->SetShow(false);
					//}
					if(m_nCurrentFMValue >= 10000)
					{
						 n = m_nCurrentFMValue/10000;
						SetTxtValue(m_pTxtFM3,n);
						if(!m_pTxtFM3->IsShow())
						{
							m_pTxtFM3->SetShow(true);
						}	
						
					}
					else
					{
						SetTxtValue(m_pTxtFM3,10);
					}
					if(!(m_pGrpCurrentFM->IsShow()))
					{
						m_pGrpCurrentFM->SetShow(true);
					}
				}
			}	
			//m_pGrpCurrentFM->Invalidate();
		}
		break;
		default:
		break;
	}
	JumpToCurrentValueIndex(0);
	//printf("111111111111111111111\r\n");
}
void HCRadioDlg::SetTxtValue(HCTextCtrl *pTxt,HINT nValue)
{
	sRadioSourceGroup *pSource = RadioSource::Instance()->GetRadioSource(GetHMIPath(_T("")).c_str());
	if(pTxt != NULL && pSource != NULL)
	{
		if(!(pTxt->IsShow()))
		{
			pTxt->SetShow(true);
		}
		switch (nValue)
		{
		case 0:
			{
				pTxt->SetBkgndN(pSource->pNum0);
			}
			break;
		case 1:
			{
				pTxt->SetBkgndN(pSource->pNum1);
			}
			break;
		case 2:
			{
				pTxt->SetBkgndN(pSource->pNum2);
			}
			break;
		case 3:
			{
				pTxt->SetBkgndN(pSource->pNum3);
			}
			break;
		case 4:
			{
				pTxt->SetBkgndN(pSource->pNum4);
			}
			break;
		case 5:
			{
				pTxt->SetBkgndN(pSource->pNum5);
			}
			break;
		case 6:
			{
				pTxt->SetBkgndN(pSource->pNum6);
			}
			break;
		case 7:
			{
				pTxt->SetBkgndN(pSource->pNum7);
			}
			break;
		case 8:
			{
				pTxt->SetBkgndN(pSource->pNum8);
			}
			break;
		case 9:
			{
				pTxt->SetBkgndN(pSource->pNum9);
			}
			break;
		case 10:
			{
				pTxt->SetBkgndN(pSource->pNumNull);
			}
		default:
			break;
		}
	}
}
void HCRadioDlg::OnStartSearch(void* pDlg, void* param)
{
	HCRadioDlg* pObj = (HCRadioDlg*)pDlg;
	pObj->OnStartSearch(pObj);
}
void HCRadioDlg::OnStartSearch(void* pDlg)
{
	if(m_ctRefrench.IsActive())
	{
		m_ctRefrench.StopTimer();
	}
	m_pTxtAvailableChannel->SetText(L" ");
#if RADIOCOMMANDQUEUE
	::PostMessage(m_hWnd,WM_USER + 50,eRADIOAUTOCHANNELSEARCH,0);
#else
	HBYTE cCommand[10] = {0};
	HUINT nlen = 0;
	cCommand[nlen++] = 0x00;
	cCommand[nlen++] = 0x01;
	cCommand[nlen++] = 0x07;	
	IPCEVENT *pIpcEvent = new IPCEVENT;
	pIpcEvent->pData = cCommand;
	pIpcEvent->uIPCEvent = IPC_U_SYS_COM_PROTOCOL;
	pIpcEvent->uSize = nlen;
	RadioSendData(IPC_ID_MANAGE,pIpcEvent);
	SAFE_DELETE(pIpcEvent);
#endif
	if(s_pLan != NULL)
	{
		m_pBtnChannelAutoSearch->SetText(s_pLan[7]);
	}
	//m_pGrpNotice->SetShow(false);
	UpDataRadioCtrlMessage(true);
	 m_bAutoSearch = true;
	m_bNoticeShow = false;
}
void HCRadioDlg::OnAMFMMoveEnd(void *pDlg,HINT nPos)
{
	HCRadioDlg *pObj = static_cast<HCRadioDlg*>(pDlg);
	RADIODEBUGINFO(L"nPos = %d",nPos);
	pObj->OnAMFM((nPos + 1)%2);
}
void HCRadioDlg::OnAMFMUp(void *pDlg,void* pParam)
{
	HCRadioDlg *pObj = static_cast<HCRadioDlg*>(pDlg);
	SAFECALL(pObj)->OnAMFMUp(pParam);
}
void 	HCRadioDlg::OnAMFMUp(void* pParam)
{
	HINT nIndex = m_pSwBtAMFM->GetIndex();
	RADIODEBUGINFO(L"%s,nIndex = %d",__FUNCTIONW__,nIndex);
	OnAMFM(nIndex);
}
HINT HCRadioDlg::AdjustValue(HINT nValue)
{
	HINT nLeft = nValue%9;
	if(nLeft<= 4)
	{
		nValue = nValue/9*9;
	}
	else
	{
		nValue = nValue/9*9 + 9;
	}
	return nValue;
}
HINT HCRadioDlg::AdjustValue(HINT nValue,eRadioType_t eType,HINT nCurrentArea)
{
	 HINT nLeft = 0;
	 RADIODEBUGINFO(L"%s:nValue = %d,eType = %d,nCurrentArea = %d",__FUNCTIONW__,nValue,eType,nCurrentArea);
	  if(eType == eFM)
	  {
			switch (nCurrentArea)
			{
				case 0:
				{
					return nValue;
				}
				break;
				case 1:
				{
					nLeft = nValue%5;
					if(nLeft<= 5)
					{
						nValue = nValue/5*5;
					}
					else
					{
						nValue = nValue/5*5 + 5;
						if(nValue >= 10800)
						{
							nValue = 10800;
						}
					}
					return nValue;
				}
				break;
				case 2:
				{
					nLeft = (nValue - 8790)%20;
					if(nLeft >= 10)
					{
						nValue = nValue/20*20 + 10;
						if(nValue > 10790)
						{
							nValue = 10790;
						}
					}
					else
					{
						nValue = nValue - nLeft;
						if(nValue < 8790)
						{
							nValue = 8790;
						}
					}
					return nValue;
				}
				break;
			}
	  }
	  else
	  {
		  switch (nCurrentArea)
		  {
		  case 0:
			  {
				  nLeft = nValue%9;
				  if(nLeft<= 4)
				  {
					  nValue = nValue/9*9;
				  }
				  else
				  {
					  nValue = nValue/9*9 + 9;
					  if(nValue > 1629)
					  {
						  nValue = 1629;
					  }
				  }
				  return nValue;
			  }
			  break;
		  case 1:
			  {
				  nLeft = nValue%9;
				  if(nLeft<= 4)
				  {
					  nValue = nValue/9*9;
				  }
				  else
				  {
					  nValue = nValue/9*9 + 9;
					  if(nValue > 1611)
					  {
						  nValue = 1611;
					  }
				  }
				  return nValue;
			  }
			  break;
		  case 2:
			  {
				  nLeft = nValue%10;
				  if(nLeft<= 5)
				  {
					  nValue = nValue/10*10;
				  }
				  else
				  {
					  nValue = nValue/10*10 + 10;
					  if(nValue > 1710)
					  {
						  nValue = 1710;
					  }
				  }
				  return nValue;
			  }
			  break;
		  }
	  }
	  return 0;
}
void HCRadioDlg::GetCurrentArea()
{
	SOUNDSETTING setting;
	KCLastMemory::GetInstance()->GetSoundMemory(setting);
	m_nCurrentArea = setting.uRadioArea ;//0中国1欧洲 2北美
	RADIODEBUGINFO(L"m_nCurrentArea = %d",m_nCurrentArea);
}
void HCRadioDlg::JumpToCurrentValueIndex(int nSelectChannel)
{
	HUINT i = 0;

	bool bContiue = false;
	if(m_eRadioType == eFM)
	{
		 i = IsStored(m_pFMStoredChannnel,m_nCurrentFMValue);
		 if(m_nPreFMValue != m_nCurrentFMValue)
		 {
			 bContiue = true;
		 }
	}
	else
	{
		 i = IsStored(m_pAMStoredChannnel,m_nCurrentAMValue);
		 if(m_nPreAMValue != m_nCurrentAMValue)
		 {
               bContiue = true;
		 }
		 
	}
	if(!bContiue)
		return ;
  if(i > 0 && i <= 20 && m_eRadioWorkState == eRADIONARMAL)
  {
	  int nIndex = ((i-1)/5)%4;
      if(m_pScrctrlChannelStore != NULL && m_pScrctrlChannelStore->GetValue() != nIndex)
	  {
		  m_pScrctrlChannelStore->SetValueEx(nIndex,true);
	  }
  }
  m_nPreAMValue = m_nCurrentAMValue;
  m_nPreFMValue = m_nCurrentFMValue;
}
