/********************************************************************
    created:    2006/12/04
    created:    4:12:2006   11:29
    filename:   d:\code\try\newhmi\include\kcwindow.h
    file path:  d:\code\try\newhmi\include
    file base:  kcwindow
    file ext:   h
    author:          

    purpose:
*********************************************************************/


#if !defined(AFX_KCWINDOW_H__B49A5B73_638F_4905_8FB0_65533C16CC62__INCLUDED_)
#define AFX_KCWINDOW_H__B49A5B73_638F_4905_8FB0_65533C16CC62__INCLUDED_

#include "KCWnd.h"
#include <vector>

using namespace std;

#define KN_OK 1
#define KN_CANCEL 0
#define KN_DEFAULT -1

#define CHILD_MAXNUM 100
#define TAB_FORE 0
#define TAB_NEXT 1
#define TAB_UP 2
#define TAB_DOWN 3

class HCRadioBox;
class HCScreen;
class HCGroupCtrl;

//搜索控件的方向
typedef enum _eDirectionType
{
	LeftDirection,
	RightDirection,
	UpDirection,
	DownDirection,
}eDirectionType;


class UICORE_DLL_API CTimer
{
public:
    CTimer();
    ~CTimer();

    //设置、获取间隔时间 精确到10毫秒
    void SetTime(HINT ms);
    HINT GetTime();

    //启动定时器
    void StartTimer();

    //停止定时器
    void StopTimer();

    //是否活动状态
    HBOOL IsActive();

    //传入主定时器运行数，判断是否启动,同时调用回调
    HBOOL Active(HMessage* msg);

    //设置定时器回调
    void SetCallBack(void (*callback)(void*, void*), void*);

protected:
    // 间隔时间，单位10ms
    HINT m_ntime;

    //基准时间点，在Start时设置
    HINT m_nBasetime;

    // 是否活动
    HBOOL m_bActive;

    //回调类指针
    void (*m_pCallBack)(void *, void *);
    void* m_pThis;
};

class UICORE_DLL_API HCWindow : public HCWnd
{
public:
    HCWindow();
    virtual ~HCWindow();

    HBOOL DeleteChild(int index);
    //消息处理函数，各子类都要重载
    virtual HBOOL DoMessage(HMessage* msg);

    virtual void Draw(IReSurface* pSurface);
	virtual void Draw(IReSurface* pSurface,IReSurface* pSurfaceMap,_kn_rect m_rectMap);

    HINT Create(int x, int y, int w, int h, HCScreen* pScreen);

    //在窗口初始化函数,继承的窗口类重载此函数初始化内部窗口
    virtual HINT OnInit();

    //焦点切换函数
    virtual void SwitchFocus(HBYTE dir);
    //焦点切换函数 用于上下按钮 根据控件布局查找
    virtual void SwitchFocusOfFind(HBYTE dir);

    HBOOL AddChild(HCBaseCtrl *pwnd);
	HBOOL InsertChild(HINT index, HCBaseCtrl *pwnd);

	HCBaseCtrl* GetChild(HINT a_nIndex);
	HINT GetChildCount(void);

    void AddTimer(CTimer *pTimer);

    HBOOL DelTimer(CTimer *pTimer);

    //弹出模式对话框
    virtual HINT DoModal();

    virtual HBOOL ShowWindow();

    //设置背景，使用外部资源，窗口也可以不设背景
    void SetBackGround(IReSurface* pSur);

    //设置背景，自己创建，窗口也可以不设背景
    void SetBackGround(const HString& pFileName);

	HBOOL IsBackGroundOutRes();

    IReSurface* GetBackGround();

    //设置窗口的背景色，在无背景图时使用背景色填充
    void SetBackColor(RECOLOR& color);

    RECOLOR& GetBackColor();

    //为编组的RadioButton使用，设置某组RadioBox 全部为FALSE
    void SetRadioGroup(HINT id, HCRadioBox* pRadioBox = NULL);

	void SetRadioGroup(HINT id, HCRadioBox* pRadioBox, HCGroupCtrl* pGroupCtrl);

    //刷新屏幕 注意是刷新屏幕而不是刷新窗口
    virtual void UpdateWindow();

    //判断自己是否是焦点窗口
    HBOOL IsFocus();

    RECOLOR& SetFocusColor(RECOLOR& clr);
    RECOLOR& GetFocusColor();
    HINT GetFocusLineWidth();
    void   SetFocusLineWidth(HINT width);

    void SetTransType(HINT type);

    //窗口被隐藏时触发
    virtual void OnDeactivated() {};

    //窗口被显示时触发
    virtual void OnActivated() {};

    //添加相应刷新区域, bOwnerUpdate为TRUE时不考虑和其它控件的相交
    void inline InvalidateRect(kn_rect &rect, HBOOL bOwnerUpdate = FALSE);
    void inline InvalidateRect(HCBaseCtrl* pBaseCtrl);

