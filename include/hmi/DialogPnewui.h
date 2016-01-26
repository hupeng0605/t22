

#ifndef __DIALOGP_DLG__
#define __DIALOGP_DLG__

/*************************************** 全局控制 ***************************************/

// Function name   : UnInitPopupSurface
// Description     : 释放POPUP 图片资源
// Return type     : void 
// Argument        : void
// Remark          : 

void UnInitPopupSurface(void);

// Function name   : InitPopupSurface
// Description     : 初始化 POPUP 中的图片资源
// Return type     : static void 
// Argument        : TCHAR * pszDirPath
// Remark          : 在 WinMain 函数中只初始化一次 或当主题发送改变时 在 WindowProc 消息函数中收到了 VWM_SETUP_CHANGE_THEME 消息调用一次

void InitPopupSurface(const TCHAR * pszDirPath);


// Function name   : SetCurThemeMode
// Description     : 设置当前主题
// Return type     : void 
// Argument        : unsigned char uThemeMode
// Remark          : 

void SetCurThemeMode(unsigned char uThemeMode);

// Function name   : GetCurThemeMode
// Description     : 得到当前主题
// Return type     : unsigned char 
// Argument        : void
// Remark          : 

unsigned char GetCurThemeMode(void);

// Function name   : IsCanDoHardKey
// Description     : 能否执行硬按钮操作
// Return type     : bool ( true : 能执行硬按钮操作 false : 不能执行硬按钮操作 )
// Argument        : void
// Remark          : 

bool IsCanDoHardKey(void);

/*************************************** 类定义 ***************************************/

// KDialogP

class KDialogP : public HDialogBase
{
public:
	// POPUP 类型定义
	typedef enum PopupType
	{
		PT_NOR = 0x00,		// 标准类型
		PT_OK,				// OK 按钮类型
		PT_OKCANCEL			// OK CANCEL类型
	};
public:

	// 构造函数
	KDialogP(void);

	// 析构函数
	virtual ~KDialogP(void);

	// Function name   : SetPopupInfor
	// Description     : 设置POPUP中显示的信息
	// Return type     : virtual void 
	// Argument        : TCHAR * pszInfor	信息字符串 支持多行 但目前最多3行文字信息
	// 
	// Remark          : 自动调节 3行信息的位置信息

	virtual void SetPopupInfor(TCHAR * pszInfor);

	// Function name   : ShowPopup
	// Description     : 显示 POPUP
	// Return type     : void 
	// Argument        : PopupType type = PT_NOR		( POPUP 类型 默认为标准类型 )
	// Argument        : HUSHORT uAutoHideTimer = 0	( 0 : 不进行自动隐藏 , > 0 : 10ms毫秒级定时隐藏 )
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	void ShowPopup(PopupType type = PT_NOR,HUSHORT uAutoHideTimer = 0);

	// Function name   : HidePopup
	// Description     : 隐藏POPUP
	// Return type     : void 
	// Argument        : void
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	void HidePopup(void);


	// Function name   : ChangeTheme
	// Description     : 切换主题
	// Return type     : virtual void 
	// Argument        : HBYTE uType
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 当切换主题时会调用该函数 请重载该函数

	virtual void ChangeTheme(HBYTE uType);

	// Function name   : DoMessage
	// Description     : 消息处理函数
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
	// Description     : POPUP自动消失的时候通知
	// Return type     : void 
	// Argument        : void
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 
	virtual void OnPopupAutoHide();
protected:

	// Function name   : InitPopupCtrl
	// Description     : 初始化 POPUP 控件
	// Return type     : void 
	// Argument        : void
	// 
	// Writer          :     
	// Date            : 
	// Remark          : 

	virtual void InitPopupCtrl(void);

	// Function name   : InitHeadCtrl
	// Description     : 初始化 POPUP 控件
	// Return type     : void 
	// Argument        : void
	// 
	// Writer          :     
	// Date            : 
	// Remark          : 

	virtual void InitHeadCtrl(void);

	// Function name   : ChangePopupStyle
	// Description     : 根据模式的不同改变POPUP的STYLE
	// Return type     : void 
	// Argument        : void
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	virtual void ChangePopupStyle(void);

	// Function name   : ChangeHeadCtrlStyle
	// Description     : 根据模式的不同改变HeadCtrl的STYLE
	// Return type     : void 
	// Argument        : void
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	virtual void ChangeHeadCtrlStyle(void);

	// Function name   : LoadPopupSkin
	// Description     : 前台加载POPUP皮肤
	// Return type     : void 
	// Argument        : void
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 
	virtual void LoadPopupSkin(void);

