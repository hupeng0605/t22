/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCAppTheme.h
* ժ    Ҫ: ��������࣬ʹ�ù����ڴ����Ӧ�ó�������
*
* ��ǰ�汾: 1.0
* ��    ��:  
* �������: 2009-11-17
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1                   2009-11-17             ����
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
    // *  ��������: ���������
    // *  ��������:  
    // *  �ա�����: 2009-12-23
    //***************************************************************
    class CYPRESS_DLL_API HCAppTheme
    {
    private:
        HCAppTheme(IN HBOOL isClient);
        ~HCAppTheme();
        HCAppTheme(const HCAppTheme&);// ���ⲻʵ��

    public:
        static HCAppTheme* GetInstance(IN HBOOL isClient);
		static void ExitInstance(void);

        // ����˼������⣬ע�⣺�ͻ��˽�ֹ���ô˺����������⵽�����ڴ�������0~255��
        HBOOL LoadTheme(IN HBYTE themeID);
        // �ͻ��˻����˻�ȡ��ǰ�����Surface
        IReSurface* GetSurface();

    private:
        IMemDispatch * m_pMemory; // �������ڴ�
        HBOOL m_bIsClient;
		static HCAppTheme* m_pClientInstance;
		static HCAppTheme* m_pServerInstance;
    };
}