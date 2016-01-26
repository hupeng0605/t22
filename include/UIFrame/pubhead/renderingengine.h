

#ifndef _RENDERING_ENGINE_H__
#define _RENDERING_ENGINE_H__

#include <stdlib.h>
#include <TCHAR.H>
#include <math.h>
#include "KCFont.h"
#include "type.h"
#include "Pubhead.h"
#include "KNFile.h"
#include "KCColorMatrix.h"

#define USE_4Bit_MASK

//FreeType库文件

#pragma warning (disable: 4183) //这个会报 RECTANGLE 的set函数错误, 没有必要
#pragma warning (disable: 4018)
#pragma warning (disable: 4244)

//FreeType库文件
#include <ft2build.h>
#include FT_FREETYPE_H

#pragma warning (disable: 4183) //这个会报 RECTANGLE 的set函数错误, 没有必要

#ifndef WIN32           // if we are not under windows os.
#define RGB(r,g,b)      ((HDWORD)(((HBYTE)(r)|((HWORD)((HBYTE)(g))<<8))|(((HDWORD)(HBYTE)(b))<<16)))
#define GetRValue(rgb)  ((HBYTE)(rgb))
#define GetGValue(rgb)  ((HBYTE)(((HWORD)(rgb)) >> 8))
#define GetBValue(rgb)  ((HBYTE)((rgb)>>16))
#endif // WIN32

//颜色转换宏
#define RGB555(r, g, b) ( (((b)>>3) & 31) + ( (((g)>>3) & 31) << 5)+( (((r)>>3) & 31) << 10))
#define RGB565(r, g, b) ( (((b)>>3) & 31) + ( (((g)>>2) & 63) << 5)+( (((r)>>3) & 31) << 11))
#define RGB888(r, g, b) ( ((b) & 0xff) + (((g) & 0xff) << 8) + (((r) & 0xff) << 16))

//分离颜色宏
#define GetRPart_555(color) (HBYTE)((((color)>>10) & 31)<<3)
#define GetGPart_555(color) (HBYTE)((((color)>>5) & 31)<<3)
#define GetBPart_555(color) (HBYTE)(((color) & 31)<<3)

//#define GetRPart_565(color) (((color>>11) & 31)<<3)
#define GetRPart_565(color) (HBYTE)(((color) & 63488) >> 8)
//#define GetGPart_565(color) (((color>>5) & 63)<<2)
#define GetGPart_565(color) (HBYTE)(((color) & 2016) >> 3)
#define GetBPart_565(color) (HBYTE)(((color) & 31) << 3)

#define GetRPart_888(color) (HBYTE)(((color) & 0xff0000) >> 16)
#define GetGPart_888(color) (HBYTE)(((color) & 0xff00) >> 8)
#define GetBPart_888(color) (HBYTE)((color) & 0xff)

// 统一安全删除操作
// delete an object.
#define SAFE_DELETE(obj) if((obj) != NULL) {delete (obj); (obj) = NULL;}
// delete a group of objects.
#define SAFE_DELETE_GROUP(pObject) if((pObject) != NULL) {delete[]  (pObject); (pObject) = NULL;}
// delete a class or release an interface.
#define SURFACE_RELEASE(obj) if(obj) {(obj)->Release(); delete (obj); (obj) = NULL;}

#define RE_PI       3.14159265359 //π
#define RE_DEGREE   0.01745329252 //度数

// 透明度级别,可以为2的n次方,现在设置为16,最大可设255级
#define TRANSPARENTLEVEL 16
//透明度位操作数 为log2(TRANSPARENTLEVEL),255时为8,为了在透明运算时避免除法
#define TRANSBIT 4


typedef HINT ERRINFO; // return value (error info).
//返回值
#define RE_OK                   1
#define RE_ERROR                0


#define RE_COLOR888             1   // RGB24.
#define RE_COLOR555             2   // mainly used in embedded device.
#define RE_COLOR32              3   // RGBA. A为Alpha通道值
#define RE_COLOR565             4   // same as COLOR555.
#define RE_SOFT_COUNT           5
#define RE_COLOR256             6
#define RE_COLORPALETTE			7	// 调色板模式

