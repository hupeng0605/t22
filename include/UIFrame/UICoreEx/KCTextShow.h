/**
* Copyright (C) 2010， 
* All rights reserved.
*
* 文件名称: TEST.h
* 摘    要:
*
* 当前版本: 1.0
* 作    者:               
* 完成日期: 2010-4-20
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1           2010-4-20                              创建
*
**/
//#include "KCWindow.h"
#pragma once
#include "KHMIBaseHead.h"
#include <vector>

struct FontInfo
{
	HINT FontIndex;
	HINT FontWidth;
	HINT FontHight;
	RECOLOR FontColor;
};

class CYPRESS_DLL_API HCTextShow: public HCBaseCtrl
{
public:
	HCTextShow();
	~HCTextShow();

	HBOOL Create(HINT x,HINT y,HINT w,HINT h);
	HBOOL Create(HINT x, HINT y, HINT w, HINT h, HINT num);

	void SetNumTextIndex(HINT index);	// 设置数字字符串的位置，默认为0。如果是Time:00:11，请设置成1
	void SetText(const HCHAR* pTxt,HINT fontindex,HINT fontw,HINT fonth,RECOLOR color);
	void SetText( const HCHAR* pTxt, HINT fontindex);
	void SetText(const HCHAR* pTxt);
	void SetTextStyle(HWORD type);	// 可以设置右对齐，默认为左对齐

	//设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
	//void SetBkgndN(IReSurface* pSur);
	//void SetBkgndN(const kn_string& pFileName);
	void DrawFrame(IReSurface* pSurface);
	void DrawOnSurface(IReSurface* pSurface, HINT x = 0, HINT y = 0);
	void Draw(IReSurface* pSurface);

	void SetTextColorA(int r, int g , int b);

	IReSurface* GetFontSurf(const HCHAR* str);
	void CreatSur(HINT fontw,HINT fonth);

	HBOOL DoMessage(HMessage* msg);

	//void EnableMoveInOut(kn_bool bEnable);
	void BeginAnimation();	// 动画开始的位置，在所有SetText之前调用
	void EndAnimation();	// 动画结束的位置，在所有SetText之后调用
	void SetAnimationDulration(HFLOAT second);	// 设置动画的时间
	HFLOAT AnimationFunction(HINT frame);

private:
	vector <HString> m_strevc;
	vector <FontInfo> m_fontinfoevc;
	//kn_int m_nStrNum;
	HINT m_iFontWidth;	// 数字字体的尺寸
	HINT m_iFontHeight;
	HUINT m_nNumTextIndex;	// 数字字符串所在位置
	map<HString,IReSurface*> m_FontCacheSurfMap;

	
	HWORD m_TextStyle;	// 文字样式

	// 滚动
	HBOOL m_bEnableRollUp;

	HFLOAT m_fRollOffset;	// 每次滚动的偏移量
	HFLOAT m_fRollCount;	// 滚动计数
	HFLOAT m_fA, m_fB, m_fH;

	HINT m_iRollBaseTime;
	IReSurface *m_pSurfaceOld;
	IReSurface *m_pSurfaceNew;
};