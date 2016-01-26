

#pragma once
#include "Configure.h"
#include "Type.h"
#include "INIFILE.h"

// ���е����ƺ�λ��
typedef struct tagCityInfo_
{
	HString name;
	HINT nLongitude;
	HINT nLatitude;
}CityInfo;

class CYPRESS_DLL_API CCityPostion
{
public:
	CCityPostion(void);
	CCityPostion(const HCHAR* strPath);
	CCityPostion(const HString& strPath);
	~CCityPostion(void);

public:
	void SetWeatherConfigFile(const HCHAR* strPath);
	void SetWeatherConfigFile(const HString& strPath);

	HINT GetCountryList(OUT vector<HString>& vecCountryList);
	HINT GetCityList(IN const HCHAR* strCountryName,OUT vector<HString>& vecCityList);
	HBOOL GetCityPostion(IN const HCHAR* strCountryName,IN const HCHAR* strCityName,OUT HINT& nLongitude, OUT HINT& nLatitude);

	HINT GetCityList(IN const HCHAR* strCountryName,OUT vector<CityInfo *>& vecCityList);

private:
	CINIFILE*	m_pIniFile;	// RSS�����ļ�
	//kn_string m_strConfigFilePath;
};
