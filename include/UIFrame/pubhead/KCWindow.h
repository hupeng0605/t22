/********************************************************************
    created:    2006/12/04
    created:    4:12:2006   11:29
    filename:   d:\code\try\newhmi\include\kcwindow.h
    file path:  d:\code\try\newhmi\include
    file base:  kcwindow
    file ext:   h
    author:          

    purpose:
*********************************************************************/


#if !defined(AFX_KCWINDOW_H__B49A5B73_638F_4905_8FB0_65533C16CC62__INCLUDED_)
#define AFX_KCWINDOW_H__B49A5B73_638F_4905_8FB0_65533C16CC62__INCLUDED_

#include "KCWnd.h"
#include <vector>

using namespace std;

#define KN_OK 1
#define KN_CANCEL 0
#define KN_DEFAULT -1

#define CHILD_MAXNUM 100
#define TAB_FORE 0
#define TAB_NEXT 1
#define TAB_UP 2
#define TAB_DOWN 3

class HCRadioBox;
class HCScreen;
class HCGroupCtrl;

//�����ؼ��ķ���
typedef enum _eDirectionType
{
	LeftDirection,
	RightDirection,
	UpDirection,
	DownDirection,
}eDirectionType;


class UICORE_DLL_API CTimer
{
public:
    CTimer();
    ~CTimer();

    //���á���ȡ���ʱ�� ��ȷ��10����
    void SetTime(HINT ms);
    HINT GetTime();

    //������ʱ��
    void StartTimer();

    //ֹͣ��ʱ��
    void StopTimer();

    //�Ƿ�״̬
    HBOOL IsActive();

    //��������ʱ�����������ж��Ƿ�����,ͬʱ���ûص�
    HBOOL Active(HMessage* msg);

    //���ö�ʱ���ص�
    void SetCallBack(void (*callback)(void*, void*), void*);

protected:
    // ���ʱ�䣬��λ10ms
    HINT m_ntime;

    //��׼ʱ��㣬��Startʱ����
    HINT m_nBasetime;

    // �Ƿ�
    HBOOL m_bActive;

    //�ص���ָ��
    void (*m_pCallBack)(void *, void *);
    void* m_pThis;
};

class UICORE_DLL_API HCWindow : public HCWnd
{
public:
    HCWindow();
    virtual ~HCWindow();

    HBOOL DeleteChild(int index);
    //��Ϣ�������������඼Ҫ����
    virtual HBOOL DoMessage(HMessage* msg);

    virtual void Draw(IReSurface* pSurface);
	virtual void Draw(IReSurface* pSurface,IReSurface* pSurfaceMap,_kn_rect m_rectMap);

    HINT Create(int x, int y, int w, int h, HCScreen* pScreen);

    //�ڴ��ڳ�ʼ������,�̳еĴ��������ش˺�����ʼ���ڲ�����
    virtual HINT OnInit();

    //�����л�����
    virtual void SwitchFocus(HBYTE dir);
    //�����л����� �������°�ť ���ݿؼ����ֲ���
    virtual void SwitchFocusOfFind(HBYTE dir);

    HBOOL AddChild(HCBaseCtrl *pwnd);
	HBOOL InsertChild(HINT index, HCBaseCtrl *pwnd);

	HCBaseCtrl* GetChild(HINT a_nIndex);
	HINT GetChildCount(void);

    void AddTimer(CTimer *pTimer);

    HBOOL DelTimer(CTimer *pTimer);

    //����ģʽ�Ի���
    virtual HINT DoModal();

    virtual HBOOL ShowWindow();

    //���ñ�����ʹ���ⲿ��Դ������Ҳ���Բ��豳��
    void SetBackGround(IReSurface* pSur);

    //���ñ������Լ�����������Ҳ���Բ��豳��
    void SetBackGround(const HString& pFileName);

	HBOOL IsBackGroundOutRes();

    IReSurface* GetBackGround();

    //���ô��ڵı���ɫ�����ޱ���ͼʱʹ�ñ���ɫ���
    void SetBackColor(RECOLOR& color);

    RECOLOR& GetBackColor();

    //Ϊ�����RadioButtonʹ�ã�����ĳ��RadioBox ȫ��ΪFALSE
    void SetRadioGroup(HINT id, HCRadioBox* pRadioBox = NULL);

	void SetRadioGroup(HINT id, HCRadioBox* pRadioBox, HCGroupCtrl* pGroupCtrl);

    //ˢ����Ļ ע����ˢ����Ļ������ˢ�´���
    virtual void UpdateWindow();

    //�ж��Լ��Ƿ��ǽ��㴰��
    HBOOL IsFocus();

    RECOLOR& SetFocusColor(RECOLOR& clr);
    RECOLOR& GetFocusColor();
    HINT GetFocusLineWidth();
    void   SetFocusLineWidth(HINT width);

    void SetTransType(HINT type);

    //���ڱ�����ʱ����
    virtual void OnDeactivated() {};

    //���ڱ���ʾʱ����
    virtual void OnActivated() {};

