#ifndef _CFG_STRUCT_H
#define _CFG_STRUCT_H

#define  COL_NUM 2
#include <vector>
#include "Type.h"

struct UICORE_DLL_API INICOLOR
{
    HINT r;
    HINT g;
    HINT b;
    INICOLOR()
    {
        r = 0;
        g = 0;
        b = 0;

    }
    INICOLOR(HINT _r, HINT _g , HINT _b)
    {
        r = _r;
        g = _g;
        b = _b;
    }
    INICOLOR& operator=(const INICOLOR& color)
    {

        r = color.r;
        g = color.g;
        b = color.b;
        return *this;
    };


};

struct UICORE_DLL_API HBaseCtrlProp
{
    HINT m_eWndType;
    HINT  m_width;
    HINT  m_height;
    HINT  m_x;
    HINT  m_y;
    INICOLOR m_clrTextN;
    INICOLOR m_clrTextA;
    INICOLOR m_clrTextS;

    HINT m_nOpacity;
    //是否可以获取焦点
    HINT m_bCanFocus;
    //是否可用
    HINT m_bEnable;
    //是否可以接受消息
    HINT m_bGetMsg;
    //是否显示
    HINT m_bShow;
    //控件名字
    HString m_strCtrlName;

    //使用字体顺序
    HINT m_font;
    HINT m_fontWidth;
    HINT m_fontHeight;

    HBaseCtrlProp()
    {
        m_eWndType = 0;
        m_width = 0;
        m_height = 0;
        m_x = 0;
        m_y = 0;
        m_nOpacity = 16;
        m_bCanFocus = 1;
        m_bEnable = 1;
        m_bGetMsg = 1;
        m_strCtrlName = _T("");
        m_font = 0;
        m_fontWidth = 0;
        m_fontHeight = 0;
    }
    void BaseSet(HBaseCtrlProp* newProp)
    {
        m_eWndType = newProp->m_eWndType;
        m_width = newProp->m_width;
        m_height = newProp->m_height;
        m_x = newProp->m_x;
        m_y = newProp->m_y;
        m_nOpacity = newProp->m_nOpacity;
        m_bCanFocus = newProp->m_bCanFocus;
        m_bEnable = newProp->m_bEnable;
        m_bGetMsg = newProp->m_bGetMsg;
        m_strCtrlName = newProp->m_strCtrlName;
        m_font = newProp->m_font;
        m_fontWidth = newProp->m_fontWidth;
        m_fontHeight = newProp->m_fontHeight;
    };

    virtual HBaseCtrlProp* Clone() const
    {
        return NULL;
    }
};


struct UICORE_DLL_API HButtonProp : public HBaseCtrlProp
{


    //按钮图标图
    HString m_pIcon;
    HINT      m_bIconResOut;

    //常规背景图
    HString m_pBkgndN;
    HINT      m_bBNResOut;

    //激活背景图
    HString m_pBkgndA;
    HINT      m_bBAResOut;


    //聚焦背景图
    HString m_pBkgndF;
    HINT      m_bBFResOut;

    //文字位置
    HINT m_nTextPosX;
    HINT m_nTextPosY;

	HBOOL m_bEnableNewLine;
	HINT m_TextWidth;
	HINT m_TextHeight;
	HINT m_LineSpace;


    //图标位置
    HINT m_nIconPosX;
    HINT m_nIconPosY;

