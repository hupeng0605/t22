#pragma once
//#include "define.h"
#include "KCBluetoothBaseDialog.h"
#define BTVERSION 0
class HCBTConnectionssettingDlg : public HCBluetoothBaseDlg
{
	public:
		HCBTConnectionssettingDlg(void);
		virtual~HCBTConnectionssettingDlg(void);
		HINT OnInit();
		virtual void ChangeLangue(HINT nType);
		void SetBTDlgBackGround();
		void AddPairedDevice();

		void StartCloseBT();
		void StopDeadTimer();
		static void CloseBt(void* pDlg, void* param);
		void CloseBt(void* pDlg);
		static void OnScrBoxPariedDevices(void* pDlg, void* param);
		void OnScrBoxPariedDevices(void* pDlg);
		static void OnDisconnect(void* pDlg, void* param);
		void OnDisconnect(void* pDlg);
		static void OnDelete(void* pDlg, void* param);
		void OnDelete(void* pDlg);
		static void OnDeleteAll(void* pDlg, void* param);
		void OnDeleteAll(void* pDlg);
		static void OnEnterPairPage(void* pDlg, void* param);
		void OnEnterPairPage(void* pDlg);
		void ClearDeviceRecord();
		//void ClearAllRecords();
#if TESTRESTARTPROTEM
		static void OnUpdataRestTime(void* pDlg, void* param);
		void OnUpdataRestTime(void* pDlg);
		static void OnClearRestTime(void* pDlg, void* param);
		void OnClearRestTime(void* pDlg);
		void UpdataRestTime(int t);
#endif
		static void OnEnterPairMode(void* pDlg, void* param);
		void OnEnterPairMode(void* pDlg);
		static void OnSelectDeviceChange(void* pDlg, void* param,void* iparam);
		void OnSelectDeviceChange(void* pDlg,void *param);
		static void OnDeadTime(void* pDlg, void* param);
		void OnDeadTime(void* pDlg);
		static void OnConfirm(void* pDlg, void* param);
		void OnConfirm(void* pDlg);
		static void OnCannel(void* pDlg, void* param);
		void OnCannel(void* pDlg);
		static void OnOpenBT(void* pDlg, void* param);
		void OnOpenBT(void* pDlg);
		void SetPairDeviceTxt(HCListItemBase* pItem,HBYTE* pTxt);
		void SetPairDeviceTxt(HCListItemBase* pItem,sDeviceINFO* pDeviceINFO);
        void  UpDataIconUnconnect(void);
		HCListItem* CreatPairDeviceItem(HBYTE *pTxt);
		HCListItem* CreatPairDeviceItem(sDeviceINFO* pDeviceINFO);
		void SetNoticeTxt(HINT nParam);
		void SetNoticeShow(HINT nParam);
		void SetNoticeSuccess();
		void SetNoticeShowHide();
		void UpdataByHFPState(HINT nState);
		bool IsPairPageShow();
		void OnPairDeviceClick(HINT iSelected);
		virtual void RequreSource();
		virtual void ReleaseSource();
#if SETBTNAME_MAC
		void UpdateDevName();
#endif
#if BTLOGSTATE
		static  void OnCopyBTLogFile(void *pDlg,void *);
		void OnCopyBTLogFile(void *pa);
#endif
	private:
		HCGroupCtrl		*m_pGrpCtrlConnectionSettingMiddle;
		HCImageCtrl      *m_pTxtConnectionSettingBK;
		HCScrollCtrl    *m_pScrCtrlConnectionSetting;
		HCScrollBox     *m_pScrBoxPariedDevices;
		HCButton	    *m_pBtnPariedDevicesUp;
		HCButton	    *m_pBtnPariedDevicesDown;
		HCImageCtrl      *m_pTxtConnectionSettingHandleBK;
		HCButton		*m_pBtnDeviceUnconnect;
		HCButton		*m_pBtnDeviceDelete;
		HCButton		*m_pBtnDeviceDeleteAll;
		HCButton     *m_pBtnPhonePair;
		//HCButton     *m_pBtnBTOpen;
		//HCGroupCtrl *m_pGrpCtrlNotice;
	//	HCTextCtrl	*m_pTxtNoticeBK;
	//	HCTextCtrl   *m_pTxtNotice;
	//	HCTextCtrl   *m_pTxtLocalDeviceName;
	//	HCTextCtrl *m_pTxtPairCode;
	//	HCTextCtrl *m_pTxtPairResult;
		HCGroupCtrl *m_pGrpBTPair;
		HCTextCtrl* m_pTxtPairNotice;
		HCTextCtrl* m_pTxtPairDeviceName;
		HCTextCtrl* m_pTxtPairDeviceCode;
		HCButton* m_pBtnPair;
		HCTextCtrl *m_pTxtDeviceLine1;
		HCTextCtrl *m_pTxtDeviceLine2;
		HCTextCtrl *m_pTxtDeviceLine3;
		HCTextCtrl *m_pTxtDeviceLine4;
		//删除列表提示
		HCGroupCtrl *m_pGrpUnconnectNotice;
		HCTextCtrl *m_pImgUnconnectNoticeBK;
		HCImageCtrl *m_pImgUnconnectNoticeFrame;
		HCButton *m_pBtnConfirm;
		HCButton *m_pBtnCannel;
		HCTextCtrl *m_pTxtUnconnectNotice;
#if TESTRESTARTPROTEM
		HCButton *m_pBtnRestTime;
#endif
#if BTVERSION
		HCTextCtrl *m_pTxtBTVersion;
#else
#endif
#if BTLOGSTATE
		HCButton *m_pBtnCopyFile;
#endif
		//数据相关
		HINT m_iSelectedButton;
		HINT m_nDeadTime;
		HINT  m_iSelectConnectDevice;//被选中的设备项
		HUINT  m_nTotalPairedNum;//已匹配过的设备总数
		HUINT m_nMode;//0, 正常状态，1，匹配状态
		CTimer m_ctBTClose;//蓝牙关闭计时器
		CTimer m_ctDeadTime;//蓝牙进入匹配状态倒计时
		bool m_bConnected;//选中项是否已连接
		bool m_bPairNoticeShow;
		bool m_nPairSend;
		//HCClockCtrlEx *m_pClkDeadTime;
	//	PairDevice  *m_pPairDevice;
};