/**
* Copyright (C) 2003-2006，            
* All rights reserved.
*
* 文件名称：PubHead.h
* 摘    要：Camellia项目公共头文件
*
* 当前版本：0.9
* 作    者：     
* 完成日期：2006年1月8日
*
* 取代版本：0.8
* 原 作 者：          
* 完成日期：2005年4月28日
**/
#ifndef _PUBHEAD_H__
#define _PUBHEAD_H__

#pragma warning(disable : 4786)
//#pragma warning(disable : 4251)

#include "Platform.h"
#include "Configure.h"
#include "Assert.h"
#include "Type.h"
//#include "KNFile.h"

#define Interface struct

#define IN
#define OUT
#define INOUT

#define KNAPI

#define MAX_FILEPATH_LEN 256
#define MAX_FILEPATH_LENGTH 256

UICORE_DLL_API void SetDataPath(IN const HCHAR *path);
UICORE_DLL_API const HCHAR* GetDataPath(void);
UICORE_DLL_API void GetFilePath(INOUT HString& strPath);
UICORE_DLL_API void GetPath(const HCHAR *allpath, HCHAR *path);

UICORE_DLL_API void SetDlgConfigPath(IN const HCHAR *path);
UICORE_DLL_API const HCHAR* GetDlgConfigPath(void);

UICORE_DLL_API void SetResourceFile(const HCHAR *name);
UICORE_DLL_API const HCHAR* GetResourceFile(void);

UICORE_DLL_API void SetCurrentPath(IN const HCHAR *path);
UICORE_DLL_API const HCHAR*  GetCurrentPath();
#endif //_PUBHEAD_H__