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

	//按钮按下回调
	void SetCallBackDown(void (*callback)(void*, void*), void*);
	//按钮弹起回调
	void SetCallBackUp(void (*callback)(void*, void*), void*);
	//长按消息
	void SetCallBackLongPress(void (*callback)(void*, void*), void*);
	void SetCallBackLongPressUp(void (*callback)(void*, void*), void*);
	void SetCallBackLongPressConsecutive(void (*callback)(void*, void*), void*);
	void EnableLongPressConsecutive(HBOOL bEnable, HINT times = 50);
	void EnableLongPress(HBOOL bEnable);
	void SetLongPressTime(HINT time);

	// 添加项
	HBOOL AddListItem(KCScrollItem* pListItem);
	// 在指定位置插入项
	HBOOL InsertListItem(HINT pos, KCScrollItem* pListItem);
	// 删除某项
	HBOOL DeleteListItem(KCScrollItem* pListItem);
	// 删除所有项
	void DeleteAllListItems();
	// 重新初始化所有变量
	void ReInit();

	//返回整个item列表
	SCROLL_ITEM_VEC& GetListItemVec();

	//获取选中的item
	KCScrollItem* GetSelectListItem();
	//返回item对应的索引
	HINT GetListItemIndex(KCScrollItem* pListItem);
	//返回选中项item的索引
	HINT GetSelectItemIndex();
	//设置选中项
	void SetSelectListItem(KCScrollItem* pListItem);
	void SetSelectListItem(HINT index);
	//点击是否自动设置选中项
	void EnableAutoCheck(HBOOL bAutoCheck = TRUE);

	//设置ScrollBoxEx的背景图
	void SetBkgnd(IReSurface* pSur);
	void SetBkgnd(const HString& pFileName);
	//设置焦点图层，即玻璃框
	void SetFouceItemBkgnd(IReSurface* pSur);
	void SetFouceItemBkgnd(const HString& pFileName);
	//设置每一行的背景图
	void SetItemBkgnd(IReSurface* pSur);
	void SetItemBkgnd(const HString& pFileName);

	//设置焦点图层在可见的哪一行显示
	void SetFouceRow(HINT nIndex);


	//设置item文本风格，如右对齐、居中，pixels表示右对齐像素
	void SetTextStyle(HDWORD dwFormat, HINT pixels = 10);
private:
	HINT GetItemIdxFromOffset(HINT yOffset);
	//返回item的索引对应在列表中显示的行
	HINT GetRowFromIndex(HINT nIndex);
protected:
	void ScrollItem(HINT nStart, HINT nEnd);
protected:
	SCROLL_ITEM_VEC		m_listItemVec;
	// 当前选中项指针
	KCScrollItem* m_pSelectItem;
	HINT m_nItemSpace;//列表框中每项的间距
	//// 所在项高度和
	//kn_int m_allHeight;
	//自动选中，当为真时，鼠标点击自动选中，否则，需要调用SetSelectListItem接口手动设置选中
	HBOOL m_bAutoCheck;
	HINT	m_nSelectIndex;
	//显示首行所在的索引
	HINT	m_nFirstItemIndex;
	//焦点框所在的显示行
	HINT	m_nFouceRowIndex;
	//焦点surface，即玻璃框
	IReSurface*	m_pFouceSurf;
	HBOOL		m_bFouceSurfRes;
	//可显示的行数
	HINT		m_nRows;
	//每一行的背景图
	IReSurface*	m_pItemBkSurf;
	HBOOL		m_bBkSurfRes;
	//控件背景图
	IReSurface*	m_pBkSurf;
	HBOOL		m_bBkRes;

	//item对齐方式
	HDWORD	m_dwTextStyle;
	HINT		m_nPixels;

	//按钮按下时回调函数变量,要传入类指针
	void (*m_pCallBackDown)(void *, void *);
	//按钮弹起时回调函数变量,要传入类指针
	void (*m_pCallBackUp)(void *, void *);
	// 鼠标长按消息
	HINT m_longPressTime;
	void (*m_pCallBackLongPress)(void *, void *);
	void (*m_pCallBackLongPressUp)(void *, void *);
	void (*m_pCallBackLongPressConsecutive)(void *, void *);
	
	//长按连续响应消息
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