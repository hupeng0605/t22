/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCDialSlide.h
* 摘    要: 带有刻度的滑动条
*
* 当前版本: 1.0
* 作    者:  
* 完成日期: 2009-12-28
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1           2009-12-28       			创建
*	2           2010-02-11                    			将快捷方式图片上文字字体设为矢量字体
**/

#ifndef _KCDIALSLIDE_H_
#define _KCDIALSLIDE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWnd.h"
#include <vector>
#define PRESETICON 12
// 表盘显示风格
enum eDialSlideStyle
{
    eFixedPoint = 0,// 指针是固定的
    eFixedDial,// 表盘是固定的（表盘刻度由背景图片提供）
};

//***************************************************************
// *  功　　能: 带有刻度的滑动条
// *  作　　者:  
// *  日　　期: 2009-12-28
//***************************************************************
class CYPRESS_DLL_API HCDialSlide : public HCBaseCtrl
{
public:
    HCDialSlide();
    virtual ~HCDialSlide();

    // 创建控件
    HBOOL Create(IN HINT x, IN HINT y, IN HINT width, IN HINT height);

    // 消息处理函数，各子类都要重载
    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);

public:
    // =======================对外部接口========================//

    // 设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
    void SetBkgndN(IN IReSurface* pSur);
    void SetBkgndN(IN const HString& pFileName);

    // 设置刻度指针图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
    void SetBkgndP(IN IReSurface* pSur);
    void SetBkgndP(IN const HString& pFileName);
	// 设置常阴影图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
	void SetBkgndNShadow(IN IReSurface* pSur);
	void SetBkgndNShadow(IN const HString& pFileName);

    // 设置快捷方式图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
    void SetPresetIcon(IN IReSurface* pSur);
    void SetPresetIcon(IN const HString& pFileName);

    // 设置格式化字符串
    void SetFormat(IN const HString& strFormat);
    // 设置当前值
    void SetValue(IN HFLOAT nValue);
    // 设置刻度区，相对于控件本身
    void SetScaleRect(IN const kn_rect& rect);
    // 滑动条范围
    void SetBound(IN HFLOAT nMin, IN HFLOAT nMax);
    // 设置单个小刻度
    void SetScale(IN HFLOAT nScale);
    // 设置控件显示方式
    void SetVertical(IN HBOOL bVertical);
    // 设置风格
	void SetStyle(IN eDialSlideStyle eStyle);
	// 设置表盘颜色 
	void SetScaleColor(const RECOLOR& color); 
	// ============================快捷方式接口
	// 添加快捷方式
	void AddShortcut(IN HFLOAT nSacle);
	// 删除快捷方式
	void DeleteShortcut(IN HFLOAT nScale);
	// 清空快捷方式
	void ClearShortcut();
	HINT IsInRect(HINT pix,HINT piy);
	void SetShortcut(IN HFLOAT nSacle,IN HINT index);
	void SetBandKind(HINT band);//设置状态
    // 获取格式化字符串
    inline HString GetFormat() const
    {
        return m_strFormat;
    }
    // 获取当前值
    inline HFLOAT GetValue() const
    {
        return m_nValue;
    }
    // 获取最小值
    inline HFLOAT GetMinValue() const
    {
        return m_nMinValue;
    }
    // 获取最大值
    inline HFLOAT GetMaxValue() const
    {
        return m_nMaxValue;
    }

    // 获取单个小刻度
    inline HFLOAT GetScale() const
    {
        return m_nScale;
    }

    // 设置值改变回调函数
    inline void SetCallBackValueChange(void (*callback)(void*, void*), void* pThis)
    {
        m_pCallBackValueChange = callback;
        m_pThisValueChange = pThis;
	}

	// 设置鼠标释放时回调函数
	inline void SetCallBackUp(void (*callback)(void*, void*), void* pThis)
	{
		m_pCallBackUp = callback;
		m_pThisUp = pThis;
	}
	inline void SetCallBackPrest(void (*callback)(void *,void*),void*pThis)
	{
		m_pCallBackPreset = callback;
		m_pThis = pThis;
	}

	inline void SetCallBackSameValue(void (*callback)(void *,HINT nindex),void* pThis)
	{
		m_pCallBackSameValue = callback;
		m_pThis = pThis;
	}
private:
    //
    HString formatStr(IN float fValue) const;
    // 判断给定数值是否处于有效范围内
    HINT isBound(float fValue) const;
    // 获取表盘固定风格时的每一个频率所占用的像素宽度（或高度）
    HFLOAT getPixelPreScale() const;
    //
    HINT getSumScaleCount() const ;
    //仅仅更新表盘刻度区m_pDialSur数据，不导致绘制

protected:
    virtual void UpdateDialSur();
	IReSurface* GetFontSurf(const HCHAR* str);
protected:
	RECOLOR m_ScaleColor;	
    vector<HFLOAT> m_vPreset;// 存储的预置频道
    HBOOL m_bAttrChanged;// 属性值是否发生改变
    HFLOAT m_nValue;// 当前值
    HFLOAT m_nMinValue, m_nMaxValue;// 最小值、最大值
    HFLOAT m_nScale;// 刻度
    kn_rect m_rectDial;// 表盘响应消息的区域
    HString m_strFormat;// 用于格式化m_nValue、m_nMinValue和m_nMaxValue的字符串
    POINT m_nMousePos;// 鼠标按下时的位置
    HBOOL m_bMouseDown;//表示鼠标是否按下
    IReSurface* m_pDialSur;//  表盘刻度区Surface
    HINT m_nOffset;// 相对上次，此次刻度移动位置（表盘固定风格时，偏移量永远为相对于起始位置）

    // 回调函数变量,要传入类指针
    void (*m_pCallBackValueChange)(void *, void *);
	void (*m_pCallBackSameValue)(void *,HINT nIndex);
	void* m_pThisValueChange;
	void (*m_pCallBackUp)(void *, void *);
	void (*m_pCallBackPreset)(void *, void *);
	HString GetStrNum(HFLOAT Freq);
	void* m_pThisUp;

    HBOOL m_bImageNFromFile;// 背景图片是否来自于文件
    IReSurface* m_pImageN;// 背景图片

    HBOOL m_bImagePFromFile;// 刻度指针图片是否来自于文件
    IReSurface* m_pImageP;// 刻度指针图片

    HBOOL m_bPresetIconFromFile;// 预置频道图片是否来自于文件
    IReSurface* m_pPresetIcon;// 预置频道图片

    // ===================================新增的属性2009-01-28
    HBOOL m_bVertical;// 是否垂直显示表盘s
	eDialSlideStyle m_eSytle;// 表盘风格
	kn_rect m_nPresetrect[PRESETICON];
	IReSurface *m_pBnkNShadow;
	HBOOL m_bmove;
	HINT m_nSpace;
	map<HString,IReSurface*> m_FontCacheSurfMap;
	HINT m_nKind;//为零时为FM  为1时为AM
};

#endif
