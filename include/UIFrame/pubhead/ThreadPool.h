/**
* Copyright (C) 2003-2006，            
* All rights reserved.
* 
* 文件名称：threadpool.h
* 摘    要：线程池接口以及互斥体类声明文件
*
* 当前版本：0.3
* 作    者：              
* 完成日期：2006年 1月 8日
*
* 取代版本：0.2
* 原 作 者：pitt
* 完成日期：2005年 7月 8日
**/ 
#ifndef _THREAD_POOL_H__
#define _THREAD_POOL_H__

#include "Pubhead.h"
#include <queue>
#include <exception>
#include <assert.h>

#undef DEBUG
using namespace std;


// ADD. hzf.2006.11.8.
// --Begin
//lint -e1735
// --End


#define THREADPOOL_MAX_THREAD_COUNT 24
#define THREADPOOL_MAX_TASK_COUNT	1024

// My thread function
typedef bool (*THREAD_POOL_EXECUTE_FN) (unsigned int, void*);

// Task structure
typedef struct _THREAD_POOL_TASK
{
	unsigned int			unMessage;		// Task Id; Can be 0.
	THREAD_POOL_EXECUTE_FN	pFunction;		// Execution Procedure provided by client.
	void*					pExtraInfo;		// Extra information.			
}THREAD_POOL_TASK, *PTHREAD_POOL_TASK;

// Task queue information
typedef struct _THREAD_POOL_QUEUE_INFO {
	THREAD_POOL_TASK	FuncInfo;
	unsigned int		ixTask;	
}THREAD_POOL_QUEUE_INFO, *PTHREAD_POOL_QUEUE_INFO;

#ifdef WIN32
	typedef unsigned int (__stdcall* THREAD_PROC)(void *);
#elif defined POSIX_THREAD
	typedef void* (*POSIX_THREAD_PROC) (void*);
#else
	//....
#endif

typedef struct _THREAD_DATA
{
	unsigned long hThread;		// Thread handle.
	unsigned int  nThreadId;	// Thread Id.
	unsigned int  nFlags;		// Thread status such as marked for exit.	
}THREAD_DATA, *PTHREAD_DATA;

// Thread Pool Interface
Interface IThreadPool
{
public:
	// Add. hzf.2006.05.17.
	virtual ~IThreadPool(){};

	virtual bool Initialize( unsigned int cntThreads      = 1, 
					 unsigned int nMaxThreadCount = THREADPOOL_MAX_THREAD_COUNT, 
					 unsigned int nMaxTaskCount   = THREADPOOL_MAX_TASK_COUNT   
				   ) = 0;

	virtual void Uninitialize() = 0;

	virtual bool AssignTask(PTHREAD_POOL_TASK pTask) = 0;
};

extern "C" KNAPI IThreadPool * GetThreadPoolSingleton();

#ifdef DEBUG

struct KNTracerPoint
{
	char sFileName[MAX_PATH];
	int iLine;

	KNTracerPoint()
	{
		sFileName[0] = '\0'; 
		iLine = 0;
	}

	virtual ~KNTracerPoint()
	{
		sFileName[0] = '\0'; 
		iLine = 0;
	}
};

#define TRACE_POINT_MAX (5)

#define lock_read() LockRead(__FILE__, __LINE__);
#define lock_write() LockWrite(__FILE__, __LINE__);

#define unlock_read() UnlockRead(__FILE__, __LINE__);
#define unlock_write() UnlockWrite(__FILE__, __LINE__);

typedef deque<KNTracerPoint> KTracerPointDeque;
#endif



