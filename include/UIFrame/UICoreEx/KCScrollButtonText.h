/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����:	KCScrollTextButton.h
* ժ    Ҫ:	
*
* ��ǰ�汾:	1.0
* ��    ��:	              
* �������:	2010-01-28
*
* �޸���ʷ��
* [�޸�����]	[�޸�����]		[�޸���]	[�޸�����]
*	1			2010-01-28    	              		����
* 	2			2010-02-26                    		���������ֱ��..����������
* 	3			2010-12-06      ����		�Ż�SetText����
*	4			2011-02-11		Ԭ����		�޸ĳ���������ʾ����
*	5			2011-10-21		              		������ֹ������
**/

#pragma once

#include "KCWnd.h"
#include "KCScrollTextCtrl.h"
struct kn_StartPoint
{
	HINT x;
	HINT y;
};
class CYPRESS_DLL_API HCScrollButtonText: public HCBaseCtrl
{
public:
	HCScrollButtonText(void);
	~HCScrollButtonText(void);
	virtual void Draw(IReSurface* pSurface);
	virtual HBOOL Create(HINT x, HINT y, HINT w, HINT h);

	void GetCurDrawPos( HINT textX, HINT x, HINT &xOffset, HINT &xTar, HINT textY, HINT y, HINT &yOffset, HINT &yTar );
	HBOOL DoMessage(HMessage* msg);

	//���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
	void SetBkgndN(IReSurface* pSur);
	void SetBkgndN(const HString& pFileName);

	void SetBkgndA(IReSurface* pSur);
	void SetBkgndA(const HString& pFileName);  
	// �������ֵ���ʼλ��
	void SetTextPos(kn_StartPoint pos);
	//�����ı���ʽ
	void SetTextStyle(eTextStyle style);
	//�����ı����ᴥ������Ч��
	void SetText(const HCHAR *str);
	//�����ı�,�ᴥ������Ч��
	void SetText(HCHAR *str,HINT x , HINT y);
	//�õ���ǰ���ı�
	HString GetText();
	void SetMoveInOutMode(eMoveInOutMode mode);
	//����ÿ���ƶ�ʱ��ʱ����
	void SetMoveInOutTime(HINT ms);
	//�����ƶ��Ĵ���
	void SetMoveInOutNum(HINT num);
	//ͼƬ����ʱ�Ƿ����������Ƴ�
	void EnableMoveInOut(HBOOL bEnable);
	//���ֳ����Ƿ������Զ������Լ�������Ȧ��
	void EnableAutoRoll(HBOOL bAuto , HINT RingNumber);
	//�ж��Ƿ��ڹ���
	HBOOL ISAutoRoll();
	// �Ƿ��������޹���
	void EnableInfinityRoll(HBOOL bInfinityRoll);

	void SetCallBackAutoRoll(void (*callback)(void*, void*), void* pThis);

	//�����Ƿ񳬳������ʾ
	void SetIsDot(HBOOL IsDot);
	//���ô�ֱƫ����
	void SetYPos(HINT pos);
	// ���ﲿ��
	HINT GetLangID(void)
	{
		return m_nLangID;
	}
	void SetLangID(HINT a_nLangID)
	{
		m_nLangID = a_nLangID;
	}

	//�������ֹ����Ŀ��
	void SetRollWidth(HINT nWidth);
private:
	HINT m_nLangID;
	//���ص�ǰ�ı���λ��
	void GetCurTextPos(HINT& x, HINT& y);

	void GetNextTextPos(HINT& x, HINT& y);
	//���ع���ʱ�ı���λ��
	void GetCurTextScrollPos(HINT&x, HINT& y);
	// ��곤����Ϣ
	void (*m_pCallBackLongPress)(void *, void *);
	void (*m_pCallBackAutoRoll)(void *, void *);
	void GetNextTextScrollPos(HINT&x, HINT& y);

	void TruncText(HBOOL* bRoll, HINT* ii);
	HINT m_longPressTime;
	HINT m_baseTime;
private:
	//���汳��ͼ
	IReSurface* m_pBkgndN;
	IReSurface *m_pBkgndA;
	HBOOL m_bBkgndNRes; 
	HBOOL m_bEnableAutoRoll;//�Ƿ��Լ��ƶ�
	HINT  m_nSetRollNumber;//�����Զ�������Ȧ��
	HINT  m_nCurRollNumber;//��ǰ�ƶ���Ȧ��

	HString m_text;//�ı�
	eTextStyle m_textStyle;
	eMoveInOutMode m_moveInOutMode;
	//���뱳��ͼ
	IReSurface* m_curTextSurf;
	IReSurface* m_inTextSurf;
	IReSurface* m_pRollTextSurf;
	HBOOL m_bRollFlag;
	HINT m_nRollIndex;
	HINT m_nSecondRollIndex;
	HBOOL m_bSecondRoll;
	//ͼƬ����ʱ�����Ƴ�
	HBOOL m_bCanMoveInOut;
	// �����λ��
	kn_StartPoint m_point;
	//��ǰ��״̬
	HBOOL m_bMoveInOut;
	HINT m_moveInOutIndex;//�ƶ����ڼ���
	HBOOL m_bHaveExecute; 
	HINT m_moveInOutBaseTime;//��׼ʱ��
	HINT m_moveInOutTime;//�ƶ��ļ��ʱ��
	HINT m_nMoveInOutNum;//�ܹ��ƶ��Ĵ���
	HBOOL m_bRoll;
	// ���޹�����־λ
	HBOOL m_bInfinityRoll;

	HBOOL m_bRedraw;	// �Ƿ���Ҫ�ػ�����
	//�����Ƿ񳬳������ʾ
	HBOOL m_bIsDot;
	//����
	HINT m_nYPos;

	//�������ֹ����Ŀ��
	HINT m_nRollWidth;
};
