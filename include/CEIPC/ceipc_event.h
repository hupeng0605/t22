

#ifndef __IPC_EVENT_H__
#define __IPC_EVENT_H__

#ifndef TCHAR
#	if defined(_UNICODE) || defined(UNICODE)
#		define TCHAR wchar_t
#	else
#		define TCHAR char
#	endif
#endif

/*************************************** 事件ID定义 ***************************************/

/*---------------- IPC 消息类型定义 ----------------------- 对应下面的结构体 -------------*/

// IPC内部系统消息起始ID 只做标识 无具体消息含义
#define IPC_EVENT_SYS_BEGIN	(0x0000)

// 一个进程注册了 当注册一个进程时 会广播方式给每个进程发送该消息
#define IPC_SYS_PROC_REGIST			(IPC_EVENT_SYS_BEGIN + 0x01)	// 对应数据结构 : 类型 unsigned char 大小 1 Byte  进程ID号
// 一个进程注销了 当注销一个进程时 会广播方式给每个进程发送该消息
#define IPC_SYS_PROC_UNREGIST	(IPC_EVENT_SYS_BEGIN + 0x02)	// 对应数据结构 : 类型 unsigned char 大小 1 Byte  进程ID号

// IPC内部系统消息结束ID 只做标识 无具消息件含义
#define IPC_EVENT_SYS_END	(0x00FF)

// IPC用户自定义消息
#define IPC_EVENT_USER		(0x1000)


#endif	/*__IPC_EVENT_H__*/