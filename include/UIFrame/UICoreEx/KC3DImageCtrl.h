/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称:	KC3DImageCtrl.h
* 摘    要:	
*
* 当前版本:	1.0
* 作    者:	 
* 完成日期:	2010-01-06
*
* 修改历史：
* [修改序列]	[修改日期] 		[修改者]		[修改内容]
*	1					2010-01-06    	     	创建
* 	
**/


#pragma once

#include "KCWnd.h"

#define MAX_IMG_NUM  (HINT)6// 最多显示图片数量

class CYPRESS_DLL_API HC3DImageCtrl: public HCBaseCtrl
{
public:
	HC3DImageCtrl(void);
	~HC3DImageCtrl(void);

	virtual HBOOL DoMessage(HMessage* msg);
	virtual void Draw(IReSurface* pSurface);
	
	// 设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
	void SetBkgndN(IN IReSurface* pSur);
	void SetBkgndN(IN const HString& pFileName);
	// 设置预览的图片
	void SetImages(IN const vector<HString>& images, IN HINT nStartIndex = 0);

	// 设置图片切换改变回调函数
	inline void SetCallBackIndexChange(void (*callback)(void*, void*), void* pThis)
	{
		m_pCallBackIndexChange = callback;
		m_pThisIndexChange = pThis;
	}
protected:
	void DrawItem(IReSurface* pSurface, HINT nIndex, HINT cnt);
	void MoveToRight();
	void MoveToLeft();

	// 转换到以透视点为原点的坐标系
	POINT GetCoor(POINT point);
	// 转换到以(0,0)为原点的坐标系
	POINT RecCoor(POINT point);
	// 获取最后一项到当前描画项的左边距之间的距离
	HINT GetDistance(HINT first, HINT diff, HINT cnt);
	

private:
	HBOOL m_bImageNFromFile;// 背景图片是否来自于文件
	IReSurface* m_pImageN;// 背景图片
	// 回调函数变量,要传入类指针
	void (*m_pCallBackIndexChange)(void *, void *);
	void* m_pThisIndexChange;

private:
	// 
	HINT m_nMouseX;
	HINT m_nMouseY;
	HBOOL m_bMouseDown;

	//kn_int m_dis_x;
	vector <IReSurface*> m_vImgSurface;

	// add 09.12.13 jhw
	HINT m_maxDisplayIdx;
	// end
	HINT m_nCurIndex;

protected:
	//kn_float x_div_gap;
	//kn_int z_div_gap;
protected:
	HINT div_cnt;
	// 移动方向
	HINT m_direction;
	// 预览图
	vector<HString> m_vImages;

	// add 09.12.15 jhw
	// 顶点斜率
	// 左下角
	HFLOAT m_slopeA;
	// 左上角
	HFLOAT m_slopeB;
	// 右上角
	HFLOAT m_slopeC;
	// 右下角
	HFLOAT m_slopeD;
	//中点斜率
	HFLOAT m_slopeBottom;
	HFLOAT m_slopeTop;
	// 边斜率
	HFLOAT m_slopeAD;
	HFLOAT m_slopeBC;
	// BC,AD延伸至Y轴交点
	HFLOAT m_yCutBC;
	// 最底层图片顶点
	POINT m_StartA;
	POINT m_StartB;
	POINT m_StartC;
	POINT m_StartD;
	POINT m_StartTop;
	POINT m_StartBottom;
	// 最顶层图片顶点
	POINT m_EndA;
	POINT m_EndB;
	POINT m_EndC;
	POINT m_EndD;
};
