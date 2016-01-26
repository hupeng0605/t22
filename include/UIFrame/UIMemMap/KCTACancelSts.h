/**
* Copyright (C) 2010， 
* All rights reserved.
*
* 文件名称: d:\Dev\Cypress\CypressDB\03IMPLEMENT\0301Code\Cypress\KMemMap\KCTACancelSts.h
* 摘    要:
*
* 当前版本: 1.0
* 作    者: 
* 完成日期: 2010-4-20
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1           2010-4-20             		创建
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
    // *  功　　能: Exe状态管理类
    // *  作　　者:   
    // *  日　　期: 2010-03-23
    //***************************************************************
    class CYPRESS_DLL_API HCTACancelSts
	{
	private:
        HCTACancelSts();
        ~HCTACancelSts();
        HCTACancelSts(const KCMemoryMap&);// 故意不实现

	public:
		static HCTACancelSts* GetInstance();
		static void ExitInstance();

        // 设置硬件状态到共享内存中
        HBOOL SetTACancelStatus(IN HINT nData);
        HINT GetTACancelStatus(void);

    private:
        IMemDispatch* m_pMemory;
		static HCTACancelSts* m_pInstance;
    };
}