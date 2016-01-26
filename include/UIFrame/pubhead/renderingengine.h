

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

//FreeType���ļ�

#pragma warning (disable: 4183) //����ᱨ RECTANGLE ��set��������, û�б�Ҫ
#pragma warning (disable: 4018)
#pragma warning (disable: 4244)

//FreeType���ļ�
#include <ft2build.h>
#include FT_FREETYPE_H

#pragma warning (disable: 4183) //����ᱨ RECTANGLE ��set��������, û�б�Ҫ

#ifndef WIN32           // if we are not under windows os.
#define RGB(r,g,b)      ((HDWORD)(((HBYTE)(r)|((HWORD)((HBYTE)(g))<<8))|(((HDWORD)(HBYTE)(b))<<16)))
#define GetRValue(rgb)  ((HBYTE)(rgb))
#define GetGValue(rgb)  ((HBYTE)(((HWORD)(rgb)) >> 8))
#define GetBValue(rgb)  ((HBYTE)((rgb)>>16))
#endif // WIN32

//��ɫת����
#define RGB555(r, g, b) ( (((b)>>3) & 31) + ( (((g)>>3) & 31) << 5)+( (((r)>>3) & 31) << 10))
#define RGB565(r, g, b) ( (((b)>>3) & 31) + ( (((g)>>2) & 63) << 5)+( (((r)>>3) & 31) << 11))
#define RGB888(r, g, b) ( ((b) & 0xff) + (((g) & 0xff) << 8) + (((r) & 0xff) << 16))

//������ɫ��
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

// ͳһ��ȫɾ������
// delete an object.
#define SAFE_DELETE(obj) if((obj) != NULL) {delete (obj); (obj) = NULL;}
// delete a group of objects.
#define SAFE_DELETE_GROUP(pObject) if((pObject) != NULL) {delete[]  (pObject); (pObject) = NULL;}
// delete a class or release an interface.
#define SURFACE_RELEASE(obj) if(obj) {(obj)->Release(); delete (obj); (obj) = NULL;}

#define RE_PI       3.14159265359 //��
#define RE_DEGREE   0.01745329252 //����

// ͸���ȼ���,����Ϊ2��n�η�,��������Ϊ16,������255��
#define TRANSPARENTLEVEL 16
//͸����λ������ Ϊlog2(TRANSPARENTLEVEL),255ʱΪ8,Ϊ����͸������ʱ�������
#define TRANSBIT 4


typedef HINT ERRINFO; // return value (error info).
//����ֵ
#define RE_OK                   1
#define RE_ERROR                0


#define RE_COLOR888             1   // RGB24.
#define RE_COLOR555             2   // mainly used in embedded device.
#define RE_COLOR32              3   // RGBA. AΪAlphaͨ��ֵ
#define RE_COLOR565             4   // same as COLOR555.
#define RE_SOFT_COUNT           5
#define RE_COLOR256             6
#define RE_COLORPALETTE			7	// ��ɫ��ģʽ

/*****************************************************************************
// the following macro will be used in class CReDisplay.
*****************************************************************************/

#define RE_DISPLAY_FULLSCREEN   1   // display fullscreen.
#define RE_DISPLAY_WINDOW       0   // display in window. ����ģʽ����û�п���

/*****************************************************************************
// the following macro will be used in class CReSurface.
*****************************************************************************/
// ������ʽ
#define RE_TS_NORMAL            0x00000000  // ������ʽ,���ֶ����������
#define RE_TS_STROKE            0x00000001  // �����б�Ե�� ����BK����
#define RE_TS_BK                0x00000002  // �����б�����ɫ 
#define RE_TS_CENTER            0x00000004  // ���ֶ�������� ����NORMAL����
#define RE_TS_BOLD              0x00000008  // ��������
#define RE_TS_SHADOW            0x00000010  // ��Ӱ����
#define RE_TS_SOFT_SHADOW       0x00000020  // �ữ��Ӱ����
#define RE_TS_RIGHT             0x00000040  // ���������Ҷ���
#define RE_TS_END_ELLIPSIS		0x00000080	// �ı�����������ʾΪʡ�Ժ�

