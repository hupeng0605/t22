
#pragma once
#include "Type.h"
#include <vector>
#include <map>

using namespace std;

typedef map<HString,HString> Key;
typedef pair<HString,HString> pair_Key;
//add by zjz
//文件编码格式。只支持三种：ANSI,Unicode(UTF-16,little endian),UTF-8
typedef enum
{
	F_ANSI=CP_ACP,
	F_UNICODE=12000,
	F_UTF8=65001
}FILETYPE;
//add end
// 段
struct Section
{
	HString	m_strSecName;
	Key			m_tKeys;

	Section(const HCHAR* app)
	{
		m_strSecName = app;
	}
	Section(HString app)
	{
		m_strSecName = app;
	}
	HString GetSectionName(void)
	{
		return m_strSecName;
	}
};

typedef vector <Section *> VPG;
typedef vector <Section *>::iterator VPGI;

class UICORE_DLL_API CINIFILE
{
public:
	CINIFILE(void);
	CINIFILE(const HString& strFileName, HBOOL IsCreatFile = FALSE,FILETYPE eType = F_ANSI):m_strPath(strFileName),m_eType(eType)
	{
		if (IsFileExist(strFileName))
		{
			ReadFile();
		}
		else
		{
			if (IsCreatFile == TRUE)
			{
				FILE *fp = NULL;
				if(_wfopen_s(&fp,strFileName.c_str(), _T("a+")) == 0)
				{
					fclose(fp);
				}
			}
		}
	}
	~CINIFILE(void);

public:	
	// 设置键值，bCreate是指段名及键名未存在时，是否创建。
	HBOOL SetValue(const HCHAR* lpSection, const HCHAR* lpKey, const HCHAR* lpValue,HBOOL bCreate=true); 
	// 设置键值，bCreate是指段名及键名未存在时，是否创建。
	HBOOL SetValue(const HCHAR* lpSection, const HCHAR* lpKey, HINT nValue,HBOOL bCreate=true); 
	// 取得键值
	HINT GetInt(const HCHAR* lpKey, const HCHAR* lpSection);
	// 取得键值
	HString GetString(const HCHAR* lpKey, const HCHAR* lpSection);
	// 判断key是否存在
	HBOOL	IsKeyExist(const HCHAR* lpKey,const HCHAR* lpSection);
	// 取得键值
	HINT GetInt(HINT nKey, const HCHAR* lpSection);
	// 取得键值
	HString GetString(HINT nKey, const HCHAR* lpSection);
	// 删除指定键
	HBOOL DelKey(const HCHAR* lpKey,const HCHAR* lpSection); 
	// 修改指定的键名
	HBOOL ModifyKey(const HCHAR* lpKey,const HCHAR* lpSection,const HCHAR* lpNewKey); 
	// 删除指定段
	HBOOL DelSection(const HCHAR* lpSection); 
	// 更新文件
	void Update(void);
	// 字符串转换为数字
	HINT Str2Int(const HString& a_strInput);
	// 数字转换为字符串
	HString Int2Str(HINT a_nVal);
	// 取得段数目
	HINT GetSectionNumber(void);
	// 取得指定段的键数目
	HINT GetKeyNumber(const HCHAR* lpSection);
	HString FindKeyBySectionAndValude(const HCHAR* lpSection,const HCHAR* lpValue);
public:
	//一般性操作：
	void SetFileName(const HCHAR* lpFileName);  //设置文件路径
	void SetFileName(const HString& strFileName);  //设置文件路径
	const HString& GetFileName(void); //获得文件名
	HString GetFirstSectionName(void);	// 取得第一个段的名字
public:
	//高级操作：
	HINT GetAllSections(vector<HString>& arrSection);  //枚举出全部的段名
	HINT GetAllKeysAndValues(vector<HString>& arrKey,vector<HString>& arrValue,const HCHAR* lpSection);  //枚举出一段内的全部键名及值
	HINT GetAllKeysAndValues(vector<HString>& arrKey,vector<HString>& arrValue,const HString& lpSection);
	
	void DelAllSections(void);//删除所有的段
private:
	HBOOL IsFileExist(const HString& strPath);
	HBOOL IsFileExist(const HCHAR* strPath);
	void ReadFile(void);
	void WriteFile(void);
	VPGI GetFirstSection(void);	// 取第一个段的iter
	VPGI GetLastSection(void);	// 取最后一个段的iter
	VPGI FindSection(const HCHAR *lpSection);// 查找section
	VPGI FindSection(const HString& lpSection);
	//Key::iterator FindKey(const kn_char *lpSection,const kn_char *lpKey);
	HString CompositeSectionString(const HString& strInput);
	HString CompositeKeyString(const HString& strKey,const HString& strValue);
	HINT Wchar2Char(const HCHAR* strInput,char *strOut);
	HINT Char2Wchar(const char* strInput,HCHAR *strOut);

	void TrimLeft(string& strInput);
	void TrimRight(string& strInput);
	void TrimLeft(wstring& strInput);
	void TrimRight(wstring& strInput);
private:
	VPG m_ini;
	HString m_strPath;

	//add by zjz
	//文件编码格式。只支持三种：ANSI,Unicode(UTF-16,little endian),UTF-8
	FILETYPE m_eType;
	//add end
};
