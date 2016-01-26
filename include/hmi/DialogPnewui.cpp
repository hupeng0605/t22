
#include "stdafx_public.h"
#include "DialogP.h"
/*************************************** 全局控制 ***************************************/

static unsigned char g_uThemeMode = 0;

// Function name   : SetCurThemeMode
// Description     : 设置当前主题
// Return type     : void 
// Argument        : unsigned char uThemeMode
// Remark          : 

void SetCurThemeMode(unsigned char uThemeMode)
{
	g_uThemeMode = uThemeMode;
}

// Function name   : GetCurThemeMode
// Description     : 得到当前主题
// Return type     : unsigned char 
// Argument        : void
// Remark          : 

unsigned char GetCurThemeMode(void)
{
	return g_uThemeMode;
}

// POPUP 背景图
static IReSurface * g_pSur_Popup_Bg = NULL;
// POPUP OK 按钮背景图
static IReSurface * g_pSur_Popup_Ok_N = NULL;
static IReSurface * g_pSur_Popup_Ok_A = NULL;
// POPUP CANCEL 按钮背景图
//static IReSurface * g_pSur_Popup_Cancel_N = NULL;
//static IReSurface * g_pSur_Popup_Cancel_A = NULL;

// Head部控件
static IReSurface * g_pSur_Head_GrpCtrl_N = NULL;
static IReSurface * g_pSur_Head_Home_N = NULL;
static IReSurface * g_pSur_Head_Home_A = NULL;
static IReSurface * g_pSur_Head_Home_D = NULL;
static IReSurface * g_pSur_Head_Back_N = NULL;
static IReSurface * g_pSur_Head_Back_A = NULL;
static IReSurface * g_pSur_Head_Back_D = NULL;
static IReSurface * g_pSur_Head_Volume_Slider_N = NULL;
static IReSurface * g_pSur_Head_Volume_Slider_S = NULL;
static IReSurface * g_pSur_Head_Radio_Icon = NULL;
static IReSurface * g_pSur_Head_Phone_Icon = NULL;
static IReSurface * g_pSur_Head_SD_Icon = NULL;
static IReSurface * g_pSur_Head_USB_Icon = NULL;
static IReSurface * g_pSur_Head_BT_Icon = NULL;
static IReSurface * g_pSur_Head_Vol_Icon = NULL;
static IReSurface * g_pSur_Head_Vol_Mute_Icon = NULL;


// Function name   : UnInitPopupSurface
// Description     : 释放POPUP 图片资源
// Return type     : void 
// Argument        : void
// Remark          : 

void UnInitPopupSurface(void)
{
	//SAFE_DELETE(g_pSur_Popup_Cancel_A);
	//SAFE_DELETE(g_pSur_Popup_Cancel_N);
	SAFE_DELETE(g_pSur_Popup_Ok_A);
	SAFE_DELETE(g_pSur_Popup_Ok_N);
	SAFE_DELETE(g_pSur_Popup_Bg);

	SAFE_DELETE(g_pSur_Head_GrpCtrl_N);
	SAFE_DELETE(g_pSur_Head_Home_N);
	SAFE_DELETE(g_pSur_Head_Home_A);
	SAFE_DELETE(g_pSur_Head_Home_D);
	SAFE_DELETE(g_pSur_Head_Back_N);
	SAFE_DELETE(g_pSur_Head_Back_A);
	SAFE_DELETE(g_pSur_Head_Back_D);
	SAFE_DELETE(g_pSur_Head_Volume_Slider_N);
	SAFE_DELETE(g_pSur_Head_Volume_Slider_S);
	SAFE_DELETE(g_pSur_Head_Radio_Icon);
	SAFE_DELETE(g_pSur_Head_Phone_Icon);
	SAFE_DELETE(g_pSur_Head_SD_Icon);
	SAFE_DELETE(g_pSur_Head_USB_Icon);
	SAFE_DELETE(g_pSur_Head_BT_Icon);
	SAFE_DELETE(g_pSur_Head_Vol_Icon);
	SAFE_DELETE(g_pSur_Head_Vol_Mute_Icon);

	wprintf(L"[KDialogP::UnInitPopupSurface] release skin.\r\n");
}

// Function name   : InitPopupSurface
// Description     : 初始化 POPUP 中的图片资源
// Return type     : static void 
// Argument        : TCHAR * pszDirPath
// Remark          : 在 WinMain 函数中只初始化一次 或当主题发送改变时 在 WindowProc 消息函数中收到了 VWM_SETUP_CHANGE_THEME 消息调用一次

