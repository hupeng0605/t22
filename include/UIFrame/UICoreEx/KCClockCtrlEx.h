/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCClockCtrlEx.h
* ժ    Ҫ:
*
* ��ǰ�汾: 1.0
* ��    ��:               
* �������: 2011-08-01
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1            2011-08-01                                ����
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
	//��׼ʱ���
	HINT m_nBasetime;
	//������ת������ͼƬλ�ÿ�
	HINT m_nRotationSecond;
	HINT m_nRotationMinute;
	HINT m_nRotationHour;
	//��ת������Կؼ����ĵ�ƫ��
	HINT m_nRotationCenterX;
	HINT m_nRotationCenterY;
	//ˢ����Ļʱ��,��λΪ10ms
	HINT m_nFlipTime;
};