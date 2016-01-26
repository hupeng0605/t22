

#pragma once

#include <windows.h>
#include "Type.h"
#include <vector>
#include "KHMIBaseHead.h"
#include "KCLangManager.h"

using namespace std;

extern UICORE_DLL_API HINT g_nTransType;

// 消息的回调
typedef LRESULT (*OwnerProc)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//***************************************************************
// *  功　　能: 创建窗口并初始化UI引擎相应参数
// *  入口参数: width 窗口宽度
// *            height 窗口高度
// *            hInstance
// *            nCmdShow
// *            szWindowClass 
// *            szWindowName	窗口名称
// *            icon			程序图标ID
// *  出口参数: hWnd 窗口句柄
// *  返 回 值: TRUE：创建成功
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
// *  功　　能: 卸载UI引擎相关资源
// *  入口参数: 
// *  出口参数: 
// *  返 回 值: 
//***************************************************************
void UICORE_DLL_API UIDevRelease();


//***************************************************************
// *  功　　能: 设置自定义的消息处理函数
// *  入口参数: 
// *  出口参数: 
// *  返 回 值: 
//***************************************************************
void UICORE_DLL_API SetOwnerProc(OwnerProc proc);

//***************************************************************
// *  功　　能: 向服务器发送消息
// *  入口参数: 
// *  出口参数: 
// *  返 回 值: 
//***************************************************************
void UICORE_DLL_API PostMessageToSever(IN HINT nMsgId, IN HINT wParam, IN HINT lParam);

//***************************************************************
// *  功　　能: 从程序的window class name得到type
// *  入口参数:
// *  出口参数:
// *  返 回 值:
// *  作　　者:   
// *  日　　期: 2010-1-21
//***************************************************************
HINT UICORE_DLL_API GetExeTypebyString(const HCHAR* strExe);

//***************************************************************
// *  功　　能: 
// *  入口参数:
// *  出口参数:
// *  返 回 值:
// *  作　　者:   
// *  日　　期: 2010-1-21
//***************************************************************
HString UICORE_DLL_API ParseCmdLine(const HCHAR* pStrCmdLine);

//***************************************************************
// *  功　　能: 
// *  入口参数:
// *  出口参数:
// *  返 回 值:
// *  作　　者:   
// *  日　　期: 2010-2-21
//***************************************************************
void UICORE_DLL_API ParseCommonParam(const HCHAR* pStrCmdLine,vector<HString>& vecString);

//***************************************************************
// *  功　　能: 将调试信息发送到服务器显示
// *  入口参数:
// *  出口参数:
// *  返 回 值:
// *  作　　者:   
// *  日　　期: 2010-2-10
//***************************************************************
void UICORE_DLL_API PostDebugMessageToSever(IN const HString& strInfo);

//***************************************************************
// *  功　　能: 将调试信息发送到服务器显示
// *  入口参数:
// *  出口参数:
// *  返 回 值:
// *  作　　者:   
// *  日　　期: 2010-2-10
//***************************************************************
void UICORE_DLL_API PostDebugMessageToSever(IN const HCHAR *format, ...);

//***************************************************************
// *  功　　能: 下面两个函数供歌乐用
// *  入口参数:
// *  出口参数:
// *  返 回 值:
// *  作　　者:   
// *  日　　期: 2010-3-3
//***************************************************************
void UICORE_DLL_API TransEffectForClarion(HDialogBase *pDlg, HINT nTransType,HINT nCmdShow );
void UICORE_DLL_API TransEffectForClarion(HDialogBase *pDlg, LPTSTR lpCmdLine,HINT nCmdShow );

//***************************************************************
// *  功　　能: 下面两个函数供F8D用
// *  入口参数:
// *  出口参数:
// *  返 回 值:
// *  作　　者:   
// *  日　　期: 2010-3-3
//***************************************************************
void UICORE_DLL_API TransEffectForF8D(HDialogBase *pDlg, IReSurface *pExeSurface,HINT nTransType,HINT nCmdShow );
void UICORE_DLL_API TransEffectForF8D(HDialogBase *pDlg, IReSurface *pExeSurface,LPTSTR lpCmdLine,HINT nCmdShow );

