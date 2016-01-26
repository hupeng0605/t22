
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

		/*--------------------------------------------- ϵͳ���� ---------------------------------------------*/
		/*************************************** �������� ***************************************/


		/*--------------------------------------------- ϵͳ���� ---------------------------------------------*/


		/*--------------------------------------------- SERVER���� ------------------------------------------*/
#pragma pack(push,1)
		//SERVER����
		typedef struct _tagServerSetting
		{
			unsigned short nStartSrc[2];						//	��������LAST MODE
			unsigned short uPwrOff;								//	����Power״̬
		}SERVERSETTING, *LPSERVERSETTING;
#pragma pack(pop)

		/*--------------------------------------------- SETUP���� ---------------------------------------------*/

		typedef struct _tagSETUPSETTING
		{
			unsigned char	c12Or24;						// 0 : 12h 1:24h
			unsigned char	cThemeMode;				//����ģʽ
			unsigned char	cBeep;							//BEEP������
			//unsigned char	cWideScreen;			//��Ƶ��ʾ���ʣ�0-16:9,1-4:3
			unsigned char	cGpsAnys;					//GPS��0:ON,1:OFF
			unsigned char	cCamera;						// ����ͷ����
			unsigned char	cOperationStriction;		//MCU�ϱ�������Ϣ(0:��ֹ���� 1:������)
			unsigned char   cIsSound;					// 0 : setup ģ�� 1����Ч���û���
			unsigned char   cLang;							// 0 : ���� 1��Ӣ��
			unsigned char	szBkgndPath[256];
		}SETUPSETTING, *LPSETUPSETTING;

		/*-------------------------------------- SOUND����������� ---------------------------------------*/
		typedef struct _tagSOUNDSETTING
		{
			unsigned char	uSoundVol;								// ������С(0������  1-40 �������ɵ�)
			unsigned char	uBright;									// ���������(1- 10��)
			unsigned char	uDayNight;								// 0������ģʽ  1��ҹ��ģʽ 2 : �Զ�ģʽ
			unsigned char	uSoundHigh;								// ����
			unsigned char	uSoundLow;							 	// ����
			unsigned char  uEQBal;										// ����ƽ��
			unsigned char  uEQFad;									// ǰ��˥��
			unsigned char  uSoundEffects;							// ��Чģʽ
			unsigned char	uKeyTone;								// ����������ֵ
			unsigned char	uSoundSw;								// ��ȿ���( 0��OFF���أ� 1��ON������)
			unsigned char	uTemperature;							// �¶���ʾ 1 : �����¶� 2�������¶�
			unsigned char  uAVC;										// AVC ����
			unsigned short usMcuVer;								// ����汾BCD���ʾ ��λ��.�� 1111 ��ʾ V11.11
			unsigned char  uRadioArea;								// Radio ����ѡ��
			unsigned char  uSpeedLimit;							// ��������
			unsigned char  uOutdoorTemperature;			// �����¶�
			unsigned char  uAutoAir;									// �Զ��յ�(�ñ�ʶ�����ж��ⲿ�¶��Ƿ���ʾ)
		}SOUNDSETTING, *LPSOUNDSETTING;

		/*--------------------------------------------- RADIO���� ---------------------------------------------*/

		/*************************************** �ṹ���� ***************************************/
//#pragma pack(push, 1)
		// RADIO����
		typedef struct tagRadioSetting
		{
			unsigned short uLastAM;						// ���һ�ε�AMƵ��
			unsigned short uLastFM;						// ���һ�ε�FMƵ��
			unsigned short uAMPreset[20];			// AM���� 20��Ԥ����Ƶ��
			unsigned short uFMPreset[20];			// FM���� 20��Ԥ����Ƶ��
			unsigned char uLastBand;					// ���һ�εĲ���(AM/FM)
		}RADIOSETTING,*LPRADIOSETTING;