	// 检查更新列表是否包含新添加区域
	void CheckListIncludeRect(kn_rect &rect);
	// 检查新添加区域是否包含更新列表
	void CheckRectIncludeList(kn_rect &rect);

	void InvalidateGroupCtrlRect(kn_rect& rect, HCBaseCtrl* pBaseCtrl);

    //获得刷新区域
    vector<kn_rect>& GetUpdateRectVector();

    //清空刷新区域
    void ClearUpdateRect();

    //两个矩形区域是否相交
    static HBOOL IsRectIntersect(kn_rect& rect1, kn_rect& rect2);
	//矩形1是否在矩形2中
	static HBOOL IsRectIncluded(kn_rect& rect1, kn_rect& rect2);
    //得到两个矩形区域相交部分
    static kn_rect GetIntersectRect(kn_rect& rect1, kn_rect& rect2);

    //设置当前是否允许添加刷新区域
    void EnableUpdateRect(HBOOL bEnable);

    //是否能添加刷新区域
    HBOOL IsCanUpdateRect();
	void SetRemovedMSG(HBOOL bRemovedMSG);
	HBOOL GetRemovedMSG();    
	//设置控件为焦点
	void SetCtrlFocus(HCBaseCtrl *pwnd);

	HCBaseCtrl* GetCtrlFocus();

	void DestoryWindow();

	HBOOL IsExiting();

	HCWindow* GetBakFocusWnd()
	{
		return m_pWndBakFocus;
	}

	// KCWindow换语言只针对HMIEngine中的控件，HMIEngineEx中的控件言语切换由子类负责
	void ChangeLanguage(HCGroupCtrl* pGroupCtrl);
	virtual void ChangeLanguage(HCBaseCtrl* pCtrl);
	virtual void ChangeLanguage(void);
#if 0
	//设置接收消息的控件
	void SetMsgCtrl(KCBaseCtrl* pBaseCtrl);
#endif
protected:
    //销毁窗口
    virtual HBOOL OnDestroy();

    //Modal的消息循环
    HINT RunModalLoop();
    //退出Modal循环
    void EndModalLoop(HINT nResult);

    virtual void OnOK();
    virtual void OnCancel();
private:
	void GetIntersectRectVec(kn_rect& rect1, kn_rect& rect2, vector<kn_rect>& rect_vec );
	HBOOL GetRectVec(vector<kn_rect>::iterator it_b, vector<kn_rect>::iterator& it_e, kn_rect rect,vector<kn_rect>& rectVec);
	//获得下一个接收消息的控件，根据相对位置来判断，左右时Y轴优先，上下时X轴优先，pBaseCtrl为空时和（0，0）比较相对位置
	void GetBaseCtrlCanRecvRemoteMsg(eDirectionType type, HCBaseCtrl* pBaseCtrl, HINT x, HINT y, HCBaseCtrl*& pNextSelectBaseCtrl);
	void GetBaseCtrlCanRecvRemoteMsgInGroupCtrl(HCGroupCtrl* pGroupCtrl, eDirectionType type, HCBaseCtrl* pBaseCtrl, HINT x, HINT y, HCBaseCtrl*& pNextSelectBaseCtrl);
protected:
    //子控件链表
    HCBaseCtrl  *m_lstCtrl[CHILD_MAXNUM];
    //获得焦点的控件指针
    HCBaseCtrl  *m_ctlFocus;

    //子控件数量
    int m_nChildNum;

    //指向主屏幕类
    HCScreen* m_pScreen;

    // 窗口背景是否使用外部资源，使用外部资源，析构函数不释放m_pSurBack
    HBOOL m_bOutRes;
    //窗口背景
    IReSurface* m_pSurBack;
    RECOLOR m_colorBack;
    //定时器列表
    vector<CTimer*> m_lstTimer;
    RECOLOR m_clrFocus;
    HINT m_focusLineWidth;
	HBOOL m_bRemovedMSG;
    HINT m_transtype; //窗口退出时的转场类型
private:
    //Domodal的返回值
    HINT m_nResult;

    //判断解除消息循环
    HBOOL m_bExit;

    //备份的焦点窗口，当本窗口弹出，取代前一窗口，窗口删除时，恢复前一窗口
    HCWindow* m_pWndBakFocus;

    vector<kn_rect> m_updateRect;

    HBOOL m_bCanUpdateRect;


	HINT m_xMouseStart,m_yMouseStart;

	HINT m_bEnableSendBeepMessage;
#if 0
	//添加setcapture功能
	KCBaseCtrl* m_pMsgCtrl;
#endif
};

#endif // !defined(AFX_KCWINDOW_H__B49A5B73_638F_4905_8FB0_65533C16CC62__INCLUDED_)
