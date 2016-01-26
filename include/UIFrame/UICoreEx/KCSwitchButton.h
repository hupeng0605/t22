/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����:	KCMorePickBtn.h
* ժ    Ҫ:	
*
* ��ǰ�汾:	1.0
* ��    ��:	              
* �������:	2010-01-28
*
* �޸���ʷ��
* [�޸�����]	[�޸�����] 		[�޸���]		[�޸�����]
*	1			2010-01-28    	                  	    ����
* 	
**/
#pragma once


#include "KCWindow.h"
#include "vector"

#define MAX_BTN_NUM (5)

typedef vector <HString> TEXT_ITEM_VEC;
// �ƶ��ص�
typedef void (*CallBackMove)(void*, HINT);
typedef void (*CallBackMoveEnd)(void*, HINT);
typedef void (*CallBackCheck)(void*, HINT);

class CYPRESS_DLL_API HCSwitchButton : public HCBaseCtrl  
{
public:
	HCSwitchButton();
	virtual ~HCSwitchButton();


	//���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
	void SetBkgndN(IReSurface* pSurf);
	void SetBkgndN(const HString& pFileName);
	//���ð�ť���汳��ͼ
	void SetButtonBkgndN(IReSurface* pSurf);
	void SetButtonBkgndN(const HString& pFileName);
	//���ð�ť�����ͼ
	void SetButtonBkgndA(IReSurface* pSurf);
	void SetButtonBkgndA(const HString& pFileName);

	// ��ʼ������
	void SetVecText(TEXT_ITEM_VEC vecText);
	// ����ָ��������
	void SetVecText(const HCHAR* pChar,HINT nIndex);
	
	void SetFontHeigthPos(HINT yPos);

	// ���ð�ť�����ڼ���
	void SetButtonIndex(HINT nIndex);

	// ���ð�ť����
	void SetBtnNum(HINT nBtnNum);
	// ���ذ�ť����
	HINT GetBtnNum();
	// ��ȡ�ƶ�״̬
	HBOOL GetMoveState();

	virtual HBOOL DoMessage(HMessage* msg);
	virtual void Draw(IReSurface* pSurface);


	// �ƶ��ص�
	void SetCallBackMove(CallBackMove pMoveCallBack, void* );
	// �ƶ������ص�
	void SetCallBackMoveEnd(CallBackMoveEnd pMoveEndCallBack, void* );

	void SetCallBackCheck(CallBackCheck pCheckCallBack, void* pThis);
	void SetEnableTran(HBOOL nbool);
	void SetXPos(HINT xPos);
	HINT GetLangID(HINT nIdex)
	{
		return m_nLangID[nIdex];
	}
	void SetLangID(HINT a_nLangID,HINT nIdex)
	{
		m_nLangID[nIdex] = a_nLangID;
	}
	HINT GetIndex();	

	void SetBtnOffset(HINT x, int y);
private:
	// ���ݵ��X�����жϵ�ǰ�����
	HINT GetIndexByX(HINT x);

private:

	HINT m_nLangID[MAX_BTN_NUM];

	//���汳��ͼ
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;
	//��ť���汳��ͼ
	IReSurface* m_pButtonBkgndN;
	HBOOL m_bButtonBkgndNRes;
	//��ť�����ͼ
	IReSurface* m_pButtonBkgndA;
	HBOOL m_bButtonBkgndARes;

	// ���� 
	TEXT_ITEM_VEC m_vecStrText;
	// ��һ��������
	HINT m_nLastIndex;
	// ��ǰ�����ڼ���
	HINT m_nIndex;
	// ��ť����
	HINT m_nBtnNum;


	//���ݰ�ťλ��
	HINT m_backUpPos;
	// ��껬��ƫ��
	HINT m_offset;

	// �ƶ�֡��
	HINT m_nFrame;

	CallBackMove m_pMoveCallBack;
	CallBackMoveEnd m_pMoveEndCallBack;
	CallBackCheck m_pCheckCallBack;
	// �Ƿ���Ӧ��ʱ����Ϣ
	HBOOL m_bEnableTime;
	HBOOL m_bEnableTran;//Ϊtrueʱʹ�ö�ʱ���������Ǩ��  falseʱ����Ǩ��
	HBOOL m_bmousemove;//�Ƿ�Ϊ������ƶ�
	HBOOL m_bmove;//�Ƿ�Ϊ�϶�Ǩ��
	HINT m_nYfontPos;
	HINT m_nXfontPos;//X���ֵ���ʼ��
	HINT m_nTime;

	//�������ƫ��
	HINT m_nOffsetX;
	HINT m_nOffsetY;

};
