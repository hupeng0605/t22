/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KDebugConsole.h
* ժ    Ҫ: �����ļ�
*
* ��ǰ�汾: 1.0
* ��    ��:  
* �������: 2010-01-22
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1                   2010-01-22             ����
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
