#pragma once

#include "KCWnd.h"
#include <vector>
#include "Thread.h"
#include "ThreadPool.h"

class CExifRead;

typedef struct tag_JpgInfo_
{
	HString path;			//图片路径
	IReSurface* pBigSurf;	//图片指针
	IReSurface* pSmallSurf;	//图片指针
	HINT width;			//图片原始宽度
	HINT height;			//图片原始高度
	IReSurface* pBigInfoSurf;	//
	IReSurface* pSmallInfoSurf; //
	HString strstyle;     //类型
	HString strdata;      //日期
	HString strname;		//图片名字

	tag_JpgInfo_()
	{
		pBigSurf = NULL;
		pSmallSurf = NULL;
		pBigInfoSurf = NULL;
		pSmallInfoSurf = NULL;
		width = 0;
		height = 0;
	}

	~tag_JpgInfo_()
	{
		Release();
	}

	void Release()
	{
		SAFE_DELETE(pBigSurf);
		SAFE_DELETE(pSmallSurf);
		SAFE_DELETE(pBigInfoSurf);
		SAFE_DELETE(pSmallInfoSurf);
	}
}JpgInfo;

struct kn_point
{
	HINT x;
	HINT y;
};
class u_point
{
	friend class HCImageViewCtrl;
	kn_point *ip;
	size_t use;
	u_point(kn_point *p):ip(p){}
	~u_point(){delete ip;}
};

typedef std::vector<JpgInfo*> IMAGE_VEC;
typedef std::vector<JpgInfo*>::iterator IMAGE_VEC_IT;

typedef std::map<int,int> LOAD_MAP;
typedef std::map<int,int>::iterator LOAD_MAP_IT;

class UICORE_DLL_API HCImageViewCtrl : public HCBaseCtrl  
{
public:
	HCImageViewCtrl();
	~HCImageViewCtrl();

	virtual HBOOL DoMessage(HMessage* msg);
	virtual void Draw(IReSurface* pSurface);
	//设置中间图片的背景以及显示图片的区域
	void SetMidBackground(const HCHAR* path, HINT x, HINT y, HINT width, HINT height);
	//设置其他图片的背景以及显示图片的区域
	void SetOtherBackground(const HCHAR* path, HINT x, HINT y, HINT width, HINT height);
	//设置每个图片的起始位置
	HBOOL SetImageNum(HINT num, kn_point point[]);
	//添加图片
	HBOOL AddPicture(const HCHAR* path);
	//删除指定图片
	HBOOL DelPicture(const HCHAR* path);
	//删除所有图片
	void DelAllPictures();
	// 设置图片点击消息
	void SetCallBackPictureClick(void (*callback)(void*, HString& path), void*);
private:
	// 根据当前设定的宽高和模式，把原始宽高转成需要的宽高
	void GetImageConvertSize(HINT orgWidth, HINT orgHeight, kn_rect& rect, HINT& width, HINT& height);
	void  KCGetFontSur(JpgInfo *pImage);
	//
	void DrawImage(IReSurface* pTarSurf, HINT x, HINT y, HINT pos, HINT imageIndex );
	void DrawMoveImage(IReSurface* pTarSurf,HINT x ,HINT y,HINT imageIndex);
	//
	void DrawImageInfo(IReSurface *pTarSurf,HINT x, HINT y,HINT pos, HINT imageIndex);
	//图片滚动时计算各图片的绘制区域
	void CalcDrawRect( HINT index, HINT srcPos, HINT tarPos, kn_rect& rect);
	//读取文件的类型
	void ReadJpgInfo(JpgInfo *pImage);

	static unsigned int LoadPicture(void* args);
	unsigned int LoadPicture();
	
private:
	IReSurface* m_midBkgSurf;
	IReSurface* m_otherBkgSurf;
	//初始的时候所在的区域
	kn_rect m_rectMidImage; //中间显示图片的矩形区域
	kn_rect m_rectOtherImage;//其他显示图片的矩形区域
	HINT m_imageNum; //界面显示多少张图片
	kn_point* m_point; //界面每个图片的坐标点
//	u_point* m_point;
	HSyncData<IMAGE_VEC> m_image_vec; //存放图片信息的容器
	HINT m_indexImage;//当前绘制的中间图片位置
	HINT m_nMoveNum; //画的次数
	HINT m_nMoveIndex; //中间图片的索引
	HBOOL m_bMouseDown; // 
	HBOOL m_bHaveMove; //
	HBOOL m_bLeftMove;//左移的标志位
	HBOOL m_bRigthMove;//右移的标志位
	kn_point m_pFirstPoint;//保留初始点击的坐标点
	IReSurface* m_pBackupBigSurf; //大的背景图片
	IReSurface* m_pBackupSmallSurf; //
	HINT nMidFontSize; //中间图片字体的宽度
	HINT nOtherFontSize;//其他图片字体的宽度

	CExifRead* m_pExifRead;

	HINT m_nCacheNum; //左右两边需要缓存的图片数目
	Thread m_thread;
	LOAD_MAP m_load_map;
	HINT m_startIndex;
	HBOOL m_bClick;
	HBOOL m_bNeedUpdateWindow;

	//回调类指针
	void* m_pThis;
	//被点击的图片
	JpgInfo* m_pJpgClick;
	//点击中间图片的回调消息
	void (*m_pCallBackPictureClick)(void*, HString& path);
	
};
