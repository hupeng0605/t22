

#pragma once

#include "kcwnd.h"
#include "vector"
using namespace std;


class HCListItemBase;
class HCScrollCtrl;
typedef vector<HCListItemBase*> LIST_ITEM_VEC;
typedef vector<HCListItemBase*>::iterator LIST_ITEM_VEC_IT;

class UICORE_DLL_API HCScrollBox : public HCBaseCtrl
{
public:
    HCScrollBox();
    ~HCScrollBox();

	friend HCScrollCtrl;
	// 添加项
    HBOOL AddListItem(HCListItemBase* pListItem);
	// 在指定位置插入项
    HBOOL InsertListItem(HINT pos, HCListItemBase* pListItem);
	// 删除某项
    HBOOL DeleteListItem(HCListItemBase* pListItem);
	// 删除所有项
    void DeleteAllListItems();
	// 重新初始化所有变量
	void ReInit();  
    // 返回指定项
    HCListItemBase* GetItemAt(HINT nIndex);
	// 返回当前选中项
    HCListItemBase* GetSelectListItem();
	//返回项数
    HINT GetListItemCount();
	// 返回指定项指针对应的项位置
    HINT GetListItemIndex(HCListItemBase* pListItem);
	// 返回指定项指针在屏幕上的对应位置
    void GetListItemPosition(HCListItemBase* pListItem, HINT& x, HINT& y);
	// 返回所有项的高度和
    HINT GetListItemAllHeight();
	// 是否更新高度信息
    void SetNeedUpdate(HBOOL bNeedUpdate);
	// 返回两个项位置间的高度和
    HINT GetListItemHeight(HINT start, HINT end);
	HINT GetStarIndex();
	HINT GetEndIndex();
    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);

    //设置常规背景图, 使用指针方式设置外部释放资源，使用文件方式设置内部释放资源
    void SetBkgndN(IReSurface* pSurf);
    void SetBkgndN(const HString& pFileName);
	// 设置滑动条背景图片
    void SetSliderBkgSurf(IReSurface* pSurf);
    void SetSliderBkgSurf(const HString& pFileName);
	// 设置滑块图片
    void SetSliderSurf(IReSurface* pSurf,HINT nOffset_Y = 0);
    void SetSliderSurf(const HString& pFileName,HINT nOffset_Y = 0);

	//列表框滚动事件
	void SetCallBackMove(void (*callback)(void*, HBOOL bSrollUp), void*);
	void SetCallBackUp(void (*callback)(void*, void*), void*);
	void SetCallBackMoveUp(void (*callback)(void*, void*), void*);
	void SetCallBackLongUp(void (*callback)(void*, void*), void*);
	// 右移事件
    void SetCallBackMoveRight(void (*callback)(void*, void*), void*);
	// 左移事件
    void SetCallBackMoveLeft(void (*callback)(void*, void*), void*);
	// 点击事件
    void SetCallBackClick(void (*callback)(void*, void*), void*);
	// 长按事件
	void SetCallBackLongPress(void (*callback)(void*, void*), void*);
	//	选中项改变回调
	void SetCallBackSelectItemChange(void (*callback)(void*, void*, void*), void*);
	// 重载父窗口设置
    void SetFatherWnd(HCWindow* pFatherWnd);
	//列表框滚动结束回调
	void SetCallBackScrollEnd(void(*callback)(void*, HBOOL bScrollUp), void*pThis);

	//设置选中项，并使其显示在屏幕内
    void SetSelectListItem(HINT index, HBOOL autoRoll = TRUE);
    void SetSelectListItem(HCListItemBase* pListItem);
	void SetTopIndex(HINT index);

	// 移动当前选中项到列表中间
    void MoveCenterSelectListItem();

	//返回所有项
	LIST_ITEM_VEC& GetListItemVec();
	// 设置长按时间
	void SetLongPressTime(HINT time);

	//返回当前偏移
	HINT GetOffset();

	//返回输入偏移所在项
	HCListItemBase* GetListItemOffset(HINT offset);
	
	//允许自动滚动
	void EnableAutoScroll(HBOOL bEnable);

	//允许滚动
	void EnableMove(HBOOL bEnable);

	//当前列表框是否在滚动状态
	HBOOL IsScroll();

	//滚动条在列表框的右边
	void EnableRightToLeft(HBOOL bEnable);

	//每次移动时都是整行移动，此时要求所有行的高度一样,返回TRUE则设置成功, pSurface为额外添加的一条线
	HBOOL EnableScrollLine(HBOOL bEnable, HINT iLineHeight, IReSurface* pSurface = NULL);

	HBOOL IsScrollLineEnable();

	//设置背景根据项一起滚动
	void EnableBkgSurfScroll(HBOOL bEnable);

	void SetItemSpace(HINT space);

	void EnableLostSelectIndexMove(HBOOL bEnable);

	void EnableFocusButtonDown(HBOOL bEnable);

	//允许第一次长按回调后以times间隔调用长按回调
	void EnableLongPressConsecutive(HBOOL bEnable = TRUE, HINT times = 50);

	//获得当前焦点项，不同于选中项
	HCListItemBase* GetFocusListItem();

	// 获取ScrollBox的每页按钮数
	HINT GetScrollBoxBtnNum(void);
	//
	void EnableSelectItemLongPress(bool bEnable);
	void SetLostFocus();
	// 清除焦点
	void ClearFocus();

	HBOOL IsPointInVisuableArea(HINT x, HINT y);
