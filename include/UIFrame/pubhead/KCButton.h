/********************************************************************
    created:    2006/12/04
    created:    4:12:2006   11:28
    filename:   d:\code\try\newhmi\include\kcbutton.h
    file path:  d:\code\try\newhmi\include
    file base:  kcbutton
    file ext:   h
    author:          

    purpose:
*********************************************************************/


#if !defined(AFX_KCBUTTON_H__A1D31C49_3686_4A89_A80B_63B62A737FD6__INCLUDED_)
#define AFX_KCBUTTON_H__A1D31C49_3686_4A89_A80B_63B62A737FD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWnd.h"
#define ANIMATION_BTN_BACK_HIDE 1 //显示动画图标时隐藏按钮背景
#define ANIMATION_BTN_ICON_HIDE 2 //显示动画图标时隐藏按钮图标
#define ANIMATION_BTN_SET_POS   4 //显示动画图标时调整动画图标位置对齐按钮

class HCImageCtrl;

class UICORE_DLL_API HCButton : public HCBaseCtrl
{
public:
    HCButton();
    virtual ~HCButton();
    //消息处理函数，各子类都要重载
    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);

    //设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
    void SetBkgndN(IReSurface* pSur);
    void SetBkgndN(const HString& pFileName);
    //取得按钮名称
    const HString& GetBtnText();

    void SetIcon(IReSurface* pSur, HINT x = 0, HINT y = 0);
    void SetIcon(const HString& pFileName, HINT x = 0, HINT y = 0);
	IReSurface* GetIcon();
	void GetIconXY(HINT& x, HINT& y);

	void SetIconA(IReSurface* pSurf);
	void SetIconA(const HString& pFileName);

	void SetIconF(IReSurface* pSurf);
	void SetIconF(const HString& pFileName);

    void SetBkgndA(IReSurface* pSur);
    void SetBkgndA(const HString& pFileName);

    void SetBkgndF(IReSurface* pSur);
    void SetBkgndF(const HString& pFileName);

	void SetBkgndS(IReSurface* pSur);
	void SetBkgndS(const HString& pFileName);

	//取得按钮背景图，可以进行拷贝和绘制操作
	IReSurface* GetBKgndN();
	IReSurface* GetBKgndA();
	IReSurface* GetBKgndF();

    void SetText(const HCHAR* pTxt, HINT x, HINT y, HWORD type = RE_TS_NORMAL);
    void SetText(const HCHAR* pTxt);
	void AddText(const HCHAR* pTxt);
    void SetTextPos(HINT x , HINT y); //
    void SetTextStyle(HWORD type); //设置文本显示类型
	void SetTextRect(HINT width, HINT height); //设置换行文本显示范围
	void EnableNewLine(HBOOL bEnable); //是否可以换行
	void SetLineSpace(HINT height); //间距
	HString GetText();

    //设置透明度
    void SetOpacity(HBYTE nTrans);

    //按钮按下回调
    void SetCallBackDown(void (*callback)(void*, void*), void*);
    //按钮弹起回调
    void SetCallBackUp(void (*callback)(void*, void*), void*);
    //获取焦点回调
    void SetCallBackOnFocus(void (*callback)(void*, void*), void*);
    //失去焦点回调
    void SetCallBackLostFocus(void (*callback)(void*, void*), void*);
    //鼠标移动消息
    void SetCallBackMouseMove(void (*callback)(void*, void*), void*);
	//长按消息
	void SetCallBackLongPress(void (*callback)(void*, void*), void*);
	void SetCallBackLongPressUp(void (*callback)(void*, void*), void*);

	void EnableLongPressConsecutive(HBOOL bEnable, HINT times = 50);

