/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCRippleImageCtrl.h 
* ժ    Ҫ:
*
* ��ǰ�汾: 1.0
* ��    ��:               
* �������: 2009-12-29
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1            2009-12-29                    			����
*   2			 2011-5-17		               			����SetInvertOnly���������Ƿ�ֻ����Ӱ�޲���
**/


#if !defined(AFX_KCPROGRESSCTRL_H__RIPPLEIMAGECTRL__INCLUDED_)
#define AFX_KCPROGRESSCTRL_H__RIPPLEIMAGECTRL__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWnd.h"


class CYPRESS_DLL_API HCRippleImageCtrl : public HCBaseCtrl  
{
public:
	HCRippleImageCtrl();
	~HCRippleImageCtrl();

	virtual void Draw(IReSurface* pSurface);
	HBOOL DoMessage(HMessage* msg);

	//���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
	void SetBkgndN(IReSurface* pSur);
	void SetBkgndN(const HString& pFileName);

	//����ÿ���ƶ�ʱ��ʱ����
	void SetMoveInOutTime(HINT ms);
	//�����ƶ��Ĵ���
	void SetMoveInOutNum(HINT num);
	//ͼƬ����ʱ�Ƿ����������Ƴ�
	void EnableMoveInOut(HBOOL bEnable);

	//����ͼƬ�Ĵ�С
	void SetImageSize(HINT width, HINT height);
	//����ˮ��ͼ��ĸ߶�
	void SetRippleImageHeight(HINT height);

	//����ˮ��ͼ��ĸ���ʱ��
	void SetRippleTime(HINT ms);
	//��ʼˮ������
	void Play();
	void Stop();

	// ����ͼƬ
	IReSurface* GetImgSurface();

	//add by zjz,2011-5-17,�����Ƿ�ֻ�е�Ӱ����
	//�����Ƿ�ֻ�е�Ӱ
	void SetInvertOnly(HBOOL bInvertOnly);
	//add end
	
private:
	//���汳��ͼ
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;

	//���뱳��ͼ
	IReSurface* m_pBkgndIn;
	HBOOL m_bBkgndInRes;

	//ͼƬ����ʱ�����Ƴ�
	HBOOL m_bCanMoveInOut;
	
	//��ǰ��״̬
	HBOOL m_bMoveInOut;
	HINT m_moveInOutIndex;//�ƶ����ڼ���
	HINT m_moveInOutBaseTime;//��׼ʱ��
	HINT m_moveInOutTime;//�ƶ��ļ��ʱ��
	HINT m_nMoveInOutNum;//�ܹ��ƶ��Ĵ���

	HINT m_imageWidth;
	HINT m_imageHeight;
	HINT m_rippleImageHeight;
	
	//������ʱ��
	HINT m_msTime;
	HBOOL m_bPlay;
	//ˮ�����ŵĵ�ǰ֡
	HINT m_nFrame;
	HINT m_nBasetime;

	//add by zjz,2011-5-17,�����Ƿ�ֻ�е�Ӱ����
	//�Ƿ�ֻ�е�Ӱ
	HBOOL m_bInvertOnly; //�Ƿ񴿵�Ӱ��Ϊtrueʱֻ�е�Ӱû�в���
	//add end

};

#endif