//#include "define_public.h"
#pragma once
#include "KCBTDialDialog.h"
#include "KHMIBaseHead.h"
#include "KCBTCommand.h"
#include "KCBTDialogManager.h"
HCBTDialDlg::HCBTDialDlg()
{
	m_pGrpCtrlBTDial = NULL;
	m_pTxtBTDialMiddleBK = NULL;
	m_pTxtDialNumber = NULL;
	m_pTxtCotactName = NULL;
	m_pBtnDial0 = NULL;
	m_pBtnDial1 = NULL;
	m_pBtnDial2 = NULL;
	m_pBtnDial3 = NULL;
	m_pBtnDial4 = NULL;
	m_pBtnDial5 = NULL;
	m_pBtnDial6 = NULL;
	m_pBtnDial7 = NULL;
	m_pBtnDial8 = NULL;
	m_pBtnDial9 = NULL;
	m_pBtnDialWell = NULL;
	m_pBtnDialStar = NULL;
	m_pBtnBTDialDelete = NULL;
	m_pBtnBTDialCall = NULL;
	m_pBtnBTDialHangUp = NULL;
	m_pBtnBTDialCancel = NULL;
   // m_ePreDlgType = eDIALOGT_UNKNOW;
	//m_sDialNum.cDialNum="";
	memset(m_sDialNum.cDialNum,0,sizeof(m_sDialNum.cDialNum));
	m_sDialNum.nCurrentLen=-1;
//	m_pTxtCallState = NULL;
	m_pTxtCallTime = NULL;
	
};

HCBTDialDlg::~HCBTDialDlg()
{
	SAFE_DELETE(m_pBtnBTDialCancel);
	SAFE_DELETE(m_pBtnBTDialHangUp);
	SAFE_DELETE(m_pBtnBTDialCall);
	SAFE_DELETE(m_pBtnBTDialDelete);
	SAFE_DELETE(m_pBtnDialStar);
	SAFE_DELETE(m_pBtnDialWell);
	SAFE_DELETE(m_pBtnDial9);
	SAFE_DELETE(m_pBtnDial8);
	SAFE_DELETE(m_pBtnDial7);
	SAFE_DELETE(m_pBtnDial6);
	SAFE_DELETE(m_pBtnDial5);
	SAFE_DELETE(m_pBtnDial4);
	SAFE_DELETE(m_pBtnDial3);
	SAFE_DELETE(m_pBtnDial2);
	SAFE_DELETE(m_pBtnDial1);
	SAFE_DELETE(m_pBtnDial0);
	SAFE_DELETE(m_pTxtDialNumber);
	SAFE_DELETE(m_pTxtBTDialMiddleBK);
	SAFE_DELETE(m_pTxtCotactName);
	SAFE_DELETE(m_pGrpCtrlBTDial);
};
HINT HCBTDialDlg::OnInit()
{
	HINT nRet = HCBluetoothBaseDlg::OnInit();
	//m_pTxtScreen->SetText(L"蓝牙拨号");
	m_pGrpCtrlBTDial = new HCGroupCtrl;
	if(m_pGrpCtrlBTDial != NULL)
	{
		AddChild(m_pGrpCtrlBTDial);
		m_pGrpCtrlBTDial->SetShow(true);
		//拨号键盘背景
		m_pTxtBTDialMiddleBK = new HCImageCtrl;
		if(m_pTxtBTDialMiddleBK != NULL)
		{
			m_pTxtBTDialMiddleBK->Create(40,68,720,344);
			m_pTxtBTDialMiddleBK->EnableMsg(false);
			m_pGrpCtrlBTDial->AddChild(m_pTxtBTDialMiddleBK);
		}
		//拨号键盘
		m_pBtnDial1 = new HCButton;
		if(m_pBtnDial1 != NULL)
		{
			m_pBtnDial1->Create(52,154,182,60);
			m_pBtnDial1->EnableMsg(true);
			m_pBtnDial1->SetCallBack(OnDialNum1,this);
			m_pGrpCtrlBTDial->AddChild(m_pBtnDial1);
		}
		m_pBtnDial2 = new HCButton;
		if(m_pBtnDial2 != NULL)
		{
			m_pBtnDial2->Create(227,154,182,60);
			m_pBtnDial2->EnableMsg(true);
			m_pBtnDial2->SetCallBack(OnDialNum2,this);
			m_pGrpCtrlBTDial->AddChild(m_pBtnDial2);
		}
		m_pBtnDial3 = new HCButton;
		if(m_pBtnDial3 != NULL)
		{
			m_pBtnDial3->Create(401, 154, 182, 60);
			m_pBtnDial3->EnableMsg(true);
			m_pBtnDial3->SetCallBack(OnDialNum3,this);
			m_pGrpCtrlBTDial->AddChild(m_pBtnDial3);
		}
		m_pBtnBTDialDelete = new HCButton;
		if(m_pBtnBTDialDelete != NULL)
		{
			m_pBtnBTDialDelete->Create(575, 154, 182, 60);
			m_pBtnBTDialDelete->EnableMsg(true);
			m_pBtnBTDialDelete->SetCallBack(OnDialNumDel,this);
			m_pGrpCtrlBTDial->AddChild(m_pBtnBTDialDelete);
		}
		m_pBtnDial4 = new HCButton;
		if(m_pBtnDial4 != NULL)
		{
			m_pBtnDial4->Create(52, 217, 182, 60);
			m_pBtnDial4->EnableMsg(true);
			m_pBtnDial4->SetCallBack(OnDialNum4,this);
			m_pGrpCtrlBTDial->AddChild(m_pBtnDial4);
		}
		m_pBtnDial5 = new HCButton;
		if(m_pBtnDial5 != NULL)
		{
			m_pBtnDial5->Create(227, 217, 182, 60);
			m_pBtnDial5->EnableMsg(true);
			m_pBtnDial5->SetCallBack(OnDialNum5,this);
			m_pGrpCtrlBTDial->AddChild(m_pBtnDial5);
		}
		m_pBtnDial6 = new HCButton;
		if(m_pBtnDial6 != NULL)
		{
			m_pBtnDial6->Create(401, 217, 182, 60);
			m_pBtnDial6->EnableMsg(true);
			m_pBtnDial6->SetCallBack(OnDialNum6,this);
			m_pGrpCtrlBTDial->AddChild(m_pBtnDial6);
		}
		m_pBtnBTDialCall = new HCButton;
		if(m_pBtnBTDialCall != NULL)
		{
			m_pBtnBTDialCall->Create(575, 217, 182, 60);
			m_pBtnBTDialCall->EnableMsg(false);
			m_pBtnBTDialCall->SetCallBack(OnDialNumCall,this);
			m_pGrpCtrlBTDial->AddChild(m_pBtnBTDialCall);
		}
		m_pBtnDial7 = new HCButton;
		if(m_pBtnDial7 != NULL)
		{
			m_pBtnDial7->Create(52, 280, 182, 60);
			m_pBtnDial7->EnableMsg(true);
			m_pBtnDial7->SetCallBack(OnDialNum7,this);
			m_pGrpCtrlBTDial->AddChild(m_pBtnDial7);
		}
		m_pBtnDial8 = new HCButton;
		if(m_pBtnDial8 != NULL)
		{
			m_pBtnDial8->Create(227, 280, 182, 60);
			m_pBtnDial8->EnableMsg(true);
			m_pBtnDial8->SetCallBack(OnDialNum8,this);
			m_pGrpCtrlBTDial->AddChild(m_pBtnDial8);
		}
		m_pBtnDial9 = new HCButton;
		if(m_pBtnDial9 != NULL)
		{
			m_pBtnDial9->Create(401, 280, 182, 60);
			m_pBtnDial9->EnableMsg(true);
			m_pBtnDial9->SetCallBack(OnDialNum9,this);
			m_pGrpCtrlBTDial->AddChild(m_pBtnDial9);
		}
		m_pBtnBTDialHangUp = new HCButton;
		if(m_pBtnBTDialHangUp != NULL)
		{
			m_pBtnBTDialHangUp->Create(575, 280, 182, 60);
			m_pBtnBTDialHangUp->EnableMsg(false);
			m_pBtnBTDialHangUp->SetCallBack(OnDialNumHangUp,this);
			m_pGrpCtrlBTDial->AddChild(m_pBtnBTDialHangUp);
		}
		m_pBtnDialStar = new HCButton;
		if(m_pBtnDialStar != NULL)
		{
			m_pBtnDialStar->Create(52, 343, 182, 60);
			m_pBtnDialStar->EnableMsg(true);
			m_pBtnDialStar->SetCallBack(OnDialNumStar,this);
			m_pGrpCtrlBTDial->AddChild(m_pBtnDialStar);
		}
		m_pBtnDial0 = new HCButton;
		if(m_pBtnDial0 != NULL)
		{
			m_pBtnDial0->Create(227, 343, 182, 60);
			m_pBtnDial0->EnableMsg(true);
			m_pBtnDial0->SetCallBack(OnDialNum0,this);
			m_pBtnDial0->SetCallBackLongPress(OnDialNum0Long,this);
			m_pGrpCtrlBTDial->AddChild(m_pBtnDial0);
		}
		m_pBtnDialWell = new HCButton;
		if(m_pBtnDialWell != NULL)
		{
			m_pBtnDialWell->Create(401, 343, 182, 60);
			m_pBtnDialWell->EnableMsg(true);
			m_pBtnDialWell->SetCallBack(OnDialNumWell,this);
			m_pGrpCtrlBTDial->AddChild(m_pBtnDialWell);
		}
		m_pBtnBTDialCancel = new HCButton;
		if(m_pBtnBTDialCancel != NULL)
		{
			m_pBtnBTDialCancel->Create(575, 343, 182, 60);
			m_pBtnBTDialCancel->EnableMsg(true);
			m_pBtnBTDialCancel->SetCallBack(OnDialNumCancel,this);
			m_pGrpCtrlBTDial->AddChild(m_pBtnBTDialCancel);
		}
		/*m_pTxtCallState = new HCTextCtrl;
		if(m_pTxtCallState != NULL)
		{
			m_pTxtCallState->Create(595,83,150,30);
			m_pTxtCallState->EnableMsg(false);
			m_pTxtCallState->SetFontSize(24,24);
			m_pTxtCallState->SetTextPos(75,15);
			m_pTxtCallState->SetTextStyle(RE_TS_CENTER);
			m_pTxtCallState->SetText(L"拨号中…");
			m_pTxtCallState->SetShow(false);
			m_pGrpCtrlBTDial->AddChild(m_pTxtCallState);
		}*/
		m_pTxtCallTime = new HCTextCtrl;
		if(m_pTxtCallTime != NULL)
		{
			m_pTxtCallTime->Create(575,113,170,30);
			m_pTxtCallTime->EnableMsg(false);
			m_pTxtCallTime->SetFontSize(20,20);
			m_pTxtCallTime->SetTextPos(75,15);
			m_pTxtCallTime->SetTextStyle(RE_TS_CENTER);
			m_pTxtCallTime->SetText(L" ");
			m_pTxtCallTime->SetShow(false);
			m_pGrpCtrlBTDial->AddChild(m_pTxtCallTime);
		}	
		m_pTxtCotactName = new HCTextCtrl;
		if(m_pTxtCotactName != NULL)
		{
			m_pTxtCotactName->Create(575,83,170,30);
			m_pTxtCotactName->EnableMsg(false);
			m_pTxtCotactName->SetFontSize(20,20);
			m_pTxtCotactName->SetTextPos(75,15);
			m_pTxtCotactName->SetTextStyle(RE_TS_CENTER);
			m_pTxtCotactName->SetText(L" ");
			m_pTxtCotactName->SetShow(true);
			m_pGrpCtrlBTDial->AddChild(m_pTxtCotactName);
		}
		//显示所拨号码
		m_pTxtDialNumber = new HCTextCtrl;
		if(m_pTxtDialNumber != NULL)
		{
			m_pTxtDialNumber->Create(56,75,534,76);
			m_pTxtDialNumber->EnableMsg(false);
			m_pTxtDialNumber->SetTextPos(274,38);
			m_pTxtDialNumber->SetTextStyle(RE_TS_CENTER);
			m_pTxtDialNumber->SetFontSize(48,48);
			m_pGrpCtrlBTDial->AddChild(m_pTxtDialNumber);
			memset(m_sDialNum.cDialNum,0,sizeof(m_sDialNum.cDialNum));
			m_sDialNum.nCurrentLen = -1;
			m_sDialNum.cDialNum[eMAXDIALNUMLEN-1] = L'\0';
			m_pTxtDialNumber->SetText(m_sDialNum.cDialNum);
			m_pGrpCtrlBTDial->AddChild(m_pTxtDialNumber);
		}
#if  TESTDAILPROBLEM
		m_pTxtHFPstate = new HCTextCtrl;
		if(m_pTxtHFPstate != NULL)
		{
			m_pTxtHFPstate->Create(0,172,30,30);
			m_pTxtHFPstate->SetFontSize(20,20);
			AddChild(m_pTxtHFPstate);
		}
		m_pTxtA2DPstate = new HCTextCtrl;
		if(m_pTxtA2DPstate != NULL)
		{
			m_pTxtA2DPstate->Create(0,246,30,30);
			m_pTxtA2DPstate->SetFontSize(20,20);
			AddChild(m_pTxtA2DPstate);
		}
		else
#endif
		m_bCleared = false;
		AddTimer(&m_ctCallDuration);
		AddTimer(&m_ctAutoAnswer);
		AddTimer(&m_ctCall);
		AddTimer(&m_ctHangUp);
        m_ctCall.SetCallBack(OnEnableCall,this);
		m_ctCallDuration.SetCallBack(OnCountCallDuration,this);
		m_ctAutoAnswer.SetCallBack(OnAutoAnswer,this);
		m_ctHangUp.SetCallBack(OnReboot,this);
       // SetBTDlgBackGround();
		SETUPSETTING LSetting;
		KCLastMemory::GetInstance()->GetSetupMemory(LSetting);
		BTDEBUGINFO(L"LSetting.cLang = %d",LSetting.cLang);
		switch (LSetting.cLang)
		{
			case 0:
			{
				ChangeLangue(0);
			}
			break;
			case 1:
			{
				ChangeLangue(1);
			}
			break;
			default:
			break;
		}
		//ChangeLangue(0);
	}
	// m_ePreDlgType = eDIALOGT_UNKNOW;
	//memset(m_sDialNum.cDialNum,0,sizeof(m_sDialNum.cDialNum));
	//m_sDialNum.nCurrentLen = -1;
	//m_sDialNum.cDialNum[eMAXDIALNUMLEN-1] = L'\0';
	//m_pTxtDialNumber->SetText(m_sDialNum.cDialNum);
	//HBYTE cCommand  [20] = {0};
	//HUINT nCmdlen = strlen("AT+HFPSTAT\r\n");
	//strncpy((char*)cCommand,"AT+HFPSTAT=",nCmdlen);
//	strncpy((char*)(cCommand+ 8),(char*)CBTCommand::Instance()->GetBTCommandData()->BTGeneralData.arrPairDevice[iSelectIndex].szMacAddress,12);
	//WideCharToMultiByte(CP_OEMCP,NULL,m_sDialNum.cDialNum,m_sDialNum.nCurrentLen,(char*)(cCommand+9),0,NULL,FALSE);
//	cCommand[20] ='\r';
//	cCommand[21] ='\n';
//	cCommand[22] ='\0';
	/*CBTCommand::Instance()->SendData(cCommand,nCmdlen);*/
	m_nVoicePos = 100;
	SetShow(true);
	return nRet;

}
void HCBTDialDlg::ChangeLangue(HINT nType)
{
	HCBluetoothBaseDlg::ChangeLangue(nType);
	//SetLangue(nType);
	if(s_pLan != NULL)
	{
		BTDEBUGINFO(L"HCBTDialDlg::%s,%d",__FUNCTIONW__,nType);
		m_pTxtScreen->SetText(s_pLan[0]);
	}
}