void InitPopupSurface(const TCHAR * pszDirPath)
{
	UnInitPopupSurface();

	if( NULL == pszDirPath ) return;

	HString strTmp;

	strTmp = pszDirPath;
	strTmp += _T("Share\\Share_Info_Frame.hfp");
	g_pSur_Popup_Bg = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	//strTmp += _T("Share\\ok_N.hfp");
	g_pSur_Popup_Ok_N = GetRESingleton()->CreateSurfaceFromFile(GetHMIPath(_T("Setup\\General\\Setup_Sure_N.hfp")));
	strTmp = pszDirPath;
	//strTmp += _T("Share\\ok_A.hfp");
	g_pSur_Popup_Ok_A = GetRESingleton()->CreateSurfaceFromFile(GetHMIPath(_T("Setup\\General\\Setup_Sure_A.hfp")));

	//strTmp = pszDirPath;
	//strTmp += _T("Share\\cancel_N.hfp");
	//g_pSur_Popup_Cancel_N = GetRESingleton()->CreateSurfaceFromFile(GetHMIPath(_T("Setup\\General\\Setup_Sure_N.hfp")));
	//strTmp = pszDirPath;
	//strTmp += _T("Share\\cancel_A.hfp");
	//g_pSur_Popup_Cancel_A = GetRESingleton()->CreateSurfaceFromFile(GetHMIPath(_T("Setup\\General\\Setup_Sure_A.hfp")));


	// 头部控件
	strTmp = pszDirPath;
	//strTmp += _T("Share\\Share_Frame_Top.hfp");
	
	strTmp += _T("NewUi\\01-Main_01 (2).hfp");
	g_pSur_Head_GrpCtrl_N = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	//strTmp += _T("Share\\Share_Home_N.hfp");
	strTmp += _T("NewUi\\USB-menu-01_03 (2).hfp");
	g_pSur_Head_Home_N = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	//strTmp += _T("Share\\Share_Home_A.hfp");
	//strTmp += _T("Share\\Share_Home_A.hfp");
	strTmp += _T("NewUi\\USB-menu-01_03 (3).hfp");
	g_pSur_Head_Home_A = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	//strTmp += _T("Share\\Share_Home_D.hfp");
	strTmp += _T("NewUi\\USB-menu-01_03 (2).hfp");
	g_pSur_Head_Home_D = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	//strTmp += _T("Share\\Share_Back_N.hfp");
	strTmp += _T("NewUi\\USB-menu-01_03-05.hfp");
	g_pSur_Head_Back_N = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	//strTmp += _T("Share\\Share_Back_A.hfp");
	strTmp += _T("NewUi\\USB-menu-01_03-05 (2).hfp");
	g_pSur_Head_Back_A = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	//strTmp += _T("Share\\Share_Back_D.hfp");
	strTmp += _T("NewUi\\USB-menu-01_03-05.hfp");
	g_pSur_Head_Back_D = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	strTmp += _T("Share\\Share_Volume_Bar 01.hfp");
	g_pSur_Head_Volume_Slider_N = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	strTmp += _T("Share\\Share_Volume_Bar 02.hfp");
	g_pSur_Head_Volume_Slider_S = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	strTmp += _T("Share\\Share_Radio_State.hfp");
	g_pSur_Head_Radio_Icon = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	//strTmp += _T("Share\\Share_Phone_State.hfp");
	strTmp += _T("NewUi\\USB-menu-01_03-10.hfp");//Ipod
	g_pSur_Head_Phone_Icon = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	//strTmp += _T("Share\\Share_SD_State.hfp");
	strTmp += _T("NewUi\\USB-menu-01_03-12.hfp");
	g_pSur_Head_SD_Icon = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	//strTmp += _T("Share\\Share_USB_State.hfp");
	strTmp += _T("NewUi\\USB-menu-01_03-14.hfp");
	g_pSur_Head_USB_Icon = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	//strTmp += _T("Share\\Share_BT_State.hfp");
	strTmp += _T("NewUi\\USB-menu-01_03-16.hfp");
	g_pSur_Head_BT_Icon = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	strTmp += _T("Share\\Share_Volume.hfp");
	g_pSur_Head_Vol_Icon = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	strTmp += _T("Share\\Share_Volume_Mune.hfp");
	g_pSur_Head_Vol_Mute_Icon = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	wprintf(L"[KDialogP::InitPopupSurface]  loaded skin. \r\n");
}

// 硬按钮操作是否有效
static bool g_bIsCanDoHardKey = true;

// Function name   : IsCanDoHardKey
// Description     : 能否执行硬按钮操作
// Return type     : bool ( true : 能执行硬按钮操作 false : 不能执行硬按钮操作 )
// Argument        : void
// Remark          : 

bool IsCanDoHardKey(void)
{
	return g_bIsCanDoHardKey;
}

/*************************************** 类实现 ***************************************/

// KDialogP


// 构造函数
KDialogP::KDialogP(void)
:m_pHeadBkgnd(NULL)
,m_pHeadGrpCtrl(NULL)
,m_pBtnHome(NULL)
,m_pTxtScreen(NULL)
,m_pTxtTemperature(NULL)
,m_pImgVolume(NULL)
,m_pVolumeSlider(NULL)
,m_pVolSize(NULL)
,m_pPhoneIco(NULL)
,m_pSDIco(NULL)
,m_pUsbIco(NULL)
,m_pBTIco(NULL)
,m_pBtnBack(NULL)
,m_pTxt_Popup_Cover(NULL)
,m_pBtn_OK(NULL)
,m_pBtn_CANCEL(NULL)
,m_pGrp_Popup(NULL)
,m_pszDlgPath(NULL)
, m_uPopupType(PT_NOR)
, m_uThemeMode(0)
{
	memset(m_pTxtTime,0,sizeof(m_pTxtTime));
	memset(m_pTxtAPM,0,sizeof(m_pTxtAPM));
	memset(m_pTxt_Popup_Infor,0,sizeof(m_pTxt_Popup_Infor));
	if( m_uThemeMode != GetCurThemeMode() )
	{
		m_uThemeMode = GetCurThemeMode();
	}
	m_bMainPage = false;
}

// 析构函数
KDialogP::~KDialogP(void)
{
}


// Function name   : ShowPopup
// Description     : 显示 POPUP
// Return type     : void 
// Argument        : PopupType type = PT_NOR		( POPUP 类型 默认为标准类型 )
// Argument        : HUSHORT uAutoHideTimer = 0	( 0 : 不进行自动隐藏 , > 0 : 10ms毫秒级定时隐藏 )
// Remark          : 

