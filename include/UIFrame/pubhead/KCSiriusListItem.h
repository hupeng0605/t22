

#pragma once

#include "KCListItemBase.h"

class UICORE_DLL_API HCSiriusListItem : public HCListItemBase
{
public:
	HCSiriusListItem();
	~HCSiriusListItem();

	//�����ؼ�
	void Create(HINT width, HINT height, IReSurface* pSurIcon, HString& text);
	void Create(HINT width, HINT height, const HString& pFileName, HString& text);
	//�����������б�Ŀ��
	void SetFontPos(HINT x);

	void Create(HINT width, HINT height, IReSurface* pSurIcon, const HCHAR* text);
	void Create(HINT width, HINT height, const HString& pFileName, const HCHAR* text);
	
	void SetEnableRoll(HBOOL bIn, HINT rollNum);
	//����ICON
	void SetIcon(IReSurface* pSur);
	void SetIcon(const HString& pFileName);

	//�����ı�
	void SetText(HString& text);
	void SetText(const HCHAR* pTxt);

	//�����Ƿ�֧���ı���Ⱦ
	void SetTextRender(HBOOL bRender);

	virtual void Draw(IReSurface* pSurface, HINT x, HINT y, HINT width, HINT height, HINT xSrc, HINT ySrc);
	virtual HBOOL DoMessage(HMessage* msg);

	void SetFatherWnd(HCWindow* pFatherWnd);

	//��������ؼ�������
	HBOOL AddBaseCtrl(HCBaseCtrl* pBaseCtrl);
	//���ؿؼ�����
	KCBASECTRL_VEC& GetBaseCtrlVec();
	//���ؿؼ���Ŀ
	HINT GetBaseCtrlCount();
	void AppText(const HCHAR* pText,HINT fontW,HINT fontH,HBOOL bstate);
	//�ͷ��ı���Դ������������Դ
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
	//��������
	IReSurface* m_pBkgBackupSurf;
	HBOOL m_bOver;//��¼�ַ��Ƿ񳬳�
	//ͼ����Դ
	IReSurface* m_pIcon;
	IReSurface* m_pIconF;
	HBOOL m_bIconRes;
	HBOOL m_bEnableRoll;

	//�ı���Դͼ
	IReSurface* m_pTextSurf;
	IReSurface* m_pInwardSurf;
	IReSurface* m_pAppTextSurf;
	HBOOL m_bTextRender;
	
	//�ؼ�����
	KCBASECTRL_VEC m_baseCtrl_vec;
	HINT m_noffset;//��¼ÿ�ε�ƫ����
	HBOOL m_bRoll;//��¼�Ƿ��ƶ��ı�־λ
	HINT m_nScrollBaseTime;//��¼��ʱ���Ļ�׼
	HINT m_nSecondOffset;//��¼�ڶ��ν�����ƫ��λ��
	HBOOL m_bSecondOffset;//��¼�Ƿ���ʾ�ڶ���
	HINT m_nRollCount; //������������
	HINT m_nRollNum;	// ��������
	HBOOL m_bStopRoll;//����m_nRollNum�εı�־λ
	HBOOL m_bAppText;
	HString m_sAddStr;
	HINT m_nAddStrW;
	HINT m_nAddStrH;
	HINT m_nIconX;//X���ƫ��
	HINT m_nIconY;//Y���ƫ��

	HBYTE m_eState;	// �ؼ�״̬
};

