
#pragma once
#include "Configure.h"
#include "Type.h"
#include "INIFILE.h"

class CYPRESS_DLL_API CSysSetting
{
//private:
public:
	CSysSetting(void);
	~CSysSetting(void);
	CSysSetting(const CSysSetting&) {}
public:
	//static CSysSetting* GetInstance(void);
	//static void ExitInstance(void);
	// 设置时间格式，true：24小时制,false:12小时制
	void SetTimeFormat(HBOOL bFormat = true);
	HBOOL GetTimeFormat(void);

	// 设置数字/模拟时钟，true：数字时钟，false：模拟时钟
	void SetClockType(HBOOL bType = true);
	HBOOL GetClockType(void);

	// 设置背景主题
	void SetTheme(HBYTE nID);
	HBYTE GetTheme(void);

	// 切换语言
	void SetLanguage(HBYTE nID);
	HBYTE GetLanguage(void);

	HBYTE GetRadioType(void);

	HBYTE GetCarType(void);
#ifdef HARDPLATFORM_CLARION
	HString GetThemePath(void);
	void SetThemePath(HString strPath);
#endif // HARDPLATFORM_CLARION
	HINT GetDeviceSizeByDIN(void);	// 用来区分1DIN机和2DIN机
	HBOOL SupportDIVX(void);			// 是否支持DIVX
	HString GetUSBVideoSupportFormat(void);
	HString GetUSBAudioSupportFormat(void);

//private:
public:
	void Save(
		HBYTE nThemeID,
		HBYTE nLangID,
		HBOOL bClockType,
		HBOOL bTimeFormat);

private:
	//CINIFILE*	m_pIniFile;	// 系统配置文件
	HString m_strPath;
	static HINT m_iDeviceSizeByDIN;	// 机身厚度，单位为DIN
	static HINT m_iSupportDIVX;		// 是否支持DIVX
};
