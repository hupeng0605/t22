#pragma once
#include"define.h"
class  CSerialPort
{
public:
	CSerialPort();
	virtual~CSerialPort();
	//static CSerialPort* Instance();
	//static void DeleteInstance();
	virtual BOOL RegisterProc(FpCallbackProc ReadDataProc, FpCallbackProc WriteDataProc, void* pData);
	virtual BOOL InitPort(DWORD dwPort, DWORD dwBaudRate);
	virtual BOOL UnInitPort(void);
	virtual BOOL IsOpen(void)	{	return m_bInitFinished;	}
	virtual BOOL SendData(LPCTSTR pszData, DWORD dwSize);
	virtual BOOL SendData(LPBYTE pszData, DWORD dwSize);
private:
	static DWORD WINAPI ReadThread(LPVOID pUserData);
	DWORD ReadData(void);

	DWORD WriteComData(void);
private:
	//static CSerialPort* s_pSerialPort;
	void*			    m_pUserData;				// 回调函数用户数据
	FpCallbackProc		m_ReadDataProc;		        // 读数据回调函数
	FpCallbackProc		m_WriteDataProc;		    // 写数据回调函数
	BOOL			    m_bInitFinished;			// 初始化状态，成功或失败
	HANDLE		m_hCom;						// Com端口句柄
	TCHAR		m_szPortName[8];			// 端口名
	HANDLE		m_hReadThread;			// 读端口线程句柄
	BYTE		m_szReadBuffer[TEXTSIZE];	// 读字符串缓冲区
	char		m_szWriteBuffer[TEXTSIZE];	// 写字符串缓冲区
	DWORD		m_dwWriteSize;			// 写字符串的大小
	DWORD		m_dwReadSize;			// 读的字符串的大小
	BOOL		m_bContinue;				// 线程是否继续

};