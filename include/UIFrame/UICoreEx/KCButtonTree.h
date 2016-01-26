/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCButtonTree.h 
* ժ    Ҫ:
*
* ��ǰ�汾: 1.0
* ��    ��:               
* �������: 2009-1-27
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1            2009-1-27                    			����
*
**/

#pragma once

#include "KCWnd.h"

class CYPRESS_DLL_API HCButtonTree : public HCBaseCtrl  
{
public:
	HCButtonTree();
	virtual ~HCButtonTree();


	//���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
	void SetBkgndN(IReSurface* pSurf);
	void SetBkgndN(const HString& pFileName);

	void Create(HINT x, HINT y, HINT w, HINT h, HINT width);

	//���õ�ǰҪ��ʾ��ͼ��ĵı���ͼ
	void SetCurrentItem(HINT nIndex);
	
	//���ð�ť���汳��ͼ
	void SetButtonTreeBkgndN(IReSurface* pSurf);

	void SetButtonTreeBkgndN(const HString& pFileName);

	virtual HBOOL DoMessage(HMessage* msg);
	virtual void Draw(IReSurface* pSurface);
	//�����¼�
	void SetCallBackMoveLeft(void (*callback)(void*, void*), void* );
	//�����¼�
	void SetCallBackMoveRight(void (*callback)(void*, void*), void* );

	HBOOL CheckPoint(HINT x, HINT y);
	
	void SetString(HString &str , HINT nIndex);
	void AddString(HString &str);
	void SetCtrlFontSize(HINT width, HINT height);
	void SetFontType(HINT type);
private:

	//���汳��ͼ
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;
	//��ť���汳��ͼ
	IReSurface* m_pButtonBkgndN;
	HBOOL m_bButtonBkgndNRes;
	//��ť�����ͼ
	IReSurface* m_pButtonBkgndA;
	HBOOL m_bButtonBkgndARes;
	//��ť״̬
	HBOOL m_bState;

	HINT m_offset;
	HINT m_nIndex;
	HINT m_ItemWidth;
	HINT m_ItemNum;
	HBOOL m_bCheck;
	HINT m_nXup,m_nXdown;
	void     (*m_pCallBackMoveRight)(void *, void *);
	void     (*m_pCallBackMoveLeft)(void *, void *);
	void Deploy();

	HBOOL m_bDrawButton;
	
	vector <HString> ItemStr;

};