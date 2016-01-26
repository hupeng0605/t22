// $Change: 000000 $
// testipod.h : main header file for the PROJECT_NAME application
//
#ifndef TESTIPOD
#define TESTIPOD
#define  TESTCRITICALSECTION   0
#define  DEBUGIPODDATA 0
#define IPODLOG_EER 1
#define IPODLOG_THREAD 0

typedef unsigned char   U8;
typedef signed char     S8;
typedef unsigned short  U16;
typedef short           S16;
typedef unsigned long   U32;
typedef long            S32;

#define COMMAND_u8Retry 10

typedef enum
{
    CP_MODE0_0,
    CP_MODE0_1,
}enumCPMode0;

#define PLAYSPEED_NORMAL            0x00
#define PLAYSPEED_FASTER            0x01
#define PLAYSPEED_SLOWER		0xFF

#define CATEGORY_TYPE_TOP_LEVEL                     0x0
#define CATEGORY_TYPE_PLAYLIST                          0x1
#define CATEGORY_TYPE_ARTIST	                            0x2
#define CATEGORY_TYPE_ALBUM	                            0x3
#define CATEGORY_TYPE_GENRE                             0x4
#define CATEGORY_TYPE_TRACK                             0x5
#define CATEGORY_TYPE_COMPOSER                      0x6
#define CATEGORY_TYPE_AUDIO_BOOK                0x7
#define CATEGORY_TYPE_PODCAST                       0x8
#define CATEGORY_TYPE_NESTED_PLAYLIST       0x9
#define CATEGORY_TYPE_GENIUS_MIXES              0xA
#define CATEGORY_TYPE_ITUNESU                           0xB

#define PLAY_CONTROL_TOGGLE_PLAYPAUSE       0x01
#define PLAY_CONTROL_STOP                                       0x02
#define PLAY_CONTROL_NEXT_TRACK                         0x03
#define PLAY_CONTROL_PRE_TRACK                          0x04
#define PLAY_CONTROL_START_FF                               0x05
#define PLAY_CONTROL_START_REW                          0x06
#define PLAY_CONTROL_END_FFREW                          0x07
#define PLAY_CONTROL_NEXT                                       0x08
#define PLAY_CONTROL_PREVIOUS                               0x09
#define PLAY_CONTROL_PLAY                                       0x0A
#define PLAY_CONTROL_PAUSE                                      0x0B
#define PLAY_CONTROL_NEXT_CHAPTER                   0x0C
#define PLAY_CONTROL_PRE_CHAPTER                    0x0D
/*
#define SHUFFLE_OFF             0x00
#define SHUFFLE_TRACKS      0x01
#define SHUFFLE_ALBUMS      0x02

#define REPEAT_OFF                      0x00
#define REPEAT_ONE_TRACK    0x01
#define REPEAT_ALL_TRACKS   0x02
*/
//I2C Address
#define DEVICE_VERSION                          0x00
#define FIRMWARE_VERSION                    0x01
#define AUTH_PRO_MAJOR_VER              0x02
#define AUTH_PRO_MINOR_VER              0x03
#define DEVICE_ID                                       0x04
#define ERROR_CODE                                  0x05
#define AUTH_CONTR_STATUS	                0x10
#define SIG_DATA_LEN                                0x11
#define SIG_DATA                                            0x12
#define CHALLENGE_DATA_LEN              0x20
#define CHALLENGE_DATA	                        0x21
#define ACC_CERTI_DATA_LEN                  0x30
#define ACC_CERTI_DATA                              0x31
#define SELFTEST_CONTR_STATUS           0x40
#define IPOD_CERTI_DATA_LEN                 0x50
#define IPOD_CERTI_DATA                             0x51


#define IOCTL_I2C_READ 1769479
#define IOCTL_I2C_WRITE 1769483
#define IOCTL_I2C_GPIO_CTL 1769503

#define IOCTL_IAPL_PCM_SETFORMAT 1441836
#define IOCTL_IAPL_ISSUE_ISO_TRF 1441828
/*
typedef struct
{
    U8   u8SlaveId;
    U8  *pu8RegAddr;
    U8  u32RegAddrCnt;
    U8  *pu8Data;
    U32  u32DataCnt;
} I2C_IO_INFO;
*/

typedef struct
{
    U8   u8SlaveId;
    U8  *pu8RegAddr;
    U32  u32RegAddrCnt;
    U8  *pu8Data;
    U32  u32DataCnt;
} I2C_IO_INFO;

typedef struct
{
    U8 u8Marker;
    U8 u8PackageLenH;
    U8 u8PackageLenL;
    U8 u8LingoID;
    U8 u8CommandID;
    U8 pu8CommandData[1024];
}ST_PACKAGE,*PST_PACKAGE;

