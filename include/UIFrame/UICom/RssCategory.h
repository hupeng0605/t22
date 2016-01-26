
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
	
	// 取得左边的分类的个数
	HINT GetLeftCategoryCount(void);
	
	// 取得左边的分类的信息 name和icon
	void GetLeftCategory(
		IN HINT nIndex,
		OUT HString& strName,
		OUT HINT& nID,
		OUT HString& strIcon);
		
	// 取得右边的分类的个数
	HINT GetRightCategoryCount(IN HINT nIndex);
	
	// 取得右边的分类的信息，name,id,icon,url
	void GetRightCategory(
		IN HINT nLeftCategoryIndex,
		IN HINT nRightCategoryIndex,
		OUT HString& strItemName,
		OUT HINT& nID,
		OUT HString& strIcon,
		OUT HString& strURL);

	// 以下函数提供修改收藏夹的功能
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
	CINIFILE*	m_pIniFile;	// RSS配置文件
};