/******************************************************************
 * Win32平台上模拟读写锁
 * 自动事件控制当前读/写状态, 手动事件控制读锁分配
 * 临界区负责控制保护分配读锁和释放读锁,手动事件或
 * 自动事件中只要一个为有信号状态，则读锁可以分配, 
 * 此时，自动事件已一定为无信号状态，获得读锁的线程
 * 负责将手动事件设为有信号状态以便其他要求分配读锁
 * 的线程通过若某线程(根据读线程计数)检测到自己是最
 * 后一个释放读锁的线程，则它负责将手动事件置为无信
 * 号状态，然后将自动事件置为有信号状态。
*******************************************************************/
// 读写锁超时时间定义为10秒,可满足绝大部分情况,
// 可避免程序发生死锁后无法继续操作的问题,
// 另外可判断程序锁死是否为程序发生死锁
// #define LOCK_TIMEOUT 100000
#define LOCK_TIMEOUT 10000 // 注释为10秒，原始定义为100秒

// ADD. hzf.2008/01/08
// --Begin
/*
 * EnterCriticalSection/LeaveCriticalSection 控制读计数的访问同步
 *
 * tockens_[0]: 有信号，表示可写（当然也可读），无信号，表示不可写
 * tockens_[1]: 有信号，表示可读，无信号，表示不可读（此时应处于写状态）
 *
 * 读鍞： 在进行写入操作时(acquire_write)，关闭读权限，即ResetEvent(tockens_[1])，等待写权限（读写操作完成后）；在写入操作完成后(release_write)，开放读权限，即SetEvent(tockens_[1])，同时开放写权限
 * 写鍞： 在1. 所有读操作(release_read)完成或2.写操作完成后(release_write)，开放写鍞，有任何读操作或写操作时，关闭写鍞
 * 
 * 写操作完成后(release_write)，读权限及写权限同时开放
 * 因写鍞等待超时获得写权限时，将读计数置0；释放读权限时，如读计数小于0，则将读计数置0(异常处理)
 * 写操作开始时，关闭读权限ResetEvent(tockens_[1])
 * 所有读操作完成时，开放写鍞（此时因处于读状态，因此不可能处于写状态）
 * 获取读权限后，应关闭写权限
 * 写权限优先级高于读权限，因此，在请求写权限时，马上阻塞读权限的获取，则只有在已取得读权限时，才阻塞写权限
 */
// --End

// 所有读操作完成后，开放写权限，但不禁止读权限。
// 写操作完成后，开放读权限，但不禁止读写权限。
// 释放写操作时，才将读读数清0，开始新一轮的读数。
// 申请写权限前先关闭读权限，但在取得读权限后关闭写权限。（如果在取得读权限前关闭写权限，是否会出现：互相关闭对方的权限，同时等待权限），这里有写优先的意味。

class KN_RW_Lock
{
public:
    
    KN_RW_Lock(int initialstate = 1)
    {
        readcount_ = 0;     
        tockens_[0] = CreateEvent (0, 0, initialstate, 0); /* 自动重置事件 */
        tockens_[1] = CreateEvent (0, 1, 0, 0); /* 手动重置事件,初始为无信号状态 */
        InitializeCriticalSection (&readguard_);

		// ADD. hzf.2008/05/06
		// --Begin
#ifdef DEBUG
		bIsWriting = false;
		bIsReading = false;
#endif		
		// --End
    }
    
