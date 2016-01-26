

#pragma once

#include <windows.h>
#include "Type.h"
#include <vector>
#include "KHMIBaseHead.h"
#include "KCLangManager.h"

using namespace std;

extern UICORE_DLL_API HINT g_nTransType;

// ��Ϣ�Ļص�
typedef LRESULT (*OwnerProc)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//***************************************************************
// *  ��������: �������ڲ���ʼ��UI������Ӧ����
// *  ��ڲ���: width ���ڿ��
// *            height ���ڸ߶�
// *            hInstance
// *            nCmdShow
// *            szWindowClass 
// *            szWindowName	��������
// *            icon			����ͼ��ID
// *  ���ڲ���: hWnd ���ھ��
// *  �� �� ֵ: TRUE�������ɹ�
//***************************************************************
#if defined(SCREEN_COLORBIT16)
HBOOL UICORE_DLL_API UIDevInit(IN HINT width, IN HINT height, IN HINSTANCE hInstance,
									 IN HCHAR* szWindowClass, IN HCHAR* szWindowName, IN HINT icon, OUT HWND& hWnd, IN HINT screenColorType = RE_COLOR565,
									 IN HINT x = 0,IN HINT y = 0);
#else
HBOOL UICORE_DLL_API UIDevInit(IN HINT width, IN HINT height, IN HINSTANCE hInstance,
									 IN HCHAR* szWindowClass, IN HCHAR* szWindowName, IN HINT icon, OUT HWND& hWnd, IN HINT screenColorType = RE_COLOR888,
									 IN HINT x = 0,IN HINT y = 0);
#endif

//***************************************************************
// *  ��������: ж��UI���������Դ
// *  ��ڲ���: 
// *  ���ڲ���: 
// *  �� �� ֵ: 
//***************************************************************
void UICORE_DLL_API UIDevRelease();


//***************************************************************
// *  ��������: �����Զ������Ϣ������
// *  ��ڲ���: 
// *  ���ڲ���: 
// *  �� �� ֵ: 
//***************************************************************
void UICORE_DLL_API SetOwnerProc(OwnerProc proc);

//***************************************************************
// *  ��������: �������������Ϣ
// *  ��ڲ���: 
// *  ���ڲ���: 
// *  �� �� ֵ: 
//***************************************************************
void UICORE_DLL_API PostMessageToSever(IN HINT nMsgId, IN HINT wParam, IN HINT lParam);

//***************************************************************
// *  ��������: �ӳ����window class name�õ�type
// *  ��ڲ���:
// *  ���ڲ���:
// *  �� �� ֵ:
// *  ��������:   
// *  �ա�����: 2010-1-21
//***************************************************************
HINT UICORE_DLL_API GetExeTypebyString(const HCHAR* strExe);

//***************************************************************
// *  ��������: 
// *  ��ڲ���:
// *  ���ڲ���:
// *  �� �� ֵ:
// *  ��������:   
// *  �ա�����: 2010-1-21
//***************************************************************
HString UICORE_DLL_API ParseCmdLine(const HCHAR* pStrCmdLine);

//***************************************************************
// *  ��������: 
// *  ��ڲ���:
// *  ���ڲ���:
// *  �� �� ֵ:
// *  ��������:   
// *  �ա�����: 2010-2-21
//***************************************************************
void UICORE_DLL_API ParseCommonParam(const HCHAR* pStrCmdLine,vector<HString>& vecString);

//***************************************************************
// *  ��������: ��������Ϣ���͵���������ʾ
// *  ��ڲ���:
// *  ���ڲ���:
// *  �� �� ֵ:
// *  ��������:   
// *  �ա�����: 2010-2-10
//***************************************************************
void UICORE_DLL_API PostDebugMessageToSever(IN const HString& strInfo);

//***************************************************************
// *  ��������: ��������Ϣ���͵���������ʾ
// *  ��ڲ���:
// *  ���ڲ���:
// *  �� �� ֵ:
// *  ��������:   
// *  �ա�����: 2010-2-10
//***************************************************************
void UICORE_DLL_API PostDebugMessageToSever(IN const HCHAR *format, ...);

//***************************************************************
// *  ��������: ��������������������
// *  ��ڲ���:
// *  ���ڲ���:
// *  �� �� ֵ:
// *  ��������:   
// *  �ա�����: 2010-3-3
//***************************************************************
void UICORE_DLL_API TransEffectForClarion(HDialogBase *pDlg, HINT nTransType,HINT nCmdShow );
void UICORE_DLL_API TransEffectForClarion(HDialogBase *pDlg, LPTSTR lpCmdLine,HINT nCmdShow );

//***************************************************************
// *  ��������: ��������������F8D��
// *  ��ڲ���:
// *  ���ڲ���:
// *  �� �� ֵ:
// *  ��������:   
// *  �ա�����: 2010-3-3
//***************************************************************
void UICORE_DLL_API TransEffectForF8D(HDialogBase *pDlg, IReSurface *pExeSurface,HINT nTransType,HINT nCmdShow );
void UICORE_DLL_API TransEffectForF8D(HDialogBase *pDlg, IReSurface *pExeSurface,LPTSTR lpCmdLine,HINT nCmdShow );

