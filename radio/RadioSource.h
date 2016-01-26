#pragma once
#include "stdafx.h"

class  RadioSource
{
public:
	static  RadioSource* Instance();
	void DeleteInstance();
	virtual ~RadioSource();
	sRadioSourceGroup* GetRadioSource(const TCHAR * pszDirPath);
	sLangue *GetRadioEnLange();
	sLangue *GetRadioChLange();
	HINT ReadLangeContent(HUINT nMax);
private:
	RadioSource();
	sRadioSourceGroup* CreateRadioSource(const TCHAR * pszDirPath);
	static RadioSource * s_pRadioSource;
	sRadioSourceGroup* m_pRadioSourceGroup;
	/*HCHAR *(m_pChLangue)[50];
	HCHAR *(m_pEnLangue)[50];*/
	sLangue m_EnLan;
	sLangue m_ChLan;
};