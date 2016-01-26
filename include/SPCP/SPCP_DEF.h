
#pragma once

/*通信失败标示*/
#define COMM_RESULT_ERR		0xFF
/*通信成功标示*/
#define COMM_RESULT_SUC 0

/////////////////////////// 枚举类型 ///////////////////////////

/*串口ID*/
typedef enum 
{
	COM_0				= 0,				// COM0
	COM_1				,					// COM1
	COM_2				,					// COM2
	COM_3				,					// COM3
	COM_14			= 0x0E,			// COM14
}eComID;

/*数据位*/
typedef enum
{
	BITS_5 = 5,				// 5位
	BITS_6,					// 6位
	BITS_7,					// 7位
	BITS_8					// 8位
}eBits;

/*奇偶效验*/
typedef enum
{
	PAR_NONE = 0,			// 无
	PAR_ODD,				// 奇效验
	PAR_EVEN,				// 偶效验
	PAR_MARK,				// 标记
	PAR_SPACE				// 空格
}eParity;

/*停止位*/
typedef enum
{
	STOP_1 = 0,				// 1位
	STOP_15,				// 1.5位
	STOP_2					// 2位
}eStopBit;

/*发送、接收数据结构体*/
typedef struct tagCom_Protocol_Head
{
	UINT8 nRet; 					/*返回结果*/
	UINT8 nCodeType;		/*种别*/
}COMRECVHEAD,*LPCOMRECVHEAD;


// CodeType类型定义
enum eCodeType
{
	// 785-->MCU数据
	e785CODETYPE_MTR785				= 0x00,					// Mstar785界面
	e785CODETYPE_RADIO					= 0x01,					// 收音机界面
	e785CODETYPE_BTPHONE				= 0x02,					// 蓝牙电话界面
	e785CODETYPE_SOUND					= 0x03,					// 声音界面
	e785CODETYPE_BACKLIGHT			= 0x04,					// 背光界面
	e785CODETYPE_WHEEL					= 0x05,					// 盘控界面
	e785CODETYPE_TV							= 0x06,					// 电视界面
	e785CODETYPE_MENU					= 0x07,					// 返回主菜单 
	e785CODETYPE_VER						= 0x08,					// 查询程序版本 
	e785CODETYPE_SKIN						= 0x09,					// 更换皮肤界面 
	e785CODETYPE_TPMS					= 0x0A,					// 胎压检测界面
	e785CODETYPE_INITSETUP			= 0x0B,					// 初始化设置界面
	e785CODETYPE_TIMESETUP			= 0x0C,					// 时间设置界面
	e785CODETYPE_IVI						= 0x0D,					// IVI 界面 
	e785CODETYPE_NAVI						= 0x0E,					// 导航界面 
	e785CODETYPE_CAMRY					= 0x10,					// CAMRY 原车信息 
	e785CODETYPE_BACKCAR				= 0x11,					// 倒车界面
	e785CODETYPE_ZOTYE						= 0x13,					// 众泰原车设置

	// MCU-->785数据
	eMCUCODETYPE_HARDWAREKEY		= 0x80,					// 按键信息 
	eMCUCODETYPE_TPMS					= 0x81,					// 胎压状态反馈 
	eMCUCODETYPE_RADIO					= 0x82,					// 收音机状态反馈
	eMCUCODETYPE_BT							= 0x83,					// 蓝牙状态反馈 
	eMCUCODETYPE_OTHER					= 0x84,					// 其它状态反馈 
	eMCUCODETYPE_AIRCON				= 0x85,					// 原车空调数据信息 
	eMCUCODETYPE_CAMR					= 0x86,					// CAMR 原车信息  
	eMCUCODETYPE_ZOTYE					= 0x87,					// 众泰原车信息 
};




