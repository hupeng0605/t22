/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCHeadDialog.h
* ժ    Ҫ: Clarion BaseDialog
*
* ��ǰ�汾: 1.0
* ��    ��:               
* �������: 2010-02-03
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1           2010-02-03                              ����
*	2			2010-4-26		  			�Ż��������
*	3			2010-5-26		  			��ӵ���ת��ť
*
**/
#pragma once
#include "hmienginecom.h"
#include <PubHead.h>
#include "kdialogbase.h"
#include "kcwindow.h"
#include "KCGroupCtrl.h"
#include "KCScrollButtonText.h"
#include "KCClockCtrl.h"

#pragma warning(disable: 4512)

// �ݶ�Ϊ1��������Ҫ���INFO ICONֻ���޸Ĵ˺�
#ifdef MAX_INFO_ICON_NUM
#undef MAX_INFO_ICON_NUM
#endif
#define MAX_INFO_ICON_NUM (2)

class CYPRESS_DLL_API HCHeadDialog :
    public HDialogBase
{
public:
    HCHeadDialog(void);
    virtual ~HCHeadDialog(void);
    //
public:


	void EnableSetTitleByString(HBOOL bIn);
	void ResetTitle();
	HBOOL IsTitleEmpty();
	//�ж���û������TITLE
	HBOOL IsResetTitle();
	//��ԭTITLE
	void RevertTitle();
    // ���õ�ǰ������
	void SetHeadIocnHide(HBOOL bShowFlag);
    void SetTitleName(const HString& strTitleName,HBOOL bEnableMoveInOut = TRUE);
	void SetTitleID(HINT nID);
	void SetTime(const HString& strTime,HBOOL bEnableMoveInOut = TRUE);
	void SetTitleNameColor(int r, int g , int b);
    // ���ñ��������ַ�
    void SetTitleByString(const HCHAR* a_pstrTitle,HBOOL bEnableMoveInOut = TRUE);
	void SetTimeByString(const HCHAR* a_pstrTime,HBOOL bEnableMoveInOut = TRUE);
    void SetTitleByLangID(HINT a_nLangID,HBOOL bEnableMoveInOut = TRUE);
	void SetTimeByLangID(HINT a_nLangID,HBOOL bEnableMoveInOut = TRUE);
	HString GetTitleName();
	
	void SetShowAMPMEvent();

    // ����ʱ���ʽ
	void SetTimeFormat(HBOOL bFormat);
	void SetHeadBkPos(HINT x,HINT y);

	// Disc��Ϣ�����仯�¼�
	virtual void OnDiscUpdateEvent(HINT /*cmdID*/, LPARAM /*lParam*/){}
    //  // ��Ϣicon��
    //  kn_int SetInfoIconVisibility(kn_int a_nIndex,kn_bool a_bShow = true);
    //  kn_int SetAllInfoIconVisibility(kn_bool a_bShow = true);
    //  kn_int SetInfoIconActivity(kn_int a_nIndex,kn_bool a_bActive = true);
    //  kn_int SetAllInfoIconActivity(kn_bool a_bActive = true);


    void StartExe(HString strExeName, HString strParam = _T(""));
    void StartExe(HINT nExeType, HCHAR* pstrParam = NULL);
    void StartExe(HINT nExeType, HINT nParam = 0);

	// ����HEAD����
	void SetHeadBK(const HString& pFileName);
	void SetHeadBK(IReSurface* pSurf);
	HBOOL GetTimeFormat();
    HCBaseCtrl* GetHeadCtrl();
	HCImageCtrl* GetHeadImageCtrl();
	HBOOL SaveSurfaceToMemery(IN const HString& strSourceName,
		IN HINT nWidth = 240,IN HINT nHeight = 144);
	void SetMemeryString(const HString& strMemString);

// 	void VideoBitmapToSurface(HBITMAP& bitmap, IReSurface*& pSurf);
// 	void ReadVideoBmp(IN const kn_string& strSourceName);

	void  SetThumbNailBySendMsg(IN const HString& strSourceName);

	void Draw(IReSurface* pSurface);
	// ����Radio��״̬
	void SetRadioIconState(HINT index,HBOOL nState);
	// ��������״̬
	void SetBTIconStatus(HINT nStatus);
	// ����mute״̬
	void SetMuteIconStatus(HBOOL bStatus);

	// ��Ƶ�����Ƿ���ڽӿ�
	void SetVideoWndShow(HBOOL bShow = false);
	HBOOL	GetVideoWndShow(void);

	// ��ʾ���ص�����ť
	void SetNaviBtnShow(HBOOL bShow = false);

	void SetFrontOrRearBtn(HBOOL bFront,HBOOL bShow = false);

	static void OnBtnNavi(void* p, void* pParam);
	void OnBtnNavi(void* pParam);
#ifdef EU_VERSION
#ifndef JP_VERSION
	static void OnBtnTACancel(void* p, void* pParam);
	void OnBtnTACancel(void* pParam);
	static void OnTACancelTimer(void *p, void *);
	void OnTACancelTimer();
#endif
#endif
	static void OnBtnFrontOrRear(void* p, void* pParam);
	void OnBtnFrontOrRear(void* pParam);

	void SetTouchCalibrateStatus(HBOOL bShow = false);
	HBOOL	GetTouchCalibrateStatus(void);
	void SetTitleNamePos(HINT x,HINT y);
	void DisableHeaderBtn(HBOOL bByPKBSts = true);
	void EnableHeaderBtn(void);
protected:
    HINT OnInit();
    HBOOL DoMessage(HMessage* msg);

	void StartMoving(void)
	{
		m_bMovingFlag = true;
	}
	
	
    
protected:
    void SetSystemTime(void);
    
private:
    // �ı�����
    //void ChangeLanguage(void);

    void ChangeLanguage(HCBaseCtrl* pCtrl);

    // �ı�ʱ��
    void ChangeTime(void);
    // �ı�ʱ���ʽ
    void ChangeTimeFormat(HBOOL bTimeFormat);

    static void OnTimer(void *p, void *);
    void OnTimer();
    void InvalidateCtrl(HCBaseCtrl *pBaseCtrl);
#ifdef EU_VERSION
#ifndef JP_VERSION
	static void OnAFTimer(void *p, void *);
	virtual void OnAFTimer();
#endif
#endif
private:
    //  static KCImageCtrl * m_pImgInfoIcon[MAX_INFO_ICON_NUM]; // ͼ����
    //  static kn_bool      m_bStatus[MAX_INFO_ICON_NUM+1];         // ͼ������״̬�����һ���Ƿ��ذ�ť��״̬

    // ʱ�䶨ʱ��
    CTimer      m_Time;
    // �ж�Surface(���������HMI������ʾ)

    // �жϽ�����ʾ��λ��
    POINT m_nBreakLocal;

    HCGroupCtrl* m_pHeadCtrl;

    // HEAD����
    HCImageCtrl* m_pHeadBk;
    // ��ǰ������
	HCScrollButtonText* m_pScrollTitleName;
	// ��Ƶ��ǰ����ʱ��
	HCScrollButtonText* m_pScrollTime;
    // ��Դ·��
    HString   m_strResPath;

    // ��ǰʱ��
    //static KCTextCtrl* m_pCurTime;
	static HCClockCtrl* m_pCurTime;

    // AM\PM
    //static KCTextCtrl* m_pAmPmTxt[2];
	//static KCImageCtrl* m_pAmPmImg[2];
	const RECOLOR m_clrAM;	// ����am��pm����ɫ
	const RECOLOR m_clrPM;

    // �ź���
    static HCImageCtrl* m_pImgInfoIcon[2];
    // ʱ���ʽ 24Сʱ��/12Сʱ��
    static HBOOL      m_bTimeFormat;
#ifdef EU_VERSION
#ifndef JP_VERSION
	// Radio Info
	static HCTextCtrl* m_pRadioInfoText[5];
#endif
#endif // EU_VERSION
	HString m_strMemString;
	IReSurface* m_pSourceTheme;		// ����ͼsurface��������draw��ʱ��ͱ���

	// ����ת��ť
	static HCButton*	m_pBtnNavi;
#ifdef EU_VERSION
#ifndef JP_VERSION
	static HCButton*	m_pTACancelBtn;
	CTimer				m_TACancelTimer;
#endif
#endif
	// �Ƿ������Ƶ����
	static HBOOL	m_bIsVideoWndShow;
	static HBOOL  m_bIsTouchCalibrate;

	HBOOL			m_bMovingFlag;	// �Ƿ�����forѭ������
	static HCButton* m_pBtnRearOrFront;
	HBOOL         m_bEnableShow;
	HBOOL         m_bTextReset;


	HBOOL         m_bEnableSetTitle;

#ifdef EU_VERSION
#ifndef JP_VERSION
		CTimer			m_AFTime;
#endif
#endif
};
