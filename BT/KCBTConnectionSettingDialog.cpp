#include "KCBTConnectionsettingDialog.h"
#include "KHMIBaseHead.h"
#include "KCBTDialogManager.h"

HCBTConnectionssettingDlg::HCBTConnectionssettingDlg(void)
{
	m_pGrpCtrlConnectionSettingMiddle = NULL ;
//	m_pTxtConnectionSettingBK = NULL;
	m_pScrCtrlConnectionSetting = NULL;
	m_pScrBoxPariedDevices = NULL;
	m_pBtnPariedDevicesUp = NULL;
	m_pBtnPariedDevicesDown = NULL;
	m_pTxtConnectionSettingHandleBK = NULL;
	m_pBtnDeviceUnconnect = NULL;
	m_pBtnDeviceDelete = NULL;
	m_pBtnDeviceDeleteAll = NULL;
	m_pBtnPhonePair = NULL;
	//m_pGrpCtrlNotice = NULL;
//	m_pTxtNoticeBK = NULL;
	//m_pTxtNotice = NULL;
	//m_pTxtLocalDeviceName = NULL;
	m_pTxtDeviceLine1 = NULL;
	m_pTxtDeviceLine2 = NULL;
	m_pTxtDeviceLine3 = NULL;
	m_pTxtDeviceLine4 = NULL;
	m_bConnected = FALSE;
//	m_pBtnBTOpen = NULL;
	m_nTotalPairedNum = 0;
	m_nMode = 0;//0, 正常状态，1，匹配状态
	m_iSelectConnectDevice = -1;
#if BTVERSION
	m_pTxtBTVersion = NULL;
#else
#endif
};

