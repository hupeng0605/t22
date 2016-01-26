#ifndef _CONFIGURE_H__
#define _CONFIGURE_H__

#include "Platform.h"

//定义版本相关信息，只能开一个
#define EU_VERSION //欧洲版
//#define UK_VERSION// 英国版
//#define US_VERSION //北美版
//#define JP_VERSION	//日本版
#define  CH_VERSION
#define JP_VERSION


// 定义DEBUG和_DEBUG宏
#if defined(ENGINE_EVC) && defined(DEBUG) && !defined(_DEBUG)
#define _DEBUG
#endif
#if defined(ENGINE_VC) && defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif

// 显示器参数
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   480

#define SCREEN_COLORBIT16	`	// 16位色引擎
//#define SCREEN_COLORBIT24		// 24位色引擎

// 常用字符串缓冲区大小
#define BUF_SIZE 256

#ifndef KN_LIB
#ifdef DLL_EXPORTS
#define CYPRESS_DLL_API __declspec(dllexport)
#else
#define CYPRESS_DLL_API __declspec(dllimport)
#endif
#else
#define CYPRESS_DLL_API
#endif
/************************************************************************/
/* 语言文件路径定义																												*/
/************************************************************************/
// 语言文件路径
#define LANGUAGE_CHN _T("HMI\\Language\\chinese_ch.ini") // 中文简体路径
#define LANGUAGE_TRA _T("HMI\\Language\\tradition_ch.ini") // 中文繁体路径
#ifdef	JP_VERSION
#define LANGUAGE_ENG _T("HMI\\Language\\english_jp.ini") // 英文路径
#else
#define LANGUAGE_ENG _T("HMI\\Language\\english_ch.ini") // 英文路径
#endif
#define LANGUAGE_JAP _T("HMI\\Language\\japanese_jp.ini")	//日文路径


/************************************************************************/
/* 资源文件路径定义																												*/
/************************************************************************/
#define RES_DIR _T("HMI\\")   // 资源文件目录
#define DATA_DIR _T("Data\\")// 数据文件目录
#define CONFIG_DIR _T("Config\\")// 配置文件目录
#define BACKGRND_MAIN_NAME	(_T("Main\\BnkFromUsb.ktc"))

#if 0
#ifndef WINCE
#define USER_DATA_PATH		(_T("D:\\Dev\\Cypress\\CypressDB\\03IMPLEMENT\\0301Code\\Cypress\\Bin\\win32\\"))	// 用户文件路径
#else
#define USER_DATA_PATH		(_T("\\NandFlash\\"))	// 用户文件路径
#endif
#endif



/************************************************************************/
/* 应用程序的窗口标题和类名定义																							*/
/************************************************************************/
#define APP_CLASSNAME_MAIN _T("Main")
#define APP_TITLE_MAIN _T("Main")

#define APP_CLASSNAME_RADIO _T("Radio")
#define APP_TITLE_RADIO _T("Radio")

#define APP_CLASSNAME_MUSIC _T("Music")
#define APP_TITLE_MUSIC _T("Music")

#define APP_CLASSNAME_SIRIUS _T("Sirius")
#define APP_TITLE_SIRIUS _T("Sirius")

#define APP_CLASSNAME_IPOD _T("iPod")
#define APP_TITLE_IPOD _T("iPod")

#define APP_CLASSNAME_AUX _T("AuxIn")
#define APP_TITLE_AUX _T("AuxIn")

//#define APP_CLASSNAME_INFOBAR _T("InfoBar")
#define APP_TITLE_INFOBAR _T("SP_InfoBar")
//#define APP_CLASSNAME_BRIGHTBAR _T("SP_Brightness")
#define APP_TITLE_BRIGHTNESS _T("SP_Brightness")
//#define APP_CLASSNAME_BRIGHTBAR _T("SP_Brightness")
#define APP_TITLE_ANGEL _T("SP_Angle")
//#define APP_CLASSNAME_BRIGHTBAR _T("SP_Brightness")
#define APP_TITLE_TURNINFO _T("SP_TurnInfoBar")
#define APP_CLASSNAME_VOLUMEBAR _T("InfoBar")	// volume bar
#define APP_TITLE_VOLUMEBARBAR _T("InfoBar")

#define APP_CLASSNAME_BLUETOOTH _T("Bluetooth")
#define APP_TITLE_BLUETOOTH _T("Bluetooth")

#define APP_CLASSNAME_INTERNET _T("Internet")
#define APP_TITLE_INTERNET _T("Internet")

#define APP_CLASSNAME_PICTURE _T("Picture")
#define APP_TITLE_PICTURE _T("Picture")

#define APP_CLASSNAME_VIDEO _T("Video")
#define APP_TITLE_VIDEO _T("Video")

