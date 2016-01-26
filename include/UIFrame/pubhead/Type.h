#ifndef _TYPE_H__
#define _TYPE_H__

#include "Platform.h"
#include <stdio.h>
#include <string>
using namespace std;

#pragma warning(disable: 4251)

typedef unsigned int    HUINT;
typedef unsigned short  HUSHORT;
typedef unsigned long   HULONG;

typedef unsigned char   HBYTE;
typedef int             HINT;
typedef short           HSHORT;
typedef long            HLONG;
typedef float           HFLOAT;
typedef double          HDOUBLE;
typedef bool            HBOOL;

typedef unsigned short  HWORD;
typedef unsigned long   HDWORD;

typedef void*           HANDLE;

#ifdef WIN32
#include "Windows.h"
typedef HWND        HWND;
#endif // WIN32

#ifdef _UNICODE
#ifdef WIN32
typedef wchar_t      HCHAR;
#else
typedef unsigned int HUINT;
#endif // WIN32
#else
typedef char             HCHAR;
#endif  // _UNICODE

typedef basic_string<HCHAR> HString;

#ifndef KN_HMI_LIB
#ifdef UICORE_DLL_EXPORTS
#define UICORE_DLL_API __declspec(dllexport)
#else
#define UICORE_DLL_API __declspec(dllimport)
#endif
#else
#define UICORE_DLL_API
#endif

typedef struct _kn_rect
{
    HINT    left;
    HINT    top;
    HINT    right;
    HINT    bottom;
    _kn_rect()
    {
        this->left = 0;
        this->top = 0;
        this->right = 0;
        this->bottom = 0;
    }
    _kn_rect(HINT left, HINT top, HINT right, HINT bottom)
    {
//      assert(left <= right && top <= bottom);
        this->left = left;
        this->top = top;
        this->right = right;
        this->bottom = bottom;
    }
    HBOOL operator==(_kn_rect& rect)
    {
        if (rect.left == this->left &&
            rect.right == this->right &&
            rect.top == this->top &&
            rect.bottom == this->bottom)
        {
            return true;
        }

        return false;
    }
    HBOOL operator!=(_kn_rect& rect)
    {
        return  rect.left != this->left ||
                rect.right != this->right ||
                rect.top != this->top ||
                rect.bottom != this->bottom;

    }
    void set(HINT left, HINT top, HINT right, HINT bottom)
    {
//      assert(left <= right && top <= bottom);
        this->left = left;
        this->top = top;
        this->right = right;
        this->bottom = bottom;
    }
    inline HINT width()
    {
        return right - left;
    }
    inline HINT height()
    {
        return bottom - top;
    }
} kn_rect;

#endif// _TYPE_H__
