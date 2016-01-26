
#ifndef __DEFINE_PUBLICE_H__
#define __DEFINE_PUBLICE_H__

#ifndef _T
#ifdef _UNICODE
#define _T(x)		L ## x
#else
#define _T(x)		x
#endif
#endif

/*************************************** 一、常量定义（BEGIN） ***************************************/

#ifndef PATH_SEPARATOR
#	if defined(WIN32) || defined(WINCE)
#		define PATH_SEPARATOR	_T("\\")
#	else
#		define PATH_SEPARATOR	"/"
#	endif
#endif

// 指针安全调用宏
#ifndef SAFECALL
#define SAFECALL(pObj) pObj == NULL ? NULL : pObj
#endif


/////////////////////////// 一级相对路径 ///////////////////////////

// 配置文件所在的相对路径文件夹名
#define DIR_CONFIG				_T("config")
// UI文件所在的相对路径文件夹名
#define DIR_UI							_T("ui")
// 语言所在的相对路径文件夹名
#define DIR_LANGUAGE			_T("language")
// 字体所在的相对路径文件夹名
#define DIR_FONT			_T("Font")


/////////////////////////// 二级相对路径 ///////////////////////////


/////////////////////////// 三级相对路径 ///////////////////////////

// 主菜单模块资源的相对路径文件夹名
#define DIR_MENU				_T("main")
// RADIO模块资源的相对路径文件夹名
#define DIR_RADIO				_T("radio")
// USB、SD模块资源的相对路径文件夹名
#define DIR_MEDIA				_T("media")
// 蓝牙模块资源的相对路径文件夹名
#define DIR_BT						_T("Bluetooth")
// 设置模块资源的相对路径文件夹名
#define DIR_SETUP				_T("Setup")
// IPOD模块资源的相对路径文件夹名
#define DIR_IPOD				_T("ipod")

/////////////////////////// 字体名称宏定义 ///////////////////////////
#define FONT_MSYH_TTF							0x00				// 微软雅黑(AVCN系统默认字体)
#define FONT_QUARTZ_REGULAR_TTF		0x01				// quartz_regular字体（AVCN时钟数值显示）
//#define FONT_DS_DIGI_TTF						0x02				// DS-DIGI字体（AVCN时钟数值和收音机频点显示字体）
/////////////////////////// 配置文件名称 ///////////////////////////

// 系统配置文件名
#define FILE_SETTING_CONFIG		_T("sys_setting.ini")

// RADIO模块配置文件名
#define FILE_RADIO_CONFIG		_T("radio_setting.ini")

//SERVER模块配置文件名
#define FILE_SERVER_CONFIG		_T("server_setting.ini")

// APP 软件版本号(众大变更：功能添加：bug修改)
#define	STR_APP_VERSION_PATH 	_T("\\HZcar\\App\\config\\AppVer.ini")

///////////////////////// MX导航相关定义 ///////////////////////////
// 导航文件名
#define		NAVI_FILE_NAME				_T("MXNavi.exe")
// 导航窗口名字
#define		NAVI_WINDOW_NAME	_T("MXNavi")
// 导航文件夹名字
#define		NAVI_FOLDER_NAME		_T("MXNavi")
// 导航窗口句柄
#define		NAVI_WINDOW_HANDLE  FindWindow(NULL, _T("MXNavi"))

// 导航与中控协议
#define  WM_NAVI_MIN							RegisterWindowMessage(_T("MX_NAVI_HAS_MINIMUM"))
// 导航启动完成时发送通知的代码
#define  WM_NAVI_HAS_START				RegisterWindowMessage(_T("MX_NAVI_HAS_START"))
// 导航退出时发送通知的代码
#define  WM_NAVI_HAS_QUIT               RegisterWindowMessage(_T("MX_NAVI_HAS_QUIT"))
// wparam 为 1 时， GPS 时间同步打开; 为 0 时， GPS 时间同步关闭
#define  WM_CTL_NAVI_GPS_SET_SYSTIME RegisterWindowMessage(_T("WM_CTL_NAVI_GPS_SET_SYSTIME")) 
// wparam ：1 恢复导航设置 2 恢复导航存储 0 同时恢复导航设置和导航存储 lParam：无意义
#define  WM_CTL_NAVI_RECOVER			RegisterWindowMessage(_T("WM_CTL_NAVI_RECOVER")) 


