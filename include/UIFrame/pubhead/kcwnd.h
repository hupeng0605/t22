

#if !defined(AFX_KCWND_H__542459D2_4C33_4E3E_840E_6A3C8733D60E__INCLUDED_)
#define AFX_KCWND_H__542459D2_4C33_4E3E_840E_6A3C8733D60E__INCLUDED_

#include "RenderingEngine.h"
#include "KCFont.h"

enum KMESSAGETYPE
{
    KMSG_INVIALID,
    KMSG_KEYPRESS,
    KMSG_KEYUP,
    KMSG_LBBUTTONDOWN,
    KMSG_LBBUTTONUP,
    KMSG_MOUSEMOVE,
    KMSG_TIMER,
    KMSG_CHANGELANG,        // 切换界面语言
    KMSG_CHANGEBACKGROUND,  // 切换界面背景
    KMSG_CHANGETIME,        // 修改时间
    KMSG_CHANGETIMEFORMAT,  // 修改时间格式
    KMSG_CHANGECLOCKTYPE,   // 修改时钟类型
    KMSG_CHANGEDATE,            // 修改日期
    //KMSG_CHANGEVOL,// 修改音量
	//KMSG_USB_IN,
	//KMSG_USB_OUT,
	//KMSG_SD_IN,
	//KMSG_SD_OUT,
	//KMSG_IPOD_IN,
	//KMSG_IPOD_OUT,
	KMSG_WND_ACTIVE,
	KMSG_WND_INACTIVE,
	KMSG_TRANSAFFECT,
	//KMSG_HARD_BTN,
	KMSG_CLOSE_EXE,
	//KMSG_MAIN_UPDATEMEM,	// 无用
	//KMSG_BT_PAIR,		// 配对蓝牙消息
	//KMSG_IPOD,
	//KMSG_BT_READPB,		// 读电话本
	//KMSG_BT_READPN,		// 读电话号码
	//KMSG_BT_DEVICEINFO,
	//KMSG_BT_CONNECTSUCCESS,	// 连接成功
	//KMSG_BT_DISCONNECTSUCCESS,// 断开成功
	//KMSG_BT_DIALSTATE,	// 通话状态
	//KMSG_BT_UPDATEID3,	// 更新ID3
	//KMSG_BT_INQUIRYADD,	// 搜索设备
	//KMSG_DISC,
	//KMSG_CLOSEVIDEO,
	//KMSG_SHOWVIDEO,
	//KMSG_RADIO_UPDATE_FREQ,
};

enum KWNDTYPE
{
    KWND_BASE = 0,
    KWND_WINDOW,
    KWND_BUTTON,
    KWND_TEXTCTL,
    KWND_LIST,
    KWND_CHECKBOX,
    KWND_RADIOBOX,
    KWND_SLIDER,
    KWND_PROGRESS,
    KWND_IMAGECTRL,
    KWND_GROUPCTRL,
    KWND_SCROLLBOX,
	KWND_KEYBOARD,
    KWND_PICKBUTTON,
    KWND_RIPPLEIMAGECTRL,
	KWND_ROTATIONCTRL,
    KWND_SCROLLTEXTCTRL,


    KWND_BUTTONTREE,
    KWND_MOREPICKBTN,
	KWND_MENUITEMCTRL,
	KWND_LISTBOXEX,
	KWND_ROLLERCTRL,
	KWND_SCROLLBUTTONTEXT,
	KWND_SHOWNUMSLIDE,
	KWND_SWITCHLIST,
	KWND_SWITCHPAGE,
	KWND_CLOCKCTRL,
	KWND_SWITCHBUTTON,
	KWND_SUBROWLIST,
};

class UICORE_DLL_API HMessage
{
 public:
    KMESSAGETYPE msgtype;
    HINT keyID;
    HINT mousex;
    HINT mousey;
    HINT wParam;  // 传递数据
    HINT lParam;  // 传递数据
    HBOOL bSendBackWnd; //标示消息是否发送到后台窗口 为true send
    HMessage()
    {
        msgtype = KMSG_INVIALID;
        keyID = -1;
        mousex = -1;
        mousey = -1;
        wParam = 0;
        lParam = 0;
        bSendBackWnd = FALSE;
    };
    ~HMessage(){};
};

class UICORE_DLL_API HCWnd
{
public:
    HCWnd();
    virtual ~HCWnd();

    //消息处理函数，各子类都要重载
    virtual HBOOL DoMessage(HMessage* msg);

    //设置是否显示
    virtual void SetShow(HBOOL bShow);
    virtual HBOOL IsShow();

    //在父窗口内部绘制窗体
    virtual void Draw(IReSurface* s);

    //设置透明度,设为0时窗口隐藏
    virtual void SetOpacity(HBYTE value);
    HBYTE GetOpacity();

    //相对移动距离
    virtual void Move(HINT dx, HINT dy);
    //绝对移动坐标
    virtual void MoveTo(HINT x, HINT y);
    //设置大小
    virtual void SetSize(HINT w, HINT h);
    //取得位置信息
    void GetPosition(HINT &x, HINT &y);
    //取得大小
    void GetSize(HINT &width, HINT &height);
    //取得窗口类型
    KWNDTYPE GetType();
    //设置使用字体
    virtual void SetFont(HCFont* font);
    //获取字体
    HCFont* GetFont();

    virtual HBOOL SetFontSize(HINT width, HINT height);
    void GetFontSize(HINT& width, HINT& height);

    //创建
    HBOOL Create(HINT x, HINT y, HINT w, HINT h);

