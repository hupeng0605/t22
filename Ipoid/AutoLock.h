//临界区
class MuterEx
{
public:
	MuterEx(void)
	{
		::InitializeCriticalSection(&m_section);
	}
	virtual ~MuterEx(void)
	{
		::DeleteCriticalSection(&m_section);
	}
	void Lock(void)
	{
		wprintf(L"------------LockCriticalSection--------\r\n");
		::EnterCriticalSection(&m_section);
	}
	void UnLock(void)
	{
		::LeaveCriticalSection(&m_section);
		wprintf(L"---------UnLockCriticalSection--------\r\n");
	}
private:
	CRITICAL_SECTION m_section;
};

//自动锁
class AutoLocker
{
public:
	AutoLocker(MuterEx * pLock)
		: m_pLock(pLock)
	{
		if( NULL != m_pLock )
			m_pLock->Lock();
	}
	virtual ~AutoLocker(void)
	{
		if( NULL != m_pLock )
		{
			m_pLock->UnLock();
			m_pLock = NULL;
		}
	}
private:
	MuterEx * m_pLock;
};

static MuterEx g_ReadWriteMuter;	//用于读写线程同步