

#include "Type.h"
#include "KNFile.h"
#include "KCFont.h"

class UICORE_DLL_API HCStringPackage
{
public:
	HCStringPackage();
	~HCStringPackage();
	HCStringPackage(HCHAR *str);
	HCStringPackage(const HString& str);
	HCStringPackage(const HCStringPackage& other);

	HCStringPackage operator = (const HCStringPackage & other);
public:
	HString GetString(void);
	void SetString(HCHAR * str);
	void SetString(const HString& str);

	HINT GetStrNum(void);

	HINT GetHrGravity(void);
	void SetHrGravity(HINT nHrGravity);

	HINT GetVtGravity(void);
	void SetVtGravity(HINT nVtGravity);

	void GetStrPos(HINT *a_nStrX,	HINT *a_nStrY);
	void SetStrPos(HINT a_nStrX, HINT a_nStrY);

	void GetStrSize(HINT *a_nStrW,INT16 *a_nStrH);
	void SetStrSize(INT16 a_nStrW,INT16 a_nStrH);

	HINT GetEditType(void);
	void SetEditType(INT8 a_nEditType);
	
	void SetFont(HCFont *a_pFont);
	HCFont* GetFont(void);

private:
	/* Attribute Area */
	HString m_strString;                         /* 文字列  */
	HCFont*   m_pFontData;                          /* フォントクラス */
	INT16     m_nHrGravity;                        /* 水平グラビティ  */
	INT16     m_nVtGravity;                        /* 垂直グラビティ  */
	INT16     m_nStrX;                             /* 文字列座標 */
	INT16     m_nStrY;                             /* 文字列座標 */
	INT16     m_nStrW;                             /* 文字列幅   */
	INT16     m_nStrH;                             /* 文字列高さ */

	INT8      m_nEditType;                         /* エディットタイプ */
	
};