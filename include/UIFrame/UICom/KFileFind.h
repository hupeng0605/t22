/********************************************************************
created:    2010/01/07
filename:
file path:
file base:  KFileFind
file ext:   h
author:                   

purpose:   �ļ�����
*********************************************************************/
#pragma once
#include "type.h"
#include "Configure.h"
#include "vector"




typedef struct tagFileFind_
{
    // ����·��
    HString strPath;
    // ���ҵ��ļ����ͣ������ԡ�|����Ϊ�ָ���
    HString strFileType;
    // ���ҵ��ļ���
    HString strFileName;
    // ���ҷ�ʽ(�Ƿ�ݹ�)
    HBOOL bIsRecusive;
    tagFileFind_()
    {
        strPath.clear();
        strFileType.clear();
        strFileName.clear();
        bIsRecusive = true;
    }

} FileFind;


// ���Һ�ĵ����ļ���Ϣ
typedef struct tagFileInfo_
{
    // ������չ�����ļ���
    HString strFileName;
    // ��������չ�����ļ���
    HString strFileTitle;
    // �ļ�����ȫ�޶�·��
    HString strFilePath;
    // ����С������ļ���չ��
    HString strFileType;
    // �Ƿ���һ��Ŀ¼��־λ
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

// �ҵ��ļ���Ļص�
typedef void (*FindListCallBack)(void*, FileInfo);


class CYPRESS_DLL_API CKFindFile
{
public:
    CKFindFile(void);
    ~CKFindFile(void);
    // �ҵ��ļ��ص�
    void SetFindListCallBack(FindListCallBack callback, void* pThis);
    // ���ҽ����ص�����
    inline void SetCallBackFindEnd(void (*callback)(void*, void *) , void* pThis)
    {
        m_pCallBackFindEnd = callback;
        m_pThis = pThis;
    }

	HString FindFirstTypeFile(const FileFind& filefind);

    // �����ļ��б�
    void FindFileList(const FileFind& filefind);


	//�ж��ļ��Ƿ����
	HBOOL IsFileExist(HString strFilePath);


	void FindParentFloderFile(const FileFind& filefind);


    // ��ȡ�ļ���
    inline vector <FileInfo>& GetFolderVec()
    {
        return m_strVecFolder;
    }
    // ��ȡ�ļ�
    inline vector <FileInfo>& GetFileVec()
    {
        return m_strVecFile;
    }


private:
    // �����ַ����ָ���
    void ParseFileType(const HString& strFileType);
    // HDD
    void FindFileTypeHDD(const FileFind& filefind);
    // USB\SD
    void FindFileTypeOther(const FileFind& filefind);

    // ����ָ���ļ�
    HBOOL FindFileName(FileFind filefind);

    // ��ȡ��չ��
    HString GetExtend(const HString& strFileName);
	//***************************************************************
// *  ��������: ɾ������ӵ�·��
// *  ��ڲ���:
// *  ���ڲ���:
// *  �� �� ֵ:
// *  ��������:               
// *  �ա�����: 2010-03-12
//***************************************************************
	HString ReturnParentFolderPath(HString strIn);

private:
    // ����ļ���
    vector <FileInfo> m_strVecFolder;
    // ����ļ�
    vector <FileInfo> m_strVecFile;
    // ��Ų������͵�����
    vector <HString> m_strVecFileType;
    FindListCallBack m_pFindListCallBack;
    void (*m_pCallBackFindEnd)(void*, void *);
    void* m_pThis;
	HBOOL m_bISFirstFlag;
	HString m_FirstMediaPath;
};