/*****************************************************************************
// the following macro will be used in class CReDisplay.
*****************************************************************************/

#define RE_DISPLAY_FULLSCREEN   1   // display fullscreen.
#define RE_DISPLAY_WINDOW       0   // display in window. 窗口模式现在没有考虑

/*****************************************************************************
// the following macro will be used in class CReSurface.
*****************************************************************************/
// 文字样式
#define RE_TS_NORMAL            0x00000000  // 常规样式,文字对坐标左对齐
#define RE_TS_STROKE            0x00000001  // 文字有边缘线 不和BK连用
#define RE_TS_BK                0x00000002  // 文字有背景颜色 
#define RE_TS_CENTER            0x00000004  // 文字对坐标居中 不和NORMAL连用
#define RE_TS_BOLD              0x00000008  // 粗体文字
#define RE_TS_SHADOW            0x00000010  // 阴影文字
#define RE_TS_SOFT_SHADOW       0x00000020  // 柔化阴影文字
#define RE_TS_RIGHT             0x00000040  // 文字坐标右对齐
#define RE_TS_END_ELLIPSIS		0x00000080	// 文本超过部分显示为省略号

#define RE_HQ_LINE              0x00000008  // 高质量反走样线
// 线条样式.
#define RE_LS_NORMAL            0x00000000  // 常规线样式.
#define RE_LS_HATCH             0x00000001  // 有边缘线.
#define RE_LS_DASH              0x00000002  // 虚线.
#define RE_LS_TRANS             0x00000004  // 透明线.
#define RE_LS_SHADOW            0x00000008  // 阴影线.
#define RE_LS_NORMALS           0x00000010  // 常规线样式(反走样).
#define RE_LS_HATCHS            0x00000020  // 有边缘线(反走样).
#define RE_BIRDVIEW_LINE        0x00000100
#define RE_AGGPOLYLINE          0x00000200
#define RE_LS_ALPHA_AGG         0x00000400
#define RE_LS_BRUSH_LINE        0x00001000  // 增加

// 多边形填充样式
#define RE_PG_NORMAL            0X00000001 // 常规样式
#define RE_PG_SHADOW            0x00000002 // 阴影样式
#define RE_PG_TEXTURE           0x00000004 // 纹理样式
#define RE_PG_ALPHA             0x00000008 // 纹理样式



//判断两矩形交集(或直线和矩形)时使用的宏定义 reClipLine 函数使用
#define RE_MUST_OUT     0  //一定不相交
#define RE_MUST_IN      1  //A完全在B内部
#define RE_OVER_OR_OUT  2  //A B有相交部分, 对于直线, 也有可能完全不相交

#define FEQUAL(a,b) (fabs((a) - (b)) < 0.0001 ? 1 : 0)

// 判断线形填充矩形的方式
enum LINERTYPE
{
    RE_RF_VLINEAR = 0 ,//垂直线形填充
    RE_RF_HLINEAR = 1, //水平线形填充
    RE_RF_CLINEAR = 2, //对角线形填充
    RE_RF_RADIATE = 3, //辐射填充
    RE_AF_VLINEAR = 4, //垂直alpha填充
    RE_AF_HLINEAR = 5  //水平alpha填充
};

//绘制粗线时,判断端点类型
enum e_line_cap
{
    square_cap,
    round_cap
};
//-----------------------------------------------------------------------------------------------------------
// Some structs.
//-----------------------------------------------------------------------------------------------------------
struct REPOINT
{
    HLONG x;
    HLONG y;
    REPOINT() {};
    REPOINT(HLONG tx, HLONG ty) : x(tx), y(ty) {};

    REPOINT(const REPOINT& point)
    {
        x = point.x;
        y = point.y;
    }

    REPOINT& operator=(const REPOINT& point)
    {
        if (this == &point) return *this;

        x = point.x;
        y = point.y;
        return *this;
    };
};
typedef REPOINT RESIZE;

