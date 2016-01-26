/**
* Copyright (C) 2009�� 
* All rights reserved.
*
* �ļ�����: KCDialSlide.h
* ժ    Ҫ: ���п̶ȵĻ�����
*
* ��ǰ�汾: 1.0
* ��    ��:  
* �������: 2009-12-28
*
* �޸���ʷ��
* [�޸�����]    [�޸�����]      [�޸���]        [�޸�����]
*   1           2009-12-28       			����
*	2           2010-02-11                    			����ݷ�ʽͼƬ������������Ϊʸ������
**/

#ifndef _KCDIALSLIDE_H_
#define _KCDIALSLIDE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KCWnd.h"
#include <vector>
#define PRESETICON 12
// ������ʾ���
enum eDialSlideStyle
{
    eFixedPoint = 0,// ָ���ǹ̶���
    eFixedDial,// �����ǹ̶��ģ����̶̿��ɱ���ͼƬ�ṩ��
};

//***************************************************************
// *  ��������: ���п̶ȵĻ�����
// *  ��������:  
// *  �ա�����: 2009-12-28
//***************************************************************
class CYPRESS_DLL_API HCDialSlide : public HCBaseCtrl
{
public:
    HCDialSlide();
    virtual ~HCDialSlide();

    // �����ؼ�
    HBOOL Create(IN HINT x, IN HINT y, IN HINT width, IN HINT height);

    // ��Ϣ�������������඼Ҫ����
    virtual HBOOL DoMessage(HMessage* msg);
    virtual void Draw(IReSurface* pSurface);

public:
    // =======================���ⲿ�ӿ�========================//

    // ���ó��汳��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
    void SetBkgndN(IN IReSurface* pSur);
    void SetBkgndN(IN const HString& pFileName);

    // ���ÿ̶�ָ��ͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
    void SetBkgndP(IN IReSurface* pSur);
    void SetBkgndP(IN const HString& pFileName);
	// ���ó���Ӱͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
	void SetBkgndNShadow(IN IReSurface* pSur);
	void SetBkgndNShadow(IN const HString& pFileName);

    // ���ÿ�ݷ�ʽͼ, ʹ��ָ�뷽ʽ�����ⲿ�ͷ���Դ��ʹ���ļ���ʽ�����ڲ��ͷ���Դ
    void SetPresetIcon(IN IReSurface* pSur);
    void SetPresetIcon(IN const HString& pFileName);

    // ���ø�ʽ���ַ���
    void SetFormat(IN const HString& strFormat);
    // ���õ�ǰֵ
    void SetValue(IN HFLOAT nValue);
    // ���ÿ̶���������ڿؼ�����
    void SetScaleRect(IN const kn_rect& rect);
    // ��������Χ
    void SetBound(IN HFLOAT nMin, IN HFLOAT nMax);
    // ���õ���С�̶�
    void SetScale(IN HFLOAT nScale);
    // ���ÿؼ���ʾ��ʽ
    void SetVertical(IN HBOOL bVertical);
    // ���÷��
	void SetStyle(IN eDialSlideStyle eStyle);
	// ���ñ�����ɫ 
	void SetScaleColor(const RECOLOR& color); 
	// ============================��ݷ�ʽ�ӿ�
	// ��ӿ�ݷ�ʽ
	void AddShortcut(IN HFLOAT nSacle);
	// ɾ����ݷ�ʽ
	void DeleteShortcut(IN HFLOAT nScale);
	// ��տ�ݷ�ʽ
	void ClearShortcut();
	HINT IsInRect(HINT pix,HINT piy);
	void SetShortcut(IN HFLOAT nSacle,IN HINT index);
	void SetBandKind(HINT band);//����״̬
    // ��ȡ��ʽ���ַ���
    inline HString GetFormat() const
    {
        return m_strFormat;
    }
    // ��ȡ��ǰֵ
    inline HFLOAT GetValue() const
    {
        return m_nValue;
    }
    // ��ȡ��Сֵ
    inline HFLOAT GetMinValue() const
    {
        return m_nMinValue;
    }
    // ��ȡ���ֵ
    inline HFLOAT GetMaxValue() const
    {
        return m_nMaxValue;
    }

