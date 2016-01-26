
#include "stdafx_public.h"
#include "DialogP.h"
/*************************************** ȫ�ֿ��� ***************************************/

static unsigned char g_uThemeMode = SP_STANDARD;

// Function name   : SetCurThemeMode
// Description     : ���õ�ǰ����
// Return type     : void 
// Argument        : unsigned char uThemeMode
// Remark          : 

void SetCurThemeMode(unsigned char uThemeMode)
{
	g_uThemeMode = uThemeMode;
}

// Function name   : GetCurThemeMode
// Description     : �õ���ǰ����
// Return type     : unsigned char 
// Argument        : void
// Remark          : 

unsigned char GetCurThemeMode(void)
{
	return g_uThemeMode;
}

// POPUP ����ͼ
static IReSurface * g_pSur_Popup_Bg = NULL;
// POPUP OK ��ť����ͼ
static IReSurface * g_pSur_Popup_Ok_N = NULL;
static IReSurface * g_pSur_Popup_Ok_A = NULL;
// POPUP CANCEL ��ť����ͼ
static IReSurface * g_pSur_Popup_Cancel_N = NULL;
static IReSurface * g_pSur_Popup_Cancel_A = NULL;

// Function name   : UnInitPopupSurface
// Description     : �ͷ�POPUP ͼƬ��Դ
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
// Description     : ��ʼ�� POPUP �е�ͼƬ��Դ
// Return type     : static void 
// Argument        : TCHAR * pszDirPath
// Remark          : �� WinMain ������ֻ��ʼ��һ�� �����ⷢ�͸ı�ʱ �� WindowProc ��Ϣ�������յ��� VWM_SETUP_CHANGE_THEME ��Ϣ����һ��

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

// Ӳ��ť�����Ƿ���Ч
static bool g_bIsCanDoHardKey = true;

// Function name   : IsCanDoHardKey
// Description     : �ܷ�ִ��Ӳ��ť����
// Return type     : bool ( true : ��ִ��Ӳ��ť���� false : ����ִ��Ӳ��ť���� )
// Argument        : void
// Remark          : 

bool IsCanDoHardKey(void)
{
	return g_bIsCanDoHardKey;
}

/*************************************** ��ʵ�� ***************************************/

// KDialogP


// ���캯��
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

// ��������
KDialogP::~KDialogP(void)
{
}


// Function name   : ShowPopup
// Description     : ��ʾ POPUP
// Return type     : void 
// Argument        : PopupType type = PT_NOR		( POPUP ���� Ĭ��Ϊ��׼���� )
// Argument        : HUSHORT uAutoHideTimer = 0	( 0 : �������Զ����� , > 0 : 10ms���뼶��ʱ���� )
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
	case PT_OK:			// OK ��ť�Ի���
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
	case PT_OKCANCEL:	// OK CANCEL �Ի���
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

	// POPUP ����ʱ��������ĳ����ť��λ�ô��ڰ���״���ͱ���Ҫ���ͷŵ�
	HMessage msg;
	msg.wParam = 0;
	msg.lParam = -1;
	msg.msgtype = KMSG_LBBUTTONUP;
	DoMessage(&msg);
}

// Function name   : HidePopup
// Description     : ����POPUP
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
// Description     : �л�����
// Return type     : virtual void 
// Argument        : HBYTE uType
// 
// Remark          : ���л�����ʱ����øú��� �����ظú���

void KDialogP::ChangeTheme(HBYTE uType)
{

}

// Function name   : DoMessage
// Description     : ��Ϣ������
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
	case KMSG_WND_ACTIVE:		// ���弤��
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
	case KMSG_LBBUTTONDOWN:		// ����
		{
			if( TRUE == bRet )
			{
				g_bIsCanDoHardKey = false;
			}
		}
		break;
	case KMSG_LBBUTTONUP:		// �ͷŰ���
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
// Description     : ��ʼ�� POPUP �ؼ�
// Return type     : void 
// Argument        : void
// 
// Remark          : 

