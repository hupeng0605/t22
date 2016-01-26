/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCRippleImageCtrl.h 
* 摘    要:
*
* 当前版本: 1.0
* 作    者:               
* 完成日期: 2009-12-29
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1            2009-12-29                    			创建
*   2			 2011-5-17		               			增加SetInvertOnly函数设置是否只贴倒影无波纹
**/


#if !defined(AFX_KCPROGRESSCTRL_H__RIPPLEIMAGECTRL__INCLUDED_)
#define AFX_KCPROGRESSCTRL_H__RIPPLEIMAGECTRL__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWnd.h"


class CYPRESS_DLL_API HCRippleImageCtrl : public HCBaseCtrl  
{
public:
	HCRippleImageCtrl();
	~HCRippleImageCtrl();

	virtual void Draw(IReSurface* pSurface);
	HBOOL DoMessage(HMessage* msg);

	//设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
	void SetBkgndN(IReSurface* pSur);
	void SetBkgndN(const HString& pFileName);

	//设置每次移动时的时间间隔
	void SetMoveInOutTime(HINT ms);
	//设置移动的次数
	void SetMoveInOutNum(HINT num);
	//图片更换时是否允许移入移出
	void EnableMoveInOut(HBOOL bEnable);

	//设置图片的大小
	void SetImageSize(HINT width, HINT height);
	//设置水波图像的高度
	void SetRippleImageHeight(HINT height);

	//设置水波图像的更新时间
	void SetRippleTime(HINT ms);
	//开始水波播放
	void Play();
	void Stop();

	// 返回图片
	IReSurface* GetImgSurface();

	//add by zjz,2011-5-17,设置是否只有倒影参数
	//设置是否只有倒影
	void SetInvertOnly(HBOOL bInvertOnly);
	//add end
	
private:
	//常规背景图
	IReSurface* m_pBkgndN;
	HBOOL m_bBkgndNRes;

	//进入背景图
	IReSurface* m_pBkgndIn;
	HBOOL m_bBkgndInRes;

	//图片更换时移入移出
	HBOOL m_bCanMoveInOut;
	
	//当前的状态
	HBOOL m_bMoveInOut;
	HINT m_moveInOutIndex;//移动到第几次
	HINT m_moveInOutBaseTime;//基准时间
	HINT m_moveInOutTime;//移动的间隔时间
	HINT m_nMoveInOutNum;//总共移动的次数

	HINT m_imageWidth;
	HINT m_imageHeight;
	HINT m_rippleImageHeight;
	
	//动画定时器
	HINT m_msTime;
	HBOOL m_bPlay;
	//水波播放的当前帧
	HINT m_nFrame;
	HINT m_nBasetime;

	//add by zjz,2011-5-17,设置是否只有倒影参数
	//是否只有倒影
	HBOOL m_bInvertOnly; //是否纯倒影，为true时只有倒影没有波纹
	//add end

};

#endif