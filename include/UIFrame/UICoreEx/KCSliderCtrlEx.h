
#include "KCWnd.h"

class CYPRESS_DLL_API HCSliderCtrlEx : public HCBaseCtrl
{
public:
	HCSliderCtrlEx();
	~HCSliderCtrlEx();

public:
	//***************************************************************
	// *  ��������: ���������Դ��·��
	// *  ��ڲ���: pSliderBkgSurfPath:����������ͼ��pSliderBkgActiveSurfPath�������������ͼ��pReapetBkgSurfPath���ظ��εı���ͼ
	// *  			pReapetBkgActiveSurfPath���ظ��εļ����ͼ��pThumbSurfPath�����鱳��ͼ��pReapetASurfPath��A��־����ͼ�� pReapetASurfPath��B��־����ͼ
	// *  ���ڲ���: 
	// *  �� �� ֵ: 
	//***************************************************************
	void SetSurface(const HCHAR* pSliderBkgSurfPath, const HCHAR* pSliderBkgActiveSurfPath,
		const HCHAR* pReapetBkgSurfPath, const HCHAR* pReapetBkgActiveSurfPath, 
		const HCHAR* pThumbSurfPath, const HCHAR* pThumbActiveSurfPath,
		const HCHAR* pReapetASurfPath, const HCHAR* pReapetBSurfPath);

	//***************************************************************
	// *  ��������: ���ñ���ͼ��Կؼ����Ͻǵ�ƫ��,y���ƫ�����ظ��εı���ͼ����
	// *  ��ڲ���: 
	// *  ���ڲ���: 
	// *  �� �� ֵ: 
	//***************************************************************
	void SetSliderBkgSurfOffset(HUINT dx, HUINT dy);
	//***************************************************************
	// *  ��������: ���û�����Ի�����������ƫ�ƣ���ֵ�����˶�����
	// *  ��ڲ���: 
	// *  ���ڲ���: 
	// *  �� �� ֵ: 
	//***************************************************************
	void SetThumbValueOffset(HUINT dx);

	//***************************************************************
	// *  ��������: ������Ӧͼ����Կؼ����Ͻǵ�y��ƫ��
	// *  ��ڲ���: 
	// *  ���ڲ���: 
	// *  �� �� ֵ: 
	//***************************************************************
	void SetReapetIconOffset(HUINT dy);
	void SetThumbIconOffset(HUINT dy);

	//***************************************************************
	// *  ��������: ���û����ķ�Χ��maxС��minʱ����ֵ
	// *  ��ڲ���: 
	// *  ���ڲ���: 
	// *  �� �� ֵ: 
	//***************************************************************
	void SetBound(HINT min, HINT max);

	//***************************************************************
	// *  ��������: ���õ�ǰ�����ֵ
	// *  ��ڲ���: 
	// *  ���ڲ���: 
	// *  �� �� ֵ: 
	//***************************************************************
	void SetCurrentValue(HINT value);
	HINT GetCurrentValue();

	//***************************************************************
	// *  ��������: �Ƿ�������ʾReapetͼ�꣬Aͼ����ʾ�������ʾBͼ�꣬Ĭ�ϲ���ʾ
	// *  ��ڲ���: 
	// *  ���ڲ���: 
	// *  �� �� ֵ: 
	//***************************************************************
	void EnableReapetAIcon(HINT value);
	void EnableReapetBIcon(HINT value);

	//***************************************************************
	// *  ��������: ȡ��Reapet����ʾ
	// *  ��ڲ���: 
	// *  ���ڲ���: 
	// *  �� �� ֵ: 
	//***************************************************************
	void CancelReapetPlay();

	// ��Ϣ�������������඼Ҫ����
	virtual HBOOL DoMessage(HMessage* msg);
	virtual void Draw(IReSurface* pSurface);

	void SetCallBackMouseUp(void (*callback)(void*, void*), void*);

	HBOOL IsRepeatABShow();
private:
	//***************************************************************
	// *  ��������: ���ݵ�ǰ��ֵ���㻬���λ��
	// *  ��ڲ���: 
	// *  ���ڲ���: 
	// *  �� �� ֵ: 
	//***************************************************************
	HINT CalcPos(HINT value);

	//***************************************************************
	// *  ��������: 
	// *  ��ڲ���: 
	// *  ���ڲ���: 
	// *  �� �� ֵ: 
	//***************************************************************
	void CalcCurrentValueFromPos(HINT offset);

	
private:
	IReSurface* m_pSliderBkgSurf;
	IReSurface* m_pSliderBkgActiveSurf;
	IReSurface* m_pReapetBkgSurf;
	IReSurface* m_pReapetBkgActiveSurf;
	IReSurface* m_pThumbSurf;
	IReSurface* m_pThumbActiveSurf;
	IReSurface* m_pReapetASurf;
	IReSurface* m_pReapetBSurf;

	HINT m_nSliderBkgXOffset;
	HINT m_nSliderBkgYOffset;
	HINT m_nThumbValueOffset;
	HINT m_nReapetIconYOffset;
	HINT m_nThumbIconYOffset;

	HINT m_nMinValue;
	HINT m_nMaxValue;
	HINT m_nCurrentValue;
	HINT m_nThumbXPos;//����ĵ�ǰλ��

	HBOOL m_bEnableReapetA;
	HBOOL m_bEnableReapetB;
	HINT m_nReapetAValue;
	HINT m_nReapetBValue;

	HINT m_nReapetAXPos;
	HINT m_nReapetBXPos;

	HINT m_nXBackup;//����ʱX���ƫ��
	
	//�ص���������,Ҫ������ָ��
	void (*m_pCallBackMouseUp)(void *, void *);
	void* m_pThis;
};