HCBTConnectionssettingDlg::~HCBTConnectionssettingDlg(void)
{
	if(m_pScrBoxPariedDevices->GetListItemCount() > 0)
	{
		m_pScrBoxPariedDevices->DeleteAllListItems();
	}
	DelTimer(&m_ctDeadTime);
	DelTimer(&m_ctBTClose);
	SAFE_DELETE(m_pTxtDeviceLine1);
	SAFE_DELETE(m_pTxtDeviceLine2);
	SAFE_DELETE(m_pTxtDeviceLine3);
	SAFE_DELETE(m_pTxtDeviceLine4);
//	SAFE_DELETE(m_pTxtLocalDeviceName);
//	SAFE_DELETE(m_pTxtNotice);
//	SAFE_DELETE(m_pTxtNoticeBK);
//	SAFE_DELETE(m_pGrpCtrlNotice);
	SAFE_DELETE(m_pBtnPhonePair);
	SAFE_DELETE(m_pBtnDeviceDeleteAll);
	SAFE_DELETE(m_pBtnDeviceDelete);
	SAFE_DELETE(m_pBtnDeviceUnconnect);
	SAFE_DELETE(m_pTxtConnectionSettingHandleBK);
	SAFE_DELETE(m_pBtnPariedDevicesDown);
	SAFE_DELETE(m_pBtnPariedDevicesUp);
	SAFE_DELETE(m_pScrBoxPariedDevices);
	SAFE_DELETE(m_pScrCtrlConnectionSetting);
//	SAFE_DELETE(m_pTxtConnectionSettingBK);
#if BTVERSION

	SAFE_DELETE(m_pTxtBTVersion);
#else
#endif
	SAFE_DELETE(m_pGrpCtrlConnectionSettingMiddle);

};
HINT HCBTConnectionssettingDlg::OnInit()
{
	HINT nRet = HCBluetoothBaseDlg::OnInit();
	//m_pTxtScreen->SetText(L"连接设置");
	m_nMode = 0;
	//连接设置中部
	m_nPairSend = 0;
	m_pGrpCtrlConnectionSettingMiddle = new HCGroupCtrl;
	if(m_pGrpCtrlConnectionSettingMiddle != NULL)
	{
		m_pGrpCtrlConnectionSettingMiddle->Create(0,68,640,344);
		m_pGrpCtrlConnectionSettingMiddle->SetShow(true);
		AddChild(m_pGrpCtrlConnectionSettingMiddle);
		m_pTxtConnectionSettingBK = new HCImageCtrl;//配对设备背景
		if(m_pTxtConnectionSettingBK != NULL)
		{
			m_pTxtConnectionSettingBK->Create(0,68,640,344);
			m_pTxtConnectionSettingBK->EnableMsg(false);
			m_pGrpCtrlConnectionSettingMiddle->AddChild(m_pTxtConnectionSettingBK);
		}
			m_pTxtDeviceLine1 = new HCTextCtrl;
			if(m_pTxtDeviceLine1 != NULL)
			{
				m_pTxtDeviceLine1->Create(30,138,526,2);
				m_pTxtDeviceLine1->EnableMsg(false);
				
				m_pGrpCtrlConnectionSettingMiddle->AddChild(m_pTxtDeviceLine1);
			}
			m_pTxtDeviceLine2 = new HCTextCtrl;
			if(m_pTxtDeviceLine2 != NULL)
			{
				m_pTxtDeviceLine2->Create(30,204,526,2);
				m_pTxtDeviceLine2->EnableMsg(false);
				m_pGrpCtrlConnectionSettingMiddle->AddChild(m_pTxtDeviceLine2);
			}
			m_pTxtDeviceLine3 = new HCTextCtrl;
			if(m_pTxtDeviceLine3 != NULL)
			{
				m_pTxtDeviceLine3->Create(30,270,526,2);
				m_pTxtDeviceLine3->EnableMsg(false);
				m_pGrpCtrlConnectionSettingMiddle->AddChild(m_pTxtDeviceLine3);
			}
			m_pTxtDeviceLine4 = new HCTextCtrl;
			if(m_pTxtDeviceLine4 != NULL)
			{
				m_pTxtDeviceLine4->Create(30,336,526,2);
				m_pTxtDeviceLine4->EnableMsg(false);
				m_pGrpCtrlConnectionSettingMiddle->AddChild(m_pTxtDeviceLine4);
			}
		
		//配对设备滚动列表
		m_pScrBoxPariedDevices = new HCScrollBox;
		if(m_pScrBoxPariedDevices != NULL)
		{
			m_pScrBoxPariedDevices->Create(15,75,582,330);
			//m_pScrBoxPariedDevices->SetShow(true);
			m_pScrBoxPariedDevices->SetTextColorN(255, 255, 255);//设置字体颜色
			m_pScrBoxPariedDevices->SetTextColorA(255, 255, 255);//设置字体颜色
			m_pScrBoxPariedDevices->SetFontSize(24, 24);//设置字体的大小
			//m_pScrBoxPariedDevices->SetCallBackSelectItemChange(OnSelectDeviceChange,this);
			AddChild(m_pScrBoxPariedDevices);
			m_pScrBoxPariedDevices->EnableScrollLine(true,66,NULL);
			m_pScrBoxPariedDevices->SetShow(true);
			m_pScrBoxPariedDevices->SetCallBackClick(OnScrBoxPariedDevices,this);
		}
		m_pScrCtrlConnectionSetting= new HCScrollCtrl;//配对设备滑块
		if(m_pScrCtrlConnectionSetting != NULL)
		{
			m_pScrCtrlConnectionSetting->Create(596,100,28,280,1);
			m_pScrCtrlConnectionSetting->SetBound(0,1);
			m_pGrpCtrlConnectionSettingMiddle->AddChild(m_pScrCtrlConnectionSetting);
			m_pScrCtrlConnectionSetting->SetScrollBox(m_pScrBoxPariedDevices,5);
		}
		//配对设备本向上按钮
		m_pBtnPariedDevicesUp= new HCButton;
		if(m_pBtnPariedDevicesUp != NULL)
		{
			m_pBtnPariedDevicesUp->Create(590, 74, 40, 36);
			m_pBtnPariedDevicesUp->EnableMsg(true);
			m_pBtnPariedDevicesUp->SetShow(true);
			m_pGrpCtrlConnectionSettingMiddle->AddChild(m_pBtnPariedDevicesUp);
		}
		//配对设备向下按钮
		m_pBtnPariedDevicesDown= new HCButton;
		if(m_pBtnPariedDevicesDown != NULL)
		{
			m_pBtnPariedDevicesDown->Create(590, 370, 40, 36);
			m_pBtnPariedDevicesDown->EnableMsg(true);
			m_pBtnPariedDevicesDown->SetShow(true);
			m_pGrpCtrlConnectionSettingMiddle->AddChild(m_pBtnPariedDevicesDown);
			m_pScrCtrlConnectionSetting->SetAddButton(m_pBtnPariedDevicesUp,m_pBtnPariedDevicesDown);
		}
		//连接设置操作背景
		m_pTxtConnectionSettingHandleBK = new HCImageCtrl;
		if(m_pTxtConnectionSettingHandleBK != NULL)
		{
			m_pTxtConnectionSettingHandleBK->Create(624,68,176,344);
			m_pTxtConnectionSettingHandleBK->EnableMsg(false);
			//m_pGrpCtrlConnectionSettingMiddle->AddChild(m_pTxtConnectionSettingHandleBK);
			AddChild(m_pTxtConnectionSettingHandleBK);
		}
		//断开按钮
		m_pBtnDeviceUnconnect = new HCButton;
		if(m_pBtnDeviceUnconnect != NULL)
		{
			m_pBtnDeviceUnconnect->Create(636,75, 152, 64);
			m_pBtnDeviceUnconnect->EnableMsg(true);
			m_pBtnDeviceUnconnect->SetCallBackDown(OnDisconnect,this);
			m_pBtnDeviceUnconnect->SetTextStyle(RE_TS_CENTER);
			m_pBtnDeviceUnconnect->SetTextPos(103 ,31);
			m_pBtnDeviceUnconnect->SetTextColorN(127,127,127);
			m_pBtnDeviceUnconnect->SetTextColorS(127,127,127);
			m_pBtnDeviceUnconnect->SetTextColorA(127,127,127);
			m_pBtnDeviceUnconnect->EnableMsg(false);
			m_pBtnDeviceUnconnect->SetFontSize(24,24);
			//m_pBtnDeviceUnconnect->SetText(_T(""));
			m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Ct_D.hfp")));
			//m_pBtnDeviceUnconnect->SetText(L"连接");
			//m_pGrpCtrlConnectionSettingMiddle->AddChild(m_pBtnDeviceUnconnect);
			AddChild(m_pBtnDeviceUnconnect);
		}
		//删除按钮
		m_pBtnDeviceDelete = new HCButton;
		if(m_pBtnDeviceDelete != NULL)
		{
			m_pBtnDeviceDelete->Create(636,142, 152, 64);
			m_pBtnDeviceDelete->EnableMsg(false);
			m_pBtnDeviceDelete->SetCallBackDown(OnDelete,this);
			m_pBtnDeviceDelete->SetTextColorN(127,127,127);
			m_pBtnDeviceDelete->SetTextColorS(127,127,127);
			m_pBtnDeviceDelete->SetTextColorA(127,127,127);
			m_pBtnDeviceDelete->EnableMsg(false);
			m_pBtnDeviceDelete->SetTextStyle(RE_TS_CENTER);
			m_pBtnDeviceDelete->SetTextPos(103 ,31);
			m_pBtnDeviceDelete->SetFontSize(24,24);
			//m_pBtnDeviceDelete->SetText(_T("删除"));
			//m_pGrpCtrlConnectionSettingMiddle->AddChild(m_pBtnDeviceDelete);
			AddChild(m_pBtnDeviceDelete);
		}
		//全部删除按钮
		m_pBtnDeviceDeleteAll = new HCButton;
		if(m_pBtnDeviceDeleteAll != NULL)
		{
			m_pBtnDeviceDeleteAll->Create(636,208, 152, 64);
			m_pBtnDeviceDeleteAll->EnableMsg(true);
			m_pBtnDeviceDeleteAll->SetCallBackDown(OnDeleteAll,this);
			m_pBtnDeviceDeleteAll->SetTextStyle(RE_TS_CENTER);
			m_pBtnDeviceDeleteAll->SetTextColorN(127,127,127);
			m_pBtnDeviceDeleteAll->SetTextColorS(127,127,127);
		   m_pBtnDeviceDeleteAll->SetTextColorA(127,127,127);
			m_pBtnDeviceDeleteAll->EnableMsg(false);
			m_pBtnDeviceDeleteAll->SetTextPos(103 ,31);
			m_pBtnDeviceDeleteAll->SetFontSize(24,24);
			//m_pBtnDeviceDeleteAll->SetText(_T("全部删除"));
			//m_pGrpCtrlConnectionSettingMiddle->AddChild(m_pBtnDeviceDeleteAll);
			AddChild(m_pBtnDeviceDeleteAll);
		}
		m_pBtnPhonePair = new HCButton;
		if(m_pBtnPhonePair != NULL)
		{
			m_pBtnPhonePair->Create(636,274, 152, 64);
			//m_pBtnPhonePair->EnableMsg(true);
			m_pBtnPhonePair->SetTextStyle(RE_TS_CENTER);
			m_pBtnPhonePair->SetTextPos(103 ,31);
			m_pBtnPhonePair->SetFontSize(24,24);
			m_pBtnPhonePair->SetTextColorN(255,255,255);
			m_pBtnPhonePair->SetTextColorA(255,255,255);
			m_pBtnPhonePair->SetTextColorS(255,255,255);
			m_pBtnPhonePair->EnableMsg(true);
			//m_pBtnPhonePair->SetText(_T("手机匹配"));
			m_pBtnPhonePair->SetCallBackDown(OnEnterPairPage,this);
			//m_pGrpCtrlConnectionSettingMiddle->AddChild(m_pBtnPhonePair);
			AddChild(m_pBtnPhonePair);
		}
#if TESTRESTARTPROTEM
		m_pBtnRestTime = new HCButton;
		if(m_pBtnRestTime != NULL)
		{
			m_pBtnRestTime->Create(636,340, 152, 64);
			//m_pBtnPhonePair->EnableMsg(true);
			m_pBtnRestTime->SetTextStyle(RE_TS_CENTER);
			m_pBtnRestTime->SetTextPos(103 ,31);
			m_pBtnRestTime->SetFontSize(24,24);
			m_pBtnRestTime->SetTextColorN(255,255,255);
			m_pBtnRestTime->SetTextColorA(255,255,255);
			m_pBtnRestTime->SetTextColorS(255,255,255);
			m_pBtnRestTime->EnableMsg(true);
			//m_pBtnPhonePair->SetText(_T("手机匹配"));
			m_pBtnRestTime->SetCallBack(OnUpdataRestTime,this);
			m_pBtnRestTime->SetCallBackLongPress(OnClearRestTime,this);
			//m_pGrpCtrlConnectionSettingMiddle->AddChild(m_pBtnPhonePair);
			AddChild(m_pBtnRestTime);
		}
#endif
	
		/*m_pBtnBTOpen = new HCButton;
		if(m_pBtnBTOpen != NULL)
		{
			m_pBtnBTOpen->Create(636,340,152,64);
			m_pBtnBTOpen->SetTextStyle(RE_TS_CENTER);
			m_pBtnBTOpen->SetTextPos(103 ,31);
			m_pBtnBTOpen->SetFontSize(24,24);
			m_pBtnBTOpen->SetTextColorN(255,255,255);
			m_pBtnBTOpen->SetText(L"关闭蓝牙");
			m_pBtnBTOpen->SetCallBack(OnOpenBT,this);
			m_pGrpCtrlConnectionSettingMiddle->AddChild(m_pBtnBTOpen);
		}*/
		//m_pGrpCtrlNotice = new HCGroupCtrl;
		//if(m_pGrpCtrlNotice != NULL)
		//{
		//	m_pGrpCtrlNotice->Create(84,140,500,220);
		//	m_pTxtNoticeBK = new HCTextCtrl;
		//	m_pTxtNoticeBK->Create(84,140,500,220);
		//	m_pTxtNoticeBK->EnableMsg(false);
		//	m_pGrpCtrlNotice->AddChild(m_pTxtNoticeBK);
		//}
		//m_pTxtNotice = new HCTextCtrl;
		//if(m_pTxtNotice != NULL)
		//{
		//	m_pTxtNotice->Create(240,163,300,30);
		//	//m_pTxtNotice->SetTextPos(150,15);
		//	m_pTxtNotice->SetTextStyle(RE_TS_NORMAL);
		//	m_pTxtNotice->SetFontSize(24,24);
		//	m_pTxtNotice->EnableMsg(false);
		//	m_pTxtNotice->SetTxtColor(255,255,255);
		//	//m_pTxtNotice->SetText(L"通过手机蓝牙搜索该设备");
		//	m_pTxtNotice->SetShow(false);
		//	m_pGrpCtrlNotice->AddChild(m_pTxtNotice);
		//}
		//m_pTxtLocalDeviceName = new HCTextCtrl;
		//if(m_pTxtLocalDeviceName != NULL)
		//{
		//	m_pTxtLocalDeviceName->Create(240,208,300,30);
		//	//m_pTxtLocalDeviceName->SetTextPos(150,15);
		//	m_pTxtLocalDeviceName->SetTextStyle(RE_TS_NORMAL);
		//	m_pTxtLocalDeviceName->SetFontSize(24,24);
		//	m_pTxtLocalDeviceName->EnableMsg(false);
		//	m_pTxtLocalDeviceName->SetTxtColor(255,255,255);
		//	//m_pTxtLocalDeviceName->SetText(L"设备名称:");
		//	m_pGrpCtrlNotice->AddChild(m_pTxtLocalDeviceName);
		//	m_pTxtLocalDeviceName->SetShow(false);
		//}
		//m_pTxtPairCode = new HCTextCtrl;
		//if(m_pTxtPairCode != NULL)
		//{
		//	m_pTxtPairCode->Create(240,253,300,30);
		//	//m_pTxtPairCode->SetTextPos(150,15);
		//	m_pTxtPairCode->SetTextStyle(RE_TS_NORMAL);
		//	m_pTxtPairCode->SetFontSize(24,24);
		//	m_pTxtPairCode->EnableMsg(false);
		//	m_pTxtPairCode->SetTxtColor(255,255,255);
		//	//m_pTxtPairCode->SetText(L"配对码:");
		//	m_pGrpCtrlNotice->AddChild(m_pTxtPairCode);
		//	m_pTxtPairCode->SetShow(false);
		//}
		//m_pTxtPairResult = new HCTextCtrl;
		//if(m_pTxtPairResult != NULL)
		//{
		//	m_pTxtPairResult->Create(240,298,300,30);
		//	//m_pTxtPairCode->SetTextPos(150,15);
		//	m_pTxtPairResult->SetTextStyle(RE_TS_NORMAL);
		//	m_pTxtPairResult->SetFontSize(24,24);
		//	m_pTxtPairResult->EnableMsg(false);
		//	m_pTxtPairResult->SetTxtColor(255,255,255);
		//	m_pTxtPairResult->SetText(L"等待连接中");
		//	m_pGrpCtrlNotice->AddChild(m_pTxtPairResult);
		//	m_pTxtPairResult->SetShow(false);
		//}
		//m_pGrpCtrlNotice->SetShow(false);
		
		m_pGrpBTPair = new HCGroupCtrl;
		if(m_pGrpBTPair != NULL)
		{
			m_pGrpBTPair->Create(0,68,640,344);
			
			m_pBtnPair = new HCButton;
			if(m_pBtnPair != NULL)
			{
				m_pBtnPair->Create(70,144,570,70);
				m_pBtnPair->SetCallBackDown(OnEnterPairMode,this);
				m_pBtnPair->SetBkgndA(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Fa_Bt_A.hfp")));
				m_pBtnPair->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Fa_Bt_N.hfp")));
				//m_pBtnPair->SetCallBackDown(OnDeleteAll,this);
				m_pBtnPair->SetTextStyle(RE_TS_CENTER);
				m_pBtnPair->SetTextColorN(255,255,255);
				m_pBtnPair->EnableMsg(true);
				m_pBtnPair->SetTextPos(249 ,27);
				m_pBtnPair->SetFontSize(24,24);
			//	m_pBtnPair->SetText(_T("匹配蓝牙设备"));
				m_pGrpBTPair->AddChild(m_pBtnPair);
			}
				
			m_pTxtPairNotice = new HCTextCtrl;
			if(m_pTxtPairNotice != NULL)
			{
				m_pTxtPairNotice->Create(50,245,550,30);
				m_pTxtPairNotice->SetTextStyle(RE_TS_NORMAL);
				m_pTxtPairNotice->SetFontSize(20,20);
				m_pTxtPairNotice->EnableMsg(false);
				m_pTxtPairNotice->SetTxtColor(255,255,255);
				m_pTxtPairNotice->SetText(L"你可打开[蓝牙可被发现]按钮通过手机搜索该设备");
				if(m_pGrpBTPair != NULL)
				{
					m_pGrpBTPair->AddChild(m_pTxtPairNotice);
				}
				//m_pTxtPairCode->SetShow(true);
			}
		
			m_pTxtPairDeviceName = new HCTextCtrl;
			if(m_pTxtPairDeviceName != NULL)
			{
				m_pTxtPairDeviceName->Create(50,290,550,30);
				m_pTxtPairDeviceName->SetTextStyle(RE_TS_NORMAL);
				m_pTxtPairDeviceName->SetFontSize(20,20);
				m_pTxtPairDeviceName->EnableMsg(false);
				m_pTxtPairDeviceName->SetTxtColor(255,255,255);
				//m_pTxtPairDeviceName->SetText(L"设备名称:");
				if(m_pGrpBTPair != NULL)
				{
					m_pGrpBTPair->AddChild(m_pTxtPairDeviceName);
				}
				m_pTxtPairDeviceName->SetShow(true);
			}
			m_pTxtPairDeviceCode = new HCTextCtrl;
			if(m_pTxtPairDeviceCode != NULL)
			{
				m_pTxtPairDeviceCode->Create(50,335,550,30);
				m_pTxtPairDeviceCode->SetTextStyle(RE_TS_NORMAL);
				m_pTxtPairDeviceCode->SetFontSize(20,20);
				m_pTxtPairDeviceCode->EnableMsg(false);
				m_pTxtPairDeviceCode->SetTxtColor(255,255,255);
				m_pTxtPairDeviceCode->SetText(L"配对码:");
				if(m_pGrpBTPair != NULL)
				{
					m_pGrpBTPair->AddChild(m_pTxtPairDeviceCode);
				}
				m_pTxtPairDeviceCode->SetShow(true);
					
			}
#if BTVERSION
            m_pTxtBTVersion = new HCTextCtrl;
			if(m_pTxtBTVersion != NULL)
			{
				m_pTxtBTVersion->Create(50,380,550,30);
				m_pTxtBTVersion->SetTextStyle(RE_TS_NORMAL);
				m_pTxtBTVersion->SetFontSize(20,20);
				m_pTxtBTVersion->EnableMsg(false);
				m_pTxtBTVersion->SetTxtColor(255,255,255);
				m_pTxtBTVersion->SetText(L"蓝牙版本:1.0.0      固件:2.2.4");
				if(m_pGrpBTPair != NULL)
				{
					m_pGrpBTPair->AddChild(m_pTxtBTVersion);
				}
				m_pTxtBTVersion->SetShow(true);
			}
#else
#endif
			m_pGrpBTPair->SetShow(false);
			AddChild(m_pGrpBTPair);
		}	
		m_pGrpUnconnectNotice = new HCGroupCtrl;
		if(m_pGrpUnconnectNotice != NULL)
		{
			m_pGrpUnconnectNotice->Create(0,0,800,480);
			AddChild(m_pGrpUnconnectNotice);
		}
		m_pImgUnconnectNoticeBK = new HCTextCtrl;
		if(m_pImgUnconnectNoticeBK != NULL)
		{
			m_pImgUnconnectNoticeBK->Create(0,0,m_width,m_height);
			m_pImgUnconnectNoticeBK->SetFillType(FT_LINEAR_ALPHAV);
			m_pImgUnconnectNoticeBK->SetFillColor(125,125,0);
			m_pImgUnconnectNoticeBK->SetShow(false);
			m_pImgUnconnectNoticeBK->EnableBeep(false);
			m_pGrpUnconnectNotice->AddChild(m_pImgUnconnectNoticeBK);
		}
		m_pImgUnconnectNoticeFrame = new HCImageCtrl;
		if(m_pImgUnconnectNoticeFrame != NULL)
		{
			m_pImgUnconnectNoticeFrame->Create(160,140,500,220);
			m_pImgUnconnectNoticeFrame->SetBkgndN(GetHMIPath(_T("Share\\Share_Info_Frame.hfp")));
			m_pImgUnconnectNoticeFrame->EnableMsg(false);
			m_pGrpUnconnectNotice->AddChild(m_pImgUnconnectNoticeFrame);
		}
		m_pTxtUnconnectNotice = new HCTextCtrl;
		if(m_pTxtUnconnectNotice != NULL)
		{
			m_pTxtUnconnectNotice->Create(250,200,350,30);
			m_pTxtUnconnectNotice->SetTextPos(175,15);
			m_pTxtUnconnectNotice->SetTextStyle(RE_TS_CENTER);
			m_pTxtUnconnectNotice->SetFontSize(24,24);
			//m_pTxtUnconnectNotice->SetText(L"此操作将会断开当前连接!");
			m_pTxtUnconnectNotice->EnableMsg(false);
			m_pGrpUnconnectNotice->AddChild(m_pTxtUnconnectNotice);
		}
		m_pBtnConfirm = new HCButton;
		if(m_pBtnConfirm != NULL)
		{
			m_pBtnConfirm->Create(263,262,116,60);
			m_pBtnConfirm->SetBkgndN(GetHMIPath(_T("Setup\\General\\Setup_Sure_N.hfp")));
			m_pBtnConfirm->SetBkgndA(GetHMIPath(_T("Setup\\General\\Setup_Sure_A.hfp")));
			m_pBtnConfirm->SetFontSize(24,24);
			//m_pBtnConfirm->SetText(L"确认");
			m_pBtnConfirm->SetTextPos(58,30);
			m_pBtnConfirm->SetCallBack(OnConfirm,this);
			m_pBtnConfirm->SetTextStyle(RE_TS_CENTER);
			m_pGrpUnconnectNotice->AddChild(m_pBtnConfirm);
		}
		m_pBtnCannel = new HCButton;
		if(m_pBtnCannel != NULL)
		{
			m_pBtnCannel->Create(423,262,116,60);
			m_pBtnCannel->SetBkgndN(GetHMIPath(_T("Setup\\General\\Setup_Sure_N.hfp")));
			m_pBtnCannel->SetBkgndA(GetHMIPath(_T("Setup\\General\\Setup_Sure_A.hfp")));
			m_pBtnCannel->SetFontSize(24,24);
			m_pBtnCannel->SetTextStyle(RE_TS_CENTER);
			//m_pBtnCannel->SetText(L"取消");
			m_pBtnCannel->SetTextPos(58,30);
			m_pBtnCannel->SetCallBack(OnCannel,this);
			m_pGrpUnconnectNotice->AddChild(m_pBtnCannel);
		}
		m_pGrpUnconnectNotice->SetShow(false);
#if BTLOGSTATE
		m_pBtnCopyFile = new HCButton;
		if(m_pBtnCopyFile != NULL)
		{
			m_pBtnCopyFile->Create(636,340, 152, 64);
			m_pBtnCopyFile->SetFontSize(24,24);
			m_pBtnCopyFile->SetText(L"拷贝");
			m_pBtnCopyFile->SetCallBack(OnCopyBTLogFile,this);
			m_pBtnCopyFile->SetTextColorA(0,255,0);
			//m_pRightR->SetShow(false);
			AddChild(m_pBtnCopyFile);
		}
#endif
//#ifdef  TESTBTCOMMANDQUEUE
//		CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketReadLocalDeviceName,NULL);
//		CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketReadPairPassword,NULL);
//		CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketReadSoftVersion,NULL);
//		CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketListPairDevice,NULL);
//#else
//		HBYTE cCommand[20] = {0};
//		HUINT nCmdlen = strlen("AT+GLDN\r\n");
//		strncpy((char*)cCommand,"AT+GLDN\r\n",nCmdlen);
//		CBTCommand::Instance()->SendData(cCommand,nCmdlen);
//		nCmdlen = strlen("AT+GFPC\r\n");
//		strncpy((char*)cCommand,"AT+GFPC\r\n",nCmdlen);
//		CBTCommand::Instance()->SendData(cCommand,nCmdlen);
//		nCmdlen = strlen("AT+GVER\r\n");
//		strncpy((char*)cCommand,"AT+GVER\r\n",nCmdlen);
//		CBTCommand::Instance()->SendData(cCommand,nCmdlen);
//		nCmdlen = strlen("AT+LSPD\r\n");
//		strncpy((char*)cCommand,"AT+LSPD\r\n",nCmdlen);
//		CBTCommand::Instance()->SendData(cCommand,nCmdlen);
//#endif
		SetShow(true);
//		AddChild(m_pGrpCtrlNotice);
		SetBTDlgBackGround( );
		
		m_bPairNoticeShow = false;
		m_iSelectConnectDevice = -1;
		m_nTotalPairedNum = 0;
		m_ctDeadTime.SetCallBack(OnDeadTime,this);
		AddTimer(&m_ctDeadTime);
		AddTimer(&m_ctBTClose);
		m_ctBTClose.SetCallBack(CloseBt,this);
		m_nDeadTime = 0;
		m_bConnected = false;
		m_iSelectedButton = -1;
		//ChangeLangue(0);
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
		UpdataBTBottomState();
	}
	//SetPopupInfor(L"删除将会断开当前连接");
	return nRet;
}
void HCBTConnectionssettingDlg::ChangeLangue(HINT nType)
{
	BTDEBUGINFO(L"HCBTConnectionssettingDlg:: ChangeLangue");
	HCBluetoothBaseDlg::ChangeLangue(nType);
	if(s_pLan == NULL)
	{
		BTDEBUGINFO(L"s_pLan = null");
	}
	if(s_pLan != NULL)
	{
		BTDEBUGINFO(L"HCBTConnectionssettingDlg::%s,%d",__FUNCTIONW__,nType);
		switch (nType)
		{
			case 0:
			{
				
				m_pBtnDeviceUnconnect->SetFontSize(24,24);
				m_pBtnDeviceDelete->SetFontSize(24,24);
				m_pBtnDeviceDeleteAll->SetFontSize(24,24);
				m_pBtnPhonePair->SetFontSize(24,24);
				m_pBtnPair->SetFontSize(24,24);
				m_pBtnCannel->SetFontSize(24,24);
				m_pBtnConfirm->SetFontSize(24,24);
				m_pTxtUnconnectNotice->SetFontSize(24,24);
			}
			break;
			case 1:
			{
				m_pBtnDeviceUnconnect->SetFontSize(18,18);
				m_pBtnDeviceDelete->SetFontSize(18,18);
				m_pBtnDeviceDeleteAll->SetFontSize(18,18);
				m_pBtnPhonePair->SetFontSize(18,18);
				m_pBtnPair->SetFontSize(18,18);
				m_pBtnCannel->SetFontSize(18,18);
				m_pBtnConfirm->SetFontSize(18,18);
				m_pTxtUnconnectNotice->SetFontSize(18,18);
			}
			break;
			default:
			break;
		}
		m_pTxtScreen->SetText(s_pLan[4]);
		if(m_bConnected == false)
		{
			m_pBtnDeviceUnconnect->SetText(s_pLan[11]);
			
		}
		else
		{
			m_pBtnDeviceUnconnect->SetText(s_pLan[12]);
		}
		m_pBtnDeviceDelete->SetText(s_pLan[7]);
		m_pBtnDeviceDeleteAll->SetText(s_pLan[8]);
		m_pBtnPhonePair->SetText(s_pLan[25]);
		m_pBtnPair->SetText(s_pLan[27]);
		m_pTxtPairNotice->SetText(s_pLan[28]);
		m_pBtnCannel->SetText(s_pLan[34]);
		m_pBtnConfirm->SetText(s_pLan[33]);
		if(m_iSelectedButton == 1)
		{
			m_pTxtUnconnectNotice->SetText(s_pLan[32]);
		}
		else if(m_iSelectedButton == 2)
		{
			m_pTxtUnconnectNotice->SetText(s_pLan[35]);
		}
	
		HCHAR pTemp[30] = {0};
		HCHAR szTxtName[50] = {0};
		sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
		WCHAR szTemp2[50] = {0};
		if(p != NULL)
		{
			bool bRet = false;
			bRet = HCRegSeting::GetRegValueStr(_T("SoftWare\\Hzcar\\App\\BT"), _T("BTNAME"), (LPBYTE)szTemp2);
			HUINT n = wcslen(s_pLan[29]);
			if(bRet)
			{
				//wprintf(L"GetRegValueStr::%s\r\n",szTemp2);
				wcsncpy(szTxtName,s_pLan[29],n);
				wcsncpy(szTxtName + n,szTemp2,wcslen(szTemp2));
				m_pTxtPairDeviceName->SetText(szTxtName);
			}
			else
			{
				m_pTxtPairDeviceName->SetText(s_pLan[29]);
			}
			//int ntotal =MultiByteToWideChar(CP_UTF8,0,(char*)p->BTGeneralData.ZotyeDeviceINFO.LocaLDeviceINFO.szDeviceName,-1,pTemp,30);
			int ntotal =MultiByteToWideChar(CP_UTF8,0,(char*)p->BTGeneralData.ZotyeDeviceINFO.LocaLDeviceINFO.szDeviceName,-1,pTemp,30);
			pTemp[ntotal] =L'\0';
		
			wcsncpy(szTxtName,s_pLan[29],n);
			wcsncpy(szTxtName + n,pTemp,ntotal);
			//m_pTxtPairDeviceName->SetText(szTxtName);
			memset(szTxtName,0,sizeof(szTxtName));
			n = wcslen(s_pLan[30]);
			wcsncpy(szTxtName,s_pLan[30],n);
			memset(pTemp,0,sizeof(pTemp));
			ntotal = MultiByteToWideChar(CP_UTF8,0,(char*)p->BTGeneralData.ZotyeDeviceINFO.szPairCode,-1,pTemp,30);
			pTemp[ntotal] =L'\0';
			wcsncpy(szTxtName + n,pTemp,ntotal);
			m_pTxtPairDeviceCode->SetText(szTxtName);
		}
		//m_pTxtPairDeviceName->SetText(s_pLan[29]);
		//m_pTxtPairDeviceCode->SetText(s_pLan[30]);
	}
}
void HCBTConnectionssettingDlg:: SetBTDlgBackGround()
{
	EnableUpdateRect(false);
	HCBluetoothBaseDlg::SetBTDlgBackGround();
	HCBluetoothBaseDlg::SetBTCSBK();
	 sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
	 if(pSource != NULL)
	 {
		 m_pTxtConnectionSettingBK->SetBkgndN(pSource->m_pbtBkLeft);
		 m_pTxtConnectionSettingBK->SetOpacity(8);
		 m_pTxtDeviceLine1->SetBkgndN(pSource->m_pbtLine);
		 m_pTxtDeviceLine2->SetBkgndN(pSource->m_pbtLine);
		 m_pTxtDeviceLine3->SetBkgndN(pSource->m_pbtLine);
		 m_pTxtDeviceLine4->SetBkgndN(pSource->m_pbtLine);
		 m_pBtnPariedDevicesUp->SetBkgndN(pSource->m_pbtUpN);
		 m_pBtnPariedDevicesUp->SetBkgndA(pSource->m_pbtUpA);
		 //配对设备向下按钮
		 m_pBtnPariedDevicesDown->SetBkgndN(pSource->m_pbtDownN);
		 m_pBtnPariedDevicesDown->SetBkgndA(pSource->m_pbtDownA);
		 m_pScrCtrlConnectionSetting->SetBkgndN(pSource->m_pbtBarN);
		 m_pScrCtrlConnectionSetting->SetBkgndA(pSource->m_pbtBarA);
		 m_pScrCtrlConnectionSetting->SetBkgndD(pSource->m_pbtBarD);
		 m_pScrCtrlConnectionSetting->SetBkgndF(pSource->m_pbtBarF);
		 m_pGrpBTPair->SetBackGround(pSource->m_pbtBkLeft);
		 m_pTxtConnectionSettingHandleBK->SetBkgndN(pSource->m_pbtBkRight);
		 m_pTxtConnectionSettingHandleBK->SetOpacity(8);
	 }
	//m_pTxtNoticeBK->SetBkgndN(GetHMIPath(_T("Share\\Share_Info_Frame.hfp")));
	////配对设备滑块
	//m_pScrCtrlConnectionSetting->SetBkgndN(GetHMIPath(_T("Share\\Share_Slide_N.hfp")));
	//m_pScrCtrlConnectionSetting->SetBkgndA(GetHMIPath(_T("Share\\Share_Slide_Bar.hfp")));
	//m_pScrCtrlConnectionSetting->SetBkgndD(GetHMIPath(_T("Share\\Share_Slide_A.hfp")));
	//m_pScrCtrlConnectionSetting->SetBkgndF(GetHMIPath(_T("Share\\Share_Slide_Bar.hfp")));
	////配对设备向上按钮
	//m_pBtnPariedDevicesUp->SetBkgndN(GetHMIPath(_T("Share\\Share_Front_N.hfp")));
	//m_pBtnPariedDevicesUp->SetBkgndA(GetHMIPath(_T("Share\\Share_Front_A.hfp")));
	////配对设备向下按钮
	//m_pBtnPariedDevicesDown->SetBkgndN(GetHMIPath(_T("Share\\Share_Last_N.hfp")));
	//m_pBtnPariedDevicesDown->SetBkgndA(GetHMIPath(_T("Share\\Share_Last_A.hfp")));
	//连接设置操作背景
	//断开按钮
	m_pBtnPhonePair->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Phone_N.hfp")));
	m_pBtnPhonePair->SetBkgndA(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Phone_A.hfp")));
	//m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Bk_Frame_U.hfp")));
	//m_pBtnDeviceUnconnect->SetBkgndA(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Bk_A.hfp")));
	//删除按钮 
	m_pBtnDeviceDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
	m_pBtnDeviceDelete->SetBkgndA(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_A.hfp")));
	//全部删除按钮 
	m_pBtnDeviceDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
	m_pBtnDeviceDeleteAll->SetBkgndA(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_A.hfp")));
	EnableUpdateRect(true);
}
void HCBTConnectionssettingDlg::SetPairDeviceTxt(HCListItemBase* pItem,HBYTE* pTxt)
{
	if(pItem != NULL && pTxt != NULL)
	{
		HCHAR pTemp[31] = {0};
		int ntotal =MultiByteToWideChar(CP_UTF8,0,(char*)pTxt,-1,pTemp,30);
		pTemp[ntotal] =L'\0';
		pItem->SetText(pTemp);
//		SAFE_DELETE_GROUP(pTemp);
		/*sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
		if(p != NULL)
		{
			strcmp((char*)pTxt,p->BTGeneralData->CurrentPairDevice)
		}*/
	}	
}
HCListItem* HCBTConnectionssettingDlg::CreatPairDeviceItem(HBYTE* pTxt)
{
	if(pTxt != NULL)
	{
		HCHAR pTemp[31] = {0};
		HCListItem* pTempListItemChannel = new HCListItem;
		 int ntotal =MultiByteToWideChar(CP_UTF8,0,(char*)pTxt,-1,pTemp,30);
		 pTemp[ntotal] =L'\0';
		//mbstowcs(pTemp,(char*)pTxt,30)   ;
		pTempListItemChannel->Create(576 , 55, NULL, NULL);
		pTempListItemChannel->SetEnableRoll(true, 1);
		pTempListItemChannel->SetFontPos(5);
		pTempListItemChannel->SetRollWidth(400);

		pTempListItemChannel->SetIconPos(0,2);
		pTemp[30] =L'0';
		pTempListItemChannel->SetText(pTemp);
		
		pTempListItemChannel->SetCanFocus(true);
		sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
		if(pSource != NULL)
		{
			pTempListItemChannel->SetIcon(pSource->m_pbtConnectIconN);
			pTempListItemChannel->SetBkgndA(pSource->m_pbtItemSelected);
			pTempListItemChannel->SetBkgndF(pSource->m_pbtItemSelected);
		}
		return pTempListItemChannel;
	}
	return NULL;
}
void HCBTConnectionssettingDlg::AddPairedDevice()
{
	//HCHAR pTemp[30] = {0};
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	m_nTotalPairedNum = m_pScrBoxPariedDevices->GetListItemCount();
	if(p != NULL )
	{
		HUINT ntotalnum = p->BTGeneralData.nTotalPairDevice;
		if(ntotalnum > 0)
		{
			m_pScrCtrlConnectionSetting->SetBound(0,(ntotalnum-1)/5);
		}
		if(m_nTotalPairedNum < ntotalnum)
		{
			for(HUINT i = 0;i < m_nTotalPairedNum;i++)
			{
				HCListItemBase *pItem= m_pScrBoxPariedDevices->GetItemAt(i);
				if(pItem != NULL)
				{
					SetPairDeviceTxt(pItem,&(p->BTGeneralData.arrPairDevice[i]));
				}
			}
			for(HUINT i = m_nTotalPairedNum;i < ntotalnum;i++)
			{
				HCListItemBase *pItem = CreatPairDeviceItem(&(p->BTGeneralData.arrPairDevice[i]));
				if(pItem != NULL)
				{
					m_pScrBoxPariedDevices->AddListItem(pItem);
				}	
			}
			m_nTotalPairedNum = ntotalnum;
		}
		else 
		{
			for(HUINT i = m_nTotalPairedNum;i > ntotalnum; i--)
			{
				m_pScrBoxPariedDevices->DeleteListItem(m_pScrBoxPariedDevices->GetItemAt(i-1));
			}
			for(HUINT i= 0;i < ntotalnum; i++)
			{
				HCListItemBase *pItem= m_pScrBoxPariedDevices->GetItemAt(i);
				if(pItem != NULL)
				{
					SetPairDeviceTxt(pItem,&(p->BTGeneralData.arrPairDevice[i]));
				}
			}
		}
		m_nTotalPairedNum = ntotalnum;
		m_iSelectConnectDevice = -1;
	//	m_pScrBoxPariedDevices->SetSelectListItem(m_iSelectConnectDevice, false);
		m_pScrBoxPariedDevices->SetSelectListItem(-1, false);
		m_pBtnDeviceDelete->EnableMsg(FALSE);
		m_pBtnDeviceDelete->SetTextColorN(127,127,127);
		m_pBtnDeviceDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
		//m_pBtnDeviceDeleteAll->EnableMsg(FALSE);
		m_pBtnDeviceUnconnect->EnableMsg(false);
		m_pBtnDeviceUnconnect->SetTextColorN(127,127,127);
		m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Ct_D.hfp")));
		//m_pBtnDeviceUnconnect->SetText(L"连接");
		m_pBtnDeviceUnconnect->SetText(s_pLan[11]);
		m_bConnected = false;
		if(ntotalnum > 0)
		{
			//m_pBtnDeviceDeleteAll->Enable(true);
			m_pBtnDeviceDeleteAll->EnableMsg(true);
			m_pBtnDeviceDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_N.hfp")));
			m_pBtnDeviceDeleteAll->SetTextColorN(255,255,255);
		}
	}
}

void HCBTConnectionssettingDlg::OnDisconnect(void* pDlg, void* param)
{
	HCBTConnectionssettingDlg* pObj = (HCBTConnectionssettingDlg*)pDlg;
	pObj->OnDisconnect(pObj);
}
void HCBTConnectionssettingDlg::OnDisconnect(void* pDlg)
{

	HCListItemBase *pListItemSelect =NULL;
	HINT iSelectIndex = -1;
	sBTCommandData *pData = CBTCommand::Instance()->GetBTCommandData();
	pListItemSelect = m_pScrBoxPariedDevices->GetSelectListItem();
	if(pListItemSelect != NULL)
	{
		iSelectIndex = m_pScrBoxPariedDevices->GetListItemIndex(pListItemSelect);
	}
	if(iSelectIndex >= 0 && iSelectIndex< eMAXPAIRDEVICE && pData != NULL)
	{	
	/*	if(p->BTHFPData.nHFPState >= 2)
		{
			m_iSelectedButton = 0;
			if(!m_pGrpUnconnectNotice->IsShow())
			{
				m_pGrpUnconnectNotice->SetShow(true);
			}
			return;
		}*/
		
		if(m_bConnected == true)
		{
			HBYTE cCommand[30] = {0};
			HINT nlen = strlen("AT+DSCA\r\n");
			strncpy((char*)cCommand,"AT+DSCA\r\n",nlen);
			//strncpy((char*)(cCommand+ 7),(char*)CBTCommand::Instance()->GetBTCommandData()->BTGeneralData.arrPairDevice[iSelectIndex].szMacAddress,12);
			//		WideCharToMultiByte(CP_OEMCP,NULL,m_sDialNum.cDialNum,m_sDialNum.nCurrentLen,(char*)(cCommand+9),0,NULL,FALSE);
			//cCommand[nlen++] ='\r';
		//	cCommand[nlen++] ='\n';
			//cCommand[nlen++] ='\0';
			//AddPairedDevice();
			CBTCommand *p= CBTCommand::Instance();
			if(p != NULL)
			{
#ifdef  TESTBTCOMMANDQUEUE
				CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketDisconnectCurrentConnection,NULL);
#else
				p->SendData(cCommand,nlen);
#endif
				//p->MessageBtclose();
			}	
		}
		else
		{
			HBYTE cCommand[30] = {0};
			HINT nlen = strlen("AT+DSCA\r\n");
			strncpy((char*)cCommand,"AT+DSCA\r\n",nlen);
			CBTCommand *p= CBTCommand::Instance();
			if(p != NULL)
			{
#ifdef  TESTBTCOMMANDQUEUE
				//CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketDisconnectCurrentConnection,NULL);
#else
				p->SendData(cCommand,nlen);
#endif
			}
			Sleep(20);
#ifdef  TESTBTCOMMANDQUEUE
			//CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketExitPairMode,NULL);
#else
			HBYTE cCommand1  [20] = {0};
			HUINT nCmdlen = strlen("AT+EPRM=0\r\n");
			strncpy((char*)cCommand1,"AT+EPRM=0\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand1,nCmdlen);
#endif
			//Sleep(20);

     		//if(pData->BTGeneralData.nPairingState != 1)
//			{
//#ifdef  TESTBTCOMMANDQUEUE
//				CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketEnterPairMode,NULL);
//#else
//				HBYTE cCommand1  [20] = {0};
//				HUINT nCmdlen = strlen("AT+EPRM=1\r\n");
//				strncpy((char*)cCommand1,"AT+EPRM=1\r\n",nCmdlen);
//				CBTCommand::Instance()->SendData(cCommand1,nCmdlen);
//#endif
//				Sleep(80);
//			}
            if(m_nPairSend == 0)
			{
				#ifdef  TESTBTCOMMANDQUEUE
								CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketEnterPairMode,NULL);
				#else
								HBYTE cCommand1  [20] = {0};
								HUINT nCmdlen = strlen("AT+EPRM=1\r\n");
								strncpy((char*)cCommand1,"AT+EPRM=1\r\n",nCmdlen);
								CBTCommand::Instance()->SendData(cCommand1,nCmdlen);
				#endif
								Sleep(80);
			}
			memset(cCommand,0,sizeof(cCommand));
			nlen = strlen("AT+CPDL=");
			strncpy((char*)cCommand,"AT+CPDL=",nlen);
			strncpy((char*)(cCommand+ nlen),(char*)CBTCommand::Instance()->GetBTCommandData()->BTGeneralData.arrPairDevice[iSelectIndex].szMacAddress,12);
			nlen +=12;
			cCommand[nlen++] ='\r';
			cCommand[nlen++] ='\n';
			//cCommand[nlen++] ='\0';
			//AddPairedDevice();
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
		}
	}
	//m_pBtnDeviceUnconnect->EnableFocus(FALSE);
}

void HCBTConnectionssettingDlg::OnDelete(void* pDlg, void* param)
{
	HCBTConnectionssettingDlg* pObj = (HCBTConnectionssettingDlg*)pDlg;
	pObj->OnDelete(pObj);
}
void HCBTConnectionssettingDlg::OnDelete(void* pDlg)
{
	HCListItemBase *pListItemSelect =NULL;
	HINT iSelectIndex = -1;
	pListItemSelect = m_pScrBoxPariedDevices->GetSelectListItem();
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	if(pListItemSelect != NULL)
	{
		iSelectIndex = m_pScrBoxPariedDevices->GetListItemIndex(pListItemSelect);
	}
	if(iSelectIndex >= 0 && m_nTotalPairedNum > 0 && p != NULL)
	{
		//if(iSelectIndex == 0 && p->BTHFPData.nHFPState >= 2)
	//	{
			m_iSelectedButton = 1;
			//m_pTxtUnconnectNotice ->SetText(L"删除当前选中设备?");
			m_pTxtUnconnectNotice->SetText(s_pLan[32]);
			if(!m_pGrpUnconnectNotice->IsShow())
			{
				m_pGrpUnconnectNotice->SetShow(true);
			}
			return;
	//	}
		HBYTE cCommand[30] = {0};
		HINT nlen = strlen("AT+DLPD=");
		strncpy((char*)cCommand,"AT+DLPD=",nlen);
		strncpy((char*)(cCommand+ 8),(char*)CBTCommand::Instance()->GetBTCommandData()->BTGeneralData.arrPairDevice[iSelectIndex].szMacAddress,12);
		//WideCharToMultiByte(CP_OEMCP,NULL,m_sDialNum.cDialNum,m_sDialNum.nCurrentLen,(char*)(cCommand+9),0,NULL,FALSE);
		nlen += 12;
		cCommand[nlen++] ='\r';
		cCommand[nlen++] ='\n';
		//cCommand[nlen++] ='\0';
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
		CBTCommand::Instance()->SendData(cCommand,nlen++);
#endif
		m_pScrBoxPariedDevices->DeleteListItem(pListItemSelect);
		m_iSelectConnectDevice = -1;
		m_nTotalPairedNum  -= 1;
		if(p->BTGeneralData.nTotalPairDevice > 0)
		{
			p->BTGeneralData.nTotalPairDevice -= 1;
		}
		//m_pScrBoxPariedDevices->DeleteListItem(pListItemSelect);
	}
	m_nTotalPairedNum = m_pScrBoxPariedDevices->GetListItemCount();
	//m_pBtnDeviceDelete->EnableFocus(FALSE);
	m_pBtnDeviceDelete->EnableMsg(FALSE);
	m_pBtnDeviceDelete->SetTextColorN(127,127,127);
//	m_pBtnDeviceDelete->EnableFocus(FALSE);
	m_pBtnDeviceDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
	m_pBtnDeviceUnconnect->EnableMsg(FALSE);
	m_pBtnDeviceUnconnect->SetTextColorN(127,127,127);
	m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Ct_D.hfp")));
	//m_pBtnDeviceUnconnect->SetText(L"连接");
	m_pBtnDeviceUnconnect->SetText(s_pLan[11]);
	m_bConnected = false;
	if(m_nTotalPairedNum > 0)
	{
		m_pBtnDeviceDeleteAll->EnableMsg(TRUE);
		m_pBtnDeviceDeleteAll->SetTextColorN(255,255,255);
		m_pBtnDeviceDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_N.hfp")));
	}
	else
	{
		m_pBtnDeviceDeleteAll->EnableMsg(false);
		m_pBtnDeviceDeleteAll->SetTextColorN(127,127,127);
		m_pBtnDeviceDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
		m_iSelectConnectDevice = -1;
		m_nTotalPairedNum = 0;
	}
	//SetFocusLineWidth(0);
	
}
void HCBTConnectionssettingDlg::OnDeleteAll(void* pDlg, void* param)
{
	//CBTCommand *pComand=CBTCommand::Instance(); 
	//PortRetureData *pPortData= new PortRetureData;
	//pPortData->dwSize =65;
//	pPortData->pszAnsiData = new HBYTE[120];
	//memcpy(pPortData->pszAnsiData,"11\r\n+LSPD=0,123456789012,iphone\r\n+123456789\r\n56HKHKH25246\r\n+123456\r\nJKHK\r\n+12345678JJJJJJJJJJJJJJJJJJJJJ9",70);
	//pComand->ReadSerialData(pComand->GetBTPacketBuffer(),WM_PORT_READ_DATA,enPortReadOK,(LPARAM)pPortData,pComand);
	//SAFE_DELETE_GROUP(pPortData->pszAnsiData);
	//SAFE_DELETE(pPortData);
	HCBTConnectionssettingDlg* pObj = (HCBTConnectionssettingDlg*)pDlg;
	pObj->OnDeleteAll(pObj);
	/*
	BTDEBUGINFO(_T("[HCBTConnectionssettingDlg::OnDeleteAll]  Enter"));
	HCBTConnectionssettingDlg* pObj = (HCBTConnectionssettingDlg*)pDlg;
	pObj->OnDeleteAll(pObj);
	BTDEBUGINFO(_T("[HCBTConnectionssettingDlg::OnDeleteAll]  Exit"));
	*/
}
void HCBTConnectionssettingDlg::OnDeleteAll(void* pDlg)
{
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	if(p != NULL)
	{
		//if(p->BTHFPData.nHFPState >= 2)
		//{
		//m_pTxtUnconnectNotice->SetText(L"删除全部已配对列表?");
		if(m_pScrBoxPariedDevices->GetListItemCount() > 0)
		{
			m_iSelectedButton = 2;
			//m_pTxtUnconnectNotice->SetText(s_pLan[35]);
			m_pTxtUnconnectNotice->SetText(s_pLan[35]);
			if(!m_pGrpUnconnectNotice->IsShow())
			{
				m_pGrpUnconnectNotice->SetShow(TRUE);
			}
			//	}
			return;
		}
		
	}

	HBYTE cCommand  [50] = {0};
	HUINT nCmdlen = strlen("AT+DLPD=000000000000\r\n");
	strncpy((char*)cCommand,"AT+DLPD=000000000000\r\n",nCmdlen);
	m_pScrBoxPariedDevices->DeleteAllListItems();
	m_pScrCtrlConnectionSetting->SetValue(0);
	m_pScrCtrlConnectionSetting->SetBound(0,1);
	m_iSelectConnectDevice = -1;
	m_nTotalPairedNum = 0;
#ifdef TESTBTCOMMANDQUEUE
	Block *pBlock = CCommandPool::Intance()->PoolNew();
	if(pBlock != NULL)
	{
		sCommandData* pt = (sCommandData*)(pBlock->Buf);
		memset(pt,0,sizeof(sCommandData));
		memcpy(pt->szCommand,cCommand,nCmdlen);
		pt->nCmdLen = nCmdlen;
		CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHIDCUSendDataToHID,pBlock);
	}
#else
	CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
	m_pBtnDeviceUnconnect->EnableMsg(FALSE);
	m_pBtnDeviceUnconnect->SetTextColorN(127,127,127);
	//m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Bk_N.hfp")));
	m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Ct_D.hfp")));
	//m_pBtnDeviceUnconnect->SetText(L"连接");
	m_pBtnDeviceUnconnect->SetText(s_pLan[11]);
	m_bConnected = false;
	m_pBtnDeviceDelete->EnableMsg(FALSE);
	m_pBtnDeviceDelete->SetTextColorN(127,127,127);
//	m_pBtnDeviceDeleteAll->EnableFocus(FALSE);
	m_pBtnDeviceDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
	m_pBtnDeviceDeleteAll->EnableMsg(FALSE);
	m_pBtnDeviceDeleteAll->SetTextColorN(127,127,127);
	//m_pBtnDeviceDeleteAll->EnableFocus(FALSE);
	m_pBtnDeviceDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
	//SetFocusLineWidth(0);
	
	//UpdateWindow();
}
void HCBTConnectionssettingDlg::OnEnterPairPage(void* pDlg, void* param)
{
	HCBTConnectionssettingDlg* pObj = (HCBTConnectionssettingDlg*)pDlg;
	pObj->OnEnterPairPage(pObj);
}
#if TESTRESTARTPROTEM
 void HCBTConnectionssettingDlg::OnUpdataRestTime(void* pDlg, void* param)
 {
	 HCBTConnectionssettingDlg* pObj = (HCBTConnectionssettingDlg*)pDlg;
	 pObj->OnUpdataRestTime(pObj);
 }
void HCBTConnectionssettingDlg::OnUpdataRestTime(void* pDlg)
{
	PostMessage(CBTCommand::Instance()->GetMyHandel(),WM_USER + 51,0,0);
}
void HCBTConnectionssettingDlg::OnClearRestTime(void* pDlg, void* param)
{
	HCBTConnectionssettingDlg* pObj = (HCBTConnectionssettingDlg*)pDlg;
	pObj->OnClearRestTime(NULL);
}
void HCBTConnectionssettingDlg::OnClearRestTime(void* pDlg)
{
	PostMessage(CBTCommand::Instance()->GetMyHandel(),WM_USER + 51,1,0);
}
void HCBTConnectionssettingDlg::UpdataRestTime(int t)
{
	if(m_pBtnRestTime != NULL)
	{
		wchar_t szTemp[20] = {0};
		swprintf(szTemp,L"%d",t);
		m_pBtnRestTime->SetText(szTemp);
	}
}
#endif

void HCBTConnectionssettingDlg::OnEnterPairPage(void* pDlg)
{
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	::PostMessage(CBTCommand::Instance()->GetMyHandel(),WM_USER + 21,0,NULL);
	if(p != NULL)
	{
		if(m_bPairNoticeShow == false)
		{			
#ifdef  TESTBTCOMMANDQUEUE
	//	CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketReadLocalDeviceName,NULL);
	//	CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketReadPairPassword,NULL);
#else
			HBYTE cCommand[20] = {0};	
			HUINT nCmdlen = strlen("AT+GLDN\r\n");
			strncpy((char*)cCommand,"AT+GLDN\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
			nCmdlen = strlen("AT+GFPC\r\n");
			strncpy((char*)cCommand,"AT+GFPC\r\n",nCmdlen);
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
		    HCHAR pTemp[30] = {0};
			HCHAR szTxtName[50] = {0};
			//int ntotal =MultiByteToWideChar(CP_UTF8,0,(char*)p->BTGeneralData.LoaclDeviceINFO.LocaLDeviceINFO.szDeviceName,-1,pTemp,30);
			int ntotal =MultiByteToWideChar(CP_UTF8,0,(char*)p->BTGeneralData.ZotyeDeviceINFO.LocaLDeviceINFO.szDeviceName,-1,pTemp,30);
			pTemp[ntotal] =L'\0';
			m_pTxtPairNotice->SetText(s_pLan[28]);
			HUINT n = wcslen(s_pLan[29]);
			wcsncpy(szTxtName,s_pLan[29],n);
			wcsncpy(szTxtName + n,pTemp,ntotal);
			//m_pTxtPairDeviceName->SetText(szTxtName);
			memset(szTxtName,0,sizeof(szTxtName));
			//n = (strlen("配对码:")+1)/2;
			n = wcslen(s_pLan[30]);
			wcsncpy(szTxtName,s_pLan[30],n);
			memset(pTemp,0,sizeof(pTemp));
			//ntotal = MultiByteToWideChar(CP_UTF8,0,(char*)p->BTGeneralData.LoaclDeviceINFO.szPairCode,-1,pTemp,30);
			ntotal = MultiByteToWideChar(CP_UTF8,0,(char*)p->BTGeneralData.ZotyeDeviceINFO.szPairCode,-1,pTemp,30);
			pTemp[ntotal] =L'\0';
			wcsncpy(szTxtName + n,pTemp,ntotal);
			m_pTxtPairDeviceCode->SetText(szTxtName);
		  // m_pBtnPhonePair->SetText(_T("退出匹配"));
			m_pBtnPhonePair->SetText(s_pLan[26]);
			m_pGrpBTPair->SetShow(true);
		//m_nMode = 1;
			m_bPairNoticeShow = true;
			m_pGrpCtrlConnectionSettingMiddle->SetShow(false);
			m_pScrBoxPariedDevices->SetShow(false);
		}
		else
		{
			if(m_nMode == 1)
			{
				HBYTE cCommand  [50] = {0};
				HUINT nCmdlen = strlen("AT+EPRM=0\r\n");
				strncpy((char*)cCommand,"AT+EPRM=0\r\n",nCmdlen);
#ifdef  TESTBTCOMMANDQUEUE
				//CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketExitPairMode,NULL);
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
				OnEnterPairMode(NULL);
			}
			//m_pBtnPhonePair->SetText(_T("手机匹配"));
			m_pBtnPhonePair->SetText(s_pLan[25]);
			m_pGrpBTPair->SetShow(FALSE);
			//m_nMode = 0;
			m_bPairNoticeShow = false;
			m_pGrpCtrlConnectionSettingMiddle->SetShow(true);
			m_pScrBoxPariedDevices->SetShow(true);
			//m_pGrpBTPair->SetShow(false);
			m_nMode = 0;
			//m_pGrpCtrlNotice->SetShow(FALSE);
		}
	}
}
 void HCBTConnectionssettingDlg::OnScrBoxPariedDevices(void* pDlg, void* param)
{
	HCBTConnectionssettingDlg* pObj = (HCBTConnectionssettingDlg*)pDlg;
	pObj->OnScrBoxPariedDevices(pObj);
}
void HCBTConnectionssettingDlg::OnScrBoxPariedDevices(void* pDlg)
{
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	HCListItemBase *pListItemSelect = m_pScrBoxPariedDevices->GetSelectListItem();
	HINT iSelectIndex = -1;
	if(pListItemSelect != NULL && p != NULL)
	{
		iSelectIndex = m_pScrBoxPariedDevices->GetListItemIndex(pListItemSelect);
		if(m_iSelectConnectDevice == iSelectIndex && iSelectIndex >= 0)
		{
			OnDisconnect(NULL);

		}
		else 
		{
			m_iSelectConnectDevice = iSelectIndex;
		}
		//m_iSelectConnectDevice = iSelectIndex;
	}
	else
	{
		m_iSelectConnectDevice = -1;
	}
	if(m_iSelectConnectDevice >= 0)
	{
		m_pScrBoxPariedDevices->SetSelectListItem(m_iSelectConnectDevice, false);
		m_pBtnDeviceUnconnect->EnableMsg(true);
		m_pBtnDeviceUnconnect->SetTextColorN(255,255,255);
		if(strcmp((char*)(p->BTGeneralData.CurrentPairDevice.szMacAddress),(char*)(p->BTGeneralData.arrPairDevice[iSelectIndex].szMacAddress)) == 0)
		{
			m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Bk_N.hfp")));
			//m_pBtnDeviceUnconnect->SetText(L"断开");
			m_pBtnDeviceUnconnect->SetText(s_pLan[12]);
			m_bConnected = true;
		}
		else
		{
			m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Ct_N.hfp")));
			//m_pBtnDeviceUnconnect->SetText(L"连接");
			m_pBtnDeviceUnconnect->SetText(s_pLan[11]);
			m_bConnected = false;
		}
		m_pBtnDeviceDelete->EnableMsg(true);
		m_pBtnDeviceDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_N.hfp")));
		m_pBtnDeviceDelete->SetTextColorN(255,255,255);
	}
	else
	{
		m_iSelectConnectDevice = -1;
		m_pBtnDeviceUnconnect->EnableMsg(false);
		m_pBtnDeviceUnconnect->SetTextColorN(127,127,127);
		m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Ct_D.hfp")));
		//m_pBtnDeviceUnconnect->SetText(L"连接");
		m_pBtnDeviceUnconnect->SetText(s_pLan[11]);
		m_bConnected = false;
		m_pBtnDeviceDelete->EnableMsg(false);
		m_pBtnDeviceDelete->SetTextColorN(127,127,127);
		m_pBtnDeviceDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
	}
	if(m_nTotalPairedNum > 0)
	{
		m_pBtnDeviceDeleteAll->EnableMsg(true);
		m_pBtnDeviceDeleteAll->SetTextColorN(255,255,255);
		m_pBtnDeviceDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_N.hfp")));
	}
	else
	{
		m_pBtnDeviceDeleteAll->EnableMsg(FALSE);
		m_pBtnDeviceDeleteAll->SetTextColorN(127,127,127);
		m_pBtnDeviceDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
	}
}

void HCBTConnectionssettingDlg::SetPairDeviceTxt(HCListItemBase* pItem,sDeviceINFO* pDeviceINFO)
{
	if(pItem != NULL && pDeviceINFO != NULL)
	{
		HCHAR pTemp[31] = {0};
		int ntotal =MultiByteToWideChar(CP_UTF8,0,(char*)pDeviceINFO->szDeviceName,-1,pTemp,30);
		pTemp[ntotal] =L'\0';
		pItem->SetText(pTemp);
		sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
		if(p != NULL)
		{
			int n = strcmp((char*)(pDeviceINFO->szMacAddress),(char*)(p->BTGeneralData.CurrentPairDevice.szMacAddress));
			sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
			if(pSource != NULL)
			{
				if(n == 0)
				{
					
					((HCListItem*)pItem)->SetIcon(pSource->m_pbtConnectIconA);
				}
				else
				{
					((HCListItem*)pItem)->SetIcon(pSource->m_pbtConnectIconN);
				}
			}	
		}
	}	
}

HCListItem* HCBTConnectionssettingDlg::CreatPairDeviceItem(sDeviceINFO* pDeviceINFO)
{
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	if(pDeviceINFO != NULL && p != NULL)
	{
		HCHAR pTemp[31] = {0};
		HCListItem* pTempListItemChannel = new HCListItem;
		int ntotal =MultiByteToWideChar(CP_UTF8,0,(char*)pDeviceINFO->szDeviceName,-1,pTemp,30);
		pTemp[ntotal] =L'\0';
		pTempListItemChannel->Create(576 , 66, NULL, NULL);
		pTempListItemChannel->SetEnableRoll(true, 1);
		pTempListItemChannel->SetFontPos(5);
		pTempListItemChannel->SetRollWidth(400);
		int n = strcmp((char*)pDeviceINFO->szMacAddress,(char*)p->BTGeneralData.CurrentPairDevice.szMacAddress);
		sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
		if(pSource != NULL)
		{
			if(n == 0)
			{
				pTempListItemChannel->SetIcon(pSource->m_pbtConnectIconA);
			}
			else
			{
				pTempListItemChannel->SetIcon(pSource->m_pbtConnectIconN);
			}
			pTempListItemChannel->SetBkgndA(pSource->m_pbtItemSelected);
			pTempListItemChannel->SetBkgndF(pSource->m_pbtItemSelected);
		}	
		pTempListItemChannel->SetIconPos(0,2);
		pTemp[30] =L'0';
		pTempListItemChannel->SetText(pTemp);
		pTempListItemChannel->SetCanFocus(true);
		return pTempListItemChannel;
	}
	return NULL;
}
void HCBTConnectionssettingDlg::SetNoticeTxt(HINT nParam)
{
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	if(p != NULL)
	{
		if(nParam == 0)
		{
			HCHAR pTemp[30] = {0};
			HCHAR szTxtName[50] = {0};
			int ntotal =MultiByteToWideChar(CP_UTF8,0,(char*)p->BTGeneralData.LoaclDeviceINFO.LocaLDeviceINFO.szDeviceName,-1,pTemp,30);
			pTemp[ntotal] =L'\0';
	//		m_pTxtNotice->SetText(L"通过手机蓝牙搜索该设备");
			/*wcsncpy(szTxtName,L"通过手机蓝牙搜索该设备",n);
			wcsncpy(szTxtName + n,pTemp,ntotal);*/
			//m_pTxtNotice->SetText(szTxtName);
			HUINT n = (strlen("设备名称:")+1)/2;
			wcsncpy(szTxtName,L"设备名称:",n);
			wcsncpy(szTxtName + n,pTemp,ntotal);
		//	m_pTxtLocalDeviceName->SetText(szTxtName);
			memset(szTxtName,0,sizeof(szTxtName));
			n = (strlen("配对密码:")+1)/2;
			wcsncpy(szTxtName,L"配对密码:",n);
			memset(pTemp,0,sizeof(pTemp));
			ntotal = MultiByteToWideChar(CP_UTF8,0,(char*)p->BTGeneralData.LoaclDeviceINFO.szPairCode,-1,pTemp,30);
			pTemp[ntotal] =L'\0';
			wcsncpy(szTxtName + n,pTemp,ntotal);
		//	m_pTxtPairCode->SetText(szTxtName);	
			//m_pTxtPairResult->SetText(L"等待手机连接中…");
			//m_pClkDeadTime->SetTime(0,2,0);
		}
		else
		{
			/*HCHAR pTemp[30] = {0};
			HCHAR szTxtName[50] = {0};
			int ntotal =MultiByteToWideChar(CP_UTF8,0,(char*)p->BTGeneralData.LoaclDeviceINFO.LocaLDeviceINFO.szDeviceName,-1,pTemp,30);
			pTemp[ntotal] =L'\0';
			HUINT n = (strlen("本机名字:")+1)/2;
			wcsncpy(szTxtName,L"本机名字:",n);
			wcsncpy(szTxtName + n,pTemp,ntotal);
			m_pTxtNotice->SetText(szTxtName);
			m_pTxtLocalDeviceName->SetText(L"进入匹配失败");*/
			HCHAR pTemp[30] = {0};
			HCHAR szTxtName[50] = {0};
			int ntotal =MultiByteToWideChar(CP_UTF8,0,(char*)p->BTGeneralData.LoaclDeviceINFO.LocaLDeviceINFO.szDeviceName,-1,pTemp,30);
			pTemp[ntotal] =L'\0';
			//m_pTxtNotice->SetText(L"通过手机蓝牙搜索该设备");
			/*wcsncpy(szTxtName,L"通过手机蓝牙搜索该设备",n);
			wcsncpy(szTxtName + n,pTemp,ntotal);*/
			//m_pTxtNotice->SetText(szTxtName);
			HUINT n = (strlen("设备名称:")+1)/2;
			wcsncpy(szTxtName,L"设备名称:",n);
			wcsncpy(szTxtName + n,pTemp,ntotal);
			//m_pTxtLocalDeviceName->SetText(szTxtName);
			memset(szTxtName,0,sizeof(szTxtName));
			n = (strlen("配对密码:")+1)/2;
			wcsncpy(szTxtName,L"配对密码:",n);
			memset(pTemp,0,sizeof(pTemp));
			ntotal = MultiByteToWideChar(CP_UTF8,0,(char*)p->BTGeneralData.LoaclDeviceINFO.szPairCode,-1,pTemp,30);
			pTemp[ntotal] =L'\0';
			wcsncpy(szTxtName + n,pTemp,ntotal);
			//m_pTxtPairCode->SetText(szTxtName);	
			//m_pTxtPairResult->SetText(L"进入手机匹配失败!");
		}
	}
}
void HCBTConnectionssettingDlg::SetNoticeShow(HINT nParam)
{
	SetNoticeTxt(nParam);
	if(m_nMode == 1)
	{
	//	m_pGrpCtrlNotice->SetShow(true);
		m_pBtnDeviceUnconnect->EnableMsg(false);
		m_pBtnDeviceUnconnect->SetTextColorN(127,127,127);
		m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Ct_D.hfp")));
		//m_pBtnDeviceUnconnect->SetText(L"连接");
		m_pBtnDeviceUnconnect->SetText(s_pLan[11]);
		m_pBtnDeviceDelete->EnableMsg(false);
		m_bConnected = false;
		m_pBtnDeviceDelete->SetTextColorN(127,127,127);
		m_pBtnDeviceDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
		m_pBtnDeviceDeleteAll->EnableMsg(FALSE);
		m_pBtnDeviceDeleteAll->SetTextColorN(127,127,127);
		m_pBtnDeviceDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
	}
	else
	{
//		m_pGrpCtrlNotice->SetShow(false);
		//m_pBtnPhonePair->SetText(_T("手机匹配"));
		m_pBtnPhonePair->SetText(s_pLan[25]);
		m_nMode = 0;
	}
}

void HCBTConnectionssettingDlg::SetNoticeSuccess()
{
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	if(p != NULL)
	{
		/*	HCHAR pTemp[30] = {0};
		HCHAR szTxtName[50] = {0};
		int ntotal =MultiByteToWideChar(CP_UTF8,0,(char*)p->BTGeneralData.LoaclDeviceINFO.LocaLDeviceINFO.szDeviceName,-1,pTemp,30);
		pTemp[ntotal] =L'\0';
		HUINT n = (strlen("已连接至本机:")+1)/2;
		wcsncpy(szTxtName,L"已连接至本机:",n);
		wcsncpy(szTxtName + n,pTemp,ntotal);
		m_pTxtNotice->SetText(szTxtName);
		m_pTxtLocalDeviceName->SetText(L"连接成功！");*/
		    HCHAR pTemp[30] = {0};
			HCHAR szTxtName[50] = {0};
			int ntotal =MultiByteToWideChar(CP_UTF8,0,(char*)p->BTGeneralData.LoaclDeviceINFO.LocaLDeviceINFO.szDeviceName,-1,pTemp,30);
			pTemp[ntotal] =L'\0';
			//m_pTxtNotice->SetText(L"通过手机蓝牙搜索该设备");
			/*wcsncpy(szTxtName,L"通过手机蓝牙搜索该设备",n);
			wcsncpy(szTxtName + n,pTemp,ntotal);*/
			//m_pTxtNotice->SetText(szTxtName);
			HUINT n = (strlen("设备名称:")+1)/2;
			wcsncpy(szTxtName,L"设备名称:",n);
			wcsncpy(szTxtName + n,pTemp,ntotal);
			//m_pTxtLocalDeviceName->SetText(szTxtName);
			memset(szTxtName,0,sizeof(szTxtName));
			n = (strlen("配对密码:")+1)/2;
			wcsncpy(szTxtName,L"配对密码:",n);
			memset(pTemp,0,sizeof(pTemp));
			ntotal = MultiByteToWideChar(CP_UTF8,0,(char*)p->BTGeneralData.LoaclDeviceINFO.szPairCode,-1,pTemp,30);
			pTemp[ntotal] =L'\0';
			wcsncpy(szTxtName + n,pTemp,ntotal);
		//	m_pTxtPairCode->SetText(szTxtName);
			//m_pTxtPairResult->SetText(L"手机已连接成功!");
		  // m_pGrpCtrlNotice->SetShow(true);
	}
}
void HCBTConnectionssettingDlg::SetNoticeShowHide()
{
	//if(m_pGrpCtrlNotice->IsShow())
	//{
	//	m_pGrpCtrlNotice->SetShow(false);
	//	m_nMode = 0;
	//	//m_pBtnPhonePair->SetText(_T("手机匹配"));
	//	m_pBtnPhonePair->SetText(s_pLan[25]);
	//}
}
void HCBTConnectionssettingDlg::OnEnterPairMode(void* pDlg, void* param)
{
	HCBTConnectionssettingDlg* pObj = (HCBTConnectionssettingDlg*)pDlg;
	pObj->OnEnterPairMode(pObj);
}
void HCBTConnectionssettingDlg::OnEnterPairMode(void* pDlg)
{
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	if(m_nMode == 0)
	{
//		HBYTE cCommand[20] ={0};
		//HINT nCmdlen = 0;
		m_nPairSend ++;
#ifdef  TESTBTCOMMANDQUEUE
		CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketEnterPairMode,NULL);
#else
		nCmdlen = strlen("AT+EPRM=1\r\n");
		strncpy((char*)cCommand,"AT+EPRM=1\r\n",nCmdlen);
		CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
		//m_pBtnPair->SetText(L"请用蓝牙连接你的系统!");
		m_nMode = 1;
		m_nDeadTime = 120;
		OnDeadTime(NULL);
		m_pBtnPair->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Fa_Bt_A.hfp")));
	/*	if(m_ctDeadTime.IsActive())
		{
			m_ctDeadTime.StopTimer();
		}
		m_ctDeadTime.SetTime(100);
		m_ctDeadTime.StartTimer();*/
		//m_nDeadTime
	}
	else
	{
//		HBYTE cCommand[20] ={0};
	//	HINT nCmdlen = 0;
#ifdef  TESTBTCOMMANDQUEUE
        if(p != NULL)
		{
			if(p->BTHFPData.nHFPState < 2)
			{
				//CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketExitPairMode,NULL);
			}
		}
#else
	 /*nCmdlen = strlen("AT+EPRM=0\r\n");
	strncpy((char*)cCommand,"AT+EPRM=0\r\n",nCmdlen);
		CBTCommand::Instance()->SendData(cCommand,nCmdlen);
		*/
#endif
		//m_pBtnPair->SetText(L"匹配蓝牙设备");
		m_pBtnPair->SetText(s_pLan[27]);
		m_nMode = 0;
		m_nDeadTime = 120;
		m_pBtnPair->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Fa_Bt_N.hfp")));
		if(m_ctDeadTime.IsActive())
		{
			m_ctDeadTime.StopTimer();
		}
	}
}

void HCBTConnectionssettingDlg::OnSelectDeviceChange(void* pDlg, void* param,void* iparam)
{
	HCBTConnectionssettingDlg* pObj = (HCBTConnectionssettingDlg*)pDlg;
	pObj->OnSelectDeviceChange(NULL,NULL);
}
void HCBTConnectionssettingDlg::OnSelectDeviceChange(void* pDlg,void* param)
{
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	HCListItemBase *pListItemSelect = m_pScrBoxPariedDevices->GetSelectListItem();
	HINT iSelectIndex = -1;
	if(pListItemSelect != NULL && p != NULL)
	{
		iSelectIndex = m_pScrBoxPariedDevices->GetListItemIndex(pListItemSelect);
		m_iSelectConnectDevice = iSelectIndex;
	}
	else
	{
		m_iSelectConnectDevice = -1;
	}
	if(m_iSelectConnectDevice >= 0)
	{
		m_pScrBoxPariedDevices->SetSelectListItem(m_iSelectConnectDevice, false);
		m_pBtnDeviceUnconnect->EnableMsg(true);
		m_pBtnDeviceUnconnect->SetTextColorN(255,255,255);
		if(strcmp((char*)(p->BTGeneralData.CurrentPairDevice.szMacAddress),(char*)(p->BTGeneralData.arrPairDevice[iSelectIndex].szMacAddress)) == 0)
		{
			m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Bk_N.hfp")));
			//m_pBtnDeviceUnconnect->SetText(L"断开");
			m_pBtnDeviceUnconnect->SetText(s_pLan[12]);
			m_bConnected = true;
		}
		else
		{
			m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Ct_N.hfp")));
		//	m_pBtnDeviceUnconnect->SetText(L"连接");
			m_pBtnDeviceUnconnect->SetText(s_pLan[11]);
			m_bConnected = false;
		}
		m_pBtnDeviceDelete->EnableMsg(true);
		m_pBtnDeviceDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_N.hfp")));
		m_pBtnDeviceDelete->SetTextColorN(255,255,255);
	}
	else
	{
		m_iSelectConnectDevice = -1;
		m_pBtnDeviceUnconnect->EnableMsg(false);
		m_pBtnDeviceUnconnect->SetTextColorN(127,127,127);
		m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Ct_D.hfp")));
	//	m_pBtnDeviceUnconnect->SetText(L"连接");
		m_pBtnDeviceUnconnect->SetText(s_pLan[11]);
		m_bConnected = false;
		m_pBtnDeviceDelete->EnableMsg(false);
		m_pBtnDeviceDelete->SetTextColorN(127,127,127);
		m_pBtnDeviceDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
	}
	if(m_nTotalPairedNum > 0)
	{
		m_pBtnDeviceDeleteAll->EnableMsg(true);
		m_pBtnDeviceDeleteAll->SetTextColorN(255,255,255);
		m_pBtnDeviceDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_N.hfp")));
	}
	else
	{
		m_pBtnDeviceDeleteAll->EnableMsg(FALSE);
		m_pBtnDeviceDeleteAll->SetTextColorN(127,127,127);
		m_pBtnDeviceDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
	}
}
void HCBTConnectionssettingDlg::OnDeadTime(void* pDlg, void* param)
{
	HCBTConnectionssettingDlg* pObj = (HCBTConnectionssettingDlg*)pDlg;
	pObj->OnDeadTime(pObj);
}
void HCBTConnectionssettingDlg::OnDeadTime(void* pDlg)
{
	if(m_nDeadTime > 0)
	{
	   if(m_ctDeadTime.IsActive())
	   {
		   m_ctDeadTime.StopTimer();
	   }
	   m_ctDeadTime.SetTime(100);
	   m_ctDeadTime.StartTimer();
	   HCHAR szTemp[50] = {0};
	   HCHAR  szTempTime[10] ={0};
	   HINT nMin = m_nDeadTime/60;
	   HINT nSec = m_nDeadTime%60;
       if(nMin > 0)
	   {
		   swprintf_s(szTempTime,4,L"%d:",nMin);
		   if(nSec >= 10)
		   {
			  swprintf_s(szTempTime + 2,4,L"%d%d",nSec/10,nSec%10);
		   }
		   else
		   {
			    swprintf_s(szTempTime + 2,4,L"0%d",nSec);
		   }
	   }
	   else
	   {
		   if(nSec >= 10)
		   {
				swprintf_s(szTempTime,4,L"%d",nSec);
		   }
		   else
		   {
				 swprintf_s(szTempTime,2,L"%d",nSec);
		   }
	   }
	  //HCHAR *p = s_pLan[31];  
	  // HINT nlen = strlen((char*)s_pLan[31]);
	   HINT nlen = wcslen(s_pLan[31]);
		wcsncpy(szTemp,s_pLan[31],nlen);
	 //  HINT nlen = strlen("请用蓝牙设备连接您的系统! ");
	  // wcsncpy(szTemp,L"请用蓝牙设备连接您的系统! ",nlen);
	 // memcpy(szTemp + nlen/2 +1,szTempTime,sizeof(szTempTime));
	  m_pBtnPair->SetText(szTemp);
	  m_pBtnPair->AddText(szTempTime);
	  m_nDeadTime -=1; 
	}
	else
	{
		if(m_ctDeadTime.IsActive())
		{
			m_ctDeadTime.StopTimer();
		}
		OnEnterPairMode(NULL);
	}
}
void HCBTConnectionssettingDlg::OnOpenBT(void* pDlg, void* param)
{
	HCBTConnectionssettingDlg* pObj = (HCBTConnectionssettingDlg*)pDlg;
	pObj->OnOpenBT(pObj);
}
void HCBTConnectionssettingDlg::OnOpenBT(void* pDlg)
{
	CBTCommand::Instance()->MessageBtclose();
}
void  HCBTConnectionssettingDlg::UpDataIconUnconnect(void)
{
	HINT nTotal = m_pScrBoxPariedDevices->GetListItemCount();
	OnPairDeviceClick(m_iSelectConnectDevice);
	if(nTotal > 0)
	{
		for(int i = 0;i < nTotal;i++)
		{
			HCListItemBase *pItem= m_pScrBoxPariedDevices->GetItemAt(i);
		    sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
			if(pItem != NULL && pSource != NULL)
			{
				((HCListItem*)pItem)->SetIcon(pSource->m_pbtConnectIconN);
			}
		}
	}
}

void  HCBTConnectionssettingDlg::UpdataByHFPState(HINT nState)
{
	switch(nState)
	{
	   case 0:
	   {
			  UpDataIconUnconnect();
	   }
	   case 1:
		{
			SetBTConected(false);
			OnConnectionSetting(NULL);
	    }
		break;
	   case 2:
		   {
			   OnPairDeviceClick(m_iSelectConnectDevice);
		   }
	   case 3:
	   case 4:
	   case 5:
	   case 6:
	  {
			SetBTConected(true);
	  }
	  break;
	   default:
	 break;
	}
	UpdataBTBottomState();
}
bool HCBTConnectionssettingDlg::IsPairPageShow()
{
	return m_bPairNoticeShow;
}

void HCBTConnectionssettingDlg::CloseBt(void* pDlg, void* param)
{
	HCBTConnectionssettingDlg* pObj = (HCBTConnectionssettingDlg*)pDlg;
	pObj->CloseBt(pObj);
}
void HCBTConnectionssettingDlg::CloseBt(void* pDlg)
{
	if(m_ctBTClose.IsActive())
	{
		m_ctBTClose.StopTimer();
	}
  CBTCommand*p =  CBTCommand::Instance();
  if(p != NULL)
  {
	  p->CloseBT();
  }
}
void HCBTConnectionssettingDlg::StartCloseBT()
{
	BTDEBUGINFO(L"开始关闭蓝牙");
	HBYTE cCommand[20] ={0};
	HINT nCmdlen = 0;
	nCmdlen = strlen("AT+DSCA\r\n");
	strncpy((char*)cCommand,"AT+DSCA\r\n",nCmdlen);
#ifdef  TESTBTCOMMANDQUEUE
	CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketDisconnectCurrentConnection,NULL);
#else
	CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
	if(m_ctBTClose.IsActive())
	{
		m_ctBTClose.StopTimer();
	}
	m_ctBTClose.SetTime(500);
	m_ctBTClose.StartTimer();
}
void HCBTConnectionssettingDlg::OnPairDeviceClick(HINT iSelected)
{
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	if(iSelected >=0 && p != NULL)
	{
	//	m_pScrBoxPariedDevices->SetSelectListItem(m_iSelectConnectDevice, false);
		m_pBtnDeviceUnconnect->EnableMsg(true);
		m_pBtnDeviceUnconnect->SetTextColorN(255,255,255);
		if(strcmp((char*)(p->BTGeneralData.CurrentPairDevice.szMacAddress),(char*)(p->BTGeneralData.arrPairDevice[iSelected].szMacAddress)) == 0)
		{
			m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Bk_N.hfp")));
			//m_pBtnDeviceUnconnect->SetText(L"断开");
			m_pBtnDeviceUnconnect->SetText(s_pLan[12]);
			m_bConnected = true;
		}
		else
		{
			m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Ct_N.hfp")));
			//m_pBtnDeviceUnconnect->SetText(L"连接");
			m_pBtnDeviceUnconnect->SetText(s_pLan[11]);
			m_bConnected = false;
		}
		m_pBtnDeviceDelete->EnableMsg(true);
		m_pBtnDeviceDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_N.hfp")));
		m_pBtnDeviceDelete->SetTextColorN(255,255,255);
	}
}
void HCBTConnectionssettingDlg::StopDeadTimer()
{
	if(m_ctBTClose.IsActive())
	{
		m_ctBTClose.StopTimer();
	}
}
void HCBTConnectionssettingDlg::RequreSource()
{
	sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str(),eDIALOGT_BTCONNECTSETTING,0);
	if(pSource != NULL)
	{
		//m_pGrpBTPair->SetBackGround(pSource->m_pbtBkLeft);
		//m_pGrpBTPair->SetOpacity(8);
		m_pTxtConnectionSettingBK->SetBkgndN(pSource->m_pbtBkLeft);
		m_pTxtConnectionSettingBK->SetOpacity(8);
	}
	/*if(m_bSourceRealse == true)
	{
		EnableUpdateRect(false);
		DWORD nCostTime = GetTickCount();
		HCBTConnectionssettingDlg::SetBTDlgBackGround();
		sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
		HINT nHFPState = 0;
		if(p != NULL)
		{
			nHFPState = p->BTHFPData.nHFPState;
		}
		if(nHFPState < 2)
		{
			UpdataBTBottomState();
		}
		UpdataBTBottomState(nHFPState);
		EnableUpdateRect(true);
		BTDEBUGINFO(L"%s,Costtime = %d",__FUNCTIONW__,(GetTickCount() - nCostTime));
		BTDEBUGINFO(L"HCBTConnectionssettingDlg::%s",__FUNCTIONW__);
	}*/
}
void HCBTConnectionssettingDlg::ReleaseSource()
{
	if(m_bSourceRealse == false)
	{
		EnableUpdateRect(false);
		m_pGrpBTPair->SetBackGround(NULL);
		m_pTxtConnectionSettingBK->SetBkgndN(NULL);
		btSource::Instance()->ReleaseBtSource(eDIALOGT_BTCONNECTSETTING);
		m_bSourceRealse = true;
		EnableUpdateRect(true);
		BTDEBUGINFO(L"HCBTConnectionssettingDlg::%s",__FUNCTIONW__);
	}
}
#if SETBTNAME_MAC
void HCBTConnectionssettingDlg::UpdateDevName()
{
	HCHAR pTemp[30] = {0};
	HCHAR szTxtName[50] = {0};
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	WCHAR szTemp2[50] = {0};
	if(p != NULL)
	{
		bool bRet = false;
		bRet = HCRegSeting::GetRegValueStr(_T("SoftWare\\Hzcar\\App\\BT"), _T("BTNAME"), (LPBYTE)szTemp2);
		HUINT n = wcslen(s_pLan[29]);
		if(bRet)
		{
		//	wprintf(L"GetRegValueStr::%s\r\n",szTemp2);
			wcsncpy(szTxtName,s_pLan[29],n);
			wcsncpy(szTxtName + n,szTemp2,wcslen(szTemp2));
			m_pTxtPairDeviceName->SetText(szTxtName);
		}
		else
		{
			m_pTxtPairDeviceName->SetText(s_pLan[29]);
		}
	}
}
#endif
void HCBTConnectionssettingDlg::OnConfirm(void* pDlg, void* param)
{
	HCBTConnectionssettingDlg* pObj = (HCBTConnectionssettingDlg*)pDlg;
	pObj->OnConfirm(pObj);
}
void HCBTConnectionssettingDlg::OnConfirm(void* pDlg)
{
	//BTDEBUGINFO(L"");
	HCListItemBase *pListItemSelect =NULL;
	HINT iSelectIndex = -1;
	pListItemSelect = m_pScrBoxPariedDevices->GetSelectListItem();
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	if(pListItemSelect != NULL)
	{
		iSelectIndex = m_pScrBoxPariedDevices->GetListItemIndex(pListItemSelect);
	}
	switch (m_iSelectedButton)
	{
		case 0:
		{
			if(iSelectIndex >= 0 && iSelectIndex< eMAXPAIRDEVICE)
			{
						if(m_bConnected == true)
						{
							HBYTE cCommand[30] = {0};
							HINT nlen = strlen("AT+DSCA\r\n");
							strncpy((char*)cCommand,"AT+DSCA\r\n",nlen);
							//strncpy((char*)(cCommand+ 7),(char*)CBTCommand::Instance()->GetBTCommandData()->BTGeneralData.arrPairDevice[iSelectIndex].szMacAddress,12);
							//		WideCharToMultiByte(CP_OEMCP,NULL,m_sDialNum.cDialNum,m_sDialNum.nCurrentLen,(char*)(cCommand+9),0,NULL,FALSE);
							//cCommand[nlen++] ='\r';
						//	cCommand[nlen++] ='\n';
							//cCommand[nlen++] ='\0';
							//AddPairedDevice();
							CBTCommand *p= CBTCommand::Instance();
							if(p != NULL)
							{
				#ifdef  TESTBTCOMMANDQUEUE
								CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketDisconnectCurrentConnection,NULL);
				#else
								p->SendData(cCommand,nlen);
				#endif
								//p->MessageBtclose();
							}	
						}
						else
						{
							HBYTE cCommand[30] = {0};
							HINT nlen = strlen("AT+DSCA\r\n");
							strncpy((char*)cCommand,"AT+DSCA\r\n",nlen);
							CBTCommand *p= CBTCommand::Instance();
							if(p != NULL)
							{
				#ifdef  TESTBTCOMMANDQUEUE
								CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketDisconnectCurrentConnection,NULL);
				#else
								p->SendData(cCommand,nlen);
				#endif
							}
							Sleep(10);
							memset(cCommand,0,sizeof(cCommand));
							nlen = strlen("AT+CPDL=");
							strncpy((char*)cCommand,"AT+CPDL=",nlen);
							strncpy((char*)(cCommand+ nlen),(char*)CBTCommand::Instance()->GetBTCommandData()->BTGeneralData.arrPairDevice[iSelectIndex].szMacAddress,12);
							nlen +=12;
							cCommand[nlen++] ='\r';
							cCommand[nlen++] ='\n';
							//cCommand[nlen++] ='\0';
							//AddPairedDevice();
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
						}
			}
		}
		break;
		case 1:
		{
			if(iSelectIndex >= 0 && m_nTotalPairedNum > 0 && p != NULL)
			{
			/*	if(iSelectIndex == 0 && p->BTHFPData.nHFPState >= 2)
				{
					m_iSelectedButton = 1;
					if(!m_pGrpUnconnectNotice->IsShow())
					{
						m_pGrpUnconnectNotice->SetShow(true);
					}
					return;
				}*/
				HBYTE cCommand[30] = {0};
				HINT nlen = strlen("AT+DLPD=");
				strncpy((char*)cCommand,"AT+DLPD=",nlen);
				strncpy((char*)(cCommand+ 8),(char*)CBTCommand::Instance()->GetBTCommandData()->BTGeneralData.arrPairDevice[iSelectIndex].szMacAddress,12);
				//WideCharToMultiByte(CP_OEMCP,NULL,m_sDialNum.cDialNum,m_sDialNum.nCurrentLen,(char*)(cCommand+9),0,NULL,FALSE);
				nlen += 12;
				cCommand[nlen++] ='\r';
				cCommand[nlen++] ='\n';
				//cCommand[nlen++] ='\0';
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
				CBTCommand::Instance()->SendData(cCommand,nlen++);
#endif
				m_pScrBoxPariedDevices->DeleteListItem(pListItemSelect);
				m_iSelectConnectDevice = -1;
				m_nTotalPairedNum  -= 1;
				if(p->BTGeneralData.nTotalPairDevice > 0)
				{
					p->BTGeneralData.nTotalPairDevice -= 1;
				}
				//m_pScrBoxPariedDevices->DeleteListItem(pListItemSelect);
			}
			m_nTotalPairedNum = m_pScrBoxPariedDevices->GetListItemCount();
			//m_pBtnDeviceDelete->EnableFocus(FALSE);
			m_pBtnDeviceDelete->EnableMsg(FALSE);
			m_pBtnDeviceDelete->SetTextColorN(127,127,127);
			//	m_pBtnDeviceDelete->EnableFocus(FALSE);
			m_pBtnDeviceDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
			m_pBtnDeviceUnconnect->EnableMsg(FALSE);
			m_pBtnDeviceUnconnect->SetTextColorN(127,127,127);
			m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Ct_D.hfp")));
			//m_pBtnDeviceUnconnect->SetText(L"连接");
			m_pBtnDeviceUnconnect->SetText(s_pLan[11]);
			m_bConnected = false;
			if(m_nTotalPairedNum > 0)
			{
				m_pBtnDeviceDeleteAll->EnableMsg(TRUE);
				m_pBtnDeviceDeleteAll->SetTextColorN(255,255,255);
				m_pBtnDeviceDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_N.hfp")));
			}
			else
			{
				m_pBtnDeviceDeleteAll->EnableMsg(false);
				m_pBtnDeviceDeleteAll->SetTextColorN(127,127,127);
				m_pBtnDeviceDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
				m_iSelectConnectDevice = -1;
				m_nTotalPairedNum = 0;
			}
		}
		break;
		case 2:
		{
			HBYTE cCommand  [50] = {0};
			HUINT nCmdlen = strlen("AT+DLPD=000000000000\r\n");
			strncpy((char*)cCommand,"AT+DLPD=000000000000\r\n",nCmdlen);
			m_pScrBoxPariedDevices->DeleteAllListItems();
			m_pScrCtrlConnectionSetting->SetValue(0);
			m_pScrCtrlConnectionSetting->SetBound(0,1);
			m_iSelectConnectDevice = -1;
			m_nTotalPairedNum = 0;
#ifdef TESTBTCOMMANDQUEUE
			Block *pBlock = CCommandPool::Intance()->PoolNew();
			if(pBlock != NULL)
			{
				sCommandData* pt = (sCommandData*)(pBlock->Buf);
				memset(pt,0,sizeof(sCommandData));
				memcpy(pt->szCommand,cCommand,nCmdlen);
				pt->nCmdLen = nCmdlen;
				CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHIDCUSendDataToHID,pBlock);
			}
