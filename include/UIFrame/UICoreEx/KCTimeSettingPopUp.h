/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCDateItem.h 
* ժ    Ҫ:
*
* ��ǰ�汾: 1.0
* ��    ��:               
* �������: 2010-1-20
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1            2010-1-20                    			����
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
	//��Ϣ������
	HBOOL DoMessage(HMessage* msg);

public:
	// ��������
	HBOOL CreateDate(HINT nYearMidValue,HINT nMonthMidValue,HINT nDayMidValue,HINT x = 89, HINT y = 73, HINT w = 621, HINT h = 354);
	// ����ʱ��
	HBOOL CreateTime(HINT nHourMidValue,HINT nMinuteMidValue,HINT x = 89, HINT y = 73, HINT w = 621, HINT h = 354);

	void SetTunePopupTitle(HString strTitle);
	void SetTunePopupTitle(const HCHAR* pStrTitle);
	void SetPreCtrl(HCBaseCtrl *pPrectrl);

	void ShowPopup(IReSurface* pFatherWndSurface);

	//����ƶ���Ϣ
	void SetCallBackMouseMove(void (*callback)(void*, void*), void*);
	//����ƶ���Ϣ
	void SetCallBackOnOK(void (*callback)(void*, void*), void*);
	//����ƶ���Ϣ
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
	// ����
	HCTextCtrl	*m_pTitleTxt;

	
	IReSurface	*m_pSurface;
	//��ť 0:ȷ�� 1:ȡ��
	HCButton	*m_pBtnOK;
	HCButton	*m_pBtnCancel;

	// ��������
	//0 left  2 right
	HCRollerCtrl*  m_pScrollItem[4];

	// ImageCtrl 
	HCImageCtrl* m_pImageCtrl[4];


	// ����ƶ���Ӧ��Ϣ
	void (*m_pCallBackMouseMove)(void *, void *);
	// ȷ����ťup��Ӧ��Ϣ
	void (*m_pCallBackOnOK)(void *, void *);
	// ȡ����ťup��Ӧ��Ϣ
	void (*m_pCallBackOnCancel)(void *, void *);

};
