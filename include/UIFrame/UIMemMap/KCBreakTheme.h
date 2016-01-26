/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCBreakTheme.h
* 摘    要: 中断界面Surface共享内存数据管理，如：音量、亮度、电话来电等临时界面的Surface
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
    class CYPRESS_DLL_API HCBreakTheme
	{
	private:
        HCBreakTheme();
        ~HCBreakTheme();
        HCBreakTheme(const KCMemoryMap&);// 故意不实现

	public:
		static HCBreakTheme* GetInstance();

        // 设置终端界面的Surface并将其保存到共享内存中
        HBOOL SetBreakSurface(IN IReSurface* pSurface);
        // 获取中断界面的m_pData数据
        HBYTE* GetBreakSurface(OUT HDWORD& width, OUT HDWORD& height, OUT HLONG& nSize);

    private:
        IMemDispatch* m_pMemory;
    };
}