#define APP_CLASSNAME_CLOCK _T("Clock")
#define APP_TITLE_CLOCK _T("Clock")

#define APP_CLASSNAME_EQ _T("EQ")
#define APP_TITLE_EQ _T("EQ")

#define APP_CLASSNAME_NAVI _T("NaviSystem")
#define APP_TITLE_NAVI _T("NaviSystem")

#define APP_CLASSNAME_COM   _T("Com")

#define APP_TITLENAME_SEVER     (_T("Server"))
#define APP_CLASSNAME_SERVER    (_T("Server"))

#define APP_TITLENAME_DISC     (_T("Disc"))
#define APP_CLASSNAME_DISC    (_T("Disc"))

#define APP_CLASSNAME_MONITOR	(_T("Monitor"))
#define APP_TITLE_MONITOR	(_T("Monitor"))

#define APP_CLASSNAME_ANTITHEFT (_T("AntiTheft"))
#define APP_TITLE_ANTITHEFT		(_T("AntiTheft"))

/************************************************************************/
/* 共享内存字段定义                                                     */
/************************************************************************/
#define MEMMAP_STRING_RADIO					(_T("Global\\MEM_STRING_RADIO"))
#define MEMMAP_STRING_DISCAUDIO				(_T("Global\\MEM_STRING_DISCAUDIO"))
#define MEMMAP_STRING_IPODAUDIO				(_T("Global\\MEM_STRING_IPODAUDIO"))
#define MEMMAP_STRING_SIRIUS				(_T("Global\\MEM_STRING_SIRIUS"))
#define MEMMAP_STRING_USBAUDIO				(_T("Global\\MEM_STRING_USBAUDIO"))
#define MEMMAP_STRING_BTAUDIO				(_T("Global\\MEM_STRING_BTAUDIO"))
#define MEMMAP_STRING_DISCVIDEO_FRONT		(_T("Global\\MEM_STRING_DISCVIDEO_FRONT"))
#define MEMMAP_STRING_IPODVIDEO_FRONT		(_T("Global\\MEM_STRING_IPODVIDEO_FRONT"))
#define MEMMAP_STRING_USBVIDEO				(_T("Global\\MEM_STRING_DISCVIDEO"))
#define MEMMAP_STRING_AUX1_FRONT			(_T("Global\\MEM_STRING_AUX1_FRONT"))
#define MEMMAP_STRING_AUX2_FRONT			(_T("Global\\MEM_STRING_AUX2_FRONT"))
#define MEMMAP_STRING_DVBT					(_T("Global\\MEM_STRING_DVBT"))
#define MEMMAP_STRING_NAVI					(_T("Global\\MEM_STRING_NAVI"))
#define MEMMAP_STRING_TEL					(_T("Global\\MEM_STRING_TEL"))
#define MEMMAP_STRING_CAMERA				(_T("Global\\MEM_STRING_CAMERA"))

#define MEMMAP_STRING_DISCVIDEO_REAR		(_T("Global\\MEM_STRING_DISCVIDEO_REAR"))
#define MEMMAP_STRING_IPODVIDEO_REAR		(_T("Global\\MEM_STRING_IPODVIDEO_REAR"))
#define MEMMAP_STRING_AUX1_REAR				(_T("Global\\MEM_STRING_AUX1_REAR"))
#define MEMMAP_STRING_AUX2_REAR				(_T("Global\\MEM_STRING_AUX2_REAR"))
#define MEMMAP_STRING_ZONEOFF				(_T("Global\\MEM_STRING_ZONEOFF"))

//#define MEMMAP_INT_RADIO				(0)
//#define MEMMAP_INT_DISCAUDIO			(1)
//#define MEMMAP_INT_IPODAUDIO			(2)
//#define MEMMAP_INT_SIRIUS				(3)
//#define MEMMAP_INT_USBAUDIO				(4)
//#define MEMMAP_INT_BTAUDIO				(5)
//#define MEMMAP_INT_DISCVIDEO_FRONT		(6)
//#define MEMMAP_INT_IPODVIDEO_FRONT		(7)
//#define MEMMAP_INT_USBVIDEO				(8)
//#define MEMMAP_INT_AUX1_FRONT			(9)
//#define MEMMAP_INT_AUX2_FRONT			(10)
//#define MEMMAP_INT_DVBT					(11)
//#define MEMMAP_INT_NAVI					(12)
//#define MEMMAP_INT_TEL					(13)
//#define MEMMAP_INT_CAMERA				(14)
//			   
//#define MEMMAP_INT_DISCVIDEO_REAR		(15)
//#define MEMMAP_INT_IPODVIDEO_REAR		(16)
//#define MEMMAP_INT_AUX1_REAR			(17)
//#define MEMMAP_INT_AUX2_REAR			(18)
//#define MEMMAP_INT_ZONEOFF				(19)

