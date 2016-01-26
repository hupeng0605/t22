/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KDebugConsole.h
* 摘    要: 调试文件
*
* 当前版本: 1.0
* 作    者:  
* 完成日期: 2010-01-22
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*   1                   2010-01-22             创建
*
**/

#pragma once


#ifdef CONSOLE
#undef CONSOLE
#endif

#ifdef _DEBUG
#include "HMIDev.h"
#define CONSOLE PostDebugMessageToSever
#else
#define CONSOLE(...)
#endif
