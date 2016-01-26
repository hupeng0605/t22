/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCStatusMemory.h
* 摘    要:
*
* 当前版本: 1.0
* 作    者:  
* 完成日期: 2010-01-22
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1                   2010-01-22             创建
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
    class KCStatusMemory : public IMemDispatch
    {
    public:
		KCStatusMemory(IN const HString& name);
        // 设置数据
        //kn_bool SetData(IN const MEMMAP_DATA& memData);
        // 设置数据（从文件中）
        //kn_bool SetDataFromFile(IN const kn_string& /*filePath*/)
        //{
        //    return false;
        //}
        //  获取数据
        void* GetData();
        
    };
}