#include "CommandPool.h"
CCommandPool * CCommandPool::s_pCCommandPool = NULL;
CCommandPool* CCommandPool::Intance()
{
	if(s_pCCommandPool == NULL)
	{
		s_pCCommandPool = new CCommandPool;
	}
	return s_pCCommandPool;
}
void CCommandPool::DeleteIntance()
{
	if(s_pCCommandPool != NULL)
	{
		delete(s_pCCommandPool);
	}
}
CCommandPool::~CCommandPool()
{
	Block *p1 = NULL;
	Block *p2 = NULL; 
	if(m_pHead != NULL)
	{
		p1 = m_pHead->pUsed;
		while(p1 != NULL)
		{
			p2 = p1->pNext;
			delete(p1);
			m_pHead->nTotal--;
			p1 = p2;
		}
		p1 = m_pHead->pFree;
		while(p1 != NULL)
		{
			p2 = p1->pNext;
			delete(p1);
			m_pHead->nTotal--;
			m_pHead->nTotalFree--;
			p1 = p2;
		}
	}
}
Block* CCommandPool::PoolNew( )
{
	char *pc = NULL;
	Block *pNew = NULL;
	if(m_pHead != NULL)
	{
		if(m_pHead->pFree == NULL)
		{
			pc = new char[sizeof(Block) + sizeof(sCommandData)];
			pNew = (Block*)pc;
			pNew->pNext = NULL;
			m_pHead->nTotal++;
			//cout<<"TotalFree = "<<m_pHead->nTotalFree<<"    Total = "<<m_pHead->nTotal<<endl;
			BTDEBUGINFO(L"Pool:%s:TotalFree = %d,Total = %d",__FUNCTIONW__,m_pHead->nTotalFree,m_pHead->nTotal);
		}
		else
		{
			pNew = m_pHead->pFree;
			m_pHead->nTotalFree--;
			if(pNew->pNext == NULL)
			{
				m_pHead->pFree = NULL;
			}
			else
			{
				m_pHead->pFree = pNew->pNext;
			}
			BTDEBUGINFO(L"Pool:%s:TotalFree = %d,Total = %d",__FUNCTIONW__,m_pHead->nTotalFree,m_pHead->nTotal);
			//cout<<"TotalFree = "<<m_pHead->nTotalFree<<"    Total = "<<m_pHead->nTotal<<endl;
		}
		if(pNew != NULL)
		{
			Block *p = m_pHead->pUsed;
			if(p == NULL)
			{
				m_pHead->pUsed = pNew;
				pNew->pNext = NULL;
			}
			else
			{
				pNew->pNext = p;
				m_pHead->pUsed = pNew;
			}
		}
	}
	//cout<<(int)pNew<<endl;
	return pNew;
}
void CCommandPool::PoolDelete(Block *pBlock)
{
	if(pBlock != NULL && m_pHead != NULL)
	{
		bool res = IsBlockUsed(pBlock);
		if(res)
		{
			Block *p = m_pHead->pUsed;
			if(p == pBlock)
			{
				m_pHead->pUsed = p->pNext;
			}
			else
			{
				while(p->pNext != NULL && p->pNext != pBlock)
				{
					p = p->pNext;
				}
				if(p != NULL)
				{
					p->pNext = pBlock->pNext;
				}
			}
			if(m_pHead->pFree == NULL)
			{
				m_pHead->pFree = pBlock;
				pBlock->pNext = NULL;
			}
			else
			{
				pBlock->pNext = m_pHead->pFree;
				m_pHead->pFree = pBlock;

			}
			m_pHead->nTotalFree++;	
			//cout<<"TotalFree = "<<m_pHead->nTotalFree<<"        Total = "<<m_pHead->nTotal<<endl;
		}
		BTDEBUGINFO(L"Pool:%s:TotalFree = %d,Total = %d",__FUNCTIONW__,m_pHead->nTotalFree,m_pHead->nTotal);
	}
}
CCommandPool::CCommandPool()
{
	m_pHead = new BTCMDList;
	m_pHead->nBlockSize = sizeof(sCommandData);
	m_pHead->pUsed = NULL;
	m_pHead->pFree = NULL;
	m_pHead->nTotalFree = 0;
	m_pHead->nTotal = 0;
}
bool CCommandPool::IsBlockUsed(Block *pBlock)
{
	if(m_pHead != NULL && pBlock != NULL)
	{
		Block *p = m_pHead->pUsed;
		while(p != NULL)
		{
			if(p == pBlock)
			{
				return true;
			}
			p = p->pNext;
		}
	}
	return false;
}