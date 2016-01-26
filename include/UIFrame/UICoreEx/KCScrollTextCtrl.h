/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCScrollTextCtrl.h 
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

#include "KCWnd.h"

//移动方式
enum eMoveInOutMode
{
	LeftToRight,
	RightToLeft,
	BottomToTop,
	TopToBottom,
};

//文字位置样式
enum eTextStyle
{
	Left,
	LeftTop, 
	LeftBottom,
	Right,
	RightTop,
	RightBottom,
	Center,//左右居中，上下居中
};


class CYPRESS_DLL_API HCScrollTextCtrl : public HCBaseCtrl  
{
public:
	HCScrollTextCtrl();
	~HCScrollTextCtrl();

	virtual void Draw(IReSurface* pSurface);
	HBOOL DoMessage(HMessage* msg);

	//设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
	void SetBkgndN(IReSurface* pSur);
	void SetBkgndN(const HString& pFileName);

	//设置文本样式
	void SetTextStyle(eTextStyle style);
	//设置文本，会触发滚动效果
	void SetText(const HCHAR* str);
	HString GetText();

	void SetMoveInOutMode(eMoveInOutMode mode);
	//设置每次移动时的时间间隔
	void SetMoveInOutTime(HINT ms);
	//设置移动的次数
	void SetMoveInOutNum(HINT num);
	//图片更换时是否允许移入移出
	void EnableMoveInOut(HBOOL bEnable);

private:
	//返回当前文本的位置
	void GetTextPos(HINT& x, HINT& y);
	//返回滚动时文本的位置
	void GetTextScrollPos(HINT&x, HINT& y);
	
private:
	//常规背景图
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;

	HString m_text;//文本
	eTextStyle m_textStyle;
	eMoveInOutMode m_moveInOutMode;

	//进入背景图
	IReSurface* m_curTextSurf;
	IReSurface* m_inTextSurf;

	//图片更换时移入移出
	HBOOL m_bCanMoveInOut;
	
	//当前的状态
	HBOOL m_bMoveInOut;
	HINT m_moveInOutIndex;//移动到第几次

	HINT m_moveInOutBaseTime;//基准时间
	HINT m_moveInOutTime;//移动的间隔时间
	HINT m_nMoveInOutNum;//总共移动的次数
	
};