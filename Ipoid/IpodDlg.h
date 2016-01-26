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
	HCTextCtrl *m_pTxtSong;//��Ŀ
	HCTextCtrl *m_pTxtArtist;//������
	HCTextCtrl *m_pTxtAbum;//ר��
	HCImageCtrl *m_pTxtIpodBk;//����
	//HCTextCtrl *m_pTxtSongHead;//��Ŀ
	//HCTextCtrl *m_pTxtArtistHead;//������
	//HCTextCtrl *m_pTxtAbumHead;//ר��
	HCTextCtrl *m_pTxtCurrentIndex;//��ǰ�������
	HCTextCtrl *m_pTxtCurrentPlayTime;//��ǰ����ʱ��
	HCTextCtrl *m_pTxtTrackTotalTime;//��ǰ��Ŀ��ʱ��
	HCSlideCtrl *m_pSldPlayTime;//������
	//HCTextCtrl *m_pTxtBootmBK;//����
	HCTextCtrl *m_pTxtArtistPic;
	//�б�
	HCGroupCtrl      *m_pGrpIpodList;
	//HCScrollCtrl    *m_pScrctrlIpodList;
	HCScrollBox     *m_pScrboxIpodList;//SHUFFLE_OFF�б�			
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
//�������
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
	unsigned long m_ntrackIndex;//��������
	unsigned long m_ntrackLength;//��������
	unsigned long m_ntrackPosition;//����λ��
	ipodctlPLAYSTATUS m_nPlayStatus;//����״̬
	ipodctlPLAYSTATUS m_nPreplayStatus;//
	WCHAR *m_ptrackTitle;//��������
	WCHAR* m_partistName;//������
	WCHAR* m_palbumName;//ר������
	unsigned char* m_pArtistPic;
	unsigned char* m_pArtistPicPre;
	unsigned long  m_ntrackNum;//shuffle off ��������
	unsigned long  m_nAlbumTotalNum;//album ��������
	unsigned long  m_ntrackTotalNum;//Track ��������
	unsigned long  m_nOffListNum;
	unsigned long  m_nTrackListNum;
	unsigned long m_nAlbumListNum;
	unsigned long  m_nPretrackNum;
	unsigned long  m_nTotalNum;
	HINT m_iPicState;
	HINT m_iPicDirection;//0 ����  1 ����
	HINT m_nDowningTime;
	CTimer m_ctPic;
	CTimer m_ctLoadData;
	CTimer m_ctGetArtistPic;
	CRITICAL_SECTION m_csThread;
	ipodctlSHUFFLE  m_shuffleStatus;//ѭ��״̬
	ipodctlREPEAT  m_repeatStatus;//�ظ�״̬
	bool m_bConnected;//�Ƿ�����
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
