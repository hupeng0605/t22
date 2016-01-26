/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KC3DRotationCtrl.h 
* 摘    要:
*
* 当前版本: 1.0
* 作    者:               
* 完成日期: 2010-04-21
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1           2010-04-21                   			创建
*
**/


#if !defined(AFX_KC3DROTATIONCTRL_H__RIPPLEIMAGECTRL__INCLUDED_)
#define AFX_KC3DROTATIONCTRL_H__ROTATIONCTRL__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWnd.h"
#include "KC3DWorld.h"

// 旋转方向
enum RotateDirect
{
	eNull = 0,
	eRight,
	eLeft
};

class CYPRESS_DLL_API HC3DRotationCtrl : public HCBaseCtrl  
{
public:
	HC3DRotationCtrl();
	~HC3DRotationCtrl();

	virtual void Draw(IReSurface* pSurface);
	HBOOL DoMessage(HMessage* msg);

	//设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
	void SetBkgndN(IReSurface* pSur,RotateDirect eRotateDirect = eNull);
	void SetBkgndN(const HString& pFileName,RotateDirect eRotateDirect = eNull);
	//设置图片的大小
	void SetImageSize(HINT width, HINT height);
	// 返回图片
	IReSurface* GetImgSurface();

	// 设置3D旋转相关参数(最佳旋转参数)
	void Set3DAttribute();
	// 设置旋转间隔时间
	void SetRotateTime(HINT nmsTime);
	// 旋转Surface
	void RotateSurface(IReSurface* pSurf);

	HINT RegularAngle(HINT angle);
private:
	//常规背景图
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;

	IReSurface* m_pBkgndNext;
	HBOOL m_bBkgndNextRes;

	// 图片宽和高
	HINT m_imageWidth;
	HINT m_imageHeight;
	//
	HC3DWorld m_3dWorld;
	// 基准时间
	HINT m_nBasetime;
	// 旋转间隔时间
	HINT m_nmsTime;
	// 旋转角度
	HINT m_nAngle;
	// 旋转方向
	RotateDirect m_eRotateDirect;



	HBOOL m_bRotateFinish;
	
};
#endif