void KDialogP::ShowPopup(PopupType type,HUSHORT uAutoHideTimer)
{
	if( NULL != m_pTxt_Popup_Cover )
	{
		if( !m_pTxt_Popup_Cover->IsShow() )
		{
			m_pTxt_Popup_Cover->SetShow(true);
		}
	}
	if( NULL != m_pGrp_Popup )
	{
		if( !m_pGrp_Popup->IsShow() )
		{
			m_pGrp_Popup->SetShow(true);
		}
	}

	switch( type )
	{
	case PT_OK:			// OK 按钮对话框
		{
			if( NULL != m_pBtn_OK )
			{
				if( !m_pBtn_OK->IsShow() )
				{
					m_pBtn_OK->SetShow(true);
				}
				m_pBtn_OK->MoveTo(263+80,262);
			}
			if( NULL != m_pBtn_CANCEL )
			{
				if( m_pBtn_CANCEL->IsShow() )
				{
					m_pBtn_CANCEL->SetShow(false);
				}
			}
		}
		break;
	case PT_OKCANCEL:	// OK CANCEL 对话框
		{
			if( NULL != m_pBtn_OK )
			{
				if( !m_pBtn_OK->IsShow() )
				{
					m_pBtn_OK->SetShow(true);
				}
				m_pBtn_OK->MoveTo(263,262);
			}
			if( NULL != m_pBtn_CANCEL )
			{
				if( !m_pBtn_CANCEL->IsShow() )
				{
					m_pBtn_CANCEL->SetShow(true);
				}
				m_pBtn_CANCEL->MoveTo(423,262);
			}
		}
		break;
	default:
		{
			if( NULL != m_pBtn_OK )
			{
				if( m_pBtn_OK->IsShow() )
				{
					m_pBtn_OK->SetShow(false);
				}
			}
			if( NULL != m_pBtn_CANCEL )
			{
				if( m_pBtn_CANCEL->IsShow() )
				{
					m_pBtn_CANCEL->SetShow(false);
				}
			}
		}
		break;
	}

	if( uAutoHideTimer > 0 )
	{
		m_ctAutoHidePopup.SetTime(uAutoHideTimer);
		m_ctAutoHidePopup.StartTimer();
	}
	else
	{
		if( m_ctAutoHidePopup.IsActive() )
		{
			m_ctAutoHidePopup.StopTimer();
			m_ctAutoHidePopup.SetTime(uAutoHideTimer);
		}
	}

	m_uPopupType = type;

	// POPUP 出来时如果鼠标在某个按钮的位置处于按下状况就必须要先释放掉
	HMessage msg;
	msg.wParam = 0;
	msg.lParam = -1;
	msg.msgtype = KMSG_LBBUTTONUP;
	DoMessage(&msg);
}

// Function name   : HidePopup
// Description     : 隐藏POPUP
// Return type     : void 
// Argument        : void
// Remark          : 

void KDialogP::HidePopup(void)
{
	if( NULL != m_pTxt_Popup_Cover )
	{
		m_pTxt_Popup_Cover->SetShow(false);
	}
	if( NULL != m_pGrp_Popup )
	{
		m_pGrp_Popup->SetShow(false);
	}

	UpdateWindow();
}


// Function name   : ChangeTheme
// Description     : 切换主题
// Return type     : virtual void 
// Argument        : HBYTE uType
// 
// Remark          : 当切换主题时会调用该函数 请重载该函数

void KDialogP::ChangeTheme(HBYTE uType)
{

}

// Function name   : DoMessage
// Description     : 消息处理函数
// Return type     : HBOOL 
// Argument        : HMessage* msg
// 
// Remark          : 

HBOOL KDialogP::DoMessage(HMessage* msg)
{
	HBOOL bRet = false;

	bRet = HDialogBase::DoMessage(msg);

	switch( (HINT)msg->msgtype )
	{
	case VWM_SERVER_UPDATE_TEMPERATURE:
		{
			UpdateTemperature();
		}
		break;

	case VWM_SERVER_UPDATE_TIME:
		{
			OnAutoUpdateTime(NULL);
		}
		break;
	case VWM_SERVER_UPDATE_ITEM_STATUS:
		{
			UpdateHeadDevIcon();
		}
		break;
	case VWM_SERVER_KEY_ROTATE:
		{
			// 更新音量
			if (eKEY_VOL == msg->wParam)
			{
				UpdateVolumeBar();
			}
		}
		break;
	case KMSG_WND_ACTIVE:		// 窗体激活
		{
			// 窗口激活更新Head信息
			UpdateTemperature();
			UpdateVolumeBar();
			UpdateHeadDevIcon();
			OnAutoUpdateTime(NULL);

			if( PT_OKCANCEL == m_uPopupType )
			{
				HidePopup();
				OnPopupCancel(NULL);
			}

			if( m_uThemeMode != GetCurThemeMode() )
			{
				EnableUpdateRect(false);
				ChangeTheme(GetCurThemeMode());
				m_uThemeMode = GetCurThemeMode();
				EnableUpdateRect(true);
			}
			else
			{
				EnableUpdateRect(false);
				ChangePopupStyle();
				EnableUpdateRect(true);
			}
			ClearUpdateRect();

			bRet = true;
		}
		break;
	case WM_WINDOWPOSCHANGED:
		{
			LPWINDOWPOS lpWindowPos = reinterpret_cast<LPWINDOWPOS>(msg->lParam);
			if( NULL != lpWindowPos )
			{
				if( SWP_SHOWWINDOW == (lpWindowPos->flags & SWP_SHOWWINDOW) )
				{
					if( m_uThemeMode != GetCurThemeMode() )
					{
						EnableUpdateRect(false);
						ChangeTheme(GetCurThemeMode());
						m_uThemeMode = GetCurThemeMode();
						EnableUpdateRect(true);

						ClearUpdateRect();
					}
				}
			}
		}
		break;
	case KMSG_LBBUTTONDOWN:		// 按下
		{
			if( TRUE == bRet )
			{
				g_bIsCanDoHardKey = false;
			}
		}
		break;
	case KMSG_LBBUTTONUP:		// 释放按下
		{
			g_bIsCanDoHardKey = true;
		}
		break;
	default:
		break;
	}

	return bRet;
}


// Function name   : InitPopupCtrl
// Description     : 初始化 POPUP 控件
// Return type     : void 
// Argument        : void
// 
// Remark          : 