///////////////////////// OS与中控的协议 ///////////////////////////
// iPod 设备插拔消息
#define		WM_IPOD_SIGNAL		RegisterWindowMessage(_T("WM_IPOD_SIGNAL"))	// wParam: IpodSignal  lParam:NULL

enum IpodSignal
{
	IPOD_INSERT = 0,
	IPOD_REMOVE,
	RESERVE,
};
// OS触摸屏消息
#define		WM_TOUCH_UP_OK     (WM_USER+201)

/////////////////////////// 进程 IPC ID ///////////////////////////
#define IPC_ID_MIN		0
// 服务进程 IPC ID
const unsigned char IPC_ID_MANAGE = 1;
// 主系统菜单进程 IPC ID
const unsigned char IPC_ID_MENU = 2;
// 收音机进程 IPC ID
const unsigned char IPC_ID_RADIO = 3;
// USB/SD进程 IPC ID
const unsigned char IPC_ID_USBSD = 4;
// 蓝牙进程 IPC ID
const unsigned char IPC_ID_BT = 5;
// Setup进程 IPC ID
const unsigned char IPC_ID_SETUP = 6;
// DVD进程 IPC ID
const unsigned char IPC_ID_DISC = 7;
// TPMS进程 IPC ID
const unsigned char IPC_ID_TPMS = 8;
// CMMB进程 IPC ID
const unsigned char IPC_ID_DVBT = 9;
// IPOD进程 IPC ID
const unsigned char IPC_ID_IPOD = 10;
// AVIN进程 IPC ID
const unsigned char IPC_ID_AVIN = 11;
// CAMERA进程 IPC ID
const unsigned char IPC_ID_CAMERA = 12;
// NAVI进程 IPC ID
const unsigned char IPC_ID_NAVI = 13;
// Info Bar进程 IPC ID
const unsigned char IPC_ID_INFOBAR = 14;

//在此添加进程ID
// AirInfo进程 IPC ID
const unsigned char IPC_ID_AIRINFO = 15;
//添加进程ID后修改此值
#define  IPC_ID_MAX		17



/////////////////////////// 进程主窗体名称 ///////////////////////////

// "服务" 进程名称
const TCHAR * const STR_PROCESSNAME_MANAGE = _T("Manage.exe");
// "主菜单" 进程名称
const TCHAR * const STR_PROCESSNAME_MENU = _T("menu.exe");
// "RADIO" 进程名称
const TCHAR * const STR_PROCESSNAME_RADIO = _T("radio.exe");
// "USB/SD" 进程名称
const TCHAR * const STR_PROCESSNAME_USBSD = _T("usbsd.exe");
// "IPOD" 进程名称
const TCHAR * const STR_PROCESSNAME_IPOD = _T("ipod.exe");
// "BT" 进程名称
const TCHAR * const STR_PROCESSNAME_BT = _T("bt.exe");
// "SETUP" 进程名称
const TCHAR * const STR_PROCESSNAME_SETUP = _T("setup.exe");
// "INFO BAR" 进程名称
const TCHAR * const STR_PROCESSNAME_INFOBAR = _T("infobar.exe");
// "AIR INFO" 进程名称
const TCHAR * const STR_PROCESSNAME_AIRINFO = _T("airinfo.exe");
// "DISC"进程名称
const TCHAR * const STR_PROCESSNAME_DISC = _T("disc.exe");
// "Hardware monitor" 进程名称 增加HWMONITOR.exe进程名称。
const TCHAR * const STR_PROCESSNAME_HWMONITOR = _T("hwmonitor.exe");
// "AVIN"进程名称
const TCHAR * const STR_PROCESSNAME_AVIN = _T("avin.exe");
// "BackCamera"进程名称
const TCHAR * const STR_PROCESSNAME_CAM = _T("backcamera.exe");
// "CMMB"进程名称
const TCHAR * const STR_PROCESSNAME_DTV = _T("dtv.exe");

// 诊断进程名称
const TCHAR * const STR_PROCESSNAME_DIAG = _T("diagnosticscreen.exe");
// TPMS进程名称
const TCHAR * const STR_PROCESSNAME_TPMS = _T("tpms.exe");

