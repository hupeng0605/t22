/**
* Copyright (C) 2003-2005��            
* All rights reserved.
* 
* �ļ����ƣ�Thread.h
* ժ    Ҫ���߳̿��ơ������ź�����������ʵ���ļ�
*
* ��ǰ�汾��0.2
* ��    �ߣ�              
* ������ڣ�2005��5��20��
*
* ȡ���汾��0.1
* ԭ �� �ߣ�����
* ������ڣ�2005��4��20��
**/ 

#ifndef _THREAD_H__
#define _THREAD_H__

#include <windows.h>
//#include "KNAssert.h"	// 2007/12/4 qipengl add 

typedef unsigned int PFN(void *);

//�߳̿�����
class Thread 
{
public:

	/*
	* �������ܣ����캯��
	* �� �� ֵ����
	*/
	Thread()
	{
		m_bActive = false;
		m_hHandle = NULL;
		m_pRun = NULL;
		m_pArg = NULL;		
	}
	
	/*
	* �������ܣ���������
	* �� �� ֵ����
	*/
	~Thread()
	{
		if(m_hHandle)
		{
			WaitForThreadEnd();	// ע�⣺���ܻ�����߳�������ֹͣ��Ӧ������ʱӦע��
			CloseHandle(m_hHandle);
		}
	}

	/*
	* �������ܣ����̺߳���ָ�뼰���в����ҵ��߳�����
	* ��    ����
	* 		*p_fn [in] ������ָ��
	* 		*arg  [out]���������в���
	* �� �� ֵ����
	*/
	void Attach(PFN *pFun, void *pArg)
	{
		ASSERT(pFun);
		m_pRun=pFun;
		m_pArg=pArg;
	}

	/*
	* �������ܣ������߳�
	* �� �� ֵ����
	*/
	HANDLE CreateMyThread(HBOOL bSuspend = false)
	{
		if (!m_bActive)
		{
			m_hHandle = CreateThread( NULL,
									 NULL,
									 (LPTHREAD_START_ROUTINE)m_pRun,
									 m_pArg,
									 bSuspend ? CREATE_SUSPENDED : NULL,NULL);
			ASSERT(m_hHandle);
			m_bActive = true;
			SetThreadPriority(THREAD_PRIORITY_NORMAL);
			return m_hHandle;
		}
		else
		{
			return NULL;
		}
	}
	
	/*
	* �������ܣ���ѯ�߳��Ƿ�
	* �� �� ֵ���/���
	*/
	HBOOL IsMyThreadActive()
	{
		return m_bActive;
	}	
	
	/*
	* �������ܣ�ֹͣ�߳�
	* �� �� ֵ����
	*/
	void StopMyThread()
	{
		m_bActive = false;
		// ADD.               .2007.4.24
		// --Begin
		if(m_hHandle)
		{
			HDWORD dwExitCode = 0;
			WaitForThreadEnd();
			GetExitCodeThread(m_hHandle, &dwExitCode);
			CloseHandle(m_hHandle);
			m_hHandle = NULL;
		}
		// --End
	}

	/*
	* �������ܣ��ȴ��߳̽���
	* �� �� ֵ����
	*/
	void WaitForThreadEnd()
	{
		WaitForSingleObject(m_hHandle, INFINITE); //�ȴ��߳̽���
	}

	/*
	* �������ܣ�ǿ�ƽ����߳�(һ�㲻Ӧʹ�ô˺��������̣߳�Ӧ���߳��Լ�����)
	* �� �� ֵ��BOOL
	*/
	BOOL TerminateMyThread()
	{
		return TerminateThread(m_hHandle, NULL);
	}

	HANDLE GetHandle()
	{
		return m_hHandle;
	}

	HBOOL SetThreadPriority(HINT priority)
	{
		return ::SetThreadPriority(m_hHandle, priority) ? true : false;
	}

	HDWORD ResumeThread()
	{
		return ::ResumeThread(m_hHandle);
	}

	HDWORD SuspendThread()
	{
		return ::SuspendThread(m_hHandle);
	}

private:
	// ����˵�����߳��Ƿ�
	HBOOL m_bActive;
	
	// ����˵�����߳̾��
	HANDLE m_hHandle;

	// ����˵�����̺߳���
	PFN *m_pRun;

	// ����˵�����̺߳������в���
	void *m_pArg;
};

//��
class SLock
{
public:

	/*
	* �������ܣ����캯��
	* ��    ����
	* 		uiLockStatus [in] ��������ʱ����״̬(1������ / ����ֵ����)
	* �� �� ֵ����
	*/
	SLock(HUINT uiLockStatus = 1 )
	{
		m_sem = ::CreateSemaphore(0, uiLockStatus, 1, 0); 
	}
	
	/*
	* �������ܣ���������
	* �� �� ֵ����
	*/
	~SLock()
	{
		if(m_sem)
		{
			CloseHandle(m_sem);
			m_sem=NULL;
		}
	}

	/*
	* �������ܣ���������
	* ��    ����
	* 		uiTimeOut [in] ����ʱʱ�䣬(-1���ò���ʱ)
	* �� �� ֵ������״̬
	*/
	HINT Lock(unsigned int uiTimeOut=INFINITE)
	{
		//�źż�1
		if(m_sem)
		{
			return WaitForSingleObject(m_sem, uiTimeOut);
		}
		return -1;
	}
	
	/*
	* �������ܣ���������
	* �� �� ֵ������״̬
	*/
	HINT UnLock()
	{
		//�źż�1
		if(m_sem)
		{
			return ReleaseSemaphore(m_sem,1,0);
		}
		return -1;
	}

private:
	// ����˵�����źž��
	HANDLE m_sem;
};

//�ź���������(����ʵ��)
class SSem
{
public:
	
	/*
	* �������ܣ����캯��(��ʼ����)
	* �� �� ֵ����
	*/
	SSem::SSem():m_SLock(0)
	{
	}
	
	/*
	* �������ܣ���������
	* �� �� ֵ����
	*/
	SSem::~SSem()
	{
	}

	/*
	* �������ܣ������ź���
	* �� �� ֵ������״̬
	*/
	HINT SSem::Product()
	{
		return m_SLock.UnLock();
	}

	/*
	* �������ܣ������ź���
	* �� �� ֵ������״̬
	*/
	HINT SSem::Custom()
	{
		return m_SLock.Lock();
	}

private:
	// ����˵��������ʵ���ź�������
	SLock m_SLock;
};

// ģ��˵�����ٽ���
template <class T> class Critical : public T,public SLock{};

#endif //_THREAD_H__
/////////////////////////////////////////////////////////////////////////////

