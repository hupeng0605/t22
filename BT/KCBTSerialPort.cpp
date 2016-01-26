#include "KCBTSerialPort.h"

CSerialPort::CSerialPort()
:m_ReadDataProc(NULL),m_WriteDataProc(NULL),m_bInitFinished(FALSE),m_hCom(INVALID_HANDLE_VALUE)
,m_hReadThread(INVALID_HANDLE_VALUE),m_dwWriteSize(0),m_dwReadSize(0),m_bContinue(FALSE)
{
	memset(m_szPortName,0,sizeof(m_szPortName));
	memset(m_szReadBuffer,0,sizeof(m_szReadBuffer));
	memset(m_szWriteBuffer,0,sizeof(m_szWriteBuffer));
}
CSerialPort::~CSerialPort()
{
	UnInitPort();
}

BOOL CSerialPort::UnInitPort(void)
{
	m_bContinue = FALSE;
	m_bInitFinished = FALSE;
	m_dwWriteSize = 0;
	//if (m_hCom)
	//{
	//	SetCommMask(m_hCom, /*EV_ERR | EV_TXEMPTY*/ 0);
	//}
	if (m_hCom)
	{
		CloseHandle(m_hCom);
		m_hCom = INVALID_HANDLE_VALUE;
	}
	if (m_hReadThread)
	{
		if (WaitForSingleObject(m_hReadThread, 1000) == WAIT_TIMEOUT)
		{
			::TerminateThread(m_hReadThread, 0);
			BTDEBUGINFO(L"读线程强行终止！");
		}
		CloseHandle(m_hReadThread);
		m_hReadThread = NULL;
	}
	return TRUE;
}
BOOL CSerialPort::InitPort(DWORD dwPort, DWORD dwBaudRate)
{
	UnInitPort();
	if(dwPort < 0 && dwPort > 10)
	{
		return FALSE;
	}
	wsprintf(m_szPortName, _T("COM%d:"), dwPort);
	if (m_hCom != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hCom);
	}
	m_hCom = CreateFile(m_szPortName, GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, 0, NULL);
	if (m_hCom == INVALID_HANDLE_VALUE)
	{
		BTDEBUGINFO(L"comfail");
		//CloseHandle(m_hCom);
		return false;
	}
		//BTDEBUGINFO(L"**************************'")	;// 配置串行端口
	DCB dcb;
	dcb.DCBlength = sizeof(DCB);
	::GetCommState(m_hCom, &dcb);
	dcb.BaudRate = dwBaudRate;
	dcb.fParity = FALSE;
	dcb.fNull = FALSE;
	dcb.Parity=NOPARITY;
	dcb.ByteSize=8;
	dcb.StopBits=ONESTOPBIT;
	::SetCommState(m_hCom, &dcb);
	COMMTIMEOUTS timeouts;
	//GetCommTimeouts(m_hComm,&timeouts);
	timeouts.ReadIntervalTimeout=10;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.ReadTotalTimeoutConstant = 100;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 100;  
	SetCommTimeouts(m_hCom,&timeouts);
	PurgeComm(m_hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
	m_bContinue = TRUE;
	DWORD dwThreadID;
	m_hReadThread = CreateThread(NULL, 0, ReadThread, this, 0, &dwThreadID);
	if (m_hReadThread == NULL)
	{
		return FALSE;
	}
	m_bInitFinished = TRUE;
	BTDEBUGINFO(L"读线程创建成功！");
	return TRUE;
}

BOOL CSerialPort::RegisterProc(FpCallbackProc ReadDataProc, FpCallbackProc WriteDataProc, void* pData)
{
	m_pUserData = pData;
	m_ReadDataProc = ReadDataProc;
	m_WriteDataProc = WriteDataProc;
	return TRUE;
}

BOOL CSerialPort::SendData(LPBYTE pszData, DWORD dwSize)
{
	if (! m_bInitFinished)
	{
		return FALSE;
	}
	if (pszData == NULL && dwSize == 0)
	{
		return FALSE;
	}
#if BTINFOMESSAGE
	HCHAR arrTxt[128] = {0};
	MultiByteToWideChar(CP_ACP,0,(char*)pszData,-1,arrTxt,dwSize);
	arrTxt[dwSize] = L'\0';
	BTDEBUGINFO(L"[%s]%s,uSize=%d",__FUNCTIONW__,arrTxt,dwSize);
#else
#endif
	// 复制数据到写数据的buffer中
	memset(m_szWriteBuffer, 0, sizeof(m_szWriteBuffer));
	memcpy(m_szWriteBuffer, pszData, dwSize);
	m_dwWriteSize = dwSize;
	//PurgeComm(m_hCom, PURGE_TXCLEAR );		// 清理串口buffer
	WriteComData();
	return TRUE;
}

