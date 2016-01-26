/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCHeadDialog.h
* 摘    要: Clarion BaseDialog
*
* 当前版本: 1.0
* 作    者:               
* 完成日期: 2010-02-03
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1           2010-02-03                              创建
*	2			2010-4-26		  			优化基类代码
*	3			2010-5-26		  			添加导航转向按钮
*
**/
#pragma once
#include "hmienginecom.h"
#include <PubHead.h>
#include "kdialogbase.h"
#include "kcwindow.h"
#include "KCGroupCtrl.h"
#include "KCScrollButtonText.h"
#include "KCClockCtrl.h"

#pragma warning(disable: 4512)

// 暂定为1，后续需要添加INFO ICON只需修改此宏
#ifdef MAX_INFO_ICON_NUM
#undef MAX_INFO_ICON_NUM
#endif
#define MAX_INFO_ICON_NUM (2)

class CYPRESS_DLL_API HCHeadDialog :
    public HDialogBase
{
public:
    HCHeadDialog(void);
    virtual ~HCHeadDialog(void);
    //
public:


	void EnableSetTitleByString(HBOOL bIn);
	void ResetTitle();
	HBOOL IsTitleEmpty();
	//判断有没有重设TITLE
	HBOOL IsResetTitle();
	//还原TITLE
	void RevertTitle();
    // 设置当前窗口名
	void SetHeadIocnHide(HBOOL bShowFlag);
    void SetTitleName(const HString& strTitleName,HBOOL bEnableMoveInOut = TRUE);
	void SetTitleID(HINT nID);
	void SetTime(const HString& strTime,HBOOL bEnableMoveInOut = TRUE);
	void SetTitleNameColor(int r, int g , int b);
    // 设置标题栏的字符
    void SetTitleByString(const HCHAR* a_pstrTitle,HBOOL bEnableMoveInOut = TRUE);
	void SetTimeByString(const HCHAR* a_pstrTime,HBOOL bEnableMoveInOut = TRUE);
    void SetTitleByLangID(HINT a_nLangID,HBOOL bEnableMoveInOut = TRUE);
	void SetTimeByLangID(HINT a_nLangID,HBOOL bEnableMoveInOut = TRUE);
	HString GetTitleName();
	
	void SetShowAMPMEvent();

    // 设置时间格式
	void SetTimeFormat(HBOOL bFormat);
	void SetHeadBkPos(HINT x,HINT y);

	// Disc信息发生变化事件
	virtual void OnDiscUpdateEvent(HINT /*cmdID*/, LPARAM /*lParam*/){}
    //  // 信息icon区
    //  kn_int SetInfoIconVisibility(kn_int a_nIndex,kn_bool a_bShow = true);
    //  kn_int SetAllInfoIconVisibility(kn_bool a_bShow = true);
    //  kn_int SetInfoIconActivity(kn_int a_nIndex,kn_bool a_bActive = true);
    //  kn_int SetAllInfoIconActivity(kn_bool a_bActive = true);


    void StartExe(HString strExeName, HString strParam = _T(""));
    void StartExe(HINT nExeType, HCHAR* pstrParam = NULL);
    void StartExe(HINT nExeType, HINT nParam = 0);

	// 设置HEAD背景
	void SetHeadBK(const HString& pFileName);
	void SetHeadBK(IReSurface* pSurf);
	HBOOL GetTimeFormat();
    HCBaseCtrl* GetHeadCtrl();
	HCImageCtrl* GetHeadImageCtrl();
	HBOOL SaveSurfaceToMemery(IN const HString& strSourceName,
		IN HINT nWidth = 240,IN HINT nHeight = 144);
	void SetMemeryString(const HString& strMemString);

// 	void VideoBitmapToSurface(HBITMAP& bitmap, IReSurface*& pSurf);
// 	void ReadVideoBmp(IN const kn_string& strSourceName);

	void  SetThumbNailBySendMsg(IN const HString& strSourceName);

	void Draw(IReSurface* pSurface);
	// 设置Radio的状态
	void SetRadioIconState(HINT index,HBOOL nState);
	// 设置蓝牙状态
	void SetBTIconStatus(HINT nStatus);
	// 设置mute状态
	void SetMuteIconStatus(HBOOL bStatus);

	// 视频窗口是否存在接口
	void SetVideoWndShow(HBOOL bShow = false);
	HBOOL	GetVideoWndShow(void);

	// 显示隐藏导航按钮
	void SetNaviBtnShow(HBOOL bShow = false);

	void SetFrontOrRearBtn(HBOOL bFront,HBOOL bShow = false);

	static void OnBtnNavi(void* p, void* pParam);
	void OnBtnNavi(void* pParam);
#ifdef EU_VERSION
#ifndef JP_VERSION
	static void OnBtnTACancel(void* p, void* pParam);
	void OnBtnTACancel(void* pParam);
	static void OnTACancelTimer(void *p, void *);
	void OnTACancelTimer();
#endif
#endif
	static void OnBtnFrontOrRear(void* p, void* pParam);
	void OnBtnFrontOrRear(void* pParam);

	void SetTouchCalibrateStatus(HBOOL bShow = false);
	HBOOL	GetTouchCalibrateStatus(void);
	void SetTitleNamePos(HINT x,HINT y);
	void DisableHeaderBtn(HBOOL bByPKBSts = true);
	void EnableHeaderBtn(void);
protected:
    HINT OnInit();
    HBOOL DoMessage(HMessage* msg);

	void StartMoving(void)
	{
		m_bMovingFlag = true;
	}
	
	
    
protected:
    void SetSystemTime(void);
    
private:
    // 改变语言
    //void ChangeLanguage(void);

    void ChangeLanguage(HCBaseCtrl* pCtrl);

    // 改变时间
    void ChangeTime(void);
    // 改变时间格式
    void ChangeTimeFormat(HBOOL bTimeFormat);

    static void OnTimer(void *p, void *);
    void OnTimer();
    void InvalidateCtrl(HCBaseCtrl *pBaseCtrl);
#ifdef EU_VERSION
#ifndef JP_VERSION
	static void OnAFTimer(void *p, void *);
	virtual void OnAFTimer();
#endif
#endif
private:
    //  static KCImageCtrl * m_pImgInfoIcon[MAX_INFO_ICON_NUM]; // 图标区
    //  static kn_bool      m_bStatus[MAX_INFO_ICON_NUM+1];         // 图标区的状态，最后一个是返回按钮的状态

    // 时间定时器
    CTimer      m_Time;
    // 中断Surface(用于乱序的HMI界面显示)

    // 中断界面显示的位置
    POINT m_nBreakLocal;

    HCGroupCtrl* m_pHeadCtrl;

    // HEAD背景
    HCImageCtrl* m_pHeadBk;
    // 当前窗口名
	HCScrollButtonText* m_pScrollTitleName;
	// 视频当前播放时间
	HCScrollButtonText* m_pScrollTime;
    // 资源路径
    HString   m_strResPath;

    // 当前时间
    //static KCTextCtrl* m_pCurTime;
	static HCClockCtrl* m_pCurTime;

    // AM\PM
    //static KCTextCtrl* m_pAmPmTxt[2];
	//static KCImageCtrl* m_pAmPmImg[2];
	const RECOLOR m_clrAM;	// 定义am和pm的颜色
	const RECOLOR m_clrPM;

    // 信号区
    static HCImageCtrl* m_pImgInfoIcon[2];
    // 时间格式 24小时制/12小时制
    static HBOOL      m_bTimeFormat;
#ifdef EU_VERSION
#ifndef JP_VERSION
	// Radio Info
	static HCTextCtrl* m_pRadioInfoText[5];
#endif
#endif // EU_VERSION
	HString m_strMemString;
	IReSurface* m_pSourceTheme;		// 缩略图surface，必须在draw的时候就保存

	// 导航转向按钮
	static HCButton*	m_pBtnNavi;
#ifdef EU_VERSION
#ifndef JP_VERSION
	static HCButton*	m_pTACancelBtn;
	CTimer				m_TACancelTimer;
#endif
#endif
	// 是否存在视频窗口
	static HBOOL	m_bIsVideoWndShow;
	static HBOOL  m_bIsTouchCalibrate;

	HBOOL			m_bMovingFlag;	// 是否在做for循环动画
	static HCButton* m_pBtnRearOrFront;
	HBOOL         m_bEnableShow;
	HBOOL         m_bTextReset;


	HBOOL         m_bEnableSetTitle;

#ifdef EU_VERSION
#ifndef JP_VERSION
		CTimer			m_AFTime;
#endif
#endif
};
