#include "btsource.h"
#include <fstream>
btSource* btSource::s_pbtsource = NULL;

btSource* btSource::Instance()
{
	if(NULL == s_pbtsource)
	{
		s_pbtsource = new btSource;
		if(NULL == s_pbtsource)
		{
			wprintf(_T("btSource::Instance() failed \n"));
			return NULL;
		}
	}
	return s_pbtsource;
}
void btSource::DeleteInstance()
{
    if(s_pbtsource != NULL)
	{
		SAFE_DELETE(s_pbtsource);
	}
}
btSource::btSource()
{
	//m_pbtBkgnd = NULL;
	//m_pbtBaseDailA = NULL;
	//m_pbtBaseAddressbookA = NULL;
	//m_pbtBaseCallRecordsA = NULL;
	//m_pbtBaseMusicA = NULL;
	//m_pbtBaseConnectStepA = NULL;
	//m_pbtBaseDailN = NULL;
	//m_pbtBaseAddressbookN = NULL;
	//m_pbtBaseCallRecordsN = NULL;
	//m_pbtBaseMusicN = NULL;
	//m_pbtBaseConnectStepN = NULL;
	//m_pbtBkLeft = NULL;
	//m_pbtBkRight = NULL;
	//m_pbtItemSelected = NULL;
	//m_pbtConnectIconN = NULL;
	//m_pbtConnectIconA = NULL;
	//m_pbtLine = NULL;
	//m_pbtCallIn = NULL;
	//m_pbtCallOut = NULL;
	//m_pbtMissedCall = NULL;
	//m_pbtUpN = NULL;
	//m_pbtUpA = NULL;
	//m_pbtDownA = NULL;
	//m_pbtDownN = NULL;
	//m_pbtBarN = NULL;
	//m_pbtBarA = NULL;
	//m_pbtBarF = NULL;
	//m_pbtBarD = NULL;
	//m_pbtBottom = NULL;
	m_pbtSourceGroup = NULL;
}
sbtSourceGroup* btSource::CreateBtSource(const TCHAR * pszDirPath)
{
	if(m_pbtSourceGroup == NULL)
	{
		m_pbtSourceGroup = new sbtSourceGroup;
		if(m_pbtSourceGroup != NULL)
		{
			memset(m_pbtSourceGroup,0,sizeof(sbtSourceGroup));
			HString strTmp;
			SETUPSETTING SetupSetting ;
			strTmp = pszDirPath; //GetHMIPath(_T("")).c_str();
			KCLastMemory::GetInstance()->GetSetupMemory(SetupSetting);
			strTmp += (HCHAR*)&SetupSetting.szBkgndPath;
			m_pbtSourceGroup->m_pbtBkgnd = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			//基类界面
			strTmp = pszDirPath;
			strTmp += _T("Bluetooth\\Share\\Bluetooth_Booklist_A.hfp");
			m_pbtSourceGroup->m_pbtBaseAddressbookA = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp += _T("Bluetooth\\Share\\Bluetooth_Booklist_N.hfp");
			m_pbtSourceGroup->m_pbtBaseAddressbookN = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp += _T("Bluetooth\\Share\\Bluetooth_Records_A.hfp");
			m_pbtSourceGroup->m_pbtBaseCallRecordsA = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp += _T("Bluetooth\\Share\\Bluetooth_Records_N.hfp");
			m_pbtSourceGroup->m_pbtBaseCallRecordsN = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Share\\Bluetooth_Connection_A.hfp");
			m_pbtSourceGroup->m_pbtBaseConnectStepA = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp += _T("Bluetooth\\Share\\Bluetooth_Connection_N.hfp");
			m_pbtSourceGroup->m_pbtBaseConnectStepN = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Share\\Bluetooth_Dial_A.hfp");
			m_pbtSourceGroup->m_pbtBaseDailA = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Share\\Bluetooth_Dial_N.hfp");
			m_pbtSourceGroup->m_pbtBaseDailN = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Share\\Bluetooth_Music_A.hfp");
			m_pbtSourceGroup->m_pbtBaseMusicA = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Share\\Bluetooth_Music_N.hfp");
			m_pbtSourceGroup->m_pbtBaseMusicN = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Booklist\\Booklist_Division_Line.hfp");
			m_pbtSourceGroup->m_pbtLine = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			//strTmp +=_T("Share\\Share_Front_A.hfp");
			strTmp +=_T("Radio\\Radio_Front_A.hfp");//向上箭头
			m_pbtSourceGroup->m_pbtUpA = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			//通讯录
			//strTmp = pszDirPath;
			//strTmp +=_T("Share\\Share_Form_Frame.hfp");//提示信息背景
			//m_pbtSourceGroup->m_pbtBkLeft = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Share\\Share_Division_Frame.hfp");
			m_pbtSourceGroup->m_pbtBkRight = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Connection\\Connection_Frame_A.hfp");
			m_pbtSourceGroup->m_pbtItemSelected = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Connection\\Connection_Ct_SM.hfp");
			m_pbtSourceGroup->m_pbtConnectIconA = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Connection\\Connection_Bk_SM.hfp");
			m_pbtSourceGroup->m_pbtConnectIconN = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Load progress\\loader10001.hfp");
			m_pbtSourceGroup->m_pDownProcess[0] = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Load progress\\loader10002.hfp");
			m_pbtSourceGroup->m_pDownProcess[1] = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Load progress\\loader10003.hfp");
			m_pbtSourceGroup->m_pDownProcess[2] = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Load progress\\loader10004.hfp");
			m_pbtSourceGroup->m_pDownProcess[3] = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Load progress\\loader10005.hfp");
			m_pbtSourceGroup->m_pDownProcess[4] = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Load progress\\loader10006.hfp");
			m_pbtSourceGroup->m_pDownProcess[5] = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Load progress\\loader10007.hfp");
			m_pbtSourceGroup->m_pDownProcess[6] = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Load progress\\loader10008.hfp");
			m_pbtSourceGroup->m_pDownProcess[7] = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Load progress\\loader10009.hfp");
			m_pbtSourceGroup->m_pDownProcess[8] = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Load progress\\loader10010.hfp");
			m_pbtSourceGroup->m_pDownProcess[9] = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Load progress\\loader10011.hfp");
			m_pbtSourceGroup->m_pDownProcess[10] = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Load progress\\loader10012.hfp");
			m_pbtSourceGroup->m_pDownProcess[11] = GetRESingleton()->CreateSurfaceFromFile(strTmp);	
//通话记录
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Records\\Received_N.hfp");
			m_pbtSourceGroup->m_pbtCallIn = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Records\\Dialed_N.hfp");
			m_pbtSourceGroup->m_pbtCallOut = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Bluetooth\\Records\\Missed_N.hfp");
			m_pbtSourceGroup->m_pbtMissedCall = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			
			strTmp = pszDirPath;
			strTmp +=_T("Share\\Share_Front_N.hfp");
			m_pbtSourceGroup->m_pbtUpN = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Share\\Share_Last_N.hfp");
			m_pbtSourceGroup->m_pbtDownN = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Radio\\Radio_Last_A.hfp");
			//strTmp +=_T("Share\\Share_Last_A.hfp");
			m_pbtSourceGroup->m_pbtDownA = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Share\\Share_Slide_N.hfp");
			m_pbtSourceGroup->m_pbtBarN = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Share\\Share_Slide_Bar.hfp");
			m_pbtSourceGroup->m_pbtBarA = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Share\\Share_Slide_Bar.hfp");
			m_pbtSourceGroup->m_pbtBarF = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Share\\Share_Slide_A.hfp");
			m_pbtSourceGroup->m_pbtBarD = GetRESingleton()->CreateSurfaceFromFile(strTmp);
			strTmp = pszDirPath;
			strTmp +=_T("Share\\Share_Frame_Bottom 02.hfp");
			m_pbtSourceGroup->m_pbtBottom = GetRESingleton()->CreateSurfaceFromFile(strTmp);

           //hdmi界面
			//strTmp = pszDirPath;
			//strTmp +=_T("Bluetooth\\Share\\Main_Phone_Bak.hfp");
			//m_pbtSourceGroup->m_pbtHmiBk = GetRESingleton()->CreateSurfaceFromFile(strTmp);		
			//strTmp = pszDirPath;
			//strTmp +=_T("Bluetooth\\Share\\Main_Phone_Bak_EN.hfp");
			//m_pbtSourceGroup->m_pbtHmiBkEn = GetRESingleton()->CreateSurfaceFromFile(strTmp);		
		}
		HINT nTotal = ReadLangeContent(400);
		if(nTotal == 0)
		{
			BTDEBUGINFO(L"读取BT语言字符串失败");
			exit(1);
		}
		else if(nTotal > 0)
		{
			BTDEBUGINFO(L"读取BT字符串成功");
		}
	}
	return m_pbtSourceGroup;
}
IReSurface* btSource::ChangeBKGndSource(const TCHAR * pszDirPath)
{
	IReSurface *pBk = NULL;
	if(m_pbtSourceGroup == NULL)
	{
		Instance()->CreateBtSource(pszDirPath);
	}
	else
	{
		pBk = m_pbtSourceGroup->m_pbtBkgnd;
		//IReSurface * p= m_pbtSourceGroup->m_pbtBkgnd;
		HString strTmp1;
		SETUPSETTING SetupSetting ;
		strTmp1 = pszDirPath; //GetHMIPath(_T("")).c_str();
		KCLastMemory::GetInstance()->GetSetupMemory(SetupSetting);
		strTmp1 += (HCHAR*)&SetupSetting.szBkgndPath;
		m_pbtSourceGroup->m_pbtBkgnd = GetRESingleton()->CreateSurfaceFromFile(strTmp1);
		//SAFE_DELETE(p);
	}
	return pBk;
	
}
sbtSourceGroup* btSource::GetBtSource(const TCHAR * pszDirPath)
{
	if(m_pbtSourceGroup == NULL)
	{
	  return	CreateBtSource(pszDirPath);
	}
	else
	{
		return m_pbtSourceGroup;
	}
}
 btSource::~btSource()
 {
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBkgnd);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBaseDailN);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBaseDailA);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBaseAddressbookA);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBaseCallRecordsA);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBaseMusicA);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBaseConnectStepA);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBaseAddressbookN);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBaseCallRecordsN);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBaseMusicN);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBaseConnectStepN);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBkLeft);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBkRight);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtItemSelected);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtLine);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtCallIn);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtCallOut);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtMissedCall);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtUpN);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtUpA);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtDownA);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtDownN);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBarN);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBarA);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBarF);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBarD);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtConnectIconN);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtConnectIconA);
		SAFE_DELETE(m_pbtSourceGroup->m_pbtBottom);
		for(int i = 0; i < 12;i++)
		{
			SAFE_DELETE(m_pbtSourceGroup->m_pDownProcess[i]);
		}
		SAFE_DELETE(m_pbtSourceGroup);
		m_pbtSourceGroup = NULL;
 }
 sLangue* btSource::GetBTEnLange()
 {
	return (&m_EnLan);
 }
 sLangue* btSource::GetBTChLange()
 {
	return (&m_ChLan);
 }
 HINT btSource::ReadLangeContent(HUINT nMax)
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
	 appPath += L"..\\Config\\BTLange.txt";
	 HINT nIndex = 0;
	 ifstream examplefile1(appPath.c_str()/*L"\\HZcar\\786sdk (armv4i)_debug\\UsefulNumbers.txt"*/);
	 if (! examplefile1.is_open())
	 {
		 BTDEBUGINFO(L"can not open BTLange.txt");
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
 sbtSourceGroup* btSource::GetBtSource(const TCHAR * pszDirPath,eDIALOGTYPE eType,HINT nParamEx)
 {
	if(pszDirPath != NULL)
	{
		if(m_pbtSourceGroup == NULL)
		{
			m_pbtSourceGroup = new sbtSourceGroup;
		}
			if(m_pbtSourceGroup != NULL)
			{
				//memset(m_pbtSourceGroup,0,sizeof(sbtSourceGroup));
				HString strTmp;
				SETUPSETTING SetupSetting ;
				strTmp = pszDirPath; //GetHMIPath(_T("")).c_str();
				KCLastMemory::GetInstance()->GetSetupMemory(SetupSetting);	
				switch (eType)
				{
					case eDIALOGT_BTDIAL:
					{
						
					}
					break;
					case eDIALOGT_BTADDRESSBOOK:
					{
						if(m_pbtSourceGroup != NULL)
						{
							if(m_pbtSourceGroup->m_pbtBkLeft == NULL)
							{
								strTmp = pszDirPath;
								strTmp +=_T("Share\\Share_Form_Frame.hfp");//提示信息背景
								m_pbtSourceGroup->m_pbtBkLeft = GetRESingleton()->CreateSurfaceFromFile(strTmp);
							}
						}
					}
					break;
					case eDIALOGT_BTCALLRECORDS:
					{
						if(m_pbtSourceGroup != NULL)
						{
							if(m_pbtSourceGroup->m_pbtBkLeft == NULL)
							{
								strTmp = pszDirPath;
								strTmp +=_T("Share\\Share_Form_Frame.hfp");//提示信息背景
								m_pbtSourceGroup->m_pbtBkLeft = GetRESingleton()->CreateSurfaceFromFile(strTmp);
							}
						}
					}
					break;
					case eDIALOGT_BTMUSIC:
					{

					}
					break;
					case eDIALOGT_BTCONNECTSETTING:
					{
						if(m_pbtSourceGroup != NULL)
						{
							if(m_pbtSourceGroup->m_pbtBkLeft == NULL)
							{
								strTmp = pszDirPath;
								strTmp +=_T("Share\\Share_Form_Frame.hfp");//提示信息背景
								m_pbtSourceGroup->m_pbtBkLeft = GetRESingleton()->CreateSurfaceFromFile(strTmp);
							}
						}
					}
					break;
					case eDIALOGT_BTHMI:
					{
						switch (nParamEx)
						{
							case 0:
							{
								if(m_pbtSourceGroup->m_pbtHmiBk == NULL)
								{
									strTmp = pszDirPath;
									strTmp +=_T("Bluetooth\\Share\\Main_Phone_Bak.hfp");
									m_pbtSourceGroup->m_pbtHmiBk = GetRESingleton()->CreateSurfaceFromFile(strTmp);		

								}
								if(m_pbtSourceGroup->pbtHDMIBTNOTICECH == NULL)
								{
									strTmp = pszDirPath;
									strTmp +=_T("BTSource\\Share\\Main Phone 0319 02.hfp");
									m_pbtSourceGroup->pbtHDMIBTNOTICECH = GetRESingleton()->CreateSurfaceFromFile(strTmp);
								}
							}
							break;
							case 1:
							{
								if(m_pbtSourceGroup->m_pbtHmiBkEn == NULL)
								{
									strTmp = pszDirPath;
									strTmp +=_T("Bluetooth\\Share\\Main_Phone_Bak_EN.hfp");
									m_pbtSourceGroup->m_pbtHmiBkEn = GetRESingleton()->CreateSurfaceFromFile(strTmp);	
								}
								if(m_pbtSourceGroup->pbtHDMIBTNOTICEEN == NULL)
								{
									strTmp = pszDirPath;
									strTmp +=_T("BTSource\\Share\\Main Phone 0319 02.hfp");
									m_pbtSourceGroup->pbtHDMIBTNOTICEEN = GetRESingleton()->CreateSurfaceFromFile(strTmp);
								}
							}
							break;
						}	
					}
					break;
					case eDIALOGT_UNKNOW:
					{

					}
					break;
				}
			}
		
	}
	return m_pbtSourceGroup;
 }
 void btSource::ReleaseBtSource(eDIALOGTYPE eType)
  {
	 switch (eType)
	 {
		 case eDIALOGT_BTDIAL:
		 {
				
		 }
		 break;
		case eDIALOGT_BTADDRESSBOOK:
		 {
			 if(m_pbtSourceGroup->m_pbtBkLeft != NULL)
			 {
				 //SAFE_DELETE(m_pbtSourceGroup->m_pbtBkLeft);
			 }
		 }
		 break;
		case eDIALOGT_BTCALLRECORDS:
		 {
			 if(m_pbtSourceGroup->m_pbtBkLeft != NULL)
			 {
				 //SAFE_DELETE(m_pbtSourceGroup->m_pbtBkLeft);
			 }
		 }
		 break;
		case eDIALOGT_BTMUSIC:
		 {

		 }
		 break;
		case eDIALOGT_BTCONNECTSETTING:
		 {
			 if(m_pbtSourceGroup->m_pbtBkLeft != NULL)
			 {
				 //SAFE_DELETE(m_pbtSourceGroup->m_pbtBkLeft);
			 }
		 }
		 break;
		case eDIALOGT_BTHMI:
		 {
			if(m_pbtSourceGroup != NULL)
			{
				SAFE_DELETE(m_pbtSourceGroup->m_pbtHmiBk);
				SAFE_DELETE(m_pbtSourceGroup->m_pbtHmiBkEn);
			}
		 }
		 break;
		case eDIALOGT_UNKNOW:
		 {

		 }
		 break;
	 }
  }
 