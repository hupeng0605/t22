#pragma once
#include "define.h"
#include "ipodctl.h"

class CIpodDlg : public KDialogP
{	
public:
	CIpodDlg();
	virtual~CIpodDlg();
	HINT OnInit();
	virtual void ChangeLangue(HINT nType);
	virtual HBOOL DoMessage(HMessage* msg);
	virtual void RequreSource();
	virtual void ReleaseSource();
	void SetIpodDlgBackGround();
	static void OnPlayPause(void* pDlg, void* param);
	void OnPlayPause(void* pDlg);
	static void OnPlayMute(void* pDlg, void* param);
	void OnPlayMute(void* pDlg);
	static void OnForward(void* pDlg, void* param);
	void OnForward(void* pDlg);
	static void OnBack(void* pDlg, void* param);
	void OnBack(void* pDlg);
	static void OnConnect(void* pDlg, void* param);
    void OnConnect(void* pDlg);
	static void OnFF(void* pDlg, void* param);
	void OnFF(void* pDlg);
	static void OnEndFFRew(void* pDlg, void* param);
	void OnEndFFRew(void* pDlg);
	static void OnStartRew(void* pDlg, void* param);
	void OnStartRew(void* pDlg);
	static void OnGetTrackInfo(void* pDlg, void* param);
	void OnGetTrackInfo(void* pDlg);
	static void OnGetPlayingTrackNum(void* pDlg, void* param);
	void OnGetPlayingTrackNum(void* pDlg);
	static void OnSetCurrentPlayingTrack(void* pDlg, void* param);
	void OnSetCurrentPlayingTrack(void* pDlg);
	static void OnGetShuffle(void* pDlg, void* param);
	void OnGetShuffle(void* pDlg);
	static void OnGetRepeat(void* pDlg, void* param);
	void OnGetRepeat(void* pDlg);
	static void OnSetShuffle(void* pDlg, void* param);
	void OnSetShuffle(void* pDlg);
	static void OnSetRepeat(void* pDlg, void* param);
	void OnSetRepeat(void* pDlg);
	void OnStartPlay(void* pDlg,void* param);
	void OnStartPlay(void* pDlg);
	static void OnIpodList(void* pDlg,void* param);
	void OnIpodList(void* pDlg);
	static void OnScrboxIpodList(void* pDlg,void* param);
	void OnScrboxIpodList(void* pDlg);
	static void OnGetArtworkData(void* pDlg, void* param);
	void OnGetArtworkData(void* pDlg);
	static void OnGetArtPicData(void* pDlg, void* param);
	void OnGetArtPicData(void* pDlg);
	static void OnLoadData(void* pDlg, void* param);
	void OnLoadData(void* pDlg);
	HINT UpDataMediaInfo(void);
	HINT UpDataMediaInfoEx(void);
	void DealWithErr(ipodctlERR err);
	void UpdataSongInfo(unsigned long curIndex);
	void ChangeTheme(HBYTE uType);
	static void  MonitorIpodEventThread();
	void SetMyHandle(HWND hWin);
	bool  ConectAndStartPlay();
	void ClearIpodData();
	void UpdataPlayingTime(unsigned long nPostion,unsigned long nTotleTime);
	void UpdataShuffleIcon(ipodctlSHUFFLE nShuffe);
	void UpdataRepeatIcon(ipodctlREPEAT nRepeat);
	static void GetIpodLists(void* pDlg, void* param);
	bool GetIpodLists(void* pDlg);
	HCListItem* CreatIpodListItem(WCHAR *pTitle);
	virtual void OnBtnBackPrevious(void* pParam); 
	static DWORD WINAPI GetIpodListsThread(LPVOID pUserData);
	void IpodListsAddItem(HCListItem *pListItem,int nShuffle);
	static DWORD WINAPI UpdataIpodInfoThread(LPVOID pUserData);
	void StatusThread();
	void UpdataArteistPic(HINT nType);
	static void CombinaPic(void* pDlg, void* param);
	void CombinaPic(void* pDlg);
	HINT ReadLangeContent(HUINT nMax);
	void StopIpodMusic();
	ipodctlERR StartPlayIpodMusic();
	ipodctlERR PauseIpodMusic();
	void  RunInBackground(bool bInBackground);
	static void OnRealseButton(void* pDlg, void* param);
	void OnRealseButton(void* pDlg);
	bool  WaitForIpodReady(int ntime);
	void OnLoadDataEx(void* pDlg);
	bool IsIpodConnect();
	int GetNumberCategorizedDBRecords();
	int GetDBITunesInfo();
   void UpdataPlayPauseIcon(ipodctlPLAYSTATUS nPlayState);
   void HideIpodPopUP();
   void ShowLoadDataFailed();
   void UpdataTrackInfo(sSongInfo *pTrack);
#if TESTIPODINSERTEVENT
	static void OnInsert(void* pDlg, void* param);
	void OnInsert(void* pDlg);
	void OnIpodRemove();
	void OnIpodreInsert();
#endif
private:
	HCHAR (*s_pLan)[50];
	sLangue m_EnLan;
	sLangue m_ChLan;
	HCGroupCtrl *m_pGrpMid;
	HCGroupCtrl *m_pGrpBtm;
	HCButton	    *m_pBtnPlayPause;
	HCButton	    *m_pBtnSetAutoConn;
	HCButton        *m_pBtnStartPlay;
	HCButton      *m_pBtnNext;
	HCButton     *m_pBtnPre;
	HCButton  *m_pBtnStartFF;
	HCButton  *m_pBtnEndFFRew;
	HCButton  *m_pBtnStartRew;
	HCButton  *m_pBtnGetTrackInfo;
	HCButton  *m_pBtnGetPlayingTarckNum;
	HCButton  *m_pBtnSetCurrentPlayingTrack;
	HCButton *m_pBtnGetArtWorkData;
	HCButton *m_pBtnGetShuffle;
	HCButton *m_pBtnSetShuffle;
	HCButton *m_pBtnGetrepeat;
	HCButton *m_pBtnSetRepead;
	HCButton *m_pBtnPlayList;
	HCTextCtrl *m_pTxtSong;//曲目
	HCTextCtrl *m_pTxtArtist;//艺术家
	HCTextCtrl *m_pTxtAbum;//专辑
	HCImageCtrl *m_pTxtIpodBk;//背景
	//HCTextCtrl *m_pTxtSongHead;//曲目
	//HCTextCtrl *m_pTxtArtistHead;//艺术家
	//HCTextCtrl *m_pTxtAbumHead;//专辑
	HCTextCtrl *m_pTxtCurrentIndex;//当前播放序号
	HCTextCtrl *m_pTxtCurrentPlayTime;//当前播放时间
	HCTextCtrl *m_pTxtTrackTotalTime;//当前曲目总时间
	HCSlideCtrl *m_pSldPlayTime;//进度条
	//HCTextCtrl *m_pTxtBootmBK;//底栏
	HCTextCtrl *m_pTxtArtistPic;
	//列表
	HCGroupCtrl      *m_pGrpIpodList;
	//HCScrollCtrl    *m_pScrctrlIpodList;
	HCScrollBox     *m_pScrboxIpodList;//SHUFFLE_OFF列表			
	HCScrollBox		*m_pScrboxIpodAlbumList;
	HCScrollBox		*m_pScrboxIpodTrackList;
//	HCButton	    *m_pBtnIpodListUp;
//	HCButton	    *m_pBtnIpodListDown;
	HCTextCtrl *m_pTxtLine1;
	HCTextCtrl *m_pTxtLine2;
	HCTextCtrl *m_pTxtLine3;
	HCTextCtrl *m_pTxtLine4;
	HCTextCtrl *m_pTxtLine5;
	HCTextCtrl *m_pTxtInfoFrame;
	HCTextCtrl *m_pTxtInfo;
	HCTextCtrl *m_pTxtCover;
#if TESTIPODINSERTEVENT
	HCButton *m_pBtnIpodInsert;
#endif
//数据相关
	//HANDLE m_hIpodInsert;
	//HANDLE m_hIpodUnplug;
	IReSurface *m_pIREArtist;
	IReSurface *m_pIREArtistPre;
	IReSurface *m_pIRELine;
	IReSurface *m_pIREListItemSelect;
	IReSurface *m_pIREMusicIcon;
	IReSurface *m_pIREStr;
	IReSurface  *m_pIREArtistBk;
	IReSurface *m_pIREInfoFrame;
	HWND m_hMyHandle;
//	HANDLE m_hMonitorIpodEventThread;
	unsigned long m_ntrackIndex;//歌曲索引
	unsigned long m_ntrackLength;//歌曲长度
	unsigned long m_ntrackPosition;//歌曲位置
	ipodctlPLAYSTATUS m_nPlayStatus;//播放状态
	ipodctlPLAYSTATUS m_nPreplayStatus;//
	WCHAR *m_ptrackTitle;//歌曲名称
	WCHAR* m_partistName;//艺术家
	WCHAR* m_palbumName;//专辑名字
	unsigned char* m_pArtistPic;
	unsigned char* m_pArtistPicPre;
	unsigned long  m_ntrackNum;//shuffle off 歌曲总数
	unsigned long  m_nAlbumTotalNum;//album 歌曲总数
	unsigned long  m_ntrackTotalNum;//Track 歌曲总数
	unsigned long  m_nOffListNum;
	unsigned long  m_nTrackListNum;
	unsigned long m_nAlbumListNum;
	unsigned long  m_nPretrackNum;
	unsigned long  m_nTotalNum;
	HINT m_iPicState;
	HINT m_iPicDirection;//0 向左  1 向右
	HINT m_nDowningTime;
	CTimer m_ctPic;
	CTimer m_ctLoadData;
	CTimer m_ctGetArtistPic;
	CRITICAL_SECTION m_csThread;
	ipodctlSHUFFLE  m_shuffleStatus;//循环状态
	ipodctlREPEAT  m_repeatStatus;//重复状态
	bool m_bConnected;//是否连接
	bool m_bRun;
	bool m_bFFREW;
	bool m_bIpodListShow;
	bool m_bUpdateThread;
	bool m_bShuffleChange;
	ipodctlERR m_IpodPreERR;
	int m_nTimes;
	HANDLE  m_hUpdataThread;
	int m_nFailed;
	HANDLE m_hIpodInsert;
	HANDLE m_hIpodReady;
	bool m_bIpodReady;
	bool m_bInsert;
	static int s_nInint;
	static int s_nSucess;
	bool m_bListThreadRun;
	HANDLE  m_hGetSongInfoThread;
	CTimer m_ctButton;
	bool m_bButtonPress;
	sSongInfo *m_pSongInfo;
	static int s_nnCount;
	//bool m_bContiue;
	//bool m_bInsert;
};
