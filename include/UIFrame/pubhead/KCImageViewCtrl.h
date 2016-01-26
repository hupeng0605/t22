#pragma once

#include "KCWnd.h"
#include <vector>
#include "Thread.h"
#include "ThreadPool.h"

class CExifRead;

typedef struct tag_JpgInfo_
{
	HString path;			//ͼƬ·��
	IReSurface* pBigSurf;	//ͼƬָ��
	IReSurface* pSmallSurf;	//ͼƬָ��
	HINT width;			//ͼƬԭʼ���
	HINT height;			//ͼƬԭʼ�߶�
	IReSurface* pBigInfoSurf;	//
	IReSurface* pSmallInfoSurf; //
	HString strstyle;     //����
	HString strdata;      //����
	HString strname;		//ͼƬ����

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
	//�����м�ͼƬ�ı����Լ���ʾͼƬ������
	void SetMidBackground(const HCHAR* path, HINT x, HINT y, HINT width, HINT height);
	//��������ͼƬ�ı����Լ���ʾͼƬ������
	void SetOtherBackground(const HCHAR* path, HINT x, HINT y, HINT width, HINT height);
	//����ÿ��ͼƬ����ʼλ��
	HBOOL SetImageNum(HINT num, kn_point point[]);
	//���ͼƬ
	HBOOL AddPicture(const HCHAR* path);
	//ɾ��ָ��ͼƬ
	HBOOL DelPicture(const HCHAR* path);
	//ɾ������ͼƬ
	void DelAllPictures();
	// ����ͼƬ�����Ϣ
	void SetCallBackPictureClick(void (*callback)(void*, HString& path), void*);
private:
	// ���ݵ�ǰ�趨�Ŀ�ߺ�ģʽ����ԭʼ���ת����Ҫ�Ŀ��
	void GetImageConvertSize(HINT orgWidth, HINT orgHeight, kn_rect& rect, HINT& width, HINT& height);
	void  KCGetFontSur(JpgInfo *pImage);
	//
	void DrawImage(IReSurface* pTarSurf, HINT x, HINT y, HINT pos, HINT imageIndex );
	void DrawMoveImage(IReSurface* pTarSurf,HINT x ,HINT y,HINT imageIndex);
	//
	void DrawImageInfo(IReSurface *pTarSurf,HINT x, HINT y,HINT pos, HINT imageIndex);
	//ͼƬ����ʱ�����ͼƬ�Ļ�������
	void CalcDrawRect( HINT index, HINT srcPos, HINT tarPos, kn_rect& rect);
	//��ȡ�ļ�������
	void ReadJpgInfo(JpgInfo *pImage);

	static unsigned int LoadPicture(void* args);
	unsigned int LoadPicture();
	
private:
	IReSurface* m_midBkgSurf;
	IReSurface* m_otherBkgSurf;
	//��ʼ��ʱ�����ڵ�����
	kn_rect m_rectMidImage; //�м���ʾͼƬ�ľ�������
	kn_rect m_rectOtherImage;//������ʾͼƬ�ľ�������
	HINT m_imageNum; //������ʾ������ͼƬ
	kn_point* m_point; //����ÿ��ͼƬ�������
//	u_point* m_point;
	HSyncData<IMAGE_VEC> m_image_vec; //���ͼƬ��Ϣ������
	HINT m_indexImage;//��ǰ���Ƶ��м�ͼƬλ��
	HINT m_nMoveNum; //���Ĵ���
	HINT m_nMoveIndex; //�м�ͼƬ������
	HBOOL m_bMouseDown; // 
	HBOOL m_bHaveMove; //
	HBOOL m_bLeftMove;//���Ƶı�־λ
	HBOOL m_bRigthMove;//���Ƶı�־λ
	kn_point m_pFirstPoint;//������ʼ����������
	IReSurface* m_pBackupBigSurf; //��ı���ͼƬ
	IReSurface* m_pBackupSmallSurf; //
	HINT nMidFontSize; //�м�ͼƬ����Ŀ��
	HINT nOtherFontSize;//����ͼƬ����Ŀ��

	CExifRead* m_pExifRead;

	HINT m_nCacheNum; //����������Ҫ�����ͼƬ��Ŀ
	Thread m_thread;
	LOAD_MAP m_load_map;
	HINT m_startIndex;
	HBOOL m_bClick;
	HBOOL m_bNeedUpdateWindow;

	//�ص���ָ��
	void* m_pThis;
	//�������ͼƬ
	JpgInfo* m_pJpgClick;
	//����м�ͼƬ�Ļص���Ϣ
	void (*m_pCallBackPictureClick)(void*, HString& path);
	
};
