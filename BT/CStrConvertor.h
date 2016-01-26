#include"define.h"
class CStrConvertor
{
public:                                  
	static int UnicodeToUtf8(HBYTE* cBuf, HUINT& iCBuf,HCHAR* uBuf, HUINT iUBuf);
	static int Utf8ToUnicode(HCHAR* pDst,  HUINT nDstLen , HBYTE* pSrc,HUINT nSrcLen);
};
