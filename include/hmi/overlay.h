

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

// 24 bit RGB888 --> 24 bit RGB2PIXEL565 ( 混合COLOR所需要的值 )
#define RGB2PIXEL565(r,g,b)  ((((r) & 0xf8) << 16) | (((g) & 0xfc) << 8) | (((b) & 0xf8)))

// 24bit RGB888 --> 16 bit RGB565
#define RGB565(r, g, b) ( (((b)>>3) & 31) + ( (((g)>>2) & 63) << 5)+( (((r)>>3) & 31) << 11))

// get r from 16bit RGB565
#define GetR565(cor565) (BYTE)(((cor565) & 0xf800) >> 8)
// get g from 16bit RGB565
#define GetG565(cor565) (BYTE)(((cor565) & 0x07e0) >> 3)
// get b from 16bit RGB565
#define GetB565(cor565) (BYTE)(((cor565) & 0x001f) << 3)

// 叠加层混合 结构体
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

// 叠加层格式
typedef enum
{
	PF_RGB555 = 0,		// 16 bit RGB555 format
	PF_RGB565,			// 16 bit RGB565 format
	PF_RGB888			// 24 bit RGB888 format
}EM_PIXELFORMAT;

// 叠加层Z序
typedef enum
{
	ZO_TOP = 0,				// 置顶
	ZO_BOTTOM			// 置底
}ZOrderType;

// 叠加层序号
typedef enum
{
	ZINDEX_1 = 0,		// Overlay 1
	ZINDEX_2				// Overlay 2
}ZIndex;

// IOverlay 叠加层操作接口

class OVERLAY_API IOverlay
{
public:

	// Function name   : Init
	// Description     : 初始化相关资源
	// Return type     : BOOL	( TRUE 成功 FALSE 失败 )
	// Argument        : HWND hWnd	窗体句柄
	// Argument        : int x		创建时所在屏幕的 x 坐标
	// Argument        : int y		创建时所在屏幕的 y 坐标
	// Argument        : int width	创建时的宽度
	// Argument        : int height	创建时的高度
	// Argument        : EM_PIXELFORMAT emPixelFormat	创建格式
	// Argument        : DWORD dwClearColor				清屏所用的颜色值 ( PF_RGB555 / PF_RGB565 16 bit 色 | PF_RGB888 24 bit 色 )
	// Argument        : BLEND_EXT_INFO * pBlendExt		混合操作设置
	// 
	// Remark          : 

	virtual BOOL Init(HWND hWnd,int x,int y,int width,int height,EM_PIXELFORMAT emPixelFormat = PF_RGB565,DWORD dwClearColor = 0x0,BLEND_EXT_INFO * pBlendExt = NULL,BOOL bShowOverlay = TRUE) = 0;


	// Function name   : Uninit
	// Description     : 释放相关资源
	// Return type     : void 
	// Argument        : void
	// 
	// Remark          : 

	virtual void Uninit(void) = 0;


	// Function name   : Clear
	// Description     : 清屏操作
	// Return type     : void 
	// Argument        : void
	// 
	// Remark          : 为了避免闪屏该操作只对缓存区进行清屏 如果要显示清屏的结果需要调用 Update

	virtual void Clear(void) = 0;


	// Function name   : Show
	// Description     : 显示和隐藏屏幕
	// Return type     : BOOL	( TRUE 成功 FALSE 失败 )
	// Argument        : BOOL bShow	TRUE 显示 FALSE 隐藏
	// 
	// Remark          : 

	virtual BOOL Show(BOOL bShow) = 0;


	// Function name   : GetDC
	// Description     : 得到缓存区Surface DC
	// Return type     : HDC 设备上下文
	// Argument        : void
	// 
	// Remark          : 

	virtual HDC GetDC(void) = 0;


	// Function name   : ReleaseDC
	// Description     : 释放得到的Surface DC
	// Return type     : void 
	// Argument        : HDC& hDC 设备上下文
	// 
	// Remark          : 

	virtual void ReleaseDC(HDC& hDC) = 0;


	// Function name   : Update
	// Description     : 让缓冲区的数据上屏操作
	// Return type     : BOOL	( TRUE 成功 FALSE 失败 )
	// Argument        : void
	// 
	// Remark          : 

	virtual BOOL Update(void) = 0;


	// Function name   : SetPos
	// Description     : 设置叠加层显示位置
	// Return type     : BOOL	( TRUE 成功 FALSE 失败 )
	// Argument        : int x		屏幕 x 坐标
	// Argument        : int y		屏幕 y 坐标
	// Argument        : int width	显示宽度
	// Argument        : int height	显示高度
	// 
	// Remark          : 

	virtual BOOL SetPos(int x,int y,int width,int height) = 0;


