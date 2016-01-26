

#ifndef __OVERLAY_H__
#define __OVERLAY_H__

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) ||  defined(_WIN32_WCE) || defined(WINCE)
#	ifdef OVERLAY_EXPROT
#		define OVERLAY_API	__declspec(dllexport)
#	else
#		define OVERLAY_API	__declspec(dllimport)
#	endif
#else
#	ifdef OVERLAY_EXPROT
#		define OVERLAY_API	
#	else
#		define OVERLAY_API	extern
#	endif
#endif

// 24 bit RGB888 --> 24 bit RGB2PIXEL565 ( ���COLOR����Ҫ��ֵ )
#define RGB2PIXEL565(r,g,b)  ((((r) & 0xf8) << 16) | (((g) & 0xfc) << 8) | (((b) & 0xf8)))

// 24bit RGB888 --> 16 bit RGB565
#define RGB565(r, g, b) ( (((b)>>3) & 31) + ( (((g)>>2) & 63) << 5)+( (((r)>>3) & 31) << 11))

// get r from 16bit RGB565
#define GetR565(cor565) (BYTE)(((cor565) & 0xf800) >> 8)
// get g from 16bit RGB565
#define GetG565(cor565) (BYTE)(((cor565) & 0x07e0) >> 3)
// get b from 16bit RGB565
#define GetB565(cor565) (BYTE)(((cor565) & 0x001f) << 3)

// ���Ӳ��� �ṹ��
typedef struct _BLEND_EXT_INFO{
	int alpha; 			/* LAYER ALPHA VALUE - 0:TRANSPARENT -> 255: NOT TRANSPARENT */
	int alpha1_use; 	/* ON/OFF */
	int alpha1_value; 	/* COLOR ALPHA VALUE - 0:TRANSPARENT -> 255: NOT TRANSPARENT */
	int alpha1_color; 	/* CAUTION!!! THIS IS RGB2PIXEL565 FORMAT!!! */
	int alpha2_use; 	/* ON/OFF */
	int alpha2_value; 	/* COLOR ALPHA VALUE - 0:TRANSPARENT -> 255: NOT TRANSPARENT */
	int alpha2_color; 	/* CAUTION!!! THIS IS RGB2PIXEL565 FORMAT!!! */
	int rotate;
}BLEND_EXT_INFO, *PBLEND_EXT_INFO;

// ���Ӳ��ʽ
typedef enum
{
	PF_RGB555 = 0,		// 16 bit RGB555 format
	PF_RGB565,			// 16 bit RGB565 format
	PF_RGB888			// 24 bit RGB888 format
}EM_PIXELFORMAT;

// ���Ӳ�Z��
typedef enum
{
	ZO_TOP = 0,				// �ö�
	ZO_BOTTOM			// �õ�
}ZOrderType;

// ���Ӳ����
typedef enum
{
	ZINDEX_1 = 0,		// Overlay 1
	ZINDEX_2				// Overlay 2
}ZIndex;

// IOverlay ���Ӳ�����ӿ�

class OVERLAY_API IOverlay
{
public:

	// Function name   : Init
	// Description     : ��ʼ�������Դ
	// Return type     : BOOL	( TRUE �ɹ� FALSE ʧ�� )
	// Argument        : HWND hWnd	������
	// Argument        : int x		����ʱ������Ļ�� x ����
	// Argument        : int y		����ʱ������Ļ�� y ����
	// Argument        : int width	����ʱ�Ŀ��
	// Argument        : int height	����ʱ�ĸ߶�
	// Argument        : EM_PIXELFORMAT emPixelFormat	������ʽ
	// Argument        : DWORD dwClearColor				�������õ���ɫֵ ( PF_RGB555 / PF_RGB565 16 bit ɫ | PF_RGB888 24 bit ɫ )
	// Argument        : BLEND_EXT_INFO * pBlendExt		��ϲ�������
	// 
	// Remark          : 

	virtual BOOL Init(HWND hWnd,int x,int y,int width,int height,EM_PIXELFORMAT emPixelFormat = PF_RGB565,DWORD dwClearColor = 0x0,BLEND_EXT_INFO * pBlendExt = NULL,BOOL bShowOverlay = TRUE) = 0;


	// Function name   : Uninit
	// Description     : �ͷ������Դ
	// Return type     : void 
	// Argument        : void
	// 
	// Remark          : 

	virtual void Uninit(void) = 0;


	// Function name   : Clear
	// Description     : ��������
	// Return type     : void 
	// Argument        : void
	// 
	// Remark          : Ϊ�˱��������ò���ֻ�Ի������������� ���Ҫ��ʾ�����Ľ����Ҫ���� Update

	virtual void Clear(void) = 0;


	// Function name   : Show
	// Description     : ��ʾ��������Ļ
	// Return type     : BOOL	( TRUE �ɹ� FALSE ʧ�� )
	// Argument        : BOOL bShow	TRUE ��ʾ FALSE ����
	// 
	// Remark          : 

	virtual BOOL Show(BOOL bShow) = 0;


	// Function name   : GetDC
	// Description     : �õ�������Surface DC
	// Return type     : HDC �豸������
	// Argument        : void
	// 
	// Remark          : 

	virtual HDC GetDC(void) = 0;


	// Function name   : ReleaseDC
	// Description     : �ͷŵõ���Surface DC
	// Return type     : void 
	// Argument        : HDC& hDC �豸������
	// 
	// Remark          : 

	virtual void ReleaseDC(HDC& hDC) = 0;


	// Function name   : Update
	// Description     : �û�������������������
	// Return type     : BOOL	( TRUE �ɹ� FALSE ʧ�� )
	// Argument        : void
	// 
	// Remark          : 

