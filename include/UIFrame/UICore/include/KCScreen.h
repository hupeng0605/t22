


#if !defined(AFX_KCSCREEN_H__EEBC52BF_A4B3_41FC_BFC1_A307384943E1__INCLUDED_)
#define AFX_KCSCREEN_H__EEBC52BF_A4B3_41FC_BFC1_A307384943E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWindow.h"
#include <vector>

class HCScreen
{
public:
    HCScreen();
    virtual ~HCScreen();

    void Release();

    //消息处理函数
    HBOOL DoMessage(HMessage* msg);

    // 在Windows下,设置Display对应的窗口句柄
    void SetHWnd(HWND hWnd) ;

    // 设置显示尺寸
#if defined(SCREEN_COLORBIT16)
    void Create(HINT width, HINT height, HINT x, HINT y, HWND hWnd, HINT colorType = RE_COLOR565);
#else
	void Create(HINT width, HINT height, HINT x, HINT y, HWND hWnd, HINT colorType = RE_COLOR888);
#endif
    HINT GetX();
    HINT GetY();
    HINT GetWidth();
    HINT GetHeight();

    // 将指定的surface上屏
    void Flip(IReSurface* surface, HINT x, HINT y);

    void Draw();
	void ClearFast(HBYTE byValue)
	{
		m_pSurface->ClearFast(byValue);
		FlipRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	}

    HCWindow* GetFocusWnd();
    //trans_type 转场特效方式， 0为无转场效果， 1为渐变， 2 滚动效果
    void SetFocusWnd(HCWindow* pWnd, HINT trans_type = 1);
    //转场特效函数
    void TransAffect(HINT trans_type);
	void TransAffect(IReSurface *pOldSur,IReSurface *pNewSur,HINT trans_type);

    //设置报警对话框
    void SetMsgWnd(HCWindow* pWnd);
    HCWindow* GetMsgWnd();

    //新增一个窗口到链表末尾
    HBOOL AddWindow(HCWindow* pWnd);
    //在窗口链表中去掉指定的窗口指针，其余的指针位置向前顺移
    HBOOL DelWindow(HCWindow* pWnd);
    //检查窗口是否存在
    HBOOL CheckWindow(HCWindow* pWnd);
    // 3D窗口切换函数
    void Trans3DRotate(IReSurface *pScreenSurface_bak);

	IReSurface* GetScreenSurface();

	void FlipRect(HINT x, HINT y, HINT width, HINT height);

	void EnableDraw(HBOOL bEnable);

	HBOOL IsCanDraw();

	HBOOL IsInDraw();
	void SetInDraw(HBOOL bInDraw);
	vector<HCWindow*>* GetListWnd();
private:
    //子控件链表 链表不负责释放
    vector<HCWindow*> m_lstChildWnd;

    //指向获得焦点的window
    HCWindow *m_pFocusWnd;

    //为模式报警对话框专门定义的Window
    HCWindow *m_pMsgWnd;

    HWND m_hMainWnd;
    HDC  m_hdc;
    HINT m_width;
    HINT m_height;
    HINT m_x;
    HINT m_y;
    IReSurface* m_pSurface;
    //用于过渡效果的surface
    //IReSurface* m_pSurface_bak;

	HBOOL m_bEnableDraw;
	HBOOL m_bInDraw;
};

#endif // !defined(AFX_KCSCREEN_H__EEBC52BF_A4B3_41FC_BFC1_A307384943E1__INCLUDED_)
