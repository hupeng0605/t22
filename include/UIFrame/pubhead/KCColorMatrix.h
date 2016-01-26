#pragma once
#include "Type.h"

enum BlindType
{
    Normal = 0,
    Protanopia, //��ɫä
    Protanomaly,//��ɫ��
    Deuteranopia,//��ɫä
    Deuteranomaly,//��ɫ��
    Tritanopia,//��ɫä
    Tritanomaly,//��ɫ��
    Achromatopsia,//ɫä
    Achromatomaly//ɫ��
};

class UICORE_DLL_API HCColorMatrix
{
public:
    HCColorMatrix();
    HCColorMatrix(HCColorMatrix& matrix);

    ~HCColorMatrix();

    void Reset();

    //Brightness ����:��Χ -100~100
    //Contrast   �Աȶȣ�-100~100
    //Saturation ���Ͷȣ�-100~100
    //Hue        ɫ����-180~180
    void ColorAdjust(HFLOAT Brightness, HFLOAT Contrast, HFLOAT Saturation, HFLOAT Hue);

    //�Ҷ�
    void SetGray();


    void SetBlind(BlindType type);

    //͸����
    void SetAlpha(HFLOAT alpha);

    //��ɺڰ�ͼƬ
    void SetDesaturate();

    //��ɫ��ת
    void SetInvert();

    //��ƬЧ��,ȡֵ��Χ0~255����Ϊ128����Ч������
    void SetThreshold(HFLOAT num);

    //�������
    void Multiply(HCColorMatrix& matrix);

    HFLOAT* GetColorMatrix();
private:
    //��ɫ�������з�ʽ
    //   R G B A Off
    // R 1 0 0 0 0
    // G 0 1 0 0 0
    // B 0 0 1 0 0
    // A 0 0 0 1 0
    //   0 0 0 0 1  ����λ,�������ʱ���ڼ���
    HFLOAT ColorMatrix[5][5];
};