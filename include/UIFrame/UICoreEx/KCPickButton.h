/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCPickButton.h 
* ժ    Ҫ:
*
* ��ǰ�汾: 1.0
* ��    ��:               
* �������: 2009-12-29
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1            2009-12-29                    			����
*
**/

#pragma once


#include "KCWindow.h"

class CYPRESS_DLL_API HCPickButton : public HCBaseCtrl  
{
public:
	HCPickButton();
	virtual ~HCPickButton();

	enum PickButtonState
	{
		Left,//���
		Right,//�ұ�
	};

	//���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
	void SetBkgndN(IReSurface* pSurf);
	void SetBkgndN(const HString& pFileName);
	//���ð�ť���汳��ͼ
	void SetButtonBkgndN(IReSurface* pSurf);
	void SetButtonBkgndN(const HString& pFileName);
	//���ð�ť�����ͼ
	void SetButtonBkgndA(IReSurface* pSurf);
	void SetButtonBkgndA(const HString& pFileName);
	//���������ʾ����
	void SetLeftText(const HCHAR* pChar);
	//�����ұ���ʾ����
	void SetRightText(const HCHAR* pChar);
	//���ð�ť����״̬
	void SetButtonState(PickButtonState state);

	virtual HBOOL DoMessage(HMessage* msg);
	virtual void Draw(IReSurface* pSurface);
	//�����¼�
	void SetCallBackMoveLeft(void (*callback)(void*, void*), void* );
	//�����¼�
	void SetCallBackMoveRight(void (*callback)(void*, void*), void* );


	HBOOL CheckPoint(HINT x, HINT y);

	HINT GetLangID(HINT nIdex)
	{
		return m_nLangID[nIdex];
	}
	void SetLangID(HINT a_nLangID,HINT nIdex)
	{
		m_nLangID[nIdex] = a_nLangID;
	}
	
private:
	
	HINT m_nLangID[2];

	//���汳��ͼ
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;
	//��ť���汳��ͼ
	IReSurface* m_pButtonBkgndN;
	HBOOL m_bButtonBkgndNRes;
	//��ť�����ͼ
	IReSurface* m_pButtonBkgndA;
	HBOOL m_bButtonBkgndARes;
	//�������
	HString m_leftText;
	//�ұ�����
	HString m_rightText;
	//״̬
	PickButtonState m_buttonState;
	//���ݰ�ťλ��
	HINT m_backUpPos;
	HINT m_offset;

	// �ƶ�֡��
	HINT m_nFrame;

	void     (*m_pCallBackMoveRight)(void *, void *);
	void     (*m_pCallBackMoveLeft)(void *, void *);
	
	// �Ƿ���Ӧ��ʱ����Ϣ
	HBOOL m_bEnableTime;

};