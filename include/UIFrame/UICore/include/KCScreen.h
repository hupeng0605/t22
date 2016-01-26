


#if !defined(AFX_KCSCREEN_H__EEBC52BF_A4B3_41FC_BFC1_A307384943E1__INCLUDED_)
#define AFX_KCSCREEN_H__EEBC52BF_A4B3_41FC_BFC1_A307384943E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWindow.h"
#include <vector>

class HCScreen
{
public:
    HCScreen();
    virtual ~HCScreen();

    void Release();

    //��Ϣ������
    HBOOL DoMessage(HMessage* msg);

    // ��Windows��,����Display��Ӧ�Ĵ��ھ��
    void SetHWnd(HWND hWnd) ;

    // ������ʾ�ߴ�
#if defined(SCREEN_COLORBIT16)
    void Create(HINT width, HINT height, HINT x, HINT y, HWND hWnd, HINT colorType = RE_COLOR565);
#else
	void Create(HINT width, HINT height, HINT x, HINT y, HWND hWnd, HINT colorType = RE_COLOR888);
#endif
    HINT GetX();
    HINT GetY();
    HINT GetWidth();
    HINT GetHeight();

    // ��ָ����surface����
    void Flip(IReSurface* surface, HINT x, HINT y);

    void Draw();
	void ClearFast(HBYTE byValue)
	{
		m_pSurface->ClearFast(byValue);
		FlipRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	}

    HCWindow* GetFocusWnd();
    //trans_type ת����Ч��ʽ�� 0Ϊ��ת��Ч���� 1Ϊ���䣬 2 ����Ч��
    void SetFocusWnd(HCWindow* pWnd, HINT trans_type = 1);
    //ת����Ч����
    void TransAffect(HINT trans_type);
	void TransAffect(IReSurface *pOldSur,IReSurface *pNewSur,HINT trans_type);

    //���ñ����Ի���
    void SetMsgWnd(HCWindow* pWnd);
    HCWindow* GetMsgWnd();

    //����һ�����ڵ�����ĩβ
    HBOOL AddWindow(HCWindow* pWnd);
    //�ڴ���������ȥ��ָ���Ĵ���ָ�룬�����ָ��λ����ǰ˳��
    HBOOL DelWindow(HCWindow* pWnd);
    //��鴰���Ƿ����
    HBOOL CheckWindow(HCWindow* pWnd);
    // 3D�����л�����
    void Trans3DRotate(IReSurface *pScreenSurface_bak);

	IReSurface* GetScreenSurface();

	void FlipRect(HINT x, HINT y, HINT width, HINT height);

	void EnableDraw(HBOOL bEnable);

	HBOOL IsCanDraw();

	HBOOL IsInDraw();
	void SetInDraw(HBOOL bInDraw);
	vector<HCWindow*>* GetListWnd();
private:
    //�ӿؼ����� ���������ͷ�
    vector<HCWindow*> m_lstChildWnd;

    //ָ���ý����window
    HCWindow *m_pFocusWnd;

    //Ϊģʽ�����Ի���ר�Ŷ����Window
    HCWindow *m_pMsgWnd;

    HWND m_hMainWnd;
    HDC  m_hdc;
    HINT m_width;
    HINT m_height;
    HINT m_x;
    HINT m_y;
    IReSurface* m_pSurface;
    //���ڹ���Ч����surface
    //IReSurface* m_pSurface_bak;

	HBOOL m_bEnableDraw;
	HBOOL m_bInDraw;
};

#endif // !defined(AFX_KCSCREEN_H__EEBC52BF_A4B3_41FC_BFC1_A307384943E1__INCLUDED_)
