

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
// ���������㷨ʹ�õĽṹ
// ����ε���������Զ��պϣ����һ���㲻��Ҫ�ڵ�һ���غϣ�
struct PtListHeader
{
	HINT iLength;		// ��ĸ���
	REPOINT* pPointPtr;	// ָ��
	REPOINT texture_point; // ��ͼ���յ�

};

// ����ˮƽ�ߵ���ʼx�������ֹx����(ֻ�ڿ�����������ʹ��)
struct HorLine
{
	HINT iXStart;	// ����ߵĵ��xֵ  X coordinate of leftmost  pixel in line 
	HINT iXEnd;	// ���ұߵĵ��xֵ  X coordinate of rightmost pixel in line 
};

// ����һ��ˮƽɨ����,����������������,��YStart��ʼ����
// �����ڿ���ɨ��
struct HorLineList
{
	HINT iLength;				// ����ˮƽ�߱��ֳ��˶��ٶ�
	HINT iYStart;				// ��ʼyֵ
	struct HorLine* pHLinePtr;	// ÿһ�ε���ʼx����ֹx
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

//��ֵ����
extern HBYTE g_BlendMatrix[16][16][4];
extern ColorConvert colorConvert;

void InitBlendMatrix();
//ADD BY CXL
HWORD Blt32BitTo16Bit(HWORD*des16, HBYTE* src32);
HWORD Add16BitAnd32Bit(HWORD* des16, HBYTE* src32);
//��32λ�����ںϵ�24λĿ������
HINT Add24BitAnd32Bit(HBYTE* des24, HBYTE* src32);

ERRINFO Projection(RECT ViewPort,  // ��ʾ�����С
                   HINT SrcHeight,  // Դͼ��߶�
                   HINT SrcWidth,   // Դͼ����
                   HINT Angle,        // Դͼ����ת�Ƕ�
                   POINT* newLeftTop, // Դͼ�����Ͻ���Ŀ��ͼ�ж�Ӧ��λ�� B
                   POINT* newRightTop, //Դͼ�����Ͻ���Ŀ��ͼ�ж�Ӧ��λ�� C
                   POINT* newLeftBottom,  // Դͼ�����½���Ŀ��ͼ�ж�Ӧ��λ�� A
                   POINT* newRightBottom); //Դͼ�����½���Ŀ��ͼ�ж�Ӧ��λ��  D


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

public:  //������ IReSurface ����Ķ���ӿں���

    // �ͷ�surface��Դ,��������������������,����ֱ��ɾ������Ҳ����,���Բ����Ե���.
    ERRINFO Release() ;

    // ʹ��ָ����ɫ������� color.
    ERRINFO Clear(HBYTE byRed, HBYTE byGreen, HBYTE byBlue) ;

    // ʹ��ָ����ɫ�����������,ֻ�����ú�,�׻��߻Ҷ�,������ûҶ�ɫ,����ʹ���������
    ERRINFO ClearFast(HBYTE v);
    ERRINFO FillLinearGridiantRect(HLONG x1, HLONG y1, HLONG x2, HLONG y2, HDWORD Startcolor, HDWORD Endcolor , LINERTYPE typ, RECOLOR FrontClr, HBYTE baseAlpha = TRANSPARENTLEVEL);
    // ȡ�ñ�����ڴ�ָ������.
    void* GetRealSurf() ;

    // ȡ�ÿ��,���ص�λ.
    HDWORD GetWidth() ;

    // ȡ�ø߶�,���ص�λ
    HDWORD GetHeight() ;

    // ȡ��������ɫ
    RECOLOR GetPixelColor(HLONG x, HLONG y);

    // ȡ���ڴ����ݿ��С
    HINT GetMemDataLen() ;

    //ȡ��͸���ȵ�ֵ
    HBYTE GetTransparency();
#ifdef WIN32
    /*
    * ��������: ȡ��HDC
    * ��    ��:
    * �� �� ֵ:
    */
    HDC GetHDC();
#endif

    HCFont* GetFont();
    // ����͸����ֵ.���������24λ,ȡǰRGB����ֵ,�����16λɫ,ȡ����RGB16��ֵ
    // Ϊ�˱��ּ�����,�ṩ�ú���,����ֵһ��Ӧ��ͼƬ�ļ��ж���,�������ڳ���������
    // ������д����ɫֵ�����
    void SetColorKey(HBYTE byRed, HBYTE byGreen, HBYTE byBlue, HWORD rgb16 = -1);

