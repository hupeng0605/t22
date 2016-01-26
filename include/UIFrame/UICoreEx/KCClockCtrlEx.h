/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCClockCtrlEx.h
* 摘    要:
*
* 当前版本: 1.0
* 作    者:               
* 完成日期: 2011-08-01
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1            2011-08-01                                创建
*
**/

#pragma once

#include "KCwnd.h"
#include "RenderingEngine.h"

class CYPRESS_DLL_API HCClockCtrlEx : public HCBaseCtrl
{
public:
	HCClockCtrlEx();
	~HCClockCtrlEx();

	virtual void Draw(IReSurface* pSurface);
	virtual HBOOL DoMessage(HMessage* msg);
public:
	void SetSecondBkgnd(IReSurface* pSur);
	void SetSecondBkgnd(const HString& pFileName);

	void SetMinuteBkgnd(IReSurface* pSur);
	void SetMinuteBkgnd(const HString& pFileName);

	void SetHourBkgnd(IReSurface* pSur);
	void SetHourBkgnd(const HString& pFileName);

	void SetBkgnd(IReSurface* pSur);
	void SetBkgnd(const HString& pFileName);

	void SetDotBkgnd(IReSurface* pSur);
	void SetDotBkgnd(const HString& pFileName);

	void AdjustTimeFromSysTime();
	void SetTime(HINT nSecond, HINT nMinute, HINT nHour);

	void SetSecondRotationPos(HINT nWidth);
	void SetMinuteRotationPos(HINT nWidth);
	void SetHourRotationPos(HINT nWidth);
	void SetRotationCenterPos(HINT nOffsetX, HINT nOffsetY);
	
	void SetFlipTime(HINT nTime);
protected:
	void AdjustTime();
	void DrawTimeSurf(IReSurface* pScreen, IReSurface* pSurf, HFLOAT fAngle, HINT nx=0);
private:

	IReSurface*		m_pSurfSecond;
	IReSurface*		m_pSurfMinute;
	IReSurface*		m_pSurfHour;
	IReSurface*		m_pSurfBk;
	IReSurface*		m_pSurfDot;

	HBOOL			m_bResSecond;
	HBOOL			m_bResMinute;
	HBOOL			m_bResHour;
	HBOOL			m_bResBk;
	HBOOL			m_bResDot;

	HINT m_nPrevSecond;
	HINT m_nPrevMinute;
	HINT m_nPrevHour;
	//基准时间点
	HINT m_nBasetime;
	//表针旋转点所在图片位置宽
	HINT m_nRotationSecond;
	HINT m_nRotationMinute;
	HINT m_nRotationHour;
	//旋转中心相对控件中心的偏移
	HINT m_nRotationCenterX;
	HINT m_nRotationCenterY;
	//刷新屏幕时间,单位为10ms
	HINT m_nFlipTime;
};