/************************************************************************/
/* 播放源和启动参数定义																										*/
/************************************************************************/
// 源名,参数都换成了整数类型了
//#define SOURCE_NAME_NULL    _T(" ")
//#define SOURCE_NAME_HDD     _T("HDD")
//#define SOURCE_NAME_USB     _T("USB")
//#define SOURCE_NAME_SD      _T("SD")
//#define SOURCE_NAME_IPOD    _T("IPOD")
//#define SOURCE_NAME_DVD     _T("DVD")
//#define SOURCE_NAME_SETUP   _T("SETUP")
//#define SOURCE_NAME_DES     _T("DES")
// 视频和音频根据不同的源的启动参数
#define SOURCE_PARAM_NULL   (0)
#define SOURCE_PARAM_HDD    (1)
#define SOURCE_PARAM_USB    (2)
#define SOURCE_PARAM_SD     (3)
#define SOURCE_PARAM_IPOD   (4)
#define SOURCE_PARAM_DVD    (5)
#define SOURCE_PARAM_SETUP  (6)
#define SOURCE_PARAM_DES    (7)
#define SOURCE_PARAM_TEL_IN (8)
#define SOURCE_PARAM_AV1	(9)
#define SOURCE_PARAM_AV2	(10)
#define SOURCE_PARAM_TV		(11)
#define SOURCE_PARAM_CAMERA	(12)
#define SOURCE_PARAM_CD     (13)
#define SOURCE_PARAM_HIDE   (14)


// 源路径,通过KCDeviceName类来从配置文件读取
//#define SOURCE_PATH_HDD       _T("\HDD")
//#define SOURCE_PATH_USB       _T("\USB")
//#define SOURCE_PATH_SD        _T("\SD")
//#define SOURCE_PATH_IPOD  _T("\IPOD")

/************************************************************************/
/* exe和服务器通信消息定义																									*/
/************************************************************************/
// 应用程序向服务器发起的请求消息
#define WM_TO_SEVER_BASE            (WM_USER+100)
#define WM_CHANEGLANG_REQ           (WM_TO_SEVER_BASE+1)
#define WM_CHANGEBKGRND_REQ         (WM_TO_SEVER_BASE+2)
#define WM_CHANGETIME_REQ           (WM_TO_SEVER_BASE+3)
#define WM_TRANSAFFECT_REQ          (WM_TO_SEVER_BASE+4)
//#define WM_STARTEXE_REQ               (WM_COPYDATA)           // 因为要传递字符串参数
#define WM_STARTEXE_REQ             (WM_TO_SEVER_BASE+5)
#define WM_CHANGETIMEFORMAT_REQ     (WM_TO_SEVER_BASE+6)
#define WM_CHANGECLOCKTYPE_REQ      (WM_TO_SEVER_BASE+7)
#define WM_CHANGEDATE_REQ           (WM_TO_SEVER_BASE+8)
#define WM_ACTIVESYNC_REQ           (WM_TO_SEVER_BASE+9)
#define WM_CLOSEEXE_REQ             (WM_TO_SEVER_BASE+10)       // 应用程序通知服务器自己已经退出了
#define WM_DEBUG_MSG_REQ            (WM_COPYDATA)
#define WM_BACKEXE_REQ				(WM_TO_SEVER_BASE+11)		// 应用程序切换到后台
// 应用程序请求硬件beep音
#define WM_BEEP_ON_REQ				(WM_TO_SEVER_BASE+12)// 硬件Beep音
//#define WM_EXE_TO_FRONT_REQ         (WM_TO_SEVER_BASE+13)

#define WM_BRIGHT_UPDATE_VAL_REQ	(WM_TO_SEVER_BASE+15)

#define WM_POWEROFF_OVER_REQ		(WM_TO_SEVER_BASE+16)
#define WM_FRONT_REAR_CHANGE_REQ	(WM_TO_SEVER_BASE+17)

#define WM_ISLOADFACTROY_REQ		(WM_TO_SEVER_BASE+18) // setting 发送给sever的
#define WM_ISLOADFACTROY_OK_REQ     (WM_TO_SEVER_BASE+19)// 应用程序发送给server的
#define WM_DISCERROR_REQ            (WM_TO_SEVER_BASE+20)
#define WM_DISC_TYPE_REQ			(WM_TO_SEVER_BASE+21)	// 自动入碟的时候读取的媒体类型，改变main的当前源

#define WM_CLOSE_VOL_BAR_REQ		(WM_TO_SEVER_BASE+22)	// 请求关闭volume bar消息

