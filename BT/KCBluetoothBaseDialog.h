#pragma once

#include "Type.h"
#include "kdialogbase.h"
#include "define.h"
#include "KCListItem.h"
//#include"KCBTDialogManager.h"
#include "KCBTCommand.h"
#include "btsource.h"
//btSource* g_pBtcourse =  btSource::Instance();
//static IReSurface * g_pBTBK = NULL;
//g_pBTBK = GetRESingleton()->CreateSurfaceFromFile(strTmp)
class HCBluetoothBaseDlg : public KDialogP/*HDialogBase*/
{
	
public:
	HCBluetoothBaseDlg(void);
	virtual ~HCBluetoothBaseDlg(void);
	virtual HINT OnInit();
	void SetPreHFPState(HUINT nState);
	HUINT GetPreHFPState(void );
	virtual void ChangeTheme(HBYTE uType);
	//virtual IReSurface* ChangeTheme(HBYTE uType);// 主题切换
	virtual void SetDlgBkGnd();
	virtual void SetBTDlgBackGround();
	virtual void ChangeLangue(HINT nType);
	virtual void RequreSource();
	virtual void ReleaseSource();
	void SetBTABBK();
	void SetBTCRBK();
	void SetBTCSBK();
	void SetBTDLBK();
	void SetBTMSCBK();
	//void ShowByinterfacetype(eDIALOGTYPE  type);
	static  void OnBTDial(void *pDlg,void *);
	void OnBTDial(void *pa);
    static  void OnAddressBook(void *pDlg,void *);
	void OnAddressBook(void *pDlg);
	static  void OnCallRecords(void *pDlg,void *);
	void OnCallRecords(void *pDlg);
	static  void OnBTMusic(void *pDlg,void *);
	void OnBTMusic(void *pDlg);
	void PlayMusicEx();
	void SendPP();
	static  void OnConnectionSetting(void *pDlg,void *);
	void OnConnectionSetting(void *pDlg);
	void SetBTMode(eBTMODE eMode);
	 static bool SetBTConected(bool bConnect);
	 static bool GetBTConnectstate(void);
	 void UpdataBTBottomState(HINT nState);
	 void UpdataBTBottomState(void);
	 virtual void OnBtnHome(void* pParam); 
	 virtual void OnBtnBackPrevious(void* pParam); 
	  bool IsDailing();
	  void SetDailingState(bool bDail);
	  void ConnectA2DP(int nConnect);
	  void StopMusicEx();
protected:
	 	HCHAR (*s_pLan)[50];
		void SetLangue(HINT nType);
		bool m_bSourceRealse;
		static bool s_bDailing;
private:	
	//底部栏
	HCGroupCtrl		*m_pGrpCtrlBluetoothBottom;
	HCImageCtrl  *m_pTxtBottomBk;
	HCButton        *m_pBtnBluetooth;
	HCButton        *m_pBtnAdressBook;
	HCButton        *m_pBtnBTDialCallRecords;
	HCButton        *m_pBtnBTMusic;
	HCButton        *m_pBtnConnectionSetup;	
	//数据相关
	HINT nCurrentLangue;//0 中文 1 英文
	static HUINT s_nPreHFPState;
	eBTMODE m_eBTMode;
	static bool s_bConnected;
};