struct UICORE_DLL_API RECOLOR
{
    HBYTE r;
    HBYTE g;
    HBYTE b;
    HBYTE a;
    HWORD rgb16;
    RECOLOR()
    {
        a = 255;
    };
    RECOLOR(HBYTE r0, HBYTE g0, HBYTE b0, HWORD rgb = 0)
    {
        Set(r0, g0, b0, rgb);
        a = 255;
    };

    void Set(HBYTE r0, HBYTE g0, HBYTE b0, HWORD rgb = 0)
    {//因为 kn_word 不支持负数,所以只有使用0值判断,如果rgb要设为0, r,g,b也需要为0
        r = r0;
        g = g0;
        b = b0;

        if (rgb == 0)
        {
            rgb16 = RGB565(r0, g0, b0);
        }
        else
        {
            rgb16 = rgb;
        }
    };

    void SetARGB(HBYTE a0, HBYTE r0, HBYTE g0, HBYTE b0)
    {
        r = r0;
        g = g0;
        b = b0;
        a = a0;
    }

    //从数组中取得颜色
    inline void pack(HBYTE* data, HINT type)
    {

        switch (type)
        {
        case RE_COLOR555:
        {
            HWORD color = *(HWORD*)data;
            r = GetRPart_555(color);
            g = GetGPart_555(color);
            b = GetBPart_555(color);
            a = 255;
        }
        break;
        case RE_COLOR565:
        {
            HWORD color = *(HWORD*)data;
            r = GetRPart_565(color);
            g = GetGPart_565(color);
            b = GetBPart_565(color);
            a = 255;
        }
        break;
        case RE_COLOR888:
            r = data[2];
            g = data[1];
            b = data[0];
            a = 255;
            break;
        case RE_COLOR32:
            r = data[2];
            g = data[1];
            b = data[0];
            a = data[3];
            break;
        default:
            break;
        }
    };
    //把当前颜色值传进内存
    inline void unpack(HBYTE* data, HINT type)
    {
        RECOLOR color;
        color.pack(data, type);
        HINT alphaDest;
        HBYTE r0, g0, b0, a0;
        alphaDest = (a << 8) + (color.a << 8) - a * color.a;

        if (alphaDest != 0)
        {
            r0 = (HBYTE)((color.r * (255 - a) * color.a + (r << 8) * a) / alphaDest) & 0xff;
            g0 = (HBYTE)((color.g * (255 - a) * color.a + (g << 8) * a) / alphaDest) & 0xff;
            b0 = (HBYTE)((color.g * (255 - a) * color.a + (b << 8) * a) / alphaDest) & 0xff;
        }
        else
        {
            return;
        }

        a0 = (HBYTE)(alphaDest >> 8) & 0xff;

        switch (type)
        {
        case RE_COLOR555:
            *(HWORD*)data = RGB555(r0, g0, b0);
            break;
        case RE_COLOR565:
            *(HWORD*)data = RGB565(r0, g0, b0);
            break;
        case RE_COLOR888:
            data[0] = b0;
            data[1] = g0;
            data[2] = r0;
            break;
        case RE_COLOR32:
            data[0] = b0;
            data[1] = g0;
            data[2] = r0;
            data[3] = a0;
            break;
        default:
            break;
        }

    };
    RECOLOR& operator=(const RECOLOR& color)
    {
        if (this == &color) return *this;

        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
        rgb16 = color.rgb16;
        return *this;
    };

    HBOOL operator==(const RECOLOR& color)
    {
        if (color.r == this->r &&
            color.g == this->g &&
            color.b == this->b &&
            color.a == this->a)
        {
            return TRUE;
        }

        return FALSE;
    }
};

