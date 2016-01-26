#include "IpodDlg.h"
//#include "ipodctl.h"
#include<fstream>
#include<iostream>
using namespace std;
#define  LOGFILE 0
#define  GETTRACKEVERYTIME 1
ofstream  g_ListFile;
int CIpodDlg::s_nSucess = 0;
int CIpodDlg::s_nInint = 0;
int CIpodDlg::s_nnCount = 0;
CIpodDlg::CIpodDlg( )
{
	m_pBtnPlayPause = NULL;
	m_pBtnSetAutoConn = NULL;
	m_pBtnStartPlay = NULL;
	m_pBtnNext = NULL;
	m_pBtnPre = NULL;
	m_pBtnStartFF = NULL;
	m_pBtnEndFFRew = NULL;
	m_pBtnStartRew = NULL;
    m_pBtnGetTrackInfo = NULL;
	m_pBtnGetPlayingTarckNum = NULL;
	m_pBtnSetCurrentPlayingTrack = NULL;
	m_pBtnGetArtWorkData = NULL;
	m_pBtnGetShuffle = NULL;
	m_pBtnSetShuffle = NULL;
	m_pBtnGetrepeat = NULL;
	m_pBtnSetRepead = NULL;
	m_pGrpMid = NULL;
	m_pGrpBtm = NULL;
	m_pTxtInfoFrame = NULL;
	m_pTxtInfo = NULL;
	m_pTxtCover = NULL;
	//m_pTxtSongHead = NULL;//曲目
	//m_pTxtArtistHead = NULL;//艺术家
	//m_pTxtAbumHead = NULL;//专辑
	 m_ntrackIndex = 0;//歌曲索引
	 m_ntrackLength = 0;//歌曲长度
    m_ntrackPosition = 0;//歌曲位置
	m_nPlayStatus = PLAYSTATUS_STOPPED;//播放状态
	m_ptrackTitle = NULL;//歌曲名称
	m_partistName = NULL;//艺术家
	m_palbumName = NULL;//专辑名字
	m_ntrackNum = 0;//
	m_shuffleStatus = SHUFFLE_OFF;
	m_repeatStatus = REPEAT_OFF;
	m_nPreplayStatus = PLAYSTATUS_STOPPED;
//	m_hIpodInsert = INVALID_HANDLE_VALUE;
	//m_hIpodUnplug = INVALID_HANDLE_VALUE;
	m_nFailed = 0;
	m_bConnected = false;
}
CIpodDlg::~CIpodDlg( )
{
	SAFE_DELETE(m_pBtnPlayPause) ;
	SAFE_DELETE (m_pBtnSetAutoConn)  ;
	SAFE_DELETE (m_pBtnStartPlay) ;
	 SAFE_DELETE (m_pBtnNext);
	 SAFE_DELETE (m_pBtnPre) ;
	SAFE_DELETE (m_pBtnStartFF) ;
	SAFE_DELETE (m_pBtnEndFFRew) ;
	SAFE_DELETE(m_pBtnStartRew)  ;
	SAFE_DELETE (m_pBtnGetTrackInfo) ;
	SAFE_DELETE (m_pBtnGetPlayingTarckNum);
	SAFE_DELETE (m_pBtnSetCurrentPlayingTrack);
	SAFE_DELETE(m_pBtnGetArtWorkData)  ;
	SAFE_DELETE (m_pBtnGetShuffle) ;
	SAFE_DELETE(m_pBtnSetShuffle)  ;
	SAFE_DELETE(m_pBtnGetrepeat)  ;
	SAFE_DELETE (m_pBtnSetRepead) ;
	SAFE_DELETE(m_ptrackTitle);
	SAFE_DELETE(m_partistName);
	SAFE_DELETE(m_palbumName);
	/*SAFE_DELETE(m_pTxtSongHead);
	SAFE_DELETE(m_pTxtArtistHead);
	SAFE_DELETE(m_pTxtAbumHead);	*/
}
HINT CIpodDlg::OnInit()
{	
	SetFocusLineWidth(0);
	m_pGrpMid = new HCGroupCtrl;
	if(m_pGrpMid != NULL)
	{
		m_pGrpMid->Create(0,68,800,344);
		AddChild(m_pGrpMid);
	}
	m_bButtonPress = false;
	HINT nRet =0;
	m_pSongInfo = new sSongInfo;
	memset(m_pSongInfo,0,sizeof(sSongInfo));
	ChangeTheme(0);
	HString strTmp;
	m_nTimes = 0;
	m_hUpdataThread = 0;
//	SETUPSETTING SetupSetting ;
	strTmp = GetHMIPath(_T("")).c_str(); //GetHMIPath(_T("")).c_str();
	strTmp += _T("Media\\Share\\Media_Division_Line.hfp");
	m_pIRELine = GetRESingleton()->CreateSurfaceFromFile(strTmp);
	strTmp = GetHMIPath(_T("")).c_str(); //GetHMIPath(_T("")).c_str();
	strTmp += _T("Media\\Music\\Music_File_Select_A.hfp");
	m_pIREListItemSelect = GetRESingleton()->CreateSurfaceFromFile(strTmp);
	strTmp = GetHMIPath(_T("")).c_str(); //GetHMIPath(_T("")).c_str();
	strTmp += _T("Media\\Music\\Music_File_Select_N.hfp");
	m_pIREMusicIcon = GetRESingleton()->CreateSurfaceFromFile(strTmp);
	strTmp = GetHMIPath(_T("")).c_str(); //GetHMIPath(_T("")).c_str();
	strTmp += _T("Ipod\\05-USB-media-music-01_04.hfp");
	m_pIREArtistBk  = GetRESingleton()->CreateSurfaceFromFile(strTmp);
	strTmp = GetHMIPath(_T("")).c_str(); //GetHMIPath(_T("")).c_str();
	strTmp += _T("Share\\Share_Info_Frame.hfp");
	m_pIREInfoFrame  = GetRESingleton()->CreateSurfaceFromFile(strTmp);
	HINT nTotal = ReadLangeContent(400);
	if(nTotal > 0)
	{
		IPODDEBEGINFO(L"获取语言数据成功");
	}
	else
	{
		IPODDEBEGINFO(L"获取语言数据失败");
		exit(20);
	}
	m_pGrpIpodList = new HCGroupCtrl;
//	SetBackGround()
	if(m_pGrpIpodList != NULL)
	{
		m_pGrpIpodList->Create(0,68,800,412);
		//m_pGrpIpodList->SetBackGround(GetHMIPath(_T("Media\\Share\\Media_Form_Frame.hfp")));
		m_pGrpIpodList->EnableMsg(true);
		m_pGrpIpodList->SetShow(false);
		AddChild(m_pGrpIpodList);
		m_pTxtLine1 = new HCTextCtrl;
		if(m_pTxtLine1 != NULL)
		{
			m_pTxtLine1->Create(16,142,724,2);
			m_pTxtLine1->SetBkgndN(m_pIRELine);
			m_pTxtLine1->EnableMsg(false);
			m_pGrpIpodList->AddChild(m_pTxtLine1);
		}
		m_pTxtLine2 = new HCTextCtrl;
		if(m_pTxtLine2 != NULL)
		{	
			m_pTxtLine2->Create(16,208,724,2);
			m_pTxtLine2->SetBkgndN(m_pIRELine);
			m_pTxtLine2->EnableMsg(false);
			m_pGrpIpodList->AddChild(m_pTxtLine2);
		}
		m_pTxtLine3 = new HCTextCtrl;
		if(m_pTxtLine3 != NULL)
		{
			m_pTxtLine3->Create(16,274,724,2);
			m_pTxtLine3->SetBkgndN(m_pIRELine);
			m_pTxtLine3->EnableMsg(false);
			m_pGrpIpodList->AddChild(m_pTxtLine3);
		}
		m_pTxtLine4 = new HCTextCtrl;
		if(m_pTxtLine4 != NULL)
		{
			m_pTxtLine4->Create(16,340,724,2);
			m_pTxtLine4->SetBkgndN(m_pIRELine);
			m_pTxtLine4->EnableMsg(false);
			m_pGrpIpodList->AddChild(m_pTxtLine4);
		}
			m_pTxtLine5 = new HCTextCtrl;
			if(m_pTxtLine5 != NULL)
			{
				m_pTxtLine5->Create(16,406,724,2);
				m_pTxtLine5->SetBkgndN(m_pIRELine);
				m_pTxtLine5->EnableMsg(false);
				m_pGrpIpodList->AddChild(m_pTxtLine5);
			}
	}
	m_pScrboxIpodList = new HCScrollBox;
	if(m_pScrboxIpodList != NULL)
	{
		m_pScrboxIpodList->Create(16,78,736,396);
		m_pScrboxIpodList->SetTextColorN(255, 255, 255);//设置字体颜色
		m_pScrboxIpodList->SetTextColorA(255, 255, 255);//设置字体颜色
		m_pScrboxIpodList->SetFontSize(24, 24);//设置字体的大小
		//m_pScrBoxPariedDevices->SetCallBackSelectItemChange(OnSelectDeviceChange,this);
		AddChild(m_pScrboxIpodList);
		m_pScrboxIpodList->SetCallBackClick(OnScrboxIpodList,this);
		m_pScrboxIpodList->EnableScrollLine(true,66,NULL);
		m_pScrboxIpodList->SetShow(false);
		//m_pScrctrlIpodList= new HCScrollCtrl;//配对设备滑块
		//if(m_pScrctrlIpodList != NULL)
		//{
		//	m_pScrctrlIpodList->Create(756,134,28,280,1);
		//	m_pScrctrlIpodList->SetBound(0,0);
		//	//m_pScrctrlIpodList->SetBkgndN();
		//	m_pScrctrlIpodList->SetBkgndN(GetHMIPath(_T("Share\\Share_Slide_N.hfp")));
		//	m_pScrctrlIpodList->SetBkgndA(GetHMIPath(_T("Share\\Share_Slide_Bar.hfp")));
		//	m_pScrctrlIpodList->SetBkgndD(GetHMIPath(_T("Share\\Share_Slide_A.hfp")));
		//	m_pScrctrlIpodList->SetBkgndF(GetHMIPath(_T("Share\\Share_Slide_Bar.hfp")));
		//	m_pGrpIpodList->AddChild(m_pScrctrlIpodList);
		//	m_pScrctrlIpodList->SetScrollBox(m_pScrboxIpodList,6);
		//}
		//配对设备本向上按钮
		//m_pBtnIpodListUp= new HCButton;
		//if(m_pBtnIpodListUp != NULL)
		//{
		//	m_pBtnIpodListUp->Create(750, 102, 40, 36);
		//	m_pBtnIpodListUp->EnableMsg(true);
		//	m_pBtnIpodListUp->SetShow(true);
		//	m_pBtnIpodListUp->SetBkgndN(GetHMIPath(_T("Share\\Share_Front_N.hfp")));
		//	m_pBtnIpodListUp->SetBkgndA(GetHMIPath(_T("Share\\Share_Front_A.hfp")));
		//	m_pGrpIpodList->AddChild(m_pBtnIpodListUp);
		//}
		////配对设备向下按钮
		//m_pBtnIpodListDown= new HCButton;
		//if(m_pBtnIpodListDown != NULL)
		//{
		//	m_pBtnIpodListDown->Create(750, 406, 40, 36);
		//	m_pBtnIpodListDown->EnableMsg(true);
		//	m_pBtnIpodListDown->SetShow(true);
		//	m_pBtnIpodListDown->SetBkgndN(GetHMIPath(_T("Share\\Share_Last_N.hfp")));
		//	m_pBtnIpodListDown->SetBkgndA(GetHMIPath(_T("Share\\Share_Last_A.hfp")));
		//	m_pGrpIpodList->AddChild(m_pBtnIpodListDown);
		//	m_pScrctrlIpodList->SetAddButton(m_pBtnIpodListUp,m_pBtnIpodListDown);
		//}
		//m_pScrboxIpodList->SetCallBackClick(OnScrBoxPariedDevices,this);
	}
	m_pScrboxIpodAlbumList = new HCScrollBox;
	if(m_pScrboxIpodAlbumList != NULL)
	{
		m_pScrboxIpodAlbumList->Create(16,78,736,396);
		m_pScrboxIpodAlbumList->SetTextColorN(255, 255, 255);//设置字体颜色
		m_pScrboxIpodAlbumList->SetTextColorA(255, 255, 255);//设置字体颜色
		m_pScrboxIpodAlbumList->SetFontSize(24, 24);//设置字体的大小
		AddChild(m_pScrboxIpodAlbumList);
		m_pScrboxIpodAlbumList->SetCallBackClick(OnScrboxIpodList,this);
		m_pScrboxIpodAlbumList->EnableScrollLine(true,66,NULL);
		m_pScrboxIpodAlbumList->SetShow(false);
		m_pScrboxIpodAlbumList->EnableMove(true);
	}
	m_pScrboxIpodTrackList = new HCScrollBox;
	if(m_pScrboxIpodTrackList != NULL)
	{
		m_pScrboxIpodTrackList->Create(16,78,736,396);
		m_pScrboxIpodTrackList->SetTextColorN(255, 255, 255);//设置字体颜色
		m_pScrboxIpodTrackList->SetTextColorA(255, 255, 255);//设置字体颜色
		m_pScrboxIpodTrackList->SetFontSize(24, 24);//设置字体的大小
		AddChild(m_pScrboxIpodTrackList);
		m_pScrboxIpodTrackList->SetCallBackClick(OnScrboxIpodList,this);
		m_pScrboxIpodTrackList->EnableScrollLine(true,66,NULL);
		m_pScrboxIpodTrackList->SetShow(false);
		m_pScrboxIpodTrackList->EnableMove(true);
	}
	m_pTxtIpodBk = new HCImageCtrl;
	if(m_pTxtIpodBk != NULL)
	{
	  m_pTxtIpodBk->Create(0,70,800,268);
	  m_pTxtIpodBk->SetBkgndN(GetHMIPath(_T("iPod\\05-USB-media-music-01_02.hfp")));
	  m_pTxtIpodBk->EnableMsg(false);
	  m_pGrpMid->AddChild(m_pTxtIpodBk);
	}
	m_pGrpBtm = new HCGroupCtrl;
	if(m_pGrpBtm != NULL)
	{
		m_pGrpBtm->Create(0,412,800,68);
		m_pGrpBtm->EnableMsg(true);
		m_pGrpBtm->SetBackGround(GetHMIPath(_T("Share\\Share_Frame_Bottom 02.hfp")));
		AddChild(m_pGrpBtm);
	}
	/*m_pTxtSongHead = new HCTextCtrl;
	if(m_pTxtSongHead !=NULL)
	{
		m_pTxtSongHead->Create(300,115,70,24);
		m_pTxtSongHead->EnableMsg(true);
		m_pTxtSongHead->SetTextStyle(RE_TS_NORMAL);
		m_pTxtSongHead->SetTextPos(0,0);
		m_pTxtSongHead->SetFontSize(24,24);
		m_pTxtSongHead->SetRoll(false);
		m_pTxtSongHead->SetTxtColor(255,255,255);
		m_pGrpMid->AddChild(m_pTxtSongHead);
	}*/
	m_pTxtSong = new HCTextCtrl;
	if(m_pTxtSong != NULL)
	{
		m_pTxtSong->Create(370,115,350,24);
		m_pTxtSong->EnableMsg(true);
		m_pTxtSong->SetTextStyle(RE_TS_NORMAL);
		m_pTxtSong->SetTextPos(0,0);
		m_pTxtSong->SetFontSize(24,24);
		m_pTxtSong->SetRoll(true);
		m_pTxtSong->SetRollWidth(330);
		m_pTxtSong->SetTxtColor(255,255,255);
		 m_pGrpMid->AddChild(m_pTxtSong);
	}
	/*m_pTxtArtistHead = new HCTextCtrl;
	if(m_pTxtArtistHead != NULL)
	{
		m_pTxtArtistHead->Create(300,227,85,24);
		m_pTxtArtistHead->EnableMsg(false);
		m_pTxtArtistHead->SetTextStyle(RE_TS_NORMAL);
		m_pTxtArtistHead->SetTextPos(0,0);
		m_pTxtArtistHead->SetFontSize(24,24);
		m_pTxtArtistHead->SetRoll(false);
		m_pTxtArtistHead->SetTxtColor(255,255,255);
		m_pGrpMid->AddChild(m_pTxtArtistHead);
	}*/
	m_pTxtArtist = new HCTextCtrl;
	if(m_pTxtArtist != NULL)
	{
		m_pTxtArtist->Create(370,171,350,24);
		m_pTxtArtist->EnableMsg(true);
		m_pTxtArtist->SetTextStyle(RE_TS_NORMAL);
		m_pTxtArtist->SetTextPos(0,0);
		m_pTxtArtist->SetFontSize(24,24);
		m_pTxtArtist->SetRoll(true);
		m_pTxtArtist->SetRollWidth(330);
		m_pTxtArtist->SetTxtColor(255,255,255);
		 m_pGrpMid->AddChild(m_pTxtArtist);
	}
	/*m_pTxtAbumHead = new HCTextCtrl;
	if(m_pTxtAbumHead != NULL)
	{
		m_pTxtAbumHead->Create(300,171,70,24);
		m_pTxtAbumHead->EnableMsg(false);
		m_pTxtAbumHead->SetTextStyle(RE_TS_NORMAL);
		m_pTxtAbumHead->SetTextPos(0,0);
		m_pTxtAbumHead->SetFontSize(24,24);
		m_pTxtAbumHead->SetRoll(false);
		m_pTxtAbumHead->SetTxtColor(255,255,255);
		m_pGrpMid->AddChild(m_pTxtAbumHead);
	}*/
	m_pTxtAbum = new HCTextCtrl;
	if(m_pTxtAbum != NULL)
	{
		m_pTxtAbum->Create(370,227,350,24);
		m_pTxtAbum->EnableMsg(true);
		m_pTxtAbum->SetTextStyle(RE_TS_NORMAL);
		m_pTxtAbum->SetTextPos(0,0);
		m_pTxtAbum->SetFontSize(24,24);
		m_pTxtAbum->SetRoll(true);
		m_pTxtAbum->SetRollWidth(330);
		m_pTxtAbum->SetTxtColor(255,255,255);
		 m_pGrpMid->AddChild(m_pTxtAbum);
	}
	m_pBtnPlayPause = new HCButton;
	if(m_pBtnPlayPause != NULL)
	{
		m_pBtnPlayPause->Create(182 + ICONGAP*2,422,64,60);
		m_pBtnPlayPause->SetFontSize(24,24);
		//m_pBtnPlayPause->SetText(L"暂停");
		m_pBtnPlayPause->EnableMsg(true);
		//m_pBtnPlayPause->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Pause_N.hfp")));
		m_pBtnPlayPause->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Pause_N.hfp")));
		m_pBtnPlayPause->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Pause_A.hfp")));
		m_pBtnPlayPause->SetCallBack(OnPlayPause,this);
		m_pGrpBtm->AddChild(m_pBtnPlayPause);
	}
	m_pBtnNext = new HCButton;
	if(m_pBtnNext != NULL)
	{
		m_pBtnNext->Create(318+ICONGAP*3,422,64,60);
		//m_pBtnNext->SetFontSize(24,24);
		//m_pBtnNext->SetText(L"下一曲");
		m_pBtnNext->EnableMsg(true);
	    //m_pBtnNext->SetBkgndN(GetHMIPath(_T("iPod\\Media_Next_N.hfp")));
		//m_pBtnNext->SetBkgndA(GetHMIPath(_T("iPod\\Media_Next_A.hfp")));
		m_pBtnNext->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Next_N.hfp")));
		m_pBtnNext->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Next_A.hfp")));
		m_pBtnNext->SetCallBack(OnForward,this);
		//m_pBtnNext->SetCallBackLongPress(OnFF,this);
		//m_pBtnNext->SetCallBackLongPressUp(OnEndFFRew,this);
		m_pGrpBtm->AddChild(m_pBtnNext);
	}
	m_pBtnPre = new HCButton;
	{
			m_pBtnPre->Create(50+ICONGAP,420,64,60);
			m_pBtnPre->EnableMsg(true);
			m_pBtnPre->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Prev_N.hfp")));
			m_pBtnPre->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Prev_A.hfp")));
			//m_pBtnPre->SetCallBackLongPress(OnStartRew,this);
			m_pBtnPre->SetCallBack(OnBack,this);
			//m_pBtnPre->SetCallBackLongPressUp(OnEndFFRew,this);
			m_pGrpBtm->AddChild(m_pBtnPre);
	}
	m_pBtnGetShuffle = new HCButton;
	if(m_pBtnGetShuffle != NULL)
	{
		m_pBtnGetShuffle->Create(444+ICONGAP*4,420,64,60);
		m_pBtnGetShuffle->SetFontSize(24,24);
		//m_pBtnGetShuffle->SetText(L"循环");
		m_pBtnGetShuffle->EnableMsg(true);
		//m_pBtnGetShuffle->SetBkgndN(GetHMIPath(_T("Media\\Music\\Music_Close_Random_N.hfp")));
		m_pBtnGetShuffle->SetBkgndN(GetHMIPath(_T("Media\\Music\\Music_Close_Random_N.hfp")));
		m_pBtnGetShuffle->SetCallBack(OnSetShuffle,this);
		m_pGrpBtm->AddChild(m_pBtnGetShuffle);
	}
	m_pBtnGetrepeat = new HCButton;
	if(m_pBtnGetrepeat != NULL)
	{
		m_pBtnGetrepeat->Create(575 + ICONGAP*5,420,64,60);
		m_pBtnGetrepeat->SetFontSize(24,24);
		//m_pBtnGetrepeat->SetText(L"重复");
		m_pBtnGetrepeat->EnableMsg(true);
		//m_pBtnGetrepeat->SetBkgndN(GetHMIPath(_T("Media\\Music\\Music_Search_N.hfp")));
		m_pBtnGetrepeat->SetBkgndN(GetHMIPath(_T("Ipod\\Music_Folder_n.hfp")));
		m_pBtnGetrepeat->SetCallBack(OnSetRepeat,this);
		m_pGrpBtm->AddChild(m_pBtnGetrepeat);
	}
	m_pBtnPlayList = new HCButton;
	if(m_pBtnPlayList != NULL)
	{
		m_pBtnPlayList->Create(714,420,64,60);
		m_pBtnPlayList->SetFontSize(24,24);
		//m_pBtnGetrepeat->SetText(L"重复");
		m_pBtnPlayList->EnableMsg(false);
		m_pBtnPlayList->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_List_N.hfp")));
		m_pBtnPlayList->SetCallBack(OnIpodList,this);
#if TESTIPODLIST
      m_pGrpBtm->AddChild(m_pBtnPlayList);
#endif
		
	}
	m_pSldPlayTime = new HCSlideCtrl;
	if(m_pSldPlayTime != NULL)
	{
		m_pSldPlayTime->Create(100,375,600,28,0,0);
		m_pSldPlayTime->SetBkgndS(GetHMIPath(_T("Media\\Share\\Media_Slide_A.hfp")));
		m_pSldPlayTime->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Slide_N.hfp")));
	    m_pSldPlayTime->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Slide_Bar.hfp")));
		m_pSldPlayTime->SetDotgndA(GetHMIPath(_T("Media\\Share\\Media_Slide_Bar.hfp")));
		m_pSldPlayTime->EnableMoveSlider(false);
		 m_pGrpMid->AddChild(m_pSldPlayTime);
		//m_pSldPlayTime->SetBkgndS(GetHMIPath(_T("Media\\Share\\Media_List_N.hfp")));
	}
	m_pTxtCurrentPlayTime = new HCTextCtrl;
	if(m_pTxtCurrentPlayTime != NULL)
	{
		m_pTxtCurrentPlayTime->Create(10,375,90,24);
		m_pTxtCurrentPlayTime->SetFontSize(24,24);
		m_pTxtCurrentPlayTime->SetText(L" ");
		m_pTxtCurrentPlayTime->SetTextStyle(RE_TS_RIGHT);
		m_pTxtCurrentPlayTime->EnableMsg(false);
		 m_pGrpMid->AddChild(m_pTxtCurrentPlayTime);
	}
	m_pTxtTrackTotalTime = new HCTextCtrl;
	if(m_pTxtTrackTotalTime != NULL)
	{
		m_pTxtTrackTotalTime->Create(700,375,90,24);
		m_pTxtTrackTotalTime->SetFontSize(24,24);
		m_pTxtTrackTotalTime->SetText(L" ");
		m_pTxtTrackTotalTime->SetTextStyle(RE_TS_NORMAL);
		m_pTxtTrackTotalTime->EnableMsg(false);
		 m_pGrpMid->AddChild(m_pTxtTrackTotalTime);
	}
	m_pTxtCurrentIndex = new HCTextCtrl;
	if(m_pTxtCurrentIndex != NULL)
	{
		m_pTxtCurrentIndex->Create(325,295,160,30);
		m_pTxtCurrentIndex->SetFontSize(30,30);
		m_pTxtCurrentIndex->SetText(L" ");
		m_pTxtCurrentIndex->SetTextColorN(255,255,255);
		m_pTxtCurrentIndex->EnableMsg(false);
		 m_pGrpMid->AddChild(m_pTxtCurrentIndex);
	}
	m_pTxtArtistPic = new HCTextCtrl;
	if(m_pTxtArtistPic != NULL)
	{
		//m_pTxtArtistPic->Create(90,130,128,128);
		m_pTxtArtistPic->Create(60,85,240,240);
		m_pTxtArtistPic->SetShow(true);
		m_pTxtArtistPic->SetBkgndN(m_pIREArtistBk);
		//m_pGrpMid->AddChild(m_pTxtArtistPic);
		AddChild(m_pTxtArtistPic);
	}
	m_pTxtInfoFrame = new HCTextCtrl;
	if(m_pTxtInfoFrame != NULL)
	{
		m_pTxtInfoFrame->Create(160,140,500,220);
		m_pTxtInfoFrame->SetBkgndN(m_pIREInfoFrame);
		//AddChild(m_pTxtInfoFrame);
	}
	m_pTxtCover = new HCTextCtrl;
	if(m_pTxtCover != NULL)
	{
		m_pTxtCover->Create(0,0,m_width,m_height);
		m_pTxtCover->SetFillType(FT_LINEAR_ALPHAV);
		m_pTxtCover->SetFillColor(125,125,0);
		m_pTxtCover->SetShow(false);
		m_pTxtCover->EnableBeep(false);
		//AddChild(m_pTxtCover);
	}
	m_pTxtInfo = new HCTextCtrl;
	if(m_pTxtInfo != NULL)
	{
		m_pTxtInfo->Create(300,225,200,30);
		m_pTxtInfo->SetFontSize(24,24);
		//m_pTxtDownLoading->SetTextStyle(RE_TS_CENTER);
		m_pTxtInfo->SetTextPos(0,5);
		m_pTxtInfo->EnableMsg(false);
		m_pTxtInfo->SetTxtColor(255,255,255);
		//m_pTxtDownLoading->SetText(L"下载中请稍后……");
		//AddChild(m_pTxtInfo);
	}

#if TESTIPODINSERTEVENT
	m_pBtnIpodInsert = new HCButton;
	if(m_pBtnIpodInsert != NULL)
	{
		m_pBtnIpodInsert->Create(400,300,50,50);
		m_pBtnIpodInsert->SetText(L"Insert");
		m_pBtnIpodInsert->SetFontSize(24,24);
		m_pBtnIpodInsert->SetCallBack(OnInsert,this);
		//AddChild(m_pBtnIpodInsert);
	}
#endif    
	KDialogP::OnInit();

	m_bListThreadRun = true;
	m_ctLoadData.SetCallBack(OnLoadData,this);
	AddTimer(&m_ctLoadData);
	m_ctPic.SetCallBack(CombinaPic,this);
	AddTimer(&m_ctPic);
	m_ctButton.SetCallBack(OnRealseButton,this);
	AddTimer(&m_ctButton);
	//m_pScrboxIpodList = new HCScrollBox;
	//if(m_pScrboxIpodList != NULL)
	//{
	//	m_pScrboxIpodList->Create(14,74,736,330);
	//	m_pScrboxIpodList->SetTextColorN(255, 255, 255);//设置字体颜色
	//	m_pScrboxIpodList->SetTextColorA(255, 255, 255);//设置字体颜色
	//	m_pScrboxIpodList->SetFontSize(24, 24);//设置字体的大小
	//	bool bb = m_pScrboxIpodList->EnableScrollLine(true,60,NULL);
	//	AddChild(m_pScrboxIpodList);
	//}
	m_hGetSongInfoThread = 0;
	InitHeadCtrl();
	InitPopupCtrl();
	
	for (size_t i=0;i<(sizeof(m_pTxt_Popup_Infor)/sizeof(m_pTxt_Popup_Infor[0]));i++)
	{
		if( NULL != m_pTxt_Popup_Infor[i] )
		{
			IPODDEBEGINFO(L"!!!!!!!!!!!!!!");
			m_pTxt_Popup_Infor[i]->SetTextStyle(RE_TS_NORMAL);
			m_pTxt_Popup_Infor[i]->SetTextPos(50,0);
			m_pTxt_Popup_Infor[i]->SetFontSize(30,30);
			m_pTxt_Popup_Infor[i]->EnableMsg(false);
		}
	}
	InitializeCriticalSection(&m_csThread);
	SETUPSETTING LSetting;
	KCLastMemory::GetInstance()->GetSetupMemory(LSetting);
	IPODDEBEGINFO(L"LSetting.cLang = %d",LSetting.cLang);
	switch (LSetting.cLang)
	{
		case 0:
		{
			ChangeLangue(0);
		}
		break;
		case 1:
		{
			ChangeLangue(1);
		}
		break;
		default:
		break;
	}
	m_hIpodInsert = CreateEvent(NULL,TRUE,false,L"IPODInsert");
	if(m_hIpodInsert == NULL)
	{
		IPODDEBEGINFO(L"CreateEvent:IPODInsert Failed");
		return 0;
	}
	m_bIpodReady = false;
	m_hIpodReady = NULL;
	m_hIpodReady = CreateEvent( NULL, TRUE, FALSE, TEXT("IPOD_READY"));
	if(m_hIpodReady == NULL)
	{
		IPODDEBEGINFO(L"CreateEvent Failed,lasterror = %d",GetLastError());
	}
	m_pGrpIpodList->SetShow(false);
//	m_pScrctrlIpodList->SetShow(false);
	m_ntrackIndex = -1;//歌曲索引
	m_ntrackLength = 0;//歌曲长度
	m_ntrackPosition = 0;//歌曲位置
	m_nDowningTime = 0;
	m_nPlayStatus = PLAYSTATUS_STOPPED;//播放状态
	m_ptrackTitle =  new WCHAR[100];//歌曲名称
	m_partistName = new WCHAR[100];//艺术家
	m_palbumName = new WCHAR[100];//专辑名字
	m_ntrackNum = 0;//
	m_shuffleStatus = SHUFFLE_OFF;
	m_repeatStatus = REPEAT_OFF;
	m_bConnected = false;
	m_pIREArtist = NULL;
	m_bRun = true;
	m_bFFREW = false;
	m_bIpodListShow = false;
	m_iPicDirection = 0;
	m_pIREArtistPre = NULL;
	m_ntrackNum = 0;//shuffle off 歌曲总数
	m_nAlbumTotalNum = 0;//album 歌曲总数
	m_ntrackTotalNum = 0;//Track 歌曲总数
	m_nOffListNum = 0;
	m_nTrackListNum = 0;
	m_nAlbumListNum = 0;
	m_nPretrackNum = 0;
	m_bInsert = false;
	m_pArtistPic = new unsigned char[128*128*3];
	memset(m_pArtistPic,0,128*128*3);
	m_pArtistPicPre = new unsigned char[128*128*3];
	memset(m_pArtistPicPre,0,128*128*3);
	 m_bUpdateThread = true;
	 m_bShuffleChange = false;
	// m_pIREArtist =  GetRESingleton()->CreateSurface(128, 128, RE_COLOR565);
	 m_pIREStr =  GetRESingleton()->CreateSurface(240, 240, RE_COLOR565);
	 if(m_pIREArtist == NULL)
	 {
		IPODDEBEGINFO(L"m_pIREArtist == null");
	 }
	 OnLoadDataEx(NULL);
	 OnInsert(NULL);
	//m_bContiue = true;
	//m_bInsert = false;
//	m_hMonitorIpodEventThread = CreateThread(NULL,0,((LPTHREAD_START_ROUTINE)MonitorIpodEventThread),NULL,0,NULL);
	return 0;
}
 void CIpodDlg::ChangeLangue(HINT nType)
{
	if(nType == 0)
	{
		s_pLan = m_ChLan.szContent;
	}
	else
	{
		s_pLan = m_EnLan.szContent;
	}
	if(s_pLan != NULL)
	{
		//BTDEBUGINFO(L"HCBTMusicDlg::%s,%d",__FUNCTIONW__,nType);
		switch(nType)
		{
		case 0:
			{
				m_pTxtScreen->SetFontSize(24,24);
				m_pTxtArtist->SetFontSize(24,24);
				m_pTxtSong->SetFontSize(24,24);
				m_pTxtAbum->SetFontSize(24,24);
			/*	m_pTxtArtistHead->SetFontSize(24,24);
				m_pTxtSongHead->SetFontSize(24,24);
				m_pTxtAbumHead->SetFontSize(24,24);*/
				m_pTxtScreen->SetText(L"iPod");
				m_pTxtSong->SetText(L"未知歌曲");
				m_pTxtArtist->SetText(L"未知艺术家");
				m_pTxtAbum->SetText(L"未知专辑");	
			}
			break;
		case 1:
			{
				m_pTxtScreen->SetFontSize(24,24);
				m_pTxtArtist->SetFontSize(20,20);
				m_pTxtSong->SetFontSize(20,20);
				m_pTxtAbum->SetFontSize(20,20);
				/*m_pTxtArtistHead->SetFontSize(20,20);
				m_pTxtSongHead->SetFontSize(20,20);
				m_pTxtAbumHead->SetFontSize(20,20);*/
				m_pTxtScreen->SetText(L"iPod");
				m_pTxtSong->SetText(L"Unknow Song");
				m_pTxtArtist->SetText(L"Unknow Artist");
				m_pTxtAbum->SetText(L"Unknow Album");
			}
			break;
		default:
			break;
		}
		m_pTxtSong->SetText(s_pLan[0]);
		m_pTxtArtist->SetText(s_pLan[1]);
		m_pTxtAbum->SetText(s_pLan[2]);	
	/*	m_pTxtSongHead->SetText(s_pLan[10]);
		m_pTxtArtistHead->SetText(s_pLan[11]);
		m_pTxtAbumHead->SetText(s_pLan[12]);	*/
		//m_pBtnPre->SetText(s_pLan[3]);
		//m_pBtnNext->SetText(s_pLan[4]);
		//m_pBtnPlayPause->SetText(s_pLan[5]);
		//m_pBtnGetShuffle->SetText(s_pLan[8]);
		//m_pBtnGetrepeat->SetText(s_pLan[7]);
		UpdataRepeatIcon(m_repeatStatus);
		UpdataShuffleIcon(m_shuffleStatus);
		//m_pBtnPlayList->SetText(s_pLan[9]);
		m_pTxtInfo->SetText(s_pLan[13]);
		switch (m_nPlayStatus)
		{
			case PLAYSTATUS_PLAYING:
			{
				//m_pBtnPlayPause->SetText(s_pLan[6]);
			}
			break;
			default:
				{
					//m_pBtnPlayPause->SetText(s_pLan[5]);
				}
				break;
		}
	}
}
 HBOOL CIpodDlg::DoMessage(HMessage* msg)
{
	HBOOL bRet = KDialogP::DoMessage(msg);
	return bRet;
}
 void CIpodDlg::RequreSource()
{
	HString strTmp;
	SETUPSETTING Setting;
	// 设置背景
	KCLastMemory::GetInstance()->GetSetupMemory(Setting);
	SetBackGround(GetHMIPath((HCHAR*)&Setting.szBkgndPath));
	if(m_pIREInfoFrame == NULL)
	{
		strTmp = GetHMIPath(_T("")).c_str(); //GetHMIPath(_T("")).c_str();
		strTmp += _T("Share\\Share_Info_Frame.hfp");
		m_pIREInfoFrame  = GetRESingleton()->CreateSurfaceFromFile(strTmp);
	}
	if(m_pIREInfoFrame != NULL)
	{
		m_pTxtInfoFrame->SetBkgndN(m_pIREInfoFrame);
	}
}
 void CIpodDlg::ReleaseSource()
{
	SetBackGround(NULL);
	m_pTxtInfoFrame->SetBkgndN(NULL);
	SAFE_DELETE(m_pIREInfoFrame);
}
void CIpodDlg::SetIpodDlgBackGround()
{
}
 void CIpodDlg::OnPlayPause(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnPlayPause(pObj);
}
void CIpodDlg::OnPlayPause(void* pDlg)
{
	if(m_bConnected == true)
	{
		ipodctlERR ERR;
		if(m_bFFREW)
		{
			ERR =  ipodctl_EndFFRew() ;
			if(ERR == ERR_OK)
			{
				m_bFFREW = false;
			}
		}
		else
		{
			ERR =  ipodctl_PlayPause() ;
			if(ERR == ERR_OK)
			{
				m_bFFREW = false;
			}
		}
		IPODDEBEGINFO(L"%s,err = %d",__FUNCTIONW__,ERR);
	}
}
 void CIpodDlg::OnPlayMute(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnPlayMute(pObj);
}
void CIpodDlg::OnPlayMute(void* pDlg)
{
}
 void CIpodDlg::OnForward(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnForward(pObj);
}
void CIpodDlg::OnForward(void* pDlg)
{
	if((!m_bButtonPress) && m_bConnected)
	{
		ipodctlERR err =  ipodctl_NextTrack();
		if(m_ctButton.IsActive())
		{
			m_ctButton.StopTimer();
		}
		m_ctButton.SetTime(60);
		m_ctButton.StartTimer();
		if(err == ERR_OK)
		{
			//UpDataMediaInfo();
		}
		m_bButtonPress = true;
		IPODDEBEGINFO(L"%s,err = %d",__FUNCTIONW__,err);
	}
}
 void CIpodDlg::OnBack(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnBack(pObj);
}
void CIpodDlg::OnBack(void* pDlg)
{
	if(!m_bButtonPress && m_bConnected)
	{
		ipodctlERR err =  ipodctl_PreviousTrack();
		if(err == ERR_OK)
		{
			//UpDataMediaInfo();
		}
		IPODDEBEGINFO(L"%s,err = %d",__FUNCTIONW__,err);
		if(m_ctButton.IsActive())
		{
			m_ctButton.StopTimer();
		}
		m_ctButton.SetTime(60);
		m_ctButton.StartTimer();
		m_bButtonPress = true;
	}
}

