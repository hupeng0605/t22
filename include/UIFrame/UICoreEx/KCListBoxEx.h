/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCPickButton.cpp
* ժ    Ҫ:
*
* ��ǰ�汾: 1.0
* ��    ��:               
* �������: 2009-12-29
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1            2010-2-4                     			����
*	2			 2010-8-12	                  			��ӳ�����������
**/

#pragma once

#include "KCwnd.h"
#include "RenderingEngine.h"
#include <vector>
using namespace std;

#define  MAX_ROW_NUM	(30)
#define  MAX_COL_NUM	(5)

typedef vector<HString*> STR_VEC;
typedef vector<HString*>::iterator STR_VEC_IT;
typedef vector<STR_VEC*>::iterator STR_VEC_VEC_IT;

typedef vector<IReSurface*> SURF_VEC;
typedef vector<IReSurface*>::iterator SURF_VEC_IT;

typedef void (*ClickCallBack)(void*, HINT, HINT);
typedef void (*MoveCallBack)(void*,void*);
//��һ��kn_intΪ��ʼֵ���ڶ���kn_intΪ����
typedef void (*DrawNoValueCallBack)(void*, HINT, HINT);

class CYPRESS_DLL_API HCListBoxEx : public HCBaseCtrl
{
public:
    HCListBoxEx();
    ~HCListBoxEx();
public:
    //***************************************************************
    // *  ��������: �����ؼ�
    // *  ��ڲ���: �ɱ������ÿ�п��
    // *  ���ڲ���:
    // *  �� �� ֵ:
    //***************************************************************
    void Create(HINT x, HINT y, HINT height, HINT columnNum, HINT rowNum, HINT columnWidth1, ...);
    //***************************************************************
    // *  ��������: ���ø���ı���
    // *  ��ڲ���:
    // *  ���ڲ���:
    // *  �� �� ֵ:
    //***************************************************************
    void SetSurf(const HCHAR* pDefaultOddSurfPath, const HCHAR* pDefaultEvenSurfPath, const HCHAR* pNormalOddSurfPath,
                 const HCHAR* pNormalEvenSurfPath, const HCHAR* pFocusOddSurfPath, const HCHAR* pFocusEvenSurfPath);
	void SetCursorSurf(const HCHAR* pNormalOddCursorSurfPath, const HCHAR* pNormalEvenSurfPath,
						const HCHAR* pFocusOddCursorSurfPath, const HCHAR* pFocusEvenSurfPath);
    //***************************************************************
    // *  ��������: ����ÿ�е�����xλ�ã�Y�������ʾ
    // *  ��ڲ���:
    // *  ���ڲ���:
    // *  �� �� ֵ:
    //***************************************************************
    void SetTextPos(HINT posX1, ...);
	void SetTextStyle(HINT style1,...);

    //***************************************************************
    // *  ��������: ����ÿ�������
    // *  ��ڲ���:
    // *  ���ڲ���:
    // *  �� �� ֵ:
    //***************************************************************
    HBOOL AddString(HCHAR** pString1, ...);
	    //***************************************************************
    // *  ��������: ָ��λ�ò�������
    // *  ��ڲ���:
    // *  ���ڲ���:
    // *  �� �� ֵ:
    //***************************************************************
	 HBOOL InsertString(HINT nPos,HCHAR** pString1, ...);

    //***************************************************************
    // *  ��������: ɾ��ĳ��
    // *  ��ڲ���:
    // *  ���ڲ���:
    // *  �� �� ֵ:
    //***************************************************************
    HBOOL DelItem(HUINT index);

    //***************************************************************
    // *  ��������: ����ĳ��ĳ�е�����
    // *  ��ڲ���:
    // *  ���ڲ���:
    // *  �� �� ֵ:
    //***************************************************************
    HBOOL SetString(HINT column, HINT row, const HCHAR* pString);
	HBOOL SetString(HINT row, HCHAR** pString1, ...);

    //***************************************************************
    // *  ��������: ���ĳ��ĳ�е�����
    // *  ��ڲ���:
    // *  ���ڲ���:
    // *  �� �� ֵ:
    //***************************************************************
    const HCHAR* GetString(HINT column, HINT row);

    // ��õ�ǰѡ�е���
    inline HINT GetSelectIndex();
	//�����Ƿ��ó�������
	inline void SetEnableScorll(HBOOL bIn);
	// ɾ��������
    void DelAllItems();
    void SetCallBackClick(ClickCallBack callBack, void* pThis);
	void SetCallBackDownMove(MoveCallBack DownMovecallBack, void* pThis);
	void SetCallBackUpMove(MoveCallBack UpMovecallBack, void* pThis);
    // ���ù��������ص�
	void SetCallBackScrollEnd(void(*callback)(void*, HBOOL bScrollUp), void*pThis);
	void SetCallBackScrollOutRange(void(*callback)(void*, HBOOL bScrollUp), void*pThis);
	//�б������¼�
	void SetCallBackMove(void (*callback)(void*, void*), void*);

	// �ڻ���ʱĳ����ֵʱ����
	void SetCallBackDrawNoValue(DrawNoValueCallBack callBack, void* pThis);

