/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCSysData.h
* ժ    Ҫ: ϵͳ�������ݹ����࣬ʹ�ù����ڴ��������
*
* ��ǰ�汾: 1.0
* ��    ��:  
* �������: 2010-01-20
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1                   2010-01-20             ����
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
    // ϵͳ��������
    typedef struct _sys_setting_
    { 
		HBYTE m_nThemeID;				// ����ID����Χ0~255
        HBYTE m_nLangID;				// ����ID����Χ0~255
	//	kn_byte m_nVedioShowratioID;	// ��Ƶ��ʾ����		
#ifdef	__VIOLET
        HBYTE m_n24Timer;// 0:12Сʱ�ƣ�1��24Сʱ��
        HBYTE m_nDigitTimer;// 1������ʱ�ӣ�0:ģ��ʱ��
        HBYTE m_nCarType;// ����ID����Χ0~255
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
    // *  ��������: ϵͳ�������ݹ����࣬ʹ�ù����ڴ��������
    // *  ��������:  
    // *  �ա�����: 2009-12-23
    //***************************************************************
    class CYPRESS_DLL_API HCSysData
    {
    private:
        HCSysData();
        ~HCSysData();
        HCSysData(const HCSysData&);// ���ⲻʵ��

    public:
        //
        static HCSysData* GetInstance();
		static void ExitInstance();
        // ����ϵͳ��������
        HBOOL SetSysSetting(IN const SYS_SETTING& sysSetting);
        // ��ȡϵͳ��������
        HBOOL GetSysSetting(OUT SYS_SETTING& sysSetting);

    private:
        IMemDispatch* m_pMemory; // �������ڴ�
		static HCSysData* m_pInstance;
    };
}