#define WM_CLOSE_INFOBAR_REQ		(WM_TO_SEVER_BASE+23)	// info bar显示出来后点击其他区域消除info bar
#define WM_STANDBY_REQ				(WM_TO_SEVER_BASE+24)	// 待机请求
#define WM_TA_CANCEL_REQ			(WM_TO_SEVER_BASE+25)	// TA cancel请求
#define WM_RETURN_CUR_SRC_REQ		(WM_TO_SEVER_BASE+26)	// 返回到当前源
#define WM_SHOW_MAIN_REQ			(WM_TO_SEVER_BASE+27)	// 显示main menu
#define WM_SETUP_STATUS_REQ			(WM_TO_SEVER_BASE+28)	// 是否在set up界面
#define WM_SRC_BTN_STATUS_REQ		(WM_TO_SEVER_BASE+29)	// 更新主界面上的sirius按钮状态
#define WM_PLAYER_STATUS_REQ		(WM_TO_SEVER_BASE+30)	// 更新播放器状态
#define WM_ANTITHIEF_STS_REQ		(WM_TO_SEVER_BASE+31)	// 通知防盗密码状态


// 消息的sub type
// 启动exe程序
#define SUB_TYPE_EXE_SEVER      (0)
#define SUB_TYPE_EXE_BT         (1)// 蓝牙程序
#define SUB_TYPE_EXE_CLOCK      (2)// 时钟程序
#define SUB_TYPE_EXE_EQ         (3)// EQ设置程序
#define SUB_TYPE_EXE_INTERNET   (4)// 网络程序
#define SUB_TYPE_EXE_MAIN       (5)// 主菜单
#define SUB_TYPE_EXE_MUSIC      (6)// 音乐播放程序
#define SUB_TYPE_EXE_PICTURE    (7)// 图片浏览程序
#define SUB_TYPE_EXE_RADIO      (8)// 收音机程序
#define SUB_TYPE_EXE_VIDEO      (9)// 视频播放程序
#define SUB_TYPE_EXE_NAVI       (10)// 导航程序
#define SUB_TYPE_EXE_SIRIUS     (11)// 卫星收音机程序
#define SUB_TYPE_EXE_IPOD       (12)// iPod播放程序
#define SUB_TYPE_EXE_AUX		(13)// Aux程序
#define SUB_TYPE_EXE_INFOBAR	(14) // infobar
#define SUB_TYPE_EXE_DISC		(15) // DISC
#define SUB_TYPE_EXE_ZONEOFF    (16) // 关闭后台
#define SUB_TYPE_EXE_BRIGHTNESS	(17)	// 亮度调节和方向调节
#define SUB_TYPE_EXE_ANGEL		(18)
#define SUB_TYPE_EXE_TURNINFO	(19)
#define SUB_TYPE_EXE_VOLUMEBAR	(20)
#define SUB_TYPE_EXE_MONITOR	(21)	// 屏幕保护界面
#define SUB_TYPE_EXE_ANTITHIEF	(22)	// 防盗密码界面


// 同步
#define SUB_TYPE_SYNC_START     (1)
#define SUB_TYPE_SYNC_END       (2)


// 服务器返回给应用程序的消息
#define WM_FROM_SEVER_BASE      (WM_USER+500)
#define WM_CHANGELANG           (WM_FROM_SEVER_BASE+1)
#define WM_CHANGEBKGRND         (WM_FROM_SEVER_BASE+2)
#define WM_CHANGETIME           (WM_FROM_SEVER_BASE+3)
#define WM_TRANSAFFECT          (WM_FROM_SEVER_BASE+4)
#define WM_STARTEXE             (WM_FROM_SEVER_BASE+5)
#define WM_CHANGETIMEFORMAT     (WM_FROM_SEVER_BASE+6)
#define WM_CHANGECLOCKTYPE      (WM_FROM_SEVER_BASE+7)
#define WM_CHANGEDATE           (WM_FROM_SEVER_BASE+8)
#define WM_INIT_BY_PARAM        (WM_FROM_SEVER_BASE+9)

#define WM_CLOSE_VIDEO          (WM_FROM_SEVER_BASE+10)	// 关闭视频窗口
#define WM_SHOW_VIDEO           (WM_FROM_SEVER_BASE+11)	// 显示视频窗口

#define WM_CLOSE_EXE            (WM_FROM_SEVER_BASE+12)	// 关闭程序
#define WM_MAIN_UPDATEMEM		(WM_FROM_SEVER_BASE+13)	// Main更新程序的缩略图,仅仅使用歌乐项目
#define WM_UPDATE_CUR_SOURCE	(WM_FROM_SEVER_BASE+14)	// main 更新当前源
#define WM_MAIN_SOURCEBTN_STS	(WM_FROM_SEVER_BASE+15) // main 更新源按钮的状态
#define WM_SHOW_FRONT_REAR_BTN	(WM_FROM_SEVER_BASE+16) // 设置标题栏的front和rear按钮的状态
#define WM_MAIN_EFFECT			(WM_FROM_SEVER_BASE+17) // 通知main做动画