//#pragma pack(pop)

		/*--------------------------------------------- IPOD���� ---------------------------------------------*/
		//IPOD����
		typedef struct _tagST_IPD_LASTMEM
		{	
			BYTE mmpconbk[552];              /* iPod�ӾA���                    */	
			BYTE mmpstsbk[112];              /* MMP���Ʃ`�������               */	
			BYTE usbconbk[16];               /* USB�ӾA���                     */	
		} ST_IPD_LASTMEM;	

		/*--------------------------------------------- TPMS���� ---------------------------------------------*/
		//TPMS��ģ���Լ�����
		//typedef struct _tagTPMSSETTING
		//{
		//	unsigned char	uMaxPressure;						//	
		//	unsigned char	uMinPressure;						//
		//	unsigned char	uMaxTemperature;					//
		//	unsigned char	uTemperatureUnit;					//
		//	unsigned char	uPressureUnit;						//
		//}TPMSSETTING;


		/*--------------------------------------------- BT���� ---------------------------------------------*/	
		#pragma pack(push,1)
		typedef struct _tagBTSETTING
		{
			unsigned short	uBtPinCode;								//	Ԥ������PIN�룬�Ա���������������չ
			unsigned char	uBtConnctStatus;						//	��������״̬
			unsigned char	uBtAutoReceive;						//	�����Զ�����
			unsigned char	uBtAutoConnect;						//	�����Զ�����
			unsigned char	uBtOnOff;									//	��������״̬
		}BTSETTING, *LPBTSETTING;
		#pragma pack(pop)


		/*--------------------------------------------- USBSD���� ---------------------------------------------*/
		typedef struct _tagUSBSDMODESETTING			//SD����USB��ģʽ��Audio/Video/Picture/Ebook
		{
			unsigned char	uModeSet;				
		}USBSDMODESETTING, *LPUSBSDMODESETTING;

		typedef struct _tagUSBSDAUDIOSETTING		//SD����USB��Audio����
		{
			unsigned short	nAudioFileIndex;						//	��һ����Ƶ���ŵ�·��������
			unsigned short  nAudioFileTotal;						//	��һ����Ƶ���ŵ���Ƶ�ļ�����
			unsigned int		nAudioPlayTime;						//	��һ����Ƶ���ŵ�ʱ��λ��
			unsigned char	uAudioRandom;						//	��һ����Ƶ�����ģʽ
			unsigned char	uAudioRepeat;							//	��һ����Ƶ��ѭ��ģʽ
		}USBSDAUDIOSETTING, *LPUSBSDAUDIOSETTING;		

		typedef struct _tagUSBSDVEDIOSETTING		//SD����USB��Vedio����
		{
			unsigned short		nVideoFileIndex;					//	��һ����Ƶ���ŵ��ļ�·��������
			unsigned short		nVideoFileTotal;					//	��һ����Ƶ���ŵ���Ƶ�ļ�����
			unsigned int			nVedioPlayTime;						//	��һ����Ƶ���ŵ�ʱ��λ��
			unsigned char		uVedioRepeat;						//	��һ����Ƶ��ѭ��ģʽ
		}USBSDVEDIOSETTING, *LPUSBSDVEDIOSETTING;

		typedef struct _tagUSBSDPICTURESETTING		//SD����USB��Picture����
		{
			unsigned short		nPicFileIndex;								//	��һ��ͼƬ���ŵ��ļ�·��������
			unsigned short		nPicFileTotal;								//	��һ��ͼƬ���ŵ�ͼƬ�ļ�����
			unsigned char		uSDPictureSlidePlay;						//	��һ��ͼƬ�����ģʽ���Ƿ����Զ����
			unsigned char		uSDPictureSlideTime;					//	��һ��ͼƬ�Զ������ʱ����
			unsigned char		uSDPictureDisplayRatio;				//	��һ��ͼƬ�Ŵ�ı���
		}USBSDPICTURESETTING, *LPUSBSDPICTURESETTING;

		typedef struct _tagUSBSDEBOOKSETTING		//SD����USB��Picture����
		{
			unsigned short		nEbookFileIndex;								//	��һ�ε����鲥�ŵ��ļ�·��������
			unsigned short		nEbookFileTotal;								//	��һ�ε����鲥�ŵ��ļ�����
			unsigned int			nEbookPlayAddr;								//	��һ�ε����鲥�ŵ��ļ�λ��
		}USBSDEBOOKSETTING, *LPUSBSDEBOOKSETTING;

		typedef struct _tagUSBFlag		//	USB��ʾ��������usb��ȫ��Ψһid��USB��ʹ�ÿռ�
		{
			ULONGLONG lUsbID;					//	usb��ȫ��Ψһid
			ULONGLONG lUsbUsdeSize;				//	Usb��ʹ�ô�С
		}USBFLAG, *LPUSBFLAG;


		/*--------------------------------------------- Last Memory���� ---------------------------------------*/
