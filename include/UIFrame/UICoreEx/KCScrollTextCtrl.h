/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCScrollTextCtrl.h 
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

#include "KCWnd.h"

//�ƶ���ʽ
enum eMoveInOutMode
{
	LeftToRight,
	RightToLeft,
	BottomToTop,
	TopToBottom,
};

//����λ����ʽ
enum eTextStyle
{
	Left,
	LeftTop, 
	LeftBottom,
	Right,
	RightTop,
	RightBottom,
	Center,//���Ҿ��У����¾���
};


class CYPRESS_DLL_API HCScrollTextCtrl : public HCBaseCtrl  
{
public:
	HCScrollTextCtrl();
	~HCScrollTextCtrl();

	virtual void Draw(IReSurface* pSurface);
	HBOOL DoMessage(HMessage* msg);

	//���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
	void SetBkgndN(IReSurface* pSur);
	void SetBkgndN(const HString& pFileName);

	//�����ı���ʽ
	void SetTextStyle(eTextStyle style);
	//�����ı����ᴥ������Ч��
	void SetText(const HCHAR* str);
	HString GetText();

	void SetMoveInOutMode(eMoveInOutMode mode);
	//����ÿ���ƶ�ʱ��ʱ����
	void SetMoveInOutTime(HINT ms);
	//�����ƶ��Ĵ���
	void SetMoveInOutNum(HINT num);
	//ͼƬ����ʱ�Ƿ����������Ƴ�
	void EnableMoveInOut(HBOOL bEnable);

private:
	//���ص�ǰ�ı���λ��
	void GetTextPos(HINT& x, HINT& y);
	//���ع���ʱ�ı���λ��
	void GetTextScrollPos(HINT&x, HINT& y);
	
private:
	//���汳��ͼ
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;

	HString m_text;//�ı�
	eTextStyle m_textStyle;
	eMoveInOutMode m_moveInOutMode;

	//���뱳��ͼ
	IReSurface* m_curTextSurf;
	IReSurface* m_inTextSurf;

	//ͼƬ����ʱ�����Ƴ�
	HBOOL m_bCanMoveInOut;
	
	//��ǰ��״̬
	HBOOL m_bMoveInOut;
	HINT m_moveInOutIndex;//�ƶ����ڼ���

	HINT m_moveInOutBaseTime;//��׼ʱ��
	HINT m_moveInOutTime;//�ƶ��ļ��ʱ��
	HINT m_nMoveInOutNum;//�ܹ��ƶ��Ĵ���
	
};