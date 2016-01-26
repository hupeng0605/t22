/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCHardWareSts.h
* 摘    要: 硬件状态管理
*
* 当前版本: 1.0
* 作    者:   
* 完成日期: 2010-03-23
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1           2010-03-23              创建
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
    // *  功　　能: 硬件状态管理类
    // *  作　　者:   
    // *  日　　期: 2010-03-23
    //***************************************************************
    class CYPRESS_DLL_API HCHardWareSts
	{
	private:
        HCHardWareSts();
        ~HCHardWareSts();
        HCHardWareSts(const KCMemoryMap&);// 故意不实现

	public:
		static HCHardWareSts* GetInstance();
		static void ExistInstance(void);

        // 设置硬件状态到共享内存中
        HBOOL SetHardWareStatus(IN HUINT nData);
		HUINT GetHardWareStatus(void);
        // 获取iPod状态
        HBOOL GetiPodStatus(void);

		// 获取XM状态
		HBOOL GetXMStatus(void);
		// 获取Sirius状态
		HBOOL GetSiriusStatus(void);
		// 获取Disc状态
		HBOOL GetDiscStatus(void);
		// 获取SD状态
		HBOOL GetSDStatus(void);
		// 获取USB状态
		HBOOL GetUSBStatus(void);
		// 获取HDRadio状态
		HBOOL GetHDRadioStatus(void);
		// 获取front aux状态
		HBOOL GetFrontAuxStatus(void);
		// 获取rear aux状态
		HBOOL GetRearAuxStatus(void);
		// 获取camera状态
		HBOOL GetCameraStatus(void);
		// 获取Parking status
		HBOOL GetParkingStatus(void);
		// 获取倒车状态
		HBOOL GetPKBStatus(void);
		// 获取dvbt状态
		HBOOL  GetDVBTStatus(void);

		HINT GetHardWareStatus(HUINT nBit);

    private:
        IMemDispatch* m_pMemory;
		static HCHardWareSts* pInstance;
    };
}