#define  LAST_MEMORY_DATA_HEAD_SIZE				154
#define  NAVI_LAST_MEMORY_SIZE							80

		/*************************************** ������ ***************************************/
		class UTILITY_API KCLastMemory
		{
		public:
			virtual ~KCLastMemory();

			static KCLastMemory*	GetInstance();
			static void				DeleteInstance();
			
			//��ȡ���е�LastMemory����ʱ�������ļ���ȡ
			void ReadLastMemory();
			//�������е�LastMemory����ʱ���浽�����ļ�
			void SaveLastMemory();
			//�ָ�������������
			void LoadFactory(int nOffset = 0);
			//ɾ�����ݣ��ָ���������
			void ClearData();

			//��ȡ������Server��LastMemory
			void GetServerMemory(SERVERSETTING& Setting);
			void SetServerMemory(SERVERSETTING& Setting);

			//��ȡ������Radio��LastMemory
			void GetRadioMemory(RADIOSETTING& Setting);
			void SetRadioMemory(RADIOSETTING& Setting);
			static void GetRadioMemoryDefault(RADIOSETTING& Setting);

			//��ȡ������BT��LastMemory
			void GetBTMemory(BTSETTING& Setting);
			void SetBTMemory(BTSETTING& Setting);

			//��ȡ������SETUP��LastMemory
			void GetSetupMemory(SETUPSETTING& Setting);
			void SetSetupMemory(SETUPSETTING& Setting);
			static void GetSetupMemoryDefault(SETUPSETTING& Setting);

			//��ȡ������SD��ģʽ��LastMemory
			void GetSDModeMemory(USBSDMODESETTING& Setting);
			void SetSDModeMemory(USBSDMODESETTING& Setting);
			//��ȡ������USB��ģʽ��LastMemory
			void GetUSBModeMemory(USBSDMODESETTING& Setting);
			void SetUSBModeMemory(USBSDMODESETTING& Setting);
			//��ȡ������SD��Audio��LastMemory
			void GetSDAudioMemory(USBSDAUDIOSETTING& Setting);
			void SetSDAudioMemory(USBSDAUDIOSETTING& Setting);
			//��ȡ������USB��Audio��LastMemory
			void GetUSBAudioMemory(USBSDAUDIOSETTING& Setting);
			void SetUSBAudioMemory(USBSDAUDIOSETTING& Setting);
			//��ȡ������SD��Vedio��LastMemory
			void GetSDVedioMemory(USBSDVEDIOSETTING& Setting);
			void SetSDVedioMemory(USBSDVEDIOSETTING& Setting);
			//��ȡ������USB��Vedio��LastMemory
			void GetUSBVedioMemory(USBSDVEDIOSETTING& Setting);
			void SetUSBVedioMemory(USBSDVEDIOSETTING& Setting);
			//��ȡ������SD��Picture��LastMemory
			void GetSDPictureMemory(USBSDPICTURESETTING& Setting);
			void SetSDPictureMemory(USBSDPICTURESETTING& Setting);
			//��ȡ������USB��Picture��LastMemory
			void GetUSBPictureMemory(USBSDPICTURESETTING& Setting);
			void SetUSBPictureMemory(USBSDPICTURESETTING& Setting);
			//��ȡ������SD��EBOOK��LastMemory
			void GetSDeBookMemory(USBSDEBOOKSETTING& Setting);
			void SetSDeBookMemory(USBSDEBOOKSETTING& Setting);
			//��ȡ������USB��EBOOK��LastMemory
			void GetUSBeBookMemory(USBSDEBOOKSETTING& Setting);
			void SetUSBeBookMemory(USBSDEBOOKSETTING& Setting);

			//��ȡ������SOUND��LastMemory
			void GetSoundMemory(SOUNDSETTING& Setting);
			void SetSoundMemory(SOUNDSETTING& Setting);
			//��ȡ������IPOD��Last Memory
			void GetIpodMemory(ST_IPD_LASTMEM& Setting);
			void SetIpodMemory(ST_IPD_LASTMEM& Setting);

			//	��ȡ�����ڴ�Ĵ�С
			int	GetLastMemorySize(int nHeadSize = LAST_MEMORY_DATA_HEAD_SIZE);
			//	��Last Memoryд�빲���ڴ�
			void GetLastMemory(void* pMem, int nHeadSize = LAST_MEMORY_DATA_HEAD_SIZE);
			// ��Last Memoryд�빲���ڴ��ͷ��
			void GetLastMemoryHead(void* pMem, int nHeadSize = LAST_MEMORY_DATA_HEAD_SIZE);

			void GetLastMemoryNavi(void* pMem, int nNaviMemorySize = NAVI_LAST_MEMORY_SIZE);
			//	����Last Memory
			bool SaveLastMemory(int nOffset, int nDataId, int nSize = -1);
			// BU˲��ʱ����Last Memory�ӿ�
			bool SaveLastMemoryBuOff(int nSize = LAST_MEMORY_DATA_HEAD_SIZE, BOOL bBu = FALSE);
			//	���ñ���Last Memory�ص�
			void SetCallBack(BOOL (*callback)(const void*, UINT32, UINT8 uDataId));
			//  ����BU˲�ϱ���Last Memory�ص�
			void SetBuSaveLastMemoryCallBack(BOOL (*callback)(const void* pData, const void* pData2, UINT32 uLen,UINT32 uLen2, BOOL bBu));
			//	��ʼ���м��Last Memory�ص�
			void SetInitMWCallBack(BOOL (*callback)(UINT8 *last_memory, UINT32 uLen));
			//	��ʼ���м�
			void InitMW(int nHeadSize = LAST_MEMORY_DATA_HEAD_SIZE);

			//��ȡ������USBFlag��Last Memory
			void GetUSBFlagMemory(USBFLAG& usbFlag);
			void SetUSBFlagMemory(USBFLAG& usbFlag);

			//��ȡ������SDFlag��Last Memory
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

		// 32λ�豸��ʾ��ÿλ0��δ���� 1������
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
			
			HANDLE		m_hShareMapping;			// �����ڴ���
			void *			m_pShareMem;					// �����ڴ�ӳ���ַ
		};

		/* 
		 * �����汾�Ź����ڴ��� 
		 */
		class UTILITY_API KCBTVersion
		{
		public:
			KCBTVersion();
			virtual ~KCBTVersion();
			static KCBTVersion*	GetInstance();
			//��ȡ�����������汾��
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
