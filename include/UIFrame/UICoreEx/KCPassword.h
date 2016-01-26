/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����:	KCPassword.h
* ժ    Ҫ:	��������ؼ�
*
* ��ǰ�汾:	1.0
* ��    ��:	  
* �������:	2010-05-25
*
* �޸���ʷ��
* [�޸�����]	[�޸�����] 		[�޸���]		[�޸�����]
*	1			2010-05-25    	      		����
* 	
**/

#pragma once
#include "KHMIBaseHead.h"
#include "KCGroupCtrl.h"
#include "KCFont.h"
#include <vector>
using namespace std;

enum
{
	ePassword_Sirius = 0,
	ePassword_USB,
	ePassword_Number,
};

#define MAX_INPUT_LENGTH	(4)
#define MAX_KEY_NUMBER		(10)

class CYPRESS_DLL_API HCPassword : public HCGroupCtrl
{
public:
	HCPassword(HINT nType = ePassword_Sirius);
	~HCPassword();

	void Draw(IReSurface* pSurface);
	HBOOL Create(HINT x, HINT y,HINT w,HINT h);

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
	
	void Reset(void);

	void SetInvalidText(void);
	//��ȡ��ǰ���������
	HString GetCurInputStr();

	//OK�ص�
	void SetCallBackBtnOk(void (*callback)(void*, void*), void*);
	//���ذ�ť�ص�
	void SetCallBackBtnBack(void (*callback)(void*, void *), void *);
	//Option�ص�
	void SetCallBackBtnOption(void (*callback)(void *,void*),void *);


	void SetInvalidText(HString str);

private:
	
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

	HCButton* m_pBtnOption;

	void (*m_pCallBackBtnOk)(void *, void *);
	void (*m_pCallBackBtnBack)(void *, void *);
	void (*m_pCallBackBtnOption) (void *,void *);
	HString DrawCurDisplayString( HINT index);
	// ����
private:
	HINT	m_nType;
	// ��������
	HINT m_nCurIndex;
	// ������ֵ
	//kn_int m_nTotalCnt;

	// ���������ַ���
	//kn_string m_strCur;
	// �������ַ���
	//kn_string m_strTotal;
	HCHAR m_szBuffer[MAX_INPUT_LENGTH+1];

	HBOOL	m_bShowInvalidText;

	HString m_strInvalidText;
};