

#ifndef __IPC_USER_EVENT_H__
#define __IPC_USER_EVENT_H__

#ifndef TCHAR
#	if defined(_UNICODE) || defined(UNICODE)
#		define TCHAR wchar_t
#	else
#		define TCHAR char
#	endif
#endif

#include "ceipc_event.h"

/*************************************** 事件ID定义 ***************************************/

/*---------------- IPC 事件类型定义 ------------------------------------- 对应下面的结构体 -------------*/


// IPC用户自定义系统事件起始ID 只做标识 无具体事件含义
#define IPC_EVENT_USER_SYS_BEGIN	(IPC_EVENT_USER + 0x01)

// 开启一个进程IPC事件
#define IPC_U_SYS_START_PROCESS		(IPC_EVENT_USER_SYS_BEGIN + 0x01)	// STARTPROCESS

// 关闭一个进程IPC事件
#define IPC_U_SYS_CLOSE_PROCESS		(IPC_EVENT_USER_SYS_BEGIN + 0x02)	// NULL

// 国际化多语言切换
#define IPC_U_SYS_CHANGE_LANGUAGE	(IPC_EVENT_USER_SYS_BEGIN + 0x03)	// LANGUAGECHANGE

// 改变模式IPC事件
#define IPC_U_SYS_CHANGE_PATTERN	(IPC_EVENT_USER_SYS_BEGIN + 0x04)	// PATTERNCHANGE

//SERVER通知一个进程到后台运行
#define IPC_U_WND_TOBACK			(IPC_EVENT_USER_SYS_BEGIN + 0x10)	// TOBACKPROCESS
//SERVER通知一个进程到前台运行
#define IPC_U_WND_INITPARAM			(IPC_EVENT_USER_SYS_BEGIN + 0x11)	// BACKINITPARAM
//SERVER通知进程关闭IPC消息
#define IPC_U_WND_CLOSE_EXE			(IPC_EVENT_USER_SYS_BEGIN + 0x12)	// CLOSEEXE
//SERVER通知播放蓝牙音乐消息
#define IPC_U_PLAY_BLUETOOTH_AUDIO	(IPC_EVENT_USER_SYS_BEGIN + 0x13)	// PLAYBLUETOOTHAUDIO
// SEVRER通知各个模块关机
#define	IPC_U_SERVER_POWER_OFF		(IPC_EVENT_USER_SYS_BEGIN + 0x14)		
// SERVER通知各个模块BU OFF，需要关闭IO等耗时工作
#define	IPC_U_SERVER_BU_OFF			(IPC_EVENT_USER_SYS_BEGIN + 0x15)	
//IPC消息通知屏幕比例是4:3还是16:9
#define	IPC_U_SYS_ASPECT_RATIO_CHANGE   (IPC_EVENT_USER_SYS_BEGIN + 0x16)
//==POWER KEY MUTE IPC消息定义 add by shenjinke 2011.12.6
#define IPC_U_SYS_POWER_MUTE_CHANGE   (IPC_EVENT_USER_SYS_BEGIN + 0x17)

//SERVER通知一个进程睡眠（如：通话过程中 需要播放源暂停）
#define IPC_U_WND_SLEEP				(IPC_EVENT_USER_SYS_BEGIN + 0x18)
//SERVER通知一个进程开始工作（如：通话结束 需要播放源恢复播放）
#define IPC_U_WND_WAKEUP			(IPC_EVENT_USER_SYS_BEGIN + 0x19)

// 串口协议IPC事件
#define IPC_U_SYS_COM_PROTOCOL		(IPC_EVENT_USER_SYS_BEGIN + 0xA0)	// BUFFERTRANS

// IPC内部系统事件结束ID 只做标识 无具体事件含义
#define IPC_EVENT_USER_SYS_END	(0x00FF)


// 调试打印IPC事件
#define IPC_DEBUG_INFOR				(IPC_EVENT_USER + 0x0FFF)			// DEBUGINFOR



/*************************************** 事件参数结构体定义 ***************************************/

///////////////////////// 内部系统事件结构体 /////////////////////////

// 启动进程结构体
typedef struct tagStartProcess
{
	tagStartProcess(void) { memset(this,0,sizeof(tagStartProcess)); }
	unsigned char uIPC_ID;		// 进程 IPC ID
	TCHAR Argument[64];			// 传入参数
	unsigned char bActiveShow;	// 如果该进程已启动 是否激活显示
	unsigned char bCloseSalf;	// 如果启动进程成功是否关闭发起者的进程
}STARTPROCESS,*LPSTARTPROCESS;

// 多语言结构体
typedef struct tagLanguageChange
{
	unsigned short uLang;			// 语言类型
}LANGUAGECHANGE,*LPLANGUAGECHANGE;

// 模式结构体
typedef struct tagPatternChange
{
	tagPatternChange(void) { memset(this,0,sizeof(tagPatternChange)); }
	unsigned char uPattern;			// 切换模式类型
}PATTERNCHANGE,*LPPATTERNCHANGE;

// 数据传输结构体
typedef struct tagBufferTrans
{
	tagBufferTrans(void) { memset(this,0,sizeof(tagBufferTrans)); }
	unsigned long uSize;			// 要传输的大小
	unsigned char buff[1024];		// 最大BUFF
}BUFFERTRANS,*LPBUFFERTRANS;

// 调试打印结构体
typedef struct tagDebugInfor
{
	tagDebugInfor(void) { memset(this,0,sizeof(tagDebugInfor)); }
	TCHAR strInfor[2048];
}DEBUGINFOR,*LPDEBUGINFOR;


typedef struct tagKeyMsg
{
	WORD event;
	BYTE index;
	BYTE vary;
/*
 * FT_KEY_BTN_DOWN = 0x10,		按钮按下（变化时发送）	[BYTE] 按键序号：0~15
 * FT_KEY_BTN_UP = 0x11,		按钮释放（变化时发送）	[BYTE] 按键序号：0~15
 * FT_KEY_SPIN_DOWN = 0x12,		旋钮反转	[BYTE] 旋钮序号：0~1
 * FT_KEY_SPIN_UP = 0x13		旋钮正转	[BYTE] 旋钮序号：0~1
 */
} KEYMSG, *LPKEYMSG;

//server显示叠加层共享内存头的结构
typedef struct _tagShowOverlay
{
	int dst_x;
	int dst_y;
	int copy_width;
	int copy_height;
	int src_width_byte;
	int src_height;
	BOOL bUseColorKey;
	DWORD dwColorKey;
}ShowOverlay;
#endif	/*__IPC_USER_EVENT_H__*/