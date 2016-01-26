/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����:	KC3DImageCtrl.h
* ժ    Ҫ:	
*
* ��ǰ�汾:	1.0
* ��    ��:	 
* �������:	2010-01-06
*
* �޸���ʷ��
* [�޸�����]	[�޸�����] 		[�޸���]		[�޸�����]
*	1					2010-01-06    	     	����
* 	
**/


#pragma once

#include "KCWnd.h"

#define MAX_IMG_NUM  (HINT)6// �����ʾͼƬ����

class CYPRESS_DLL_API HC3DImageCtrl: public HCBaseCtrl
{
public:
	HC3DImageCtrl(void);
	~HC3DImageCtrl(void);

	virtual HBOOL DoMessage(HMessage* msg);
	virtual void Draw(IReSurface* pSurface);
	
	// ���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
	void SetBkgndN(IN IReSurface* pSur);
	void SetBkgndN(IN const HString& pFileName);
	// ����Ԥ����ͼƬ
	void SetImages(IN const vector<HString>& images, IN HINT nStartIndex = 0);

	// ����ͼƬ�л��ı�ص�����
	inline void SetCallBackIndexChange(void (*callback)(void*, void*), void* pThis)
	{
		m_pCallBackIndexChange = callback;
		m_pThisIndexChange = pThis;
	}
protected:
	void DrawItem(IReSurface* pSurface, HINT nIndex, HINT cnt);
	void MoveToRight();
	void MoveToLeft();

	// ת������͸�ӵ�Ϊԭ�������ϵ
	POINT GetCoor(POINT point);
	// ת������(0,0)Ϊԭ�������ϵ
	POINT RecCoor(POINT point);
	// ��ȡ���һ���ǰ�軭�����߾�֮��ľ���
	HINT GetDistance(HINT first, HINT diff, HINT cnt);
	

private:
	HBOOL m_bImageNFromFile;// ����ͼƬ�Ƿ��������ļ�
	IReSurface* m_pImageN;// ����ͼƬ
	// �ص���������,Ҫ������ָ��
	void (*m_pCallBackIndexChange)(void *, void *);
	void* m_pThisIndexChange;

private:
	// 
	HINT m_nMouseX;
	HINT m_nMouseY;
	HBOOL m_bMouseDown;

	//kn_int m_dis_x;
	vector <IReSurface*> m_vImgSurface;

	// add 09.12.13 jhw
	HINT m_maxDisplayIdx;
	// end
	HINT m_nCurIndex;

protected:
	//kn_float x_div_gap;
	//kn_int z_div_gap;
protected:
	HINT div_cnt;
	// �ƶ�����
	HINT m_direction;
	// Ԥ��ͼ
	vector<HString> m_vImages;

	// add 09.12.15 jhw
	// ����б��
	// ���½�
	HFLOAT m_slopeA;
	// ���Ͻ�
	HFLOAT m_slopeB;
	// ���Ͻ�
	HFLOAT m_slopeC;
	// ���½�
	HFLOAT m_slopeD;
	//�е�б��
	HFLOAT m_slopeBottom;
	HFLOAT m_slopeTop;
	// ��б��
	HFLOAT m_slopeAD;
	HFLOAT m_slopeBC;
	// BC,AD������Y�ύ��
	HFLOAT m_yCutBC;
	// ��ײ�ͼƬ����
	POINT m_StartA;
	POINT m_StartB;
	POINT m_StartC;
	POINT m_StartD;
	POINT m_StartTop;
	POINT m_StartBottom;
	// ���ͼƬ����
	POINT m_EndA;
	POINT m_EndB;
	POINT m_EndC;
	POINT m_EndD;
};