/*************************************** 二、进程间窗口消息定义（BEGIN）*****************************/
/*
进程外部消息       进程类型					        进程子类型
  #define      UWM_IPOD_XXXXXX              (1<<15) + （（IPC_ID_XX+4）<<8） + 0xXX
  消息ID的第16位为1表示进程间的消息，0表示进程内的消息，
  高字节的其他7个字节表示模块，即0x400+进程ID作为高字节的其他7字节，
  最低1个字节表示消息类型
*/
////////////////////服务器进程的消息////////////////////
#define		  UWM_FROM_SERVER_BASE			((1<<15) + ((IPC_ID_MANAGE+4)<<8)+0x0)
#define		  UWM_SERVER_CLOSE_VEDIO		(UWM_FROM_SERVER_BASE + 1)      // server通知进程关闭视频消息
#define		  VWM_SHOW_OVERLAY				(UWM_FROM_SERVER_BASE + 2)		// 音量条、控制按钮、popup显示叠加层消息
#define		  VWM_SERVER_CHANGE_TRACK		(UWM_FROM_SERVER_BASE + 3)		// server通知infobar切换声道消息，lParam：源ID
#define		  VWM_SERVER_KEY_ROTATE			(UWM_FROM_SERVER_BASE + 4)		// 硬按钮旋钮消息，wParam：1-音量条旋钮，2-另一个旋钮；lParam：0-正旋，1-反旋（参考下面宏定义值）
#define		  VWM_SERVER_KET_BTN					(UWM_FROM_SERVER_BASE + 5)		// 硬按钮按键消息，wParam：0-按下，1-抬起；lParam：按钮索引（参考下面宏定义值）GOTO:466
#define		  VWM_SERVER_START_NAVI			(UWM_FROM_SERVER_BASE + 6)		// 通知MAINMENU启动NAVI消息
#define		  VWM_SERVER_EJECT				      (UWM_FROM_SERVER_BASE + 7)		// 通知DISC出仓消息
#define		  VWM_SERVER_UPDATE_ITEM_STATUS (UWM_FROM_SERVER_BASE + 8)		// 通知MENU更新ITEM状态
#define		  VWM_TO_SERVER_SAVE_OK			(UWM_FROM_SERVER_BASE + 9)		// 各个模块通知SERVER保存完成，wParam表示进程ID
#define		  VWM_SERVER_CHANGE_THEME_OK	(UWM_FROM_SERVER_BASE + 10)		// 各个模块切换主题完毕通知SERVER
#define		  VWM_SERVER_CHANGE_SRC			(UWM_FROM_SERVER_BASE + 11)		// 切换AV源时通知常驻AV源行为 ( WPARAM : FALSE -> 通知上一个源要切换出去了 | TRUE -> 通知下一个源要切换进去了 ; LPARAM 忽略 )
#define		  VWM_SERVER_KEY_SEEK			(UWM_FROM_SERVER_BASE + 12)		//	Server转发Seek按钮消息，wParam:0是Seek+ 1是Seek-，lParam：0-0.8秒未满 1-0.8秒经过时 
#define		  VWM_SERVER_ST_SW_MODE			(UWM_FROM_SERVER_BASE + 13)		//	Server收到ST-SW的MODE按键时，如果AV源是Radio源则发此消息通知Radio按照FM1->FM2->AM顺序切源
#define		  VWM_SERVER_PARKING			(UWM_FROM_SERVER_BASE + 14)		//	Server发送Parking消息， lParam参数：0-Parking状态，1-非Paking状态
#define		  VWM_SERVER_INIT_PARAM			(UWM_FROM_SERVER_BASE + 15)		//	需要使用Send方式发送给模块先切换KCWindow，模块被放到前台消息，lParam表示启动参数，同IPC_U_WND_INITPARAMIPC消息
#define		  VWM_SERVER_BACK_BOX_STATUS	(UWM_FROM_SERVER_BASE + 16)		//	Server通知BackCamera后备箱状态更新,LPARAM:	1  后备箱打开; 0  后备箱关闭 
#define		  VWM_SERVER_RESUME_AV			(UWM_FROM_SERVER_BASE + 17)		//	进入或者离开Camera或者BT Call时重新播放或者暂停AV播放，lParam: 1-停止， 0-播放
#define		  VWM_SERVER_ST_SW_KET_BTN		(UWM_FROM_SERVER_BASE + 18)		//	ST-SW按键消息，wParam：KEY_DOWN-按下，KEY_UP-抬起；lParam：按钮索引（参考下面宏定义值）
#define		  VWM_SERVER_LOAD_LAST_MEM_OVER (UWM_FROM_SERVER_BASE + 19)		//	Server加载Last Memory完成，通知HWMonite取Last Memory数据.
#define		  VWM_SERVER_GET_CURRENT_AV_SRC	(UWM_FROM_SERVER_BASE + 20)		//	各个模块查询当前源，返回当前AV源（不包括NAVI）的IPC_ID，此消息只能采用Send方式发送
#define		  VWM_SERVER_SRC_CLOSE			(UWM_FROM_SERVER_BASE + 21)				//	各个模块进程退出后通知Server，wParam：IPC进程ID
#define		  VWM_SERVER_BACKCAMERA_STATUS	(UWM_FROM_SERVER_BASE + 22)		//	Server通知BackCamera状态更新,WPARAM 1 BackCamera倒车信号		LPARAM	1  进入倒车;       0  退出倒车 */
#define		  VWM_SERVER_ENTER_NAVI			(UWM_FROM_SERVER_BASE + 23)		//	TServer进入NAVI请求消息
#define		  VWM_SERVER_ENTER_TSERVER		(UWM_FROM_SERVER_BASE + 24)		//	从NAVI进入T-MIND请求消息
#define		  VWM_SERVER_ARRIVAL_USB		(UWM_FROM_SERVER_BASE + 25)		//  Server通知USB播放另外一个USB，lparam：USB端口号，最好通过共享内存取值
#define		  VWM_SERVER_ACCOFF_ON			(UWM_FROM_SERVER_BASE + 26)		//	通知Server发送ACC OFF-ON指令
#define		  VWM_SERVER_SAVE_LASTMEMORY_REQ (UWM_FROM_SERVER_BASE + 27)	//	其他模块保存Last Memory请求，lParam:IPC_ID区分哪个模块的请求 WParam 区分是通知Server保存Bu瞬断数据还是其他数据 1:为BU瞬断 0为需要差分保存的数据

