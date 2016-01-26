

#pragma once

#include "kcwnd.h"
#include "vector"
using namespace std;


class HCListItemBase;
class HCScrollCtrl;
typedef vector<HCListItemBase*> LIST_ITEM_VEC;
typedef vector<HCListItemBase*>::iterator LIST_ITEM_VEC_IT;

class UICORE_DLL_API HCScrollBox : public HCBaseCtrl
{
public:
    HCScrollBox();
    ~HCScrollBox();

	friend HCScrollCtrl;
	// �����
    HBOOL AddListItem(HCListItemBase* pListItem);
	// ��ָ��λ�ò�����
    HBOOL InsertListItem(HINT pos, HCListItemBase* pListItem);
	// ɾ��ĳ��
    HBOOL DeleteListItem(HCListItemBase* pListItem);
	// ɾ��������
    void DeleteAllListItems();
	// ���³�ʼ�����б���
	void ReInit();  
    // ����ָ����
    HCListItemBase* GetItemAt(HINT nIndex);
	// ���ص�ǰѡ����
    HCListItemBase* GetSelectListItem();
	//��������
    HINT GetListItemCount();
	// ����ָ����ָ���Ӧ����λ��
    HINT GetListItemIndex(HCListItemBase* pListItem);
	// ����ָ����ָ������Ļ�ϵĶ�Ӧλ��
    void GetListItemPosition(HCListItemBase* pListItem, HINT& x, HINT& y);
	// ����������ĸ߶Ⱥ�
    HINT GetListItemAllHeight();
	// �Ƿ���¸߶���Ϣ
    void SetNeedUpdate(HBOOL bNeedUpdate);
	// ����������λ�ü�ĸ߶Ⱥ�
    HINT GetListItemHeight(HINT start, HINT end);
	HINT GetStarIndex();
	HINT GetEndIndex();
    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);

    //���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
    void SetBkgndN(IReSurface* pSurf);
    void SetBkgndN(const HString& pFileName);
	// ���û���������ͼƬ
    void SetSliderBkgSurf(IReSurface* pSurf);
    void SetSliderBkgSurf(const HString& pFileName);
	// ���û���ͼƬ
    void SetSliderSurf(IReSurface* pSurf,HINT nOffset_Y = 0);
    void SetSliderSurf(const HString& pFileName,HINT nOffset_Y = 0);

	//�б������¼�
	void SetCallBackMove(void (*callback)(void*, HBOOL bSrollUp), void*);
	void SetCallBackUp(void (*callback)(void*, void*), void*);
	void SetCallBackMoveUp(void (*callback)(void*, void*), void*);
	void SetCallBackLongUp(void (*callback)(void*, void*), void*);
	// �����¼�
    void SetCallBackMoveRight(void (*callback)(void*, void*), void*);
	// �����¼�
    void SetCallBackMoveLeft(void (*callback)(void*, void*), void*);
	// ����¼�
    void SetCallBackClick(void (*callback)(void*, void*), void*);
	// �����¼�
	void SetCallBackLongPress(void (*callback)(void*, void*), void*);
	//	ѡ����ı�ص�
	void SetCallBackSelectItemChange(void (*callback)(void*, void*, void*), void*);
	// ���ظ���������
    void SetFatherWnd(HCWindow* pFatherWnd);
	//�б����������ص�
	void SetCallBackScrollEnd(void(*callback)(void*, HBOOL bScrollUp), void*pThis);

	//����ѡ�����ʹ����ʾ����Ļ��
    void SetSelectListItem(HINT index, HBOOL autoRoll = TRUE);
    void SetSelectListItem(HCListItemBase* pListItem);
	void SetTopIndex(HINT index);

	// �ƶ���ǰѡ����б��м�
    void MoveCenterSelectListItem();

	//����������
	LIST_ITEM_VEC& GetListItemVec();
	// ���ó���ʱ��
	void SetLongPressTime(HINT time);

	//���ص�ǰƫ��
	HINT GetOffset();

	//��������ƫ��������
	HCListItemBase* GetListItemOffset(HINT offset);
	
	//�����Զ�����
	void EnableAutoScroll(HBOOL bEnable);

	//�������
	void EnableMove(HBOOL bEnable);

	//��ǰ�б���Ƿ��ڹ���״̬
	HBOOL IsScroll();

	//���������б����ұ�
	void EnableRightToLeft(HBOOL bEnable);

	//ÿ���ƶ�ʱ���������ƶ�����ʱҪ�������еĸ߶�һ��,����TRUE�����óɹ�, pSurfaceΪ������ӵ�һ����
	HBOOL EnableScrollLine(HBOOL bEnable, HINT iLineHeight, IReSurface* pSurface = NULL);

	HBOOL IsScrollLineEnable();

	//���ñ���������һ�����
	void EnableBkgSurfScroll(HBOOL bEnable);

	void SetItemSpace(HINT space);

	void EnableLostSelectIndexMove(HBOOL bEnable);

	void EnableFocusButtonDown(HBOOL bEnable);

	//�����һ�γ����ص�����times������ó����ص�
	void EnableLongPressConsecutive(HBOOL bEnable = TRUE, HINT times = 50);

	//��õ�ǰ�������ͬ��ѡ����
	HCListItemBase* GetFocusListItem();

	// ��ȡScrollBox��ÿҳ��ť��
	HINT GetScrollBoxBtnNum(void);
	//
	void EnableSelectItemLongPress(bool bEnable);
	void SetLostFocus();
	// �������
	void ClearFocus();

	HBOOL IsPointInVisuableArea(HINT x, HINT y);
