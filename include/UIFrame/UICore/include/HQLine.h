// HQLINE.h: interface for the CHQLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HQLINE_H__0D9E2B92_1D82_484E_A75C_79100805120B__INCLUDED_)
#define AFX_HQLINE_H__0D9E2B92_1D82_484E_A75C_79100805120B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "RenderingEngine.h"

#define HQ_END_ROUND    0x2
#ifndef PI
#define PI 3.1415926535897935
#endif

const int LINE_TAN_TABLE[65] =
{
    0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 9, 10, 11, 12, 13, 14, 14, 15, 16, 17, 18, 18, 19, 20, 21, 22, 22, 23,
    24, 25, 25, 26, 27, 27, 28, 29, 30, 30, 31, 32, 32, 33, 33, 34, 35, 35, 36, 36, 37, 37, 38, 39, 39,
    40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45
};

const int LINE_COS_TABLE[361] =
{
    // 放大512倍
    512, 511, 511, 511, 510, 510, 509, 508, 507, 505, 504, 502, 500, 498, 496, 494, 492, 489, 486,
    484, 481, 477, 474, 471, 467, 464, 460, 456, 452, 447, 443, 438, 434, 429, 424, 419, 414, 408,
    403, 397, 392, 386, 380, 374, 368, 362, 355, 349, 342, 335, 329, 322, 315, 308, 300, 293, 286,
    278, 271, 263, 255, 248, 240, 232, 224, 216, 208, 200, 191, 183, 175, 166, 158, 149, 141, 132,
    123, 115, 106, 97, 88, 80, 71, 62, 53, 44, 35, 26, 17, 8, 0, -8, -17, -26, -35, -44, -53, -62, -71,
    -80, -88, -97, -106, -115, -123, -132, -141, -149, -158, -166, -175, -183, -191, -200, -208, -216,
    -224, -232, -240, -248, -256, -263, -271, -278, -286, -293, -300, -308, -315, -322, -329, -335,
    -342, -349, -355, -362, -368, -374, -380, -386, -392, -397, -403, -408, -414, -419, -424, -429,
    -434, -438, -443, -447, -452, -456, -460, -464, -467, -471, -474, -477, -481, -484, -486, -489,
    -492, -494, -496, -498, -500, -502, -504, -505, -507, -508, -509, -510, -510, -511, -511, -511,
    -512, -511, -511, -511, -510, -510, -509, -508, -507, -505, -504, -502, -500, -498, -496, -494,
    -492, -489, -486, -484, -481, -477, -474, -471, -467, -464, -460, -456, -452, -447, -443, -438,
    -434, -429, -424, -419, -414, -408, -403, -397, -392, -386, -380, -374, -368, -362, -355, -349,
    -342, -335, -329, -322, -315, -308, -300, -293, -286, -278, -271, -263, -255, -248, -240, -232,
    -224, -216, -208, -200, -191, -183, -175, -166, -158, -149, -141, -132, -123, -115, -106, -97,
    -88, -80, -71, -62, -53, -44, -35, -26, -17, -8, 0, 8, 17, 26, 35, 44, 53, 62, 71, 80, 88, 97, 106,
    115, 123, 132, 141, 149, 158, 166, 175, 183, 191, 200, 208, 216, 224, 232, 240, 248, 256, 263,
    271, 278, 286, 293, 300, 308, 315, 322, 329, 335, 342, 349, 355, 362, 368, 374, 380, 386, 392,
    397, 403, 408, 414, 419, 424, 429, 434, 438, 443, 447, 452, 456, 460, 464, 467, 471, 474, 477,
    481, 484, 486, 489, 492, 494, 496, 498, 500, 502, 504, 505, 507, 508, 509, 510, 510, 511, 511, 511, 512
};