void HCBTDialDlg::OnDialNum0(void *pDlg,void *Param)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	pObj->OnDialNum(pObj,(LPARAM_KEYCODE)KEY_0);
}
void HCBTDialDlg::OnDialNum0Long(void *pDlg,void *Param)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	pObj->OnDialNum(pObj,(LPARAM_KEYCODE)KEY_PLAUS);
}

void HCBTDialDlg::OnDialNum1(void *pDlg,void *Param)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	pObj->OnDialNum(pObj,(LPARAM_KEYCODE)KEY_1);
}

void HCBTDialDlg::OnDialNum2(void *pDlg,void *Param)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	pObj->OnDialNum(pObj,(LPARAM_KEYCODE)KEY_2);
}

void HCBTDialDlg::OnDialNum3(void *pDlg,void *Param)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	pObj->OnDialNum(pObj,(LPARAM_KEYCODE)KEY_3);
}
void HCBTDialDlg::OnDialNum4(void *pDlg,void *Param)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	pObj->OnDialNum(pObj,(LPARAM_KEYCODE)KEY_4);
}
void HCBTDialDlg::OnDialNum5(void *pDlg,void *Param)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	pObj->OnDialNum(pObj,(LPARAM_KEYCODE)KEY_5);
}
void HCBTDialDlg::OnDialNum6(void *pDlg,void *Param)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	pObj->OnDialNum(pObj,(LPARAM_KEYCODE)KEY_6);
}
void HCBTDialDlg::OnDialNum7(void *pDlg,void *Param)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	pObj->OnDialNum(pObj,(LPARAM_KEYCODE)KEY_7);
}
void HCBTDialDlg::OnDialNum8(void *pDlg,void *Param)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	pObj->OnDialNum(pObj,(LPARAM_KEYCODE)KEY_8);
}
void HCBTDialDlg::OnDialNum9(void *pDlg,void *Param)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	pObj->OnDialNum(pObj,(LPARAM_KEYCODE)KEY_9);
}
void HCBTDialDlg::OnDialNumStar(void *pDlg,void *Param)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	pObj->OnDialNum(pObj,(LPARAM_KEYCODE)KEY_STAR);
}
void HCBTDialDlg::OnDialNumWell(void *pDlg,void *Param)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	pObj->OnDialNum(pObj,(LPARAM_KEYCODE)KEY_WELL);
}
void HCBTDialDlg::OnDialNumDel(void *pDlg,void *Param)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	pObj->OnDialNum(pObj,(LPARAM_KEYCODE)KEY_DEL);
}
void HCBTDialDlg::OnDialNumCall(void *pDlg,void *Param)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	pObj->OnDialNum(pObj,(LPARAM_KEYCODE)KEY_CALL);
}
void HCBTDialDlg::OnDialNumHangUp(void *pDlg,void *Param)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	pObj->OnDialNum(pObj,(LPARAM_KEYCODE)KEY_HANGUP);
}
void HCBTDialDlg::OnDialNumCancel(void *pDlg,void *Param)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	pObj->OnDialNum(pObj,(LPARAM_KEYCODE)KEY_CANCEL);
}

