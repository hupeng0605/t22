

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
    KMSG_CHANGELANG,        // �л���������
    KMSG_CHANGEBACKGROUND,  // �л����汳��
    KMSG_CHANGETIME,        // �޸�ʱ��
    KMSG_CHANGETIMEFORMAT,  // �޸�ʱ���ʽ
    KMSG_CHANGECLOCKTYPE,   // �޸�ʱ������
    KMSG_CHANGEDATE,            // �޸�����
    //KMSG_CHANGEVOL,// �޸�����
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
	//KMSG_MAIN_UPDATEMEM,	// ����
	//KMSG_BT_PAIR,		// ���������Ϣ
	//KMSG_IPOD,
	//KMSG_BT_READPB,		// ���绰��
	//KMSG_BT_READPN,		// ���绰����
	//KMSG_BT_DEVICEINFO,
	//KMSG_BT_CONNECTSUCCESS,	// ���ӳɹ�
	//KMSG_BT_DISCONNECTSUCCESS,// �Ͽ��ɹ�
	//KMSG_BT_DIALSTATE,	// ͨ��״̬
	//KMSG_BT_UPDATEID3,	// ����ID3
	//KMSG_BT_INQUIRYADD,	// �����豸
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
    HINT wParam;  // ��������
    HINT lParam;  // ��������
    HBOOL bSendBackWnd; //��ʾ��Ϣ�Ƿ��͵���̨���� Ϊtrue send
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

    //��Ϣ�������������඼Ҫ����
    virtual HBOOL DoMessage(HMessage* msg);

    //�����Ƿ���ʾ
    virtual void SetShow(HBOOL bShow);
    virtual HBOOL IsShow();

    //�ڸ������ڲ����ƴ���
    virtual void Draw(IReSurface* s);

    //����͸����,��Ϊ0ʱ��������
    virtual void SetOpacity(HBYTE value);
    HBYTE GetOpacity();

    //����ƶ�����
    virtual void Move(HINT dx, HINT dy);
    //�����ƶ�����
    virtual void MoveTo(HINT x, HINT y);
    //���ô�С
    virtual void SetSize(HINT w, HINT h);
    //ȡ��λ����Ϣ
    void GetPosition(HINT &x, HINT &y);
    //ȡ�ô�С
    void GetSize(HINT &width, HINT &height);
    //ȡ�ô�������
    KWNDTYPE GetType();
    //����ʹ������
    virtual void SetFont(HCFont* font);
    //��ȡ����
    HCFont* GetFont();

    virtual HBOOL SetFontSize(HINT width, HINT height);
    void GetFontSize(HINT& width, HINT& height);

    //����
    HBOOL Create(HINT x, HINT y, HINT w, HINT h);

    // ȡ�ñ���ͼ��С��ֻ�ڱ༭������ʹ��
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

    //ʹ�õ�����,Ϊ�ⲿָ��,�����ͷ�
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
    //����
    virtual HBOOL Create(HINT x, HINT y, HINT w, HINT h);
    //ȡ�ö��㴰��
    HCWnd* GetTopWindow();
    //������
    virtual void SetFatherWnd(HCWindow* pFatherWnd);
    HCWindow* GetFatherWnd();
    //��Ϊ����
    virtual void SetFocus(HBOOL bFocus);
    virtual HBOOL IsFocus();
    virtual void SetShow(HBOOL bShow);
    virtual  void SetOpacity(HBYTE value);
    //����ƶ�����
    virtual void Move(HINT dx, HINT dy);
    //�����ƶ�����
    virtual void MoveTo(HINT x, HINT y);
    //���ô�С
    virtual void SetSize(HINT w, HINT h);

    //��ȡ����ʱ����
    virtual void OnFocus();
    //ʧȥ����ʱ����
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
    //ȡ�ÿؼ������Screen������,��Ҫ�Ǽ��ϸ����ڵ�����
    void GetScreenXY(HINT &x, HINT &y);

    void SetName(const HCHAR* name);
    HString GetName();

    virtual HBOOL CheckPoint(HINT x, HINT y);

    // ���ƽ����ĺ���
    static void DrawFocusRect(IReSurface* s,
                              HINT left, HINT top,
                              HINT right, HINT bottom,
                              RECOLOR& color, HINT iWidth);

    //��õ�ǰ�Ŀؼ�״̬
    HBYTE GetState();

    //��ָ����Surface�����X,Y�ϻ��ƿؼ�
    virtual void DrawBaseCtrl(IReSurface* pSurf, int x, int y);
    virtual inline void Invalidate();
    void inline InvalidateRect(kn_rect& rect);

    HBOOL IsGlobal();

    void SetGlobal(HBOOL bState);

	//// ����ǰ����
	//virtual void SuspendLayout();
	//// Ӧ�õ�ǰ���֣������ػ�
	//virtual void ResumeLayout();

	//ֻ����ؼ������Լ������򣬲�ȥ���������ؼ��Ƿ����
	virtual void EnableOwnerUpdate(HBOOL bEnable);

	HBOOL IsOwnerUpdate();

	//���ÿؼ������ػ�
	virtual void Redraw(HBOOL bEnable = TRUE);

	HBOOL IsRedraw();

	//�ؼ��ܷ���Ӧң����������������Ϣ,Ĭ�ϲ���Ӧ
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
	//Setcapture����ʵ�ֺ���
	void SetCapture();
	void ReleaseCapture();
#endif
protected:
	HBOOL m_bEnableDraw;
	//HBOOL m_bSuspendLayout;// ��ǰ�����Ƿ��ڹ���״̬
    HCWindow*  m_pFatherWnd;
    HINT  m_wndID;

    HString m_strName;

    //�Ƿ���Ի�ȡ����
    HBOOL m_bCanFocus;

    //�Ƿ����
    HBOOL m_bEnable;
    //�Ƿ���Խ�����Ϣ
    HBOOL m_bGetMsg;

    HBYTE m_eState;

    RECOLOR m_clrTextN;
    RECOLOR m_clrTextA;
    RECOLOR m_clrTextS;

    //�ص���������,Ҫ������ָ��
    void (*m_pCallBack)(void *, void *);
    //�ص���ָ��
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
