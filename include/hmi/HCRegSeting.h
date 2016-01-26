#pragma once

#include <Windows.h>

class HCRegSeting
{
public:
	static BOOL SetRegValueInt(LPCTSTR keyPath,LPCTSTR keyName, DWORD dwkeyValue,HKEY hRoot=HKEY_LOCAL_MACHINE);
	static BOOL GetRegValueInt(LPCTSTR keyPath,LPCTSTR keyName, DWORD &dwkeyValue,HKEY hRoot=HKEY_LOCAL_MACHINE);
	static BOOL SetRegValueStr( LPCTSTR keyPath,LPCTSTR keyName, LPBYTE pBuffer,HKEY hRoot=HKEY_LOCAL_MACHINE );
	static BOOL GetRegValueStr(LPCTSTR keyPath,LPCTSTR keyName, LPBYTE pBuffer,HKEY hRoot=HKEY_LOCAL_MACHINE );
};