    ~KN_RW_Lock()
    {
        CloseHandle (tockens_[0]);
        CloseHandle (tockens_[1]);
        DeleteCriticalSection (&readguard_);
    }
 
#ifdef DEBUG
    int acquire (char* sFileName, int iLine) /*const*/ // 请求写操作
#else
    int acquire (void) /*const*/ // 请求写操作
#endif
    {        
		ResetEvent(tockens_[1]); // 关闭读权限

		DWORD ret  = WaitForSingleObject (tockens_[0], LOCK_TIMEOUT);

		// ADD. hzf.2008/05/06
		// --Begin
#ifdef DEBUG
		if (WAIT_OBJECT_0 != ret)
		{
			assert(0); // 写等待超时	
		}

		bIsWriting = true;
		bIsReading = false;

		if (deqTracerPoint.size() >= TRACE_POINT_MAX)
		{
			deqTracerPoint.pop_front();
		}
		KNTracerPoint oneTracerPoint;
		strcpy(oneTracerPoint.sFileName, sFileName);
		oneTracerPoint.iLine = iLine;
		deqTracerPoint.push_back(oneTracerPoint);
#endif		
		// --End

        if (WAIT_OBJECT_0 != ret)
		{
			return -1;
		}
		else
		{
			return 0;    		
		}
    }
    
#ifdef DEBUG
    int acquire_read (char* sFileName, int iLine) // 请求读操作
#else
    int acquire_read (void) // 请求读操作
#endif
    {        
        DWORD ret = WaitForMultipleObjects (2, tockens_, 0 /*any*/, LOCK_TIMEOUT); // 可读或可写状态，均具有可读权限

		// ADD. hzf.2008/05/06
		// --Begin
#ifdef DEBUG
		if (!(WAIT_OBJECT_0 <= ret && (WAIT_OBJECT_0 + 1) >= ret))
		{
			assert(0); // 读等待超时
		}

		bIsReading = true;
		bIsWriting = false;

		if (deqTracerPoint.size() >= TRACE_POINT_MAX)
		{
			deqTracerPoint.pop_front();
		}
		KNTracerPoint oneTracerPoint;
// 		oneTracerPoint.sFileName = sFileName;
		strcpy(oneTracerPoint.sFileName, sFileName);
		oneTracerPoint.iLine = iLine;
		deqTracerPoint.push_back(oneTracerPoint);
#endif
		// --End

		ResetEvent(tockens_[0]); // 此时，可能写权限也处于开放状态，因此要避免执行读操作时同时又执行写操作
        
		EnterCriticalSection (&readguard_);
        readcount_++;    
        LeaveCriticalSection (&readguard_);
        
		if (WAIT_OBJECT_0 != ret)
		{
			return -1;
		}
		else
		{
			return 0;
		}
    }
    
#ifdef DEBUG
	int acquire_write (char* sFileName, int iLine) /*const*/ // 请求写操作
	{
		return acquire(sFileName, iLine);
	}
#else
    int acquire_write (void) /*const*/ // 请求写操作
	{
		return acquire();
	}
#endif

    
    int release (void) /*const*/ // 写操作完成
    {        
		EnterCriticalSection (&readguard_);
		readcount_ = 0; // 读计数清空
		LeaveCriticalSection (&readguard_);

		SetEvent(tockens_[1]); // 开放读权限，但也不能禁止写操作。此时，读、写权限进行资源竞争。
		SetEvent(tockens_[0]); // 激活新的写操作权限

#ifdef DEBUG
		bIsWriting = false;
#endif		

        return 0;       
    }
    
#ifdef DEBUG
    int release_read (char* sFileName, int iLine) // 读操作完成
#else
    int release_read (void) // 读操作完成
#endif
    {        
        EnterCriticalSection (&readguard_);
        
        readcount_--;
		if (readcount_ < 0)
		{
			readcount_ = 0;
		}

        if (!readcount_)
        {
            SetEvent (tockens_[0]); // 所有读权限释放，则开放写权限。但也不能禁止读操作。此时，读、写权限进行资源竞争。
        }

		LeaveCriticalSection (&readguard_);

#ifdef DEBUG
		bIsReading = false;

		if (deqTracerPointForRelease.size() >= TRACE_POINT_MAX)
		{
			deqTracerPointForRelease.pop_front();
		}
		KNTracerPoint oneTracerPoint;
// 		oneTracerPoint.sFileName = sFileName;
		strcpy(oneTracerPoint.sFileName, sFileName);
		oneTracerPoint.iLine = iLine;
		deqTracerPointForRelease.push_back(oneTracerPoint);
#endif
        
        return 0;     
    }
    
#ifdef DEBUG
    int release_write (char* sFileName, int iLine) /*const*/ // 写操作完成
    {
		if (deqTracerPointForRelease.size() >= TRACE_POINT_MAX)
		{
			deqTracerPointForRelease.pop_front();
		}
		KNTracerPoint oneTracerPoint;
// 		oneTracerPoint.sFileName = sFileName;
		strcpy(oneTracerPoint.sFileName, sFileName);
		oneTracerPoint.iLine = iLine;
		deqTracerPointForRelease.push_back(oneTracerPoint);

        return release ();
    }
#endif

