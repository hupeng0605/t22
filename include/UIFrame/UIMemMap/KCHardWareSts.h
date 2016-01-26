/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCHardWareSts.h
* ժ    Ҫ: Ӳ��״̬����
*
* ��ǰ�汾: 1.0
* ��    ��:   
* �������: 2010-03-23
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1           2010-03-23              ����
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
    // *  ��������: Ӳ��״̬������
    // *  ��������:   
    // *  �ա�����: 2010-03-23
    //***************************************************************
    class CYPRESS_DLL_API HCHardWareSts
	{
	private:
        HCHardWareSts();
        ~HCHardWareSts();
        HCHardWareSts(const KCMemoryMap&);// ���ⲻʵ��

	public:
		static HCHardWareSts* GetInstance();
		static void ExistInstance(void);

        // ����Ӳ��״̬�������ڴ���
        HBOOL SetHardWareStatus(IN HUINT nData);
		HUINT GetHardWareStatus(void);
        // ��ȡiPod״̬
        HBOOL GetiPodStatus(void);

		// ��ȡXM״̬
		HBOOL GetXMStatus(void);
		// ��ȡSirius״̬
		HBOOL GetSiriusStatus(void);
		// ��ȡDisc״̬
		HBOOL GetDiscStatus(void);
		// ��ȡSD״̬
		HBOOL GetSDStatus(void);
		// ��ȡUSB״̬
		HBOOL GetUSBStatus(void);
		// ��ȡHDRadio״̬
		HBOOL GetHDRadioStatus(void);
		// ��ȡfront aux״̬
		HBOOL GetFrontAuxStatus(void);
		// ��ȡrear aux״̬
		HBOOL GetRearAuxStatus(void);
		// ��ȡcamera״̬
		HBOOL GetCameraStatus(void);
		// ��ȡParking status
		HBOOL GetParkingStatus(void);
		// ��ȡ����״̬
		HBOOL GetPKBStatus(void);
		// ��ȡdvbt״̬
		HBOOL  GetDVBTStatus(void);

		HINT GetHardWareStatus(HUINT nBit);

    private:
        IMemDispatch* m_pMemory;
		static HCHardWareSts* pInstance;
    };
}