    // ����ͼƬ͸����,0-TRANSPARENTLEVEL ֮��ȡֵ,��Ϊ0��ʾ͸����Ϊ0, TRANSPARENTLEVELΪ��͸��,
    //
    void SetTransparency(HBYTE byTrans) ;

    // �������ֵ�ȱʡ��ɫ
    void SetTextColor(HBYTE byRed, HBYTE byGreen, HBYTE byBlue);

    // ����ʹ�õ�����,��ʱ�ⲿ������,��ReDraw�г�ʼ��,�����ϵ�����ָ��
    HCFont* SetFont(HCFont* pFont);

    void drawLine_with_patten(REPOINT p1, REPOINT p2, int& cnt, float& hasDraw, RECOLOR* clrFore);

    // ����һ������,�������Ч�ʲ����, ������ȫ,�ṩ���ⲿʹ��
    ERRINFO DrawPixel(HLONG x, HLONG y, HBYTE r, HBYTE g, HBYTE b) ;
    ERRINFO DrawPixel(HLONG x, HLONG y, HBYTE r, HBYTE g, HBYTE b, HBYTE a) ;

    /*
    * ��������: ����һ��ֱ��
    * ��    ��:
    * �� �� ֵ:
    */
    ERRINFO DrawLine(HLONG x1, HLONG y1, HLONG x2, HLONG y2,
                     RECOLOR Color = RECOLOR(0, 0, 0), HINT iWidth = 1, HBOOL bAntialising = false) ;

    /*
	* ��������: ���ƶ����߶�
	* ��    ��:
	* �� �� ֵ:
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

    // ������·�ĺ���. Ĭ���Ǻ�ɫ,���ǵ����ܻ����·��һ������(�������),Ҳ��ָ��������ɫ
    // ������·����ʹ��GDI�����߻��ƺ���
    ERRINFO DrawRailway(REPOINT* lppt, HLONG nCount, HBYTE r = 0,
                        HBYTE g = 0, HBYTE b = 0) ;

    //���ƾ��ο�֧��͸����
    ERRINFO DrawRectFrame(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color, HINT width);

	ERRINFO DrawRoundRect(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color, HINT r);

    //����Բ�Ǿ��ο�֧��͸����
    ERRINFO DrawRoundRectFrame(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color, HINT r);

    // ʹ����ɫ������.
    //
    ERRINFO FillSolidRect(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color) ;

    //��͸�����ƾ���
    ERRINFO FillTansparentRect(HLONG x1, HLONG y1, HLONG x2, HLONG y2, RECOLOR color) ;

    /*
    * ��������:���ƶ����
    * ��    ��:
    * �� �� ֵ:
    */
    ERRINFO Polygon(const REPOINT* lppt, HLONG lCount, RECOLOR Color, HINT Type = RE_PG_NORMAL, IReSurface* pTexture = NULL) ;

    ERRINFO Polygon(const vector<REPOINT>& lppt, HLONG lCount, RECOLOR Color, HINT Type = RE_PG_NORMAL) ;

    // ����Բ��
    ERRINFO Ellipse(HLONG left, HLONG top, HLONG right, HLONG bottom) ;

//     // ����
//     ERRINFO DrawArc(
//         const REPOINT& o, // Բ��
//         kn_int r, // �뾶
//         kn_double startAngle, // �����Y����������Ƕ�
//         kn_double sweepAngle, // ɨ��Ƕ�
//         const RECOLOR& color = RECOLOR(0, 0, 0),// �����ɫ
//         kn_int width = 2, // �����
//         ARC_CUTTING_TYPE eType = CUTTING_V);// ��ֱ�ü���

