

#pragma once
#include <vector>
#include <Type.h>
#include "Pubhead.h"
using namespace std;

// 根据言语ID获取字符串
#define GET_LANG_CSTRING(langID) HCLangManager::GetInstance()->HMI_LANG_GetStr(## langID).c_str()
#define GET_LANG_STRING(langID) HString(HCLangManager::GetInstance()->HMI_LANG_GetStr(## langID))

class UICORE_DLL_API HCLangManager
{
public:
	enum
	{
#ifdef JP_VERSION
		HMI_LANG_ENGLISH = 0,
		HMI_LANG_JAPANESE = 1,
		HMI_LANG_NOTHING = -1
#else
		HMI_LANG_ENGLISH = 0,
		HMI_LANG_CHINESE = 1,
		HMI_LANG_TRADITION = 2,
		HMI_LANG_NOTHING = -1
#endif
	};


	enum
	{
		CHARSET_ANSII = 0,
		CHARSET_GB2312 = 1,
		CHARSET_NOTHING = -1,
	};
private:
	HCLangManager(void);
	~HCLangManager(void);
	HCLangManager(const HCLangManager&) {}

public:
	/*==============================================================*/
	/* get string by language id */
	const HString& HMI_LANG_GetStr( HINT a_nStrID);

	/* get charset */
	HINT HMI_LANG_GetCharacterSet(void);

	/* set string size */
	HINT HMI_LANG_GetStrSize( HINT a_nStrID);


	void HMI_LANG_Setting( HINT a_nLanguage/*,kn_bool a_bUpdate = true */);

	inline HINT HMI_LANG_Getting(void ){return m_nLanguage;}

	static HCLangManager* GetInstance(void);
	
	HINT HMI_LANG_GetLang();

private:
	/* change language */
	//void HMI_LANG_Change( void );
	void InitStringTable(HString a_StringTablePath);

	HINT Str2Int(const HString &a_str);
	HString Int2Str(HINT a_Val);

private:
	HINT		m_nLanguage;
	HINT		m_nCharset; 
	HINT		m_nTotalCnt;
	vector<HString> m_pLangStrTbl;
};