#define		  VWM_SERVER_SET_DIVXCODE		(UWM_FROM_SERVER_BASE + 31)		//	通知Setup有DicxCode设置过 lParam参数：0-注销码，1-注册码
#define		  VWM_SERVER_AMS_CLICK			(UWM_FROM_SERVER_BASE + 32)		//	通知收音机AMS按钮被按下
#define		  VWM_SERVER_AM_CLICK			(UWM_FROM_SERVER_BASE + 33)		//	通知收音机AM按钮被按下
#define		  VWM_SERVER_FM_CLICK			(UWM_FROM_SERVER_BASE + 34)		//	通知收音机FM按钮被按下
#define		  VWM_SERVER_USBSD_CHANGE		(UWM_FROM_SERVER_BASE + 35)		//	USB/SD状态改变及时通知USB进程：WPARAM 1:USB1,2:USB2 3:SD		LPARAM	1  插入       0  拔出
#define	      VWM_SERVER_NAVI_SAVE_LAST_MEMORY_SUCCESS	(UWM_FROM_SERVER_BASE + 36)	//NAVI保存LAst Memory成功通知Server
#define		  VWM_SERVER_IPOD_REMOVECOMPLETE		(UWM_FROM_SERVER_BASE + 37)	//	Server通知IPOD设备已经拔出

#define		  VWM_SERVER_CHANGE_MODE				(UWM_FROM_SERVER_BASE + 40)		//	通知进程改变Mode  wParam： Radio（0：AM 1：FM） USB（0：Audio 1：Video）
#define		  VWM_TO_SERVER_CANCAL_MUTE			(UWM_FROM_SERVER_BASE + 41)				// 通知Server向MCU发送取消Mute操作指令
#define		  VWM_SERVER_UPDATE_TIME					(UWM_FROM_SERVER_BASE + 42)				// 通知进程更新当前时间
#define		  VWM_SERVER_LANG_SW							(UWM_FROM_SERVER_BASE + 43)				// 通知进行语言切换wParam：0-中文 1-英文 lParam ：无意义
#define		  VWM_SERVER_BEEP									(UWM_FROM_SERVER_BASE + 44)				// BEEP 发声
#define		  VWM_SERVER_BEEP_SW							(UWM_FROM_SERVER_BASE + 45)				// BEEP 使能开关
#define		  VWM_SERVER_PEPS_ALARM						(UWM_FROM_SERVER_BASE + 46)				// PEPS 警报 wParam：0-中文 1-英文
#define		  VWM_SERVER_UPDATE_TEMPERATURE	(UWM_FROM_SERVER_BASE + 47)				// 通知进程更新当前温度

