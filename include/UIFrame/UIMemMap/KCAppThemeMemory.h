/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCAppThemeMemory.h
* ժ    Ҫ:
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

namespace KMemMap
{
    //***************************************************************
    // *  ��������: ���⹲���ڴ������
    // *  ��������:  
    // *  �ա�����: 2009-12-23
    //***************************************************************
    class KCAppThemeMemory : public IMemDispatch
    {
    public:
        KCAppThemeMemory(IN const HString& name);
        ~KCAppThemeMemory();
        // ��������
        HBOOL SetData(const MEMMAP_DATA& /*memData*/)
        {
            return false;
        }
        // �������ݣ����ļ��У�
        HBOOL SetDataFromFile(const HString& filePath);
        //  ��ȡ����
        void* GetData();
	private:
	IReSurface* m_pBakSurface;
    };
}