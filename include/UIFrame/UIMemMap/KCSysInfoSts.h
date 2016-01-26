/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCSysInfoSts.h
* ժ    Ҫ: sys״̬����
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

/*

��16 λ����ͬ��ϵͳ��Ϣ���� 16 λ����״̬���������±���ʾ��
ÿ��״̬��λ

����״̬ 0x0000 0x0: �����رգ���ͼ�꣩ ��
				0x1:�����򿪵���û������ֻ�����ɫͼ�꣩ ��
				0x2:�����Ѿ�������ֻ�����ɫͼ�꣩
����״̬ 0x0001 0x0���Ǿ���״̬��
				0x1������״̬��
REG״̬  0x0002	0x0��REG ��ɫ��ʾ������REG ���ܹر�
				0x1��REG ��ɫ��ʾ������REG ���ܴ�
PTY״̬  0x0003	0x0��PTY ��ɫ��ʾ������PTY���ܹر�
				0x1��PTY ��ɫ��ʾ������PTY���ܴ�
AF״̬   0x0004	0x0��AF��ɫ��ʾ������ AF���ܹر�
				0x1��AF��ɫ��ֹ״̬������ AF�ѳɹ��������
				0x2��AF��ɫ��ʾ����˸������ AF����״̬����˸����1��
TA״̬   0x0005	0x0��TA ��ɫ��ʾ������ TA ���ܹر�
				0x1��TA ��ɫ��ʾ������ TA ���ܴ�
TP״̬   0x0006	0x0��TP��ɫ��ʾ������ TA ���ܹر�
				0x1��TP��ɫ��ʾ������ TA ���ܴ�
*/

namespace KMemMap
{
    //***************************************************************
    // *  ��������: sys״̬������
    // *  ��������:   
    // *  �ա�����: 2010-03-23
    //***************************************************************
    class CYPRESS_DLL_API HCSysInfoSts
	{
	private:
        HCSysInfoSts();
        ~HCSysInfoSts();
        HCSysInfoSts(const KCMemoryMap&);// ���ⲻʵ��

	public:
		static HCSysInfoSts* GetInstance();
		static void ExistInstance(void);

        // ����Ӳ��״̬�������ڴ���
        HBOOL SetSysInfoStatus(IN HINT nData);
		HINT GetSysInfoStatus(void);
        // ��ȡ����״̬
        HINT GetBTStatus(void);
		void SetBTStatus(HINT nVal);

		// ��ȡ����״̬
		HINT GetMutetatus(void);
		void SetMuteStatus(HINT nVal);
		// ��ȡREG״̬
		HINT GetREGStatus(void);
		void SetREGStatus(HINT nVal);
		// ��ȡPTY״̬
		HINT GetPTYStatus(void);
		void SetPTYStatus(HINT nVal);
		// ��ȡAF״̬
		HINT GetAFStatus(void);
		void SetAFStatus(HINT nVal);
		// ��ȡTA״̬
		HINT GetTAStatus(void);
		void SetTAStatus(HINT nVal);
		// ��ȡTP״̬
		HINT GetTPStatus(void);
		void SetTPStatus(HINT nVal);
		//// ��ȡfront aux״̬
		//kn_bool GetFrontAuxStatus(void);
		//// ��ȡrear aux״̬
		//kn_bool GetRearAuxStatus(void);
		//// ��ȡcamera״̬
		//kn_bool GetCameraStatus(void);
		//// ��ȡParking status
		//kn_bool GetParkingStatus(void);
		//// ��ȡ����״̬
		//kn_bool GetPKBStatus(void);

		//kn_int GetHardWareStatus(kn_int nBit);

    private:
        IMemDispatch* m_pMemory;
		static HCSysInfoSts* pInstance;
    };
}