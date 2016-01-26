/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCButtonTree.h 
* 摘    要:
*
* 当前版本: 1.0
* 作    者:               
* 完成日期: 2009-1-27
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1            2009-1-27                    			创建
*
**/

#pragma once

#include "KCWnd.h"

class CYPRESS_DLL_API HCButtonTree : public HCBaseCtrl  
{
public:
	HCButtonTree();
	virtual ~HCButtonTree();


	//设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
	void SetBkgndN(IReSurface* pSurf);
	void SetBkgndN(const HString& pFileName);

	void Create(HINT x, HINT y, HINT w, HINT h, HINT width);

	//设置当前要显示的图标的的背景图
	void SetCurrentItem(HINT nIndex);
	
	//设置按钮常规背景图
	void SetButtonTreeBkgndN(IReSurface* pSurf);

	void SetButtonTreeBkgndN(const HString& pFileName);

	virtual HBOOL DoMessage(HMessage* msg);
	virtual void Draw(IReSurface* pSurface);
	//左移事件
	void SetCallBackMoveLeft(void (*callback)(void*, void*), void* );
	//右移事件
	void SetCallBackMoveRight(void (*callback)(void*, void*), void* );

	HBOOL CheckPoint(HINT x, HINT y);
	
	void SetString(HString &str , HINT nIndex);
	void AddString(HString &str);
	void SetCtrlFontSize(HINT width, HINT height);
	void SetFontType(HINT type);
private:

	//常规背景图
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;
	//按钮常规背景图
	IReSurface* m_pButtonBkgndN;
	HBOOL m_bButtonBkgndNRes;
	//按钮激活背景图
	IReSurface* m_pButtonBkgndA;
	HBOOL m_bButtonBkgndARes;
	//按钮状态
	HBOOL m_bState;

	HINT m_offset;
	HINT m_nIndex;
	HINT m_ItemWidth;
	HINT m_ItemNum;
	HBOOL m_bCheck;
	HINT m_nXup,m_nXdown;
	void     (*m_pCallBackMoveRight)(void *, void *);
	void     (*m_pCallBackMoveLeft)(void *, void *);
	void Deploy();

	HBOOL m_bDrawButton;
	
	vector <HString> ItemStr;

};