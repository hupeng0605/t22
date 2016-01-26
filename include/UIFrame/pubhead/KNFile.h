#ifndef _KNFILE_H_
#define _KNFILE_H_

// ʹ��KNFileǰ����Read Me��
// KNFile��Ҫ�����ļ���д��Ϊʹ�ļ���д�����ڲ���ϵͳ���ر�д�ļ���д��
// KNFile��Ҫ��������������ȡ����ֵ����ȡһ���ڴ�
// �벻Ҫ�����ض������йصı����������ݶ�ȡ��������������
// �磺Type.h�ж��壬��û�ж���UNICODEʱ:kn_char=char����������UNICODEʱ:kn_char=wchar_t
// �������ʹ����ȷ���ȵı������磺byte,short,long,float,double

// ���ʹ��KNFile�����ļ���ȡ��������ϵͳ�仯������ʵ��KNFile�ĳ�Ա�������ӿڿ��Ա��ֲ���

// This class now can be only used in Win32.

// ���Ҫ����ٶ�,��Read������Ϊ������������.
#include "Platform.h"
#include "Type.h"
#include "Pubhead.h"

#include <cctype>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

#ifndef KN_HMI_LIB
#ifdef UICORE_DLL_EXPORTS
#define UICORE_DLL_API __declspec(dllexport)
#else
#define UICORE_DLL_API __declspec(dllimport)
#endif
#else
#define UICORE_DLL_API
#endif


struct FILEDEC  //�ļ�����ͷ���ṹ
{
    HCHAR strDec[10]; //��������
    HINT iReserve; //�����ֶ�
    FILEDEC()
    {
        memset(strDec, 0, 10);
        iReserve = 0;
    }
};

struct FILEATTRIBUTION //�ļ�����
{
    HULONG ulSize;  //��С�������ļ�ʱ��Ч
    HULONG ulOffset; //���ͷ��ƫ�ƣ������ļ�ʱ��Ч
    FILEATTRIBUTION()
    {
        ulSize = 0;
        ulOffset = 0;
    }
};

//�ļ�Ŀ¼,kn_string�����ļ�������Ϊ�����Ĺؼ���
typedef map<string, FILEATTRIBUTION> MAPFILEINFO;

//�ļ�ͷ���ṹ
struct FILEHEAD
{
    FILEDEC FileDec;   //��������
    string strRoot;     //��Ŀ¼�ַ���
    HUSHORT uiFileNum;   //���ļ�����
    MAPFILEINFO mFileInfo; //�ļ���ͷ��Ϣ�ṹ
    FILEHEAD()
    {
        strRoot = "";
        uiFileNum = 0;
    }
};

struct INDEXINFO  //Ŀ¼��Ϣ
{
    string strDir;  //��Ŀ¼
    HString strComFile; //����ļ��ļ���
    FILEHEAD FileHead; //�ļ�ͷ��Ϣ
    HINT pos; //dataĿ¼�ַ����ȣ�����·���ü�
    INDEXINFO()
    {
        strDir = "";
        strComFile = _T("");
    }
    INDEXINFO(string Dir, HString ComFile)
    {
        strDir = Dir;
        strComFile = ComFile;
    }
    void SetDir(string Dir)
    {
        strDir = Dir;
    }
    void SetComFileName(HString ComFile)
    {
        strComFile = ComFile;
    }
};

typedef vector<INDEXINFO> INDEXINFOLIST;

UICORE_DLL_API HINT ReadHead(HString strFileName, FILEHEAD& FileHead);

// ADD. hzf.2006.11.8.
// --Begin
//lint -e1735 -e1506 -e774 -e1740 -e1763
// --End

#define REVERSE2(x) ((((x)&0xff00)>>8)|(((x)&0x00FF)<<8))
#define REVERSE4(x) ((((x)&0xff000000)>>24)|(((x)&0x00ff0000)>>8)|(((x)&0x0000ff00)<<8)|(((x)&0x000000ff)<<24))

#define KNERR_FILE_ERR -1
#define KNERR_FILE_OK 1

class UICORE_DLL_API HFile
{
public:
    HFile();
    virtual ~HFile();
public:
    HBOOL IsFileOpen() const;

    /*
    * �������ܣ����ļ�
    * ��    ����
    *       strFileName [in] ���ļ���
    *       dwShareMode [in]����ģʽ(share/exclusive)
    *       dwCreationDisposition [in]���ο�API:CreateFile()
    *       dwFlagsAndAttributes [in]���ο�API:CreateFile()
    * �� �� ֵ��������Ϣ
    */
    virtual HLONG OpenFile(const HString& strFileName,
                             HDWORD dwDesiredAccess = GENERIC_READ,
                             HDWORD dwShareMode = FILE_SHARE_READ,
                             HDWORD dwCreationDisposition = OPEN_EXISTING,
                             HDWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_READONLY);