    // �����ַ�������.
    // x, y: �ַ�������, NORMALʱΪ���Ͻ�����, CENTERʱΪ��������
    // MultiString: �ַ���
    // clrFore: ����ǰ��ɫ,Ϊ��ʱʹ��ȱʡ����ǰ��ɫ
    // clrBack: ���ֱ���ɫ,Ϊ��ʱʹ��ȱʡ���屳��ɫ
    // dwFormat: ��ʽ
    //
	ERRINFO DrawString(HLONG x, HLONG y, HBYTE * MultiString, RECOLOR* clrFore = NULL,
		HDWORD dwFormat = RE_TS_NORMAL, RECOLOR* pclrBack = NULL);
    //����Unicode�ַ�, ��Ҫ�ṩHMI�ַ�,����� width ֵΪ���ֿ���ʾ�Ŀ��,�������ֲ���ʾ
    ERRINFO DrawUCodeString(HLONG x, HLONG y, HINT width, HBYTE * MultiString,
                            RECOLOR* clrFore = NULL, HDWORD dwFormat = RE_TS_NORMAL,
                            RECOLOR* clrBack = NULL) ;
    //ʸ���ֻ��ƺ���,��Ҫ����Unicode�ַ� ʸ������ֻ֧�ֳ������ӰЧ��
    ERRINFO DrawTTFUCodeString(HLONG x, HLONG y, HINT width, HCHAR * MultiString,
                               const RECOLOR* clrFore, HDWORD dwFormat = RE_TS_NORMAL, const RECOLOR* clrBack = NULL) ;
    //���ݵ��ֽڻҶ�ͼ��Ϊ͸������Ϣ��ʹ��ָ����ɫ���Ƶ�����������ʸ�������Ԥ�õ�����λͼ����
    ERRINFO DrawBitmapChar(HLONG x, HLONG y, const RECOLOR* clrFore, HBYTE* buffer, HUINT w, HUINT h, HBYTE nTrans = TRANSPARENTLEVEL) ;

    // ��ԴSrc�����ָ�������ͼ�񿽱����������ָ����
    ERRINFO BitBlt(IReSurface* pSrcdc, // ԴDC
                   HINT xTar,       // Ŀ����x����
                   HINT yTar,       // Ŀ����y����
                   HINT width,      // Ŀ�������
                   HINT height,     // Ŀ�����߶�
                   HINT xSrc,       // Դx����
                   HINT ySrc,       // Դy����
                   RECOLOR* pColor = NULL) ; // ������ɫ��ֻ���8λɫ��surface

    //���ſ�������
    void  StretchBlt(IReSurface* pInSrc,  //ԴDC
                     HINT xTar,       //Ŀ����x����
                     HINT yTar,       //Ŀ����y����
                     HINT TarWidth,      //Ŀ�������
                     HINT TarHeight,     //Ŀ�����߶�
                     HINT xSrc,       //Դx����
                     HINT ySrc,       //Դy����
                     HINT SrcWidth,      //Ŀ�������
                     HINT SrcHeight,  //Ŀ�����߶�
                     HINT Quality = 1);

    //////////////////////////////////////////////////////////////////////////
    //chenzhi
    //���ſ�������, һ�� ������
    void  StretchBltQualityOne(IReSurface* pSrcdc, // ԴDC
                               HINT xTar,       //Ŀ����x����
                               HINT yTar,       //Ŀ����y����
                               HINT TarWidth,      //Ŀ�������
                               HINT TarHeight,     //Ŀ�����߶�
                               HINT xSrc,       //Դx����
                               HINT ySrc,       //Դy����
                               HINT SrcWidth,      //Ŀ�������
                               HINT SrcHeight);       //Ŀ�����߶�

    //���ſ�������, ���� �е����� ��ģ��
    void  StretchBltQualityTwo(IReSurface* pSrcdc, // ԴDC
                               HINT xTar,       //Ŀ����x����
                               HINT yTar,       //Ŀ����y����
                               HINT TarWidth,      //Ŀ�������
                               HINT TarHeight,     //Ŀ�����߶�
                               HINT xSrc,       //Դx����
                               HINT ySrc,       //Դy����
                               HINT SrcWidth,      //Ŀ�������
                               HINT SrcHeight);       //Ŀ�����߶�

    //���ſ�������, ���� ������ ���ű����ϴ�ʱ����
    void  StretchBltQualityThree(IReSurface* pSrcdc, // ԴDC
                                 HINT xTar,       //Ŀ����x����
                                 HINT yTar,       //Ŀ����y����
                                 HINT TarWidth,      //Ŀ�������
                                 HINT TarHeight,     //Ŀ�����߶�
                                 HINT xSrc,       //Դx����
                                 HINT ySrc,       //Դy����
                                 HINT SrcWidth,      //Ŀ�������
                                 HINT SrcHeight);     //Ŀ�����߶�

