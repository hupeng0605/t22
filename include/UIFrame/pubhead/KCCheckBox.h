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

    //消息处理函数，各子类都要重载
    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);

    virtual void SetCheck(HBOOL v);
    HBOOL GetCheck();

    virtual void GetBackSufSize(HINT& x, HINT& y);
	
	virtual void EnableAutoCheck(HBOOL bAutoCheck = TRUE);
protected:
	HBOOL m_bAutoCheck;//自动选中，当为真时，鼠标点击自动选中，否则，需要调用SetCheck接口手动设置选中
    HBOOL m_bCheck;

};

class UICORE_DLL_API HCRadioBox : public HCCheckBox
{
public:
    HCRadioBox();
    ~HCRadioBox();

    //消息处理函数，各子类都要重载
    void SetCheck(HBOOL v);
    HBOOL DoMessage(HMessage* msg);
    void SetGroupID(HINT id);
    HINT GetGroupID();

    virtual void GetBackSufSize(HINT& x, HINT& y);

protected:
    //设置编组的其它按钮
    void ReSetGroup();
    HINT  m_nGroupID;
};
#endif // !defined(AFX_KCCHECKBOX_H__3440C27E_16CD_45DF_89A9_6B1B28C00008__INCLUDED_)
