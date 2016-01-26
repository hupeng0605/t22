

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

	/* VerUp�ص��¼���ö�ٶ��� */
	typedef enum
	{
		ENUM_LASTMEMORY_DATA_SUC,		/* ���ݶ�ȡ�ɹ� */
		ENUM_LASTMEMORY_DATA_ERR,		/* ���ݶ�ȡʧ�� */
		ENUM_LASTMEMORY_SUC,			/* ���ݱ���ɹ� */
		ENUM_LASTMEMORY_BUSEND_FAIL,	/* BU OFF���ݱ���ʧ��*/
		ENUM_LASTMEMORY_BUQUERY_SUC,	/* BU˲�ϻ�ȡ���ݳɹ� */
		ENUM_LASTMEMORY_BUQUERY_FAIL,	/* BU˲�ϻ�ȡ����ʧ�� */
		ENUM_LASTMEMORY_FAIL,			/* ���ݱ���ʧ�� */
		ENUM_LASTMEMORY_SEND_OVER		/* ���ݱ������ */
	}LASTMEMORY_EVENT_ENUM;

	typedef struct
	{
		UINT8 ucId;
	}LASTMEMORY_INFO;

	/*===========================================================
	*****************      �ӿں�������     *********************/

	/************************************************************
	**�������ƣ�SystemMemory_Send_Callback
	**�������ܣ�����Э�����ݻص�����
	**��ڲ�����
	**         void * pBuff  [in]�����͵�������
	��·������־��
	���
	data[��ϸ]
	data[0]
	data[1]
	:
	data[n]
	**         UINT32 uLen  [in]���������ݳ���
	** ����ֵ ����
	** ˵  �� ����ģ���װ�����ݺ� ���ûص������������������ķ�����ȥ,
	**          ��һ���͹��̽����ϲ�HMI�����͸�SEVER�� ��SEVER�˷��͸�����
	** ��  �� ��  
	** ��  �� ��   
	*************************************************************/
	typedef BOOL (__stdcall * SystemMemory_Send_Callback)(const void * pBuff, UINT32 uLen);

	/************************************************************
	**�������ƣ�SystemMemory_BuOff_Send_Callback
	**�������ܣ�����Э�����ݻص�����
	**��ڲ�����
	**         void * pBuff  [in]�����͵�������
	��·������־��
	���
	data[��ϸ]
	data[0]
	data[1]
	:
	data[n]
	**         UINT32 uLen  [in]���������ݳ���
	** ����ֵ ����
	** ˵  �� ����ģ���װ�����ݺ� ���ûص������������������ķ�����ȥ,
	**          ��һ���͹��̽����ϲ�HMI�����͸�SEVER�� ��SEVER�˷��͸�����
	** ��  �� ��  
	** ��  �� ��   
	*************************************************************/
	typedef BOOL (__stdcall * SystemMemory_BuOff_Send_Callback)(const void * pBuff, UINT32 uLen);

	/************************************************************
	**�������ƣ�FT_VerUp_Resp_Callback
	**�������ܣ���Ӧ���ݻص�����
	**��ڲ�����
	**         VERUP_EVENT_ENUM eCode  [in]�����յ���ϸ����
	**         void * pBuff  [in]�����յ�����������ͬ������ص����ݸ�ʽ��һ�� 
	**         UINT32 uLen  [in]�����յ����ݳ���
	** ����ֵ ����
	** ˵  �� ���ûص���ʵ�����ϲ�����˽�������(ParseData)�ɽ�����
	**          �Ľ�������øûص��������ϲ���д���
	** ��  �� ��  
	** ��  �� ��   
	*************************************************************/
	typedef void (__stdcall * SystemMemory_Resp_Callback)(LASTMEMORY_EVENT_ENUM eCode, const void * pBuff, UINT32 uLen);

	/***************************************************************************
	**�������ƣ�SystemMemory_RegisterSend
	**�������ܣ�ע�ᷢ��Э�����ݵĻص�����
	**��ڲ�����
	**         FT_VerUp_Send_Callback pfVerUpSend  [in]���ص�����ָ��
	** ����ֵ ��TRUE �ɹ���FALSE, ʧ��
	** ��  �� ��  
	** ��  �� ��   
	***************************************************************************/
	SYSTEMMEMORY_API BOOL SystemMemory_RegisterSend(SystemMemory_Send_Callback pfLastMemorySend);

	/***************************************************************************
	**�������ƣ�SystemMemory_BuOff_RegisterSend
	**�������ܣ�ע�ᷢ��Э�����ݵĻص�����
	**��ڲ�����
	**         FT_VerUp_Send_Callback pfVerUpSend  [in]���ص�����ָ��
	** ����ֵ ��TRUE �ɹ���FALSE, ʧ��
	** ��  �� ��  
	** ��  �� ��   
	***************************************************************************/
	SYSTEMMEMORY_API BOOL SystemMemory_BuOff_RegisterSend(SystemMemory_BuOff_Send_Callback pfLastMemoryBuOffSend);

	/***************************************************************************
	**�������ƣ�FT_VerUp_RegisterResponse
	**�������ܣ�ע���Ӧ���ݵĻص�����
	**��ڲ�����
	**         FT_VerUp_Resp_Callback pfVerUpResp  [in]���ص�����ָ��
	** ����ֵ ��TRUE �ɹ���FALSE, ʧ��
	** ��  �� ��  
	** ��  �� ��   
	***************************************************************************/
	SYSTEMMEMORY_API BOOL SystemMemory_RegisterResponse(SystemMemory_Resp_Callback pfLastMemoryResp);

	/***************************************************************************
	**�������ƣ�SystemMemory_ParseData
	**�������ܣ���������
	**��ڲ�����
	**         const void * pBuff  [in]����������������
	��·��������
	���
	data[��ϸ]
	data[0]
	data[1]
	:
	data[n]
	**         UINT32 uLen  [in]�����������ݵĳ���
	** ����ֵ ����
	** ��  �� ��  
	** ��  �� ��   
	***************************************************************************/
	SYSTEMMEMORY_API BOOL SystemMemory_ParseData(const void * pBuff, UINT32 uLen);

	/***************************************************************************
	**�������ƣ�SystemMemory_Init
	**�������ܣ���ʼ��ģ��
	**��ڲ�����
	UINT32 uLen����������������
	** ����ֵ ��BOOL TRUE ��������ɹ���FALSE ʧ��
	** ��  �� ��  
	** ��  �� ��   
	***************************************************************************/
	 SYSTEMMEMORY_API BOOL SystemMemory_Init(UINT8 *last_memory, UINT32 uLen);

	/***************************************************************************
	**�������ƣ�SystemMemory_UnInit
	**�������ܣ�ж��ģ��
	**��ڲ�������
	** ����ֵ ��BOOL TRUE ��������ɹ���FALSE ʧ��
	** ��  �� ��  
	** ��  �� ��   
	***************************************************************************/
	SYSTEMMEMORY_API BOOL SystemMemory_UnInit();

	/***************************************************************************
	**�������ƣ�SystemMemory_SaveData
	**�������ܣ���ʼ�汾����
	**��ڲ�����
				UINT32 uAddr��Ҫ���������ƫ����
				const void * pBuff��Ҫ���������
				UINT32 uLen��Ҫ��������ݳ���
	** ����ֵ ��BOOL TRUE ��������ɹ���FALSE ʧ��
	** ��  �� ��  
	** ��  �� ��   
	***************************************************************************/
	SYSTEMMEMORY_API BOOL SystemMemory_SaveData(const void * pBuff, UINT32 uLen, UINT8 uDataId);

	/***************************************************************************
	**�������ƣ�SystemMemory_BuOff_SaveData
	**�������ܣ�BU˲��ʱ��������
	**��ڲ�����
				void * pBuff��Ҫ���������ָ��
				UINT32 uLen��Ҫ��������ݳ���
	** ����ֵ ��BOOL TRUE ��������ɹ���FALSE ʧ��
	** ��  �� ��  
	** ��  �� ��     
	***************************************************************************/
	SYSTEMMEMORY_API BOOL SystemMemory_BuOff_SaveData(const void * pBuff1, const void *pBuff2, \
														UINT32 uLen1, UINT32 uLen2, BOOL bBuOffFlag);

	/***************************************************************************
	**�������ƣ�SystemMemory_QueryData
	**�������ܣ���ʼ�汾����
	**��ڲ�����
	UINT32 uAddr��Ҫ��ȡ������ƫ����
	void * pBuff����ȡ������ָ��
	UINT32 uLen��Ҫ��ȡ�����ݳ���
	** ����ֵ ��BOOL TRUE ��������ɹ���FALSE ʧ��
	** ��  �� ��  
	** ��  �� ��   
	***************************************************************************/
	SYSTEMMEMORY_API BOOL SystemMemory_QueryData(UINT32 uLen);

	/***************************************************************************
	**�������ƣ�SystemMemory_BuQueryData
	**�������ܣ���ȡBU˲�ϵ�����
	**��ڲ�������
	** ����ֵ ��BOOL TRUE ��������ɹ���FALSE ʧ��
	** ��  �� ��  
	** ��  �� ��   
	***************************************************************************/
	BOOL SystemMemory_BuQueryData(void);
	

#ifdef __cplusplus
}
#endif

#endif  /* #define FT_MID_LASTMEMORY_H */