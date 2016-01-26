// $Change: 000000 $
#include "stdafx.h"
#include "ipodctl.h"
#include "testipod.h"
TestIpod* testipod = NULL;
BOOL bCnntbleIpodctl = FALSE;
CRITICAL_SECTION csIpodctl;
HANDLE hExitEvent,hCnntEvent;
HANDLE hConnectThread=NULL;
BOOL bRunIpodctl = TRUE;
BOOL bConnectedIpodctl = FALSE;
BOOL bAutoConnectIpodctl = TRUE;
BOOL bResumeble = FALSE;
U32 u32CurListIpodctl,u32CurIndexIpodctl;
ipodctlPAGE eCurPage;
static int nnnCtl = 0;
void EnterCsCtlCriticalSection(LPCRITICAL_SECTION pcsCriticalSection);
void LeaveCsCtlCriticalSection(LPCRITICAL_SECTION pcsCriticalSection);

void EnterCsCtlCriticalSection(LPCRITICAL_SECTION pcsCriticalSection)
{
#if TESTCRITICALSECTION
		  nnnCtl++;printf("++++++csIpodctl = %d++++++",nnnCtl);
#endif
	EnterCriticalSection(pcsCriticalSection);
}
void LeaveCsCtlCriticalSection(LPCRITICAL_SECTION pcsCriticalSection)
{
   LeaveCriticalSection(pcsCriticalSection);
#if TESTCRITICALSECTION
   nnnCtl--;printf("--------csIpodctl = %d-------",nnnCtl);
#endif
}
void AliveThread()
{
	while (1)
	{
		printf("+++++++++++++time:%d,alive+++++++++++++\r\n",GetTickCount());
		Sleep(5000);
	}
}
void ConnectThread()
{
    U32 u32tracklen,u32trackpos;
    U8 u8status;
    if(bCnntbleIpodctl)
    {
        while(bRunIpodctl)
        {
            //wait exit
            hExitEvent = CreateEvent( NULL, FALSE, FALSE, TEXT("_IPOD_UAC_EXIT_"));
            WaitForSingleObject(hExitEvent,INFINITE);
            RETAILMSG(1,(TEXT("&&&&&&&&&&&&&\r\n_IPOD_UAC_EXIT_\r\n&&&&&&&&&&&&&\r\n")));
            ResetEvent(hExitEvent);
            CloseHandle(hExitEvent);
            //todo
ipod_exit1:
		    printf("2222\r\n");
           EnterCsCtlCriticalSection(&csIpodctl);
            testipod->CloseDevice();
            bConnectedIpodctl = FALSE;
            bCnntbleIpodctl = FALSE;
            LeaveCsCtlCriticalSection(&csIpodctl);
            //wait insert
            hCnntEvent = CreateEvent( NULL, FALSE, FALSE, TEXT("_IPOD_UAC_CNNT_"));
            WaitForSingleObject(hCnntEvent,INFINITE);
            RETAILMSG(1,(TEXT("&&&&&&&&&&&&&\r\n_IPOD_UAC_CNNT\r\n&&&&&&&&&&&&&\r\n")));
            ResetEvent(hCnntEvent);
            CloseHandle(hCnntEvent);
            //todo
            bCnntbleIpodctl = TRUE;
            if(bAutoConnectIpodctl)
            {
               EnterCsCtlCriticalSection(&csIpodctl);
                if(!testipod->Connect())
                {
                    LeaveCsCtlCriticalSection(&csIpodctl);
                    goto ipod_exit1;
                }
                if(!testipod->IpodAuthenticationAcc())
                {
                    LeaveCsCtlCriticalSection(&csIpodctl);
                    goto ipod_exit1;
                }
                if(!testipod->StartPlay())
                {
                    LeaveCsCtlCriticalSection(&csIpodctl);
                    goto ipod_exit1;
                }
                bConnectedIpodctl = TRUE;
				testipod->SetIpodReadyEvent();
				printf("___1111__Connect Success__22222____\r\n");
                LeaveCsCtlCriticalSection(&csIpodctl);
            }
        }
    }
    else
    {
        while(bRunIpodctl)
        {
            //wait insert
            hCnntEvent = CreateEvent( NULL, FALSE, FALSE, TEXT("_IPOD_UAC_CNNT_"));
            RETAILMSG(1,(TEXT("&&&&&&&&&&&&&\r\n_IPOD_UAC_CNNT\r\n&&&&&&&&&&&&&\r\n")));
            WaitForSingleObject(hCnntEvent,INFINITE);
            ResetEvent(hCnntEvent);
            CloseHandle(hCnntEvent);
            //todo
            bCnntbleIpodctl = TRUE;
            if(bAutoConnectIpodctl)
            {
               EnterCsCtlCriticalSection(&csIpodctl);
                if(!testipod->Connect())
                {
                    LeaveCsCtlCriticalSection(&csIpodctl);
                    goto ipod_exit2;
                }
                if(!testipod->IpodAuthenticationAcc())
                {
                    LeaveCsCtlCriticalSection(&csIpodctl);
                    goto ipod_exit2;
                }
                if(!testipod->StartPlay())
                {
                    LeaveCsCtlCriticalSection(&csIpodctl);
                    goto ipod_exit2;
                }
                bConnectedIpodctl = TRUE;
                LeaveCsCtlCriticalSection(&csIpodctl);
            }
			testipod->SetIpodReadyEvent();
			printf("_____Connect Success______\r\n");
            //wait exit
            hExitEvent = CreateEvent( NULL, FALSE, FALSE, TEXT("_IPOD_UAC_EXIT_"));
            RETAILMSG(1,(TEXT("&&&&&&&&&&&&&\r\n_IPOD_UAC_EXIT_\r\n&&&&&&&&&&&&&\r\n")));
            WaitForSingleObject(hExitEvent,INFINITE);
            ResetEvent(hExitEvent);
            CloseHandle(hExitEvent);
            //todo
ipod_exit2:
           EnterCsCtlCriticalSection(&csIpodctl);
            testipod->CloseDevice();
            bConnectedIpodctl = FALSE;
            bCnntbleIpodctl = FALSE;
            LeaveCsCtlCriticalSection(&csIpodctl);
        }
    }
}
ipodctlERR ipodctl_Init(BOOL bAutoCnnt)
{
    if(NULL!=hConnectThread) return ERR_FAIL;
    testipod = new TestIpod();
    bAutoConnectIpodctl = bAutoCnnt;
	 InitializeCriticalSection(&csIpodctl);
 /*   if(testipod->OpenDevice())
    {
		Sleep(30);
         testipod->CloseDevice();
        bCnntbleIpodctl = TRUE;
    }
    else
    {
        bCnntbleIpodctl = FALSE;
    }*/
	 bCnntbleIpodctl = TRUE;
   
   hConnectThread = CreateThread(NULL, 0, ((LPTHREAD_START_ROUTINE)ConnectThread), NULL, 0, NULL);//É¾³ý0722
	CreateThread(NULL, 0, ((LPTHREAD_START_ROUTINE)AliveThread), NULL, 0, NULL);

    return ERR_OK;
}
ipodctlERR ipodctl_SetAutoConnect(BOOL bAutoCnnt)
{
   EnterCsCtlCriticalSection(&csIpodctl);
    bAutoConnectIpodctl = bAutoCnnt;
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}
ipodctlERR ipodctl_ConnectToIpod()
{
   EnterCsCtlCriticalSection(&csIpodctl);
    if(NULL==hConnectThread)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTINIT;
    }
    if(!bCnntbleIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_IPODEXIT;
    }
  /*  if(bConnectedIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_OK;
    }*/   //delete 0722
    if(!testipod->Connect())
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    if(!testipod->IpodAuthenticationAcc())
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    if(!testipod->StartPlay())
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    bConnectedIpodctl = TRUE;
	testipod->SetIpodReadyEvent();
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}
ipodctlERR ipodctl_StartPlay(ipodctlPAGE startPage,U32 startList,U32 startIndex)
{
   EnterCsCtlCriticalSection(&csIpodctl);
    if(NULL==hConnectThread)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTINIT;
    }
    if(!bCnntbleIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_IPODEXIT;
    }
    if(!bConnectedIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTCNNT;
    }
    U32 u32tracklen,u32trackpos;
    U8 u8status;
    bResumeble = TRUE;
    eCurPage = startPage;
    u32CurListIpodctl = startList;
    u32CurIndexIpodctl = startIndex;
    if(!testipod->ResetDBSelection())
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
	int iPage= 0;
	unsigned long nTotal = 0;
	//for(iPage = 0; iPage <= 11;iPage++)
	{
		
		ipodctl_GetNumberCategorizedDBRecords((ipodctlPAGE)startPage,&nTotal);
		//if(iPage == PAGE_ARTIST)
		//{
		// unsigned char *pOut = new unsigned char[3000];
		// unsigned long nGet = 0;
		// unsigned long nStart = 0;
		//while(nTotal > 0)
		// {
		//  if(nTotal > 5)
		//  {
		//	 nGet = 5;
		//  }
		//  else
		//  {
		//	  nGet = nTotal;
		//  }
		//  IPODDEBEGINFO(L"----------ipodctl_GetCategorizedDBRecords: iPage = %d,nStart = %d,nGet = %d-----------------",iPage,nStart,nGet);
		//ipodctl_GetCategorizedDBRecords((ipodctlPAGE)iPage,nStart,nGet,pOut);
		//nStart += nGet;
		//nTotal -= nGet;
		// }
		//}
	}
	if(nTotal > 0)
	{
		for(unsigned long nn = 0; nn < nTotal;nn++)
		{
			if(!testipod->SelectDBRecord(startPage,nn))
			{
				if(bCnntbleIpodctl)
				{
					LeaveCsCtlCriticalSection(&csIpodctl);
					return ERR_FAIL;
				}
				else
				{
					LeaveCsCtlCriticalSection(&csIpodctl);
					return ERR_IPODEXIT;
				}
			}
		}
	}
  
    //if(!testipod->PlayCurrentSelection(startIndex))
    //{
    //    if(bCnntbleIpodctl)
    //    {
    //        LeaveCsCtlCriticalSection(&csIpodctl);
    //        return ERR_FAIL;
    //    }
    //    else
    //    {
    //        LeaveCsCtlCriticalSection(&csIpodctl);
    //        return ERR_IPODEXIT;
    //    }
    //}//delete 0723
    if(!testipod->GetPlayStatus(&u32tracklen, &u32trackpos, &u8status))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    if(1==u8status)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_OK;
    }
	testipod->SetPlayStatusChangeNotification(FALSE,0x00);
    if(!testipod->PlayControl(PLAY_CONTROL_TOGGLE_PLAYPAUSE))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}
