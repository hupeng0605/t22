#pragma once
#include "Type.h"
#include "KDialogBase.h"
#include "KCListItem.h"
#include "KCScrollCtrl.h"
#include "stdafx.h"
#include "RadioSource.h"
#include "DialogP.h"
#include "utility_public.h"
class HCRadioDlg : public KDialogP
{
public:
	virtual ~HCRadioDlg(void);
	static HCRadioDlg* Instance();
	static void DeleteInstance();
	virtual HINT OnInit();
	virtual void SetDlgBkGnd();
	virtual void UpDataRadioSource();
	virtual void SaveRadioLastMem();
	virtual void ReadRadioLastMem();
	virtual void UpDataCurrentValue();
	virtual HBOOL DoMessage(HMessage* msg);
	virtual void ChangeTheme(HBYTE uType);// 主题切换
	static void OnBtnDown(void *p, void *pParam);
	void OnBtnDown(void* pParam);
	static void OnAMFM(void *pDlg,HINT nPos);
	void 	OnAMFM(HINT nPos);
	static void OnAMFMUp(void *pDlg,void* pParam);
	void 	OnAMFMUp(void* pParam);
	static void OnScan(void* pDlg, void* param);
	void OnScan(void* pDlg);
	//static void OnAM(void* pDlg, void* param);
	void RadioSendData(__in unsigned char uID,__in LPIPCEVENT lpIPCEvent);
	void OnAM(void);
	//static void OnFM(void* pDlg, void* param);
	void OnFM(void);
	static void OnRadioMouseMove(void* pDlg, void* param);
	void OnRadioMouseMove(void* pDlg);
	static void OnRadioMouseDown(void* pDlg, void* param);
	void OnRadioMouseDown(void* pDlg);
	static void OnRadioMouseUp(void* pDlg, void* param);
	void OnRadioMouseUp(void* pDlg);
	static void OnPreSearch(void* pDlg, void* param);
	void OnPreSearch(void* pDlg);
	static void OnNextSearch(void* pDlg, void* param);
	void OnNextSearch(void* pDlg);
    void ChannelStoreAddChannel(void);
	//void ChannelListsAddChannel(void);
	static void OnChannelAutoSearch(void* pDlg, void* param);
	void OnChannelAutoSearch(void* pDlg);
	static void OnRadioUp(void* pDlg, void* param);
	void  OnRadioUp(void* pDlg);
	static void OnRadioDown(void* pDlg, void* param);
	void OnRadioDown(void* pDlg);
	static void OnConfirm(void* pDlg, void* param);
	void OnConfirm(void* pDlg);
	static void OnCannel(void* pDlg, void* param);
	void OnCannel(void* pDlg);
	//void SetChannelListsShow(bool bShow);
	static void OnScrboxChannelStore(void* pDlg,void* param);
	void OnScrboxChannelStore(void* pDlg);
	static void OnScrboxChannelStoreLong(void* pDlg,void* param);
	void OnScrboxChannelStoreLong(void* pDlg);
	static void OnScrboxChannelLists(void* pDlg,void* param);
	void OnScrboxChannelLists(void* pDlg);
	eRADIOCOMMANDTYPE ParseRadioCommandType(HBYTE *cCommand);
	HINT HandRadioData(HBYTE *cCommand,HUINT nLen);
	void  HandelEnterRadioInterface(HBYTE *cCommand,HUINT nLen);
	void  HandelRadioChannelChange(HBYTE *cCommand,HUINT nLen);
	void HandelRadioAMFMChange(HBYTE *cCommand,HUINT nLen);
	void HandelRadioChannelSearch(HBYTE *cCommand,HUINT nLen);
	void HandelRadioOn(HBYTE *cCommand,HUINT nLen);
	void HandelRadioChannelStore(HBYTE *cCommand,HUINT nLen);
	void HandelRadioAdjust(HBYTE *cCommand,HUINT nLen);
	void HandelRadioAutoSearch(HBYTE *cCommand,HUINT nLen);
	void HandelRadioScan(HBYTE *cCommand,HUINT nLen);
	void HandelRadioChannelLists(HBYTE *cCommand,HUINT nLen);
	void HandelRadioChannelAdjust(HBYTE *cCommand,HUINT nLen);
	void HandelRadioStopAutoSearch(HBYTE *cCommand,HUINT nLen);
	void HandelChannelSearchingFB(HBYTE *cCommand,HUINT nLen);
	void HandelSTStateFB(HBYTE *cCommand,HUINT nLen);
	void HandelAMFMStateFB(HBYTE *cCommand,HUINT nLen);
	void HandelChannelStoreFB(HBYTE *cCommand,HUINT nLen);
	void HandelChannelChangeStateFB(HBYTE *cCommand,HUINT nLen);
	eRADIOFEEDBACKSTATE ParseRadioFeedBackStateType(HBYTE *cCommand);
	HUINT *GetCurrentRadioValueAddress();
	void UpdataRadioWindow();
	void StoreChannel();
	void UpDataRadioLisitem(eRadioType_t eRadioType);
	void UpDataLisitem(HCScrollBox *pScrllBox,HUINT *pArr,eRadioType_t eRadioType);
	void UpData(void);
	void UpDataSelectRadioListem();
	void UpDataRadioCtrlMessage(bool bAble);
	HUINT IsStored(HUINT *pChannel,HUINT uChannelValue);
	void PostMessageToWin(HUINT msg,HINT nparam);
	virtual void SendRadioCommand(eRADIOCOMMANDTYPE eType,HINT iData);
	void SetMyhWnd(HWND hhand);
	void ChangeLangue(HINT nType);
	void SetTxtValue(HCTextCtrl *pTxt,HINT nValue);
	static void OnStartSearch(void* pDlg, void* param);
	void OnStartSearch(void* pDlg);
	static void OnAMFMMoveEnd(void *pDlg,HINT nPos);
	HINT AdjustValue(HINT nValue);
	HINT AdjustValue(HINT nVaue,eRadioType_t eType,HINT nCurrentArea);
	void GetCurrentArea();
    void JumpToCurrentValueIndex(int nSelectChannel);
	//void 	OnAMFMMoveEnd(HINT nPos);
	//virtual void SendRadioCommand(eRADIOCOMMANDTYPE eType,HINT iData);
private:
	void SetLangue(HINT nType);//0中文1英文
	HCRadioDlg(void);
	//底部栏
	static  HCRadioDlg*  s_pRadioDlg;
	HCHAR (*s_pLan)[50];
	HCGroupCtrl		*m_pGrpCtrlRadioBottom;
	HCImageCtrl      *m_pTxtBootmBK;
	HCButton        *m_pBtnPrevious;
	HCButton        *m_pBtnNext;
	HCButton	    *m_pBtnScan;
	HCButton	    *m_pBtnChannelAutoSearch;
    //中部栏
	HCGroupCtrl		*m_pGrpCtrlRadioMiddle;
	//中部左侧
	HCTextCtrl      *m_pTxtChannelStoreBK;
	HCScrollCtrl    *m_pScrctrlChannelStore;
	HCScrollBox     *m_pScrboxChannelStore;
	HCButton	    *m_pBtnChannelStoreUp;
	HCButton	    *m_pBtnChannelStoreDown;
	//中部右侧
	HCButton	    *m_pBtnTopScale;
	HCButton	    *m_pBtnBottomScale;
	HCTextCtrl      *m_pTxtRadioCurrentValue;
	HCTextCtrl      *m_pTxtRadioType;
	HCTextCtrl      *m_pTxtRadioUnit;
	HCSlideCtrl     *m_pSliderChannelScan;
	HCSwitchButton *m_pSwBtAMFM;
	HCImageCtrl      *m_pTxtAMFMBK;
	HCTextCtrl  *m_pTxtSTstate;
	HCTextCtrl  *m_pTxtRadioMessage;
	//当前频率值
	HCGroupCtrl *m_pGrpCurrentFM;
	HCTextCtrl *m_pTxtFM0;
	HCTextCtrl *m_pTxtFM1;
	HCTextCtrl *m_pTxtFM2;
	HCTextCtrl *m_pTxtFM3;
	HCTextCtrl *m_pTxtFM4;
	HCTextCtrl *m_pTxtDot;
	HCGroupCtrl *m_pGrpCurrentAM;
	HCTextCtrl *m_pTxtAM0;
	HCTextCtrl *m_pTxtAM1;
	HCTextCtrl *m_pTxtAM2;
	HCTextCtrl *m_pTxtAM3;
	//   有无有效台
	HCTextCtrl *m_pTxtAvailableChannel;
	//提示框
	//HCGroupCtrl		*m_pGrpNotice;
	//HCButton *m_pBtnCannel;
	//HCButton *m_pBtnConfirm;
	//HCTextCtrl *m_pTxtNotice1;
//	HCTextCtrl *m_pTxtNotice2;
	//数据相关
	HUINT *m_pFMStoredChannnel;
	HUINT *m_pAMStoredChannnel;
	HUINT m_nCurrentFMValue;
	HUINT m_nCurrentAMValue;
	HUINT m_nPreFMValue;
	HUINT m_nPreAMValue;
	DWORD m_dwNowTime;
	HINT m_iScrboxChannelStore;
	HWND m_hWnd;
	HINT m_nCurrentLange;
	HINT m_nCurrentArea;
	CTimer m_ctRefrench;
	HCHAR  m_cRadioCurrentFMValue[7];
	HCHAR  m_cRadioCurrentAMValue[7];
	bool m_bNoticeShow;
	bool  m_bAutoSearch;
	eRadioType_t     m_eRadioType;
	bool m_bST;
	bool  m_bshow;
	eRADIOWORKSTATE m_eRadioWorkState; 
	//CTimer ctNoState;	
};