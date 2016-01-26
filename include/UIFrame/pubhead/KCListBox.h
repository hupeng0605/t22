/********************************************************************
    created:    2006/12/04
    created:    4:12:2006   11:28
    filename:   d:\code\try\newhmi\include\kclistbox.h
    file path:  d:\code\try\newhmi\include
    file base:  kclistbox
    file ext:   h
    author:          

    purpose:
*********************************************************************/

#if !defined(AFX_KCLIST_H__A1D31C49_3686_4A89_A80B_63B62A737FD6__INCLUDED_)
#define AFX_KCLIST_H__A1D31C49_3686_4A89_A80B_63B62A737FD6__INCLUDED_

#pragma warning(disable : 4786)

#include <vector>
#include "KCWindow.h"
#include "KCSlideCtrl.h"
#include "KCTextCtrl.h"

#define COL_NUM 2 // 支持的列数

// 当使用OwnerData时的回调类型
enum CALLBACKTYPE
{
    LST_ADDSTRING,
    LST_DELETE,
    LST_CLEAR,
    LST_SETSTRING,
    LST_GETSTRING,
    LST_GETCOUNT,
	LST_GETTEXTSTRING,
};

struct CALLBACKINFO
{
    CALLBACKTYPE cbtype;    // 回调类型
    HINT iItem;       // 条目序号(行)、也用作传递ListCount属性
    HINT iSubitem;    // 子条目序号(列)
    const HCHAR* str;     // 条目的字符串内容
};

class UICORE_DLL_API HCListBox : public HCBaseCtrl
{
public:
    HCListBox();
    virtual ~HCListBox();

    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);

    //设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
    void SetBkgndN(IReSurface* pSur);
    void SetBkgndN(const HString& pFileName);

    void SetBkgndA(IReSurface* pSur);
    void SetBkgndA(const HString& pFileName);

    HBOOL Create(HINT x, HINT y, HINT w, HINT h, HUINT row, HUINT col, HINT height);
    //设置文字偏移
    void SetTextPos(HINT x, HINT y, HINT width, HUINT col = 0);
    //加入一行新字符串(内容为第一列)
    void AddString(const HString& str);
    //删除一行
    void Delete(HUINT n);
    //取得当前选择行。0开始
    HINT GetCurSel();
    //取得当前被选第一列字符串，
    HString GetCurSelString();
    //取得指定行列的字符串
    HString GetString(HUINT nIndex, HUINT col = 0);
    //取得指定行列的字符串
    void SetString(const HString& str, HUINT nIndex, HUINT col = 0);
    //设置被选行
    HBOOL SetCurSel(HINT nIndex);
    //清除
    void Clear();
    //取得首行索引位置
    HINT GetPos();
    //设置首行位置
    HINT SetPos(HUINT pos);

    //取得列表框可显示行数
    HINT GetRow();
    //取得列表框数据总行数
    HINT GetListCount();

    // 设置pos属性改变时的回调
    void SetCallBackPosChange(void (*callback)(void*, void*), void* pThis);

    // Add.              .2007.02.08
    // 设置OwnerData方式时的回调(提供类似Windows的Virtual List View的功能)
    void SetCallBackOwnerData(void (*callback)(void*, void*), void* pThis);

	// 列表弹起回调
	void SetCallBackUp(void (*callback)(void*, void*), void* );

    // 设置与之绑定的slider控件
    void SetSlideCtrl(HCSlideCtrl *pSlide);

	// 设置与之绑定的Text控件
	void SetTextCtrl(HCTextCtrl *pText);

	//取得Text控件的字符串
	HString GetTextString();
	void SetTextString();

    //根据KCSlideCtrl 滑动条值刷新列表框位置
    void RefreshFromSlideCtrl();

	

    virtual void GetBackSufSize(HINT& x, HINT& y);

	HINT GetLangID(HINT nRow)
	{
		return m_nLangID[nRow];
	}
	void SetLangID(HINT a_nLangID,HINT nRow)
	{
		m_nLangID[nRow] = a_nLangID;
	}


protected:
	vector<HINT> m_nLangID;

    //文字越界的定时偏移量增一
    void AddStrOut();

    // 计算是否有某一列文字需要滚动显示
    void IsNeedRoll();

    //常规背景图
    IReSurface* m_pBkgndN;
    HBOOL m_bBkgndNRes;

    //激活背景图
    IReSurface* m_pBkgndA;
    HBOOL m_bBkgndARes;

    vector<HString> m_lstString[COL_NUM];

    //字符串长度超出的宽度
    HINT m_nStrOutSize[COL_NUM];

    //定时偏移量
    HINT m_nStrOut[COL_NUM];

    //当前选中的索引 从0开始
    HINT m_nCurrent;
    //列
    HINT m_nCol;
    //行
    HINT m_nRow;
    //行高
    HINT m_nHeight;

    //列表显示项第一项位置,从0开始
    HINT m_nPos;

    //文字起始位置
    HINT m_nColx[COL_NUM];
    HINT m_nColy[COL_NUM];

    //文字显示宽度
    HINT m_nColw[COL_NUM];

    //文字是否越界，要响应定时器消息
    HBOOL m_bOut;

    // OwnerData方式的回调函数指针
    void (*m_pCallBackPosChange)(void* pThis, void* pParam);

    // 获取显示信息的回调函数指针
    void (*m_pCallBackOwnerData)(void* pThis, void* pParam);

	//列表弹起时回调
	void (*m_pCallBackUp)(void *, void *);

    //绑定的Slide变量
    HCSlideCtrl *m_pSlide;

	//绑定的Text变量
	HCTextCtrl *m_pText;

    HUINT m_baseTime;
};

#endif