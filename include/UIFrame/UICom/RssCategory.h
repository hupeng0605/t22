
#pragma once
#include "Configure.h"
#include "Type.h"
#include "INIFILE.h"

class CYPRESS_DLL_API CRssCategory
{
public:
	CRssCategory(const HString& strPath);
	CRssCategory(const HCHAR* strPath);
	~CRssCategory(void);
	
private:
	CRssCategory(void);
	CRssCategory(const CRssCategory&);
	
public:
	//static CRssCategory* GetInstance(void);
	//static void ExitInstance(void);
	void SetIniPath(const HString& strPath);
	void SetIniPath(const HCHAR* strPath);
	
	// ȡ����ߵķ���ĸ���
	HINT GetLeftCategoryCount(void);
	
	// ȡ����ߵķ������Ϣ name��icon
	void GetLeftCategory(
		IN HINT nIndex,
		OUT HString& strName,
		OUT HINT& nID,
		OUT HString& strIcon);
		
	// ȡ���ұߵķ���ĸ���
	HINT GetRightCategoryCount(IN HINT nIndex);
	
	// ȡ���ұߵķ������Ϣ��name,id,icon,url
	void GetRightCategory(
		IN HINT nLeftCategoryIndex,
		IN HINT nRightCategoryIndex,
		OUT HString& strItemName,
		OUT HINT& nID,
		OUT HString& strIcon,
		OUT HString& strURL);

	// ���º����ṩ�޸��ղؼеĹ���
	HINT AddFavoriteCategory(
		IN const HString& strItemName,
		IN HINT nID,
		IN const HString& strIcon,
		IN const HString& strURL);
		
	void ModifyFavoriteCategory(
		IN HINT nRightCategoryIndex,
		IN const HString& strItemName,
		IN HINT nID,
		IN const HString& strIcon,
		IN const HString& strURL);
		
	void DeleteFavoriteCategory(
		IN HINT nRightCategoryIndex
		);
	void Save(void);
		
private:
	HINT AddRightCategory(
		IN HINT nLeftCategoryIndex,
		IN const HString& strItemName,
		IN HINT nID,
		IN const HString& strIcon,
		IN const HString& strURL);
		
	void ModifyRightCategory(
		IN HINT nLeftCategoryIndex,
		IN HINT nRightCategoryIndex,
		IN const HString& strItemName,
		IN HINT nID,
		IN const HString& strIcon,
		IN const HString& strURL);
	void DeleteRightCategory(
		IN HINT nLeftCategoryIndex,
		IN HINT nRightCategoryIndex
		);
//private:
private:
	HBOOL CreateIniObject(const HString& strIniPath);

private:
	CINIFILE*	m_pIniFile;	// RSS�����ļ�
};
