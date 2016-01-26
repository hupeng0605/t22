
#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) ||  defined(_WIN32_WCE) || defined(WINCE)
#	ifdef UTILITY_EXPROT
#		define UTILITY_API	__declspec(dllexport)
#	else
#		define UTILITY_API	__declspec(dllimport)
#	endif
#else
#	ifdef UTILITY_EXPROT
#		define UTILITY_API	
#	else
#		define UTILITY_API	extern
#	endif
#endif

#ifdef __cplusplus
extern "C" {
	namespace UTILITY {
#endif

		/*--------------------------------------------- 系统配置 ---------------------------------------------*/
		/*************************************** 导出函数 ***************************************/


		/*--------------------------------------------- 系统配置 ---------------------------------------------*/


		/*--------------------------------------------- SERVER配置 ------------------------------------------*/
#pragma pack(push,1)
		//SERVER设置
		typedef struct _tagServerSetting
		{
			unsigned short nStartSrc[2];						//	保存两份LAST MODE
			unsigned short uPwrOff;								//	记载Power状态
		}SERVERSETTING, *LPSERVERSETTING;
#pragma pack(pop)

		/*--------------------------------------------- SETUP配置 ---------------------------------------------*/

		typedef struct _tagSETUPSETTING
		{
			unsigned char	c12Or24;						// 0 : 12h 1:24h
			unsigned char	cThemeMode;				//主题模式
			unsigned char	cBeep;							//BEEP音开关
			//unsigned char	cWideScreen;			//视频显示比率，0-16:9,1-4:3
			unsigned char	cGpsAnys;					//GPS，0:ON,1:OFF
			unsigned char	cCamera;						// 摄像头开关
			unsigned char	cOperationStriction;		//MCU上报车速信息(0:禁止播放 1:允许播放)
			unsigned char   cIsSound;					// 0 : setup 模块 1：音效设置画面
			unsigned char   cLang;							// 0 : 中文 1：英文
			unsigned char	szBkgndPath[256];
		}SETUPSETTING, *LPSETUPSETTING;

		/*-------------------------------------- SOUND声音相关配置 ---------------------------------------*/
		typedef struct _tagSOUNDSETTING
		{
			unsigned char	uSoundVol;								// 音量大小(0：静音  1-40 级音量可调)
			unsigned char	uBright;									// 背光调节有(1- 10级)
			unsigned char	uDayNight;								// 0：白天模式  1：夜晚模式 2 : 自动模式
			unsigned char	uSoundHigh;								// 高音
			unsigned char	uSoundLow;							 	// 低音
			unsigned char  uEQBal;										// 左右平衡
			unsigned char  uEQFad;									// 前后衰减
			unsigned char  uSoundEffects;							// 音效模式
			unsigned char	uKeyTone;								// 按键音开关值
			unsigned char	uSoundSw;								// 响度开关( 0：OFF（关） 1：ON（开）)
			unsigned char	uTemperature;							// 温度显示 1 : 摄氏温度 2：华氏温度
			unsigned char  uAVC;										// AVC 功能
			unsigned short usMcuVer;								// 程序版本BCD码表示 四位数.如 1111 表示 V11.11
			unsigned char  uRadioArea;								// Radio 区域选择
			unsigned char  uSpeedLimit;							// 车速限制
			unsigned char  uOutdoorTemperature;			// 室外温度
			unsigned char  uAutoAir;									// 自动空调(该标识用来判断外部温度是否显示)
		}SOUNDSETTING, *LPSOUNDSETTING;

		/*--------------------------------------------- RADIO配置 ---------------------------------------------*/

		/*************************************** 结构定义 ***************************************/
//#pragma pack(push, 1)
		// RADIO设置
		typedef struct tagRadioSetting
		{
			unsigned short uLastAM;						// 最后一次的AM频道
			unsigned short uLastFM;						// 最后一次的FM频道
			unsigned short uAMPreset[20];			// AM波段 20个预设置频道
			unsigned short uFMPreset[20];			// FM波段 20个预设置频道
			unsigned char uLastBand;					// 最后一次的波段(AM/FM)
		}RADIOSETTING,*LPRADIOSETTING;
//#pragma pack(pop)

		/*--------------------------------------------- IPOD配置 ---------------------------------------------*/
		//IPOD设置
		typedef struct _tagST_IPD_LASTMEM
		{	
			BYTE mmpconbk[552];              /* iPod接続情報                    */	
			BYTE mmpstsbk[112];              /* MMPステータス情報               */	
			BYTE usbconbk[16];               /* USB接続情報                     */	
		} ST_IPD_LASTMEM;	

		/*--------------------------------------------- TPMS配置 ---------------------------------------------*/
		//TPMS由模块自己保存
		//typedef struct _tagTPMSSETTING
		//{
		//	unsigned char	uMaxPressure;						//	
		//	unsigned char	uMinPressure;						//
		//	unsigned char	uMaxTemperature;					//
		//	unsigned char	uTemperatureUnit;					//
		//	unsigned char	uPressureUnit;						//
		//}TPMSSETTING;


		/*--------------------------------------------- BT配置 ---------------------------------------------*/	
		#pragma pack(push,1)
		typedef struct _tagBTSETTING
		{
			unsigned short	uBtPinCode;								//	预留蓝牙PIN码，以备后期其他车型扩展
			unsigned char	uBtConnctStatus;						//	蓝牙连接状态
			unsigned char	uBtAutoReceive;						//	蓝牙自动接听
			unsigned char	uBtAutoConnect;						//	蓝牙自动连接
			unsigned char	uBtOnOff;									//	蓝牙开关状态
		}BTSETTING, *LPBTSETTING;
		#pragma pack(pop)


		/*--------------------------------------------- USBSD配置 ---------------------------------------------*/
		typedef struct _tagUSBSDMODESETTING			//SD或者USB的模式：Audio/Video/Picture/Ebook
		{
			unsigned char	uModeSet;				
		}USBSDMODESETTING, *LPUSBSDMODESETTING;

		typedef struct _tagUSBSDAUDIOSETTING		//SD或者USB的Audio配置
		{
			unsigned short	nAudioFileIndex;						//	上一次音频播放的路径的索引
			unsigned short  nAudioFileTotal;						//	上一次音频播放的音频文件总数
			unsigned int		nAudioPlayTime;						//	上一次音频播放的时间位置
			unsigned char	uAudioRandom;						//	上一次音频的随机模式
			unsigned char	uAudioRepeat;							//	上一次音频的循环模式
		}USBSDAUDIOSETTING, *LPUSBSDAUDIOSETTING;		

		typedef struct _tagUSBSDVEDIOSETTING		//SD或者USB的Vedio配置
		{
			unsigned short		nVideoFileIndex;					//	上一次视频播放的文件路径的索引
			unsigned short		nVideoFileTotal;					//	上一次视频播放的视频文件总数
			unsigned int			nVedioPlayTime;						//	上一次视频播放的时间位置
			unsigned char		uVedioRepeat;						//	上一次视频的循环模式
		}USBSDVEDIOSETTING, *LPUSBSDVEDIOSETTING;

		typedef struct _tagUSBSDPICTURESETTING		//SD或者USB的Picture配置
		{
			unsigned short		nPicFileIndex;								//	上一次图片播放的文件路径的索引
			unsigned short		nPicFileTotal;								//	上一次图片播放的图片文件总数
			unsigned char		uSDPictureSlidePlay;						//	上一次图片浏览的模式，是否是自动浏览
			unsigned char		uSDPictureSlideTime;					//	上一次图片自动浏览的时间间隔
			unsigned char		uSDPictureDisplayRatio;				//	上一次图片放大的倍数
		}USBSDPICTURESETTING, *LPUSBSDPICTURESETTING;

		typedef struct _tagUSBSDEBOOKSETTING		//SD或者USB的Picture配置
		{
			unsigned short		nEbookFileIndex;								//	上一次电子书播放的文件路径的索引
			unsigned short		nEbookFileTotal;								//	上一次电子书播放的文件总数
			unsigned int			nEbookPlayAddr;								//	上一次电子书播放的文件位置
		}USBSDEBOOKSETTING, *LPUSBSDEBOOKSETTING;

		typedef struct _tagUSBFlag		//	USB标示符，包括usb的全球唯一id和USB已使用空间
		{
			ULONGLONG lUsbID;					//	usb的全球唯一id
			ULONGLONG lUsbUsdeSize;				//	Usb已使用大小
		}USBFLAG, *LPUSBFLAG;


		/*--------------------------------------------- Last Memory配置 ---------------------------------------*/
#define  LAST_MEMORY_DATA_HEAD_SIZE				154
#define  NAVI_LAST_MEMORY_SIZE							80

		/*************************************** 导出类 ***************************************/
		class UTILITY_API KCLastMemory
		{
		public:
			virtual ~KCLastMemory();

			static KCLastMemory*	GetInstance();
			static void				DeleteInstance();
			
			//读取所有的LastMemory，暂时从配置文件读取
			void ReadLastMemory();
			//保存所有的LastMemory，暂时保存到配置文件
			void SaveLastMemory();
			//恢复出产设置数据
			void LoadFactory(int nOffset = 0);
			//删除数据，恢复出产设置
			void ClearData();

			//获取、设置Server的LastMemory
			void GetServerMemory(SERVERSETTING& Setting);
			void SetServerMemory(SERVERSETTING& Setting);

			//获取、设置Radio的LastMemory
			void GetRadioMemory(RADIOSETTING& Setting);
			void SetRadioMemory(RADIOSETTING& Setting);
			static void GetRadioMemoryDefault(RADIOSETTING& Setting);

			//获取、设置BT的LastMemory
			void GetBTMemory(BTSETTING& Setting);
			void SetBTMemory(BTSETTING& Setting);

			//获取、设置SETUP的LastMemory
			void GetSetupMemory(SETUPSETTING& Setting);
			void SetSetupMemory(SETUPSETTING& Setting);
			static void GetSetupMemoryDefault(SETUPSETTING& Setting);

			//获取、设置SD的模式的LastMemory
			void GetSDModeMemory(USBSDMODESETTING& Setting);
			void SetSDModeMemory(USBSDMODESETTING& Setting);
			//获取、设置USB的模式的LastMemory
			void GetUSBModeMemory(USBSDMODESETTING& Setting);
			void SetUSBModeMemory(USBSDMODESETTING& Setting);
			//获取、设置SD的Audio的LastMemory
			void GetSDAudioMemory(USBSDAUDIOSETTING& Setting);
			void SetSDAudioMemory(USBSDAUDIOSETTING& Setting);
			//获取、设置USB的Audio的LastMemory
			void GetUSBAudioMemory(USBSDAUDIOSETTING& Setting);
			void SetUSBAudioMemory(USBSDAUDIOSETTING& Setting);
			//获取、设置SD的Vedio的LastMemory
			void GetSDVedioMemory(USBSDVEDIOSETTING& Setting);
			void SetSDVedioMemory(USBSDVEDIOSETTING& Setting);
			//获取、设置USB的Vedio的LastMemory
			void GetUSBVedioMemory(USBSDVEDIOSETTING& Setting);
			void SetUSBVedioMemory(USBSDVEDIOSETTING& Setting);
			//获取、设置SD的Picture的LastMemory
			void GetSDPictureMemory(USBSDPICTURESETTING& Setting);
			void SetSDPictureMemory(USBSDPICTURESETTING& Setting);
			//获取、设置USB的Picture的LastMemory
			void GetUSBPictureMemory(USBSDPICTURESETTING& Setting);
			void SetUSBPictureMemory(USBSDPICTURESETTING& Setting);
			//获取、设置SD的EBOOK的LastMemory
			void GetSDeBookMemory(USBSDEBOOKSETTING& Setting);
			void SetSDeBookMemory(USBSDEBOOKSETTING& Setting);
			//获取、设置USB的EBOOK的LastMemory
			void GetUSBeBookMemory(USBSDEBOOKSETTING& Setting);
			void SetUSBeBookMemory(USBSDEBOOKSETTING& Setting);

			//获取、设置SOUND的LastMemory
			void GetSoundMemory(SOUNDSETTING& Setting);
			void SetSoundMemory(SOUNDSETTING& Setting);
			//获取、设置IPOD的Last Memory
			void GetIpodMemory(ST_IPD_LASTMEM& Setting);
			void SetIpodMemory(ST_IPD_LASTMEM& Setting);

			//	获取共享内存的大小
			int	GetLastMemorySize(int nHeadSize = LAST_MEMORY_DATA_HEAD_SIZE);
			//	将Last Memory写入共享内存
			void GetLastMemory(void* pMem, int nHeadSize = LAST_MEMORY_DATA_HEAD_SIZE);
			// 将Last Memory写入共享内存的头部
			void GetLastMemoryHead(void* pMem, int nHeadSize = LAST_MEMORY_DATA_HEAD_SIZE);

			void GetLastMemoryNavi(void* pMem, int nNaviMemorySize = NAVI_LAST_MEMORY_SIZE);
			//	保存Last Memory
			bool SaveLastMemory(int nOffset, int nDataId, int nSize = -1);
			// BU瞬断时保存Last Memory接口
			bool SaveLastMemoryBuOff(int nSize = LAST_MEMORY_DATA_HEAD_SIZE, BOOL bBu = FALSE);
			//	设置保存Last Memory回调
			void SetCallBack(BOOL (*callback)(const void*, UINT32, UINT8 uDataId));
			//  设置BU瞬断保存Last Memory回调
			void SetBuSaveLastMemoryCallBack(BOOL (*callback)(const void* pData, const void* pData2, UINT32 uLen,UINT32 uLen2, BOOL bBu));
			//	初始化中间件Last Memory回调
			void SetInitMWCallBack(BOOL (*callback)(UINT8 *last_memory, UINT32 uLen));
			//	初始化中间
			void InitMW(int nHeadSize = LAST_MEMORY_DATA_HEAD_SIZE);

			//获取、设置USBFlag的Last Memory
			void GetUSBFlagMemory(USBFLAG& usbFlag);
			void SetUSBFlagMemory(USBFLAG& usbFlag);

			//获取、设置SDFlag的Last Memory
			void GetSDFlagMemory(ULONGLONG& lSize);
			void SetSDFlagMemory(ULONGLONG& lSize);
		private:
			KCLastMemory();
			bool utility_lastMemory_InitShareMemory(void);
			void utility_lastMemory_UnInitShareMemory(void);

			BOOL (*m_pSaveLastMemCallBack) (const void * pBuff, UINT32 uLen, UINT8 uDataId);
			BOOL (*m_pLastMemory_InitCallBack) (UINT8 *last_memory, UINT32 uLen);
			BOOL (*m_pBuSaveLastMemoryCallBack) (const void * pBuff1, const void * pBuff2, UINT32 uLen1, UINT32 uLen2,BOOL bBu);

		private:
			static KCLastMemory*	m_pInstance;
		};
		//==================LastMemory End===================

		// 32位设备表示，每位0：未连接 1：连接
		#define IDDS_USB1			((DWORD)0x00000001)
		#define IDDS_USB2			((DWORD)0x00000002)
		#define IDDS_SD1				((DWORD)0x00000004)
		#define IDDS_SD2				((DWORD)0x00000008)
		#define IDDS_IPOD			((DWORD)0x00000010)
		#define IDDS_DISC			((DWORD)0x00000020)
		#define IDDS_AVIN			((DWORD)0x00000040)
		#define IDDS_BT				((DWORD)0x00000080)
		#define IDDS_RADIO			((DWORD)0x00000100)
		#define IDDS_NAVI			((DWORD)0x00000200)
		#define IDDS_PHONE		((DWORD)0x00000400)

		class UTILITY_API KCStatusIcon
		{
		public:
			virtual ~KCStatusIcon();
			static KCStatusIcon*	GetInstance();
			static void				ExitInstance();

			bool SetStatus(DWORD dwState);
			DWORD GetStatus();

			int     GetBtDialog();
			bool  SetBtDialog(int nDlgID);

			bool  IsBtConnected();
			bool  IsTpmsNotNormal();
			bool  IsNotParking();
			bool  IsNeedStopAV();
			int     GetBtBattery();
			int     GetBtSignal();

			bool  IsRevBackCamera();
			unsigned char GetUsbConnectStatus();
			bool SaveDTVInfoStatus(bool bEnable);
			bool IsDTVInfoStatus();	
			bool SetCurrentVideoWnd(unsigned char chIpcID);
			unsigned char GetCurrentVideoWnd();
			const FT_CAR_TYPE GetCarType();

		private:
			KCStatusIcon();
			bool utility_InitShareMemory();
			void utility_UnInitShareMemory();

		private:
			static KCStatusIcon* m_pInstance;
			
			HANDLE		m_hShareMapping;			// 共享内存句柄
			void *			m_pShareMem;					// 共享内存映射地址
		};

		/* 
		 * 蓝牙版本号共享内存类 
		 */
		class UTILITY_API KCBTVersion
		{
		public:
			KCBTVersion();
			virtual ~KCBTVersion();
			static KCBTVersion*	GetInstance();
			//获取、设置蓝牙版本号
			void GetBTVersion(char* strVersion);
			void SetBTVersion(char* strVersion);
		private:
			void *m_pShareMemory;
			HANDLE m_hFileMap;
		};

#ifdef __cplusplus
	}
}
#endif
