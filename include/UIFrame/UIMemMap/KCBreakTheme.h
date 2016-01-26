/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCBreakTheme.h
* ժ    Ҫ: �жϽ���Surface�����ڴ����ݹ����磺���������ȡ��绰�������ʱ�����Surface
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

#ifndef MEMMAP_API
#error "Please include KMemMapAPI.h replace this head file, Have question to email:xiongzhens@dev.kotei.co"
#endif

namespace KMemMap
{
    //***************************************************************
    // *  ��������: ����ת��ʱ�����л���Surface������
    // *  ��������:  
    // *  �ա�����: 2009-12-23
    //***************************************************************
    class CYPRESS_DLL_API HCBreakTheme
	{
	private:
        HCBreakTheme();
        ~HCBreakTheme();
        HCBreakTheme(const KCMemoryMap&);// ���ⲻʵ��

	public:
		static HCBreakTheme* GetInstance();

        // �����ն˽����Surface�����䱣�浽�����ڴ���
        HBOOL SetBreakSurface(IN IReSurface* pSurface);
        // ��ȡ�жϽ����m_pData����
        HBYTE* GetBreakSurface(OUT HDWORD& width, OUT HDWORD& height, OUT HLONG& nSize);

    private:
        IMemDispatch* m_pMemory;
    };
}