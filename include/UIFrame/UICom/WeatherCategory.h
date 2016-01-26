

#pragma once
#include "Configure.h"
#include "Type.h"
#include "INIFILE.h"



class CYPRESS_DLL_API CWeatherCategory
{
public:
	CWeatherCategory(void);
	~CWeatherCategory(void);
	CWeatherCategory(const CWeatherCategory&) {}
public:
	/*static CWeatherCategory* GetInstance(void);*/
	//static void ExitInstance(void);
	HBOOL GetConditionImage(IN const HString& strConditionName,
							OUT HString& strNormalIcon,
							OUT HString& strSmallIcon);
private:
	CINIFILE*	m_pIniFile;	// RSS≈‰÷√Œƒº˛
};
