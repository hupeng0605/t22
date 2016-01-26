/**
*文件名称：ReadVerUpSetting.h
* 摘    要：
*
* 当前版本：2.0
* 作    者：宿世利
* 创建日期：2012年3月13日
*
* 修改历史：
* [修改序列]   [修改日期]    [修改者]     [修改内容]
*   
* 
**/
#ifndef _READVERUPSETTING_H
#define _READVERUPSETTING_H
#include<Windows.h>

//A表示A文件夹路径，B表示B文件夹路径

#define APP_FOLDER_A   _T("\\EMMC\\APPA")
#define APP_FOLDER_B   _T("\\EMMC\\APPB")

//配置文件路径
#define APP_CONFIG     _T("emmc\\AppSetting.bin")

//标志位为0表示升级未完成，1表示完成
enum
{
	UPDATE_BEGIN = 0,
	UPDATE_END = 1
};

enum 
{
	APP_START_A = 0,       //从A目录启动
	APP_START_B = 1        //从B目录启动
};

class CReadVerUpSetting
{
public:
	CReadVerUpSetting(void);
	~CReadVerUpSetting(void);

	//单例模式
	static CReadVerUpSetting* GetInstance();
	static void ReleaseInstance();

	//读配置文件函数
	UINT8 ReadPowerVerUpFlag();
	UINT8 ReadNKVerUpFlag();
	UINT8 ReadAPPVerUpFlag();
	UINT8 ReadDVDVerUpFlag();
	UINT8 ReadBTVerUpFlag();
	UINT8 ReadFolderFlag();
	BOOL ReadSettingInfo(UINT8 &ucPowerVerUpFlag,UINT8 &ucNKVerUpFlag,UINT8 &ucAPPVerUpFlag,UINT8 &ucDVDVerUpFlag,UINT8 &ucBTVerUpFlag,UINT8 &ucFoldFlag);
    
	//写配置文件函数
	BOOL WritePowerVerUpFlag(UINT8 ucPowerVerUpFlag);
	BOOL WriteNKVerUpFlag(UINT8 ucNKVerUpFlag);
	BOOL WriteAPPVerUpFlag(UINT8 ucAPPVerUpFlag);
	BOOL WriteDVDVerUpFlag(UINT8 ucDVDVerUpFlag);
	BOOL WriteBTVerUpFlag(UINT8 ucBTVerUpFlag);
	BOOL WriteFolderFlag(UINT8 ucFoldFlag);
    BOOL WriteSettingInfo(UINT8 ucPowerVerUpFlag,UINT8 ucNKVerUpFlag,UINT8 ucAPPVerUpFlag,UINT8 ucDVDVerUpFlag,UINT8 ucBTVerUpFlag,UINT8 ucFoldFlag);

protected:
    //解析从配置文件中读取的数据
	BOOL GetConfigValueByString(TCHAR*pString,UINT8 &ucPowerVerUpFlag,UINT8 &ucNKVerUpFlag,UINT8 &ucAPPVerUpFlag,UINT8 &ucDVDVerUpFlag,UINT8 &ucBTVerUpFlag,UINT8 &ucFoldFlag);
	
private:
	static CReadVerUpSetting* m_pReadVerUpSetting;

};
#endif //_READVERUPSETTING_H