    void BoundStretchBlt(IReSurface* pSrcdc, // ԴDC
                         HINT xTar,       //Ŀ����x����
                         HINT yTar,       //Ŀ����y����
                         HINT TarWidth,      //Ŀ�������
                         HINT TarHeight,     //Ŀ�����߶�
                         HINT xSrc,       //Դx����
                         HINT ySrc,       //Դy����
                         HINT SrcWidth,      //Դ���
                         HINT SrcHeight,     //Դ�߶�
                         HINT Quality);     //����������1:��������2:��������Ĭ��Ϊ������

    //////////////////////////////////////////////////////////////////////////
    //��ת����
    void RotateBltLow(IReSurface* pSrcdc, // ԴDC
                      HINT xTar,          //Ŀ����x����
                      HINT yTar,          //Ŀ����y����
                      HINT iRotateAngle   //��ת�Ƕ�
                     );
    void RotateBltHigh(IReSurface* pSrcdc, // ԴDC
                       HFLOAT xTar,          //Ŀ����x����
                       HFLOAT yTar,          //Ŀ����y����
                       HINT iRotateAngle   //��ת�Ƕ�
                      );
    void RotateBlt(IReSurface* pSrcdc, // ԴDC
                   HINT xTar,          //Ŀ����x����
                   HINT yTar,          //Ŀ����y����
                   HINT iRotateAngle,   //��ת�Ƕ�
                   HINT quality = 0  //���� 0 ��  1��
                  ) ;
    void RotateBlt(IReSurface* pSrcdc, // ԴDC
                   HFLOAT xSrc,          //Դ����ת��������
                   HFLOAT ySrc,          //Դ����ת��������
                   HINT xTar,          //��ת������Ŀ������������
                   HINT yTar,          //��ת������Ŀ������������
                   HINT iRotateAngle,   //��ת�Ƕ�
                   HINT quality   //���� 0 ��  1��
                  ) ;

    ERRINFO ImageColorMatrix(HCColorMatrix& matrix,
                             IReSurface* pInSrc,
                             HINT xTar,       // Ŀ����x����
                             HINT yTar,       // Ŀ����y����
                             HINT width,      // Ŀ�������
                             HINT height,     // Ŀ�����߶�
                             HINT xSrc,       // Դx����
                             HINT ySrc);  // Դy����
    //////////////////////////////////////////////////////////////////////////

    // ������浽ktcͼ���ļ�.
    //
    ERRINFO SaveSurface(const HString* pFileName,HINT nColorBit = 1);

    //��Բ
    void Circle(HINT x1, HINT y1, HINT r, HBOOL bFill, RECOLOR* color);

    //draw guide arrow
    void   DrawLineArrow(const REPOINT& start, const REPOINT& end, HINT linewid, HINT width, int height, RECOLOR clr, HINT iAlpha);

    //��鵱ǰ���Ƿ�͸��,���ڰ�ť��Ϣ�ж�����
    HBOOL CheckPoint(HINT x, HINT y);

    //agg����Ļ���polyline
    ERRINFO AGGPolyLine(REPOINT* lppt, HLONG nCount, RECOLOR clrFore,
                        HINT width = 1, HDWORD dwFlag = RE_LS_NORMAL, RECOLOR clrBack = RECOLOR(0, 0, 0), HINT shadWidth = 0, HINT shaddir = -1);

public: //�����������������Ĺ��ú���

    //����һ����surface
    ERRINFO CreateSurface(HINT width, HINT height, HDWORD dwColorFormat, HBOOL bUseDraw = false, HBOOL bCreateDC = false);
	//strWidth ֻ��RE_TS_END_ELLIPSIS
    ERRINFO CreateTTFFontSurface(HINT font_width, HINT font_height, HCFont* pFont, HDWORD dwFormat, const HCHAR* str, HINT strWidth = 0);
    void Draw256Surface(IReSurface* pSrcSurf, int xDest, int yDest, int width, int height, RECOLOR color, int xSrc, int ySrc);
    void Draw256Surface(IReSurface* pSrcSurf, int xDest, int yDest, int width, int height, RECOLOR color, int xSrc, int ySrc, HINT yStart, HINT yEnd, HINT startAlpha, HINT endAlpha);
    //����ͼ���ļ�����surface
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
	//�����ɢ�����㷨
	void  CvsPic24To16_ErrorDiffuse_1( HBYTE*  dst, const HBYTE*  src, long width, long height, long src_width_byte, long dst_width_byte);