//***************************************************************
// *  ��������: 
// *  ��ڲ���:
// *  ���ڲ���:
// *  �� �� ֵ:
// *  ��������:   
// *  �ա�����: 2010-3-3
//***************************************************************
HINT UICORE_DLL_API GetTransTypeFromCmdLine(const HCHAR* lpCmdLine);


//***************************************************************
// *  ��������:	��ȡ���λ��
// *  ��ڲ���:	
// *  ���ڲ���:	
// *  �� �� ֵ:	
// *  ��������:	 
// *  �ա�����:	2010-03-12
//***************************************************************
void UICORE_DLL_API GetMousePos(OUT HINT& x,OUT HINT& y);

//***************************************************************
// *  ��������: ����Ӳ��Beep��
// *  ��ڲ���:
// *  ���ڲ���:
// *  �� �� ֵ:
// *  ��������: 
// *  �ա�����: 2010-3-23
//***************************************************************
void UICORE_DLL_API BeepOn(void);

//***************************************************************
// *  ��������: ��memstringת����mem int
// *  ��ڲ���:
// *  ���ڲ���:
// *  �� �� ֵ:
// *  ��������: 
// *  �ա�����: 2010-3-23
//***************************************************************
HINT UICORE_DLL_API MemStringToMemInt(const HString& strMem);

//***************************************************************
// *  ��������: ��mem intת����mem string
// *  ��ڲ���:
// *  ���ڲ���:
// *  �� �� ֵ:
// *  ��������: 
// *  �ա�����: 2010-3-23
//***************************************************************
HString UICORE_DLL_API MemIntToMemString(HINT nMem);

//***************************************************************
// *  ��������: �豸focus����
// *  ��ڲ���:
// *  ���ڲ���:
// *  �� �� ֵ:
// *  ��������: 
// *  �ա�����: 2010-3-23
//***************************************************************
HBOOL UICORE_DLL_API UI_SetFocusWnd(HCWindow* pWnd);


//***************************************************************
// *  ��������: ��Ӧ�ó������Ϣת����UI����Ĵ���
// *  ��ڲ���:
// *  ���ڲ���:
// *  �� �� ֵ:
// *  ��������: 
// *  �ա�����: 2010-5-19
//***************************************************************
void UICORE_DLL_API UI_TranslateMsg(UINT message, WPARAM wParam, LPARAM lParam,HBOOL bSendToBackWnd);


//***************************************************************
// *  ��������: ɾ�������б��еķ�ģʽ���ں���
// *  ��ڲ���: 
// *  ���ڲ���: 
// *  �� �� ֵ: 
// *  ��������: �ϻ���
// *  �ա�����: 2010-5-26
//***************************************************************
void UICORE_DLL_API UI_DelWindow(HCWindow* pDelWnd);

//***************************************************************
// *  ��������: ����Cursor״̬�Ƿ���Ч
// *  ��ڲ���: 
// *  ���ڲ���: 
// *  �� �� ֵ: 
// *  ��������:               
// *  �ա�����: 2010-06-04
//***************************************************************
void UICORE_DLL_API UI_CursorEnabled(HBOOL bEnable);
HBOOL UICORE_DLL_API IsCursorEnabled();

//***************************************************************
// *  ��������: ��鴰���Ƿ����
// *  ��ڲ���: 
// *  ���ڲ���: 
// *  �� �� ֵ: 
// *  ��������:   
// *  �ա�����: 2010-06-24
//***************************************************************
HBOOL UICORE_DLL_API CheckWindow(HCWindow *pWnd);

#ifndef  __IPC_EVENT
typedef void (*IPC_EVENT) (__in unsigned char uSendID,__in unsigned short uIPCEvent,__in unsigned long uSize,__in const unsigned char * pData);
typedef short (*HMI_INIT)	(unsigned char, HWND, IPC_EVENT);
//***************************************************************
// *  ��������: ע��Register����ص�,��HMIDevInit֮ǰע��˻ص�����ע��IPC
// *  ��ڲ���: 
// *  ���ڲ���: 
// *  �� �� ֵ: 
// *  ��������:               
// *  �ա�����: 2011-11-08
//***************************************************************
void UICORE_DLL_API RegisterHMI(HMI_INIT hmiInit, unsigned char uID, IPC_EVENT RecvIPCEvent);
#endif

void UICORE_DLL_API TransAffect(IReSurface *pOldSur, IReSurface *pNewSur, HINT trans_type);

void UICORE_DLL_API ClearScreen(HBYTE byValue);

HBOOL UICORE_DLL_API IsForceWndNotInfoBar(void);

UICORE_DLL_API HCHAR*  GetUserDataPath(void);

HBYTE UICORE_DLL_API GetCarType(void);