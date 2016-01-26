/********************************************************************
created:    2006/12/04
created:    4:12:2006   11:28
filename:
file path:
file base:  SystemTime
file ext:   h
author:       

purpose:
*********************************************************************/
#pragma once

#include "Configure.h"
#include "Type.h"


class CYPRESS_DLL_API CSystemTime
{
public:
    CSystemTime(void);
    ~CSystemTime(void);

public:
    void SetSysTime(HUSHORT nHour, HUSHORT nMin);
    HString GetDateString(HString a_strFormat);
    HString GetTimeString(HBOOL a_b24Format, HBOOL bTimeOnly=TRUE, HString a_strFormat = _T("hh:mm"));
    HString GetWeek(void);
    void UpdateTime(void);
    HString GetHourString(HBOOL a_b24Format, HString a_strFormat = _T("hh"));
    HString GetMinString(HString a_strFormat = _T("mm"));
    HUSHORT GetYear(void)
    {
        return m_tSysTime.wYear;
    }
    HUSHORT GetMonth(void)
    {
        return m_tSysTime.wMonth;
    }
    HUSHORT GetDay(void)
    {
        return m_tSysTime.wDay;
    }
    HUSHORT GetHour(void)
    {
        return m_tSysTime.wHour;
    }
    HUSHORT GetMinute(void)
    {
        return m_tSysTime.wMinute;
    }
    HUSHORT GetSecond(void)
    {
        return m_tSysTime.wSecond;
    }
    HUSHORT GetDayOfWeek(void)
    {
        return m_tSysTime.wDayOfWeek;
    }
    HINT GetTimeDiff(void);
    HString GetHourString(void);
    HString GetMinuteString(void);
    static HString Int2Str(HINT a_nVal);
    static HINT Str2Int(const HString& a_strInput);
    static HLONG GetMinutes(const SYSTEMTIME& time);
    void SetSysDate(HUSHORT nYear, HUSHORT nMonth, HUSHORT nDay);
private:
    SYSTEMTIME  m_tSysTime; // 系统时间
    TIME_ZONE_INFORMATION m_tZoneInfo;// 用于获取时差
};