    // ��ȡ����С�̶�
    inline HFLOAT GetScale() const
    {
        return m_nScale;
    }

    // ����ֵ�ı�ص�����
    inline void SetCallBackValueChange(void (*callback)(void*, void*), void* pThis)
    {
        m_pCallBackValueChange = callback;
        m_pThisValueChange = pThis;
	}

	// ��������ͷ�ʱ�ص�����
	inline void SetCallBackUp(void (*callback)(void*, void*), void* pThis)
	{
		m_pCallBackUp = callback;
		m_pThisUp = pThis;
	}
	inline void SetCallBackPrest(void (*callback)(void *,void*),void*pThis)
	{
		m_pCallBackPreset = callback;
		m_pThis = pThis;
	}

	inline void SetCallBackSameValue(void (*callback)(void *,HINT nindex),void* pThis)
	{
		m_pCallBackSameValue = callback;
		m_pThis = pThis;
	}
private:
    //
    HString formatStr(IN float fValue) const;
    // �жϸ�����ֵ�Ƿ�����Ч��Χ��
    HINT isBound(float fValue) const;
    // ��ȡ���̶̹����ʱ��ÿһ��Ƶ����ռ�õ����ؿ�ȣ���߶ȣ�
    HFLOAT getPixelPreScale() const;
    //
    HINT getSumScaleCount() const ;
    //�������±��̶̿���m_pDialSur���ݣ������»���

protected:
    virtual void UpdateDialSur();
	IReSurface* GetFontSurf(const HCHAR* str);
protected:
	RECOLOR m_ScaleColor;	
    vector<HFLOAT> m_vPreset;// �洢��Ԥ��Ƶ��
    HBOOL m_bAttrChanged;// ����ֵ�Ƿ����ı�
    HFLOAT m_nValue;// ��ǰֵ
    HFLOAT m_nMinValue, m_nMaxValue;// ��Сֵ�����ֵ
    HFLOAT m_nScale;// �̶�
    kn_rect m_rectDial;// ������Ӧ��Ϣ������
    HString m_strFormat;// ���ڸ�ʽ��m_nValue��m_nMinValue��m_nMaxValue���ַ���
    POINT m_nMousePos;// ��갴��ʱ��λ��
    HBOOL m_bMouseDown;//��ʾ����Ƿ���
    IReSurface* m_pDialSur;//  ���̶̿���Surface
    HINT m_nOffset;// ����ϴΣ��˴ο̶��ƶ�λ�ã����̶̹����ʱ��ƫ������ԶΪ�������ʼλ�ã�

    // �ص���������,Ҫ������ָ��
    void (*m_pCallBackValueChange)(void *, void *);
	void (*m_pCallBackSameValue)(void *,HINT nIndex);
	void* m_pThisValueChange;
	void (*m_pCallBackUp)(void *, void *);
	void (*m_pCallBackPreset)(void *, void *);
	HString GetStrNum(HFLOAT Freq);
	void* m_pThisUp;

    HBOOL m_bImageNFromFile;// ����ͼƬ�Ƿ��������ļ�
    IReSurface* m_pImageN;// ����ͼƬ

    HBOOL m_bImagePFromFile;// �̶�ָ��ͼƬ�Ƿ��������ļ�
    IReSurface* m_pImageP;// �̶�ָ��ͼƬ

    HBOOL m_bPresetIconFromFile;// Ԥ��Ƶ��ͼƬ�Ƿ��������ļ�
    IReSurface* m_pPresetIcon;// Ԥ��Ƶ��ͼƬ

    // ===================================����������2009-01-28
    HBOOL m_bVertical;// �Ƿ�ֱ��ʾ����s
	eDialSlideStyle m_eSytle;// ���̷��
	kn_rect m_nPresetrect[PRESETICON];
	IReSurface *m_pBnkNShadow;
	HBOOL m_bmove;
	HINT m_nSpace;
	map<HString,IReSurface*> m_FontCacheSurfMap;
	HINT m_nKind;//Ϊ��ʱΪFM  Ϊ1ʱΪAM
};

#endif
