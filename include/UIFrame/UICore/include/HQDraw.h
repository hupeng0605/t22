// HQDraw.h: interface for the CHQDraw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HQDRAW_H__0D9E2B92_1D82_484E_A75C_79100805120B__INCLUDED_)
#define AFX_HQDRAW_H__0D9E2B92_1D82_484E_A75C_79100805120B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "RenderingEngine.h"
#include "HQLine.h"

// enum cell_block_scale_e
// {
// 	cell_block_shift = 12,
// 		cell_block_size  = 1 << cell_block_shift,
// 		cell_block_mask  = cell_block_size - 1,
// 		cell_block_pool  = 256,
// 		cell_block_limit = 1024
// };
// enum poly_subpixel_scale_e
// {
// 	poly_subpixel_shift = 8,                      //----poly_subpixel_shift
// 		poly_subpixel_scale = 1<<poly_subpixel_shift, //----poly_subpixel_scale 
// 		poly_subpixel_mask  = poly_subpixel_scale-1,  //----poly_subpixel_mask 
// };


// typedef struct PU // 单个像素单元 pixelUnit
// {
// 	int x;
// 	int y;
// 	int cover;
// 	int area;
// 	PU()
// 	{
// 		x = 0x7FFFFFFF;
// 		y = 0x7FFFFFFF;
// 		cover = 0;
// 		area  = 0;
// 	}
// 	int not_equal(int ex, int ey) const
// 	{
// 		return (ex - x) | (ey - y);
// 	}
// 	void initial()
// 	{
// 		x = 0x7FFFFFFF;
// 		y = 0x7FFFFFFF;
// 		cover = 0;
// 		area  = 0;
// 	}
// }PU ,*ptrPU;
// class ScanLine;
// class RasterizePU
// {
// public:
// 
// 	struct sorted_y
// 	{
// 		unsigned start;
// 		unsigned num;
// 		sorted_y(): start(0),num(0)
// 		{
// 		}
//     };
// 
// 	RasterizePU(): m_cells(NULL),m_sorted_cells(NULL),m_curr_cell(),m_sorted_y(0),m_sorted(false),m_num_cells(0),
// 		m_min_x(0x7FFFFFFF),m_min_y(0x7FFFFFFF),m_max_x(-0x7FFFFFFF),m_max_y(-0x7FFFFFFF),m_num_blocks(0),m_max_blocks(0),
// 		m_curr_block(0)
// 
// 
// 	{
//         m_curr_cell.x = 0x7FFFFFFF;
//         m_curr_cell.y = 0x7FFFFFFF;
// 		m_curr_cell.area = 0;
// 		m_curr_cell.cover = 0;
// 	}
// 	~RasterizePU();
// 	void Reset();
// 	void SortPUs();
// 	void AllocateBlock();
// 	void add_curr_cell();
// 	void qsort_cells(PU** start, unsigned num);
// 	bool GenerateScanLine(ScanLine& sl);
// 	void line(int x1, int y1, int x2, int y2);
// 	inline unsigned GetPUNumY(unsigned y) const  //取得y行的像素个数
// 	{ 
// 		return m_sorted_y[y - m_min_y].num; 
//     }
// 	const PU* const* GetPUPtrInY(unsigned y) const
// 	{ 
// 		return m_sorted_cells + m_sorted_y[y - m_min_y].start; 
// 	}
// 
// 	inline unsigned calculate_alpha(int area) const
// 	{
// 		int cover = area >> (8*2 + 1 - 8);
// 		if(cover < 0) cover = -cover;
// 		if(cover > 255) cover = 255;
// 		return cover;
// 	}
// 
// inline 	void set_curr_cell(int x, int y)
// 	{
// 		if(m_curr_cell.not_equal(x, y))
// 		{
// 			add_curr_cell();
// 			m_curr_cell.x     = x;
// 			m_curr_cell.y     = y;
// 			m_curr_cell.cover = 0;
// 			m_curr_cell.area  = 0;
// 		}
// 	}
// void render_hline(int ey, int x1, int y1,int x2, int y2);
//     unsigned                m_num_blocks;
// 	unsigned                m_max_blocks;
// 	unsigned                m_curr_block;
// 	unsigned                m_num_cells;
// 	PU**					m_cells;
// 	PU*						m_curr_cell_ptr;
// 	PU**					m_sorted_cells;
// 	sorted_y*				m_sorted_y;
// 	PU						m_curr_cell;
// 
// 	int                     m_min_x;
// 	int                     m_min_y;
// 	int                     m_max_x;
// 	int                     m_max_y;
// 
// 	bool                    m_sorted;
// 	int						m_iNumOfSortY,m_iNumOfSortPU;
// 	int						m_iScanY;
// };
// 
// class ScanLine
// {	public:
// 
// 	struct span //描述唯一alpha值的部分连续像素 (某行)
// 	{
// 		short        x;
// 		short        len; 
// 		const byte* covers;
// 	};
// 	ScanLine(): m_last_x(0x7FFFFFF0),m_cover_ptr(0),m_cur_span(0),m_iNumSpan(2000)
// 	{
// 		m_spans  = new span[m_iNumSpan];
// 		m_pcovers = new byte[m_iNumSpan];
// 	}
// 	~ScanLine()
// 	{
// 		Release();
// 	};
// 	inline void Release()
// 	{
// 		if(m_spans)
// 		{
// 			delete [] m_spans;
// 			m_spans = NULL;
// 		}
// 		if (m_pcovers)
// 		{
// 			delete [] m_pcovers ;
// 			m_pcovers = NULL;
// 		}
// 		;
// 	}
// 	inline void Reset(int length)
// 	{
// 		int SizeOfSpan = length + 3; // 头尾是空出来的
// 		if (SizeOfSpan >  m_iNumSpan)
// 		{
// 			Release();
// 			//LPVOID lpMsgBuf;
// 			//FormatMessage( 
// 			//	FORMAT_MESSAGE_ALLOCATE_BUFFER | 
// 			//	FORMAT_MESSAGE_FROM_SYSTEM | 
// 			//	FORMAT_MESSAGE_IGNORE_INSERTS,
// 			//	NULL,
// 			//	GetLastError(),
// 			//	0, // Default language
// 			//	(LPTSTR) &lpMsgBuf,
// 			//	0,
// 			//	NULL 
// 			//	);
// 			//// Process any inserts in lpMsgBuf.
// 			//// ...
// 			//// Display the string.
// 			//MessageBox( NULL, (LPCTSTR)lpMsgBuf, _T(""), MB_OK | MB_ICONINFORMATION );
// 			//// Free the buffer.
// 			//LocalFree( lpMsgBuf );
// 			m_pcovers = new byte[SizeOfSpan];
// 			m_spans  = new span[SizeOfSpan];
// 			memset(m_pcovers,0,SizeOfSpan);
// 			memset(m_spans,0,SizeOfSpan*sizeof(span));
// 			m_iNumSpan = SizeOfSpan;
// 		}
// 		ResetSpan();	
// 	}
// 	inline void ResetSpan()
// 	{
// 		m_last_x    = 0x7FFFFFF0;
// 		m_cover_ptr = m_pcovers;
// 		m_cur_span  = m_spans;
// 		m_cur_span->len = 0;
// 	}
// 	void add_cell(int x, kn_uint cover);
// 	void add_cells(int x, kn_ushort len, const byte* covers);
// 	void add_span(int x, kn_ushort len, kn_uint  cover);
// 	kn_ushort       num_spans() const { return unsigned(m_cur_span - m_spans); }
// 	span* begin()     const { return &m_spans[1]; }
// 
// 
//  
//  	int             m_last_x;
//  	int             m_y;
//  	byte*			m_pcovers;
//  	span*			m_spans;
// 	kn_int			m_iNumSpan;
//  	span*           m_cur_span;
// 	byte*           m_cover_ptr;
// 
// };
// typedef struct REPOINT_D
// {
// 	double x,y;
// 	REPOINT_D()
// 	{
// 		x = 0;
// 		y = 0;
// 	}
// 	REPOINT_D(double _x, double _y):x(_x),y(_y)
// 	{}
// }REPOINT_D;
// const double intersection_epsilon = 1.0e-30;