/*******************************************************
// struct : RECTANGLE.
// same as the struct RECT defined in "wTypes.h".
*******************************************************/
//对于矩形结构, top和bottom谁大谁小是个值得注意的问题
//对于经纬度, (0,0)是左下角, top > bottom
//对于窗口及位图坐标系, (0,0)是左上角, top < bottom
//而在CDC的内存里面,内存以左下角为0,0点
//在这里,构造函数赋值,保证了top > bottom 逻辑坐标可以采用这种赋值方法
//对于绘制引擎, 采用 (0,0)是左上角, 使用 set函数赋值, 不对t b 进行校验
//同windows的SetRect函数一至
struct UICORE_DLL_API RECTANGLE
{
    HLONG left;
    HLONG top;
    HLONG right;
    HLONG bottom;

    RECTANGLE()
    {
        left    = 0;
        right   = 0;
        bottom  = 0;
        top     = 0;
    }
    RECTANGLE(HLONG l, HLONG b, HLONG r, HLONG t)
    {
        left    = l < r ? l : r;
        right   = r > l ? r : l;
        bottom  = b < t ? b : t;
        top     = t > b ? t : b;
    }
    void set(HLONG l, HLONG t, HLONG r, HLONG b)
    {
        left    = l;
        top     = t;
        right   = r;
        bottom  = b;
    }
};

struct KBIRDVIEWPARA
{
    int g_xc, g_yc, g_zc, g_lc;
};
//definition of brush
enum KBRUSHTYPE
{
    BRUSH_CIRCL,
    BRUSH_SQUARE
};

struct BrushBuffer
{
    HBYTE* byMask; //透明度掩码
    HINT width;
    HINT height;
    BrushBuffer()
    {
        byMask = NULL;
        width = height = 0;
    }
};

struct REBrush
{
    BrushBuffer* buff;
    HINT space;
};

struct REBrushGenerate
{
    REBrush* instant;
    KBRUSHTYPE shape;
    HFLOAT                  radius;
    HINT                    spikes;       /* 2 - 20     */
    HFLOAT                  hardness;     /* 0.0 - 1.0  */
};

// definition of all interfaces.
//-----------------------------------------------------------------------------------------------------------

struct IReDraw;
struct IReDisplay;
struct IReSurface;
class  CReBitmapFont;
class  HCFont;

/*******************************************************
// interface : Draw. 接口类
*******************************************************/
struct UICORE_DLL_API IReDraw
{
public:
    virtual ~IReDraw() {};

    // initialize the interface.
    virtual ERRINFO Initialize() = 0;
    virtual IReSurface* CreateTTFFontSurface(HINT font_width, HINT font_height, HCFont* pFont, HDWORD dwFormat, const HCHAR* str, HINT strWidth = 0) = 0;
    // 创建一个表面用于绘制，指定大小和颜色模式
#if defined(SCREEN_COLORBIT16)
	virtual IReSurface* CreateSurface(HLONG iWidth, HLONG iHeight, HDWORD dwColorFormat = RE_COLOR565, HBOOL bUseDraw = FALSE, HBOOL bCreateDC = FALSE) = 0;
#else
    virtual IReSurface* CreateSurface(HLONG iWidth, HLONG iHeight, HDWORD dwColorFormat = RE_COLOR888, HBOOL bUseDraw = FALSE, HBOOL bCreateDC = FALSE) = 0;
#endif
    // 从内存流中创建一个表面
    virtual IReSurface* CreateSurfaceFromKtcStream(const HBYTE* pMemAddr) = 0;
    virtual IReSurface* CreateSurfaceFromJpegStream(const HBYTE* pMemAddr, HINT MemSize) = 0;
	virtual IReSurface* CreateSurfaceFromBmpStream(const HBYTE* pMemAddr, HINT nMemSize) = 0;
	//从RGB888的内存流创建一个采用误差扩散处理过的RGB565表面
	/*virtual IReSurface* CreateSurfaceFromRGB888Stream(const HBYTE* pMemAddr, HINT width, HINT height, HINT nSize, HBOOL bUseErrorDiffuse = TRUE) = 0;*/
	virtual IReSurface* CreateSurfaceFrom565Mem(const HBYTE* pMemAddr, HINT width, HINT height) = 0;
	//virtual IReSurface* CreateSurfaceInErrorDiffuse(IReSurface* pSurf) = 0;
    // 修改一个表面
    virtual void ModifyKtcStreamSurface(IN const HBYTE* pMemAddr, OUT IReSurface* pKtcStreamSur) = 0;

