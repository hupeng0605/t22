/**
* Copyright (C) 2003-2005，            
* All rights reserved.
* 
* 文件名称：Thread.h
* 摘    要：线程控制、锁、信号量类声明及实现文件
*
* 当前版本：0.2
* 作    者：              
* 完成日期：2005年5月20日
*
* 取代版本：0.1
* 原 作 者：周瑞
* 完成日期：2005年4月20日
**/ 

#ifndef _THREAD_H__
#define _THREAD_H__

#include <windows.h>
//#include "KNAssert.h"	// 2007/12/4 qipengl add 

typedef unsigned int PFN(void *);

//线程控制类
class Thread 
{
public:

	/*
	* 函数功能：构造函数
	* 返 回 值：无
	*/
	Thread()
	{
		m_bActive = false;
		m_hHandle = NULL;
		m_pRun = NULL;
		m_pArg = NULL;		
	}
	
	/*
	* 函数功能：析构函数
	* 返 回 值：无
	*/
	~Thread()
	{
		if(m_hHandle)
		{
			WaitForThreadEnd();	// 注意：可能会造成线程锁死，停止响应，测试时应注意
			CloseHandle(m_hHandle);
		}
	}

	/*
	* 函数功能：将线程函数指针及运行参数挂到线程类上
	* 参    数：
	* 		*p_fn [in] ：函数指针
	* 		*arg  [out]：函数运行参数
	* 返 回 值：无
	*/
	void Attach(PFN *pFun, void *pArg)
	{
		ASSERT(pFun);
		m_pRun=pFun;
		m_pArg=pArg;
	}

	/*
	* 函数功能：创建线程
	* 返 回 值：无
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
	* 函数功能：查询线程是否活动
	* 返 回 值：活动/不活动
	*/
	HBOOL IsMyThreadActive()
	{
		return m_bActive;
	}	
	
	/*
	* 函数功能：停止线程
	* 返 回 值：无
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
	* 函数功能：等待线程结束
	* 返 回 值：无
	*/
	void WaitForThreadEnd()
	{
		WaitForSingleObject(m_hHandle, INFINITE); //等待线程结束
	}

	/*
	* 函数功能：强制结束线程(一般不应使用此函数结束线程，应由线程自己结束)
	* 返 回 值：BOOL
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
	// 属性说明：线程是否活动
	HBOOL m_bActive;
	
	// 属性说明：线程句柄
	HANDLE m_hHandle;

	// 属性说明：线程函数
	PFN *m_pRun;

	// 属性说明：线程函数运行参数
	void *m_pArg;
};

//锁
class SLock
{
public:

	/*
	* 函数功能：构造函数
	* 参    数：
	* 		uiLockStatus [in] ：构造锁时锁的状态(1：锁定 / 其他值：打开)
	* 返 回 值：无
	*/
	SLock(HUINT uiLockStatus = 1 )
	{
		m_sem = ::CreateSemaphore(0, uiLockStatus, 1, 0); 
	}
	
	/*
	* 函数功能：析构函数
	* 返 回 值：无
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
	* 函数功能：将锁加锁
	* 参    数：
	* 		uiTimeOut [in] ：超时时间，(-1：用不超时)
	* 返 回 值：加锁状态
	*/
	HINT Lock(unsigned int uiTimeOut=INFINITE)
	{
		//信号减1
		if(m_sem)
		{
			return WaitForSingleObject(m_sem, uiTimeOut);
		}
		return -1;
	}
	
	/*
	* 函数功能：将锁解锁
	* 返 回 值：解锁状态
	*/
	HINT UnLock()
	{
		//信号加1
		if(m_sem)
		{
			return ReleaseSemaphore(m_sem,1,0);
		}
		return -1;
	}

private:
	// 属性说明：信号句柄
	HANDLE m_sem;
};

//信号量控制类(用锁实现)
class SSem
{
public:
	
	/*
	* 函数功能：构造函数(初始化锁)
	* 返 回 值：无
	*/
	SSem::SSem():m_SLock(0)
	{
	}
	
	/*
	* 函数功能：析构函数
	* 返 回 值：无
	*/
	SSem::~SSem()
	{
	}

	/*
	* 函数功能：产生信号量
	* 返 回 值：解锁状态
	*/
	HINT SSem::Product()
	{
		return m_SLock.UnLock();
	}

	/*
	* 函数功能：消费信号量
	* 返 回 值：加锁状态
	*/
	HINT SSem::Custom()
	{
		return m_SLock.Lock();
	}

private:
	// 属性说明：用于实现信号量的锁
	SLock m_SLock;
};

// 模板说明：临界区
template <class T> class Critical : public T,public SLock{};

#endif //_THREAD_H__
/////////////////////////////////////////////////////////////////////////////

