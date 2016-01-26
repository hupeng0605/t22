#pragma once
#include "KCWindow.h"
#include "KCButton.h"
#include "KCTextCtrl.h"
#include "KHMIBaseHead.h"

enum
{
	KCMSG,
	KCMB_YESNO, 
	KCMB_YESNOCANCEL,
	KCMB_CANNEL
};
enum eRET
{
	KCNULL = 0,
	KCYES,
	KCNO,
	KCCANCEL
};
//***************************************************************
// *  功　　能:	1为YES 2 为NO 3 为CANNEL
// *  入口参数:	
// *  出口参数:	
// *  返 回 值:	
// *  作　　者:	              
// *  日　　期:	2010-03-17
//***************************************************************
CYPRESS_DLL_API int KCMessageBox(HString strTitle, HString strInfo, HINT type = KCMSG);

class CYPRESS_DLL_API CMessageBox :public HCWindow
{
public:
	CMessageBox(void);
	~CMessageBox(void);
	void Create(HWORD nType,HString strTitle,HString strInfo, HINT width = 621,HINT height = 262);
	static void OnBtYES(void* p, void*);
	void OnBtYES();

	static void OnBtnNO(void* p, void*);
	
	static void OnBtnCannel(void* p, void*);
	
	static void OnTimer(void* p, void*);
	HINT GetReturnValue();

private:
	HCButton *m_pBtnYes;
	HCButton *m_pBtnNo;
	HCButton *m_pBtnCannel;
	HCButton *m_pBtnTitle;
	HCButton *m_pBtnMat;
	CTimer m_timer;
	eRET m_eRet;
};