const int LINE_SIN_TABLE[361] =
{
    // 放大512倍
    0, 8, 17, 26, 35, 44, 53, 62, 71, 80, 88, 97, 106, 115, 123, 132, 141, 149, 158, 166, 175, 183, 191,
    200, 208, 216, 224, 232, 240, 248, 256, 263, 271, 278, 286, 293, 300, 308, 315, 322, 329, 335,
    342, 349, 355, 362, 368, 374, 380, 386, 392, 397, 403, 408, 414, 419, 424, 429, 434, 438, 443,
    447, 452, 456, 460, 464, 467, 471, 474, 477, 481, 484, 486, 489, 492, 494, 496, 498, 500, 502,
    504, 505, 507, 508, 509, 510, 510, 511, 511, 511, 512, 511, 511, 511, 510, 510, 509, 508, 507,
    505, 504, 502, 500, 498, 496, 494, 492, 489, 486, 484, 481, 477, 474, 471, 467, 464, 460, 456,
    452, 447, 443, 438, 434, 429, 424, 419, 414, 408, 403, 397, 392, 386, 380, 374, 368, 362, 355,
    349, 342, 335, 329, 322, 315, 308, 300, 293, 286, 278, 271, 263, 255, 248, 240, 232, 224, 216,
    208, 200, 191, 183, 175, 166, 158, 149, 141, 132, 123, 115, 106, 97, 88, 80, 71, 62, 53, 44, 35,
    26, 17, 8, 0, -8, -17, -26, -35, -44, -53, -62, -71, -80, -88, -97, -106, -115, -123, -132, -141, -149,
    -158, -166, -175, -183, -191, -200, -208, -216, -224, -232, -240, -248, -256, -263, -271, -278,
    -286, -293, -300, -308, -315, -322, -329, -335, -342, -349, -355, -362, -368, -374, -380, -386,
    -392, -397, -403, -408, -414, -419, -424, -429, -434, -438, -443, -447, -452, -456, -460, -464,
    -467, -471, -474, -477, -481, -484, -486, -489, -492, -494, -496, -498, -500, -502, -504, -505,
    -507, -508, -509, -510, -510, -511, -511, -511, -512, -511, -511, -511, -510, -510, -509, -508,
    -507, -505, -504, -502, -500, -498, -496, -494, -492, -489, -486, -484, -481, -477, -474, -471,
    -467, -464, -460, -456, -452, -447, -443, -438, -434, -429, -424, -419, -414, -408, -403, -397,
    -392, -386, -380, -374, -368, -362, -355, -349, -342, -335, -329, -322, -315, -308, -300, -293,
    -286, -278, -271, -263, -255, -248, -240, -232, -224, -216, -208, -200, -191, -183, -175, -166,
    -158, -149, -141, -132, -123, -115, -106, -97, -88, -80, -71, -62, -53, -44, -35, -26, -17, -8, 0,
};

enum cell_block_scale_e
{
    cell_block_shift = 12,
    cell_block_size  = 1 << cell_block_shift,
    cell_block_mask  = cell_block_size - 1,
    cell_block_pool  = 256,
    cell_block_limit = 1024
};
enum poly_subpixel_scale_e
{
    poly_subpixel_shift = 8,                      //----poly_subpixel_shift
    poly_subpixel_scale = 1 << poly_subpixel_shift, //----poly_subpixel_scale
    poly_subpixel_mask  = poly_subpixel_scale - 1,  //----poly_subpixel_mask
};


typedef struct PU // 单个像素单元 pixelUnit
{
    int x;
    int y;
    int cover;
    int area;
    PU()
    {
        x = 0x7FFFFFFF;
        y = 0x7FFFFFFF;
        cover = 0;
        area  = 0;
    }
    int not_equal(int ex, int ey) const
    {
        return (ex - x) | (ey - y);
    }
    void initial()
    {
        x = 0x7FFFFFFF;
        y = 0x7FFFFFFF;
        cover = 0;
        area  = 0;
    }
} PU , *ptrPU;

class ScanLine;

class RasterizePU
{
public:
    struct sorted_y
    {
        unsigned start;
        unsigned num;
        sorted_y(): start(0), num(0)
        {
        }
    };

    RasterizePU(): m_cells(NULL), m_sorted_cells(NULL), m_curr_cell(), m_sorted_y(0), m_sorted(false), m_num_cells(0),
        m_min_x(0x7FFFFFFF), m_min_y(0x7FFFFFFF), m_max_x(-0x7FFFFFFF), m_max_y(-0x7FFFFFFF), m_num_blocks(0), m_max_blocks(0),
        m_curr_block(0)
    {
        m_curr_cell.x = 0x7FFFFFFF;
        m_curr_cell.y = 0x7FFFFFFF;
        m_curr_cell.area = 0;
        m_curr_cell.cover = 0;
    }

    ~RasterizePU();
    void Reset();
    void SortPUs();
    void AllocateBlock();
    void add_curr_cell();
    void qsort_cells(PU** start, unsigned num);
    bool GenerateScanLine(ScanLine& sl);
    void line(int x1, int y1, int x2, int y2);
    inline unsigned GetPUNumY(unsigned y) const  //取得y行的像素个数
    {
        return m_sorted_y[y - m_min_y].num;
    }
    const PU* const* GetPUPtrInY(unsigned y) const
    {
        return m_sorted_cells + m_sorted_y[y - m_min_y].start;
    }

