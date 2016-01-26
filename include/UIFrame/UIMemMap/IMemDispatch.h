/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: IMemDispatch.h
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

#include <Type.h>
#include <RenderingEngine.h>
#include "KCMemoryMap.h"

namespace KMemMap
{
    //***************************************************************
    // *  功　　能: 负责共享内存数据分发接口
    // *  作　　者:  
    // *  日　　期: 2009-12-23
    //***************************************************************
    class IMemDispatch
    {
    private:
        IMemDispatch(const IMemDispatch&);// 故意不实现
    public:
        IMemDispatch(IN const HString& name)
        {
            m_pMemMap = new KCMemoryMap(name);
        }
        virtual ~IMemDispatch()
        {
            SAFE_DELETE(m_pMemMap);
        }
        // 设置数据
        HBOOL SetData(const MEMMAP_DATA& memData)
		{
			return m_pMemMap->SetMemData(memData);
		}
        // 设置数据（从文件中）
        HBOOL SetDataFromFile(const HString& /*filePath*/)
		{
			return false;
		};
        //  获取数据
        virtual void* GetData() = 0;

    protected:
        KCMemoryMap* m_pMemMap; // 管理共享内存
    };
}