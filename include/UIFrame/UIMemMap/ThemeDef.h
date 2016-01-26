/**
* Copyright (C) 2009， 
* All rights reserved.
*
* 文件名称: ThemeDef.h
* 摘    要:
*
* 当前版本: 1.0
* 作    者:  
* 完成日期: 2009-11-18
*
* 修改历史：
* [修改序列]    [修改日期]      [修改者]        [修改内容]
*	1			2009-11-18		 			创建
*	2			2009-12-28		鞠华玮			添加THEME_8到THEME_10,修改可选主题数量THEME_COUNT
*
**/

#pragma once

namespace KMemMap
{
	// 2 begin 修改可选主题数量THEME_COUNT
	#define THEME_COUNT 10 // 主题个数
	// 2 end

	#define THEME_1 _T("HMI\\Com\\bk01.ktc") // 主题1路径
	#define THEME_2 _T("HMI\\Com\\bk02.ktc") // 主题2路径
	#define THEME_3 _T("HMI\\Com\\bk03.ktc") // 主题3路径
	#define THEME_4 _T("HMI\\Com\\bk04.ktc") // 主题4路径
	#define THEME_5 _T("HMI\\Com\\bk05.ktc") // 主题5路径
	#define THEME_6 _T("HMI\\Com\\bk06.ktc") // 主题6路径
	#define THEME_7 _T("HMI\\Com\\bk07.ktc") // 主题7路径
	// 2 begin 添加THEME_8到THEME_10
	#define THEME_8 _T("HMI\\Com\\bk08.ktc") // 主题8路径
	#define THEME_9 _T("HMI\\Com\\bk09.ktc") // 主题9路径
	#define THEME_10 _T("HMI\\Com\\bk10.ktc")// 主题10路径
	// 2 end
}