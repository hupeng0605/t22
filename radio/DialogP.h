

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
	// Date            : 2011-11-25
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
	// Date            : 2011-11-25
	// Remark          : 

	virtual void InitPopupCtrl(void);

	// Function name   : ChangePopupStyle
	// Description     : ����ģʽ�Ĳ�ͬ�ı�POPUP��STYLE
	// Return type     : void 
	// Argument        : void
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	virtual void ChangePopupStyle(void);

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

protected:

	///////////////////////////////// �ؼ� /////////////////////////////////

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

	// ��ǰ����
	unsigned char m_uThemeMode;
};

#endif