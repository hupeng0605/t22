

#ifndef _KDIALOGBASE_H_
#define _KDIALOGBASE_H_

#include "KHMIConfig.h"
#include "CfgStruct.h"
#include "KCWindow.h"
#include "KCButton.h"
#include "KCTextCtrl.h"
#include "KCCheckBox.h"
#include "KCListBox.h"
#include "KCSlideCtrl.h"
#include "KCProgressCtrl.h"
#include "KCImageCtrl.h"
#include "KCGroupCtrl.h"
#include "KCScrollBox.h"
#include "KCKeyBoard.h"

// 调试宏，弹出调试信息
#ifdef _DEBUG
#define DBGASSERT(b, msg) \
    if(!(b))\
    {\
        MessageBox(GetActiveWindow(), msg, _T("调试信息"), MB_OK);\
    }
#else
#define DBGASSERT(b, msg)
#endif

// 调试宏，弹出调试信息，同一位置只发生一次
#ifdef _DEBUG
#define DBGASSERTONCE(b, msg) \
    if(!(b))\
    {\
        static HBOOL bShown = false;\
        if(!bShown)\
        {\
            bShown = true;\
            MessageBox(GetActiveWindow(), msg, _T("调试信息"), MB_OK);\
        }\
    }
#else
#define DBGASSERTONCE(b, msg)
#endif

#define DialogName(IDD_) HString GetDialogName(){ HString str = IDD_ ; return str;}
//=============================================================================

struct ResStruct
{
    HString m_name;
    IReSurface* m_pSur;
};
//=============================================================================

//资源容器类
class UICORE_DLL_API HCResCase
{
public:
    HCResCase();
    ~HCResCase();
    void Release();

    //取得一个资源，如果资源内部没有，bLoad为真 会加载后返回
    IReSurface* GetResource(const HString& filename, HBOOL bLoad = TRUE);

    //设置全局背景图
    void SetGolbalBackGround(const HString& filename);

	DWORD m_dwResStructPoints[128];
	DWORD m_dwResCount;

    IReSurface* m_pGlobalBackGround;
};
//=============================================================================

extern UICORE_DLL_API HCResCase g_GlobalRes;
//=============================================================================



class UICORE_DLL_API HDialogBase : public HCWindow
{
public:
    // 给对话框赋ID
    virtual DialogName(_T(""))

    HDialogBase();

    virtual ~HDialogBase();

	void SetDialogName(HString str) {m_strDlgName = str;};

    HCBaseCtrl* CreateCtrl(HBaseCtrlProp* pBaseCtrlProp);

    // 此函数用于对话框实例取得调用者发送来的参数
    virtual void OnSetParam(void* /*pParam*/, va_list /*args*/) {};

    // 此回调用于非模式对话框发送通知给调用者
    void SetCallBack(void (*pCallBack)(void*, void*), void*);


	// 重绘
		void Draw(IReSurface* pSurface);
	// 重绘
		void Draw(IReSurface* pSurface,IReSurface* pSurfaceMap,_kn_rect m_rectMap);
protected:
	

    // 初始化组件
    virtual void InitComponents() {};

    // 处理消息
    HBOOL DoMessage(HMessage* msg);

    // 初始化
    HINT OnInit();

    // 当环境发生改变时被调用
    LRESULT OnSettingChange(HUINT uParam);

    // 装入组件对象
    void LoadComponents();

    // 装入对话框的属性信息
    void LoadProp();

    // 装入某个组件的属性信息
    void LoadCtrlProp(HBaseCtrlProp* pBaseProp, HCBaseCtrl* pBase);

    // 释放属性值对象及对应的控件
    void ReleaseComponents();

    // 从名字查找控件
    HCBaseCtrl* GetCtrlByName(const HString& strName);
    // 从名字查找控件，但不检查
    HCBaseCtrl* GetCtrlByNameNoCheck(const HString& strName);

    // 获取控件数组，如前缀为"Ctrl_",名称可为Ctrl_A~Ctrl_Z或Ctrl_0~Ctrl_n(n>0)
    CtrlArray GetCtrlsByName(const HString& strPrefix, HINT iStart = 0);
    CtrlArray GetCtrlsByName(const HString& strPrefix, HCHAR chStart);
    CtrlArray GetCtrlsBySameName(const HString& strName);

    // 返回按钮回调
    static void OnBtnReturn(void*, void*);
    void OnBtnReturn();

    // 可以覆盖此函数以在关闭前执行其他代码
    virtual void OnClose() {};

    void (*m_pCallBack)(void*, void*); // 输入完成后的回调函数
    void* m_pThis; // 需要保存并传回的this指针

	HString m_strDlgName;
private:
    // 包含各控件属性值对象的列表
    HDialogProp* m_pDialogProp;
    map<HBaseCtrlProp*, HCBaseCtrl*> m_lstDynamicCtrl;
	map<HString, CtrlArray*> m_lstCtrlNameMap;
	
    HCResCase m_Res;
};

#endif // _KDIALOGBASE_H_