#define RE_HQ_LINE              0x00000008  // ��������������
// ������ʽ.
#define RE_LS_NORMAL            0x00000000  // ��������ʽ.
#define RE_LS_HATCH             0x00000001  // �б�Ե��.
#define RE_LS_DASH              0x00000002  // ����.
#define RE_LS_TRANS             0x00000004  // ͸����.
#define RE_LS_SHADOW            0x00000008  // ��Ӱ��.
#define RE_LS_NORMALS           0x00000010  // ��������ʽ(������).
#define RE_LS_HATCHS            0x00000020  // �б�Ե��(������).
#define RE_BIRDVIEW_LINE        0x00000100
#define RE_AGGPOLYLINE          0x00000200
#define RE_LS_ALPHA_AGG         0x00000400
#define RE_LS_BRUSH_LINE        0x00001000  // ����

// ����������ʽ
#define RE_PG_NORMAL            0X00000001 // ������ʽ
#define RE_PG_SHADOW            0x00000002 // ��Ӱ��ʽ
#define RE_PG_TEXTURE           0x00000004 // ������ʽ
#define RE_PG_ALPHA             0x00000008 // ������ʽ



//�ж������ν���(��ֱ�ߺ;���)ʱʹ�õĺ궨�� reClipLine ����ʹ��
#define RE_MUST_OUT     0  //һ�����ཻ
#define RE_MUST_IN      1  //A��ȫ��B�ڲ�
#define RE_OVER_OR_OUT  2  //A B���ཻ����, ����ֱ��, Ҳ�п�����ȫ���ཻ

#define FEQUAL(a,b) (fabs((a) - (b)) < 0.0001 ? 1 : 0)

// �ж����������εķ�ʽ
enum LINERTYPE
{
    RE_RF_VLINEAR = 0 ,//��ֱ�������
    RE_RF_HLINEAR = 1, //ˮƽ�������
    RE_RF_CLINEAR = 2, //�Խ��������
    RE_RF_RADIATE = 3, //�������
    RE_AF_VLINEAR = 4, //��ֱalpha���
    RE_AF_HLINEAR = 5  //ˮƽalpha���
};

