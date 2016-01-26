

#include "KCListItemBase.h"
#include <map>

#include "Thread.h"
#include "ThreadPool.h"
class CExifRead;


struct sPicture
{
	HString path;		//图片路径
	IReSurface* pSurf;	//图片指针
	HINT width;		//图片原始宽度
	HINT height;		//图片原始高度
	HBOOL bThumbNail; //存储的图片是从缩略图得到的
	sPicture()
	{
		pSurf = NULL;
		width = 0;
		height = 0;
		bThumbNail = false;
	}

	~sPicture()
	{
		SAFE_DELETE(pSurf);
	}

	void Release()
	{
		SAFE_DELETE(pSurf);
	}
};

enum ePictureMode
{
	KeepRatio,		//维持纵横比，图片小于设置大小时维持原状不放大
	KeepRatioZoom,	//图片小于设置大小时进行放大
	Center,			//只显示正中间的部分,要求图片的设置高宽相同
};

typedef std::vector<sPicture*> PICTURE_VEC;
typedef std::vector<sPicture*>::iterator PICTURE_VEC_IT;

typedef std::map<int,int> LOAD_MAP;
typedef std::map<int,int>::iterator LOAD_MAP_IT;

class UICORE_DLL_API HCPictureListItem : public HCListItemBase
{
public:
	HCPictureListItem();
	~HCPictureListItem();

	void Create(HINT width, HINT height);

	virtual void Draw(IReSurface* pSurface, HINT x, HINT y, HINT width, HINT height, HINT xSrc, HINT ySrc);
	virtual HBOOL DoMessage(HMessage* msg);

	//设置文本
	void SetText(HString& text){};
	void SetText(const HCHAR* pTxt){};

	// 设置图片间列距和行距
	void SetSpace(HINT column, HINT row);
	// 设置边距
	void SetMargin(HINT left, HINT right, HINT top, HINT bottom);
	// 设置图片大小
	void SetPictureSize(HINT width, HINT height);
	// 设置图片显示模式
	HBOOL SetPictureMode(ePictureMode mode);

	// 添加图片，内部转成相应大小
	HBOOL AddPicture(const HCHAR* path);
	// 删除图片
	HBOOL DelPicture(HCHAR* path);
	// 删除所有图片
	void DelAllPictures();
	// 设置图片点击消息
	void SetCallBackPictureClick(void (*callback)(void*, HString& path), void*);

	// 外部用，把传入的图片转成满足显示需要的图片, 会改变指针的值
	void ConvertPicture(IReSurface*& pSurface);

	void SetFather(HCScrollBox* pScrollBox);
private:
	//计算有多少列、多少行
	void CalcColumnRowNum();

	// 把输入的结构转成相应的结构, 要保证其中的pSurf为整张图
	void ConvertPicture(sPicture* pPicture);
	// 图片大小或显示模式变化时转化图片大小, mode为0时宽高变化，为1时PictureMode变化
	void ConvertPictures(HINT mode, ePictureMode pictureMode);
	
	// 根据当前设定的宽高和模式，把原始宽高转成需要的宽高
	void GetPictureConvertSize(HINT orgWidth, HINT orgHeight, HINT& width, HINT& height);

	static unsigned int LoadPicture(void* args);
	unsigned int LoadPicture();

private:
	HINT m_rowSpace;//行距
	HINT m_columnSpace;//列距

	HINT m_leftMargin;//左边距
	HINT m_rightMargin;//右边距
	HINT m_topMargin;//上边距
	HINT m_bottomMargin;//下边距

	HINT m_PictureWidth;//图片宽度
	HINT m_PictureHeight;//图片高度

	ePictureMode m_PictureMode;

	HINT m_columnNum;//列数
	HINT m_rowNum;//行数
	HINT m_nNormalShowNum;

	HSyncData<PICTURE_VEC> m_picture_vec;
	//图片点击回调消息
	void (*m_pCallBackPictureClick)(void*, HString& path);
	//回调类指针
	void* m_pThis;

	//绘制的起始偏移
	HINT m_xOffsetDraw;
	HINT m_yOffsetDraw;
	//绘制的区域
	kn_rect m_rectDraw;
	//被点击的图片
	sPicture* m_pPictureClick;

	HINT m_nCacheNum; //左右两边需要缓存的图片数目
	Thread m_thread;
	LOAD_MAP m_load_map;
	HINT m_startIndex;
	HINT m_endIndex;

	HBOOL m_bNeedUpdateWindow;

	CExifRead* m_pExifRead;

	HBOOL m_bMouseDown;
	HINT m_xBackup;
	HINT m_yBackup;
	HINT m_nMouseDownTime;
};