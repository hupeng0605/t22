// $Change: 000000 $
#pragma once
#ifdef __cplusplus
extern "C" {
#endif
	enum ipodctlERR
	{
		ERR_OK,
		ERR_FAIL,
		ERR_BADPARAM,
		ERR_IPODEXIT,
		ERR_NOTCNNT,
		ERR_NOTINIT
	};
	enum ipodctlPAGE
	{
		PAGE_TOP_LEVEL=0,
		PAGE_PLAYLIST,
		PAGE_ARTIST,
		PAGE_ALBUM,
		PAGE_GENRE,
		PAGE_TRACK,
		PAGE_COMPOSER,
		PAGE_AUDIO_BOOK,
		PAGE_PODCAST,
		PAGE_NESTED_PLAYLIST,
		PAGE_GENIUS_MIXES,
		PAGE_ITUNESU
	};
	enum ipodctlPLAYSTATUS
	{
		PLAYSTATUS_STOPPED=0,
		PLAYSTATUS_PLAYING,
		PLAYSTATUS_PAUSED
	};
	enum ipodctlARTWORKSIZE
	{
		ARTWORKSIZE_320x320=0,
		ARTWORKSIZE_240x240,
		ARTWORKSIZE_128x128,
		ARTWORKSIZE_80x80,
		ARTWORKSIZE_55x55
	};
	enum ipodctlSHUFFLE
	{
		SHUFFLE_OFF=0,
		SHUFFLE_TRACKS,
		SHUFFLE_ALBUMS
	};
	enum ipodctlREPEAT
	{

		REPEAT_OFF=0,
		REPEAT_ONE_TRACK,
		REPEAT_ALL_TRACKS
	};
	ipodctlERR ipodctl_Init(BOOL bAutoCnnt);
	ipodctlERR ipodctl_SetAutoConnect(BOOL bAutoCnnt);
	ipodctlERR ipodctl_ConnectToIpod();
	ipodctlERR ipodctl_StartPlay(ipodctlPAGE startPage,unsigned long startList,unsigned long startIndex);
	ipodctlERR ipodctl_GetPlayStatus(unsigned long* trackIndex,unsigned long* trackLength,unsigned long* trackPosition,ipodctlPLAYSTATUS* playStatus );
	ipodctlERR ipodctl_PlayPause();
	ipodctlERR ipodctl_NextTrack();
	ipodctlERR ipodctl_PreviousTrack();
	ipodctlERR ipodctl_StartFF();
	ipodctlERR ipodctl_StartRew();
	ipodctlERR ipodctl_EndFFRew();
	ipodctlERR ipodctl_GetTrackInfo(unsigned long trackIndex,WCHAR* trackTitle,WCHAR* artistName,WCHAR* albumName);
	ipodctlERR ipodctl_GetPlayingTrackNum(unsigned long* trackNum);
	ipodctlERR ipodctl_SetCurrentPlayingTrack(unsigned long trackIndex);
	ipodctlERR ipodctl_GetArtworkData(unsigned long trackIndex,ipodctlARTWORKSIZE artworkSize,unsigned char* artworkData);
	ipodctlERR ipodctl_GetShuffle(ipodctlSHUFFLE* shuffleStatus);
	ipodctlERR ipodctl_SetShuffle(ipodctlSHUFFLE shuffleStatus);
	ipodctlERR ipodctl_GetRepeat(ipodctlREPEAT* repeatStatus);
	ipodctlERR ipodctl_SetRepeat(ipodctlREPEAT repeatStatus);
	ipodctlERR ipodctl_GetNumberCategorizedDBRecords(ipodctlPAGE iPage,unsigned long *pnTotal);
	ipodctlERR ipodctl_GetCategorizedDBRecords(ipodctlPAGE iPage,unsigned long iStart,unsigned long iCount,unsigned char *p);
	ipodctlERR  ipodctl_GetDBiTunesinfo(unsigned char cType);
    ipodctlERR   ipodctl_GetDBTrackinfo(unsigned long nStart,unsigned long nCount,unsigned char cBitMask);
#ifdef __cplusplus
}
#endif
 