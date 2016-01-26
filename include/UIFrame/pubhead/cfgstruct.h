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
    //�Ƿ���Ի�ȡ����
    HINT m_bCanFocus;
    //�Ƿ����
    HINT m_bEnable;
    //�Ƿ���Խ�����Ϣ
    HINT m_bGetMsg;
    //�Ƿ���ʾ
    HINT m_bShow;
    //�ؼ�����
    HString m_strCtrlName;

    //ʹ������˳��
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


    //��ťͼ��ͼ
    HString m_pIcon;
    HINT      m_bIconResOut;

    //���汳��ͼ
    HString m_pBkgndN;
    HINT      m_bBNResOut;

    //�����ͼ
    HString m_pBkgndA;
    HINT      m_bBAResOut;


    //�۽�����ͼ
    HString m_pBkgndF;
    HINT      m_bBFResOut;

    //����λ��
    HINT m_nTextPosX;
    HINT m_nTextPosY;

	HBOOL m_bEnableNewLine;
	HINT m_TextWidth;
	HINT m_TextHeight;
	HINT m_LineSpace;


    //ͼ��λ��
    HINT m_nIconPosX;
    HINT m_nIconPosY;

    //���ֶ��뷽ʽ ���У����� ����
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

    //�����ͼ
    HString m_pBkgndA;//file name of active back
    HINT      m_bBAResOut;
    //��
    HINT m_nCol;
    //��
    HINT m_nRow;
    //�и�
    HINT m_nHeight;

    //�б���ʾ���һ��λ��,��0��ʼ
    HINT m_nPos;
    //������ʼλ��
    HINT m_nColx[COL_NUM];
    HINT m_nColy[COL_NUM];

    //������ʾ���
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
    //���������ֵ����Сֵ
    HINT  m_nMin;
    HINT  m_nMax;
    //���汳��ͼ
    HString m_pBkgndN;
    HINT m_bBNResOut;

	HString m_pBkgndS;
    //�������α�ͼ
    HString m_pBkgndA;
    HINT m_bBAResOut;
    //�α�ͼ��ʼλ��ƫ��
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
    //���汳��ͼ
    HString m_pBkgndN;//file name of Nomal back
    HINT      m_bBNResOut;

    //����λ��
    HINT m_nTextPosX;
    HINT m_nTextPosY;

    //���ֶ��뷽ʽ ���У����� ����
    HBYTE m_TextAlign;

    //������ɫ
    INICOLOR m_clrText;
    HDWORD m_clrRectA;
    HDWORD m_clrRectB;
    HDWORD m_clrRect;
    HINT   m_FillType;//0:ͼƬ 1��ɫ�� 2�� v����  3: h���� 4:alpha ���� 5��none
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

    //������ͼ
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
    //����ֵ
    HINT m_nStep;

    //�˳�Աֻ�ڹ�����ʹ��
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

// ���̿ؼ�����
struct UICORE_DLL_API HKeyBoardProp : public HBaseCtrlProp
{
	HString m_pBkgndN;
	HINT m_bBNResOut;

	HString m_pBkgndA;
	HINT m_bBAResOut;

	HString m_pBkgndF;
	HINT m_bBFResOut;
	// ����
	HINT m_iRowNum;
	// ����
	HINT m_iColNum;

	// �е�ƫ����,�������п�ʼ��ʾ
	HINT m_iOffset;
	HString m_strTxt;
	//���̰�ť���
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
		m_iOffset = (int)0;// �е�ƫ����,�������п�ʼ��ʾ
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

	// ��¡һ���¶���
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