void HCBTDialDlg::OnDialNum(void *pDlg,LPARAM_KEYCODE eParam)
{
	HCBTDialDlg *pObj = (HCBTDialDlg*)pDlg;
	sBTCommandData*p = CBTCommand::Instance()->GetBTCommandData();
	//LPARAM_KEYCODE eKeyType = (LPARAM_KEYCODE )Param;
	if(pObj->m_sDialNum.nCurrentLen < (eMAXDIALNUMLEN-1))
		pObj->m_sDialNum.nCurrentLen += 1;
	switch(eParam)
	{
	case KEY_0:
		{
			//if(((p->BTHFPData.nHFPState == 3) || (p->BTHFPData.nHFPState == 4) || (p->BTHFPData.nHFPState == 5) ||(p->BTHFPData.nHFPState == 6)))
			if(p->BTHFPData.nHFPState == 5)
			{
				HBYTE cCommand[50] = {0};
				HUINT nCmdLen = strlen("AT+HFDTMF=0\r\n");
				strncpy((char*)cCommand,"AT+HFDTMF=0\r\n",nCmdLen);
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock = CCommandPool::Intance()->PoolNew();
				if(pBlock != NULL)
				{
					sCommandData* pt = (sCommandData*)(pBlock->Buf);
					memset(pt,0,sizeof(sCommandData));
					memcpy(pt->szCommand,cCommand,nCmdLen);
					pt->nCmdLen = nCmdLen;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdLen);
#endif
			}
				if(pObj->m_sDialNum.nCurrentLen == eMAXDIALNUMLEN- 1)
					pObj->m_sDialNum.nCurrentLen = eMAXDIALNUMLEN - 2;
				pObj->m_sDialNum.cDialNum[pObj->m_sDialNum.nCurrentLen] = L'0';
				pObj->m_pTxtDialNumber->SetText(pObj->m_sDialNum.cDialNum);	
			//pObj->StartCountCallDuration();
		}
		break;

	case KEY_1:
		{
			//if(((p->BTHFPData.nHFPState == 3) || (p->BTHFPData.nHFPState == 4) || (p->BTHFPData.nHFPState == 5) ||(p->BTHFPData.nHFPState == 6)))
			if(p->BTHFPData.nHFPState == 5)
			{
				HBYTE cCommand[50] = {0};
				HUINT nCmdLen = strlen("AT+HFDTMF=1\r\n");
				strncpy((char*)cCommand,"AT+HFDTMF=1\r\n",nCmdLen);
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock = CCommandPool::Intance()->PoolNew();
				if(pBlock != NULL)
				{
					sCommandData* pt = (sCommandData*)(pBlock->Buf);
					memset(pt,0,sizeof(sCommandData));
					memcpy(pt->szCommand,cCommand,nCmdLen);
					pt->nCmdLen = nCmdLen;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdLen);
#endif
			}
				if(pObj->m_sDialNum.nCurrentLen == eMAXDIALNUMLEN- 1)
					pObj->m_sDialNum.nCurrentLen = eMAXDIALNUMLEN - 2;
				pObj->m_sDialNum.cDialNum[pObj->m_sDialNum.nCurrentLen] =L'1';
				pObj->m_pTxtDialNumber->SetText(pObj->m_sDialNum.cDialNum);
		}
		break;
	case KEY_2:
		{
			//if(((p->BTHFPData.nHFPState == 3) || (p->BTHFPData.nHFPState == 4) || (p->BTHFPData.nHFPState == 5) ||(p->BTHFPData.nHFPState == 6)))
			if(p->BTHFPData.nHFPState == 5)
			{
				HBYTE cCommand[50] = {0};
				HUINT nCmdLen = strlen("AT+HFDTMF=2\r\n");
				strncpy((char*)cCommand,"AT+HFDTMF=2\r\n",nCmdLen);
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock = CCommandPool::Intance()->PoolNew();
				if(pBlock != NULL)
				{
					sCommandData* pt = (sCommandData*)(pBlock->Buf);
					memset(pt,0,sizeof(sCommandData));
					memcpy(pt->szCommand,cCommand,nCmdLen);
					pt->nCmdLen = nCmdLen;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdLen);
#endif
			}
			if(pObj->m_sDialNum.nCurrentLen == eMAXDIALNUMLEN- 1)
				pObj->m_sDialNum.nCurrentLen = eMAXDIALNUMLEN - 2;
			pObj->m_sDialNum.cDialNum[pObj->m_sDialNum.nCurrentLen] = L'2';
			pObj->m_pTxtDialNumber->SetText(pObj->m_sDialNum.cDialNum);
		}
		break;
	case KEY_3:
		{
			//if(((p->BTHFPData.nHFPState == 3) || (p->BTHFPData.nHFPState == 4) || (p->BTHFPData.nHFPState == 5) ||(p->BTHFPData.nHFPState == 6)))
			if(p->BTHFPData.nHFPState == 5)
			{
				HBYTE cCommand[50] = {0};
				HUINT nCmdLen = strlen("AT+HFDTMF=3\r\n");
				strncpy((char*)cCommand,"AT+HFDTMF=3\r\n",nCmdLen);
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock = CCommandPool::Intance()->PoolNew();
				if(pBlock != NULL)
				{
					sCommandData* pt = (sCommandData*)(pBlock->Buf);
					memset(pt,0,sizeof(sCommandData));
					memcpy(pt->szCommand,cCommand,nCmdLen);
					pt->nCmdLen = nCmdLen;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdLen);
#endif
			}
			if(pObj->m_sDialNum.nCurrentLen == eMAXDIALNUMLEN- 1)
				pObj->m_sDialNum.nCurrentLen = eMAXDIALNUMLEN - 2;
			pObj->m_sDialNum.cDialNum[pObj->m_sDialNum.nCurrentLen] =L'3';
			pObj->m_pTxtDialNumber->SetText(pObj->m_sDialNum.cDialNum);
		}
		break;
	case KEY_4:
		{
			//if(((p->BTHFPData.nHFPState == 3) || (p->BTHFPData.nHFPState == 4) || (p->BTHFPData.nHFPState == 5) ||(p->BTHFPData.nHFPState == 6)))
			if(p->BTHFPData.nHFPState == 5)
			{
				HBYTE cCommand[50] = {0};
				HUINT nCmdLen = strlen("AT+HFDTMF=4\r\n");
				strncpy((char*)cCommand,"AT+HFDTMF=4\r\n",nCmdLen);
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock = CCommandPool::Intance()->PoolNew();
				if(pBlock != NULL)
				{
					sCommandData* pt = (sCommandData*)(pBlock->Buf);
					memset(pt,0,sizeof(sCommandData));
					memcpy(pt->szCommand,cCommand,nCmdLen);
					pt->nCmdLen = nCmdLen;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdLen);
#endif
			}
			if(pObj->m_sDialNum.nCurrentLen == eMAXDIALNUMLEN- 1)
				pObj->m_sDialNum.nCurrentLen = eMAXDIALNUMLEN - 2;
			pObj->m_sDialNum.cDialNum[pObj->m_sDialNum.nCurrentLen] = L'4';
			pObj->m_pTxtDialNumber->SetText(pObj->m_sDialNum.cDialNum);
		}
		break;
	case KEY_5:
		{	
			//if(((p->BTHFPData.nHFPState == 3) || (p->BTHFPData.nHFPState == 4) || (p->BTHFPData.nHFPState == 5) ||(p->BTHFPData.nHFPState == 6)))
			if(p->BTHFPData.nHFPState == 5)
			{
				HBYTE cCommand[50] = {0};
				HUINT nCmdLen = strlen("AT+HFDTMF=5\r\n");
				strncpy((char*)cCommand,"AT+HFDTMF=5\r\n",nCmdLen);
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock = CCommandPool::Intance()->PoolNew();
				if(pBlock != NULL)
				{
					sCommandData* pt = (sCommandData*)(pBlock->Buf);
					memset(pt,0,sizeof(sCommandData));
					memcpy(pt->szCommand,cCommand,nCmdLen);
					pt->nCmdLen = nCmdLen;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdLen);
#endif
			}
			if(pObj->m_sDialNum.nCurrentLen == eMAXDIALNUMLEN- 1)
			pObj->m_sDialNum.nCurrentLen = eMAXDIALNUMLEN - 2;
		pObj->m_sDialNum.cDialNum[pObj->m_sDialNum.nCurrentLen] = L'5';
		pObj->m_pTxtDialNumber->SetText(pObj->m_sDialNum.cDialNum);
		}
		break;
	case KEY_6:
		{	
			//if(((p->BTHFPData.nHFPState == 3) || (p->BTHFPData.nHFPState == 4) || (p->BTHFPData.nHFPState == 5) ||(p->BTHFPData.nHFPState == 6)))
			if(p->BTHFPData.nHFPState == 5)
			{
				HBYTE cCommand[50] = {0};
				HUINT nCmdLen = strlen("AT+HFDTMF=6\r\n");
				strncpy((char*)cCommand,"AT+HFDTMF=6\r\n",nCmdLen);
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock = CCommandPool::Intance()->PoolNew();
				if(pBlock != NULL)
				{
					sCommandData* pt = (sCommandData*)(pBlock->Buf);
					memset(pt,0,sizeof(sCommandData));
					memcpy(pt->szCommand,cCommand,nCmdLen);
					pt->nCmdLen = nCmdLen;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdLen);
#endif
			}
			if(pObj->m_sDialNum.nCurrentLen == eMAXDIALNUMLEN- 1)
			pObj->m_sDialNum.nCurrentLen = eMAXDIALNUMLEN - 2;
			pObj->m_sDialNum.cDialNum[pObj->m_sDialNum.nCurrentLen] = L'6';
			pObj->m_pTxtDialNumber->SetText(pObj->m_sDialNum.cDialNum);
		}
		break;
	case KEY_7:
		{	
			//if(((p->BTHFPData.nHFPState == 3) || (p->BTHFPData.nHFPState == 4) || (p->BTHFPData.nHFPState == 5) ||(p->BTHFPData.nHFPState == 6)))
			if(p->BTHFPData.nHFPState == 5)
			{
				HBYTE cCommand[50] = {0};
				HUINT nCmdLen = strlen("AT+HFDTMF=7\r\n");
				strncpy((char*)cCommand,"AT+HFDTMF=7\r\n",nCmdLen);
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock = CCommandPool::Intance()->PoolNew();
				if(pBlock != NULL)
				{
					sCommandData* pt = (sCommandData*)(pBlock->Buf);
					memset(pt,0,sizeof(sCommandData));
					memcpy(pt->szCommand,cCommand,nCmdLen);
					pt->nCmdLen = nCmdLen;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdLen);
#endif
			}
			if(pObj->m_sDialNum.nCurrentLen == eMAXDIALNUMLEN- 1)
			pObj->m_sDialNum.nCurrentLen = eMAXDIALNUMLEN - 2;
			pObj->m_sDialNum.cDialNum[pObj->m_sDialNum.nCurrentLen] = L'7';
			pObj->m_pTxtDialNumber->SetText(pObj->m_sDialNum.cDialNum);
		}
		break;
	case KEY_8:
		{	
			//if(((p->BTHFPData.nHFPState == 3) || (p->BTHFPData.nHFPState == 4) || (p->BTHFPData.nHFPState == 5) ||(p->BTHFPData.nHFPState == 6)))
			if(p->BTHFPData.nHFPState == 5)
			{
				HBYTE cCommand[50] = {0};
				HUINT nCmdLen = strlen("AT+HFDTMF=8\r\n");
				strncpy((char*)cCommand,"AT+HFDTMF=8\r\n",nCmdLen);
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock = CCommandPool::Intance()->PoolNew();
				if(pBlock != NULL)
				{
					sCommandData* pt = (sCommandData*)(pBlock->Buf);
					memset(pt,0,sizeof(sCommandData));
					memcpy(pt->szCommand,cCommand,nCmdLen);
					pt->nCmdLen = nCmdLen;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdLen);
#endif
			}
			if(pObj->m_sDialNum.nCurrentLen == eMAXDIALNUMLEN- 1)
			pObj->m_sDialNum.nCurrentLen = eMAXDIALNUMLEN - 2;
			pObj->m_sDialNum.cDialNum[pObj->m_sDialNum.nCurrentLen] = L'8';
			pObj->m_pTxtDialNumber->SetText(pObj->m_sDialNum.cDialNum);
		}
		break;
	case KEY_9:
		{	
			//if(((p->BTHFPData.nHFPState == 3) || (p->BTHFPData.nHFPState == 4) || (p->BTHFPData.nHFPState == 5) ||(p->BTHFPData.nHFPState == 6)))
			if(p->BTHFPData.nHFPState == 5)
			{
				HBYTE cCommand[50] = {0};
				HUINT nCmdLen = strlen("AT+HFDTMF=9\r\n");
				strncpy((char*)cCommand,"AT+HFDTMF=9\r\n",nCmdLen);
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock = CCommandPool::Intance()->PoolNew();
				if(pBlock != NULL)
				{
					sCommandData* pt = (sCommandData*)(pBlock->Buf);
					memset(pt,0,sizeof(sCommandData));
					memcpy(pt->szCommand,cCommand,nCmdLen);
					pt->nCmdLen = nCmdLen;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdLen);
#endif
			}
			if(pObj->m_sDialNum.nCurrentLen == eMAXDIALNUMLEN- 1)
			pObj->m_sDialNum.nCurrentLen = eMAXDIALNUMLEN - 2;
			pObj->m_sDialNum.cDialNum[pObj->m_sDialNum.nCurrentLen] = L'9';
			pObj->m_pTxtDialNumber->SetText(pObj->m_sDialNum.cDialNum);
		}
		break;
	case KEY_STAR:
		{
			//if(((p->BTHFPData.nHFPState == 3) || (p->BTHFPData.nHFPState == 4) || (p->BTHFPData.nHFPState == 5) ||(p->BTHFPData.nHFPState == 6)))
			if(p->BTHFPData.nHFPState == 5)
			{
				HBYTE cCommand[50] = {0};
				HUINT nCmdLen = strlen("AT+HFDTMF=*\r\n");
				strncpy((char*)cCommand,"AT+HFDTMF=*\r\n",nCmdLen);
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock = CCommandPool::Intance()->PoolNew();
				if(pBlock != NULL)
				{
					sCommandData* pt = (sCommandData*)(pBlock->Buf);
					memset(pt,0,sizeof(sCommandData));
					memcpy(pt->szCommand,cCommand,nCmdLen);
					pt->nCmdLen = nCmdLen;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdLen);
#endif
			}
			if(pObj->m_sDialNum.nCurrentLen == eMAXDIALNUMLEN- 1)
				pObj->m_sDialNum.nCurrentLen = eMAXDIALNUMLEN - 2;
			pObj->m_sDialNum.cDialNum[pObj->m_sDialNum.nCurrentLen] = L'*';
			pObj->m_pTxtDialNumber->SetText(pObj->m_sDialNum.cDialNum);
		}
		break;
	case KEY_PLAUS:
		{
			if(p->BTHFPData.nHFPState == 5)
			{
				HBYTE cCommand[50] = {0};
				HUINT nCmdLen = strlen("AT+HFDTMF=+\r\n");
				strncpy((char*)cCommand,"AT+HFDTMF=+\r\n",nCmdLen);
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock = CCommandPool::Intance()->PoolNew();
				if(pBlock != NULL)
				{
					sCommandData* pt = (sCommandData*)(pBlock->Buf);
					memset(pt,0,sizeof(sCommandData));
					memcpy(pt->szCommand,cCommand,nCmdLen);
					pt->nCmdLen = nCmdLen;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdLen);
#endif
			}
			if(pObj->m_sDialNum.nCurrentLen == eMAXDIALNUMLEN- 1)
				pObj->m_sDialNum.nCurrentLen = eMAXDIALNUMLEN - 2;
			pObj->m_sDialNum.cDialNum[pObj->m_sDialNum.nCurrentLen] = L'+';
			pObj->m_pTxtDialNumber->SetText(pObj->m_sDialNum.cDialNum);
		}
		break;
	case KEY_WELL:
		{
			//if(((p->BTHFPData.nHFPState == 3) || (p->BTHFPData.nHFPState == 4) || (p->BTHFPData.nHFPState == 5) ||(p->BTHFPData.nHFPState == 6)))
			if(p->BTHFPData.nHFPState == 5)
			{
				HBYTE cCommand[50] = {0};
				HUINT nCmdLen = strlen("AT+HFDTMF=#\r\n");
				strncpy((char*)cCommand,"AT+HFDTMF=#\r\n",nCmdLen);
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock = CCommandPool::Intance()->PoolNew();
				if(pBlock != NULL)
				{
					sCommandData* pt = (sCommandData*)(pBlock->Buf);
					memset(pt,0,sizeof(sCommandData));
					memcpy(pt->szCommand,cCommand,nCmdLen);
					pt->nCmdLen = nCmdLen;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdLen);
#endif
			}
			if(pObj->m_sDialNum.nCurrentLen == eMAXDIALNUMLEN- 1)
				pObj->m_sDialNum.nCurrentLen = eMAXDIALNUMLEN - 2;
			pObj->m_sDialNum.cDialNum[pObj->m_sDialNum.nCurrentLen] =L'#';
			pObj->m_pTxtDialNumber->SetText(pObj->m_sDialNum.cDialNum);
		}
		break;
	case KEY_DEL:
		{
			//if(pObj->m_sDialNum.nCurrentLen != eMAXDIALNUMLEN- 1)
			pObj->m_sDialNum.nCurrentLen -= 1;
			if(pObj->m_sDialNum.nCurrentLen >= 0)
			{
				pObj->m_sDialNum.cDialNum[pObj->m_sDialNum.nCurrentLen] =0;
			}
			pObj->m_sDialNum.nCurrentLen -= 1;
			if(pObj->m_sDialNum.nCurrentLen <-1)
				pObj->m_sDialNum.nCurrentLen = -1;
			pObj->m_pTxtDialNumber->SetText(pObj->m_sDialNum.cDialNum);

		}
		break;
	case KEY_CALL:
		{
			if(m_ctAutoAnswer.IsActive())
			{
				m_ctAutoAnswer.StopTimer();
			}
			if(p->BTHFPData.nHFPState ==2 && m_sDialNum.nCurrentLen >0 && s_bDailing == false)
			{
				s_bDailing = true;
				pObj->m_sDialNum.nCurrentLen -= 1;
				HUINT nCmdLen = strlen("AT+HFDIAL=");
				HBYTE cCommand[100] = {0};
				strncpy((char*)cCommand,"AT+HFDIAL=",nCmdLen);
				int nwLen = WideCharToMultiByte(CP_ACP,NULL,m_sDialNum.cDialNum,-1,NULL,0,NULL,NULL);
				WideCharToMultiByte(CP_ACP,NULL,m_sDialNum.cDialNum,-1,(char*)(cCommand+nCmdLen),nwLen-1,NULL,NULL);
				cCommand[nCmdLen+nwLen-1] ='\r';
				cCommand[nCmdLen+nwLen ] ='\n';
#ifdef TESTBTCOMMANDQUEUE
				Block *pBlock = CCommandPool::Intance()->PoolNew();
				if(pBlock != NULL)
				{
					sCommandData* pt = (sCommandData*)(pBlock->Buf);
					memset(pt,0,sizeof(sCommandData));
					memcpy(pt->szCommand,cCommand,nCmdLen + nwLen +1);
					pt->nCmdLen = nCmdLen + nwLen +1;
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSendDTMFWhenCalling,pBlock);
				}
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdLen + nwLen +1);	
#endif
				m_ctCall.SetTime(500);
				m_ctCall.StartTimer();
			}
			else if((p->BTHFPData.nHFPState == 3))
			{
				pObj->m_sDialNum.nCurrentLen -= 1;
				HBYTE cCommand[50] = {0};
				HUINT nCmdLen = strlen("AT+HFANSW\r\n");
				strncpy((char*)cCommand,"AT+HFANSW\r\n",nCmdLen);
#ifdef  TESTBTCOMMANDQUEUE
				CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPAnswerCallWhenBeCalled,NULL);
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdLen);
#endif
			}
			 else
			 {
				pObj->m_sDialNum.nCurrentLen -= 1;
			 }
		}
		break;
	case KEY_HANGUP:
		{		
			pObj->m_sDialNum.nCurrentLen -= 1;
			if((p->BTHFPData.nHFPState == 3) || (p->BTHFPData.nHFPState == 4) || (p->BTHFPData.nHFPState == 5) || (p->BTHFPData.nHFPState == 6))
			{
#ifdef  TESTBTCOMMANDQUEUE
				CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPRejectPhoneWhenCalling,NULL);
#else
				HBYTE cCommand[50] = {0};
				HUINT nCmdLen = strlen("AT+HFCHUP\r\n");
				strncpy((char*)cCommand,"AT+HFCHUP\r\n",nCmdLen);
				CBTCommand::Instance()->SendData(cCommand,nCmdLen);
				
#endif
				//if(!m_ctHangUp.IsActive())
				{
					StartHangUpTimer();
				}
			}

