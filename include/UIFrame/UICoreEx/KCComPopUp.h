/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCComPopUp.h 
* 摘    要:
*
* 当前版本: 1.0
* 作    者:               
* 完成日期: 2010-02-02
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1           2010-02-02                    			创建
*	2			2010-05-26		  			添加Retry Cancel类型
*
**/

#pragma once
#include "kcgroupctrl.h"
#include "hmienginecom.h"
#include <PubHead.h>
#include "kdialogbase.h"
#include "kcwindow.h"
#include "Configure.h"
#include "KHMIBaseHead.h"


enum PopUpType
{
	PU_NULL = 0,
	PU_OK ,
	PU_YESNO,
	PU_CONNECTDELTECANCEL,
	PU_CANCEL,
	PU_RETRYCANCEL,
	PU_MUINFO,
};

//***************************************************************
// *  功　　能:	 
// *  入口参数:	
// *  出口参数:	
// *  返 回 值:	 0 为NULL 1为OK 2 为YES 3为NO 4 为CONNTCT 5 为DELTE 6 为CANNEL
// *  作　　者:	              
// *  日　　期:	2010-03-17
//***************************************************************
CYPRESS_DLL_API int KCPopUp(HString strTitle, HString strInfo,HINT titleId, HINT strId,HINT type = PU_NULL ,HINT nTimer = 300);
CYPRESS_DLL_API void EndPopUp(void);

class CYPRESS_DLL_API HCComPopUp :
	public /*KCGroupCtrl*/HCWindow
{
private:
	HCComPopUp(void);
	~HCComPopUp(void);
public:
	static HCComPopUp *GetInstance(void);
	static void ExitInstance(void);
public:
// 	void Draw(IReSurface* pSurface);
// 
// 	kn_bool DoMessage(KMessage* msg);

public:
	// 根据传入参数创建不同类型POPUP
	void Create(HString strTitle,HString strInfo,HINT titleId, HINT strId,HUINT nType, HINT nTimer,HINT x = 89, HINT y = 100, HINT w = 724, HINT h = 339);
	HINT GetRetValue();

	void CloseDlg();

//	void SetPreCtrl(KCBaseCtrl *pPrectrl);

//	void ShowPopup(IReSurface* pFatherWndSurface);

// 	// 单击OK消息
// 	void SetCallBackOk(void (*callback)(void*, void*), void*);
// 	// Yes
// 	void SetCallBackYes(void (*callback)(void*, void*), void*);
// 	// No
// 	void SetCallBackNo(void (*callback)(void*, void*), void*);
// 	// Connect
// 	void SetCallBackConnect(void (*callback)(void*, void*), void*);
// 	// Delete
// 	void SetCallBackDelete(void (*callback)(void*, void*), void*);
// 	// Cancel
// 	void SetCallBackCancel(void (*callback)(void*, void*), void*);

//	void InvalidateCtrl(KCBaseCtrl* pBaseCtrl);

//	void InvalidateRect(kn_rect& rect);

//	void EnableUpdateRect(kn_bool bEnable);

//	kn_bool IsCtrlInGroup(KCBaseCtrl* pBaseCtrl);

// 	void SetTipTextPos(kn_int x,kn_int y,kn_int nWidth);
// 	void SetTipText(kn_string strTipTxt);
// 	void SetInfoTextPos(kn_int x,kn_int y,kn_int nWidth);
// 	void SetInfoText(kn_string strInfoTxt);


// 	static void OnBtnUp(void* p, void* pParam);
// 	void OnBtnUp(void* pParam);

private:
//	kn_bool IsCtrlInGroup(KCBaseCtrl* pBaseCtrl, vector<KCBaseCtrl*>& ctrlList);

private:
//	KCBaseCtrl*	m_pPreCtrl;	


	HString	m_strResPath;

	HINT m_nTimer;
//	IReSurface	*m_pSurface;

	// 按钮 OK
	HCButton	*m_pBtnOK;
	// 按钮： YES NO
	HCButton	*m_pBtnYes;
	HCButton    *m_pBtnNo;
	// 按钮 CONNECT DELETE CANCEL
	HCButton    *m_pBtnConnect;
	HCButton    *m_pBtnDelete;
	HCButton    *m_pBtnCancel;

	HCButton    *m_pBtnInfo;
	HCButton     *m_pBtnTopInfo;
	HCButton    *m_pBtnTitle;
	// ImageCtrl 
	HCImageCtrl* m_pImageCtrl[3];

	CTimer m_timer;
	static void OnTimerEnent(void* p, void*);
	static void OnBtnOkEnent(void* p, void*);
	
	static void OnBtnYesEnent(void* p, void*);

	static void OnBtnNoEnent(void* p, void*);

	static void OnBtnConnectEnent(void* p, void*);

	static void OnBtnDeleteEnent(void* p, void*);

	static void OnBtnCancelEnent(void* p, void*);
	

// 	// OK消息
// 	void (*m_pCallBackOk)(void *, void *);
// 	// Yes
// 	void (*m_pCallBackYes)(void *, void *);
// 	// No
// 	void (*m_pCallBackNo)(void *, void *);
// 	// Connect
// 	void (*m_pCallBackConnect)(void *, void *);
// 	// Delete
// 	void (*m_pCallBackDelete)(void *, void *);
// 	// Cancel
// 	void (*m_pCallBackCancel)(void *, void *);
// 
// 	kn_int m_nTipTextX,m_nTipTextY,m_nTipTextWidth;
// 	kn_int m_nInfoTextX,m_nInfoTextY,m_nInfoTextWidth;
	HString m_strInfoTxt;
	HString m_strTitle;
	HINT m_nRet;
	static HCComPopUp *m_pIns;
};
