
/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����:	KCShowNumSlide.h
* ժ    Ҫ:	
*
* ��ǰ�汾:	1.0
* ��    ��:	              
* �������:	2010-01-28
*
* �޸���ʷ��
* [�޸�����]	[�޸�����] 		[�޸���]		[�޸�����]
*	1					2010-01-28    	                  	����
* 	2				2010-11-4	Ԭ����			������ʼ���Ƿ���ʾ�ӿ�
**/
#pragma once
#include "KCWnd.h"
#include "Configure.h"
//***************************************************************
// *  ��������:	�����б�
// *  ��������:	              
// *  �ա�����:	2010-01-28
//***************************************************************
class CYPRESS_DLL_API HCShowNumSlide : public HCBaseCtrl
{
public:
	HCShowNumSlide();
	~HCShowNumSlide();
	//
	HBOOL Create(HINT x, HINT y, HINT w, HINT h);
	//���õ�ǰƵ��
	void SetValue(HFLOAT num);
	void SetValue(HString sFreq);
	//��������Ƶ�ʵļ��
	void SetSpaceBetweenNumber(HFLOAT num);
	//���õ�ǰƵ����ʾ����
	void SetCurFrequecyId(const HCHAR* pTxt);
	//���ñ���
	void SetBkgndN(IReSurface* pSurf);
	//���ñ���
	void SetBkgndN(const HString& pFileName);
	//����С����λ��
	void SetDecDig(HBOOL Index);
	//��õ�ǰƵ��
	HFLOAT GetMidFrequecy();
	void SetBound(IN HFLOAT nMin, IN HFLOAT nMax);
	void SetCallBackValueChange(void (*callback)(void*, void*), void* pThis);
	void SetCallBackMoveDown(void (*callback)(void*, void*), void* pThis);
	void SetCallBackMoveUp(void (*callback)(void*, void*), void* pThis);
	//��ʼ��ʱ�Ƿ���ʾ��ֵ
	void SetShowNum(HBOOL IsShowNum);

	//���ӵ���ص�
	void SetCallBackMouseClick(void (*callback)(void*,void*),void* pThis);

	void StarTran(HBOOL bbool);
	void ChengedInt(HINT x);
	void SetStopFreq(HString freq,HBOOL bstop);
	void SetShowNumCanTran(HBOOL bBool);
	void SetShowNumCanTran();
	void SetRadioFile(HINT RadioFile);
protected:
private:
	//����ת�����ַ���
	HString DiStillIntPart(HINT num);
	virtual void Draw(IReSurface* pSurface);
	//��Ϣ������
	HBOOL DoMessage(HMessage* msg);
	HString DiStillDecPart(HINT num);
	void JudgeDecPart(HINT &num);
	HBOOL JudgeDecPartMoveNumber(HINT &num);
	void FormatFre(HFLOAT &ftr);

	IReSurface* GetFontSurf(HString& str);
private:

	IReSurface *m_pUnitText; 
	IReSurface *m_pPointSur;
	HBOOL m_bMoveHead;//TrueΪ�������£�FALSEΪ��������
	HBOOL m_bBkgndNRes;//�Ƿ���ڱ���
	HBOOL m_bIntCanMoveInOut; //�Ƿ�����ƶ�
	HBOOL m_bDecCanMoveInOut;
	HBOOL m_bIntMoveInOut;//�����ƶ��ı�־λ
	HBOOL m_bDecMoveInOut; //С���ƶ��ı�־λ
	HBOOL m_bDecDig;//�Ƿ���С��

	IReSurface *m_pBkgndN;//����ͼƬ
	IReSurface *m_pSeekUpSur;
	IReSurface *m_pSeekDownSur;
	HFLOAT m_fMidValue; //��ǰ��Ƶ��

	HINT m_nSpaceNumber; //���
	HINT m_nMargin;//�м��

	kn_rect m_RectMiddle; //��������
	HINT m_yoffset; //ƫ��
	HINT m_nBaseTime; //����ʱ��

	HINT m_moveInOutTime; //�ƶ���ʱ����
	HINT m_nMoveNum;//�ƶ�����
	HINT m_nDownpos;//���µ�λ��
	HBOOL m_bIntMouseMove;//�Ƿ��ƶ�
	HBOOL m_bDecMouseMove;

	HINT m_nFontSizeY; //����Ĵ�С 
	HINT m_nFontSizeX;// 
	HINT m_nIntNumber;//��¼��������
	HINT m_nDecNumber;//��¼С������
	HINT m_nTar;
	HFLOAT m_fMaxValue;
	HFLOAT m_fMinValue;
	HBOOL m_bCanBeMove;
	// �ص���������,Ҫ������ָ��
	void (*m_pCallBackValueChange)(void *, void *);
	void (*m_pCallBackMoveDown)(void *,void *);
	void (*m_pCallBackMoveUp)(void *,void *);

	//����ص�
	void (*m_pCallBackMouseClick)(void *,void *);

	HString GetFreqStr();
	void CriticlDeal();

	void* m_pThisValueChange;
	HBOOL m_btran;
	IReSurface *m_pBKSurUp; //����ͼƬ
	IReSurface *m_pBKSurDown;
	HBOOL m_bstop;
	HString m_fStopFreq;
	HBOOL m_bStarMove;
	HINT m_nStarTime;
	HBOOL m_bmove;
	HBOOL m_bCanTran;//�������ֻ����Ƿ������Ǩ��
	map<HString,IReSurface*> m_FontCacheSurfMap;//�ַ���
	HString m_nMaxIntNum;//�������
	HString m_nMinIntNum;//��С����
	HString m_nMaxDecNum;//���С��
	HString m_nMinDecNum;//��СС��
	HINT m_nRadioKind;//���Radio������Ϊ���ʱ����US Ϊһ��ʱ����EU
	HBOOL m_bIsShowNum;//��ʼ��ʱ�Ƿ���ʾ��ֵ
};
