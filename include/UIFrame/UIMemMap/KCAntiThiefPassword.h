/**
* Copyright (C) 2010�� 
* All rights reserved.
*
* �ļ�����: d:\Dev\Cypress\CypressDB\03IMPLEMENT\0301Code\Cypress\KMemMap\KCAntiThiefPassword.h
* ժ    Ҫ:
*
* ��ǰ�汾: 1.0
* ��    ��: 
* �������: 2010-4-20
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1           2010-4-20             		����
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
    // *  ��������: Exe״̬������
    // *  ��������:   
    // *  �ա�����: 2010-03-23
    //***************************************************************
    class CYPRESS_DLL_API HCAntiThiefPassword
	{
	private:
        HCAntiThiefPassword();
        ~HCAntiThiefPassword();
        HCAntiThiefPassword(const KCMemoryMap&);// ���ⲻʵ��

	public:
		static HCAntiThiefPassword* GetInstance();
		static void ExitInstance();

        // ����Ӳ��״̬�������ڴ���
        HBOOL SetPassword(IN HINT nData);
        HINT GetPassword(void);

    private:
        IMemDispatch* m_pMemory;
		static HCAntiThiefPassword* m_pInstance;
    };
}