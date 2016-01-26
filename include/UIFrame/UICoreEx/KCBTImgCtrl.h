/**
* Copyright (C) 2010， 
* All rights reserved.
*
* 文件名称: d:\Dev\Cypress\CypressDB\03IMPLEMENT\0301Code\Cypress\hmiengineEx\KCBTImgCtrl.h
* 摘    要:
*
* 当前版本: 1.0
* 作    者: 
* 完成日期: 2010-4-21
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1           2010-4-21             		创建
*	2			2010-4-23		  		修改控件阴影效果
*	3			2010-4-27		  		添加惯性效果
*	4			2010-7-3		鞠华玮		添加重置控件状态的函数
*
**/


#pragma once
#include "KCWnd.h"
#include <vector>

#define MAX_ALPHA_NUM	(27)

class CYPRESS_DLL_API HCBTImgCtrl: public HCBaseCtrl
{
public:
	HCBTImgCtrl(void);
	~HCBTImgCtrl(void);
	// 描画函数
	void Draw(IReSurface *pSurface);
	// 消息处理函数
	HBOOL DoMessage(HMessage* msg);
	// 设置点击回调
	void SetCallClickImgEvent(void (*callback)(HINT , void*) ,void *pThis);
	// 检查点击位置有效性
	HBOOL CheckPointValid(HINT x,HINT y);
	// 重置控件
	void Reset(void);

private:
	//vector<kn_string>	m_vInfo;


	IReSurface *		m_pBkSurf;
	HINT m_nBWidth;
	HINT m_nBheigth;
	HINT m_nMoveWidth;
	HINT m_nIndex;
	HBOOL m_bDownEvent;
	IReSurface *		m_pSeclectSurf;
	HINT m_nLbtnDown;
	HBOOL m_bMove;

	// 点击回调
	void* m_pParentCtrl;
	void (*m_pCallbackClickEvent)(HINT nIndex, void*);

	IReSurface *		m_pBackGrndSurf;
	IReSurface *		m_pSlideSurf;
	HINT				m_nOffset;

	// 惯性效果
	HINT  m_xBackup;//光标按下时位置
	//kn_int  m_xOffset;//相对偏移

	HBOOL m_bCanMove; // 当前是否处于滚动状态
	//kn_int m_startIndex;//起始绘制的项

	HINT m_StartTime;//鼠标按下时基准时间
	HBOOL m_bAutoScroll;//自动滑行
	HBOOL m_bAutoScrollBackup;//备份，主要用于指定滚动过程中单击时状态
	HINT m_nScrollOffset;
	//kn_int m_nOffsetBackup;
	HINT m_ScrollbaseTime;

	IReSurface* m_szpAlphaSur_Sel[MAX_ALPHA_NUM];
	IReSurface* m_szpAlphaSur_Nor[MAX_ALPHA_NUM];

	HINT m_rowWidth;
};
