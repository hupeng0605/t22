/********************************************************************
created:    2010/01/07
filename:
file path:
file base:  KFileFind
file ext:   h
author:                   

purpose:   文件查找
*********************************************************************/
#pragma once
#include "type.h"
#include "Configure.h"
#include "vector"




typedef struct tagFileFind_
{
    // 查找路径
    HString strPath;
    // 查找的文件类型，必须以“|”作为分隔符
    HString strFileType;
    // 查找的文件名
    HString strFileName;
    // 查找方式(是否递归)
    HBOOL bIsRecusive;
    tagFileFind_()
    {
        strPath.clear();
        strFileType.clear();
        strFileName.clear();
        bIsRecusive = true;
    }

} FileFind;


// 查找后的到的文件信息
typedef struct tagFileInfo_
{
    // 包含扩展名的文件名
    HString strFileName;
    // 不包含扩展名的文件名
    HString strFileTitle;
    // 文件的完全限定路径
    HString strFilePath;
    // 包含小数点的文件扩展名
    HString strFileType;
    // 是否是一个目录标志位
    HBOOL b_IsDir;

    void clear()
    {
        b_IsDir = false;
        strFileName.clear();
        strFileTitle.clear();
        strFilePath.clear();
        strFileType.clear();
    }
    tagFileInfo_()
    {
        clear();
    }
	tagFileInfo_(const tagFileInfo_& other) 
	{
		strFileName = other.strFileName;
		strFileTitle = other.strFileTitle;
		strFilePath = other.strFilePath;
		strFileType = other.strFileType;
		b_IsDir = other.b_IsDir;
	}
	tagFileInfo_& operator=(const tagFileInfo_& other)
	{
		strFileName = other.strFileName;
		strFileTitle = other.strFileTitle;
		strFilePath = other.strFilePath;
		strFileType = other.strFileType;
		b_IsDir = other.b_IsDir;
		return *this;
	}

} FileInfo;

// 找到文件后的回调
typedef void (*FindListCallBack)(void*, FileInfo);


class CYPRESS_DLL_API CKFindFile
{
public:
    CKFindFile(void);
    ~CKFindFile(void);
    // 找到文件回调
    void SetFindListCallBack(FindListCallBack callback, void* pThis);
    // 查找结束回调函数
    inline void SetCallBackFindEnd(void (*callback)(void*, void *) , void* pThis)
    {
        m_pCallBackFindEnd = callback;
        m_pThis = pThis;
    }

	HString FindFirstTypeFile(const FileFind& filefind);

    // 查找文件列表
    void FindFileList(const FileFind& filefind);


	//判断文件是否存在
	HBOOL IsFileExist(HString strFilePath);


	void FindParentFloderFile(const FileFind& filefind);


    // 获取文件夹
    inline vector <FileInfo>& GetFolderVec()
    {
        return m_strVecFolder;
    }
    // 获取文件
    inline vector <FileInfo>& GetFileVec()
    {
        return m_strVecFile;
    }


private:
    // 解析字符串分隔符
    void ParseFileType(const HString& strFileType);
    // HDD
    void FindFileTypeHDD(const FileFind& filefind);
    // USB\SD
    void FindFileTypeOther(const FileFind& filefind);

    // 查找指定文件
    HBOOL FindFileName(FileFind filefind);

    // 获取扩展名
    HString GetExtend(const HString& strFileName);
	//***************************************************************
// *  功　　能: 删除新添加的路径
// *  入口参数:
// *  出口参数:
// *  返 回 值:
// *  作　　者:               
// *  日　　期: 2010-03-12
//***************************************************************
	HString ReturnParentFolderPath(HString strIn);

private:
    // 存放文件夹
    vector <FileInfo> m_strVecFolder;
    // 存放文件
    vector <FileInfo> m_strVecFile;
    // 存放查找类型的容器
    vector <HString> m_strVecFileType;
    FindListCallBack m_pFindListCallBack;
    void (*m_pCallBackFindEnd)(void*, void *);
    void* m_pThis;
	HBOOL m_bISFirstFlag;
	HString m_FirstMediaPath;
};