#define		  VWM_TO_SERVER_ENTER_PLAY_SRC		(UWM_FROM_SERVER_BASE + 50)		//	通知管理程序进入播放源画面
#define		  VWM_TO_SERVER_ENTER_DIRECTION_SWITCH (UWM_FROM_SERVER_BASE + 51)		//	通知管理程序进入播放源画面
// TopBar的消息
#define		  UWM_TOPBAR_HOME						(UWM_FROM_SERVER_BASE + 80)			// 返回home
#define		  UWM_TOPBAR_BACK						(UWM_FROM_SERVER_BASE + 81)			// 返回上一级
#define		  UWM_BACK_SRC								(UWM_FROM_SERVER_BASE + 82)			// 返回上一个源

///////////////////MENU进程的消息////////////////////
#define		  UWM_FROM_MENU_BASE			((1<<15) + ((IPC_ID_MENU+4)<<8)+0x0)
#define		  UWM_FROM_MENU_START_OK		(UWM_FROM_MENU_BASE + 1)		// Menu启动OK，（临时使用）
#define		  UWM_FROM_MENU_START_DIAG		(UWM_FROM_MENU_BASE + 2)		//	Menu启动诊断画面通知Server
#define		  UWM_FROM_MENU_POWER_OFF		(UWM_FROM_MENU_BASE + 3)		//	Menu退出诊断画面通知Server掉电ACC-OFF
#define		  UWM_TO_MENU_UPDATE_DLG			(UWM_FROM_MENU_BASE + 4)		//	Server通知MENU当前画面改变lParam：0 MianMenu 1 ：MediaMenu
#define		  UWM_MENU_SHOW_DIALOG			(UWM_FROM_MENU_BASE + 5)		//	lParam:MENU 启动模式参数定义

///////////////////RADIO进程的消息////////////////////
#define		  UWM_FROM_RADIO_BASE			((1<<15) + ((IPC_ID_RADIO+4)<<8)+0x0)
#define		  VWM_RADIO_MODE_NEXT			(UWM_FROM_RADIO_BASE + 1)		//	Radio模块处于AM模式，收到ST-SW的MODE按键切源后通知Server切换到USB源
#define		  VWM_RADIO_AUTO_SCAN			(UWM_FROM_RADIO_BASE + 2)		//	自动搜台
#define		  VWM_RADIO_AVAILABLE_CHANNEL  (UWM_FROM_RADIO_BASE + 3)  //是否信号的电台,wParam 0:无 1：有  lParam:当前波段 0:AM  1:FM
#define		  VWM_RADIO_AREA_CHANGE	  (UWM_FROM_RADIO_BASE + 4)  // 收音机区域改变



///////////////////USBSD进程的消息////////////////////
#define		  UWM_FROM_USBSD_BASE			((1<<15) + ((IPC_ID_USBSD+4)<<8)+0x0)
#define		  VWM_USBSD_EXE_EXIT					(UWM_FROM_USBSD_BASE+0x01)		// 退出回到Radio

///////////////////BT进程的消息////////////////////
#define		  UWM_FROM_BT_BASE				((1<<15) + ((IPC_ID_BT+4)<<8)+0x0)
#define		  VWM_BT_HFP_STATE					(UWM_FROM_BT_BASE + 1)			// wParam参数见下方330: BT_HFP_STATE 定义
#define		  VWM_BT_OPEN_STATE              (UWM_FROM_BT_BASE + 2)        //蓝牙开关 wParam： 0 关闭 1 打开
#define		  VWM_BT_ENTER_MUSICDLG		(UWM_FROM_BT_BASE + 3)			//BT进入蓝牙界面
#define		  VWM_BT_PHONE_STATE            (UWM_FROM_BT_BASE + 4)			//wParam:0 手机已连接 1手机未连接  其他 未知状态
#define		  VWM_BT_MUSICDLG_TIMEOUT		(UWM_FROM_BT_BASE + 5)	//自动连接超时退出蓝牙音乐
#define		  VWM_TO_BT_RESET				 	(UWM_FROM_BT_BASE + 6)			//通知蓝牙恢复出场设置
#define      VWM_TO_BT_A2DP_DISCONNECT   (UWM_FROM_BT_BASE + 7)      //蓝牙断A2DP  wparam: 1 A2DP断开  0 A2DP连接 

