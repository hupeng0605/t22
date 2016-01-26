#pragma once

#include "kcwnd.h"
#include "vector"
using namespace std;

class HCScrollBoxEx;
class CYPRESS_DLL_API KCScrollItem
{
public:
	KCScrollItem();
	virtual ~KCScrollItem();

	//void SetBkgnd(IReSurface* pSur);
	//void SetBkgnd(const kn_string& pFileName);

	void SetText(const HCHAR* str);
	HString GetText();

	/*void SetTxtColorN(int r , int g , int b);*/

	void EnableSelect(HBOOL bEnable);
	HBOOL IsEnableSelect();

	friend HCScrollBoxEx;
protected:
	void SetFather(HCBaseCtrl* pFather);
	/*RECOLOR		m_colorN;*/
	HCBaseCtrl*	m_pFatherCtrl;
	HString	m_strText;
	/*IReSurface*	m_pBkSurf;
	kn_bool		m_bBkRes;*/
	IReSurface*	m_pTxtSurf;

	HBOOL		m_bEnableSel;
};

typedef vector<KCScrollItem*> SCROLL_ITEM_VEC;
typedef vector<KCScrollItem*>::iterator SCROLL_ITEM_VEC_IT;

class CYPRESS_DLL_API HCScrollBoxEx : public HCBaseCtrl
{
public:
	HCScrollBoxEx();
	~HCScrollBoxEx();
	virtual HBOOL DoMessage(HMessage* msg);
	virtual void Draw(IReSurface* pSurface);
	virtual HBOOL Create(HINT x, HINT y, HINT w, HINT h, HINT nRows);

	//��ť���»ص�
	void SetCallBackDown(void (*callback)(void*, void*), void*);
	//��ť����ص�
	void SetCallBackUp(void (*callback)(void*, void*), void*);
	//������Ϣ
	void SetCallBackLongPress(void (*callback)(void*, void*), void*);
	void SetCallBackLongPressUp(void (*callback)(void*, void*), void*);
	void SetCallBackLongPressConsecutive(void (*callback)(void*, void*), void*);
	void EnableLongPressConsecutive(HBOOL bEnable, HINT times = 50);
	void EnableLongPress(HBOOL bEnable);
	void SetLongPressTime(HINT time);

	// �����
	HBOOL AddListItem(KCScrollItem* pListItem);
	// ��ָ��λ�ò�����
	HBOOL InsertListItem(HINT pos, KCScrollItem* pListItem);
	// ɾ��ĳ��
	HBOOL DeleteListItem(KCScrollItem* pListItem);
	// ɾ��������
	void DeleteAllListItems();
	// ���³�ʼ�����б���
	void ReInit();

	//��������item�б�
	SCROLL_ITEM_VEC& GetListItemVec();

	//��ȡѡ�е�item
	KCScrollItem* GetSelectListItem();
	//����item��Ӧ������
	HINT GetListItemIndex(KCScrollItem* pListItem);
	//����ѡ����item������
	HINT GetSelectItemIndex();
	//����ѡ����
	void SetSelectListItem(KCScrollItem* pListItem);
	void SetSelectListItem(HINT index);
	//����Ƿ��Զ�����ѡ����
	void EnableAutoCheck(HBOOL bAutoCheck = TRUE);

	//����ScrollBoxEx�ı���ͼ
	void SetBkgnd(IReSurface* pSur);
	void SetBkgnd(const HString& pFileName);
	//���ý���ͼ�㣬��������
	void SetFouceItemBkgnd(IReSurface* pSur);
	void SetFouceItemBkgnd(const HString& pFileName);
	//����ÿһ�еı���ͼ
	void SetItemBkgnd(IReSurface* pSur);
	void SetItemBkgnd(const HString& pFileName);

	//���ý���ͼ���ڿɼ�����һ����ʾ
	void SetFouceRow(HINT nIndex);


	//����item�ı�������Ҷ��롢���У�pixels��ʾ�Ҷ�������
	void SetTextStyle(HDWORD dwFormat, HINT pixels = 10);
private:
	HINT GetItemIdxFromOffset(HINT yOffset);
	//����item��������Ӧ���б�����ʾ����
	HINT GetRowFromIndex(HINT nIndex);
protected:
	void ScrollItem(HINT nStart, HINT nEnd);
protected:
	SCROLL_ITEM_VEC		m_listItemVec;
	// ��ǰѡ����ָ��
	KCScrollItem* m_pSelectItem;
	HINT m_nItemSpace;//�б����ÿ��ļ��
	//// ������߶Ⱥ�
	//kn_int m_allHeight;
	//�Զ�ѡ�У���Ϊ��ʱ��������Զ�ѡ�У�������Ҫ����SetSelectListItem�ӿ��ֶ�����ѡ��
	HBOOL m_bAutoCheck;
	HINT	m_nSelectIndex;
	//��ʾ�������ڵ�����
	HINT	m_nFirstItemIndex;
	//��������ڵ���ʾ��
	HINT	m_nFouceRowIndex;
	//����surface����������
	IReSurface*	m_pFouceSurf;
	HBOOL		m_bFouceSurfRes;
	//����ʾ������
	HINT		m_nRows;
	//ÿһ�еı���ͼ
	IReSurface*	m_pItemBkSurf;
	HBOOL		m_bBkSurfRes;
	//�ؼ�����ͼ
	IReSurface*	m_pBkSurf;
	HBOOL		m_bBkRes;

	//item���뷽ʽ
	HDWORD	m_dwTextStyle;
	HINT		m_nPixels;

	//��ť����ʱ�ص���������,Ҫ������ָ��
	void (*m_pCallBackDown)(void *, void *);
	//��ť����ʱ�ص���������,Ҫ������ָ��
	void (*m_pCallBackUp)(void *, void *);
	// ��곤����Ϣ
	HINT m_longPressTime;
	void (*m_pCallBackLongPress)(void *, void *);
	void (*m_pCallBackLongPressUp)(void *, void *);
	void (*m_pCallBackLongPressConsecutive)(void *, void *);
	
	//����������Ӧ��Ϣ
	HBOOL m_bEnableLongPressConsecutive;
	HINT m_LongPressTimeConsecutive;
	HBOOL m_bEnableLongPress;

	HINT m_baseTime;
	HBOOL m_bHaveExecute;
	HBOOL m_bOutOfRange;

	KCScrollItem* m_pMouseDownItem;

	IReSurface*   m_pTmpSurf;
};


typedef struct _tagScrollParam
{
	KCScrollItem* pItem;
	HCScrollBoxEx* pScrollBoxEx;
	_tagScrollParam(){pItem = NULL; pScrollBoxEx = NULL;};
}ScrollParam;