/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����:	KCComMemory.h
* ժ    Ҫ:	
*
* ��ǰ�汾:	1.0
* ��    ��:	 
* �������:	2010-01-25
*
* �޸���ʷ��
* [�޸�����]	[�޸�����] 		[�޸���]		[�޸�����]
*	1					2010-01-25    	     	����
* 	
**/



#pragma once

#include <RenderingEngine.h>
#include "IMemDispatch.h"

namespace KMemMap
{
    //***************************************************************
    // *  ��������: Exe����ת���ڴ������
    // *  ��������:  
    // *  �ա�����: 2009-12-23
    //***************************************************************
    class KCComMemory : public IMemDispatch
    {
    public:
        KCComMemory(IN const HString& name);
        ~KCComMemory();

        // ��������
		//kn_bool SetData(const MEMMAP_DATA& memData);
		// �������ݣ����ļ��У�
		//kn_bool SetDataFromFile(const kn_string& /*filePath*/){return false;}
        //  ��ȡ����
		void* GetData();

    private:
        HBYTE* m_pDataArrary;// ����Surface
    };
}