    //��ͼ���ļ�װ��surface�������������ͼ���ļ��ߴ粻�����ʽ����16λ�����ܾ�����
    ERRINFO LoadSurfaceFromFile(const HString& filename);
    ERRINFO LoadSurfaceFromKtcFile(const HString& filename);
    ERRINFO LoadSurfaceFromJpegFile(const HString& filename);
    ERRINFO LoadSurfaceFromePNG(HBYTE* mem, HDWORD size);

    void BrushLineMask(HINT iStartX, HINT iStartY, HINT iEndX, HINT iEndY,  RECOLOR* pBack, HINT brID = 0);
    void BrushDotMask(HINT x, HINT y, REBrushGenerate* br, RECOLOR* pclr);
    void BlendBrushWithForClr(RECOLOR* pclr, RECTANGLE& rct);
    void TransformMask(HINT a , HINT b , HINT Trans);
    HINT ShadowBlend(HINT type, RECOLOR* clr, RECOLOR* shadow = NULL);

    //�Ƿ��м�ֵ͸��
    HBOOL IsColorKey();

    //ȡ�ü�ֵ��ɫ
    RECOLOR GetColorKey();

    HINT GetColorType();

    HINT GetXPitch();

    HINT GetYPitch();
    //���ÿ�����ʽΪ�Ҷ�
    void SetGray(HBOOL v);
    HBOOL IsGray();

    static HBYTE GetGrayValue(HBYTE r, HBYTE g, HBYTE b);

    // ����ת������ �����������������.����������������
    // ���ת����tarRect srcRect��һ������Ϊ��, �򷵻�FALSE
    static HBOOL CalCoordinate(HINT xTar, HINT yTar, HINT widthTar, HINT heightTar, HINT width, HINT height,
                                 HINT xSrc, HINT ySrc, HINT widthSrc, HINT heightSrc, RECTANGLE& tarRect, RECTANGLE& srcRect);

    void BrightToRGB(RECOLOR& Clr, BRIGHT Bright);
    void RGBToBright(RECOLOR& Clr, BRIGHT& Bright);

    /*
    * ��������: ��Ӱ�Ŀ���
    * ��    ��:
    *      iStartX    [in]  ���X
    *      iStartY    [in]  ���Y
    *      iEndX      [in]  �յ�X
    *      iEndY      [in]  �յ�Y
    *      iWidth     [in]  ���
    *      iShadWidth [in]  ��Ӱ�Ŀ��
    *      iDir       [in]  ����
    *      pColor     [in]  ��ɫ
    * �� �� ֵ:
    */
    void WidthLineShadow(HINT iStartX, HINT iStartY, HINT iEndX, HINT iEndY, HINT iWidth,
                         HINT iShadWidth, HINT iDir, RECOLOR* pColor);

	inline void Pixel(HINT x, HINT y, const RECOLOR* color);

protected:
    // ���GDIͼ����ֽڶ��뺯����24λ�����widthӦ�ó�3
    HLONG AdjustWidth(HLONG width)
    {
        if (width % 4 == 0)    return    width;
        else    return    width - width % 4 + 4;
    };


    //������д�����ֺ���
    //drawwidth ��������ֻ��ƿ��, С��0��ʾ������
    ERRINFO DrawText(HINT x, HINT y, HBYTE * MultiString, const RECOLOR* color, HDWORD dwFormat, const RECOLOR* clrBack = NULL, HINT drawwidth = 0);

    //��㺯��,Ϊ��֤�ٶ�,��������Ϸ����ж�,���ú���Ӧ��֤��Խ��
    inline void Pixel16(HINT x, HINT y, HWORD color);
    inline void Pixel24(HINT x, HINT y, const RECOLOR* color);
    inline void Pixel32(HINT x, HINT y, const RECOLOR* color);

    /*
    * ��������:  ��㺯��
    * ��    ��:
    *      pData   [in]  �ڴ�ָ��
    *      dwColor [in]  ��ɫ
    * �� �� ֵ:
    */
    inline void Pixel16F(HWORD* pData, HWORD wColor)
    {
        *pData = wColor;
    };