///////////////////SETUP进程的消息////////////////////
#define		  UWM_FROM_SETUP_BASE			((1<<15) + ((IPC_ID_SETUP+4)<<8)+0x0)
#define		  VWM_SETUP_DONE				(UWM_FROM_SETUP_BASE + 1)	//	SETUP通知SERVER需要返回LAST MODEL
#define		  VWM_SETUP_CHANGE_THEME		(UWM_FROM_SETUP_BASE + 2)	//	SETUP切换主题消息，lParam参数表示主题号
#define		  VWM_SETUP_ENABLE_BACK_PLAY	(UWM_FROM_SETUP_BASE + 3)	//	SETUP后台播放设置消息，lParam：0禁用，1：启用后台播放
#define		  VWM_SETUP_ENABLE_BEEP			(UWM_FROM_SETUP_BASE + 4)	//	SETUP设置启用BEEP音消息，lParam:0 禁用，1：启用
#define		  VWM_SETUP_ENABLE_CAMERA		(UWM_FROM_SETUP_BASE + 5)	//	SETUP设置启用倒车摄像头消息，lParam:0 禁用，1：启用
#define		  VWM_SETUP_ENABLE_PLAY_RULE	(UWM_FROM_SETUP_BASE + 6)	//	SETUP设置启用走行规则消息，lParam:0 禁用，1：启用
#define       VWM_SETUP_SET_BRT_CONTRAST    (UWM_FROM_SETUP_BASE + 7)   //	SETUP设置LCD亮度对比度消息 wParam参数：1-亮度，2-对比度； lParam参数：1~15代表level值
#define		  VWM_SETUP_LOADFACTORY			(UWM_FROM_SETUP_BASE + 8)	//	恢复出产设置
#define		  VWM_SETUP_DISPLAY_USB_VIDEO	(UWM_FROM_SETUP_BASE + 9)	//  通知USB在Display画面下打开视频， lParam参数：1--打开，0--关闭
#define		  VWM_SETUP_CHANGE_BT_SETING		(UWM_FROM_SETUP_BASE + 10)		//	通知进程改变bt.EXE setup画面bt设置发生变化，到LastMemory获取设置信息
#define		  VWM_SETUP_UPDATE_TIME				(UWM_FROM_SETUP_BASE + 11)			// 通知server更换当前系统时间
#define		  VWM_SETUP_SCREEN_OFF				(UWM_FROM_MENU_BASE + 12)		//	关屏通知Manage wParam : 0-关屏 1-开屏  lParam:NULL



///////////////////DISC进程的消息////////////////////
#define		  UWM_FROM_DISC_BASE			((1<<15) + ((IPC_ID_DISC+4)<<8)+0x0)

///////////////////TPMS进程的消息////////////////////
#define		  UWM_FROM_TPMS_BASE			((1<<15) + ((IPC_ID_TPMS+4)<<8)+0x0)
#define		  VWM_TPMS_DEVICE_STATUS		(UWM_FROM_TPMS_BASE + 1)	//	TPMS通知状态变化，lParam：0-TPMS正常；1-TPMS异常
#define		  VWM_TPMS_RETURN_LAST_SCREEN	(UWM_FROM_TPMS_BASE + 2)	//	通知Server从TPMS界面返回到上一个画面消息
#define		  VWM_TPMS_ENTER_SETUP			(UWM_FROM_TPMS_BASE + 3)	//	通知进入TPMS的设置画面
#define		  VWM_TPMS_MATCH_START			(UWM_FROM_TPMS_BASE + 4)	//	通知TPMS模块发送轮胎匹配命令
#define		  VWM_TPMS_MATCH_DATA_A			(UWM_FROM_TPMS_BASE + 5)	//	TPMS轮胎匹配成功后，给诊断画面的数据（A部分）
#define		  VWM_TPMS_MATCH_DATA_B			(UWM_FROM_TPMS_BASE + 6)	//	TPMS轮胎匹配成功后，给诊断画面的数据（B部分）
#define		  VWM_TPMS_EXIST				(UWM_FROM_TPMS_BASE + 7)	//  通知MainMenu TPMS模块存在
#define		  VWM_TPMS_MATCH_TIMEOUT		(UWM_FROM_TPMS_BASE + 8)	//  TPMS模块通知诊断画面轮胎匹配超时

///////////////////DVBT进程的消息////////////////////
#define		  UWM_FROM_DVBT_BASE			((1<<15) + ((IPC_ID_DVBT+4)<<8)+0x0)

///////////////////IPOD进程的消息////////////////////
#define		  UWM_FROM_IPOD_BASE			((1<<15) + ((IPC_ID_IPOD+4)<<8)+0x0)
#define		  VWM_IPOD_DEVICE_STATUS		(UWM_FROM_IPOD_BASE + 1)		//	iPod插入拔出状态改变消息, wParam： 0-系统运行过程中状态，1-系统启动时状态；lParam参数：0-拔出，1-插入