void KDialogP::InitPopupCtrl(void)
{
	// 遮罩窗体
	m_pTxt_Popup_Cover = new HCTextCtrl;
	if( NULL != m_pTxt_Popup_Cover )
	{
		m_pTxt_Popup_Cover->Create(0,0,m_width,m_height);
		m_pTxt_Popup_Cover->SetFillType(FT_LINEAR_ALPHAV);
		m_pTxt_Popup_Cover->SetFillColor(100,100,0);
		m_pTxt_Popup_Cover->SetShow(false);
		m_pTxt_Popup_Cover->EnableBeep(false);
		AddChild(m_pTxt_Popup_Cover);
	}

	// POPUP GROUP
	m_pGrp_Popup = new HCGroupCtrl;
	if( NULL != m_pGrp_Popup )
	{
		SAFECALL(m_pGrp_Popup)->Create(160,140,500,220);
		SAFECALL(m_pGrp_Popup)->SetShow(false);
		AddChild(m_pGrp_Popup);

		// 信息控件
		for (size_t i=0;i<(sizeof(m_pTxt_Popup_Infor)/sizeof(m_pTxt_Popup_Infor[0]));i++)
		{
			m_pTxt_Popup_Infor[i] = new HCTextCtrl;
			if( NULL != m_pTxt_Popup_Infor[i] )
			{
				m_pTxt_Popup_Infor[i]->Create(214,-50/*100*/,380,40);
				SAFECALL(m_pGrp_Popup)->AddChild(m_pTxt_Popup_Infor[i]);
				m_pTxt_Popup_Infor[i]->SetTextStyle(RE_TS_CENTER);
				m_pTxt_Popup_Infor[i]->SetTextPos(190,20);
				m_pTxt_Popup_Infor[i]->SetTxtColor(255,255,255);
				m_pTxt_Popup_Infor[i]->SetFont(GetRESingleton()->GetFont(0));
				m_pTxt_Popup_Infor[i]->SetFontSize(30,30);
				m_pTxt_Popup_Infor[i]->EnableMsg(false);
			}
		}

		// OK 按钮
		m_pBtn_OK = new HCButton;
		SAFECALL(m_pBtn_OK)->Create(263,262,116,60);
		SAFECALL(m_pBtn_OK)->SetFontSize(22, 22);
		SAFECALL(m_pBtn_OK)->SetFont(GetRESingleton()->GetFont(0));
		SAFECALL(m_pBtn_OK)->SetText(L"", 58, 30, RE_TS_CENTER);
		SAFECALL(m_pBtn_OK)->SetCallBack(OnPopupOk,this);
		SAFECALL(m_pGrp_Popup)->AddChild(m_pBtn_OK);

		// CANCEL 按钮
		m_pBtn_CANCEL = new HCButton;
		SAFECALL(m_pBtn_CANCEL)->Create(423,262,116,60);
		SAFECALL(m_pBtn_CANCEL)->SetFontSize(22, 22);
		SAFECALL(m_pBtn_CANCEL)->SetFont(GetRESingleton()->GetFont(0));
		SAFECALL(m_pBtn_CANCEL)->SetText(L"", 58, 30, RE_TS_CENTER);
		SAFECALL(m_pBtn_CANCEL)->SetCallBack(OnPopupCancel,this);
		SAFECALL(m_pGrp_Popup)->AddChild(m_pBtn_CANCEL);


		// 自动隐藏POPUP 定时器
		m_ctAutoHidePopup.SetCallBack(OnAutoHidePopup,this);
		AddTimer(&m_ctAutoHidePopup);
	}
}


