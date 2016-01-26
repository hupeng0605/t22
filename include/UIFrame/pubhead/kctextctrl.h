


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

    //�����ı�
    void SetText(const HCHAR* pTxt, HINT x , HINT y, HWORD type = RE_TS_NORMAL);
    void SetText(const HCHAR* pTxt);
    void SetTextPos(HINT x , HINT y);
    void SetTextStyle(HWORD type);

    //�����ַ�
    void AddChar(HCHAR c);

    // ADD.              .2007.4.12.
    // --Begin-----------------------------------------------------------------

    // �����ı�
    void AppendText(const HCHAR* str);

    // �����ַ�������nPosΪ-1������ַ������룬�����ĩβ����
    void InsertText(const HCHAR* str, HINT nPos = -1);

    // ����һ��(�����ַ�������bCaretPosΪtrue������ַ���ɾ���������ĩβɾ��)
    void Backspace(HBOOL bFromCaretPos = true);

    // --End-------------------------------------------------------------------

    //ȡ���ı�
    HString GetText();

    // ADD.              .2007.4.12.������
    // --Begin-----------------------------------------------------------------
    CARET_MODE GetCaretMode();
    void SetCaretMode(CARET_MODE mode);

    // ���ַ��ߴ�
    void GetCaretSize(HINT& nWidth, HINT& nHeight);
    void SetCaretSize(HINT nWidth, HINT nHeight);

	 //���ַ�����ʾ��񣬷�����ͺ���
	CARET_STYLE GetCaretStyle();
	void SetCaretStyle(CARET_STYLE style);

    // ���ַ���ɫ
    void SetCaretColor(HBYTE r, HBYTE g, HBYTE b);
    void SetCaretColor(RECOLOR& clr);

    // ���ַ��Ƿ���˸
    HBOOL IsCaretBlink();
    void SetCaretBlink(HBOOL bBlink);

    // ���ַ���˸���ʱ��
    HUINT GetCaretBlinkTime();
    void SetCaretBlinkTime(HUINT nTime);

    // ��ȡ���ַ�λ�ã��ַ�Ϊ��λ
    HINT GetCaretPos();

    // �������ַ���λ��(bMakeCaretInSightΪtrueʱ����֤���ַ�һ���ڿ���������)
    void SetCaretPos(HINT nPos, HBOOL bMakeCaretInSight = false);

    HINT GetSelLength();
    void SetSelLength(HINT nSelLength);

    // ������֮�󶨵����������ƶ����İ�ť
    void SetLRButton(HCButton* lBtn, HCButton* rBtn);
    // --End-------------------------------------------------------------------

    //��Ϣ�������������඼Ҫ����
    HBOOL DoMessage(HMessage* msg);
    void Draw(IReSurface* pSurface);

    HBOOL IsCanFocus();

    //���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
    void SetBkgndN(IReSurface* pSur);
    void SetBkgndN(const HString& pFileName);
    void SetFillColor(HDWORD clrA, HDWORD clrB = 0, HDWORD clrC = 0);
    void SetFillType(HINT typ);
    void SetTxtColor(int r , int g , int b);

    void SetRoll(HBOOL roll);
	void SetMultiline(HBOOL multi);

    virtual void GetBackSufSize(HINT& x, HINT& y);
	// ���ﲿ��
	HINT GetLangID(void)
	{
		return m_nLangID;
	}
	void SetLangID(HINT a_nLangID)
	{
		m_nLangID = a_nLangID;
	}

	void SetCallBackDown(void (*callback)(void*, void*), void*);
	// ���������ʾ
	void EnableDot(HBOOL bDot);
	//�������ֹ����Ŀ��
	void SetRollWidth(HINT nWidth);
protected:
    void IsNeedRoll();
    HBOOL CheckPoint(HINT x, HINT y);

    // ADD.              .2007.4.12
    // --Begin-----------------------------------------------------------------
    HBOOL HasCaret();
    HBOOL IsCaretShow();

    // �������ַ���Χ�����ⳬ��
    HINT AdjustCaretPos(HINT nPos);

    // ����ƫ��ʹ���ַ������ڿ��ӷ�Χ
    void MakeCaretInSight();

    // ��ȡָ�������ŵ��ַ���������λ��(����ı����Ͻ�)
    void GetPosFromChar(HINT iCharIndex, HINT& x, HINT& y);

    // ��ȡĿǰ�ɿ������ַ�����
    HINT GetVisibleCharNumber();

    // ��ȡ����ַ���ƫ����
    HINT GetMaxOffset();

    // ����Change�¼�
    void OnChange();

    static void OnBtnLR(void* p, void* pParam);
    void OnBtnLR(void* pParam);
    // ��ȡm_strTxtָ����Χ�Ŀ��(�������ַ�),0<=iStartPos<=iEndPos<=m_strTxt.size().
    HINT GetStrTextWidth(HINT iStartPos, HINT iEndPos);
    // --End-------------------------------------------------------------------
	
protected:
	HINT	m_nLangID;
    //���汳��ͼ
    IReSurface* m_pBkgndN;
    HBOOL m_bBkgndNRes;

    //����λ��
    HINT m_nTextPosX;
    HINT m_nTextPosY;

    //������ʽ
    HWORD m_TextStyle;

    //��䷽ʽ
    HBYTE m_FillType;
    //������ɫ
    RECOLOR m_clrText;
    HDWORD m_clrRectA;
    HDWORD m_clrRectB;
    HDWORD m_clrRect;

    HString m_strTxt;

    HINT m_broll;
    HINT m_nStrOutSize;
    HINT m_nStrOut;
    HBOOL m_bOut;

    // ADD.              .2007.4.12.���ַ����
    // --Begin-----------------------------------------------------------------
    CARET_MODE m_CaretMode;     // ���ַ���ʾģʽ
	CARET_STYLE m_CaretStyle;    // ���ַ���ʾ���
    HINT m_nCaretWidth;       // ���ַ���
    HINT m_nCaretHeight;      // ���ַ���
    RECOLOR m_clrCaret;         // ���ַ���ɫ
    HBOOL m_bCaretBlink;      // ���ַ��Ƿ���˸
    HUINT m_nCaretBlinkTime;  // ���ַ���˸ʱ��(10msΪ��λ)
    HINT m_nCaretPos;         // ���ַ���ǰλ��(���ַ���Ϊ��λ,0��ʼ)
    HINT m_nSelLength;        // ѡ���ı��ĳ���(������ʾ���ѡ��)

    HINT m_iCaretState;       // ���ַ�״̬(0:��ʧ;1:����)
    HINT m_iBaseTime;         // ��¼��˸�Ļ�׼ʱ���
    HCButton* m_btnLeft;        // �󶨵�����ť�������ƶ����ַ�
    HCButton* m_btnRight;       // �󶨵��ҷ���ť�������ƶ����ַ�

	void (*m_pCallBackDown)(void*, void*);
	HBOOL m_bEnableDot;
	//�������ֹ����Ŀ��
	HINT m_nRollWidth;
    // --End-------------------------------------------------------------------

	/* 20140519 jinlingw: BEGIN ADD("������ʾ")  */
	HBOOL m_bMultiline;
	/* 20140519 jinlingw: BEGIN ADD("������ʾ")  */
};

#endif // !defined(AFX_KCTEXTCTL_H__191B5196_9FC3_4F4F_B194_CCC17DF27244__INCLUDED_)
