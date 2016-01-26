

#ifndef __DIALOGP_DLG__
#define __DIALOGP_DLG__

/*************************************** ȫ�ֿ��� ***************************************/

// Function name   : UnInitPopupSurface
// Description     : �ͷ�POPUP ͼƬ��Դ
// Return type     : void 
// Argument        : void
// Remark          : 

void UnInitPopupSurface(void);

// Function name   : InitPopupSurface
// Description     : ��ʼ�� POPUP �е�ͼƬ��Դ
// Return type     : static void 
// Argument        : TCHAR * pszDirPath
// Remark          : �� WinMain ������ֻ��ʼ��һ�� �����ⷢ�͸ı�ʱ �� WindowProc ��Ϣ�������յ��� VWM_SETUP_CHANGE_THEME ��Ϣ����һ��

void InitPopupSurface(const TCHAR * pszDirPath);


// Function name   : SetCurThemeMode
// Description     : ���õ�ǰ����
// Return type     : void 
// Argument        : unsigned char uThemeMode
// Remark          : 

void SetCurThemeMode(unsigned char uThemeMode);

// Function name   : GetCurThemeMode
// Description     : �õ���ǰ����
// Return type     : unsigned char 
// Argument        : void
// Remark          : 

unsigned char GetCurThemeMode(void);

// Function name   : IsCanDoHardKey
// Description     : �ܷ�ִ��Ӳ��ť����
// Return type     : bool ( true : ��ִ��Ӳ��ť���� false : ����ִ��Ӳ��ť���� )
// Argument        : void
// Remark          : 

bool IsCanDoHardKey(void);

/*************************************** �ඨ�� ***************************************/

// KDialogP

class KDialogP : public HDialogBase
{
public:
	// POPUP ���Ͷ���
	typedef enum PopupType
	{
		PT_NOR = 0x00,		// ��׼����
		PT_OK,				// OK ��ť����
		PT_OKCANCEL			// OK CANCEL����
	};
public:

	// ���캯��
	KDialogP(void);

	// ��������
	virtual ~KDialogP(void);

	// Function name   : SetPopupInfor
	// Description     : ����POPUP����ʾ����Ϣ
	// Return type     : virtual void 
	// Argument        : TCHAR * pszInfor	��Ϣ�ַ��� ֧�ֶ��� ��Ŀǰ���3��������Ϣ
	// 
	// Remark          : �Զ����� 3����Ϣ��λ����Ϣ

	virtual void SetPopupInfor(TCHAR * pszInfor);

	// Function name   : ShowPopup
	// Description     : ��ʾ POPUP
	// Return type     : void 
	// Argument        : PopupType type = PT_NOR		( POPUP ���� Ĭ��Ϊ��׼���� )
	// Argument        : HUSHORT uAutoHideTimer = 0	( 0 : �������Զ����� , > 0 : 10ms���뼶��ʱ���� )
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	void ShowPopup(PopupType type = PT_NOR,HUSHORT uAutoHideTimer = 0);

	// Function name   : HidePopup
	// Description     : ����POPUP
	// Return type     : void 
	// Argument        : void
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	void HidePopup(void);


	// Function name   : ChangeTheme
	// Description     : �л�����
	// Return type     : virtual void 
	// Argument        : HBYTE uType
	// 
	// Writer          :     
	// Date            :     
	// Remark          : ���л�����ʱ����øú��� �����ظú���

	virtual void ChangeTheme(HBYTE uType);

	// Function name   : DoMessage
	// Description     : ��Ϣ������
	// Return type     : HBOOL 
	// Argument        : HMessage* msg
	// 
	// Writer          :     
	// Date            : 2013-11-25
	// Remark          : 

	virtual HBOOL DoMessage(HMessage* msg);

	virtual void OnDeactivated(void);
	virtual void OnActivated(void);
	// Function name   : OnPopupAutoHide
	// Description     : POPUP�Զ���ʧ��ʱ��֪ͨ
	// Return type     : void 
	// Argument        : void
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 
	virtual void OnPopupAutoHide();
protected:

	// Function name   : InitPopupCtrl
	// Description     : ��ʼ�� POPUP �ؼ�
	// Return type     : void 
	// Argument        : void
	// 
	// Writer          :     
	// Date            : 
	// Remark          : 

	virtual void InitPopupCtrl(void);

	// Function name   : InitHeadCtrl
	// Description     : ��ʼ�� POPUP �ؼ�
	// Return type     : void 
	// Argument        : void
	// 
	// Writer          :     
	// Date            : 
	// Remark          : 

	virtual void InitHeadCtrl(void);

	// Function name   : ChangePopupStyle
	// Description     : ����ģʽ�Ĳ�ͬ�ı�POPUP��STYLE
	// Return type     : void 
	// Argument        : void
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	virtual void ChangePopupStyle(void);

	// Function name   : ChangeHeadCtrlStyle
	// Description     : ����ģʽ�Ĳ�ͬ�ı�HeadCtrl��STYLE
	// Return type     : void 
	// Argument        : void
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	virtual void ChangeHeadCtrlStyle(void);

	// Function name   : LoadPopupSkin
	// Description     : ǰ̨����POPUPƤ��
	// Return type     : void 
	// Argument        : void
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 
	virtual void LoadPopupSkin(void);

