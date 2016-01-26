#pragma once
#include <Windows.h>
#include <string>
using namespace std;
#define  IPODDEBEGINFOSTATE  0
extern inline void IPODDEBEGINFO(const wchar_t* wcsFormat, ... );
class Mutex
{
public:
	Mutex();
	~Mutex();
	int Acquire();
	int Release();
private:
	CRITICAL_SECTION	m_mutex;
};

class ScopeMutex
{
public:
	ScopeMutex(Mutex& mutex);
	~ScopeMutex();
private:
	Mutex&		m_mutex;
};

class Condition
{
public:
	Condition();
	~Condition();
	int Wait(Mutex& mutex);
	int Signal();
	int Broadcast();
private:
	int m_nWaitCount;
	int m_nReleaseCount;
	int m_nGenerationCount;
	Mutex m_WaitCountMutex;
	HANDLE m_hEvent;
};

wstring GetBTAddrStr(BYTE* pbAddr,int nAddrLen);