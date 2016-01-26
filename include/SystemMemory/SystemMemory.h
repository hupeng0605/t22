

#ifndef FT_MID_LASTMEMORY_H
#define FT_MID_LASTMEMORY_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) ||  defined(_WIN32_WCE) || defined(WINCE)
#	ifdef SYSTEMMEMORY_EXPORT
#		define SYSTEMMEMORY_API	__declspec(dllexport)
#	else
#		define SYSTEMMEMORY_API	__declspec(dllimport)
#	endif
#else
#	ifdef SYSTEMMEMORY_EXPORT
#		define SYSTEMMEMORY_API	
#	else
#		define SYSTEMMEMORY_API	extern
#	endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

	/* VerUp回调事件的枚举定义 */
	typedef enum
	{
		ENUM_LASTMEMORY_DATA_SUC,		/* 数据读取成功 */
		ENUM_LASTMEMORY_DATA_ERR,		/* 数据读取失败 */
		ENUM_LASTMEMORY_SUC,			/* 数据保存成功 */
		ENUM_LASTMEMORY_BUSEND_FAIL,	/* BU OFF数据保存失败*/
		ENUM_LASTMEMORY_BUQUERY_SUC,	/* BU瞬断获取数据成功 */
		ENUM_LASTMEMORY_BUQUERY_FAIL,	/* BU瞬断获取数据失败 */
		ENUM_LASTMEMORY_FAIL,			/* 数据保存失败 */
		ENUM_LASTMEMORY_SEND_OVER		/* 数据保存完成 */
	}LASTMEMORY_EVENT_ENUM;

	typedef struct
	{
		UINT8 ucId;
	}LASTMEMORY_INFO;

	/*===========================================================
	*****************      接口函数定义     *********************/

	/************************************************************
	**函数名称：SystemMemory_Send_Callback
	**函数功能：发送协议数据回调函数
	**入口参数：
	**         void * pBuff  [in]：发送的数据流
	链路层错误标志符
	类别
	data[详细]
	data[0]
	data[1]
	:
	data[n]
	**         UINT32 uLen  [in]：发送数据长度
	** 返回值 ：无
	** 说  明 ：该模块封装好数据后 调用回调函数来把数据真正的发生出去,
	**          这一发送过程将有上层HMI来发送给SEVER端 由SEVER端发送给串口
	** 作  者 ：  
	** 日  期 ：   
	*************************************************************/
	typedef BOOL (__stdcall * SystemMemory_Send_Callback)(const void * pBuff, UINT32 uLen);

	/************************************************************
	**函数名称：SystemMemory_BuOff_Send_Callback
	**函数功能：发送协议数据回调函数
	**入口参数：
	**         void * pBuff  [in]：发送的数据流
	链路层错误标志符
	类别
	data[详细]
	data[0]
	data[1]
	:
	data[n]
	**         UINT32 uLen  [in]：发送数据长度
	** 返回值 ：无
	** 说  明 ：该模块封装好数据后 调用回调函数来把数据真正的发生出去,
	**          这一发送过程将有上层HMI来发送给SEVER端 由SEVER端发送给串口
	** 作  者 ：  
	** 日  期 ：   
	*************************************************************/
	typedef BOOL (__stdcall * SystemMemory_BuOff_Send_Callback)(const void * pBuff, UINT32 uLen);

	/************************************************************
	**函数名称：FT_VerUp_Resp_Callback
	**函数功能：回应数据回调函数
	**入口参数：
	**         VERUP_EVENT_ENUM eCode  [in]：接收的详细代码
	**         void * pBuff  [in]：接收的数据流，不同的命令返回的数据格式不一样 
	**         UINT32 uLen  [in]：接收的数据长度
	** 返回值 ：无
	** 说  明 ：该回调其实是在上层调用了解析函数(ParseData)由解析后
	**          的结果来调用该回调函数给上层进行处理
	** 作  者 ：  
	** 日  期 ：   
	*************************************************************/
	typedef void (__stdcall * SystemMemory_Resp_Callback)(LASTMEMORY_EVENT_ENUM eCode, const void * pBuff, UINT32 uLen);

	/***************************************************************************
	**函数名称：SystemMemory_RegisterSend
	**函数功能：注册发送协议数据的回调函数
	**入口参数：
	**         FT_VerUp_Send_Callback pfVerUpSend  [in]：回调函数指针
	** 返回值 ：TRUE 成功，FALSE, 失败
	** 作  者 ：  
	** 日  期 ：   
	***************************************************************************/
	SYSTEMMEMORY_API BOOL SystemMemory_RegisterSend(SystemMemory_Send_Callback pfLastMemorySend);

	/***************************************************************************
	**函数名称：SystemMemory_BuOff_RegisterSend
	**函数功能：注册发送协议数据的回调函数
	**入口参数：
	**         FT_VerUp_Send_Callback pfVerUpSend  [in]：回调函数指针
	** 返回值 ：TRUE 成功，FALSE, 失败
	** 作  者 ：  
	** 日  期 ：   
	***************************************************************************/
	SYSTEMMEMORY_API BOOL SystemMemory_BuOff_RegisterSend(SystemMemory_BuOff_Send_Callback pfLastMemoryBuOffSend);

	/***************************************************************************
	**函数名称：FT_VerUp_RegisterResponse
	**函数功能：注册回应数据的回调函数
	**入口参数：
	**         FT_VerUp_Resp_Callback pfVerUpResp  [in]：回调函数指针
	** 返回值 ：TRUE 成功，FALSE, 失败
	** 作  者 ：  
	** 日  期 ：   
	***************************************************************************/
	SYSTEMMEMORY_API BOOL SystemMemory_RegisterResponse(SystemMemory_Resp_Callback pfLastMemoryResp);

	/***************************************************************************
	**函数名称：SystemMemory_ParseData
	**函数功能：解析数据
	**入口参数：
	**         const void * pBuff  [in]：将解析的数据流
	链路层错误代码
	类别
	data[详细]
	data[0]
	data[1]
	:
	data[n]
	**         UINT32 uLen  [in]：将解析数据的长度
	** 返回值 ：无
	** 作  者 ：  
	** 日  期 ：   
	***************************************************************************/
	SYSTEMMEMORY_API BOOL SystemMemory_ParseData(const void * pBuff, UINT32 uLen);

	/***************************************************************************
	**函数名称：SystemMemory_Init
	**函数功能：初始化模块
	**入口参数：
	UINT32 uLen：备份数据区长度
	** 返回值 ：BOOL TRUE 发送命令成功，FALSE 失败
	** 作  者 ：  
	** 日  期 ：   
	***************************************************************************/
	 SYSTEMMEMORY_API BOOL SystemMemory_Init(UINT8 *last_memory, UINT32 uLen);

	/***************************************************************************
	**函数名称：SystemMemory_UnInit
	**函数功能：卸载模块
	**入口参数：无
	** 返回值 ：BOOL TRUE 发送命令成功，FALSE 失败
	** 作  者 ：  
	** 日  期 ：   
	***************************************************************************/
	SYSTEMMEMORY_API BOOL SystemMemory_UnInit();

	/***************************************************************************
	**函数名称：SystemMemory_SaveData
	**函数功能：开始版本升级
	**入口参数：
				UINT32 uAddr：要保存的数据偏移量
				const void * pBuff：要保存的数据
				UINT32 uLen：要保存的数据长度
	** 返回值 ：BOOL TRUE 发送命令成功，FALSE 失败
	** 作  者 ：  
	** 日  期 ：   
	***************************************************************************/
	SYSTEMMEMORY_API BOOL SystemMemory_SaveData(const void * pBuff, UINT32 uLen, UINT8 uDataId);

	/***************************************************************************
	**函数名称：SystemMemory_BuOff_SaveData
	**函数功能：BU瞬断时保存数据
	**入口参数：
				void * pBuff：要保存的数据指针
				UINT32 uLen：要保存的数据长度
	** 返回值 ：BOOL TRUE 发送命令成功，FALSE 失败
	** 作  者 ：  
	** 日  期 ：     
	***************************************************************************/
	SYSTEMMEMORY_API BOOL SystemMemory_BuOff_SaveData(const void * pBuff1, const void *pBuff2, \
														UINT32 uLen1, UINT32 uLen2, BOOL bBuOffFlag);

	/***************************************************************************
	**函数名称：SystemMemory_QueryData
	**函数功能：开始版本升级
	**入口参数：
	UINT32 uAddr：要获取的数据偏移量
	void * pBuff：获取的数据指针
	UINT32 uLen：要获取的数据长度
	** 返回值 ：BOOL TRUE 发送命令成功，FALSE 失败
	** 作  者 ：  
	** 日  期 ：   
	***************************************************************************/
	SYSTEMMEMORY_API BOOL SystemMemory_QueryData(UINT32 uLen);

	/***************************************************************************
	**函数名称：SystemMemory_BuQueryData
	**函数功能：获取BU瞬断的数据
	**入口参数：无
	** 返回值 ：BOOL TRUE 发送命令成功，FALSE 失败
	** 作  者 ：  
	** 日  期 ：   
	***************************************************************************/
	BOOL SystemMemory_BuQueryData(void);
	

#ifdef __cplusplus
}
#endif

#endif  /* #define FT_MID_LASTMEMORY_H */