class CHQDraw  
{
public:
	CHQDraw();
	virtual ~CHQDraw();
	int width, height;
	int pixelFt;
	byte* m_pData;
	int m_ystride;
	RasterizePU m_raster;
	ScanLine m_sl;
	double m_lineWidth;
	double m_lineWidth_eps;
	HWORD ren_color ;

	HINT Attach(byte* ,int,int,int,int);
	void Render();
	void BlendSolidHspan565(int x, int y, int len, 
							const HWORD& c, 
                            const byte* covers);
	void BlendHline565(int x1, int y, int x2, 
					const HWORD& c, byte cover);
	void PolyLine(REPOINT* lppt, HLONG lCount, RECOLOR clrFore, HINT iWidth,RECOLOR clrBack,KBIRDVIEWPARA* param = NULL);
	void PolygonInvertY( REPOINT_D* lppt, HLONG lCount, RECOLOR clrFore );
	void PolygonNotInvertY( vector<REPOINT_D>& lppt, HLONG lCount, RECOLOR clrFore );
	void GenerateEnd(vector<REPOINT_D>& vc,const REPOINT& v0, const REPOINT& v1, double len);
	void GenerateJoint( vector<REPOINT_D> & vc,const REPOINT& v0, const REPOINT& v1,const REPOINT& v2, double len1,double len2 );
	void calc_miter(vector<REPOINT_D>& vc,const REPOINT& v0, const REPOINT& v1, const REPOINT& v2,
					double dx1, double dy1,double dx2, double dy2,double mlimit,double dbevel);
	void GenerateEdgePts(REPOINT* pts,vector<REPOINT_D> & lppt, HINT count,HINT iWidth);

