
#include "KCWnd.h"

class CYPRESS_DLL_API HCSliderCtrlEx : public HCBaseCtrl
{
public:
	HCSliderCtrlEx();
	~HCSliderCtrlEx();

public:
	//***************************************************************
	// *  功　　能: 设置相关资源的路径
	// *  入口参数: pSliderBkgSurfPath:滑动条背景图，pSliderBkgActiveSurfPath：滑动条激活背景图，pReapetBkgSurfPath：重复段的背景图
	// *  			pReapetBkgActiveSurfPath：重复段的激活背景图，pThumbSurfPath：滑块背景图，pReapetASurfPath：A标志背景图， pReapetASurfPath：B标志背景图
	// *  出口参数: 
	// *  返 回 值: 
	//***************************************************************
	void SetSurface(const HCHAR* pSliderBkgSurfPath, const HCHAR* pSliderBkgActiveSurfPath,
		const HCHAR* pReapetBkgSurfPath, const HCHAR* pReapetBkgActiveSurfPath, 
		const HCHAR* pThumbSurfPath, const HCHAR* pThumbActiveSurfPath,
		const HCHAR* pReapetASurfPath, const HCHAR* pReapetBSurfPath);

	//***************************************************************
	// *  功　　能: 设置背景图相对控件左上角的偏移,y轴的偏移与重复段的背景图共用
	// *  入口参数: 
	// *  出口参数: 
	// *  返 回 值: 
	//***************************************************************
	void SetSliderBkgSurfOffset(HUINT dx, HUINT dy);
	//***************************************************************
	// *  功　　能: 设置滑块相对滑动条背景的偏移，该值对两端都有用
	// *  入口参数: 
	// *  出口参数: 
	// *  返 回 值: 
	//***************************************************************
	void SetThumbValueOffset(HUINT dx);

	//***************************************************************
	// *  功　　能: 设置相应图标相对控件左上角的y轴偏移
	// *  入口参数: 
	// *  出口参数: 
	// *  返 回 值: 
	//***************************************************************
	void SetReapetIconOffset(HUINT dy);
	void SetThumbIconOffset(HUINT dy);

	//***************************************************************
	// *  功　　能: 设置滑动的范围，max小于min时交换值
	// *  入口参数: 
	// *  出口参数: 
	// *  返 回 值: 
	//***************************************************************
	void SetBound(HINT min, HINT max);

	//***************************************************************
	// *  功　　能: 设置当前滑块的值
	// *  入口参数: 
	// *  出口参数: 
	// *  返 回 值: 
	//***************************************************************
	void SetCurrentValue(HINT value);
	HINT GetCurrentValue();

	//***************************************************************
	// *  功　　能: 是否允许显示Reapet图标，A图标显示后才能显示B图标，默认不显示
	// *  入口参数: 
	// *  出口参数: 
	// *  返 回 值: 
	//***************************************************************
	void EnableReapetAIcon(HINT value);
	void EnableReapetBIcon(HINT value);

	//***************************************************************
	// *  功　　能: 取消Reapet的显示
	// *  入口参数: 
	// *  出口参数: 
	// *  返 回 值: 
	//***************************************************************
	void CancelReapetPlay();

	// 消息处理函数，各子类都要重载
	virtual HBOOL DoMessage(HMessage* msg);
	virtual void Draw(IReSurface* pSurface);

	void SetCallBackMouseUp(void (*callback)(void*, void*), void*);

	HBOOL IsRepeatABShow();
private:
	//***************************************************************
	// *  功　　能: 根据当前的值计算滑块的位置
	// *  入口参数: 
	// *  出口参数: 
	// *  返 回 值: 
	//***************************************************************
	HINT CalcPos(HINT value);

	//***************************************************************
	// *  功　　能: 
	// *  入口参数: 
	// *  出口参数: 
	// *  返 回 值: 
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
	HINT m_nThumbXPos;//滑块的当前位置

	HBOOL m_bEnableReapetA;
	HBOOL m_bEnableReapetB;
	HINT m_nReapetAValue;
	HINT m_nReapetBValue;

	HINT m_nReapetAXPos;
	HINT m_nReapetBXPos;

	HINT m_nXBackup;//按下时X轴的偏移
	
	//回调函数变量,要传入类指针
	void (*m_pCallBackMouseUp)(void *, void *);
	void* m_pThis;
};