///////////////////AUXIN进程的消息////////////////////
#define		  UWM_FROM_AUXIN_BASE			((1<<15) + ((IPC_ID_AVIN+4)<<8)+0x0)


///////////////////CAMERA进程的消息////////////////////
#define		  UWM_FROM_CAMERA_BASE			((1<<15) + ((IPC_ID_CAMERA+4)<<8)+0x0)

///////////////////NAVI进程的消息////////////////////
#define		  UWM_FROM_NAVI_BASE			((1<<15) + ((IPC_ID_NAVI+4)<<8)+0x0)
#define		  VWM_RETURN_MAINMENU			(UWM_FROM_NAVI_BASE + 1)		// 从NAVI界面返回到主界面消息
#define		  VWM_RETURN_SETUP				(UWM_FROM_NAVI_BASE + 2)		// 从NAVI界面返回到系统设置界面消息


/*************************************** 面板按键消息宏定义**********************************/

//VWM_SHOW_OVERLAY消息wParam参数表示哪一层overlay
#define  OVERLAY_BUTTON			0x00			// 控制按钮叠加层
#define  OVERLAY_AIRINFO		0x01			// 空调信息叠加层
#define  OVERLAY_VOLUME			0x02			// 音量条叠加层

/*************************************** 枚举定义 ***************************************/

typedef enum BT_HFP_STATE
{
	STATE_BT_HFP_READY									= 0,	// 就绪状态(未连接状态)
	STATE_BT_HFP_CONNECTING						= 1,	// 正在连接状态
	STATE_BT_HFP_CONNECTED						= 2,	// 已经连接状态
	STATE_BT_HFP_CALLINCOMING					= 3,	// 来电状态
	STATE_BT_HFP_CALLOUTGOING					= 4,	// 去电状态
	STATE_BT_HFP_CALLACTIVE							= 5,	// 呼叫建立(通话中状态)
	STATE_BT_HFP_THREEPARTY			                = 6,  // 三方通话状态
	STATE_BT_HFP_CALLSTOP							    = 7, // 通话结束
	STATE_BT_HFP_DISCONNECTING                 = 8,  // 断开连接状态
}BT_HFP_STATE;

/*************************************** 二、进程间窗口消息定义（END）*****************************/


/*************************************** 三、进程启动参数宏定义 （BEGIN）**************************/

///////////// BU-ON/ACC-ON 启动参数定义 /////////////
#define START_IGNORE	0		//	忽略，不是第一次启动程序
#define START_BU_ON		1		//	BU上电
#define START_ACC_ON	2		//	ACC上电

#define PARAM_BUACC_CMD(nParam)			((nParam & 0xC0000000)>>30)

///////////// 显示/隐藏 启动参数定义 /////////////
#define PARAM_SHOW_CMD(nParam)			((0x000E0000 == ( nParam & 0x000E0000 ) ) ? SW_HIDE : SW_SHOW )


///////////// RADIO 启动模式参数定义 /////////////
#define START_RADIO_BAND_NULL	0
#define START_RADIO_BAND_AM		1
#define START_RADIO_BAND_FM		2

#define PARAM_RADIO_BAND_CMD(nParam)	((nParam & 0x38000000)>>27)

///////////// BT 启动模式参数定义 /////////////
#define START_BT_DLG_NULL			0
#define START_BT_DLG_DIAL				1
#define START_BT_DLG_PHONE_BOOK		2
#define START_BT_DLG_HISTORY		3
#define START_BT_DLG_AUDIO			4
#define START_BT_DLG_CONNECT		5
#define START_BT_DLG_MIRRORLINK	6

#define PARAM_BT_DLG_CMD(nParam)	(nParam & 0x000000FF)

///////////// media 启动模式参数定义 /////////////
#define START_MEDIA_DLG_NULL			0
#define START_MEDIA_DLG_AUDIO		1
#define START_MEDIA_DLG_VIDEO			2
#define START_MEDIA_DLG_PICTURE		3
#define START_MEDIA_DLG_EBOOK		4
#define START_MEDIA_DLG_MENU			5

#define PARAM_MEDIA_DLG_CMD(nParam)  (nParam & 0x000000FF)


/*************************************** 三、进程启动参数宏定义 （END）**************************/


///////////// IPOD和USB声道互斥名称宏定义 ////////
#define _MUTEX_AUDIO_USB_CHANNEL_NAME_	_T("_audio_usb_channel_")		


