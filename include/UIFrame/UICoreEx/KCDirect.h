/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称:	KCDirect.h
* 摘    要:	DVD数字键盘控件
*
* 当前版本:	1.0
* 作    者:	  
* 完成日期:	2010-05-25
*
* 修改历史：
* [修改序列]	[修改日期] 		[修改者]		[修改内容]
*	1			2010-05-25    	      		创建
* 	2			2010-11-8		              			添加设置键盘序号值接口
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
	//OK回调
	void SetCallBackBtnOk(void (*callback)(void*, void*), void*);
	//返回按钮回调
	void SetCallBackBtnBack(void (*callback)(void*, void *), void *);
	//Option回调
	void SetCallBackBtnOption(void (*callback)(void *,void*),void *);
	// 设置超级数据
	void SetSuperData(HINT nData);
	// 获取超级数据
	HINT GetSuperData(void);

	// 设置当前序号
	void SetCurValue(HINT nValue);
private:
	HINT GetTotalNumber(void);
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

	HCButton*	m_pBtnOption;
	HCTextCtrl* m_pText;

	void (*m_pCallBackBtnOk)(void *, void *);
	void (*m_pCallBackBtnBack)(void *, void *);
	void (*m_pCallBackBtnOption) (void *,void *);
// 属性
private:
	HINT	m_nSuperNum;
	HINT	m_nType;
	// 输入的序号
	HINT m_nCurIndex;
	// 序号最大值
	HINT m_nTotalCnt;

	// 运行的最小序号
	HINT	m_nMinCnt;

	// 输入的序号字符串
	HString m_strCur;
	// 最大序号字符串
	HString m_strTotal;
};