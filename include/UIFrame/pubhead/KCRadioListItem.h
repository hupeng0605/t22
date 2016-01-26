

#pragma once

#include "KCListItem.h"

class UICORE_DLL_API HCRadioListItem : public HCListItem
{
public:
	HCRadioListItem();
	~HCRadioListItem();

	//创建控件
	void Create(HINT width, HINT height, IReSurface* pSurIcon, HString& text,HString &index,HINT nTextOffset_Y = 0,HINT nTextOffset_Y_pushed = 0);
	void Create(HINT width, HINT height, const HString& pFileName, HString& text,HString& index,HINT nTextOffset_Y = 0,HINT nTextOffset_Y_pushed = 0);

	void Create(HINT width, HINT height, IReSurface* pSurIcon, const HCHAR* text,HCHAR* index,HINT nTextOffset_Y = 0,HINT nTextOffset_Y_pushed = 0);
	void Create(HINT width, HINT height, const HString& pFileName, const HCHAR* text,HCHAR* index,HINT nTextOffset_Y = 0,HINT nTextOffset_Y_pushed = 0);

	//设置Index
	void SetIndex(HString& index);
	void SetIndex(const HCHAR* index);

	void SetIndexTextColorN(int r , int g , int b);
	void SetIndexTextColorA(int r , int g , int b);
	void SetIndexTextColorS(int r , int g , int b);

	virtual void Draw(IReSurface* pSurface, HINT x, HINT y, HINT width, HINT height, HINT xSrc, HINT ySrc);

	//释放文本资源、背景副本资源
	void Release();

	void ReInit();
	// 6.7 add SetIconA
	// 避免计算，x y使用绝对坐标
	void SetIconN(IReSurface* pSur,HINT x = 0,HINT y = 0);
	void SetIconN(const HString& pFileName,HINT x = 0,HINT y = 0);
	void SetIconA(IReSurface* pSur,HINT x = 0,HINT y = 0);
	void SetIconA(const HString& pFileName,HINT x = 0,HINT y = 0);
	void SetIconF(IReSurface* pSur,HINT x = 0,HINT y = 0);
	void SetIconF(const HString& pFileName,HINT x = 0,HINT y = 0);

	void SetPushedOffset(HINT nOffset = 0)
	{
		m_nOffset_Pushed = nOffset;
	}
protected:
	//void SetFontCenter(kn_int nWidth);
	//kn_int m_nFontPos;
	////背景副本
	//IReSurface* m_pBkgBackupSurf;
	//kn_bool m_bOver;//记录字符是否超长
	////图标资源
	//IReSurface* m_pIcon;
	//kn_bool m_bIconRes;
	//kn_bool m_bEnableRoll;

	////文本资源图
	//IReSurface* m_pTextSurf;
	//IReSurface* m_pInwardSurf;
	//kn_bool m_bTextRender;
	//
	////控件容器
	//KCBASECTRL_VEC m_baseCtrl_vec;
	//kn_int m_noffset;//记录每次的偏移量
	//kn_bool m_bRoll;
	//kn_int m_nScrollBaseTime;
	//kn_int m_nSecondOffset;
	//kn_bool m_bSecondOffset;
	
protected:
	HINT		m_nOffset_Pushed;
	REPOINT		m_ptIconN;
	REPOINT		m_ptIconF;
	REPOINT		m_ptIconA;
	HINT		m_nTextOffset_Y;
	HINT		m_nTextOffset_Y_Pushed;
	HString	m_strIndex;
	// 激活和聚集态的序号背景
	HBOOL m_bIconARes;
	HBOOL m_bIconFRes;
	IReSurface* m_pIconA;
	IReSurface* m_pIconF;

	RECOLOR m_clrTextN;
	RECOLOR m_clrTextA;
	RECOLOR m_clrTextS;
};

