/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: IMemDispatch.h
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

#include <Type.h>
#include <RenderingEngine.h>
#include "KCMemoryMap.h"

namespace KMemMap
{
    //***************************************************************
    // *  ��������: �������ڴ����ݷַ��ӿ�
    // *  ��������:  
    // *  �ա�����: 2009-12-23
    //***************************************************************
    class IMemDispatch
    {
    private:
        IMemDispatch(const IMemDispatch&);// ���ⲻʵ��
    public:
        IMemDispatch(IN const HString& name)
        {
            m_pMemMap = new KCMemoryMap(name);
        }
        virtual ~IMemDispatch()
        {
            SAFE_DELETE(m_pMemMap);
        }
        // ��������
        HBOOL SetData(const MEMMAP_DATA& memData)
		{
			return m_pMemMap->SetMemData(memData);
		}
        // �������ݣ����ļ��У�
        HBOOL SetDataFromFile(const HString& /*filePath*/)
		{
			return false;
		};
        //  ��ȡ����
        virtual void* GetData() = 0;

    protected:
        KCMemoryMap* m_pMemMap; // �������ڴ�
    };
}