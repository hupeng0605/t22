#include "define.h"
#pragma once
class  btSource
{
   public:
	  static  btSource* Instance();
	   static void DeleteInstance();
	  //void DestoryBtSource();
	   virtual ~btSource();
	   virtual IReSurface* ChangeBKGndSource(const TCHAR * pszDirPath);
	 sbtSourceGroup* GetBtSource(const TCHAR * pszDirPath);
	  sbtSourceGroup* GetBtSource(const TCHAR * pszDirPath,eDIALOGTYPE eType,HINT nParamEx);
	  void ReleaseBtSource(eDIALOGTYPE eType);
	//void RealseBtSource()
	 sLangue *GetBTEnLange();
	 sLangue *GetBTChLange();
	 HINT ReadLangeContent(HUINT nMax);
   private:
	   btSource();
	   sbtSourceGroup* CreateBtSource(const TCHAR * pszDirPath);
	   static btSource * s_pbtsource;
	   // IReSurface *m_pbtBkgnd;
	   //IReSurface *m_pbtBaseDailN;
	   //IReSurface *m_pbtBaseDailA;
	   //IReSurface *m_pbtBaseAddressbookA;
	   //IReSurface *m_pbtBaseCallRecordsA;
	   //IReSurface *m_pbtBaseMusicA;
	   //IReSurface *m_pbtBaseConnectStepA;
	   //IReSurface *m_pbtBaseAddressbookN;
	   //IReSurface *m_pbtBaseCallRecordsN;
	   //IReSurface *m_pbtBaseMusicN;
	   //IReSurface *m_pbtBaseConnectStepN;
	   //IReSurface *m_pbtBkLeft;
	   //IReSurface *m_pbtBkRight;
	   //IReSurface *m_pbtItemSelected;
	   //IReSurface *m_pbtLine;
	   //IReSurface *m_pbtCallIn;
	   //IReSurface *m_pbtCallOut;
	   //IReSurface *m_pbtMissedCall;
	   //IReSurface *m_pbtUpN;
	   //IReSurface *m_pbtUpA;
	   //IReSurface *m_pbtDownA;
	   //IReSurface *m_pbtDownN;
	   //IReSurface *m_pbtBarN;
	   //IReSurface *m_pbtBarA;
	   //IReSurface *m_pbtBarF;
	   //IReSurface *m_pbtBarD;
	   //IReSurface *m_pbtConnectIconN;
	   //IReSurface *m_pbtConnectIconA;
	   //IReSurface *m_pbtBottom;
		sbtSourceGroup* m_pbtSourceGroup;
		sLangue m_EnLan;
		sLangue m_ChLan;
};