/********************************************************************
    created:    2006/12/04
    created:    4:12:2006   11:28
    filename:   d:\code\try\newhmi\include\kclistbox.h
    file path:  d:\code\try\newhmi\include
    file base:  kclistbox
    file ext:   h
    author:          

    purpose:
*********************************************************************/

#if !defined(AFX_KCLIST_H__A1D31C49_3686_4A89_A80B_63B62A737FD6__INCLUDED_)
#define AFX_KCLIST_H__A1D31C49_3686_4A89_A80B_63B62A737FD6__INCLUDED_

#pragma warning(disable : 4786)

#include <vector>
#include "KCWindow.h"
#include "KCSlideCtrl.h"
#include "KCTextCtrl.h"

#define COL_NUM 2 // ֧�ֵ�����

// ��ʹ��OwnerDataʱ�Ļص�����
enum CALLBACKTYPE
{
    LST_ADDSTRING,
    LST_DELETE,
    LST_CLEAR,
    LST_SETSTRING,
    LST_GETSTRING,
    LST_GETCOUNT,
	LST_GETTEXTSTRING,
};

struct CALLBACKINFO
{
    CALLBACKTYPE cbtype;    // �ص�����
    HINT iItem;       // ��Ŀ���(��)��Ҳ��������ListCount����
    HINT iSubitem;    // ����Ŀ���(��)
    const HCHAR* str;     // ��Ŀ���ַ�������
};

class UICORE_DLL_API HCListBox : public HCBaseCtrl
{
public:
    HCListBox();
    virtual ~HCListBox();

    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);

    //���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
    void SetBkgndN(IReSurface* pSur);
    void SetBkgndN(const HString& pFileName);

    void SetBkgndA(IReSurface* pSur);
    void SetBkgndA(const HString& pFileName);

    HBOOL Create(HINT x, HINT y, HINT w, HINT h, HUINT row, HUINT col, HINT height);
    //��������ƫ��
    void SetTextPos(HINT x, HINT y, HINT width, HUINT col = 0);
    //����һ�����ַ���(����Ϊ��һ��)
    void AddString(const HString& str);
    //ɾ��һ��
    void Delete(HUINT n);
    //ȡ�õ�ǰѡ���С�0��ʼ
    HINT GetCurSel();
    //ȡ�õ�ǰ��ѡ��һ���ַ�����
    HString GetCurSelString();
    //ȡ��ָ�����е��ַ���
    HString GetString(HUINT nIndex, HUINT col = 0);
    //ȡ��ָ�����е��ַ���
    void SetString(const HString& str, HUINT nIndex, HUINT col = 0);
    //���ñ�ѡ��
    HBOOL SetCurSel(HINT nIndex);
    //���
    void Clear();
    //ȡ����������λ��
    HINT GetPos();
    //��������λ��
    HINT SetPos(HUINT pos);

    //ȡ���б�����ʾ����
    HINT GetRow();
    //ȡ���б������������
    HINT GetListCount();

    // ����pos���Ըı�ʱ�Ļص�
    void SetCallBackPosChange(void (*callback)(void*, void*), void* pThis);

    // Add.              .2007.02.08
    // ����OwnerData��ʽʱ�Ļص�(�ṩ����Windows��Virtual List View�Ĺ���)
    void SetCallBackOwnerData(void (*callback)(void*, void*), void* pThis);

	// �б���ص�
	void SetCallBackUp(void (*callback)(void*, void*), void* );

    // ������֮�󶨵�slider�ؼ�
    void SetSlideCtrl(HCSlideCtrl *pSlide);

	// ������֮�󶨵�Text�ؼ�
	void SetTextCtrl(HCTextCtrl *pText);

	//ȡ��Text�ؼ����ַ���
	HString GetTextString();
	void SetTextString();

    //����KCSlideCtrl ������ֵˢ���б��λ��
    void RefreshFromSlideCtrl();

	

    virtual void GetBackSufSize(HINT& x, HINT& y);

	HINT GetLangID(HINT nRow)
	{
		return m_nLangID[nRow];
	}
	void SetLangID(HINT a_nLangID,HINT nRow)
	{
		m_nLangID[nRow] = a_nLangID;
	}


protected:
	vector<HINT> m_nLangID;

    //����Խ��Ķ�ʱƫ������һ
    void AddStrOut();

    // �����Ƿ���ĳһ��������Ҫ������ʾ
    void IsNeedRoll();

    //���汳��ͼ
    IReSurface* m_pBkgndN;
    HBOOL m_bBkgndNRes;

    //�����ͼ
    IReSurface* m_pBkgndA;
    HBOOL m_bBkgndARes;

    vector<HString> m_lstString[COL_NUM];

    //�ַ������ȳ����Ŀ��
    HINT m_nStrOutSize[COL_NUM];

    //��ʱƫ����
    HINT m_nStrOut[COL_NUM];

    //��ǰѡ�е����� ��0��ʼ
    HINT m_nCurrent;
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

    //�����Ƿ�Խ�磬Ҫ��Ӧ��ʱ����Ϣ
    HBOOL m_bOut;

    // OwnerData��ʽ�Ļص�����ָ��
    void (*m_pCallBackPosChange)(void* pThis, void* pParam);

    // ��ȡ��ʾ��Ϣ�Ļص�����ָ��
    void (*m_pCallBackOwnerData)(void* pThis, void* pParam);

	//�б���ʱ�ص�
	void (*m_pCallBackUp)(void *, void *);

    //�󶨵�Slide����
    HCSlideCtrl *m_pSlide;

	//�󶨵�Text����
	HCTextCtrl *m_pText;

    HUINT m_baseTime;
};

#endif