    inline unsigned calculate_alpha(int area) const
    {
		int cover = area >> (8*2 + 1 - 8);

        if(cover < 0) cover = -cover;

        if(cover > 255) cover = 255;

        return cover;
    }

    inline  void set_curr_cell(int x, int y)
    {
        if(m_curr_cell.not_equal(x, y))
        {
            add_curr_cell();
            m_curr_cell.x     = x;
            m_curr_cell.y     = y;
            m_curr_cell.cover = 0;
            m_curr_cell.area  = 0;
        }
    }
    void render_hline(int ey, int x1, int y1, int x2, int y2);
    unsigned                m_num_blocks;
    unsigned                m_max_blocks;
    unsigned                m_curr_block;
    unsigned                m_num_cells;
    PU**                    m_cells;
    PU*                     m_curr_cell_ptr;
    PU**                    m_sorted_cells;
    sorted_y*               m_sorted_y;
    PU                      m_curr_cell;

    int                     m_min_x;
    int                     m_min_y;
    int                     m_max_x;
    int                     m_max_y;

    bool                    m_sorted;
    int                     m_iNumOfSortY, m_iNumOfSortPU;
    int                     m_iScanY;
};

class ScanLine
{
public:

    struct span //描述唯一alpha值的部分连续像素 (某行)
    {
        short        x;
        short        len;
        const HBYTE* covers;
    };

	ScanLine(): m_last_x(0x7FFFFFF0),m_cover_ptr(0),m_cur_span(0),m_iNumSpan(2000)
    {
		m_spans = NULL;
		m_pcovers = NULL;
        m_spans  = new span[m_iNumSpan];
        m_pcovers = new HBYTE[m_iNumSpan];
    }

    ~ScanLine()
    {
        Release();
    };

    inline void Release()
    {
        if(m_spans)
        {
            delete [] m_spans;
            m_spans = NULL;
        }

        if(m_pcovers)
        {
            delete [] m_pcovers ;
            m_pcovers = NULL;
        }

        ;
    }
    inline void Reset(int length)
    {
        int SizeOfSpan = length + 3; // 头尾是空出来的

        if(SizeOfSpan >  m_iNumSpan)
        {
            Release();
            m_pcovers = new HBYTE[SizeOfSpan];
            m_spans  = new span[SizeOfSpan];
            memset(m_pcovers, 0, SizeOfSpan);
            memset(m_spans, 0, SizeOfSpan * sizeof(span));
            m_iNumSpan = SizeOfSpan;
        }

        ResetSpan();
    }

    inline void ResetSpan()
    {
        m_last_x    = 0x7FFFFFF0;
        m_cover_ptr = m_pcovers;
        m_cur_span  = m_spans;
        m_cur_span->len = 0;
    }
    /*
    void add_cell(int x, kn_uint cover);
    void add_cells(int x, kn_ushort len, const kn_byte* covers);
    void add_span(int x, kn_ushort len, kn_uint  cover);
    */
    //////////////////////////////////////////////////////////////////////////
    inline void add_cell(int x, HUINT cover)
    {
        *m_cover_ptr = (HBYTE)cover;

        if(x == m_last_x + 1 && m_cur_span->len > 0)
        {
            m_cur_span->len++;
        }
        else
        {
            m_cur_span++;
            m_cur_span->covers = m_cover_ptr;
			m_cur_span->x = x;
            m_cur_span->len = 1;
        }

        m_last_x = x;
        m_cover_ptr++;
    }

    inline void add_cells(int x, HUSHORT len, const HBYTE* covers)
    {
        memcpy(m_cover_ptr, covers, len);

        if(x == m_last_x + 1 && m_cur_span->len > 0)
        {
			m_cur_span->len += len;
        }
        else
        {
            m_cur_span++;
            m_cur_span->covers = m_cover_ptr;
			m_cur_span->x = x;
            m_cur_span->len = len;
        }

        m_cover_ptr += len;
        m_last_x = x + len - 1;
    }

    inline void add_span(int x, HUSHORT len, HUINT cover)
    {
        if(x == m_last_x + 1 &&
           m_cur_span->len < 0 &&
           cover == *m_cur_span->covers)
        {
			m_cur_span->len -= len;
        }
        else
        {
            *m_cover_ptr = (HBYTE)cover;
            m_cur_span++;
            m_cur_span->covers = m_cover_ptr++;
            m_cur_span->x      = (short)x;
            m_cur_span->len    = -len;
        }

        m_last_x = x + len - 1;
    }
    //////////////////////////////////////////////////////////////////////////

    HUSHORT    num_spans() const
    {
		return unsigned(m_cur_span - m_spans); 
    }

