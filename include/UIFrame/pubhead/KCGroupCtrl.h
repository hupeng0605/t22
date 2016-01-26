

#pragma once

#include "KCWnd.h"
#include "vector"
using namespace std;

class UICORE_DLL_API HCGroupCtrl : public HCBaseCtrl
{
public:

    HCGroupCtrl();

    virtual ~HCGroupCtrl();

    //消息处理函数，各子类都要重载
    virtual HBOOL DoMessage(HMessage* msg);

	//返回所有响应了消息的控件
	HBOOL DoMessage(HMessage* msg, OUT vector<HCBaseCtrl*>& ctrlList);

    virtual void Draw(IReSurface* pSurface);

    // 设置背景，使用外部资源，窗口也可以不设背景
    void SetBackGround(IReSurface* pSur);

    // 设置背景，自己创建，窗口也可以不设背景
    void SetBackGround(const HString& pFileName);

    IReSurface* GetBackGround();

	// 移除子控件，默认不清除资源
	HBOOL RemoveChild(int index, HBOOL bDelete = FALSE);
	// 移除子控件，默认不清除资源
	HBOOL RemoveChild(HCBaseCtrl* childCtrl, HBOOL bDelete = FALSE);

	// 添加子控件
    HBOOL AddChild(HCBaseCtrl *pwnd);

	// 在指定位置插入子控件
	HBOOL InsertChild(HINT index, HCBaseCtrl *pwnd);

	// 设置是否显示
	void SetShow(HBOOL bShow);
//  void SetOpacity(kn_byte value);
    //相对移动距离
    void Move(HINT dx, HINT dy);
    //绝对移动坐标
    void MoveTo(HINT x, HINT y);
//  //设置大小
//  void SetSize(kn_int w, kn_int h);

	void EnableOwnerUpdate(HBOOL bEnable);

	void Redraw(HBOOL bEnable = TRUE);

	// 设置父窗口
    void SetFatherWnd(HCWindow* pFatherWnd);

	// 设置焦点控件
    void SetCtrlFocus(HCBaseCtrl *pWnd);

	//得到控件列表
    vector<HCBaseCtrl*>& GetCtrlList();

    void GetBackSufSize(HINT& x, HINT& y);

	void Invalidate();

	// 绘制控件到给定Surface的指定坐标
	void DrawBaseCtrl(IReSurface* pSurf, int x, int y);

	HCBaseCtrl* GetFocusCtrl();
protected:
	HCBaseCtrl  *m_ctlFocus; //焦点控件
private:
    //子控件链表
    vector<HCBaseCtrl*>  m_lstCtrl;
    //获得焦点的控件指针
    
    IReSurface* m_pSurBack; //背景
    HBOOL m_bOutRes;		//是否是外部资源
};