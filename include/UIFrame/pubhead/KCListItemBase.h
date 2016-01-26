
#pragma once

#include "Type.h"
#include "RenderingEngine.h"
#include "KCScrollBox.h"
#include "vector"

class HCScrollBox;

//背景图片的对齐方式
enum BkgMode
{
	LeftTopMode = 0,
	LeftBottomMode,
	RightTopMode,
	RightBottomMode,
};

enum eListItemType
{
	BaseListItem,//基类
	CustomListItem,//常规类
	TextListItem,//文本换行显示类
	PictureListItem,//图片缩略图显示
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

	//设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
	void SetBkgndN(IReSurface* pSur, BkgMode bkgMode = LeftBottomMode);
	void SetBkgndN(const HString& pFileName , BkgMode bkgMode = LeftBottomMode);

	//激活背景图
	void SetBkgndA(IReSurface* pSur);
	void SetBkgndA(const HString& pFileName );

	//聚焦背景图
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

	//设置宽高度
	void SetSize(HINT width, HINT height);
	HINT GetWidth();
	HINT GetHeight();

	//设置文本
	virtual void SetText(HString& text) = 0;
	virtual void SetText(const HCHAR* pTxt) = 0;
	HString& GetText();

	virtual void SetFatherWnd(HCWindow* pFatherWnd);
	//设置是否能被选中
	void SetCanFocus(HBOOL bCanFocus);
	//是否能被选中
	HBOOL IsCanFocus();
	//当前项类型
	eListItemType GetListItemType();

	//设置该项是否显示
	void SetShow(HBOOL bShow);
	HBOOL IsShow();

	//把项从偏移(xSrc,ySrc)按(width,height)绘制到pSurface的(x,y)上
	virtual void Draw(IReSurface* pSurface, HINT x, HINT y, HINT width, HINT height, HINT xSrc, HINT ySrc);
	virtual HBOOL DoMessage(HMessage* msg);

	//释放相关临时资源
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
	//项类型
	eListItemType m_listItemType;

	HINT m_nLangID;
	HINT m_bCenter;
	//常规背景图
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;
	BkgMode m_bkgMode;

	//聚焦背景图
	IReSurface* m_pBkgndA;
	HBOOL m_bBkgndARes;

	//聚焦背景图
	IReSurface* m_pBkgndF;
	HBOOL m_bBkgndFRes;

	IReSurface* m_pBkgndCursorN;
	HBOOL m_bBkgndCursorNRes;

	IReSurface* m_pBkgndCursorF;
	HBOOL m_bBkgndCursorFRes;

	//项宽度，高度
	HINT m_width;
	HINT m_height;

	//文本
	HString m_text;

	//所在KCScrollBox
	HCScrollBox* m_pFather;
	//是否能被选中
	HBOOL m_bCanFocus;

	HBOOL m_bShow;
	int m_nData;
};

