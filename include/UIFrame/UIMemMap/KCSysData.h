/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCSysData.h
* 摘    要: 系统设置数据管理类，使用共享内存管理数据
*
* 当前版本: 1.0
* 作    者:  
* 完成日期: 2010-01-20
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1                   2010-01-20             创建
*
**/


#pragma once

#include <Type.h>
#include <RenderingEngine.h>
#include "IMemDispatch.h"

#ifndef MEMMAP_API
#error "Please include KMemMapAPI.h replace this head file, Have question to email:xiongzhens@dev.kotei.co"
#endif

namespace KMemMap
{
    // 系统设置数据
    typedef struct _sys_setting_
    { 
		HBYTE m_nThemeID;				// 主题ID：范围0~255
        HBYTE m_nLangID;				// 言语ID：范围0~255
	//	kn_byte m_nVedioShowratioID;	// 视频显示比例		
#ifdef	__VIOLET
        HBYTE m_n24Timer;// 0:12小时制；1：24小时制
        HBYTE m_nDigitTimer;// 1：数字时钟；0:模拟时钟
        HBYTE m_nCarType;// 车型ID：范围0~255
#endif
        void clear()
        {
			m_nThemeID = 0;
			m_nLangID = 0;
#ifdef	__VIOLET
            m_n24Timer = 1;
            m_nDigitTimer = 0;
			m_nCarType = 0;
#endif
        }
        _sys_setting_()
        {
            clear();
        }
        _sys_setting_& operator=(const _sys_setting_& other)
        {
			m_nThemeID = other.m_nThemeID;
			m_nLangID = other.m_nLangID;
#ifdef	__VIOLET
            m_n24Timer = other.m_n24Timer;
            m_nDigitTimer = other.m_nDigitTimer;
			m_nCarType = other.m_nCarType;
#endif
            return *this;
        }
    } SYS_SETTING;

    //***************************************************************
    // *  功　　能: 系统设置数据管理类，使用共享内存管理数据
    // *  作　　者:  
    // *  日　　期: 2009-12-23
    //***************************************************************
    class CYPRESS_DLL_API HCSysData
    {
    private:
        HCSysData();
        ~HCSysData();
        HCSysData(const HCSysData&);// 故意不实现

    public:
        //
        static HCSysData* GetInstance();
		static void ExitInstance();
        // 设置系统设置数据
        HBOOL SetSysSetting(IN const SYS_SETTING& sysSetting);
        // 获取系统设置数据
        HBOOL GetSysSetting(OUT SYS_SETTING& sysSetting);

    private:
        IMemDispatch* m_pMemory; // 管理共享内存
		static HCSysData* m_pInstance;
    };
}