void KDialogP::InitHeadCtrl(void)
{
	// 构建画面
	m_pHeadGrpCtrl = new HCGroupCtrl;
	SAFECALL(m_pHeadGrpCtrl)->Create(0, 0, 800, 60/*68*/);
	AddChild(m_pHeadGrpCtrl);

	m_pHeadBkgnd = new HCImageCtrl;
	//SAFECALL(m_pHeadBkgnd)->Create(0, 0, 800, 60/*68*/);
	SAFECALL(m_pHeadBkgnd)->Create(0, 0, 800, 64/*68*/);
	//SAFECALL(m_pHeadBkgnd)->Enable(false);
	SAFECALL(m_pHeadBkgnd)->EnableMsg(false);
	SAFECALL(m_pHeadGrpCtrl)->AddChild(m_pHeadBkgnd);

	m_pBtnHome = new HCButton;
	//SAFECALL(m_pBtnHome)->Create(0,0,86,68);
	SAFECALL(m_pBtnHome)->Create(20,4,56,50);
	SAFECALL(m_pBtnHome)->SetCallBack(OnBtnHome, this);
	SAFECALL(m_pHeadGrpCtrl)->AddChild(m_pBtnHome);

	m_pTxtScreen = new HCTextCtrl;
	SAFECALL(m_pTxtScreen)->Create(80,0,154,60);
	SAFECALL(m_pTxtScreen)->SetFont(GetRESingleton()->GetFont(0));
	SAFECALL(m_pTxtScreen)->SetTxtColor(255, 255, 255);
	SAFECALL(m_pTxtScreen)->SetFontSize(25,25);
	SAFECALL(m_pTxtScreen)->SetText(L"",0, 15,  RE_TS_NORMAL);
	SAFECALL(m_pHeadGrpCtrl)->AddChild(m_pTxtScreen);

	m_pImgVolume = new HCImageCtrl;
	SAFECALL(m_pImgVolume)->Create(233,0,42,68);
	SAFECALL(m_pImgVolume)->Enable(false);
	SAFECALL(m_pHeadGrpCtrl)->AddChild(m_pImgVolume);
    m_pImgVolume->Move(-35,0);
	// 音量条
	m_pVolumeSlider=new HCSlideCtrl;
	SAFECALL(m_pVolumeSlider)->Create(277,27,120,6,0,0);
	SAFECALL(m_pVolumeSlider)->SetBound(0,30);
	//m_pVolumeSlider->SetValue(20);
	SAFECALL(m_pVolumeSlider)->EnableMsg(false);
	SAFECALL(m_pHeadGrpCtrl)->AddChild(m_pVolumeSlider);
	 m_pVolumeSlider->Move(-35,0);
	m_pVolSize = new HCTextCtrl;
	SAFECALL(m_pVolSize)->Create(401,0,40,60);
	SAFECALL(m_pVolSize)->SetFontSize(22,22);
	SAFECALL(m_pVolSize)->SetFont(GetRESingleton()->GetFont(0));
	SAFECALL(m_pVolSize)->SetTxtColor(255, 255, 255);
	SAFECALL(m_pVolSize)->SetText(L"",5, 16,  RE_TS_NORMAL);
	SAFECALL(m_pHeadGrpCtrl)->AddChild(m_pVolSize);
     m_pVolSize->Move(-35,0);
	//m_pRadioIco = new HCImageCtrl;
	//m_pRadioIco->Create(494,0,26,68);
	//m_pRadioIco->SetShow(false);
	//m_pHeadGrpCtrl->AddChild(m_pRadioIco);
	m_pTxtTemperature = new HCTextCtrl;
	SAFECALL(m_pTxtTemperature)->Create(436,0,76,60);
	SAFECALL(m_pTxtTemperature)->SetFont(GetRESingleton()->GetFont(0));
	SAFECALL(m_pTxtTemperature)->SetTxtColor(255, 255, 255);
	SAFECALL(m_pTxtTemperature)->SetFontSize(22,22);
	SAFECALL(m_pTxtTemperature)->SetText(L"20℃",0, 17,  RE_TS_NORMAL);
	SAFECALL(m_pTxtTemperature)->SetShow(false);
	SAFECALL(m_pHeadGrpCtrl)->AddChild(m_pTxtTemperature);
	m_pTxtTemperature->Move(90,0);
	m_pPhoneIco = new HCImageCtrl;
	SAFECALL(m_pPhoneIco)->Create(528,18,22,27);
	SAFECALL(m_pPhoneIco)->SetShow(false);
	SAFECALL(m_pPhoneIco)->Enable(false);
	SAFECALL(m_pHeadGrpCtrl)->AddChild(m_pPhoneIco);
    m_pPhoneIco->Move(-110,0);
	m_pSDIco = new HCImageCtrl;
	SAFECALL(m_pSDIco)->Create(553,18,22,27);
	SAFECALL(m_pSDIco)->SetShow(false);
	SAFECALL(m_pSDIco)->Enable(false);
	SAFECALL(m_pHeadGrpCtrl)->AddChild(m_pSDIco);
	m_pSDIco->Move(-110,0);
	m_pUsbIco = new HCImageCtrl;
	SAFECALL(m_pUsbIco)->Create(578,18,22,27);
	SAFECALL(m_pUsbIco)->SetShow(false);
	SAFECALL(m_pUsbIco)->Enable(false);
	SAFECALL(m_pHeadGrpCtrl)->AddChild(m_pUsbIco);
	m_pUsbIco->Move(-110,0);
	m_pBTIco = new HCImageCtrl;
	SAFECALL(m_pBTIco)->Create(603,18,22,27);
	SAFECALL(m_pBTIco)->SetShow(false);
	SAFECALL(m_pBTIco)->Enable(false);
	SAFECALL(m_pHeadGrpCtrl)->AddChild(m_pBTIco);
	m_pBTIco->Move(-110,0);
	for (HINT i = 0; i < 2; ++i)
	{
		m_pTxtTime[i] = new HCTextCtrl;
		SAFECALL(m_pTxtTime[i])->Create(625+i*18, 0, 18, 60);
		SAFECALL(m_pTxtTime[i])->SetFontSize(40,40);
		SAFECALL(m_pTxtTime[i])->SetFont(GetRESingleton()->GetFont(FONT_QUARTZ_REGULAR_TTF));
		SAFECALL(m_pTxtTime[i])->SetTxtColor(255, 255, 255);
		SAFECALL(m_pTxtTime[i])->SetText(L"",9, 26,  RE_TS_CENTER);
		SAFECALL(m_pHeadGrpCtrl)->AddChild(m_pTxtTime[i]);
	}

	m_pTxtTime[2] = new HCTextCtrl;
	SAFECALL(m_pTxtTime[2])->Create(625+36, 0, 6, 60);
	SAFECALL(m_pTxtTime[2])->SetFontSize(40,40);
	SAFECALL(m_pTxtTime[2])->SetFont(GetRESingleton()->GetFont(FONT_QUARTZ_REGULAR_TTF));
	SAFECALL(m_pTxtTime[2])->SetTxtColor(255, 255, 255);
	SAFECALL(m_pTxtTime[2])->SetText(L":",3, 24,  RE_TS_CENTER);
	SAFECALL(m_pHeadGrpCtrl)->AddChild(m_pTxtTime[2]);

	for (HINT i = 3; i < 5; ++i)
	{
		m_pTxtTime[i] = new HCTextCtrl;
		SAFECALL(m_pTxtTime[i])->Create(625+42+(i-3)*18, 0, 18, 60);
		SAFECALL(m_pTxtTime[i])->SetFontSize(40,40);
		SAFECALL(m_pTxtTime[i])->SetFont(GetRESingleton()->GetFont(FONT_QUARTZ_REGULAR_TTF));
		SAFECALL(m_pTxtTime[i])->SetTxtColor(255, 255, 255);
		SAFECALL(m_pTxtTime[i])->SetText(L"",9, 26,  RE_TS_CENTER);
		SAFECALL(m_pHeadGrpCtrl)->AddChild(m_pTxtTime[i]);
	}

	m_pTxtAPM[0] = new HCTextCtrl;
	SAFECALL(m_pTxtAPM[0])->Create(705, 0, 6, 15);
	SAFECALL(m_pTxtAPM[0])->SetFontSize(12,12);
	SAFECALL(m_pTxtAPM[0])->SetFont(GetRESingleton()->GetFont(FONT_MSYH_TTF));
	SAFECALL(m_pTxtAPM[0])->SetTxtColor(255, 255, 255);
	SAFECALL(m_pTxtAPM[0])->SetText(L"A",3, 24,  RE_TS_CENTER);
	SAFECALL(m_pTxtAPM[0])->SetShow(false);
	SAFECALL(m_pHeadGrpCtrl)->AddChild(m_pTxtAPM[0]);
	m_pTxtAPM[0]->Move(-90,0);
	m_pTxtAPM[1] = new HCTextCtrl;
	SAFECALL(m_pTxtAPM[1])->Create(705, 15, 6, 15);
	SAFECALL(m_pTxtAPM[1])->SetFontSize(12,12);
	SAFECALL(m_pTxtAPM[1])->SetFont(GetRESingleton()->GetFont(FONT_MSYH_TTF));
	SAFECALL(m_pTxtAPM[1])->SetTxtColor(255, 255, 255);
	SAFECALL(m_pTxtAPM[1])->SetText(L"M",3, 24,  RE_TS_CENTER);
	SAFECALL(m_pTxtAPM[1])->SetShow(false);
	SAFECALL(m_pHeadGrpCtrl)->AddChild(m_pTxtAPM[1]);
	m_pTxtAPM[1]->Move(-90,0);
	// 60s更新一次
	m_cTime.SetTime(100*60);
	m_cTime.SetCallBack(OnAutoUpdateTime,this);
	AddTimer(&m_cTime);
	m_cTime.StartTimer();

	m_pBtnBack = new HCButton;
	SAFECALL(m_pBtnBack)->Create(714,4,56,50);
	SAFECALL(m_pBtnBack)->SetCallBack(OnBtnBackPrevious, this);
	SAFECALL(m_pHeadGrpCtrl)->AddChild(m_pBtnBack);
}

