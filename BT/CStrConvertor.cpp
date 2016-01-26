#include "CStrConvertor.h"

/**
  *     �ú������ڽ�Unicode����תΪutf8��ʽ!
  * 	@param out   ת������������ָ��
  * 	@param outLength   ת�������������С
  * 	@param in   Դ���������ָ��
  * 	@param inLength   Դ����������С
  * 	@return QINT ת�������Ŀ�Ĵ���ʵ��ʹ�õĳ��ȣ�ת��ʧ���򷵻�-1
  */
int CStrConvertor::UnicodeToUtf8( HBYTE* out, HUINT& outLength,HCHAR* in, HUINT inLength  )
{
	//------------------------------------------------
	//������Ч���ж�
	if(out == NULL || in == NULL || inLength<0)
	{
		return -1;
	}
	HUINT totalNum = 0;
	for(int i = 0; i < inLength; i++)//����ת�����ʵ�����賤��
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
	if( outLength < totalNum )//������Ч���жϣ�
	{
		return -1;
	}
	//------------------------------------------------

    HUINT outsize = 0;//����������������ʵ�ʴ�С��
    HBYTE *tmp = out;
	int i = 0;
    for (i = 0; i < inLength; i++)
    {
		if(outsize>outLength) //�ռ䲻���Ӧ����
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
  * �ú������ڽ�utf8����תΪUnicode��ʽ!
  * Ŀǰ�ú�������ֵΪ��ת����unicode����ռ�õ�wchar_t�ĸ������мǲ�����char�ĸ����� ��
  * 	@param out   ת������������ָ��
  * 	@param outsize   ת�������������С
  * 	@param in   Դ���������ָ��
  * 	@param insize   Դ����������С
  * 	@return QINT ת�������Ŀ�Ĵ��еĳ��ȣ�ת��ʧ���򷵻�-1
  */ 
INT  CStrConvertor::Utf8ToUnicode(HCHAR* out,  HUINT outsize  , HBYTE* in,HUINT insize)
{
	//-------------------------------------------------------------------------------------------
	//������Ч���ж�
	if(out == NULL || in == NULL || insize<0)
	{
		return -1;
	}

	HUINT totalNum = 0;
	HBYTE *p = in;
	for(HUINT i=0;i<insize;i++)
	{
		if (*p >= 0x00 && *p <= 0x7f)//˵�����λΪ'0'������ζ��utf8����ֻ��1���ֽڣ�
		{
			p++;
			totalNum += 1;
		}
		else if ((*p & (0xe0))== 0xc0)//ֻ���������λ���������λ�ǲ���110�����������ζ��utf8������2���ֽڣ�
		{
			p++;
			p++;
			totalNum += 1;
		}
		else if ((*p & (0xf0))== 0xe0)//ֻ���������λ���������λ�ǲ���1110�����������ζ��utf8������3���ֽڣ�
		{
			p++;
			p++;
			p++;
			totalNum += 1;
		}
	}
	if( outsize < totalNum )//������Ч���жϣ�
	{
		return -1;
	}
	//------------------------------------------------
		int resultsize = 0;

		p = in;
		HCHAR* tmp = (HCHAR *)out;
		while(*p)
		{
			if (*p >= 0x00 && *p <= 0x7f)//˵�����λΪ'0'������ζ��utf8����ֻ��1���ֽڣ�
			{
				*tmp = *p;
				tmp++;
				//*tmp = '/0';
				tmp++;
				resultsize += 1;
			}
			else if ((*p & 0xe0)== 0xc0)//ֻ���������λ���������λ�ǲ���110�����������ζ��utf8������2���ֽڣ�
			{
//				wchar_t t = 0;
				HCHAR t1 = 0;
				HCHAR t2 = 0;

				t1 = *p & (0x1f);//��λ�ĺ�5λ����ȥ����ͷ����110�����־λ��
				p++;
				t2 = *p & (0x3f);//��λ�ĺ�6λ����ȥ����ͷ����10�����־λ��

				*tmp = t2 | ((t1 & (0x03)) << 6);
				tmp++;
				*tmp = t1 >> 2;//�����䱣������λ
				tmp++;
				resultsize += 1;
			}
			else if ((*p & (0xf0))== 0xe0)//ֻ���������λ���������λ�ǲ���1110�����������ζ��utf8������3���ֽڣ�
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
		/*�����ǽ����������������򿪴˶Σ�
		*tmp = '/0';
		tmp++;
		*tmp = '/0';
		resultsize += 2;
		*/
		return resultsize;
}
