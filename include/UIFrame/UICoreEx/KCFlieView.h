/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCFileView.h 
* 摘    要:
*
* 当前版本: 1.0
* 作    者:               
* 完成日期: 2009-1-29
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1            2009-1-27                    			   创建
*	2			2010-08-09		王俊			修改上下滑动控制
*	3			2010-09-21		              			添加新的变量
**/

#pragma once

#include "KCWnd.h"
#include "KCButton.h"
#include "KCTextCtrl.h"
#include "KCImageCtrl.h"
#include "KCGroupCtrl.h"
#include "KHMIBaseHead.h"
#include "KCScrollButtonText.h"
#include "KCWindow.h"
class CYPRESS_DLL_API HCFileView : public HCGroupCtrl 
{
public:
	HCFileView();
	virtual ~HCFileView();
	HBOOL Create(HINT x, HINT y, HINT w, HINT h);
	void SetBkgndN(IReSurface* pSurf);
	void SetBkgndN(const HString& pFileName);
	virtual HBOOL DoMessage(HMessage* msg);

	void ChangImage(HString strCentIconName,  HString UpFolderNameStr,  HString DownFolderNameStr, HString CentFolderName, HINT nType);

	void SetCentFolderName(const HString& Textstr);
	void SetCentFolderID(HINT nID);

	HString GetUpText();
	HString GetDownText ();
	HString GetCurText();
	void Draw(IReSurface* pSurface);


	void SetCallBackup(void (*callback)(void*, void*), void*);
	void SetCallBackDown(void (*callback)(void*, void *), void *);
	void SetCallBackMove(void (*callback)(void *,void*),void *);

	//两个上下ICON的回调
	static void OnDownButton(void* p, void* pParam);
	void OnDownButton(void);
	static void OnUpButton(void* p, void* pParam);
	void OnUpButton(void);

	void UpBrowse(HString Uptext, HString DownText, HString FileViewText, HINT nType);
	
	void OnInitCtrl(HString str);
private:
	HBOOL m_bImageNFromFile;
	HCButton *m_pBtnUpIcon;
	HCButton *m_pBtnDownIcon;

	HCScrollButtonText *m_pUpFolderNameText;
	HCScrollButtonText *m_pDownFolderNameText;
	HCScrollButtonText *m_pCentFolderNameText;
	HCImageCtrl *m_pCentFolderImage;
	HString m_strUpFolderText;
	HString m_strDownFolderText;
	HINT m_nWidth;
	HINT m_nHeight;
	HINT m_nType;
	IReSurface* m_pBkgndN;
	IReSurface *m_pTransurin;
	IReSurface *m_pTransurout;
	HINT m_nLbtndown;

	void (*m_pCallBackup)(void *, void *);
	void (*m_pCallBackDown)(void *, void *);
	void (*m_pCallBackMove) (void *,void *);


	HINT m_nBaseTime;
	HINT m_nMoveTime;
	HINT m_nMoveNum;
	HBOOL m_bMove;
	HBOOL m_bUpIconShowFlag;
	HBOOL m_bDownIconShowFlag;
	HINT m_nLbtnDownY;
	HBOOL m_bMouseMove;

	HBOOL m_bEnableDrawOutSur;
};
