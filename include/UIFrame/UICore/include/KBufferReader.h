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

// 	 功能：从缓冲区中读取一个long型的值
// 	 参数：
// 			value  [out]: 存储从缓冲区中读取的值
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

// 	 函数功能： 设置数据缓冲区
// 	 参数：
// 			*pBuf [in] ：数据缓冲区
// 	 返回值：本函数无返回值
	void SetBufferPointer(const HBYTE* pBuf);

// 	 函数功能： 取得数据缓冲区指针
// 	 参数：
// 			*pBuf [in] ：数据缓冲区
// 	 返回值：缓冲区指针
	const HBYTE* & GetBufferPointer();

// 	 函数功能： 设置当前游标位置
// 	 参数：
// 			lCur [in] ：游标绝对或相对位置
// 			bFlag [in] ：表示参数lCur是相对位置还是绝对位置，其默认值FALSE，表示绝对位置
// 	 返回值：本函数无返回值
	void SetCursor(const HLONG cur , HBOOL bFlag = FALSE);

// 	 功能： 返回当前游标位置，可用于统计读取的字节数
	const HLONG& GetCursor() const;

private:


	// 指向数据缓冲区的指针
	const HBYTE* m_pBuf;
	
	// 记录偏移位置的游标
	HLONG m_lCursor;
	HUINT m_uiSize;
};

#endif // KBUFFERREADER_H__
