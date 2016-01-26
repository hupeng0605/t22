/********************************************************************
    created:    2006/12/04
    created:    4:12:2006   11:28
    filename:   d:\code\try\newhmi\include\kcslidectrl.h
    file path:  d:\code\try\newhmi\include
    file base:  kcslidectrl
    file ext:   h
    author:          

    purpose:
*********************************************************************/


#if !defined(AFX_KCSLIDECTRL_H__E8783179_BE3E_455F_A6EC_377F43DCFCF2__INCLUDED_)
#define AFX_KCSLIDECTRL_H__E8783179_BE3E_455F_A6EC_377F43DCFCF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWnd.h"

#define HORIZONTAL 0  //水平
#define VERTICAL 1 //竖直

enum SLIDEDIR
{
    SLIDE_LINEADD,
    SLIDE_LINESUB,
    SLIDE_PAGEADD,
    SLIDE_PAGESUB,
    SLIDE_TRACK,
    SLIDE_CHANGE,
};

struct SLIDEPARA
{
    HBYTE eDir;
    HINT nValue;
};

class HCButton;
class HCListBox;

class UICORE_DLL_API HCSlideCtrl : public HCBaseCtrl
{
public:
    HCSlideCtrl();
    virtual ~HCSlideCtrl();

    // dir为控件方向,ex为滑块起始位置的偏移
    HBOOL Create(HINT x, HINT y, HINT w, HINT h, HBYTE dir, HINT iOffset);

    // 消息处理函数，各子类都要重载
    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);

    void Enable(HBOOL able);

    // 设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
    void SetBkgndN(IReSurface* pSur);
    void SetBkgndN(const HString& pFileName);

    // 滑动条前景图
    void SetBkgndA(IReSurface* pSur);
    void SetBkgndA(const HString& pFileName);

    // 滑动条激活图
    void SetDotgndA(IReSurface* pSur);
    void SetDotgndA(const HString& pFileName);
    // 状态条图片
    void SetBkgndS(IReSurface* pSur);
    void SetBkgndS(const HString& pFileName);

	// 滑块上显示的文本
    //void SetText(const HCHAR* pTxt);

    // 设置、获取当前值
    void SetValue(HINT n);
    HINT GetValue();

    // 滑动条范围
    void SetBound(HINT iMin, HINT iMax);
    HINT GetMaximum();
    HINT GetMinimum();

    // 设置、获取每页数量
    void SetPage(HINT);
    HINT GetPage();

    // 设置可滚动的最大值
    HINT GetLimit();

    // 设置用于增加value的按钮
    void SetButton(HCButton* btnSub, HCButton* btnAdd);

    // 设置绑定的ListBox控件
    void SetListBox(HCListBox *pList);

    // 根据ListBox刷新滑动条值
    void RefreshFromListBox();

    void SetCallBackMouseUp(void (*callback)(void*, void*), void*);
	//鼠标移动消息
	void SetCallBackMouseMove(void (*callback)(void*, void*), void*);

	//	设置鼠标点击消息
	void SetCallBackMouseDown(void (*callback)(void*, void*), void*);
    virtual void GetBackSufSize(HINT& x, HINT& y);

	//设置背景图片的偏移
	void SetBkOffset(HINT x, HINT y);

	//滑块拖动使能开关
	void EnableMoveSlider(HBOOL bEnable);

	//滑块点击使能开关
	void EnableClickSlider(HBOOL bEnable);

	// 滑块数值使能开关
	void EnableValueSlider(HBOOL bEnable);

protected:

    // 通过滑块的Value获取对应的坐标位置(一个Value只对应一个坐标)
    HINT GetPosFromValue(HINT);

    // 通过滑块的坐标位置获取对应的Value(连续的一段坐标对应同一个Value)
    HINT GetValueFromPos(HINT);

    // 计算滑块的位置
    void CalcThumbPos();

    // 计算滑块的长度
    void CalcThumbSize();

    // 通过滑块的坐标位置来更新Value
    void UpdateValue(HINT);

    static void OnBtnSubAdd(void* p, void* pParam);
    void OnBtnSubAdd(void* pParam);

	// 滑块上显示的文本
	//HString m_strTxt;
	//IReSurface* m_pTextSurf;

    // 滑动条最大值，最小值
    HINT  m_nMin;
    HINT  m_nMax;

    // 常规背景图
    IReSurface* m_pBkgndN;
    HBOOL m_bBkgndNRes;

	//滑动条游标激活图
	IReSurface* m_pDotgndA;
	HBOOL		m_bDotgndARes;
    // 滑动条游标图
    IReSurface* m_pBkgndA;
    HBOOL m_bBkgndARes;

    // 状态条图
    IReSurface* m_pBkgndS;
    HBOOL m_bBkgndSRes;

    // 游标图起始位置偏移
    HINT m_iOffset;

    // 游标当前值
    HINT m_nValue;

    // 滑动条方向(横/纵)
    HBYTE m_eDir;

    // 滑块的位置属性(左/上/宽/高)
    HINT m_ex, m_ey, m_ew, m_eh;

    //每页的数量
    HINT m_iPage;

    HCButton* m_btnSub;
    HCButton* m_btnAdd;

    //绑定的ListBox控件
    HCListBox* m_pListBox;

    // 记录拖动滑块时光标相对于滑块头部的偏移
    HINT m_iCursorOffset;

    // 滑动条游标大小是否需要改变，现在只有与List绑定时才会改变
    HBOOL m_bThumbSize;

    //回调函数变量,要传入类指针
    void (*m_pCallBackMouseUp)(void *, void *);
	// 鼠标移动响应消息
	void (*m_pCallBackMouseMove)(void *, void *);

	//	鼠标点击响应消息
	void (*m_pCallBackMouseDown)(void *, void *);

    void* m_pThisMouseUp;

	//背景图片的偏移
	HINT m_nBkOffsetX;
	HINT m_nBkOffsetY;

	//滑块拖动使能
	HBOOL m_bEnableMoveSlider;
	//	滑块点击改变坐标使能
	HBOOL m_bEnableClickSlider;

	HBOOL m_bEnableValueSlider;
};

#endif // !defined(AFX_KCSLIDECTRL_H__E8783179_BE3E_455F_A6EC_377F43DCFCF2__INCLUDED_)
