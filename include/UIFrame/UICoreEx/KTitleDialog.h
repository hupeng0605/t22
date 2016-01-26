#if 0

/************************************************************************/
/* 歌乐项目部需要                                                       */
/************************************************************************/

#pragma once
#include "hmienginecom.h"
#include <PubHead.h>
#include "kdialogbase.h"
#include "kcwindow.h"
#include <KMemMapAPI.h>

#ifdef MAX_INFO_ICON_NUM
#undef MAX_INFO_ICON_NUM
#endif
#define		MAX_INFO_ICON_NUM	(3)

class CYPRESS_DLL_API KTitleDialog :
	public HDialogBase
{
public:
	KTitleDialog(void);
	virtual ~KTitleDialog(void);
	KTitleDialog(const SYS_SETTING& sysSet);

public:
	// 设置属性
	void SetSysSetting(const SYS_SETTING& sysSet);
	// 设置标题栏的字符
	void SetTitleByString(const HCHAR* a_pstrTitle);
	void SetTitleByLangID(HINT a_nLangID);
	// 设置标题栏的icon
	void SetTitleIcon(const HString a_strPath);
	// 设置返回的Icon可见或不可见
	void SetReturnIconVisibility(HBOOL a_bShow = true);
	
	void SetTimeZoneTransTo(HBOOL a_bTrans);
	HBOOL GetTimeZoneTransTo(void){return m_bToScreenOff;};

	// 信息icon区
	HINT SetInfoIconVisibility(HINT a_nIndex,HBOOL a_bShow = true);
	HINT SetAllInfoIconVisibility(HBOOL a_bShow = true);
	HINT SetInfoIconActivity(HINT a_nIndex,HBOOL a_bActive = true);
	HINT SetAllInfoIconActivity(HBOOL a_bActive = true);
	// 隐藏标题栏
	void SetTitleBarVisibility(HBOOL a_bShow = true);
	// 隐藏时间
	void SetTimeVisibility(HBOOL a_bShow = true);
	// 隐藏状态
	void SetStatusVisibility(HBOOL a_bShow = true);
	virtual void OnTitleBtnUp(void* pParam);
	virtual void OnTitleBtn(void* pParam);
	//void StartExe(kn_string strExeName,kn_string strParam = _T(""));
	//void StartExe(kn_int nExeType,kn_char* pstrParam = NULL);
	void StartExe(HINT nExeType,HINT nParam = 0);

	virtual void OnChildTimer(void* pParam);
public:
	virtual HINT OnInit();
	
	HBOOL DoMessage(HMessage* msg);
	// 
	virtual void Draw(IReSurface* pSurface);
	virtual void Draw(IReSurface* pSurface,IReSurface* pSurfaceMap,_kn_rect m_rectMap);
protected:
	void SetSystemTime(void);
	void StartEQ(void);
	void SetMemBkgdNULL();
private:
	// 改变语言
	void ChangeLanguage(void);

	void ChangeLanguage(HCBaseCtrl* pCtrl);
	void ChangeLanguage(HCGroupCtrl* pGroupCtrl);
	// 改变背景
	void ChangeBackground(void);
	// 改变时间
	void ChangeTime(void);
	// 改变时间格式
	void ChangeTimeFormat(HBOOL bTimeFormat);
	// 改变时钟类型
	void ChangeClockType(HBOOL bClockType);
	// 改变日期
	void ChangeDate(void);
	// 显示音量界面
	void ShowVol();
	
	static void OnTimer(void *p,void *pParam);
	void OnTimer(void* pParam);
	static void OnVolTimer(void *p,void *pParam);
	void OnVolTimer(void* pParam);

	static void OnTimeBtnUp(void* p, void* pParam);
	void OnTimeBtnUpToTimeSetup(void* pParam);
	void OnTimeBtnUpToScreenOff(void* pParam);

	//void SetSystemTime(void);
	void InvalidateCtrl(HCBaseCtrl *pBaseCtrl);

	static void OnTitleBtnDown(void* p, void* pParam);
	void OnTitleBtnDown(void* pParam);
	//static void OnTitleBtnUp(void* p, void* pParam);
	static void OnTitleBtn(void* p, void* pParam);
	void OnTitleBtnBase(void* pParam);

private:
	static HString	m_strResPath;						// 资源路径
	static HCImageCtrl	* m_pImgBK;							// 标题栏背景
	static HCImageCtrl * m_pImgTitleIcon;					// 标题栏Icon
	HCButton	* m_pBtnTitle;								// 标题栏title
	static HCButton	* m_pBtnTime;							// 时间区
	static HCImageCtrl * m_pImgInfoIcon[MAX_INFO_ICON_NUM];	// 图标区
	HBOOL		m_bToScreenOff;
	static HBOOL		m_bStatus[MAX_INFO_ICON_NUM+1];			// 图标区的状态，最后一个是返回按钮的状态

	//static kn_bool		m_bTimeFormat;							// 时间格式 24小时制/12小时制
	//static kn_bool		m_bClockType;						// 时钟类型，数字时钟/模拟时钟
	CTimer		m_Time;									// 时间定时器
	CTimer		m_VolTime;									// 音量调节定时器
	static IReSurface* s_pMemBkgd;// 共享内存背景
	IReSurface* m_pBreakSurface;// 中断Surface(用于乱序的HMI界面显示)
	POINT m_nBreakLocal;// 中断界面显示的位置
protected:
	static SYS_SETTING			m_sysSetting;					// 共享内存中的数据
};
#endif