ipodctlERR ipodctl_GetPlayStatus(unsigned long* trackIndex,unsigned long* trackLength,unsigned long* trackPosition,ipodctlPLAYSTATUS* playStatus )
{
   EnterCsCtlCriticalSection(&csIpodctl);
    if(NULL==hConnectThread)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTINIT;
    }
    if(!bCnntbleIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_IPODEXIT;
    }
    if(!bConnectedIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTCNNT;
    }
    U32 u32tracklen,u32trackpos,u32idx;
    U8 u8status;
    if(NULL==trackIndex||NULL==trackLength||NULL==trackPosition||NULL==playStatus)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_BADPARAM;
    }
    if(!testipod->GetCurrentPlayingTrackIndex(&u32idx))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    u32CurIndexIpodctl = u32idx;
    if(!testipod->GetPlayStatus(&u32tracklen, &u32trackpos, &u8status))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    *trackIndex = u32idx;
    *trackLength = u32tracklen;
    *trackPosition = u32trackpos;
    *playStatus = (ipodctlPLAYSTATUS)u8status;
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}
ipodctlERR ipodctl_PlayPause()
{
   EnterCsCtlCriticalSection(&csIpodctl);
    if(NULL==hConnectThread)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTINIT;
    }
    if(!bCnntbleIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_IPODEXIT;
    }
    if(!bConnectedIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTCNNT;
    }
    if(!testipod->PlayControl(PLAY_CONTROL_TOGGLE_PLAYPAUSE))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}
