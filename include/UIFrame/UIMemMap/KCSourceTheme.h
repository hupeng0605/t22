/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: KCSourceTheme.h
* 摘    要: 
*
* 当前版本: 1.0
* 作    者:   
* 完成日期: 2010-04-26
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]    [修改内容]
*   1           2010-04-26        		创建
*
**/


#pragma once

#include <RenderingEngine.h>
#include "IMemDispatch.h"


#ifndef MEMMAP_API
#error "Please include KMemMapAPI.h replace this head file, Have question to email:xiongzhens@dev.kotei.co"
#endif

namespace KMemMap
{
    //***************************************************************
    // *  功　　能: 
    // *  作　　者:   
    // *  日　　期: 2010-04-26
    //***************************************************************
    class CYPRESS_DLL_API HCSourceTheme
	{
	private:
        HCSourceTheme(/*IN kn_bool isClient*/);
        ~HCSourceTheme();
        HCSourceTheme(const KCMemoryMap&);// 故意不实现

	public:
		static HCSourceTheme* GetInstance(/*IN kn_bool isClient*/);
		static void ExitInstance();

        // 设置源的数据到共享内存中
        HBOOL SetSourceTheme(IN const HString& strSourceName,IN IReSurface* pSurface);
        // 从共享内存中获取源的数据
        HBYTE* GetSourceTheme(IN const HString& strSourceName,OUT HDWORD& width, OUT HDWORD& height, OUT HLONG& nSize);

	private:
		//IMemDispatch* GetMemFromString(const kn_string& strSoureName);
		//IMemDispatch* GetMemTypeFromString(const kn_string& strSoureName);
    private:
        IMemDispatch* m_pRadioMemory;
		/*IMemDispatch* m_pDiscAudioMemory;
		IMemDispatch* m_piPodAudioMemory;
		IMemDispatch* m_pSiriusMemory;
		IMemDispatch* m_pUSBAudioMemory;
		IMemDispatch* m_pBTAudioMemory;
		IMemDispatch* m_pDiscVideoMemory;
		IMemDispatch* m_piPodVideoMemory;
		IMemDispatch* m_pUSBVideoMemory;
		IMemDispatch* m_pFrontAux1Memory;
		IMemDispatch* m_pFrontAux2Memory;
		IMemDispatch* m_pDVBTMemory;
		IMemDispatch* m_pNaviMemory;
		IMemDispatch* m_pTelMemory;
		IMemDispatch* m_pCameraMemory;
		IMemDispatch* m_pRearDiscVideoMemory;
		IMemDispatch* m_pReariPodVideoMemory;
		IMemDispatch* m_pRearAux1Memory;
		IMemDispatch* m_pRearAux2Memory;*/
		//IMemDispatch* m_pRadioMemory;
		//map<kn_string,IMemDispatch*>	m_mapSourceMem;
		static HCSourceTheme* m_pInstance;
		//kn_bool m_bIsClient;
		//static KCSourceTheme* m_pClientInstance;
		//static KCSourceTheme* m_pServerInstance;
    };
}