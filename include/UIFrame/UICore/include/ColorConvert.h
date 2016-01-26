


#pragma  once

#include "Type.h"
#include "RenderingEngine.h"

// #define RE_COLOR888				1	// RGB24.
// #define RE_COLOR555				2	// mainly used in embedded device.
// #define RE_COLOR32				3	// RGBA. AΪAlphaͨ��ֵ
// #define RE_COLOR565				4	// same as COLOR555.
#define RE_256_to_256 (RE_COLOR256 << 4 | RE_COLOR256)
#define RE_256_to_565 (RE_COLOR256 << 4 | RE_COLOR565)
#define RE_256_to_888 (RE_COLOR256 << 4 | RE_COLOR888)
#define RE_256_to_32  (RE_COLOR256 << 4 | RE_COLOR32)

#define RE_565_to_565 (RE_COLOR565 << 4 | RE_COLOR565)
#define RE_565_to_888 (RE_COLOR565 << 4 | RE_COLOR888)
#define RE_565_to_32  (RE_COLOR565 << 4 | RE_COLOR32)

#define RE_888_to_565 (RE_COLOR888 << 4 | RE_COLOR565)
#define RE_888_to_888 (RE_COLOR888 << 4 | RE_COLOR888)
#define RE_888_to_32  (RE_COLOR888 << 4 | RE_COLOR32)

#define RE_32_to_565  (RE_COLOR32  << 4 | RE_COLOR565)
#define RE_32_to_888  (RE_COLOR32  << 4 | RE_COLOR888)
#define RE_32_to_32   (RE_COLOR32  << 4 | RE_COLOR32)

#define RE_PALETTE_to_565	(RE_COLORPALETTE  << 4 | RE_COLOR565)
#define RE_PALETTE_to_888	(RE_COLORPALETTE  << 4 | RE_COLOR888)
#define RE_PALETTE_to_32	(RE_COLORPALETTE  << 4 | RE_COLOR32)

class ColorConvert
{
public:
	ColorConvert();
	~ColorConvert();

	//***************************************************************
	// *  ��������: ����ת����Դ��Ŀ��Surface
	// *  ��ڲ���: Ŀ��, Դ
	// *  ���ڲ���: 
	// *  �� �� ֵ: ��
	//***************************************************************
	void Set(IN IReSurface* pTarSurface, IN IReSurface* pSrcSurface);

	//***************************************************************
	// *  ��������: ������͸����ֵ
	// *  ��ڲ���: ͸����ֵ��ȡֵ��Χ1~256
	// *  ���ڲ���: 
	// *  �� �� ֵ: ��
	//***************************************************************
	void SetLineTransparent(HINT transparent);

	//***************************************************************
	// *  ��������: ��ô���RGB�ĻҶ�ֵ
	// *  ��ڲ���: r,g,b
	// *  ���ڲ���: 
	// *  �� �� ֵ: �Ҷ�ֵ
	//***************************************************************
	inline HBYTE GetGrayValue( IN HBYTE r, IN HBYTE g, IN HBYTE b );

	//***************************************************************
	// *  ��������: �����������ת������Ӧ��Ŀ���ַ��
	// *  ��ڲ���: 
	// *  ���ڲ���: 
	// *  �� �� ֵ: true:ת���ɹ�
	//***************************************************************
	HBOOL Convert(IN HBYTE* pTarData, IN HBYTE* pSrcData, IN HINT num);//һ��ת��һ�е�

	void SetPaletteArray(HDWORD* pPaletteArray, HINT count = 0);

private:
	HINT m_TarType;		// Ŀ����ɫ��ʽ
	HINT m_SrcType;		// Դ��ɫ��ʽ
	HBOOL m_bSrcGray;		// Դ��ʽ�Ƿ�Ϊ�Ҷ�
	HBOOL m_bColorKey;	// �Ƿ�Ϊ��ֵ����
	RECOLOR m_ColorKey;		// ��ֵ
	HINT m_Transparent;	// ͸����
	HINT m_LineTransparent; // ��͸����0~255
	HDWORD* m_pPaletteArray;

};