ipodctlERR ipodctl_NextTrack()
{
   EnterCsCtlCriticalSection(&csIpodctl);
    if(NULL==hConnectThread)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTINIT;
    }
    if(!bCnntbleIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_IPODEXIT;
    }
    if(!bConnectedIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTCNNT;
    }
    if(!testipod->PlayControl(PLAY_CONTROL_NEXT_TRACK))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}
ipodctlERR ipodctl_PreviousTrack()
{
   EnterCsCtlCriticalSection(&csIpodctl);
    if(NULL==hConnectThread)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTINIT;
    }
    if(!bCnntbleIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_IPODEXIT;
    }
    if(!bConnectedIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTCNNT;
    }
    if(!testipod->PlayControl(PLAY_CONTROL_PRE_TRACK))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}
ipodctlERR ipodctl_StartFF()
{
   EnterCsCtlCriticalSection(&csIpodctl);
    if(NULL==hConnectThread)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTINIT;
    }
    if(!bCnntbleIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_IPODEXIT;
    }
    if(!bConnectedIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTCNNT;
    }
    if(!testipod->PlayControl(PLAY_CONTROL_START_FF))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}
ipodctlERR ipodctl_StartRew()
{
   EnterCsCtlCriticalSection(&csIpodctl);
    if(NULL==hConnectThread)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTINIT;
    }
    if(!bCnntbleIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_IPODEXIT;
    }
    if(!bConnectedIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTCNNT;
    }
    if(!testipod->PlayControl(PLAY_CONTROL_START_REW))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}