    int release_write (void) /*const*/ // 写操作完成
    {
        return release ();
    }
    
protected:

    
    HANDLE tockens_[2];

    int readcount_;
    CRITICAL_SECTION readguard_;      

	// ADD. hzf.2008/05/06
	// --Begin
#ifdef DEBUG
	HBOOL bIsWriting; // 增加此成员方便调试，初始化为false，当取得写权限时置true，当释放写权限或取得读权限时置false。
	HBOOL bIsReading; // 增加此成员方便调试，初始化为false，当取得读权限时置true，当释放读权限或取得写权限时置false。
	KTracerPointDeque deqTracerPoint;
	KTracerPointDeque deqTracerPointForRelease;
#endif	
	// --End
};


// DELETE. hzf.2006.11.8.
// --Begin
//class KN_Lock
//{
//public:
//    KN_Lock(int initialstate = 1)
//    {
//        InitializeCriticalSection (&guard_);
//    }
//    
//    ~KN_Lock()
//    {
//        DeleteCriticalSection (&guard_);
//    }
//	
//private:    
//    int acquire (void) 
//    {        
//        EnterCriticalSection (&guard_);
//		
//        return 0;    
//    }
//    
//    int acquire_read (void) 
//    {        
//        EnterCriticalSection (&guard_);
//        
//        return 0;
//    }
//    
//    int acquire_write (void)
//    {
//        return acquire();
//    }
//	
//    int release (void)
//    {        
//        LeaveCriticalSection (&guard_);
//        
//        return 0;       
//    }
//    
//    int release_read (void)
//    {        
//        LeaveCriticalSection (&guard_);
//		
//        return 0;     
//    }
//    
//    int release_write (void)
//    {
//        return release ();
//    }
//    
//    
//protected:
//    
//    CRITICAL_SECTION guard_;   
//};
// --End

template <class T/* 数据的类型 */, class LOCK = KN_RW_Lock /* 同步类型 */>
class HSyncData
{
public:
    HSyncData()
    {
    }

    ~HSyncData()
    {

    }

#ifdef DEBUG

	int LockRead(char* sName, int iLine)
	{
		return lock_.acquire_read(sName, iLine);
	}

    int LockWrite(char* sName, int iLine) /*const*/
    {
        return lock_.acquire_write(sName, iLine);
    }

	int UnlockRead(char* sName, int iLine)
	{
		return lock_.release_read(sName, iLine);
	}

    int UnlockWrite(char* sName, int iLine) /*const*/
    {
		return lock_.release_write(sName, iLine);
    }

#else

	int lock_read()
	{
		return lock_.acquire_read();
	}

	int lock_write() /*const*/
    {
        return lock_.acquire_write();
    }

	int unlock_read()
	{
		return lock_.release_read();
	}

    int unlock_write() /*const*/
    {
		return lock_.release_write();
    }

#endif
	

   typename T data_;

protected:

   typename LOCK lock_;
};

template<class T, class LOCK = KN_RW_Lock>
class KSyncDataPtr
{
    typedef HSyncData<T,LOCK> ptr_type;

public:
    KSyncDataPtr(int lock_type = 0) : type_(lock_type)
    {
        ptr_ = NULL;
    }

    KSyncDataPtr(ptr_type *ptr):type_(0)
    {
        ptr_ = ptr;

        type_ == 0?ptr_->lock_read():ptr_->lock_write();
    }

    ~KSyncDataPtr()
    {
        type_ == 0?ptr_->unlock_read():ptr_->unlock_write();
    }

    ptr_type* operator = (ptr_type *ptr)
    {
        ptr_ = ptr;

        type_ == 0?ptr_->lock_read():ptr_->lock_write();

        return ptr;
    }

    ptr_type* operator ->()
    {
        return ptr_;
    }

protected:

   ptr_type* ptr_;
   const int type_;
};

// ADD. hzf.2006.11.8.
// --Begin
//lint +e1735
// --End

#endif  // _THREAD_POOL_H__