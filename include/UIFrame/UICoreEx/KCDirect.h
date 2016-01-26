/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����:	KCDirect.h
* ժ    Ҫ:	DVD���ּ��̿ؼ�
*
* ��ǰ�汾:	1.0
* ��    ��:	  
* �������:	2010-05-25
*
* �޸���ʷ��
* [�޸�����]	[�޸�����] 		[�޸���]		[�޸�����]
*	1			2010-05-25    	      		����
* 	2			2010-11-8		              			������ü������ֵ�ӿ�
**/

#pragma once
#include "KHMIBaseHead.h"
#include "KCGroupCtrl.h"
#include "KCFont.h"
#include "KCScrollButtonText.h"
#include <vector>
using namespace std;

enum
{
	eType_Disc = 0,
	eType_USB,
	eType_Sirius,
};


#define MAX_KEY_NUMBER	(10)

class CYPRESS_DLL_API HCDirect : public HCGroupCtrl
{
public:
	HCDirect(HINT nType = eType_Disc);
	~HCDirect();

	HBOOL DoMessage(HMessage* msg);
	void Draw(IReSurface* pSurface);
	HBOOL Create(HINT x, HINT y,HINT w,HINT h, HINT nTotalCnt,HINT nMinCnt = 0);

	static void OnButtonNum(void* p, void* pParam);
	void OnButtonNum(void* pParam);
	static void OnBtnClear(void* p, void* pParam);
	void OnBtnClear(void* pParam);

	static void OnBtnOK(void* p, void* pParam);
	void OnBtnOK(void* pParam);

	static void OnBtnBack(void* p, void* pParam);
	void OnBtnBack(void* pParam);

	static void OnBtnOption(void* p, void* pParam);
	void OnBtnOption(void* pParam);
	HINT GetCurNumber();
	void SetText(HString strText);
	
	void Reset(HINT nTotalCnt);
	//OK�ص�
	void SetCallBackBtnOk(void (*callback)(void*, void*), void*);
	//���ذ�ť�ص�
	void SetCallBackBtnBack(void (*callback)(void*, void *), void *);
	//Option�ص�
	void SetCallBackBtnOption(void (*callback)(void *,void*),void *);
	// ���ó�������
	void SetSuperData(HINT nData);
	// ��ȡ��������
	HINT GetSuperData(void);

	// ���õ�ǰ���
	void SetCurValue(HINT nValue);
private:
	HINT GetTotalNumber(void);
	void SetBackGrndByType(void);
	void SetOptionBtnPicByType(void);

// �ؼ�
private:
	// ȷ�ϰ�ť
	HCButton* m_pBtnOK;
	HCButton* m_pBtnBack;
	// ���
	HCButton* m_pBtnClear;
	// ���ְ�ť
	HCButton* m_aOpd[MAX_KEY_NUMBER];

	HCButton*	m_pBtnOption;
	HCTextCtrl* m_pText;

	void (*m_pCallBackBtnOk)(void *, void *);
	void (*m_pCallBackBtnBack)(void *, void *);
	void (*m_pCallBackBtnOption) (void *,void *);
// ����
private:
	HINT	m_nSuperNum;
	HINT	m_nType;
	// ��������
	HINT m_nCurIndex;
	// ������ֵ
	HINT m_nTotalCnt;

	// ���е���С���
	HINT	m_nMinCnt;

	// ���������ַ���
	HString m_strCur;
	// �������ַ���
	HString m_strTotal;
};