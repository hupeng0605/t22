/********************************************************************
    created:    2006/12/18
    created:    18:12:2006   8:55
    filename:   d:\工作文档\camellia项目\08prototype\camellianewhmi\hmi\base\include\kcimagectrl.h
    file path:  d:\工作文档\camellia项目\08prototype\camellianewhmi\hmi\base\include
    file base:  kcimagectrl
    file ext:   h
    author:          

    purpose:    图像(动画)控件
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

    //当前的图像帧索引
    void SetIndex(HINT v);
    HINT GetIndex();

    //步长值
    void SetStepWidth(HINT n);
    HINT GetStepWidth();

	void SetSetpHeigth(HINT n);

    //总长度值
    HDWORD GetTotalWidth();

    // 总帧数
    HDWORD GetCount();

    //设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
    void SetBkgndN(IReSurface* pSur);
    void SetBkgndN(const HString& pFileName);

    void SetTime(HINT ms);

    void Play();
    void Stop();

    void SetOpacity(HBYTE nTrans);
    // 返回图片
    IReSurface* GetImgSurface();

    virtual void GetBackSufSize(HINT& x, HINT& y);

	void SetAlignStyle(HINT nAlign);

protected:
    HBOOL CheckPoint(HINT x, HINT y);

private:
	HINT	m_nAlign;
    //常规背景图
    IReSurface* m_pBkgndN;
    HBOOL m_bBkgndNRes;
    //图像当前的输出位置
    RECTANGLE m_rect;
    //动画定时器
    HINT m_msTime;
    //步长值
    HINT m_nStep;

    HBOOL m_bPlay;

    //当前索引,0开始
    HINT m_nIndex;

    HINT m_nBasetime;
};

#endif