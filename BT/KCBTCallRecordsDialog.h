#pragma once

#include "KCBluetoothBaseDialog.h"
class HCBTCallRecordsDlg : public HCBluetoothBaseDlg
{	
public:
	HCBTCallRecordsDlg();
	virtual~HCBTCallRecordsDlg();
	HINT OnInit();
	virtual void ChangeLangue(HINT nType);
	void SetBTDlgBackGround();
	HCListItem* CreatCallHistoryItem(sCallHistory *pCallHistory);
	static void OnCall(void* pDlg, void* param);
	void OnCall(void* pDlg);
	static void OnScrBoxCallRecords(void* pDlg, void* param);
	void OnScrBoxCallRecords(void* pDlg);
	void AddCallRecordsItem(void);
	static void OnAllRecords(void* pDlg, void* param);
	void OnAllRecords(void* pDlg);
	static void OnMissedCall(void* pDlg, void* param);
	void OnMissedCall(void* pDlg);
	static void OnDelete(void* pDlg, void* param);
	void OnDelete(void* pDlg);
	static void OnDeleteAll(void* pDlg, void* param);
	void OnDeleteAll(void* pDlg);
	void UpDataRecords(bool bDowned);
	void DeleteAllItems();
	virtual void ClearRecordsData();
	void AutoUpDataRecords();
	virtual void RequreSource();
	virtual void ReleaseSource();
private:
	HCGroupCtrl		*m_pGrpCtrlCallRecordsMiddle;
	HCImageCtrl      *m_pTxtCallRecordsBK;
	HCScrollCtrl    *m_pScrCtrlCallRecords;
	HCScrollBox     *m_pScrBoxCallRecords;
	HCButton	    *m_pBtnCallRecordsUp;
	HCButton	    *m_pBtnCallRecordsDown;
	HCImageCtrl      *m_pTxtCallRecordsHandleBK;
	HCButton		*m_pBtnCallRecordsDial;
	HCButton		*m_pBtnCallRecordsAllRecords;
	HCButton		*m_pBtnCallRecordsMissedCalls;
	HCButton        *m_pBtnCallRecordsDelete;
	HCButton		*m_pBtnCallRecordsDeleteAll;
	eCALLHISTORY        m_eCallHistory;
	HINT      m_iScrboxCallRecords;
	HCTextCtrl *m_pTxtDeviceLine1;
	HCTextCtrl *m_pTxtDeviceLine2;
	HCTextCtrl *m_pTxtDeviceLine3;
	HCTextCtrl *m_pTxtDeviceLine4;
	//HINT m_nRecordsType;
    bool m_bRecordsCleared;
};