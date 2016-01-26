/********************************************************************
created:    2009/12/03
created:    3:12:2009   13:43
filename:   KCTunePopup.h
file path:
file base:  KCTunePopup
file ext:   h
author:       

purpose:
*********************************************************************/
#pragma  once

#include "kcgroupctrl.h"
#include "hmienginecom.h"
#include <PubHead.h>
#include "kdialogbase.h"
#include "kcwindow.h"
#include "Configure.h"


class CYPRESS_DLL_API HCTunePopup :
    public HCGroupCtrl
{
public:
    HCTunePopup(void);
    ~HCTunePopup(void);

public:
    void Draw(IReSurface* pSurface);
    //��Ϣ������
    HBOOL DoMessage(HMessage* msg);

public:
    HBOOL Create(HINT nLeftValue, HINT nRightValue, HINT nCurValue, HINT x = 69, HINT y = 104, HINT w = 663, HINT h = 327);
    void SetLeftValue(HINT nLeftValue);
    void SetRightValue(HINT nRightValue);
    void SetCurValue(HINT nCurValue);
    HINT GetCurValue(void);
    void SetTunePopupTitle(HString strTitle);
    void SetTunePopupTitle(const HCHAR* pStrTitle);
    void SetPreCtrl(HCBaseCtrl *pPrectrl);

    void ShowPopup(IReSurface* pFatherWndSurface);

    //����ƶ���Ϣ
    void SetCallBackMouseMove(void (*callback)(void*, void*), void*);
    //����ƶ���Ϣ
    void SetCallBackOnOK(void (*callback)(void*, void*), void*);
    //����ƶ���Ϣ
    void SetCallBackOnCancel(void (*callback)(void*, void*), void*);

    void InvalidateCtrl(HCBaseCtrl* pBaseCtrl);

    void InvalidateRect(kn_rect& rect);

    void EnableUpdateRect(HBOOL bEnable);

    HBOOL IsCtrlInGroup(HCBaseCtrl* pBaseCtrl);

private:
    HBOOL IsCtrlInGroup(HCBaseCtrl* pBaseCtrl, vector<HCBaseCtrl*>& ctrlList);

    static void OnSlider(void* p, void* pParam);
    void OnSlider(void);

    static void OnMouseMove(void* p, void* pParam);
    void OnMouseMove(void);

    static void OnBtnOK(void* p, void* pParam);
    void OnBtnOK(void);

    static void OnBtnCancel(void* p, void* pParam);
    void OnBtnCancel(void);

    HString Int2Str(HINT a_nVal);
private:
    HCBaseCtrl* m_pPreCtrl;
    //kn_string m_strTitle;
    HINT      m_nLeftValue;
    HINT      m_nRightValue;
    HINT      m_nCurValue;

    HString   m_strResPath;
    HCTextCtrl  *m_pTitleTxt;
    HCTextCtrl  *m_pValueTxt;
    HCTextCtrl  *m_pLeftValueTxt;
    HCTextCtrl  *m_pRightValueTxt;
    HCSlideCtrl *m_pSlideCtrl;
    //KCWindow  *m_pFatherWnd;
    IReSurface  *m_pSurface;
    //��ť 0:ȷ�� 1:ȡ��
    HCButton    *m_pBtnOK;
    HCButton    *m_pBtnCancel;
    // ����ƶ���Ӧ��Ϣ
    void (*m_pCallBackMouseMove)(void *, void *);
    // ȷ����ťup��Ӧ��Ϣ
    void (*m_pCallBackOnOK)(void *, void *);
    // ȡ����ťup��Ӧ��Ϣ
    void (*m_pCallBackOnCancel)(void *, void *);
};
