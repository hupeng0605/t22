#if !defined(AFX_KCPROGRESSCTRL_H__E8783179_BE3E_455F_A6EC_377F43DCFCF2__INCLUDED_)
#define AFX_KCPROGRESSCTRL_H__E8783179_BE3E_455F_A6EC_377F43DCFCF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWnd.h"
#include "KCWindow.h"

class UICORE_DLL_API HCProgressCtrl : public HCBaseCtrl
{
public:
    HCProgressCtrl();
    ~HCProgressCtrl();
    HBOOL Create(HINT x, HINT y, HINT w, HINT h);
    virtual void Draw(IReSurface* pSurface);
    HINT GetValue();
    void SetValue(HINT v);
    HBOOL DoMessage(HMessage* msg);
	HINT GetMax();
	HINT GetMin();
    //���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
    void SetBkgndN(IReSurface* pSur);
    void SetBkgndN(const HString& pFileName);

    //������ǰ��ͼ
    void SetBkgndA(IReSurface* pSur);
    void SetBkgndA(const HString& pFileName);

    void SetMinMax(HINT min, HINT max);

    void ClacPos();

    virtual void GetBackSufSize(HINT& x, HINT& y);

	void EnableShowProgress(HBOOL bEnable);

private:
    //���汳��ͼ
    IReSurface* m_pBkgndN;
    HBOOL m_bBkgndNRes;

    //������ͼ
    IReSurface* m_pBkgndA;
    HBOOL m_bBkgndARes;

    HINT m_Value;

    HINT m_Min;
    HINT m_Max;

    HINT m_pos;

	HBOOL m_bShowProgress;
};

#endif