// Function name   : ChangePopupStyle
// Description     : 根据模式的不同改变POPUP的STYLE
// Return type     : void 
// Argument        : void
// Remark          : 

void KDialogP::ChangePopupStyle(void)
{
	HCFont * pCurFont = GetRESingleton()->GetFont(0);

	// POPUP 背景图
	if( NULL != m_pGrp_Popup )
	{
		if( m_pGrp_Popup->GetBackGround() != g_pSur_Popup_Bg )
			m_pGrp_Popup->SetBackGround(g_pSur_Popup_Bg);
		//m_pGrp_Popup->SetOpacity(8);
	}

	// OK 按钮
	if( NULL != m_pBtn_OK )
	{
		if( m_pBtn_OK->GetBKgndN() != g_pSur_Popup_Ok_N )
		{
			m_pBtn_OK->SetBkgndN(g_pSur_Popup_Ok_N);
		}
		
		if( m_pBtn_OK->GetBKgndA() != g_pSur_Popup_Ok_A )
		{	
			m_pBtn_OK->SetBkgndA(g_pSur_Popup_Ok_A);
		}

		//m_pBtn_OK->SetOpacity(8);
	}

	// CANCEL 按钮
	if( NULL != m_pBtn_CANCEL )
	{
		if( m_pBtn_CANCEL->GetBKgndN() != g_pSur_Popup_Ok_N )
			m_pBtn_CANCEL->SetBkgndN(g_pSur_Popup_Ok_N);

		if( m_pBtn_CANCEL->GetBKgndA() != g_pSur_Popup_Ok_A )
			m_pBtn_CANCEL->SetBkgndA(g_pSur_Popup_Ok_A);
		//m_pBtn_CANCEL->SetOpacity(8);
	}

	// 信息控件
	for (size_t i=0;i<(sizeof(m_pTxt_Popup_Infor)/sizeof(m_pTxt_Popup_Infor[0]));i++)
	{
		if( NULL != m_pTxt_Popup_Infor[i] )
		{
			if( m_pTxt_Popup_Infor[i]->GetFont() != pCurFont )
				m_pTxt_Popup_Infor[i]->SetFont(pCurFont);
		}
	}
}

void KDialogP::ChangeHeadCtrlStyle(void)
{
	SAFECALL(m_pHeadBkgnd)->SetBkgndN(g_pSur_Head_GrpCtrl_N);
	SAFECALL(m_pHeadBkgnd)->SetOpacity(8);

	SAFECALL(m_pBtnHome)->SetBkgndN(g_pSur_Head_Home_N);
	SAFECALL(m_pBtnHome)->SetBkgndA(g_pSur_Head_Home_A);
	SAFECALL(m_pBtnHome)->SetBkgndS(g_pSur_Head_Home_D);
	//SAFECALL(m_pBtnHome)->SetOpacity(8);

	SAFECALL(m_pBtnBack)->SetBkgndN(g_pSur_Head_Back_N);
	SAFECALL(m_pBtnBack)->SetBkgndA(g_pSur_Head_Back_A);
	SAFECALL(m_pBtnBack)->SetBkgndS(g_pSur_Head_Back_D);
	//SAFECALL(m_pBtnBack)->SetOpacity(8);

	SAFECALL(m_pVolumeSlider)->SetBkgndN(g_pSur_Head_Volume_Slider_N);
	SAFECALL(m_pVolumeSlider)->SetBkgndS(g_pSur_Head_Volume_Slider_S);	

	//m_pRadioIco->SetBkgndN(g_pSur_Head_Radio_Icon);
	SAFECALL(m_pPhoneIco)->SetBkgndN(g_pSur_Head_Phone_Icon);
	SAFECALL(m_pSDIco)->SetBkgndN(g_pSur_Head_SD_Icon);
	SAFECALL(m_pUsbIco)->SetBkgndN(g_pSur_Head_USB_Icon);
	SAFECALL(m_pBTIco)->SetBkgndN(g_pSur_Head_BT_Icon);

	UpdateTemperature();
	UpdateVolumeBar();
	UpdateHeadDevIcon();
	OnAutoUpdateTime(NULL);
}

void KDialogP::LoadPopupSkin()
{
	ChangePopupStyle();
	ChangeHeadCtrlStyle();
}

// Function name   : ReleasePopupSkin
// Description     : 退出到后台释放POPUP皮肤所占内存
// Return type     : void 
// Argument        : void
// 
// Writer          :     
// Date            :     
// Remark          : 
void KDialogP::ReleasePopupSkin()
{
	SAFECALL(m_pGrp_Popup)->SetBackGround(NULL);
	SAFECALL(m_pBtn_OK)->SetBkgndN(NULL);
	SAFECALL(m_pBtn_OK)->SetBkgndA(NULL);
	SAFECALL(m_pBtn_CANCEL)->SetBkgndN(NULL);
	SAFECALL(m_pBtn_CANCEL)->SetBkgndA(NULL);

	SAFECALL(m_pHeadGrpCtrl)->SetBackGround(NULL);
	SAFECALL(m_pBtnHome)->SetBkgndN(NULL);
	SAFECALL(m_pBtnHome)->SetBkgndA(NULL);
	SAFECALL(m_pBtnHome)->SetBkgndS(NULL);
	SAFECALL(m_pBtnBack)->SetBkgndN(NULL);
	SAFECALL(m_pBtnBack)->SetBkgndA(NULL);
	SAFECALL(m_pBtnBack)->SetBkgndS(NULL);
	SAFECALL(m_pVolumeSlider)->SetBkgndN(NULL);
	SAFECALL(m_pVolumeSlider)->SetBkgndS(NULL);	
	//SAFECALL(m_pRadioIco)->SetBkgndN(NULL);
	SAFECALL(m_pPhoneIco)->SetBkgndN(NULL);
	SAFECALL(m_pSDIco)->SetBkgndN(NULL);
	SAFECALL(m_pUsbIco)->SetBkgndN(NULL);
	SAFECALL(m_pBTIco)->SetBkgndN(NULL);
}


