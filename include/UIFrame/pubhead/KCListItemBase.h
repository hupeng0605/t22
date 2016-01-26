
#pragma once

#include "Type.h"
#include "RenderingEngine.h"
#include "KCScrollBox.h"
#include "vector"

class HCScrollBox;

//����ͼƬ�Ķ��뷽ʽ
enum BkgMode
{
	LeftTopMode = 0,
	LeftBottomMode,
	RightTopMode,
	RightBottomMode,
};

enum eListItemType
{
	BaseListItem,//����
	CustomListItem,//������
	TextListItem,//�ı�������ʾ��
	PictureListItem,//ͼƬ����ͼ��ʾ
	DISCListItem,
};

typedef std::vector<HCBaseCtrl*> KCBASECTRL_VEC;
typedef std::vector<HCBaseCtrl*>::iterator KCBASECTRL_VEC_IT;

class UICORE_DLL_API HCListItemBase
{
public:
	HCListItemBase();
	virtual ~HCListItemBase();

	virtual void Create(HINT width, HINT height);

	//���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
	void SetBkgndN(IReSurface* pSur, BkgMode bkgMode = LeftBottomMode);
	void SetBkgndN(const HString& pFileName , BkgMode bkgMode = LeftBottomMode);

	//�����ͼ
	void SetBkgndA(IReSurface* pSur);
	void SetBkgndA(const HString& pFileName );

	//�۽�����ͼ
	void SetBkgndF(IReSurface* pSur);
	void SetBkgndF(const HString& pFileName );

	void SetBkgndCursorN(IReSurface* pSur);
	void SetBkgndCursorN(const HString& pFileName );

	void SetBkgndCursorF(IReSurface* pSur);
	void SetBkgndCursorF(const HString& pFileName );

	IReSurface* GetBkgndN();
	IReSurface* GetBkgndA();
	IReSurface* GetBkgndF();
	IReSurface* GetBkgndCursorN();
	IReSurface* GetBkgndCursorF();

	void Invalidate();

	virtual void SetFather(HCScrollBox* pScrollBox);
	HCScrollBox* GetFather();

	//���ÿ�߶�
	void SetSize(HINT width, HINT height);
	HINT GetWidth();
	HINT GetHeight();

	//�����ı�
	virtual void SetText(HString& text) = 0;
	virtual void SetText(const HCHAR* pTxt) = 0;
	HString& GetText();

	virtual void SetFatherWnd(HCWindow* pFatherWnd);
	//�����Ƿ��ܱ�ѡ��
	void SetCanFocus(HBOOL bCanFocus);
	//�Ƿ��ܱ�ѡ��
	HBOOL IsCanFocus();
	//��ǰ������
	eListItemType GetListItemType();

	//���ø����Ƿ���ʾ
	void SetShow(HBOOL bShow);
	HBOOL IsShow();

	//�����ƫ��(xSrc,ySrc)��(width,height)���Ƶ�pSurface��(x,y)��
	virtual void Draw(IReSurface* pSurface, HINT x, HINT y, HINT width, HINT height, HINT xSrc, HINT ySrc);
	virtual HBOOL DoMessage(HMessage* msg);

	//�ͷ������ʱ��Դ
	virtual void Release(){};

	HINT GetLangID()
	{
		return m_nLangID;
	}
	void SetLangID(HINT a_nLangID)
	{
		m_nLangID = a_nLangID;
	}
	void SetTextCenter(HBOOL bCenter);
	void SetData(int nData);
	int  GetData();
protected:
	//������
	eListItemType m_listItemType;

	HINT m_nLangID;
	HINT m_bCenter;
	//���汳��ͼ
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;
	BkgMode m_bkgMode;

	//�۽�����ͼ
	IReSurface* m_pBkgndA;
	HBOOL m_bBkgndARes;

	//�۽�����ͼ
	IReSurface* m_pBkgndF;
	HBOOL m_bBkgndFRes;

	IReSurface* m_pBkgndCursorN;
	HBOOL m_bBkgndCursorNRes;

	IReSurface* m_pBkgndCursorF;
	HBOOL m_bBkgndCursorFRes;

	//���ȣ��߶�
	HINT m_width;
	HINT m_height;

	//�ı�
	HString m_text;

	//����KCScrollBox
	HCScrollBox* m_pFather;
	//�Ƿ��ܱ�ѡ��
	HBOOL m_bCanFocus;

	HBOOL m_bShow;
	int m_nData;
};

