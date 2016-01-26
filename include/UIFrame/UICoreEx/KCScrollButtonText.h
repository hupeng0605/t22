/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称:	KCScrollTextButton.h
* 摘    要:	
*
* 当前版本:	1.0
* 作    者:	              
* 完成日期:	2010-01-28
*
* 修改历史：
* [修改序列]	[修改日期]		[修改者]	[修改内容]
*	1			2010-01-28    	              		创建
* 	2			2010-02-26                    		超长的文字变成..点击上面滚动
* 	3			2010-12-06      王俊		优化SetText性能
*	4			2011-02-11		袁江江		修改超长文字显示坐标
*	5			2011-10-21		              		添加文字滚动宽度
**/

#pragma once

#include "KCWnd.h"
#include "KCScrollTextCtrl.h"
struct kn_StartPoint
{
	HINT x;
	HINT y;
};
class CYPRESS_DLL_API HCScrollButtonText: public HCBaseCtrl
{
public:
	HCScrollButtonText(void);
	~HCScrollButtonText(void);
	virtual void Draw(IReSurface* pSurface);
	virtual HBOOL Create(HINT x, HINT y, HINT w, HINT h);

	void GetCurDrawPos( HINT textX, HINT x, HINT &xOffset, HINT &xTar, HINT textY, HINT y, HINT &yOffset, HINT &yTar );
	HBOOL DoMessage(HMessage* msg);

	//设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
	void SetBkgndN(IReSurface* pSur);
	void SetBkgndN(const HString& pFileName);

	void SetBkgndA(IReSurface* pSur);
	void SetBkgndA(const HString& pFileName);  
	// 设置文字的起始位置
	void SetTextPos(kn_StartPoint pos);
	//设置文本样式
	void SetTextStyle(eTextStyle style);
	//设置文本，会触发滚动效果
	void SetText(const HCHAR *str);
	//设置文本,会触发滚动效果
	void SetText(HCHAR *str,HINT x , HINT y);
	//得到当前的文本
	HString GetText();
	void SetMoveInOutMode(eMoveInOutMode mode);
	//设置每次移动时的时间间隔
	void SetMoveInOutTime(HINT ms);
	//设置移动的次数
	void SetMoveInOutNum(HINT num);
	//图片更换时是否允许移入移出
	void EnableMoveInOut(HBOOL bEnable);
	//文字超长是否允许自动滚动以及滚动的圈数
	void EnableAutoRoll(HBOOL bAuto , HINT RingNumber);
	//判断是否在滚动
	HBOOL ISAutoRoll();
	// 是否允许无限滚动
	void EnableInfinityRoll(HBOOL bInfinityRoll);

	void SetCallBackAutoRoll(void (*callback)(void*, void*), void* pThis);

	//设置是否超长打点显示
	void SetIsDot(HBOOL IsDot);
	//设置垂直偏移量
	void SetYPos(HINT pos);
	// 言语部分
	HINT GetLangID(void)
	{
		return m_nLangID;
	}
	void SetLangID(HINT a_nLangID)
	{
		m_nLangID = a_nLangID;
	}

	//设置文字滚动的宽度
	void SetRollWidth(HINT nWidth);
private:
	HINT m_nLangID;
	//返回当前文本的位置
	void GetCurTextPos(HINT& x, HINT& y);

	void GetNextTextPos(HINT& x, HINT& y);
	//返回滚动时文本的位置
	void GetCurTextScrollPos(HINT&x, HINT& y);
	// 鼠标长按消息
	void (*m_pCallBackLongPress)(void *, void *);
	void (*m_pCallBackAutoRoll)(void *, void *);
	void GetNextTextScrollPos(HINT&x, HINT& y);

	void TruncText(HBOOL* bRoll, HINT* ii);
	HINT m_longPressTime;
	HINT m_baseTime;
private:
	//常规背景图
	IReSurface* m_pBkgndN;
	IReSurface *m_pBkgndA;
	HBOOL m_bBkgndNRes; 
	HBOOL m_bEnableAutoRoll;//是否自己移动
	HINT  m_nSetRollNumber;//设置自动滚动的圈数
	HINT  m_nCurRollNumber;//当前移动的圈数

	HString m_text;//文本
	eTextStyle m_textStyle;
	eMoveInOutMode m_moveInOutMode;
	//进入背景图
	IReSurface* m_curTextSurf;
	IReSurface* m_inTextSurf;
	IReSurface* m_pRollTextSurf;
	HBOOL m_bRollFlag;
	HINT m_nRollIndex;
	HINT m_nSecondRollIndex;
	HBOOL m_bSecondRoll;
	//图片更换时移入移出
	HBOOL m_bCanMoveInOut;
	// 字体的位置
	kn_StartPoint m_point;
	//当前的状态
	HBOOL m_bMoveInOut;
	HINT m_moveInOutIndex;//移动到第几次
	HBOOL m_bHaveExecute; 
	HINT m_moveInOutBaseTime;//基准时间
	HINT m_moveInOutTime;//移动的间隔时间
	HINT m_nMoveInOutNum;//总共移动的次数
	HBOOL m_bRoll;
	// 无限滚动标志位
	HBOOL m_bInfinityRoll;

	HBOOL m_bRedraw;	// 是否需要重绘文字
	//设置是否超长打点显示
	HBOOL m_bIsDot;
	//设置
	HINT m_nYPos;

	//设置文字滚动的宽度
	HINT m_nRollWidth;
};
