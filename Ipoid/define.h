#pragma once
#include <Windows.h>
#include <tchar.h>
#include "stdafx_public.h"
#include "define_public.h"
#include "KCListItem.h"
#include "KCScrollCtrl.h"
#include "KCClockCtrlEx.h"
#include <iostream>
#include <fstream>
#include <list>
#include<string>
#include<utility>
#include<vector>
#include "IpodCore.h"
using namespace std;
struct sLangue
{
	HCHAR szContent[50][50];
};
struct sPlayTime
{
	unsigned long nPostionTime;
	unsigned long nTotalTime;
};
struct sSongInfo
{
	unsigned long nIndex;
	unsigned long nTotal;
	WCHAR szTitle[150];
	WCHAR szArtist[150];
	WCHAR szAlbum[150];
};
#define  TESTIPODBACKGGROUND 0
#define  TESTIPODINSERTEVENT 1
#define  GETARTUSTPICDELAYTIME 300 //3秒获取图片延时时间
#define  TESTIPODLIST 0//列表开关
#define  ICONGAP  20