private:
	void SetFocusListItem(int offset);

private:
	HINT	m_nSlideOffset_Y;
	//����ƫ���趨��ǰѡ����
    void SetCurSel(HINT offset);
	
    //���汳��ͼ
    IReSurface* m_pBkgndN;
    HBOOL m_bBkgndNRes;
	// ����������
    IReSurface* m_pSliderBkgSurf;
    HBOOL m_bSliderBkgSurfRes;
	// ���鱳��
    IReSurface* m_pSliderSurf;
    HBOOL m_bSliderSurfRes;
	// ������߶Ⱥ�
    HINT m_allHeight;
	// �Ƿ���Ҫ����
    HBOOL m_bNeedUpdate;
	// ������洢����
    LIST_ITEM_VEC m_listItemVec;
	// ��ǰѡ����ָ��
    HCListItemBase* m_pSelectItem;
	// ��ǰ��ʾ����Ļ�ڵ����Ӧ��ƫ��ֵ
    HINT m_allOffset;

    HINT  m_xBackup;//��갴��ʱλ��
    HINT  m_yBackup;
    HINT  m_xOffset;//���ƫ��
    HINT  m_yOffset;
// 	HINT  m_xMaxOffset;
// 	HINT  m_yMaxOffset;
// 	HINT  m_xMinOffset;
// 	HINT  m_yMinOffset;
	// ��ǰ�Ƿ��ڹ���״̬
    HBOOL m_bCanMove;//�б��ǰ�Ƿ��ڹ���״̬

	HBOOL m_bEnableMove;//�Ƿ������б�����
	HBOOL m_bEnableAutoScroll;//�Ƿ������б���Զ�����

    HINT m_StartTime;//��갴��ʱ��׼ʱ��
	HINT m_LongPressBaseTime;//������Ӧ��ʱ
    HBOOL m_bAutoScroll;//�Զ�����
	HBOOL m_bAutoScrollBackup;//���ݣ���Ҫ����ָ�����������е���ʱ״̬
    HFLOAT m_ScrollSpeed;//�����ٶ�
    HINT m_ScrollbaseTime;//��׼ʱ�䣬���ڼ�ʱ
    HINT m_SpareNum;//���ٵ�ʣ�����

	HBOOL m_bHaveExecuteMove;//�Ѿ�ִ����Move�Ļص�
	void (*m_pCallBackMove)(void *, HBOOL bSrollUp);
    void (*m_pCallBackMoveRight)(void *, void *);
    void (*m_pCallBackMoveLeft)(void *, void *);
    void (*m_pCallBackClick)(void *, void *);
	void (*m_pCallBackUp)(void *,void *);
	void (*m_pCallBackMoveUp)(void *,void *);
	void (*m_pCallBackLongUp)(void *,void *);
	void (*m_pCallBackLongPress)(void *, void *);
	void (*m_pCallBackSelectItemChange)(void*, void*, void*);
	HINT m_longPressTime;// ����ʱ��
	HBOOL m_bHaveExecuteLongPress;// �¼��Ƿ��Ѿ���Ӧ����

    HBOOL m_bMoveRight;// ����������Ϣ��Ӧ��

    HINT m_startListItem;// ��ǰ��ʾ����Ļ�ڵ���ʼ��
    HINT m_endListItem;// ��ǰ��ʾ����Ļ�ڵĽ�����
	void* m_pThisScrollEnd;
	HBOOL m_bEnableRightToLeft;//������ҵ�����ʾ������
	void(*m_pCallBackScrollEnd)(void*, HBOOL);

	HBOOL m_bEnableScrollLine;//�Ƿ��������й���
	HINT m_nLineHeight;//�����ƶ��ĸ߶�
	HINT m_nScrollOffset;//�Զ�����ʱ����Ҫ�����ľ���
	HINT m_nOffsetBackup;//���ڱ��ݹ����������ٴε��ʱ��ƫ����
	IReSurface* m_pScrollLineSurf;//������ӵ���

	HBOOL m_bEnableBkgSurfScroll;//�Ƿ�����������

	HINT m_nItemSpace;//�б����ÿ��ļ��

	HBOOL m_bEnableLostSelectIndexMove; //���ƶ��б��ʱ�Ƿ�����ʧȥ��ǰѡ����Ľ���

	HBOOL m_bEnableFocusButtonDown;//��갴��ʱ���þ۽���

	HCListItemBase* m_pFocusItem;// ��ǰ�۽���ָ��
	HCListItemBase* m_pOldSelectItem;//ǰһ��ѡ�����ָ��
	HBOOL m_bEnableSelectItemLongPress;//�Ƿ�������Ӧѡ����ĳ����¼�
	HBOOL m_bHaveSetSelectItem;//��ʱ�����Ƿ��Ѿ�������ѡ����

	IReSurface* m_pSliderSurfStretch;//���������Ļ�������

	HINT m_nTmpStartIndex;
	HINT m_nTmpEndIndex;
	//����������Ӧ��Ϣ
	HBOOL m_bEnableLongPressConsecutive;
	HINT m_LongPressTimeConsecutive;

	HBOOL m_bCanLongPress;//�Ƿ������Ӧ����

protected:
	//
	HBOOL m_bMouseDownScroll;
};

