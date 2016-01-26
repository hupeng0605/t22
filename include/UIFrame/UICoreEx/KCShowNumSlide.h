
/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称:	KCShowNumSlide.h
* 摘    要:	
*
* 当前版本:	1.0
* 作    者:	              
* 完成日期:	2010-01-28
*
* 修改历史：
* [修改序列]	[修改日期] 		[修改者]		[修改内容]
*	1					2010-01-28    	                  	创建
* 	2				2010-11-4	袁江江			新增初始化是否显示接口
**/
#pragma once
#include "KCWnd.h"
#include "Configure.h"
//***************************************************************
// *  功　　能:	滚动列表
// *  作　　者:	              
// *  日　　期:	2010-01-28
//***************************************************************
class CYPRESS_DLL_API HCShowNumSlide : public HCBaseCtrl
{
public:
	HCShowNumSlide();
	~HCShowNumSlide();
	//
	HBOOL Create(HINT x, HINT y, HINT w, HINT h);
	//设置当前频率
	void SetValue(HFLOAT num);
	void SetValue(HString sFreq);
	//设置上下频率的间距
	void SetSpaceBetweenNumber(HFLOAT num);
	//设置当前频率显示文字
	void SetCurFrequecyId(const HCHAR* pTxt);
	//设置背景
	void SetBkgndN(IReSurface* pSurf);
	//设置背景
	void SetBkgndN(const HString& pFileName);
	//设置小数点位数
	void SetDecDig(HBOOL Index);
	//获得当前频率
	HFLOAT GetMidFrequecy();
	void SetBound(IN HFLOAT nMin, IN HFLOAT nMax);
	void SetCallBackValueChange(void (*callback)(void*, void*), void* pThis);
	void SetCallBackMoveDown(void (*callback)(void*, void*), void* pThis);
	void SetCallBackMoveUp(void (*callback)(void*, void*), void* pThis);
	//初始化时是否显示数值
	void SetShowNum(HBOOL IsShowNum);

	//增加点击回调
	void SetCallBackMouseClick(void (*callback)(void*,void*),void* pThis);

	void StarTran(HBOOL bbool);
	void ChengedInt(HINT x);
	void SetStopFreq(HString freq,HBOOL bstop);
	void SetShowNumCanTran(HBOOL bBool);
	void SetShowNumCanTran();
	void SetRadioFile(HINT RadioFile);
protected:
private:
	//数字转换成字符串
	HString DiStillIntPart(HINT num);
	virtual void Draw(IReSurface* pSurface);
	//消息处理函数
	HBOOL DoMessage(HMessage* msg);
	HString DiStillDecPart(HINT num);
	void JudgeDecPart(HINT &num);
	HBOOL JudgeDecPartMoveNumber(HINT &num);
	void FormatFre(HFLOAT &ftr);

	IReSurface* GetFontSurf(HString& str);
private:

	IReSurface *m_pUnitText; 
	IReSurface *m_pPointSur;
	HBOOL m_bMoveHead;//True为从上往下，FALSE为从下往上
	HBOOL m_bBkgndNRes;//是否存在背景
	HBOOL m_bIntCanMoveInOut; //是否进行移动
	HBOOL m_bDecCanMoveInOut;
	HBOOL m_bIntMoveInOut;//整数移动的标志位
	HBOOL m_bDecMoveInOut; //小数移动的标志位
	HBOOL m_bDecDig;//是否有小数

	IReSurface *m_pBkgndN;//背景图片
	IReSurface *m_pSeekUpSur;
	IReSurface *m_pSeekDownSur;
	HFLOAT m_fMidValue; //当前的频率

	HINT m_nSpaceNumber; //间距
	HINT m_nMargin;//行间距

	kn_rect m_RectMiddle; //绘制区域
	HINT m_yoffset; //偏移
	HINT m_nBaseTime; //基础时间

	HINT m_moveInOutTime; //移动的时间间隔
	HINT m_nMoveNum;//移动次数
	HINT m_nDownpos;//按下的位置
	HBOOL m_bIntMouseMove;//是否移动
	HBOOL m_bDecMouseMove;

	HINT m_nFontSizeY; //字体的大小 
	HINT m_nFontSizeX;// 
	HINT m_nIntNumber;//记录整数部分
	HINT m_nDecNumber;//记录小数部分
	HINT m_nTar;
	HFLOAT m_fMaxValue;
	HFLOAT m_fMinValue;
	HBOOL m_bCanBeMove;
	// 回调函数变量,要传入类指针
	void (*m_pCallBackValueChange)(void *, void *);
	void (*m_pCallBackMoveDown)(void *,void *);
	void (*m_pCallBackMoveUp)(void *,void *);

	//点击回调
	void (*m_pCallBackMouseClick)(void *,void *);

	HString GetFreqStr();
	void CriticlDeal();

	void* m_pThisValueChange;
	HBOOL m_btran;
	IReSurface *m_pBKSurUp; //背景图片
	IReSurface *m_pBKSurDown;
	HBOOL m_bstop;
	HString m_fStopFreq;
	HBOOL m_bStarMove;
	HINT m_nStarTime;
	HBOOL m_bmove;
	HBOOL m_bCanTran;//设置数字滑轮是否可以做迁移
	map<HString,IReSurface*> m_FontCacheSurfMap;//字符串
	HString m_nMaxIntNum;//最大整数
	HString m_nMinIntNum;//最小整数
	HString m_nMaxDecNum;//最大小数
	HString m_nMinDecNum;//最小小数
	HINT m_nRadioKind;//获得Radio的种类为零的时候是US 为一的时候是EU
	HBOOL m_bIsShowNum;//初始化时是否显示数值
};
