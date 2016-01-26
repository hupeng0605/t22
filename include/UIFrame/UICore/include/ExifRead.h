#pragma once
	
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>	


typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef char  s8;
typedef short s16;
typedef int   s32;

const char Photoshop_Header[] = "Photoshop 3.0\x0";
const char Photoshop_8BIM[] = "8BIM";
const char Photoshop_1C02[] = "\x1c\02";

#define MAX_COMMENT 1000
#define MAX_SECTIONS 20

typedef enum ExifFlag
{
	EXIF_VERSION			= 0x00000001,
	EXIF_CAMERA_MAKER		= 0x00000002,
	EXIF_CAMERA_MODEL		= 0x00000004,
	EXIF_DATA_TIME			= 0x00000008,

	EXIF_WIDTH				= 0x00000010,
	EXIF_HEIGHT				= 0x00000020,
	EXIF_ORIENTATION		= 0x00000040,
	EXIF_PROCESS			= 0x00000080,

	EXIF_FLASH_USED			= 0x00000100,
	EXIF_FOCAL_LENGTH		= 0x00000200,
	EXIF_EXPOSURE_TIME		= 0x00000400,
	EXIF_APERTUREF_NUMBER	= 0x00000800,

	EXIF_DISTANCE			= 0x00001000,
//	EXIF_CCDWidth			= 0x00002000,//和有关EXIF_FOCALPLANE_XRES
	EXIF_EXPOSURE_BIAS		= 0x00004000,
	EXIF_WHITE_BALANCE		= 0x00008000,

	EXIF_METERING_MODE		= 0x00010000,
	EXIF_EXPOSURE_PROGRAM	= 0x00020000,
	EXIF_ISO_EAUIVALENT		= 0x00040000,
	EXIF_COMPRESSION_LEVEL	= 0x00080000,

	EXIF_FOCALPLANE_XRES	= 0x00100000,
	EXIF_FOCALPLANE_YRES	= 0x00200000,
	EXIF_FOCALPLANE_UNITS	= 0x00400000,
	EXIF_XRESOLUTION		= 0x00800000,

	EXIF_YRESOLUTION		= 0x01000000,
	EXIF_RESOLUTION_UNITS	= 0x02000000,
	EXIF_BRIGHTNESS			= 0x04000000,
	EXIF_USER_COMMENT		= 0x08000000,
};

typedef struct tag_ExifInfo {
	char  Version      [5];
    char  CameraMake   [32];
    char  CameraModel  [40];
    char  DateTime     [20];
    int   Height, Width;
    int   Orientation;
    int   IsColor;
    int   Process;
    int   FlashUsed;
    float FocalLength;
    float ExposureTime;
    float ApertureFNumber;
    float Distance;
    float CCDWidth;
    float ExposureBias;
    int   Whitebalance;
    int   MeteringMode;
    int   ExposureProgram;
    int   ISOequivalent;
    int   CompressionLevel;
	float FocalplaneXRes;
	float FocalplaneYRes;
	float FocalplaneUnits;
	float Xresolution;
	float Yresolution;
	float ResolutionUnit;
	float Brightness;
    char  Comments[MAX_COMMENT];

    unsigned char * pThumbnailPointer;  /* Pointer at the thumbnail */
    unsigned ThumbnailSize;     /* Size of thumbnail. */
    unsigned int ThumbnailOffset; //缩略图的相对偏移
	bool  IsExif;
	
	tag_ExifInfo()
	{	
		memset(this, 0, sizeof(tag_ExifInfo));
	}
	
	~tag_ExifInfo()
	{
		if(pThumbnailPointer)
		{
			delete pThumbnailPointer;
			pThumbnailPointer = NULL;
		}
	}

	void Clear()
	{
		if(pThumbnailPointer)
		{
			delete pThumbnailPointer;
			pThumbnailPointer = NULL;
		}

		memset(this, 0, sizeof(tag_ExifInfo));
	}
} ExifInfo;


//--------------------------------------------------------------------------
// JPEG markers consist of one or more 0xFF unsigned chars, followed by a marker
// code unsigned char (which is not an FF).  Here are the marker codes of interest
// in this program.  (See jdmarker.c for a more complete list.)
//--------------------------------------------------------------------------

#define M_SOF0  0xC0            // Start Of Frame N
#define M_SOF1  0xC1            // N indicates which compression process
#define M_SOF2  0xC2            // Only SOF0-SOF2 are now in common use
#define M_SOF3  0xC3
#define M_SOF5  0xC5            // NB: codes C4 and CC are NOT SOF markers
#define M_SOF6  0xC6
#define M_SOF7  0xC7
#define M_SOF9  0xC9
#define M_SOF10 0xCA
#define M_SOF11 0xCB
#define M_SOF13 0xCD
#define M_SOF14 0xCE
#define M_SOF15 0xCF
#define M_SOI   0xD8            // Start Of Image (beginning of datastream)
#define M_EOI   0xD9            // End Of Image (end of datastream)
#define M_SOS   0xDA            // Start Of Scan (begins compressed data)
#define M_JFIF  0xE0            // Jfif marker
#define M_EXIF  0xE1            // Exif marker
#define M_PHOTOSHOP 0xED		// 
#define M_COM   0xFE            // COMment 


typedef struct tag_Section_t{
    unsigned char*    Data;
    int               Type;
    unsigned int      Size;
} Section_t;


class CExifRead
{
public:
	CExifRead(ExifInfo* info = NULL);
	~CExifRead();

	//需要读取的信息位
	void SetReadFlags(int flag);
	//传入文件句柄，获得Exif信息, 可设定是否获得缩略图数据, 默认不获得
	bool DecodeExif(FILE* hFile, bool bGetThumbNail = false);

#ifdef GetErrorCode
	char* GetErrorMsg();
#endif

protected:
	
	bool ProcessExif(unsigned char * CharBuf, unsigned int length, int offset);
	void ProcessCOM (const unsigned char * Data, int length);
	void ProcessSOFn (const unsigned char * Data, int marker);
	int Get16u(void * Short);
	int Get16m(void * Short);
	long Get32m(void * Long);
	long Get32s(void * Long);
	unsigned long Get32u(void * Long);
	double ConvertAnyFormat(void* ValuePtr, int Format);
	bool ProcessExifDir(unsigned char * DirStart, unsigned char * OffsetBase, unsigned int ExifLength, unsigned char ** const LastExifRefdP);
	bool ProcessJFIF(unsigned char* pStart, unsigned int length);
	bool ProcessPhotoshop(unsigned char* pStart, unsigned int length, unsigned int offset);
private:
	bool m_bGetThumbNail;
	int m_ExifImageWidth;
	bool m_bMotorolaOrder;
	Section_t m_Sections[MAX_SECTIONS];
	int m_SectionsRead;
	bool m_bFreeInfo;
	
	int m_flags;
public:
	ExifInfo* m_pExifInfo;
#ifdef GetErrorCode
	char m_szLastError[256];
#endif
};