    // 取得背景图大小，只在编辑工具中使用
    virtual void GetBackSufSize(HINT& /*x*/ , HINT& /*y*/) {};

protected:
    virtual void OnShow() {};
    virtual void OnHide() {};

    KWNDTYPE m_eWndType;
    HINT  m_width;
    HINT  m_height;
    HINT  m_x;
    HINT  m_y;
    HBYTE m_nOpacity;
    HBOOL m_bFocus;
    HBOOL m_bShow;

    //使用的字体,为外部指针,不用释放
    HCFont* m_pfont;
    HINT m_fontWidth;
    HINT m_fontHeight;

};

#define BUTTON_NORMAL 0
#define BUTTON_ACTIVE 1
#define BUTTON_DISABLE 2
#define BUTTON_FOCUS 4

class HCWindow;
typedef void (*pFun)(void*, void*);
class UICORE_DLL_API HCBaseCtrl : public HCWnd
{
public:
    HCBaseCtrl();
    virtual ~HCBaseCtrl();
    //创建
    virtual HBOOL Create(HINT x, HINT y, HINT w, HINT h);
    //取得顶层窗口
    HCWnd* GetTopWindow();
    //父窗口
    virtual void SetFatherWnd(HCWindow* pFatherWnd);
    HCWindow* GetFatherWnd();
    //设为焦点
    virtual void SetFocus(HBOOL bFocus);
    virtual HBOOL IsFocus();
    virtual void SetShow(HBOOL bShow);
    virtual  void SetOpacity(HBYTE value);
    //相对移动距离
    virtual void Move(HINT dx, HINT dy);
    //绝对移动坐标
    virtual void MoveTo(HINT x, HINT y);
    //设置大小
    virtual void SetSize(HINT w, HINT h);

    //获取焦点时调用
    virtual void OnFocus();
    //失去焦点时调用
    virtual void OnLostFocus();

    virtual void Enable(HBOOL able);
    virtual HBOOL IsEnable();

    virtual void EnableMsg(HBOOL able);
    virtual HBOOL IsGetMsg();

    virtual void EnableFocus(HBOOL able);
    virtual HBOOL IsCanFocus();

	virtual void EnableBeep(HBOOL able);
	virtual HBOOL IsCanBeep();

    void SetCallBack(void (*callback)(void*, void*), void*);
    pFun GetCallBack();

    void SetWndID(HINT id);
    HINT GetWndID();
    void SetTextColorN(int r, int g , int b);
    void SetTextColorA(int r, int g , int b);
    void SetTextColorS(int r, int g , int b);

    RECOLOR* GetColorTextN();
    RECOLOR* GetColorTextA();
    RECOLOR* GetColorTextS();
    //取得控件相对于Screen的坐标,主要是加上父窗口的坐标
    void GetScreenXY(HINT &x, HINT &y);

    void SetName(const HCHAR* name);
    HString GetName();

    virtual HBOOL CheckPoint(HINT x, HINT y);

    // 绘制焦点框的函数
    static void DrawFocusRect(IReSurface* s,
                              HINT left, HINT top,
                              HINT right, HINT bottom,
                              RECOLOR& color, HINT iWidth);

    //获得当前的控件状态
    HBYTE GetState();

    //在指定的Surface表面的X,Y上绘制控件
    virtual void DrawBaseCtrl(IReSurface* pSurf, int x, int y);
    virtual inline void Invalidate();
    void inline InvalidateRect(kn_rect& rect);

    HBOOL IsGlobal();

    void SetGlobal(HBOOL bState);

	//// 挂起当前布局
	//virtual void SuspendLayout();
	//// 应用当前布局，立即重绘
	//virtual void ResumeLayout();

	//只允许控件更新自己的区域，不去考虑其它控件是否更新
	virtual void EnableOwnerUpdate(HBOOL bEnable);

	HBOOL IsOwnerUpdate();

	//设置控件进行重绘
	virtual void Redraw(HBOOL bEnable = TRUE);

	HBOOL IsRedraw();

	//控件能否响应遥控器的上下左右消息,默认不响应
	void EnableRecvRemoteMsg(HBOOL bEnable);
	HBOOL IsCanRecvRemoteMsg();

	void EnableDraw(HBOOL bDrawAble = true)
	{
		m_bEnableDraw = bDrawAble;
	}
	HBOOL IsEnableDraw(void)
	{
		return m_bEnableDraw;
	}
#if 0
	//Setcapture功能实现函数
	void SetCapture();
	void ReleaseCapture();
#endif
protected:
	HBOOL m_bEnableDraw;
	//HBOOL m_bSuspendLayout;// 当前布局是否处于挂起状态
    HCWindow*  m_pFatherWnd;
    HINT  m_wndID;

    HString m_strName;

    //是否可以获取焦点
    HBOOL m_bCanFocus;

    //是否可用
    HBOOL m_bEnable;
    //是否可以接受消息
    HBOOL m_bGetMsg;

    HBYTE m_eState;

    RECOLOR m_clrTextN;
    RECOLOR m_clrTextA;
    RECOLOR m_clrTextS;

    //回调函数变量,要传入类指针
    void (*m_pCallBack)(void *, void *);
    //回调类指针
    void*   m_pThis;

	HBOOL m_bNeedRedraw;
	HBOOL m_bOwnerUpdate;

	HBOOL m_bEnableBeep;

private:

    HBOOL m_bGlobal;
	HBOOL m_bEnableRecvRemoteMsg;
	

};
typedef vector<HCBaseCtrl*> CtrlArray;
#endif // !defined(AFX_KCWND_H__542459D2_4C33_4E3E_840E_6A3C8733D60E__INCLUDED_)
