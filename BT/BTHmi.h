#pragma once
#include "Type.h"
#include "kdialogbase.h"
#include "define.h"
#include "KCBTCommand.h"
#include "btsource.h"
#include "winioctl.h "
class CBTHmiDlg: public HDialogBase
{
	public:
		CBTHmiDlg( );
		virtual ~CBTHmiDlg( );
		virtual HINT OnInit();
		//virtual int DoMessage(HMessage *msg);
		virtual void ChangeLanguage(HINT nType);
		virtual void ShowHMIVidio();
		virtual void CloseHMIVidio();
		virtual void OpenHMI();
		virtual void CloseHMI();
		virtual void RequreSource();
		virtual void ReleaseSource();
		void SetDisplayMute(HANDLE hDeviceFile, SCA_DEST_TYPE eDestType, BOOL bMuteOn);
		void DisConnectAutoDetct(HANDLE hDeviceFile, SCA_DEST_TYPE enCurDest);
		virtual HBOOL DoMessage(HMessage* msg);
		virtual void Draw(IReSurface* pSurface);
		void SetSPPConnected(bool bConnected);
		void SetHIDConnected(bool bConnected);
		void SendPhonePosition(int x,int y,char cType);
		bool SendCEPositionToPhone(int x,int y,KMESSAGETYPE eType);
		static void BackToZero(void* pDlg, void* param);
		void BackToZero(void* pDlg);
		static void StateMange(void* pDlg, void* param);
		void StateMange(void* pDlg);
		static void OnCheckForReady(void* pDlg, void* param);
		void OnCheckForReady(void* pDlg);
		bool SetBackToZeroTime(int nTime);
		void StartBackToZeroTimer();
		sPostion GetAvailableArea(int Cex,int Cey,int Phonex,int Phoney);
		void OpenCheckHandle();
		void CloseCheckHandle();
		static void OnBTNoticeShow(void * pThis,void * pParam);
		void OnBTNoticeShow(void * pParam);
	private:
		HANDLE m_hAVD ;
		HCTextCtrl *m_pTxtBk;
		HCButton *m_pBtnBtConnect;
		int  m_nBackToZero;//设定回归零点时间 10ms 为单位
		sPostion m_PosCurrentCePostion;
		HINT m_nHMIState;//0无信号，1有信号 其他未知状态
	//	CTimer m_ctStateManage;
		//CTimer m_ctSingel;
		CTimer m_ctNotice;
		HINT m_nCout;
		HINSTANCE m_hDll;
		HANDLE m_HandleCheck;
		HANDLE m_HandelTemp;
		bool m_bBTNoticeShow;
		bool m_bBTConneted;
		bool m_bPhoneReady;
		bool m_bBTSPPConnected;
		bool m_bBTHIDConnected;
		bool m_pIsCarBack;
		bool m_bPositionInZero;
		bool m_bHMIShow;
		bool m_bSourceRealse;

		//CTimer m_ctTimeToBackToZero;
	
		pGetCameraSignalStatus m_pGetCameraSignalStatus;
		pInitCameraPreview m_pInitCameraPreview;
		pRequestCameraPreviewRsc m_pRequestCameraPreviewRsc;
		pSetCameraPreviewChannel m_pSetCameraPreviewChannel;
		pInitLayeredWindow m_pInitLayeredWindow;
		pRequestLayeredWindowRsc m_pRequestLayeredWindowRsc;
		pGetLayeredWindowPhyFreBuffer m_pGetLayeredWindowPhyFreBuffer;
		pSetLayeredWindowPosition m_pSetLayeredWindowPosition;
		pSetLayeredWindowAlpha m_pSetLayeredWindowAlpha;
		pSetLayeredWindowColorKey m_pSetLayeredWindowColorKey;
		pOpenLayeredWindow m_pOpenLayeredWindow;
		pUnInitCameraPreview m_pUnInitCameraPreview;
		pReleaseCameraPreviewRsc m_pReleaseCameraPreviewRsc;
		pStopCameraPreview m_pStopCameraPreview;
};