	// Function name   : SetZOrder
	// Description     : 设置叠加层Z序
	// Return type     : BOOL	( TRUE 成功 FALSE 失败 )
	// Argument        : ZOrderType emZOrder	Z序
	// 
	// Remark          : 

	virtual BOOL SetZOrder(ZOrderType emZOrder) = 0;


	// Function name   : SetClearColor
	// Description     : 设置清屏颜色
	// Return type     : BOOL	( TRUE 成功 FALSE 失败 )
	// Argument        : DWORD dwClearColor	清屏所用的颜色值 ( PF_RGB555 / PF_RGB565 16 bit 色 | PF_RGB888 24 bit 色 )
	// 
	// Remark          : 

	virtual BOOL SetClearColor(DWORD dwClearColor) = 0;


	// Function name   : SetBlendExt
	// Description     : 设置混合操作
	// Return type     : BOOL	( TRUE 成功 FALSE 失败 )
	// Argument        : BLEND_EXT_INFO * pBlendExt		混合操作设置
	// 
	// Remark          : 

	virtual BOOL SetBlendExt(BLEND_EXT_INFO * pBlendExt) = 0;


	// Function name   : GetOverlayDisplayAddress
	// Description     : 得到叠加层物理缓存区地址 供CEU解码上屏 往地址中写入了数据后 调用 Update 方可上屏
	// Return type     : DWORD 物理地址
	// Argument        : UINT8 uIndex		缓存区序号 总共两个缓存区 这里 0: 一级缓存区 1: 二级缓存区
	// 
	// Remark          : 

	virtual DWORD GetPhysicalBackDisplayAddress(UINT8 uIndex) = 0;


	// Function name   : FlipPhysical
	// Description     : 物理地址换页功能
	// Return type     : BOOL	( TRUE 成功 FALSE 失败 )
	// Argument        : UINT8 uIndex		缓存区序号 总共两个缓存区 这里 0: 一级缓存区 1: 二级缓存区
	// 
	// Remark          : 

	virtual BOOL FlipPhysical(UINT8 uIndex) = 0;


	// Function name   : BitBltDC
	// Description     : 拷贝DC Surface到叠加层上
	// Return type     : BOOL	( TRUE 成功 FALSE 失败 )
	// Argument        : RECT rcDest			目标范围
	// Argument        : HDC hSrcDC				源HDC 即传入 GDI HDC句柄
	// Argument        : RECT rcSrc				源范围
	// Argument        : BOOL bUseColorKey		是否启用关键色
	// Argument        : DWORD dwColorKey		关键色颜色值
	// 
	// Remark          : 

	virtual BOOL BitBltDC(RECT rcDest,HDC hSrcDC,RECT rcSrc,BOOL bUseColorKey,DWORD dwColorKey) = 0;


	// Function name   : CopyStream
	// Description     : 拷贝Surface数据流到叠加层上
	// Return type     : BOOL	( TRUE 成功 FALSE 失败 )
	// Argument        : LPVOID pSrcBuf			输入Surface数据流
	// Argument        : int dst_x				目标 x 坐标
	// Argument        : int dst_y				目标 y 坐标
	// Argument        : int copy_width			目标 宽度
	// Argument        : int copy_height		目标 高度
	// Argument        : int src_width_byte		输入Surface宽度字节数
	// Argument        : int src_height			输入Surface图像高度
	// Argument        : BOOL bUseColorKey		是否使用关键色
	// Argument        : DWORD dwColorKey		关键色颜色值
	// 
	// Remark          : 

	virtual BOOL CopyStream(LPVOID pSrcBuf,int dst_x,int dst_y,int copy_width,int copy_height,int src_width_byte,int src_height,BOOL bUseColorKey,DWORD dwColorKey) = 0;
};


// Function name   : Overlay_CreateInstance
// Description     : 创建叠加层操作类实例
// Return type     : IOverlay *	实例化对象指针
// Argument        : void
// 
// Remark          : 

OVERLAY_API IOverlay * Overlay_CreateInstance(void);



// Function name   : Overlay_ReleaseInstance
// Description     : 释放创建的实例
// Return type     : void 
// Argument        : IOverlay * pIOverlay	实例对象指针
// 
// Remark          : 

OVERLAY_API void Overlay_ReleaseInstance(IOverlay * pIOverlay);


// Function name   : Overlay_SetBlendExt
// Description     : 直接设置哪一层的混合操作
// Return type     : BOOL	( TRUE 成功 FALSE 失败 )
// Argument        : ZIndex emZIndex				叠加层序号
// Argument        : BLEND_EXT_INFO * pBlendExt		混合操作设置
// 
// Remark          : 

OVERLAY_API BOOL Overlay_SetBlendExt(ZIndex emZIndex,BLEND_EXT_INFO * pBlendExt);

#endif	/*__UTILITY_PUBLIC_H__*/