void KDialogP::InitPopupCtrl(void)
{
	// ���ִ���
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

		// ��Ϣ�ؼ�
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

		// OK ��ť
		m_pBtn_OK = new HCButton;
		if( NULL != m_pBtn_OK )
		{
			m_pBtn_OK->Create(240,300,135,80);
			m_pBtn_OK->SetCallBack(OnPopupOk,this);
			m_pGrp_Popup->AddChild(m_pBtn_OK);
		}

		// CANCEL ��ť
		m_pBtn_CANCEL = new HCButton;
		if( NULL != m_pBtn_CANCEL )
		{
			m_pBtn_CANCEL->Create(425,300,135,80);
			m_pBtn_CANCEL->SetCallBack(OnPopupCancel,this);
			m_pGrp_Popup->AddChild(m_pBtn_CANCEL);
		}

		// �Զ�����POPUP ��ʱ��
		m_ctAutoHidePopup.SetCallBack(OnAutoHidePopup,this);
		AddTimer(&m_ctAutoHidePopup);
	}
}


// Function name   : ChangePopupStyle
// Description     : ����ģʽ�Ĳ�ͬ�ı�POPUP��STYLE
// Return type     : void 
// Argument        : void
// Remark          : 

void KDialogP::ChangePopupStyle(void)
{
	HCFont * pCurFont = GetRESingleton()->GetFont(0);

	// POPUP ����ͼ
	if( NULL != m_pGrp_Popup )
	{
		if( m_pGrp_Popup->GetBackGround() != g_pSur_Popup_Bg )
			m_pGrp_Popup->SetBackGround(g_pSur_Popup_Bg);
	}

	// OK ��ť
	if( NULL != m_pBtn_OK )
	{
		if( m_pBtn_OK->GetBKgndN() != g_pSur_Popup_Ok_N )
			m_pBtn_OK->SetBkgndN(g_pSur_Popup_Ok_N);

		if( m_pBtn_OK->GetBKgndA() != g_pSur_Popup_Ok_A )
			m_pBtn_OK->SetBkgndA(g_pSur_Popup_Ok_A);
	}

	// CANCEL ��ť
	if( NULL != m_pBtn_CANCEL )
	{
		if( m_pBtn_CANCEL->GetBKgndN() != g_pSur_Popup_Cancel_N )
			m_pBtn_CANCEL->SetBkgndN(g_pSur_Popup_Cancel_N);

		if( m_pBtn_CANCEL->GetBKgndA() != g_pSur_Popup_Cancel_A )
			m_pBtn_CANCEL->SetBkgndA(g_pSur_Popup_Cancel_A);
	}

	// ��Ϣ�ؼ�
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
// Description     : ����POPUP����ʾ����Ϣ
// Return type     : virtual void 
// Argument        : TCHAR * pszInfor	��Ϣ�ַ��� ֧�ֶ��� ��Ŀǰ���3��������Ϣ
// 
// Remark          : �Զ����� 3����Ϣ��λ����Ϣ

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
// Description     : �Զ�����POPUP�ص�����
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
// Description     : �Զ�����POPUP���ܺ���
// Return type     : void 
// Argument        : void * pParam
// 
// Remark          : 

void KDialogP::OnAutoHidePopup(void * pParam)
{
	// ֹͣTIMER
	m_ctAutoHidePopup.StopTimer();
	OnPopupAutoHide();
	// ����POPUP
	HidePopup();
}


// Function name   : OnPopupOk
// Description     : POPUP��OK��ť�ص�����
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
// Description     : POPUP��OK��ť���ܺ���
// Return type     : virtual void 
// Argument        : void * pParam
// Remark          : ���������غ� ���Լ��Ĵ���

void KDialogP::OnPopupOk(void * pParam)
{
}

// Function name   : OnPopupCancel
// Description     : POPUP��CANCEL��ť�ص�����
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
// Description     : POPUP��CANCEL��ť���ܺ���
// Return type     : static void 
// Argument        : void * pThis
// Argument        : void * pParam
// Remark          : ���������غ� ���Լ��Ĵ���

void KDialogP::OnPopupCancel(void * pParam)
{
}

void KDialogP::OnDeactivated()
{
	// EnableScreenDraw������Ӳ���ʾ����
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