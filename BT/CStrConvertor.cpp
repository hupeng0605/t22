#include "CStrConvertor.h"

/**
  *     该函数用于将Unicode数组转为utf8格式!
  * 	@param out   转换结果存放区域指针
  * 	@param outLength   转换结果存放区域大小
  * 	@param in   源串存放区域指针
  * 	@param inLength   源串存放区域大小
  * 	@return QINT 转换结果在目的串中实际使用的长度，转换失败则返回-1
  */
int CStrConvertor::UnicodeToUtf8( HBYTE* out, HUINT& outLength,HCHAR* in, HUINT inLength  )
{
	//------------------------------------------------
	//参数有效性判断
	if(out == NULL || in == NULL || inLength<0)
	{
		return -1;
	}
	HUINT totalNum = 0;
	for(int i = 0; i < inLength; i++)//计算转换结果实际所需长度
	{
		wchar_t unicode = in[i];
		if (unicode >= 0x0000 && unicode <= 0x007f)
        {
            totalNum += 1;
        }
        else if (unicode >= 0x0080 && unicode <= 0x07ff)
        {
            totalNum += 2;
        }
        else if (unicode >= 0x0800 && unicode <= 0xffff)
        {
            totalNum += 3;
        }
	}
	if( outLength < totalNum )//参数有效性判断！
	{
		return -1;
	}
	//------------------------------------------------

    HUINT outsize = 0;//用来计数输出结果的实际大小！
    HBYTE *tmp = out;
	int i = 0;
    for (i = 0; i < inLength; i++)
    {
		if(outsize>outLength) //空间不足对应处理！
		{
			return -1;
		}
        wchar_t unicode = in[i];
        
        if (unicode >= 0x0000 && unicode <= 0x007f)
        {
            *tmp = (HBYTE )unicode;
            tmp += 1;
            outsize += 1;
        }
        else if (unicode >= 0x0080 && unicode <= 0x07ff)
        {
            *tmp = 0xc0 | (unicode >> 6);
            tmp += 1;
            *tmp = 0x80 | (unicode & (0xff >> 2));
            tmp += 1;
            outsize += 2;
        }
        else if (unicode >= 0x0800 && unicode <= 0xffff)
        {
            *tmp = 0xe0 | (unicode >> 12);
            tmp += 1;
            *tmp = 0x80 | (unicode >> 6 & 0x00ff);
            tmp += 1;
            *tmp = 0x80 | (unicode & (0xff >> 2));
            tmp += 1;
            outsize += 3;
        }
    }
	return outsize;
}

/**
  * 该函数用于将utf8数组转为Unicode格式!
  * 目前该函数返回值为：转换后unicode数据占用的wchar_t的个数（切记不是总char的个数） ！
  * 	@param out   转换结果存放区域指针
  * 	@param outsize   转换结果存放区域大小
  * 	@param in   源串存放区域指针
  * 	@param insize   源串存放区域大小
  * 	@return QINT 转换结果在目的串中的长度，转换失败则返回-1
  */ 
INT  CStrConvertor::Utf8ToUnicode(HCHAR* out,  HUINT outsize  , HBYTE* in,HUINT insize)
{
	//-------------------------------------------------------------------------------------------
	//参数有效性判断
	if(out == NULL || in == NULL || insize<0)
	{
		return -1;
	}

	HUINT totalNum = 0;
	HBYTE *p = in;
	for(HUINT i=0;i<insize;i++)
	{
		if (*p >= 0x00 && *p <= 0x7f)//说明最高位为'0'，这意味着utf8编码只有1个字节！
		{
			p++;
			totalNum += 1;
		}
		else if ((*p & (0xe0))== 0xc0)//只保留最高三位，看最高三位是不是110，如果是则意味着utf8编码有2个字节！
		{
			p++;
			p++;
			totalNum += 1;
		}
		else if ((*p & (0xf0))== 0xe0)//只保留最高四位，看最高三位是不是1110，如果是则意味着utf8编码有3个字节！
		{
			p++;
			p++;
			p++;
			totalNum += 1;
		}
	}
	if( outsize < totalNum )//参数有效性判断！
	{
		return -1;
	}
	//------------------------------------------------
		int resultsize = 0;

		p = in;
		HCHAR* tmp = (HCHAR *)out;
		while(*p)
		{
			if (*p >= 0x00 && *p <= 0x7f)//说明最高位为'0'，这意味着utf8编码只有1个字节！
			{
				*tmp = *p;
				tmp++;
				//*tmp = '/0';
				tmp++;
				resultsize += 1;
			}
			else if ((*p & 0xe0)== 0xc0)//只保留最高三位，看最高三位是不是110，如果是则意味着utf8编码有2个字节！
			{
//				wchar_t t = 0;
				HCHAR t1 = 0;
				HCHAR t2 = 0;

				t1 = *p & (0x1f);//高位的后5位！（去除了头部的110这个标志位）
				p++;
				t2 = *p & (0x3f);//低位的后6位！（去除了头部的10这个标志位）

				*tmp = t2 | ((t1 & (0x03)) << 6);
				tmp++;
				*tmp = t1 >> 2;//留下其保留的三位
				tmp++;
				resultsize += 1;
			}
			else if ((*p & (0xf0))== 0xe0)//只保留最高四位，看最高三位是不是1110，如果是则意味着utf8编码有3个字节！
			{
				//wchar_t t = 0;
				wchar_t t1 = 0;
				wchar_t t2 = 0;
				wchar_t t3 = 0;
				t1 = *p & (0x1f);
				p++;
				t2 = *p & (0x3f);
				p++;
				t3 = *p & (0x3f);

				*tmp = ((t2 & (0x03)) << 6) | t3;
				tmp++;
				*tmp = (t1 << 4) | (t2 >> 2);
				tmp++;
				resultsize += 1;
			}
			p++;
		}
		/*不考虑结束符，如果考虑则打开此段！
		*tmp = '/0';
		tmp++;
		*tmp = '/0';
		resultsize += 2;
		*/
		return resultsize;
}
