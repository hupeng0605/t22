/********************************************************************
    created:    2006/12/04
    created:    4:12:2006   11:28
    filename:   d:\code\try\newhmi\include\kcslidectrl.h
    file path:  d:\code\try\newhmi\include
    file base:  kcslidectrl
    file ext:   h
    author:          

    purpose:
*********************************************************************/


#if !defined(AFX_KCSLIDECTRL_H__E8783179_BE3E_455F_A6EC_377F43DCFCF2__INCLUDED_)
#define AFX_KCSLIDECTRL_H__E8783179_BE3E_455F_A6EC_377F43DCFCF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWnd.h"

#define HORIZONTAL 0  //ˮƽ
#define VERTICAL 1 //��ֱ

enum SLIDEDIR
{
    SLIDE_LINEADD,
    SLIDE_LINESUB,
    SLIDE_PAGEADD,
    SLIDE_PAGESUB,
    SLIDE_TRACK,
    SLIDE_CHANGE,
};

struct SLIDEPARA
{
    HBYTE eDir;
    HINT nValue;
};

class HCButton;
class HCListBox;

class UICORE_DLL_API HCSlideCtrl : public HCBaseCtrl
{
public:
    HCSlideCtrl();
    virtual ~HCSlideCtrl();

    // dirΪ�ؼ�����,exΪ������ʼλ�õ�ƫ��
    HBOOL Create(HINT x, HINT y, HINT w, HINT h, HBYTE dir, HINT iOffset);

    // ��Ϣ�������������඼Ҫ����
    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);

    void Enable(HBOOL able);

    // ���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
    void SetBkgndN(IReSurface* pSur);
    void SetBkgndN(const HString& pFileName);

    // ������ǰ��ͼ
    void SetBkgndA(IReSurface* pSur);
    void SetBkgndA(const HString& pFileName);

    // ����������ͼ
    void SetDotgndA(IReSurface* pSur);
    void SetDotgndA(const HString& pFileName);
    // ״̬��ͼƬ
    void SetBkgndS(IReSurface* pSur);
    void SetBkgndS(const HString& pFileName);

	// ��������ʾ���ı�
    //void SetText(const HCHAR* pTxt);

    // ���á���ȡ��ǰֵ
    void SetValue(HINT n);
    HINT GetValue();

    // ��������Χ
    void SetBound(HINT iMin, HINT iMax);
    HINT GetMaximum();
    HINT GetMinimum();

    // ���á���ȡÿҳ����
    void SetPage(HINT);
    HINT GetPage();

    // ���ÿɹ��������ֵ
    HINT GetLimit();

    // ������������value�İ�ť
    void SetButton(HCButton* btnSub, HCButton* btnAdd);

    // ���ð󶨵�ListBox�ؼ�
    void SetListBox(HCListBox *pList);

    // ����ListBoxˢ�»�����ֵ
    void RefreshFromListBox();

    void SetCallBackMouseUp(void (*callback)(void*, void*), void*);
	//����ƶ���Ϣ
	void SetCallBackMouseMove(void (*callback)(void*, void*), void*);

	//	�����������Ϣ
	void SetCallBackMouseDown(void (*callback)(void*, void*), void*);
    virtual void GetBackSufSize(HINT& x, HINT& y);

	//���ñ���ͼƬ��ƫ��
	void SetBkOffset(HINT x, HINT y);

	//�����϶�ʹ�ܿ���
	void EnableMoveSlider(HBOOL bEnable);

	//������ʹ�ܿ���
	void EnableClickSlider(HBOOL bEnable);

	// ������ֵʹ�ܿ���
	void EnableValueSlider(HBOOL bEnable);

protected:

    // ͨ�������Value��ȡ��Ӧ������λ��(һ��Valueֻ��Ӧһ������)
    HINT GetPosFromValue(HINT);

    // ͨ�����������λ�û�ȡ��Ӧ��Value(������һ�������Ӧͬһ��Value)
    HINT GetValueFromPos(HINT);

    // ���㻬���λ��
    void CalcThumbPos();

    // ���㻬��ĳ���
    void CalcThumbSize();

    // ͨ�����������λ��������Value
    void UpdateValue(HINT);

    static void OnBtnSubAdd(void* p, void* pParam);
    void OnBtnSubAdd(void* pParam);

	// ��������ʾ���ı�
	//HString m_strTxt;
	//IReSurface* m_pTextSurf;

    // ���������ֵ����Сֵ
    HINT  m_nMin;
    HINT  m_nMax;

    // ���汳��ͼ
    IReSurface* m_pBkgndN;
    HBOOL m_bBkgndNRes;

	//�������α꼤��ͼ
	IReSurface* m_pDotgndA;
	HBOOL		m_bDotgndARes;
    // �������α�ͼ
    IReSurface* m_pBkgndA;
    HBOOL m_bBkgndARes;

    // ״̬��ͼ
    IReSurface* m_pBkgndS;
    HBOOL m_bBkgndSRes;

    // �α�ͼ��ʼλ��ƫ��
    HINT m_iOffset;

    // �α굱ǰֵ
    HINT m_nValue;

    // ����������(��/��)
    HBYTE m_eDir;

    // �����λ������(��/��/��/��)
    HINT m_ex, m_ey, m_ew, m_eh;

    //ÿҳ������
    HINT m_iPage;

    HCButton* m_btnSub;
    HCButton* m_btnAdd;

    //�󶨵�ListBox�ؼ�
    HCListBox* m_pListBox;

    // ��¼�϶�����ʱ�������ڻ���ͷ����ƫ��
    HINT m_iCursorOffset;

    // �������α��С�Ƿ���Ҫ�ı䣬����ֻ����List��ʱ�Ż�ı�
    HBOOL m_bThumbSize;

    //�ص���������,Ҫ������ָ��
    void (*m_pCallBackMouseUp)(void *, void *);
	// ����ƶ���Ӧ��Ϣ
	void (*m_pCallBackMouseMove)(void *, void *);

	//	�������Ӧ��Ϣ
	void (*m_pCallBackMouseDown)(void *, void *);

    void* m_pThisMouseUp;

	//����ͼƬ��ƫ��
	HINT m_nBkOffsetX;
	HINT m_nBkOffsetY;

	//�����϶�ʹ��
	HBOOL m_bEnableMoveSlider;
	//	�������ı�����ʹ��
	HBOOL m_bEnableClickSlider;

	HBOOL m_bEnableValueSlider;
};

#endif // !defined(AFX_KCSLIDECTRL_H__E8783179_BE3E_455F_A6EC_377F43DCFCF2__INCLUDED_)
