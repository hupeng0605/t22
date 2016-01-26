#include "ExifRead.h"
	
////////////////////////////////////////////////////////////////////////////////
CExifRead::CExifRead(ExifInfo* pInfo)
{
	if (pInfo) 
	{
		m_pExifInfo = pInfo;
		m_bFreeInfo = false;
	} 
	else 
	{
		m_pExifInfo = new ExifInfo;
		m_bFreeInfo = true;
	}
#ifdef GetErrorCode
	m_szLastError[0]='\0';
#endif
	m_ExifImageWidth = 0;
	m_bMotorolaOrder = false;
	m_SectionsRead = 0;
	memset(&m_Sections, 0, MAX_SECTIONS * sizeof(Section_t));

	m_bGetThumbNail = false;
	m_flags = 0xffffffff;
}

////////////////////////////////////////////////////////////////////////////////
CExifRead::~CExifRead()
{
	for(int i=0;i<MAX_SECTIONS;i++) 
	{
		if(m_Sections[i].Data) 
			free(m_Sections[i].Data);
	}
	if (m_bFreeInfo) 
		delete m_pExifInfo;
}

void CExifRead::SetReadFlags(int flags)
{
	m_flags = flags;
}

////////////////////////////////////////////////////////////////////////////////
bool CExifRead::DecodeExif(FILE * hFile, bool bGetThumbNail)
{
    int a;
    int HaveCom = 0;
	m_bGetThumbNail = bGetThumbNail;
    a = fgetc(hFile);

	m_pExifInfo->Clear();
	for(int i=0;i<MAX_SECTIONS;i++) 
	{
		if(m_Sections[i].Data)
		{
			free(m_Sections[i].Data);
			m_Sections[i].Data = 0;
		}
	}
	m_SectionsRead = 0;
	m_bMotorolaOrder = false;
	m_ExifImageWidth = 0;

    if (a != 0xff || fgetc(hFile) != M_SOI){
        return 0;
    }

	int offset = 2;
	int itemlen;
	int marker = 0;
	int ll,lh, got;
	unsigned char * Data;

    for(;;)
	{
        if (m_SectionsRead >= MAX_SECTIONS)
		{
#ifdef GetErrorCode
			strcpy(m_szLastError,"Too many sections in jpg file");
#endif
			return 0;
        }

        for (a=0;a<7;a++)
		{
            marker = fgetc(hFile);
			offset++;
            if (marker != 0xff) 
				break;

            if (a >= 6)
			{
#ifdef GetErrorCode
                printf("too many padding unsigned chars\n");
#endif
                return 0;
            }
        }

        if (marker == 0xff)
		{
#ifdef GetErrorCode
			// 0xff is legal padding, but if we get that many, something's wrong.
            strcpy(m_szLastError,"too many padding unsigned chars!");
#endif
			return 0;
        }

        m_Sections[m_SectionsRead].Type = marker;

        // Read the length of the section.
        lh = fgetc(hFile);
        ll = fgetc(hFile);

        itemlen = (lh << 8) | ll;

        if (itemlen < 2)
		{
#ifdef GetErrorCode
			strcpy(m_szLastError,"invalid marker");
#endif
			return 0;
        }

        m_Sections[m_SectionsRead].Size = itemlen;

        Data = (unsigned char *)malloc(itemlen);
        if (Data == NULL)
		{
#ifdef GetErrorCode
            strcpy(m_szLastError,"Could not allocate memory");
#endif
			return 0;
        }
        m_Sections[m_SectionsRead].Data = Data;

        // Store first two pre-read unsigned chars.
        Data[0] = (unsigned char)lh;
        Data[1] = (unsigned char)ll;

        got = fread(Data+2, 1, itemlen-2, hFile); // Read the whole section.

        if (got != itemlen-2)
		{
#ifdef GetErrorCode
			strcpy(m_szLastError,"Premature end of file?");
#endif
			free(Data);
			return 0;
        }
        m_SectionsRead += 1;

        switch(marker){

            case M_SOS:   // stop before hitting compressed data 
                // If reading entire image is requested, read the rest of the data.
                /*if (ReadMode & READ_IMAGE){
                    int cp, ep, size;
                    // Determine how much file is left.
                    cp = ftell(infile);
                    fseek(infile, 0, SEEK_END);
                    ep = ftell(infile);
                    fseek(infile, cp, SEEK_SET);

                    size = ep-cp;
                    Data = (uchar *)malloc(size);
                    if (Data == NULL){
                        strcpy(m_szLastError,"could not allocate data for entire image");
						return 0;
                    }

                    got = fread(Data, 1, size, infile);
                    if (got != size){
                        strcpy(m_szLastError,"could not read the rest of the image");
						return 0;
                    }

                    m_Sections[m_SectionsRead].Data = Data;
                    m_Sections[m_SectionsRead].Size = size;
                    m_Sections[m_SectionsRead].Type = PSEUDO_IMAGE_MARKER;
                    m_SectionsRead ++;
                    HaveAll = 1;
                }*/
                return 1;

            case M_EOI:   // in case it's a tables-only JPEG stream
#ifdef GetErrorCode
                printf("No image in jpeg!\n");
#endif
                return 0;

            case M_COM: // Comment section
                if (HaveCom)
				{
                    // Discard this section.
                    free(m_Sections[--m_SectionsRead].Data);
					m_Sections[m_SectionsRead].Data = 0;
                }
				else
				{
                    ProcessCOM(Data, itemlen);
                    HaveCom = 1;
                }
                break;

            case M_JFIF:
                // Regular jpegs always have this tag, exif images have the exif
                // marker instead, althogh ACDsee will write images with both markers.
                // this program will re-create this marker on absence of exif marker.
                // hence no need to keep the copy from the file.
                ProcessJFIF(Data + 2, itemlen - 2);
				
                break;

            case M_EXIF:
                // Seen files from some 'U-lead' software with Vivitar scanner
                // that uses marker 31 for non exif stuff.  Thus make sure 
                // it says 'Exif' in the section before treating it as exif.
                if (memcmp(Data+2, "Exif", 4) == 0)
				{
                    m_pExifInfo->IsExif = ProcessExif((unsigned char *)Data+2, itemlen, offset + 2 );
                }
				else
				{
                    // Discard this section.
                    free(m_Sections[--m_SectionsRead].Data);
					m_Sections[m_SectionsRead].Data = 0;
                }
                break;
			
			case M_PHOTOSHOP:
				m_pExifInfo->IsExif = ProcessPhotoshop(Data + 2, itemlen - 2, offset + 2);
				break;
            case M_SOF0: 
            case M_SOF1: 
            case M_SOF2: 
            case M_SOF3: 
            case M_SOF5: 
            case M_SOF6: 
            case M_SOF7: 
            case M_SOF9: 
            case M_SOF10:
            case M_SOF11:
            case M_SOF13:
            case M_SOF14:
            case M_SOF15:
                ProcessSOFn(Data, marker);
                break;
            default:
                // Skip any other sections.
                //if (ShowTags) printf("Jpeg section marker 0x%02x size %d\n",marker, itemlen);
                break;
        }

		offset += itemlen;
    }
	return 1;
}