//			Sleep(10);
//#ifdef  TESTBTCOMMANDQUEUE
//			CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPAcqureHFPState,NULL);
//#else
//			HBYTE cCommand[50] = {0};
//			HUINT nCmdLen = strlen("AT+HFPSTAT\r\n");
//			strncpy((char*)cCommand,"AT+HFPSTAT\r\n",nCmdLen);
//			CBTCommand::Instance()->SendData(cCommand,nCmdLen);
//#endif
		}
		break;
	case KEY_CANCEL:
		{
			if(p!= NULL)
			{
				if(((p->BTHFPData.nHFPState == 3) || (p->BTHFPData.nHFPState == 4) || (p->BTHFPData.nHFPState == 5) ||(p->BTHFPData.nHFPState == 6)))
				{
					HBYTE cCommand[50] = {0};
					HUINT nCmdLen = strlen("AT+HFADTS\r\n");
					strncpy((char*)cCommand,"AT+HFADTS\r\n",nCmdLen);
#ifdef  TESTBTCOMMANDQUEUE
					CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSwitchVoiceBetweenPhoneAndDevice,NULL);
#else
					CBTCommand::Instance()->SendData(cCommand,nCmdLen);
#endif
					pObj->m_sDialNum.nCurrentLen -= 1;
				}
				else
				{
					memset(pObj->m_sDialNum.cDialNum,0,sizeof(pObj->m_sDialNum.cDialNum));
					pObj->m_pTxtDialNumber->SetText(pObj->m_sDialNum.cDialNum);
					pObj->m_sDialNum.cDialNum[eMAXDIALNUMLEN-1] = L'\0';
					pObj->m_sDialNum.nCurrentLen = -1;
				}
			}	
		}
		break;
	}
	BTDEBUGINFO(L"m_sDialNum.nCurrentLen = %d",m_sDialNum.nCurrentLen);
}

