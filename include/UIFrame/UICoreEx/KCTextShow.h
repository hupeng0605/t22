/**
* Copyright (C) 2010�� 
* All rights reserved.
*
* �ļ�����: TEST.h
* ժ    Ҫ:
*
* ��ǰ�汾: 1.0
* ��    ��:               
* �������: 2010-4-20
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1           2010-4-20                              ����
*
**/
//#include "KCWindow.h"
#pragma once
#include "KHMIBaseHead.h"
#include <vector>

struct FontInfo
{
	HINT FontIndex;
	HINT FontWidth;
	HINT FontHight;
	RECOLOR FontColor;
};

class CYPRESS_DLL_API HCTextShow: public HCBaseCtrl
{
public:
	HCTextShow();
	~HCTextShow();

	HBOOL Create(HINT x,HINT y,HINT w,HINT h);
	HBOOL Create(HINT x, HINT y, HINT w, HINT h, HINT num);

	void SetNumTextIndex(HINT index);	// ���������ַ�����λ�ã�Ĭ��Ϊ0�������Time:00:11�������ó�1
	void SetText(const HCHAR* pTxt,HINT fontindex,HINT fontw,HINT fonth,RECOLOR color);
	void SetText( const HCHAR* pTxt, HINT fontindex);
	void SetText(const HCHAR* pTxt);
	void SetTextStyle(HWORD type);	// ���������Ҷ��룬Ĭ��Ϊ�����

	//���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
	//void SetBkgndN(IReSurface* pSur);
	//void SetBkgndN(const kn_string& pFileName);
	void DrawFrame(IReSurface* pSurface);
	void DrawOnSurface(IReSurface* pSurface, HINT x = 0, HINT y = 0);
	void Draw(IReSurface* pSurface);

	void SetTextColorA(int r, int g , int b);

	IReSurface* GetFontSurf(const HCHAR* str);
	void CreatSur(HINT fontw,HINT fonth);

	HBOOL DoMessage(HMessage* msg);

	//void EnableMoveInOut(kn_bool bEnable);
	void BeginAnimation();	// ������ʼ��λ�ã�������SetText֮ǰ����
	void EndAnimation();	// ����������λ�ã�������SetText֮�����
	void SetAnimationDulration(HFLOAT second);	// ���ö�����ʱ��
	HFLOAT AnimationFunction(HINT frame);

private:
	vector <HString> m_strevc;
	vector <FontInfo> m_fontinfoevc;
	//kn_int m_nStrNum;
	HINT m_iFontWidth;	// ��������ĳߴ�
	HINT m_iFontHeight;
	HUINT m_nNumTextIndex;	// �����ַ�������λ��
	map<HString,IReSurface*> m_FontCacheSurfMap;

	
	HWORD m_TextStyle;	// ������ʽ

	// ����
	HBOOL m_bEnableRollUp;

	HFLOAT m_fRollOffset;	// ÿ�ι�����ƫ����
	HFLOAT m_fRollCount;	// ��������
	HFLOAT m_fA, m_fB, m_fH;

	HINT m_iRollBaseTime;
	IReSurface *m_pSurfaceOld;
	IReSurface *m_pSurfaceNew;
};