bool CExifRead::ProcessPhotoshop(unsigned char* pStart, unsigned int length, unsigned int offset)
{
	int temp = strlen(Photoshop_Header);
	if ( memcmp(pStart, Photoshop_Header, temp) == 0)
	{
		temp += 1;
		while ( temp < length)
		{
			if ( memcmp(pStart + temp, Photoshop_8BIM, 4) == 0)
			{
				temp += 4;
				int tag = Get16m(pStart + temp);
				int type = Get16m(pStart + temp + 2);
				int lengthTag = Get32m(pStart + temp + 4);
				if ( lengthTag%2 == 1)
				{
					lengthTag ++;
				}
				temp += 8;

				switch (tag)
				{
				case 0x040c:
					if ( m_bGetThumbNail && m_pExifInfo->pThumbnailPointer == NULL)
					{
						/*//0 Motorola-order Long Appears to always equal 1
						Officially, this denotes the 'format', and this value could also equal 0, but it is not clear what that should mean, nor have we ever seen this. 
						4 Motorola-order Long Thumbnail width 
						8 Motorola-order Long Thumbnail height 
						12 Motorola-order Long Scanline size ( = thumbnail width * 3, padded to nearest multiple of 4) 
						16 Motorola-order Long Total decompressed thumbnail memory size ( = scanline size * thumbnail height) 
						20 Motorola-order Long Size of the JFIF data ( = size of resource data - 28) 
						24 Motorola-order Word Appears to always equal 24
						Officially, this denotes the number of bits per pixel 
						26 Motorola-order Word Appears to always equal 1
						Officially, this denotes the number of planes 
						28 Variable number of bytes, as indicated by 'Size of JFIF data' field JFIF data 
						*/
						m_pExifInfo->ThumbnailSize = lengthTag - 28;

						unsigned char * dat = new unsigned char[m_pExifInfo->ThumbnailSize];
						memcpy(dat, pStart + temp + 28, m_pExifInfo->ThumbnailSize);
						m_pExifInfo->pThumbnailPointer = dat;

						m_pExifInfo->ThumbnailOffset = offset + temp + 28;
					}
					break;
				default :
					break;
				
				}
				temp += lengthTag;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
	
}

bool CExifRead::ProcessJFIF(unsigned char* pStart, unsigned int length)
{
	if ( memcmp(pStart, "JFIF", 5 ) == 0)
	{
		if ( length < 14)
		{
			return false;
		}
		if ( m_flags & EXIF_VERSION)
			strncpy_s(m_pExifInfo->Version,5,(char*)(pStart + 5), 2);

		if ( m_flags & EXIF_RESOLUTION_UNITS)
		{
			m_pExifInfo->ResolutionUnit = *(pStart + 7);
		}

		if ( m_flags & EXIF_XRESOLUTION)
		{
			m_pExifInfo->Xresolution = Get16m(pStart + 8);
		}

		if ( m_flags & EXIF_YRESOLUTION)
		{
			m_pExifInfo->Yresolution = Get16m(pStart + 10);
		}
	
		//ËõÂÔÍ¼µÄ¿í¸ß
// 		m_pExifInfo->Width = *(pStart + 12);
// 		m_pExifInfo->Height = *(pStart + 13);

		return true;
	}
	else
	{
		return false;
	}
	
}

////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------
   Process a EXIF marker
   Describes all the drivel that most digital cameras include...
--------------------------------------------------------------------------*/
bool CExifRead::ProcessExif(unsigned char * CharBuf, unsigned int length, int offset)
{
    m_pExifInfo->FlashUsed = 0; 
    /* If it's from a digicam, and it used flash, it says so. */
    m_pExifInfo->Comments[0] = '\0';  /* Initial value - null string */

    m_ExifImageWidth = 0;

    {   /* Check the EXIF header component */
        static const unsigned char ExifHeader[] = "Exif\0\0";
        if (memcmp(CharBuf+0, ExifHeader,6))
		{
#ifdef GetErrorCode
			strcpy(m_szLastError,"Incorrect Exif header");
#endif
			return 0;
		}
    }

    if (memcmp(CharBuf+6,"II",2) == 0)
	{
        m_bMotorolaOrder = false;
    }
	else
	{
        if (memcmp(CharBuf+6,"MM",2) == 0)
		{
            m_bMotorolaOrder = true;
        }
		else
		{
#ifdef GetErrorCode            
			strcpy(m_szLastError,"Invalid Exif alignment marker.");
#endif
			return 0;
        }
    }

    /* Check the next two values for correctness. */
    if (Get16u(CharBuf+8) != 0x2a)
	{
#ifdef GetErrorCode
        strcpy(m_szLastError,"Invalid Exif start (1)");
#endif
		return 0;
    }

	int FirstOffset = Get32u(CharBuf+10);
    if (FirstOffset < 8 || FirstOffset > 16){
        // I used to ensure this was set to 8 (website I used indicated its 8)
        // but PENTAX Optio 230 has it set differently, and uses it as offset. (Sept 11 2002)
#ifdef GetErrorCode
        strcpy(m_szLastError,"Suspicious offset of first IFD value");
#endif
		return 0;
    }

    unsigned char * LastExifRefd = CharBuf;

    /* First directory starts 16 unsigned chars in.  Offsets start at 8 unsigned chars in. */
    if (!ProcessExifDir(CharBuf+14, CharBuf+6, length-6, &LastExifRefd))
		return 0;

	if ( m_bGetThumbNail && m_pExifInfo->pThumbnailPointer != NULL)
	{
		unsigned char * dat = new unsigned char[m_pExifInfo->ThumbnailSize];
		memcpy( dat, m_pExifInfo->pThumbnailPointer, m_pExifInfo->ThumbnailSize);
		m_pExifInfo->pThumbnailPointer = dat;
		m_pExifInfo->ThumbnailOffset = (m_pExifInfo->ThumbnailOffset) + offset + 6;
	}
	else
	{
		m_pExifInfo->pThumbnailPointer = NULL;
		m_pExifInfo->ThumbnailOffset = 0;
		m_pExifInfo->ThumbnailSize = 0;
	}

    /* This is how far the interesting (non thumbnail) part of the exif went. */
    // int ExifSettingsLength = LastExifRefd - CharBuf;

    /* Compute the CCD width, in milimeters. */
    if (m_pExifInfo->FocalplaneXRes != 0)
	{
        m_pExifInfo->CCDWidth = (float)(m_ExifImageWidth * m_pExifInfo->FocalplaneUnits / m_pExifInfo->FocalplaneXRes);
    }

	return 1;
}
//--------------------------------------------------------------------------
// Get 16 bits motorola order (always) for jpeg header stuff.
//--------------------------------------------------------------------------
int CExifRead::Get16m(void * Short)
{
    return (((unsigned char *)Short)[0] << 8) | ((unsigned char *)Short)[1];
}

////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------
   Convert a 16 bit unsigned value from file's native unsigned char order
--------------------------------------------------------------------------*/
int CExifRead::Get16u(void * Short)
{
    if (m_bMotorolaOrder){
        return (((unsigned char *)Short)[0] << 8) | ((unsigned char *)Short)[1];
    }else{
        return (((unsigned char *)Short)[1] << 8) | ((unsigned char *)Short)[0];
    }
}

long CExifRead::Get32m(void * Long)
{
	return  ((( char *)Long)[0] << 24) | (((unsigned char *)Long)[1] << 16)
			| (((unsigned char *)Long)[2] << 8 ) | (((unsigned char *)Long)[3] << 0 );
}

////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------
   Convert a 32 bit signed value from file's native unsigned char order
--------------------------------------------------------------------------*/
long CExifRead::Get32s(void * Long)
{
    if (m_bMotorolaOrder){
        return  ((( char *)Long)[0] << 24) | (((unsigned char *)Long)[1] << 16)
              | (((unsigned char *)Long)[2] << 8 ) | (((unsigned char *)Long)[3] << 0 );
    }else{
        return  ((( char *)Long)[3] << 24) | (((unsigned char *)Long)[2] << 16)
              | (((unsigned char *)Long)[1] << 8 ) | (((unsigned char *)Long)[0] << 0 );
    }
}

////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------
   Convert a 32 bit unsigned value from file's native unsigned char order
--------------------------------------------------------------------------*/
unsigned long CExifRead::Get32u(void * Long)
{
    return (unsigned long)Get32s(Long) & 0xffffffff;
}

////////////////////////////////////////////////////////////////////////////////

/* Describes format descriptor */
static const int BytesPerFormat[] = {0,1,1,2,4,8,1,1,2,4,8,4,8};
#define NUM_FORMATS 12

#define FMT_BYTE       1 
#define FMT_STRING     2
#define FMT_USHORT     3
#define FMT_ULONG      4
#define FMT_URATIONAL  5
#define FMT_SBYTE      6
#define FMT_UNDEFINED  7
#define FMT_SSHORT     8
#define FMT_SLONG      9
#define FMT_SRATIONAL 10
#define FMT_SINGLE    11
#define FMT_DOUBLE    12

/* Describes tag values */

#define TAG_EXIF_VERSION      0x9000
#define TAG_EXIF_OFFSET       0x8769
#define TAG_INTEROP_OFFSET    0xa005

#define TAG_MAKE              0x010F
#define TAG_MODEL             0x0110

#define TAG_ORIENTATION       0x0112
#define TAG_XRESOLUTION       0x011A
#define TAG_YRESOLUTION       0x011B
#define TAG_RESOLUTIONUNIT    0x0128

#define TAG_EXPOSURETIME      0x829A
#define TAG_FNUMBER           0x829D

#define TAG_SHUTTERSPEED      0x9201
#define TAG_APERTURE          0x9202
#define TAG_BRIGHTNESS        0x9203
#define TAG_MAXAPERTURE       0x9205
#define TAG_FOCALLENGTH       0x920A

#define TAG_DATETIME_ORIGINAL 0x9003
#define TAG_USERCOMMENT       0x9286

#define TAG_SUBJECT_DISTANCE  0x9206
#define TAG_FLASH             0x9209

#define TAG_FOCALPLANEXRES    0xa20E
#define TAG_FOCALPLANEYRES    0xa20F
#define TAG_FOCALPLANEUNITS   0xa210
#define TAG_EXIF_IMAGEWIDTH   0xA002
#define TAG_EXIF_IMAGELENGTH  0xA003

/* the following is added 05-jan-2001 vcs */
#define TAG_EXPOSURE_BIAS     0x9204
#define TAG_WHITEBALANCE      0x9208
#define TAG_METERING_MODE     0x9207
#define TAG_EXPOSURE_PROGRAM  0x8822
#define TAG_ISO_EQUIVALENT    0x8827
#define TAG_COMPRESSION_LEVEL 0x9102

#define TAG_THUMBNAIL_OFFSET  0x0201
#define TAG_THUMBNAIL_LENGTH  0x0202


/*--------------------------------------------------------------------------
   Process one of the nested EXIF directories.
--------------------------------------------------------------------------*/
bool CExifRead::ProcessExifDir(unsigned char * DirStart, unsigned char * OffsetBase, unsigned int ExifLength, unsigned char ** const LastExifRefdP )
{
    int de;
    int a;
    int NumDirEntries;
    unsigned ThumbnailOffset = 0;
    unsigned ThumbnailSize = 0;

    NumDirEntries = Get16u(DirStart);

    if ((DirStart+2+NumDirEntries*12) > (OffsetBase+ExifLength))
	{
#ifdef GetErrorCode
        strcpy(m_szLastError,"Illegally sized directory");
#endif
		return 0;
    }

    for (de=0;de<NumDirEntries;de++){
        int Tag, Format, Components;
        unsigned char * ValuePtr;
            /* This actually can point to a variety of things; it must be
               cast to other types when used.  But we use it as a unsigned char-by-unsigned char
               cursor, so we declare it as a pointer to a generic unsigned char here.
            */
        int BytesCount;
        unsigned char * DirEntry;
        DirEntry = DirStart+2+12*de;

        Tag = Get16u(DirEntry);
        Format = Get16u(DirEntry+2);
        Components = Get32u(DirEntry+4);

        if ((Format-1) >= NUM_FORMATS) 
		{
#ifdef GetErrorCode            
			/* (-1) catches illegal zero case as unsigned underflows to positive large */
            strcpy(m_szLastError,"Illegal format code in EXIF dir");
#endif
			return 0;
		}

        BytesCount = Components * BytesPerFormat[Format];

        if (BytesCount > 4){
            unsigned OffsetVal;
            OffsetVal = Get32u(DirEntry+8);
            /* If its bigger than 4 unsigned chars, the dir entry contains an offset.*/
            if (OffsetVal+BytesCount > ExifLength)
			{
#ifdef GetErrorCode                
				/* Bogus pointer offset and / or unsigned charcount value */
                strcpy(m_szLastError,"Illegal pointer offset value in EXIF.");
#endif
				return 0;
            }
            ValuePtr = OffsetBase+OffsetVal;
        }
		else
		{
            /* 4 unsigned chars or less and value is in the dir entry itself */
            ValuePtr = DirEntry+8;
        }

        if (*LastExifRefdP < ValuePtr+BytesCount)
		{
            /* Keep track of last unsigned char in the exif header that was
               actually referenced.  That way, we know where the
               discardable thumbnail data begins.
            */
            *LastExifRefdP = ValuePtr+BytesCount;
        }

        /* Extract useful components of tag */
        switch(Tag)
		{
            case TAG_MAKE:
				if ( m_flags & EXIF_CAMERA_MAKER)
					strncpy(m_pExifInfo->CameraMake, (char*)ValuePtr, 31);
                break;

            case TAG_MODEL:
				if ( m_flags & EXIF_CAMERA_MODEL)
					strncpy_s(m_pExifInfo->CameraModel,40, (char*)ValuePtr, 39);
                break;

			case TAG_EXIF_VERSION:
				if ( m_flags & EXIF_VERSION)
					strncpy_s(m_pExifInfo->Version,5,(char*)ValuePtr, 4);
				break;

            case TAG_DATETIME_ORIGINAL:
				if ( m_flags & EXIF_DATA_TIME)
					strncpy_s(m_pExifInfo->DateTime,20, (char*)ValuePtr, 19);
                break;

            case TAG_USERCOMMENT:
				if ( m_flags & EXIF_USER_COMMENT)
				{
					// Olympus has this padded with trailing spaces. Remove these first. 
					for ( a=BytesCount; ;)
					{
						a--;
						if (((char*)ValuePtr)[a] == ' ')
						{
							((char*)ValuePtr)[a] = '\0';
						}
						else
						{
							break;
						}
						if (a == 0) 
							break;
					}

					/* Copy the comment */
					if (memcmp(ValuePtr, "ASCII",5) == 0)
					{
						for (a=5;a<10;a++)
						{
							char c;
							c = ((char*)ValuePtr)[a];
							if (c != '\0' && c != ' ')
							{
								strncpy_s(m_pExifInfo->Comments,MAX_COMMENT, (char*)ValuePtr+a, 199);
								break;
							}
						}

					}else
					{
						strncpy_s(m_pExifInfo->Comments,MAX_COMMENT, (char*)ValuePtr, 199);
					}
				}
                break;

            case TAG_FNUMBER:
				
                /* Simplest way of expressing aperture, so I trust it the most.
                   (overwrite previously computd value if there is one)
                   */
				if ( m_flags & EXIF_APERTUREF_NUMBER)
					m_pExifInfo->ApertureFNumber = (float)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_APERTURE:
            case TAG_MAXAPERTURE:
                /* More relevant info always comes earlier, so only
                 use this field if we don't have appropriate aperture
                 information yet. 
                */
                if ((m_flags & EXIF_APERTUREF_NUMBER) && m_pExifInfo->ApertureFNumber == 0)
				{
                    m_pExifInfo->ApertureFNumber = (float)exp(ConvertAnyFormat(ValuePtr, Format)*log(2.0)*0.5);
                }
                break;

			case TAG_BRIGHTNESS:
				if ( m_flags & EXIF_BRIGHTNESS)
					m_pExifInfo->Brightness = (float)ConvertAnyFormat(ValuePtr, Format);
				break;

            case TAG_FOCALLENGTH:
                /* Nice digital cameras actually save the focal length
                   as a function of how farthey are zoomed in. 
                */
				if ( m_flags & EXIF_FOCAL_LENGTH)
					m_pExifInfo->FocalLength = (float)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_SUBJECT_DISTANCE:
                /* Inidcates the distacne the autofocus camera is focused to.
                   Tends to be less accurate as distance increases.
                */
				if ( m_flags & EXIF_DISTANCE)
					m_pExifInfo->Distance = (float)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_EXPOSURETIME:
                /* Simplest way of expressing exposure time, so I
                   trust it most.  (overwrite previously computd value
                   if there is one) 
                */
				if ( m_flags & EXIF_EXPOSURE_TIME)
					m_pExifInfo->ExposureTime = (float)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_SHUTTERSPEED:
                /* More complicated way of expressing exposure time,
                   so only use this value if we don't already have it
                   from somewhere else.  
                */
                if (( m_flags & EXIF_EXPOSURE_TIME) && m_pExifInfo->ExposureTime == 0)
				{
                    m_pExifInfo->ExposureTime = (float) (1/exp(ConvertAnyFormat(ValuePtr, Format)*log(2.0)));
                }
                break;

            case TAG_FLASH:
				if ( m_flags & EXIF_FLASH_USED)
				{
					if ((int)ConvertAnyFormat(ValuePtr, Format) & 7)
					{
						m_pExifInfo->FlashUsed = 1;
					}
					else
					{
						m_pExifInfo->FlashUsed = 0;
					}
				}
                break;

            case TAG_ORIENTATION:
				if ( m_flags & EXIF_ORIENTATION)
				{
					m_pExifInfo->Orientation = (int)ConvertAnyFormat(ValuePtr, Format);
					if (m_pExifInfo->Orientation < 1 || m_pExifInfo->Orientation > 8)
					{
#ifdef GetErrorCode 
						strcpy(m_szLastError,"Undefined rotation value");
#endif
						m_pExifInfo->Orientation = 0;
					}
				}
                break;

            case TAG_EXIF_IMAGELENGTH:
            case TAG_EXIF_IMAGEWIDTH:
                /* Use largest of height and width to deal with images
                   that have been rotated to portrait format.  
                */
                a = (int)ConvertAnyFormat(ValuePtr, Format);
                if (m_ExifImageWidth < a) 
					m_ExifImageWidth = a;
                break;

            case TAG_FOCALPLANEXRES:
				if ( m_flags & EXIF_FOCALPLANE_XRES)
					m_pExifInfo->FocalplaneXRes = (float)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_FOCALPLANEYRES:
				if ( m_flags & EXIF_FOCALPLANE_YRES)
					m_pExifInfo->FocalplaneYRes = (float)ConvertAnyFormat(ValuePtr, Format);
                break;

			case TAG_RESOLUTIONUNIT:
				if ( m_flags & EXIF_RESOLUTION_UNITS)
				{
					switch((int)ConvertAnyFormat(ValuePtr, Format))
					{
					case 1: m_pExifInfo->ResolutionUnit = 1.0f; break; /* 1 inch */
					case 2:	m_pExifInfo->ResolutionUnit = 1.0f; break;
					case 3: m_pExifInfo->ResolutionUnit = 0.3937007874f;    break;  /* 1 centimeter*/
					case 4: m_pExifInfo->ResolutionUnit = 0.03937007874f;   break;  /* 1 millimeter*/
					case 5: m_pExifInfo->ResolutionUnit = 0.00003937007874f;  /* 1 micrometer*/
					}
				}
                break;

            case TAG_FOCALPLANEUNITS:
				if ( m_flags & EXIF_FOCALPLANE_UNITS)
				{
					switch((int)ConvertAnyFormat(ValuePtr, Format))
					{
						case 1: m_pExifInfo->FocalplaneUnits = 1.0f; break; /* 1 inch */
						case 2:	m_pExifInfo->FocalplaneUnits = 1.0f; break;
						case 3: m_pExifInfo->FocalplaneUnits = 0.3937007874f;    break;  /* 1 centimeter*/
						case 4: m_pExifInfo->FocalplaneUnits = 0.03937007874f;   break;  /* 1 millimeter*/
						case 5: m_pExifInfo->FocalplaneUnits = 0.00003937007874f;  /* 1 micrometer*/
					}
				}
                break;

                // Remaining cases contributed by: Volker C. Schoech <schoech(at)gmx(dot)de>

            case TAG_EXPOSURE_BIAS:
				if ( m_flags & EXIF_EXPOSURE_BIAS)
					m_pExifInfo->ExposureBias = (float) ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_WHITEBALANCE:
				if ( m_flags & EXIF_WHITE_BALANCE)
					m_pExifInfo->Whitebalance = (int)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_METERING_MODE:
				if ( m_flags & EXIF_METERING_MODE)
					m_pExifInfo->MeteringMode = (int)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_EXPOSURE_PROGRAM:
				if ( m_flags & EXIF_EXPOSURE_PROGRAM)
					m_pExifInfo->ExposureProgram = (int)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_ISO_EQUIVALENT:
				if ( m_flags & EXIF_ISO_EAUIVALENT)
				{
					m_pExifInfo->ISOequivalent = (int)ConvertAnyFormat(ValuePtr, Format);
					if ( m_pExifInfo->ISOequivalent < 50 ) 
						m_pExifInfo->ISOequivalent *= 200;
				}
                break;

            case TAG_COMPRESSION_LEVEL:
				if ( m_flags & EXIF_COMPRESSION_LEVEL)
					m_pExifInfo->CompressionLevel = (int)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_XRESOLUTION:
				if ( m_flags & EXIF_XRESOLUTION)
					m_pExifInfo->Xresolution = (float)ConvertAnyFormat(ValuePtr, Format);
                break;
            case TAG_YRESOLUTION:
				if ( m_flags & EXIF_YRESOLUTION)
					m_pExifInfo->Yresolution = (float)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_THUMBNAIL_OFFSET:
                ThumbnailOffset = (unsigned)ConvertAnyFormat(ValuePtr, Format);
                break;

            case TAG_THUMBNAIL_LENGTH:
                ThumbnailSize = (unsigned)ConvertAnyFormat(ValuePtr, Format);
                break;

        }

        if (Tag == TAG_EXIF_OFFSET || Tag == TAG_INTEROP_OFFSET )
		{
            unsigned char * SubdirStart;
            SubdirStart = OffsetBase + Get32u(ValuePtr);
            if ( SubdirStart < OffsetBase || 
                 SubdirStart > OffsetBase + ExifLength )
			{
#ifdef GetErrorCode                
				strcpy(m_szLastError,"Illegal subdirectory link");
#endif
				return 0;
            }
            ProcessExifDir(SubdirStart, OffsetBase, ExifLength, LastExifRefdP);
            continue;
        }
    }


    {
        /* In addition to linking to subdirectories via exif tags,
           there's also a potential link to another directory at the end
           of each directory.  This has got to be the result of a
           committee!  
        */
        unsigned char * SubdirStart;
        unsigned Offset;
        Offset = Get32u(DirStart+2+12*NumDirEntries);
        if (Offset > 0)
		{
            SubdirStart = OffsetBase + Offset;
            if (SubdirStart < OffsetBase 
                || SubdirStart > OffsetBase+ExifLength)
			{
#ifdef GetErrorCode                
				strcpy(m_szLastError,"Illegal subdirectory link");
#endif
				return 0;
            }
            ProcessExifDir(SubdirStart, OffsetBase, ExifLength, LastExifRefdP);
        }
    }

    if (ThumbnailSize && ThumbnailOffset)
	{
        if (ThumbnailSize + ThumbnailOffset <= ExifLength)
		{
			if ( m_pExifInfo->pThumbnailPointer != NULL)
			{
				delete m_pExifInfo->pThumbnailPointer;
			}
			/* The thumbnail pointer appears to be valid.  Store it. */
            m_pExifInfo->pThumbnailPointer = OffsetBase + ThumbnailOffset;
			m_pExifInfo->ThumbnailOffset = ThumbnailOffset;
            m_pExifInfo->ThumbnailSize = ThumbnailSize;
        }
    }

	return 1;
}

////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------
   Evaluate number, be it int, rational, or float from directory.
--------------------------------------------------------------------------*/
double CExifRead::ConvertAnyFormat(void * ValuePtr, int Format)
{
    double Value;
    Value = 0;

    switch(Format){
        case FMT_SBYTE:     Value = *(signed char *)ValuePtr;  break;
        case FMT_BYTE:      Value = *(unsigned char *)ValuePtr;        break;

        case FMT_USHORT:    Value = Get16u(ValuePtr);          break;
        case FMT_ULONG:     Value = Get32u(ValuePtr);          break;

        case FMT_URATIONAL:
        case FMT_SRATIONAL: 
            {
                int Num,Den;
                Num = Get32s(ValuePtr);
                Den = Get32s(4+(char *)ValuePtr);
                if (Den == 0){
                    Value = 0;
                }else{
                    Value = (double)Num/Den;
                }
                break;
            }

        case FMT_SSHORT:    Value = (signed short)Get16u(ValuePtr);  break;
        case FMT_SLONG:     Value = Get32s(ValuePtr);                break;

        /* Not sure if this is correct (never seen float used in Exif format)
         */
        case FMT_SINGLE:    Value = (double)*(float *)ValuePtr;      break;
        case FMT_DOUBLE:    Value = *(double *)ValuePtr;             break;
    }
    return Value;
}
////////////////////////////////////////////////////////////////////////////////
void CExifRead::ProcessCOM (const unsigned char * Data, int length)
{
    int ch;
    char Comment[MAX_COMMENT+1];
    int nch;
    int a;

    nch = 0;

    if (length > MAX_COMMENT) length = MAX_COMMENT; // Truncate if it won't fit in our structure.

    for (a=2;a<length;a++){
        ch = Data[a];

        if (ch == '\r' && Data[a+1] == '\n') continue; // Remove cr followed by lf.

        if ((ch>=0x20) || ch == '\n' || ch == '\t'){
            Comment[nch++] = (char)ch;
        }else{
            Comment[nch++] = '?';
        }
    }

    Comment[nch] = '\0'; // Null terminate

    //if (ShowTags) printf("COM marker comment: %s\n",Comment);

    strcpy_s(m_pExifInfo->Comments,MAX_COMMENT,Comment);
}

////////////////////////////////////////////////////////////////////////////////
void CExifRead::ProcessSOFn (const unsigned char * Data, int marker)
{
    int data_precision, num_components;

    data_precision = Data[2];
    m_pExifInfo->Height = Get16m((void*)(Data+3));
    m_pExifInfo->Width = Get16m((void*)(Data+5));
    num_components = Data[7];

    if (num_components == 3){
        m_pExifInfo->IsColor = 1;
    }else{
        m_pExifInfo->IsColor = 0;
    }

    m_pExifInfo->Process = marker;

    //if (ShowTags) printf("JPEG image is %uw * %uh, %d color components, %d bits per sample\n",
    //               ImageInfo.Width, ImageInfo.Height, num_components, data_precision);
}
////////////////////////////////////////////////////////////////////////////////

