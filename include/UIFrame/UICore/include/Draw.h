

#ifndef _RE_DRAW__
#define _RE_DRAW__

#include "RenderingEngine.h"
#include "Surface.h"
#include "KCFont.h"
#include "Brush.h"


#define	THEME_COUNT		3
//#include "KSingleton.h"

class CReDraw : public IReDraw
{
public:
    CReDraw();
    ~CReDraw();

public:
    /*
	* ��������:initialize the interface.
	* ��    ��:��
	* �� �� ֵ:��
	*/
    ERRINFO Initialize();

    /*
	* ��������:��һ���������ڻ���,ָ����С����ɫģʽ
	* ��    ��:
	*      lWidth  [in] :������
	*      lHeight [in] :����߶�
	*      dwColorFormat  [in] :���ʽ
	* �� �� ֵ:����ָ��
	*/
#if	defined(SCREEN_COLORBIT16)
	IReSurface* CreateSurface(HLONG lWidth, HLONG lHeight, HDWORD dwColorFormat = RE_COLOR565, HBOOL bUseDraw = FALSE, HBOOL bCreateDC = FALSE);
#else
    IReSurface* CreateSurface(HLONG lWidth, HLONG lHeight, HDWORD dwColorFormat = RE_COLOR888, HBOOL bUseDraw = FALSE, HBOOL bCreateDC = FALSE);
#endif // _DEBUG
	IReSurface* CreateTTFFontSurface(HINT font_width, HINT font_height, HCFont* pFont, HDWORD dwFormat, const HCHAR* str, HINT strWidth = 0);
	IReSurface* CreateSurfaceFromKtcStream(const HBYTE* pMemAddr);
	IReSurface* CreateSurfaceFromJpegStream(const HBYTE* pMemAddr, HINT MemSize);
	virtual IReSurface* CreateSurfaceFromBmpStream(const HBYTE* pMemAddr, HINT nMemSize);

	//IReSurface* CreateSurfaceFromRGB888Stream(const kn_byte* pMemAddr, kn_int width, kn_int height, kn_int nSize, kn_bool bUseErrorDiffuse = TRUE);
	void ModifyKtcStreamSurface(IN const HBYTE* pMemAddr, OUT IReSurface* pKtcStreamSur);

    /*
	* ��������:���ļ��д�������.����ļ���24λɫ,��ʽָ��RE_COLOR565,���Զ�תΪ16λ����
	* ��    ��:
	*      strFileName [in] :�ļ���
	*      dwColorFormat  [in] :���ʽ
	* �� �� ֵ:����ָ��
	*/
    IReSurface* CreateSurfaceFromFile(const HString& pFileName, HDWORD dwColorFormat);
	//IReSurface* CreateSurfaceInErrorDiffuse(IReSurface* pSurf);
	IReSurface* CreateSurfaceFrom565Mem(const HBYTE* pMemAddr, HINT width, HINT height);
    /*
	* ��������:ȡ�������Size
	* ��    ��:
	*      iWidth   [out] :������
	*      iHeight  [out] :����߶�
	*      iIndex   [in]: ��������
	* �� �� ֵ:��
	*/
    void GetFontSize(HINT &iWidth, HINT &iHeight, HINT iIndex);

	/*
	* ��������:ȡ������
	* ��    ��:
	*      iIndex   [in]: ��������
	* �� �� ֵ:����
	*/
    HCFont* GetFont(HINT iIndex);

	//���¼������壬����ֻ����һ�������ļ�
	void ReLoadFont(HINT iThemeIndex);

	/*
	* ��������:initialize alpha table
	* ��    ��:��
	* �� �� ֵ:��
	*/ 
	void InitAlpha();

	/*
	* ��������:get alpha table head point
	* ��    ��:��
	* �� �� ֵ:table head point
	*/
	HBYTE** GetTransparentTable();

	/*
	* ��������:get alpha table head point
	* ��    ��:��
	* �� �� ֵ:table head point
	*/
	//remove by cxl
	//kn_int**  GetAlphaTable();

	REBrushGenerate* GetBrush(HINT ID)
	{
		return brushMgr.GetBrush(ID);
	}

protected:
	BOOL CreateShareMemory(HINT nThemeIndex, HLONG& nMemSize);

protected:
    // surfaceʹ�õ�����, ����surface����һ��ָ��ָ���������,����ֻ֧��һ������,���Ժ�Ҫ֧�ֶ��,������
    vector<HCFont*> m_font;

	// alpha table
	HBYTE* m_RGB_Transparent_table[TRANSPARENTLEVEL + 1];
	//remove by cxl
	//kn_int*  m_RGB_Alpha_table[256];

	BrushManager brushMgr;
	//kn_byte	m_byCurrentTheme[THEME_COUNT];	//	��ǰ����

	HCFont*		m_pThemeFont[THEME_COUNT];

	//���������ڴ棬���ڴ������
	HANDLE m_hFontShareMapping[3];
	void* m_pFontShareMem[3];

	//���ڼ�¼�������干���ڴ��С�Ĺ����ڴ�
	HANDLE m_hFontSizeShareMapping;
	void* m_pFontSizeShareMem;
};

#endif // _RE_DRAW__
