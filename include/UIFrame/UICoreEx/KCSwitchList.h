/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称:	KCSwitchList.h
* 摘    要:	
*
* 当前版本:	1.0
* 作    者:	              
* 完成日期:	2010-01-29
*
* 修改历史：
* [修改序列]	[修改日期] 		[修改者]		[修改内容]
*	1			2010-01-29    	                  	    创建
* 	
**/
#pragma once


#include "KCWindow.h"
#include "vector"

typedef vector <IReSurface*> SURF_ITEM_VEC;
typedef void (*CLICKCALLBACK)(void* , HINT, HBOOL,HBOOL);

class CYPRESS_DLL_API HCSwitchList : public HCBaseCtrl  
{
public:
	HCSwitchList();
	virtual ~HCSwitchList();


	//设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
	void SetBkgndN(IReSurface* pSurf);
	void SetBkgndN(const HString& pFileName);

	// 设置每页显示Icon数
	void SetPrePageIcon(HINT nNum);

	// 设置常规状态的Icon集合
	void SetNormalSurf(SURF_ITEM_VEC vecSufN);

	// 设置激活状态的Icon集合
	void SetActiveSurf(SURF_ITEM_VEC vecSufA);
	
	// 存放聚焦状态的Icon集合
	void SetFocusSurf(SURF_ITEM_VEC vecSufF);
	
	// 重置激活状态得图片
	void Reset();

	void ReturnHomePage();
	
	//单击回调
	void SetCallBackClick(CLICKCALLBACK pClickCallBack, void* );

	HBOOL DoMessage(HMessage* msg);
	void Draw(IReSurface* pSurface);

private:
	HINT GetIndexByY(HINT y);

private:

	//常规背景图
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;

	// 每页显示ICON数目
	HINT m_nPrePageIcon;
	
	// 存放常规状态的Icon集合
	SURF_ITEM_VEC m_vecSufNormal;

	// 存放激活状态的Icon集合
	SURF_ITEM_VEC m_vecSufActive;
	
	// 存放聚焦状态的Icon集合
	SURF_ITEM_VEC m_vecSufFocus;

	// 当前激活项
	HINT m_nActiveIndex;
	// 当前聚焦项
	HINT m_nFocusIndex;
	// 
	HINT m_nLastActiveIndex;
	
	CLICKCALLBACK m_pClickCallBack;

	HBOOL m_bHomePage;// 是否为主页标志位
	HBOOL m_bSwitch;// 是否点击切换按钮标志位
	HBOOL m_bCancelActive;
//	kn_bool m_bReset;// 是否重置指定位置图片标志位

	HINT m_nMouseDownIndex;
	HINT m_nMouseUpIndex;
	HBOOL m_bEnableCallBack;

};