//     设置动画图标
//     #define ANIMATION_BTN_BACK_HIDE 1 //显示动画图标时隐藏按钮背景
//     #define ANIMATION_BTN_ICON_HIDE 2 //显示动画图标时隐藏按钮图标
//     #define ANIMATION_BTN_SET_POS   4 //显示动画图标时调整动画图标位置对齐按钮
    void SetAnimationIcon(HCImageCtrl* pIcon, HDWORD type);

    virtual void GetBackSufSize(HINT& x, HINT& y);
	//是否让字体超长变点
	void SetEnableTruncationFont(HBOOL m_bEnable);
	//截取字体
	HString TruncationFont(HString str);

	HINT GetLangID(void)
	{
		return m_nLangID;
	}
	void SetLangID(HINT a_nLangID)
	{
		m_nLangID = a_nLangID;
	}

	HINT GetTagIndex(void)
	{
		return m_nTagIndex;
	}
	void SetTagIndex(HINT a_nLangID)
	{
		m_nTagIndex = a_nLangID;
	}


	void SetLongPressTime(HINT time);

	//获取焦点时调用 重载
	void OnFocus();
	//失去焦点时调用 重载
	void OnLostFocus();

	//是否允许自定义消息响应区域，相对控件的座标
	void EnableOwnerMsgRecvRect(HBOOL bEnable, kn_rect* pRectMsgRecv );

protected:
    HBOOL CheckPoint(HINT x, HINT y);
    //void OnShow();
    void OnHide();

private:
	void RenderTextSurface();

protected:
	HINT	m_nLangID;
    //按钮图标图
    IReSurface* m_pIcon;
    HBOOL m_bIconRes;

	IReSurface* m_pIconA;
	HBOOL m_bIconARes;

	IReSurface* m_pIconF;
	HBOOL m_bIconFRes;

    //常规背景图
    IReSurface* m_pBkgndN;
    HBOOL m_bBkgndNRes;

	//禁用图
	IReSurface*	m_pBkgndDisable;
	HBOOL		m_bBkgndDisableRes;

    //激活背景图
    IReSurface* m_pBkgndA;
    HBOOL m_bBkgndARes;

    //聚焦背景图
    IReSurface* m_pBkgndF;
    HBOOL m_bBkgndFRes;

    //文字位置
    HINT m_nTextPosX;
    HINT m_nTextPosY;

    //图标位置
    HINT m_nIconPosX;
    HINT m_nIconPosY;

    //文字对齐方式 居中，靠左 靠右
    HWORD m_TextStyle;

    HString m_strTxt;

	HINT m_TextWidth;//文字区域宽度
	HINT m_TextHeight;//文字区域高度
	HINT m_TextRowSpace;//两行文字之间的距离
	HBOOL m_bEnableNewLine;//允许换行
	IReSurface* m_pTextSurf;

    //动画按钮使用的动画图标,此项非空表示是动画按钮
    HCImageCtrl* m_pImageCtrl;
    HDWORD    m_eAnimationType;


    //按钮按下时回调函数变量,要传入类指针
    void (*m_pCallBackDown)(void *, void *);
    //按钮弹起时回调函数变量,要传入类指针
    void (*m_pCallBackUp)(void *, void *);

    //按钮按下时回调函数变量,要传入类指针
    void (*m_pCalllBackOnFocus)(void *, void *);
    //按钮弹起时回调函数变量,要传入类指针
    void (*m_pCallBackLostFocus)(void *, void *);

    // 鼠标移动响应消息
    void (*m_pCallBackMouseMove)(void *, void *);

	// 鼠标长按消息
	void (*m_pCallBackLongPress)(void *, void *);
	void (*m_pCallBackLongPressUp)(void *, void *);

	HINT m_longPressTime;
	HINT m_baseTime;
	HBOOL m_bHaveExecute;
	HBOOL m_bOutOfRange;
	HBOOL m_bEnableInterceptFont;
	
	//长按连续响应消息
	HBOOL m_bEnableLongPressConsecutive;
	HINT m_LongPressTimeConsecutive;
	//按钮序号的标识符
	HINT m_nTagIndex;

	HBOOL m_bEnableOwnerMsgRecv;
	kn_rect m_rectMsgRecv;
};

#endif // !defined(AFX_KCBUTTON_H__A1D31C49_3686_4A89_A80B_63B62A737FD6__INCLUDED_)