void HCBTDialDlg::SetBTDlgBackGround()
{
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	HINT nHFPState = 0;
	if(p != NULL)
	{
       nHFPState = p->BTHFPData.nHFPState;
	}
	EnableUpdateRect(false);
	HCBluetoothBaseDlg::SetBTDlgBackGround();
	HCBluetoothBaseDlg::SetBTDLBK();
	//拨号键盘背景
	m_pTxtBTDialMiddleBK->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Frame.hfp")));
	m_pTxtBTDialMiddleBK->SetOpacity(8);
	//拨号键盘按键
	m_pBtnDial1->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_1_N.hfp")));
	m_pBtnDial1->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_1_A.hfp")));
	//m_pBtnDial1->SetOpacity(8);
	m_pBtnDial2->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_2_N.hfp")));
	m_pBtnDial2->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_2_A.hfp")));
	//m_pBtnDial2->SetOpacity(8);
	m_pBtnDial3->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_3_N.hfp")));
	m_pBtnDial3->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_3_A.hfp")));
	//m_pBtnDial3->SetOpacity(8);
	m_pBtnBTDialDelete->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Remove_N.hfp")));
	m_pBtnBTDialDelete->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Remove_A.hfp")));
	//m_pBtnBTDialDelete->SetOpacity(8);
	m_pBtnDial4->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_4_N.hfp")));
	m_pBtnDial4->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_4_A.hfp")));
	//m_pBtnDial4->SetOpacity(8);
	m_pBtnDial5->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_5_N.hfp")));
	m_pBtnDial5->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_5_A.hfp")));
	//m_pBtnDial5->SetOpacity(8);
	m_pBtnDial6->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_6_N.hfp")));
	m_pBtnDial6->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_6_A.hfp")));
	//m_pBtnDial6->SetOpacity(8);
	if(nHFPState >= 2)
	{
		m_pBtnBTDialCall->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Answer_N.hfp")));
		//m_pBtnBTDialCall->SetOpacity(8);
	}
	else
	{
		m_pBtnBTDialCall->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Answer_D.hfp")));
		//m_pBtnBTDialCall->SetOpacity(8);
	}
	m_pBtnBTDialCall->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Answer_A.hfp")));
	m_pBtnDial7->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_7_N.hfp")));
	m_pBtnDial7->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_7_A.hfp")));
	//m_pBtnDial7->SetOpacity(8);
	m_pBtnDial8->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_8_N.hfp")));
	m_pBtnDial8->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_8_A.hfp")));
	//m_pBtnDial8->SetOpacity(8);
	m_pBtnDial9->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_9_N.hfp")));
	m_pBtnDial9->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_9_A.hfp")));
	//m_pBtnDial9->SetOpacity(8);
	m_pBtnBTDialHangUp->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Break_D.hfp")));
	m_pBtnBTDialHangUp->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Break_A.hfp")));
	//m_pBtnBTDialHangUp->SetOpacity(8);
	m_pBtnDialStar->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Asterisk_N.hfp")));
	m_pBtnDialStar->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Asterisk_A.hfp")));
	//m_pBtnDialStar->SetOpacity(8);
	m_pBtnDial0->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_0_N.hfp")));
	m_pBtnDial0->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_0_A.hfp")));
	//m_pBtnDial0->SetOpacity(8);
	m_pBtnDialWell->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Well_N.hfp")));
	m_pBtnDialWell->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Well_A.hfp")));
	//m_pBtnDialWell->SetOpacity(8);
	m_pBtnBTDialCancel->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_C_N.hfp")));
	m_pBtnBTDialCancel->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_C_A.hfp")));
	//m_pBtnBTDialCancel->SetOpacity(8);
	EnableUpdateRect(true);
}