    // 从文件中创建表面.如果文件是24位色,格式指定RE_COLOR565,则自动转为16位表面
#if defined(SCREEN_COLORBIT16)
	virtual IReSurface* CreateSurfaceFromFile(const HString& pFileName, HDWORD dwColorFormat = RE_COLOR565) = 0;
#else
    virtual IReSurface* CreateSurfaceFromFile(const HString& pFileName, HDWORD dwColorFormat = RE_COLOR888) = 0;
#endif
    virtual void GetFontSize(HINT &iWidth, HINT &iHeight, HINT iIndex) = 0;
    virtual HCFont* GetFont(HINT iIndex) = 0;

	//重新加载字体，还是只加载一个矢量字体文件，根据配置文件的索引加载字体库
	virtual void ReLoadFont(HINT iThemeIndex) = 0;
	
	virtual HBYTE** GetTransparentTable() = 0;
	//virtual HINT**  GetAlphaTable() = 0;

	virtual REBrushGenerate* GetBrush(HINT ID) = 0;
};


/*******************************************************
// interface : Surface.
*******************************************************/

struct UICORE_DLL_API IReSurface
{
public:
    virtual ~IReSurface() {};
    // 释放surface资源,析构函数会调用这个函数,所以直接删除对象也可以,可以不显性调用.
    //
    virtual ERRINFO Release() = 0;

    // 使用指定颜色清除表面 color.
    //
    virtual ERRINFO Clear(HBYTE r, HBYTE g, HBYTE b) = 0;

    // 使用指定颜色快速清除表面,只能设置黑,白或者灰度,如果设置灰度色,建议使用这个函数
    //
    virtual ERRINFO ClearFast(HBYTE v) = 0;

    // 取得表面的内存指针数据.
    virtual void* GetRealSurf() = 0;
    // 取得宽度,像素单位.
    //
    virtual HDWORD GetWidth() = 0;

    // 取得高度,像素单位
    //
    virtual HDWORD GetHeight() = 0;

    // 取得像素颜色
    virtual RECOLOR GetPixelColor(HLONG x, HLONG y) = 0;

    // 取得内存数据块大小
    virtual HINT GetMemDataLen() = 0;

    //取得透明度的值
    virtual HBYTE GetTransparency() = 0;

    // 取得HDC
    virtual HDC GetHDC() = 0;
    //取得字体
    virtual HCFont* GetFont() = 0;
    // 设置透明键值.如果表面是24位,取前RGB三个值,如果是16位色,取后面RGB16的值
    // 为了保持兼容性,提供该函数,但键值一般应从图片文件中读出,不建议在程序中设置
    // 代码中写死颜色值不灵活
    virtual void SetColorKey(HBYTE r, HBYTE g, HBYTE b, HWORD rgb16 = -1) = 0;

    // 设置图片透明度,0-TRANSPARENTLEVEL 之间取值,设为0表示透明度为0, TRANSPARENTLEVEL为不透明,
    //
    virtual void SetTransparency(HBYTE nTrans) = 0;

    // 设置文字的缺省颜色
    //
    virtual void SetTextColor(HBYTE r, HBYTE g, HBYTE b) = 0;

    // 设置使用的字体,暂时外部不调用,在ReDraw中初始化
    virtual HCFont* SetFont(HCFont* font) = 0;
    virtual void Draw256Surface(IReSurface* pSrcSurf, int xDest, int yDest, int width, int height, RECOLOR color, int xSrc, int ySrc) = 0;
    virtual void Draw256Surface(IReSurface* pSrcSurf, int xDest, int yDest, int width, int height, RECOLOR color, int xSrc, int ySrc, HINT yStart, HINT yEnd, HINT startAlpha, HINT endAlpha) = 0;
    // 绘制一个像素,这个函数效率不算高, 不过安全,提供给外部使用
    //
    virtual ERRINFO DrawPixel(HLONG x, HLONG y, HBYTE r, HBYTE g, HBYTE b) = 0;

