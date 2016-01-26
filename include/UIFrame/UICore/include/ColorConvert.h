


#pragma  once

#include "Type.h"
#include "RenderingEngine.h"

// #define RE_COLOR888				1	// RGB24.
// #define RE_COLOR555				2	// mainly used in embedded device.
// #define RE_COLOR32				3	// RGBA. A为Alpha通道值
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
	// *  功　　能: 设置转化的源和目标Surface
	// *  入口参数: 目标, 源
	// *  出口参数: 
	// *  返 回 值: 无
	//***************************************************************
	void Set(IN IReSurface* pTarSurface, IN IReSurface* pSrcSurface);

	//***************************************************************
	// *  功　　能: 设置行透明度值
	// *  入口参数: 透明度值，取值范围1~256
	// *  出口参数: 
	// *  返 回 值: 无
	//***************************************************************
	void SetLineTransparent(HINT transparent);

	//***************************************************************
	// *  功　　能: 获得传入RGB的灰度值
	// *  入口参数: r,g,b
	// *  出口参数: 
	// *  返 回 值: 灰度值
	//***************************************************************
	inline HBYTE GetGrayValue( IN HBYTE r, IN HBYTE g, IN HBYTE b );

	//***************************************************************
	// *  功　　能: 将传入的数据转化到相应的目标地址上
	// *  入口参数: 
	// *  出口参数: 
	// *  返 回 值: true:转化成功
	//***************************************************************
	HBOOL Convert(IN HBYTE* pTarData, IN HBYTE* pSrcData, IN HINT num);//一次转化一行的

	void SetPaletteArray(HDWORD* pPaletteArray, HINT count = 0);

private:
	HINT m_TarType;		// 目标颜色格式
	HINT m_SrcType;		// 源颜色格式
	HBOOL m_bSrcGray;		// 源格式是否为灰度
	HBOOL m_bColorKey;	// 是否为键值类型
	RECOLOR m_ColorKey;		// 键值
	HINT m_Transparent;	// 透明度
	HINT m_LineTransparent; // 行透明度0~255
	HDWORD* m_pPaletteArray;

};