#define WM_LOADFACTROY          (WM_FROM_SEVER_BASE+18)
#define WM_RESTAR               (WM_FROM_SEVER_BASE+19) 

#define WM_CLOSE_VOL_BAR		(WM_FROM_SEVER_BASE+20) // 关闭volume bar消息
#define WM_CHANGE_USB_VOLUME	(WM_FROM_SEVER_BASE+21) // 调节USB的音量
#define WM_NOTIFY_MAIN_BACKGRND	(WM_FROM_SEVER_BASE+22)	// 通知main menu到后台了
#define WM_DISCONNECTA2DP		(WM_FROM_SEVER_BASE+23)	// 通知蓝牙切断A2DP
#define WM_DISCONNECT_DISC		(WM_FROM_SEVER_BASE+24) // 请求断开disc串口
#define WM_SHOW_DATE			(WM_FROM_SEVER_BASE+25)
#define WM_UPDATE_CAMERA_STS	(WM_FROM_SEVER_BASE+26) // 更新倒车状态
#define WM_PLAYER_STATUS		(WM_FROM_SEVER_BASE+27) // 更新播放器状态
#define WM_ANTITHIEF_PASSWORD	(WM_FROM_SEVER_BASE+28) // 防盗密码消息



/************************************************************************/
/* 服务器和OS通信消息定义																									*/
/************************************************************************/
// 服务器接受到的OS的消息,需要根据客户的信息作调整，应用程序不需要处理
#define WM_OS_MSG_BASE_RECEIVE              (WM_USER+5000)
#define WM_OS_MSG_DEVICE_RECEIVE			(WM_OS_MSG_BASE_RECEIVE+7)// 设备连接消息

// 服务器接受到OS的消息后转发给应用程序的消息，应用程序要处理
#define WM_OS_MSG_BASE              (WM_USER+1000)
#define WM_OS_MSG_DEVICE			(WM_OS_MSG_BASE+7)// 设备连接消息

#define OS_MSG_DEVICE_WPARAM_USB	(1)
#define OS_MSG_DEVICE_WPARAM_SD		(2)
#define OS_MSG_DEVICE_WPARAM_IPOD	(3)
#define OS_MSG_DEVICE_LPARAM_IN		(1)
#define OS_MSG_DEVICE_LPARAM_OUT	(0)


/************************************************************************/
/* 服务器和硬按钮通信的消息定义																							*/
/************************************************************************/
// 服务器接受到的硬按钮的消息，应用程序不需要处理
#define WM_HARD_MSG_BASE_RECEIVE            (WM_USER+5500)
//#define WM_HARD_MSG_START_RECEIVE           (WM_HARD_MSG_BASE_RECEIVE+1)    // 开关机       开关机按钮
//#define WM_HARD_MSG_FMAM_RECEIVE            (WM_HARD_MSG_BASE_RECEIVE+2)    // FM/AM        FM/AM波段切换
//#define WM_HARD_MSG_DVD_RECEIVE             (WM_HARD_MSG_BASE_RECEIVE+3)    // DVD          进入DVD界面快捷按钮
//#define WM_HARD_MSG_SRC_RECEIVE             (WM_HARD_MSG_BASE_RECEIVE+4)    // SRC          源切换
//#define WM_HARD_MSG_NAV_RECEIVE             (WM_HARD_MSG_BASE_RECEIVE+5)    // NAV          进入导航界面快捷按钮
//#define WM_HARD_MSG_PREV_RECEIVE            (WM_HARD_MSG_BASE_RECEIVE+6)    // |<<          播放器和IPOD界面为上一曲，收音机界面是按频率减小方向搜索
//#define WM_HARD_MSG_NEXT_RECEIVE            (WM_HARD_MSG_BASE_RECEIVE+7)    // >>|          播放器和IPOD界面为下一曲，收音机界面是按频率增加方向搜索
//#define WM_HARD_MSG_BT_RECEIVE              (WM_HARD_MSG_BASE_RECEIVE+8)    // BT           进入蓝牙界面快捷按钮
//#define WM_HARD_MSG_EQ_RECEIVE              (WM_HARD_MSG_BASE_RECEIVE+9)    // EQ           进入EQ界面快捷按钮
//#define WM_HARD_MSG_SETUP_RECEIVE           (WM_HARD_MSG_BASE_RECEIVE+10)   // Setup        进入设置界面快捷按钮
//#define WM_HARD_MSG_TTS_RECEIVE             (WM_HARD_MSG_BASE_RECEIVE+11)   // 语音播放     语音播放按钮
//#define WM_HARD_MSG_REPEAT_RECEIVE          (WM_HARD_MSG_BASE_RECEIVE+12)   // Repeat       语音重复按钮
//#define WM_HARD_MSG_MENU_RECEIVE            (WM_HARD_MSG_BASE_RECEIVE+13)   // MENU         进入主菜单按钮
//#define WM_HARD_MSG_MUTE_RECEIVE            (WM_HARD_MSG_BASE_RECEIVE+14)   // MUTE         静音按钮
//#define WM_HARD_MSG_ASPS_RECEIVE            (WM_HARD_MSG_BASE_RECEIVE+15)   // AS/PS        自动存储和节目搜索
//#define WM_HARD_MSG_DES_RECEIVE             (WM_HARD_MSG_BASE_RECEIVE+16)   // DES          地图界面目的地快捷按钮
//#define WM_HARD_MSG_VOL_RECEIVE             (WM_HARD_MSG_BASE_RECEIVE+17)   // VOL          音量旋钮
//#define WM_HARD_MSG_SMARTDIAL_RECEIVE       (WM_HARD_MSG_BASE_RECEIVE+18)   // SMART DIAL   移动焦点旋钮
//#define WM_HARD_MSG_DIRECTION_RECEIVE		(WM_HARD_MSG_BASE_RECEIVE+19)
//#define WM_HARD_MSG_LIGHT_RECEIVE			(WM_HARD_MSG_BASE_RECEIVE+20)
//#define WM_HARD_MSG_TENKEY_RECEIVE			(WM_HARD_MSG_BASE_RECEIVE+21)
//#define WM_HADR_KEY_MSG_RECEIVE				(WM_HARD_MSG_BASE_RECEIVE+22)	// 遥控器和面板按钮


