
#ifndef __STDAFX_PUBLIC_H__
#define __STDAFX_PUBLIC_H__

//#pragma comment(lib,"UICom.lib")
#pragma comment(lib,"UICore.lib")
#pragma comment(lib,"UICoreEx.lib")
//#pragma comment(lib,"UIMemMap.lib")

#pragma comment(lib,"ceipc.lib")
#pragma comment(lib,"utility.lib")

// UI����
#include <Type.h>
#include <Configure.h>
#include <KHMIBaseHead.h>
#include <KProfile.h>
#include <KDialogBase.h>
#include <RenderingEngine.h>
#include <HMIDev.h>
#include <KMemMapAPI.h>
#include <KLock.h>
#include <KCListItem.h>
#include <KCCheckBox.h>
#include <KCScrollBoxEx.h>


// ������
#include <gettext.h>
// ����ͨѶ
#include "../CEIPC/ceipc.h"


// ����ͷ�ļ�
#include "define_public.h"
#include "utility_public.h"
#include "../CEIPC/ipc_user_event.h"
#include "DialogP.h"


using namespace std;
using namespace GETTEXT;
using namespace CEIPC;
using namespace UTILITY;

#endif	/*__STDAFX_PUBLIC_H__*/