//���ƴ���ʱ,�ж϶˵�����
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
    {//��Ϊ kn_word ��֧�ָ���,����ֻ��ʹ��0ֵ�ж�,���rgbҪ��Ϊ0, r,g,bҲ��ҪΪ0
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

    //��������ȡ����ɫ
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
    //�ѵ�ǰ��ɫֵ�����ڴ�
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
//���ھ��νṹ, top��bottom˭��˭С�Ǹ�ֵ��ע�������
//���ھ�γ��, (0,0)�����½�, top > bottom
//���ڴ��ڼ�λͼ����ϵ, (0,0)�����Ͻ�, top < bottom
//����CDC���ڴ�����,�ڴ������½�Ϊ0,0��
//������,���캯����ֵ,��֤��top > bottom �߼�������Բ������ָ�ֵ����
//���ڻ�������, ���� (0,0)�����Ͻ�, ʹ�� set������ֵ, ����t b ����У��
//ͬwindows��SetRect����һ��
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
    HBYTE* byMask; //͸��������
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
// interface : Draw. �ӿ���
*******************************************************/
struct UICORE_DLL_API IReDraw
{
public:
    virtual ~IReDraw() {};

    // initialize the interface.
    virtual ERRINFO Initialize() = 0;
    virtual IReSurface* CreateTTFFontSurface(HINT font_width, HINT font_height, HCFont* pFont, HDWORD dwFormat, const HCHAR* str, HINT strWidth = 0) = 0;
    // ����һ���������ڻ��ƣ�ָ����С����ɫģʽ
#if defined(SCREEN_COLORBIT16)
	virtual IReSurface* CreateSurface(HLONG iWidth, HLONG iHeight, HDWORD dwColorFormat = RE_COLOR565, HBOOL bUseDraw = FALSE, HBOOL bCreateDC = FALSE) = 0;
#else
    virtual IReSurface* CreateSurface(HLONG iWidth, HLONG iHeight, HDWORD dwColorFormat = RE_COLOR888, HBOOL bUseDraw = FALSE, HBOOL bCreateDC = FALSE) = 0;
#endif
    // ���ڴ����д���һ������
    virtual IReSurface* CreateSurfaceFromKtcStream(const HBYTE* pMemAddr) = 0;
    virtual IReSurface* CreateSurfaceFromJpegStream(const HBYTE* pMemAddr, HINT MemSize) = 0;
	virtual IReSurface* CreateSurfaceFromBmpStream(const HBYTE* pMemAddr, HINT nMemSize) = 0;
	//��RGB888���ڴ�������һ�����������ɢ�������RGB565����
	/*virtual IReSurface* CreateSurfaceFromRGB888Stream(const HBYTE* pMemAddr, HINT width, HINT height, HINT nSize, HBOOL bUseErrorDiffuse = TRUE) = 0;*/
	virtual IReSurface* CreateSurfaceFrom565Mem(const HBYTE* pMemAddr, HINT width, HINT height) = 0;
	//virtual IReSurface* CreateSurfaceInErrorDiffuse(IReSurface* pSurf) = 0;
    // �޸�һ������
    virtual void ModifyKtcStreamSurface(IN const HBYTE* pMemAddr, OUT IReSurface* pKtcStreamSur) = 0;

    // ���ļ��д�������.����ļ���24λɫ,��ʽָ��RE_COLOR565,���Զ�תΪ16λ����
#if defined(SCREEN_COLORBIT16)
	virtual IReSurface* CreateSurfaceFromFile(const HString& pFileName, HDWORD dwColorFormat = RE_COLOR565) = 0;
#else
    virtual IReSurface* CreateSurfaceFromFile(const HString& pFileName, HDWORD dwColorFormat = RE_COLOR888) = 0;
#endif
    virtual void GetFontSize(HINT &iWidth, HINT &iHeight, HINT iIndex) = 0;
    virtual HCFont* GetFont(HINT iIndex) = 0;

	//���¼������壬����ֻ����һ��ʸ�������ļ������������ļ����������������
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
    // �ͷ�surface��Դ,��������������������,����ֱ��ɾ������Ҳ����,���Բ����Ե���.
    //
    virtual ERRINFO Release() = 0;

    // ʹ��ָ����ɫ������� color.
    //
    virtual ERRINFO Clear(HBYTE r, HBYTE g, HBYTE b) = 0;

    // ʹ��ָ����ɫ�����������,ֻ�����ú�,�׻��߻Ҷ�,������ûҶ�ɫ,����ʹ���������
    //
    virtual ERRINFO ClearFast(HBYTE v) = 0;

    // ȡ�ñ�����ڴ�ָ������.
    virtual void* GetRealSurf() = 0;
    // ȡ�ÿ��,���ص�λ.
    //
    virtual HDWORD GetWidth() = 0;

    // ȡ�ø߶�,���ص�λ
    //
    virtual HDWORD GetHeight() = 0;

    // ȡ��������ɫ
    virtual RECOLOR GetPixelColor(HLONG x, HLONG y) = 0;

    // ȡ���ڴ����ݿ��С
    virtual HINT GetMemDataLen() = 0;

    //ȡ��͸���ȵ�ֵ
    virtual HBYTE GetTransparency() = 0;

    // ȡ��HDC
    virtual HDC GetHDC() = 0;
    //ȡ������
    virtual HCFont* GetFont() = 0;
    // ����͸����ֵ.���������24λ,ȡǰRGB����ֵ,�����16λɫ,ȡ����RGB16��ֵ
    // Ϊ�˱��ּ�����,�ṩ�ú���,����ֵһ��Ӧ��ͼƬ�ļ��ж���,�������ڳ���������
    // ������д����ɫֵ�����
    virtual void SetColorKey(HBYTE r, HBYTE g, HBYTE b, HWORD rgb16 = -1) = 0;

    // ����ͼƬ͸����,0-TRANSPARENTLEVEL ֮��ȡֵ,��Ϊ0��ʾ͸����Ϊ0, TRANSPARENTLEVELΪ��͸��,
    //
    virtual void SetTransparency(HBYTE nTrans) = 0;

    // �������ֵ�ȱʡ��ɫ
    //
    virtual void SetTextColor(HBYTE r, HBYTE g, HBYTE b) = 0;

    // ����ʹ�õ�����,��ʱ�ⲿ������,��ReDraw�г�ʼ��
    virtual HCFont* SetFont(HCFont* font) = 0;
    virtual void Draw256Surface(IReSurface* pSrcSurf, int xDest, int yDest, int width, int height, RECOLOR color, int xSrc, int ySrc) = 0;
    virtual void Draw256Surface(IReSurface* pSrcSurf, int xDest, int yDest, int width, int height, RECOLOR color, int xSrc, int ySrc, HINT yStart, HINT yEnd, HINT startAlpha, HINT endAlpha) = 0;
    // ����һ������,�������Ч�ʲ����, ������ȫ,�ṩ���ⲿʹ��
    //
    virtual ERRINFO DrawPixel(HLONG x, HLONG y, HBYTE r, HBYTE g, HBYTE b) = 0;

    virtual ERRINFO DrawPixel(HLONG x, HLONG y, HBYTE r, HBYTE g, HBYTE b, HBYTE a) = 0;

    // ����һ��ֱ��
    //
    virtual ERRINFO DrawLine(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color = RECOLOR(0, 0, 0), HINT iWidth = 1, HBOOL bAntialising = false) = 0;
    // ���ƶ����߶�
    //
	virtual ERRINFO PolyLine( REPOINT* lppt, HLONG lCount, RECOLOR* clrFore, 
		HINT iWidth = 1, HDWORD dwFlag = RE_LS_NORMAL, RECOLOR* clrBack = NULL,HINT iShadWidth = 0,HINT iShaddir = -1,KBIRDVIEWPARA* param = NULL) = 0;

	virtual ERRINFO PolyLine(vector<REPOINT>& lppt, HLONG nCount, RECOLOR clrFore, 
		HINT iWidth = 1, HDWORD dwFlag = RE_LS_NORMAL,
		RECOLOR clrBack = RECOLOR(0, 0, 0 ),HINT iShadWidth = 0,HINT iShaddir = -1,HBOOL bHalfTrans = false) = 0;

    // ������·�ĺ���. Ĭ���Ǻ�ɫ,���ǵ����ܻ����·��һ������(�������),Ҳ��ָ��������ɫ
    // ������·����ʹ��GDI�����߻��ƺ���
    virtual ERRINFO DrawRailway(REPOINT* lppt, HLONG nCount, HBYTE r = 0, HBYTE g = 0, HBYTE b = 0) = 0;

    virtual ERRINFO DrawRectFrame(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color, HINT width) = 0;
	virtual ERRINFO DrawRoundRect(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color, HINT r)=0;
    virtual ERRINFO DrawRoundRectFrame(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color, HINT nround) = 0;

    // ʹ����ɫ������.
    //
    virtual ERRINFO FillSolidRect(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color) = 0;

    virtual ERRINFO FillTansparentRect(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color) = 0;
    //���ƽ���ɫ����
    virtual ERRINFO FillLinearGridiantRect(HLONG x1, HLONG y1, HLONG x2, HLONG y2, HDWORD Startcolor, HDWORD Endcolor , LINERTYPE typ, RECOLOR FrontClr, HBYTE byBaseAlpha = TRANSPARENTLEVEL) = 0;

    // ���ƶ����
    //
	virtual ERRINFO Polygon(const REPOINT* lppt, HLONG lCount, RECOLOR Color,HINT Type=RE_PG_NORMAL, IReSurface* pTexture=NULL) = 0;

	virtual ERRINFO Polygon(const vector<REPOINT>& lppt, HLONG lCount, RECOLOR Color,HINT Type=RE_PG_NORMAL) = 0;

    // ����Բ��
    virtual ERRINFO Ellipse(HLONG left, HLONG top, HLONG right, HLONG bottom) = 0;

    //��Բ
    virtual void Circle(HINT x1, HINT y1, HINT r, HBOOL bFill, RECOLOR* color) = 0;

    // �����ַ�������.
    // x, y: �ַ�������, NORMALʱΪ���Ͻ�����, CENTERʱΪ��������
    // MultiString: �ַ���
    // clrFore: ����ǰ��ɫ,Ϊ��ʱʹ��ȱʡ����ǰ��ɫ
    // clrBack: ���ֱ���ɫ,Ϊ��ʱʹ��ȱʡ���屳��ɫ
    // dwFormat: ��ʽ
    //
    virtual ERRINFO DrawString(HLONG x, HLONG y, HBYTE * MultiString, RECOLOR* clrFore = NULL,
                               HDWORD dwFormat = RE_TS_NORMAL, RECOLOR* pclrBack = NULL) = 0;
    //����Unicode�ַ���������
    virtual ERRINFO DrawUCodeString(HLONG x, HLONG y, HINT width, HBYTE * MultiString, RECOLOR* clrFore,
                                    HDWORD dwFormat = RE_TS_NORMAL, RECOLOR* pclrBack = NULL) = 0;
    // ��ԴSrc�����ָ�������ͼ�񿽱����������ָ����
    virtual ERRINFO BitBlt(IReSurface* pSrcdc, // ԴDC
                           HINT xTar,       // Ŀ����x����
                           HINT yTar,       // Ŀ����y����
                           HINT width,      // Ŀ�������
                           HINT height,     // Ŀ�����߶�
                           HINT xSrc,       // Դx����
                           HINT ySrc,       // Դy����
                           RECOLOR* pColor = NULL) = 0;  //ֻ���8λSurface

    virtual void  StretchBlt(IReSurface* pInSrc,  //ԴDC
                             HINT xTar,       //Ŀ����x����
                             HINT yTar,       //Ŀ����y����
                             HINT TarWidth,      //Ŀ�������
                             HINT TarHeight,     //Ŀ�����߶�
                             HINT xSrc,       //Դx����
                             HINT ySrc,        //Դy����
                             HINT SrcWidth,      //Ŀ�������
                             HINT SrcHeight,     //Ŀ�����߶�
                             HINT Quality = 1) = 0;

    virtual void RotateBlt(IReSurface* pSrcdc, // ԴDC
                           HINT xTar,          //Ŀ����x����
                           HINT yTar,          //Ŀ����y����
                           HINT iRotateAngle,   //��ת�Ƕ�
                           HINT quality = 0  //���� 0 ��  1��
                          ) = 0;
    virtual void RotateBlt(IReSurface* pSrcdc, // ԴDC
                           HFLOAT xSrc,          //Դ����ת��������
                           HFLOAT ySrc,          //Դ����ת��������
                           HINT xTar,          //��ת������Ŀ������������
                           HINT yTar,          //��ת������Ŀ������������
                           HINT iRotateAngle,   //��ת�Ƕ�
                           HINT quality   //���� 0 ��  1��
                          ) = 0;
    virtual ERRINFO ImageColorMatrix(HCColorMatrix& matrix,
                                     IReSurface* pInSrc,//ԴDC
                                     HINT xTar,       // Ŀ����x����
                                     HINT yTar,       // Ŀ����y����
                                     HINT width,      // Ŀ�������
                                     HINT height,     // Ŀ�����߶�
                                     HINT xSrc,       // Դx����
                                     HINT ySrc) = 0;  // Դy����

    // ������浽ktcͼ���ļ�.
    //
    virtual ERRINFO SaveSurface(const HString* pFileName,HINT nColorBit = 1) = 0;

    //draw guide arrow
    virtual  void   DrawLineArrow(const REPOINT& start, const REPOINT& end, HINT linewid, HINT width, int height, RECOLOR clr, HINT iAlpha) = 0;

    virtual HINT GetColorType() = 0;

    virtual HINT GetXPitch() = 0;

    virtual HINT GetYPitch() = 0;

    virtual RECOLOR GetColorKey() = 0;

    //��鵱ǰ���Ƿ�͸��
    virtual HBOOL CheckPoint(HINT x, HINT y) = 0;

    //���ÿ�����ʽΪ�Ҷ�
    virtual void SetGray(HBOOL v) = 0;
    virtual HBOOL IsGray() = 0;

    //�Ƿ��м�ֵ͸��
    virtual HBOOL IsColorKey() = 0;

    //��ͼ���ļ�װ��surface�������������ͼ���ļ��ߴ粻�����ʽ����16λ�����ܾ�����
    virtual ERRINFO LoadSurfaceFromFile(const HString& filename) = 0;

    virtual ERRINFO AlternationBitblt(IReSurface* pInSrcA, IReSurface* pInSrcB, POINT mid_pos,  HINT frame) = 0;

    // ģ��������Ч
    virtual ERRINFO BlurBitblt(IReSurface* pInSrc, // ԴDC
                               HINT xTar,       // Ŀ����x����
                               HINT yTar,       // Ŀ����y����
                               HINT width,      // Ŀ�������
                               HINT height,     // Ŀ�����߶�
                               HINT xSrc,       // Դx����
                               HINT ySrc,      // Դy����
                               HINT alpha,   // ͸����
                               HINT radius)  = 0;    //�뾶
    virtual ERRINFO GaussBlurBitblt(IReSurface* pInSrc, // ԴDC
                                    HINT xTar,       // Ŀ����x����
                                    HINT yTar,       // Ŀ����y����
                                    HINT width,      // Ŀ�������
                                    HINT height,     // Ŀ�����߶�
                                    HINT xSrc,       // Դx����
                                    HINT ySrc,       // Դy����
                                    HFLOAT sigma,    //
                                    HINT radius) = 0;

    // ͸���ȵ�Ӱ��Ч
    virtual ERRINFO AlphaShadeBitblt(IReSurface* pInSrc, // ԴDC
                                     HINT xTar,       // Ŀ����x����
                                     HINT yTar,       // Ŀ����y����
                                     HINT width,      // Ŀ�������
                                     HINT height,     // Ŀ�����߶�
                                     HINT xSrc,       // Դx����
                                     HINT ySrc,      // Դy����
                                     HINT alpha,   //  // ͸����
                                     HINT type) = 0;  // ���� 0������ 1���ݶ�

    virtual ERRINFO Convolve(
        HINT kernelWidth,
        HINT kernelHeight,
        HINT shiftX,
        HINT shiftY,
        HINT * kernel,
        HFLOAT scale,
        HINT bias = 0) = 0;

    // ͼ�������㷨
    virtual ERRINFO StretchBitBlt(IReSurface* pInSrc, // ԴDC
                                  POINT newLeftTop,  // Դͼ�����Ͻ���Ŀ��ͼ�ж�Ӧ��λ�� B
                                  POINT newRightTop, //Դͼ�����Ͻ���Ŀ��ͼ�ж�Ӧ��λ�� C
                                  POINT newLeftBottom,  // Դͼ�����½���Ŀ��ͼ�ж�Ӧ��λ�� A
                                  POINT newRightBottom, //Դͼ�����½���Ŀ��ͼ�ж�Ӧ��λ��  D
                                  HINT alpha = 0, //  ȫ��alpha
                                  HINT quality = 0) = 0; // ��������)

    // ˮ������Ч
    virtual ERRINFO RippleBitBlt(IReSurface* pInSrc, // ԴDC
                                 HINT xTar,       // Ŀ����x����
                                 HINT yTar,       // Ŀ����y����
                                 HINT frame,     // ֡���
                                 HINT Alpha,   // alphaֵ
                                 HINT xSrc,       // Դx����
                                 HINT ySrc,   // Դy����
                                 HINT srcWidth, // Դ���
                                 HINT srcHeight, // Դ�߶�
                                 HINT bType = 1, // ��Ӱ���� 0��NULL  1���ݶ� 2���̶�͸����ֵ
								 HBOOL bInvertOnly = false //�Ƿ񴿵�Ӱ��Ϊtrueʱֻ�е�Ӱû�в���
								 ) = 0;
	virtual void SingleLineS(HINT iStartX, HINT iStartY, HINT iEndX, HINT iEndY, const RECOLOR* pColor) = 0;

	//agg������㷨����
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