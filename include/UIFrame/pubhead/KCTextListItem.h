

#include "KCListItemBase.h"

class UICORE_DLL_API HCTextListItem : public HCListItemBase
{
public:
	HCTextListItem();
	~HCTextListItem();

	virtual void Draw(IReSurface* pSurface, HINT x, HINT y, HINT width, HINT height, HINT xSrc, HINT ySrc);
	virtual HBOOL DoMessage(HMessage* msg);

	// �����о�
	void SetLineSpace(HINT height);
	// �����ı���ʽ
	void SetTextStyle(HINT style);
	// ���ñ߾�
	void SetMargin(HINT left, HINT right, HINT top, HINT bottom);

	//�����ı�
	void SetText(HString& text);
	void SetText(const HCHAR* pTxt);

	//�ͷ��ı���Դ
	void Release();

private:
	// ��Ⱦ�ı�
	void RenderTextSurface();
private:
	HINT m_lineSpace;
	HINT m_textStyle;

	HINT m_leftMargin;
	HINT m_rightMargin;
	HINT m_topMargin;
	HINT m_bottomMargin;

	//�ı���Դͼ
	IReSurface* m_pTextSurf;
};