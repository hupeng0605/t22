

#pragma once
#include "Type.h"
#include "Configure.h"

#ifdef ETIMETYPE
#undef ETIMETYPE
// 时间格式
enum eTimeType
{
	eHHMMSS = -1,// 01:03:08
	eHMMSS,// 1:03:08
	eMMSS,// 03:08
	eMSS// 3:08
};
#endif

class CYPRESS_DLL_API KCCommon
{
public:
	KCCommon(void);
	~KCCommon(void);
public:
	// 转换
	static HINT Str2Int(const HString& a_strInput);
	static HINT Str2Int(const HCHAR* a_strInput);
	static HString Int2Str(HINT a_nVal);
	static HFLOAT Str2Float(const HString& a_strInput);
	static HFLOAT Str2Float(const HCHAR* a_strInput);
	static HString Float2Str(HFLOAT a_fVal);
	
	// 文件操作
	static HBOOL IsFileExist(const HString& strPath);
	static HBOOL IsFileExist(const HCHAR* strPath);
	static HINT	GetFileTypeByPath(const HString& strPath);
	static HINT	GetFileTypeByPath(const HCHAR* strPath);
	static HString GetExtNameByPath(const HString& strPath);
	static HString GetExtNameByPath(const HCHAR* strPath);
	static HString GetFileNameByPath(const HString& strPath);
	static HString GetFileNameByPath(const HCHAR* strPath);
	
	static HString GetFileNameNoExtByPath(const HString& strPath);
	static HString GetFileNameNoExtByPath(const HCHAR* strPath);

	static HString StringRepace(const HCHAR* strInput,HINT nSharp,const HCHAR* strAsterisk);
	static HString StringRepace(const HCHAR* strInput,HINT nSharp,const HString& strAsterisk);
	static HString StringRepace(const HString& strInput,HINT nSharp,const HCHAR* strAsterisk);
	static HString StringRepace(const HString& strInput,HINT nSharp,const HString& strAsterisk);

	static HINT Wchar2Char(const HCHAR* strInput,char *strOut);
	static HINT Char2Wchar(const char* strInput,HCHAR *strOut);
	// 格式化时间格式
	static HString FormatTime(HINT seconds);

};
