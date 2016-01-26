#pragma once
#include "HQLine.h"

enum image_filter_scale_e
{
    image_filter_shift = 14,                      //----image_filter_shift
    image_filter_scale = 1 << image_filter_shift, //----image_filter_scale
    image_filter_mask  = image_filter_scale - 1   //----image_filter_mask
};

enum image_subpixel_scale_e
{
    image_subpixel_shift = 8,                         //----image_subpixel_shift
    image_subpixel_scale = 1 << image_subpixel_shift, //----image_subpixel_scale
    image_subpixel_mask  = image_subpixel_scale - 1   //----image_subpixel_mask
};

static int iround(double v)
{
    return int((v < 0.0) ? v - 0.5 : v + 0.5);
}

//=================================================dda2_line_interpolator
class dda2_line_interpolator
{
public:
    typedef int save_data_type;
    enum save_size_e { save_size = 2 };

    //--------------------------------------------------------------------
    dda2_line_interpolator() {}

    //-------------------------------------------- Forward-adjusted line
    dda2_line_interpolator(int y1, int y2, int count) :
            m_cnt(count <= 0 ? 1 : count),
            m_lft((y2 - y1) / m_cnt),
            m_rem((y2 - y1) % m_cnt),
            m_mod(m_rem),
            m_y(y1)
    {
        if (m_mod <= 0)
        {
            m_mod += count;
            m_rem += count;
            m_lft--;
        }

        m_mod -= count;
    }

    //-------------------------------------------- Backward-adjusted line
    dda2_line_interpolator(int y1, int y2, int count, int) :
            m_cnt(count <= 0 ? 1 : count),
            m_lft((y2 - y1) / m_cnt),
            m_rem((y2 - y1) % m_cnt),
            m_mod(m_rem),
            m_y(y1)
    {
        if (m_mod <= 0)
        {
            m_mod += count;
            m_rem += count;
            m_lft--;
        }
    }

    //-------------------------------------------- Backward-adjusted line
    dda2_line_interpolator(int y, int count) :
            m_cnt(count <= 0 ? 1 : count),
            m_lft(y / m_cnt),
            m_rem(y % m_cnt),
            m_mod(m_rem),
            m_y(0)
    {
        if (m_mod <= 0)
        {
            m_mod += count;
            m_rem += count;
            m_lft--;
        }
    }


    //--------------------------------------------------------------------
    void save(save_data_type* data) const
    {
        data[0] = m_mod;
        data[1] = m_y;
    }

    //--------------------------------------------------------------------
    void load(const save_data_type* data)
    {
        m_mod = data[0];
        m_y   = data[1];
    }

    //--------------------------------------------------------------------
    void operator++()
    {
        m_mod += m_rem;
        m_y += m_lft;

        if (m_mod > 0)
        {
            m_mod -= m_cnt;
            m_y++;
        }
    }

    //--------------------------------------------------------------------
    void operator--()
    {
        if (m_mod <= m_rem)
        {
            m_mod += m_cnt;
            m_y--;
        }

        m_mod -= m_rem;
        m_y -= m_lft;
    }

    //--------------------------------------------------------------------
    void adjust_forward()
    {
        m_mod -= m_cnt;
    }

    //--------------------------------------------------------------------
    void adjust_backward()
    {
        m_mod += m_cnt;
    }

    //--------------------------------------------------------------------
    int mod() const
    {
        return m_mod;
    }
    int rem() const
    {
        return m_rem;
    }
    int lft() const
    {
        return m_lft;
    }

    //--------------------------------------------------------------------
    int y() const
    {
        return m_y;
    }

private:
    int m_cnt;
    int m_lft;
    int m_rem;
    int m_mod;
    int m_y;
};


struct trans_perspective
{
    double sx, shy, w0, shx, sy, w1, tx, ty, w2;

    bool quad_to_rect(const double* q,
                      double x1, double y1,
                      double x2, double y2)
    {
        double r[8];
        r[0] = r[6] = x1;
        r[2] = r[4] = x2;
        r[1] = r[3] = y1;
        r[5] = r[7] = y2;

        return quad_to_quad(q, r);
    }

    inline bool is_valid()
    {
        double epsilon = 1e-14;
        return fabs(sx) > epsilon && fabs(sy) > epsilon && fabs(w2) > epsilon;
    }

