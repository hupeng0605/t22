

#pragma once

#include "KCWnd.h"
#include "vector"
using namespace std;

class UICORE_DLL_API HCGroupCtrl : public HCBaseCtrl
{
public:

    HCGroupCtrl();

    virtual ~HCGroupCtrl();

    //��Ϣ�������������඼Ҫ����
    virtual HBOOL DoMessage(HMessage* msg);

	//����������Ӧ����Ϣ�Ŀؼ�
	HBOOL DoMessage(HMessage* msg, OUT vector<HCBaseCtrl*>& ctrlList);

    virtual void Draw(IReSurface* pSurface);

    // ���ñ�����ʹ���ⲿ��Դ������Ҳ���Բ��豳��
    void SetBackGround(IReSurface* pSur);

    // ���ñ������Լ�����������Ҳ���Բ��豳��
    void SetBackGround(const HString& pFileName);

    IReSurface* GetBackGround();

	// �Ƴ��ӿؼ���Ĭ�ϲ������Դ
	HBOOL RemoveChild(int index, HBOOL bDelete = FALSE);
	// �Ƴ��ӿؼ���Ĭ�ϲ������Դ
	HBOOL RemoveChild(HCBaseCtrl* childCtrl, HBOOL bDelete = FALSE);

	// ����ӿؼ�
    HBOOL AddChild(HCBaseCtrl *pwnd);

	// ��ָ��λ�ò����ӿؼ�
	HBOOL InsertChild(HINT index, HCBaseCtrl *pwnd);

	// �����Ƿ���ʾ
	void SetShow(HBOOL bShow);
//  void SetOpacity(kn_byte value);
    //����ƶ�����
    void Move(HINT dx, HINT dy);
    //�����ƶ�����
    void MoveTo(HINT x, HINT y);
//  //���ô�С
//  void SetSize(kn_int w, kn_int h);

	void EnableOwnerUpdate(HBOOL bEnable);

	void Redraw(HBOOL bEnable = TRUE);

	// ���ø�����
    void SetFatherWnd(HCWindow* pFatherWnd);

	// ���ý���ؼ�
    void SetCtrlFocus(HCBaseCtrl *pWnd);

	//�õ��ؼ��б�
    vector<HCBaseCtrl*>& GetCtrlList();

    void GetBackSufSize(HINT& x, HINT& y);

	void Invalidate();

	// ���ƿؼ�������Surface��ָ������
	void DrawBaseCtrl(IReSurface* pSurf, int x, int y);

	HCBaseCtrl* GetFocusCtrl();
protected:
	HCBaseCtrl  *m_ctlFocus; //����ؼ�
private:
    //�ӿؼ�����
    vector<HCBaseCtrl*>  m_lstCtrl;
    //��ý���Ŀؼ�ָ��
    
    IReSurface* m_pSurBack; //����
    HBOOL m_bOutRes;		//�Ƿ����ⲿ��Դ
};