#pragma once
#include "KCBluetoothBaseDialog.h"

class HCBTMusicDlg : public HCBluetoothBaseDlg
{	
public:
	HCBTMusicDlg();
	virtual~HCBTMusicDlg();
	HINT OnInit();
	virtual void ChangeLangue(HINT nType);
	virtual HBOOL DoMessage(HMessage* msg);
	virtual void RequreSource();
	virtual void ReleaseSource();
	void SetBTDlgBackGround();
	static void OnPlayPause(void* pDlg, void* param);
	void OnPlayPause(void* pDlg);
	static void OnPlayMute(void* pDlg, void* param);
	void OnPlayMute(void* pDlg);
	static void OnForward(void* pDlg, void* param);
	void OnForward(void* pDlg);
	static void OnBack(void* pDlg, void* param);
	void OnBack(void* pDlg);
	HINT UpDataMediaInfo(void);
	HINT UpDataPlayState(eBTMUSICRUNNINGSTATUS ePlayState);
	void ClearMusicInfo();
	void StopMusic();
	void PlayMusic();
	void UpdateVision();
	void UpdateBtName();
	void MusicMute(bool bMute);
	void MusicMuteEx(bool bMute);
#if TestBTVISION
	static void OnGetBtVision(void* pDlg, void* param);
	void OnGetBtVision(void* pDlg);
#endif
private:
	HCGroupCtrl		*m_pGrpCtrlBTMusicMiddle;
	HCImageCtrl      *m_pTxtBTMusicBK;
	//HCTextCtrl      *m_pTxtBTMusicCover;
	HCTextCtrl      *m_pTxtBTMusicSong;
	HCTextCtrl      *m_pTxtBTMusicSinger;
	HCTextCtrl      *m_pTxtBTMusicAlbum;
	HCTextCtrl      *m_pTxtA2DPState;
	HCTextCtrl      *m_pTxtMusicSong;
	HCTextCtrl      *m_pTxtMusicSinger;
	HCTextCtrl      *m_pTxtMusicAlbum;
#if  BTMUSIC_NUMBER_STATE
	HCTextCtrl *m_pTxtCurrentPlayNumber;
#endif
#if TestBTVISION
    HCButton *m_pBtnVision;
#endif
	HCButton	    *m_pBtnBTMusicUp;
	HCButton	    *m_pBtnBTMusicDown;
	HCButton        *m_pTxtBTMusicPlayPause;
	HCImageCtrl      *m_pTxtBTMusicHandleBK;
	eBTMUSICRUNNINGSTATUS m_eBTMusicStatus;
    bool m_bPlaySend;
	bool m_bPauseSend;
};
