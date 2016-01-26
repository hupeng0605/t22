/********************************************************************
    created:    2011/09/05
    created:    09:05:2011   10:47
    filename:   d:\code\try\newhmi\include\kcslidectrl.h
    file path:  d:\code\try\newhmi\include
    file base:  kcscrollctrl
    file ext:   h
    author:                   

    purpose:
*********************************************************************/


#if !defined(AFX_KCSCROLLCTRL_H__E8783179_BE3E_455F_A6EC_377F43DCFCF2__INCLUDED_)
#define AFX_KCSCROLLCTRL_H__E8783179_BE3E_455F_A6EC_377F43DCFCF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWnd.h"
#include "KCTextCtrl.h"
#define HORIZONTAL 0  //ˮƽ
#define VERTICAL 1 //��ֱ

enum SCROLLDIR
{
    SCROLL_MOVEUP,
    SCROLL_MOVE,
    SCROLL_CHANGE,
};

struct SCROLLPARA
{
    HBYTE eDir;
    HINT nValue;
};

class HCButton;
class HCScrollBox;
class UICORE_DLL_API HCScrollCtrl : public HCBaseCtrl
{
public:
    HCScrollCtrl();
    virtual ~HCScrollCtrl();

    // dirΪ�ؼ�����
    HBOOL Create(HINT x, HINT y, HINT w, HINT h, HBYTE dir);

    // ��Ϣ�������������඼Ҫ����
    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);

    // ���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
    void SetBkgndN(IReSurface* pSur);
    void SetBkgndN(const HString& pFileName);

    // ������ǰ��ͼ
    void SetBkgndA(IReSurface* pSur);
    void SetBkgndA(const HString& pFileName);

   // ������ǰ������ͼ
    void SetBkgndF(IReSurface* pSur);
    void SetBkgndF(const HString& pFileName);

	// ������ǰ������ͼ
	void SetBkgndD(IReSurface* pSur);
	void SetBkgndD(const HString& pFileName);

    // ���á���ȡ��ǰֵ
    void SetValue(HINT n);
    HINT GetValue();
	//	���õ�ǰֵ��չ����,bRoll��ʾ�Ƿ���Ҫ����
	void SetValueEx(HINT n, HBOOL bRoll=false);

    // ��������Χ
    void SetBound(HINT iMin, HINT iMax);
    HINT GetMaximum();
    HINT GetMinimum();

    // ������������value�İ�ť
    void SetAddButton(HCButton* btnSub, HCButton* btnAdd);
	//���ù������ö����õװ�ť
	void SetTopButton(HCButton* btnTop, HCButton* btnBottom);
	//����������ʾ������TXT�ı�
	void SetTextCtrl(HCTextCtrl* txtInd);
	//�����б��
	void SetScrollBox(HCScrollBox* pCtrl/*KCScrollBox�ؼ�*/, HINT nRows/*����ʾ������*/);/*��Ҫÿ�еĸ���ͬ*/


    void SetCallBackMouseUp(void (*callback)(void*, void*), void*);
	//����ƶ���Ϣ
	void SetCallBackMouseMove(void (*callback)(void*, void*), void*);


protected:

    // ͨ�������Value��ȡ��Ӧ������λ��(һ��Valueֻ��Ӧһ������)
    HINT GetPosFromValue(HINT);

    // ͨ�����������λ�û�ȡ��Ӧ��Value(������һ�������Ӧͬһ��Value)
    HINT GetValueFromPos(HINT,HBOOL bNear);

    // ���㻬���λ��
    void CalcThumbPos();
	void UpdateButton();
    // ͨ�����������λ��������Value
    void UpdateValue(HINT,HBOOL bNear = FALSE);

    static void OnBtnSubAdd(void* p, void* pParam);
    void OnBtnSubAdd(void* pParam);

	static void OnBtnSubTop(void* p, void* pParam);
	void OnBtnSubTop(void* pParam);

	void ScrollCtrl(HINT nStartOffset, HINT nEndOffset);

    // ���������ֵ����Сֵ
    HINT  m_nMin;
    HINT  m_nMax;

    // ���汳��ͼ
    IReSurface* m_pBkgndN;
    HBOOL m_bBkgndNRes;

    // �������α�ͼ
    IReSurface* m_pBkgndA;
    HBOOL m_bBkgndARes;
    // �������α꼤��ͼ
    IReSurface* m_pBkgndF;
    HBOOL m_bBkgndFRes;

	// ������ǰ������ͼ
	IReSurface* m_pBkgndD;
	HBOOL m_bBkgndDRes;

    // �α굱ǰֵ
    HINT m_nValue;

    // ����������(��/��)
    HBYTE m_eDir;

    // �����λ������(��/��/��/��)
    HINT m_ex, m_ey, m_ew, m_eh;

    HCButton* m_btnSub;
    HCButton* m_btnAdd;
	HCButton* m_btnTop;
	HCButton* m_btnBottom;
	HCTextCtrl* m_txtIdx;
	HCScrollBox* m_pScrollBox;
	//	��ʾ������
	HINT		m_nRows;


	//kn_int	m_nAllOffset;
	//	������ʱ����λ��
	HINT	m_nMouseDownPos;
	//	������ʱ�����λ��
	HINT	m_nMouseDownEPos;
	//	������ʱ��ǰ���������
	HINT	m_nMouseDownIndex;
    //�ص���������,Ҫ������ָ��
    void (*m_pCallBackMouseUp)(void *, void *);
	// ����ƶ���Ӧ��Ϣ
	void (*m_pCallBackMouseMove)(void *, void *);

    void* m_pThisMouseUp;

};

#endif // !defined(AFX_KCSCROLLCTRL_H__E8783179_BE3E_455F_A6EC_377F43DCFCF2__INCLUDED_)