// 服务器接受到硬按钮的消息后转发给应用程序的消息，应用程序要处理
#define WM_HARD_MSG_BASE            (WM_USER+1500)
#define WM_HARD_MSG_START           (WM_HARD_MSG_BASE+1)    // 开关机       开关机按钮
//#define WM_HARD_MSG_FMAM            (WM_HARD_MSG_BASE+2)    // FM/AM        FM/AM波段切换
//#define WM_HARD_MSG_DVD             (WM_HARD_MSG_BASE+3)    // DVD          进入DVD界面快捷按钮
//#define WM_HARD_MSG_SRC             (WM_HARD_MSG_BASE+4)    // SRC          源切换
//#define WM_HARD_MSG_NAV             (WM_HARD_MSG_BASE+5)    // NAV          进入导航界面快捷按钮
//#define WM_HARD_MSG_PREV            (WM_HARD_MSG_BASE+6)    // |<<          播放器和IPOD界面为上一曲，收音机界面是按频率减小方向搜索
//#define WM_HARD_MSG_NEXT            (WM_HARD_MSG_BASE+7)    // >>|          播放器和IPOD界面为下一曲，收音机界面是按频率增加方向搜索
//#define WM_HARD_MSG_BT              (WM_HARD_MSG_BASE+8)    // BT           进入蓝牙界面快捷按钮
//#define WM_HARD_MSG_EQ              (WM_HARD_MSG_BASE+9)    // EQ           进入EQ界面快捷按钮
//#define WM_HARD_MSG_SETUP           (WM_HARD_MSG_BASE+10)   // Setup        进入设置界面快捷按钮
//#define WM_HARD_MSG_TTS             (WM_HARD_MSG_BASE+11)   // 语音播放     语音播放按钮
//#define WM_HARD_MSG_REPEAT          (WM_HARD_MSG_BASE+12)   // Repeat       语音重复按钮
//#define WM_HARD_MSG_MENU            (WM_HARD_MSG_BASE+13)   // MENU         进入主菜单按钮
//#define WM_HARD_MSG_MUTE            (WM_HARD_MSG_BASE+14)   // MUTE         静音按钮
//#define WM_HARD_MSG_ASPS            (WM_HARD_MSG_BASE+15)   // AS/PS        自动存储和节目搜索
//#define WM_HARD_MSG_DES             (WM_HARD_MSG_BASE+16)   // DES          地图界面目的地快捷按钮
#define WM_HARD_MSG_VOL             (WM_HARD_MSG_BASE+17)   // VOL          音量旋钮
#define WM_HARD_MSG_SMARTDIAL       (WM_HARD_MSG_BASE+18)   // SMART DIAL   移动焦点旋钮
#define WM_HARD_MSG_DIRECTION		(WM_HARD_MSG_BASE+19)
#define WM_HARD_MSG_LIGHT			(WM_HARD_MSG_BASE+20)	// 亮度调节
#define WM_HARD_MSG_TENKEY			(WM_HARD_MSG_BASE+21)
#define WM_HARD_MSG_ANGLE			(WM_HARD_MSG_BASE+22)

