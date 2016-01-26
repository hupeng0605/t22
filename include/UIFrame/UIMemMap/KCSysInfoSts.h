/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCSysInfoSts.h
* 摘    要: sys状态管理
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

/*

高16 位代表不同的系统信息，低 16 位代表状态。具体如下表所示：
每个状态两位

蓝牙状态 0x0000 0x0: 蓝牙关闭（无图标） ；
				0x1:蓝牙打开但是没有配对手机（灰色图标） ；
				0x2:蓝牙已经配对上手机（蓝色图标）
静音状态 0x0001 0x0：非静音状态；
				0x1：静音状态；
REG状态  0x0002	0x0：REG 灰色显示，代表REG 功能关闭
				0x1：REG 彩色显示，代表REG 功能打开
PTY状态  0x0003	0x0：PTY 灰色显示，代表PTY功能关闭
				0x1：PTY 彩色显示，代表PTY功能打开
AF状态   0x0004	0x0：AF灰色显示，代表 AF功能关闭
				0x1：AF彩色静止状态，代表 AF已成功搜索完成
				0x2：AF彩色显示并闪烁，代表 AF搜索状态。闪烁周期1秒
TA状态   0x0005	0x0：TA 灰色显示，代表 TA 功能关闭
				0x1：TA 彩色显示，代表 TA 功能打开
TP状态   0x0006	0x0：TP灰色显示，代表 TA 功能关闭
				0x1：TP彩色显示，代表 TA 功能打开
*/

namespace KMemMap
{
    //***************************************************************
    // *  功　　能: sys状态管理类
    // *  作　　者:   
    // *  日　　期: 2010-03-23
    //***************************************************************
    class CYPRESS_DLL_API HCSysInfoSts
	{
	private:
        HCSysInfoSts();
        ~HCSysInfoSts();
        HCSysInfoSts(const KCMemoryMap&);// 故意不实现

	public:
		static HCSysInfoSts* GetInstance();
		static void ExistInstance(void);

        // 设置硬件状态到共享内存中
        HBOOL SetSysInfoStatus(IN HINT nData);
		HINT GetSysInfoStatus(void);
        // 获取蓝牙状态
        HINT GetBTStatus(void);
		void SetBTStatus(HINT nVal);

		// 获取静音状态
		HINT GetMutetatus(void);
		void SetMuteStatus(HINT nVal);
		// 获取REG状态
		HINT GetREGStatus(void);
		void SetREGStatus(HINT nVal);
		// 获取PTY状态
		HINT GetPTYStatus(void);
		void SetPTYStatus(HINT nVal);
		// 获取AF状态
		HINT GetAFStatus(void);
		void SetAFStatus(HINT nVal);
		// 获取TA状态
		HINT GetTAStatus(void);
		void SetTAStatus(HINT nVal);
		// 获取TP状态
		HINT GetTPStatus(void);
		void SetTPStatus(HINT nVal);
		//// 获取front aux状态
		//kn_bool GetFrontAuxStatus(void);
		//// 获取rear aux状态
		//kn_bool GetRearAuxStatus(void);
		//// 获取camera状态
		//kn_bool GetCameraStatus(void);
		//// 获取Parking status
		//kn_bool GetParkingStatus(void);
		//// 获取倒车状态
		//kn_bool GetPKBStatus(void);

		//kn_int GetHardWareStatus(kn_int nBit);

    private:
        IMemDispatch* m_pMemory;
		static HCSysInfoSts* pInstance;
    };
}