    //�����Ӧˢ������, bOwnerUpdateΪTRUEʱ�����Ǻ������ؼ����ཻ
    void inline InvalidateRect(kn_rect &rect, HBOOL bOwnerUpdate = FALSE);
    void inline InvalidateRect(HCBaseCtrl* pBaseCtrl);

	// �������б��Ƿ�������������
	void CheckListIncludeRect(kn_rect &rect);
	// �������������Ƿ���������б�
	void CheckRectIncludeList(kn_rect &rect);

	void InvalidateGroupCtrlRect(kn_rect& rect, HCBaseCtrl* pBaseCtrl);

    //���ˢ������
    vector<kn_rect>& GetUpdateRectVector();

    //���ˢ������
    void ClearUpdateRect();

    //�������������Ƿ��ཻ
    static HBOOL IsRectIntersect(kn_rect& rect1, kn_rect& rect2);
	//����1�Ƿ��ھ���2��
	static HBOOL IsRectIncluded(kn_rect& rect1, kn_rect& rect2);
    //�õ��������������ཻ����
    static kn_rect GetIntersectRect(kn_rect& rect1, kn_rect& rect2);

    //���õ�ǰ�Ƿ��������ˢ������
    void EnableUpdateRect(HBOOL bEnable);

    //�Ƿ������ˢ������
    HBOOL IsCanUpdateRect();
	void SetRemovedMSG(HBOOL bRemovedMSG);
	HBOOL GetRemovedMSG();    
	//���ÿؼ�Ϊ����
	void SetCtrlFocus(HCBaseCtrl *pwnd);

	HCBaseCtrl* GetCtrlFocus();

	void DestoryWindow();

	HBOOL IsExiting();

	HCWindow* GetBakFocusWnd()
	{
		return m_pWndBakFocus;
	}

	// KCWindow������ֻ���HMIEngine�еĿؼ���HMIEngineEx�еĿؼ������л������ฺ��
	void ChangeLanguage(HCGroupCtrl* pGroupCtrl);
	virtual void ChangeLanguage(HCBaseCtrl* pCtrl);
	virtual void ChangeLanguage(void);
#if 0
	//���ý�����Ϣ�Ŀؼ�
	void SetMsgCtrl(KCBaseCtrl* pBaseCtrl);
#endif
protected:
    //���ٴ���
    virtual HBOOL OnDestroy();

    //Modal����Ϣѭ��
    HINT RunModalLoop();
    //�˳�Modalѭ��
    void EndModalLoop(HINT nResult);

    virtual void OnOK();
    virtual void OnCancel();
private:
	void GetIntersectRectVec(kn_rect& rect1, kn_rect& rect2, vector<kn_rect>& rect_vec );
	HBOOL GetRectVec(vector<kn_rect>::iterator it_b, vector<kn_rect>::iterator& it_e, kn_rect rect,vector<kn_rect>& rectVec);
	//�����һ��������Ϣ�Ŀؼ����������λ�����жϣ�����ʱY�����ȣ�����ʱX�����ȣ�pBaseCtrlΪ��ʱ�ͣ�0��0���Ƚ����λ��
	void GetBaseCtrlCanRecvRemoteMsg(eDirectionType type, HCBaseCtrl* pBaseCtrl, HINT x, HINT y, HCBaseCtrl*& pNextSelectBaseCtrl);
	void GetBaseCtrlCanRecvRemoteMsgInGroupCtrl(HCGroupCtrl* pGroupCtrl, eDirectionType type, HCBaseCtrl* pBaseCtrl, HINT x, HINT y, HCBaseCtrl*& pNextSelectBaseCtrl);
protected:
    //�ӿؼ�����
    HCBaseCtrl  *m_lstCtrl[CHILD_MAXNUM];
    //��ý���Ŀؼ�ָ��
    HCBaseCtrl  *m_ctlFocus;

    //�ӿؼ�����
    int m_nChildNum;

    //ָ������Ļ��
    HCScreen* m_pScreen;

    // ���ڱ����Ƿ�ʹ���ⲿ��Դ��ʹ���ⲿ��Դ�������������ͷ�m_pSurBack
    HBOOL m_bOutRes;
    //���ڱ���
    IReSurface* m_pSurBack;
    RECOLOR m_colorBack;
    //��ʱ���б�
    vector<CTimer*> m_lstTimer;
    RECOLOR m_clrFocus;
    HINT m_focusLineWidth;
	HBOOL m_bRemovedMSG;
    HINT m_transtype; //�����˳�ʱ��ת������
private:
    //Domodal�ķ���ֵ
    HINT m_nResult;

    //�жϽ����Ϣѭ��
    HBOOL m_bExit;

    //���ݵĽ��㴰�ڣ��������ڵ�����ȡ��ǰһ���ڣ�����ɾ��ʱ���ָ�ǰһ����
    HCWindow* m_pWndBakFocus;

    vector<kn_rect> m_updateRect;

    HBOOL m_bCanUpdateRect;


	HINT m_xMouseStart,m_yMouseStart;

	HINT m_bEnableSendBeepMessage;
#if 0
	//���setcapture����
	KCBaseCtrl* m_pMsgCtrl;
#endif
};

#endif // !defined(AFX_KCWINDOW_H__B49A5B73_638F_4905_8FB0_65533C16CC62__INCLUDED_)
