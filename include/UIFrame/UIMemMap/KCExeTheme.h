/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCExeTheme.h
* 摘    要: 程序转场时界面切换的Surface管理类，使用共享内存管理转场时的Surface
*
* 当前版本: 1.0
* 作    者:  
* 完成日期: 2009-12-23
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1                   2009-12-23             创建
*
**/

#pragma once

#include <RenderingEngine.h>
#include "IMemDispatch.h"

#ifndef MEMMAP_API
#error "Please include KMemMapAPI.h replace this head file, Have question to email:xiongzhens@dev.kotei.co"
#endif

namespace KMemMap
{
    //***************************************************************
    // *  功　　能: 程序转场时界面切换的Surface管理类
    // *  作　　者:  
    // *  日　　期: 2009-12-23
    //***************************************************************
    class CYPRESS_DLL_API HCExeTheme
    {
    private:
        HCExeTheme();
        ~HCExeTheme();
    private:
        HCExeTheme(const KCMemoryMap&);// 故意不实现

    public:
		static HCExeTheme* GetInstance();
        // 设置当前屏幕的Surface并将其保存到共享内存中
        HBOOL SetScreenSurface(IN IN IReSurface* pSurf);
        // 获取前一个屏幕显示的Surface
        IReSurface* GetPreScreenSurface();
		// 释放资源
		void Release();
		
    private:
        IMemDispatch* m_pMemory;
    };
}