    inline bool square_to_quad(const double* q)
    {
        double dx = q[0] - q[2] + q[4] - q[6];
        double dy = q[1] - q[3] + q[5] - q[7];

        if (dx == 0.0 && dy == 0.0)
        {
            // Affine case (parallelogram)
            //---------------
            sx  = q[2] - q[0];
            shy = q[3] - q[1];
            w0  = 0.0;
            shx = q[4] - q[2];
            sy  = q[5] - q[3];
            w1  = 0.0;
            tx  = q[0];
            ty  = q[1];
            w2  = 1.0;
        }
        else
        {
            double dx1 = q[2] - q[4];
            double dy1 = q[3] - q[5];
            double dx2 = q[6] - q[4];
            double dy2 = q[7] - q[5];
            double den = dx1 * dy2 - dx2 * dy1;

            if (den == 0.0)
            {
                // Singular case
                //---------------
                sx = shy = w0 = shx = sy = w1 = tx = ty = w2 = 0.0;
                return false;
            }

            // General case
            //---------------
            double u = (dx * dy2 - dy * dx2) / den;
            double v = (dy * dx1 - dx * dy1) / den;
            sx  = q[2] - q[0] + u * q[2];
            shy = q[3] - q[1] + u * q[3];
            w0  = u;
            shx = q[6] - q[0] + v * q[6];
            sy  = q[7] - q[1] + v * q[7];
            w1  = v;
            tx  = q[0];
            ty  = q[1];
            w2  = 1.0;
        }

        return true;
    }

    //------------------------------------------------------------------------
    inline bool invert()
    {
        double d0 = sy  * w2 - w1  * ty;
        double d1 = w0  * ty - shy * w2;
        double d2 = shy * w1 - w0  * sy;
        double d  = sx  * d0 + shx * d1 + tx * d2;

        if (d == 0.0)
        {
            sx = shy = w0 = shx = sy = w1 = tx = ty = w2 = 0.0;
            return false;
        }

        d = 1.0 / d;
        trans_perspective a = *this;
        sx  = d * d0;
        shy = d * d1;
        w0  = d * d2;
        shx = d * (a.w1 * a.tx  - a.shx * a.w2);
        sy  = d * (a.sx * a.w2  - a.w0 * a.tx);
        w1  = d * (a.w0 * a.shx - a.sx * a.w1);
        tx  = d * (a.shx * a.ty  - a.sy * a.tx);
        ty  = d * (a.shy * a.tx  - a.sx * a.ty);
        w2  = d * (a.sx * a.sy  - a.shy * a.shx);
        return true;
    }

    inline bool trans_perspective::quad_to_square(const double* q)
    {
        if (!square_to_quad(q)) return false;

        invert();
        return true;
    }

    trans_perspective& multiply(const trans_perspective& a)
    {
        trans_perspective b = *this;
        sx  = a.sx * b.sx  + a.shx * b.shy + a.tx * b.w0;
        shx = a.sx * b.shx + a.shx * b.sy  + a.tx * b.w1;
        tx  = a.sx * b.tx  + a.shx * b.ty  + a.tx * b.w2;
        shy = a.shy * b.sx  + a.sy * b.shy + a.ty * b.w0;
        sy  = a.shy * b.shx + a.sy * b.sy  + a.ty * b.w1;
        ty  = a.shy * b.tx  + a.sy * b.ty  + a.ty * b.w2;
        w0  = a.w0 * b.sx  + a.w1 * b.shy + a.w2 * b.w0;
        w1  = a.w0 * b.shx + a.w1 * b.sy  + a.w2 * b.w1;
        w2  = a.w0 * b.tx  + a.w1 * b.ty  + a.w2 * b.w2;
        return *this;
    }

    inline bool quad_to_quad(const double* qs,
                             const double* qd)
    {
        trans_perspective p;

        if (!  quad_to_square(qs)) return false;

        if (!p.square_to_quad(qd)) return false;

        multiply(p);
        return true;
    }

    inline void transform(double* px, double* py) const
    {
        double x = *px;
        double y = *py;
        double m = 1.0 / (x * w0 + y * w1 + w2);
        *px = m * (x * sx  + y * shx + tx);
        *py = m * (x * shy + y * sy  + ty);
    }
};

class span_interpolator_linear_subdiv
{
public:

    enum subpixel_scale_e
    {
        subpixel_shift = 8,
        subpixel_scale = 1 << subpixel_shift
    };


    //----------------------------------------------------------------
    span_interpolator_linear_subdiv() :
            m_subdiv_shift(4),
            m_subdiv_size(1 << m_subdiv_shift),
            m_subdiv_mask(m_subdiv_size - 1) {}

