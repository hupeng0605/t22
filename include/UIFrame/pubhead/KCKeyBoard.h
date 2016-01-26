
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

	// ��Ϣ������
	virtual HBOOL DoMessage(HMessage* msg);
	// ���ƺ���
	virtual void Draw(IReSurface* psurface);
	// ����Create����
	virtual HBOOL Create(HINT x, HINT y, HINT w, HINT h);

	/*
	* ��������:��������������
	* ��    ��:
	*   iRowNum[IN]:����
	*   iColNum[IN]:����
	* �� �� ֵ:��
	*/
	void SetRCNum(HINT iRowNum, HINT iColNum);
	/*
	* ��������:����ÿ��С���ӵĿ�͸�
	* ��    ��:
	*   iW[IN]:���
	*   iH[IN]:�߶�
	* �� �� ֵ:��
	*/
	void SetGridSize(HINT iW, HINT iH);
	/*
	* ��������:�����е�ƫ����,�������п�ʼ��ʾ
	* ��    ��:
	*   offset[IN]:ƫ����
	* �� �� ֵ:��
	*/
	void SetInputOffset(HINT offset);
	/*
	* ��������:�жϵ����Ǹ�С����(������),�����Χ�����ڸÿؼ���Χ��
	* ��    ��:
	*      iX[IN]:������,��Ը����
	*      iY[IN]:������,��Ը����
	*   iRow[OUT]:������С�������ڵ���,-1��ʾûѡ���κ�С����
	*   iCol[OUT]:������С�������ڵ���,-1��ʾûѡ���κ�С����
	* �� �� ֵ:
	*      false:δ�����κ�(��Ч)С���� true:����ĳ��(��Ч)С����
	*/
	HBOOL InnerCheckPoint(HINT iX, HINT iY, HINT &iRow, HINT &iCol);
	/*
	* ��������:��������ؼ�����ʾ����
	* ��    ��:
	*      pp[IN]:ָ������ؼ�����ʾ����
	* �� �� ֵ:
	*      ��
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

	// �����Ƿ�������Ҫ������ʾ
	void IsNeedRoll();
	void SetDrawNull(HBOOL bDrawNull);
	void GetNoNullIndex(HINT &iRow,HINT &iCol);
	void SetStretch(HBOOL bStretch);
private:
	// ����
	HINT m_iRowNum;
	// ����
	HINT m_iColNum;
	// ÿ��С���ӵĿ��
	HINT m_iGridWidth;
	// ÿ��С���ӵĸ߶�
	HINT m_iGridHeight;
	// �е�ƫ����,�������п�ʼ��ʾ
	HINT m_iOffset;
	// ���ڼ���״̬��С���ӵ���
	HINT m_iActiveRow;
	// ���ڼ���״̬��С���ӵ���
	HINT m_iActiveCol;

	// ���ھ۽�״̬��С���ӵ���
	HINT m_iFocusRow;
	// ���ھ۽�״̬��С���ӵ���
	HINT m_iFocusCol;
	// �洢��������
 	InputVec m_pPoiContent;

	// ���̰�ť����
	IReSurface* m_pKeySurfaceN;
	HBOOL m_bBkgndNRes;
	IReSurface* m_pKeySurfaceA;
	HBOOL m_bBkgndARes;
	IReSurface* m_pKeySurfaceF;
	HBOOL m_bBkgndFRes;


	//���̰�ť���
	HINT m_iAlternationX;
	HINT m_iAlternationY;


	//�ַ������ȳ����Ŀ��
	HINT m_nStrOutSize[100];

	//��ʱƫ����
	HINT m_nStrOut[100];

	//�����Ƿ�Խ�磬Ҫ��Ӧ��ʱ����Ϣ
	HBOOL m_bOut[100];
	HINT m_iScreenRollFlag;//��ǰ��Ļ��keyboard����flag
	HBOOL m_bDrawNull;
	HBOOL m_bStretch;//����ͼ�Ƿ�Ť��
};

#endif // !defined(AFX_KCPOIINPUT_H__29AD494F_5FEB_4B8C_BCBD_AD65A8F198A5__INCLUDED_)
