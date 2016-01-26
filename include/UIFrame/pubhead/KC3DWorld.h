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

    // ������ת��
    void SetRotateSurface(ROTATE_SURFACE rs);

    //�����ӵ�����
    void SetViewPoint(COORDINATE_3D ViewPoint3D);

    //������ʾ�����С
    void SetViewRect(RECT rectView);

    // ������ת���ĵ�, �Ե������Ч
    void SetRotateCentre(COORDINATE_3D RotateCentre);

    //������ת�뾶, ���������Ч
    void SetRotateRadius(HFLOAT radius);

    //������ת�Ƕ�
	//2009.12.11 jhw ��������kn_int�޸�Ϊkn_float
    void SetRotateAngle(HFLOAT angle);

    // ����Դͼ��߶�, ���������Ч
    void SetSrcHeight(HINT height);

    // ����Դͼ����, ���������Ч
    void SetSrcWidht(HINT width);

    // ��ȡ�ӽ�
    HINT GetViewAngle();

    void operator=(COORDINATE_3D & s)
    {
        m_coordView.x = s.x;
        m_coordView.y = s.y;
        m_coordView.z = s.z;
    };

    // ����ά�ռ��ϵĵ�ͶӰ��XOYƽ����
    // type = 0: ֧����ת
    // type = 1����֧����ת
    POINT PointProjection(COORDINATE_3D pt3D, HINT type = 0);

    // �Դ�ֱ��XOZƽ���ϵľ��������ͶӰӳ�䣬���Ҿ����������������ʾ��������Ĺ̶�Ϊһ��
    // ���С�� SetSrcHeight() �� SetSrcWidth()����
    ERRINFO SurfaceProjection(
        POINT* newLeftTop, // Դͼ�����Ͻ���Ŀ��ͼ�ж�Ӧ��λ�� B
        POINT* newRightTop, //Դͼ�����Ͻ���Ŀ��ͼ�ж�Ӧ��λ�� C
        POINT* newLeftBottom,  // Դͼ�����½���Ŀ��ͼ�ж�Ӧ��λ�� A
        POINT* newRightBottom); //Դͼ�����½���Ŀ��ͼ�ж�Ӧ��λ��  D

private:
    ROTATE_SURFACE m_RotateSuface;
    // ��ʾ�����С
    RECT m_ViewRect;
    // �ӵ�
    COORDINATE_3D m_coordView;
    // ��ת���ĵ�, �Ե����������Ч�����������Ч
    COORDINATE_3D m_Centre;
    // ��ת�뾶�����������Ч
    HFLOAT m_Radius;
    // ��ת�Ƕ�
	//2009.12.11 jhw ��������kn_int�޸�Ϊkn_float
    HFLOAT m_Angle;
    // Դͼ��߶�, ���������Ч
    HINT m_SrcHeight;
    // Դͼ����, ���������Ч
    HINT m_SrcWidth;

};

#endif // _KC_3DWorld__