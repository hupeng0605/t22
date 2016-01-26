#ifndef _KNFILE_H_
#define _KNFILE_H_

// 使用KNFile前请先Read Me：
// KNFile主要用于文件读写，为使文件读写独立于操作系统，特编写文件读写类
// KNFile主要功能有两个：读取变量值、读取一块内存
// 请不要将与特定环境有关的变量用于数据读取，否则会引起错误
// 如：Type.h中定义，当没有定义UNICODE时:kn_char=char；当定义了UNICODE时:kn_char=wchar_t
// 这里，必须使用明确长度的变量，如：byte,short,long,float,double

// 最好使用KNFile进行文件读取，当操作系统变化，重新实现KNFile的成员函数，接口可以保持不变

// This class now can be only used in Win32.

// 如果要提高速度,将Read函数改为内联函数试试.
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


struct FILEDEC  //文件声明头部结构
{
    HCHAR strDec[10]; //数据声明
    HINT iReserve; //保留字段
    FILEDEC()
    {
        memset(strDec, 0, 10);
        iReserve = 0;
    }
};

struct FILEATTRIBUTION //文件属性
{
    HULONG ulSize;  //大小，对于文件时有效
    HULONG ulOffset; //相对头部偏移，对于文件时有效
    FILEATTRIBUTION()
    {
        ulSize = 0;
        ulOffset = 0;
    }
};

//文件目录,kn_string保存文件名，作为检索的关键字
typedef map<string, FILEATTRIBUTION> MAPFILEINFO;

//文件头部结构
struct FILEHEAD
{
    FILEDEC FileDec;   //数据声明
    string strRoot;     //根目录字符串
    HUSHORT uiFileNum;   //子文件个数
    MAPFILEINFO mFileInfo; //文件的头信息结构
    FILEHEAD()
    {
        strRoot = "";
        uiFileNum = 0;
    }
};

struct INDEXINFO  //目录信息
{
    string strDir;  //根目录
    HString strComFile; //打包文件文件名
    FILEHEAD FileHead; //文件头信息
    HINT pos; //data目录字符长度，用于路径裁剪
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
    * 函数功能：打开文件
    * 参    数：
    *       strFileName [in] ：文件名
    *       dwShareMode [in]：打开模式(share/exclusive)
    *       dwCreationDisposition [in]：参考API:CreateFile()
    *       dwFlagsAndAttributes [in]：参考API:CreateFile()
    * 返 回 值：错误信息
    */
    virtual HLONG OpenFile(const HString& strFileName,
                             HDWORD dwDesiredAccess = GENERIC_READ,
                             HDWORD dwShareMode = FILE_SHARE_READ,
                             HDWORD dwCreationDisposition = OPEN_EXISTING,
                             HDWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_READONLY);

    //
    HBOOL IsFileExist(string strFileName, FILEATTRIBUTION& FileAtt);

    /*
    * 函数功能：关闭文件
    * 返 回 值：错误信息
    */
    virtual HLONG CloseFile();

    /*
    * 函数功能：获取文件句柄
    * 返 回 值：文件句柄
    */
    virtual const HANDLE& GetFileHandle() const;

    /*
    * 函数功能：取得文件大小(oNLY fOR fUN !)
    * 参    数：
    *       size [in] ：文件大小
    * 返 回 值：错误信息
    */
    virtual HLONG GetFilesize(HULONG& ulSize);

    /*
    * 函数功能：移动文件句柄到指定位置
    * 参    数：
    *       lOffset [in] ：移动大小
    *       dwMoveMethod [in]：0-文件头  1-当前位置  2-文件尾
    * 返 回 值：错误信息
    */
    virtual HLONG Seek(HLONG offset, HDWORD dwMoveMethod);

    /*
    * 函数功能：取得当前文件指针的位置
    * 返 回 值：相对文件起始位置的位置
    */
    virtual HLONG Tell();

    // 本来要在所有的Read()函数实现前进行m_hFile的检查，现在先没有写，以后可补上
    // if (m_bFileOpen) {...}
    /*
    * 函数功能：读取1/2/4个字节
    * 参    数：
    *       value [in] ：保存1/2/4个字节数据
    * 返 回 值：错误信息
    */
    virtual HLONG Read(HBYTE& value);   // unsigned char

    virtual HLONG Read(HWORD& value);   // unsigned short

    virtual HLONG Read(HDWORD& value);  // unsigned long

    virtual HLONG ReadReverse(HWORD& value); // 读出后做大小端转换

    virtual HLONG ReadReverse(HDWORD& value); // 读出后做大小端转换

    virtual HLONG Read(HSHORT& value);

    virtual HLONG Read(HINT& value);

    virtual HLONG Read(HLONG& value);

    /*
    * 函数功能：读取浮点数
    * 参    数：
    *       value [in] ：保存想读的值
    * 返 回 值：错误信息
    */
    virtual HLONG Read(HFLOAT& value);
    virtual HLONG Read(HDOUBLE& value);

    /*
    * 函数功能：从当前位置读取一块内存
    * 参    数：
    *       pDest [in] ：已经申请的内存
    *       size [in]：读取的数据块的大小
    * 返 回 值：错误信息
    */
    virtual HLONG Read(void * pDest, const HULONG ulSize);

    virtual HLONG Read(void * pBuff, const HULONG ulSizeToRead, HULONG &ulSizeReturn);

    virtual HLONG Write(const void * pBuff, const HULONG ulSize);

protected:
    /*
    * 函数功能：打开文件
    * 参    数：
    *       strFileName [in] ：文件名
    *       dwShareMode [in]：打开模式(share/exclusive)
    *       dwCreationDisposition [in]：参考API:CreateFile()
    *       dwFlagsAndAttributes [in]：参考API:CreateFile()
    * 返 回 值：错误信息
    */
    virtual HLONG OpenNormalFile(const HString& strFileName,
                                   HDWORD dwDesiredAccess = GENERIC_READ,
                                   HDWORD dwShareMode = FILE_SHARE_READ,
                                   HDWORD dwCreationDisposition = OPEN_EXISTING,
                                   HDWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_READONLY);

    //设置当前偏移，对于非打包文件为0
    virtual void SetOffset(HULONG Offset = 0);

    //设置当前文件大小
    virtual void SetFileSize(HULONG FileSize);

public:
    static INDEXINFOLIST m_IndexInfoList;

private:
    // 是否打开了一个文件
    HBOOL m_bFileOpen;

    // 当前位置
    HLONG m_lCursor;

    //当前文件在打包文件中的偏移
    HULONG m_ulOffset;

    //当前文件大小，对于打包文件，指当前的子文件自身的大小，不是整个打包文件大小
    HULONG m_ulFileSize;

    // 文件句柄
    HANDLE m_hFile;
};

#endif // _KNFILE_H_