    /*
    * ��������:  ��㺯��
    * ��    ��:
    *      pData   [in]  �ڴ�ָ��
    *      dwColor [in]  ��ɫ
    * �� �� ֵ:
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
    * ��������: �����������ߵĿ���(����)
    * ��    ��:
    *      iStartX [in]  ���X
    *      iStartY [in]  ���Y
    *      iEndX   [in]  �յ�X
    *      iEndY   [in]  �յ�Y
    *      iWidth  [in]  ���
    *      pFore   [in]   ǰ����ɫ
    *      pBack   [in]   ������ɫ
    * �� �� ֵ:
    */
    void WidthLineWithAdgeSFast(HINT StartX, HINT StartY, HINT EndX, HINT EndY, HINT Width, RECOLOR* color, RECOLOR* color1);
    void WidthLineS3(HINT iStartX, HINT iStartY, HINT iEndX, HINT iEndY, HINT iWidth, RECOLOR* pColor, RECOLOR*pEdgeColor);
    void PolyLineBird(REPOINT* lppt, HLONG lCount, RECOLOR clrFore, HINT iWidth, HBOOL  bhalf = false);


    // ���ݶ��뷽ʽ����(x, y)  �������ֶ���
    void AdjustAlignFormat(HINT& x, HINT& y, HINT width, HINT height, HDWORD uFormat);

    //���ڴ��߻��Ƶĺ�����
    //���߻���
    void SingleLine(HINT StartX, HINT StartY, HINT EndX, HINT EndY, const RECOLOR* color);
    //�Կ�һ��ĵ��߻���
    void VerboseLine(HINT StartX, HINT StartY, HINT EndX, HINT EndY, const RECOLOR* color);

	void SingleLineS(HINT iStartX, HINT iStartY, HINT iEndX, HINT iEndY, const RECOLOR* pColor);

	/*
	* ��������: ���������߻���
	* ��    ��:
	*      iStartX [in]  ���X
	*      iStartY [in]  ���Y
	*      iEndX   [in]  �յ�X
	*      iEndY   [in]  �յ�Y
	*      iWidth  [in]  ���
	*      pColor  [in]  ��ɫ
	* �� �� ֵ: 
	*/	
	void WidthLineS(HINT iStartX, HINT iStartY, HINT iEndX, HINT iEndY, HINT iWidth, const RECOLOR* pColor);

	/*
	* ��������: �����������ߵĿ���
	* ��    ��:
	*      iStartX [in]  ���X
	*      iStartY [in]  ���Y
	*      iEndX   [in]  �յ�X
	*      iEndY   [in]  �յ�Y
	*      iWidth  [in]  ���
	*      pFore   [in]   ǰ����ɫ
	*      pBack   [in]   ������ɫ
	* �� �� ֵ: 
	*/	
	void WidthLineWithAdgeS(HINT iStartX, HINT iStartY, HINT iEndX, HINT iEndY, HINT iWidth, RECOLOR* pFore,RECOLOR* pBack);

    //������
    void WidthLine(HINT StartX, HINT StartY, HINT EndX, HINT EndY, HINT Width, const RECOLOR* color);
    //�������ߵĿ���
    void WidthLineWithAdge(HINT StartX, HINT StartY, HINT EndX, HINT EndY, HINT Width, const RECOLOR* color, const RECOLOR* color1);
    //������
    void WidthLinePattern(HINT StartX, HINT StartY, HINT EndX, HINT EndY, HINT Width, const RECOLOR* color,
                           HBYTE byDraw, HBYTE byUnDraw, HBYTE& startPos, HBOOL& bFirst);

    //////////////////////////////////////////////////////////////////////////
    //�����Ƕ��������㷨��صĺ����ͽṹ
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
    ERRINFO RippleBitBlt(IReSurface* pInSrc, // ԴDC
                         HINT xTar,       // Ŀ����x����
                         HINT yTar,       // Ŀ����y����
                         HINT frame,     // ֡���
                         HINT Alpha,   // alphaֵ
                         HINT xSrc,       // Դx����
                         HINT ySrc,   // Դy����
                         HINT srcWidth, // Դ���
                         HINT srcHeight, // Դ�߶�
						 HINT bType = 1,// ��Ӱ���� 0��NULL  1���ݶ� 2���̶�͸����ֵ
						 HBOOL bInvertOnly = false //�Ƿ񴿵�Ӱ��Ϊtrueʱֻ�е�Ӱû�в���
                         );  

