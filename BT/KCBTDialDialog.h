#pragma once
#include "KCBluetoothBaseDialog.h"
class HCBTDialDlg : public HCBluetoothBaseDlg
{	
public:
	HCBTDialDlg();
	virtual~HCBTDialDlg();
	HINT OnInit();
	void SetBTDlgBackGround();
	virtual void ChangeLangue(HINT nType);
	virtual void RequreSource();
	virtual void ReleaseSource();
	/*
	static  void OnBTDial(void *pDlg,void *);
	void OnBTDial(void *pa);
	*/
	static  void OnDialNum0(void *pDlg,void *Param);
	static  void OnDialNum0Long(void *pDlg,void *Param);
	static  void OnDialNum1(void *pDlg,void *Param);
	static  void OnDialNum2(void *pDlg,void *Param);
	static  void OnDialNum3(void *pDlg,void *Param);
	static  void OnDialNum4(void *pDlg,void *Param);
	static  void OnDialNum5(void *pDlg,void *Param);
	static  void OnDialNum6(void *pDlg,void *Param);
	static  void OnDialNum7(void *pDlg,void *Param);
	static  void OnDialNum8(void *pDlg,void *Param);
	static  void OnDialNum9(void *pDlg,void *Param);
	static  void OnDialNumStar(void *pDlg,void *Param);
	static  void OnDialNumWell(void *pDlg,void *Param);
	static  void OnDialNumDel(void *pDlg,void *Param);
	static  void OnDialNumCall(void *pDlg,void *Param);
	static  void OnDialNumHangUp(void *pDlg,void *Param);
	static  void OnDialNumCancel(void *pDlg,void *Param);
	void OnDialNum(void *pDlg,LPARAM_KEYCODE eKey);
	void UpDataKeyBoard(HUINT uHFPState);
	void ClearKeyBoardNum();
	void UpDataKeyBoardNum();
	void UpDataKeyBoardNum(sContact *pContact);
	void StartCountCallDuration();
	void StopCountCallDuration();
	void UpdataTextShow(HINT nState);
	static void OnCountCallDuration(void* pDlg, void* param);
	void OnCountCallDuration(void* pDlg);
	static void OnAutoAnswer(void* pDlg, void* param);
	void OnAutoAnswer(void* pDlg);
	virtual void ClearDailData();
	void ChangeVoicePoisition(HINT nPosition);
	void SetVoiceToPhone();
	static void OnEnableCall(void* pDlg, void* param);
	void OnEnableCall(void* pDlg);
	static void OnReboot(void* pDlg, void* param);
	void OnReboot(void* pDlg);
	void StopCallTimer();
	void StartCallTimer();
	void StartHangUpTimer();
	void StopHangUpTimer();
#if TESTDAILPROBLEM
	void UpdataTestHFP();
#else
#endif
private:
	HCGroupCtrl		*m_pGrpCtrlBTDial;
	HCImageCtrl      *m_pTxtBTDialMiddleBK;
	HCTextCtrl      *m_pTxtDialNumber;
	//HCTextCtrl      *m_pTxtCallState;
	HCTextCtrl      *m_pTxtCallTime;
	HCTextCtrl       *m_pTxtCotactName;
	HCButton        *m_pBtnDial0;
	HCButton        *m_pBtnDial1;
	HCButton        *m_pBtnDial2;
	HCButton        *m_pBtnDial3;
	HCButton        *m_pBtnDial4;
	HCButton        *m_pBtnDial5;
	HCButton        *m_pBtnDial6;
	HCButton        *m_pBtnDial7;
	HCButton        *m_pBtnDial8;
	HCButton        *m_pBtnDial9;
	HCButton        *m_pBtnDialWell;
	HCButton        *m_pBtnDialStar;
	HCButton        *m_pBtnBTDialDelete;
	HCButton        *m_pBtnBTDialCall;
	HCButton        *m_pBtnBTDialHangUp;
	HCButton        *m_pBtnBTDialCancel;
#if TESTDAILPROBLEM
	HCTextCtrl      *m_pTxtHFPstate;
	HCTextCtrl  *m_pTxtA2DPstate;
#else
#endif
	Dialpad_t		m_sDialNum;
	HUINT m_nCallDuration;
	CTimer m_ctCallDuration;
	CTimer m_ctAutoAnswer;
	CTimer m_ctCall;
	CTimer m_ctHangUp;
	HINT m_nVoicePos;//0手机，1车机 其他 未知
	bool m_bCleared;
	//eDIALOGTYPE  m_ePreDlgType;
};