    virtual ERRINFO DrawPixel(HLONG x, HLONG y, HBYTE r, HBYTE g, HBYTE b, HBYTE a) = 0;

    // 绘制一条直线
    //
    virtual ERRINFO DrawLine(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color = RECOLOR(0, 0, 0), HINT iWidth = 1, HBOOL bAntialising = false) = 0;
    // 绘制多条线段
    //
	virtual ERRINFO PolyLine( REPOINT* lppt, HLONG lCount, RECOLOR* clrFore, 
		HINT iWidth = 1, HDWORD dwFlag = RE_LS_NORMAL, RECOLOR* clrBack = NULL,HINT iShadWidth = 0,HINT iShaddir = -1,KBIRDVIEWPARA* param = NULL) = 0;

	virtual ERRINFO PolyLine(vector<REPOINT>& lppt, HLONG nCount, RECOLOR clrFore, 
		HINT iWidth = 1, HDWORD dwFlag = RE_LS_NORMAL,
		RECOLOR clrBack = RECOLOR(0, 0, 0 ),HINT iShadWidth = 0,HINT iShaddir = -1,HBOOL bHalfTrans = false) = 0;

    // 绘制铁路的函数. 默认是黑色,考虑到可能会对铁路有一定区分(比如地铁),也可指定其它颜色
    // 绘制铁路现在使用GDI的虚线绘制函数
    virtual ERRINFO DrawRailway(REPOINT* lppt, HLONG nCount, HBYTE r = 0, HBYTE g = 0, HBYTE b = 0) = 0;

    virtual ERRINFO DrawRectFrame(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color, HINT width) = 0;
	virtual ERRINFO DrawRoundRect(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color, HINT r)=0;
    virtual ERRINFO DrawRoundRectFrame(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color, HINT nround) = 0;

    // 使用颜色填充矩形.
    //
    virtual ERRINFO FillSolidRect(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color) = 0;

    virtual ERRINFO FillTansparentRect(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color) = 0;
    //绘制渐变色矩形
    virtual ERRINFO FillLinearGridiantRect(HLONG x1, HLONG y1, HLONG x2, HLONG y2, HDWORD Startcolor, HDWORD Endcolor , LINERTYPE typ, RECOLOR FrontClr, HBYTE byBaseAlpha = TRANSPARENTLEVEL) = 0;

    // 绘制多边形
    //
	virtual ERRINFO Polygon(const REPOINT* lppt, HLONG lCount, RECOLOR Color,HINT Type=RE_PG_NORMAL, IReSurface* pTexture=NULL) = 0;

	virtual ERRINFO Polygon(const vector<REPOINT>& lppt, HLONG lCount, RECOLOR Color,HINT Type=RE_PG_NORMAL) = 0;

    // 绘制圆形
    virtual ERRINFO Ellipse(HLONG left, HLONG top, HLONG right, HLONG bottom) = 0;

    //画圆
    virtual void Circle(HINT x1, HINT y1, HINT r, HBOOL bFill, RECOLOR* color) = 0;

    // 绘制字符串函数.
    // x, y: 字符串坐标, NORMAL时为左上角坐标, CENTER时为中心坐标
    // MultiString: 字符串
    // clrFore: 文字前景色,为空时使用缺省字体前景色
    // clrBack: 文字背景色,为空时使用缺省字体背景色
    // dwFormat: 样式
    //
    virtual ERRINFO DrawString(HLONG x, HLONG y, HBYTE * MultiString, RECOLOR* clrFore = NULL,
                               HDWORD dwFormat = RE_TS_NORMAL, RECOLOR* pclrBack = NULL) = 0;
    //绘制Unicode字符集的文字
    virtual ERRINFO DrawUCodeString(HLONG x, HLONG y, HINT width, HBYTE * MultiString, RECOLOR* clrFore,
                                    HDWORD dwFormat = RE_TS_NORMAL, RECOLOR* pclrBack = NULL) = 0;
    // 将源Src表面的指定区域的图像拷贝到本表面的指定区
    virtual ERRINFO BitBlt(IReSurface* pSrcdc, // 源DC
                           HINT xTar,       // 目标区x坐标
                           HINT yTar,       // 目标区y坐标
                           HINT width,      // 目标区宽度
                           HINT height,     // 目标区高度
                           HINT xSrc,       // 源x坐标
                           HINT ySrc,       // 源y坐标
                           RECOLOR* pColor = NULL) = 0;  //只针对8位Surface

