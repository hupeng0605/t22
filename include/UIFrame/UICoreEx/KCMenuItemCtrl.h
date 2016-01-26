/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCMenuItemCtrl.cpp
* 摘    要:
*
* 当前版本: 1.0
* 作    者:               
* 完成日期: 2009-12-29
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1            2010-1-29                                创建
*
**/

#pragma once

#include "KCwnd.h"
#include "RenderingEngine.h"

typedef struct _sBorderSurf
{
    IReSurface* pSurf;  //边框图片
    HBOOL bOutRes;
    HINT x;           //距离控件左上角的X轴距离
    HINT y;           //距离控件左上角的Y轴距离

    _sBorderSurf()
    {
        pSurf = NULL;
        x = 0;
        y = 0;
        bOutRes = TRUE;
    }

    ~_sBorderSurf()
    {
		Release();
    }

    void Release()
    {
        if (bOutRes == FALSE)
        {
            SAFE_DELETE(pSurf);
        }
    }

} sBorderSurf;

enum eBorderDirection
{
    CursorBorderLeft,
    CursorBorderRight,
    CursorBorderTop,
    CursorBorderBottom,
    BorderLeft,
    BorderRight,
    BorderTop,
    BorderBottom,
};

class CYPRESS_DLL_API HCMenuItemCtrl : public HCBaseCtrl
{
public:
    HCMenuItemCtrl();
    ~HCMenuItemCtrl();
public:

    //***************************************************************
    // *  功　　能:
    // *  入口参数: pSurf：图片
    // *            stepWidth：每帧宽度
    // *            height：图片高度
    // *            time：帧更新时间
    // *  出口参数:
    // *  返 回 值:
    //***************************************************************
	void SetImage(const HCHAR* pFormat, HINT pictureNum, HINT stepWidth, HINT height, HINT time );
    // 返回图片显示的宽度和高度
    void GetImageShowSize(HINT& width, HINT& height);
    // 设置图片的左上角坐标
    void SetImagePos(HINT x, HINT y);
    // 设置缩略图，有缩略图时自动替换掉图像的显示
    void SetThumbNail(IReSurface* pSurf);

    void SetBorderSurf(IReSurface* pSurf, HINT x, HINT y, eBorderDirection direction);
    void SetBorderSurf(const HCHAR* path, HINT x, HINT y, eBorderDirection direction);
	void SetPressedShaderSurf(IReSurface* pSurf);

	void SetLongPressTime(HINT time);
    //创建文本surface
    void CreateTextSurf();
	void CreateDesableTextSurf();
    //设置文字阴影
    void SetTextShaderSurf(IReSurface* pSurf);
    //设置文字的中心位置
    void SetTextPos(HINT x, HINT y);

    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);
	//设置区域阴影
	void SetChageAshSur(IReSurface *pSur);
	//设置是否显示阴影
	void SetChageAsh(HBOOL bIN);
    //按钮按下回调
    void SetCallBackDown(void (*callback)(void*, void*), void*);
    //按钮弹起回调
    void SetCallBackUp(void (*callback)(void*, void*), void*);
    //长按消息
    void SetCallBackLongPress(void (*callback)(void*, void*), void*);

	HINT GetLangID(void)
	{
		return m_nLangID;
	}
	void SetLangID(HINT a_nLangID)
	{
		m_nLangID = a_nLangID;
	}

	void OnFocus();

	void EnableImagePlay(HBOOL bEnable);

	void ReleaseImageSurf();

	void EnableDesableState(HBOOL bEnable);
	bool IsDesableState();

	void EnableCurSource(HBOOL bEnable);
	void SetCurSourceSurf(const HCHAR* pFilePath);

	//设置显示文字
	void SetText(HString strText);
	void SetTextStyle(HWORD textStyle);
	void SetTextColor(int r, int g , int b);
	void SetTextColor(RECOLOR color);
	void SetTextColorD(int r, int g , int b);
	void SetTextColorD(RECOLOR color);

	HString GetText(void);
private:
    HINT  m_nLangID;

    sBorderSurf m_CursorLeftSurf;
    sBorderSurf m_CursorRightSurf;
    sBorderSurf m_CursorTopSurf;
    sBorderSurf m_CursorBottomSurf;

    //边框
    sBorderSurf m_LeftSurf;
    sBorderSurf m_RightSurf;
    sBorderSurf m_TopSurf;
    sBorderSurf m_BottomSurf;
	//PressedShader
	IReSurface* m_pPressedShaderSurf;

	//字体大小 颜色
	HWORD m_TextStyle;
	HString m_strTxt;
	RECOLOR   m_colorDesableText;
	RECOLOR   m_colorText;
    //文字位置,居中
    HINT m_nTextPosX;
    HINT m_nTextPosY;
    IReSurface* m_pTextShaderSurf;
    IReSurface* m_pTextSurf;
	IReSurface* m_pDesableTextSurf;
    //图片
	vector<IReSurface*> m_pImageSurfVec;
    HINT m_nImageStepWidth;
    HINT m_nImageHeight;
    HINT m_nRefreshTime;//帧更新时间
    HINT m_nRefreshBaseTime;//基准时间
    HINT m_nIndex;//显示到第几帧
	HString m_strFormat;

    HBOOL m_bCanRefresh;//能够切换帧

    HINT m_nImagePosX;
    HINT m_nImagePosY;

	HBOOL m_bEnableImagePlay;
    //缩略图
    IReSurface* m_pThumbNailSurf;
	IReSurface* m_pChangeAshSur;
	HBOOL m_bChagerAsh;
    //按钮按下时回调函数变量,要传入类指针
    void (*m_pCallBackDown)(void *, void *);
    //按钮弹起时回调函数变量,要传入类指针
    void (*m_pCallBackUp)(void *, void *);

    // 鼠标长按消息
    void (*m_pCallBackLongPress)(void *, void *);


    HINT m_longPressTime;
    HINT m_baseTime;
    HBOOL m_bHaveExecute;
    HBOOL m_bOutOfRange;

	HBOOL m_bDesable;

	HBOOL m_bCurSource;
	IReSurface* m_pCurSourceSurf;

};