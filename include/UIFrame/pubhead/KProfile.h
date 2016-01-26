#ifndef _KPROFILE_H__
#define _KPROFILE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Pubhead.h"
#include <stdlib.h>
#include <stdio.h>

class UICORE_DLL_API HProfile
{
public:
    HProfile();
    virtual ~HProfile();

    int Open(const HString& strFilename);
    void Close(void);

    int Reset();
    int Mark();
    int Back();

    int GetSection(const char *key);
    int GetString(const char *key, char *buff, int count);
    int GetValue(const char *key, int &value);
    int GetValue(const char *key, double &value);

    static void Split(const char *buff, ...);

protected:
    int GetLine(char *buff, int count);
    int strnicmp2(const char *str1, const char *str2, int count) const;

    FILE *m_file;
    unsigned int m_mark;
};

#endif // _KPROFILE_H__
