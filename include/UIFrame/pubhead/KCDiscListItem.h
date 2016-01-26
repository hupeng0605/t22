


#pragma once
#include "KCListItemBase.h"
#include "KCWnd.h"
typedef struct _scroll_ex_data_
{
    HINT nIndex;// 文件索引
    HBOOL bIsFolder;// 标识是否是文件夹
    IReSurface* pIcon;// 文件夹Icon
    HString strTrack;// 轨道名
    HString strArtist;// 艺术家
    HString strAlbum;// 唱片标题

    void clear()
    {
        nIndex = -1;
        bIsFolder = false;
        pIcon = NULL;
        strTrack.clear();
        strArtist.clear();
        strAlbum.clear();
    }
    _scroll_ex_data_()
    {
        clear();
    }
    _scroll_ex_data_& operator=(const _scroll_ex_data_& other)
    {
        this->nIndex = other.nIndex;
        this->bIsFolder = other.bIsFolder;
        this->pIcon = other.pIcon;
        this->strTrack = other.strTrack;
        this->strArtist = other.strArtist;
        this->strAlbum = other.strAlbum;
        return *this;
    }
} SCROLL_EX_ITEM;

class UICORE_DLL_API  HCDiscListItem : public HCListItemBase
{
public:
    HCDiscListItem();
    ~HCDiscListItem();
public:
    void Create(HINT width, HINT height, SCROLL_EX_ITEM *Item);
    //设置当前播放暂停状态的
    void SetBKMidItemIcon(IReSurface *pSurICon);
    SCROLL_EX_ITEM * GetSelectItemContent();

    //释放文本资源、背景副本资源
    void Release();
    void SetFatherWnd(HCWindow* pFatherWnd);
    //设置文本
    void SetText(HString& text);
    void SetText(const HCHAR* pTxt);

    void SetMidIndex(HBOOL bMid);
    HBOOL IsMidIndex();
    HINT GetItemIndex();
    void SetItemContent(SCROLL_EX_ITEM *Item);
    void SetTrackItem(HString strTrack);
    void SetArtistItem(HString strArtist);
    void SetAlbumItem(HString strAlbum);

private:
    virtual void Draw(IReSurface* pSurface, HINT x, HINT y, HINT width, HINT height, HINT xSrc, HINT ySrc);
    virtual HBOOL DoMessage(HMessage* msg);

    inline void DrawItem(IReSurface* pSurface, HINT tarX, HINT tarY, HINT height, const SCROLL_EX_ITEM* pData, HBOOL bMidItem, HBOOL bActive, HINT xSrc, HINT ySrc);

	inline void JudgeFontOver(HCFont* Pfont,HINT FontWidth,HINT FontHeight, 
		                      HString str, HBOOL &bOver, HINT &pos);


private:

    SCROLL_EX_ITEM *m_Item;
    IReSurface *m_pPlayIcon;
    HINT m_nFolderY;

    //控件容器
    KCBASECTRL_VEC m_baseCtrl_vec;

    IReSurface* m_pSurfBackup;

    HBOOL m_bMidIndex;
    HBOOL m_bMidIcon;
    HBOOL m_bCanUpdata;
	HINT m_bPreState;
	HINT m_bNowState;
	IReSurface *m_pSurBornTrack;
	IReSurface *m_pSurCurTrack;
	HBOOL m_bMidOver;
	HINT m_nRollNumber;
	HINT m_nScrollRollNumber;
	HBOOL m_bRoll;
	HINT m_nScrollBaseTime;
	HINT m_nSecondOffset;
	HBOOL m_bSecondOffset;
	HBOOL m_bEnableDrawTrack;

	HString m_strOldTrack;


};