private:
	void SetFocusListItem(int offset);

private:
	HINT	m_nSlideOffset_Y;
	//根据偏移设定当前选中项
    void SetCurSel(HINT offset);
	
    //常规背景图
    IReSurface* m_pBkgndN;
    HBOOL m_bBkgndNRes;
	// 滑动条背景
    IReSurface* m_pSliderBkgSurf;
    HBOOL m_bSliderBkgSurfRes;
	// 滑块背景
    IReSurface* m_pSliderSurf;
    HBOOL m_bSliderSurfRes;
	// 所在项高度和
    HINT m_allHeight;
	// 是否需要更新
    HBOOL m_bNeedUpdate;
	// 所有项存储容器
    LIST_ITEM_VEC m_listItemVec;
	// 当前选中项指针
    HCListItemBase* m_pSelectItem;
	// 当前显示在屏幕内的项对应的偏移值
    HINT m_allOffset;

    HINT  m_xBackup;//光标按下时位置
    HINT  m_yBackup;
    HINT  m_xOffset;//相对偏移
    HINT  m_yOffset;
// 	HINT  m_xMaxOffset;
// 	HINT  m_yMaxOffset;
// 	HINT  m_xMinOffset;
// 	HINT  m_yMinOffset;
	// 当前是否处于滚动状态
    HBOOL m_bCanMove;//列表框当前是否处于滚动状态

	HBOOL m_bEnableMove;//是否允许列表框滚动
	HBOOL m_bEnableAutoScroll;//是否允许列表框自动滑动

    HINT m_StartTime;//鼠标按下时基准时间
	HINT m_LongPressBaseTime;//长按相应计时
    HBOOL m_bAutoScroll;//自动滑行
	HBOOL m_bAutoScrollBackup;//备份，主要用于指定滚动过程中单击时状态
    HFLOAT m_ScrollSpeed;//滑行速度
    HINT m_ScrollbaseTime;//基准时间，用于计时
    HINT m_SpareNum;//加速的剩余次数

	HBOOL m_bHaveExecuteMove;//已经执行了Move的回调
	void (*m_pCallBackMove)(void *, HBOOL bSrollUp);
    void (*m_pCallBackMoveRight)(void *, void *);
    void (*m_pCallBackMoveLeft)(void *, void *);
    void (*m_pCallBackClick)(void *, void *);
	void (*m_pCallBackUp)(void *,void *);
	void (*m_pCallBackMoveUp)(void *,void *);
	void (*m_pCallBackLongUp)(void *,void *);
	void (*m_pCallBackLongPress)(void *, void *);
	void (*m_pCallBackSelectItemChange)(void*, void*, void*);
	HINT m_longPressTime;// 长按时间
	HBOOL m_bHaveExecuteLongPress;// 事件是否已经响应过了

    HBOOL m_bMoveRight;// 左移右移消息响应了

    HINT m_startListItem;// 当前显示在屏幕内的起始项
    HINT m_endListItem;// 当前显示在屏幕内的结束项
	void* m_pThisScrollEnd;
	HBOOL m_bEnableRightToLeft;//允许从右到左显示滑动条
	void(*m_pCallBackScrollEnd)(void*, HBOOL);

	HBOOL m_bEnableScrollLine;//是否允许整行滚动
	HINT m_nLineHeight;//整行移动的高度
	HINT m_nScrollOffset;//自动滚动时还需要滚动的距离
	HINT m_nOffsetBackup;//用于备份滚动过程中再次点击时的偏移量
	IReSurface* m_pScrollLineSurf;//额外添加的线

	HBOOL m_bEnableBkgSurfScroll;//是否允许背景滚动

	HINT m_nItemSpace;//列表框中每项的间距

	HBOOL m_bEnableLostSelectIndexMove; //在移动列表框时是否允许失去当前选中项的焦点

	HBOOL m_bEnableFocusButtonDown;//鼠标按下时设置聚焦项

	HCListItemBase* m_pFocusItem;// 当前聚焦项指针
	HCListItemBase* m_pOldSelectItem;//前一个选中项的指针
	HBOOL m_bEnableSelectItemLongPress;//是否允许响应选中项的长按事件
	HBOOL m_bHaveSetSelectItem;//定时器中是否已经设置了选中项

	IReSurface* m_pSliderSurfStretch;//进行拉伸后的滑动背景

	HINT m_nTmpStartIndex;
	HINT m_nTmpEndIndex;
	//长按连续响应消息
	HBOOL m_bEnableLongPressConsecutive;
	HINT m_LongPressTimeConsecutive;

	HBOOL m_bCanLongPress;//是否可以响应长按

protected:
	//
	HBOOL m_bMouseDownScroll;
};

