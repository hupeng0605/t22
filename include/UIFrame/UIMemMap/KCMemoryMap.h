/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCMemoryMap.h
* ժ    Ҫ: �����ڴ�
*
* ��ǰ�汾: 1.0
* ��    ��:  
* �������: 2009-11-18
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1                   2009-11-18             ����
*
**/

#pragma once

#include <PubHead.h>
#include "ThemeDef.h"

namespace KMemMap
{
    // KTC�ļ������ڴ�����
    typedef struct _memmap_ktc_
    {
        HLONG m_nSize;
        HBYTE* m_pData;
        void clear()
        {
            m_nSize = 0;
            m_pData = NULL;
        }
        _memmap_ktc_()
        {
            clear();
        }
    } MEMMAP_DATA;

    //***************************************************************
    // *  ��������: �ڴ�ӳ��
    // *  ��������:  
    // *  �ա�����: 2009-11-27
    //***************************************************************
    class KCMemoryMap
    {
    private:
        KCMemoryMap(const KCMemoryMap&);

    public:
        KCMemoryMap(IN const HString& memName);
        ~KCMemoryMap();

        // ���ù������ݣ����Է������Ч
        HBOOL SetMemData(IN const MEMMAP_DATA& ktcMem);
        // ��ȡ��������
        HBOOL GetMemData(OUT MEMMAP_DATA& ktcMem);

    protected:
        virtual void Disponse();// �ͷ���Դ

    private:
        HString m_strMemName;// �����ڴ�����
		HINT m_nMemSize;// �����ڴ��С
		HANDLE   m_hMapFile;// �������ݿ���
        HBYTE* m_pMapAddr;   // �������ݿ��ַ
		HANDLE m_hAccessMutex;//������
    };
}