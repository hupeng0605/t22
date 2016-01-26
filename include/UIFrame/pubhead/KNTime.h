

#ifndef _KNTIME_H__
#define _KNTIME_H__

#include "Platform.h"
#include "Assert.h"
#ifdef WIN32
	#include "Windows.h"
#endif

// ADD. hzf.2006.11.7.
// --Begin

//lint -e734 -e520

// --End

class HTime
{
public:
	// Get the local time of system using API.
	static HTime GetCurrentTime()
	{
	#ifdef WIN32
		SYSTEMTIME localtime;
		::GetLocalTime(&localtime);
		return HTime(localtime.wYear, localtime.wMonth, localtime.wDay, localtime.wHour, localtime.wMinute, localtime.wSecond);
	#else
		return HTime(0);
	#endif // WIN32
	}

	// Set the local time to system using API.
	static bool SetCurrentTime(const HTime& time)
	{
	#ifdef WIN32
		SYSTEMTIME localtime;
		localtime.wSecond = time.GetSecond();
		localtime.wMinute = time.GetMinute();
		localtime.wHour = time.GetHour();
		localtime.wDay = time.GetDay();
		localtime.wMonth = time.GetMonth();
		localtime.wYear = time.GetYear();
		if (::SetLocalTime(&localtime) != 0)
			return true;
		else
			return false;
	#else
		return false;
	#endif // WIN32
	}

	// Get the number of milliseconds that have elapsed since the system was started.
	static unsigned long GetElapsedMSec(void)
	{
		unsigned long ulTickCount = 0;
	#ifdef WIN32
		ulTickCount = ::GetTickCount();
	#else
		//ulTickCount = 0;
	#endif
		return ulTickCount;
	}
	
public:
	HTime(const unsigned long ulSeconds = 0)
	{
		m_ulTotalSeconds = ulSeconds;
	}
	
	HTime(const int iYear,   const int iMonth,    const int iDay, 
			const int iHour=0, const int iMinute=0, const int iSecond=0)
	{
		assert(iYear >= 1970  &&  iYear <= 2106);
		assert(iMonth > 0  &&  iMonth <= 12);
		assert(iDay > 0  &&  iDay <= 31);
		assert(iHour >= 0  &&  iHour < 24);
		assert(iMinute >= 0  &&  iHour < 60);
		assert(iSecond >= 0  &&  iHour < 60);
		
		const int iDaysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		unsigned long ulTotalSeconds = 0;
		
		// Year
		int i = 1970;
		for (; i < iYear; i++)
		{
			if (IsLeapYear(i))
				ulTotalSeconds += 366 * 24 * 3600;
			else
				ulTotalSeconds += 365 * 24 * 3600;
		}
		
		// Month
// 		i = 2;
		// UPDATE.2007.4.8.hzf
		// --Begin
		i = 1;
		// --End
		for (i; i < iMonth; i++)
		{
			if (IsLeapYear(iYear)  &&  (i == 2))
				ulTotalSeconds += (iDaysInMonth[i-1]+1) * 24 * 3600;
			else
				ulTotalSeconds += iDaysInMonth[i-1] * 24 * 3600;
		}
		
		// Day
		ulTotalSeconds += (iDay-1) * 24 * 3600;
		
		// Hour
		ulTotalSeconds += (iHour) * 3600;
		
		// Minute
		ulTotalSeconds += (iMinute) * 60;
		
		// Second
		ulTotalSeconds += iSecond;
		
		m_ulTotalSeconds = ulTotalSeconds;
	}
	
	~HTime()
	{
		m_ulTotalSeconds = 0;
	}

public:
	void Clear()
	{
		m_ulTotalSeconds = 0;
	}
	
	int GetYear() const
	{
		int iYear = 1970;
		unsigned long ulYearBeginSeconds = 0;
		unsigned long ulYearEndSeconds = 0;
		
		for (; iYear <= 2106; iYear++)
		{
			if (IsLeapYear(iYear))
			{
				// Leap year
				ulYearBeginSeconds = ulYearEndSeconds;
				ulYearEndSeconds += 366 * 24 * 3600;
			}
			else
			{
				// Non-leap year
				ulYearBeginSeconds = ulYearEndSeconds;
				ulYearEndSeconds += 365 * 24 * 3600;
			}
			
			if (m_ulTotalSeconds < ulYearEndSeconds  &&  m_ulTotalSeconds >= ulYearBeginSeconds)
				break;
		}
		return iYear;
	}
	
	int GetMonth() const
	{
		const int iDaysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		unsigned long ulMonthBeginSeconds = 0;
		unsigned long ulMonthEndSeconds = 0;
		int iMonth = 1;
		
		HTime tYearBegin(GetYear(), 1, 1);
		unsigned long ulRemainSeconds = m_ulTotalSeconds - tYearBegin.GetTotalSeconds();
		
		for (; iMonth <= 12; iMonth++)
		{
			ulMonthBeginSeconds = ulMonthEndSeconds;
			if (iMonth ==2  && IsLeapYear())
				ulMonthEndSeconds += (iDaysInMonth[iMonth-1]+1) * 24 * 3600;		
			else
				ulMonthEndSeconds += iDaysInMonth[iMonth-1] * 24 * 3600;
			
			if (ulRemainSeconds < ulMonthEndSeconds  &&  ulRemainSeconds >= ulMonthBeginSeconds)
				break;
		}
		
		return iMonth;
	}
	
