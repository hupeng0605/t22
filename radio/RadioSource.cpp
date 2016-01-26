#include "RadioSource.h"
#include <fstream>
RadioSource* RadioSource::s_pRadioSource = NULL;

RadioSource* RadioSource::Instance()
{
	if(NULL == s_pRadioSource)
	{
		s_pRadioSource = new RadioSource;
		if(NULL == s_pRadioSource)
		{
			wprintf(_T("btSource::Instance() failed \n"));
			return NULL;
		}
	}
	return s_pRadioSource;
}
void RadioSource::DeleteInstance()
{
	if(s_pRadioSource != NULL)
	{
		SAFE_DELETE(s_pRadioSource);
		s_pRadioSource = NULL;
	}
}
RadioSource::RadioSource()
{
	m_pRadioSourceGroup = NULL;
}
RadioSource::~RadioSource()
{
	if(m_pRadioSourceGroup != NULL)
	{
		SAFE_DELETE(m_pRadioSourceGroup->pSelectedItem) ;
		SAFE_DELETE(m_pRadioSourceGroup->pAmScale);
		SAFE_DELETE(m_pRadioSourceGroup->pFmScale);
		SAFE_DELETE(m_pRadioSourceGroup->pNotice);
		SAFE_DELETE(m_pRadioSourceGroup->pCannelN);
		SAFE_DELETE(m_pRadioSourceGroup->pCannelA);
		SAFE_DELETE(m_pRadioSourceGroup->pNum0);
		SAFE_DELETE(m_pRadioSourceGroup->pNum1);
		SAFE_DELETE(m_pRadioSourceGroup->pNum2);
		SAFE_DELETE(m_pRadioSourceGroup->pNum3);
		SAFE_DELETE(m_pRadioSourceGroup->pNum4);
		SAFE_DELETE(m_pRadioSourceGroup->pNum5);
		SAFE_DELETE(m_pRadioSourceGroup->pNum6);
		SAFE_DELETE(m_pRadioSourceGroup->pNum7);
		SAFE_DELETE(m_pRadioSourceGroup->pNum8);
		SAFE_DELETE(m_pRadioSourceGroup->pNum9);
		SAFE_DELETE(m_pRadioSourceGroup->pNumDot);
		SAFE_DELETE(m_pRadioSourceGroup->pNumNull);
		SAFE_DELETE(m_pRadioSourceGroup);
		m_pRadioSourceGroup = NULL;
	}
	RADIODEBUGINFO(L"~RadioSource");
}
sRadioSourceGroup* RadioSource::CreateRadioSource(const TCHAR * pszDirPath)
{
	if(m_pRadioSourceGroup == NULL)
	{
		m_pRadioSourceGroup = new sRadioSourceGroup;
		if(m_pRadioSourceGroup != NULL)
		{
			HString strTmp;
			strTmp = pszDirPath;
			strTmp += _T("Radio\\Radio_Storage_A.hfp");
			m_pRadioSourceGroup->pSelectedItem = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp += _T("Radio\\Radio_FM_Scale.hfp");
			m_pRadioSourceGroup->pFmScale = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp += _T("Radio\\Radio_AM_Scale.hfp");
			m_pRadioSourceGroup->pAmScale = GetRESingleton()->CreateSurfaceFromFile(strTmp);
		//	strTmp = pszDirPath;
			//strTmp +=_T("Share\\Share_Info_Frame.hfp");
			//m_pRadioSourceGroup->pNotice = GetRESingleton()->CreateSurfaceFromFile(strTmp);
		//	strTmp = pszDirPath;
		//	strTmp +=_T("Radio\\Radio_ensure_A.hfp");
		//	m_pRadioSourceGroup->pCannelA = GetRESingleton()->CreateSurfaceFromFile(strTmp);
		//	strTmp = pszDirPath;
		//	strTmp +=_T("Radio\\Radio_ensure_N.hfp");
		//	m_pRadioSourceGroup->pCannelN= GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Radio\\0.hfp");
			m_pRadioSourceGroup->pNum0 = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Radio\\1.hfp");
			m_pRadioSourceGroup->pNum1 = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Radio\\2.hfp");
			m_pRadioSourceGroup->pNum2 = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Radio\\3.hfp");
			m_pRadioSourceGroup->pNum3 = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Radio\\4.hfp");
			m_pRadioSourceGroup->pNum4 = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Radio\\5.hfp");
			m_pRadioSourceGroup->pNum5 = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Radio\\6.hfp");
			m_pRadioSourceGroup->pNum6 = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Radio\\7.hfp");
			m_pRadioSourceGroup->pNum7 = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Radio\\8.hfp");
			m_pRadioSourceGroup->pNum8 = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Radio\\9.hfp");
			m_pRadioSourceGroup->pNum9 = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Radio\\P.hfp");
			m_pRadioSourceGroup->pNumDot = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Radio\\BtPhone_Match_Nextlevel_N.hfp");
			m_pRadioSourceGroup->pNumNull = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			
		}
	}
	return m_pRadioSourceGroup;
}
sRadioSourceGroup* RadioSource::GetRadioSource(const TCHAR * pszDirPath)
{
	if(m_pRadioSourceGroup == NULL)
	{
		CreateRadioSource(pszDirPath);
	}
	return m_pRadioSourceGroup;
}
sLangue* RadioSource::GetRadioEnLange()
{
	return (&m_EnLan);
}
sLangue* RadioSource::GetRadioChLange()
{
	return (&m_ChLan);
}
HINT RadioSource::ReadLangeContent(HUINT nMax)
{
	char buffer[256] = {0};
	char name[30] = {0};
	char number[70] = {0};
	char *p= NULL;
	char  *pend = NULL;
	HString appPath;
	//m_pChLangue = new sLangue;
	//m_pEnLangue = new sLangue;
	memset(&m_ChLan,0,sizeof(m_ChLan));
	memset(&m_EnLan,0,sizeof(m_EnLan));
	HCHAR (*pLan)[50] = m_ChLan.szContent;
	HCHAR		szPath[MAX_PATH] = {0};
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	appPath += szPath;
	HINT nPos = (HINT)appPath.rfind(_T('\\'));
	if(nPos == -1)
	{
		wprintf(L"[HCSourceBase::GetExePath] exe path error ");
		return false;
	}
	appPath = appPath.substr(0, nPos+1);
	appPath += L"..\\Config\\RadioLange.txt";
     HINT nIndex = 0;
	ifstream examplefile1(appPath.c_str()/*L"\\HZcar\\786sdk (armv4i)_debug\\UsefulNumbers.txt"*/);
	if (! examplefile1.is_open())
	{
		RADIODEBUGINFO(L"can not open RadioLange.txt");
		return 1;
	}
	while (! examplefile1.eof() ) {
		memset(buffer,0,sizeof(buffer));
		memset(name,0,sizeof(name));
		memset(number,0,sizeof(number));
		examplefile1.getline (buffer,100);
		p = buffer;
		while((*p) != '^')
		{
			p++;
		}
		if(p != number && (p-buffer > 0) && (p-buffer < 19))
		{
			memcpy(name,buffer,p-buffer);
		}
		while((*p) == '^')
		{
			p++;
		}
		pend = p;
		while ((*pend) != '^')
		{
			pend++;
		}
		if(p != NULL && pend != NULL  && (pend - p) < 50 && (pend - p) > 0)
		{
			memcpy(number,p,pend - p);
		}
		if(strcmp(name,"200") == 0)
		{
			pLan =  m_EnLan.szContent; 
		}
		//MultiByteToWideChar(CP_ACP,0,name,20,pUsefulContact->szUsefulNum[nIndex].szName,20);
		if(pLan != NULL)
		MultiByteToWideChar(CP_ACP,0,number,50,(HCHAR*)pLan,50);
		pLan++;
		nIndex ++;
	}
	//pUsefulContact->nTolNum = nIndex;
	examplefile1.close();
	return nIndex;
}