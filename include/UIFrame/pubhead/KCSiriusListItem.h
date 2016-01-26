

#pragma once

#include "KCListItemBase.h"

class UICORE_DLL_API HCSiriusListItem : public HCListItemBase
{
public:
	HCSiriusListItem();
	~HCSiriusListItem();

	//创建控件
	void Create(HINT width, HINT height, IReSurface* pSurIcon, HString& text);
	void Create(HINT width, HINT height, const HString& pFileName, HString& text);
	//设置字体离列表的宽度
	void SetFontPos(HINT x);

	void Create(HINT width, HINT height, IReSurface* pSurIcon, const HCHAR* text);
	void Create(HINT width, HINT height, const HString& pFileName, const HCHAR* text);
	
	void SetEnableRoll(HBOOL bIn, HINT rollNum);
	//设置ICON
	void SetIcon(IReSurface* pSur);
	void SetIcon(const HString& pFileName);

	//设置文本
	void SetText(HString& text);
	void SetText(const HCHAR* pTxt);

	//设置是否支持文本渲染
	void SetTextRender(HBOOL bRender);

	virtual void Draw(IReSurface* pSurface, HINT x, HINT y, HINT width, HINT height, HINT xSrc, HINT ySrc);
	virtual HBOOL DoMessage(HMessage* msg);

	void SetFatherWnd(HCWindow* pFatherWnd);

	//添加其它控件到项中
	HBOOL AddBaseCtrl(HCBaseCtrl* pBaseCtrl);
	//返回控件容器
	KCBASECTRL_VEC& GetBaseCtrlVec();
	//返回控件数目
	HINT GetBaseCtrlCount();
	void AppText(const HCHAR* pText,HINT fontW,HINT fontH,HBOOL bstate);
	//释放文本资源、背景副本资源
	void Release();

	void ReInit();
	void SetIconF(IReSurface* pSur);
	void SetIconF(const HString& pFileName);
	void SetYPos(HINT npos);
	void SetIconPos(HINT x,HINT y);
protected:
	void SetFontCenter(HINT nWidth);
	
	HINT m_nFontPos;
	HINT m_nYPos;
	//背景副本
	IReSurface* m_pBkgBackupSurf;
	HBOOL m_bOver;//记录字符是否超长
	//图标资源
	IReSurface* m_pIcon;
	IReSurface* m_pIconF;
	HBOOL m_bIconRes;
	HBOOL m_bEnableRoll;

	//文本资源图
	IReSurface* m_pTextSurf;
	IReSurface* m_pInwardSurf;
	IReSurface* m_pAppTextSurf;
	HBOOL m_bTextRender;
	
	//控件容器
	KCBASECTRL_VEC m_baseCtrl_vec;
	HINT m_noffset;//记录每次的偏移量
	HBOOL m_bRoll;//记录是否移动的标志位
	HINT m_nScrollBaseTime;//记录定时器的基准
	HINT m_nSecondOffset;//记录第二次进来的偏移位置
	HBOOL m_bSecondOffset;//记录是否显示第二次
	HINT m_nRollCount; //滚动次数计数
	HINT m_nRollNum;	// 滚动次数
	HBOOL m_bStopRoll;//滚动m_nRollNum次的标志位
	HBOOL m_bAppText;
	HString m_sAddStr;
	HINT m_nAddStrW;
	HINT m_nAddStrH;
	HINT m_nIconX;//X轴的偏移
	HINT m_nIconY;//Y轴的偏移

	HBYTE m_eState;	// 控件状态
};

