/**
* Copyright (C) 2010�� 
* All rights reserved.
*
* �ļ�����: d:\Dev\Cypress\CypressDB\03IMPLEMENT\0301Code\Cypress\hmiengineEx\KCBTImgCtrl.h
* ժ    Ҫ:
*
* ��ǰ�汾: 1.0
* ��    ��: 
* �������: 2010-4-21
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1           2010-4-21             		����
*	2			2010-4-23		  		�޸Ŀؼ���ӰЧ��
*	3			2010-4-27		  		��ӹ���Ч��
*	4			2010-7-3		�ϻ���		������ÿؼ�״̬�ĺ���
*
**/


#pragma once
#include "KCWnd.h"
#include <vector>

#define MAX_ALPHA_NUM	(27)

class CYPRESS_DLL_API HCBTImgCtrl: public HCBaseCtrl
{
public:
	HCBTImgCtrl(void);
	~HCBTImgCtrl(void);
	// �軭����
	void Draw(IReSurface *pSurface);
	// ��Ϣ������
	HBOOL DoMessage(HMessage* msg);
	// ���õ���ص�
	void SetCallClickImgEvent(void (*callback)(HINT , void*) ,void *pThis);
	// �����λ����Ч��
	HBOOL CheckPointValid(HINT x,HINT y);
	// ���ÿؼ�
	void Reset(void);

private:
	//vector<kn_string>	m_vInfo;


	IReSurface *		m_pBkSurf;
	HINT m_nBWidth;
	HINT m_nBheigth;
	HINT m_nMoveWidth;
	HINT m_nIndex;
	HBOOL m_bDownEvent;
	IReSurface *		m_pSeclectSurf;
	HINT m_nLbtnDown;
	HBOOL m_bMove;

	// ����ص�
	void* m_pParentCtrl;
	void (*m_pCallbackClickEvent)(HINT nIndex, void*);

	IReSurface *		m_pBackGrndSurf;
	IReSurface *		m_pSlideSurf;
	HINT				m_nOffset;

	// ����Ч��
	HINT  m_xBackup;//��갴��ʱλ��
	//kn_int  m_xOffset;//���ƫ��

	HBOOL m_bCanMove; // ��ǰ�Ƿ��ڹ���״̬
	//kn_int m_startIndex;//��ʼ���Ƶ���

	HINT m_StartTime;//��갴��ʱ��׼ʱ��
	HBOOL m_bAutoScroll;//�Զ�����
	HBOOL m_bAutoScrollBackup;//���ݣ���Ҫ����ָ�����������е���ʱ״̬
	HINT m_nScrollOffset;
	//kn_int m_nOffsetBackup;
	HINT m_ScrollbaseTime;

	IReSurface* m_szpAlphaSur_Sel[MAX_ALPHA_NUM];
	IReSurface* m_szpAlphaSur_Nor[MAX_ALPHA_NUM];

	HINT m_rowWidth;
};
