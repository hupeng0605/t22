/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCStatusMemory.h
* ժ    Ҫ:
*
* ��ǰ�汾: 1.0
* ��    ��:  
* �������: 2010-01-22
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1                   2010-01-22             ����
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
    class KCStatusMemory : public IMemDispatch
    {
    public:
		KCStatusMemory(IN const HString& name);
        // ��������
        //kn_bool SetData(IN const MEMMAP_DATA& memData);
        // �������ݣ����ļ��У�
        //kn_bool SetDataFromFile(IN const kn_string& /*filePath*/)
        //{
        //    return false;
        //}
        //  ��ȡ����
        void* GetData();
        
    };
}