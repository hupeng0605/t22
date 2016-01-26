

#include "KCListItemBase.h"
#include <map>

#include "Thread.h"
#include "ThreadPool.h"
class CExifRead;


struct sPicture
{
	HString path;		//ͼƬ·��
	IReSurface* pSurf;	//ͼƬָ��
	HINT width;		//ͼƬԭʼ���
	HINT height;		//ͼƬԭʼ�߶�
	HBOOL bThumbNail; //�洢��ͼƬ�Ǵ�����ͼ�õ���
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
	KeepRatio,		//ά���ݺ�ȣ�ͼƬС�����ô�Сʱά��ԭ״���Ŵ�
	KeepRatioZoom,	//ͼƬС�����ô�Сʱ���зŴ�
	Center,			//ֻ��ʾ���м�Ĳ���,Ҫ��ͼƬ�����ø߿���ͬ
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

	//�����ı�
	void SetText(HString& text){};
	void SetText(const HCHAR* pTxt){};

	// ����ͼƬ���о���о�
	void SetSpace(HINT column, HINT row);
	// ���ñ߾�
	void SetMargin(HINT left, HINT right, HINT top, HINT bottom);
	// ����ͼƬ��С
	void SetPictureSize(HINT width, HINT height);
	// ����ͼƬ��ʾģʽ
	HBOOL SetPictureMode(ePictureMode mode);

	// ���ͼƬ���ڲ�ת����Ӧ��С
	HBOOL AddPicture(const HCHAR* path);
	// ɾ��ͼƬ
	HBOOL DelPicture(HCHAR* path);
	// ɾ������ͼƬ
	void DelAllPictures();
	// ����ͼƬ�����Ϣ
	void SetCallBackPictureClick(void (*callback)(void*, HString& path), void*);

	// �ⲿ�ã��Ѵ����ͼƬת��������ʾ��Ҫ��ͼƬ, ��ı�ָ���ֵ
	void ConvertPicture(IReSurface*& pSurface);

	void SetFather(HCScrollBox* pScrollBox);
private:
	//�����ж����С�������
	void CalcColumnRowNum();

	// ������Ľṹת����Ӧ�Ľṹ, Ҫ��֤���е�pSurfΪ����ͼ
	void ConvertPicture(sPicture* pPicture);
	// ͼƬ��С����ʾģʽ�仯ʱת��ͼƬ��С, modeΪ0ʱ��߱仯��Ϊ1ʱPictureMode�仯
	void ConvertPictures(HINT mode, ePictureMode pictureMode);
	
	// ���ݵ�ǰ�趨�Ŀ�ߺ�ģʽ����ԭʼ���ת����Ҫ�Ŀ��
	void GetPictureConvertSize(HINT orgWidth, HINT orgHeight, HINT& width, HINT& height);

	static unsigned int LoadPicture(void* args);
	unsigned int LoadPicture();

private:
	HINT m_rowSpace;//�о�
	HINT m_columnSpace;//�о�

	HINT m_leftMargin;//��߾�
	HINT m_rightMargin;//�ұ߾�
	HINT m_topMargin;//�ϱ߾�
	HINT m_bottomMargin;//�±߾�

	HINT m_PictureWidth;//ͼƬ���
	HINT m_PictureHeight;//ͼƬ�߶�

	ePictureMode m_PictureMode;

	HINT m_columnNum;//����
	HINT m_rowNum;//����
	HINT m_nNormalShowNum;

	HSyncData<PICTURE_VEC> m_picture_vec;
	//ͼƬ����ص���Ϣ
	void (*m_pCallBackPictureClick)(void*, HString& path);
	//�ص���ָ��
	void* m_pThis;

	//���Ƶ���ʼƫ��
	HINT m_xOffsetDraw;
	HINT m_yOffsetDraw;
	//���Ƶ�����
	kn_rect m_rectDraw;
	//�������ͼƬ
	sPicture* m_pPictureClick;

	HINT m_nCacheNum; //����������Ҫ�����ͼƬ��Ŀ
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