// Function name   : SetPopupInfor
// Description     : 设置POPUP中显示的信息
// Return type     : virtual void 
// Argument        : TCHAR * pszInfor	信息字符串 支持多行 但目前最多3行文字信息
// 
// Remark          : 自动调节 3行信息的位置信息

void KDialogP::SetPopupInfor(TCHAR * pszInfor)
{
	for (size_t i=0;i<(sizeof(m_pTxt_Popup_Infor)/sizeof(m_pTxt_Popup_Infor[0]));i++)
	{
		if( NULL != m_pTxt_Popup_Infor[i] )
		{
			m_pTxt_Popup_Infor[i]->SetText(_T(""));
		}
	}
	if( NULL == pszInfor ) return;
	size_t nFindIndex = 0;
	size_t nFinded = 0;
	size_t nFindCount = 0;
	HINT nHeight = 0;
	HString strInfo = pszInfor;

	while( -1 != nFinded )
	{
		nFinded = strInfo.find(_T('\n'),nFindIndex);
		if( -1 != nFinded )
		{
			if( nFindCount < (sizeof(m_pTxt_Popup_Infor)/sizeof(m_pTxt_Popup_Infor[0])) )
			{
				if( NULL != m_pTxt_Popup_Infor[nFindCount] )
				{
					m_pTxt_Popup_Infor[nFindCount]->SetText(strInfo.substr(nFindIndex,nFinded-nFindIndex).c_str());
				}
			}
			nFindCount++;
			nFindIndex = nFinded+1;
		}
		else
		{
			if( nFindCount < (sizeof(m_pTxt_Popup_Infor)/sizeof(m_pTxt_Popup_Infor[0])) )
			{
				if( NULL != m_pTxt_Popup_Infor[nFindCount] )
				{
					m_pTxt_Popup_Infor[nFindCount]->SetText(strInfo.substr(nFindIndex,strInfo.length()-nFindIndex).c_str());
				}
			}

			nFindCount++;
		}
	}

	nHeight = (SCREEN_HEIGHT - (nFindCount*40))/2;// 220/*170*/ - (HINT)((nFindCount-1)*20);
	for (size_t i=0;i<(sizeof(m_pTxt_Popup_Infor)/sizeof(m_pTxt_Popup_Infor[0]));i++)
	{
		if( NULL != m_pTxt_Popup_Infor[i] )
		{
			m_pTxt_Popup_Infor[i]->MoveTo(214,(HINT)(nHeight+i*40));
		}
	}
}


// Function name   : OnAutoHidePopup
// Description     : 自动隐藏POPUP回调函数
// Return type     : static void 
// Argument        : void * pThis
// Argument        : void * pParam
// 
// Remark          : 

void KDialogP::OnAutoHidePopup(void * pThis,void * pParam)
{
	reinterpret_cast<KDialogP*>(pThis)->OnAutoHidePopup(pParam);
}

void KDialogP::OnPopupAutoHide()
{
	return;
}

// Function name   : OnAutoHidePopup
// Description     : 自动隐藏POPUP功能函数
// Return type     : void 
// Argument        : void * pParam
// 
// Remark          : 

void KDialogP::OnAutoHidePopup(void * pParam)
{
	// 停止TIMER
	m_ctAutoHidePopup.StopTimer();
	OnPopupAutoHide();
	// 隐藏POPUP
	HidePopup();
}

void KDialogP::OnAutoUpdateTime(void * pThis,void * pParam)
{
	reinterpret_cast<KDialogP*>(pThis)->OnAutoUpdateTime(pParam);
}

void KDialogP::OnAutoUpdateTime(void * pParam)
{
	SYSTEMTIME systime; 
	// ::GetSystemTime(&systime); 
	::GetLocalTime(&systime);

	SETUPSETTING seting;
	memset(&seting,0,sizeof(seting));
	KCLastMemory::GetInstance()->GetSetupMemory(seting);

	WCHAR wcsTime[4] = {0};
	//wsprintf(wcsTime, L"%02d:%02d", ((seting.c12Or24)?(systime.wHour):(systime.wHour%12)), systime.wMinute);
	if (seting.c12Or24)
	{
		_itow(systime.wHour/10, wcsTime, 10);
		SAFECALL(m_pTxtTime[0])->SetText(wcsTime);
		ZeroMemory(wcsTime, 4*sizeof(WCHAR));
		_itow(systime.wHour%10, wcsTime, 10);
		SAFECALL(m_pTxtTime[1])->SetText(wcsTime);

		SAFECALL(m_pTxtAPM[0])->SetShow(false);
		SAFECALL(m_pTxtAPM[1])->SetShow(false);
	}
	else
	{
		WORD wHour = systime.wHour%12;
		wHour = ((wHour == 0) ? 12 : wHour);
		_itow(wHour/10, wcsTime, 10);
		SAFECALL(m_pTxtTime[0])->SetText(wcsTime);
		ZeroMemory(wcsTime, 4*sizeof(WCHAR));
		_itow(wHour%10, wcsTime, 10);
		SAFECALL(m_pTxtTime[1])->SetText(wcsTime);

		if (systime.wHour < 12)
		{
			SAFECALL(m_pTxtAPM[0])->SetText(L"A");
		} 
		else
		{
			SAFECALL(m_pTxtAPM[0])->SetText(L"P");
		}
		if(!m_bMainPage)
		{
			SAFECALL(m_pTxtAPM[0])->SetShow(true);
			SAFECALL(m_pTxtAPM[1])->SetShow(true);
		}
	}
	ZeroMemory(wcsTime, 4*sizeof(WCHAR));
	_itow(systime.wMinute/10, wcsTime, 10);
	SAFECALL(m_pTxtTime[3])->SetText(wcsTime);
	ZeroMemory(wcsTime, 4*sizeof(WCHAR));
	_itow(systime.wMinute%10, wcsTime, 10);
	SAFECALL(m_pTxtTime[4])->SetText(wcsTime);
}


