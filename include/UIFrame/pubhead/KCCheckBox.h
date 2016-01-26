/********************************************************************
    created:    2006/12/04
    created:    4:12:2006   11:28
    filename:   d:\code\try\newhmi\include\kccheckbox.h
    file path:  d:\code\try\newhmi\include
    file base:  kccheckbox
    file ext:   h
    author:          

    purpose:
*********************************************************************/


#if !defined(AFX_KCCHECKBOX_H__3440C27E_16CD_45DF_89A9_6B1B28C00008__INCLUDED_)
#define AFX_KCCHECKBOX_H__3440C27E_16CD_45DF_89A9_6B1B28C00008__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCButton.h"

class UICORE_DLL_API HCCheckBox : public HCButton
{
public:
    HCCheckBox();
    virtual ~HCCheckBox();

    //��Ϣ�������������඼Ҫ����
    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);

    virtual void SetCheck(HBOOL v);
    HBOOL GetCheck();

    virtual void GetBackSufSize(HINT& x, HINT& y);
	
	virtual void EnableAutoCheck(HBOOL bAutoCheck = TRUE);
protected:
	HBOOL m_bAutoCheck;//�Զ�ѡ�У���Ϊ��ʱ��������Զ�ѡ�У�������Ҫ����SetCheck�ӿ��ֶ�����ѡ��
    HBOOL m_bCheck;

};

class UICORE_DLL_API HCRadioBox : public HCCheckBox
{
public:
    HCRadioBox();
    ~HCRadioBox();

    //��Ϣ�������������඼Ҫ����
    void SetCheck(HBOOL v);
    HBOOL DoMessage(HMessage* msg);
    void SetGroupID(HINT id);
    HINT GetGroupID();

    virtual void GetBackSufSize(HINT& x, HINT& y);

protected:
    //���ñ����������ť
    void ReSetGroup();
    HINT  m_nGroupID;
};
#endif // !defined(AFX_KCCHECKBOX_H__3440C27E_16CD_45DF_89A9_6B1B28C00008__INCLUDED_)