    span_interpolator_linear_subdiv(const trans_perspective& trans,
                                    unsigned subdiv_shift = 4) :
            m_subdiv_shift(subdiv_shift),
            m_subdiv_size(1 << m_subdiv_shift),
            m_subdiv_mask(m_subdiv_size - 1),
            m_pTrans(&trans) {}

    span_interpolator_linear_subdiv(const trans_perspective& trans,
                                    double x, double y, unsigned len,
                                    unsigned subdiv_shift = 4) :
            m_subdiv_shift(subdiv_shift),
            m_subdiv_size(1 << m_subdiv_shift),
            m_subdiv_mask(m_subdiv_size - 1),
            m_pTrans(&trans)
    {
        begin(x, y, len);
    }

    //----------------------------------------------------------------

    //----------------------------------------------------------------
    unsigned subdiv_shift() const
    {
        return m_subdiv_shift;
    }
    void subdiv_shift(unsigned shift)
    {
        m_subdiv_shift = shift;
        m_subdiv_size = 1 << m_subdiv_shift;
        m_subdiv_mask = m_subdiv_size - 1;
    }

    void SetTransPerspective(const trans_perspective& trans)
    {
        m_pTrans = &trans;
    }

    //----------------------------------------------------------------
    void begin(double x, double y, unsigned len)
    {
        double tx;
        double ty;
        m_pos   = 1;
        m_src_x = iround(x * subpixel_scale) + subpixel_scale;
        m_src_y = y;
        m_len   = len;

        if (len > m_subdiv_size) len = m_subdiv_size;

        tx = x;
        ty = y;
        m_pTrans->transform(&tx, &ty);
        int x1 = iround(tx * subpixel_scale);
        int y1 = iround(ty * subpixel_scale);

        tx = x + len;
        ty = y;
        m_pTrans->transform(&tx, &ty);

        m_li_x = dda2_line_interpolator(x1, iround(tx * subpixel_scale), len);
        m_li_y = dda2_line_interpolator(y1, iround(ty * subpixel_scale), len);
    }

    //----------------------------------------------------------------
    void operator++()
    {
        ++m_li_x;
        ++m_li_y;

        if (m_pos >= m_subdiv_size)
        {
            unsigned len = m_len;

            if (len > m_subdiv_size) len = m_subdiv_size;

            double tx = double(m_src_x) / double(subpixel_scale) + len;
            double ty = m_src_y;
            m_pTrans->transform(&tx, &ty);
            m_li_x = dda2_line_interpolator(m_li_x.y(), iround(tx * subpixel_scale), len);
            m_li_y = dda2_line_interpolator(m_li_y.y(), iround(ty * subpixel_scale), len);
            m_pos = 0;
        }

        m_src_x += subpixel_scale;
        ++m_pos;
        --m_len;
    }

    //----------------------------------------------------------------
    void coordinates(int* x, int* y) const
    {
        *x = m_li_x.y();
        *y = m_li_y.y();
    }

private:
    unsigned m_subdiv_shift;
    unsigned m_subdiv_size;
    unsigned m_subdiv_mask;
    const trans_perspective* m_pTrans;
    dda2_line_interpolator m_li_x;
    dda2_line_interpolator m_li_y;
    int      m_src_x;
    double   m_src_y;
    unsigned m_pos;
    unsigned m_len;
};


class CHQStretch
{
public:
    CHQStretch(void);
    ~CHQStretch(void);

public:
    ERRINFO StretchBitblt(IReSurface* pInSrc, // 源DC
                          IReSurface* pInDst, // 目标DC
                          POINT newLeftTop,  // 源图像左上角在目标图中对应的位置 B
                          POINT newRightTop, //源图像右上角在目标图中对应的位置 C
                          POINT newLeftBottom,  //// 源图像左下角在目标图中对应的位置 A
                          POINT newRightBottom,  //源图像右下角在目标图中对应的位置  D
                          int alpha);

protected:
    void Generate(RECOLOR* span, int x, int y, unsigned len);
    void BlendColorHSpan(int x, int y, int len,
                         const RECOLOR* colors,
                         const HBYTE* covers,
                         int alpha);

protected:
    IReSurface* m_pInSrc;
    IReSurface* m_pInDst;
    RasterizePU m_raster;
    ScanLine m_sl;
    trans_perspective m_tr;
    span_interpolator_linear_subdiv m_interLiner;

    int m_SrcWidth;
    int m_SrcHeight;

    int m_DstWidth;
    int m_DstHeight;
};
