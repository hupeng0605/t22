


#if !defined(AFX_KCTEXTCTL_H__191B5196_9FC3_4F4F_B194_CCC17DF27244__INCLUDED_)
#define AFX_KCTEXTCTL_H__191B5196_9FC3_4F4F_B194_CCC17DF27244__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWnd.h"
#include "KCWindow.h"
#include "KCButton.h"

#define FT_IMAGE        0
#define FT_RECT         1
#define FT_LINEAR_RECTV 2
#define FT_LINEAR_RECTH 3
#define FT_LINEAR_ALPHAV 4
#define FT_LINEAR_ALPHAH 5
#define FT_NONE         6
#define FT_RECTFRAME        7
#define FT_ROUNDRECTFRAME   8

class UICORE_DLL_API HCTextCtrl : public HCBaseCtrl
{
public:
    enum CARET_MODE {CARET_NONE, CARET_SHOW_ON_FOCUS, CARET_SHOW_ALWAYS};
	enum CARET_STYLE {CARET_VERTICAL, CARET_HORIZONTAl};

    HCTextCtrl();
    ~HCTextCtrl();

    HBOOL HCTextCtrl::Create(HINT x, HINT y, HINT w, HINT h);

    //设置文本
    void SetText(const HCHAR* pTxt, HINT x , HINT y, HWORD type = RE_TS_NORMAL);
    void SetText(const HCHAR* pTxt);
    void SetTextPos(HINT x , HINT y);
    void SetTextStyle(HWORD type);

    //增加字符
    void AddChar(HCHAR c);

    // ADD.              .2007.4.12.
    // --Begin-----------------------------------------------------------------

    // 附加文本
    void AppendText(const HCHAR* str);

    // 如脱字符存在且nPos为-1则从脱字符处插入，否则从末尾插入
    void InsertText(const HCHAR* str, HINT nPos = -1);

    // 回退一格(如脱字符存在且bCaretPos为true则从脱字符处删除，否则从末尾删除)
    void Backspace(HBOOL bFromCaretPos = true);

    // --End-------------------------------------------------------------------

    //取得文本
    HString GetText();

    // ADD.              .2007.4.12.光标相关
    // --Begin-----------------------------------------------------------------
    CARET_MODE GetCaretMode();
    void SetCaretMode(CARET_MODE mode);

    // 脱字符尺寸
    void GetCaretSize(HINT& nWidth, HINT& nHeight);
    void SetCaretSize(HINT nWidth, HINT nHeight);

	 //脱字符的显示风格，分竖向和横向
	CARET_STYLE GetCaretStyle();
	void SetCaretStyle(CARET_STYLE style);

    // 脱字符颜色
    void SetCaretColor(HBYTE r, HBYTE g, HBYTE b);
    void SetCaretColor(RECOLOR& clr);

    // 脱字符是否闪烁
    HBOOL IsCaretBlink();
    void SetCaretBlink(HBOOL bBlink);

    // 脱字符闪烁间隔时间
    HUINT GetCaretBlinkTime();
    void SetCaretBlinkTime(HUINT nTime);

    // 获取脱字符位置，字符为单位
    HINT GetCaretPos();

    // 设置脱字符的位置(bMakeCaretInSight为true时，保证脱字符一定在可显区域内)
    void SetCaretPos(HINT nPos, HBOOL bMakeCaretInSight = false);

    HINT GetSelLength();
    void SetSelLength(HINT nSelLength);

    // 设置与之绑定的用于左右移动光标的按钮
    void SetLRButton(HCButton* lBtn, HCButton* rBtn);
    // --End-------------------------------------------------------------------

    //消息处理函数，各子类都要重载
    HBOOL DoMessage(HMessage* msg);
    void Draw(IReSurface* pSurface);

    HBOOL IsCanFocus();

    //设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
    void SetBkgndN(IReSurface* pSur);
    void SetBkgndN(const HString& pFileName);
    void SetFillColor(HDWORD clrA, HDWORD clrB = 0, HDWORD clrC = 0);
    void SetFillType(HINT typ);
    void SetTxtColor(int r , int g , int b);