    //文字对齐方式 居中，靠左 靠右
    HBYTE m_TextAlign;
    HString m_strTxt;
    HButtonProp()
    {
        m_eWndType = 2;
        m_pIcon = _T("");
        m_pBkgndN = _T("");
        m_pBkgndA = _T("");
        m_pBkgndF = _T("");
        m_strTxt = _T("");
        m_nTextPosX = 0;
        m_nTextPosY = 0;
		m_bEnableNewLine = false;
		m_TextWidth = 0;
		m_TextHeight = 0;
		m_LineSpace = 0;
        m_TextAlign = 0;
        m_clrTextN = INICOLOR(255, 255, 255);
        m_clrTextA = INICOLOR(0, 0, 0);
        m_clrTextS = INICOLOR(200, 200, 200);
        m_nIconPosX = 0;
        m_nIconPosY = 0;
        m_bBFResOut = 1;
        m_bBNResOut = 1;
        m_bBAResOut = 1;
        m_bIconResOut = 1;
    }
    void BtnSet(HButtonProp* newBtnProp)
    {

        m_pIcon = newBtnProp->m_pIcon;
        m_nTextPosX = newBtnProp->m_nTextPosX;
        m_nTextPosY = newBtnProp->m_nTextPosY;
        m_TextAlign = newBtnProp->m_TextAlign;
        m_clrTextN = newBtnProp->m_clrTextN;
        m_clrTextA = newBtnProp->m_clrTextA;
        m_clrTextS = newBtnProp->m_clrTextS;

        m_pBkgndN = newBtnProp->m_pBkgndN;
        m_pBkgndA = newBtnProp->m_pBkgndA;
        m_pBkgndF = newBtnProp->m_pBkgndF;
        m_strTxt = newBtnProp->m_strTxt;
        m_nIconPosX = newBtnProp->m_nIconPosX;
        m_nIconPosY = newBtnProp->m_nIconPosY;
        m_bBFResOut = newBtnProp->m_bBFResOut;
        m_bBNResOut = newBtnProp->m_bBNResOut;
        m_bBAResOut = newBtnProp->m_bBAResOut;
        m_bIconResOut = newBtnProp->m_bIconResOut;


        BaseSet((HBaseCtrlProp*)newBtnProp);
    };

    virtual HBaseCtrlProp* Clone() const
    {
        return new HButtonProp(*this);
    }

};

struct UICORE_DLL_API HCheckBoxProp : public HButtonProp
{
    HCheckBoxProp()
    {
        m_eWndType = 5;
    }
    void CKSet(HCheckBoxProp* newCKboxProp)
    {
        BtnSet(newCKboxProp);
    };

    virtual HBaseCtrlProp* Clone() const
    {
        return new HCheckBoxProp(*this);
    }
};


struct UICORE_DLL_API HRadioBoxProp : public HCheckBoxProp
{
    HINT GroupID;
    HRadioBoxProp()
    {
        GroupID = 0;
        m_eWndType = 6;

    }
    void RDBoxSet(HRadioBoxProp * newRDboxProp)
    {
        GroupID = newRDboxProp->GroupID;
        BtnSet(newRDboxProp);

    };

    virtual HBaseCtrlProp* Clone() const
    {
        return new HRadioBoxProp(*this);
    }
};


struct UICORE_DLL_API HListBoxProp   : public HBaseCtrlProp
{
    HString m_pBkgndN; //file name of Normal back
    HINT      m_bBNResOut;

    //激活背景图
    HString m_pBkgndA;//file name of active back
    HINT      m_bBAResOut;
    //列
    HINT m_nCol;
    //行
    HINT m_nRow;
    //行高
    HINT m_nHeight;

    //列表显示项第一项位置,从0开始
    HINT m_nPos;
    //文字起始位置
    HINT m_nColx[COL_NUM];
    HINT m_nColy[COL_NUM];

