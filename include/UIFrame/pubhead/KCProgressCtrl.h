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
    //设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
    void SetBkgndN(IReSurface* pSur);
    void SetBkgndN(const HString& pFileName);

    //滑动条前景图
    void SetBkgndA(IReSurface* pSur);
    void SetBkgndA(const HString& pFileName);

    void SetMinMax(HINT min, HINT max);

    void ClacPos();

    virtual void GetBackSufSize(HINT& x, HINT& y);

	void EnableShowProgress(HBOOL bEnable);

private:
    //常规背景图
    IReSurface* m_pBkgndN;
    HBOOL m_bBkgndNRes;

    //进度条图
    IReSurface* m_pBkgndA;
    HBOOL m_bBkgndARes;

    HINT m_Value;

    HINT m_Min;
    HINT m_Max;

    HINT m_pos;

	HBOOL m_bShowProgress;
};

#endif