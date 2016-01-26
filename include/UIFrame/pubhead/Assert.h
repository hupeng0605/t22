/**
* Copyright (C) 2003-2005，            
* All rights reserved.
*
* 文件名称：Assert.h
* 摘    要：Camellia项目宏定义定义及调试工具文件
*
* 当前版本：1.0
* 作    者：
* 完成日期：2005年5月20日
*
* 取代版本：0.9
* 原 作 者：          
* 完成日期：2005年4月16日
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

// 安全删除一个需调用delete释放的对象
#define SAFE_DELETE(pObject) if((pObject) != NULL) {delete (pObject); (pObject) = NULL;}
// 安全删除一组需调用delete[]释放的对象
#define SAFE_DELETE_GROUP(pObject) if((pObject) != NULL) {delete[] (pObject); (pObject) = NULL;}


template<class T>					
inline void DelObj(T& t)							
{
	if ( t != NULL )
	{
		delete	t;
		t = NULL;
	}
	
}//删除指针对象

template<typename T>				
inline void DelObj(vector<T> &vecData)				
{
	for_each(vecData.begin(), vecData.end(), DelObjPtr<T>());
	vecData.clear();
}//删除vector中的指针对象

template<typename K, typename T>	
inline void DelObj(typename map<K, T> &mapData)	
{
	for_each(mapData.begin(), mapData.end(), DelObjObj<K, T>());
	mapData.clear();
}//删除map中的指针对象

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