#define WM_HADR_KEY_MSG				(WM_HARD_MSG_BASE+22)	// 遥控器和面板按钮
#define WM_HARD_KEY_EJECT			(WM_HARD_MSG_BASE+23)	// 出碟

// 增加按方向盘上的按钮接通电话的消息
#define WM_HARD_MSG_SEND				(WM_HARD_MSG_BASE+24)// SEND
#define WM_HARD_MSG_END					(WM_HARD_MSG_BASE+25)// END
#define WM_HARD_MSG_SENDEND				(WM_HARD_MSG_BASE+26)// SEND END


typedef enum
{
	KEY_MUTE        = 0x01,     //MUTE
	KEY_PLAY        = 0x02,     //PLAY/PAISE
	KEY_NEXT        = 0x03,		//下一曲>>|
	KEY_PREVIOUS    = 0x04,		//上一曲|<<
	KEY_EJECT       = 0x05,        //出碟
	KEY_SOURCE      = 0x06,     //SRC 键
	KEY_SET	        = 0x0c,		// 进入set up
	KEY_BAND        = 0x0d,		// band切换
	KEY_UP 		    = 0x12,		// 向上方向键
	KEY_DOWN 	    = 0x13,		// 向下方向键
	KEY_LEFT 	    = 0x14,		// 向左方向键
	KEY_RIGHT 		= 0x15,		// 向右方向键
	KEY_0           = 0x17,     //数字键
	KEY_1           = 0x18,
	KEY_2           = 0x19,
	KEY_3           = 0x1a,
	KEY_4           = 0x1b,
	KEY_5           = 0x1c,
	KEY_6           = 0x1d,
	KEY_7           = 0x1e,
	KEY_8           = 0x1f,
	KEY_9           = 0x20,
	KEY_MENU        = 0x23,		// menu
	KEY_STOPBAND	= 0x24,		// play pause long press
	KEY_ANGLE   	= 0x26,		// changel dvd angle
	KEY_TILT		= 0x8b,	// 调整屏幕的倾斜角
	KEY_TITLE       = 0x27,
	KEY_AUDIO       = 0x28,
	KEY_SUBTITLE 	= 0x29,
	KEY_ROOT        = 0x2a,
	KEY_ZOOM        = 0x2b,
	KEY_FAST_REW 	= 0x2c,		//快退
	KEY_FAST_FF 	= 0x2d,		//快进
	KEY_POWER_OFF 	= 0x35,		//关机
	KEY_ENTER 		= 0x36,  
	KEY_SEARCH      = 0x37,
	KEY_NEXT_PLUS	= 0x39,
	KEY_PREV_PLUS	= 0x3a,
	KEY_BACK 		= 0x52,
	KEY_TAG			= 0x66,
	KEY_ISR_LONG    = 0x6a,
	KEY_PIC         = 0x89 ,  
	KEY_REPEAT      = 0x30,
	KEY_AF          = 0xa9,
	KEY_SHUFFLE     = 0x2F,//0xd4,
	KEY_PRT_LONG    = 0xbd,
	KEY_RDM			= 0xFF, // key_shuffle,
	KEY_SEND		= 0x5E,
	KEY_END			= 0x5F,
	KEY_SEND_END	= 0x6D ,
	KEY_SMART_CW 	= 0x39,		//顺时针旋转
	KEY_SMART_CCW 	= 0x3a,	    //逆时针旋转
	KEY_SMART_CLICK = 0x3b,	    //按下
	KEY_SMART_HOLD 	= 0x3c,	    //长按
	KEY_TEL			= 0x41,		//TEL
	KEY_STAR   ,
	KEY_WELL,
	KEY_DEL,
	KEY_CALL,
	KEY_HANGUP,
	KEY_CANCEL,
	KEY_PLAUS
}LPARAM_KEYCODE;


/************************************************************************/
/* 突发事件定义																														*/
/************************************************************************/
// 服务器接受到的紧急事件的消息，应用程序不需要处理
#define WM_URGENT_MSG_BASE_RECEIVE				(WM_USER+6000)
#define WM_URGENT_MSG_TEL_IN_RECEIVE			(WM_URGENT_MSG_BASE_RECEIVE+1)
#define WM_URGENT_MSG_DISCLOADING_RECEIVE		(WM_URGENT_MSG_BASE_RECEIVE+2)
#define WM_URGENT_MSG_DISCLOADFINISH_RECEIVE	(WM_URGENT_MSG_BASE_RECEIVE+3)


