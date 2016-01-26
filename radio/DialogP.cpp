
#include "stdafx_public.h"
#include "DialogP.h"
/*************************************** 全局控制 ***************************************/

static unsigned char g_uThemeMode = SP_STANDARD;

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
static IReSurface * g_pSur_Popup_Cancel_N = NULL;
static IReSurface * g_pSur_Popup_Cancel_A = NULL;

// Function name   : UnInitPopupSurface
// Description     : 释放POPUP 图片资源
// Return type     : void 
// Argument        : void
// Remark          : 

void UnInitPopupSurface(void)
{
	SAFE_DELETE(g_pSur_Popup_Cancel_A);
	SAFE_DELETE(g_pSur_Popup_Cancel_N);
	SAFE_DELETE(g_pSur_Popup_Ok_A);
	SAFE_DELETE(g_pSur_Popup_Ok_N);
	SAFE_DELETE(g_pSur_Popup_Bg);
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
	strTmp += _T("Share\\Share_Info_Frame.ktc");
	g_pSur_Popup_Bg = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	//strTmp += _T("Share\\ok_N.ktc");
	g_pSur_Popup_Ok_N = GetRESingleton()->CreateSurfaceFromFile(strTmp);
	strTmp = pszDirPath;
	//strTmp += _T("Share\\ok_A.ktc");
	g_pSur_Popup_Ok_A = GetRESingleton()->CreateSurfaceFromFile(strTmp);

	strTmp = pszDirPath;
	//strTmp += _T("Share\\cancel_N.ktc");
	g_pSur_Popup_Cancel_N = GetRESingleton()->CreateSurfaceFromFile(strTmp);
	strTmp = pszDirPath;
	//strTmp += _T("Share\\cancel_A.ktc");
	g_pSur_Popup_Cancel_A = GetRESingleton()->CreateSurfaceFromFile(strTmp);
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
: m_pGrp_Popup(NULL)
, m_pTxt_Popup_Cover(NULL)
, m_pBtn_OK(NULL)
, m_pBtn_CANCEL(NULL)
, m_uPopupType(PT_NOR)
, m_uThemeMode(SP_STANDARD)
{
	memset(m_pTxt_Popup_Infor,0,sizeof(m_pTxt_Popup_Infor));
	if( m_uThemeMode != GetCurThemeMode() )
	{
		m_uThemeMode = GetCurThemeMode();
	}
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
				m_pBtn_OK->MoveTo(332,300);
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
				m_pBtn_OK->MoveTo(240,300);
			}
			if( NULL != m_pBtn_CANCEL )
			{
				if( !m_pBtn_CANCEL->IsShow() )
				{
					m_pBtn_CANCEL->SetShow(true);
				}
				m_pBtn_CANCEL->MoveTo(425,300);
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
	case KMSG_WND_ACTIVE:		// 窗体激活
		{
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
		m_pGrp_Popup->Create(160,140,500,220);
		m_pGrp_Popup->SetShow(false);
		AddChild(m_pGrp_Popup);

		// 信息控件
		for (size_t i=0;i<(sizeof(m_pTxt_Popup_Infor)/sizeof(m_pTxt_Popup_Infor[0]));i++)
		{
			m_pTxt_Popup_Infor[i] = new HCTextCtrl;
			if( NULL != m_pTxt_Popup_Infor[i] )
			{
				m_pTxt_Popup_Infor[i]->Create(214,-100,380,40);
				m_pGrp_Popup->AddChild(m_pTxt_Popup_Infor[i]);
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
		if( NULL != m_pBtn_OK )
		{
			m_pBtn_OK->Create(240,300,135,80);
			m_pBtn_OK->SetCallBack(OnPopupOk,this);
			m_pGrp_Popup->AddChild(m_pBtn_OK);
		}

		// CANCEL 按钮
		m_pBtn_CANCEL = new HCButton;
		if( NULL != m_pBtn_CANCEL )
		{
			m_pBtn_CANCEL->Create(425,300,135,80);
			m_pBtn_CANCEL->SetCallBack(OnPopupCancel,this);
			m_pGrp_Popup->AddChild(m_pBtn_CANCEL);
		}

		// 自动隐藏POPUP 定时器
		m_ctAutoHidePopup.SetCallBack(OnAutoHidePopup,this);
		AddTimer(&m_ctAutoHidePopup);
	}
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
	}

	// OK 按钮
	if( NULL != m_pBtn_OK )
	{
		if( m_pBtn_OK->GetBKgndN() != g_pSur_Popup_Ok_N )
			m_pBtn_OK->SetBkgndN(g_pSur_Popup_Ok_N);

		if( m_pBtn_OK->GetBKgndA() != g_pSur_Popup_Ok_A )
			m_pBtn_OK->SetBkgndA(g_pSur_Popup_Ok_A);
	}

	// CANCEL 按钮
	if( NULL != m_pBtn_CANCEL )
	{
		if( m_pBtn_CANCEL->GetBKgndN() != g_pSur_Popup_Cancel_N )
			m_pBtn_CANCEL->SetBkgndN(g_pSur_Popup_Cancel_N);

		if( m_pBtn_CANCEL->GetBKgndA() != g_pSur_Popup_Cancel_A )
			m_pBtn_CANCEL->SetBkgndA(g_pSur_Popup_Cancel_A);
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

	nHeight = 170 - (HINT)((nFindCount-1)*20);

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
	}
}