	inline double cross_product(double x1, double y1, 
		double x2, double y2, 
		double x,  double y)
    {
        return (x - x2) * (y2 - y1) - (y - y2) * (x2 - x1);
    }
	
	inline bool calc_intersection(double ax, double ay, double bx, double by,
		double cx, double cy, double dx, double dy,
		double* x, double* y)
    {
        double num = (ay-cy) * (dx-cx) - (ax-cx) * (dy-cy);
        double den = (bx-ax) * (dy-cy) - (by-ay) * (dx-cx);
        if(fabs(den) < intersection_epsilon) return false;
        double r = num / den;
        *x = ax + r * (bx-ax);
        *y = ay + r * (by-ay);
        return true;
    }


    void calc_arc(vector<REPOINT_D>& vc,
		double x,   double y, 
		double dx1, double dy1, 
		double dx2, double dy2)
    {
        double a1 = atan2(dy1 , dx1 );
        double a2 = atan2(dy2 , dx2 );
        double da = a1 - a2;
        int i, n;
		const double pi = 3.1415926535897931;
        da = acos(m_lineWidth / (m_lineWidth + 2 )) * 2;
        vc.push_back(REPOINT_D(x + dx1, y + dy1));
            if(a1 > a2)
			{
				a2 += 2 * pi;
			}
            n = int((a2 - a1) / da);
            da = (a2 - a1) / (n + 1);
            a1 += da;
            for(i = 0; i < n; i++)
            {
                vc.push_back(REPOINT_D(x + cos(a1) * m_lineWidth, y + sin(a1) * m_lineWidth));
                a1 += da;
            }
        vc.push_back(REPOINT_D(x + dx2, y + dy2));
    }
};

// template <class T> static inline void swap_cells(T* a, T* b)
// {
// 	T temp = *a;
// 	*a = *b;
// 	*b = temp;
// }
#endif // !defined(AFX_HQDRAW_H__0D9E2B92_1D82_484E_A75C_79100805120B__INCLUDED_)
