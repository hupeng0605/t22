#ifndef _PLATFORM_H__
#define _PLATFORM_H__

#define _LINUX_PLATFORM     0x01
#define _WIN32_PLATFORM     0x02
#define _WINCE_PLATFORM     0x03

// OS Platform
#if defined(_WINDOWS)
#if defined(_WIN32_WCE)
#define _CURRENT_PLATFORM _WINCE_PLATFORM
#else
#define _CURRENT_PLATFORM _WIN32_PLATFORM
#endif

#ifndef WIN32
#define WIN32
#endif
#else
#define _CURRENT_PLATFORM _LINUX_PLATFORM
#endif

// C++ Compiler
#if   _CURRENT_PLATFORM == _LINUX_PLATFORM
//#include "Linux.h"
#ifndef KOTEI_GCC
#define KOTEI_GCC
#endif
#elif _CURRENT_PLATFORM == _WIN32_PLATFORM
#include "Windows.h"
#include <TCHAR.h>
#ifndef KOTEI_VC
#define KOTEI_VC
#endif
#elif _CURRENT_PLATFORM == _WINCE_PLATFORM
#include "Windows.h"
#include <TCHAR.h>
#ifndef KOTEI_EVC
#define KOTEI_EVC
#endif
#endif

#endif // _PLATFORM_H__