ipodctlERR ipodctl_EndFFRew()
{
   EnterCsCtlCriticalSection(&csIpodctl);
    if(NULL==hConnectThread)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTINIT;
    }
    if(!bCnntbleIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_IPODEXIT;
    }
    if(!bConnectedIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTCNNT;
    }
    if(!testipod->PlayControl(PLAY_CONTROL_END_FFREW))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}
ipodctlERR ipodctl_GetTrackInfo(unsigned long trackIndex,WCHAR* trackTitle,WCHAR* artistName,WCHAR* albumName)
{
   EnterCsCtlCriticalSection(&csIpodctl);
    if(NULL==hConnectThread)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTINIT;
    }
    if(!bCnntbleIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_IPODEXIT;
    }
    if(!bConnectedIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTCNNT;
    }
    if(NULL==trackTitle||NULL==artistName||NULL==albumName)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_BADPARAM;
    }
    if(!testipod->GetIndexedPlayingTrackTitle(trackIndex,trackTitle))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    if(!testipod->GetIndexedPlayingTrackArtistName(trackIndex,artistName))
    {
      // EnterCsCtlCriticalSection(&csIpodctl);
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    if(!testipod->GetIndexedPlayingTrackAlbumName(trackIndex,albumName))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}
ipodctlERR ipodctl_GetPlayingTrackNum(unsigned long* trackNum)
{
   EnterCsCtlCriticalSection(&csIpodctl);
    if(NULL==hConnectThread)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTINIT;
    }
    if(!bCnntbleIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_IPODEXIT;
    }
    if(!bConnectedIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTCNNT;
    }
    U32 u32totle;
    if(NULL==trackNum)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_BADPARAM;
    }
    if(!testipod->GetNumPlayingTracks(&u32totle))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    *trackNum = u32totle;
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}
ipodctlERR ipodctl_SetCurrentPlayingTrack(unsigned long trackIndex)
{
   EnterCsCtlCriticalSection(&csIpodctl);
    if(NULL==hConnectThread)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTINIT;
    }
    if(!bCnntbleIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_IPODEXIT;
    }
    if(!bConnectedIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTCNNT;
    }
    if(!testipod->SetCurrentPlayingTrack(trackIndex))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}
