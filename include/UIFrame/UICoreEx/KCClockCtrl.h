/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCClockCtrl.h
* 摘    要:
*
* 当前版本: 1.0
* 作    者:               
* 完成日期: 2009-12-29
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1            2010-03-01                                创建
*
**/

/*
KCBaseCtrl 本来就有属性m_strName,m_strName保存时间，新加的m_strText保存am/pm
*/

#pragma once

#define AMPM_FONT_SIZE	(20)		// ampm字体大小
//#define TIME_FONT_SIZE	(33)		// 时间字体大小

#include "KCwnd.h"
#include "RenderingEngine.h"

class CYPRESS_DLL_API HCClockCtrl : public HCBaseCtrl
{
public:
    HCClockCtrl();
    ~HCClockCtrl();
public:
	void SetIcon(const HCHAR* path, HINT x, HINT y);
	void SetText(const HCHAR* str);
	void SetText(HString& str);

	void SetAMPMColorN(int r, int g , int b);	// 设置am,pm的颜色
	void SetAMPMColorN(RECOLOR color);
	void SetAMPMFontSize(HINT width, HINT height);	// 设置am,pm的字体大小
	
	void Draw(IReSurface* pSurface);
	
private:
	void UpdateCtrlPos();
	void ParseTimeString(const HString& strTime);
private:
    HINT m_xIconPos;			// icon坐标
	HINT m_yIconPos;
	IReSurface* m_pIconSurf;	// icon内容
	
	HINT m_xTextPos;			// ampm文本的坐标
	HINT m_yTextPos;
	HINT m_nTextWidth;		// am,pm字符串的宽度
	HINT m_nAMPMFontWidth;	// am,pm字体大小
	HINT m_nAMPMFontHeight;	// am,pm字体大小
	HString m_strAMPM;		// 保存am,pm字符串
	RECOLOR m_clrAMPM;			// am,pm的颜色

	HINT m_xNamePos;			// 时间文本坐标
	HINT m_yNamePos;
	HINT m_nNameWidth;
};