    //文字显示宽度
    HINT m_nColw[COL_NUM];
    HListBoxProp()
    {
        m_pBkgndN = _T("");
        m_pBkgndA = _T("");
        m_nCol = 0;
        m_nRow = 0;
        m_nHeight = 0;
        m_nPos = 0;
        m_nColx[0] = 0;
        m_nColx[1] = 0;
        m_nColy[0] = 0;
        m_nColy[1] = 0;
        m_nColw[0] = 0;
        m_nColw[1] = 0;
        m_eWndType = 4;
        m_bBNResOut = 1;
        m_bBAResOut = 1;

    }
    void ListBoxSet(HListBoxProp* newListBoxProp)
    {
        m_pBkgndN = newListBoxProp->m_pBkgndN;
        m_pBkgndA = newListBoxProp->m_pBkgndA;
        m_nCol = newListBoxProp->m_nCol;
        m_nRow = newListBoxProp->m_nRow;
        m_nHeight = newListBoxProp->m_nHeight;
        m_nPos = newListBoxProp->m_nPos;
        m_nColx[0] = newListBoxProp->m_nColx[0];
        m_nColx[1] = newListBoxProp->m_nColx[1];
        m_nColy[0] = newListBoxProp->m_nColy[0];
        m_nColy[1] = newListBoxProp->m_nColy[1];
        m_nColw[0] = newListBoxProp->m_nColw[0];
        m_nColw[1] = newListBoxProp->m_nColw[1];
        m_bBNResOut = newListBoxProp->m_bBNResOut;
        m_bBAResOut = newListBoxProp->m_bBAResOut;
        m_clrTextN = newListBoxProp->m_clrTextN;
        m_clrTextA = newListBoxProp->m_clrTextA;
        m_clrTextS = newListBoxProp->m_clrTextS;

        BaseSet(newListBoxProp);

    };

    virtual HBaseCtrlProp* Clone() const
    {
        return new HListBoxProp(*this);
    }
};

struct UICORE_DLL_API HSliderProp : public HBaseCtrlProp
{
    //滑动条最大值，最小值
    HINT  m_nMin;
    HINT  m_nMax;
    //常规背景图
    HString m_pBkgndN;
    HINT m_bBNResOut;

	HString m_pBkgndS;
    //滑动条游标图
    HString m_pBkgndA;
    HINT m_bBAResOut;
    //游标图起始位置偏移
    HINT m_nEx;
    HINT m_eDir;
    HSliderProp()
    {
        m_eWndType = 7;
        m_nMin = 0;
        m_nMax = 0;
        m_pBkgndN = _T("");
		m_pBkgndS = _T("");
        m_pBkgndA = _T("");
        m_nEx = 0;
        m_eDir = 0;
        m_bBNResOut = 1;
        m_bBAResOut = 1;

    }
    void SliderSet(HSliderProp* newSliderProp)
    {
        BaseSet(newSliderProp);
        m_nMin = newSliderProp->m_nMin;
        m_nMax = newSliderProp->m_nMax;
        m_pBkgndN = newSliderProp->m_pBkgndN;
        m_pBkgndA = newSliderProp->m_pBkgndA;
        m_nEx = newSliderProp->m_nEx;
        m_eDir = newSliderProp->m_eDir;
        m_bBNResOut = newSliderProp->m_bBNResOut;
        m_bBAResOut = newSliderProp->m_bBAResOut;
    };

    virtual HBaseCtrlProp* Clone() const
    {
        return new HSliderProp(*this);
    }

};

struct UICORE_DLL_API HTextProp : public HBaseCtrlProp
{
    //常规背景图
    HString m_pBkgndN;//file name of Nomal back
    HINT      m_bBNResOut;

    //文字位置
    HINT m_nTextPosX;
    HINT m_nTextPosY;

    //文字对齐方式 居中，靠左 靠右
    HBYTE m_TextAlign;

    //文字颜色
    INICOLOR m_clrText;
    HDWORD m_clrRectA;
    HDWORD m_clrRectB;
    HDWORD m_clrRect;
    HINT   m_FillType;//0:图片 1：色块 2： v渐变  3: h渐变 4:alpha 渐变 5：none
    HString   m_strTxt;

    HTextProp()
    {
        m_eWndType = 3;
        m_strTxt = _T("");
        m_TextAlign = 0;
        m_nTextPosX = 0;
        m_nTextPosY = 0;
        m_pBkgndN = _T("");
        m_clrText = INICOLOR();
        m_bBNResOut = 0;
        m_FillType = 0;
        m_clrRectA = 0;
        m_clrRectB = 0;
        m_clrRect = 0;

    }
    void TextSet(HTextProp* newTextProp)
    {
        BaseSet(newTextProp);
        m_strTxt = newTextProp->m_strTxt;
        m_TextAlign = newTextProp->m_TextAlign;
        m_nTextPosX = newTextProp->m_nTextPosX;
        m_nTextPosY = newTextProp->m_nTextPosY;
        m_pBkgndN = newTextProp->m_pBkgndN;
        m_clrText = newTextProp->m_clrText;
        m_bBNResOut = newTextProp->m_bBNResOut;
        m_FillType = newTextProp->m_FillType;
        m_clrRectA = newTextProp->m_clrRectA;
        m_clrRectB = newTextProp->m_clrRectB;
        m_clrRect = newTextProp->m_clrRect;
    };
    virtual HBaseCtrlProp* Clone() const
    {
        return new HTextProp(*this);
    }

};


