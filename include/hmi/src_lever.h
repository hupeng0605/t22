

#ifndef __SRC_LEVER_H__
#define __SRC_LEVER_H__

#pragma once
#include "stdafx.h"
#include "define_public.h"
/*
源的定义 
		最高8位暂时保留
        1<<23，即第24位为1表示源为常驻源，否则为普通源
		 <<16，表示源的lever等级（优先级）
		 <<8 ，表示源所在的画面
		 最后8位表示源的进程ID
*/
//暂时没有定义的源的进程ID，
//等模块定义完以后需要去掉这里的定义
#if 0
#define  IPC_ID_DISC	 8		//DISC进程ID
#define  IPC_ID_DVBT	 9		//CMMB数字电视进程ID
#define  IPC_ID_CAMERA   10		//Camera进程ID
#define	 IPC_ID_TPMS	 11		//TPMS进程ID
#define  IPC_ID_NAVI	 12		//导航进程ID
#define  IPC_ID_IPOD	 13		//IPOD进程ID
#define	 IPC_ID_AVIN	 14		//AUXIN进程ID
#endif

typedef unsigned int SRCTYPE;
//MENU源，常驻
const SRCTYPE SRC_MENU     =     (1<<23) + (4<<16) +					   IPC_ID_MENU;
//Radio源
const SRCTYPE SRC_RADIO    =											   IPC_ID_RADIO;
//USBSD源, 
//	0 -- USB画面
//  1 -- SD画面
const SRCTYPE SRC_USB      =			   (2<<16) +					   IPC_ID_USBSD;
const SRCTYPE SRC_SD       =			   (2<<16) +			 (1<<8) +  IPC_ID_USBSD;
//BT源，常驻
//  1 -- BT其他画面
//  2 -- BT通话画面
//	3 -- BT拨号画面
//	4 -- BT配对画面
//  <<12，  1 进入过BTADIO画面，有蓝牙音乐声音
//			0 没有蓝牙音乐声音
const SRCTYPE SRC_BT_AUDIO  =	 (1<<23) +/* (5<<16) + (1<<12) + */(1<<8) + IPC_ID_BT;
const SRCTYPE SRC_BT_TALK   =	 (1<<23) +   (8<<16)			 + (2<<8) + IPC_ID_BT;
const SRCTYPE SRC_BT_CALL   =    (1<<23) +/*   (8<<16)	*/		 + (3<<8) + IPC_ID_BT;
const SRCTYPE SRC_BT_PAIR   =    (1<<23) +/*   (8<<16)	*/		 + (4<<8) + IPC_ID_BT;
//SETUP源，常驻
//  1 -- setup声音设置画面
//  2 -- setup其他设置画面
const SRCTYPE SRC_SETUPSOUND =	 (1<<23) +	(3<<16) +			   (1<<8) + IPC_ID_SETUP;
const SRCTYPE SRC_SETUP		 =	 (1<<23) +	(3<<16) +		       (2<<8) + IPC_ID_SETUP;
//DISC源
const SRCTYPE SRC_DISC		 =				(2<<16) +						IPC_ID_DISC;
//CMMB源
//暂时将CMMB与CAMERA定义成两个不同的进程
const SRCTYPE SRC_DVBT		 =				(2<<16) +					    IPC_ID_DVBT;
//Camera源，常驻
const SRCTYPE SRC_CAMERA	 =	 (1<<23) + (10<<16) +						IPC_ID_CAMERA;
//暂时不能手动进入canera源，所以不用定义
//const SRCTYPE SRC_CAMERA_NORMAL = (1<<23) + (3<<16) + 10;//IPC_ID_CAMERA;


//TPMS探压检测源，常驻
//  1 -- TPMS手动设置画面
//  2 -- TPMS警告画面
//  3 -- TPMS普通画面，从MENU进入的画面
const SRCTYPE SRC_TPMS_SET	 =	 (1<<23) + /*(3<<16) +*/		 (1<<8) +  IPC_ID_TPMS;
const SRCTYPE SRC_TPMS_ALARM =	 (1<<23) + (9<<16) +			 (2<<8) +  IPC_ID_TPMS;
const SRCTYPE SRC_TPMS_NORMAL=	 (1<<23) + /*(3<<16) +*/		 (3<<8) +  IPC_ID_TPMS;
//NAVI源，常驻
const SRCTYPE SRC_NAVI		 =	 (1<<23) + (7<<16) +					   IPC_ID_NAVI;
//TSERICES源， 常驻
//const SRCTYPE SRC_TSERVICES  =	 (1<<23) +/* (2<<16) +*/				   IPC_ID_TSERVICES;
//IPOD源
const SRCTYPE SRC_IPOD		 =	 (1<<23) + (2<<16) +				       IPC_ID_IPOD;
//AV-IN源
const SRCTYPE SRC_AVIN		 =			   (2<<16) +					   IPC_ID_AVIN;


#endif