	// Function name   : ReleasePopupSkin
	// Description     : 后台释放POPUP皮肤所占内存
	// Return type     : void 
	// Argument        : void
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 
	virtual void ReleasePopupSkin(void);

	// Function name   : OnAutoHidePopup
	// Description     : 自动隐藏POPUP回调函数
	// Return type     : static void 
	// Argument        : void * pThis
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	static void OnAutoHidePopup(void * pThis,void * pParam);

	// Function name   : OnAutoHidePopup
	// Description     : 自动隐藏POPUP功能函数
	// Return type     : void 
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	void OnAutoHidePopup(void * pParam);

	// Function name   : OnAutoUpdateTime
	// Description     : 自动更新时间回调函数
	// Return type     : static void 
	// Argument        : void * pThis
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	static void OnAutoUpdateTime(void * pThis,void * pParam);

	// Function name   : OnAutoUpdateTime
	// Description     : 自动更新时间回调函数
	// Return type     : void 
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	void OnAutoUpdateTime(void * pParam);

	// Function name   : OnPopupOk
	// Description     : POPUP上OK按钮回调函数
	// Return type     : static void 
	// Argument        : void * pThis
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	static void OnPopupOk(void * pThis,void * pParam);

	// Function name   : OnPopupOk
	// Description     : POPUP上OK按钮功能函数
	// Return type     : virtual void 
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 派生类重载后 做自己的处理

	virtual void OnPopupOk(void * pParam);

	// Function name   : OnPopupCancel
	// Description     : POPUP上CANCEL按钮回调函数
	// Return type     : static void 
	// Argument        : void * pThis
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 

	static void OnPopupCancel(void * pThis,void * pParam);

	// Function name   : OnPopupCancel
	// Description     : POPUP上CANCEL按钮功能函数
	// Return type     : static void 
	// Argument        : void * pThis
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 派生类重载后 做自己的处理

	virtual void OnPopupCancel(void * pParam);

	// Function name   : OnBtnHome
	// Description     : Head上home按钮回调函数
	// Return type     : static void 
	// Argument        : void * pThis
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 
	static void OnBtnHome(void* pThis, void* pParam); 

	// Function name   : OnBtnHome
	// Description     : Head上home按钮回调函数
	// Return type     : static void 
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 派生类重载后 做自己的处理
	virtual void OnBtnHome(void* pParam); 

	// Function name   : OnBtnBackPrevious
	// Description     : Head上back按钮回调函数
	// Return type     : static void 
	// Argument        : void * pThis
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 
	static void OnBtnBackPrevious(void* pThis, void* pParam);

	// Function name   : OnBtnBackPrevious
	// Description     : Head上back按钮回调函数
	// Return type     : static void 
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 派生类重载后 做自己的处理
	virtual void OnBtnBackPrevious(void* pParam); 

	// Function name   : UpdateHeadDevIcon
	// Description     : Head上设备状态ICON更新
	// Return type     : static void 
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 派生类可重载后做自己的处理
	virtual void UpdateHeadDevIcon();

	// Function name   : UpdateHeadDevIcon
	// Description     : Head上设备状态ICON更新
	// Return type     : static void 
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 派生类可重载后做自己的处理
	virtual void UpdateVolumeBar();

	// Function name   : UpdateTemperature
	// Description     : Head上温度更新
	// Return type     : static void 
	// Argument        : void * pParam
	// 
	// Writer          :     
	// Date            :     
	// Remark          : 派生类可重载后做自己的处理
	virtual void UpdateTemperature();

protected:

	///////////////////////////////// 控件 /////////////////////////////////
	
	// 头部控件（Home、Vol、Model、Back）
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
	// 定时消失 POPUP
	CTimer				m_cTime;

	// 遮罩控件
	HCTextCtrl * m_pTxt_Popup_Cover;
	// 信息控件 n
	HCTextCtrl * m_pTxt_Popup_Infor[3];

	// OK 按钮
	HCButton * m_pBtn_OK;
	// CANCEL 按钮
	HCButton * m_pBtn_CANCEL;

	// 遮罩Group控件
	HCGroupCtrl * m_pGrp_Popup;

	// 定时消失 POPUP
	CTimer m_ctAutoHidePopup;

	// 对话框配置文件路径
	const HCHAR * m_pszDlgPath;

	// POPUP类型
	PopupType m_uPopupType;
    bool m_bMainPage;
	// 当前主题
	unsigned char m_uThemeMode;
};

#endif