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
	void*			    m_pUserData;				// �ص������û�����
	FpCallbackProc		m_ReadDataProc;		        // �����ݻص�����
	FpCallbackProc		m_WriteDataProc;		    // д���ݻص�����
	BOOL			    m_bInitFinished;			// ��ʼ��״̬���ɹ���ʧ��
	HANDLE		m_hCom;						// Com�˿ھ��
	TCHAR		m_szPortName[8];			// �˿���
	HANDLE		m_hReadThread;			// ���˿��߳̾��
	BYTE		m_szReadBuffer[TEXTSIZE];	// ���ַ���������
	char		m_szWriteBuffer[TEXTSIZE];	// д�ַ���������
	DWORD		m_dwWriteSize;			// д�ַ����Ĵ�С
	DWORD		m_dwReadSize;			// �����ַ����Ĵ�С
	BOOL		m_bContinue;				// �߳��Ƿ����

};