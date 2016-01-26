

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

// ���Ժ꣬����������Ϣ
#ifdef _DEBUG
#define DBGASSERT(b, msg) \
    if(!(b))\
    {\
        MessageBox(GetActiveWindow(), msg, _T("������Ϣ"), MB_OK);\
    }
#else
#define DBGASSERT(b, msg)
#endif

// ���Ժ꣬����������Ϣ��ͬһλ��ֻ����һ��
#ifdef _DEBUG
#define DBGASSERTONCE(b, msg) \
    if(!(b))\
    {\
        static HBOOL bShown = false;\
        if(!bShown)\
        {\
            bShown = true;\
            MessageBox(GetActiveWindow(), msg, _T("������Ϣ"), MB_OK);\
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

//��Դ������
class UICORE_DLL_API HCResCase
{
public:
    HCResCase();
    ~HCResCase();
    void Release();

    //ȡ��һ����Դ�������Դ�ڲ�û�У�bLoadΪ�� ����غ󷵻�
    IReSurface* GetResource(const HString& filename, HBOOL bLoad = TRUE);

    //����ȫ�ֱ���ͼ
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
    // ���Ի���ID
    virtual DialogName(_T(""))

    HDialogBase();

    virtual ~HDialogBase();

	void SetDialogName(HString str) {m_strDlgName = str;};

    HCBaseCtrl* CreateCtrl(HBaseCtrlProp* pBaseCtrlProp);

    // �˺������ڶԻ���ʵ��ȡ�õ����߷������Ĳ���
    virtual void OnSetParam(void* /*pParam*/, va_list /*args*/) {};

    // �˻ص����ڷ�ģʽ�Ի�����֪ͨ��������
    void SetCallBack(void (*pCallBack)(void*, void*), void*);


	// �ػ�
		void Draw(IReSurface* pSurface);
	// �ػ�
		void Draw(IReSurface* pSurface,IReSurface* pSurfaceMap,_kn_rect m_rectMap);
protected:
	

    // ��ʼ�����
    virtual void InitComponents() {};

    // ������Ϣ
    HBOOL DoMessage(HMessage* msg);

    // ��ʼ��
    HINT OnInit();

    // �����������ı�ʱ������
    LRESULT OnSettingChange(HUINT uParam);

    // װ���������
    void LoadComponents();

    // װ��Ի����������Ϣ
    void LoadProp();

    // װ��ĳ�������������Ϣ
    void LoadCtrlProp(HBaseCtrlProp* pBaseProp, HCBaseCtrl* pBase);

    // �ͷ�����ֵ���󼰶�Ӧ�Ŀؼ�
    void ReleaseComponents();

    // �����ֲ��ҿؼ�
    HCBaseCtrl* GetCtrlByName(const HString& strName);
    // �����ֲ��ҿؼ����������
    HCBaseCtrl* GetCtrlByNameNoCheck(const HString& strName);

    // ��ȡ�ؼ����飬��ǰ׺Ϊ"Ctrl_",���ƿ�ΪCtrl_A~Ctrl_Z��Ctrl_0~Ctrl_n(n>0)
    CtrlArray GetCtrlsByName(const HString& strPrefix, HINT iStart = 0);
    CtrlArray GetCtrlsByName(const HString& strPrefix, HCHAR chStart);
    CtrlArray GetCtrlsBySameName(const HString& strName);

    // ���ذ�ť�ص�
    static void OnBtnReturn(void*, void*);
    void OnBtnReturn();

    // ���Ը��Ǵ˺������ڹر�ǰִ����������
    virtual void OnClose() {};

    void (*m_pCallBack)(void*, void*); // ������ɺ�Ļص�����
    void* m_pThis; // ��Ҫ���沢���ص�thisָ��

	HString m_strDlgName;
private:
    // �������ؼ�����ֵ������б�
    HDialogProp* m_pDialogProp;
    map<HBaseCtrlProp*, HCBaseCtrl*> m_lstDynamicCtrl;
	map<HString, CtrlArray*> m_lstCtrlNameMap;
	
    HCResCase m_Res;
};

#endif // _KDIALOGBASE_H_
