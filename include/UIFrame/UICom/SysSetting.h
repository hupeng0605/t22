
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
	// ����ʱ���ʽ��true��24Сʱ��,false:12Сʱ��
	void SetTimeFormat(HBOOL bFormat = true);
	HBOOL GetTimeFormat(void);

	// ��������/ģ��ʱ�ӣ�true������ʱ�ӣ�false��ģ��ʱ��
	void SetClockType(HBOOL bType = true);
	HBOOL GetClockType(void);

	// ���ñ�������
	void SetTheme(HBYTE nID);
	HBYTE GetTheme(void);

	// �л�����
	void SetLanguage(HBYTE nID);
	HBYTE GetLanguage(void);

	HBYTE GetRadioType(void);

	HBYTE GetCarType(void);
#ifdef HARDPLATFORM_CLARION
	HString GetThemePath(void);
	void SetThemePath(HString strPath);
#endif // HARDPLATFORM_CLARION
	HINT GetDeviceSizeByDIN(void);	// ��������1DIN����2DIN��
	HBOOL SupportDIVX(void);			// �Ƿ�֧��DIVX
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
	//CINIFILE*	m_pIniFile;	// ϵͳ�����ļ�
	HString m_strPath;
	static HINT m_iDeviceSizeByDIN;	// �����ȣ���λΪDIN
	static HINT m_iSupportDIVX;		// �Ƿ�֧��DIVX
};
