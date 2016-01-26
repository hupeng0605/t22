#include "radiocore.h"



Mutex::Mutex()
{
	InitializeCriticalSection(&m_mutex);
}

Mutex::~Mutex()
{
	DeleteCriticalSection(&m_mutex);
}

int Mutex::Acquire()
{
	EnterCriticalSection(&m_mutex); return 0; 
}

int Mutex::Release()
{
	LeaveCriticalSection(&m_mutex); return 0;
}

ScopeMutex::ScopeMutex( Mutex& mutex )
: m_mutex(mutex)
{
	m_mutex.Acquire();
}

ScopeMutex::~ScopeMutex()
{
	m_mutex.Release();
}

Condition::Condition()
{
	m_nWaitCount = 0;
	m_nReleaseCount = 0;
	m_nGenerationCount = 0;
	m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
}

Condition::~Condition()
{
	CloseHandle(m_hEvent);
	m_hEvent = INVALID_HANDLE_VALUE;
}

int Condition::Wait( Mutex& mutex )
{
	m_WaitCountMutex.Acquire();
	m_nWaitCount++;
	int nGeneration = m_nGenerationCount;
	m_WaitCountMutex.Release();

	mutex.Release();

	for(; ;)
	{
		//printf("for wait...\n");

		WaitForSingleObject(m_hEvent, INFINITE);

		m_WaitCountMutex.Acquire();
		//printf("m_nReleaseCount == %d m_nGenerationCount == %d nGeneration == %d\n", m_nReleaseCount, m_nGenerationCount, nGeneration);
		int nWaitDone = (m_nReleaseCount > 0 && m_nGenerationCount != nGeneration);
		m_WaitCountMutex.Release();

		if(nWaitDone) break;
	}

	//xlib_debug_info(_T("for wait end...\n"));

	mutex.Acquire();
	m_WaitCountMutex.Acquire();
	m_nWaitCount--;
	m_nReleaseCount--;
	int nLastWait = m_nReleaseCount == 0;
	m_WaitCountMutex.Release();

	if(nLastWait) ResetEvent(m_hEvent);

	return 0;
}

int Condition::Signal()
{
	ScopeMutex lock(m_WaitCountMutex);
	if(m_nWaitCount > m_nReleaseCount)
	{
		SetEvent(m_hEvent);
		m_nReleaseCount++;
		m_nGenerationCount++;
	}
	return 0;
}

int Condition::Broadcast()
{
	ScopeMutex lock(m_WaitCountMutex);
	//printf("m_nWaitCount == %d\n", m_nWaitCount);
	if(m_nWaitCount > 0)
	{
		SetEvent(m_hEvent);
		m_nReleaseCount = m_nWaitCount;
		m_nGenerationCount++;
	}
	return 0;
}

inline void RADIODEBUGINFO(const wchar_t* wcsFormat, ... )
{
#if RADIODEBEGINFOSTATE
	va_list     va;
	static wchar_t	buffer[1024] = {0};
	memset(buffer,0,sizeof(buffer) );
	va_start( va, wcsFormat );
	_vsnwprintf_s( buffer,1024, 1024 - 1, wcsFormat, va );
	va_end( va );

	//swprintf_s(buffer, 1024 -1, L"%d [USB] : %s", ::GetTickCount(), buffer);
	wprintf(L"\r\n%d [Radio] : %s\r\n", ::GetTickCount(), buffer);
#else
#endif
	//OutputDebugString(buffer);
}