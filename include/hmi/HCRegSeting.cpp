#include "HCRegSeting.h"



BOOL HCRegSeting::SetRegValueInt( LPCTSTR keyPath,LPCTSTR keyName, DWORD dwkeyValue,HKEY hRoot/*=HKEY_LOCAL_MACHINE*/ )
{
	HKEY key;
	long ret=RegOpenKeyEx(hRoot,keyPath,0,0,&key);
	if (ret!=ERROR_SUCCESS)
	{
		ret=RegCreateKeyEx(hRoot,keyPath,0,NULL,0,0,NULL,&key,NULL);
		if (ret!=ERROR_SUCCESS)
		{
			return FALSE;
		}
	}

	DWORD type1=REG_DWORD;
	DWORD cbData = sizeof(DWORD);
	ret=RegSetValueEx(key,keyName,NULL,type1,(LPBYTE)&dwkeyValue,cbData);

	RegCloseKey(key);

	return ret==ERROR_SUCCESS;
}

BOOL HCRegSeting::GetRegValueInt( LPCTSTR keyPath,LPCTSTR keyName, DWORD &dwkeyValue,HKEY hRoot/*=HKEY_LOCAL_MACHINE*/ )
{
	HKEY key;
	long ret=RegOpenKeyEx(hRoot,keyPath,0,0,&key);
	if (ret!=ERROR_SUCCESS)
	{
		return FALSE;
	}

	DWORD type1=REG_DWORD;
	DWORD cbData=sizeof(DWORD);
	ret=RegQueryValueEx(key,keyName,NULL,&type1,(LPBYTE)&dwkeyValue,&cbData);
	RegCloseKey(key);

	return ret==ERROR_SUCCESS;
}

BOOL HCRegSeting::SetRegValueStr( LPCTSTR keyPath,LPCTSTR keyName, LPBYTE pBuffer,HKEY hRoot/*=HKEY_LOCAL_MACHINE */ )
{
	HKEY key;
	long ret=RegOpenKeyEx(hRoot,keyPath,0,0,&key);
	if (ret!=ERROR_SUCCESS)
	{
		ret=RegCreateKeyEx(hRoot,keyPath,0,NULL,0,0,NULL,&key,NULL);
		if (ret!=ERROR_SUCCESS)
		{
			return FALSE;
		}
	}

	DWORD cbData = wcslen((WCHAR*)pBuffer)*sizeof(WCHAR);
	ret=RegSetValueEx(key,keyName,NULL, REG_SZ, pBuffer,cbData);

	RegCloseKey(key);

	return ret==ERROR_SUCCESS;
}

BOOL HCRegSeting::GetRegValueStr(LPCTSTR keyPath,LPCTSTR keyName, LPBYTE pBuffer,HKEY hRoot/*=HKEY_LOCAL_MACHINE*/ )
{
	HKEY key;
	long ret=RegOpenKeyEx(hRoot,keyPath,0,0,&key);
	if (ret!=ERROR_SUCCESS)
	{
		return FALSE;
	}

	DWORD type1 = REG_SZ;
	DWORD cbData = MAX_PATH;
	ret=RegQueryValueEx(key,keyName,NULL,&type1, pBuffer,&cbData);
	RegCloseKey(key);

	return ret==ERROR_SUCCESS;
}
