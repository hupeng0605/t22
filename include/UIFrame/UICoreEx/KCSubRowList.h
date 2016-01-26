/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCSubRowList.h
* ժ    Ҫ:
*
* ��ǰ�汾: 1.0
* ��    ��:               
* �������: 2010-04-20
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1           2010-04-20                    			����
*	2			2010-04-21                    			������������ı�����
*	3			2010-04-24		              			�޸ĵ����ص�
**/

#pragma once

#include "KCwnd.h"
#include "RenderingEngine.h"
#include <vector>
using namespace std;

typedef vector<HString*> STR_VEC;
typedef vector<HString*>::iterator STR_VEC_IT;
typedef vector<STR_VEC*>::iterator STR_VEC_VEC_IT;

typedef vector<IReSurface*> SURF_VEC;
typedef vector<IReSurface*>::iterator SURF_VEC_IT;

typedef void (*ClickCallBack)(void*, HINT, HINT);
typedef void (*MoveCallBack)(void*,void*);
//��һ��kn_intΪ��ʼֵ���ڶ���kn_intΪ����
typedef void (*DrawNoValueCallBack)(void*, HINT, HINT);
// �����ı�����
typedef struct tagTextAttribute
{
	HINT x;
	HINT y;
	HINT fontwidth;
	HINT fontheight;
	RECOLOR nColor;
	RECOLOR fColor;
}TextAttribute;

class CYPRESS_DLL_API HCSubRowList : public HCBaseCtrl
{
public:
    HCSubRowList();
    ~HCSubRowList();
public:
	// �����ؼ�
    void Create(HINT x, HINT y, HINT rowheight, HINT subrownum, HINT rowNum,HINT nRowWidth);
	// ���ø���ı���
    void SetSurf(const HCHAR* pDefaultOddSurfPath, const HCHAR* pDefaultEvenSurfPath, const HCHAR* pNormalOddSurfPath,
                 const HCHAR* pNormalEvenSurfPath, const HCHAR* pFocusOddSurfPath, const HCHAR* pFocusEvenSurfPath);

	// �����ı�����
	void SetTextAttribute(TextAttribute pTextAttribute,...);
	// ����ÿ������
    HBOOL AddString(HCHAR** pString1, ...);

	// ɾ��ĳ��
    HBOOL DelItem(HUINT index);

	// ����ĳ������������
    HBOOL SetString(HINT subrow, HINT row, const HCHAR* pString);
	HBOOL SetString(HINT row, HCHAR** pString1, ...);
	// ���ĳ������������
    const HCHAR* GetString(HINT subrow, HINT row);

    // ��õ�ǰѡ�е���
    inline HINT GetSelectIndex();
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
    //void EnableMsg(kn_int index, kn_bool bEnable);

	void EnableLostSelectIndexMove(HBOOL bEnable);
	
	HBOOL InsertString(HINT nPos,HCHAR** pString1, ...);

	void EnableFocusButtonDown(HBOOL bEnable);

	//���ÿ�ʼ��
	void SetStartIndex(HINT index);

	void EnableCallBack(HBOOL bEnableCallBack);

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

    IReSurface* m_pBackupSurf;

    HINT m_nSubRowNum;// ������
    vector<HINT> m_columnWidthVec;//ÿ�п��
    vector<HINT> m_textPosXVec;//ÿ��������ʾλ�ã����ÿ����ʼλ��
	vector<HINT> m_textStyleVec;

    HINT m_rowNum;// ��ʾ������
    HINT m_rowHeight;// ÿ�еĸ߶�
	HINT m_rowWidth;// ÿ�еĿ��
    HINT m_selectIndex;// ��ǰѡ�е���
    vector<STR_VEC*> m_strVec;
	vector<SURF_VEC*> m_surfVec;

	// �ı�ʽ������
	vector <TextAttribute> m_vecTextAttribute;

	MoveCallBack m_pCallBackDownMove;
	MoveCallBack m_pCallBackUpMove;
    ClickCallBack m_pCallBackClick;
	DrawNoValueCallBack m_pCallBackDrawNoValue;

	void(*m_pCallBackScrollOutRange)(void*, HBOOL);
    void(*m_pCallBackScrollEnd)(void*, HBOOL);
	void (*m_pCallBackMove)(void *, void *);

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

    vector<HINT> m_bEnableMsgVec;

	HBOOL m_bEnableLostSelectIndexMove;
	HBOOL m_bEnableFocusButtonDown;

	HBOOL m_bEnableCallBack;
};