struct UICORE_DLL_API HProgressCtrlProp : public HBaseCtrlProp
{
    HString m_pBkgndN;
    HINT m_bBNResOut;

    //进度条图
    HString m_pBkgndA;
    HINT m_bBAResOut;


    HINT m_Min;
    HINT m_Max;

    HINT m_pos;
    HProgressCtrlProp()
    {
        m_eWndType = 8;
        m_Min = 0;
        m_Max = 100;
        m_pos = 0;
        m_bBNResOut = 0;
        m_bBAResOut = 0;
        m_pBkgndN = _T("");
        m_pBkgndA = _T("");
    }

    void ProcessSet(HProgressCtrlProp* newProcessCtrl)
    {
        m_Min = newProcessCtrl->m_Min;
        m_Max = newProcessCtrl->m_Max;
        m_pos = newProcessCtrl->m_pos;
        m_bBNResOut = newProcessCtrl->m_bBNResOut;
        m_bBAResOut = newProcessCtrl->m_bBAResOut;
        m_pBkgndN = newProcessCtrl->m_pBkgndN;
        m_pBkgndA = newProcessCtrl->m_pBkgndA;
        BaseSet(newProcessCtrl);
    }
    virtual HBaseCtrlProp* Clone() const
    {
        return new HProgressCtrlProp(*this);
    }
};

struct UICORE_DLL_API HImageCtrlProp : public HBaseCtrlProp
{
    HINT m_bBNResOut;
    HString m_pBkgndN;
    HINT m_msTime;
    //步长值
    HINT m_nStep;

    //此成员只在工具中使用
    BOOL m_bPlay;

    HImageCtrlProp()
    {
        m_bBNResOut = 0;
        m_pBkgndN = _T("");
        m_msTime = 10;
        m_nStep = 0;
        m_eWndType = 9;
        m_bPlay = FALSE;
    }
    void ImageCtrlSet(HImageCtrlProp* newImageCtrl)
    {
        m_bBNResOut = newImageCtrl->m_bBNResOut;
        m_pBkgndN = newImageCtrl->m_pBkgndN;
        m_msTime = newImageCtrl->m_msTime;
        m_nStep = newImageCtrl->m_nStep;
        m_bPlay = FALSE;
        BaseSet(newImageCtrl);
    }
    virtual HBaseCtrlProp* Clone() const
    {
        return new HImageCtrlProp(*this);
    }
};

struct UICORE_DLL_API HGroupCtrlProp : public HBaseCtrlProp
{
    vector<HBaseCtrlProp*> m_baseCtrlProp;
    HString m_pBackGroud;
    HBOOL m_bOutRes;

    HGroupCtrlProp()
    {
        m_baseCtrlProp.clear();
        m_pBackGroud = _T("");
        m_bOutRes = FALSE;
    }

    void GroupCtrlSet(HGroupCtrlProp* newGroupCtrl)
    {
        m_pBackGroud = newGroupCtrl->m_pBackGroud;
        m_bOutRes = newGroupCtrl->m_bOutRes;

        BaseSet(newGroupCtrl);
    }

    virtual HGroupCtrlProp* Clone() const
    {
        return new HGroupCtrlProp(*this);
    }
};

struct UICORE_DLL_API HScrollBoxProp : public HBaseCtrlProp
{
	HString m_pBackGroud;
	HBOOL m_bOutRes;
	HString m_SliderBkgSurf;
	HString m_SliderSurf;