	virtual BOOL Update(void) = 0;


	// Function name   : SetPos
	// Description     : ���õ��Ӳ���ʾλ��
	// Return type     : BOOL	( TRUE �ɹ� FALSE ʧ�� )
	// Argument        : int x		��Ļ x ����
	// Argument        : int y		��Ļ y ����
	// Argument        : int width	��ʾ���
	// Argument        : int height	��ʾ�߶�
	// 
	// Remark          : 

	virtual BOOL SetPos(int x,int y,int width,int height) = 0;


	// Function name   : SetZOrder
	// Description     : ���õ��Ӳ�Z��
	// Return type     : BOOL	( TRUE �ɹ� FALSE ʧ�� )
	// Argument        : ZOrderType emZOrder	Z��
	// 
	// Remark          : 

	virtual BOOL SetZOrder(ZOrderType emZOrder) = 0;


	// Function name   : SetClearColor
	// Description     : ����������ɫ
	// Return type     : BOOL	( TRUE �ɹ� FALSE ʧ�� )
	// Argument        : DWORD dwClearColor	�������õ���ɫֵ ( PF_RGB555 / PF_RGB565 16 bit ɫ | PF_RGB888 24 bit ɫ )
	// 
	// Remark          : 

	virtual BOOL SetClearColor(DWORD dwClearColor) = 0;


	// Function name   : SetBlendExt
	// Description     : ���û�ϲ���
	// Return type     : BOOL	( TRUE �ɹ� FALSE ʧ�� )
	// Argument        : BLEND_EXT_INFO * pBlendExt		��ϲ�������
	// 
	// Remark          : 

	virtual BOOL SetBlendExt(BLEND_EXT_INFO * pBlendExt) = 0;


	// Function name   : GetOverlayDisplayAddress
	// Description     : �õ����Ӳ�����������ַ ��CEU�������� ����ַ��д�������ݺ� ���� Update ��������
	// Return type     : DWORD �����ַ
	// Argument        : UINT8 uIndex		��������� �ܹ����������� ���� 0: һ�������� 1: ����������
	// 
	// Remark          : 

	virtual DWORD GetPhysicalBackDisplayAddress(UINT8 uIndex) = 0;


	// Function name   : FlipPhysical
	// Description     : �����ַ��ҳ����
	// Return type     : BOOL	( TRUE �ɹ� FALSE ʧ�� )
	// Argument        : UINT8 uIndex		��������� �ܹ����������� ���� 0: һ�������� 1: ����������
	// 
	// Remark          : 

	virtual BOOL FlipPhysical(UINT8 uIndex) = 0;


	// Function name   : BitBltDC
	// Description     : ����DC Surface�����Ӳ���
	// Return type     : BOOL	( TRUE �ɹ� FALSE ʧ�� )
	// Argument        : RECT rcDest			Ŀ�귶Χ
	// Argument        : HDC hSrcDC				ԴHDC ������ GDI HDC���
	// Argument        : RECT rcSrc				Դ��Χ
	// Argument        : BOOL bUseColorKey		�Ƿ����ùؼ�ɫ
	// Argument        : DWORD dwColorKey		�ؼ�ɫ��ɫֵ
	// 
	// Remark          : 

	virtual BOOL BitBltDC(RECT rcDest,HDC hSrcDC,RECT rcSrc,BOOL bUseColorKey,DWORD dwColorKey) = 0;


	// Function name   : CopyStream
	// Description     : ����Surface�����������Ӳ���
	// Return type     : BOOL	( TRUE �ɹ� FALSE ʧ�� )
	// Argument        : LPVOID pSrcBuf			����Surface������
	// Argument        : int dst_x				Ŀ�� x ����
	// Argument        : int dst_y				Ŀ�� y ����
	// Argument        : int copy_width			Ŀ�� ���
	// Argument        : int copy_height		Ŀ�� �߶�
	// Argument        : int src_width_byte		����Surface����ֽ���
	// Argument        : int src_height			����Surfaceͼ��߶�
	// Argument        : BOOL bUseColorKey		�Ƿ�ʹ�ùؼ�ɫ
	// Argument        : DWORD dwColorKey		�ؼ�ɫ��ɫֵ
	// 
	// Remark          : 

	virtual BOOL CopyStream(LPVOID pSrcBuf,int dst_x,int dst_y,int copy_width,int copy_height,int src_width_byte,int src_height,BOOL bUseColorKey,DWORD dwColorKey) = 0;
};


// Function name   : Overlay_CreateInstance
// Description     : �������Ӳ������ʵ��
// Return type     : IOverlay *	ʵ��������ָ��
// Argument        : void
// 
// Remark          : 

OVERLAY_API IOverlay * Overlay_CreateInstance(void);



// Function name   : Overlay_ReleaseInstance
// Description     : �ͷŴ�����ʵ��
// Return type     : void 
// Argument        : IOverlay * pIOverlay	ʵ������ָ��
// 
// Remark          : 

OVERLAY_API void Overlay_ReleaseInstance(IOverlay * pIOverlay);


// Function name   : Overlay_SetBlendExt
// Description     : ֱ��������һ��Ļ�ϲ���
// Return type     : BOOL	( TRUE �ɹ� FALSE ʧ�� )
// Argument        : ZIndex emZIndex				���Ӳ����
// Argument        : BLEND_EXT_INFO * pBlendExt		��ϲ�������
// 
// Remark          : 

OVERLAY_API BOOL Overlay_SetBlendExt(ZIndex emZIndex,BLEND_EXT_INFO * pBlendExt);

#endif	/*__UTILITY_PUBLIC_H__*/