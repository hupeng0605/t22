/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称:	KCComMemory.h
* 摘    要:	
*
* 当前版本:	1.0
* 作    者:	 
* 完成日期:	2010-01-25
*
* 修改历史：
* [修改序列]	[修改日期] 		[修改者]		[修改内容]
*	1					2010-01-25    	     	创建
* 	
**/



#pragma once

#include <RenderingEngine.h>
#include "IMemDispatch.h"

namespace KMemMap
{
    //***************************************************************
    // *  功　　能: Exe程序转场内存管理类
    // *  作　　者:  
    // *  日　　期: 2009-12-23
    //***************************************************************
    class KCComMemory : public IMemDispatch
    {
    public:
        KCComMemory(IN const HString& name);
        ~KCComMemory();

        // 设置数据
		//kn_bool SetData(const MEMMAP_DATA& memData);
		// 设置数据（从文件中）
		//kn_bool SetDataFromFile(const kn_string& /*filePath*/){return false;}
        //  获取数据
		void* GetData();

    private:
        HBYTE* m_pDataArrary;// 备份Surface
    };
}