HINT CIpodDlg::UpDataMediaInfoEx(void)
{
	if(m_hUpdataThread != 0)
	{
		int nPirorty = CeGetThreadPriority(m_hUpdataThread);
		IPODDEBEGINFO(L"UpdataIpodInfoThread:nPirorty = %d",nPirorty);
	}
	ipodctlERR err = ERR_FAIL;
	unsigned long nCurrentIndex,nTotalNum;
	while (m_bRun)
	{
		if(m_nFailed >= 40)
		{
			 m_bRun = false;
			 ResetEvent(m_hIpodInsert);
			m_ctLoadData.StopTimer();
			PostMessage(m_hMyHandle,WM_USER + 16,0,0);
	/*		SetPopupInfor(s_pLan[23]);
			ShowPopup(PT_NOR, 30);*/
		}
		if(m_bRun)
		{
		DWORD dwWaitResult = 0;
		dwWaitResult =  WaitForSingleObject(m_hIpodInsert,INFINITE);
		IPODDEBEGINFO(L"dwWaitResult = %d",dwWaitResult);
		if(dwWaitResult == WAIT_OBJECT_0)
		{
		//if(m_bUpdateThread)
		{
		//	EnterCriticalSection(&m_csThread);
			if(!m_pTxtArtistPic->IsShow() && !m_bIpodListShow)
			{
				m_pTxtArtistPic->SetShow(true);
			}
			DWORD nTime = GetTickCount();
			//err = ipodctl_PlayPause();
			if(m_nTimes > 0 && m_bRun)
			{
					IPODDEBEGINFO(L"ipodctl_GetPlayStatus::888888nCost = %d",GetTickCount() - nTime);
					WaitForSingleObject(m_hIpodReady,INFINITE);
					IPODDEBEGINFO(L"ipodctl_GetPlayStatus::89999999nCost = %d",GetTickCount() - nTime);
					err = ipodctl_GetPlayStatus(&nCurrentIndex,&m_ntrackLength,&m_ntrackPosition,&m_nPlayStatus);
					IPODDEBEGINFO(L"ipodctl_GetPlayStatus::nCost = %d",GetTickCount() - nTime);
			}
			else
			{
					err = ERR_NOTINIT;
			}
		if(m_IpodPreERR == ERR_IPODEXIT && err == ERR_OK)
		 {
			 // ::PostMessage(m_hMyHandle,WM_USER + 5,0,NULL);//Ipod重新插入
		 }
		if((m_IpodPreERR == ERR_OK) && ((err == ERR_FAIL) || (err == ERR_IPODEXIT)))
		 {
			 // ::PostMessage(m_hMyHandle,WM_USER + 6,0,NULL);
		 }
		m_IpodPreERR = err;
		IPODDEBEGINFO(L"m_bConnected = %d,m_ntrackIndex = %d",m_bConnected,m_ntrackIndex);
		IPODDEBEGINFO(L"%s,err = %d,nCurrentIndex = %d,m_pntrackLength = %d,m_pntrackPosition = %d,m_nplayStatus = %d",__FUNCTIONW__,err,nCurrentIndex,m_ntrackLength,m_ntrackPosition,m_nPlayStatus);
		switch (err)
		 {
			case ERR_OK:
			 {
				 static bool s_bFirst111 = true;
			/*	 if(s_bFirst111)
				 {
					 DWORD dwThreadID111;
					m_hGetSongInfoThread = CreateThread(NULL,0,GetIpodListsThread,this,0,&dwThreadID111);
					s_bFirst111 = FALSE;
				 }*/
				 
				 m_nTimes++;
				 m_nFailed = 0; 
				 if(m_bConnected == false && m_bRun)
				 {
					 IPODDEBEGINFO(L"++++++++First Ok !!!!!+++++");
					 ipodctlERR err1;
					// m_pBtnGetShuffle->EnableMsg(false);
					 // err1=  ipodctl_SetShuffle(SHUFFLE_OFF);
					 // err1 = ipodctl_StartPlay(PAGE_PLAYLIST,0,0);
                      PostMessage(m_hMyHandle,WM_USER + 15,0,0);
					 DWORD dwThreadID;
					// m_hGetSongInfoThread = CreateThread(NULL,0,GetIpodListsThread,this,0,&dwThreadID);
					 IPODDEBEGINFO(L"GetIpodListsThread::dwThreadID = %d",dwThreadID);
					 m_bConnected = true;
					 IPODDEBEGINFO(L"ipodctl_StartPlay:err1 = %d",err1);
					 continue;
				 }		
				 unsigned long nTotal;
				  err =  ipodctl_GetPlayingTrackNum(&nTotal);//曲目总数
				 PostMessage(m_hMyHandle,WM_USER + 15,0,0);
				
				 if(m_nPlayStatus != m_nPreplayStatus && m_bRun)
				 {
					 PostMessage(m_hMyHandle,WM_USER + 14,m_nPlayStatus,0);
					 m_nPreplayStatus = m_nPlayStatus;
				 }
				 unsigned long nn = 0;
				// EnterCriticalSection(&m_csThread);
				// err = ipodctl_GetPlayingTrackNum(&nTotalNum);
				//EnterCriticalSection(&m_csThread);
				 switch(m_shuffleStatus)
				 {
					case SHUFFLE_OFF:
					 {
						nn =  m_ntrackNum;
					 }
					 break;
					 case SHUFFLE_ALBUMS:
						{
							nn = m_nAlbumTotalNum;
						}
						break;
						case SHUFFLE_TRACKS:
						{
							nn =m_ntrackTotalNum;
						}
						break;
					 default:
					 break;
				 }
				 if(nCurrentIndex == 0)
				 {
                     s_nnCount ++;
					 if(s_nnCount >= 5)
					 {
						 m_bShuffleChange = true;
						 s_nnCount = 0;
					 }
				 }
				 else
				 {
                     s_nnCount = 0;
				 }
				// if(nCurrentIndex != m_ntrackIndex || nTotalNum != nn || m_bShuffleChange == true)
				 if(nCurrentIndex != m_ntrackIndex || m_bShuffleChange == true)
				 {
					 if(nCurrentIndex > m_ntrackIndex)
					 {
						 m_iPicDirection = 0;
					 }
					 else
					 {
						 m_iPicDirection = 1;
					 }
					 m_ntrackIndex = nCurrentIndex;
					 if(m_bConnected && m_bInsert && m_ntrackIndex != -1)
					 {
						 
							 err =  ipodctl_GetTrackInfo(nCurrentIndex,m_ptrackTitle,m_partistName,m_palbumName);
							 if(m_pSongInfo != NULL)
							 {
								 memset(m_pSongInfo,0,sizeof(sSongInfo));
								 m_pSongInfo->nIndex = nCurrentIndex;
								 m_pSongInfo->nTotal = nTotal;
								 
								 memcpy(m_pSongInfo->szTitle,m_ptrackTitle,100);
								 memcpy(m_pSongInfo->szArtist,m_partistName,100);
								 memcpy(m_pSongInfo->szAlbum,m_palbumName,100);
								 PostMessage(m_hMyHandle,WM_USER + 17,(WPARAM)m_pSongInfo,0);
							 }
							//UpdataSongInfo(m_ntrackIndex);
							//PostMessage(m_hMyHandle,WM_USER + 13,m_ntrackIndex,0);
					 }
					 m_bShuffleChange = false;
				 }
				 ipodctlERR eErrGet = ERR_FAIL;

				 ipodctlSHUFFLE eGetShuffle;
				 eErrGet = ipodctl_GetShuffle(&m_shuffleStatus);
				 if(eErrGet == ERR_OK)
				 {
					 //UpdataShuffleIcon(eGetShuffle);
					 PostMessage(m_hMyHandle,WM_USER + 11,(WPARAM)m_shuffleStatus,0);
				 }
				 ipodctlREPEAT eGetRpeat;
				 eErrGet = ipodctl_GetRepeat(&m_repeatStatus);
				 if(eErrGet == ERR_OK)
				 {
					 //UpdataRepeatIcon(eGetRpeat);
					 PostMessage(m_hMyHandle,WM_USER + 10,(WPARAM)m_repeatStatus,0);
				 }
				 if(m_bConnected && m_bInsert)
				 {
					 sPlayTime *pPlayTime = new sPlayTime;
					 if(pPlayTime != NULL)
					 {
						 if(m_ntrackIndex != -1)
						 {
							 pPlayTime->nPostionTime = m_ntrackPosition;
							 pPlayTime->nTotalTime = m_ntrackLength;
						 }
						 else
						 {
							 pPlayTime->nPostionTime = 0;
							 pPlayTime->nTotalTime = 0;
						 }
						 PostMessage(m_hMyHandle,WM_USER + 12,(WPARAM)pPlayTime,NULL);
					 }
					//UpdataPlayingTime(m_ntrackPosition,m_ntrackLength);
				 }
			 }
			 break;
			case ERR_FAIL:
			 {
				 m_bConnected = false;
				 m_nFailed++;
			 }
			 break;
			case ERR_BADPARAM:
			 {
				 if(m_ctLoadData.IsActive())
				 {
					 m_ctLoadData.StopTimer();
				 }
			//	 m_bRun = false;
				// IPODDEBEGINFO(L"iPod加载数据超时!");
			/*	 m_pTxtInfo->SetText(s_pLan[23]);*/
				 PostMessage(m_hMyHandle,WM_USER + 16,0,0);
				 m_bConnected = false;

			 }
			 break;
			case ERR_IPODEXIT:
			 {
				 m_nFailed++;
				 m_bConnected = false;
				 // ipodctl_ConnectToIpod();
				 // ClearIpodData();
				/* if(m_ctLoadData.IsActive())
				 {
					 m_ctLoadData.StopTimer();
				 }
				 m_bRun = false;*/
				//m_pTxtInfo->SetText(s_pLan[23]);
			 }
			 break;
			case  ERR_NOTCNNT:
			 {
				 m_nFailed++;
				// m_bRun = false;
				 m_bConnected = false;
				// if(m_nConnect == 0)
				 //{
					//  ipodctlERR err2=  ipodctl_ConnectToIpod();
					//  IPODDEBEGINFO(L"ipodctl_ConnectToIpod:: err2= %d",err2);
					//  if(err2 == ERR_OK)
					//  {
					//	  err2=  ipodctl_SetShuffle(SHUFFLE_OFF);
					//	  err2 = ipodctl_StartPlay(PAGE_PLAYLIST,0,0);
					//	    m_bConnected = true;
					//	  if(err2 == ERR_OK)
					//	  {
					//		  IPODDEBEGINFO(L"***************123456**");
					//	  }
					//	  if(m_ctLoadData.IsActive())
					//	  {
					//		 m_ctLoadData.StopTimer();
					//	  }
					//	  HidePopup();
					//	  DWORD dwThreadID;
					//	  m_hGetSongInfoThread = CreateThread(NULL,0,GetIpodListsThread,this,0,&dwThreadID);
					//	  IPODDEBEGINFO(L"GetIpodListsThread::dwThreadID = %d",dwThreadID);
					//  }
					// m_nConnect ++;
					//  IPODDEBEGINFO(L"ipodctl_ConnectToIpod,err = %d",err2);
				 //}

			 }
			 break;
			case ERR_NOTINIT:
			 {
				 IPODDEBEGINFO(L"++++++++++++ERR_NOTINIT++++++++");
				 m_nFailed++;
				 ipodctlERR ret;
				 ipodctlERR err1;
				 if(s_nInint == 0)
				 {
					 err1 = ipodctl_Init(false);
					 printf("+++++++ipodctl_Init = %d+++++++\r\n",err1);
					 if(err1 = ERR_OK)
					 {
						 s_nInint++;
					 }
				 }
				
				 IPODDEBEGINFO(L"ipodctl_Init,err1 = %d",err1);
				 if(err1 != ERR_OK )
				 {
					 if(m_ctLoadData.IsActive())
					 {
						 m_ctLoadData.StopTimer();
					 }
					 PostMessage(m_hMyHandle,WM_USER + 16,0,0);
					/* SetPopupInfor(s_pLan[23]);
					 ShowPopup(PT_NOR, 0);*/
					 return 5;
				 }
				 else if(err1 == ERR_OK)
				 {
					// WaitForIpodReady(5000);
					 ret = ipodctl_ConnectToIpod();
					 if(ret  != ERR_OK)
					 {
						 if(m_ctLoadData.IsActive())
						 {
							 m_ctLoadData.StopTimer();
						 }
					/*	 SetPopupInfor(s_pLan[23]);
						 ShowPopup(PT_NOR, 0);*/
						 PostMessage(m_hMyHandle,WM_USER + 16,0,0);
						 return 5;
					 }
					 if(ret == ERR_OK)
					 {
						 //m_bConnected = true;
						// err1 =  ipodctl_SetShuffle(SHUFFLE_OFF);//delete 0723
						 // if(m_nPlayStatus != PLAYSTATUS_PLAYING)
						 {
							 // if(err1 !=  ERR_OK)
							 {
								// GetDBITunesInfo();
								//GetNumberCategorizedDBRecords();
								 err1 = ipodctl_StartPlay(PAGE_PLAYLIST,0,0);
								// err1 = ipodctl_StartPlay(PAGE_TRACK,0,0);
							 }
							 if(err1 == ERR_OK)
							 {
								  err1 =  ipodctl_SetShuffle(SHUFFLE_OFF);
								  printf("+++++++++ipodctl_SetShuffle::err1 = %d+++++++",err1);
								 err1 = ipodctl_GetPlayingTrackNum(&m_nTotalNum);//曲目总数
								 PostMessage(m_hMyHandle,WM_USER + 15,0,0);
			/*					 if(m_ctLoadData.IsActive())
								 {
									 m_ctLoadData.StopTimer();
								 }
								 HidePopup();*/
							 }
							 err1 =  ipodctl_GetRepeat(&m_repeatStatus);
							 if(err1 == ERR_OK)
							 {
								 PostMessage(m_hMyHandle,WM_USER + 10,(WPARAM)m_repeatStatus,NULL);
								// UpdataRepeatIcon(m_repeatStatus);
							 }
							 err1 =  ipodctl_GetShuffle(&m_shuffleStatus);
							 if(err1 == ERR_OK)
							 {
								  PostMessage(m_hMyHandle,WM_USER + 11,(WPARAM)m_shuffleStatus,NULL);
								 //UpdataShuffleIcon(m_shuffleStatus);
							 }
							// return 10;
							 DWORD dwThreadID;
							  m_bConnected = true;
							//m_hGetSongInfoThread = CreateThread(NULL,0,GetIpodListsThread,this,0,&dwThreadID);
							 printf("-----------GetIpodListsThread = %d-------------\r\n",m_hGetSongInfoThread);
						 }
#if TESTIPODBACKGGROUND
						 OnBackground(NULL);
#endif
						 m_nTimes++;
					 }
				 }
			 }
			 break;
			default:
				break;
			} 
			//LeaveCriticalSection(&m_csThread);
			DWORD nTime1 = GetTickCount();
			DWORD nTimeCost = nTime1 - nTime;
			if(nTimeCost < 1000)
			 { 
				Sleep(1000 -nTimeCost);	 
				IPODDEBEGINFO(L"Sleep[%d]",1000 -nTimeCost);
			}
			else
			 {
				IPODDEBEGINFO(L"nTimeCost = %d,",nTimeCost);
				Sleep(200);
			 }
		}
		}
		}
	}
	//::PostMessage(m_hMyHandle,WM_USER + 9,NULL,NULL);//更新线程退出
	  return 0;
}
HINT CIpodDlg::UpDataMediaInfo(void)
{
	ipodctlERR err = ERR_FAIL;
	unsigned long nCurrentIndex,nTotalNum;
	while (m_bRun)
	{
		//EnterCriticalSection(&m_csThread);
		if(m_bUpdateThread)
		{
			if(!m_pTxtArtistPic->IsShow() && !m_bIpodListShow)
			{
				m_pTxtArtistPic->SetShow(true);
			}
			DWORD nTime = GetTickCount();
			 err = ipodctl_GetPlayStatus(&nCurrentIndex,&m_ntrackLength,&m_ntrackPosition,&m_nPlayStatus);
			//  IPODDEBEGINFO(L"ipodctl_GetPlayStatus:err = %d",err);
			 if(m_IpodPreERR == ERR_IPODEXIT && err == ERR_OK)
			 {
				// ::PostMessage(m_hMyHandle,WM_USER + 5,0,NULL);//Ipod重新插入
			 }
			 if((m_IpodPreERR == ERR_OK) && ((err == ERR_FAIL) || (err == ERR_IPODEXIT)))
			 {
				// ::PostMessage(m_hMyHandle,WM_USER + 6,0,NULL);
			 }
			 m_IpodPreERR = err;
			  IPODDEBEGINFO(L"%s,err = %d,m_ntrackIndex = %d,m_pntrackLength = %d,m_pntrackPosition = %d,m_nplayStatus = %d",__FUNCTIONW__,err,m_ntrackIndex,m_ntrackLength,m_ntrackPosition,m_nPlayStatus);
			 switch (err)
			 {
				case ERR_OK:
				 {
					if(m_bConnected == false)
					{
						 ipodctlERR err1; //=  ipodctl_StartPlay(PAGE_PLAYLIST, 0, 0);
						 m_bConnected = true;
						 if(m_nPlayStatus != PLAYSTATUS_PLAYING)
						 {
							 err1 = ipodctl_PlayPause();
						 }
						 if(m_ctLoadData.IsActive())
						 {
							 m_ctLoadData.StopTimer();
						 }
						 if(m_pTxtInfo->IsShow())
						 {
							 m_pTxtInfo->SetShow(false);
						 }
						 if(m_pTxtCover->IsShow())
						 {
							 m_pTxtCover->SetShow(false);
						 }
						 if(m_pTxtInfoFrame->IsShow())
						 {
							 m_pTxtInfoFrame->SetShow(false);
						 }
						/* DWORD dwThreadID;
						 HANDLE Threadhandel;
						 Threadhandel = CreateThread(NULL,0,GetIpodListsThread,this,0,&dwThreadID);*/
						 IPODDEBEGINFO(L"ipodctl_StartPlay:err1 = %d",err1);
					}		
					if(m_nPlayStatus != m_nPreplayStatus)
					{
						switch (m_nPlayStatus)
						{
							case PLAYSTATUS_STOPPED:
							{
								 //m_pBtnPlayPause->SetText(s_pLan[5]);
								m_pBtnPlayPause->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Pause_N.hfp")));
								m_pBtnPlayPause->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Pause_A.hfp")));
							}
							break;
							case PLAYSTATUS_PLAYING:
							{
							//	m_pBtnPlayPause->SetText(s_pLan[6]);
								m_pBtnPlayPause->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Play_N.hfp")));
								m_pBtnPlayPause->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Play_A.hfp")));
							}
							break;
							case PLAYSTATUS_PAUSED:
							{
							//	 m_pBtnPlayPause->SetText(s_pLan[5]);
								m_pBtnPlayPause->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Pause_N.hfp")));
								m_pBtnPlayPause->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Pause_A.hfp")));
							}
							break;
							default:
							break;
						}
						m_nPreplayStatus = m_nPlayStatus;
					}
					unsigned long nn = 0;
					 err = ipodctl_GetPlayingTrackNum(&nTotalNum);
					 switch(m_shuffleStatus)
					 {
					 case SHUFFLE_OFF:
						 {
							 nn =  m_ntrackNum;
						 }
						 break;
					 case SHUFFLE_ALBUMS:
						 {
							 nn = m_nAlbumTotalNum;
						 }
						 break;
					 case SHUFFLE_TRACKS:
						 {
							 nn =m_ntrackTotalNum;
						 }
						 break;
					 default:
						 break;
					 }
					if(nCurrentIndex != m_ntrackIndex || nTotalNum != nn || m_bShuffleChange == true)
					{
						if(nCurrentIndex > m_ntrackIndex)
						{
							m_iPicDirection = 0;
						}
						else
						{
							m_iPicDirection = 1;
						}
						m_ntrackIndex = nCurrentIndex;
						switch(m_shuffleStatus)
					 {
						case SHUFFLE_OFF:
						 {
							 m_ntrackNum = nTotalNum;
						 }
						 break;
						case SHUFFLE_ALBUMS:
							{
								m_nAlbumTotalNum = nTotalNum;
							}
							break;
						case SHUFFLE_TRACKS:
							{
								m_ntrackTotalNum = nTotalNum;
							}
							break;
						default:
							break;
					 }
						UpdataSongInfo(m_ntrackIndex);
						m_bShuffleChange = false;
					}
					UpdataPlayingTime(m_ntrackPosition,m_ntrackLength);
				 }
				 break;
				 case ERR_FAIL:
				 {

				 }
				 break;
				 case ERR_BADPARAM:
				 {
				 }
				 break;
				case ERR_IPODEXIT:
				 {
					 m_bConnected = false;
					// ipodctl_ConnectToIpod();
					// ClearIpodData();
				 }
				 break;
				 case  ERR_NOTCNNT:
				 {
					 m_bConnected = false;
					 //ClearIpodData();
					 //ipodctlERR err1=  ipodctl_ConnectToIpod();
				 }
				 break;
				 case ERR_NOTINIT:
				 {
					 ipodctlERR ret;
					 ipodctlERR err1 = ipodctl_Init(TRUE);
					 IPODDEBEGINFO(L"ipodctl_Init,err1 = %d",err1);
					ret = ipodctl_ConnectToIpod();
					 IPODDEBEGINFO(L"ipodctl_ConnectToIpod:ret = %d",ret);
					 if(ret == ERR_OK)
					 {
						 m_bConnected = true;
						 //ret =  ipodctl_GetShuffle(&m_shuffleStatus);
						 //ret = ipodctl_GetRepeat(&m_repeatStatus);
						// ret = ipodctl_StartPlay(PAGE_PLAYLIST,0,0);
						 if(m_nPlayStatus != PLAYSTATUS_PLAYING)
						 {
							 err1 = ipodctl_PlayPause();
							 if(err1 !=  ERR_OK)
							 {
								 err1 = ipodctl_StartPlay(PAGE_PLAYLIST,0,0);
							 }
							 if(m_ctLoadData.IsActive())
							 {
								 m_ctLoadData.StopTimer();
							 }
							 if(m_pTxtInfo->IsShow())
							 {
								 m_pTxtInfo->SetShow(false);
							 }
							 if(m_pTxtCover->IsShow())
							 {
								 m_pTxtCover->SetShow(false);
							 }
							 if(m_pTxtInfoFrame->IsShow())
							 {
								 m_pTxtInfoFrame->SetShow(false);
							 }
						 }
						 err1 =  ipodctl_GetRepeat(&m_repeatStatus);
						 if(err1 == ERR_OK)
						 {
							 UpdataRepeatIcon(m_repeatStatus);
							  ipodctl_SetRepeat(m_repeatStatus);
							 IPODDEBEGINFO(L"ipodctl_GetRepeat,m_repeatStatus = %d",m_repeatStatus);
						 }
						 err1 =  ipodctl_GetShuffle(&m_shuffleStatus);
						 if(err1 == ERR_OK)
						 {
							 UpdataShuffleIcon(m_shuffleStatus);
							  ipodctl_SetShuffle(m_shuffleStatus);
							 IPODDEBEGINFO(L"ipodctl_GetShuffle:m_shuffleStatus = %d",m_shuffleStatus);
						 }
						 IPODDEBEGINFO(L"ipodctl_StartPlay:ret = %d",ret);
						/* if(ret == ERR_OK)
						 {
							 DWORD dwThreadID;
							 HANDLE Threadhandel;
							Threadhandel = CreateThread(NULL,0,GetIpodListsThread,this,0,&dwThreadID);
							  IPODDEBEGINFO(L"CreateThread:Threadid = %d",dwThreadID);
						 }*/

					 }
					 //ipodctlERR err2= ipodctl_Init(false);
				 }
				 break;
				 default:
				 break;
			 } 
			 DWORD nTime1 = GetTickCount();
			 DWORD nTimeCost = nTime1 - nTime;
			 if(nTimeCost < 1000)
			 {
				Sleep(1000 -nTimeCost);
			 }
			 else
			 {
				 IPODDEBEGINFO(L"nTimeCost = %d,",nTimeCost);
				Sleep(150);
			 }
		}
		else
		{
			Sleep(50);
		}
	//	LeaveCriticalSection(&m_csThread);
	}
	  return 0;
}
 void CIpodDlg::OnConnect(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnConnect(pObj);
}
void CIpodDlg::OnConnect(void* pDlg)
{
	ipodctlERR err =  ipodctl_ConnectToIpod();
	if(err == ERR_OK)
	{
		//UpDataMediaInfo();
		 err = ipodctl_StartPlay(PAGE_PLAYLIST,0,0);
	}
	IPODDEBEGINFO(L"%s,err = %d",__FUNCTIONW__,err);
}
 void CIpodDlg::OnFF(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnFF(pObj);
}
void CIpodDlg::OnFF(void* pDlg)
{
	ipodctlERR err = ERR_FAIL;
	if(m_bConnected && m_bInsert)
	{
		if(m_bFFREW)
		{
			err = ipodctl_EndFFRew();
			if(err = ERR_OK)
			{
				m_bFFREW = false;
			}
		}
		else if(m_bInsert)
		{
			err =  ipodctl_StartFF();
			if(err == ERR_OK)
			{
				m_bFFREW = true;
			}
		}
	}
	if(err == ERR_OK)
	{
		/*UpDataMediaInfo();*/
	}
	IPODDEBEGINFO(L"%s,err = %d",__FUNCTIONW__,err);
}
 void CIpodDlg::OnEndFFRew(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnEndFFRew(pObj);
}
void CIpodDlg::OnEndFFRew(void* pDlg)
{
	if(m_bConnected && m_bInsert && m_bFFREW)
	{
		ipodctlERR err =  ipodctl_EndFFRew();
		if(err == ERR_OK)
		{

		}
		IPODDEBEGINFO(L"%s,err = %d",__FUNCTIONW__,err);
	}
}
 void CIpodDlg::OnStartRew(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnStartRew(pObj);
}
void CIpodDlg::OnStartRew(void* pDlg)
{
	ipodctlERR err;
	if(m_bConnected && m_bInsert)
	{
       if(m_bFFREW)
	   {
			err = ipodctl_EndFFRew();
			if(err == ERR_OK)
			{
				m_bFFREW = false;
			}
	   }
	   else  if(m_bInsert)
	   {
			err =  ipodctl_StartRew();
			if(err = ERR_OK)
			{
				m_bFFREW = true;
			}
	   }
	   IPODDEBEGINFO(L"%s,err = %d",__FUNCTIONW__,err);
	}	
}
 void CIpodDlg::OnGetTrackInfo(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnGetTrackInfo(pObj);
}
void CIpodDlg::OnGetTrackInfo(void* pDlg)
{
	ipodctlERR err =  ipodctl_GetTrackInfo(m_ntrackIndex,m_ptrackTitle,m_partistName,m_palbumName);
	if(err == ERR_OK)
	{
		UpDataMediaInfo();
	}
	IPODDEBEGINFO(L"%s,err = %d",__FUNCTIONW__,err);
}
 void CIpodDlg::OnGetPlayingTrackNum(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnGetPlayingTrackNum(pObj);
}
void CIpodDlg::OnGetPlayingTrackNum(void* pDlg)
{
	ipodctlERR err =  ipodctl_GetPlayingTrackNum(&m_ntrackNum);
	if(err == ERR_OK)
	{
		UpDataMediaInfo();
	}
	IPODDEBEGINFO(L"%s,err = %d",__FUNCTIONW__,err);
}
 void CIpodDlg::OnGetShuffle(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnGetShuffle(pObj);
}
void CIpodDlg::OnGetShuffle(void* pDlg)
{
	ipodctlERR err =  ipodctl_GetShuffle(&m_shuffleStatus);
	if(err == ERR_OK)
	{
		UpDataMediaInfo();
	}
	IPODDEBEGINFO(L"%s,err = %d",__FUNCTIONW__,err);
}
 void CIpodDlg::OnGetRepeat(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnGetRepeat(pObj);
}
void CIpodDlg::OnGetRepeat(void* pDlg)
{
	ipodctlERR err =  ipodctl_GetRepeat(&m_repeatStatus);
	if(err == ERR_OK)
	{
		UpDataMediaInfo();
	}
	IPODDEBEGINFO(L"%s,err = %d",__FUNCTIONW__,err);
}
 void CIpodDlg::OnSetShuffle(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnSetShuffle(pObj);
}
void CIpodDlg::OnSetShuffle(void* pDlg)
{
	ipodctlERR ret;
	if(m_bConnected == true)
	{
		ipodctlSHUFFLE nn = (ipodctlSHUFFLE)((m_shuffleStatus +1)%(SHUFFLE_ALBUMS + 1));
		switch (m_shuffleStatus)
		{
		case SHUFFLE_ALBUMS:
			{
				nn = SHUFFLE_OFF;
			}
			break;
		case SHUFFLE_TRACKS:
			{
				nn = SHUFFLE_OFF;
			}
			break;
		case SHUFFLE_OFF:
			{
				nn = SHUFFLE_TRACKS;
			}
			break;
		default:
			break;
		}
		if(!m_bButtonPress)
		{
			ret = ipodctl_SetShuffle(nn);
			IPODDEBEGINFO(L"ipodctl_SetShuffle:err = %d",ret);
			if(ret == ERR_OK)
			{
				//m_shuffleStatus  = nn;
				m_bShuffleChange = true;
               // UpdataShuffleIcon(m_shuffleStatus);
				//switch (m_shuffleStatus)
				//{
				//case SHUFFLE_OFF:
				//	{
				//		//m_pBtnGetShuffle->SetBkgndN(GetHMIPath(_T("Media\\Music\\Music_Close_Random_N.hfp")));
				//		m_pBtnGetShuffle->SetBkgndN(GetHMIPath(_T("iPod\\02-Radio-CO_A_17-32.hfp")));
				//		m_pBtnGetShuffle->SetBkgndA(GetHMIPath(_T("iPod\\02-Radio-CO_A_17-32 (2).hfp")));
				//		//m_pBtnGetShuffle->SetText(s_pLan[22]);
				//		//IPODDEBEGINFO(L"@@1111");
				//		//ret = ipodctl_GetPlayingTrackNum(&m_ntrackNum);
				//	//	IPODDEBEGINFO(L"@@2222");
				//	}
				//	break;
				//case SHUFFLE_TRACKS:
				//	{
				//		m_pBtnGetShuffle->SetBkgndN(GetHMIPath(_T("iPod\\02-Radio-CO_A_17-32.hfp")));
				//		m_pBtnGetShuffle->SetBkgndA(GetHMIPath(_T("iPod\\02-Radio-CO_A_17-32 (2).hfp")));
				//		//m_pBtnGetShuffle->SetText(s_pLan[8]);
				//		IPODDEBEGINFO(L"@@3333");
				//		//ret = ipodctl_GetPlayingTrackNum(&m_ntrackTotalNum);
				//		IPODDEBEGINFO(L"@@4444");
				//		//m_pBtnGetShuffle->SetBkgndN(GetHMIPath(_T("Ipod\\Music_loop_N.hfp")));
				//	}
				//	break;
				//case SHUFFLE_ALBUMS:
				//	{
				//		m_pBtnGetShuffle->SetBkgndN(GetHMIPath(_T("iPod\\02-Radio-CO_A_17-32 (4).hfp")));
				//		m_pBtnGetShuffle->SetBkgndA(GetHMIPath(_T("iPod\\02-Radio-CO_A_17-32 (3).hfp")));
				//		//m_pBtnGetShuffle->SetText(s_pLan[21]);
				//		IPODDEBEGINFO(L"@@5555");
				//		//ret = ipodctl_GetPlayingTrackNum(&m_ntrackTotalNum);
				//		IPODDEBEGINFO(L"@@5555");
				//		//m_pBtnGetShuffle->SetBkgndN(GetHMIPath(_T("Ipod\\Music_Close_n.hfp")));
				//	}
				//	break;
				//}
			}
			if(m_ctButton.IsActive())
			{
				m_ctButton.StopTimer();
			}
			m_ctButton.SetTime(60);
			m_ctButton.StartTimer();
			m_bButtonPress = true;
			//PostMessage(m_hMyHandle,WM_USER + 11,(WPARAM)m_shuffleStatus,0);
		}
	}
}
void CIpodDlg::OnSetRepeat(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnSetRepeat(pObj);
}
void CIpodDlg::OnSetRepeat(void* pDlg)
{
	ipodctlERR ret;
	if(m_bConnected == true)
	{
		if(!m_bButtonPress)
		{
			ipodctlREPEAT nRepeat = (ipodctlREPEAT)((m_repeatStatus +1)%(REPEAT_ALL_TRACKS + 1));
			//if(nRepeat == REPEAT_OFF)
			//{
			//	nRepeat = REPEAT_ONE_TRACK;
			//}
			switch(m_repeatStatus)
			{
				case REPEAT_ALL_TRACKS:
				{
                  nRepeat = REPEAT_OFF;
				}
				break;
				case REPEAT_ONE_TRACK:
				{
                       nRepeat = REPEAT_ALL_TRACKS;
				}
				break;
				case  REPEAT_OFF:
					{
                        nRepeat = REPEAT_ONE_TRACK;
					}
					break;
				default:
					{
                       nRepeat = REPEAT_OFF;
					}
					break;
			}
			ret = ipodctl_SetRepeat((ipodctlREPEAT)(nRepeat));
			printf("ipodctl_SetRepeat:nRepeat = %d+++++++++++++++\r\n",nRepeat);
			IPODDEBEGINFO(L"ipodctl_SetRepeat:nRepeat = %d",nRepeat);
			if(ret == ERR_OK)
			{
				//m_repeatStatus = nRepeat;
				//UpdataRepeatIcon(m_repeatStatus);
				//switch(m_repeatStatus)
				//{
				//case REPEAT_OFF:
				//	{
				//		//	m_pBtnGetrepeat->SetBkgndN(GetHMIPath(_T("Ipod\\Music_Folder_n.hfp")));
				//		m_pBtnGetrepeat->SetBkgndN(GetHMIPath(_T("iPod\\02-Radio-CO_A_17-30.hfp")));
				//		m_pBtnGetrepeat->SetBkgndA(GetHMIPath(_T("iPod\\02-Radio-CO_A_17-30 (2).hfp")));
				//		//m_pBtnGetrepeat->SetText(s_pLan[7]);
				//	}
				//	break;
				//case REPEAT_ONE_TRACK:
				//	{
				//		m_pBtnGetrepeat->SetBkgndN(GetHMIPath(_T("iPod\\02-Radio-CO_A_17-30 (4).hfp")));
				//		m_pBtnGetrepeat->SetBkgndA(GetHMIPath(_T("iPod\\02-Radio-CO_A_17-30 (3).hfp")));
				//		//m_pBtnGetrepeat->SetText(s_pLan[20]);
				//		//m_pBtnGetrepeat->SetBkgndN(GetHMIPath(_T("Ipod\\Music_Singles_N.hfp")));
				//	}
				//	break;
				//case REPEAT_ALL_TRACKS:
				//	{
				//		m_pBtnGetrepeat->SetBkgndN(GetHMIPath(_T("iPod\\02-Radio-CO_A_17-30.hfp")));
				//		m_pBtnGetrepeat->SetBkgndA(GetHMIPath(_T("iPod\\02-Radio-CO_A_17-30 (2).hfp")));
				//		//m_pBtnGetrepeat->SetText(s_pLan[19]);
				//		//m_pBtnGetrepeat->SetBkgndN(GetHMIPath(_T("Ipod\\Music_loop_N.hfp")));
				//	}
				//	break;
				//}
				if(m_ctButton.IsActive())
				{
					m_ctButton.StopTimer();
				}
				m_ctButton.SetTime(60);
				m_ctButton.StartTimer();
				//PostMessage(m_hMyHandle,WM_USER + 10,(WPARAM)m_repeatStatus,0);
			}
			m_bButtonPress = false;
		}
	}
}
void CIpodDlg::OnSetCurrentPlayingTrack(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnSetCurrentPlayingTrack(pObj);
}
void CIpodDlg::OnSetCurrentPlayingTrack(void* pDlg)
{
}
void CIpodDlg::OnStartPlay(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnStartPlay(pObj);
}
void CIpodDlg::OnStartPlay(void* pDlg)
{
	ipodctlERR err =  ipodctl_StartPlay(PAGE_PLAYLIST,0,0);
	if(err == ERR_OK)
	{
		UpDataMediaInfo();
	}
	IPODDEBEGINFO(L"%s,err = %d",__FUNCTIONW__,err);
}
void CIpodDlg::OnIpodList(void* pDlg,void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnIpodList(pObj);
}
void CIpodDlg::OnIpodList(void* pDlg)
{
	if(m_bUpdateThread)
	{
		m_bUpdateThread = false;
		if(!m_bIpodListShow)
		{
			m_pGrpBtm->SetShow(false);
			m_pTxtArtistPic->SetShow(false);
			m_pGrpMid->SetShow(false);
			m_bIpodListShow = true;
			m_pGrpIpodList->SetShow(true);
			ipodctlSHUFFLE nshuffleStatus = SHUFFLE_OFF;
			//switch (m_shuffleStatus)
			switch (nshuffleStatus)
			{
				case SHUFFLE_OFF:
				{
					m_pScrboxIpodList->SetShow(true);
				}
				break;
				case SHUFFLE_ALBUMS:
				{
					m_pScrboxIpodAlbumList->SetShow(true);
				}
				break;
				case SHUFFLE_TRACKS:
				{
					m_pScrboxIpodTrackList->SetShow(true);
				}
				break;
				default:
					break;
			}
		/*	DWORD dwThreadID;
			 HANDLE Threadhandel;
			 Threadhandel = CreateThread(NULL,0,GetIpodListsThread,this,0,&dwThreadID);
			 if(Threadhandel != 0)
			 {
				 IPODDEBEGINFO(L"Threadhandel = %d,dwThreadID = %d",Threadhandel,dwThreadID);
			 }*/
			//GetIpodLists(NULL);
		}
	}
}
void CIpodDlg::OnScrboxIpodList(void* pDlg,void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnScrboxIpodList(pObj);
}
void CIpodDlg::OnScrboxIpodList(void* pDlg)
{
	HCListItemBase *pListItemSelect = NULL;
		//= m_pScrboxIpodList->GetSelectListItem();
	if(!m_bConnected)
		return;
	HINT iSelectIndex = -1;

		
			switch (m_shuffleStatus)
			{
			case SHUFFLE_OFF:
				{
					pListItemSelect = m_pScrboxIpodList->GetSelectListItem();
					if(pListItemSelect != NULL)
					{
						iSelectIndex = m_pScrboxIpodList->GetListItemIndex(pListItemSelect);
						m_pScrboxIpodList->SetSelectListItem(iSelectIndex,false);
						if(iSelectIndex >= 0 && iSelectIndex < m_ntrackNum)
						{
							printf("\r\nOnScrboxIpodList::111111111111\r\n");
							ipodctlERR ret = ipodctl_SetCurrentPlayingTrack(iSelectIndex);
							printf("\r\nOnScrboxIpodList::22222222222\r\n");
						}
					}
					
				}
				break;
			case SHUFFLE_ALBUMS:
				{
					pListItemSelect = m_pScrboxIpodAlbumList->GetSelectListItem();
					if(pListItemSelect != NULL)
					{
						iSelectIndex = m_pScrboxIpodAlbumList->GetListItemIndex(pListItemSelect);
						m_pScrboxIpodAlbumList->SetSelectListItem(iSelectIndex,false);
						if(iSelectIndex >= 0 && iSelectIndex < m_nAlbumTotalNum)
						{
							ipodctlERR ret = ipodctl_SetCurrentPlayingTrack(iSelectIndex);
						}
					}
				}
				break;
			case SHUFFLE_TRACKS:
				{
					pListItemSelect = m_pScrboxIpodTrackList->GetSelectListItem();
					if(pListItemSelect != NULL)
					{
						iSelectIndex = m_pScrboxIpodTrackList->GetListItemIndex(pListItemSelect);
						m_pScrboxIpodTrackList->SetSelectListItem(iSelectIndex,false);
						if(iSelectIndex >= 0 && iSelectIndex < m_ntrackTotalNum)
						{
							ipodctlERR ret = ipodctl_SetCurrentPlayingTrack(iSelectIndex);
						}
					}
				}
				break;
			default:
				break;
			}
			printf("\r\nOnScrboxIpodList::33333333333\r\n");
}
void CIpodDlg::OnGetArtworkData(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnGetArtworkData(pObj);
}
void CIpodDlg::OnGetArtworkData(void* pDlg)
{
	unsigned char szInfo[240*240*3] = {0};
	ipodctlERR err =  ipodctl_GetArtworkData(m_ntrackIndex,ARTWORKSIZE_240x240,szInfo);
	if(err == ERR_OK)
	{
		UpDataMediaInfo();
	}
	IPODDEBEGINFO(L"%s,err = %d",__FUNCTIONW__,err);
}
void CIpodDlg::OnGetArtPicData(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnGetArtPicData(pObj);
}
void CIpodDlg::OnGetArtPicData(void* pDlg)
{
      memset(m_pArtistPicPre,0,128*128*3);
	 memcpy(m_pArtistPicPre,m_pArtistPic,128*128*3);
	  if(m_ctPic.IsActive())
	  {
		  m_ctPic.StopTimer();
	  }
	  memset(m_pArtistPic,0,128*128*3);
	 // unsigned char *ptem = m_pArtistPic;
      ipodctlERR ret = ipodctl_GetArtworkData(0,ARTWORKSIZE_128x128 ,m_pArtistPic);//屏蔽0720
	  if(ret == ERR_OK)
	  {
		  unsigned char szTemp1[256] = {0};
		  for(int i = 0; i < 64;i++)
		  {
			  memset(szTemp1,0,sizeof(szTemp1));
			  memcpy(szTemp1,m_pArtistPic + 256*i,256);
			  memcpy(m_pArtistPic + 256*i,m_pArtistPic + 256*(127 - i),256);
			  memcpy(m_pArtistPic + 256*(127 - i),szTemp1,256);
		  }
		  unsigned char szTemp[256] = {0};
		  if(m_iPicDirection == 0)
		  {
			  for(int j = 0;j < 128;j++)
			  {
				  memset(szTemp,0,sizeof(szTemp));
				  memcpy(szTemp,m_pArtistPicPre + 256*j+ 64,192);
				  memcpy(szTemp + 192,m_pArtistPic + 256*j,64);
				  memcpy(m_pArtistPicPre + j*256,szTemp,256);
			  }
		  }
		  else
		  {
			  for(int j = 0;j < 128;j++)
			  {
				  memset(szTemp,0,sizeof(szTemp));
				  memcpy(szTemp ,m_pArtistPic + 256*j + 192,64);
				  memcpy(szTemp+ 64,m_pArtistPicPre + 256*j,192);
				  memcpy(m_pArtistPicPre + j*256,szTemp,256);
			  }
		  }
		 if(m_pIREArtist == NULL)
		 {
			m_pIREArtist = GetRESingleton()->CreateSurfaceFrom565Mem(m_pArtistPicPre,128,128);
          }
		 if(m_pIREArtist != NULL)
		  {
			  m_iPicState = -1;
			  ::PostMessage(m_hMyHandle,WM_USER + 7,1,NULL);
		  }
	  }
	  else
	  {
		  ::PostMessage(m_hMyHandle,WM_USER + 7,0,NULL);
	  }
}
void CIpodDlg::DealWithErr(ipodctlERR err)
{
	switch (err)
	{
	case ERR_OK:
		{
		}
		break;
	case ERR_FAIL:
		{

		}
		break;
	case ERR_BADPARAM:
		{
		}
		break;
	case ERR_IPODEXIT:
		{
		}
		break;
	case  ERR_NOTCNNT:
		{
			ipodctlERR err1=  ipodctl_ConnectToIpod();
		}
		break;
	case ERR_NOTINIT:
		{
			ipodctlERR err2= ipodctl_Init(false);
		}
		break;
	default:
		break;
	}
	IPODDEBEGINFO(L"%s,err = %d",__FUNCTIONW__,err);
}
void CIpodDlg::OnLoadData(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	//pObj->OnLoadData(pObj);
	pObj->OnLoadDataEx(pObj);
}
void CIpodDlg::OnLoadData(void* pDlg)
{
	if(m_ctLoadData.IsActive())
	{
		m_ctLoadData.StopTimer();
	}
	IPODDEBEGINFO(L"m_nDowningTime = %d",m_nDowningTime);
	if(m_nDowningTime == 80)
	{
		IPODDEBEGINFO(L"iPod加载数据超时!");
		::PostMessage(m_hMyHandle,WM_USER +8,0,NULL);
		return;
	}
	m_ctLoadData.SetTime(40);
	m_ctLoadData.StartTimer();
	HINT nn = m_nDowningTime%6;
	switch (nn)
	{
	case 0:
		{
			m_pTxtInfo->SetText(s_pLan[13]);
			//	 m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[0]);
		}
		break;
	case 1:
		{
			m_pTxtInfo->SetText(s_pLan[14]);
			// m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[1]);
		}
		break;
	case 2:
		{
			m_pTxtInfo->SetText(s_pLan[15]);
			// m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[2]);
		}
		break;
	case 3:
		{
			m_pTxtInfo->SetText(s_pLan[16]);
			// m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[3]);
		}
		break;
	case 4:
		{
			m_pTxtInfo->SetText(s_pLan[17]);
			// m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[4]);
		}
		break;
	case 5:
		{
			m_pTxtInfo->SetText(s_pLan[18]);
			// m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[5]);
		}
		break;
	}
	m_nDowningTime++;

	//m_nDowningTime %= 6;
	if(!m_pTxtCover->IsShow())
	{
		m_pTxtCover->SetShow(true);
	}

	if(!m_pTxtInfoFrame->IsShow())
	{
		m_pTxtInfoFrame->SetShow(true);
	}
	if(!m_pTxtInfo->IsShow())
	{
		m_pTxtInfo->SetShow(true);
	}
}
void CIpodDlg::UpdataSongInfo(unsigned long curIndex)
{
	ipodctlERR ret;
	unsigned long nTotal = 0;
	ret = ipodctl_GetPlayingTrackNum(&nTotal);//曲目总数
	switch (m_shuffleStatus)
	  {
		  case SHUFFLE_OFF:
		  {
			   //ret = ipodctl_GetPlayingTrackNum(&nTotal);//曲目总数
			  m_ntrackNum = nTotal;
		  }
		  break;
		  case SHUFFLE_ALBUMS:
		 {
			 //ret = ipodctl_GetPlayingTrackNum(&nTotal);//曲目总数
			 m_nAlbumTotalNum = nTotal;
		 }
		 break;
		 case SHUFFLE_TRACKS:
		{
			m_ntrackTotalNum = nTotal;
		}
		break;
	  }
	  if(ret == ERR_OK)
	  {
		  /*  if(nTotal > 0 && m_pSongInfoArr == NULL)
			{
					m_pSongInfoArr = new sSongInfo[nTotal];
					IPODDEBEGINFO(L"m_pSongInfoArr = %d,Requre %d SongInfo Mem",m_pSongInfoArr,m_ntrackNum);
			}*/
		  HCHAR szTemp[30] = {0};
		   wsprintf(szTemp,L"%d/%d",curIndex+1,nTotal);             
		  m_pTxtCurrentIndex->SetText(szTemp);
	  }
	  ret = ipodctl_GetTrackInfo(curIndex,m_ptrackTitle,m_partistName,m_palbumName);
	  m_pTxtSong->SetText(m_ptrackTitle);
	  m_pTxtArtist->SetText(m_partistName);
	  m_pTxtAbum->SetText(m_palbumName);
	  m_pSldPlayTime->SetBound(0,m_ntrackLength);
	 memset(m_pArtistPicPre,0,128*128*3);
	 memcpy(m_pArtistPicPre,m_pArtistPic,128*128*3);
	  if(m_ctPic.IsActive())
	  {
		  m_ctPic.StopTimer();
	  }
	  memset(m_pArtistPic,0,128*128*3);
	 // unsigned char *ptem = m_pArtistPic;
	//ret = ipodctl_GetArtworkData(curIndex,ARTWORKSIZE_128x128 ,m_pArtistPic);//屏蔽0720
	  ret = ERR_FAIL; 
	  if(ret == ERR_OK)
	  {
		  unsigned char szTemp1[256] = {0};
		  for(int i = 0; i < 64;i++)
		  {
			  memset(szTemp1,0,sizeof(szTemp1));
			  memcpy(szTemp1,m_pArtistPic + 256*i,256);
			  memcpy(m_pArtistPic + 256*i,m_pArtistPic + 256*(127 - i),256);
			  memcpy(m_pArtistPic + 256*(127 - i),szTemp1,256);
		  }
		  unsigned char szTemp[256] = {0};
		  if(m_iPicDirection == 0)
		  {
			  for(int j = 0;j < 128;j++)
			  {
				  memset(szTemp,0,sizeof(szTemp));
				  memcpy(szTemp,m_pArtistPicPre + 256*j+ 64,192);
				  memcpy(szTemp + 192,m_pArtistPic + 256*j,64);
				  memcpy(m_pArtistPicPre + j*256,szTemp,256);
			  }
		  }
		  else
		  {
			  for(int j = 0;j < 128;j++)
			  {
				  memset(szTemp,0,sizeof(szTemp));
				  memcpy(szTemp ,m_pArtistPic + 256*j + 192,64);
				  memcpy(szTemp+ 64,m_pArtistPicPre + 256*j,192);
				  memcpy(m_pArtistPicPre + j*256,szTemp,256);
			  }
		  }
		  //m_pIREArtist = GetRESingleton()->CreateSurfaceFrom565Mem(m_pArtistPic,128,128);
		 if(m_pIREArtist == NULL)
		 {
			m_pIREArtist = GetRESingleton()->CreateSurfaceFrom565Mem(m_pArtistPicPre,128,128);
			//IReSurface *PP = GetRESingleton()->CreateSurfaceFrom565Mem(m_pArtistPicPre,128,128);
			//SAFE_DELETE(PP);
          }
//		 else
		// {
			 //GetRESingleton()->ModifyKtcStreamSurface(m_pArtistPicPre,m_pIREArtist);
		// }
		 if(m_pIREArtist != NULL)
		  {
			  m_iPicState = -1;
			  ::PostMessage(m_hMyHandle,WM_USER + 7,1,NULL);
			/* if(m_pIREArtist != NULL)
			 {
				 m_pTxtArtistPic->SetBkgndN(m_pIREArtist);
			 }			
			IPODDEBEGINFO(L"m_pIREArtist = %d",m_pIREArtist);
			if(!m_pTxtArtistPic->IsShow())
			{
				m_pTxtArtistPic->SetShow(true);
			}*/
		  }
		 // SAFE_DELETE(pp);
	  }
	  else
	  {
		 /* if(m_pTxtArtistPic->IsShow())
		  {
			  m_pTxtArtistPic->SetShow(false);
		  }*/
		  ::PostMessage(m_hMyHandle,WM_USER + 7,0,NULL);
	  }
}
void CIpodDlg::ChangeTheme(HBYTE uType)
{
	SETUPSETTING Setting;
	// 设置背景
	KCLastMemory::GetInstance()->GetSetupMemory(Setting);
	SetBackGround(GetHMIPath((HCHAR*)&Setting.szBkgndPath));
	//SetDlgBkGnd();
	m_uThemeMode =  GetCurThemeMode();
}
void  CIpodDlg::MonitorIpodEventThread()
{
	/*DWORD ret ;
	if(m_bContiue)
	{
		if(m_bInsert)
		{
			ret = WaitForSingleObject(m_hIpodUnplug,1000);
		}
		else
		{
			ret = WaitForSingleObject(m_hIpodInsert,1000);
		}
		switch (ret)
		{
			case WAIT_OBJECT_0:
			{
				if(m_bInsert)
				{
					m_bInsert = false:
					::PostMessage(m_hMyHandle,WM_USER + 2,0,NULL);
				}
				else
				{
					m_bInsert = true;
					::PostMessage(m_hMyHandle,WM_USER + 2,1,NULL);
				}
			}
			break;
			case WAIT_TIMEOUT:
			{
				
			}
			break;
		}

	}*/
}
void CIpodDlg::SetMyHandle(HWND hWin)
{
	m_hMyHandle = hWin;
}
bool CIpodDlg::ConectAndStartPlay()
{
	bool bResult = false;
//	ipodctlERR ret;
//	unsigned long u32len,u32pos,u32index;
	//ipodctlPLAYSTATUS u8status;
	  //ret = ipodctl_Init(TRUE);
	  //  ret = ipodctl_ConnectToIpod();
	DWORD nThread;
	m_hUpdataThread = CreateThread(NULL, 0, ((LPTHREAD_START_ROUTINE)UpdataIpodInfoThread), this, 0, &nThread);
	//   HCHAR szTemp[50] = {0};
	//swprintf(szTemp,L"%x",)
	IPODDEBEGINFO(L"UpdataIpodInfoThread::%x",nThread);
	//Sleep(1000);
	/*ret = ipodctl_GetPlayStatus(&u32index,&u32len,&u32pos,&u8status);
	 if(ret == ERR_NOTINIT)
	 {
		 DWORD dwThreadID;
		  CreateThread(NULL,0,UpdataIpodInfoThread,this,0,&dwThreadID);
	 }*/
//	 if(ret == ERR_OK)
//	 {
//		  ipodctl_StartPlay(PAGE_PLAYLIST, 0, 0);
//		  m_bConnected = true;
//		  return true;
//
//	 }
//	 else if( ret == ERR_NOTINIT)
//	 {
//		 if(!m_bConnected)
//		 {
//			 ipodctlERR err = ipodctl_Init(true);
//			 IPODDEBEGINFO(L"ipodctl_Init,err = %d",err);
//			 ret = ipodctl_ConnectToIpod();
//			 IPODDEBEGINFO(L"ipodctl_ConnectToIpod:ret = %d",ret);
//			 if(ret == ERR_OK)
//			 {
//				 m_bConnected = true;
//				 //ret =  ipodctl_GetShuffle(&m_shuffleStatus);
//				 //ret = ipodctl_GetRepeat(&m_repeatStatus);
//				 ret = ipodctl_StartPlay(PAGE_PLAYLIST,0,0);
//				 err =  ipodctl_GetRepeat(&m_repeatStatus);
//				 if(err = ERR_OK)
//				 {
//					 UpdataRepeatIcon(m_repeatStatus);
//					 IPODDEBEGINFO(L"ipodctl_GetRepeat,m_repeatStatus = %d",m_repeatStatus);
//				 }
//				 err =  ipodctl_GetShuffle(&m_shuffleStatus);
//				 if(err = ERR_OK)
//				 {
//					 UpdataShuffleIcon(m_shuffleStatus);
//					 IPODDEBEGINFO(L"ipodctl_GetShuffle:m_shuffleStatus = %d",m_shuffleStatus);
//				 }
//				 IPODDEBEGINFO(L"ipodctl_StartPlay:ret = %d",ret);
//				 if(ret == ERR_OK)
//				 {
//					 bResult = true;
//					 DWORD dwThreadID;
//					 HANDLE Threadhandel;
//					 Threadhandel = CreateThread(NULL,0,GetIpodListsThread,this,0,&dwThreadID);
//					 IPODDEBEGINFO(L"CreateThread:Threadid = %d",dwThreadID);
//				 }
//
//			 }
//		 }
//		 else
//		 {
//			 //ret =  ipodctl_GetShuffle(&m_shuffleStatus);
//			 //ret = ipodctl_GetRepeat(&m_repeatStatus);
//			 ret = ipodctl_StartPlay(PAGE_PLAYLIST,0,0);
//			 if(ret == ERR_OK)
//			 {
//				 bResult = true;
//			 }
//		 }
//	 }
//	 else if(ret == ERR_IPODEXIT)
//	 {
//		// ipodctlERR err;
//		//// ret = ipodctl_ConnectToIpod();
//		// IPODDEBEGINFO(L"ipodctl_ConnectToIpod:ret = %d",ret);
//		// if(ret == ERR_OK)
//		// {
//		//	 m_bConnected = true;
//		//	 //ret =  ipodctl_GetShuffle(&m_shuffleStatus);
//		//	 //ret = ipodctl_GetRepeat(&m_repeatStatus);
//		//	 ret = ipodctl_StartPlay(PAGE_PLAYLIST,0,0);
//		//	 err =  ipodctl_GetRepeat(&m_repeatStatus);
//		//	 if(err = ERR_OK)
//		//	 {
//		//		 UpdataRepeatIcon(m_repeatStatus);
//		//		 IPODDEBEGINFO(L"ipodctl_GetRepeat,m_repeatStatus = %d",m_repeatStatus);
//		//	 }
//		//	 err =  ipodctl_GetShuffle(&m_shuffleStatus);
//		//	 if(err = ERR_OK)
//		//	 {
//		//		 UpdataShuffleIcon(m_shuffleStatus);
//		//		 IPODDEBEGINFO(L"ipodctl_GetShuffle:m_shuffleStatus = %d",m_shuffleStatus);
//		//	 }
//		//	 IPODDEBEGINFO(L"ipodctl_StartPlay:ret = %d",ret);
//		//	 if(ret == ERR_OK)
//		//	 {
//		//		 bResult = true;
//		//		 DWORD dwThreadID;
//		//		 HANDLE Threadhandel;
//		//		 Threadhandel = CreateThread(NULL,0,GetIpodListsThread,this,0,&dwThreadID);
//		//		 IPODDEBEGINFO(L"CreateThread:Threadid = %d",dwThreadID);
//		//	 }
//		// }
//	 }
//	IPODDEBEGINFO(L"%s:result = %d",__FUNCTIONW__,bResult);
//	return bResult;
//}
//void CIpodDlg::ClearIpodData()
//{
//	m_pTxtScreen->SetText(L"Ipod");
//	m_pTxtSong->SetText(L"未知歌曲");
//	m_pTxtArtist->SetText(L"未知艺术家");
//	m_pTxtAbum->SetText(L"未知专辑");
//	m_bConnected = false;
return true;
}
void CIpodDlg::UpdataPlayingTime(unsigned long nPostion,unsigned long nTotleTime)
{
	unsigned long lensec,lenmin,possec,posmin;
	if(nPostion > nTotleTime || nTotleTime == -1 || nTotleTime == -1)
	{
       nPostion = nTotleTime = 0;
	}
	HCHAR szTime[30] = {0};
	posmin = nPostion/60000;
	possec = (nPostion/1000)%60;
	lenmin = nTotleTime/60000;
	lensec = (nTotleTime/1000)%60;
	if(possec < 10 && posmin < 10)
	{
		wsprintf(szTime,L"0%d:0%d",posmin,possec);
	}
	else if(possec >= 10 && posmin < 10)
	{
		wsprintf(szTime,L"0%d:%d",posmin,possec);
	}
	else if(possec< 10 && posmin >= 10)
	{
		wsprintf(szTime,L"%d:0%d",posmin,possec);
	}
	else
	{
		wsprintf(szTime,L"%d:%d",posmin,possec);
	}

	if(m_pTxtCurrentPlayTime != NULL)
	{
		m_pTxtCurrentPlayTime->SetText(szTime);
	}
	memset(szTime,0,sizeof(szTime));
	if(lensec < 10 && lenmin < 10)
	{
		wsprintf(szTime,L"0%d:0%d",lenmin,lensec);
	}
	else if(lensec >= 10 && lenmin < 10)
	{
		wsprintf(szTime,L"0%d:%d",lenmin,lensec);
	}
	else if(lensec < 10 && lenmin >= 10)
	{
		wsprintf(szTime,L"%d:0%d",lenmin,lensec);
	}
	else
	{
		wsprintf(szTime,L"%d:%d",lenmin,lensec);
	}
	if(m_pTxtTrackTotalTime != NULL)
	{
		m_pTxtTrackTotalTime->SetText(szTime);
	}
	if(nPostion <= nTotleTime)
	{
		m_pSldPlayTime->SetBound(0,nTotleTime);
		m_pSldPlayTime->SetValue(nPostion);
	}
}
void CIpodDlg::UpdataShuffleIcon(ipodctlSHUFFLE nShuffe)
{
	//m_shuffleStatus = nShuffe;
	switch (nShuffe)
	{
	case SHUFFLE_OFF:
		{
			//m_pBtnGetShuffle->SetText(s_pLan[22]);
			m_pBtnGetShuffle->SetBkgndN(GetHMIPath(_T("Media\\Music\\Music_Close_Random_N.hfp")));
			m_pBtnGetShuffle->SetBkgndA(GetHMIPath(_T("Ipod\\Music_Close_Random_A.hfp")));
		}
		break;
	case SHUFFLE_TRACKS:
		{
			//m_pBtnGetShuffle->SetText(s_pLan[8]);
			m_pBtnGetShuffle->SetBkgndN(GetHMIPath(_T("Ipod\\Music_Random_N.hfp")));
			m_pBtnGetShuffle->SetBkgndA(GetHMIPath(_T("Ipod\\Music_Random_A.hfp")));
		}
		break;
	case SHUFFLE_ALBUMS:
		{
			m_pBtnGetShuffle->SetBkgndN(GetHMIPath(_T("Ipod\\Music_Random_N.hfp")));
			m_pBtnGetShuffle->SetBkgndA(GetHMIPath(_T("Ipod\\Music_Random_A.hfp")));
			//m_pBtnGetShuffle->SetText(s_pLan[21]);
			//m_pBtnGetShuffle->SetBkgndN(GetHMIPath(_T("Ipod\\Music_Close_n.hfp")));
			/*m_pBtnGetShuffle->SetBkgndN(GetHMIPath(_T("Ipod\\Music_Random_N.hfp")));
			m_pBtnGetShuffle->SetBkgndA(GetHMIPath(_T("Media\\Music\\Music_Close_Random_A.hfp")));*/
		}
		break;
	}
}
void CIpodDlg::UpdataRepeatIcon(ipodctlREPEAT nRepeat)
{
	//m_repeatStatus = nRepeat;
	switch(nRepeat)
	{
	case REPEAT_OFF:
		{
			//m_pBtnGetrepeat->SetText(s_pLan[7]);
			m_pBtnGetrepeat->SetBkgndN(GetHMIPath(_T("Ipod\\Music_Folder_n.hfp")));
			m_pBtnGetrepeat->SetBkgndA(GetHMIPath(_T("Ipod\\Music_Folder_a n.hfp")));
		}
		break;
	case REPEAT_ONE_TRACK:
		{
			//m_pBtnGetrepeat->SetText(s_pLan[20]);
			m_pBtnGetrepeat->SetBkgndN(GetHMIPath(_T("Ipod\\Music_Singles_N.hfp")));
			m_pBtnGetrepeat->SetBkgndA(GetHMIPath(_T("Ipod\\Music_Singles_A.hfp")));
		}
		break;
	case REPEAT_ALL_TRACKS:
		{
			//m_pBtnGetrepeat->SetText(s_pLan[19]);
			m_pBtnGetrepeat->SetBkgndN(GetHMIPath(_T("Ipod\\Music_loop_N.hfp")));
			m_pBtnGetrepeat->SetBkgndA(GetHMIPath(_T("Ipod\\Music_loop_A.hfp")));
		}
		break;
	}
}
void CIpodDlg::GetIpodLists(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->GetIpodLists(pObj);
}
bool CIpodDlg::GetIpodLists(void* pDlg)
{
	Sleep(10000);
	if(m_hGetSongInfoThread != 0)
	{
		//int  nPirority = GetThreadPriority(m_hGetSongInfoThread);
		//BOOL bRet = CeSetThreadPriority(m_hGetSongInfoThread,252);
		int  nPirority = CeGetThreadPriority(m_hGetSongInfoThread);
		IPODDEBEGINFO(L"m_hGetSongInfoThread = %d",nPirority);
	}
	DWORD nCostTime = GetTickCount();
	bool bResult = true;
	ipodctlERR nErr= ERR_FAIL;
	unsigned long nTotal = 0;
	m_nTrackListNum = 0;
	m_nAlbumListNum = 0;
	m_nOffListNum = 0;
	m_bListThreadRun = true;
	//m_bRun = false;
	if(m_bConnected)
	{
		IPODDEBEGINFO(L"&&555555");
		//EnterCriticalSection(&m_csThread);
		
		int nTry = 10;
		while (nTry > 0)
		{
			printf("++++++++++++nTry = %d++++++++++++++++++\r\n",nTry);
			nErr = ipodctl_GetPlayingTrackNum(&nTotal);//曲目总数
			if(nErr == ERR_OK)
			{
				break;
			}
			else
			{
				nTry--;
			   Sleep(1500);
			}
		}
		//LeaveCriticalSection(&m_csThread);
		IPODDEBEGINFO(L"&&666666");
		//nTotal = m_nTotalNum;
		ipodctlSHUFFLE nshuffleStatus = SHUFFLE_OFF;
		//switch (m_shuffleStatus)
		switch (nshuffleStatus)
		{
		case SHUFFLE_TRACKS:
			{
				if(nErr == ERR_OK)
				{
					unsigned i = 0;
					IPODDEBEGINFO(L"SHUFFLE_TRACKS::m_ntrackNum = %d",nTotal);
					wchar_t szTitle[100],szArtist[100],szAbum[100];
					while(!m_bUpdateThread && m_nTrackListNum < nTotal && m_bListThreadRun && m_bRun)
					{
						if(m_pTxtArtistPic->IsShow())
						{
							m_pTxtArtistPic->SetShow(false);
						}
						memset(szTitle,0,sizeof(szTitle));
						memset(szArtist,0,sizeof(szArtist));
						memset(szAbum,0,sizeof(szAbum));
						nCostTime = GetTickCount();
						//EnterCriticalSection(&m_csThread);
						nErr = ERR_FAIL;
						if(m_bRun)
						{
							nErr = ipodctl_GetTrackInfo(m_nTrackListNum,szTitle,szArtist,szAbum);
						}
						//LeaveCriticalSection(&m_csThread);
						if(nErr == ERR_OK && m_pScrboxIpodList != NULL && m_bRun)
						{
							HCListItem *pList= CreatIpodListItem(szTitle);
							if(pList != NULL && m_hMyHandle != INVALID_HANDLE_VALUE)
							{
								m_nTrackListNum++;
#if LOGFILE
								if(g_ListFile.is_open())
								{
									g_ListFile<<"m_nAlbumListNum = "<<m_nAlbumListNum<<"Title:"<<szTitle<<"  "<<"Artest:"<<szArtist<<"  "<<"Abum:"<<szAbum<<endl;
								}
#else
#endif
								::PostMessage(m_hMyHandle,WM_USER + 4,(WPARAM)pList,int(SHUFFLE_TRACKS));
							}
						}
					}
				}	
			}
			break;
		case SHUFFLE_ALBUMS:
			{
				if(nErr == ERR_OK)
				{
					unsigned i = 0;
					IPODDEBEGINFO(L"SHUFFLE_ALBUMS::m_ntrackNum = %d",nTotal);
					wchar_t szTitle[100],szArtist[100],szAbum[100];
					while(!m_bUpdateThread && m_nAlbumListNum < nTotal && m_bListThreadRun && m_bRun)
					{
						nCostTime = GetTickCount();
						memset(szTitle,0,sizeof(szTitle));
						memset(szArtist,0,sizeof(szArtist));
						memset(szAbum,0,sizeof(szAbum));
						//EnterCriticalSection(&m_csThread);
						nErr = ERR_FAIL;
						if(m_bRun)
						{
							nErr = ipodctl_GetTrackInfo(m_nAlbumListNum,szTitle,szArtist,szAbum);
						}
						//	LeaveCriticalSection(&m_csThread);
						if(nErr == ERR_OK && m_pScrboxIpodList != NULL && m_bRun)
						{
							HCListItem *pList= CreatIpodListItem(szTitle);
							if(pList != NULL && m_hMyHandle != INVALID_HANDLE_VALUE && m_bRun)
							{
								//InvalidateRect(m_pScrboxIpodList);
								//m_pScrboxIpodList->AddListItem(pList);
								m_nAlbumListNum++;
								IPODDEBEGINFO(L"ipodctl_GetTrackInfo:m_nAlbumListNum = %d,Title:%s,Artest:%s,Abum:%s",m_nAlbumListNum,szTitle,szArtist,szAbum);
#if LOGFILE
								if(g_ListFile.is_open())
								{
									g_ListFile<<"m_nAlbumListNum = "<<m_nAlbumListNum<<"Title:"<<szTitle<<"  "<<"Artest:"<<szArtist<<"  "<<"Abum:"<<szAbum<<endl;
								}
#else
#endif
								::PostMessage(m_hMyHandle,WM_USER + 4,(WPARAM)pList,(int)SHUFFLE_ALBUMS);
							}
						}
					}
				}	
			}
			break;
		case SHUFFLE_OFF:
			{
				if(nErr == ERR_OK)
				{
					IPODDEBEGINFO(L"&&777777");
					//IPODDEBEGINFO(L"SHUFFLE_OFF::m_ntrackNum = %d",nTotal);
					unsigned i = 0;
					wchar_t szTitle[100],szArtist[100],szAbum[100];
					while(m_nOffListNum < nTotal && m_bRun && m_bListThreadRun)
					{
						nCostTime = GetTickCount();
						memset(szTitle,0,sizeof(szTitle));
						memset(szArtist,0,sizeof(szArtist));
						memset(szAbum,0,sizeof(szAbum));
						IPODDEBEGINFO(L"&&888888");
						//EnterCriticalSection(&m_csThread);
						nErr = ERR_FAIL;
						nErr = ipodctl_GetTrackInfo(m_nOffListNum,szTitle,szArtist,szAbum);
						//LeaveCriticalSection(&m_csThread);
						IPODDEBEGINFO(L"&&9999999");
						if(nErr == ERR_OK && m_pScrboxIpodList != NULL && m_bRun)
						{
							IPODDEBEGINFO(L"&&101010");
							HCListItem *pList= CreatIpodListItem(szTitle);
							if(pList != NULL && m_hMyHandle != INVALID_HANDLE_VALUE)
							{
								m_nOffListNum++;
								IPODDEBEGINFO(L"ipodctl_GetTrackInfo:m_nOffListNum = %d,Title:%s,Artest:%s,Abum:%s",m_nOffListNum,szTitle,szArtist,szAbum);
#if LOGFILE
								if(g_ListFile.is_open())
								{
									string str1,str2,str3;

									g_ListFile<<"m_nOffListNum = "<<m_nOffListNum<<"Title:"<<szTitle<<"  "<<"Artest:"<<szArtist<<"  "<<"Abum:"<<szAbum<<endl;
								}
#else
#endif
								//::PostMessage(m_hMyHandle,WM_USER + 4,(WPARAM)pList,(int)SHUFFLE_OFF);
								::PostMessage(m_hMyHandle,WM_USER + 4,(WPARAM)pList,(int)((SHUFFLE_OFF<<16) + m_nOffListNum));
								Sleep(40);
							}
						}
						else 
						{
							m_bListThreadRun = false;
						}
					}
				}
			}
			break;
		}
	}
	//m_pBtnGetShuffle->EnableMsg(true);
	//m_hGetSongInfoThread = 0;
	IPODDEBEGINFO(L"m_hGetSongInfoThread = 0");
	return true;
}
HCListItem* CIpodDlg::CreatIpodListItem(WCHAR *pTitle)
{
		HCHAR pTemp[65] ;
		memset(pTemp,0,sizeof(pTemp));
		HCListItem* pTempListItemCallHistory = new HCListItem;
		HCTextCtrl* pIcon = new HCTextCtrl;
		pIcon->Create(0,0,80,60);
		pIcon->EnableMsg(false);
	//	sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
		if(m_pIREMusicIcon != NULL)
		{
			pIcon->SetBkgndN(m_pIREMusicIcon);
		}
		HCTextCtrl* p1 = new HCTextCtrl;
		if(pTitle != NULL && p1 != NULL)
		{
			p1->Create(100,0,600,60);
			p1->SetText(pTitle);
			p1->SetTextPos(0,16);
			p1->SetFontSize(24,24);
			p1->SetTxtColor(255,255,255);
			p1->EnableMsg(false);
			p1->SetTextStyle(RE_TS_NORMAL);
			if(pTempListItemCallHistory != NULL)
			{
				pTempListItemCallHistory->AddBaseCtrl((HCBaseCtrl*)pIcon);
				pTempListItemCallHistory->AddBaseCtrl((HCBaseCtrl*)p1);
				pTempListItemCallHistory->Create(736 , 66, NULL, NULL);
				pTempListItemCallHistory->SetEnableRoll(true, 1);
				pTempListItemCallHistory->SetFontPos(5);
				pTempListItemCallHistory->SetRollWidth(600);
				//pTempListItemCallHistory->SetText(pTitle);
				pTempListItemCallHistory->SetCanFocus(true);
				//		sbtSourceGroup *pSource= btSource::Instance()->GetBtSource(GetHMIPath(_T("")).c_str());
				if(m_pIREListItemSelect != NULL)
				{
					pTempListItemCallHistory->SetBkgndA(m_pIREListItemSelect);
					pTempListItemCallHistory->SetBkgndF(m_pIREListItemSelect);
				}
			}
			return pTempListItemCallHistory;
		}
	return NULL;
}
void CIpodDlg::OnBtnBackPrevious(void* pParam)
{
	if(m_bIpodListShow)
	{
		m_pGrpIpodList->SetShow(false);
		if(m_pScrboxIpodList->IsShow())
		{
			m_pScrboxIpodList->SetShow(false);
		}
		if(m_pScrboxIpodAlbumList->IsShow())
		{
			m_pScrboxIpodAlbumList->SetShow(false);
		}
		if(m_pScrboxIpodTrackList->IsShow())
		{
			m_pScrboxIpodTrackList->SetShow(false);
		}
		m_pGrpBtm->SetShow(true);
		m_pGrpMid->SetShow(true);
		m_pTxtArtist->SetShow(true);
		m_pTxtArtistPic->SetShow(true);
		m_bIpodListShow = false;
		m_bUpdateThread = true;
	}
	else
	{
		HWND hServerWnd = CEIPC_GetHWND(IPC_ID_MANAGE);
		if (NULL != hServerWnd)
		{
			//	::PostMessage(hServerWnd, UWM_TOPBAR_BACK, 0, 0);
			::PostMessage(hServerWnd, UWM_TOPBAR_HOME, 0, 0);
		}
	}
}
 DWORD  CIpodDlg::GetIpodListsThread(LPVOID pUserData)
{
	CIpodDlg* pDlg = static_cast<CIpodDlg*>(pUserData);
	if (pDlg != NULL)	
	{
		pDlg->GetIpodLists(NULL);
	}
	return 0;
 }
 void CIpodDlg::IpodListsAddItem(HCListItem *pListItem,int nShuffle)
 {
	 ipodctlSHUFFLE eShuffle = (ipodctlSHUFFLE)(nShuffle>>16);
	 int nIndex = (nShuffle&0xffff);
	 if(pListItem != NULL)
	 {
		 switch (eShuffle)
		 {
		 case SHUFFLE_OFF:
			 {
				 if(m_pScrboxIpodList != NULL)
				 {
					 if(nIndex == 1)
					 {
						 m_pScrboxIpodList->DeleteAllListItems();
						 IPODDEBEGINFO(L"m_pScrboxIpodList:DeleteAllListItems");
					 }
					 m_pScrboxIpodList->AddListItem(pListItem);
				 }
			 }
			 break;
		 case SHUFFLE_ALBUMS:
			 {
				 if(m_pScrboxIpodAlbumList != NULL)
				 {
					 m_pScrboxIpodAlbumList->AddListItem(pListItem);
				 }
			 }
			 break;
		 case SHUFFLE_TRACKS:
			 {
				 if(m_pScrboxIpodTrackList != NULL)
				 {
					 m_pScrboxIpodTrackList->AddListItem(pListItem);
				 }
			 }
			 break;
		 default:
			 break;
		 }
	 }
 }
  DWORD  CIpodDlg::UpdataIpodInfoThread(LPVOID pUserData)
  {
	  CIpodDlg* pDlg = static_cast<CIpodDlg*>(pUserData);
	  if (pDlg != NULL)	
	  {
		  pDlg->UpDataMediaInfoEx();
		//  pDlg->StatusThread();
	  }
	  return 0;
  }
  void CIpodDlg::ClearIpodData()
  {
	  IPODDEBEGINFO(L"%s",__FUNCTIONW__);
	/* m_pTxtSong->SetText(L"未知歌曲");
	 m_pTxtArtist->SetText(L"未知艺术家");
	 m_pTxtAbum->SetText(L"未知专辑");*/
	  m_bListThreadRun = false;
	 // m_bRun = false;
	 m_pTxtSong->SetText(s_pLan[0]);
	 m_pTxtArtist->SetText(s_pLan[1]);
	 m_pTxtAbum->SetText(s_pLan[2]);	
	/* m_pTxtSongHead->SetText(s_pLan[10]);
	 m_pTxtArtistHead->SetText(s_pLan[11]);
	 m_pTxtAbumHead->SetText(s_pLan[12]);	*/
	 IPODDEBEGINFO(L"___________2222225545555");
	// m_pTxtArtistPic->SetShow(false);	 
	  IPODDEBEGINFO(L"___________211111111111111");
	 m_nDowningTime = 0;
	 m_ntrackIndex = -1;
	 if(m_ctLoadData.IsActive())
	 {
		 m_ctLoadData.StopTimer();
	 }
	// m_pTxtCurrentIndex->SetShow(false);
	 IPODDEBEGINFO(L"^^^^^^^12^^***&&^^^^");
	BOOL bRusult =  ResetEvent(m_hIpodInsert);
	if(bRusult)
	{
		IPODDEBEGINFO(L"ResetEvent::bRusult = %d",bRusult);
	}
	DWORD dwRet = 0;
	if(m_hGetSongInfoThread != 0)
	{
		IPODDEBEGINFO(L"$$$44$$$44");
		dwRet = WaitForSingleObject(m_hGetSongInfoThread,2500);
		
		IPODDEBEGINFO(L"$$$44$$$11111144");
		//WaitForSingleObject(m_hUpdataThread,1000);
		if(dwRet== WAIT_TIMEOUT)
		{
			::TerminateThread(m_hGetSongInfoThread, 20);
			IPODDEBEGINFO(L"m_hGetSongInfoThread 程强行终止！");
		}
		else if(dwRet == WAIT_OBJECT_0)
		{
			IPODDEBEGINFO(L"m_hGetSongInfoThread exit Sucess!");
		}
		//dwRet = WaitForSingleObject(m_hUpdataThread,2500);
		////WaitForSingleObject(m_hUpdataThread,1000);
		//if(dwRet== WAIT_TIMEOUT)
		//{
		//	::TerminateThread(m_hUpdataThread, 10);
		//	IPODDEBEGINFO(L"m_hUpdataThread 程强行终止！");
		//}
		//else if(dwRet == WAIT_OBJECT_0)
		//{
		//	IPODDEBEGINFO(L"m_hUpdataThread exit Sucess!");
		//}
	}
	m_hGetSongInfoThread = 0;
	if(m_bIpodListShow)
	{
		OnBtnBackPrevious(NULL);
	}
	m_pTxtCurrentIndex->SetText(L" ");
	m_pTxtCurrentPlayTime->SetText(L"00:00");
	m_pTxtTrackTotalTime->SetText(L"00:00");
	m_pSldPlayTime->SetBound(0,50);
	m_pSldPlayTime->SetValue(0);
	if(!m_pTxtArtistPic->IsShow())
	{
		m_pTxtArtistPic->SetShow(TRUE);
	}
	m_pTxtArtistPic->SetBkgndN(m_pIREArtistBk);
	IPODDEBEGINFO(L"%s:end",__FUNCTIONW__);
  }

  void CIpodDlg::StatusThread()//更新时间与播放状态
  {
	  unsigned long u32len,u32pos,u32index;
	  ipodctlPLAYSTATUS u8status;
	  ipodctlERR ret;
	  unsigned long lensec,lenmin,possec,posmin;
//	  CString *str = new CString();
	  while(true)
	  {
		  ret = ipodctl_GetPlayStatus(&u32index,&u32len,&u32pos,&u8status);
		//  RETAILMSG(1,(TEXT("**************StatusThread:\r\n")));
		  //wprintf(TEXT("ret = %d",ret));
		  IPODDEBEGINFO(L"ret = %d,u32index = %d,u32len = %d,u32pos = %d,u8status = %d",ret,u32index,u32len,u32pos,u8status);
		  //  IPODDEBEGINFO(L"%s,err = %d,m_ntrackIndex = %d,m_pntrackLength = %d,m_pntrackPosition = %d,m_nplayStatus = %d",__FUNCTIONW__,err,m_ntrackIndex,m_ntrackLength,m_ntrackPosition,m_nPlayStatus);
		  if(ERR_OK==ret)
		  {
			  if(m_bConnected == FALSE)
			  {
				  ipodctl_StartPlay(PAGE_PLAYLIST, 0, 0);
				  m_bConnected = TRUE;
			  }
			  posmin = u32pos/60000;
			  possec = (u32pos/1000)%60;
			  lenmin = u32len/60000;
			  lensec = (u32len/1000)%60;
			//  str->Format(_T("%02d:%02d/%02d:%02d"),posmin,possec,lenmin,lensec);
			  //cWnd5->SetWindowTextW(*str);
			  switch(u8status)
			  {
			  case PLAYSTATUS_STOPPED:
				 // cWnd6->SetWindowTextW(_T("stopped"));
				  break;
			  case PLAYSTATUS_PLAYING:
				//  cWnd6->SetWindowTextW(_T("playing"));
				  break;
			  case PLAYSTATUS_PAUSED:
				 // cWnd6->SetWindowTextW(_T("paused"));
				  break;
			  default:
				  break;
			  }
//			  if(u32index!=m_ntrackIndex)
			 // {
				  //update(u32index);
				 // u32CurIndex = u32index;
			//  }
		  }
		  else if(ERR_IPODEXIT==ret)
		  {
			  m_bConnected = FALSE;
			 // cWnd6->SetWindowTextW(_T("ipod exit"));
		  }
		  else if(ERR_NOTCNNT==ret)
		  {
			 // bConnected = FALSE;
			 // cWnd6->SetWindowTextW(_T("not connect"));
		  }
		  Sleep(1000);
	  }
  }
  void CIpodDlg::UpdataArteistPic(HINT nType)
  {
	  if(m_pTxtArtistPic != NULL)
	  {
		  switch(nType)//0 有照片 1 无照片
		  {
			 case 0:
			  {
				  if(m_pIREArtistBk != NULL)
				  {
					  if(m_bUpdateThread)
					  {
						  if(!m_pTxtArtistPic->IsShow())
						  {
							  m_pTxtArtistPic->SetShow(TRUE);
						  }
						  m_pTxtArtistPic->SetBkgndN(m_pIREArtistBk);
					  }
					  else
					  {
						  if(m_pTxtArtistPic->IsShow())
						  {
							  m_pTxtArtistPic->SetBkgndN(m_pIREArtistBk);
							  m_pTxtArtistPic->SetShow(FALSE);
						  }
					  }
					
				  } 
			  }
			  break;
			 case 1:
			{
				//EnableUpdateRect(false);	
			  //  IReSurface *pp = GetRESingleton()->CreateSurface(184, 184, RE_COLOR565);
			     m_pIREStr->StretchBlt(m_pIREArtist,0,0,240,240,0,0,128,128,1);
			//	 if(m_iPicState == 0)
				// {
					// pp->RippleBitBlt(m_pIREStr,0,0,10,30,0,0,50,50,1,false);
					// m_pTxtArtistPic->SetBkgndN(pp);
				// }
				// else
				// {
					m_pTxtArtistPic->SetBkgndN(m_pIREStr);	
				// }
				//m_pTxtArtistPic->SetBkgndN(m_pIREArtist);
				//SAFE_DELETE(m_pIREArtist);
				IPODDEBEGINFO(L"m_pIREArtist = %d,m_pIREArtistPre = %d",m_pIREArtist,m_pIREArtistPre);
			  //SAFE_DELETE(m_pIREArtistPre);
				/*if(m_pIREArtistPre != NULL)
				{
					m_pIREArtistPre->Release();
				}*/
				m_pIREArtistPre = m_pIREArtist;
				//EnableUpdateRect(true);
				if(m_bUpdateThread)
				{
					if(!m_pTxtArtistPic->IsShow())
					{
						m_pTxtArtistPic->SetShow(true);
					}
				}
				else
				{
					if(m_pTxtArtistPic->IsShow())
					{
						m_pTxtArtistPic->SetShow(false);
					}
				}
				
				//EnableUpdateRect(true);
				if(m_iPicState == -1)
				{
					m_ctPic.SetTime(30);
					m_iPicState = 0;
					m_ctPic.StartTimer();
				}
			 }
			break;
		  }
	  }
  }