	HScrollBoxProp()
	{
		m_pBackGroud = _T("");
		m_bOutRes = FALSE;
		m_SliderBkgSurf = _T("");
		m_SliderSurf = _T("");
	}

	void ScrollBoxSet(HScrollBoxProp* newGroupCtrl)
	{
		m_pBackGroud = newGroupCtrl->m_pBackGroud;
		m_bOutRes = newGroupCtrl->m_bOutRes;
		m_SliderBkgSurf = newGroupCtrl->m_SliderBkgSurf;
		m_SliderSurf = newGroupCtrl->m_SliderSurf;

		BaseSet(newGroupCtrl);
	}

	virtual HScrollBoxProp* Clone() const
	{
		return new HScrollBoxProp(*this);
	}
};

// 键盘控件属性
struct UICORE_DLL_API HKeyBoardProp : public HBaseCtrlProp
{
	HString m_pBkgndN;
	HINT m_bBNResOut;

	HString m_pBkgndA;
	HINT m_bBAResOut;

	HString m_pBkgndF;
	HINT m_bBFResOut;
	// 行数
	HINT m_iRowNum;
	// 列数
	HINT m_iColNum;

	// 列的偏移量,即从这列开始显示
	HINT m_iOffset;
	HString m_strTxt;
	//键盘按钮间隔
	HINT m_iAlternationX;
	HINT m_iAlternationY;

	HBOOL m_bStretch;

	HKeyBoardProp()
	{
		m_pBkgndN = _T("");
		m_pBkgndA = _T("");
		m_pBkgndF = _T("");
		m_iRowNum = (int)0;
		m_iColNum = (int)0;
		m_iOffset = (int)0;// 列的偏移量,即从这列开始显示
		m_strTxt = _T("");
		m_iAlternationX = (int)0;
		m_iAlternationY = (int)0;

		m_bBNResOut = (bool)0;
		m_bBAResOut = (bool)0;
		m_bBFResOut = (bool)0;

		m_bStretch = (bool)0;
	}

	void KeyBoardPropSet(HKeyBoardProp* newKeyBoardProp)
	{
		m_pBkgndN = newKeyBoardProp->m_pBkgndN;
		m_pBkgndA = newKeyBoardProp->m_pBkgndA;
		m_pBkgndF = newKeyBoardProp->m_pBkgndF;
		m_iRowNum = newKeyBoardProp->m_iRowNum;
		m_iColNum = newKeyBoardProp->m_iColNum;
		m_iOffset = newKeyBoardProp->m_iOffset;
		m_strTxt = newKeyBoardProp->m_strTxt;
		m_iAlternationX = newKeyBoardProp->m_iAlternationX;
		m_iAlternationY = newKeyBoardProp->m_iAlternationY;

		m_bBNResOut = newKeyBoardProp->m_bBNResOut;
		m_bBAResOut = newKeyBoardProp->m_bBAResOut;
		m_bBFResOut = newKeyBoardProp->m_bBFResOut;

		m_bStretch = newKeyBoardProp->m_bStretch;
		BaseSet(newKeyBoardProp);
	}

	// 克隆一个新对象
	virtual HKeyBoardProp* Clone() const
	{
		return new HKeyBoardProp(*this);
	}
};

struct UICORE_DLL_API HDialogProp
{
    vector<HBaseCtrlProp*> CtrlList;
    HINT m_x;
    HINT m_y;
    HINT m_width;
    HINT m_height;
    HString strBackGndFileName;
    INICOLOR m_clrline;
    HINT   m_lineWidth;
    HINT m_BkgntOutRes;

    HDialogProp()
    {
        CtrlList.empty();
        m_x = 0;
        m_y = 0;
        m_width = SCREEN_WIDTH;
        m_height = SCREEN_HEIGHT;
        m_clrline.r = 255;
        m_clrline.g = 255;
        m_clrline.b = 0;
        m_lineWidth = 2;
        m_BkgntOutRes = 0;

    };
    virtual HDialogProp* Clone() const
    {
        return new HDialogProp(*this);
    }
};

#endif