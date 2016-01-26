

#include "KCListItemBase.h"

class UICORE_DLL_API HCTextListItem : public HCListItemBase
{
public:
	HCTextListItem();
	~HCTextListItem();

	virtual void Draw(IReSurface* pSurface, HINT x, HINT y, HINT width, HINT height, HINT xSrc, HINT ySrc);
	virtual HBOOL DoMessage(HMessage* msg);

	// 设置行距
	void SetLineSpace(HINT height);
	// 设置文本样式
	void SetTextStyle(HINT style);
	// 设置边距
	void SetMargin(HINT left, HINT right, HINT top, HINT bottom);

	//设置文本
	void SetText(HString& text);
	void SetText(const HCHAR* pTxt);

	//释放文本资源
	void Release();

private:
	// 渲染文本
	void RenderTextSurface();
private:
	HINT m_lineSpace;
	HINT m_textStyle;

	HINT m_leftMargin;
	HINT m_rightMargin;
	HINT m_topMargin;
	HINT m_bottomMargin;

	//文本资源图
	IReSurface* m_pTextSurf;
};