    span* begin()     const
    {
        return &m_spans[1];
    }



    int             m_last_x;
    int             m_y;
    HBYTE*            m_pcovers;
    span*           m_spans;
    HINT          m_iNumSpan;
    span*           m_cur_span;
    HBYTE*           m_cover_ptr;

};

typedef struct REPOINT_D
{
    double x, y;
    REPOINT_D()
    {
        x = 0;
        y = 0;
    }
    REPOINT_D(double _x, double _y): x(_x), y(_y)
    {}
} REPOINT_D;
const double intersection_epsilon = 1.0e-2;

class CHQLine
{

public:
    CHQLine();
    virtual ~CHQLine();
    int width, height;
    int pixelFt;
    HBYTE* m_pData;
    int m_ystride;
    RasterizePU m_raster;
    ScanLine m_sl;
    double m_lineWidth;
    double m_lineWidth_eps;
    RECOLOR ren_color ;

    HINT Attach(HBYTE* , int, int, int, int);
    void Render();
    void BlendSolidHspan565(int x, int y, int len,
                            const RECOLOR& c,
                            const HBYTE* covers);
    void BlendHline565(int x1, int y, int x2,
                       const RECOLOR& c, HBYTE cover);

    void BlendSolidHspan888(int x, int y, int len,
                            const RECOLOR& c,
                            const HBYTE* covers);
    void BlendHline888(int x1, int y, int x2,
                       const RECOLOR& c, HBYTE cover);

    ERRINFO PolyLine(REPOINT* lppt, HLONG lCount, RECOLOR clrFore, HINT iWidth, RECOLOR clrBack, KBIRDVIEWPARA* param = NULL);
    void PolygonInvertY(REPOINT_D* lppt, HLONG lCount, RECOLOR clrFore);
    void PolygonNotInvertY(vector<REPOINT_D>& lppt, HLONG lCount, RECOLOR clrFore);
    void GenerateEnd(vector<REPOINT>& vc, const REPOINT& v0, const REPOINT& v1, double len);
    void GenerateJoint(vector<REPOINT> & vc, const REPOINT& v0, const REPOINT& v1, const REPOINT& v2, double len1, double len2);
	void GenerateEnd(const REPOINT& v0, const REPOINT& v1, double len,HWORD Type = HQ_END_ROUND);
	void GenerateJoint(const REPOINT& v0, const REPOINT& v1,const REPOINT& v2, double len1,double len2 ,HWORD type = 0);
    void calc_miter(vector<REPOINT_D>& vc, const REPOINT& v0, const REPOINT& v1, const REPOINT& v2,
                    double dx1, double dy1, double dx2, double dy2, double mlimit, double dbevel);
    void GenerateEdgePts(REPOINT* pts, vector<REPOINT> & lppt, HINT count, HINT iWidth);
	void PolygonHQ(REPOINT* lppt, HLONG size,RECOLOR* clr, HBYTE alpha);
	REPOINT m_stockPoints[1000];
	HINT  iNumOfStock;
	HINT iCurPoint;
	HINT iNumResult;

    inline int cross_product(int x1, int y1,
                             int x2, int y2,
                             int x,  int y)
    {
        return (x - x2) * (y2 - y1) - (y - y2) * (x2 - x1);
    }

    inline bool calc_intersection(double ax, double ay, double bx, double by,
                                  double cx, double cy, double dx, double dy,
                                  double* x, double* y)
    {
#if 0
        double acy = ay - cy;
        double dcx = dx - cx;
        double acx = ax - cx;
        double dcy = dy - cy;
        double bax = bx - ax;
        double bay = by - ay;
        double num = acy * dcx - acx * dcy;
        double den = bax * dcy - bay * dcx;

        if(fabs(den) < intersection_epsilon) return false;

        double r = num / den;
        *x = ax + r * (bx - ax);
        *y = ay + r * (by - ay);
#else
        int iax = (int)(ax * 256);
        int iay = (int)(ay * 256);
        int ibx = (int)(bx * 256);
        int iby = (int)(by * 256);
        int icx = (int)(cx * 256);
        int icy = (int)(cy * 256);
        int idx = (int)(dx * 256);
        int idy = (int)(dy * 256);
        int acy = iay - icy;
        int dcx = idx - icx;
        int acx = iax - icx;
        int dcy = idy - icy;
        int bax = ibx - iax;
        int bay = iby - iay;
        LONG64 num = (LONG64)acy * dcx - (LONG64)acx * dcy;
        LONG64 den = (LONG64)bax * dcy - (LONG64)bay * dcx;
        LONG64 Num = den > 0 ? den : -den;

        if(Num < 728) return false;

        int ix = (int)(iax + num * (ibx - iax) / den);
        int iy = (int)(iay + num * (iby - iay) / den);
        *x = ix / 256.0;
        *y = iy / 256.0;
#endif
        return true;
    }

