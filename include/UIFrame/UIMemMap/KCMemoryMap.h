/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCMemoryMap.h
* 摘    要: 共享内存
*
* 当前版本: 1.0
* 作    者:  
* 完成日期: 2009-11-18
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1                   2009-11-18             创建
*
**/

#pragma once

#include <PubHead.h>
#include "ThemeDef.h"

namespace KMemMap
{
    // KTC文件共享内存数据
    typedef struct _memmap_ktc_
    {
        HLONG m_nSize;
        HBYTE* m_pData;
        void clear()
        {
            m_nSize = 0;
            m_pData = NULL;
        }
        _memmap_ktc_()
        {
            clear();
        }
    } MEMMAP_DATA;

    //***************************************************************
    // *  功　　能: 内存映射
    // *  作　　者:  
    // *  日　　期: 2009-11-27
    //***************************************************************
    class KCMemoryMap
    {
    private:
        KCMemoryMap(const KCMemoryMap&);

    public:
        KCMemoryMap(IN const HString& memName);
        ~KCMemoryMap();

        // 设置共享数据，仅对服务端有效
        HBOOL SetMemData(IN const MEMMAP_DATA& ktcMem);
        // 获取共享数据
        HBOOL GetMemData(OUT MEMMAP_DATA& ktcMem);

    protected:
        virtual void Disponse();// 释放资源

    private:
        HString m_strMemName;// 共享内存名称
		HINT m_nMemSize;// 共享内存大小
		HANDLE   m_hMapFile;// 共享数据块句柄
        HBYTE* m_pMapAddr;   // 共享数据块地址
		HANDLE m_hAccessMutex;//互斥体
    };
}