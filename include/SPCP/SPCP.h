

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "SPCP_DEF.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) ||  defined(_WIN32_WCE) || defined(WINCE)
#	ifdef __COM_PROTOCOL_EXPROT__
#		define SPCP_API	__declspec(dllexport)
#	else
#		define SPCP_API	__declspec(dllimport)
#	endif
#else
#	ifdef __COM_PROTOCOL_EXPROT__
#		define SPCP_API	
#	else
#		define SPCP_API	extern
#	endif
#endif


extern "C"
{
/******************************************************************************
** ��������    : SPCP_ComInit
** ��������    : �򿪴��ں���API
** ��ڲ���    : 
**				 emComID portNo     : ���ں�ID
**				 UINT16 baud        : ����������
**				 emParity parity    : У��λ
**				 emBits databits    : ���ݳ���
**				 emStopBit stopbits : ֹͣλ
** ����ֵ      :  
*******************************************************************************/
SPCP_API BOOL SPCP_ComInit(eComID portNo, UINT32 baud, eParity parity, eBits databits, eStopBit stopbits);

/******************************************************************************
** ��������    : SPCP_ComUnInit
** ��������    : �رմ��ں���API
** ��ڲ���    : ��
** ����ֵ      : ��
*******************************************************************************/
SPCP_API VOID SPCP_ComUnInit(VOID);

/******************************************************************************
** ��������    : SPCP_ComSend
** ��������    : �ϲ㷢�����ݺ���API
** ��ڲ���    : 
**				 UINT8 *buf : ������������(���������ϸ��data)
**				 UINT16 len : �������ݳ���
** ����ֵ      : ��
*******************************************************************************/
SPCP_API BOOL SPCP_ComSend(const UINT8 *buf, UINT16 len);

/******************************************************************************
** ��������    : SPCP_ComPrioritySend
** ��������    : ֱ�ӷ������ݲ�������(����BU ˲�ϵȽ����������ݵ����)
** ��ڲ���    : 
**				 UINT8 *buf : ������������(���������ϸ��data)
**				 UINT8 len :  �������ݳ�����󳤶� 256
** ����ֵ      : ���ͳ���
*******************************************************************************/
SPCP_API BOOL SPCP_ComPrioritySend(const UINT8 *buf, UINT8 len);

/******************************************************************************
** ��������    : SPCP_ComDataRecv
** ��������    : �ϲ�ص�����API
** ��ڲ���    : 
**				 UINT8 *buf : �ص�������(���������ϸ��data)
**				 UINT16 len : �ص����ݳ���
** ����ֵ      : ��
*******************************************************************************/
typedef VOID (__stdcall * SPCP_ComDataRecv)(const UINT8 * buf, UINT16 len);

/******************************************************************************
** ��������    : RegistryComRecvCallBack
** ��������    : ע���ϲ�ص�����API
** ��ڲ���    : �ص���������ָ��
** ����ֵ      : ��
*******************************************************************************/
SPCP_API VOID __stdcall RegistryComRecvCallBack(SPCP_ComDataRecv pFunction);

/******************************************************************************
** ��������    : SPCP_HeartBeatEnable
** ��������    : ʹ������
** ��ڲ���    : ��
** ����ֵ      : ��
*******************************************************************************/
SPCP_API BOOL SPCP_HeartBeatEnable(void);

/******************************************************************************
** ��������    : SPCP_HeartBeatDisable
** ��������    : ��ֹ����
** ��ڲ���    : ��
** ����ֵ      : ��
*******************************************************************************/
SPCP_API BOOL SPCP_HeartBeatDisable(void);
};

#endif