	int GetDay() const
	{
		const int iDaysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		HTime tMonthBegin(GetYear(), GetMonth(), 1);
		unsigned long ulRemainSeconds = m_ulTotalSeconds - tMonthBegin.GetTotalSeconds();
		
		int iDay = ulRemainSeconds / (24 * 3600) + 1;
		
		return iDay;
	}
	
	int GetDayOfWeek() const
	{
		const int iDayOfWeek19700101 = 4;
		
		int iDayOfWeek = (GetTotalDays()+ iDayOfWeek19700101) % 7;
		
		return iDayOfWeek;
	}
	
	int GetHour() const
	{
		HTime tDayBegin(GetYear(), GetMonth(), GetDay());
		unsigned long ulRemainSeconds = m_ulTotalSeconds - tDayBegin.GetTotalSeconds();
		
		int iHour = ulRemainSeconds / 3600;
		
		return iHour;
	}
	
	int GetMinute() const
	{
		HTime tHourBegin(GetYear(), GetMonth(), GetDay(), GetHour());
		unsigned long ulRemainSeconds = m_ulTotalSeconds - tHourBegin.GetTotalSeconds();
		
		int iMinute = ulRemainSeconds / 60;
		
		return iMinute;
	}
	
	int GetSecond() const
	{
		return m_ulTotalSeconds % 60;
	}
	
	unsigned long GetTotalYears() const
	{
		return GetYear() - 1970;
	}
	
	unsigned long GetTotalMonths() const
	{
		return GetTotalYears() * 12 + GetMonth();
	}
	
	unsigned long GetTotalDays() const
	{
		return m_ulTotalSeconds / (24 * 3600);
	}
	
	unsigned long GetTotalHours() const
	{
		return m_ulTotalSeconds / 3600;
	}
	
	unsigned long GetTotalMinutes() const
	{
		return m_ulTotalSeconds / 60;
	}
	
	unsigned long GetTotalSeconds() const
	{
		return m_ulTotalSeconds;
	}
	
	bool IsLeapYear() const
	{
		return IsLeapYear(GetYear());
	}
	
	bool operator==(const HTime& time) const
	{
		return (time.GetTotalSeconds() == m_ulTotalSeconds);
	}

	bool operator!=(const HTime& time) const
	{
		return (time.GetTotalSeconds() != m_ulTotalSeconds);
	}
	
	bool operator<(const HTime& time) const
	{
		return (time.GetTotalSeconds() < m_ulTotalSeconds);
	}

	bool operator<=(const HTime& time) const
	{
		return (time.GetTotalSeconds() <= m_ulTotalSeconds);
	}

	bool operator>(const HTime& time) const
	{
		return (time.GetTotalSeconds() > m_ulTotalSeconds);
	}

	bool operator>=(const HTime& time) const
	{
		return (time.GetTotalSeconds() >= m_ulTotalSeconds);
	}
	
	HTime operator+(const HTime& time) const
	{
		unsigned long ulTSec = m_ulTotalSeconds + time.GetTotalSeconds();
		HTime retTime(ulTSec);
		return retTime;
	}

	HTime& operator+=(const HTime& time)
	{
		m_ulTotalSeconds += time.GetTotalSeconds();
		return *this;
	}
	
	HTime operator-(const HTime& time) const
	{
		unsigned long ulTSec = m_ulTotalSeconds - time.GetTotalSeconds();
		HTime retTime(ulTSec);
		return retTime;
	}

	HTime& operator-=(const HTime& time)
	{
		m_ulTotalSeconds -= time.GetTotalSeconds();
		return *this;
	}

	HTime& operator=(const HTime& time)
	{
		// ADD. hzf.2006.11.7.
		// --Begin
		if (&time == this)
		{
			return *this;
		}
		// --End

		m_ulTotalSeconds = time.GetTotalSeconds();
		return *this;
	}

	operator unsigned long() const
	{
		return m_ulTotalSeconds;
	}

protected:
	bool IsLeapYear(const int iYear) const
	{
		if ( (iYear % 4 == 0  &&  iYear % 100 != 0)  ||  (iYear % 400 == 0) )
		{
			// Leap year
			return true;
		}
		else
		{
			// Non-Leap year
			return false;
		}
	}

	// Elapsed seconds since midnight(00:00:00), January 1, 1970.
	unsigned long m_ulTotalSeconds;
};


// ADD. hzf.2006.11.7.
// --Begin

//lint +e734 +e520
// --End

#endif // _KNTIME_H__