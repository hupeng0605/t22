#pragma once

#include "KCBluetoothBaseDialog.h"
class HCBTAddressBookDlg : public HCBluetoothBaseDlg
{	
public:
	HCBTAddressBookDlg();
	virtual ~HCBTAddressBookDlg();
	HINT OnInit();
	virtual HBOOL DoMessage(HMessage* msg);
	void SetBTDlgBackGround();
	void virtual  ChangeLangue(HINT nType);
	static void OnCall(void* pDlg, void* param);
	void OnCall(void* pDlg);
	static void OnAddressBookScrollEnd(void* pDlg, HBOOL bScrollUp);
	void OnAddressBookScrollEnd(HBOOL bScrollUp);
	static void OnNextPage(void* pDlg, void* param);
	void OnNextPage(void* pDlg);
	static void OnScrBoxAddressBook(void* pDlg, void* param);
	void OnScrBoxAddressBook(void* pDlg);
	void AddAddressBookItem(void);
	static void OnDownLoad(void* pDlg, void* param);
	void OnDownLoad(void* pDlg);
	static void OnDelete(void* pDlg, void* param);
	void OnDelete(void* pDlg);
	static void OnDeleteAll(void* pDlg, void* param);
	void OnDeleteAll(void* pDlg);
	static void OnDowingTimer(void* pDlg, void* param);
	void OnDowingTimer(void* pDlg);
	HCListItem* CreatContactItem(HCHAR *pName,HCHAR *pPhoneNumber);
	void SetNotice(ePBAPCSTATE eState);
	void SetNoticeShow(bool bShow);
	void DeleteAllItems();
	virtual void ClearBookData();
	void ClearBookDataEx();
	void RequreSource();
	void ReleaseSource();
	void StartDownBookData();
	void StartDown();
	void CancelByPhone();
	static void UpdataNameLetter(void* pDlg, void* param);
	void UpdataNameLetter(void* pDlg);
	HINT GetLetterIndex(HINT nPos);
	void UpDateDownLoad(HINT nState,HINT nNum);//nstate :0下载启动 1联系人 2:已接电话 3:已拨电话 4：未接电话 5全部记录 nNum:数目 
	//void ClearBookData();
	//static  void OnAddressBook(void *pDlg,void *);
	//void OnAddressBook(void *pDlg);
	//HCListItem* CreatCallHistoryItem(sCallHistory *pCallHistory);

private:
	HCGroupCtrl		*m_pGrpCtrlAddressBookMiddle;
	HCImageCtrl      *m_pTxtAddressBookBK;
	HCScrollCtrl    *m_pScrCtrlAddressBook;
	HCScrollBox     *m_pScrBoxAddressBook;
	HCButton	    *m_pBtnAddressBookUp;
	HCButton	    *m_pBtnAddressBookDown;
	HCTextCtrl      *m_pTxtAddressBookName;
	HCTextCtrl      *m_pTxtAddressBookHandleBK;
	HCButton		*m_pBtnAddressBookDial;
	HCButton		*m_pBtnAddressBookDownLoad;
	HCButton		*m_pBtnAddressBookDelete;
	HCButton		*m_pBtnAddressBookDeleteAll;
	HCGroupCtrl		*m_pGrpCtrlAddressBookNotice;
	HCTextCtrl    *m_pTxtDownLoading;
	HCTextCtrl *m_pTxtDownNum;
	//HCTextCtrl     *m_pTxtDownLoaded;
	HCTextCtrl *m_pTxtDeviceLine1;
	HCTextCtrl *m_pTxtDeviceLine2;
	HCTextCtrl *m_pTxtDeviceLine3;
	HCTextCtrl *m_pTxtDeviceLine4;
	HCTextCtrl      *m_pTxtNoticeBK;
	HINT m_iScrboxAddressBook;
	HUINT m_nTotalConcats;
	HINT m_nBeg;
	CTimer m_ctUpdataLetter;
	CTimer m_ctDowingTime;
	HUINT m_nDowningTime;
	int m_nContactDown;
	int m_nAllRecordsDown;
	bool m_bDowning;
	bool m_bCleared;
	//ePBAPCSTATE m_ePBAPCstate;
};