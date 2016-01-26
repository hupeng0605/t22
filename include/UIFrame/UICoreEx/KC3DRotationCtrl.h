/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KC3DRotationCtrl.h 
* ժ    Ҫ:
*
* ��ǰ�汾: 1.0
* ��    ��:               
* �������: 2010-04-21
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1           2010-04-21                   			����
*
**/


#if !defined(AFX_KC3DROTATIONCTRL_H__RIPPLEIMAGECTRL__INCLUDED_)
#define AFX_KC3DROTATIONCTRL_H__ROTATIONCTRL__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWnd.h"
#include "KC3DWorld.h"

// ��ת����
enum RotateDirect
{
	eNull = 0,
	eRight,
	eLeft
};

class CYPRESS_DLL_API HC3DRotationCtrl : public HCBaseCtrl  
{
public:
	HC3DRotationCtrl();
	~HC3DRotationCtrl();

	virtual void Draw(IReSurface* pSurface);
	HBOOL DoMessage(HMessage* msg);

	//���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
	void SetBkgndN(IReSurface* pSur,RotateDirect eRotateDirect = eNull);
	void SetBkgndN(const HString& pFileName,RotateDirect eRotateDirect = eNull);
	//����ͼƬ�Ĵ�С
	void SetImageSize(HINT width, HINT height);
	// ����ͼƬ
	IReSurface* GetImgSurface();

	// ����3D��ת��ز���(�����ת����)
	void Set3DAttribute();
	// ������ת���ʱ��
	void SetRotateTime(HINT nmsTime);
	// ��תSurface
	void RotateSurface(IReSurface* pSurf);

	HINT RegularAngle(HINT angle);
private:
	//���汳��ͼ
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;

	IReSurface* m_pBkgndNext;
	HBOOL m_bBkgndNextRes;

	// ͼƬ��͸�
	HINT m_imageWidth;
	HINT m_imageHeight;
	//
	HC3DWorld m_3dWorld;
	// ��׼ʱ��
	HINT m_nBasetime;
	// ��ת���ʱ��
	HINT m_nmsTime;
	// ��ת�Ƕ�
	HINT m_nAngle;
	// ��ת����
	RotateDirect m_eRotateDirect;



	HBOOL m_bRotateFinish;
	
};
#endif