/*************************************** 视频背景色宏定义**********************************/
#define VIDEO_BAR_BG_ALPHA		0
#define VIDEO_BAR_BG_COLOR_R	0x18/*20*/
#define VIDEO_BAR_BG_COLOR_G	0x08/*10*/
#define VIDEO_BAR_BG_COLOR_B	0x18/*30*/

//  添加车型类型枚举
enum FT_CAR_TYPE
{
	CAR_TYPE_INVALID = -1,			// 非法类型
	CAR_TYPE_NORMAL,				// 普通车型(785平台)
	CAR_TYPE_ZOTYE,					// 众泰T22
	CAR_TYPE_LEXUS,					// 雷克萨斯
	CAR_TYPE_RAV4,
	CAR_TYPE_REZI,						// 锐志
	CAR_TYPE_HIGHLANDER,			// 汉兰达
	CAR_TYPE_SOC,						// 斯巴鲁
};
// 

/*************************************** 面板按键消息宏定义**********************************/
// 一般车型按键类型
enum eKeyTypeNomal
{
	eKEY_ACCOFF						= 0x00,			// 
	eKEY_UP								= 0x01,			// 上一曲键 
	eKEY_DOWN							= 0x02,		// 下一曲键	
	eKEY_MENU							= 0x03,			// 回到主界面键
	eKEY_RADIO							= 0x04,		// 收音机键
	eKEY_VOL								= 0x05,		// 声音键(最大调节幅度 40，0 表示静音	)
	eKEY_MODE							= 0x07,			// 模式切换(此按键控制收音机， MP3等界面的切换)
	eKEY_TFT								= 0x08,			// 控制背光(小灯信号)
	eKEY_MEDIA							= 0x09,
	eKEY_BACK							= 0x0B,			// 回上一级菜单
	eKEY_OFF_HOOK					= 0x0C,			//	蓝牙电话接听键
	eKEY_ON_HOOK					= 0x0D,			//	蓝牙电话挂断键
	//eKEY_FF								= 0x0E,			// 快进键
	//eKEY_FB								= 0x0F,			// 快退键
	eKEY_PLAY_CONTROL			= 0x0E,				// 播放控制(0x00:正常播放 0x01:快进 0x02:快退)
	eKEY_SCAN							= 0x10,			// Scan 键 
	eKEY_CALL							= 0x11,			// 
	eKEY_NAVI							= 0x15,			// 导航键
	eKEY_SETUP							= 0x16,			// 设置键 
	eKEY_PWROFF						= 0x17,			// 休眠键 
	eKEY_PWRON						= 0x18,			// 开机键
	eKEY_ACCON						= 0x1A,			// 开机
	eKEY_DIRECTION					= 0x2C,			// 方向键(左上、左下、右上、右下)
	eKEY_ROTATE_SMART			= 0x2D,			// 智能旋钮
};

// 注册表ACC状态宏定义
#define  ACC_ON							0x01
#define  ACC_OFF						0x02

// 注册表PWR状态宏定义
#define  PWR_ON						0x01
#define  PWR_OFF						0x02

//旋钮消息，以下是两个旋钮的消息的定义
#define  KEY_ROTATE_VOLUME		0x00				// 音量条旋钮
#define  KEY_ROTATE_SMART			0x01					// 另一个旋钮(Smart)

// 旋钮旋转方向及状态
#define  KEY_SPIN_LEFT					0x00				// 左旋(逆时针)
#define  KEY_SPIN_RIGHT				0x01				// 右旋(顺时针)
#define  KEY_SPIN_DOWN				0x02				// 旋钮按下
#define  KEY_SPIN_UP						0x03				// 旋钮抬起
#define  KEY_SPIN_LONG_PRESS    0x04

// 方向键方位
#define  KEY_DIRECTION_TOPLEFT				0x01			// 左上按键
#define  KEY_DIRECTION_BOTTOMLEFT		0x02			// 左下按键
#define  KEY_DIRECTION_TOPRIGHT			0x03			// 右上按键
#define  KEY_DIRECTION_BOTTOMRIGHT	0x04			// 右下按键

//硬按钮消息类型，包括按下和抬起
#define KEY_DOWN					0x00				// 硬按钮按下
#define KEY_UP						0x01				// 硬按钮抬起
#define KEY_LONG_PRESS		0x02				// 硬按钮长按

/*************************************** 结构体定义 ***************************************/

#endif /*__DEFINE_PUBLICE_H__*/