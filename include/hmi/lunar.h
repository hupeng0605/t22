/*
*  Gregorian Solar Calendar and Chinese Lunar Calendar
*  ũ��; ����; ����; ����; ʱ��; ����; ��֧; ��Ф
*  1900-2100 ����������
*  �������ߣ�webmote 2006-09 �ο��Ի��������е� 1900-2100 ����������,���޸���һ����BUG
*  ���κ����⣬��email�� luo31@yahoo.com.cn
*  �����������ñ��࣬�벻Ҫɾ���˶�ע�ͣ�������
*/
#pragma once
#include "stdafx_public.h"

class CLunar
{
public:
	CLunar(void);
	~CLunar(void);

public:


	//ũ��
	int     m_lYear;    //��Ԫ��4λ����
	int     m_lMonth;   //ũ��������
	int     m_lDay;     //ũ��������
	HString m_cYearName; //��ż����ʾ
	HString m_cWordDay; //���ֱ�ʾ������
	HString m_cMonthSB; //�´� С��
	BOOL    m_isLeap;  //�Ƿ�Ϊũ������?
	//����
	HString m_cYear;   //����, 2������
	HString m_cMonth;  //����, 2������
	HString m_cDay;    //����, 2������
	HString m_cAnimal; //��������

	//����
	HString m_lunarFestival; //ũ������
	HString m_solarFestival; //��������
	HString m_solarTerms;    //����

	BOOL    m_bStrong;       //ǿ���Ľ��� �ż���

	/************************************************************************/
	/* ����ũ������                                                         */
	/************************************************************************/
	//����ũ��
	void Lunar(COleDateTime tmMeas);
private:
	/************************************************************************/
	/* ũ[��]����ʹ�õ�ȫ�ֳ���                                                 */
	/************************************************************************/
	// ��������
	static const int m_lunarInfo[]; //ũ������
	static const HString m_GAN[]; //���
	static const HString m_ZHI[]; //��֧
	static const HString m_Animals[]; //��Ф
	static const HString m_nStr1[]; //���ֵ���������
	static const HString m_nStr2[]; //���ֵ���������

	//ũ������
	static const HString m_lFtv[];

	/************************************************************************/
	/* ��[��]����ʹ�õ�ȫ�ֳ���                                                 */
	/************************************************************************/ 
	static const int m_solarMonth[];    //�µ�����
	static const HString m_solarTerm[];   //��������������
	static const int     m_sTermInfo[]; //������������Ϣ
	static const HString m_monthName[]; //�µ�Ӣ������

	//�������� *��ʾ�ż���
	static const HString m_sFtv[];
	//ĳ�µĵڼ������ڼ��� 5,6,7,8 ��ʾ������ 1,2,3,4 �����ڼ�
	static const HString m_wFtv[];

	//���ʱ��
	COleDateTime  m_tmMeas; //�������


private:

	//����ũ�� y���������
	int getYearDays(int y);
	//����ũ�� y�����µ�����
	int getLeapDays(int y);
	//����ũ�� y�����ĸ��� 1-12 , û�򷵻� 0
	int getLeapMonth(int y);
	//����ũ�� y��m�µ�������
	int getMonthDays(int y,int m);

	//ĳ��ĵ�n������Ϊ����(��0С������)
	int getSTerm(int y,int n);
	//�õ�ũ���������
	HString getWordDay(int d);
	//�õ���ż��� ����
	// HString getYearName(int y);

	//�õ���֧����
	HString getGZ(LONGLONG num);
	//�ӽ����ַ�����������֣�������*
	void parseFtv(HString strInfo,int& nFirst,int& nLast,HString& strDesc,BOOL& bStrong);

	//�õ�����Ϊ���µĵڼ���
	int getWeekOfMonth(int y,int m,int d);

	//�õ������м���
	int getWeeksOfMonth(int y,int m);

	//����ָ������� UTCʱ������ 100ns ��
	LONGLONG getUTC(int nYear,
		int nMonth,
		int nDay,
		int nHour=0,
		int nMin=0,
		int nSec=0);

};