#else
			CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
			m_pBtnDeviceUnconnect->EnableMsg(FALSE);
			m_pBtnDeviceUnconnect->SetTextColorN(127,127,127);
			//m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Bk_N.hfp")));
			m_pBtnDeviceUnconnect->SetBkgndN(GetHMIPath(_T("Bluetooth\\Connection\\Connection_Ct_D.hfp")));
			//m_pBtnDeviceUnconnect->SetText(L"连接");
			m_pBtnDeviceUnconnect->SetText(s_pLan[11]);
			m_bConnected = false;
			m_pBtnDeviceDelete->EnableMsg(FALSE);
			m_pBtnDeviceDelete->SetTextColorN(127,127,127);
			//	m_pBtnDeviceDeleteAll->EnableFocus(FALSE);
			m_pBtnDeviceDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_D.hfp")));
			m_pBtnDeviceDeleteAll->EnableMsg(FALSE);
			m_pBtnDeviceDeleteAll->SetTextColorN(127,127,127);
			//m_pBtnDeviceDeleteAll->EnableFocus(FALSE);
			m_pBtnDeviceDeleteAll->SetBkgndN(GetHMIPath(_T("Bluetooth\\Share\\Bluetooth_Delete_All_D.hfp")));
		}
		break;
		default:
			break;
	}
	m_iSelectedButton = -1;
	if(m_pGrpUnconnectNotice->IsShow())
	{
		m_pGrpUnconnectNotice->SetShow(false);
	}
}
void HCBTConnectionssettingDlg::OnCannel(void* pDlg, void* param)
{
	HCBTConnectionssettingDlg* pObj = (HCBTConnectionssettingDlg*)pDlg;
	pObj->OnCannel(pObj);
}
void HCBTConnectionssettingDlg::OnCannel(void* pDlg)
{
	if(m_pGrpUnconnectNotice->IsShow())
	{
		m_pGrpUnconnectNotice->SetShow(false);
	}
}
//void HCBTConnectionssettingDlg::ClearAllRecords()
//{
//	HBYTE cCommand  [50] = {0};
//	HUINT nCmdlen = strlen("AT+DLPD=000000000000\r\n");
//	strncpy((char*)cCommand,"AT+DLPD=000000000000\r\n",nCmdlen);
//	m_pScrBoxPariedDevices->DeleteAllListItems();
//	m_pScrCtrlConnectionSetting->SetValue(0);
//	m_pScrCtrlConnectionSetting->SetBound(0,1);
//	m_iSelectConnectDevice = -1;
//	m_nTotalPairedNum = 0;
//#ifdef TESTBTCOMMANDQUEUE
//	Block *pBlock = CCommandPool::Intance()->PoolNew();
//	if(pBlock != NULL)
//	{
//		sCommandData* pt = (sCommandData*)(pBlock->Buf);
//		memset(pt,0,sizeof(sCommandData));
//		memcpy(pt->szCommand,cCommand,nCmdlen);
//		pt->nCmdLen = nCmdlen;
//		CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHIDCUSendDataToHID,pBlock);
//	}
//#else
//	CBTCommand::Instance()->SendData(cCommand,nCmdlen);
//#endif
//}
#if BTLOGSTATE
void HCBTConnectionssettingDlg::OnCopyBTLogFile(void *pDlg,void *)
{
	HCBTConnectionssettingDlg* pObj = (HCBTConnectionssettingDlg*)pDlg;
	pObj->OnCopyBTLogFile(pObj);
}
void HCBTConnectionssettingDlg::OnCopyBTLogFile(void *pa)
{
	HString appPath;
	HString appPath1;
	HString appPath3;
	HString appPath2;
	HCHAR		szPath[MAX_PATH] = {0};
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	appPath += szPath;
	HINT nPos = (HINT)appPath.rfind(_T('\\'));
	if(nPos == -1)
	{
		wprintf(L"[HCSourceBase::GetExePath] exe path error ");
		return ;
	}
	appPath = appPath.substr(0, nPos+1);
	appPath1= appPath;
	appPath2 = appPath;
	appPath += L"..\\Config\\BTLog.txt";
	appPath1 += L"..\\..\\..\\StorageCard\\BTLog.txt";
	appPath2 += L"..\\Config\\BTSerialDataLogfile.txt";
	appPath3 += L"..\\..\\..\\StorageCard\\BTSerialDataLogfile.txt";
	BOOL bret =  CopyFile(appPath.c_str(),appPath1.c_str(),false);
#if BTSerialPortData
	bret =  CopyFile(appPath2.c_str(),appPath3.c_str(),false);
#endif
}
#endif

void HCBTConnectionssettingDlg::ClearDeviceRecord()
{
	HBYTE cCommand  [50] = {0};
	HUINT nCmdlen = strlen("AT+DLPD=000000000000\r\n");
	strncpy((char*)cCommand,"AT+DLPD=000000000000\r\n",nCmdlen);
#ifdef TESTBTCOMMANDQUEUE
	Block *pBlock = CCommandPool::Intance()->PoolNew();
	if(pBlock != NULL)
	{
		sCommandData* pt = (sCommandData*)(pBlock->Buf);
		memset(pt,0,sizeof(sCommandData));
		memcpy(pt->szCommand,cCommand,nCmdlen);
		pt->nCmdLen = nCmdlen;
		//CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHIDCUSendDataToHID,pBlock);
	}
#else
	//CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
	CBTCommand::Instance()->SendData(cCommand,nCmdlen);
}