// Function name   : OnPopupOk
// Description     : POPUP上OK按钮回调函数
// Return type     : static void 
// Argument        : void * pThis
// Argument        : void * pParam
// Remark          : 

void KDialogP::OnPopupOk(void * pThis,void * pParam)
{
	reinterpret_cast<KDialogP*>(pThis)->HidePopup();
	reinterpret_cast<KDialogP*>(pThis)->OnPopupOk(pParam);
}

// Function name   : OnPopupOk
// Description     : POPUP上OK按钮功能函数
// Return type     : virtual void 
// Argument        : void * pParam
// Remark          : 派生类重载后 做自己的处理

void KDialogP::OnPopupOk(void * pParam)
{
}

// Function name   : OnPopupCancel
// Description     : POPUP上CANCEL按钮回调函数
// Return type     : static void 
// Argument        : void * pThis
// Argument        : void * pParam
// Remark          : 

void KDialogP::OnPopupCancel(void * pThis,void * pParam)
{
	reinterpret_cast<KDialogP*>(pThis)->HidePopup();
	reinterpret_cast<KDialogP*>(pThis)->OnPopupCancel(pParam);
}

// Function name   : OnPopupCancel
// Description     : POPUP上CANCEL按钮功能函数
// Return type     : static void 
// Argument        : void * pThis
// Argument        : void * pParam
// Remark          : 派生类重载后 做自己的处理

void KDialogP::OnPopupCancel(void * pParam)
{
}


void KDialogP::OnBtnHome(void * pThis,void * pParam)
{
	reinterpret_cast<KDialogP*>(pThis)->OnBtnHome(pParam);
}

void KDialogP::OnBtnHome(void * pParam)
{
	HWND hServerWnd = CEIPC_GetHWND(IPC_ID_MANAGE);
	if (NULL != hServerWnd)
	{
		::PostMessage(hServerWnd, UWM_TOPBAR_HOME, 0, 0);
	}
}

void KDialogP::OnBtnBackPrevious(void * pThis,void * pParam)
{
	reinterpret_cast<KDialogP*>(pThis)->OnBtnBackPrevious(pParam);
}

void KDialogP::OnBtnBackPrevious(void * pParam)
{
	HWND hServerWnd = CEIPC_GetHWND(IPC_ID_MANAGE);
	if (NULL != hServerWnd)
	{
		::PostMessage(hServerWnd, UWM_TOPBAR_HOME, 0, 0);
	}
}

void KDialogP::OnDeactivated()
{
	// EnableScreenDraw处理叠加层显示错误
	EnableScreenDraw(FALSE);
	HidePopup();
	EnableScreenDraw(TRUE);
	OnPopupCancel(NULL);
}

void KDialogP::OnActivated(void)
{
	if( m_uThemeMode != GetCurThemeMode() )
	{
		EnableUpdateRect(false);
		ChangeTheme(GetCurThemeMode());
		m_uThemeMode = GetCurThemeMode();
		EnableUpdateRect(true);
		ClearUpdateRect();
	}
	else
	{
		ChangePopupStyle();
		ChangeHeadCtrlStyle();
	}

	UpdateVolumeBar();
}

void KDialogP::UpdateHeadDevIcon()
{
	DWORD dwDevStatus = KCStatusIcon::GetInstance()->GetStatus();
	if (dwDevStatus & IDDS_USB1 || dwDevStatus & IDDS_USB2)
	{
		SAFECALL(m_pUsbIco)->SetShow(true);
	}
	else
	{
		SAFECALL(m_pUsbIco)->SetShow(false);
	}

	if (dwDevStatus & IDDS_SD1 || dwDevStatus & IDDS_SD2)
	{
		SAFECALL(m_pSDIco)->SetShow(true);
	}
	else
	{
		SAFECALL(m_pSDIco)->SetShow(false);
	}

	if (dwDevStatus & IDDS_BT)
	{
		SAFECALL(m_pBTIco)->SetShow(true);
	}
	else
	{
		SAFECALL(m_pBTIco)->SetShow(false);
	}

	if (dwDevStatus & IDDS_IPOD)
	{
		SAFECALL(m_pPhoneIco)->SetShow(true);
	}
	else
	{
		SAFECALL(m_pPhoneIco)->SetShow(false);
	}

	//if (dwDevStatus & IDDS_RADIO)
	//{
	//	m_pRadioIco->SetShow(true);
	//}
	//else
	//{
	//	m_pRadioIco->SetShow(false);
	//}
}

void KDialogP::UpdateVolumeBar()
{
	SOUNDSETTING seting;
	KCLastMemory::GetInstance()->GetSoundMemory(seting);
	SAFECALL(m_pVolumeSlider)->SetValue(seting.uSoundVol);
	WCHAR szBuf[MAX_PATH] = {0};
	_itow(seting.uSoundVol, szBuf, 10);
	SAFECALL(m_pVolSize)->SetText(szBuf);

	if (0 != seting.uSoundVol)
	{
		SAFECALL(m_pImgVolume)->SetBkgndN(g_pSur_Head_Vol_Icon);
	}
	else
	{
		SAFECALL(m_pImgVolume)->SetBkgndN(g_pSur_Head_Vol_Mute_Icon);
	}
}

void KDialogP::UpdateTemperature()
{
	SOUNDSETTING setting;
	KCLastMemory::GetInstance()->GetSoundMemory(setting);
	if (setting.uAutoAir)
	{
		// 换算公式 F=(C×9/5)+32 ; 
		// C=(F-32)×5/9 ;式中F--华氏温度,C--摄氏温度 · 
		WCHAR wcsTemperature[16] = {0};
		DOUBLE dbTemperature = DOUBLE(setting.uOutdoorTemperature)/2 - 35;
		// 1 : 摄氏温度 2：华氏温度
		if (2 == setting.uTemperature)
		{
			swprintf(wcsTemperature, L"%.1f℉", (dbTemperature*9/5+32));
		}
		else
		{
			swprintf(wcsTemperature, L"%.1f℃", dbTemperature);
		}
		SAFECALL(m_pTxtTemperature)->SetText(wcsTemperature);
		SAFECALL(m_pTxtTemperature)->SetShow(true);
	}
	else
	{
		SAFECALL(m_pTxtTemperature)->SetShow(false);
	}
}
