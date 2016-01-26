/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCComPopUp.h 
* ժ    Ҫ:
*
* ��ǰ�汾: 1.0
* ��    ��:               
* �������: 2010-02-02
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1           2010-02-02                    			����
*	2			2010-05-26		  			���Retry Cancel����
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
// *  ��������:	 
// *  ��ڲ���:	
// *  ���ڲ���:	
// *  �� �� ֵ:	 0 ΪNULL 1ΪOK 2 ΪYES 3ΪNO 4 ΪCONNTCT 5 ΪDELTE 6 ΪCANNEL
// *  ��������:	              
// *  �ա�����:	2010-03-17
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
	// ���ݴ������������ͬ����POPUP
	void Create(HString strTitle,HString strInfo,HINT titleId, HINT strId,HUINT nType, HINT nTimer,HINT x = 89, HINT y = 100, HINT w = 724, HINT h = 339);
	HINT GetRetValue();

	void CloseDlg();

//	void SetPreCtrl(KCBaseCtrl *pPrectrl);

//	void ShowPopup(IReSurface* pFatherWndSurface);

// 	// ����OK��Ϣ
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

	// ��ť OK
	HCButton	*m_pBtnOK;
	// ��ť�� YES NO
	HCButton	*m_pBtnYes;
	HCButton    *m_pBtnNo;
	// ��ť CONNECT DELETE CANCEL
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
	

// 	// OK��Ϣ
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
