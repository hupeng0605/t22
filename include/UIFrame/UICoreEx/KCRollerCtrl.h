/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCRollerCtrl.h 
* 摘    要:
*
* 当前版本: 1.0
* 作    者:               
* 完成日期: 2010-1-20
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1            2010-1-20                    			创建
*
**/

#if !defined(AFX_KCDateItem_H__INCLUDED_)
#define AFX_KCDateItem_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWnd.h"

// 滑动停止回调
typedef void (*ScrollStopCallBack)(void*, HINT);

class CYPRESS_DLL_API HCRollerCtrl : public HCBaseCtrl  
{
public:
	HCRollerCtrl();
	~HCRollerCtrl();

	virtual void Draw(IReSurface* pSurface);
	HBOOL DoMessage(HMessage* msg);

	// 滑动停止回调
	void SetScrollStopCallBack( ScrollStopCallBack callback, void* pThis );

	//设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
	void SetBkgndN(IReSurface* pSur);
	void SetBkgndN(const HString& pFileName);

	//设置文本样式
	void SetTextStyle(HWORD style);
	
	// 是否循环
	void EnableRecycle(HBOOL bEnable);

	// 设置范围
	void SetBound(HINT nMin, HINT nMax);

	void SetValidBound(HINT nMin, HINT nMax);

	// 设置显示数目
	void SetShowNum(HINT nNum);

	// 设置中间文本
	void SetMidText(HINT nMidText);

	// 设置行间距
	void SetRowSpace(HINT space);

	// 设置文本格式
	void SetFormat(const HCHAR* pChar);

	// 设置文本位置
	void SetTextPos(HINT x, HINT y);

	// 获取中间值
	HINT GetMidText();

	void StopAutoScroll();

private:
	// 判断是否在范围内
	HBOOL GetIndex(HINT& index);

	// 计算起始和中间值
	void CalStartAndMid();
private:
	//常规背景图
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;
	
	HBOOL m_bEnableCycle;
	HINT m_nMin;
	HINT m_nMax;
	HINT m_nShowNum;

	HINT m_nMinValid;
	HINT m_nMaxValid;

	// 中间值
	HINT m_nMidText;

	HINT m_nMidTextBackup;

	HINT m_yDownOffset;
	HINT m_yOffset;
	
	// 行间距
	HINT m_rowSpace;

	// 格式化
	HString m_strFormat;
	// 文本位置
	HINT m_xTextPos;
	HINT m_yTextPos;
	// 样式
	HWORD m_TextStyle;

	// 鼠标按下时的基准时间
	HINT m_nStartTime;
	// 是否自动滚动
	HBOOL m_bAutoScroll;

	// 滚动时间速度
	HINT m_nScrollOffset;
	// 基准时间，用于计时
	HINT m_nScrollbaseTime;

	// 回调
	ScrollStopCallBack m_pScrollStopCallBack;
	void* m_this;

};

#endif