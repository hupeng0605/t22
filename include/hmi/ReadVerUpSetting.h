/**
*�ļ����ƣ�ReadVerUpSetting.h
* ժ    Ҫ��
*
* ��ǰ�汾��2.0
* ��    �ߣ�������
* �������ڣ�2012��3��13��
*
* �޸���ʷ��
* [�޸�����]   [�޸�����]    [�޸���]     [�޸�����]
*   
* 
**/
#ifndef _READVERUPSETTING_H
#define _READVERUPSETTING_H
#include<Windows.h>

//A��ʾA�ļ���·����B��ʾB�ļ���·��

#define APP_FOLDER_A   _T("\\EMMC\\APPA")
#define APP_FOLDER_B   _T("\\EMMC\\APPB")

//�����ļ�·��
#define APP_CONFIG     _T("emmc\\AppSetting.bin")

//��־λΪ0��ʾ����δ��ɣ�1��ʾ���
enum
{
	UPDATE_BEGIN = 0,
	UPDATE_END = 1
};

enum 
{
	APP_START_A = 0,       //��AĿ¼����
	APP_START_B = 1        //��BĿ¼����
};

class CReadVerUpSetting
{
public:
	CReadVerUpSetting(void);
	~CReadVerUpSetting(void);

	//����ģʽ
	static CReadVerUpSetting* GetInstance();
	static void ReleaseInstance();

	//�������ļ�����
	UINT8 ReadPowerVerUpFlag();
	UINT8 ReadNKVerUpFlag();
	UINT8 ReadAPPVerUpFlag();
	UINT8 ReadDVDVerUpFlag();
	UINT8 ReadBTVerUpFlag();
	UINT8 ReadFolderFlag();
	BOOL ReadSettingInfo(UINT8 &ucPowerVerUpFlag,UINT8 &ucNKVerUpFlag,UINT8 &ucAPPVerUpFlag,UINT8 &ucDVDVerUpFlag,UINT8 &ucBTVerUpFlag,UINT8 &ucFoldFlag);
    
	//д�����ļ�����
	BOOL WritePowerVerUpFlag(UINT8 ucPowerVerUpFlag);
	BOOL WriteNKVerUpFlag(UINT8 ucNKVerUpFlag);
	BOOL WriteAPPVerUpFlag(UINT8 ucAPPVerUpFlag);
	BOOL WriteDVDVerUpFlag(UINT8 ucDVDVerUpFlag);
	BOOL WriteBTVerUpFlag(UINT8 ucBTVerUpFlag);
	BOOL WriteFolderFlag(UINT8 ucFoldFlag);
    BOOL WriteSettingInfo(UINT8 ucPowerVerUpFlag,UINT8 ucNKVerUpFlag,UINT8 ucAPPVerUpFlag,UINT8 ucDVDVerUpFlag,UINT8 ucBTVerUpFlag,UINT8 ucFoldFlag);

protected:
    //�����������ļ��ж�ȡ������
	BOOL GetConfigValueByString(TCHAR*pString,UINT8 &ucPowerVerUpFlag,UINT8 &ucNKVerUpFlag,UINT8 &ucAPPVerUpFlag,UINT8 &ucDVDVerUpFlag,UINT8 &ucBTVerUpFlag,UINT8 &ucFoldFlag);
	
private:
	static CReadVerUpSetting* m_pReadVerUpSetting;

};
#endif //_READVERUPSETTING_H