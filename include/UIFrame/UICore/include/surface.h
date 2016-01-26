

#ifndef _RE_SURFACE__
#define _RE_SURFACE__

#include "RenderingEngine.h"
#include "HQLine.h"
#include "HQStretch.h"
#include "ColorConvert.h"

#define RE_MASK_SHIFT 0
#define RE_MASK_INVERT 1
#define RE_MASK_ROTATE  2
#define RE_MASK_FB_INTERSET 3
#define RE_MASK_FB_UNION 4

#ifdef PNG_SURPORT
#include "KBufferReader.h"

#ifndef WINCE
#pragma comment (lib, "lib\\png_win.lib")
#pragma comment (lib, "lib\\zlib_win.lib")
#else
#pragma comment (lib, "lib\\png_ce.lib")
#pragma comment (lib, "lib\\zlib_ce.lib")
#endif

#endif

extern HINT g_grayType;

#ifdef KOTEI_LINUX
typedef struct tagRGBQUAD
{
    BYTE    rgbBlue;
    BYTE    rgbGreen;
    BYTE    rgbRed;
    BYTE    rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPINFOHEADER
{
    DWORD      biSize;
    LONG       biWidth;
    LONG       biHeight;
    WORD       biPlanes;
    WORD       biBitCount;
    DWORD      biCompression;
    DWORD      biSizeImage;
    LONG       biXPelsPerMeter;
    LONG       biYPelsPerMeter;
    DWORD      biClrUsed;
    DWORD      biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagBITMAPINFO
{
    BITMAPINFOHEADER    bmiHeader;
    RGBQUAD             bmiColors[1];
} BITMAPINFO, *PBITMAPINFO;
#endif

//////////////////////////////////////////////////////////////////////////
// 多边形填充算法使用的结构
// 多边形点的描述，自动闭合（最后一个点不需要于第一个重合）
struct PtListHeader
{
	HINT iLength;		// 点的个数
	REPOINT* pPointPtr;	// 指针
	REPOINT texture_point; // 贴图参照点

};

// 描述水平线的起始x坐标和终止x坐标(只在快速填充代码中使用)
struct HorLine
{
	HINT iXStart;	// 最左边的点的x值  X coordinate of leftmost  pixel in line 
	HINT iXEnd;	// 最右边的点的x值  X coordinate of rightmost pixel in line 
};

// 描述一条水平扫描线,假设它们是连续的,从YStart开始向下
// 仅用于快速扫描
struct HorLineList
{
	HINT iLength;				// 这条水平线被分成了多少段
	HINT iYStart;				// 起始y值
	struct HorLine* pHLinePtr;	// 每一段的起始x和终止x
};

struct EdgeState
{
	struct EdgeState* pNextEdge;
	HINT iX;
	HINT iStartY;
	HINT iWholePixelXMove;
	HINT iXDirection;
	HINT iErrorTerm;
	HINT iErrorTermAdjUp;
	HINT iErrorTermAdjDown;
	HINT iCount;
};
//////////////////////////////////////////////////////////////////////////

//插值矩阵
extern HBYTE g_BlendMatrix[16][16][4];
extern ColorConvert colorConvert;

void InitBlendMatrix();
//ADD BY CXL
HWORD Blt32BitTo16Bit(HWORD*des16, HBYTE* src32);
HWORD Add16BitAnd32Bit(HWORD* des16, HBYTE* src32);
//将32位像素融合到24位目标像素
HINT Add24BitAnd32Bit(HBYTE* des24, HBYTE* src32);

ERRINFO Projection(RECT ViewPort,  // 显示区域大小
                   HINT SrcHeight,  // 源图像高度
                   HINT SrcWidth,   // 源图像宽度
                   HINT Angle,        // 源图像旋转角度
                   POINT* newLeftTop, // 源图像左上角在目标图中对应的位置 B
                   POINT* newRightTop, //源图像右上角在目标图中对应的位置 C
                   POINT* newLeftBottom,  // 源图像左下角在目标图中对应的位置 A
                   POINT* newRightBottom); //源图像右下角在目标图中对应的位置  D


typedef struct BRIGHT_
{
    HFLOAT fH;
    HFLOAT fS;
    HFLOAT fL;
} BRIGHT;

class CReSurface : public IReSurface
{
public:
    CReSurface();
    virtual ~CReSurface();

public:  //以下是 IReSurface 定义的对外接口函数

    // 释放surface资源,析构函数会调用这个函数,所以直接删除对象也可以,可以不显性调用.
    ERRINFO Release() ;

    // 使用指定颜色清除表面 color.
    ERRINFO Clear(HBYTE byRed, HBYTE byGreen, HBYTE byBlue) ;

    // 使用指定颜色快速清除表面,只能设置黑,白或者灰度,如果设置灰度色,建议使用这个函数
    ERRINFO ClearFast(HBYTE v);
    ERRINFO FillLinearGridiantRect(HLONG x1, HLONG y1, HLONG x2, HLONG y2, HDWORD Startcolor, HDWORD Endcolor , LINERTYPE typ, RECOLOR FrontClr, HBYTE baseAlpha = TRANSPARENTLEVEL);
    // 取得表面的内存指针数据.
    void* GetRealSurf() ;

    // 取得宽度,像素单位.
    HDWORD GetWidth() ;

    // 取得高度,像素单位
    HDWORD GetHeight() ;

    // 取得像素颜色
    RECOLOR GetPixelColor(HLONG x, HLONG y);

    // 取得内存数据块大小
    HINT GetMemDataLen() ;

    //取得透明度的值
    HBYTE GetTransparency();
#ifdef WIN32
    /*
    * 函数功能: 取得HDC
    * 参    数:
    * 返 回 值:
    */
    HDC GetHDC();
#endif

    HCFont* GetFont();
    // 设置透明键值.如果表面是24位,取前RGB三个值,如果是16位色,取后面RGB16的值
    // 为了保持兼容性,提供该函数,但键值一般应从图片文件中读出,不建议在程序中设置
    // 代码中写死颜色值不灵活
    void SetColorKey(HBYTE byRed, HBYTE byGreen, HBYTE byBlue, HWORD rgb16 = -1);

    // 设置图片透明度,0-TRANSPARENTLEVEL 之间取值,设为0表示透明度为0, TRANSPARENTLEVEL为不透明,
    //
    void SetTransparency(HBYTE byTrans) ;

    // 设置文字的缺省颜色
    void SetTextColor(HBYTE byRed, HBYTE byGreen, HBYTE byBlue);

    // 设置使用的字体,暂时外部不调用,在ReDraw中初始化,返回老的字体指针
    HCFont* SetFont(HCFont* pFont);

    void drawLine_with_patten(REPOINT p1, REPOINT p2, int& cnt, float& hasDraw, RECOLOR* clrFore);

    // 绘制一个像素,这个函数效率不算高, 不过安全,提供给外部使用
    ERRINFO DrawPixel(HLONG x, HLONG y, HBYTE r, HBYTE g, HBYTE b) ;
    ERRINFO DrawPixel(HLONG x, HLONG y, HBYTE r, HBYTE g, HBYTE b, HBYTE a) ;

    /*
    * 函数功能: 绘制一条直线
    * 参    数:
    * 返 回 值:
    */
    ERRINFO DrawLine(HLONG x1, HLONG y1, HLONG x2, HLONG y2,
                     RECOLOR Color = RECOLOR(0, 0, 0), HINT iWidth = 1, HBOOL bAntialising = false) ;

    /*
	* 函数功能: 绘制多条线段
	* 参    数:
	* 返 回 值:
	*/
	ERRINFO PolyLine(REPOINT* lppt, HLONG lCount, RECOLOR* clrFore, 
		HINT iWidth = 1, HDWORD dwFlag = RE_LS_NORMAL,
		RECOLOR* clrBack = NULL,HINT iShadWidth = 0,HINT iShadDir = -1,KBIRDVIEWPARA * param = NULL) ;

	ERRINFO PolyLine(vector<REPOINT>& lppt, HLONG lCount, RECOLOR clrFore, 
		HINT iWidth = 1, HDWORD dwFlag = RE_LS_NORMAL,
		RECOLOR clrBack = RECOLOR(0,0,0),HINT iShadWidth = 0,HINT iShadDir = -1,HBOOL bHalfTrans = false) ;

    ERRINFO PolyLineHQ(const REPOINT* lppt, HLONG nCount, RECOLOR clrFore, HINT width);


    ERRINFO PolyLinePattern(REPOINT *lppt, HLONG lCount, RECOLOR clrFore, HINT iWidth, HINT bias = 0, HINT Imageid = -1);
    ERRINFO PolyBoardLine(REPOINT* lppt, HLONG lCount, RECOLOR* clrFore, HINT iWidth = 1);

    // 绘制铁路的函数. 默认是黑色,考虑到可能会对铁路有一定区分(比如地铁),也可指定其它颜色
    // 绘制铁路现在使用GDI的虚线绘制函数
    ERRINFO DrawRailway(REPOINT* lppt, HLONG nCount, HBYTE r = 0,
                        HBYTE g = 0, HBYTE b = 0) ;

    //绘制矩形框，支持透明度
    ERRINFO DrawRectFrame(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color, HINT width);

	ERRINFO DrawRoundRect(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color, HINT r);

    //绘制圆角矩形框，支持透明度
    ERRINFO DrawRoundRectFrame(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color, HINT r);

    // 使用颜色填充矩形.
    //
    ERRINFO FillSolidRect(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color) ;

    //半透明绘制矩形
    ERRINFO FillTansparentRect(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color) ;

    /*
    * 函数功能:绘制多边形
    * 参    数:
    * 返 回 值:
    */
    ERRINFO Polygon(const REPOINT* lppt, HLONG lCount, RECOLOR Color, HINT Type = RE_PG_NORMAL, IReSurface* pTexture = NULL) ;

    ERRINFO Polygon(const vector<REPOINT>& lppt, HLONG lCount, RECOLOR Color, HINT Type = RE_PG_NORMAL) ;

    // 绘制圆形
    ERRINFO Ellipse(HLONG left, HLONG top, HLONG right, HLONG bottom) ;

//     // 画弧
//     ERRINFO DrawArc(
//         const REPOINT& o, // 圆心
//         kn_int r, // 半径
//         kn_double startAngle, // 相对于Y正半轴的起点角度
//         kn_double sweepAngle, // 扫描角度
//         const RECOLOR& color = RECOLOR(0, 0, 0),// 填充颜色
//         kn_int width = 2, // 弧宽度
//         ARC_CUTTING_TYPE eType = CUTTING_V);// 垂直裁剪弧

    // 绘制字符串函数.
    // x, y: 字符串坐标, NORMAL时为左上角坐标, CENTER时为中心坐标
    // MultiString: 字符串
    // clrFore: 文字前景色,为空时使用缺省字体前景色
    // clrBack: 文字背景色,为空时使用缺省字体背景色
    // dwFormat: 样式
    //
	ERRINFO DrawString(HLONG x, HLONG y, HBYTE * MultiString, RECOLOR* clrFore = NULL,
		HDWORD dwFormat = RE_TS_NORMAL, RECOLOR* pclrBack = NULL);
    //绘制Unicode字符, 主要提供HMI字符,多出的 width 值为文字可显示的宽度,超过部分不显示
    ERRINFO DrawUCodeString(HLONG x, HLONG y, HINT width, HBYTE * MultiString,
                            RECOLOR* clrFore = NULL, HDWORD dwFormat = RE_TS_NORMAL,
                            RECOLOR* clrBack = NULL) ;
    //矢量字绘制函数,需要传入Unicode字符 矢量字体只支持常规和阴影效果
    ERRINFO DrawTTFUCodeString(HLONG x, HLONG y, HINT width, HCHAR * MultiString,
                               const RECOLOR* clrFore, HDWORD dwFormat = RE_TS_NORMAL, const RECOLOR* clrBack = NULL) ;
    //根据单字节灰度图作为透明度信息，使用指定颜色绘制到背景，用于矢量字体和预置的字体位图绘制
    ERRINFO DrawBitmapChar(HLONG x, HLONG y, const RECOLOR* clrFore, HBYTE* buffer, HUINT w, HUINT h, HBYTE nTrans = TRANSPARENTLEVEL) ;

    // 将源Src表面的指定区域的图像拷贝到本表面的指定区
    ERRINFO BitBlt(IReSurface* pSrcdc, // 源DC
                   HINT xTar,       // 目标区x坐标
                   HINT yTar,       // 目标区y坐标
                   HINT width,      // 目标区宽度
                   HINT height,     // 目标区高度
                   HINT xSrc,       // 源x坐标
                   HINT ySrc,       // 源y坐标
                   RECOLOR* pColor = NULL) ; // 绘制颜色，只针对8位色的surface

    //缩放拷贝函数
    void  StretchBlt(IReSurface* pInSrc,  //源DC
                     HINT xTar,       //目标区x坐标
                     HINT yTar,       //目标区y坐标
                     HINT TarWidth,      //目标区宽度
                     HINT TarHeight,     //目标区高度
                     HINT xSrc,       //源x坐标
                     HINT ySrc,       //源y坐标
                     HINT SrcWidth,      //目标区宽度
                     HINT SrcHeight,  //目标区高度
                     HINT Quality = 1);

    //////////////////////////////////////////////////////////////////////////
    //chenzhi
    //缩放拷贝函数, 一级 低质量
    void  StretchBltQualityOne(IReSurface* pSrcdc, // 源DC
                               HINT xTar,       //目标区x坐标
                               HINT yTar,       //目标区y坐标
                               HINT TarWidth,      //目标区宽度
                               HINT TarHeight,     //目标区高度
                               HINT xSrc,       //源x坐标
                               HINT ySrc,       //源y坐标
                               HINT SrcWidth,      //目标区宽度
                               HINT SrcHeight);       //目标区高度

    //缩放拷贝函数, 二级 中等质量 较模糊
    void  StretchBltQualityTwo(IReSurface* pSrcdc, // 源DC
                               HINT xTar,       //目标区x坐标
                               HINT yTar,       //目标区y坐标
                               HINT TarWidth,      //目标区宽度
                               HINT TarHeight,     //目标区高度
                               HINT xSrc,       //源x坐标
                               HINT ySrc,       //源y坐标
                               HINT SrcWidth,      //目标区宽度
                               HINT SrcHeight);       //目标区高度

    //缩放拷贝函数, 三级 高质量 缩放比例较大时较慢
    void  StretchBltQualityThree(IReSurface* pSrcdc, // 源DC
                                 HINT xTar,       //目标区x坐标
                                 HINT yTar,       //目标区y坐标
                                 HINT TarWidth,      //目标区宽度
                                 HINT TarHeight,     //目标区高度
                                 HINT xSrc,       //源x坐标
                                 HINT ySrc,       //源y坐标
                                 HINT SrcWidth,      //目标区宽度
                                 HINT SrcHeight);     //目标区高度

    void BoundStretchBlt(IReSurface* pSrcdc, // 源DC
                         HINT xTar,       //目标区x坐标
                         HINT yTar,       //目标区y坐标
                         HINT TarWidth,      //目标区宽度
                         HINT TarHeight,     //目标区高度
                         HINT xSrc,       //源x坐标
                         HINT ySrc,       //源y坐标
                         HINT SrcWidth,      //源宽度
                         HINT SrcHeight,     //源高度
                         HINT Quality);     //缩放质量，1:低质量，2:高质量，默认为高质量

    //////////////////////////////////////////////////////////////////////////
    //旋转函数
    void RotateBltLow(IReSurface* pSrcdc, // 源DC
                      HINT xTar,          //目标区x坐标
                      HINT yTar,          //目标区y坐标
                      HINT iRotateAngle   //旋转角度
                     );
    void RotateBltHigh(IReSurface* pSrcdc, // 源DC
                       HFLOAT xTar,          //目标区x坐标
                       HFLOAT yTar,          //目标区y坐标
                       HINT iRotateAngle   //旋转角度
                      );
    void RotateBlt(IReSurface* pSrcdc, // 源DC
                   HINT xTar,          //目标区x坐标
                   HINT yTar,          //目标区y坐标
                   HINT iRotateAngle,   //旋转角度
                   HINT quality = 0  //质量 0 底  1高
                  ) ;
    void RotateBlt(IReSurface* pSrcdc, // 源DC
                   HFLOAT xSrc,          //源区旋转中心坐标
                   HFLOAT ySrc,          //源区旋转中心坐标
                   HINT xTar,          //旋转中心在目标区中心坐标
                   HINT yTar,          //旋转中心在目标区中心坐标
                   HINT iRotateAngle,   //旋转角度
                   HINT quality   //质量 0 底  1高
                  ) ;

    ERRINFO ImageColorMatrix(HCColorMatrix& matrix,
                             IReSurface* pInSrc,
                             HINT xTar,       // 目标区x坐标
                             HINT yTar,       // 目标区y坐标
                             HINT width,      // 目标区宽度
                             HINT height,     // 目标区高度
                             HINT xSrc,       // 源x坐标
                             HINT ySrc);  // 源y坐标
    //////////////////////////////////////////////////////////////////////////

    // 保存表面到ktc图形文件.
    //
    ERRINFO SaveSurface(const HString* pFileName,HINT nColorBit = 1);

    //画圆
    void Circle(HINT x1, HINT y1, HINT r, HBOOL bFill, RECOLOR* color);

    //draw guide arrow
    void   DrawLineArrow(const REPOINT& start, const REPOINT& end, HINT linewid, HINT width, int height, RECOLOR clr, HINT iAlpha);

    //检查当前点是否透明,用于按钮消息判断区域
    HBOOL CheckPoint(HINT x, HINT y);

    //agg引擎的绘制polyline
    ERRINFO AGGPolyLine(REPOINT* lppt, HLONG nCount, RECOLOR clrFore,
                        HINT width = 1, HDWORD dwFlag = RE_LS_NORMAL, RECOLOR clrBack = RECOLOR(0, 0, 0), HINT shadWidth = 0, HINT shaddir = -1);

public: //以下是面向绘制引擎的公用函数

    //创建一个空surface
    ERRINFO CreateSurface(HINT width, HINT height, HDWORD dwColorFormat, HBOOL bUseDraw = false, HBOOL bCreateDC = false);
	//strWidth 只在RE_TS_END_ELLIPSIS
    ERRINFO CreateTTFFontSurface(HINT font_width, HINT font_height, HCFont* pFont, HDWORD dwFormat, const HCHAR* str, HINT strWidth = 0);
    void Draw256Surface(IReSurface* pSrcSurf, int xDest, int yDest, int width, int height, RECOLOR color, int xSrc, int ySrc);
    void Draw256Surface(IReSurface* pSrcSurf, int xDest, int yDest, int width, int height, RECOLOR color, int xSrc, int ySrc, HINT yStart, HINT yEnd, HINT startAlpha, HINT endAlpha);
    //根据图像文件创建surface
    ERRINFO CreateSurfaceFromFile(const HString& filename, HDWORD dwColorFormat);
    ERRINFO CreateSurfaceFromKtcFile(const HString& filename, HDWORD dwColorFormat);
    ERRINFO CreateSurfaceFromJpegFile(const HString& filename);
	//ERRINFO CreateSurfaceInErrorDiffuse(IReSurface* pSurf);
    ERRINFO CreateSurfaceFromKtcStream(const HBYTE* pMemAddr);
	//ERRINFO CreateSurfaceFromRGB888Stream(const kn_byte* pMemAddr, kn_int width, kn_int height, kn_int nSize, kn_bool bUseErrorDiffuse = TRUE);
	ERRINFO CreateSurfaceFrom565Mem(const HBYTE* pMemAddr, HINT width, HINT height);
    ERRINFO CreateSurfaceFromJpegStream(const HBYTE* pMemAddr, HINT MemSize);
	ERRINFO CreateSurfaceFromBmpStream(HBYTE* pMemAddr, HINT nMemSize);
    ERRINFO CreateSurfaceFromBmpFile(const HString& filename);
	//误差扩散处理算法
	void  CvsPic24To16_ErrorDiffuse_1( HBYTE*  dst, const HBYTE*  src, long width, long height, long src_width_byte, long dst_width_byte);

    //从图像文件装载surface，不创建，如果图像文件尺寸不符或格式不是16位，都拒绝创建
    ERRINFO LoadSurfaceFromFile(const HString& filename);
    ERRINFO LoadSurfaceFromKtcFile(const HString& filename);
    ERRINFO LoadSurfaceFromJpegFile(const HString& filename);
    ERRINFO LoadSurfaceFromePNG(HBYTE* mem, HDWORD size);

    void BrushLineMask(HINT iStartX, HINT iStartY, HINT iEndX, HINT iEndY,  RECOLOR* pBack, HINT brID = 0);
    void BrushDotMask(HINT x, HINT y, REBrushGenerate* br, RECOLOR* pclr);
    void BlendBrushWithForClr(RECOLOR* pclr, RECTANGLE& rct);
    void TransformMask(HINT a , HINT b , HINT Trans);
    HINT ShadowBlend(HINT type, RECOLOR* clr, RECOLOR* shadow = NULL);

    //是否有键值透明
    HBOOL IsColorKey();

    //取得键值颜色
    RECOLOR GetColorKey();

    HINT GetColorType();

    HINT GetXPitch();

    HINT GetYPitch();
    //设置拷贝方式为灰度
    void SetGray(HBOOL v);
    HBOOL IsGray();

    static HBYTE GetGrayValue(HBYTE r, HBYTE g, HBYTE b);

    // 坐标转换函数 求出两个矩形区交集.并更新两个矩形区
    // 如果转换后tarRect srcRect有一个区域为空, 则返回FALSE
    static HBOOL CalCoordinate(HINT xTar, HINT yTar, HINT widthTar, HINT heightTar, HINT width, HINT height,
                                 HINT xSrc, HINT ySrc, HINT widthSrc, HINT heightSrc, RECTANGLE& tarRect, RECTANGLE& srcRect);

    void BrightToRGB(RECOLOR& Clr, BRIGHT Bright);
    void RGBToBright(RECOLOR& Clr, BRIGHT& Bright);

    /*
    * 函数功能: 阴影的宽线
    * 参    数:
    *      iStartX    [in]  起点X
    *      iStartY    [in]  起点Y
    *      iEndX      [in]  终点X
    *      iEndY      [in]  终点Y
    *      iWidth     [in]  宽度
    *      iShadWidth [in]  阴影的宽度
    *      iDir       [in]  方向
    *      pColor     [in]  颜色
    * 返 回 值:
    */
    void WidthLineShadow(HINT iStartX, HINT iStartY, HINT iEndX, HINT iEndY, HINT iWidth,
                         HINT iShadWidth, HINT iDir, RECOLOR* pColor);

	inline void Pixel(HINT x, HINT y, const RECOLOR* color);

protected:
    // 针对GDI图像的字节对齐函数，24位传入的width应该乘3
    HLONG AdjustWidth(HLONG width)
    {
        if (width % 4 == 0)    return    width;
        else    return    width - width % 4 + 4;
    };


    //真正的写点阵字函数
    //drawwidth 允许的文字绘制宽度, 小于0表示不限制
    ERRINFO DrawText(HINT x, HINT y, HBYTE * MultiString, const RECOLOR* color, HDWORD dwFormat, const RECOLOR* clrBack = NULL, HINT drawwidth = 0);

    //描点函数,为保证速度,不对坐标合法性判断,调用函数应保证不越界
    inline void Pixel16(HINT x, HINT y, HWORD color);
    inline void Pixel24(HINT x, HINT y, const RECOLOR* color);
    inline void Pixel32(HINT x, HINT y, const RECOLOR* color);

    /*
    * 函数功能:  描点函数
    * 参    数:
    *      pData   [in]  内存指针
    *      dwColor [in]  颜色
    * 返 回 值:
    */
    inline void Pixel16F(HWORD* pData, HWORD wColor)
    {
        *pData = wColor;
    };

    /*
    * 函数功能:  描点函数
    * 参    数:
    *      pData   [in]  内存指针
    *      dwColor [in]  颜色
    * 返 回 值:
    */
    inline void Pixel16FT(HWORD* pData, HWORD dwColor)
    {
        HBYTE r1 = GetRPart_565(dwColor);
        HBYTE r2 = GetRPart_565(*pData);
        HBYTE g1 = GetGPart_565(dwColor);
        HBYTE g2 = GetGPart_565(*pData);
        HBYTE b1 = GetBPart_565(dwColor);
        HBYTE b2 = GetBPart_565(*pData);
        HINT bkTrans = TRANSPARENTLEVEL - m_byDrawTrans;
        *pData = RGB565(m_pRGB_Transparent_table[m_byDrawTrans][r1] + m_pRGB_Transparent_table[bkTrans][r2],
                        m_pRGB_Transparent_table[m_byDrawTrans][g1] + m_pRGB_Transparent_table[bkTrans][g2],
                        m_pRGB_Transparent_table[m_byDrawTrans][b1] + m_pRGB_Transparent_table[bkTrans][b2]);
    }

    /*
    * 函数功能: 反走样带边线的宽线(快速)
    * 参    数:
    *      iStartX [in]  起点X
    *      iStartY [in]  起点Y
    *      iEndX   [in]  终点X
    *      iEndY   [in]  终点Y
    *      iWidth  [in]  宽度
    *      pFore   [in]   前景颜色
    *      pBack   [in]   边线颜色
    * 返 回 值:
    */
    void WidthLineWithAdgeSFast(HINT StartX, HINT StartY, HINT EndX, HINT EndY, HINT Width, RECOLOR* color, RECOLOR* color1);
    void WidthLineS3(HINT iStartX, HINT iStartY, HINT iEndX, HINT iEndY, HINT iWidth, RECOLOR* pColor, RECOLOR*pEdgeColor);
    void PolyLineBird(REPOINT* lppt, HLONG lCount, RECOLOR clrFore, HINT iWidth, HBOOL  bhalf = false);


    // 根据对齐方式调整(x, y)  用于文字对齐
    void AdjustAlignFormat(HINT& x, HINT& y, HINT width, HINT height, HDWORD uFormat);

    //用于粗线绘制的函数集
    //单线绘制
    void SingleLine(HINT StartX, HINT StartY, HINT EndX, HINT EndY, const RECOLOR* color);
    //稍宽一点的单线绘制
    void VerboseLine(HINT StartX, HINT StartY, HINT EndX, HINT EndY, const RECOLOR* color);

	void SingleLineS(HINT iStartX, HINT iStartY, HINT iEndX, HINT iEndY, const RECOLOR* pColor);

	/*
	* 函数功能: 反走样宽线绘制
	* 参    数:
	*      iStartX [in]  起点X
	*      iStartY [in]  起点Y
	*      iEndX   [in]  终点X
	*      iEndY   [in]  终点Y
	*      iWidth  [in]  宽度
	*      pColor  [in]  颜色
	* 返 回 值: 
	*/	
	void WidthLineS(HINT iStartX, HINT iStartY, HINT iEndX, HINT iEndY, HINT iWidth, const RECOLOR* pColor);

	/*
	* 函数功能: 反走样带边线的宽线
	* 参    数:
	*      iStartX [in]  起点X
	*      iStartY [in]  起点Y
	*      iEndX   [in]  终点X
	*      iEndY   [in]  终点Y
	*      iWidth  [in]  宽度
	*      pFore   [in]   前景颜色
	*      pBack   [in]   边线颜色
	* 返 回 值: 
	*/	
	void WidthLineWithAdgeS(HINT iStartX, HINT iStartY, HINT iEndX, HINT iEndY, HINT iWidth, RECOLOR* pFore,RECOLOR* pBack);

    //画宽线
    void WidthLine(HINT StartX, HINT StartY, HINT EndX, HINT EndY, HINT Width, const RECOLOR* color);
    //画带边线的宽线
    void WidthLineWithAdge(HINT StartX, HINT StartY, HINT EndX, HINT EndY, HINT Width, const RECOLOR* color, const RECOLOR* color1);
    //画虚线
    void WidthLinePattern(HINT StartX, HINT StartY, HINT EndX, HINT EndY, HINT Width, const RECOLOR* color,
                           HBYTE byDraw, HBYTE byUnDraw, HBYTE& startPos, HBOOL& bFirst);

    //////////////////////////////////////////////////////////////////////////
    //以下是多边形填充算法相关的函数和结构
    HINT	FillPolygon(PtListHeader* pVertexList, HINT Type = RE_PG_NORMAL, CReSurface* pTexture = NULL,HINT iXOffset = 0, HINT iYOffset = 0);
	void	DrawHorizontalLineSeg(HINT Y, HINT LeftX, HINT RightX,HINT Type, CReSurface* pTexture, REPOINT& point);
	void	DrawHorizontalLineSeg_Normal(HINT iY, HINT iLeftX, HINT iRightX,HINT type);
	void	DrawHorizontalLineSeg_Texture(HINT, HINT, HINT, HINT, CReSurface* pTexture, REPOINT& point);

    void    BuildGET(PtListHeader*, EdgeState*, HINT, HINT);
    void    MoveXSortedToAET(HINT);
    void    ScanOutAET(HINT iYToScan, HINT Type, CReSurface* pTexture, REPOINT& point);
    void    AdvanceAET();
    void    XSortAET();
	struct  EdgeState* m_pGET, *m_pAET;
	RECOLOR m_clrPolygon;
    //////////////////////////////////////////////////////////////////////////

    bool ClipRect(HINT scrx1, HINT scry1, HINT scrx2, HINT scry2,
                  HINT desx1, HINT desy1, HINT desx2, HINT desy2, RECTANGLE& rect);

    inline HBOOL ClipLine(HINT& StartX, HINT& StartY, HINT& EndX, HINT& EndY);

    inline HBOOL BarskyTest(HFLOAT p, HFLOAT q, HFLOAT* u1, HFLOAT* u2);

public:
    ERRINFO RippleBitBlt(IReSurface* pInSrc, // 源DC
                         HINT xTar,       // 目标区x坐标
                         HINT yTar,       // 目标区y坐标
                         HINT frame,     // 帧序号
                         HINT Alpha,   // alpha值
                         HINT xSrc,       // 源x坐标
                         HINT ySrc,   // 源y坐标
                         HINT srcWidth, // 源宽度
                         HINT srcHeight, // 源高度
						 HINT bType = 1,// 消影类型 0：NULL  1：梯度 2：固定透明度值
						 HBOOL bInvertOnly = false //是否纯倒影，为true时只有倒影没有波纹
                         );  

    ERRINFO StretchBitBlt(IReSurface* pInSrc, // 源DC
                          POINT newLeftTop,  // 源图像左上角在目标图中对应的位置
                          POINT newRightTop, //源图像左上角在目标图中对应的位置
                          POINT newLeftBottom,  //// 源图像左下角在目标图中对应的位置
                          POINT newRightBottom,  //源图像右下角在目标图中对应的位置
                          HINT alpha = 0, //  全局alpha
                          HINT quality = 0); // 拉伸质量

    ERRINFO AlternationBitblt(IReSurface* pInSrcA, // 源A
                              IReSurface* pInSrcB,// 源B
                              POINT mid_pos, // 目标中心点坐标
                              HINT frame); // 当前帧号

    ERRINFO BlurBitblt(IReSurface* pInSrc, // 源DC
                       HINT xTar,       // 目标区x坐标
                       HINT yTar,       // 目标区y坐标
                       HINT width,      // 目标区宽度
                       HINT height,     // 目标区高度
                       HINT xSrc,       // 源x坐标
                       HINT ySrc,   // 源y坐标
                       HINT alpha = 255, // 透明度
                       HINT radius = 3);//半径
    ERRINFO GaussBlurBitblt(IReSurface* pInSrc, // 源DC
                            HINT xTar,       // 目标区x坐标
                            HINT yTar,       // 目标区y坐标
                            HINT width,      // 目标区宽度
                            HINT height,     // 目标区高度
                            HINT xSrc,       // 源x坐标
                            HINT ySrc,       // 源y坐标
                            HFLOAT sigma,    //
                            HINT radius);     //

    ERRINFO AlphaShadeBitblt(IReSurface* pInSrc, // 源DC
                             HINT xTar,       // 目标区x坐标
                             HINT yTar,       // 目标区y坐标
                             HINT width,      // 目标区宽度
                             HINT height,     // 目标区高度
                             HINT xSrc,       // 源x坐标
                             HINT ySrc,      // 源y坐标
                             HINT alpha = 0,   // 透明度
                             HINT type = 1); // 类型 0：整体 1：梯度

    ERRINFO Convolve(
        HINT kernelWidth,
        HINT kernelHeight,
        HINT shiftX,
        HINT shiftY,
        HINT * kernel,
        HFLOAT scale,
        HINT bias = 0);

    HBOOL SetFontSize(HINT width, HINT height);
    void GetFontSize(HINT& width, HINT& height);

	HDWORD* GetPaletteArray();


private:
    ERRINFO AlphaShadeBitblt_Whole(IReSurface* pInSrc, // 源DC
                                   HINT xTar,       // 目标区x坐标
                                   HINT yTar,       // 目标区y坐标
                                   HINT width,      // 目标区宽度
                                   HINT height,     // 目标区高度
                                   HINT xSrc,       // 源x坐标
                                   HINT ySrc,      // 源y坐标
                                   HINT alpha);   //  // 透明度

    ERRINFO AlphaShadeBitblt_Gradient(IReSurface* pInSrc, // 源DC
                                      HINT xTar,       // 目标区x坐标
                                      HINT yTar,       // 目标区y坐标
                                      HINT width,      // 目标区宽度
                                      HINT height,     // 目标区高度
                                      HINT xSrc,       // 源x坐标
                                      HINT ySrc,      // 源y坐标
                                      HINT aipha);   //  // 透明度

    void LeftTop(IReSurface* pInSrc, // 源DC
                 POINT newLeftTop,  // 源图像左上角在目标图中对应的位置 B
                 POINT newRightTop, //源图像右上角在目标图中对应的位置 C
                 POINT newLeftBottom,  //// 源图像左下角在目标图中对应的位置 A
                 POINT newRightBottom, //源图像右下角在目标图中对应的位置  D
                 HINT alpha);
    void RightTop(IReSurface* pInSrc, // 源DC
                  POINT newLeftTop,  // 源图像左上角在目标图中对应的位置 B
                  POINT newRightTop, //源图像右上角在目标图中对应的位置 C
                  POINT newLeftBottom,  //// 源图像左下角在目标图中对应的位置 A
                  POINT newRightBottom, //源图像右下角在目标图中对应的位置  D
                  HINT alpha);
    void LeftBottom(IReSurface* pInSrc, // 源DC
                    POINT newLeftTop,  // 源图像左上角在目标图中对应的位置 B
                    POINT newRightTop, //源图像右上角在目标图中对应的位置 C
                    POINT newLeftBottom,  //// 源图像左下角在目标图中对应的位置 A
                    POINT newRightBottom, //源图像右下角在目标图中对应的位置  D
                    HINT alpha);
    void RightBottom(IReSurface* pInSrc, // 源DC
                     POINT newLeftTop,  // 源图像左上角在目标图中对应的位置 B
                     POINT newRightTop, //源图像右上角在目标图中对应的位置 C
                     POINT newLeftBottom,  //// 源图像左下角在目标图中对应的位置 A
                     POINT newRightBottom, //源图像右下角在目标图中对应的位置  D
                     HINT alpha);
    void FillLine(IReSurface* pInSrc, //源DC
                  POINT oldLineStart, // 源DC扫描线开始位置
                  POINT oldLineEnd, // 源DC扫描线结束位置
                  POINT newLineStart, // 目标DC扫描线开始位置
                  POINT newLineEnd, // 源DC扫描线结束位置
                  HINT alpha);// 透明度

    RECOLOR GetBlurValue(IReSurface* pInSrc, //源DC
                         HINT x,
                         HINT y,
                         HINT radius = 3);

	/*
	* 函数功能: 裁减多边形
	* 参    数:
	*      lppt  [in]  裁减前的点
	*      lCount [in]  点的个数
	*      Clippt   [in]   裁减后的点
	* 返 回 值:相交点
	*/
	HBOOL ClipPoly(const REPOINT* lppt, HLONG lCount,vector<REPOINT>& Clippt);


	/*
	* 函数功能: 相交计算，计算出相交的点
	* 参    数:
	*      ptPrev  [in]  起点
	*      ptAfter [in]  终点
	*      iType   [in]  和矩形框相交的边
	* 返 回 值:相交点
	*/
	REPOINT InterSect(REPOINT& ptPrev,REPOINT& ptAfter,HINT iType);


protected: //成员
    HINT  m_iType;        //surface的颜色模式 565 555 888 32
    HBOOL m_bColorKey;    //是否使用颜色键值透明
    HBOOL m_bGray;    //转为灰度图拷贝

#ifdef WIN32
    HDC     m_Hdc;      //设备DC
    HBITMAP m_Hbmp;     //设备位图
#endif
    BITMAPINFO  m_BmpInfo;    //位图信息结构
    HDWORD    m_dwMemTemp[4];  //为了设置565格式定义的Mask区域,一定要紧随m_BmpInfo后面定义

    HBYTE*  m_pData;  //设备内位图内存数据地址指针
    RECOLOR m_clrKey;   //透明颜色值
    RECOLOR m_clrText;  //缺省的文字前景色

    //整体透明度,0-TRANSPARENTLEVEL, 0完全透明, TRANSPARENTLEVEL不透明
    //中间值为N/TRANSPARENTLEVEL透明度, 其余无效值都按不透明处理
    //此参数只用于位图类型的 Bitblt copy
    HBYTE    m_byTransparent;

    //用于矢量绘制控制透明度
    HBYTE    m_byDrawTrans;

    HCFont* m_pFont; //字体指针, 外部设置, 不用删除

    HINT     m_iXPitch; //每像素字节数
    HINT     m_iYPitch; //每行像素字节数

    HBYTE** m_pRGB_Transparent_table;  // Alpha table指针
    HINT** m_pRGB_Alpha_table;

    HINT CreateMaskLayer(HINT byVal);
    HINT ClearLayer(HINT bVal);
    HBOOL HasAlphaLayer()
    {
        return m_bHasMask;
    }

#ifdef AFX_HQLINE_H__0D9E2B92_1D82_484E_A75C_79100805120B__INCLUDED_
    CHQLine* m_HQpolyLine;
#else
    CHQDraw m_HQpolyLine;
#endif

    CHQStretch m_hqStretch;

    HINT m_fontWidth;
    HINT m_fontHeight;

    // add masklayer
    HBYTE * m_byMaskLayer;
    HBYTE * m_byBackMaskLayer;
    HBOOL m_bHasMask;
    HBOOL m_bMaskClear;

	HDWORD* m_pPaletteColorArray;
    HINT m_nPaletteColor; //调色板颜色数
};

#endif //_RE_SURFACE__
