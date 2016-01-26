#ifndef _KC_3DWorld__
#define _KC_3DWorld__

#include "type.h"

#ifdef WIN32
#include <math.h>
#endif

#ifndef PI
#define PI 3.1415926535f
#endif

#ifndef ERRINFO
typedef HINT ERRINFO; // return value (error info).
#endif

#ifndef RE_OK
#define RE_OK                   1
#endif

#ifndef RE_ERROR
#define RE_ERROR                0
#endif

enum ROTATE_SURFACE
{
    XOY = 0,
    YOZ,
    ZOX
};

struct COORDINATE_3D
{
    HFLOAT x;
    HFLOAT y;
    HFLOAT z;
};

class UICORE_DLL_API HC3DWorld
{
public:

    HC3DWorld(void);
    virtual ~HC3DWorld(void);

    // 设置旋转面
    void SetRotateSurface(ROTATE_SURFACE rs);

    //设置视点坐标
    void SetViewPoint(COORDINATE_3D ViewPoint3D);

    //设置显示区域大小
    void SetViewRect(RECT rectView);

    // 设置旋转中心点, 对点操作有效
    void SetRotateCentre(COORDINATE_3D RotateCentre);

    //设置旋转半径, 对面操作有效
    void SetRotateRadius(HFLOAT radius);

    //设置旋转角度
	//2009.12.11 jhw 参数类型kn_int修改为kn_float
    void SetRotateAngle(HFLOAT angle);

    // 设置源图像高度, 对面操作有效
    void SetSrcHeight(HINT height);

    // 设置源图像宽度, 对面操作有效
    void SetSrcWidht(HINT width);

    // 读取视角
    HINT GetViewAngle();

    void operator=(COORDINATE_3D & s)
    {
        m_coordView.x = s.x;
        m_coordView.y = s.y;
        m_coordView.z = s.z;
    };

    // 将三维空间上的点投影到XOY平面上
    // type = 0: 支持旋转
    // type = 1：不支持旋转
    POINT PointProjection(COORDINATE_3D pt3D, HINT type = 0);

    // 对垂直于XOZ平面上的矩形面进行投影映射，并且矩形区域的中心与显示区域的中心固定为一致
    // 面大小由 SetSrcHeight() 与 SetSrcWidth()设置
    ERRINFO SurfaceProjection(
        POINT* newLeftTop, // 源图像左上角在目标图中对应的位置 B
        POINT* newRightTop, //源图像右上角在目标图中对应的位置 C
        POINT* newLeftBottom,  // 源图像左下角在目标图中对应的位置 A
        POINT* newRightBottom); //源图像右下角在目标图中对应的位置  D

private:
    ROTATE_SURFACE m_RotateSuface;
    // 显示区域大小
    RECT m_ViewRect;
    // 视点
    COORDINATE_3D m_coordView;
    // 旋转中心点, 对单个点操作有效，对面操作无效
    COORDINATE_3D m_Centre;
    // 旋转半径，对面操作有效
    HFLOAT m_Radius;
    // 旋转角度
	//2009.12.11 jhw 变量类型kn_int修改为kn_float
    HFLOAT m_Angle;
    // 源图像高度, 对面操作有效
    HINT m_SrcHeight;
    // 源图像宽度, 对面操作有效
    HINT m_SrcWidth;

};

#endif // _KC_3DWorld__