//#define MAXCMDLEN 100
#pragma once
#include "define.h"
class CCommandPool
{
public:
	static CCommandPool* Intance();
	static void DeleteIntance();
	virtual ~CCommandPool();
	//List *FoundList(HINT nBytes);
	Block *PoolNew();
	void PoolDelete(Block *pBlock);
	bool IsBlockUsed(Block *pBlock);
private:
	CCommandPool();
	static CCommandPool* s_pCCommandPool;
	BTCMDList *m_pHead;
};
