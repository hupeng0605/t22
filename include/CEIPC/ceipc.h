

#ifndef __CEIPC_H__
#define __CEIPC_H__

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) ||  defined(_WIN32_WCE) || defined(WINCE)
#	ifdef CEIPC_EXPROT
#		define CEIPC_API	__declspec(dllexport)
#	else
#		define CEIPC_API	__declspec(dllimport)
#	endif
#else
#	ifdef CEIPC_EXPROT
#		define CEIPC_API	
#	else
#		define CEIPC_API	extern
#	endif
#endif

#include "ceipc_event.h"

#ifdef __cplusplus
extern "C" {
	namespace CEIPC {
#endif

		/*************************************** ���Ͷ��� ***************************************/

		///////////////////////// �ṹ���� /////////////////////////

		// IPC �¼��ṹ��
		typedef struct tagIPCEvent
		{
			unsigned short uIPCEvent;		// �¼�����ID
			unsigned long uSize;			// ���ݳ���
			unsigned char * pData;			// ����
		}IPCEVENT,*LPIPCEVENT;

		///////////////////////// �������� /////////////////////////

		// ����IPC��Ϣ�ص�����
#ifndef RECV_IPC_EVENT

		// Description     : ����IPC��Ϣ�ص�����
		// Return type     : void 
		// Argument        : __in unsigned char uSendID			������ID
		// Argument        : __in unsigned short uIPCEvent		���յ�IPC��Ϣ����
		// Argument        : __in unsigned long uSize			���յ����ݳ���
		// Argument        : __in const unsigned char * pData	���յ�����
		// Remark          : 

		typedef void (__stdcall *RECV_IPC_EVENT)(__in unsigned char uSendID,__in unsigned short uIPCEvent,__in unsigned long uSize,__in const unsigned char * pData);
#endif

		/*************************************** �������� ***************************************/

		// Function name   : CEIPC_SetMemSize
		// Description     : ����IPCͨѶ�ɴ�����ݵ��ڴ��С
		// Return type     : void 
		// Argument        : __in unsigned long uSize	// �����ڴ��С
		// 
		// Remark          : ��ע�����(IPC_Regist)֮ǰ���ò���Ч ֻ��Ҫ���������Ľ��̵���һ�μ��� ͨ���ɷ���˳������ �����ý�����Ĭ��ֵ����ʼ�� ( Ĭ��ֵ: 10 KByte )

		CEIPC_API void CEIPC_SetMemSize(__in unsigned long uSize);


		// Function name   : CEIPC_Regist
		// Description     : ע��IPC���� ����ʼ��
		// Return type     : short ( 0 : �ɹ�, !0 : ʧ�� ˵�� [ 1 : ��ʾ��Ч����ID, 2 : �����ڴ�ط���ʧ��, 3 : ��ʾ�ý����Ѵ���, 4 : ��ʾע��Ľ�������������ע��, 5 : ��ʾ��ʼ��ʧ�� ] )
		// Argument        : __in unsigned char uID			// �Զ������ID ( ��� ID Ϊ 0 ��ʾ ��Ч����ID ����ע���ID���� > 0 )
		// Argument        : __in HWND hWnd					// �ý��̵������� APP_WIN
		// Argument        : __in RECV_IPC_EVENT pFunction	// ����IPC��Ϣ�Ļص�
		// 
		// Remark          : ע��IPC���̳ɹ��� ��㲥һ���и�����ע���˸�������������ע��Ľ���

		CEIPC_API short CEIPC_Regist(__in unsigned char uID,__in HWND hWnd,__in RECV_IPC_EVENT pFunction);


		// Function name   : CEIPC_UnRegist
		// Description     : ע��IPC���� ���ͷ���Դ
		// Return type     : short ( true : �ɹ� false : ʧ�� )
		// Argument        : void
		// 
		// Remark          : ע��IPC���̺� ��㲥һ���и�����ע���˸�������������ע��Ľ���

		CEIPC_API bool CEIPC_UnRegist(void);


		// Function name   : CEIPC_IsExist
		// Description     : �жϽ����Ƿ����
		// Return type     : bool ( true : �ɹ� false : ʧ�� ֻ��δע��ʱ�Żᷴע��ʧ�� )
		// Argument        : __in unsigned char uID			// �Զ������ID
		// 
		// Remark          : 

		CEIPC_API bool CEIPC_IsExist(__in unsigned char uID);


		// Function name   : CEIPC_GetHWND
		// Description     : �õ�ĳһ���̵�������
		// Return type     : HWND ( ������ )
		// Argument        : __in unsigned char uID			// �Զ������ID
		// 
		// Remark          : 

		CEIPC_API HWND CEIPC_GetHWND(__in unsigned char uID);


		// Function name   : CEIPC_SetHWND
		// Description     : ���õ�ǰ���̵�������
		// Return type     : bool ( true : �ɹ� false : ʧ�� )
		// Argument        : __in HWND hWnd					// ������ 
		// 
		// Remark          : �������е������巢�͸ı�ʱ���øú���

		CEIPC_API bool CEIPC_SetHWND(__in HWND hWnd);


		// Function name   : CEIPC_SendEvent
		// Description     : ������ĳ�����̷���IPC��Ϣ
		// Return type     : bool ( true : �ɹ� false : ʧ��)
		// Argument        : __in unsigned char uID			// �Զ������ID
		// Argument        : __in LPIPCEVENT lpIPCEvent		// IPC��Ϣ�ṹ��
		// Remark          : 

		CEIPC_API bool CEIPC_SendEvent(__in unsigned char uID,__in LPIPCEVENT lpIPCEvent);


		// Function name   : CEIPC_BroadcastEvent
		// Description     : �㲥��ʽ�����Լ���������н��̷���IPC��Ϣ
		// Return type     : bool ( true : �ɹ� false : ʧ�� )
		// Argument        : __in LPIPCEVENT lpIPCEvent		// IPC��Ϣ�ṹ��
		// Remark          : 

		CEIPC_API bool CEIPC_BroadcastEvent(__in LPIPCEVENT lpIPCEvent);

#ifdef __cplusplus
	}
}
#endif

#endif	/*__IPC_H__*/