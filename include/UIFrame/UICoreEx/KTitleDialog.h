#if 0

/************************************************************************/
/* ������Ŀ����Ҫ                                                       */
/************************************************************************/

#pragma once
#include "hmienginecom.h"
#include <PubHead.h>
#include "kdialogbase.h"
#include "kcwindow.h"
#include <KMemMapAPI.h>

#ifdef MAX_INFO_ICON_NUM
#undef MAX_INFO_ICON_NUM
#endif
#define		MAX_INFO_ICON_NUM	(3)

class CYPRESS_DLL_API KTitleDialog :
	public HDialogBase
{
public:
	KTitleDialog(void);
	virtual ~KTitleDialog(void);
	KTitleDialog(const SYS_SETTING& sysSet);

public:
	// ��������
	void SetSysSetting(const SYS_SETTING& sysSet);
	// ���ñ��������ַ�
	void SetTitleByString(const HCHAR* a_pstrTitle);
	void SetTitleByLangID(HINT a_nLangID);
	// ���ñ�������icon
	void SetTitleIcon(const HString a_strPath);
	// ���÷��ص�Icon�ɼ��򲻿ɼ�
	void SetReturnIconVisibility(HBOOL a_bShow = true);
	
	void SetTimeZoneTransTo(HBOOL a_bTrans);
	HBOOL GetTimeZoneTransTo(void){return m_bToScreenOff;};

	// ��Ϣicon��
	HINT SetInfoIconVisibility(HINT a_nIndex,HBOOL a_bShow = true);
	HINT SetAllInfoIconVisibility(HBOOL a_bShow = true);
	HINT SetInfoIconActivity(HINT a_nIndex,HBOOL a_bActive = true);
	HINT SetAllInfoIconActivity(HBOOL a_bActive = true);
	// ���ر�����
	void SetTitleBarVisibility(HBOOL a_bShow = true);
	// ����ʱ��
	void SetTimeVisibility(HBOOL a_bShow = true);
	// ����״̬
	void SetStatusVisibility(HBOOL a_bShow = true);
	virtual void OnTitleBtnUp(void* pParam);
	virtual void OnTitleBtn(void* pParam);
	//void StartExe(kn_string strExeName,kn_string strParam = _T(""));
	//void StartExe(kn_int nExeType,kn_char* pstrParam = NULL);
	void StartExe(HINT nExeType,HINT nParam = 0);

	virtual void OnChildTimer(void* pParam);
public:
	virtual HINT OnInit();
	
	HBOOL DoMessage(HMessage* msg);
	// 
	virtual void Draw(IReSurface* pSurface);
	virtual void Draw(IReSurface* pSurface,IReSurface* pSurfaceMap,_kn_rect m_rectMap);
protected:
	void SetSystemTime(void);
	void StartEQ(void);
	void SetMemBkgdNULL();
private:
	// �ı�����
	void ChangeLanguage(void);

	void ChangeLanguage(HCBaseCtrl* pCtrl);
	void ChangeLanguage(HCGroupCtrl* pGroupCtrl);
	// �ı䱳��
	void ChangeBackground(void);
	// �ı�ʱ��
	void ChangeTime(void);
	// �ı�ʱ���ʽ
	void ChangeTimeFormat(HBOOL bTimeFormat);
	// �ı�ʱ������
	void ChangeClockType(HBOOL bClockType);
	// �ı�����
	void ChangeDate(void);
	// ��ʾ��������
	void ShowVol();
	
	static void OnTimer(void *p,void *pParam);
	void OnTimer(void* pParam);
	static void OnVolTimer(void *p,void *pParam);
	void OnVolTimer(void* pParam);

	static void OnTimeBtnUp(void* p, void* pParam);
	void OnTimeBtnUpToTimeSetup(void* pParam);
	void OnTimeBtnUpToScreenOff(void* pParam);

	//void SetSystemTime(void);
	void InvalidateCtrl(HCBaseCtrl *pBaseCtrl);

	static void OnTitleBtnDown(void* p, void* pParam);
	void OnTitleBtnDown(void* pParam);
	//static void OnTitleBtnUp(void* p, void* pParam);
	static void OnTitleBtn(void* p, void* pParam);
	void OnTitleBtnBase(void* pParam);

private:
	static HString	m_strResPath;						// ��Դ·��
	static HCImageCtrl	* m_pImgBK;							// ����������
	static HCImageCtrl * m_pImgTitleIcon;					// ������Icon
	HCButton	* m_pBtnTitle;								// ������title
	static HCButton	* m_pBtnTime;							// ʱ����
	static HCImageCtrl * m_pImgInfoIcon[MAX_INFO_ICON_NUM];	// ͼ����
	HBOOL		m_bToScreenOff;
	static HBOOL		m_bStatus[MAX_INFO_ICON_NUM+1];			// ͼ������״̬�����һ���Ƿ��ذ�ť��״̬

	//static kn_bool		m_bTimeFormat;							// ʱ���ʽ 24Сʱ��/12Сʱ��
	//static kn_bool		m_bClockType;						// ʱ�����ͣ�����ʱ��/ģ��ʱ��
	CTimer		m_Time;									// ʱ�䶨ʱ��
	CTimer		m_VolTime;									// �������ڶ�ʱ��
	static IReSurface* s_pMemBkgd;// �����ڴ汳��
	IReSurface* m_pBreakSurface;// �ж�Surface(���������HMI������ʾ)
	POINT m_nBreakLocal;// �жϽ�����ʾ��λ��
protected:
	static SYS_SETTING			m_sysSetting;					// �����ڴ��е�����
};
#endif