    virtual void  StretchBlt(IReSurface* pInSrc,  //源DC
                             HINT xTar,       //目标区x坐标
                             HINT yTar,       //目标区y坐标
                             HINT TarWidth,      //目标区宽度
                             HINT TarHeight,     //目标区高度
                             HINT xSrc,       //源x坐标
                             HINT ySrc,        //源y坐标
                             HINT SrcWidth,      //目标区宽度
                             HINT SrcHeight,     //目标区高度
                             HINT Quality = 1) = 0;

    virtual void RotateBlt(IReSurface* pSrcdc, // 源DC
                           HINT xTar,          //目标区x坐标
                           HINT yTar,          //目标区y坐标
                           HINT iRotateAngle,   //旋转角度
                           HINT quality = 0  //质量 0 底  1高
                          ) = 0;
    virtual void RotateBlt(IReSurface* pSrcdc, // 源DC
                           HFLOAT xSrc,          //源区旋转中心坐标
                           HFLOAT ySrc,          //源区旋转中心坐标
                           HINT xTar,          //旋转中心在目标区中心坐标
                           HINT yTar,          //旋转中心在目标区中心坐标
                           HINT iRotateAngle,   //旋转角度
                           HINT quality   //质量 0 底  1高
                          ) = 0;
    virtual ERRINFO ImageColorMatrix(HCColorMatrix& matrix,
                                     IReSurface* pInSrc,//源DC
                                     HINT xTar,       // 目标区x坐标
                                     HINT yTar,       // 目标区y坐标
                                     HINT width,      // 目标区宽度
                                     HINT height,     // 目标区高度
                                     HINT xSrc,       // 源x坐标
                                     HINT ySrc) = 0;  // 源y坐标

    // 保存表面到ktc图形文件.
    //
    virtual ERRINFO SaveSurface(const HString* pFileName,HINT nColorBit = 1) = 0;

    //draw guide arrow
    virtual  void   DrawLineArrow(const REPOINT& start, const REPOINT& end, HINT linewid, HINT width, int height, RECOLOR clr, HINT iAlpha) = 0;

    virtual HINT GetColorType() = 0;

    virtual HINT GetXPitch() = 0;

    virtual HINT GetYPitch() = 0;

    virtual RECOLOR GetColorKey() = 0;

    //检查当前点是否透明
    virtual HBOOL CheckPoint(HINT x, HINT y) = 0;

    //设置拷贝方式为灰度
    virtual void SetGray(HBOOL v) = 0;
    virtual HBOOL IsGray() = 0;

    //是否有键值透明
    virtual HBOOL IsColorKey() = 0;

    //从图像文件装载surface，不创建，如果图像文件尺寸不符或格式不是16位，都拒绝创建
    virtual ERRINFO LoadSurfaceFromFile(const HString& filename) = 0;

    virtual ERRINFO AlternationBitblt(IReSurface* pInSrcA, IReSurface* pInSrcB, POINT mid_pos,  HINT frame) = 0;

    // 模糊处理特效
    virtual ERRINFO BlurBitblt(IReSurface* pInSrc, // 源DC
                               HINT xTar,       // 目标区x坐标
                               HINT yTar,       // 目标区y坐标
                               HINT width,      // 目标区宽度
                               HINT height,     // 目标区高度
                               HINT xSrc,       // 源x坐标
                               HINT ySrc,      // 源y坐标
                               HINT alpha,   // 透明度
                               HINT radius)  = 0;    //半径
    virtual ERRINFO GaussBlurBitblt(IReSurface* pInSrc, // 源DC
                                    HINT xTar,       // 目标区x坐标
                                    HINT yTar,       // 目标区y坐标
                                    HINT width,      // 目标区宽度
                                    HINT height,     // 目标区高度
                                    HINT xSrc,       // 源x坐标
                                    HINT ySrc,       // 源y坐标
                                    HFLOAT sigma,    //
                                    HINT radius) = 0;

