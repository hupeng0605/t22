/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCExeTheme.h
* ժ    Ҫ: ����ת��ʱ�����л���Surface�����࣬ʹ�ù����ڴ����ת��ʱ��Surface
*
* ��ǰ�汾: 1.0
* ��    ��:  
* �������: 2009-12-23
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1                   2009-12-23             ����
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
    class CYPRESS_DLL_API HCExeTheme
    {
    private:
        HCExeTheme();
        ~HCExeTheme();
    private:
        HCExeTheme(const KCMemoryMap&);// ���ⲻʵ��

    public:
		static HCExeTheme* GetInstance();
        // ���õ�ǰ��Ļ��Surface�����䱣�浽�����ڴ���
        HBOOL SetScreenSurface(IN IN IReSurface* pSurf);
        // ��ȡǰһ����Ļ��ʾ��Surface
        IReSurface* GetPreScreenSurface();
		// �ͷ���Դ
		void Release();
		
    private:
        IMemDispatch* m_pMemory;
    };
}