    //
    HBOOL IsFileExist(string strFileName, FILEATTRIBUTION& FileAtt);

    /*
    * �������ܣ��ر��ļ�
    * �� �� ֵ��������Ϣ
    */
    virtual HLONG CloseFile();

    /*
    * �������ܣ���ȡ�ļ����
    * �� �� ֵ���ļ����
    */
    virtual const HANDLE& GetFileHandle() const;

    /*
    * �������ܣ�ȡ���ļ���С(oNLY fOR fUN !)
    * ��    ����
    *       size [in] ���ļ���С
    * �� �� ֵ��������Ϣ
    */
    virtual HLONG GetFilesize(HULONG& ulSize);

    /*
    * �������ܣ��ƶ��ļ������ָ��λ��
    * ��    ����
    *       lOffset [in] ���ƶ���С
    *       dwMoveMethod [in]��0-�ļ�ͷ  1-��ǰλ��  2-�ļ�β
    * �� �� ֵ��������Ϣ
    */
    virtual HLONG Seek(HLONG offset, HDWORD dwMoveMethod);

    /*
    * �������ܣ�ȡ�õ�ǰ�ļ�ָ���λ��
    * �� �� ֵ������ļ���ʼλ�õ�λ��
    */
    virtual HLONG Tell();

    // ����Ҫ�����е�Read()����ʵ��ǰ����m_hFile�ļ�飬������û��д���Ժ�ɲ���
    // if (m_bFileOpen) {...}
    /*
    * �������ܣ���ȡ1/2/4���ֽ�
    * ��    ����
    *       value [in] ������1/2/4���ֽ�����
    * �� �� ֵ��������Ϣ
    */
    virtual HLONG Read(HBYTE& value);   // unsigned char

    virtual HLONG Read(HWORD& value);   // unsigned short

    virtual HLONG Read(HDWORD& value);  // unsigned long

    virtual HLONG ReadReverse(HWORD& value); // ����������С��ת��

    virtual HLONG ReadReverse(HDWORD& value); // ����������С��ת��

    virtual HLONG Read(HSHORT& value);

    virtual HLONG Read(HINT& value);

    virtual HLONG Read(HLONG& value);

    /*
    * �������ܣ���ȡ������
    * ��    ����
    *       value [in] �����������ֵ
    * �� �� ֵ��������Ϣ
    */
    virtual HLONG Read(HFLOAT& value);
    virtual HLONG Read(HDOUBLE& value);

    /*
    * �������ܣ��ӵ�ǰλ�ö�ȡһ���ڴ�
    * ��    ����
    *       pDest [in] ���Ѿ�������ڴ�
    *       size [in]����ȡ�����ݿ�Ĵ�С
    * �� �� ֵ��������Ϣ
    */
    virtual HLONG Read(void * pDest, const HULONG ulSize);

    virtual HLONG Read(void * pBuff, const HULONG ulSizeToRead, HULONG &ulSizeReturn);

    virtual HLONG Write(const void * pBuff, const HULONG ulSize);

protected:
    /*
    * �������ܣ����ļ�
    * ��    ����
    *       strFileName [in] ���ļ���
    *       dwShareMode [in]����ģʽ(share/exclusive)
    *       dwCreationDisposition [in]���ο�API:CreateFile()
    *       dwFlagsAndAttributes [in]���ο�API:CreateFile()
    * �� �� ֵ��������Ϣ
    */
    virtual HLONG OpenNormalFile(const HString& strFileName,
                                   HDWORD dwDesiredAccess = GENERIC_READ,
                                   HDWORD dwShareMode = FILE_SHARE_READ,
                                   HDWORD dwCreationDisposition = OPEN_EXISTING,
                                   HDWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_READONLY);

    //���õ�ǰƫ�ƣ����ڷǴ���ļ�Ϊ0
    virtual void SetOffset(HULONG Offset = 0);

    //���õ�ǰ�ļ���С
    virtual void SetFileSize(HULONG FileSize);

public:
    static INDEXINFOLIST m_IndexInfoList;

private:
    // �Ƿ����һ���ļ�
    HBOOL m_bFileOpen;

    // ��ǰλ��
    HLONG m_lCursor;

    //��ǰ�ļ��ڴ���ļ��е�ƫ��
    HULONG m_ulOffset;

    //��ǰ�ļ���С�����ڴ���ļ���ָ��ǰ�����ļ�����Ĵ�С��������������ļ���С
    HULONG m_ulFileSize;

    // �ļ����
    HANDLE m_hFile;
};

#endif // _KNFILE_H_