    ERRINFO StretchBitBlt(IReSurface* pInSrc, // ԴDC
                          POINT newLeftTop,  // Դͼ�����Ͻ���Ŀ��ͼ�ж�Ӧ��λ��
                          POINT newRightTop, //Դͼ�����Ͻ���Ŀ��ͼ�ж�Ӧ��λ��
                          POINT newLeftBottom,  //// Դͼ�����½���Ŀ��ͼ�ж�Ӧ��λ��
                          POINT newRightBottom,  //Դͼ�����½���Ŀ��ͼ�ж�Ӧ��λ��
                          HINT alpha = 0, //  ȫ��alpha
                          HINT quality = 0); // ��������

    ERRINFO AlternationBitblt(IReSurface* pInSrcA, // ԴA
                              IReSurface* pInSrcB,// ԴB
                              POINT mid_pos, // Ŀ�����ĵ�����
                              HINT frame); // ��ǰ֡��

    ERRINFO BlurBitblt(IReSurface* pInSrc, // ԴDC
                       HINT xTar,       // Ŀ����x����
                       HINT yTar,       // Ŀ����y����
                       HINT width,      // Ŀ�������
                       HINT height,     // Ŀ�����߶�
                       HINT xSrc,       // Դx����
                       HINT ySrc,   // Դy����
                       HINT alpha = 255, // ͸����
                       HINT radius = 3);//�뾶
    ERRINFO GaussBlurBitblt(IReSurface* pInSrc, // ԴDC
                            HINT xTar,       // Ŀ����x����
                            HINT yTar,       // Ŀ����y����
                            HINT width,      // Ŀ�������
                            HINT height,     // Ŀ�����߶�
                            HINT xSrc,       // Դx����
                            HINT ySrc,       // Դy����
                            HFLOAT sigma,    //
                            HINT radius);     //

    ERRINFO AlphaShadeBitblt(IReSurface* pInSrc, // ԴDC
                             HINT xTar,       // Ŀ����x����
                             HINT yTar,       // Ŀ����y����
                             HINT width,      // Ŀ�������
                             HINT height,     // Ŀ�����߶�
                             HINT xSrc,       // Դx����
                             HINT ySrc,      // Դy����
                             HINT alpha = 0,   // ͸����
                             HINT type = 1); // ���� 0������ 1���ݶ�

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
    ERRINFO AlphaShadeBitblt_Whole(IReSurface* pInSrc, // ԴDC
                                   HINT xTar,       // Ŀ����x����
                                   HINT yTar,       // Ŀ����y����
                                   HINT width,      // Ŀ�������
                                   HINT height,     // Ŀ�����߶�
                                   HINT xSrc,       // Դx����
                                   HINT ySrc,      // Դy����
                                   HINT alpha);   //  // ͸����

    ERRINFO AlphaShadeBitblt_Gradient(IReSurface* pInSrc, // ԴDC
                                      HINT xTar,       // Ŀ����x����
                                      HINT yTar,       // Ŀ����y����
                                      HINT width,      // Ŀ�������
                                      HINT height,     // Ŀ�����߶�
                                      HINT xSrc,       // Դx����
                                      HINT ySrc,      // Դy����
                                      HINT aipha);   //  // ͸����

