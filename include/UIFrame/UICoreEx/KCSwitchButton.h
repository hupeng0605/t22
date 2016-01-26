/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称:	KCMorePickBtn.h
* 摘    要:	
*
* 当前版本:	1.0
* 作    者:	              
* 完成日期:	2010-01-28
*
* 修改历史：
* [修改序列]	[修改日期] 		[修改者]		[修改内容]
*	1			2010-01-28    	                  	    创建
* 	
**/
#pragma once


#include "KCWindow.h"
#include "vector"

#define MAX_BTN_NUM (5)

typedef vector <HString> TEXT_ITEM_VEC;
// 移动回调
typedef void (*CallBackMove)(void*, HINT);
typedef void (*CallBackMoveEnd)(void*, HINT);
typedef void (*CallBackCheck)(void*, HINT);

class CYPRESS_DLL_API HCSwitchButton : public HCBaseCtrl  
{
public:
	HCSwitchButton();
	virtual ~HCSwitchButton();


	//设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
	void SetBkgndN(IReSurface* pSurf);
	void SetBkgndN(const HString& pFileName);
	//设置按钮常规背景图
	void SetButtonBkgndN(IReSurface* pSurf);
	void SetButtonBkgndN(const HString& pFileName);
	//设置按钮激活背景图
	void SetButtonBkgndA(IReSurface* pSurf);
	void SetButtonBkgndA(const HString& pFileName);

	// 初始化文字
	void SetVecText(TEXT_ITEM_VEC vecText);
	// 设置指定项文字
	void SetVecText(const HCHAR* pChar,HINT nIndex);
	
	void SetFontHeigthPos(HINT yPos);

	// 设置按钮所处第几项
	void SetButtonIndex(HINT nIndex);

	// 设置按钮个数
	void SetBtnNum(HINT nBtnNum);
	// 返回按钮个数
	HINT GetBtnNum();
	// 获取移动状态
	HBOOL GetMoveState();

	virtual HBOOL DoMessage(HMessage* msg);
	virtual void Draw(IReSurface* pSurface);


	// 移动回调
	void SetCallBackMove(CallBackMove pMoveCallBack, void* );
	// 移动结束回调
	void SetCallBackMoveEnd(CallBackMoveEnd pMoveEndCallBack, void* );

	void SetCallBackCheck(CallBackCheck pCheckCallBack, void* pThis);
	void SetEnableTran(HBOOL nbool);
	void SetXPos(HINT xPos);
	HINT GetLangID(HINT nIdex)
	{
		return m_nLangID[nIdex];
	}
	void SetLangID(HINT a_nLangID,HINT nIdex)
	{
		m_nLangID[nIdex] = a_nLangID;
	}
	HINT GetIndex();	

	void SetBtnOffset(HINT x, int y);
private:
	// 根据点击X坐标判断当前点击项
	HINT GetIndexByX(HINT x);

private:

	HINT m_nLangID[MAX_BTN_NUM];

	//常规背景图
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;
	//按钮常规背景图
	IReSurface* m_pButtonBkgndN;
	HBOOL m_bButtonBkgndNRes;
	//按钮激活背景图
	IReSurface* m_pButtonBkgndA;
	HBOOL m_bButtonBkgndARes;

	// 文字 
	TEXT_ITEM_VEC m_vecStrText;
	// 上一次所在项
	HINT m_nLastIndex;
	// 当前所处第几项
	HINT m_nIndex;
	// 按钮个数
	HINT m_nBtnNum;


	//备份按钮位置
	HINT m_backUpPos;
	// 鼠标滑动偏移
	HINT m_offset;

	// 移动帧数
	HINT m_nFrame;

	CallBackMove m_pMoveCallBack;
	CallBackMoveEnd m_pMoveEndCallBack;
	CallBackCheck m_pCheckCallBack;
	// 是否响应定时器消息
	HBOOL m_bEnableTime;
	HBOOL m_bEnableTran;//为true时使用定时器做画面的迁移  false时不做迁移
	HBOOL m_bmousemove;//是否为额鼠标移动
	HBOOL m_bmove;//是否为拖动迁移
	HINT m_nYfontPos;
	HINT m_nXfontPos;//X文字的起始点
	HINT m_nTime;

	//添加设置偏移
	HINT m_nOffsetX;
	HINT m_nOffsetY;

};
