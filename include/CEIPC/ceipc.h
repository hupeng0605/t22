

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

		/*************************************** 类型定义 ***************************************/

		///////////////////////// 结构类型 /////////////////////////

		// IPC 事件结构体
		typedef struct tagIPCEvent
		{
			unsigned short uIPCEvent;		// 事件类型ID
			unsigned long uSize;			// 数据长度
			unsigned char * pData;			// 数据
		}IPCEVENT,*LPIPCEVENT;

		///////////////////////// 函数类型 /////////////////////////

		// 接收IPC消息回调函数
#ifndef RECV_IPC_EVENT

		// Description     : 接收IPC消息回调函数
		// Return type     : void 
		// Argument        : __in unsigned char uSendID			发送者ID
		// Argument        : __in unsigned short uIPCEvent		接收的IPC消息类型
		// Argument        : __in unsigned long uSize			接收的数据长度
		// Argument        : __in const unsigned char * pData	接收的数据
		// Remark          : 

		typedef void (__stdcall *RECV_IPC_EVENT)(__in unsigned char uSendID,__in unsigned short uIPCEvent,__in unsigned long uSize,__in const unsigned char * pData);
#endif

		/*************************************** 函数定义 ***************************************/

		// Function name   : CEIPC_SetMemSize
		// Description     : 设置IPC通讯可存放数据的内存大小
		// Return type     : void 
		// Argument        : __in unsigned long uSize	// 共享内存大小
		// 
		// Remark          : 在注册进程(IPC_Regist)之前调用才生效 只需要最先启动的进程调用一次即可 通常由服务端程序调用 不调用将启用默认值来初始化 ( 默认值: 10 KByte )

		CEIPC_API void CEIPC_SetMemSize(__in unsigned long uSize);


		// Function name   : CEIPC_Regist
		// Description     : 注册IPC进程 并初始化
		// Return type     : short ( 0 : 成功, !0 : 失败 说明 [ 1 : 表示无效进程ID, 2 : 共享内存池分配失败, 3 : 表示该进程已存在, 4 : 表示注册的进程已满不能再注册, 5 : 表示初始化失败 ] )
		// Argument        : __in unsigned char uID			// 自定义进程ID ( 如果 ID 为 0 表示 无效进程ID 所有注册的ID必须 > 0 )
		// Argument        : __in HWND hWnd					// 该进程的主窗体 APP_WIN
		// Argument        : __in RECV_IPC_EVENT pFunction	// 接收IPC消息的回调
		// 
		// Remark          : 注册IPC进程成功后 会广播一次有个进程注册了告诉其他所有已注册的进程

		CEIPC_API short CEIPC_Regist(__in unsigned char uID,__in HWND hWnd,__in RECV_IPC_EVENT pFunction);


		// Function name   : CEIPC_UnRegist
		// Description     : 注销IPC进程 并释放资源
		// Return type     : short ( true : 成功 false : 失败 )
		// Argument        : void
		// 
		// Remark          : 注销IPC进程后 会广播一次有个进程注销了告诉其他所有已注册的进程

		CEIPC_API bool CEIPC_UnRegist(void);


		// Function name   : CEIPC_IsExist
		// Description     : 判断进程是否存在
		// Return type     : bool ( true : 成功 false : 失败 只有未注册时才会反注册失败 )
		// Argument        : __in unsigned char uID			// 自定义进程ID
		// 
		// Remark          : 

		CEIPC_API bool CEIPC_IsExist(__in unsigned char uID);


		// Function name   : CEIPC_GetHWND
		// Description     : 得到某一进程的主窗体
		// Return type     : HWND ( 窗体句柄 )
		// Argument        : __in unsigned char uID			// 自定义进程ID
		// 
		// Remark          : 

		CEIPC_API HWND CEIPC_GetHWND(__in unsigned char uID);


		// Function name   : CEIPC_SetHWND
		// Description     : 设置当前进程的主窗体
		// Return type     : bool ( true : 成功 false : 失败 )
		// Argument        : __in HWND hWnd					// 窗体句柄 
		// 
		// Remark          : 当进程中的主窗体发送改变时调用该函数

		CEIPC_API bool CEIPC_SetHWND(__in HWND hWnd);


		// Function name   : CEIPC_SendEvent
		// Description     : 单独给某个进程发送IPC消息
		// Return type     : bool ( true : 成功 false : 失败)
		// Argument        : __in unsigned char uID			// 自定义进程ID
		// Argument        : __in LPIPCEVENT lpIPCEvent		// IPC消息结构体
		// Remark          : 

		CEIPC_API bool CEIPC_SendEvent(__in unsigned char uID,__in LPIPCEVENT lpIPCEvent);


		// Function name   : CEIPC_BroadcastEvent
		// Description     : 广播方式给除自己以外的所有进程发送IPC消息
		// Return type     : bool ( true : 成功 false : 失败 )
		// Argument        : __in LPIPCEVENT lpIPCEvent		// IPC消息结构体
		// Remark          : 

		CEIPC_API bool CEIPC_BroadcastEvent(__in LPIPCEVENT lpIPCEvent);

#ifdef __cplusplus
	}
}
#endif

#endif	/*__IPC_H__*/