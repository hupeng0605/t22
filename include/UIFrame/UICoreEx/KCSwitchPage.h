/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����:	KCSwitchPage.h
* ժ    Ҫ:	
*
* ��ǰ�汾:	1.0
* ��    ��:	              
* �������:	2010-02-01
*
* �޸���ʷ��
* [�޸�����]	[�޸�����] 		[�޸���]		[�޸�����]
*	1			2010-02-01    	                  	    ����
* 	
**/
#pragma once


#include "KCWindow.h"
#include "vector"

class CYPRESS_DLL_API HCSwitchPage : public HCBaseCtrl  
{
public:
	HCSwitchPage();
	virtual ~HCSwitchPage();


	//���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
	void SetBkgndN(IReSurface* pSurf);
	void SetBkgndN(const HString& pFileName);

	void ActiveRearPage();
	void AddRearPage();
	void CancelRearPage();
	
	// ҳ���л�
	HBOOL SwitchPage(HINT page);

	// ����ICON
	void SetIconSurface(HString& pSurfActivePath,HString& pSurfNormalPath, HString& pSurfRearPath);

	// ����ICON���
	void SetIconOffset(HINT nOffset);

	// ����ICON��ʼλ��
	void SetIconStartPos(HINT x, HINT y);

	void SetTotalPageNum(HINT pageNum);

	virtual void Draw(IReSurface* pSurface);


private:

	//���汳��ͼ
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;

	// ����ICONͼ
	IReSurface* m_pSurfActiveIcon;
	// ��ͨICONͼ
	IReSurface* m_pSurfNormalIcon;
	// ��̨ICONͼ;
	IReSurface* m_pSurfRearIcon;

	// ��ǰҳ
	HINT m_nCurPage;
	// ��ҳ��
	HINT m_nTotalPage;

	// ����ǰ̨����ҳ
	HINT m_nFrontActivePage;


	// �л�ҳ
	HINT m_nSwitchPage;
	// ICON֮��ƫ��
	HINT m_nIconOffset;
	// ICON��ʼλ��
	HINT m_xIconPos;
	HINT m_yIconPos;

	// �Ƿ񼤻��̨
	HBOOL m_bActiveRear;

};
