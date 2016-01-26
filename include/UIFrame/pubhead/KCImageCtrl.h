/********************************************************************
    created:    2006/12/18
    created:    18:12:2006   8:55
    filename:   d:\�����ĵ�\camellia��Ŀ\08prototype\camellianewhmi\hmi\base\include\kcimagectrl.h
    file path:  d:\�����ĵ�\camellia��Ŀ\08prototype\camellianewhmi\hmi\base\include
    file base:  kcimagectrl
    file ext:   h
    author:          

    purpose:    ͼ��(����)�ؼ�
*********************************************************************/
#if !defined(AFX_KCPROGRESSCTRL_H__IMAGECTRL__INCLUDED_)
#define AFX_KCPROGRESSCTRL_H__IMAGECTRL__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWnd.h"


class UICORE_DLL_API HCImageCtrl : public HCBaseCtrl
{
public:
    HCImageCtrl();
    ~HCImageCtrl();
    HBOOL Create(HINT x, HINT y, HINT w, HINT h);
    virtual void Draw(IReSurface* pSurface);
    HBOOL DoMessage(HMessage* msg);

    //��ǰ��ͼ��֡����
    void SetIndex(HINT v);
    HINT GetIndex();

    //����ֵ
    void SetStepWidth(HINT n);
    HINT GetStepWidth();

	void SetSetpHeigth(HINT n);

    //�ܳ���ֵ
    HDWORD GetTotalWidth();

    // ��֡��
    HDWORD GetCount();

    //���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
    void SetBkgndN(IReSurface* pSur);
    void SetBkgndN(const HString& pFileName);

    void SetTime(HINT ms);

    void Play();
    void Stop();

    void SetOpacity(HBYTE nTrans);
    // ����ͼƬ
    IReSurface* GetImgSurface();

    virtual void GetBackSufSize(HINT& x, HINT& y);

	void SetAlignStyle(HINT nAlign);

protected:
    HBOOL CheckPoint(HINT x, HINT y);

private:
	HINT	m_nAlign;
    //���汳��ͼ
    IReSurface* m_pBkgndN;
    HBOOL m_bBkgndNRes;
    //ͼ��ǰ�����λ��
    RECTANGLE m_rect;
    //������ʱ��
    HINT m_msTime;
    //����ֵ
    HINT m_nStep;

    HBOOL m_bPlay;

    //��ǰ����,0��ʼ
    HINT m_nIndex;

    HINT m_nBasetime;
};

#endif