

#ifndef __SRC_LEVER_H__
#define __SRC_LEVER_H__

#pragma once
#include "stdafx.h"
#include "define_public.h"
/*
Դ�Ķ��� 
		���8λ��ʱ����
        1<<23������24λΪ1��ʾԴΪ��פԴ������Ϊ��ͨԴ
		 <<16����ʾԴ��lever�ȼ������ȼ���
		 <<8 ����ʾԴ���ڵĻ���
		 ���8λ��ʾԴ�Ľ���ID
*/
//��ʱû�ж����Դ�Ľ���ID��
//��ģ�鶨�����Ժ���Ҫȥ������Ķ���
#if 0
#define  IPC_ID_DISC	 8		//DISC����ID
#define  IPC_ID_DVBT	 9		//CMMB���ֵ��ӽ���ID
#define  IPC_ID_CAMERA   10		//Camera����ID
#define	 IPC_ID_TPMS	 11		//TPMS����ID
#define  IPC_ID_NAVI	 12		//��������ID
#define  IPC_ID_IPOD	 13		//IPOD����ID
#define	 IPC_ID_AVIN	 14		//AUXIN����ID
#endif

typedef unsigned int SRCTYPE;
//MENUԴ����פ
const SRCTYPE SRC_MENU     =     (1<<23) + (4<<16) +					   IPC_ID_MENU;
//RadioԴ
const SRCTYPE SRC_RADIO    =											   IPC_ID_RADIO;
//USBSDԴ, 
//	0 -- USB����
//  1 -- SD����
const SRCTYPE SRC_USB      =			   (2<<16) +					   IPC_ID_USBSD;
const SRCTYPE SRC_SD       =			   (2<<16) +			 (1<<8) +  IPC_ID_USBSD;
//BTԴ����פ
//  1 -- BT��������
//  2 -- BTͨ������
//	3 -- BT���Ż���
//	4 -- BT��Ի���
//  <<12��  1 �����BTADIO���棬��������������
//			0 û��������������
const SRCTYPE SRC_BT_AUDIO  =	 (1<<23) +/* (5<<16) + (1<<12) + */(1<<8) + IPC_ID_BT;
const SRCTYPE SRC_BT_TALK   =	 (1<<23) +   (8<<16)			 + (2<<8) + IPC_ID_BT;
const SRCTYPE SRC_BT_CALL   =    (1<<23) +/*   (8<<16)	*/		 + (3<<8) + IPC_ID_BT;
const SRCTYPE SRC_BT_PAIR   =    (1<<23) +/*   (8<<16)	*/		 + (4<<8) + IPC_ID_BT;
//SETUPԴ����פ
//  1 -- setup�������û���
//  2 -- setup�������û���
const SRCTYPE SRC_SETUPSOUND =	 (1<<23) +	(3<<16) +			   (1<<8) + IPC_ID_SETUP;
const SRCTYPE SRC_SETUP		 =	 (1<<23) +	(3<<16) +		       (2<<8) + IPC_ID_SETUP;
//DISCԴ
const SRCTYPE SRC_DISC		 =				(2<<16) +						IPC_ID_DISC;
//CMMBԴ
//��ʱ��CMMB��CAMERA�����������ͬ�Ľ���
const SRCTYPE SRC_DVBT		 =				(2<<16) +					    IPC_ID_DVBT;
//CameraԴ����פ
const SRCTYPE SRC_CAMERA	 =	 (1<<23) + (10<<16) +						IPC_ID_CAMERA;
//��ʱ�����ֶ�����caneraԴ�����Բ��ö���
//const SRCTYPE SRC_CAMERA_NORMAL = (1<<23) + (3<<16) + 10;//IPC_ID_CAMERA;


//TPMS̽ѹ���Դ����פ
//  1 -- TPMS�ֶ����û���
//  2 -- TPMS���滭��
//  3 -- TPMS��ͨ���棬��MENU����Ļ���
const SRCTYPE SRC_TPMS_SET	 =	 (1<<23) + /*(3<<16) +*/		 (1<<8) +  IPC_ID_TPMS;
const SRCTYPE SRC_TPMS_ALARM =	 (1<<23) + (9<<16) +			 (2<<8) +  IPC_ID_TPMS;
const SRCTYPE SRC_TPMS_NORMAL=	 (1<<23) + /*(3<<16) +*/		 (3<<8) +  IPC_ID_TPMS;
//NAVIԴ����פ
const SRCTYPE SRC_NAVI		 =	 (1<<23) + (7<<16) +					   IPC_ID_NAVI;
//TSERICESԴ�� ��פ
//const SRCTYPE SRC_TSERVICES  =	 (1<<23) +/* (2<<16) +*/				   IPC_ID_TSERVICES;
//IPODԴ
const SRCTYPE SRC_IPOD		 =	 (1<<23) + (2<<16) +				       IPC_ID_IPOD;
//AV-INԴ
const SRCTYPE SRC_AVIN		 =			   (2<<16) +					   IPC_ID_AVIN;


#endif