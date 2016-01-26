/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCPickButton.cpp
* 摘    要:
*
* 当前版本: 1.0
* 作    者:               
* 完成日期: 2009-12-29
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1            2010-2-4                     			创建
*	2			 2010-8-12	                  			添加超长滚动功能
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
//第一个kn_int为起始值，第二个kn_int为个数
typedef void (*DrawNoValueCallBack)(void*, HINT, HINT);

class CYPRESS_DLL_API HCListBoxEx : public HCBaseCtrl
{
public:
    HCListBoxEx();
    ~HCListBoxEx();
public:
    //***************************************************************
    // *  功　　能: 创建控件
    // *  入口参数: 可变参数：每列宽度
    // *  出口参数:
    // *  返 回 值:
    //***************************************************************
    void Create(HINT x, HINT y, HINT height, HINT columnNum, HINT rowNum, HINT columnWidth1, ...);
    //***************************************************************
    // *  功　　能: 设置各项的背景
    // *  入口参数:
    // *  出口参数:
    // *  返 回 值:
    //***************************************************************
    void SetSurf(const HCHAR* pDefaultOddSurfPath, const HCHAR* pDefaultEvenSurfPath, const HCHAR* pNormalOddSurfPath,
                 const HCHAR* pNormalEvenSurfPath, const HCHAR* pFocusOddSurfPath, const HCHAR* pFocusEvenSurfPath);
	void SetCursorSurf(const HCHAR* pNormalOddCursorSurfPath, const HCHAR* pNormalEvenSurfPath,
						const HCHAR* pFocusOddCursorSurfPath, const HCHAR* pFocusEvenSurfPath);
    //***************************************************************
    // *  功　　能: 设置每列的文字x位置，Y轴居中显示
    // *  入口参数:
    // *  出口参数:
    // *  返 回 值:
    //***************************************************************
    void SetTextPos(HINT posX1, ...);
	void SetTextStyle(HINT style1,...);

    //***************************************************************
    // *  功　　能: 设置每项的文字
    // *  入口参数:
    // *  出口参数:
    // *  返 回 值:
    //***************************************************************
    HBOOL AddString(HCHAR** pString1, ...);
	    //***************************************************************
    // *  功　　能: 指定位置插入文字
    // *  入口参数:
    // *  出口参数:
    // *  返 回 值:
    //***************************************************************
	 HBOOL InsertString(HINT nPos,HCHAR** pString1, ...);

    //***************************************************************
    // *  功　　能: 删除某项
    // *  入口参数:
    // *  出口参数:
    // *  返 回 值:
    //***************************************************************
    HBOOL DelItem(HUINT index);

    //***************************************************************
    // *  功　　能: 设置某项某列的文字
    // *  入口参数:
    // *  出口参数:
    // *  返 回 值:
    //***************************************************************
    HBOOL SetString(HINT column, HINT row, const HCHAR* pString);
	HBOOL SetString(HINT row, HCHAR** pString1, ...);

    //***************************************************************
    // *  功　　能: 获得某项某列的文字
    // *  入口参数:
    // *  出口参数:
    // *  返 回 值:
    //***************************************************************
    const HCHAR* GetString(HINT column, HINT row);

    // 获得当前选中的行
    inline HINT GetSelectIndex();
	//设置是否让超长滚动
	inline void SetEnableScorll(HBOOL bIn);
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

	void EnableCallBack(HBOOL bEnableCallBack);

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
    void EnableMsgByIndex(HINT index, HBOOL bEnable);

	//滚动时是否丢失选中项的状态
	void EnableLostSelectIndexMove(HBOOL bEnable);

	void EnableFocusButtonDown(HBOOL bEnable);
	
	HBOOL IsListEmpty();

	void StopAutoScroll(HINT nStartIndex);

	//设置开始项
	void SetStartIndex(HINT index);

	//移动当前选中项，并保证选中项始终在屏幕内
	void MoveChangedIndex(HBOOL bDown);
	//添加长按事件
	void SetCallBackLongPress( void (*callback)(void*, HINT, HINT), void*pThis );
	//获取焦点时调用
	void OnFocus();
	//失去焦点时调用
	void OnLostFocus();
	//允许滚动
	void EnableMove(HBOOL bEnable);
	//允许长按回调
	void IsEnableLongPress(HBOOL bEnable);
	//返回列数
	HINT GetColNum()
	{
		return m_columnNum;
	}
	//获得LangID
	HINT GetLangID(HINT nRowIndex,HINT nColIndex)
	{
		return m_nLangId[nRowIndex][nColIndex];
	}
	//设置LangID
	void SetLangID(HINT a_nLangID,HINT nRowIndex,HINT nColIndex)
	{
		m_nLangId[nRowIndex][nColIndex] = a_nLangID;
	}

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

	IReSurface* m_pNormalCursorOddSurf;
	IReSurface* m_pNormalCursorEvenSurf;
	IReSurface* m_pFocusCursorOddSurf;
	IReSurface* m_pFocusCursorEvenSurf;

    IReSurface* m_pBackupSurf;

    HINT m_columnNum;// 列数
    vector<HINT> m_columnWidthVec;//每列宽度
    vector<HINT> m_textPosXVec;//每列文字显示位置，相对每列起始位置
	vector<HINT> m_textStyleVec;

    HINT m_rowNum;// 显示的行数
    HINT m_rowHeight;// 每行的高度
    HINT m_selectIndex;// 当前选中的项
    vector<STR_VEC*> m_strVec;
	vector<SURF_VEC*> m_surfVec; // 打点以后的Surface
	vector<SURF_VEC*> m_OrgSurfVec;// 原始的Surface




    ClickCallBack m_pCallBackClick;
	// 下滑
	MoveCallBack m_pCallBackDownMove;
	// 上滑
	MoveCallBack m_pCallBackUpMove;

	DrawNoValueCallBack m_pCallBackDrawNoValue;

	void(*m_pCallBackScrollOutRange)(void*, HBOOL);
    void(*m_pCallBackScrollEnd)(void*, HBOOL);
	void (*m_pCallBackMove)(void *, void *);
	void (*m_pCallBackLongPress)(void*, HINT, HINT);
	
	HINT m_nLangId[MAX_ROW_NUM][MAX_COL_NUM];
	//void EnableMove(kn_bool bEnable);
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
	HBOOL m_bEnableMove; //允许滑动
    vector<HINT> m_bEnableMsgVec;

	HBOOL m_bEnableLostSelectIndexMove;

	HBOOL m_bEnableFocusButtonDown;

	HINT m_nChangedIndex;

	HBOOL m_bEnableCallBack;

	HBOOL m_bClickEventHappen;

	HBOOL m_bEnableRoll;

	HINT m_nRollCount; //滚动次数计数
	HINT m_nRollNum;	// 滚动次数
	HINT m_nScrollBaseTime;//记录定时器的基准

	HINT m_nOffset;
	
	HBOOL m_bCanScroll;

	HBOOL m_bSecondeFlag;
	HINT  m_nSecondOffset;
	HINT  m_nLongPressTime;
	//kn_int	m_StartTime;
	HBOOL m_bHaveLongPress;
	HBOOL m_bEnableLongPress;//是否允许长按
};