    // 透明度倒影特效
    virtual ERRINFO AlphaShadeBitblt(IReSurface* pInSrc, // 源DC
                                     HINT xTar,       // 目标区x坐标
                                     HINT yTar,       // 目标区y坐标
                                     HINT width,      // 目标区宽度
                                     HINT height,     // 目标区高度
                                     HINT xSrc,       // 源x坐标
                                     HINT ySrc,      // 源y坐标
                                     HINT alpha,   //  // 透明度
                                     HINT type) = 0;  // 类型 0：整体 1：梯度

    virtual ERRINFO Convolve(
        HINT kernelWidth,
        HINT kernelHeight,
        HINT shiftX,
        HINT shiftY,
        HINT * kernel,
        HFLOAT scale,
        HINT bias = 0) = 0;

    // 图像拉伸算法
    virtual ERRINFO StretchBitBlt(IReSurface* pInSrc, // 源DC
                                  POINT newLeftTop,  // 源图像左上角在目标图中对应的位置 B
                                  POINT newRightTop, //源图像右上角在目标图中对应的位置 C
                                  POINT newLeftBottom,  // 源图像左下角在目标图中对应的位置 A
                                  POINT newRightBottom, //源图像右下角在目标图中对应的位置  D
                                  HINT alpha = 0, //  全局alpha
                                  HINT quality = 0) = 0; // 拉伸质量)

    // 水波纹特效
    virtual ERRINFO RippleBitBlt(IReSurface* pInSrc, // 源DC
                                 HINT xTar,       // 目标区x坐标
                                 HINT yTar,       // 目标区y坐标
                                 HINT frame,     // 帧序号
                                 HINT Alpha,   // alpha值
                                 HINT xSrc,       // 源x坐标
                                 HINT ySrc,   // 源y坐标
                                 HINT srcWidth, // 源宽度
                                 HINT srcHeight, // 源高度
                                 HINT bType = 1, // 消影类型 0：NULL  1：梯度 2：固定透明度值
								 HBOOL bInvertOnly = false //是否纯倒影，为true时只有倒影没有波纹
								 ) = 0;
	virtual void SingleLineS(HINT iStartX, HINT iStartY, HINT iEndX, HINT iEndY, const RECOLOR* pColor) = 0;

	//agg引擎的算法绘制
	virtual ERRINFO AGGPolyLine( REPOINT* lppt, HLONG nCount, RECOLOR clrFore, 
		HINT width=1, HDWORD dwFlag = RE_LS_NORMAL, RECOLOR clrBack=RECOLOR(0,0,0),HINT shadWidth = 0,HINT shaddir = -1 ) = 0;
	virtual ERRINFO LoadSurfaceFromePNG(HBYTE* mem, HDWORD size) = 0;
	virtual HINT CreateMaskLayer(HINT byVal) = 0;

	virtual HINT ShadowBlend(HINT type, RECOLOR* clr, RECOLOR* shadow = NULL) = 0;

    virtual HBOOL SetFontSize(HINT width, HINT height) = 0;

    virtual void GetFontSize(HINT& width, HINT& height) = 0;

	virtual inline void Pixel(HINT x, HINT y, const RECOLOR* color) = 0;
};


extern UICORE_DLL_API HBYTE reClipLine(HLONG x1, HLONG y1,
                                            HLONG x2, HLONG y2,
                                            const HLONG left, const HLONG right,
                                            const HLONG bottom, const HLONG top);

extern UICORE_DLL_API IReDraw* GetRESingleton();
// --End
#endif // _RENDERING_ENGINE_H__