//***************************************************************
// *  功　　能: 
// *  入口参数:
// *  出口参数:
// *  返 回 值:
// *  作　　者:   
// *  日　　期: 2010-3-3
//***************************************************************
HINT UICORE_DLL_API GetTransTypeFromCmdLine(const HCHAR* lpCmdLine);


//***************************************************************
// *  功　　能:	获取鼠标位置
// *  入口参数:	
// *  出口参数:	
// *  返 回 值:	
// *  作　　者:	 
// *  日　　期:	2010-03-12
//***************************************************************
void UICORE_DLL_API GetMousePos(OUT HINT& x,OUT HINT& y);

//***************************************************************
// *  功　　能: 触发硬件Beep音
// *  入口参数:
// *  出口参数:
// *  返 回 值:
// *  作　　者: 
// *  日　　期: 2010-3-23
//***************************************************************
void UICORE_DLL_API BeepOn(void);

//***************************************************************
// *  功　　能: 将memstring转换到mem int
// *  入口参数:
// *  出口参数:
// *  返 回 值:
// *  作　　者: 
// *  日　　期: 2010-3-23
//***************************************************************
HINT UICORE_DLL_API MemStringToMemInt(const HString& strMem);

//***************************************************************
// *  功　　能: 将mem int转换到mem string
// *  入口参数:
// *  出口参数:
// *  返 回 值:
// *  作　　者: 
// *  日　　期: 2010-3-23
//***************************************************************
HString UICORE_DLL_API MemIntToMemString(HINT nMem);

//***************************************************************
// *  功　　能: 设备focus窗口
// *  入口参数:
// *  出口参数:
// *  返 回 值:
// *  作　　者: 
// *  日　　期: 2010-3-23
//***************************************************************
HBOOL UICORE_DLL_API UI_SetFocusWnd(HCWindow* pWnd);


//***************************************************************
// *  功　　能: 将应用程序的消息转发到UI引擎的窗口
// *  入口参数:
// *  出口参数:
// *  返 回 值:
// *  作　　者: 
// *  日　　期: 2010-5-19
//***************************************************************
void UICORE_DLL_API UI_TranslateMsg(UINT message, WPARAM wParam, LPARAM lParam,HBOOL bSendToBackWnd);


//***************************************************************
// *  功　　能: 删除窗口列表中的非模式窗口函数
// *  入口参数: 
// *  出口参数: 
// *  返 回 值: 
// *  作　　者: 鞠华玮
// *  日　　期: 2010-5-26
//***************************************************************
void UICORE_DLL_API UI_DelWindow(HCWindow* pDelWnd);

//***************************************************************
// *  功　　能: 设置Cursor状态是否有效
// *  入口参数: 
// *  出口参数: 
// *  返 回 值: 
// *  作　　者:               
// *  日　　期: 2010-06-04
//***************************************************************
void UICORE_DLL_API UI_CursorEnabled(HBOOL bEnable);
HBOOL UICORE_DLL_API IsCursorEnabled();

//***************************************************************
// *  功　　能: 检查窗口是否存在
// *  入口参数: 
// *  出口参数: 
// *  返 回 值: 
// *  作　　者:   
// *  日　　期: 2010-06-24
//***************************************************************
HBOOL UICORE_DLL_API CheckWindow(HCWindow *pWnd);

#ifndef  __IPC_EVENT
typedef void (*IPC_EVENT) (__in unsigned char uSendID,__in unsigned short uIPCEvent,__in unsigned long uSize,__in const unsigned char * pData);
typedef short (*HMI_INIT)	(unsigned char, HWND, IPC_EVENT);
//***************************************************************
// *  功　　能: 注册Register引擎回调,在HMIDevInit之前注册此回调用来注册IPC
// *  入口参数: 
// *  出口参数: 
// *  返 回 值: 
// *  作　　者:               
// *  日　　期: 2011-11-08
//***************************************************************
void UICORE_DLL_API RegisterHMI(HMI_INIT hmiInit, unsigned char uID, IPC_EVENT RecvIPCEvent);
#endif

void UICORE_DLL_API TransAffect(IReSurface *pOldSur, IReSurface *pNewSur, HINT trans_type);

void UICORE_DLL_API ClearScreen(HBYTE byValue);

HBOOL UICORE_DLL_API IsForceWndNotInfoBar(void);

UICORE_DLL_API HCHAR*  GetUserDataPath(void);

HBYTE UICORE_DLL_API GetCarType(void);