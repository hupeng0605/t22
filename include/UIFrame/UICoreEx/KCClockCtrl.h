/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCClockCtrl.h
* ժ    Ҫ:
*
* ��ǰ�汾: 1.0
* ��    ��:               
* �������: 2009-12-29
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1            2010-03-01                                ����
*
**/

/*
KCBaseCtrl ������������m_strName,m_strName����ʱ�䣬�¼ӵ�m_strText����am/pm
*/

#pragma once

#define AMPM_FONT_SIZE	(20)		// ampm�����С
//#define TIME_FONT_SIZE	(33)		// ʱ�������С

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

	void SetAMPMColorN(int r, int g , int b);	// ����am,pm����ɫ
	void SetAMPMColorN(RECOLOR color);
	void SetAMPMFontSize(HINT width, HINT height);	// ����am,pm�������С
	
	void Draw(IReSurface* pSurface);
	
private:
	void UpdateCtrlPos();
	void ParseTimeString(const HString& strTime);
private:
    HINT m_xIconPos;			// icon����
	HINT m_yIconPos;
	IReSurface* m_pIconSurf;	// icon����
	
	HINT m_xTextPos;			// ampm�ı�������
	HINT m_yTextPos;
	HINT m_nTextWidth;		// am,pm�ַ����Ŀ��
	HINT m_nAMPMFontWidth;	// am,pm�����С
	HINT m_nAMPMFontHeight;	// am,pm�����С
	HString m_strAMPM;		// ����am,pm�ַ���
	RECOLOR m_clrAMPM;			// am,pm����ɫ

	HINT m_xNamePos;			// ʱ���ı�����
	HINT m_yNamePos;
	HINT m_nNameWidth;
};