class TestIpod
{
private:
    HANDLE hI2c;
    HANDLE hReadThread;
	HANDLE m_hIpodReady;
    U32 u32DeviceID;
    U8 u8MajorVersion;
    U8 u8MinorVersion;
    U8 i2cReadAdd;
    U8 i2cWriteAdd;
	bool m_bReadThread;
	bool m_bReadThreadSup;
    BOOL ConnectToIpod();
    BOOL ReadI2c(U8 u8RegAddr,U8 *pu8ReadValue, U32 u32ReadCnt);
    BOOL WriteI2c(U8 u8RegAddr,U8 *pu8ReadValue, U32 u32WriteCnt);
    enumCPMode0 GetCPMode0();
    void Utf8ToUnicode(WCHAR* pOutBuf,char* pInBuf,U16  u16Len);
    U16 ReadAccCerData(U8 *pu8data);
    //1cmd++
    BOOL StartIDPS(U8 u8Retry);
    BOOL SetFIDTokenValues();
    BOOL EndIDPS();
	BOOL GetMaxPayloadSize(unsigned long *plMaxSize);
    BOOL RetDevAuthenticationInfo();
    BOOL AckDevAuthenticationInfo();
    BOOL RetDevAuthenticationSignature();
    BOOL GetiPodAuthenticationInfo();
    BOOL GetiPodAuthenticationSignature();
    U16 RetTrackArtworkData(U8 *pu8artwork);
    //1cmd--
public:
	TestIpod();
	~TestIpod();
    BOOL Connect();
    BOOL OpenDevice();
	BOOL OpenDeviceEx();
    void CloseDevice();
    BOOL IpodAuthenticationAcc();
    BOOL AccAuthenticationIpod();
    BOOL StartPlay();
    //1cmd++
    BOOL SetUIMode();
    BOOL GetCurrentPlayingTrackChapterInfo(U32* pu32CurChapterIdx,U32* pu32ChapterCnt);//获取总列表数和当前列表汉?
    BOOL SetCurrentPlayingTrackChapter(U32 u32CurChapterIdx);//设置当前列表
    BOOL GetAudiobookSpeed(U8* pu8Playspeed);//获取播放速度
    BOOL SetAudiobookSpeed(U8 u8Playspeed);//设置播放速度
    BOOL GetIndexedPlayingTrackInfoPodcastName(U32 u32TrackIdx,U32 u32ChapterIdx,WCHAR* pPodcastName);
    BOOL ResetDBSelection();//在SelectDBRecord使用
    BOOL SelectDBRecord(U8 u8CategoryTypes,U32 u32Index);//选择当前页面
    BOOL GetNumberCategorizedDBRecords(U8 u8CategoryTypes,U32* pu32Num);//获取指定页面的选项数
    BOOL GetPlayStatus(U32* pu32TrackLen,U32* pu32TrackPos,U8* pu8State);//获取播放状态
    BOOL GetCurrentPlayingTrackIndex(U32* pu32Trackidx);//获取当前播放的编号
    BOOL GetIndexedPlayingTrackTitle(U32 u32TrackIdx,WCHAR* pTrackTitle);//获取当前播放的名称
    BOOL GetIndexedPlayingTrackArtistName(U32 u32TrackIdx,WCHAR* pArtistName);//获取当前播放的演唱者
    BOOL GetIndexedPlayingTrackAlbumName(U32 u32TrackIdx,WCHAR* pAlbumName);//获取当前播放的专辑
    BOOL SetPlayStatusChangeNotification(BOOL enable,U32 u32StatusChangeMas);//设置播放状态变化的提醒
    BOOL PlayCurrentSelection(U32 u32TrackIdx);//选择当前播放
    BOOL PlayControl(U8 u8Control);//控制播放
    BOOL GetShuffle(U8* pu8ShuffleType);//获取随机播放
    BOOL SetShuffle(U8 u8ShuffleType);//设置随机播放
    BOOL GetRepeat(U8* pu8RepeatType);//获取重复
    BOOL SetRepeat(U8 u8RepeatType);//设置重复
    BOOL GetNumPlayingTracks(U32* pu32TrackNum);//获取歌曲总数
    BOOL SetCurrentPlayingTrack(U32 u32TrackIdx);//设置当前播放歌曲，仅在播放和暂停时有效
    BOOL GetArtworkFormats();
    BOOL GetTrackArtworkData(U8 *pu8artwork,U32 u32TrackIndex,U8 u8Format);
    BOOL RetAccSampleRateCaps(U32 *u32SampleRate);
	BOOL GetDBiTunesInfo(unsigned char cType);
	void SetIpodReadyEvent();
	void ResetIpodReadyEvent();
    BOOL RetrieveCategorizedDatabaseRecords(unsigned char cType,unsigned long iStart,unsigned long iCount,unsigned char *pOut);
	BOOL ReturnCategorizedDatabaseRecords(unsigned char *pOut);
	BOOL ReadCategorizedDatabaseRecords(PST_PACKAGE sp);
	BOOL HandleTarckNewAttributes(unsigned char *Command,unsigned long nLen);
	bool GetDBTrackinfo(unsigned long nStart,unsigned long nCount,unsigned char cBitMask);
    //1cmd--
};
#endif
