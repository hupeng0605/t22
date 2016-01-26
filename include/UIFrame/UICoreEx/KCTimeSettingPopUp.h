/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCDateItem.h 
* 摘    要:
*
* 当前版本: 1.0
* 作    者:               
* 完成日期: 2010-1-20
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1            2010-1-20                    			创建
*
**/

#pragma once
#include "kcgroupctrl.h"
#include "hmienginecom.h"
#include <PubHead.h>
#include "kdialogbase.h"
#include "kcwindow.h"
#include "Configure.h"

#include "KCRollerCtrl.h"

class CYPRESS_DLL_API HCTimeSettingPopUp :
	public HCGroupCtrl
{
public:
	HCTimeSettingPopUp(void);
	~HCTimeSettingPopUp(void);
public:
	void Draw(IReSurface* pSurface);
	//消息处理函数
	HBOOL DoMessage(HMessage* msg);

public:
	// 设置日期
	HBOOL CreateDate(HINT nYearMidValue,HINT nMonthMidValue,HINT nDayMidValue,HINT x = 89, HINT y = 73, HINT w = 621, HINT h = 354);
	// 设置时间
	HBOOL CreateTime(HINT nHourMidValue,HINT nMinuteMidValue,HINT x = 89, HINT y = 73, HINT w = 621, HINT h = 354);

	void SetTunePopupTitle(HString strTitle);
	void SetTunePopupTitle(const HCHAR* pStrTitle);
	void SetPreCtrl(HCBaseCtrl *pPrectrl);

	void ShowPopup(IReSurface* pFatherWndSurface);

	//鼠标移动消息
	void SetCallBackMouseMove(void (*callback)(void*, void*), void*);
	//鼠标移动消息
	void SetCallBackOnOK(void (*callback)(void*, void*), void*);
	//鼠标移动消息
	void SetCallBackOnCancel(void (*callback)(void*, void*), void*);

	void InvalidateCtrl(HCBaseCtrl* pBaseCtrl);

	void InvalidateRect(kn_rect& rect);

	void EnableUpdateRect(HBOOL bEnable);

	HBOOL IsCtrlInGroup(HCBaseCtrl* pBaseCtrl);

	void GetCurValue(HINT &nHour,HINT &nMinute);


private:
	HBOOL IsCtrlInGroup(HCBaseCtrl* pBaseCtrl, vector<HCBaseCtrl*>& ctrlList);

	static void OnBtnOK(void* p, void* pParam);
	void OnBtnOK(void);

	static void OnBtnCancel(void* p, void* pParam);
	void OnBtnCancel(void);

private:
	HCBaseCtrl*	m_pPreCtrl;	


	HString	m_strResPath;
	// 标题
	HCTextCtrl	*m_pTitleTxt;

	
	IReSurface	*m_pSurface;
	//按钮 0:确定 1:取消
	HCButton	*m_pBtnOK;
	HCButton	*m_pBtnCancel;

	// 两个滑轮
	//0 left  2 right
	HCRollerCtrl*  m_pScrollItem[4];

	// ImageCtrl 
	HCImageCtrl* m_pImageCtrl[4];


	// 鼠标移动响应消息
	void (*m_pCallBackMouseMove)(void *, void *);
	// 确定按钮up响应消息
	void (*m_pCallBackOnOK)(void *, void *);
	// 取消按钮up响应消息
	void (*m_pCallBackOnCancel)(void *, void *);

};
