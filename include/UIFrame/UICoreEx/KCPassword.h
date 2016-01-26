/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称:	KCPassword.h
* 摘    要:	密码输入控件
*
* 当前版本:	1.0
* 作    者:	  
* 完成日期:	2010-05-25
*
* 修改历史：
* [修改序列]	[修改日期] 		[修改者]		[修改内容]
*	1			2010-05-25    	      		创建
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
	//获取当前输入的密码
	HString GetCurInputStr();

	//OK回调
	void SetCallBackBtnOk(void (*callback)(void*, void*), void*);
	//返回按钮回调
	void SetCallBackBtnBack(void (*callback)(void*, void *), void *);
	//Option回调
	void SetCallBackBtnOption(void (*callback)(void *,void*),void *);


	void SetInvalidText(HString str);

private:
	
	void SetBackGrndByType(void);
	void SetOptionBtnPicByType(void);

// 控件
private:
	// 确认按钮
	HCButton* m_pBtnOK;
	HCButton* m_pBtnBack;
	// 清除
	HCButton* m_pBtnClear;
	// 数字按钮
	HCButton* m_aOpd[MAX_KEY_NUMBER];

	HCButton* m_pBtnOption;

	void (*m_pCallBackBtnOk)(void *, void *);
	void (*m_pCallBackBtnBack)(void *, void *);
	void (*m_pCallBackBtnOption) (void *,void *);
	HString DrawCurDisplayString( HINT index);
	// 属性
private:
	HINT	m_nType;
	// 输入的序号
	HINT m_nCurIndex;
	// 序号最大值
	//kn_int m_nTotalCnt;

	// 输入的序号字符串
	//kn_string m_strCur;
	// 最大序号字符串
	//kn_string m_strTotal;
	HCHAR m_szBuffer[MAX_INPUT_LENGTH+1];

	HBOOL	m_bShowInvalidText;

	HString m_strInvalidText;
};