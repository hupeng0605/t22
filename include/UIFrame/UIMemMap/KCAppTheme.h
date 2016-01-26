/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCAppTheme.h
* 摘    要: 主题管理类，使用共享内存管理应用程序主题
*
* 当前版本: 1.0
* 作    者:  
* 完成日期: 2009-11-17
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1                   2009-11-17             创建
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
    // *  功　　能: 主题管理类
    // *  作　　者:  
    // *  日　　期: 2009-12-23
    //***************************************************************
    class CYPRESS_DLL_API HCAppTheme
    {
    private:
        HCAppTheme(IN HBOOL isClient);
        ~HCAppTheme();
        HCAppTheme(const HCAppTheme&);// 故意不实现

    public:
        static HCAppTheme* GetInstance(IN HBOOL isClient);
		static void ExitInstance(void);

        // 服务端加载主题，注意：客户端禁止调用此函数加载主题到共享内存区（从0~255）
        HBOOL LoadTheme(IN HBYTE themeID);
        // 客户端或服务端获取当前主题的Surface
        IReSurface* GetSurface();

    private:
        IMemDispatch * m_pMemory; // 管理共享内存
        HBOOL m_bIsClient;
		static HCAppTheme* m_pClientInstance;
		static HCAppTheme* m_pServerInstance;
    };
}