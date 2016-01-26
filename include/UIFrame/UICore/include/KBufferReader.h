#ifndef KBUFFERREADER_H__
#define KBUFFERREADER_H__

#include "Pubhead.h"

class KNAPI KBufferReader  
{
public:
	KBufferReader();
	KBufferReader(const HBYTE* pBuf);
	KBufferReader(const HBYTE* pBuf, HDWORD size);
	virtual ~KBufferReader();

public:

// 	 ���ܣ��ӻ������ж�ȡһ��long�͵�ֵ
// 	 ������
// 			value  [out]: �洢�ӻ������ж�ȡ��ֵ
	void Read(HLONG &value);
	void Read(HDWORD &value);
	void Read(HWORD &value);
	void Read(HBYTE &value);
	void Read(CHAR &value);	
	void Read(HINT &value);
	void Read(short &value);

	void ReadReverse(HDWORD &value);
	void ReadReverse(HWORD &value);
	HUINT CopyBuffer(HBYTE* buffer,  HUINT size, HUINT count);

	void Read(HBYTE* _str, const HULONG ulSize);

public:

// 	 �������ܣ� �������ݻ�����
// 	 ������
// 			*pBuf [in] �����ݻ�����
// 	 ����ֵ���������޷���ֵ
	void SetBufferPointer(const HBYTE* pBuf);

// 	 �������ܣ� ȡ�����ݻ�����ָ��
// 	 ������
// 			*pBuf [in] �����ݻ�����
// 	 ����ֵ��������ָ��
	const HBYTE* & GetBufferPointer();

// 	 �������ܣ� ���õ�ǰ�α�λ��
// 	 ������
// 			lCur [in] ���α���Ի����λ��
// 			bFlag [in] ����ʾ����lCur�����λ�û��Ǿ���λ�ã���Ĭ��ֵFALSE����ʾ����λ��
// 	 ����ֵ���������޷���ֵ
	void SetCursor(const HLONG cur , HBOOL bFlag = FALSE);

// 	 ���ܣ� ���ص�ǰ�α�λ�ã�������ͳ�ƶ�ȡ���ֽ���
	const HLONG& GetCursor() const;

private:


	// ָ�����ݻ�������ָ��
	const HBYTE* m_pBuf;
	
	// ��¼ƫ��λ�õ��α�
	HLONG m_lCursor;
	HUINT m_uiSize;
};

#endif // KBUFFERREADER_H__