ipodctlERR ipodctl_GetArtworkData(unsigned long trackIndex,ipodctlARTWORKSIZE artworkSize,unsigned char *artworkData)
{
   EnterCsCtlCriticalSection(&csIpodctl);
    if(NULL==hConnectThread)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTINIT;
    }
    if(!bCnntbleIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_IPODEXIT;
    }
    if(!bConnectedIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTCNNT;
    }
    if(NULL==artworkData)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_BADPARAM;
    }
    if(!testipod->GetTrackArtworkData(artworkData,trackIndex,artworkSize))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}
ipodctlERR ipodctl_GetShuffle(ipodctlSHUFFLE* shuffleStatus)
{
   EnterCsCtlCriticalSection(&csIpodctl);
    if(NULL==hConnectThread)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTINIT;
    }
    if(!bCnntbleIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_IPODEXIT;
    }
    if(!bConnectedIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTCNNT;
    }
    U8 u8tmp;
    if(NULL==shuffleStatus)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_BADPARAM;
    }
    if(!testipod->GetShuffle(&u8tmp))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    *shuffleStatus = (ipodctlSHUFFLE)u8tmp;
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}
ipodctlERR ipodctl_SetShuffle(ipodctlSHUFFLE shuffleStatus)
{
   EnterCsCtlCriticalSection(&csIpodctl);
    if(NULL==hConnectThread)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTINIT;
    }
    if(!bCnntbleIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_IPODEXIT;
    }
    if(!bConnectedIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTCNNT;
    }
    if(!testipod->SetShuffle(shuffleStatus))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}
ipodctlERR ipodctl_GetRepeat(ipodctlREPEAT* repeatStatus)
{
   EnterCsCtlCriticalSection(&csIpodctl);
    if(NULL==hConnectThread)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTINIT;
    }
    if(!bCnntbleIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_IPODEXIT;
    }
    if(!bConnectedIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTCNNT;
    }
    U8 u8tmp;
    if(NULL==repeatStatus)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_BADPARAM;
    }
    if(!testipod->GetRepeat(&u8tmp))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    *repeatStatus = (ipodctlREPEAT)u8tmp;
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}
ipodctlERR ipodctl_SetRepeat(ipodctlREPEAT repeatStatus)
{
   EnterCsCtlCriticalSection(&csIpodctl);
    if(NULL==hConnectThread)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTINIT;
    }
    if(!bCnntbleIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_IPODEXIT;
    }
    if(!bConnectedIpodctl)
    {
        LeaveCsCtlCriticalSection(&csIpodctl);
        return ERR_NOTCNNT;
    }
    //if(NULL==repeatStatus)
    //{
    //    LeaveCsCtlCriticalSection(&csIpodctl);
    //    return ERR_BADPARAM;
    //}
    if(!testipod->SetRepeat(repeatStatus))
    {
        if(bCnntbleIpodctl)
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_FAIL;
        }
        else
        {
            LeaveCsCtlCriticalSection(&csIpodctl);
            return ERR_IPODEXIT;
        }
    }
    LeaveCsCtlCriticalSection(&csIpodctl);
    return ERR_OK;
}

ipodctlERR  ipodctl_GetDBiTunesinfo(unsigned char cType)
{
	EnterCsCtlCriticalSection(&csIpodctl);
	if(NULL==hConnectThread)
	{
		LeaveCsCtlCriticalSection(&csIpodctl);
		return ERR_NOTINIT;
	}
	if(!bCnntbleIpodctl)
	{
		LeaveCsCtlCriticalSection(&csIpodctl);
		return ERR_IPODEXIT;
	}
	if(!bConnectedIpodctl)
	{
		LeaveCsCtlCriticalSection(&csIpodctl);
		return ERR_NOTCNNT;
	}

	if(!testipod->GetDBiTunesInfo(cType))
	{
		if(bCnntbleIpodctl)
		{
			LeaveCsCtlCriticalSection(&csIpodctl);
			return ERR_FAIL;
		}
		else
		{
			LeaveCsCtlCriticalSection(&csIpodctl);
			return ERR_IPODEXIT;
		}
	}
	LeaveCsCtlCriticalSection(&csIpodctl);
	return ERR_OK;
}