void HCBTDialDlg::UpDataKeyBoard(HUINT uHFPState)
{
	HUINT nState = GetPreHFPState();
	switch (uHFPState)
	{
		case 0:
			{
				if(nState != 0)
				{
					OnDialNum(this,(LPARAM_KEYCODE)KEY_CANCEL);
				}
				if(m_ctAutoAnswer.IsActive())
				{
					m_ctAutoAnswer.StopTimer();
				}
				StopCallTimer();
				m_pBtnBTDialCancel->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_C_N.hfp")));
				m_pBtnBTDialCancel->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_C_A.hfp")));
			}
		case 1:
		{
			StopCallTimer();
			m_pBtnBTDialCall->EnableMsg(false);
			m_pBtnBTDialCall->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Answer_D.hfp")));
			m_pBtnBTDialHangUp->EnableMsg(false);
			m_pBtnBTDialHangUp->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Break_D.hfp")));
		}
		break;
		case 2:
		{
			StopCallTimer();
			m_pBtnBTDialCall->EnableMsg(true);
			m_pBtnBTDialCall->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Answer_N.hfp")));
			m_pBtnBTDialHangUp->EnableMsg(false);
			m_pBtnBTDialHangUp->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Break_D.hfp")));
			m_pBtnBTDialCancel->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_C_N.hfp")));
			m_pBtnBTDialCancel->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_C_A.hfp")));
			m_pBtnDial0->EnableMsg(true);
			m_pBtnDial1->EnableMsg(true);
			m_pBtnDial2->EnableMsg(true);
			m_pBtnDial3->EnableMsg(true);
			m_pBtnDial4->EnableMsg(true);
			m_pBtnDial5->EnableMsg(true);
			m_pBtnDial6->EnableMsg(true);
			m_pBtnDial7->EnableMsg(true);
			m_pBtnDial8->EnableMsg(true);
			m_pBtnDial9->EnableMsg(true);
			m_pBtnBTDialDelete->EnableMsg(true);
			m_pBtnBTDialCancel->EnableMsg(true);
			m_pBtnDialStar->EnableMsg(true);
			m_pBtnDialWell->EnableMsg(true);
			SetDailingState(false);
			if(m_ctAutoAnswer.IsActive())
			{
				m_ctAutoAnswer.StopTimer();
			}
		}
		break;
		case 3:
		{
			m_pBtnBTDialCall->EnableMsg(true);
			m_pBtnBTDialCall->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Answer_N.hfp")));
			m_pBtnBTDialHangUp->EnableMsg(true);
			m_pBtnBTDialHangUp->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Break_N.hfp")));
			//m_pBtnBTDialCancel->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Private_N.hfp")));
			//m_pBtnBTDialCancel->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Private_A.hfp")));
			m_pBtnDial0->EnableMsg(true);
			m_pBtnDial1->EnableMsg(true);
			m_pBtnDial2->EnableMsg(true);
			m_pBtnDial3->EnableMsg(true);
			m_pBtnDial4->EnableMsg(true);
			m_pBtnDial5->EnableMsg(true);
			m_pBtnDial6->EnableMsg(true);
			m_pBtnDial7->EnableMsg(true);
			m_pBtnDial8->EnableMsg(true);
			m_pBtnDial9->EnableMsg(true);
			m_pBtnBTDialDelete->EnableMsg(false);
			m_pBtnBTDialCancel->EnableMsg(true);
			m_pBtnDialStar->EnableMsg(true);
			m_pBtnDialWell->EnableMsg(true);
     		BTSETTING Setting;
		    KCLastMemory::GetInstance()->GetBTMemory(Setting);
			if(Setting.uBtAutoReceive == 1)
		    {
				if(m_ctAutoAnswer.IsActive())
				{
					m_ctAutoAnswer.StopTimer();
				}
				m_ctAutoAnswer.SetTime(500);
				m_ctAutoAnswer.StartTimer();
			}
			StopCallTimer();
//				HBYTE cCommand[50] = {0};
//				BTDEBUGINFO(L"Setting.uBtAutoReceive == 1");
//				HINT nCmdlen = strlen("AT+HFANSW\r\n");
//				strncpy((char*)cCommand,"AT+HFANSW\r\n",nCmdlen);
//#ifdef  TESTBTCOMMANDQUEUE
//				CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPAnswerCallWhenBeCalled,NULL);
//#else
//				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
//#endif
//			}
			s_bDailing = false;
		}
		break;
		case 4:
		{
		/*	m_pBtnBTDialCall->EnableMsg(false);
			m_pBtnBTDialCall->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Answer_D.hfp")));
			m_pBtnBTDialHangUp->EnableMsg(true);
			m_pBtnBTDialHangUp->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Break_N.hfp")));
			m_pBtnBTDialCancel->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Private_N.hfp")));
			m_pBtnBTDialCancel->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Private_A.hfp")));
			m_pBtnDial0->EnableMsg(false);
			m_pBtnDial1->EnableMsg(false);
			m_pBtnDial2->EnableMsg(false);
			m_pBtnDial3->EnableMsg(false);
			m_pBtnDial4->EnableMsg(false);
			m_pBtnDial5->EnableMsg(false);
			m_pBtnDial6->EnableMsg(false);
			m_pBtnDial7->EnableMsg(false);
			m_pBtnDial8->EnableMsg(false);
			m_pBtnDial9->EnableMsg(true);
			m_pBtnBTDialDelete->EnableMsg(false);
			m_pBtnBTDialCancel->EnableMsg(true);
			m_pBtnDialStar->EnableMsg(true);
			m_pBtnDialWell->EnableMsg(true);*/
		}
		//break;
		case 5:
		case 6:
		{
			m_pBtnBTDialCall->EnableMsg(false);
			m_pBtnBTDialCall->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Answer_D.hfp")));
			m_pBtnBTDialHangUp->EnableMsg(true);
			m_pBtnBTDialHangUp->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Break_N.hfp")));
		//	m_pBtnBTDialCancel->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Private_N.hfp")));
		//	m_pBtnBTDialCancel->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Private_A.hfp")));

			m_pBtnDial0->EnableMsg(true);
			m_pBtnDial1->EnableMsg(true);
			m_pBtnDial2->EnableMsg(true);
			m_pBtnDial3->EnableMsg(true);
			m_pBtnDial4->EnableMsg(true);
			m_pBtnDial5->EnableMsg(true);
			m_pBtnDial6->EnableMsg(true);
			m_pBtnDial7->EnableMsg(true);
			m_pBtnDial8->EnableMsg(true);
			m_pBtnDial9->EnableMsg(true);
			m_pBtnBTDialDelete->EnableMsg(false);
			m_pBtnBTDialCancel->EnableMsg(true);
			m_pBtnDialStar->EnableMsg(true);
			m_pBtnDialWell->EnableMsg(true);
			if(m_ctAutoAnswer.IsActive())
			{
				m_ctAutoAnswer.StopTimer();
			}
			StopCallTimer();
			s_bDailing = false;
		}
		break;
		case 7:
			{
				StopCallTimer();
				m_pBtnBTDialCall->EnableMsg(false);
				m_pBtnBTDialCall->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Answer_D.hfp")));
				m_pBtnBTDialHangUp->EnableMsg(false);
				m_pBtnBTDialHangUp->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Break_D.hfp")));
			}
			break;
		default:
		break;
	}
  SetPreHFPState(uHFPState);
}

