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
// *  ��������:	1ΪYES 2 ΪNO 3 ΪCANNEL
// *  ��ڲ���:	
// *  ���ڲ���:	
// *  �� �� ֵ:	
// *  ��������:	              
// *  �ա�����:	2010-03-17
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