    void LeftTop(IReSurface* pInSrc, // ԴDC
                 POINT newLeftTop,  // Դͼ�����Ͻ���Ŀ��ͼ�ж�Ӧ��λ�� B
                 POINT newRightTop, //Դͼ�����Ͻ���Ŀ��ͼ�ж�Ӧ��λ�� C
                 POINT newLeftBottom,  //// Դͼ�����½���Ŀ��ͼ�ж�Ӧ��λ�� A
                 POINT newRightBottom, //Դͼ�����½���Ŀ��ͼ�ж�Ӧ��λ��  D
                 HINT alpha);
    void RightTop(IReSurface* pInSrc, // ԴDC
                  POINT newLeftTop,  // Դͼ�����Ͻ���Ŀ��ͼ�ж�Ӧ��λ�� B
                  POINT newRightTop, //Դͼ�����Ͻ���Ŀ��ͼ�ж�Ӧ��λ�� C
                  POINT newLeftBottom,  //// Դͼ�����½���Ŀ��ͼ�ж�Ӧ��λ�� A
                  POINT newRightBottom, //Դͼ�����½���Ŀ��ͼ�ж�Ӧ��λ��  D
                  HINT alpha);
    void LeftBottom(IReSurface* pInSrc, // ԴDC
                    POINT newLeftTop,  // Դͼ�����Ͻ���Ŀ��ͼ�ж�Ӧ��λ�� B
                    POINT newRightTop, //Դͼ�����Ͻ���Ŀ��ͼ�ж�Ӧ��λ�� C
                    POINT newLeftBottom,  //// Դͼ�����½���Ŀ��ͼ�ж�Ӧ��λ�� A
                    POINT newRightBottom, //Դͼ�����½���Ŀ��ͼ�ж�Ӧ��λ��  D
                    HINT alpha);
    void RightBottom(IReSurface* pInSrc, // ԴDC
                     POINT newLeftTop,  // Դͼ�����Ͻ���Ŀ��ͼ�ж�Ӧ��λ�� B
                     POINT newRightTop, //Դͼ�����Ͻ���Ŀ��ͼ�ж�Ӧ��λ�� C
                     POINT newLeftBottom,  //// Դͼ�����½���Ŀ��ͼ�ж�Ӧ��λ�� A
                     POINT newRightBottom, //Դͼ�����½���Ŀ��ͼ�ж�Ӧ��λ��  D
                     HINT alpha);
    void FillLine(IReSurface* pInSrc, //ԴDC
                  POINT oldLineStart, // ԴDCɨ���߿�ʼλ��
                  POINT oldLineEnd, // ԴDCɨ���߽���λ��
                  POINT newLineStart, // Ŀ��DCɨ���߿�ʼλ��
                  POINT newLineEnd, // ԴDCɨ���߽���λ��
                  HINT alpha);// ͸����

    RECOLOR GetBlurValue(IReSurface* pInSrc, //ԴDC
                         HINT x,
                         HINT y,
                         HINT radius = 3);

	/*
	* ��������: �ü������
	* ��    ��:
	*      lppt  [in]  �ü�ǰ�ĵ�
	*      lCount [in]  ��ĸ���
	*      Clippt   [in]   �ü���ĵ�
	* �� �� ֵ:�ཻ��
	*/
	HBOOL ClipPoly(const REPOINT* lppt, HLONG lCount,vector<REPOINT>& Clippt);


	/*
	* ��������: �ཻ���㣬������ཻ�ĵ�
	* ��    ��:
	*      ptPrev  [in]  ���
	*      ptAfter [in]  �յ�
	*      iType   [in]  �;��ο��ཻ�ı�
	* �� �� ֵ:�ཻ��
	*/
	REPOINT InterSect(REPOINT& ptPrev,REPOINT& ptAfter,HINT iType);


protected: //��Ա
    HINT  m_iType;        //surface����ɫģʽ 565 555 888 32
    HBOOL m_bColorKey;    //�Ƿ�ʹ����ɫ��ֵ͸��
    HBOOL m_bGray;    //תΪ�Ҷ�ͼ����

#ifdef WIN32
    HDC     m_Hdc;      //�豸DC
    HBITMAP m_Hbmp;     //�豸λͼ
#endif
    BITMAPINFO  m_BmpInfo;    //λͼ��Ϣ�ṹ
    HDWORD    m_dwMemTemp[4];  //Ϊ������565��ʽ�����Mask����,һ��Ҫ����m_BmpInfo���涨��

    HBYTE*  m_pData;  //�豸��λͼ�ڴ����ݵ�ַָ��
    RECOLOR m_clrKey;   //͸����ɫֵ
    RECOLOR m_clrText;  //ȱʡ������ǰ��ɫ

    //����͸����,0-TRANSPARENTLEVEL, 0��ȫ͸��, TRANSPARENTLEVEL��͸��
    //�м�ֵΪN/TRANSPARENTLEVEL͸����, ������Чֵ������͸������
    //�˲���ֻ����λͼ���͵� Bitblt copy
    HBYTE    m_byTransparent;

    //����ʸ�����ƿ���͸����
    HBYTE    m_byDrawTrans;

    HCFont* m_pFont; //����ָ��, �ⲿ����, ����ɾ��

    HINT     m_iXPitch; //ÿ�����ֽ���
    HINT     m_iYPitch; //ÿ�������ֽ���

    HBYTE** m_pRGB_Transparent_table;  // Alpha tableָ��
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
    HINT m_nPaletteColor; //��ɫ����ɫ��
};

#endif //_RE_SURFACE__
