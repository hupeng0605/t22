/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCSubRowList.h
* 摘    要:
*
* 当前版本: 1.0
* 作    者:               
* 完成日期: 2010-04-20
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1           2010-04-20                    			创建
*	2			2010-04-21                    			添加设置子项文本属性
*	3			2010-04-24		              			修改单击回调
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
//第一个kn_int为起始值，第二个kn_int为个数
typedef void (*DrawNoValueCallBack)(void*, HINT, HINT);
// 子项文本属性
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
	// 创建控件
    void Create(HINT x, HINT y, HINT rowheight, HINT subrownum, HINT rowNum,HINT nRowWidth);
	// 设置各项的背景
    void SetSurf(const HCHAR* pDefaultOddSurfPath, const HCHAR* pDefaultEvenSurfPath, const HCHAR* pNormalOddSurfPath,
                 const HCHAR* pNormalEvenSurfPath, const HCHAR* pFocusOddSurfPath, const HCHAR* pFocusEvenSurfPath);

	// 设置文本属性
	void SetTextAttribute(TextAttribute pTextAttribute,...);
	// 设置每项文字
    HBOOL AddString(HCHAR** pString1, ...);

	// 删除某项
    HBOOL DelItem(HUINT index);

	// 设置某项中子项文字
    HBOOL SetString(HINT subrow, HINT row, const HCHAR* pString);
	HBOOL SetString(HINT row, HCHAR** pString1, ...);
	// 获得某项中子项文字
    const HCHAR* GetString(HINT subrow, HINT row);

    // 获得当前选中的行
    inline HINT GetSelectIndex();
	// 删除所有行
    void DelAllItems();
    void SetCallBackClick(ClickCallBack callBack, void* pThis);
	void SetCallBackDownMove(MoveCallBack DownMovecallBack, void* pThis);
	void SetCallBackUpMove(MoveCallBack UpMovecallBack, void* pThis);
    // 设置滚动结束回调
	void SetCallBackScrollEnd(void(*callback)(void*, HBOOL bScrollUp), void*pThis);
	void SetCallBackScrollOutRange(void(*callback)(void*, HBOOL bScrollUp), void*pThis);
	//列表框滚动事件
	void SetCallBackMove(void (*callback)(void*, void*), void*);

	// 在绘制时某项无值时调用
	void SetCallBackDrawNoValue(DrawNoValueCallBack callBack, void* pThis);

    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);

	//设置选择行
    void SetSelectIndex(HINT index);
	//获得项的总数目
    HINT GetTotalNum();
	// 获得行数
	HINT GetRowNum();
    // 得到第一个的索引号
    inline  HINT GetStarIndex();
	//设置第几项能响应消息或者不能
    //void EnableMsg(kn_int index, kn_bool bEnable);

	void EnableLostSelectIndexMove(HBOOL bEnable);
	
	HBOOL InsertString(HINT nPos,HCHAR** pString1, ...);

	void EnableFocusButtonDown(HBOOL bEnable);

	//设置开始项
	void SetStartIndex(HINT index);

	void EnableCallBack(HBOOL bEnableCallBack);

private:
    //***************************************************************
    // *  功　　能: 获得当前项的背景图片和文字颜色
    // *  入口参数: index:要获得的项
    // *  出口参数: pSurface:返回背景 pTextColor：文字颜色
    // *  返 回 值: TRUE:输入的index有效
    //***************************************************************
    HBOOL GetSurfAndColor(HINT index, IReSurface*& pSurface, RECOLOR*& pTextColor);

private:
    //奇偶项的背景，Default为无内容时背景
    IReSurface* m_pDefaultOddSurf;
    IReSurface* m_pDefaultEvenSurf;
    IReSurface* m_pNormalOddSurf;
    IReSurface* m_pNormalEvenSurf;
    IReSurface* m_pFocusOddSurf;
    IReSurface* m_pFocusEvenSurf;

    IReSurface* m_pBackupSurf;

    HINT m_nSubRowNum;// 子行数
    vector<HINT> m_columnWidthVec;//每列宽度
    vector<HINT> m_textPosXVec;//每列文字显示位置，相对每列起始位置
	vector<HINT> m_textStyleVec;

    HINT m_rowNum;// 显示的行数
    HINT m_rowHeight;// 每行的高度
	HINT m_rowWidth;// 每行的宽度
    HINT m_selectIndex;// 当前选中的项
    vector<STR_VEC*> m_strVec;
	vector<SURF_VEC*> m_surfVec;

	// 文本式样容器
	vector <TextAttribute> m_vecTextAttribute;

	MoveCallBack m_pCallBackDownMove;
	MoveCallBack m_pCallBackUpMove;
    ClickCallBack m_pCallBackClick;
	DrawNoValueCallBack m_pCallBackDrawNoValue;

	void(*m_pCallBackScrollOutRange)(void*, HBOOL);
    void(*m_pCallBackScrollEnd)(void*, HBOOL);
	void (*m_pCallBackMove)(void *, void *);

    void*m_pThisScrollEnd;
    HINT  m_xBackup;//光标按下时位置
    HINT  m_yBackup;
    HINT  m_xOffset;//相对偏移
    HINT  m_yOffset;

    HBOOL m_bCanMove; // 当前是否处于滚动状态
    HINT m_startIndex;//起始绘制的项

    HINT m_StartTime;//鼠标按下时基准时间
    HBOOL m_bAutoScroll;//自动滑行
    HBOOL m_bAutoScrollBackup;//备份，主要用于指定滚动过程中单击时状态
    HINT m_nScrollOffset;
    HINT m_nOffsetBackup;
    HINT m_ScrollbaseTime;

    vector<HINT> m_bEnableMsgVec;

	HBOOL m_bEnableLostSelectIndexMove;
	HBOOL m_bEnableFocusButtonDown;

	HBOOL m_bEnableCallBack;
};