void HCBTDialDlg::UpDataKeyBoardNum()
{
	sBTCommandData *p = CBTCommand::Instance()->GetBTCommandData();
	if(p != NULL)
	{
		HCHAR *pTxt=p->BTHFPData.sCurrentCall.szContact.szTelNumber.PhoneNumber; 
		HCHAR *pNameTxt = p->BTHFPData.sCurrentCall.szContact.szName;
		HINT  n = 0;
		while(n <19 && pTxt[n] != 0)
		{
			n++;
		}
		if(n > 0)
		{
			memset(m_sDialNum.cDialNum,0,sizeof(m_sDialNum.cDialNum));
			memcpy(m_sDialNum.cDialNum,pTxt,2*n);
			m_sDialNum.nCurrentLen = n-1;
			BTDEBUGINFO(L"m_sDialNum.nCurrentLen = %d,NUmber:%s",m_sDialNum.nCurrentLen,pTxt);
			m_pTxtDialNumber->SetText(m_sDialNum.cDialNum);
			m_pTxtCotactName->SetText(pNameTxt);
		}
	}
}
void HCBTDialDlg::UpDataKeyBoardNum(sContact *pContact)
{
	if(pContact != NULL)
	{
		HCHAR *pTxt=pContact->szTelNumber.PhoneNumber; 
		HCHAR *pNameTxt = pContact->szName;
		HINT  n = 0;
		while(n <19 && pTxt[n] != 0)
		{
			n++;
		}
		if(n > 0)
		{
			memset(m_sDialNum.cDialNum,0,sizeof(m_sDialNum.cDialNum));
			memcpy(m_sDialNum.cDialNum,pTxt,2*n);
			m_sDialNum.nCurrentLen = n-1;
			BTDEBUGINFO(L"m_sDialNum.nCurrentLen = %d,NUmber:%s",m_sDialNum.nCurrentLen,pTxt);
			m_pTxtDialNumber->SetText(m_sDialNum.cDialNum);
			m_pTxtCotactName->SetText(pNameTxt);
		}
	}
}
void HCBTDialDlg::ClearKeyBoardNum()
{
	memset(m_sDialNum.cDialNum,0,sizeof(m_sDialNum.cDialNum));
	m_pTxtDialNumber->SetText(m_sDialNum.cDialNum);
	m_sDialNum.cDialNum[eMAXDIALNUMLEN-1] = L'\0';
	m_sDialNum.nCurrentLen = -1;
	s_bDailing = false;
}

 void HCBTDialDlg::StartCountCallDuration()
 {
	 if(m_ctCallDuration.IsActive())
	 {
		 m_ctCallDuration.StopTimer();
	 }
	   // m_pTxtCallState->SetText(L"通话中")；
		//m_pTxtCallState->SetShow(true);
	    m_nCallDuration = 0;
		if(s_pLan != NULL)
		{
			m_pTxtCallTime->SetText(s_pLan[17]);
		}
		m_pTxtCallTime->AppendText(L"00:00");
		//m_pTxtCallTime->SetText(L"通话中  00:00");
		//m_pTxtCallTime->(L"");
		m_pTxtCallTime->SetShow(true);
		m_ctCallDuration.SetTime(100);
		m_ctCallDuration.StartTimer();
 }

 void HCBTDialDlg::StopCountCallDuration()
 {
	 if(m_ctCallDuration.IsActive())
	 {
		 m_ctCallDuration.StopTimer();
	 }
	 m_nCallDuration = 0;
 }

 void HCBTDialDlg::UpdataTextShow(HINT nState)
 {
	 switch (nState)
	 {
		 case 0:
		 case 1:
		 case 2:
		{
			m_pTxtCallTime->SetShow(false);
			//m_pTxtCallState->SetShow(false);
			m_pTxtCotactName->SetText(L" ");
			StopCountCallDuration();
			StopHangUpTimer();
		}
		break;
		 case 3:
		{
			/*m_pTxtCallState->SetText(L"来电…");
			m_pTxtCallState->SetShow(true);*/
			//m_pTxtCallTime->SetText(L"来电…");
			if(s_pLan != NULL)
			{
				m_pTxtCallTime->SetText(s_pLan[16]);
			}
			m_pTxtCallTime->SetShow(true);
			StopCountCallDuration();
			StopHangUpTimer();
			//KCBTDialogManager::Instance()->JumpToDlg(eDIALOGT_BTDIAL);
			KCBTDialogManager::Instance()->JumpToDlg(eDIALOGT_BTDIAL);
			
			//来电自动接听处理
		}
		break;
		case 4:
		{
		/*	m_pTxtCallState->SetText(L"拨号中…");
			m_pTxtCallState->SetShow(true);*/
			//m_pTxtCallTime->SetText(L"正在拨号…");
			StopCountCallDuration();
			if(s_pLan != NULL)
			{
				m_pTxtCallTime->SetText(s_pLan[14]);
			}
			m_pTxtCallTime->SetShow(true);
			//KCBTDialogManager::Instance()->JumpToDlg(eDIALOGT_BTDIAL);
			//OnBTDial(NULL);
			StopHangUpTimer();
			KCBTDialogManager::Instance()->JumpToDlg(eDIALOGT_BTDIAL);
		}
		break;
		case 5:
		{
			/*m_pTxtCallState->SetText(L"通话中");
			m_pTxtCallState->SetShow(true);*/
			
			StartCountCallDuration();
			KCBTDialogManager::Instance()->JumpToDlg(eDIALOGT_BTDIAL);
			//OnBTDial(NULL);
			StopHangUpTimer();
		}
		break;
		case  6:
		{
			/*m_pTxtCallState->SetText(L"三方通话中");
			m_pTxtCallState->SetShow(true);*/
			StartCountCallDuration();
			KCBTDialogManager::Instance()->JumpToDlg(eDIALOGT_BTDIAL);
			StopHangUpTimer();
			//OnBTDial(NULL);
		}
		break;
		case 7:
		{
			/*m_pTxtCallState->SetText(L"通话结束");
			m_pTxtCallState->SetShow(true);*/
			//m_nCallDuration ++;
			//StopCountCallDuration();
			StopHangUpTimer();
			if(m_ctCallDuration.IsActive())
			{
				m_ctCallDuration.StopTimer();
			}
			HCHAR szTemp[30] = {0};
			HINT uHour = m_nCallDuration/3600%24;
			HINT uMin = (m_nCallDuration%3600)/60;
			HINT uSec = m_nCallDuration%60;
			swprintf_s(szTemp,10,L"通话结束    ");
			m_pTxtCallTime->SetText(s_pLan[15]);
			if(uHour ==0 && uMin == 0)
			{
				if(uSec <10 && uSec >= 0)
				{
					swprintf_s(szTemp+5,10,L"00:0%d",uSec);
				}
				else if(uSec >= 10)
				{
					swprintf_s(szTemp+5,10,L"00:%d",uSec);
				}
			}
			else if(uHour == 0 && uMin > 0)
			{
				if(uMin < 10)
				{
					if(uSec < 10)
					{
						swprintf_s(szTemp+5,10,L"0%d:0%d",uMin,uSec);
					}
					else
					{
						swprintf_s(szTemp+5,10,L"0%d:%d",uMin,uSec);
					}
				}
				else
				{
					if(uSec < 10)
					{
						swprintf_s(szTemp+5,10,L"%d:0%d",uMin,uSec);
					}
					else
					{
						swprintf_s(szTemp+5,10,L"%d:%d",uMin,uSec);
					}
				}
			}
			else if(uHour > 0)
			{
				if(uMin < 10)
				{
					if(uSec < 10)
					{
						swprintf_s(szTemp+5,16,L"%d:0%d:0%d",uHour,uMin,uSec);
					}
					else
					{
						swprintf_s(szTemp+5,16,L"%d:0%d:%d",uHour,uMin,uSec);
					}
				}
				else
				{
					if(uSec < 10)
					{
						swprintf_s(szTemp+5,16,L"%d:%d:0%d",uHour,uMin,uSec);
					}
					else
					{
						swprintf_s(szTemp+5,16,L"%d:%d:%d",uHour,uMin,uSec);
					}
				}
			}
			//m_pTxtCallTime->SetText(szTemp);
			m_pTxtCallTime->AppendText(szTemp + 5);
			m_pTxtCallTime->SetShow(true);
			KCBTDialogManager::Instance()->JumpToDlg(eDIALOGT_BTDIAL);
			//OnBTDial(NULL);
			m_nCallDuration = 0;
		}
		default:
		break;
	 }
 }

 void HCBTDialDlg::OnCountCallDuration(void* pDlg, void* param)
 {
	 HCBTDialDlg* pObj = (HCBTDialDlg*)pDlg;
	 pObj->OnCountCallDuration(pObj);
 }
 void HCBTDialDlg::OnCountCallDuration(void* pDlg)
 {
   if(m_ctCallDuration.IsActive())
   {
	   m_ctCallDuration.StopTimer();
   }
   m_ctCallDuration.SetTime(100);
   m_ctCallDuration.StartTimer();
  // m_nCallDuration +=33; 
   m_nCallDuration ++;
   HCHAR szTemp[30] = {0};
   HINT uHour = m_nCallDuration/3600%24;
   HINT uMin = (m_nCallDuration%3600)/60;
   HINT uSec = m_nCallDuration%60;
  // if(uMin == 0 && uHour == 0)
  // {
		//swprintf_s(szTemp,4,L"%d",uSec);
  // }
  // else if(uHour == 0 && uMin > 0)
	 //{
		//	if(uSec >= 10)
		//	 {
		//       swprintf_s(szTemp,10,L"%d:%d",uMin,uSec);
		//	 }
	 //       if(uSec < 10 && uSec >=0)
	 //      {
		//	    swprintf_s(szTemp,10,L"%d:0%d",uMin,uSec);
	 //      }
  // }
  // else if(uHour > 0)
  // {
	 //  if(uMin >=10)
	 //  {
		//   if(uSec >= 10)
		//   {
		//	   swprintf_s(szTemp,14,L"%d:%d:%d",uHour,uMin,uSec);
		//   }
		//   else
		//   {
  //             swprintf_s(szTemp,14,L"%d:%d:0%d",uHour,uMin,uSec);
		//   }
	 //  }
	 //  else
	 //  {
		//   if(uSec < 10)
		//   {
		//	   swprintf_s(szTemp,14,L"%d:0%d:0%d",uHour,uMin,uSec);
		//   }
		//   else
		//   {
		//	   swprintf_s(szTemp,14,L"%d:0%d:%d",uHour,uMin,uSec);
		//   }
	 //  }   
  // }
   swprintf_s(szTemp,10,L"通话中    ");
   if(s_pLan != NULL)
   {
		m_pTxtCallTime->SetText(s_pLan[17]);
   }
   if(uHour ==0 && uMin == 0)
   {
	   if(uSec <10 && uSec >= 0)
	   {
		   swprintf_s(szTemp+5,10,L"00:0%d",uSec);
	   }
	   else if(uSec >= 10)
	   {
		   swprintf_s(szTemp+5,10,L"00:%d",uSec);
	   }
   }
   else if(uHour == 0 && uMin > 0)
   {
	   if(uMin < 10)
	   {
		   if(uSec < 10)
		   {
			   swprintf_s(szTemp+5,10,L"0%d:0%d",uMin,uSec);
		   }
		   else
		   {
			   swprintf_s(szTemp+5,10,L"0%d:%d",uMin,uSec);
		   }
	   }
	   else
	   {
		   if(uSec < 10)
		   {
			   swprintf_s(szTemp+5,10,L"%d:0%d",uMin,uSec);
		   }
		   else
		   {
			   swprintf_s(szTemp+5,10,L"%d:%d",uMin,uSec);
		   }
	   }
   }
   else if(uHour > 0)
   {
	   if(uMin < 10)
	   {
		   if(uSec < 10)
		   {
			   swprintf_s(szTemp+5,16,L"%d:0%d:0%d",uHour,uMin,uSec);
		   }
		   else
		   {
			   swprintf_s(szTemp+5,16,L"%d:0%d:%d",uHour,uMin,uSec);
		   }
	   }
	   else
	   {
		   if(uSec < 10)
		   {
			   swprintf_s(szTemp+5,16,L"%d:%d:0%d",uHour,uMin,uSec);
		   }
		   else
		   {
			   swprintf_s(szTemp+5,16,L"%d:%d:%d",uHour,uMin,uSec);
		   }
	   }
   }
  // m_pTxtCallState->SetText(L"通话中");
  // m_pTxtCallState->SetShow(true);
   //m_pTxtCallTime->SetText(szTemp);
   m_pTxtCallTime->AppendText(szTemp + 5);
   m_pTxtCallTime->SetShow(true);
 }
 void HCBTDialDlg::ClearDailData()
 {
	 if(!m_bCleared)
	 {
		ClearKeyBoardNum();
		if(m_pTxtCallTime->IsShow())
		{
			m_pTxtCallTime->SetShow(false);
		}
		if(m_ctCallDuration.IsActive())
		{
			m_ctCallDuration.StopTimer();
		}
		//UpdataTextShow(0);
		//updat
		m_bCleared = true;
	 }
 }
 void HCBTDialDlg::RequreSource()
 {
	 if(m_bSourceRealse == true)
	 {
		HCBTDialDlg::SetBTDlgBackGround();
		m_bSourceRealse = false;
		BTDEBUGINFO(L"HCBTDialDlg::%s",__FUNCTIONW__);
	 }
 }
 void HCBTDialDlg::ReleaseSource()
 {
	 if(m_bSourceRealse == false)
	 {
		 m_pTxtBTDialMiddleBK->SetBkgndN(NULL);
		 //拨号键盘按键
		 m_pBtnDial1->SetBkgndN(NULL);
		 m_pBtnDial1->SetBkgndA(NULL);
		 m_pBtnDial2->SetBkgndN(NULL);
		 m_pBtnDial2->SetBkgndA(NULL);
		 m_pBtnDial3->SetBkgndN(NULL);
		 m_pBtnDial3->SetBkgndA(NULL);
		 m_pBtnBTDialDelete->SetBkgndN(NULL);
		 m_pBtnBTDialDelete->SetBkgndA(NULL);
		 m_pBtnDial4->SetBkgndN(NULL);
		 m_pBtnDial4->SetBkgndA(NULL);
		 m_pBtnDial5->SetBkgndN(NULL);
		 m_pBtnDial5->SetBkgndA(NULL);
		 m_pBtnDial6->SetBkgndN(NULL);
		 m_pBtnDial6->SetBkgndA(NULL);
		 // m_pBtnBTDialCall->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Answer_D.hfp")));
		 // m_pBtnBTDialCall->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Answer_A.hfp")));
		 m_pBtnDial7->SetBkgndN(NULL);
		 m_pBtnDial7->SetBkgndA(NULL);
		 m_pBtnDial8->SetBkgndN(NULL);
		 m_pBtnDial8->SetBkgndA(NULL);
		 m_pBtnDial9->SetBkgndN(NULL);
		 m_pBtnDial9->SetBkgndA(NULL);
		 // m_pBtnBTDialHangUp->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Break_D.hfp")));
		 //m_pBtnBTDialHangUp->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Break_A.hfp")));
		 m_pBtnDialStar->SetBkgndN(NULL);
		 m_pBtnDialStar->SetBkgndA(NULL);
		 m_pBtnDial0->SetBkgndN(NULL);
		 m_pBtnDial0->SetBkgndA(NULL);
		 m_pBtnDialWell->SetBkgndN(NULL);
		 m_pBtnDialWell->SetBkgndA(NULL);
		 // m_pBtnBTDialCancel->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_C_N.hfp")));
		 //m_pBtnBTDialCancel->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_C_A.hfp")));	
		 m_bSourceRealse = true;
		 BTDEBUGINFO(L"HCBTDialDlg::%s",__FUNCTIONW__);
	 }
 }
 void HCBTDialDlg::ChangeVoicePoisition(HINT nPosition)
{
	if(m_pBtnBTDialCancel != NULL)
	{
		switch (nPosition)
		{
		case 0:
			{
				//m_pBtnBTDialCancel->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Phone_N.hfp")));
				//m_pBtnBTDialCancel->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Phone_A.hfp")));
				m_pBtnBTDialCancel->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Pcar_N.hfp")));
				m_pBtnBTDialCancel->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Pcar_A.hfp")));
				m_nVoicePos = 0;
			}
			break;
		case 1:
			{
				m_pBtnBTDialCancel->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Phone_N.hfp")));
				m_pBtnBTDialCancel->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Phone_A.hfp")));
				//m_pBtnBTDialCancel->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Pcar_N.hfp")));
				//m_pBtnBTDialCancel->SetBkgndA(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Pcar_A.hfp")));
				m_nVoicePos = 1;
			}
			break;
		case 3:
			{
				//m_pBtnBTDialCall->SetBkgndN(GetHMIPath(_T("Bluetooth\\Dial\\Dial_Num_Answer_N.hfp")));
			}
			break;
		default:
			m_nVoicePos = 100;
			break;
		}
	}	
}
 void HCBTDialDlg::OnAutoAnswer(void* pDlg, void* param)
 {
	 HCBTDialDlg* pObj = (HCBTDialDlg*)pDlg;
	 pObj->OnAutoAnswer(pObj);
 }
 void HCBTDialDlg::OnAutoAnswer(void* pDlg)
 {
	 sBTCommandData* pData =  CBTCommand::Instance()->GetBTCommandData();
	 BTSETTING Setting;
	 KCLastMemory::GetInstance()->GetBTMemory(Setting);
	 if(Setting.uBtAutoReceive == 1)
	 {
			if(pData != NULL && pData->BTHFPData.nHFPState == 3)
			{
				HBYTE cCommand[50] = {0};
				BTDEBUGINFO(L"Setting.uBtAutoReceive == 1");
				HINT nCmdlen = strlen("AT+HFANSW\r\n");
				strncpy((char*)cCommand,"AT+HFANSW\r\n",nCmdlen);
#ifdef  TESTBTCOMMANDQUEUE
				CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPAnswerCallWhenBeCalled,NULL);
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
			}
			
	 }
 }
 void HCBTDialDlg::SetVoiceToPhone()
 {
	 sBTCommandData* p = CBTCommand::Instance()->GetBTCommandData();
	 if(p != NULL)
	 {
		 HINT nHFPState = p->BTHFPData.nHFPState;
		 if(nHFPState == 5 || nHFPState == 6 || nHFPState == 3 || nHFPState == 4)
		 {
			if(m_nVoicePos == 1)
			{
				HBYTE cCommand[50] = {0};
				HUINT nCmdLen = strlen("AT+HFADTS\r\n");
				strncpy((char*)cCommand,"AT+HFADTS\r\n",nCmdLen);
#ifdef  TESTBTCOMMANDQUEUE
				CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketHFPSwitchVoiceBetweenPhoneAndDevice,NULL);
#else
				CBTCommand::Instance()->SendData(cCommand,nCmdLen);
#endif
			}
		 }
	 }
 }
 void HCBTDialDlg::OnEnableCall(void* pDlg, void* param)
 {
	 HCBTDialDlg* pObj = (HCBTDialDlg*)pDlg;
	 pObj->OnEnableCall(pObj);
 }
 void HCBTDialDlg::OnEnableCall(void* pDlg)
 {
	 s_bDailing = false;
 }
 void HCBTDialDlg::OnReboot(void* pDlg, void* param)
 {
	 HCBTDialDlg* pObj = (HCBTDialDlg*)pDlg;
	 pObj->OnReboot(pObj);
 }
 void HCBTDialDlg::OnReboot(void* pDlg)
 {
#ifdef  TESTBTCOMMANDQUEUE
	 CBTCommand::Instance()->SendBTCommandBlockToQueue(BTPacketSoftRestart,NULL);
#else
	 HBYTE cCommand[50] = {0};
	 HUINT nCmdlen = strlen("AT+BOOT\r\n");
	 strncpy((char*)cCommand,"AT+BOOT\r\n",nCmdlen);
	 CBTCommand::Instance()->SendData(cCommand,nCmdlen);
#endif
 }
 void HCBTDialDlg::StopCallTimer()
 {
    m_ctCall.StopTimer();
 }

 void HCBTDialDlg::StartCallTimer()
 {
	 if(m_ctCall.IsActive())
	 {
		 m_ctCall.StopTimer();
	 }
	 m_ctCall.SetTime(500);
	 m_ctCall.StartTimer();
 }
 void HCBTDialDlg::StartHangUpTimer()
 {
	if(m_ctHangUp.IsActive())
	{
		m_ctHangUp.StopTimer();
	}
	m_ctHangUp.SetTime(200);
	m_ctHangUp.StartTimer();
 }
 void HCBTDialDlg::StopHangUpTimer()
 {
	m_ctHangUp.StopTimer();
 }
#if TESTDAILPROBLEM
 void HCBTDialDlg::UpdataTestHFP()
 {
	 sBTCommandData* p = CBTCommand::Instance()->GetBTCommandData();
	 HINT nHfp = p->BTHFPData.nHFPState;
	 HINT nA2dp = p->BTAVRCPData.nA2DPState;
	 HCHAR szBuffer[10] = {0};
	 BTDEBUGINFO(L"%s:nHfp = %d,nA2dp = %d",__FUNCTIONW__,nHfp,nA2dp);
	 swprintf(szBuffer,L"%d",nHfp);
	 m_pTxtHFPstate->SetText(szBuffer);
	 memset(szBuffer,0,sizeof(szBuffer));
	 swprintf(szBuffer,L"%d",nA2dp);
	 m_pTxtA2DPstate->SetText(szBuffer);
 }
#else
#endif
