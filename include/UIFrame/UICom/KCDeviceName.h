

#pragma once
#include "Configure.h"
#include "Type.h"
#include "INIFILE.h"


class CYPRESS_DLL_API KCDeviceName
{
public:
	KCDeviceName(void);
	~KCDeviceName(void);

public:
	HString GetHDDPath(void);
	HString GetSDPath(void);
	HString GetUSBPath(void);
	HString GetiPodPath(void);
	HBOOL		IsUSBExist(void);
	HBOOL		IsSDExist(void);
	HBOOL		IsHDDExist(void);
	HBOOL		IsIPodExist(void);

private:
	HBOOL		IsDeviceExist(HCHAR	*pStrDevice);
	HBOOL		IsDeviceExist(const HString&	strDevice);
private:
	CINIFILE*	m_pIniFile;	// RSS≈‰÷√Œƒº˛
};
