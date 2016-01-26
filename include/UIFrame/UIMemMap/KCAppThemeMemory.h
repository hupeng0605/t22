/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCAppThemeMemory.h
* 摘    要:
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

namespace KMemMap
{
    //***************************************************************
    // *  功　　能: 主题共享内存管理类
    // *  作　　者:  
    // *  日　　期: 2009-12-23
    //***************************************************************
    class KCAppThemeMemory : public IMemDispatch
    {
    public:
        KCAppThemeMemory(IN const HString& name);
        ~KCAppThemeMemory();
        // 设置数据
        HBOOL SetData(const MEMMAP_DATA& /*memData*/)
        {
            return false;
        }
        // 设置数据（从文件中）
        HBOOL SetDataFromFile(const HString& filePath);
        //  获取数据
        void* GetData();
	private:
	IReSurface* m_pBakSurface;
    };
}