    int calc_angle(double x,   double y)
    {
        if(x == 0)
            return 0;

        double k = y / x;
        double fk = fabs(k);
        int angle = 0;

        if(fk <= 1.0)
        {
            angle = LINE_TAN_TABLE[(int)(fk*64)];
        }
        else
        {
            angle = 135 - LINE_TAN_TABLE[(int)(64/fk)];
        }

        if(x < 0 && y > 0)
        {
            angle = 180 - angle;
        }
        else if(x < 0 && y < 0)
        {
            angle = 180 + angle;
        }
        else if(x > 0 && y < 0)
        {
            angle = 360 - angle;
        }
        else
        {
        }

        return angle;
    }

    void calc_arc(vector<REPOINT>& vc,
                  double x,   double y,
                  double dx1, double dy1,
                  double dx2, double dy2)
    {
        int da = 0;
        int i, n;
        vc.push_back(REPOINT((int)((x + dx1) * 256 + 0.5), (int)((y + dy1) * 256 + 0.5)));
        int ia1 = calc_angle(dx1, dy1);
        int ia2 = calc_angle(dx2, dy2);
        //double a1 = atan2(dy1 , dx1 );
        //double a2 = atan2(dy2 , dx2 );
        //int ia1 = (int)(180 * a1 / PI);
        //int ia2 = (int)(180 * a2 / PI);

        if(ia1 > ia2)
        {
            ia2 += 360;
        }

        //n = int((a2 - a1) / da);
        n = 4;
        da = (ia2 - ia1) / (n + 1);
        ia1 += da;

        for(i = 0; i < n; i++)
        {
            ia1 = ia1 > 360 ? (ia1 - 360) : ia1;
            ia1 = ia1 < 0 ? (ia1 + 360) : ia1;
            vc.push_back(REPOINT((int)(x * 256 + (LINE_COS_TABLE[ia1] * m_lineWidth) / 2), (int)(y * 256 + (LINE_SIN_TABLE[ia1] * m_lineWidth) / 2)));
            ia1 += da;
        }

        vc.push_back(REPOINT((int)((x + dx2) * 256 + 0.5), (int)((y + dy2) * 256 + 0.5)));
	}

	void calc_arc(
		double x,   double y, 
		double dx1, double dy1, 
		double dx2, double dy2)
	{
		int da = 0;
		int i, n;

		int ia1 = calc_angle(dx1, dy1);
		int ia2 = calc_angle(dx2, dy2);

		//double a1 = atan2(dy1 , dx1 );
		//double a2 = atan2(dy2 , dx2 );
		//int ia1 = (int)(180 * a1 / PI);
		//int ia2 = (int)(180 * a2 / PI);

		if(ia1 > ia2)
		{
			ia2 += 360;
		}
		//n = int((a2 - a1) / da);
		n = 4;
		da = (ia2 - ia1) / (n + 1);
		ia1 += da;

		m_stockPoints[iNumOfStock++] = REPOINT((int)((x + dx1)*256+0.5), (int)((y + dy1)*256+0.5));
		//vc.push_back(REPOINT((int)((x + dx1)*256+0.5), (int)((y + dy1)*256+0.5)));
		for(i = 0; i < n; i++)
		{
			ia1 = ia1 > 360 ? (ia1-360) : ia1;
			ia1 = ia1 < 0 ? (ia1+360) : ia1;

			//vc.push_back(REPOINT((int)(x*256 + (LINE_COS_TABLE[ia1] * m_lineWidth)/2), (int)(y*256 + (LINE_SIN_TABLE[ia1] * m_lineWidth)/2)));
			m_stockPoints[iNumOfStock++] = REPOINT((int)(x*256 + (LINE_COS_TABLE[ia1] * m_lineWidth)/2), (int)(y*256 + (LINE_SIN_TABLE[ia1] * m_lineWidth)/2));
			ia1 += da;
		}
		//vc.push_back(REPOINT((int)((x + dx2)*256+0.5), (int)((y + dy2)*256+0.5)));
		m_stockPoints[iNumOfStock++] = REPOINT((int)((x + dx2)*256+0.5), (int)((y + dy2)*256+0.5));
	}
};

template <class T> static inline void swap_cells(T* a, T* b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
}
#endif // !defined(AFX_HQLINE_H__0D9E2B92_1D82_484E_A75C_79100805120B__INCLUDED_)