	// Function name   : ReleasePopupSkin
	// Description     : ��̨�ͷ�POPUPƤ����ռ�ڴ�
	// Return type     : void 
	// Argument        : void
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 
	virtual void ReleasePopupSkin(void);

	// Function name   : OnAutoHidePopup
	// Description     : �Զ�����POPUP�ص�����
	// Return type     : static void 
	// Argument        : void * pThis
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	static void OnAutoHidePopup(void * pThis,void * pParam);

	// Function name   : OnAutoHidePopup
	// Description     : �Զ�����POPUP���ܺ���
	// Return type     : void 
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	void OnAutoHidePopup(void * pParam);

	// Function name   : OnAutoUpdateTime
	// Description     : �Զ�����ʱ��ص�����
	// Return type     : static void 
	// Argument        : void * pThis
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	static void OnAutoUpdateTime(void * pThis,void * pParam);

	// Function name   : OnAutoUpdateTime
	// Description     : �Զ�����ʱ��ص�����
	// Return type     : void 
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	void OnAutoUpdateTime(void * pParam);

	// Function name   : OnPopupOk
	// Description     : POPUP��OK��ť�ص�����
	// Return type     : static void 
	// Argument        : void * pThis
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	static void OnPopupOk(void * pThis,void * pParam);

	// Function name   : OnPopupOk
	// Description     : POPUP��OK��ť���ܺ���
	// Return type     : virtual void 
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : ���������غ� ���Լ��Ĵ���

	virtual void OnPopupOk(void * pParam);

	// Function name   : OnPopupCancel
	// Description     : POPUP��CANCEL��ť�ص�����
	// Return type     : static void 
	// Argument        : void * pThis
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	static void OnPopupCancel(void * pThis,void * pParam);

	// Function name   : OnPopupCancel
	// Description     : POPUP��CANCEL��ť���ܺ���
	// Return type     : static void 
	// Argument        : void * pThis
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : ���������غ� ���Լ��Ĵ���

	virtual void OnPopupCancel(void * pParam);

	// Function name   : OnBtnHome
	// Description     : Head��home��ť�ص�����
	// Return type     : static void 
	// Argument        : void * pThis
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 
	static void OnBtnHome(void* pThis, void* pParam); 

	// Function name   : OnBtnHome
	// Description     : Head��home��ť�ص�����
	// Return type     : static void 
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : ���������غ� ���Լ��Ĵ���
	virtual void OnBtnHome(void* pParam); 

	// Function name   : OnBtnBackPrevious
	// Description     : Head��back��ť�ص�����
	// Return type     : static void 
	// Argument        : void * pThis
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 
	static void OnBtnBackPrevious(void* pThis, void* pParam);

	// Function name   : OnBtnBackPrevious
	// Description     : Head��back��ť�ص�����
	// Return type     : static void 
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : ���������غ� ���Լ��Ĵ���
	virtual void OnBtnBackPrevious(void* pParam); 

	// Function name   : UpdateHeadDevIcon
	// Description     : Head���豸״̬ICON����
	// Return type     : static void 
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : ����������غ����Լ��Ĵ���
	virtual void UpdateHeadDevIcon();

	// Function name   : UpdateHeadDevIcon
	// Description     : Head���豸״̬ICON����
	// Return type     : static void 
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : ����������غ����Լ��Ĵ���
	virtual void UpdateVolumeBar();

	// Function name   : UpdateTemperature
	// Description     : Head���¶ȸ���
	// Return type     : static void 
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : ����������غ����Լ��Ĵ���
	virtual void UpdateTemperature();

protected:

	///////////////////////////////// �ؼ� /////////////////////////////////
	
	// ͷ���ؼ���Home��Vol��Model��Back��
	HCImageCtrl	*m_pHeadBkgnd;
	HCGroupCtrl	*m_pHeadGrpCtrl;
	HCButton			*m_pBtnHome;
	HCTextCtrl		*m_pTxtScreen;
	HCTextCtrl		*m_pTxtTemperature;
	HCImageCtrl		*m_pImgVolume;
	HCSlideCtrl		*m_pVolumeSlider;
	HCTextCtrl		*m_pVolSize;
	//HCImageCtrl		*m_pRadioIco;
	HCImageCtrl		*m_pPhoneIco;
	HCImageCtrl		*m_pSDIco;
	HCImageCtrl		*m_pUsbIco;
	HCImageCtrl		*m_pBTIco;
	HCTextCtrl			*m_pTxtTime[5];
	HCTextCtrl			*m_pTxtAPM[2];
	HCButton				*m_pBtnBack;
	// ��ʱ��ʧ POPUP
	CTimer				m_cTime;

	// ���ֿؼ�
	HCTextCtrl * m_pTxt_Popup_Cover;
	// ��Ϣ�ؼ� n
	HCTextCtrl * m_pTxt_Popup_Infor[3];

	// OK ��ť
	HCButton * m_pBtn_OK;
	// CANCEL ��ť
	HCButton * m_pBtn_CANCEL;

	// ����Group�ؼ�
	HCGroupCtrl * m_pGrp_Popup;

	// ��ʱ��ʧ POPUP
	CTimer m_ctAutoHidePopup;

	// �Ի��������ļ�·��
	const HCHAR * m_pszDlgPath;

	// POPUP����
	PopupType m_uPopupType;
    bool m_bMainPage;
	// ��ǰ����
	unsigned char m_uThemeMode;
};

#endif