	void EnableCallBack(HBOOL bEnableCallBack);

    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);

	//����ѡ����
    void SetSelectIndex(HINT index);
	//����������Ŀ
    HINT GetTotalNum();
	// �������
	HINT GetRowNum();
    // �õ���һ����������
    inline  HINT GetStarIndex();
	//���õڼ�������Ӧ��Ϣ���߲���
    void EnableMsgByIndex(HINT index, HBOOL bEnable);

	//����ʱ�Ƿ�ʧѡ�����״̬
	void EnableLostSelectIndexMove(HBOOL bEnable);

	void EnableFocusButtonDown(HBOOL bEnable);
	
	HBOOL IsListEmpty();

	void StopAutoScroll(HINT nStartIndex);

	//���ÿ�ʼ��
	void SetStartIndex(HINT index);

	//�ƶ���ǰѡ�������֤ѡ����ʼ������Ļ��
	void MoveChangedIndex(HBOOL bDown);
	//��ӳ����¼�
	void SetCallBackLongPress( void (*callback)(void*, HINT, HINT), void*pThis );
	//��ȡ����ʱ����
	void OnFocus();
	//ʧȥ����ʱ����
	void OnLostFocus();
	//�������
	void EnableMove(HBOOL bEnable);
	//�������ص�
	void IsEnableLongPress(HBOOL bEnable);
	//��������
	HINT GetColNum()
	{
		return m_columnNum;
	}
	//���LangID
	HINT GetLangID(HINT nRowIndex,HINT nColIndex)
	{
		return m_nLangId[nRowIndex][nColIndex];
	}
	//����LangID
	void SetLangID(HINT a_nLangID,HINT nRowIndex,HINT nColIndex)
	{
		m_nLangId[nRowIndex][nColIndex] = a_nLangID;
	}

private:
    //***************************************************************
    // *  ��������: ��õ�ǰ��ı���ͼƬ��������ɫ
    // *  ��ڲ���: index:Ҫ��õ���
    // *  ���ڲ���: pSurface:���ر��� pTextColor��������ɫ
    // *  �� �� ֵ: TRUE:�����index��Ч
    //***************************************************************
    HBOOL GetSurfAndColor(HINT index, IReSurface*& pSurface, RECOLOR*& pTextColor);

private:
    //��ż��ı�����DefaultΪ������ʱ����
    IReSurface* m_pDefaultOddSurf;
    IReSurface* m_pDefaultEvenSurf;
    IReSurface* m_pNormalOddSurf;
    IReSurface* m_pNormalEvenSurf;
    IReSurface* m_pFocusOddSurf;
    IReSurface* m_pFocusEvenSurf;

	IReSurface* m_pNormalCursorOddSurf;
	IReSurface* m_pNormalCursorEvenSurf;
	IReSurface* m_pFocusCursorOddSurf;
	IReSurface* m_pFocusCursorEvenSurf;

    IReSurface* m_pBackupSurf;

    HINT m_columnNum;// ����
    vector<HINT> m_columnWidthVec;//ÿ�п��
    vector<HINT> m_textPosXVec;//ÿ��������ʾλ�ã����ÿ����ʼλ��
	vector<HINT> m_textStyleVec;

    HINT m_rowNum;// ��ʾ������
    HINT m_rowHeight;// ÿ�еĸ߶�
    HINT m_selectIndex;// ��ǰѡ�е���
    vector<STR_VEC*> m_strVec;
	vector<SURF_VEC*> m_surfVec; // ����Ժ��Surface
	vector<SURF_VEC*> m_OrgSurfVec;// ԭʼ��Surface




    ClickCallBack m_pCallBackClick;
	// �»�
	MoveCallBack m_pCallBackDownMove;
	// �ϻ�
	MoveCallBack m_pCallBackUpMove;

	DrawNoValueCallBack m_pCallBackDrawNoValue;

	void(*m_pCallBackScrollOutRange)(void*, HBOOL);
    void(*m_pCallBackScrollEnd)(void*, HBOOL);
	void (*m_pCallBackMove)(void *, void *);
	void (*m_pCallBackLongPress)(void*, HINT, HINT);
	
	HINT m_nLangId[MAX_ROW_NUM][MAX_COL_NUM];
	//void EnableMove(kn_bool bEnable);
    void*m_pThisScrollEnd;
    HINT  m_xBackup;//��갴��ʱλ��
    HINT  m_yBackup;
    HINT  m_xOffset;//���ƫ��
    HINT  m_yOffset;

    HBOOL m_bCanMove; // ��ǰ�Ƿ��ڹ���״̬
    HINT m_startIndex;//��ʼ���Ƶ���

    HINT m_StartTime;//��갴��ʱ��׼ʱ��
    HBOOL m_bAutoScroll;//�Զ�����
    HBOOL m_bAutoScrollBackup;//���ݣ���Ҫ����ָ�����������е���ʱ״̬
    HINT m_nScrollOffset;
    HINT m_nOffsetBackup;
    HINT m_ScrollbaseTime;
	HBOOL m_bEnableMove; //������
    vector<HINT> m_bEnableMsgVec;

	HBOOL m_bEnableLostSelectIndexMove;

	HBOOL m_bEnableFocusButtonDown;

	HINT m_nChangedIndex;

	HBOOL m_bEnableCallBack;

	HBOOL m_bClickEventHappen;

	HBOOL m_bEnableRoll;

	HINT m_nRollCount; //������������
	HINT m_nRollNum;	// ��������
	HINT m_nScrollBaseTime;//��¼��ʱ���Ļ�׼

	HINT m_nOffset;
	
	HBOOL m_bCanScroll;

	HBOOL m_bSecondeFlag;
	HINT  m_nSecondOffset;
	HINT  m_nLongPressTime;
	//kn_int	m_StartTime;
	HBOOL m_bHaveLongPress;
	HBOOL m_bEnableLongPress;//�Ƿ�������
};