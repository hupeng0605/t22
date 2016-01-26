#pragma once

#include "Type.h"
#include "KNFile.h"
#include "ft2build.h"
#include FT_FREETYPE_H

enum FontType
{
    BITMAP_FONT,
    TTF_FONT,
};

#ifdef KCFONTSIZE// Add by SongXiongzhen 2009-12-13
#undef KCFONTSIZE
#endif // FONTSIZE

#define KCFONTSIZE 16 //字库点阵字支持的最大Size
#define FONTNUMBER 3 //字体数量
typedef struct _KNTEXTCACHE
{
    HBYTE qu;
    HBYTE wei;
    HBYTE* textmem;

} KNTEXTCACHE;


class UICORE_DLL_API HCFont
{
public:
    HCFont() {}
    ~HCFont() {}
    virtual HINT Open(const HCHAR* pFileName, HUINT w = 0, HUINT h = 0) = 0;
	virtual HINT Open(unsigned char* pMemory, HLONG lSize, HUINT w = 0, HUINT h = 0) = 0;
    virtual void GetFontSize(HINT& width, HINT& height) = 0;
    virtual void SetFontSize(HINT& width, HINT& height) = 0;
	//获得字体宽度
    virtual HINT GetWidth(void) = 0;
	//获得字体高度
    virtual HINT GetHeight(void) = 0;
	//得到所给字符串长度
    virtual HINT GetStringWidth(HBYTE* cstr) = 0;
	//得到所给字符串中各字符长度
	virtual void GetStringWidth(HBYTE* cstr, vector<HWORD>& vec ) = 0;

    FontType GetFontType(void)
    {
        return m_fontType;
    }

    HString GetFontName()
    {
        return m_fontName;
    }

protected:
    FontType m_fontType;
    HString m_fontName;   // font name

};

class UICORE_DLL_API CReBitmapFont : public HCFont
{
public:
    CReBitmapFont();
    ~CReBitmapFont();

    HINT Open(const HCHAR* pFileName, HUINT w = 0, HUINT h = 0);
	virtual HINT Open(unsigned char* pMemory, HLONG lSize, HUINT w = 0, HUINT h = 0);
    // Get the bitmap of specified charator.
    // pCh [IN]: the charator.
    // pBitmap [INOUT]: return value, the bitmap of the charator.
    //  kn_byte* GetCharator(kn_word ch);
    HBYTE* GetCharator(HBYTE qu, HBYTE wei);

    HBYTE* GetMeMCharator(HBYTE qu, HBYTE wei);

    // Get the min Qu code of the bitmap font.
    HINT GetMinQu();

    // Get the min Wei code of the bitmap font.
    HINT GetMinWei();

    // Get the width of the bitmap charator.
    HINT GetWidth();

    void GetFontSize(HINT& width, HINT& height);
    void SetFontSize(HINT& width, HINT& height);

    // Get the height of the bitmap charator.
    HINT GetHeight();

    // 取得字符串使用该字体的宽度
    HINT GetStringWidth(HBYTE* cstr);

	void GetStringWidth(HBYTE* cstr, vector<HWORD>& vec );
    // Get the size of every charator.
    HINT GetCharSize();

private:
    //    FILE* m_pFile;
    HFile m_File;

    struct REFONTHEADER
    {
        HINT width;       // 字体的宽 width of a charactor.
        HINT height;      // 字体的高 height of a charactor.
        HINT minQu;       // 字体的起始区号 indicate the start pos of the qu code (1-94).
        HINT minWei;      // 字体的起始位号 indicate the start pos of the qu code (1-94).
        HLONG bHas16; // 有无区位码开始的16个区的字符
        HLONG bHasAnsi;   // 有无256个Ansi字符
    };

    REFONTHEADER m_fontHeader;

    HINT m_iHeaderSize;   // sizeof(m_iMinQu+m_iMinWei+m_iBmpWidth+m_iBmpHeight).
    HINT m_iCnCharOffset;// offset from the file start to the Chinese charactor.
    HINT m_iCharSize; // size (in bytes) of every charator.
    HINT m_size;   //number of evevy qu

    HBYTE m_Temp[KCFONTSIZE*KCFONTSIZE/8];    // 保存一个字符的点阵数据,返回给调用函数.
    KNTEXTCACHE m_cache[100];
    HINT m_cur;
    HINT m_total;
};

typedef struct _TTFFontSize
{
	HINT left;
	HINT top;
	HINT width;
	HINT height;

	_TTFFontSize()
	{
		left = 0;
		top = 0;
		width = 0;
		height = 0;
	}
}TTFFontSize;

class UICORE_DLL_API CReTTFFont : public HCFont
{
public:
    CReTTFFont();
    ~CReTTFFont();
    HINT Open(const HCHAR* pFileName, HUINT w = 0, HUINT h = 0);
	virtual HINT Open(unsigned char* pMemory, HLONG lSize, HUINT w = 0, HUINT h = 0);
    HINT GetWidth();
    HINT GetHeight();
    void GetFontSize(HINT& width, HINT& height);
    void SetFontSize(HINT& width, HINT& height);

    // 取得字符串使用该字体的宽度
    HINT GetStringWidth(HBYTE* cstr);
	HINT GetStringWidth( HCHAR* cstr );

	// 取得字符串中每个字符的宽度，包括空隙
	void GetStringWidth(HBYTE* cstr, vector<HWORD>& vec );
	void GetStringWidth(HCHAR* cstr, vector<HWORD>& vec );
	void GetStringWidthHeight(HCHAR* cstr, vector<TTFFontSize>& vec );



	// 取得字符串的宽度和高度，该高度不同于文字高度
	void GetStringSize(HCHAR* cstr, HINT& width, HINT& height);
	void GetStringSize(HCHAR*cstr, HINT& width, HINT& height, HINT& pos);

    FT_Face GetFTFace();

    static FT_Library m_ft_library;
private:

    FT_Face m_ft_face;
    HINT m_width;
    HINT m_height;
};