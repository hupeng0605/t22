

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
** 函数名称    : SPCP_ComInit
** 函数功能    : 打开串口函数API
** 入口参数    : 
**				 emComID portNo     : 串口号ID
**				 UINT16 baud        : 波特率设置
**				 emParity parity    : 校验位
**				 emBits databits    : 数据长度
**				 emStopBit stopbits : 停止位
** 返回值      :  
*******************************************************************************/
SPCP_API BOOL SPCP_ComInit(eComID portNo, UINT32 baud, eParity parity, eBits databits, eStopBit stopbits);

/******************************************************************************
** 函数名称    : SPCP_ComUnInit
** 函数功能    : 关闭串口函数API
** 入口参数    : 无
** 返回值      : 无
*******************************************************************************/
SPCP_API VOID SPCP_ComUnInit(VOID);

/******************************************************************************
** 函数名称    : SPCP_ComSend
** 函数功能    : 上层发送数据函数API
** 入口参数    : 
**				 UINT8 *buf : 待发送数据流(包括类别、详细、data)
**				 UINT16 len : 待发数据长度
** 返回值      : 无
*******************************************************************************/
SPCP_API BOOL SPCP_ComSend(const UINT8 *buf, UINT16 len);

/******************************************************************************
** 函数名称    : SPCP_ComPrioritySend
** 函数功能    : 直接发送数据不进队列(用于BU 瞬断等紧急发送数据的情况)
** 入口参数    : 
**				 UINT8 *buf : 待发送数据流(包括类别、详细、data)
**				 UINT8 len :  待发数据长度最大长度 256
** 返回值      : 发送长度
*******************************************************************************/
SPCP_API BOOL SPCP_ComPrioritySend(const UINT8 *buf, UINT8 len);

/******************************************************************************
** 函数名称    : SPCP_ComDataRecv
** 函数功能    : 上层回调函数API
** 入口参数    : 
**				 UINT8 *buf : 回调数据流(包括类别、详细、data)
**				 UINT16 len : 回调数据长度
** 返回值      : 无
*******************************************************************************/
typedef VOID (__stdcall * SPCP_ComDataRecv)(const UINT8 * buf, UINT16 len);

/******************************************************************************
** 函数名称    : RegistryComRecvCallBack
** 函数功能    : 注册上层回调函数API
** 入口参数    : 回调函数函数指针
** 返回值      : 无
*******************************************************************************/
SPCP_API VOID __stdcall RegistryComRecvCallBack(SPCP_ComDataRecv pFunction);

/******************************************************************************
** 函数名称    : SPCP_HeartBeatEnable
** 函数功能    : 使能心跳
** 入口参数    : 无
** 返回值      : 无
*******************************************************************************/
SPCP_API BOOL SPCP_HeartBeatEnable(void);

/******************************************************************************
** 函数名称    : SPCP_HeartBeatDisable
** 函数功能    : 禁止心跳
** 入口参数    : 无
** 返回值      : 无
*******************************************************************************/
SPCP_API BOOL SPCP_HeartBeatDisable(void);
};

#endif