ipodctlERR   ipodctl_GetDBTrackinfo(unsigned long nStart,unsigned long nCount,unsigned char cBitMask)
{
	EnterCsCtlCriticalSection(&csIpodctl);
	if(NULL==hConnectThread)
	{
		LeaveCsCtlCriticalSection(&csIpodctl);
		return ERR_NOTINIT;
	}
	if(!bCnntbleIpodctl)
	{
		LeaveCsCtlCriticalSection(&csIpodctl);
		return ERR_IPODEXIT;
	}
	if(!bConnectedIpodctl)
	{
		LeaveCsCtlCriticalSection(&csIpodctl);
		return ERR_NOTCNNT;
	}

	if(!testipod->GetDBTrackinfo(nStart,nCount,cBitMask))
	{
		if(bCnntbleIpodctl)
		{
			LeaveCsCtlCriticalSection(&csIpodctl);
			return ERR_FAIL;
		}
		else
		{
			LeaveCsCtlCriticalSection(&csIpodctl);
			return ERR_IPODEXIT;
		}
	}
	LeaveCsCtlCriticalSection(&csIpodctl);
	return ERR_OK;
}




ipodctlERR ipodctl_GetNumberCategorizedDBRecords(ipodctlPAGE iPage,unsigned long *pnTotal)
{
	EnterCsCtlCriticalSection(&csIpodctl);
	if(NULL==hConnectThread)
	{
		LeaveCsCtlCriticalSection(&csIpodctl);
		return ERR_NOTINIT;
	}
	if(!bCnntbleIpodctl)
	{
		LeaveCsCtlCriticalSection(&csIpodctl);
		return ERR_IPODEXIT;
	}
	if(!bConnectedIpodctl)
	{
		LeaveCsCtlCriticalSection(&csIpodctl);
		return ERR_NOTCNNT;
	}
	if(!testipod->GetNumberCategorizedDBRecords(iPage,pnTotal))
	{
		if(bCnntbleIpodctl)
		{
			LeaveCsCtlCriticalSection(&csIpodctl);
			return ERR_FAIL;
		}
		else
		{
			LeaveCsCtlCriticalSection(&csIpodctl);
			return ERR_IPODEXIT;
		}
	}
	printf("iPage = %d,nTotal = %d+++++++=\r\n",iPage,(*pnTotal));
	LeaveCsCtlCriticalSection(&csIpodctl);
	return ERR_OK;
}

ipodctlERR ipodctl_GetCategorizedDBRecords(ipodctlPAGE iPage,unsigned long iStart,unsigned long iCount,unsigned char *p)
{
	EnterCsCtlCriticalSection(&csIpodctl);
	if(NULL==hConnectThread)
	{
		LeaveCsCtlCriticalSection(&csIpodctl);
		return ERR_NOTINIT;
	}
	if(!bCnntbleIpodctl)
	{
		LeaveCsCtlCriticalSection(&csIpodctl);
		return ERR_IPODEXIT;
	}
	if(!bConnectedIpodctl)
	{
		LeaveCsCtlCriticalSection(&csIpodctl);
		return ERR_NOTCNNT;
	}
	if(!testipod->RetrieveCategorizedDatabaseRecords(iPage,iStart,iCount,p))
	{
		if(bCnntbleIpodctl)
		{
			LeaveCsCtlCriticalSection(&csIpodctl);
			return ERR_FAIL;
		}
		else
		{
			LeaveCsCtlCriticalSection(&csIpodctl);
			return ERR_IPODEXIT;
		}
	}
	LeaveCsCtlCriticalSection(&csIpodctl);
	return ERR_OK;
}