/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����:	KCSwitchList.h
* ժ    Ҫ:	
*
* ��ǰ�汾:	1.0
* ��    ��:	              
* �������:	2010-01-29
*
* �޸���ʷ��
* [�޸�����]	[�޸�����] 		[�޸���]		[�޸�����]
*	1			2010-01-29    	                  	    ����
* 	
**/
#pragma once


#include "KCWindow.h"
#include "vector"

typedef vector <IReSurface*> SURF_ITEM_VEC;
typedef void (*CLICKCALLBACK)(void* , HINT, HBOOL,HBOOL);

class CYPRESS_DLL_API HCSwitchList : public HCBaseCtrl  
{
public:
	HCSwitchList();
	virtual ~HCSwitchList();


	//���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
	void SetBkgndN(IReSurface* pSurf);
	void SetBkgndN(const HString& pFileName);

	// ����ÿҳ��ʾIcon��
	void SetPrePageIcon(HINT nNum);

	// ���ó���״̬��Icon����
	void SetNormalSurf(SURF_ITEM_VEC vecSufN);

	// ���ü���״̬��Icon����
	void SetActiveSurf(SURF_ITEM_VEC vecSufA);
	
	// ��ž۽�״̬��Icon����
	void SetFocusSurf(SURF_ITEM_VEC vecSufF);
	
	// ���ü���״̬��ͼƬ
	void Reset();

	void ReturnHomePage();
	
	//�����ص�
	void SetCallBackClick(CLICKCALLBACK pClickCallBack, void* );

	HBOOL DoMessage(HMessage* msg);
	void Draw(IReSurface* pSurface);

private:
	HINT GetIndexByY(HINT y);

private:

	//���汳��ͼ
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;

	// ÿҳ��ʾICON��Ŀ
	HINT m_nPrePageIcon;
	
	// ��ų���״̬��Icon����
	SURF_ITEM_VEC m_vecSufNormal;

	// ��ż���״̬��Icon����
	SURF_ITEM_VEC m_vecSufActive;
	
	// ��ž۽�״̬��Icon����
	SURF_ITEM_VEC m_vecSufFocus;

	// ��ǰ������
	HINT m_nActiveIndex;
	// ��ǰ�۽���
	HINT m_nFocusIndex;
	// 
	HINT m_nLastActiveIndex;
	
	CLICKCALLBACK m_pClickCallBack;

	HBOOL m_bHomePage;// �Ƿ�Ϊ��ҳ��־λ
	HBOOL m_bSwitch;// �Ƿ����л���ť��־λ
	HBOOL m_bCancelActive;
//	kn_bool m_bReset;// �Ƿ�����ָ��λ��ͼƬ��־λ

	HINT m_nMouseDownIndex;
	HINT m_nMouseUpIndex;
	HBOOL m_bEnableCallBack;

};
