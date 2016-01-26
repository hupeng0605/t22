/********************************************************************
    created:    2011/09/05
    created:    09:05:2011   10:47
    filename:   d:\code\try\newhmi\include\kcslidectrl.h
    file path:  d:\code\try\newhmi\include
    file base:  kcscrollctrl
    file ext:   h
    author:                   

    purpose:
*********************************************************************/


#if !defined(AFX_KCSCROLLCTRL_H__E8783179_BE3E_455F_A6EC_377F43DCFCF2__INCLUDED_)
#define AFX_KCSCROLLCTRL_H__E8783179_BE3E_455F_A6EC_377F43DCFCF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWnd.h"
#include "KCTextCtrl.h"
#define HORIZONTAL 0  //水平
#define VERTICAL 1 //竖直

enum SCROLLDIR
{
    SCROLL_MOVEUP,
    SCROLL_MOVE,
    SCROLL_CHANGE,
};

struct SCROLLPARA
{
    HBYTE eDir;
    HINT nValue;
};

class HCButton;
class HCScrollBox;
class UICORE_DLL_API HCScrollCtrl : public HCBaseCtrl
{
public:
    HCScrollCtrl();
    virtual ~HCScrollCtrl();

    // dir为控件方向
    HBOOL Create(HINT x, HINT y, HINT w, HINT h, HBYTE dir);

    // 消息处理函数，各子类都要重载
    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);

    // 设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
    void SetBkgndN(IReSurface* pSur);
    void SetBkgndN(const HString& pFileName);

    // 滑动条前景图
    void SetBkgndA(IReSurface* pSur);
    void SetBkgndA(const HString& pFileName);

   // 滑动条前景激活图
    void SetBkgndF(IReSurface* pSur);
    void SetBkgndF(const HString& pFileName);

	// 滑动条前景禁用图
	void SetBkgndD(IReSurface* pSur);
	void SetBkgndD(const HString& pFileName);

    // 设置、获取当前值
    void SetValue(HINT n);
    HINT GetValue();
	//	设置当前值扩展函数,bRoll表示是否需要滚动
	void SetValueEx(HINT n, HBOOL bRoll=false);

    // 滑动条范围
    void SetBound(HINT iMin, HINT iMax);
    HINT GetMaximum();
    HINT GetMinimum();

    // 设置用于增加value的按钮
    void SetAddButton(HCButton* btnSub, HCButton* btnAdd);
	//设置滚动条置顶和置底按钮
	void SetTopButton(HCButton* btnTop, HCButton* btnBottom);
	//设置用于显示索引的TXT文本
	void SetTextCtrl(HCTextCtrl* txtInd);
	//设置列表框
	void SetScrollBox(HCScrollBox* pCtrl/*KCScrollBox控件*/, HINT nRows/*可显示的行数*/);/*需要每行的高相同*/


    void SetCallBackMouseUp(void (*callback)(void*, void*), void*);
	//鼠标移动消息
	void SetCallBackMouseMove(void (*callback)(void*, void*), void*);


protected:

    // 通过滑块的Value获取对应的坐标位置(一个Value只对应一个坐标)
    HINT GetPosFromValue(HINT);

    // 通过滑块的坐标位置获取对应的Value(连续的一段坐标对应同一个Value)
    HINT GetValueFromPos(HINT,HBOOL bNear);

    // 计算滑块的位置
    void CalcThumbPos();
	void UpdateButton();
    // 通过滑块的坐标位置来更新Value
    void UpdateValue(HINT,HBOOL bNear = FALSE);

    static void OnBtnSubAdd(void* p, void* pParam);
    void OnBtnSubAdd(void* pParam);

	static void OnBtnSubTop(void* p, void* pParam);
	void OnBtnSubTop(void* pParam);

	void ScrollCtrl(HINT nStartOffset, HINT nEndOffset);

    // 滑动条最大值，最小值
    HINT  m_nMin;
    HINT  m_nMax;

    // 常规背景图
    IReSurface* m_pBkgndN;
    HBOOL m_bBkgndNRes;

    // 滑动条游标图
    IReSurface* m_pBkgndA;
    HBOOL m_bBkgndARes;
    // 滑动条游标激活图
    IReSurface* m_pBkgndF;
    HBOOL m_bBkgndFRes;

	// 滑动条前景禁用图
	IReSurface* m_pBkgndD;
	HBOOL m_bBkgndDRes;

    // 游标当前值
    HINT m_nValue;

    // 滑动条方向(横/纵)
    HBYTE m_eDir;

    // 滑块的位置属性(左/上/宽/高)
    HINT m_ex, m_ey, m_ew, m_eh;

    HCButton* m_btnSub;
    HCButton* m_btnAdd;
	HCButton* m_btnTop;
	HCButton* m_btnBottom;
	HCTextCtrl* m_txtIdx;
	HCScrollBox* m_pScrollBox;
	//	显示的行数
	HINT		m_nRows;


	//kn_int	m_nAllOffset;
	//	鼠标点下时鼠标的位置
	HINT	m_nMouseDownPos;
	//	鼠标点下时滑块的位置
	HINT	m_nMouseDownEPos;
	//	鼠标点下时当前滑块的索引
	HINT	m_nMouseDownIndex;
    //回调函数变量,要传入类指针
    void (*m_pCallBackMouseUp)(void *, void *);
	// 鼠标移动响应消息
	void (*m_pCallBackMouseMove)(void *, void *);

    void* m_pThisMouseUp;

};

#endif // !defined(AFX_KCSCROLLCTRL_H__E8783179_BE3E_455F_A6EC_377F43DCFCF2__INCLUDED_)
