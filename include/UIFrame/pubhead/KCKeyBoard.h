
#if !defined(AFX_KCPOIINPUT_H__29AD494F_5FEB_4B8C_BCBD_AD65A8F198A5__INCLUDED_)
#define AFX_KCPOIINPUT_H__29AD494F_5FEB_4B8C_BCBD_AD65A8F198A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWnd.h"
#include "KCWindow.h"

//#define GRIDWIDTH 42
//#define GRIDHEIGHT 26
typedef vector<HString> InputRow;
typedef vector<InputRow> InputVec;

class UICORE_DLL_API HCKeyBoard : public HCBaseCtrl  
{
public:
	HCKeyBoard();
	virtual ~HCKeyBoard();

	// 消息处理函数
	virtual HBOOL DoMessage(HMessage* msg);
	// 绘制函数
	virtual void Draw(IReSurface* psurface);
	// 重载Create方法
	virtual HBOOL Create(HINT x, HINT y, HINT w, HINT h);

	/*
	* 函数功能:设置行数和列数
	* 参    数:
	*   iRowNum[IN]:行数
	*   iColNum[IN]:列数
	* 返 回 值:无
	*/
	void SetRCNum(HINT iRowNum, HINT iColNum);
	/*
	* 函数功能:设置每个小格子的宽和高
	* 参    数:
	*   iW[IN]:宽度
	*   iH[IN]:高度
	* 返 回 值:无
	*/
	void SetGridSize(HINT iW, HINT iH);
	/*
	* 函数功能:设置列的偏移量,即从这列开始显示
	* 参    数:
	*   offset[IN]:偏移量
	* 返 回 值:无
	*/
	void SetInputOffset(HINT offset);
	/*
	* 函数功能:判断点中那个小格子(有内容),点击范围必须在该控件范围内
	* 参    数:
	*      iX[IN]:横坐标,相对该组件
	*      iY[IN]:纵坐标,相对该组件
	*   iRow[OUT]:被点中小格子所在的行,-1表示没选中任何小格子
	*   iCol[OUT]:被点中小格子所在的列,-1表示没选中任何小格子
	* 返 回 值:
	*      false:未点中任何(有效)小格子 true:点中某个(有效)小格子
	*/
	HBOOL InnerCheckPoint(HINT iX, HINT iY, HINT &iRow, HINT &iCol);
	/*
	* 函数功能:设置输入控件的显示内容
	* 参    数:
	*      pp[IN]:指向输入控件的显示内容
	* 返 回 值:
	*      无
	*/
	void SetInputContent(HString pp);
	HBOOL HasContent();
// 	void Clear(){vector <InputRow>().swap(m_pPoiContent); };
	void SetKeySurfaceN(IReSurface* psurface);
	void SetKeySurfaceA(IReSurface* psurface);
	void SetKeySurfaceF(IReSurface* psurface);

	void SetKeySurfaceN(const HString& pFileName);
	void SetKeySurfaceA(const HString& pFileName);
	void SetKeySurfaceF(const HString& pFileName);

	void SetAlternation(HINT x,HINT y);
	void SetKeyActive(HINT Row,HINT Col);
	void SetKeyFocus(HINT Row,HINT Col);
	void SetFocus(HBOOL bFocus,HBOOL R2L);
	virtual void SetFocus(HBOOL bFocus);

	void AddStrOut();

	// 计算是否文字需要滚动显示
	void IsNeedRoll();
	void SetDrawNull(HBOOL bDrawNull);
	void GetNoNullIndex(HINT &iRow,HINT &iCol);
	void SetStretch(HBOOL bStretch);
private:
	// 行数
	HINT m_iRowNum;
	// 列数
	HINT m_iColNum;
	// 每个小格子的宽度
	HINT m_iGridWidth;
	// 每个小格子的高度
	HINT m_iGridHeight;
	// 列的偏移量,即从这列开始显示
	HINT m_iOffset;
	// 处于激活状态的小格子的行
	HINT m_iActiveRow;
	// 处于激活状态的小格子的列
	HINT m_iActiveCol;

	// 处于聚焦状态的小格子的行
	HINT m_iFocusRow;
	// 处于聚焦状态的小格子的列
	HINT m_iFocusCol;
	// 存储输入内容
 	InputVec m_pPoiContent;

	// 键盘按钮背景
	IReSurface* m_pKeySurfaceN;
	HBOOL m_bBkgndNRes;
	IReSurface* m_pKeySurfaceA;
	HBOOL m_bBkgndARes;
	IReSurface* m_pKeySurfaceF;
	HBOOL m_bBkgndFRes;


	//键盘按钮间隔
	HINT m_iAlternationX;
	HINT m_iAlternationY;


	//字符串长度超出的宽度
	HINT m_nStrOutSize[100];

	//定时偏移量
	HINT m_nStrOut[100];

	//文字是否越界，要响应定时器消息
	HBOOL m_bOut[100];
	HINT m_iScreenRollFlag;//当前屏幕的keyboard滚动flag
	HBOOL m_bDrawNull;
	HBOOL m_bStretch;//激活图是否扭曲
};

#endif // !defined(AFX_KCPOIINPUT_H__29AD494F_5FEB_4B8C_BCBD_AD65A8F198A5__INCLUDED_)