void CIpodDlg::CombinaPic(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->CombinaPic(pObj);
}
  void CIpodDlg::CombinaPic(void* pDlg)
  {
	  if(m_pArtistPic != NULL && m_pArtistPicPre != NULL && m_pTxtArtistPic != NULL)
	  {
		  switch (m_iPicState)
		  {
				case 0:
			  {
				  unsigned char szTemp[256] = {0};
				  if(m_iPicDirection == 0)
				  {
					  for(int j = 0;j < 128;j++)
					  {
						  memset(szTemp,0,sizeof(szTemp));
						  memcpy(szTemp,m_pArtistPicPre + 256*j + 64,192);
						  memcpy(szTemp + 192,m_pArtistPic + 256*j + 64,64);
						  memcpy(m_pArtistPicPre + j*256,szTemp,256);
					  }
				  }
				  else
				  {
					  for(int j = 0;j < 128;j++)
					  {
						  memset(szTemp,0,sizeof(szTemp));
						  memcpy(szTemp,m_pArtistPic + 256*j + 128,64);
						  memcpy(szTemp+ 64,m_pArtistPicPre + 256*j,192);
						  memcpy(m_pArtistPicPre + j*256,szTemp,256);
					  }
				  }
				// m_pIREArtist = GetRESingleton()->CreateSurfaceFrom565Mem(m_pArtistPic,128,128);
				  //GetRESingleton()->ModifyKtcStreamSurface(m_pArtistPicPre,m_pIREArtist);
				//  m_pIREArtist = GetRESingleton()->CreateSurfaceFrom565Mem(m_pArtistPicPre,128,128);
				  if(m_ctPic.IsActive())
				  {
					  m_ctPic.StopTimer();
				  }
				  ::PostMessage(m_hMyHandle,WM_USER + 7,1,NULL);
				  m_ctPic.SetTime(30);
				  m_iPicState = 1;
				  m_ctPic.StartTimer();
			  }
			  break;
			case 1:
			{
				unsigned char szTemp[256] = {0};
				if(m_iPicDirection == 0)
				{
					for(int j = 0;j < 128;j++)
					{
						memset(szTemp,0,sizeof(szTemp));
						memcpy(szTemp,m_pArtistPicPre + 256*j + 64,192);
						memcpy(szTemp + 192,m_pArtistPic + 256*j + 128,64);
						memcpy(m_pArtistPicPre + j*256,szTemp,256);
					}
				}
				else
				{
					for(int j = 0;j < 128;j++)
					{
						memset(szTemp,0,sizeof(szTemp));
						memcpy(szTemp,m_pArtistPic + 256*j + 64,64);
						memcpy(szTemp+64,m_pArtistPicPre + 256*j,192);
						memcpy(m_pArtistPicPre + j*256,szTemp,256);
					}
				}
				//IReSurface *PP = m_pIREArtist;
				//GetRESingleton()->ModifyKtcStreamSurface(m_pArtistPicPre,m_pIREArtist);
			//	m_pIREArtist = GetRESingleton()->CreateSurfaceFrom565Mem(m_pArtistPicPre,128,128);		
				if(m_ctPic.IsActive())
				{
					m_ctPic.StopTimer();
				}
				::PostMessage(m_hMyHandle,WM_USER + 7,1,NULL);
				m_ctPic.SetTime(30);
				m_iPicState = 2;
				m_ctPic.StartTimer();
			}
			break;
			case 2:
			{
			//	memcpy(m_pArtistPicPre,m_pArtistPic,sizeof(m_pArtistPicPre));
				if(m_ctPic.IsActive())
				{
					m_ctPic.StopTimer();
				}
				memset(m_pArtistPicPre,0,128*128*3);
				memcpy(m_pArtistPicPre,m_pArtistPic,128*128*3);
				//GetRESingleton()->ModifyKtcStreamSurface(m_pArtistPicPre,m_pIREArtist);
			//	m_pIREArtist = GetRESingleton()->CreateSurfaceFrom565Mem(m_pArtistPicPre,128,128);
				//m_pIREArtist = GetRESingleton()->CreateSurfaceFrom565Mem(m_pArtistPicPre,128,128);
				::PostMessage(m_hMyHandle,WM_USER + 7,1,NULL);
				m_iPicState = 0;
			}
			break;
		  }
	  }
  }
  HINT CIpodDlg::ReadLangeContent(HUINT nMax)
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
	  appPath += L"..\\Config\\IpodLange.txt";
	  HINT nIndex = 0;
	  ifstream examplefile1(appPath.c_str()/*L"\\HZcar\\786sdk (armv4i)_debug\\UsefulNumbers.txt"*/);
	  if (! examplefile1.is_open())
	  {
		  IPODDEBEGINFO(L"can not open IpodLange.txt");
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
  void CIpodDlg::StopIpodMusic()
  {
	  m_bRun = false;
	  if(m_nPlayStatus == PLAYSTATUS_PLAYING || m_bFFREW)
	  {
		  OnPlayPause(NULL);
	  }
  }
  ipodctlERR CIpodDlg::StartPlayIpodMusic()
  {
	  IPODDEBEGINFO(L"%s____-",__FUNCTIONW__);
	  ipodctlERR err = ERR_FAIL;
	  ipodctlPLAYSTATUS nPlayState = PLAYSTATUS_PLAYING;
	  unsigned long nCurrentIndex = 0;
	  unsigned long ntrackLength = 0;
	  unsigned long ntrackPosition = 0;
	  if(m_bInsert == false)
	  {
		 // OnInsert(NULL);
	  }
	  else
	  {
		  err = ipodctl_GetPlayStatus(&nCurrentIndex,&ntrackLength,&ntrackPosition,&nPlayState);
		  switch (nPlayState)
		  {
		  case PLAYSTATUS_PLAYING:
			  {
				  err = ERR_OK;
			  }
			  break;
	/*	  case PLAYSTATUS_STOPPED:
			  {
				  err = ipodctl_StartPlay(PAGE_PLAYLIST,0,0);
			  }
			  break;*/
		  case PLAYSTATUS_PAUSED:
			  {
				  err = ipodctl_PlayPause();
				  //OnPlayPause(NULL);
				  //err  = ERR_OK;
			  }
			  break;
		  }
		  SetEvent(m_hIpodInsert);
	  }
	  return err;
  }
  ipodctlERR CIpodDlg::PauseIpodMusic()
  {
	  IPODDEBEGINFO(L"%s:beg",__FUNCTIONW__);
	  if(!m_bConnected)
		  return ERR_FAIL;
	  ipodctlERR err = ERR_OK;
	  if(m_bFFREW && m_bInsert)
	  {
		  err = ipodctl_EndFFRew();
	  }
	  ipodctlPLAYSTATUS nPlayState = PLAYSTATUS_PLAYING;
	  unsigned long nCurrentIndex = 0;
	  unsigned long ntrackLength = 0;
	  unsigned long ntrackPosition = 0;
	  IPODDEBEGINFO(L"JKJKHJKjkhhjkhh");
	  // EnterCriticalSection(&m_csThread);
	  err = ipodctl_GetPlayStatus(&nCurrentIndex,&ntrackLength,&ntrackPosition,&nPlayState);
	  //  LeaveCriticalSection(&m_csThread);
	  IPODDEBEGINFO(L"JKJKHJKjkhhjkhh1111");
	  if(nPlayState == PLAYSTATUS_PLAYING && m_bInsert)
	  {
		  err = ipodctl_PlayPause();
		  //if(err == ERR_OK)
		  //{
			 // m_pBtnPlayPause->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Pause_N.hfp")));
			 // m_pBtnPlayPause->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Pause_A.hfp")));
			 //  m_nPreplayStatus = PLAYSTATUS_PAUSED;
		  //}
		  IPODDEBEGINFO(L"JKJKHJKjkhhjkhh22222222");
	  }
	  IPODDEBEGINFO(L"ResetEvent::768676676");
	 // ResetEvent(m_hIpodInsert);
	  IPODDEBEGINFO(L"ResetEvent::333333");
	  IPODDEBEGINFO(L"%s:End",__FUNCTIONW__);
	  return ERR_OK;
  }
  void  CIpodDlg::RunInBackground(bool bInBackground)
  {
	  IPODDEBEGINFO(L"%s:bInBackground = %d",__FUNCTIONW__,bInBackground);
	  if(bInBackground)
	  {
		 /* HWND hServerWnd = ::FindWindow(STR_PROCESSNAME_BT, STR_PROCESSNAME_BT);
		  if (hServerWnd)
		  {
			  ::ShowWindow(hServerWnd,SW_SHOW);
			  ::SetForegroundWindow(hServerWnd);
		  }*/
		  PauseIpodMusic();
		  ReleaseSource();
		  if(m_bUpdateThread)
		  {
			//  EnterCriticalSection(&m_csThread);
		  }
		  else
		  {
			  //OnBtnBackPrevious(NULL);
			  //m_bIpodListShow = false;
			  m_bUpdateThread = true;
			//  EnterCriticalSection(&m_csThread);	
		  }
	  }
	  else
	  {
		  RequreSource();
		/*  HWND hServerWnd = ::FindWindow(STR_PROCESSNAME_IPOD, STR_PROCESSNAME_IPOD);
		  if (hServerWnd)
		  {
			  ::ShowWindow(hServerWnd,SW_SHOW);
			  ::SetForegroundWindow(hServerWnd);
		  }*/
		  StartPlayIpodMusic();
		  if(m_bIpodListShow)
		  {
			  m_bUpdateThread = true;
			  m_bIpodListShow = false;
			  //m_bUpdateThread = false
			  OnIpodList(NULL);
		  }
		 // LeaveCriticalSection(&m_csThread);
	  }
  }

 #if TESTIPODINSERTEVENT
void CIpodDlg::OnInsert(void* pDlg, void* param)
{
  CIpodDlg* pObj = (CIpodDlg*)pDlg;
  pObj->OnInsert(pObj);
}
void CIpodDlg::OnInsert(void* pDlg)
{
	bool bResult = false;
	if(!m_bInsert)
	{
		bResult = SetEvent(m_hIpodInsert);
		if(bResult)
		{
			IPODDEBEGINFO(L"SetEvent::m_hIpodInsert Sucess");
		}
		else
		{
			IPODDEBEGINFO(L"SetEvent::m_hIpodInsert Failed");
			IPODDEBEGINFO(L"Lasterr = %d",GetLastError());
		}
#if TESTIPODINSERTEVENT
		m_pBtnIpodInsert->SetText(L"Disconnect");
#endif
		m_bInsert = true;
		RequreSource();
		OnLoadDataEx(NULL);
	}
	else
	{
		/*bResult = ResetEvent(m_hIpodInsert);
		if(bResult)
		{
		IPODDEBEGINFO(L"ResetEvent::m_hIpodInsert Sucess");
		}
		else
		{
		IPODDEBEGINFO(L"ResetEvent::m_hIpodInsert Failed");
		IPODDEBEGINFO(L"Lasterr = %d",GetLastError());
		}*/
		ClearIpodData();
		m_bInsert = false;
#if TESTIPODINSERTEVENT
	m_pBtnIpodInsert->SetText(L"Insert");
#endif
		
	/*	ipodctlERR err1 =  ipodctl_SetShuffle(SHUFFLE_OFF);
		if(err1 == ERR_OK)
		{
			IPODDEBEGINFO(L"ipodctl_SetShuffle::Sucessful");
		}*/
		ReleaseSource();
	}
	
}
#endif
//void CIpodDlg::OnIpodRemove()
//{
//	IPODDEBEGINFO(L"%s",__FUNCTIONW__);
//     ClearIpodData();
//	 ReleaseSource();
//	 m_bInsert = false;
//	 IPODDEBEGINFO(L"%s:end",__FUNCTIONW__);
//}
//void CIpodDlg::OnIpodreInsert()
//{
//	m_bConnected = false;
//	//ClearIpodData();
//	 m_pTxtSong->SetText(s_pLan[0]);
//	 m_pTxtArtist->SetText(s_pLan[1]);
//	 m_pTxtAbum->SetText(s_pLan[2]);	
//	/* m_pTxtSongHead->SetText(s_pLan[10]);
//	 m_pTxtArtistHead->SetText(s_pLan[11]);
//	 m_pTxtAbumHead->SetText(s_pLan[12]);	*/
//	 //m_pTxtArtistPic->SetShow(false);	 
//	 m_nDowningTime = 0;
//	 m_ntrackIndex = -1;
//	 if(m_ctLoadData.IsActive())
//	 {
//		 m_ctLoadData.StopTimer();
//	 }
//	 m_pTxtCurrentIndex->SetText(L" ");
//	 m_pTxtCurrentPlayTime->SetText(L"00:00 ");
//	 m_pTxtTrackTotalTime->SetText(L"00:00");
//	 m_pSldPlayTime->SetBound(0,50);
//	 m_pSldPlayTime->SetValue(0);
//}
void CIpodDlg::OnRealseButton(void* pDlg, void* param)
{
	CIpodDlg* pObj = (CIpodDlg*)pDlg;
	pObj->OnRealseButton(pObj);
}
void CIpodDlg::OnRealseButton(void* pDlg)
{
	if(m_ctButton.IsActive())
	{
		m_ctButton.StopTimer();
	}
	m_bButtonPress = false;
}


bool  CIpodDlg::WaitForIpodReady(int ntime)
{
	if(!m_bIpodReady)
	{
		OnLoadDataEx(NULL);
		DWORD nRet = WaitForSingleObject(m_hIpodReady,8000);
		switch(nRet)
		{
		case WAIT_OBJECT_0:
			{
				if(m_ctLoadData.IsActive())
				{
					m_ctLoadData.StopTimer();
				}
				HidePopup();
				m_bIpodReady = true;
				return true;
			}
			break;
		case WAIT_TIMEOUT:
			{
				return false;
				if(m_ctLoadData.IsActive())
				{
					m_ctLoadData.StopTimer();
				}
				//SetPopupInfor(s_pLan[23]);
				//ShowPopup(PT_NOR, 0);
				PostMessage(m_hMyHandle,WM_USER + 16,0,0);
			}
			break;
		}
		return false;
	}
	else
	{
		return true;
	}
}
void CIpodDlg::OnLoadDataEx(void* pDlg)
{
	if(m_ctLoadData.IsActive())
	{
		m_ctLoadData.StopTimer();
	}
	IPODDEBEGINFO(L"m_nDowningTime = %d",m_nDowningTime);
	if(m_nDowningTime >= 40)
	{
		IPODDEBEGINFO(L"iPod加载数据超时!");
		//SetPopupInfor(s_pLan[23]);
		//ShowPopup(PT_NOR, 30);
		PostMessage(m_hMyHandle,WM_USER + 16,0,0);
		//::PostMessage(m_hMyHandle,WM_USER +8,0,NULL);
		return;
	}

	m_ctLoadData.SetTime(40);
	m_ctLoadData.StartTimer();
	HINT nn = m_nDowningTime%6;
	switch (nn)
	{
	case 0:
		{
			//m_pTxtInfo->SetText(s_pLan[13]);
			//	 m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[0]);
			SetPopupInfor(s_pLan[13]);
			ShowPopup(PT_NOR, 0);
		}
		break;
	case 1:
		{
			//m_pTxtInfo->SetText(s_pLan[14]);
			SetPopupInfor(s_pLan[14]);
			ShowPopup(PT_NOR, 0);
			// m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[1]);
		}
		break;
	case 2:
		{
			//m_pTxtInfo->SetText(s_pLan[15]);
			SetPopupInfor(s_pLan[15]);
			ShowPopup(PT_NOR, 0);
			// m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[2]);
		}
		break;
	case 3:
		{
			//m_pTxtInfo->SetText(s_pLan[16]);
			SetPopupInfor(s_pLan[16]);
			ShowPopup(PT_NOR, 0);
			// m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[3]);
		}
		break;
	case 4:
		{
			//m_pTxtInfo->SetText(s_pLan[17]);
			SetPopupInfor(s_pLan[17]);
			ShowPopup(PT_NOR, 0);
			// m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[4]);
		}
		break;
	case 5:
		{
			//m_pTxtInfo->SetText(s_pLan[18]);
			SetPopupInfor(s_pLan[18]);
			ShowPopup(PT_NOR, 0);
			// m_pTxtNoticeBK->SetBkgndN(pSource->m_pDownProcess[5]);
		}
		break;
	}
	m_nDowningTime++;

	//m_nDowningTime %= 6;
	//if(!m_pTxtCover->IsShow())
	//{
	//	m_pTxtCover->SetShow(true);
	//}

	//if(!m_pTxtInfoFrame->IsShow())
	//{
	//	m_pTxtInfoFrame->SetShow(true);
	//}
	//if(!m_pTxtInfo->IsShow())
	//{
	//	m_pTxtInfo->SetShow(true);
	//}
}
bool CIpodDlg::IsIpodConnect()
{
    return m_bConnected;
}
int CIpodDlg::GetNumberCategorizedDBRecords()
{
  unsigned char iPage = 0;
  for(iPage = 0; iPage <= 11;iPage++)
  {
	 unsigned long nTotal = 0;
      ipodctl_GetNumberCategorizedDBRecords((ipodctlPAGE)iPage,&nTotal);
	 // if(iPage == PAGE_ARTIST)
	  //if(iPage == PAGE_TRACK)
	  {
		  unsigned char *pOut = new unsigned char[3000];
		  unsigned long nGet = 0;
		  unsigned long nStart = 0;
		 while(nTotal > 0)
		  {
			  if(nTotal > GETTRACKEVERYTIME)
			  {
				 nGet = GETTRACKEVERYTIME;
			  }
			  else
			  {
				  nGet = nTotal;
			  }
			IPODDEBEGINFO(L"----------ipodctl_GetCategorizedDBRecords: iPage = %d,nStart = %d,nGet = %d-----------------",iPage,nStart,nGet);
			ipodctl_GetCategorizedDBRecords((ipodctlPAGE)iPage,nStart,nGet,pOut);
			nStart += nGet;
			nTotal -= nGet;
		  }
	  }
  }
  return 0;
}
int CIpodDlg::GetDBITunesInfo()
{
  for(unsigned char cType = 0;cType < 0x06;cType++)
  {
	  ipodctl_GetDBiTunesinfo(cType);
  }
  return 0;
}

void CIpodDlg::UpdataPlayPauseIcon(ipodctlPLAYSTATUS nPlayState)
 {
	 switch (m_nPlayStatus)
	 {
	 case PLAYSTATUS_STOPPED:
		 {
			 // m_pBtnPlayPause->SetText(s_pLan[5]);
			 m_pBtnPlayPause->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Pause_N.hfp")));
			 m_pBtnPlayPause->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Pause_A.hfp")));
		 }
		 break;
	 case PLAYSTATUS_PLAYING:
		 {
			 //m_pBtnPlayPause->SetText(s_pLan[6]);
			 m_pBtnPlayPause->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Play_N.hfp")));
			 m_pBtnPlayPause->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Play_A.hfp")));
		 }
		 break;
	 case PLAYSTATUS_PAUSED:
		 {
			 m_pBtnPlayPause->SetBkgndN(GetHMIPath(_T("Media\\Share\\Media_Pause_N.hfp")));
			 m_pBtnPlayPause->SetBkgndA(GetHMIPath(_T("Media\\Share\\Media_Pause_A.hfp")));
		 }
		 break;
	 default:
		 break;
   }
}
void CIpodDlg::HideIpodPopUP()
{
	if(m_ctLoadData.IsActive())
	{
		m_ctLoadData.StopTimer();
	}
	if(m_pTxtInfo->IsShow())
	{
		m_pTxtInfo->SetShow(false);
	}
	if(m_pTxtCover->IsShow())
	{
		m_pTxtCover->SetShow(false);
	}
	if(m_pTxtInfoFrame->IsShow())
	{
		m_pTxtInfoFrame->SetShow(false);
	}
	// s_nSucess++;
	if(m_ctLoadData.IsActive())
	{
		m_ctLoadData.StopTimer();
		IPODDEBEGINFO(L"HidePopup");
	}
	if(m_pGrp_Popup->IsShow())
	{
			HidePopup();
	}
}
void CIpodDlg::ShowLoadDataFailed()
  {
	   SetPopupInfor(s_pLan[23]);
	  ShowPopup(PT_NOR, 0);
  }
void CIpodDlg::UpdataTrackInfo(sSongInfo *pTrack)
{
	 if(pTrack != NULL)
	 {
		 m_pTxtSong->SetText(pTrack->szTitle);
		 m_pTxtArtist->SetText(pTrack->szArtist);
		 m_pTxtAbum->SetText(pTrack->szAlbum);
	 }
	// printf("pTrack->nIndex = %d,pTrack->nTotal = %d\r\n",pTrack->nIndex+1,pTrack->nTotal);
	 HCHAR szTemp[30] = {0};
	 if((pTrack->nIndex+1 <= pTrack->nTotal) && (pTrack->nTotal != -1))
	 {
		 wsprintf(szTemp,L"%d/%d",pTrack->nIndex+1,pTrack->nTotal);             
		 m_pTxtCurrentIndex->SetText(szTemp);
		 m_pTxtCurrentIndex->SetShow(true);
	 }
	 else
	 {
        m_pTxtCurrentIndex->SetShow(false);
	 }
}