DWORD CSerialPort::WriteComData(void)
{
	if (m_hCom == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	BOOL bResult = FALSE;
	DWORD dwWrite;
	bResult = ::WriteFile(m_hCom, (LPBYTE)m_szWriteBuffer, m_dwWriteSize, &dwWrite, NULL);
	if (bResult && dwWrite == m_dwWriteSize)
	{
		//BTDEBUGINFO(L"[%s]write data successful",__FUNCTIONW__);
		if (m_WriteDataProc)
			m_WriteDataProc(m_pUserData, WM_PORT_WRITE_DATA, (WPARAM)enPortWrittenOK, (LPARAM)m_szWriteBuffer,this);
	}
	else
	{
		if (m_WriteDataProc)
			m_WriteDataProc(m_pUserData, WM_PORT_WRITE_DATA, (WPARAM)enPortWrittenError, (LPARAM)m_szWriteBuffer,this);
	}
	return dwWrite;
}



DWORD WINAPI CSerialPort::ReadThread(LPVOID pUserData)
{
	CSerialPort* pSerialPort = static_cast<CSerialPort*>(pUserData);
	if (pSerialPort != NULL)	
	{
		pSerialPort->ReadData();
	}
	BTDEBUGINFO(L"读线程正常退出！");
	return 0;
}

// 发送宽字符数据到串口
BOOL CSerialPort::SendData(LPCTSTR pszData, DWORD dwSize)
{
	if (! m_bInitFinished)
	{
		return FALSE;
	}
	if (pszData == NULL && lstrlen(pszData) == 0)
	{
		return FALSE;
	}
	// 复制数据到写数据的buffer中
	memset(m_szWriteBuffer, 0, sizeof(m_szWriteBuffer));
	wcstombs(m_szWriteBuffer, pszData, TEXTSIZE);
	m_dwWriteSize = strlen(m_szWriteBuffer);
	PurgeComm(m_hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);		// 清理串口buffer
	WriteComData();
	return TRUE;
}

DWORD CSerialPort::ReadData(void)
{
	DWORD dwEventMask = EV_ERR | EV_RXCHAR;
	if (!SetCommMask(m_hCom, dwEventMask))		// 设置
	{
		return 0;
	}
	while (m_bContinue)
	{
		if (m_hCom == INVALID_HANDLE_VALUE)
		{
			return 0;
		}
		if (WaitCommEvent(m_hCom, &dwEventMask, NULL))
		{
			DWORD dwError;
			COMSTAT comstat;
			ClearCommError(m_hCom, &dwError, &comstat);
			DWORD dwValue = comstat.cbInQue;
			if(dwValue > (TEXTSIZE - 1))
			{
				PurgeComm(m_hCom, PURGE_RXCLEAR | PURGE_TXCLEAR);
				ClearCommError(m_hCom, &dwError, &comstat);
				if(m_hCom == INVALID_HANDLE_VALUE)
				{
					BTDEBUGINFO(L"读线程异常");
				}
				BTDEBUGINFO(L"warrn :dwValue=%d",dwValue);
				continue;	
			}
			//DWORD dwValue2 = comstat.cbOutQue;
			switch (dwEventMask & 0xFF)
			{
			case EV_RXCHAR:
				{
					DWORD dwRead = 0;
					memset(m_szReadBuffer, 0, sizeof(m_szReadBuffer));
					if (! ReadFile(m_hCom, m_szReadBuffer, dwValue, &dwRead, 0))
						break;
				//	wprintf(L"[BT] [CSerialPort::ReadData] %d\r\n", dwValue);
					//if(dwRead < 2048)
					//{
						//for(int i = 0; i < dwRead;i++)
						//{
							//cout<<m_szReadBuffer[i];
						//}
				//	}
				/*HBYTE cc[100] = "N;CHARSET=UTF-8:我的名字";
					HINT n = strlen( "N;CHARSET=UTF-8:我的名字");
					for(HINT i = 0; i < n;i++)
					{
						cout<<cc[i];
					}
					cout<<endl<<"%%%%%%%%%%%%%%%%"<<endl;*/
					//BTDEBUGINFO(L"N;CHARSET=UTF-8:我的名字");
					m_dwReadSize = dwRead;
					//BTDEBUGINFO(L"%s,m_dwReadSize = %d",__FUNCTIONW__,m_dwReadSize);
					PortRetureData data = {0};
					data.pszUnicodeData = NULL;
					// HBYTE p[100]="aaaa\r\nPBDATA=20\r\n12345678901234567890";
					data.pszAnsiData = m_szReadBuffer;
					//data.pszAnsiData = p;
					data.dwSize = m_dwReadSize;
				//	data.dwSize = strlen("aaaa\r\nPBDATA=20\r\n12345678901234567890");
					if (m_ReadDataProc)
					{
					//	BTDEBUGINFO(L"[%s]m_ReadDataProc Enter",__FUNCTIONW__);
					m_ReadDataProc(m_pUserData, WM_PORT_READ_DATA, (WPARAM)enPortReadOK, (LPARAM)&data,this);
					}
					break;
				}
			case EV_ERR:
				{
					PurgeComm(m_hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);		
					if (m_ReadDataProc)
						m_ReadDataProc(m_pUserData, WM_PORT_READ_DATA, (WPARAM)enPortReadError, 0,this);
					break;
				}
			}
		}
		Sleep(50);
	}
	return 0;
}




