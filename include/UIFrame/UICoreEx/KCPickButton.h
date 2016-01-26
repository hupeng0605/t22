/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCPickButton.h 
* 摘    要:
*
* 当前版本: 1.0
* 作    者:               
* 完成日期: 2009-12-29
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1            2009-12-29                    			创建
*
**/

#pragma once


#include "KCWindow.h"

class CYPRESS_DLL_API HCPickButton : public HCBaseCtrl  
{
public:
	HCPickButton();
	virtual ~HCPickButton();

	enum PickButtonState
	{
		Left,//左边
		Right,//右边
	};

	//设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
	void SetBkgndN(IReSurface* pSurf);
	void SetBkgndN(const HString& pFileName);
	//设置按钮常规背景图
	void SetButtonBkgndN(IReSurface* pSurf);
	void SetButtonBkgndN(const HString& pFileName);
	//设置按钮激活背景图
	void SetButtonBkgndA(IReSurface* pSurf);
	void SetButtonBkgndA(const HString& pFileName);
	//设置左边显示文字
	void SetLeftText(const HCHAR* pChar);
	//设置右边显示文字
	void SetRightText(const HCHAR* pChar);
	//设置按钮所处状态
	void SetButtonState(PickButtonState state);

	virtual HBOOL DoMessage(HMessage* msg);
	virtual void Draw(IReSurface* pSurface);
	//左移事件
	void SetCallBackMoveLeft(void (*callback)(void*, void*), void* );
	//右移事件
	void SetCallBackMoveRight(void (*callback)(void*, void*), void* );


	HBOOL CheckPoint(HINT x, HINT y);

	HINT GetLangID(HINT nIdex)
	{
		return m_nLangID[nIdex];
	}
	void SetLangID(HINT a_nLangID,HINT nIdex)
	{
		m_nLangID[nIdex] = a_nLangID;
	}
	
private:
	
	HINT m_nLangID[2];

	//常规背景图
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;
	//按钮常规背景图
	IReSurface* m_pButtonBkgndN;
	HBOOL m_bButtonBkgndNRes;
	//按钮激活背景图
	IReSurface* m_pButtonBkgndA;
	HBOOL m_bButtonBkgndARes;
	//左边文字
	HString m_leftText;
	//右边文字
	HString m_rightText;
	//状态
	PickButtonState m_buttonState;
	//备份按钮位置
	HINT m_backUpPos;
	HINT m_offset;

	// 移动帧数
	HINT m_nFrame;

	void     (*m_pCallBackMoveRight)(void *, void *);
	void     (*m_pCallBackMoveLeft)(void *, void *);
	
	// 是否响应定时器消息
	HBOOL m_bEnableTime;

};