// 服务器接受到紧急事件的消息后转发给应用程序的消息，应用程序要处理
#define WM_URGENT_MSG_BASE                  (WM_USER+2000)
#define WM_URGENT_MSG_TEL_IN                (WM_URGENT_MSG_BASE+1)  // 收到来电消息
#define WM_URGENT_MSG_DISCLOADING			(WM_URGENT_MSG_BASE+2)
#define WM_URGENT_MSG_DISCLOADFINISH		(WM_URGENT_MSG_BASE+3)
#define WM_URGENT_MSG_TEL_OFF               (WM_URGENT_MSG_BASE+4)  // 收到挂断消息


#define WM_MESSAGE_UART						(WM_USER +121) 
#define WM_MESSAGE_GETDLLCOMMAND			(WM_USER+133)

/************************************************************************/
/* Rear通信事件定义																														*/
/************************************************************************/
#define WM_MESSAGE_REAR_BASE				(WM_USER+6500)
#define WM_MESSAGE_REAR_OPEN				(WM_MESSAGE_REAR_BASE+1)
#define WM_MESSAGE_REAR_CLOSE				(WM_MESSAGE_REAR_BASE+2)


#define WM_PROCESS_BASE						(WM_USER+7000)
#define WM_BTMSG_PAIR						(WM_PROCESS_BASE+1)	// 配对蓝牙消息
#define WM_IPODMSG							(WM_PROCESS_BASE+2)	// ipod消息
#define WM_BTMSG_READPB						(WM_PROCESS_BASE+3)	// 读电话本
#define WM_BTMSG_READPN						(WM_PROCESS_BASE+4)	// 读电话号码
#define WM_BTMSG_DEVICEINFO					(WM_PROCESS_BASE+5)	// device info
#define WM_BTMSG_CONNECTSUCCESS				(WM_PROCESS_BASE+6) // 连接成功
#define WM_BTMSG_DISCONNECTSUCCESS			(WM_PROCESS_BASE+7)	// 断开成功
#define WM_BTMSG_DIALSTATE					(WM_PROCESS_BASE+8)	// 通话状态
#define WM_BTMSG_UPDATEID3					(WM_PROCESS_BASE+9)	// 更新ID3
#define WM_BTMSG_INQUIRYADD					(WM_PROCESS_BASE+10)// 搜索设备
#define WM_BTMSG_CLOSEWND					(WM_PROCESS_BASE+11)// 关闭窗口
#define WM_DISCMSG							(WM_PROCESS_BASE+12)// Disc消息
#define WM_BTMSG_MULTICALL					(WM_PROCESS_BASE+13)// 通话数
#define	WM_BTMSG_MODULEINFO					(WM_PROCESS_BASE+14)// 更新模块信息
#define WM_BTMSG_CHANGEPB					(WM_PROCESS_BASE+15)// 更新电话本
#define WM_BTMSG_UPDATEWND					(WM_PROCESS_BASE+16)// 蓝牙更新界面
#define WM_BTMSG_PLAYSTATUS					(WM_PROCESS_BASE+17)// 更新播放状态
#define WM_RADIO_UPDATE_FREQ				(WM_PROCESS_BASE+18) //收音机传送频率
#define WM_BTMSG_SEARCHPHONEBOOK			(WM_PROCESS_BASE+19)// 快速定位电话本




#define WM_HDRADIO_EVENT					(WM_PROCESS_BASE+20)// HD radio的更新UI消息
#define WM_MESSAGE_AntiTheft				(WM_PROCESS_BASE+21)


/************************************************************************/
/* 硬件状态通知事件定义																														*/
/************************************************************************/
#define WM_HARDWARE_SYS_BASE						(WM_USER+7500)
#define	WM_HARDWARE_SYS_INFO						(WM_HARDWARE_SYS_BASE+1)
#define WM_HARDWARE_NAVI_INFO						(WM_HARDWARE_SYS_BASE+2)
#define WM_NAVI_INFO_BTN_DOWN_REQ					(WM_HARDWARE_SYS_BASE+3)

#define WM_VIDEO_IN_MSG								(WM_HARDWARE_SYS_BASE+4)
#define VIDEOIN_DVBT		(1)
#define VIDEOIN_CAMERA		(2)
#define VIDEOIN_AUX1		(3)
#define VIDEOIN_AUX2		(4)

#define WM_PARKING_MSG								(WM_HARDWARE_SYS_BASE+5)
#define WM_TA_CANCEL_STS							(WM_HARDWARE_SYS_BASE+6)

#define WM_UPDATE_PTY_LANG				(WM_USER+7900)

/************************************************************************/
/* 自动测试消息															*/
/************************************************************************/
#define WM_CUR_EXE_REQ							(WM_USER+8000)

#endif // _CONFIGURE_H__