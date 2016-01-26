

#ifndef _RE_DRAW__
#define _RE_DRAW__

#include "RenderingEngine.h"
#include "Surface.h"
#include "KCFont.h"
#include "Brush.h"


#define	THEME_COUNT		3
//#include "KSingleton.h"

class CReDraw : public IReDraw
{
public:
    CReDraw();
    ~CReDraw();

public:
    /*
	* 函数功能:initialize the interface.
	* 参    数:无
	* 返 回 值:无
	*/
    ERRINFO Initialize();

    /*
	* 函数功能:建一个表面用于绘制,指定大小和颜色模式
	* 参    数:
	*      lWidth  [in] :表面宽度
	*      lHeight [in] :表面高度
	*      dwColorFormat  [in] :点格式
	* 返 回 值:表面指针
	*/
#if	defined(SCREEN_COLORBIT16)
	IReSurface* CreateSurface(HLONG lWidth, HLONG lHeight, HDWORD dwColorFormat = RE_COLOR565, HBOOL bUseDraw = FALSE, HBOOL bCreateDC = FALSE);
#else
    IReSurface* CreateSurface(HLONG lWidth, HLONG lHeight, HDWORD dwColorFormat = RE_COLOR888, HBOOL bUseDraw = FALSE, HBOOL bCreateDC = FALSE);
#endif // _DEBUG
	IReSurface* CreateTTFFontSurface(HINT font_width, HINT font_height, HCFont* pFont, HDWORD dwFormat, const HCHAR* str, HINT strWidth = 0);
	IReSurface* CreateSurfaceFromKtcStream(const HBYTE* pMemAddr);
	IReSurface* CreateSurfaceFromJpegStream(const HBYTE* pMemAddr, HINT MemSize);
	virtual IReSurface* CreateSurfaceFromBmpStream(const HBYTE* pMemAddr, HINT nMemSize);

	//IReSurface* CreateSurfaceFromRGB888Stream(const kn_byte* pMemAddr, kn_int width, kn_int height, kn_int nSize, kn_bool bUseErrorDiffuse = TRUE);
	void ModifyKtcStreamSurface(IN const HBYTE* pMemAddr, OUT IReSurface* pKtcStreamSur);

    /*
	* 函数功能:从文件中创建表面.如果文件是24位色,格式指定RE_COLOR565,则自动转为16位表面
	* 参    数:
	*      strFileName [in] :文件名
	*      dwColorFormat  [in] :点格式
	* 返 回 值:表面指针
	*/
    IReSurface* CreateSurfaceFromFile(const HString& pFileName, HDWORD dwColorFormat);
	//IReSurface* CreateSurfaceInErrorDiffuse(IReSurface* pSurf);
	IReSurface* CreateSurfaceFrom565Mem(const HBYTE* pMemAddr, HINT width, HINT height);
    /*
	* 函数功能:取得字体的Size
	* 参    数:
	*      iWidth   [out] :字体宽度
	*      iHeight  [out] :字体高度
	*      iIndex   [in]: 字体索引
	* 返 回 值:无
	*/
    void GetFontSize(HINT &iWidth, HINT &iHeight, HINT iIndex);

	/*
	* 函数功能:取得字体
	* 参    数:
	*      iIndex   [in]: 字体索引
	* 返 回 值:字体
	*/
    HCFont* GetFont(HINT iIndex);

	//重新加载字体，还是只加载一个字体文件
	void ReLoadFont(HINT iThemeIndex);

	/*
	* 函数功能:initialize alpha table
	* 参    数:无
	* 返 回 值:无
	*/ 
	void InitAlpha();

	/*
	* 函数功能:get alpha table head point
	* 参    数:无
	* 返 回 值:table head point
	*/
	HBYTE** GetTransparentTable();

	/*
	* 函数功能:get alpha table head point
	* 参    数:无
	* 返 回 值:table head point
	*/
	//remove by cxl
	//kn_int**  GetAlphaTable();

	REBrushGenerate* GetBrush(HINT ID)
	{
		return brushMgr.GetBrush(ID);
	}

protected:
	BOOL CreateShareMemory(HINT nThemeIndex, HLONG& nMemSize);

protected:
    // surface使用的字体, 所有surface都有一个指针指向这个变量,现在只支持一种字体,如以后要支持多个,可扩充
    vector<HCFont*> m_font;

	// alpha table
	HBYTE* m_RGB_Transparent_table[TRANSPARENTLEVEL + 1];
	//remove by cxl
	//kn_int*  m_RGB_Alpha_table[256];

	BrushManager brushMgr;
	//kn_byte	m_byCurrentTheme[THEME_COUNT];	//	当前主题

	HCFont*		m_pThemeFont[THEME_COUNT];

	//创建共享内存，用于存放字体
	HANDLE m_hFontShareMapping[3];
	void* m_pFontShareMem[3];

	//用于记录三个字体共享内存大小的共享内存
	HANDLE m_hFontSizeShareMapping;
	void* m_pFontSizeShareMem;
};

#endif // _RE_DRAW__
