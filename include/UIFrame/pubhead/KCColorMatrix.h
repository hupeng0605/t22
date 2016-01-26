#pragma once
#include "Type.h"

enum BlindType
{
    Normal = 0,
    Protanopia, //红色盲
    Protanomaly,//红色弱
    Deuteranopia,//绿色盲
    Deuteranomaly,//绿色弱
    Tritanopia,//蓝色盲
    Tritanomaly,//蓝色弱
    Achromatopsia,//色盲
    Achromatomaly//色弱
};

class UICORE_DLL_API HCColorMatrix
{
public:
    HCColorMatrix();
    HCColorMatrix(HCColorMatrix& matrix);

    ~HCColorMatrix();

    void Reset();

    //Brightness 亮度:范围 -100~100
    //Contrast   对比度：-100~100
    //Saturation 饱和度：-100~100
    //Hue        色调：-180~180
    void ColorAdjust(HFLOAT Brightness, HFLOAT Contrast, HFLOAT Saturation, HFLOAT Hue);

    //灰度
    void SetGray();


    void SetBlind(BlindType type);

    //透明度
    void SetAlpha(HFLOAT alpha);

    //变成黑白图片
    void SetDesaturate();

    //颜色反转
    void SetInvert();

    //负片效果,取值范围0~255，设为128左右效果明显
    void SetThreshold(HFLOAT num);

    //矩阵相乘
    void Multiply(HCColorMatrix& matrix);

    HFLOAT* GetColorMatrix();
private:
    //颜色矩阵排列方式
    //   R G B A Off
    // R 1 0 0 0 0
    // G 0 1 0 0 0
    // B 0 0 1 0 0
    // A 0 0 0 1 0
    //   0 0 0 0 1  虚拟位,矩阵相乘时便于计算
    HFLOAT ColorMatrix[5][5];
};