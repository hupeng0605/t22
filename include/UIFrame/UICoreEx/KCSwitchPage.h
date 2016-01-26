/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称:	KCSwitchPage.h
* 摘    要:	
*
* 当前版本:	1.0
* 作    者:	              
* 完成日期:	2010-02-01
*
* 修改历史：
* [修改序列]	[修改日期] 		[修改者]		[修改内容]
*	1			2010-02-01    	                  	    创建
* 	
**/
#pragma once


#include "KCWindow.h"
#include "vector"

class CYPRESS_DLL_API HCSwitchPage : public HCBaseCtrl  
{
public:
	HCSwitchPage();
	virtual ~HCSwitchPage();


	//设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
	void SetBkgndN(IReSurface* pSurf);
	void SetBkgndN(const HString& pFileName);

	void ActiveRearPage();
	void AddRearPage();
	void CancelRearPage();
	
	// 页面切换
	HBOOL SwitchPage(HINT page);

	// 设置ICON
	void SetIconSurface(HString& pSurfActivePath,HString& pSurfNormalPath, HString& pSurfRearPath);

	// 设置ICON间距
	void SetIconOffset(HINT nOffset);

	// 设置ICON起始位置
	void SetIconStartPos(HINT x, HINT y);

	void SetTotalPageNum(HINT pageNum);

	virtual void Draw(IReSurface* pSurface);


private:

	//常规背景图
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;

	// 激活ICON图
	IReSurface* m_pSurfActiveIcon;
	// 普通ICON图
	IReSurface* m_pSurfNormalIcon;
	// 后台ICON图;
	IReSurface* m_pSurfRearIcon;

	// 当前页
	HINT m_nCurPage;
	// 总页数
	HINT m_nTotalPage;

	// 备份前台激活页
	HINT m_nFrontActivePage;


	// 切换页
	HINT m_nSwitchPage;
	// ICON之间偏移
	HINT m_nIconOffset;
	// ICON起始位置
	HINT m_xIconPos;
	HINT m_yIconPos;

	// 是否激活后台
	HBOOL m_bActiveRear;

};