    void SetRoll(HBOOL roll);
	void SetMultiline(HBOOL multi);

    virtual void GetBackSufSize(HINT& x, HINT& y);
	// 言语部分
	HINT GetLangID(void)
	{
		return m_nLangID;
	}
	void SetLangID(HINT a_nLangID)
	{
		m_nLangID = a_nLangID;
	}

	void SetCallBackDown(void (*callback)(void*, void*), void*);
	// 超长打点显示
	void EnableDot(HBOOL bDot);
	//设置文字滚动的宽度
	void SetRollWidth(HINT nWidth);
protected:
    void IsNeedRoll();
    HBOOL CheckPoint(HINT x, HINT y);

    // ADD.              .2007.4.12
    // --Begin-----------------------------------------------------------------
    HBOOL HasCaret();
    HBOOL IsCaretShow();

    // 调整脱字符范围，避免超界
    HINT AdjustCaretPos(HINT nPos);

    // 调整偏移使脱字符出现在可视范围
    void MakeCaretInSight();

    // 获取指定索引号的字符所在坐标位置(相对文本左上角)
    void GetPosFromChar(HINT iCharIndex, HINT& x, HINT& y);

    // 获取目前可看到的字符个数
    HINT GetVisibleCharNumber();

    // 获取最大字符串偏移量
    HINT GetMaxOffset();

    // 触发Change事件
    void OnChange();

    static void OnBtnLR(void* p, void* pParam);
    void OnBtnLR(void* pParam);
    // 获取m_strTxt指定范围的宽度(包括脱字符),0<=iStartPos<=iEndPos<=m_strTxt.size().
    HINT GetStrTextWidth(HINT iStartPos, HINT iEndPos);
    // --End-------------------------------------------------------------------
	
protected:
	HINT	m_nLangID;
    //常规背景图
    IReSurface* m_pBkgndN;
    HBOOL m_bBkgndNRes;

    //文字位置
    HINT m_nTextPosX;
    HINT m_nTextPosY;

    //文字样式
    HWORD m_TextStyle;

    //填充方式
    HBYTE m_FillType;
    //文字颜色
    RECOLOR m_clrText;
    HDWORD m_clrRectA;
    HDWORD m_clrRectB;
    HDWORD m_clrRect;

    HString m_strTxt;

    HINT m_broll;
    HINT m_nStrOutSize;
    HINT m_nStrOut;
    HBOOL m_bOut;

    // ADD.              .2007.4.12.脱字符相关
    // --Begin-----------------------------------------------------------------
    CARET_MODE m_CaretMode;     // 脱字符显示模式
	CARET_STYLE m_CaretStyle;    // 脱字符显示风格
    HINT m_nCaretWidth;       // 脱字符宽
    HINT m_nCaretHeight;      // 脱字符高
    RECOLOR m_clrCaret;         // 脱字符颜色
    HBOOL m_bCaretBlink;      // 脱字符是否闪烁
    HUINT m_nCaretBlinkTime;  // 脱字符闪烁时间(10ms为单位)
    HINT m_nCaretPos;         // 脱字符当前位置(以字符数为单位,0起始)
    HINT m_nSelLength;        // 选中文本的长度(负数表示向后选中)

    HINT m_iCaretState;       // 脱字符状态(0:消失;1:闪现)
    HINT m_iBaseTime;         // 记录闪烁的基准时间点
    HCButton* m_btnLeft;        // 绑定的左方向按钮，用于移动脱字符
    HCButton* m_btnRight;       // 绑定的右方向按钮，用于移动脱字符

	void (*m_pCallBackDown)(void*, void*);
	HBOOL m_bEnableDot;
	//设置文字滚动的宽度
	HINT m_nRollWidth;
    // --End-------------------------------------------------------------------

	/* 20140519 jinlingw: BEGIN ADD("多行显示")  */
	HBOOL m_bMultiline;
	/* 20140519 jinlingw: BEGIN ADD("多行显示")  */
};

#endif // !defined(AFX_KCTEXTCTL_H__191B5196_9FC3_4F4F_B194_CCC17DF27244__INCLUDED_)
