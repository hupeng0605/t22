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
#define ANIMATION_BTN_BACK_HIDE 1 //��ʾ����ͼ��ʱ���ذ�ť����
#define ANIMATION_BTN_ICON_HIDE 2 //��ʾ����ͼ��ʱ���ذ�ťͼ��
#define ANIMATION_BTN_SET_POS   4 //��ʾ����ͼ��ʱ��������ͼ��λ�ö��밴ť

class HCImageCtrl;

class UICORE_DLL_API HCButton : public HCBaseCtrl
{
public:
    HCButton();
    virtual ~HCButton();
    //��Ϣ�������������඼Ҫ����
    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);

    //���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
    void SetBkgndN(IReSurface* pSur);
    void SetBkgndN(const HString& pFileName);
    //ȡ�ð�ť����
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

	//ȡ�ð�ť����ͼ�����Խ��п����ͻ��Ʋ���
	IReSurface* GetBKgndN();
	IReSurface* GetBKgndA();
	IReSurface* GetBKgndF();

    void SetText(const HCHAR* pTxt, HINT x, HINT y, HWORD type = RE_TS_NORMAL);
    void SetText(const HCHAR* pTxt);
	void AddText(const HCHAR* pTxt);
    void SetTextPos(HINT x , HINT y); //
    void SetTextStyle(HWORD type); //�����ı���ʾ����
	void SetTextRect(HINT width, HINT height); //���û����ı���ʾ��Χ
	void EnableNewLine(HBOOL bEnable); //�Ƿ���Ի���
	void SetLineSpace(HINT height); //���
	HString GetText();

    //����͸����
    void SetOpacity(HBYTE nTrans);

    //��ť���»ص�
    void SetCallBackDown(void (*callback)(void*, void*), void*);
    //��ť����ص�
    void SetCallBackUp(void (*callback)(void*, void*), void*);
    //��ȡ����ص�
    void SetCallBackOnFocus(void (*callback)(void*, void*), void*);
    //ʧȥ����ص�
    void SetCallBackLostFocus(void (*callback)(void*, void*), void*);
    //����ƶ���Ϣ
    void SetCallBackMouseMove(void (*callback)(void*, void*), void*);
	//������Ϣ
	void SetCallBackLongPress(void (*callback)(void*, void*), void*);
	void SetCallBackLongPressUp(void (*callback)(void*, void*), void*);

	void EnableLongPressConsecutive(HBOOL bEnable, HINT times = 50);

//     ���ö���ͼ��
//     #define ANIMATION_BTN_BACK_HIDE 1 //��ʾ����ͼ��ʱ���ذ�ť����
//     #define ANIMATION_BTN_ICON_HIDE 2 //��ʾ����ͼ��ʱ���ذ�ťͼ��
//     #define ANIMATION_BTN_SET_POS   4 //��ʾ����ͼ��ʱ��������ͼ��λ�ö��밴ť
    void SetAnimationIcon(HCImageCtrl* pIcon, HDWORD type);

    virtual void GetBackSufSize(HINT& x, HINT& y);
	//�Ƿ������峬�����
	void SetEnableTruncationFont(HBOOL m_bEnable);
	//��ȡ����
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

	//��ȡ����ʱ���� ����
	void OnFocus();
	//ʧȥ����ʱ���� ����
	void OnLostFocus();

	//�Ƿ������Զ�����Ϣ��Ӧ������Կؼ�������
	void EnableOwnerMsgRecvRect(HBOOL bEnable, kn_rect* pRectMsgRecv );

protected:
    HBOOL CheckPoint(HINT x, HINT y);
    //void OnShow();
    void OnHide();

private:
	void RenderTextSurface();

protected:
	HINT	m_nLangID;
    //��ťͼ��ͼ
    IReSurface* m_pIcon;
    HBOOL m_bIconRes;

	IReSurface* m_pIconA;
	HBOOL m_bIconARes;

	IReSurface* m_pIconF;
	HBOOL m_bIconFRes;

    //���汳��ͼ
    IReSurface* m_pBkgndN;
    HBOOL m_bBkgndNRes;

	//����ͼ
	IReSurface*	m_pBkgndDisable;
	HBOOL		m_bBkgndDisableRes;

    //�����ͼ
    IReSurface* m_pBkgndA;
    HBOOL m_bBkgndARes;

    //�۽�����ͼ
    IReSurface* m_pBkgndF;
    HBOOL m_bBkgndFRes;

    //����λ��
    HINT m_nTextPosX;
    HINT m_nTextPosY;

    //ͼ��λ��
    HINT m_nIconPosX;
    HINT m_nIconPosY;

    //���ֶ��뷽ʽ ���У����� ����
    HWORD m_TextStyle;

    HString m_strTxt;

	HINT m_TextWidth;//����������
	HINT m_TextHeight;//��������߶�
	HINT m_TextRowSpace;//��������֮��ľ���
	HBOOL m_bEnableNewLine;//������
	IReSurface* m_pTextSurf;

    //������ťʹ�õĶ���ͼ��,����ǿձ�ʾ�Ƕ�����ť
    HCImageCtrl* m_pImageCtrl;
    HDWORD    m_eAnimationType;


    //��ť����ʱ�ص���������,Ҫ������ָ��
    void (*m_pCallBackDown)(void *, void *);
    //��ť����ʱ�ص���������,Ҫ������ָ��
    void (*m_pCallBackUp)(void *, void *);

    //��ť����ʱ�ص���������,Ҫ������ָ��
    void (*m_pCalllBackOnFocus)(void *, void *);
    //��ť����ʱ�ص���������,Ҫ������ָ��
    void (*m_pCallBackLostFocus)(void *, void *);

    // ����ƶ���Ӧ��Ϣ
    void (*m_pCallBackMouseMove)(void *, void *);

	// ��곤����Ϣ
	void (*m_pCallBackLongPress)(void *, void *);
	void (*m_pCallBackLongPressUp)(void *, void *);

	HINT m_longPressTime;
	HINT m_baseTime;
	HBOOL m_bHaveExecute;
	HBOOL m_bOutOfRange;
	HBOOL m_bEnableInterceptFont;
	
	//����������Ӧ��Ϣ
	HBOOL m_bEnableLongPressConsecutive;
	HINT m_LongPressTimeConsecutive;
	//��ť��ŵı�ʶ��
	HINT m_nTagIndex;

	HBOOL m_bEnableOwnerMsgRecv;
	kn_rect m_rectMsgRecv;
};

#endif // !defined(AFX_KCBUTTON_H__A1D31C49_3686_4A89_A80B_63B62A737FD6__INCLUDED_)
