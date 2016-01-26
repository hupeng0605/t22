/**
* Copyright (C) 2003-2005��            
* All rights reserved.
*
* �ļ����ƣ�Assert.h
* ժ    Ҫ��Camellia��Ŀ�궨�嶨�弰���Թ����ļ�
*
* ��ǰ�汾��1.0
* ��    �ߣ�
* ������ڣ�2005��5��20��
*
* ȡ���汾��0.9
* ԭ �� �ߣ�          
* ������ڣ�2005��4��16��
**/
#ifndef _ASSERT_H_
#define _ASSERT_H_

#include <stdlib.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

//#include <assert.h>
#define assert(X)
#ifndef ASSERT
#define ASSERT(X) assert(X)
#endif

// ��ȫɾ��һ�������delete�ͷŵĶ���
#define SAFE_DELETE(pObject) if((pObject) != NULL) {delete (pObject); (pObject) = NULL;}
// ��ȫɾ��һ�������delete[]�ͷŵĶ���
#define SAFE_DELETE_GROUP(pObject) if((pObject) != NULL) {delete[] (pObject); (pObject) = NULL;}


template<class T>					
inline void DelObj(T& t)							
{
	if ( t != NULL )
	{
		delete	t;
		t = NULL;
	}
	
}//ɾ��ָ�����

template<typename T>				
inline void DelObj(vector<T> &vecData)				
{
	for_each(vecData.begin(), vecData.end(), DelObjPtr<T>());
	vecData.clear();
}//ɾ��vector�е�ָ�����

template<typename K, typename T>	
inline void DelObj(typename map<K, T> &mapData)	
{
	for_each(mapData.begin(), mapData.end(), DelObjObj<K, T>());
	mapData.clear();
}//ɾ��map�е�ָ�����

template<class T>class DelObjPtr
{
public:
	inline void operator()(T& t)
	{
		if ( t != NULL)
		{
			delete	t; 
			t = NULL;
		}
	}
};

template<class K, class T>
class DelObjObj
{
public:
	typedef typename map<K, T>::value_type VT;
	inline void operator()(VT &t)
	{
		delete	t.second;
	}
};

#ifdef _SYSTEMMONITOR
#define MONITOR(sInfo) \
    {\
        IMonitorConsole* pIMonitorConsole = GetMonitorConsoleSinglton();\
        pIMonitorConsole->Record(sInfo);\
    }
#define EXCEPTION() \
    {\
        HCHAR sBuffer[200];\
        swprintf_s(sBuffer, 200, _T("%s(%s) : Error code : %d.\r\n"), __FILE__, __LINE__, GetLastError());\
        MONITOR(sBuffer);\
    }
#else
#define MONITOR(sInfo)
#define EXCEPTION ((void)0)
#endif

#endif // _ASSERT_H_
