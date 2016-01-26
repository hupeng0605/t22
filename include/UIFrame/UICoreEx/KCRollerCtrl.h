/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCRollerCtrl.h 
* ժ    Ҫ:
*
* ��ǰ�汾: 1.0
* ��    ��:               
* �������: 2010-1-20
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1            2010-1-20                    			����
*
**/

#if !defined(AFX_KCDateItem_H__INCLUDED_)
#define AFX_KCDateItem_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWnd.h"

// ����ֹͣ�ص�
typedef void (*ScrollStopCallBack)(void*, HINT);

class CYPRESS_DLL_API HCRollerCtrl : public HCBaseCtrl  
{
public:
	HCRollerCtrl();
	~HCRollerCtrl();

	virtual void Draw(IReSurface* pSurface);
	HBOOL DoMessage(HMessage* msg);

	// ����ֹͣ�ص�
	void SetScrollStopCallBack( ScrollStopCallBack callback, void* pThis );

	//���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
	void SetBkgndN(IReSurface* pSur);
	void SetBkgndN(const HString& pFileName);

	//�����ı���ʽ
	void SetTextStyle(HWORD style);
	
	// �Ƿ�ѭ��
	void EnableRecycle(HBOOL bEnable);

	// ���÷�Χ
	void SetBound(HINT nMin, HINT nMax);

	void SetValidBound(HINT nMin, HINT nMax);

	// ������ʾ��Ŀ
	void SetShowNum(HINT nNum);

	// �����м��ı�
	void SetMidText(HINT nMidText);

	// �����м��
	void SetRowSpace(HINT space);

	// �����ı���ʽ
	void SetFormat(const HCHAR* pChar);

	// �����ı�λ��
	void SetTextPos(HINT x, HINT y);

	// ��ȡ�м�ֵ
	HINT GetMidText();

	void StopAutoScroll();

private:
	// �ж��Ƿ��ڷ�Χ��
	HBOOL GetIndex(HINT& index);

	// ������ʼ���м�ֵ
	void CalStartAndMid();
private:
	//���汳��ͼ
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;
	
	HBOOL m_bEnableCycle;
	HINT m_nMin;
	HINT m_nMax;
	HINT m_nShowNum;

	HINT m_nMinValid;
	HINT m_nMaxValid;

	// �м�ֵ
	HINT m_nMidText;

	HINT m_nMidTextBackup;

	HINT m_yDownOffset;
	HINT m_yOffset;
	
	// �м��
	HINT m_rowSpace;

	// ��ʽ��
	HString m_strFormat;
	// �ı�λ��
	HINT m_xTextPos;
	HINT m_yTextPos;
	// ��ʽ
	HWORD m_TextStyle;

	// ��갴��ʱ�Ļ�׼ʱ��
	HINT m_nStartTime;
	// �Ƿ��Զ�����
	HBOOL m_bAutoScroll;

	// ����ʱ���ٶ�
	HINT m_nScrollOffset;
	// ��׼ʱ�䣬���ڼ�ʱ
	HINT m_nScrollbaseTime;

	// �ص�
	ScrollStopCallBack m_pScrollStopCallBack;
	void* m_this;

};

#endif