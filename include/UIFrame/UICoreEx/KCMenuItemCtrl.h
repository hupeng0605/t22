/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCMenuItemCtrl.cpp
* ժ    Ҫ:
*
* ��ǰ�汾: 1.0
* ��    ��:               
* �������: 2009-12-29
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1            2010-1-29                                ����
*
**/

#pragma once

#include "KCwnd.h"
#include "RenderingEngine.h"

typedef struct _sBorderSurf
{
    IReSurface* pSurf;  //�߿�ͼƬ
    HBOOL bOutRes;
    HINT x;           //����ؼ����Ͻǵ�X�����
    HINT y;           //����ؼ����Ͻǵ�Y�����

    _sBorderSurf()
    {
        pSurf = NULL;
        x = 0;
        y = 0;
        bOutRes = TRUE;
    }

    ~_sBorderSurf()
    {
		Release();
    }

    void Release()
    {
        if (bOutRes == FALSE)
        {
            SAFE_DELETE(pSurf);
        }
    }

} sBorderSurf;

enum eBorderDirection
{
    CursorBorderLeft,
    CursorBorderRight,
    CursorBorderTop,
    CursorBorderBottom,
    BorderLeft,
    BorderRight,
    BorderTop,
    BorderBottom,
};

class CYPRESS_DLL_API HCMenuItemCtrl : public HCBaseCtrl
{
public:
    HCMenuItemCtrl();
    ~HCMenuItemCtrl();
public:

    //***************************************************************
    // *  ��������:
    // *  ��ڲ���: pSurf��ͼƬ
    // *            stepWidth��ÿ֡���
    // *            height��ͼƬ�߶�
    // *            time��֡����ʱ��
    // *  ���ڲ���:
    // *  �� �� ֵ:
    //***************************************************************
	void SetImage(const HCHAR* pFormat, HINT pictureNum, HINT stepWidth, HINT height, HINT time );
    // ����ͼƬ��ʾ�Ŀ�Ⱥ͸߶�
    void GetImageShowSize(HINT& width, HINT& height);
    // ����ͼƬ�����Ͻ�����
    void SetImagePos(HINT x, HINT y);
    // ��������ͼ��������ͼʱ�Զ��滻��ͼ�����ʾ
    void SetThumbNail(IReSurface* pSurf);

    void SetBorderSurf(IReSurface* pSurf, HINT x, HINT y, eBorderDirection direction);
    void SetBorderSurf(const HCHAR* path, HINT x, HINT y, eBorderDirection direction);
	void SetPressedShaderSurf(IReSurface* pSurf);

	void SetLongPressTime(HINT time);
    //�����ı�surface
    void CreateTextSurf();
	void CreateDesableTextSurf();
    //����������Ӱ
    void SetTextShaderSurf(IReSurface* pSurf);
    //�������ֵ�����λ��
    void SetTextPos(HINT x, HINT y);

    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);
	//����������Ӱ
	void SetChageAshSur(IReSurface *pSur);
	//�����Ƿ���ʾ��Ӱ
	void SetChageAsh(HBOOL bIN);
    //��ť���»ص�
    void SetCallBackDown(void (*callback)(void*, void*), void*);
    //��ť����ص�
    void SetCallBackUp(void (*callback)(void*, void*), void*);
    //������Ϣ
    void SetCallBackLongPress(void (*callback)(void*, void*), void*);

	HINT GetLangID(void)
	{
		return m_nLangID;
	}
	void SetLangID(HINT a_nLangID)
	{
		m_nLangID = a_nLangID;
	}

	void OnFocus();

	void EnableImagePlay(HBOOL bEnable);

	void ReleaseImageSurf();

	void EnableDesableState(HBOOL bEnable);
	bool IsDesableState();

	void EnableCurSource(HBOOL bEnable);
	void SetCurSourceSurf(const HCHAR* pFilePath);

	//������ʾ����
	void SetText(HString strText);
	void SetTextStyle(HWORD textStyle);
	void SetTextColor(int r, int g , int b);
	void SetTextColor(RECOLOR color);
	void SetTextColorD(int r, int g , int b);
	void SetTextColorD(RECOLOR color);

	HString GetText(void);
private:
    HINT  m_nLangID;

    sBorderSurf m_CursorLeftSurf;
    sBorderSurf m_CursorRightSurf;
    sBorderSurf m_CursorTopSurf;
    sBorderSurf m_CursorBottomSurf;

    //�߿�
    sBorderSurf m_LeftSurf;
    sBorderSurf m_RightSurf;
    sBorderSurf m_TopSurf;
    sBorderSurf m_BottomSurf;
	//PressedShader
	IReSurface* m_pPressedShaderSurf;

	//�����С ��ɫ
	HWORD m_TextStyle;
	HString m_strTxt;
	RECOLOR   m_colorDesableText;
	RECOLOR   m_colorText;
    //����λ��,����
    HINT m_nTextPosX;
    HINT m_nTextPosY;
    IReSurface* m_pTextShaderSurf;
    IReSurface* m_pTextSurf;
	IReSurface* m_pDesableTextSurf;
    //ͼƬ
	vector<IReSurface*> m_pImageSurfVec;
    HINT m_nImageStepWidth;
    HINT m_nImageHeight;
    HINT m_nRefreshTime;//֡����ʱ��
    HINT m_nRefreshBaseTime;//��׼ʱ��
    HINT m_nIndex;//��ʾ���ڼ�֡
	HString m_strFormat;

    HBOOL m_bCanRefresh;//�ܹ��л�֡

    HINT m_nImagePosX;
    HINT m_nImagePosY;

	HBOOL m_bEnableImagePlay;
    //����ͼ
    IReSurface* m_pThumbNailSurf;
	IReSurface* m_pChangeAshSur;
	HBOOL m_bChagerAsh;
    //��ť����ʱ�ص���������,Ҫ������ָ��
    void (*m_pCallBackDown)(void *, void *);
    //��ť����ʱ�ص���������,Ҫ������ָ��
    void (*m_pCallBackUp)(void *, void *);

    // ��곤����Ϣ
    void (*m_pCallBackLongPress)(void *, void *);


    HINT m_longPressTime;
    HINT m_baseTime;
    HBOOL m_bHaveExecute;
    HBOOL m_bOutOfRange;

	HBOOL m_bDesable;

	HBOOL m_bCurSource;
	IReSurface* m_pCurSourceSurf;

};