/**
* Copyright (C) 2003-2006��            
* All rights reserved.
* 
* �ļ����ƣ�threadpool.h
* ժ    Ҫ���̳߳ؽӿ��Լ��������������ļ�
*
* ��ǰ�汾��0.3
* ��    �ߣ�              
* ������ڣ�2006�� 1�� 8��
*
* ȡ���汾��0.2
* ԭ �� �ߣ�pitt
* ������ڣ�2005�� 7�� 8��
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
 * Win32ƽ̨��ģ���д��
 * �Զ��¼����Ƶ�ǰ��/д״̬, �ֶ��¼����ƶ�������
 * �ٽ���������Ʊ�������������ͷŶ���,�ֶ��¼���
 * �Զ��¼���ֻҪһ��Ϊ���ź�״̬����������Է���, 
 * ��ʱ���Զ��¼���һ��Ϊ���ź�״̬����ö������߳�
 * �����ֶ��¼���Ϊ���ź�״̬�Ա�����Ҫ��������
 * ���߳�ͨ����ĳ�߳�(���ݶ��̼߳���)��⵽�Լ�����
 * ��һ���ͷŶ������̣߳����������ֶ��¼���Ϊ����
 * ��״̬��Ȼ���Զ��¼���Ϊ���ź�״̬��
*******************************************************************/
// ��д����ʱʱ�䶨��Ϊ10��,��������󲿷����,
// �ɱ���������������޷���������������,
// ������жϳ��������Ƿ�Ϊ����������
// #define LOCK_TIMEOUT 100000
#define LOCK_TIMEOUT 10000 // ע��Ϊ10�룬ԭʼ����Ϊ100��

// ADD. hzf.2008/01/08
// --Begin
/*
 * EnterCriticalSection/LeaveCriticalSection ���ƶ������ķ���ͬ��
 *
 * tockens_[0]: ���źţ���ʾ��д����ȻҲ�ɶ��������źţ���ʾ����д
 * tockens_[1]: ���źţ���ʾ�ɶ������źţ���ʾ���ɶ�����ʱӦ����д״̬��
 *
 * ��唣� �ڽ���д�����ʱ(acquire_write)���رն�Ȩ�ޣ���ResetEvent(tockens_[1])���ȴ�дȨ�ޣ���д������ɺ󣩣���д�������ɺ�(release_write)�����Ŷ�Ȩ�ޣ���SetEvent(tockens_[1])��ͬʱ����дȨ��
 * д唣� ��1. ���ж�����(release_read)��ɻ�2.д������ɺ�(release_write)������д唣����κζ�������д����ʱ���ر�д�
 * 
 * д������ɺ�(release_write)����Ȩ�޼�дȨ��ͬʱ����
 * ��д唵ȴ���ʱ���дȨ��ʱ������������0���ͷŶ�Ȩ��ʱ���������С��0���򽫶�������0(�쳣����)
 * д������ʼʱ���رն�Ȩ��ResetEvent(tockens_[1])
 * ���ж��������ʱ������д唣���ʱ���ڶ�״̬����˲����ܴ���д״̬��
 * ��ȡ��Ȩ�޺�Ӧ�ر�дȨ��
 * дȨ�����ȼ����ڶ�Ȩ�ޣ���ˣ�������дȨ��ʱ������������Ȩ�޵Ļ�ȡ����ֻ������ȡ�ö�Ȩ��ʱ��������дȨ��
 */
// --End

// ���ж�������ɺ󣬿���дȨ�ޣ�������ֹ��Ȩ�ޡ�
// д������ɺ󣬿��Ŷ�Ȩ�ޣ�������ֹ��дȨ�ޡ�
// �ͷ�д����ʱ���Ž���������0����ʼ��һ�ֵĶ�����
// ����дȨ��ǰ�ȹرն�Ȩ�ޣ�����ȡ�ö�Ȩ�޺�ر�дȨ�ޡ��������ȡ�ö�Ȩ��ǰ�ر�дȨ�ޣ��Ƿ����֣�����رնԷ���Ȩ�ޣ�ͬʱ�ȴ�Ȩ�ޣ���������д���ȵ���ζ��

class KN_RW_Lock
{
public:
    
    KN_RW_Lock(int initialstate = 1)
    {
        readcount_ = 0;     
        tockens_[0] = CreateEvent (0, 0, initialstate, 0); /* �Զ������¼� */
        tockens_[1] = CreateEvent (0, 1, 0, 0); /* �ֶ������¼�,��ʼΪ���ź�״̬ */
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
    int acquire (char* sFileName, int iLine) /*const*/ // ����д����
#else
    int acquire (void) /*const*/ // ����д����
#endif
    {        
		ResetEvent(tockens_[1]); // �رն�Ȩ��

		DWORD ret  = WaitForSingleObject (tockens_[0], LOCK_TIMEOUT);

		// ADD. hzf.2008/05/06
		// --Begin
#ifdef DEBUG
		if (WAIT_OBJECT_0 != ret)
		{
			assert(0); // д�ȴ���ʱ	
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
    int acquire_read (char* sFileName, int iLine) // ���������
#else
    int acquire_read (void) // ���������
#endif
    {        
        DWORD ret = WaitForMultipleObjects (2, tockens_, 0 /*any*/, LOCK_TIMEOUT); // �ɶ����д״̬�������пɶ�Ȩ��

		// ADD. hzf.2008/05/06
		// --Begin
#ifdef DEBUG
		if (!(WAIT_OBJECT_0 <= ret && (WAIT_OBJECT_0 + 1) >= ret))
		{
			assert(0); // ���ȴ���ʱ
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

		ResetEvent(tockens_[0]); // ��ʱ������дȨ��Ҳ���ڿ���״̬�����Ҫ����ִ�ж�����ʱͬʱ��ִ��д����
        
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
	int acquire_write (char* sFileName, int iLine) /*const*/ // ����д����
	{
		return acquire(sFileName, iLine);
	}
#else
    int acquire_write (void) /*const*/ // ����д����
	{
		return acquire();
	}
#endif

    
    int release (void) /*const*/ // д�������
    {        
		EnterCriticalSection (&readguard_);
		readcount_ = 0; // ���������
		LeaveCriticalSection (&readguard_);

		SetEvent(tockens_[1]); // ���Ŷ�Ȩ�ޣ���Ҳ���ܽ�ֹд��������ʱ������дȨ�޽�����Դ������
		SetEvent(tockens_[0]); // �����µ�д����Ȩ��

#ifdef DEBUG
		bIsWriting = false;
#endif		

        return 0;       
    }
    
#ifdef DEBUG
    int release_read (char* sFileName, int iLine) // ���������
#else
    int release_read (void) // ���������
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
            SetEvent (tockens_[0]); // ���ж�Ȩ���ͷţ��򿪷�дȨ�ޡ���Ҳ���ܽ�ֹ����������ʱ������дȨ�޽�����Դ������
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
    int release_write (char* sFileName, int iLine) /*const*/ // д�������
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

    int release_write (void) /*const*/ // д�������
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
	HBOOL bIsWriting; // ���Ӵ˳�Ա������ԣ���ʼ��Ϊfalse����ȡ��дȨ��ʱ��true�����ͷ�дȨ�޻�ȡ�ö�Ȩ��ʱ��false��
	HBOOL bIsReading; // ���Ӵ˳�Ա������ԣ���ʼ��Ϊfalse����ȡ�ö�Ȩ��ʱ��true�����ͷŶ�Ȩ�޻�ȡ��дȨ��ʱ��false��
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

template <class T/* ���ݵ����� */, class LOCK = KN_RW_Lock /* ͬ������ */>
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