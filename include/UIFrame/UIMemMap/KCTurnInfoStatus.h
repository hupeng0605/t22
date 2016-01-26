/**
* Copyright (C) 2010�� 
* All rights reserved.
*
* �ļ�����: d:\Dev\Cypress\CypressDB\03IMPLEMENT\0301Code\Cypress\KMemMap\KCTurnInfoStatus.h
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
    class CYPRESS_DLL_API HCTurnInfoStatus
	{
	private:
        HCTurnInfoStatus();
        ~HCTurnInfoStatus();
        HCTurnInfoStatus(const KCMemoryMap&);// ���ⲻʵ��

	public:
		static HCTurnInfoStatus* GetInstance();
		static void ExitInstance();

        // ����Ӳ��״̬�������ڴ���
        HBOOL SetTurnInfoStatus(IN HINT nData);
        HINT GetTurnInfoStatus(void);

    private:
        IMemDispatch* m_pMemory;
		static HCTurnInfoStatus* m_pInstance;
    };
}