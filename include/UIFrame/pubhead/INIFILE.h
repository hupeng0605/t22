
#pragma once
#include "Type.h"
#include <vector>
#include <map>

using namespace std;

typedef map<HString,HString> Key;
typedef pair<HString,HString> pair_Key;
//add by zjz
//�ļ������ʽ��ֻ֧�����֣�ANSI,Unicode(UTF-16,little endian),UTF-8
typedef enum
{
	F_ANSI=CP_ACP,
	F_UNICODE=12000,
	F_UTF8=65001
}FILETYPE;
//add end
// ��
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
	// ���ü�ֵ��bCreate��ָ����������δ����ʱ���Ƿ񴴽���
	HBOOL SetValue(const HCHAR* lpSection, const HCHAR* lpKey, const HCHAR* lpValue,HBOOL bCreate=true); 
	// ���ü�ֵ��bCreate��ָ����������δ����ʱ���Ƿ񴴽���
	HBOOL SetValue(const HCHAR* lpSection, const HCHAR* lpKey, HINT nValue,HBOOL bCreate=true); 
	// ȡ�ü�ֵ
	HINT GetInt(const HCHAR* lpKey, const HCHAR* lpSection);
	// ȡ�ü�ֵ
	HString GetString(const HCHAR* lpKey, const HCHAR* lpSection);
	// �ж�key�Ƿ����
	HBOOL	IsKeyExist(const HCHAR* lpKey,const HCHAR* lpSection);
	// ȡ�ü�ֵ
	HINT GetInt(HINT nKey, const HCHAR* lpSection);
	// ȡ�ü�ֵ
	HString GetString(HINT nKey, const HCHAR* lpSection);
	// ɾ��ָ����
	HBOOL DelKey(const HCHAR* lpKey,const HCHAR* lpSection); 
	// �޸�ָ���ļ���
	HBOOL ModifyKey(const HCHAR* lpKey,const HCHAR* lpSection,const HCHAR* lpNewKey); 
	// ɾ��ָ����
	HBOOL DelSection(const HCHAR* lpSection); 
	// �����ļ�
	void Update(void);
	// �ַ���ת��Ϊ����
	HINT Str2Int(const HString& a_strInput);
	// ����ת��Ϊ�ַ���
	HString Int2Str(HINT a_nVal);
	// ȡ�ö���Ŀ
	HINT GetSectionNumber(void);
	// ȡ��ָ���εļ���Ŀ
	HINT GetKeyNumber(const HCHAR* lpSection);
	HString FindKeyBySectionAndValude(const HCHAR* lpSection,const HCHAR* lpValue);
public:
	//һ���Բ�����
	void SetFileName(const HCHAR* lpFileName);  //�����ļ�·��
	void SetFileName(const HString& strFileName);  //�����ļ�·��
	const HString& GetFileName(void); //����ļ���
	HString GetFirstSectionName(void);	// ȡ�õ�һ���ε�����
public:
	//�߼�������
	HINT GetAllSections(vector<HString>& arrSection);  //ö�ٳ�ȫ���Ķ���
	HINT GetAllKeysAndValues(vector<HString>& arrKey,vector<HString>& arrValue,const HCHAR* lpSection);  //ö�ٳ�һ���ڵ�ȫ��������ֵ
	HINT GetAllKeysAndValues(vector<HString>& arrKey,vector<HString>& arrValue,const HString& lpSection);
	
	void DelAllSections(void);//ɾ�����еĶ�
private:
	HBOOL IsFileExist(const HString& strPath);
	HBOOL IsFileExist(const HCHAR* strPath);
	void ReadFile(void);
	void WriteFile(void);
	VPGI GetFirstSection(void);	// ȡ��һ���ε�iter
	VPGI GetLastSection(void);	// ȡ���һ���ε�iter
	VPGI FindSection(const HCHAR *lpSection);// ����section
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
	//�ļ������ʽ��ֻ֧�����֣�ANSI,Unicode(UTF-16,little endian),UTF-8
	FILETYPE m_eType;
	//add end
};
