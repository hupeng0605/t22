// $Change: 000000 $
// testipod.cpp : Defines the class behaviors for the application.
//
static int nnIpodRead = 0;
#include "stdafx.h"
#include "testipod.h"
BOOL ReadFromIpod(PST_PACKAGE sPackage);
BOOL WriteToIpod(PST_PACKAGE sPackage);
BOOL ReadIpodArtwork(PST_PACKAGE sp);
BOOL ReadCategorizedDatabaseRecords(PST_PACKAGE sp);
void EnterCsReadCriticalSection( LPCRITICAL_SECTION pcsCriticalSection);
void LeaveCsReadCriticalSection( LPCRITICAL_SECTION pcsCriticalSection);

BOOL HandleTarckNewAttributesEx(unsigned char *Command,unsigned long nLen);
HANDLE hIpodhid = NULL;
HANDLE hIpoduac = NULL;
CRITICAL_SECTION csIpodRead ;
CRITICAL_SECTION csCtlCtl;
U16 u16TransID;
U16 nAck = 0;
BOOL bRunTestipod = TRUE;
U32 u32SampleRate;
U32 u32Rate0 = 0;


BOOL HandleTarckNewAttributesEx(unsigned char *Command,unsigned long nLen)
{
	//return FALSE;
	unsigned long uRate = 0;
	if(Command == NULL || nLen < 15)
	{
		return FALSE;
	}
	int i = 0;
	while (Command[i] != 0x55 && i < nLen)
	{
		i++;
	}
	unsigned nLeft = nLen - i - 1;
	if(nLeft < 15)
	{
		return FALSE;
	}
	else
	{
		if(Command[i + 3] == 0x04 && Command[i + 2] == 0x0a)
		{
			uRate = ((U32)Command[i + 6]<<24)+((U32)Command[i + 7]<<16)+((U32)Command[i + 8]<<8)+((U32)Command[i + 9]);
		}
		else
		{
			return FALSE;
		}
		ST_PACKAGE package;
		package.u8Marker = 0x06;//accessoryack
		package.u8LingoID = 0x0A;
		package.u8CommandID =0x00;
		package.pu8CommandData[0] = Command[i +4];
		package.pu8CommandData[1] = Command[i +5];
		package.pu8CommandData[2] = 0x00;
		package.pu8CommandData[3] = 0x04;
		unsigned long uAck = ((U32)Command[i +4] << 8) +((U32)Command[i +5]);
	
		//u16TransID++;
		WriteToIpod(&package);
		u32Rate0 = uRate;
		printf("ack2222++++++++++uRate = %d,nLen = %d,ack = %d+++++++++\r\n",uRate,nLen,uAck);
		//return TRUE;
		
		if(uRate != u32SampleRate && uRate > 0)
		//if(uRate > 0)
		{
			//
			u32SampleRate = u32Rate0;
			U32 dwBytesReturned;
			U16 j;
			WAVEFORMATEX waveform;
			waveform.wFormatTag=1;
			waveform.nChannels=2;
			waveform.nSamplesPerSec=u32SampleRate;
			waveform.nAvgBytesPerSec=0x2b110;
			waveform.nBlockAlign=4;
			waveform.wBitsPerSample=0x10;
			waveform.cbSize=0;
            // printf("DeviceIoControl+++++++ uRate = %d  ++++++++++++\r\n",uRate);
			 if(hIpoduac != NULL)
			 {
				 //u32SampleRate = uRate;
				 printf("Time:%d++1122211+++DeviceIoControl:beg---u32tmprate = %d \r\n",GetTickCount(),u32SampleRate);
				 DeviceIoControl (hIpoduac, IOCTL_IAPL_PCM_SETFORMAT, (LPVOID)&waveform, sizeof(WAVEFORMATEX),NULL, 0, &dwBytesReturned, 0);
				 nAck = uAck;
				 printf("Time:%d++1122211+++DeviceIoControl:end---u32tmprate = %d,lasterr = %d \r\n",GetTickCount(),u32SampleRate,GetLastError());
			 }
			return TRUE;
		}

	}
}
void EnterCsReadCriticalSection( LPCRITICAL_SECTION pcsCriticalSection)
{
#if TESTCRITICALSECTION
	 nnIpodRead++;printf("11111111+++++csIpodRead = %d+++++\r\n",nnIpodRead);
#endif
  EnterCriticalSection(&csIpodRead);
}
void LeaveCsReadCriticalSection( LPCRITICAL_SECTION pcsCriticalSection)
{
   LeaveCriticalSection(&csIpodRead);
#if TESTCRITICALSECTION
   nnIpodRead--;printf("-----csIpodRead = %d----\r\n",nnIpodRead);
#endif
}
void ReadThread()
{
    ST_PACKAGE package;
    U8 pu8Data[1100]={0};
    U32 u32read,u32tmprate,dwBytesReturned;
    U16 j;
    WAVEFORMATEX waveform;
    waveform.wFormatTag=1;
    waveform.nChannels=2;
    waveform.nSamplesPerSec=u32SampleRate;
    waveform.nAvgBytesPerSec=0x2b110;
    waveform.nBlockAlign=4;
    waveform.wBitsPerSample=0x10;
    waveform.cbSize=0;
	//bRunTestipod = FALSE;
    while(bRunTestipod)
    {
       EnterCsReadCriticalSection(&csIpodRead);
      //  RETAILMSG(IPODLOG_THREAD,(TEXT("ReadThread\r\n")));
        //ReadFromIpod(&package);
	   memset(pu8Data,0,sizeof(pu8Data));
        ReadFile(hIpodhid,pu8Data,1026,&u32read,0);
#if DEBUGIPODDATA
		if(u32read > 0 && u32read < 1024)
		{
			printf("Gettick()++++++++++ = %d,len = %d,ReadFromIpod:",GetTickCount(),u32read);
			char tmpBuf[1200] = {0};
			for(int k = 0; k < u32read;k++)
			{
				sprintf_s(tmpBuf, 1100, "%s %02x", tmpBuf, pu8Data[k]);
			}
			printf("%s\r\n",tmpBuf);
			printf("_________u32SampleRate = %d\r\n",u32SampleRate);
		}
#endif
		
        if(0x55==pu8Data[0]&&0x0A==pu8Data[2]&&0x04==pu8Data[3])
        {

            u32tmprate = ((U32)pu8Data[6]<<24)+((U32)pu8Data[7]<<16)+((U32)pu8Data[8]<<8)+((U32)pu8Data[9]);
			u32Rate0 = u32tmprate;
		   printf("gettickcout = %d,u32SampleRate = %d\r\n",GetTickCount(),u32SampleRate);
		   unsigned long uAck11 = ((U32)pu8Data[4] << 8) +((U32)pu8Data[5]);
		   printf("AcK11++++++++++++++uack = %d+++++\r\n",uAck11);	
#if DEBUGIPODDATA
        printf("u32SampleRate = %d\r\n",u32SampleRate);
#endif
           if(u32tmprate!=u32SampleRate)
		   // if(u32tmprate > 0)
            {
                package.u8Marker = 0x06;
                package.u8LingoID = 0x04;
                package.u8CommandID =0x00;
                package.pu8CommandData[0] = 0x29;
                package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
                package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
                package.pu8CommandData[3] = PLAY_CONTROL_TOGGLE_PLAYPAUSE;
                u16TransID++;
                WriteToIpod(&package);
                waveform.nSamplesPerSec=u32tmprate;
                //u32SampleRate = u32tmprate;
				ST_PACKAGE package;
				package.u8Marker = 0x06;//accessoryack
				package.u8LingoID = 0x0A;
				package.u8CommandID =0x00;
				package.pu8CommandData[0] = pu8Data[4];
				package.pu8CommandData[1] = pu8Data[5];
				package.pu8CommandData[2] = 0x00;
				package.pu8CommandData[3] = 0x04;
				//u16TransID++;
				WriteToIpod(&package);//ack
				unsigned long uAck = ((U32)pu8Data[4] << 8) +((U32)pu8Data[5]);
				printf("AcK++++++++++++++uack = %d+++++\r\n",uAck);	
				//if(hIpoduac != NULL && uAck  > nAck)
			 if(hIpoduac != NULL)
			 {
				/* u16TransID++;
				 WriteToIpod(&package);*/
				  u32SampleRate = u32tmprate;
				 printf("Time:%d+++++DeviceIoControl:beg---u32tmprate = %d \r\n",GetTickCount(),u32tmprate);
				 BOOL bRet = DeviceIoControl (hIpoduac, IOCTL_IAPL_PCM_SETFORMAT, (LPVOID)&waveform, sizeof(WAVEFORMATEX),NULL, 0, &dwBytesReturned, 0);
				 nAck = uAck;
				 printf("Time:%d+++++DeviceIoControl:end---u32tmprate = %d,bret = %d,getlasterr = %d \r\n",GetTickCount(),u32tmprate,bRet,GetLastError());
			 }
                package.u8Marker = 0x06;
                package.u8LingoID = 0x04;
                package.u8CommandID =0x00;
                package.pu8CommandData[0] = 0x29;
                package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
                package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
                package.pu8CommandData[3] = PLAY_CONTROL_TOGGLE_PLAYPAUSE;
                u16TransID++;
                WriteToIpod(&package);
            }
			else
			{
				ST_PACKAGE package;
				package.u8Marker = 0x06;//accessoryack
				package.u8LingoID = 0x0A;
				package.u8CommandID =0x00;
				package.pu8CommandData[0] = pu8Data[4];
				package.pu8CommandData[1] = pu8Data[5];
				package.pu8CommandData[2] = 0x00;
				package.pu8CommandData[3] = 0x04;
				//u16TransID++;
				WriteToIpod(&package);//ack
				unsigned long uAck = ((U32)pu8Data[4] << 8) +((U32)pu8Data[5]);
				waveform.nSamplesPerSec=u32tmprate;
				//DeviceIoControl (hIpoduac, IOCTL_IAPL_PCM_SETFORMAT, (LPVOID)&waveform, sizeof(WAVEFORMATEX),NULL, 0, &dwBytesReturned, 0);
				printf("AcK22++++++++++++++uack 22222333= %d+++++\r\n",uAck);	
			}
		
        }
		else
		{
			if(u32Rate0 != u32SampleRate && u32Rate0 != 0 && FALSE)
			{
				u32SampleRate = u32Rate0;
                 package.u8Marker = 0x06;
                package.u8LingoID = 0x04;
                package.u8CommandID =0x00;
                package.pu8CommandData[0] = 0x29;
                package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
                package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
                package.pu8CommandData[3] = PLAY_CONTROL_TOGGLE_PLAYPAUSE;
                u16TransID++;
                WriteToIpod(&package);
                waveform.nSamplesPerSec=u32SampleRate;
                //u32SampleRate = u32tmprate;
				ST_PACKAGE package;
				package.u8Marker = 0x06;//accessoryack
				package.u8LingoID = 0x0A;
				package.u8CommandID =0x00;
				package.pu8CommandData[0] = pu8Data[4];
				package.pu8CommandData[1] = pu8Data[5];
				package.pu8CommandData[2] = 0x00;
				package.pu8CommandData[3] = 0x04;
				//u16TransID++;
				WriteToIpod(&package);//ack
				unsigned long uAck = ((U32)pu8Data[4] << 8) +((U32)pu8Data[5]);
				printf("AcK333++++++++++++++uack333 = %d+++++\r\n",uAck);
			 if(hIpoduac != NULL)
			 {
				 // u32SampleRate = u32tmprate;
				 printf("Time:%d+++++DeviceIoControl:beg11---u32tmprate = %d \r\n",GetTickCount(),u32SampleRate);
				// Sleep(100);
				 DeviceIoControl (hIpoduac, IOCTL_IAPL_PCM_SETFORMAT, (LPVOID)&waveform, sizeof(WAVEFORMATEX),NULL, 0, &dwBytesReturned, 0);
				 nAck = uAck;
				 printf("Time:%d+++++DeviceIoControl:end111---u32tmprate = %d,getlasterr = %d \r\n",GetTickCount(),u32SampleRate,GetLastError());
			 }
                package.u8Marker = 0x06;
                package.u8LingoID = 0x04;
                package.u8CommandID =0x00;
                package.pu8CommandData[0] = 0x29;
                package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
                package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
                package.pu8CommandData[3] = PLAY_CONTROL_TOGGLE_PLAYPAUSE;
                u16TransID++;
                WriteToIpod(&package);
			}
		}
        LeaveCsReadCriticalSection(&csIpodRead);
        Sleep(150);
    }
}
TestIpod::TestIpod()
{
	hI2c = NULL;
	hReadThread = NULL;
	u32DeviceID = 0;
	u8MajorVersion = 0;
	u8MinorVersion = 0;
	i2cReadAdd = 0;
	i2cWriteAdd = 0;
	m_bReadThread = false;
	m_bReadThreadSup = false;
	m_hIpodReady  = CreateEvent( NULL, TRUE, FALSE, TEXT("IPOD_READY"));
	 InitializeCriticalSection(&csIpodRead);
}
TestIpod::~TestIpod()
{
	 hI2c = NULL;
	 hReadThread = NULL;
	 u32DeviceID = 0;
	 u8MajorVersion = 0;
	 u8MinorVersion = 0;
	 i2cReadAdd = 0;
	 i2cWriteAdd = 0;
	 m_bReadThreadSup = false;
	 DeleteCriticalSection(&csIpodRead);
	 CloseHandle(m_hIpodReady);
}
BOOL TestIpod::Connect()
{
    u16TransID=0;
    if(CP_MODE0_0==GetCPMode0())
    {
        i2cReadAdd = 0x20;
        i2cWriteAdd = 0x20;
    }
    else
    {
        i2cReadAdd = 0x23;
        i2cWriteAdd = 0x22;
    }
   // return (OpenDevice()&&ConnectToIpod());
	return (OpenDeviceEx()&&ConnectToIpod());
}

BOOL TestIpod::OpenDeviceEx()
{
	int nTry = 0;
	while (nTry < 5)
	{
		hI2c = CreateFile(L"I2C2:",GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if(INVALID_HANDLE_VALUE==hI2c)
		{
			RETAILMSG(IPODLOG_EER,(_T("open i2c fail\r\n")));
			printf("open i2c fail\r\n,getlasterr = %d,nTry = %d",GetLastError(),nTry);
			nTry++;
			Sleep(600);
		}
		else
		{
			break;
		}
	}
	if(nTry >= 5 && INVALID_HANDLE_VALUE==hI2c)
	{
       return FALSE;
	}
	
	nTry = 0;
	while (nTry < 5)
	{
		hIpodhid = CreateFile(_T("POD1:"),GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL );
		if(INVALID_HANDLE_VALUE== hIpodhid)
		{
			RETAILMSG(IPODLOG_EER,(_T("open hIpodhid fail\r\n")));
			printf("open hIpodhid fail\r\n,getlasterr = %d,nTry = %d",GetLastError(),nTry);
			nTry++;
			Sleep(600);
		}
		else
		{
			break;
		}
	}
	if(nTry >= 5 && INVALID_HANDLE_VALUE== hIpodhid)
	{
      return FALSE;
	}
	nTry = 0;
	while (nTry < 5)
	{
		hIpoduac = CreateFile(_T("APL1:"),GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL );
		if(INVALID_HANDLE_VALUE== hIpoduac)
		{
			RETAILMSG(IPODLOG_EER,(_T("open hIpoduac fail\r\n")));
			printf("open hIpoduac fail\r\n,getlasterr = %d,nTry = %d",GetLastError(),nTry);
			nTry++;
			Sleep(600);
		}
		else
		{
			break;
		}
	}
	if(nTry >= 5  && INVALID_HANDLE_VALUE== hIpoduac)
	{
		return FALSE;
	}
	bRunTestipod = TRUE;
	if((hReadThread == NULL || hReadThread == INVALID_HANDLE_VALUE) && !m_bReadThread && !m_bReadThreadSup)
	{
		hReadThread = CreateThread(NULL, 0, ((LPTHREAD_START_ROUTINE)ReadThread), NULL, 0, NULL);
		if(hReadThread != INVALID_HANDLE_VALUE)
		{
			m_bReadThread = true;
			m_bReadThreadSup = false;
		}
		else
		{
			printf("hReadThread:GetLasterror = %d\r\n",GetLastError());
		}
		printf("Create Thread:ReadThread\r\n");
	}
	else if(hReadThread != NULL && hReadThread != INVALID_HANDLE_VALUE && m_bReadThreadSup)
	{
		DWORD nRet = ResumeThread(hReadThread);
		if(nRet == 0xffff)
		{
			printf("ResumeThread failed\r\n");
		}
		else
		{
			m_bReadThreadSup = false;
			printf("ResumeThread sucess nRet = %d\r\n",nRet);
		}
	}
	return TRUE;
}
BOOL TestIpod::OpenDevice()
{
    hI2c = CreateFile( L"I2C2:",
                        GENERIC_READ | GENERIC_WRITE,
                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL );
    if(INVALID_HANDLE_VALUE==hI2c)
    {
        RETAILMSG(IPODLOG_EER,(_T("open i2c fail\r\n")));
		printf("open i2c fail\r\n,getlasterr = %d",GetLastError());
        return FALSE;
    }
    hIpodhid = CreateFile(_T("POD1:"),
                        GENERIC_READ|GENERIC_WRITE,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL );
    if(INVALID_HANDLE_VALUE==hIpodhid)
    {
        CloseHandle(hI2c);
        RETAILMSG(IPODLOG_EER,(_T("open ipodhid fail\r\n")));
		printf("open ipodhid fail\r\n,getlasterr = %d",GetLastError());
        return FALSE;
    }
    hIpoduac = CreateFile(_T("APL1:"),
                        GENERIC_READ|GENERIC_WRITE,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL );
    if(INVALID_HANDLE_VALUE==hIpoduac)
    {
        CloseHandle(hI2c);
        CloseHandle(hIpodhid);
        RETAILMSG(IPODLOG_EER,(_T("open APL1 fail\r\n")));
		printf("open APL1 fail\r\n,getlasterr = %d",GetLastError());
        return FALSE;
    }
 //   InitializeCriticalSection(&csIpodRead);
    bRunTestipod = TRUE;
	if((hReadThread == NULL || hReadThread == INVALID_HANDLE_VALUE) && !m_bReadThread && !m_bReadThreadSup)
	{
		  hReadThread = CreateThread(NULL, 0, ((LPTHREAD_START_ROUTINE)ReadThread), NULL, 0, NULL);
		  if(hReadThread != INVALID_HANDLE_VALUE)
		  {
			  m_bReadThread = true;
			  m_bReadThreadSup = false;
		  }
		  else
		  {
			  printf("hReadThread:GetLasterror = %d\r\n",GetLastError());
		  }
		  printf("Create Thread:ReadThread\r\n");
	}
	else if(hReadThread != NULL && hReadThread != INVALID_HANDLE_VALUE && m_bReadThreadSup)
	{
		DWORD nRet = ResumeThread(hReadThread);
		if(nRet == 0xffff)
		{
			printf("ResumeThread failed\r\n");
		}
		else
		{
			m_bReadThreadSup = false;
			printf("ResumeThread sucess nRet = %d\r\n",nRet);
		}
	}
    return TRUE;
}
void TestIpod::CloseDevice()
{
	ResetIpodReadyEvent();
	printf("CloseDevice  beg\r\n");
	if(INVALID_HANDLE_VALUE!=hReadThread && hReadThread != NULL)
	{
	     
		//nnIpodRead++;printf("+++++csIpodRead = %d+++++\r\n",nnIpodRead);EnterCriticalSection(&csIpodRead);
		DWORD dwRet = SuspendThread(hReadThread);
		//LeaveCsReadCriticalSection(&csIpodRead);
		if(dwRet == 0xFFFF)
		{
			printf("SuspendThread failed\r\n");
			bRunTestipod = FALSE;
			DWORD dRet = WaitForSingleObject(hReadThread,2000);
			switch(dRet)
			{
			case WAIT_OBJECT_0:
				{
					printf("hReadThread exit sucess\r\n");
				}
				break;
			case WAIT_TIMEOUT:
				{
					printf("hReadThread exit timeout\r\n");
					::TerminateThread(hReadThread, 10);
				}
				break;
				CloseHandle(hReadThread);
				m_bReadThread = false;
				hReadThread = NULL;
				m_bReadThreadSup = false;
			}
		}
		else
		{
			printf("SuspendThread sucess dwRet = %d\r\n",dwRet);
			m_bReadThread = false;
			m_bReadThreadSup = TRUE;
		}
		//CloseHandle(hReadThread);
		//m_bReadThread = false;
		// hReadThread = NULL;
	}
    if(INVALID_HANDLE_VALUE!=hI2c)
    {
        CloseHandle(hI2c);
        hI2c = NULL;
    }
    if(INVALID_HANDLE_VALUE!=hIpodhid)
    {
        CloseHandle(hIpodhid);
        hIpodhid = NULL;
    }
    if(INVALID_HANDLE_VALUE!=hIpoduac)
    {
        CloseHandle(hIpoduac);
        hIpoduac = NULL;
    }
  //  bRunTestipod = FALSE;
    //DeleteCriticalSection(&csIpodRead);

	printf("CloseDevice  end\r\n");
    u16TransID = 0;
}
BOOL TestIpod::ConnectToIpod()
{
    U32 bRet,tmp,dwBytesReturned;
    tmp = 0;
    bRet = DeviceIoControl (hI2c, IOCTL_I2C_GPIO_CTL, (LPVOID)&tmp, sizeof(DWORD),
                                NULL, 0, &dwBytesReturned, 0);
    if(!bRet)
    {
        RETAILMSG(IPODLOG_EER,(_T("IOCTL_I2C_GPIO_CTL fail\r\n")));
        CloseDevice();
        return FALSE;
    }
    Sleep(10);
    tmp = 1;
    bRet = DeviceIoControl (hI2c, IOCTL_I2C_GPIO_CTL, (LPVOID)&tmp, sizeof(DWORD),
                                NULL, 0, &dwBytesReturned, 0);
    if(!bRet)
    {
        RETAILMSG(IPODLOG_EER,(_T("IOCTL_I2C_GPIO_CTL fail\r\n")));
        CloseDevice();
        return FALSE;
    }
   EnterCsReadCriticalSection(&csIpodRead);
    if(!StartIDPS(COMMAND_u8Retry))
    {
        RETAILMSG(IPODLOG_EER,(_T("StartIDPS fail\r\n")));
        LeaveCsReadCriticalSection(&csIpodRead);
        CloseDevice();
        return FALSE;
    }
	unsigned long uMaxSize;
	//EnterCsReadCriticalSection(&csIpodRead);
	if(!GetMaxPayloadSize(&uMaxSize))
	{
        LeaveCsReadCriticalSection(&csIpodRead);
		CloseDevice();
		return FALSE;
	}
    if(!SetFIDTokenValues())
    {
        RETAILMSG(IPODLOG_EER,(_T("SetFIDTokenValues fail\r\n")));
        LeaveCsReadCriticalSection(&csIpodRead);
        CloseDevice();
        return FALSE;
    }
    if(!EndIDPS())
    {
        RETAILMSG(IPODLOG_EER,(_T("EndIDPS fail\r\n")));
        LeaveCsReadCriticalSection(&csIpodRead);
        CloseDevice();
        return FALSE;
    }
    if(!RetDevAuthenticationInfo())
    {
        RETAILMSG(IPODLOG_EER,(_T("RetDevAuthenticationInfo fail\r\n")));
        LeaveCsReadCriticalSection(&csIpodRead);
        CloseDevice();
        return FALSE;
    }
    if(!RetDevAuthenticationSignature())
    {
        RETAILMSG(IPODLOG_EER,(_T("RetDevAuthenticationSignature fail\r\n")));
        LeaveCsReadCriticalSection(&csIpodRead);
        CloseDevice();
        return FALSE;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    return TRUE;
}
BOOL TestIpod::IpodAuthenticationAcc()
{
    return TRUE;
}
BOOL TestIpod::AccAuthenticationIpod()
{
    if(!GetiPodAuthenticationInfo())
    {
        RETAILMSG(IPODLOG_EER,(_T("GetiPodAuthenticationInfo fail\r\n")));
        return FALSE;
    }
    if(!GetiPodAuthenticationSignature())
    {
        RETAILMSG(IPODLOG_EER,(_T("GetiPodAuthenticationSignature fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::StartPlay()
{
    /*ResetDBSelection();
    SelectDBRecord(CATEGORY_TYPE_ARTIST,1);
    PlayCurrentSelection(0);*/
    WAVEFORMATEX waveform;
    U32 dwstart=1;
    U32 bRet,dwBytesReturned;
    U8 u8tmp;
    /*if(!RetAccSampleRateCaps())
    {
        RETAILMSG(1,(_T("RetAccSampleRateCaps fail\r\n")));
        return FALSE;
    }*/
    waveform.wFormatTag=1;
    waveform.nChannels=2;
    waveform.nSamplesPerSec=u32SampleRate;
    waveform.nAvgBytesPerSec=0x2b110;
    waveform.nBlockAlign=4;
    waveform.wBitsPerSample=0x10;
    waveform.cbSize=0;
   // bRet = DeviceIoControl (hIpoduac, IOCTL_IAPL_PCM_SETFORMAT, (LPVOID)&waveform, sizeof(WAVEFORMATEX),NULL, 0, &dwBytesReturned, 0);
	if(hIpoduac != NULL)
	{
		bRet = DeviceIoControl (hIpoduac, IOCTL_IAPL_PCM_SETFORMAT, (LPVOID)&waveform, sizeof(WAVEFORMATEX),NULL, 0, &dwBytesReturned, 0);
	}                          
	printf("++++++DeviceIoControl::u32SampleRate = %d+++++\r\n",u32SampleRate);
    if(bRet)
    {
        RETAILMSG(IPODLOG_EER,(TEXT("IOCTL_IAPL_PCM_SETFORMAT success\r\n")));
    }
    else
    {
        RETAILMSG(IPODLOG_EER,(TEXT("IOCTL_IAPL_PCM_SETFORMAT fail\r\n")));
        return FALSE;
    }
    if(!SetUIMode())
    {
        RETAILMSG(IPODLOG_EER,(_T("SetUIMode fail\r\n")));
        return FALSE;
    }
/*    if(!ResetDBSelection())
    {
        RETAILMSG(IPODLOG_EER,(_T("ResetDBSelection fail\r\n")));
        return FALSE;
    }
    if(!SelectDBRecord(CATEGORY_TYPE_PLAYLIST,0))
    {
        RETAILMSG(IPODLOG_EER,(_T("SelectDBRecord fail\r\n")));
        return FALSE;
    }
    if(!PlayCurrentSelection(0))
    {
        RETAILMSG(IPODLOG_EER,(_T("PlayCurrentSelection fail\r\n")));
        return FALSE;
    }
    if(!PlayControl(PLAY_CONTROL_TOGGLE_PLAYPAUSE))
    {
        RETAILMSG(IPODLOG_EER,(_T("PlayControl fail\r\n")));
        return FALSE;
    }*/
    bRet = DeviceIoControl (hIpoduac, IOCTL_IAPL_ISSUE_ISO_TRF, (LPVOID)&dwstart, sizeof(U32),
                                NULL, 0, &dwBytesReturned, 0);
    if(bRet)
    {
        RETAILMSG(IPODLOG_EER,(TEXT("IOCTL_IAPL_ISSUE_ISO_TRF success\r\n")));
    }
    else
    {
        RETAILMSG(IPODLOG_EER,(TEXT("IOCTL_IAPL_ISSUE_ISO_TRF fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
enumCPMode0 TestIpod::GetCPMode0()
{
    return CP_MODE0_0;
}
U16 TestIpod::ReadAccCerData(U8 *pu8data)
{
    U16 len,i=0,j=0;
    U8 tmp[2]={0};
    if(NULL ==pu8data) return 0;
    if(!ReadI2c(ACC_CERTI_DATA_LEN,tmp,2)) return 0;
    len = ((U16)tmp[0]<<8)+((U16)tmp[1]);
    while(len)
    {
        if(len>=128)
        {
            if(!ReadI2c(ACC_CERTI_DATA+i,pu8data+j,128)) return 0;
            i++;
            j+=128;
            len-=128;
        }
        else
        {
            if(!ReadI2c(ACC_CERTI_DATA+i,pu8data+j,len)) return 0;
            j+=len;
            len=0;
        }
    }
    return j;
}
BOOL TestIpod::StartIDPS(U8 u8Retry)
{
    ST_PACKAGE package;
    U16 u16tid;
    ReadFromIpod(&package);
	memset(&package,0,sizeof(package));//add 0722
    //1StartIDPS
    package.u8Marker = 0x04;
    package.u8LingoID = 0x00;
    package.u8CommandID = 0x38;
    package.pu8CommandData[0] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[1] = (U8)(u16TransID&0xFF);
    u16tid = u16TransID++;
    if(!WriteToIpod(&package))
    {
        return FALSE;
    }
    //1ACK
    while(u8Retry--)
    {
        if(!ReadFromIpod(&package)) continue;
        if(package.u8LingoID!=0x00||package.u8CommandID!=0x02||((U16)(package.pu8CommandData[0])<<8|(U16)(package.pu8CommandData[1]))!=u16tid)
        {
            Sleep(50);
            continue;
        }
        if(0==package.pu8CommandData[2])
        {
            return TRUE;
        }
        else
        {
            RETAILMSG(IPODLOG_EER,(_T("not support IDPS ACK")));
            return FALSE;
        }
    }
    RETAILMSG(IPODLOG_EER,(_T("no correct startIDPS ACK")));
    return FALSE;
}
BOOL TestIpod::GetMaxPayloadSize(unsigned long *plMaxSize)
{
    ST_PACKAGE package;
	U16 u16tid;
	package.u8Marker = 0x04;
	package.u8LingoID = 0x00;
	package.u8CommandID = 0x11;
	package.pu8CommandData[0] = (U8)((u16TransID>>8)&0xFF);
	package.pu8CommandData[1] = (U8)(u16TransID&0xFF);
	u16tid = u16TransID++;
	if(!WriteToIpod(&package))
	{
		return FALSE;
	}
     char u8Retry = 8;
	while(u8Retry--)
	{
		if(!ReadFromIpod(&package)) continue;
		if(package.u8LingoID!=0x00||package.u8CommandID!=0x12||((U16)(package.pu8CommandData[0])<<8|(U16)(package.pu8CommandData[1]))!=u16tid)
		{
			Sleep(50);
			continue;
		}
           if(plMaxSize != NULL)
		   {
			   *plMaxSize = package.pu8CommandData[2]>>8 +package.pu8CommandData[3];
			   printf("+++++++++GetMaxPayloadSize::MaxSize = %d++++++++++++++\r\n",*plMaxSize);
		   }
			return TRUE;
	
	}
	//RETAILMSG(IPODLOG_EER,(_T("no correct startIDPS ACK")));
	return FALSE;
}
BOOL TestIpod::SetFIDTokenValues()
{
    ST_PACKAGE package;
    U16 u16tid;
    U16 j=0;
    U16 len;
    U8 pu8deviceid[4];
    U8 u8retry=10;
    ReadI2c(DEVICE_VERSION,pu8deviceid,4);
    u32DeviceID = *((U32 *)pu8deviceid);
    //1SetFIDTokenValues
    package.u8LingoID = 0x00;
    package.u8CommandID = 0x39;
    package.pu8CommandData[j++] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[j++] = (U8)(u16TransID&0xFF);
    package.pu8CommandData[j++] = 0x0D; //fid num
    package.pu8CommandData[j++] = 0x0F; //len
    package.pu8CommandData[j++] = 0x00; //token id
    package.pu8CommandData[j++] = 0x00; //token id
    package.pu8CommandData[j++] = 0x04; //lingo num
    package.pu8CommandData[j++] = 0x00; //general lingo
    package.pu8CommandData[j++] = 0x03;
    package.pu8CommandData[j++] = 0x04; //extended protrol
    package.pu8CommandData[j++] = 0x0A;
    package.pu8CommandData[j++] = 0x00; //device options
    package.pu8CommandData[j++] = 0x00; //device options
    package.pu8CommandData[j++] = 0x00; //device options
    package.pu8CommandData[j++] = 0x02; //device options
    package.pu8CommandData[j++] = 0x00;//device id
    package.pu8CommandData[j++] = 0x00;//device id
    package.pu8CommandData[j++] = 0x02;//device id
    package.pu8CommandData[j++] = 0x00;//device id
    package.pu8CommandData[j++] = 0x0A; //len
    package.pu8CommandData[j++] = 0x00; //token id
    package.pu8CommandData[j++] = 0x01; //token id
    package.pu8CommandData[j++] = 0x00; //Accessory capabilities???????
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x14;//?????14
    package.pu8CommandData[j++] = 0x0A; //len
    package.pu8CommandData[j++] = 0x00; //token id
    package.pu8CommandData[j++] = 0x02; //token id
    package.pu8CommandData[j++] = 0x01; //Accessory info type
    package.pu8CommandData[j++] = 0x4D;
    package.pu8CommandData[j++] = 0x53;
    package.pu8CommandData[j++] = 0x54;
    package.pu8CommandData[j++] = 0x37;
    package.pu8CommandData[j++] = 0x38;
    package.pu8CommandData[j++] = 0x36;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x06; //len
    package.pu8CommandData[j++] = 0x00; //token id
    package.pu8CommandData[j++] = 0x02; //token id
    package.pu8CommandData[j++] = 0x04; //Accessory firmware version
    package.pu8CommandData[j++] = 0x01;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x06; //len
    package.pu8CommandData[j++] = 0x00; //token id
    package.pu8CommandData[j++] = 0x02; //token id
    package.pu8CommandData[j++] = 0x05; //Accessory hardware version
    package.pu8CommandData[j++] = 0x01;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x09; //len
    package.pu8CommandData[j++] = 0x00; //token id
    package.pu8CommandData[j++] = 0x02; //token id
    package.pu8CommandData[j++] = 0x06; //Accessory manufacturer
    package.pu8CommandData[j++] = 0x4D;
    package.pu8CommandData[j++] = 0x53;
    package.pu8CommandData[j++] = 0x54;
    package.pu8CommandData[j++] = 0x41;
    package.pu8CommandData[j++] = 0x52;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x08; //len
    package.pu8CommandData[j++] = 0x00; //token id
    package.pu8CommandData[j++] = 0x02; //token id
    package.pu8CommandData[j++] = 0x07; //Accessory model number
    package.pu8CommandData[j++] = 0x31;
    package.pu8CommandData[j++] = 0x32;
    package.pu8CommandData[j++] = 0x33;
    package.pu8CommandData[j++] = 0x34;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x07; //len
    package.pu8CommandData[j++] = 0x00; //token id
    package.pu8CommandData[j++] = 0x02; //token id
    package.pu8CommandData[j++] = 0x0C; //Accessory RF certifications
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x05; //len 05 00 03 00 01 01
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x03;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x01;
    package.pu8CommandData[j++] = 0x01;
    package.pu8CommandData[j++] = 0x05; //len 05 00 03 01 00 01
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x03;
    package.pu8CommandData[j++] = 0x01;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x01;
    package.pu8CommandData[j++] = 0x05; //len 05 00 03 02 00 01
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x03;
    package.pu8CommandData[j++] = 0x02;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x01;
    package.pu8CommandData[j++] = 0x05; //len 05 00 03 08 01 01
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x03;
    package.pu8CommandData[j++] = 0x08;
    package.pu8CommandData[j++] = 0x01;
    package.pu8CommandData[j++] = 0x01;
    package.pu8CommandData[j++] = 0x05; //len 05 00 03 0A 01 01
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x03;
    package.pu8CommandData[j++] = 0x0A;
    package.pu8CommandData[j++] = 0x01;
    package.pu8CommandData[j++] = 0x01;
    u16tid = u16TransID++;
    package.u8Marker = j+2;
    if(!WriteToIpod(&package))
    {
        return FALSE;
    }
    //1RetFIDTokenValueACKs
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8LingoID!=0x00||package.u8CommandID!=0x3A||(((U16)(package.pu8CommandData[0])<<8)|(U16)(package.pu8CommandData[1]))!=u16tid)
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker)
        {
            len = package.u8Marker;
        }
        else
        {
            len = ((U16)(package.u8PackageLenH)<<8)|(U16)(package.u8PackageLenL);
        }
        j=3;
        if(package.pu8CommandData[j+3]!=0x00)
        {
            u8retry--;
            continue;
        }
        j+=(package.pu8CommandData[j]+1);
        if(package.pu8CommandData[j+3]!=0x00)
        {
            u8retry--;
            continue;
        }
        j+=(package.pu8CommandData[j]+1);
        if(package.pu8CommandData[j+3]!=0x00)
        {
            u8retry--;
            continue;
        }
        j+=(package.pu8CommandData[j]+1);
        if(package.pu8CommandData[j+3]!=0x00)
        {
            u8retry--;
            continue;
        }
        j+=(package.pu8CommandData[j]+1);
        if(package.pu8CommandData[j+3]!=0x00)
        {
            u8retry--;
            continue;
        }
        j+=(package.pu8CommandData[j]+1);
        if(package.pu8CommandData[j+3]!=0x00)
        {
            u8retry--;
            continue;
    	  }
        j+=(package.pu8CommandData[j]+1);
        if(package.pu8CommandData[j+3]!=0x00)
        {
            u8retry--;
            continue;
        }
        j+=(package.pu8CommandData[j]+1);
        if(package.pu8CommandData[j+3]!=0x00)
        {
            u8retry--;
            continue;
        }
        j+=(package.pu8CommandData[j]+1);
        if(package.pu8CommandData[j+3]!=0x00)
        {
            u8retry--;
            continue;
        }
        j+=(package.pu8CommandData[j]+1);
        if(package.pu8CommandData[j+3]!=0x00)
        {
            u8retry--;
            continue;
        }
        j+=(package.pu8CommandData[j]+1);
        if(package.pu8CommandData[j+3]!=0x00)
        {
            u8retry--;
            continue;
        }
        j+=(package.pu8CommandData[j]+1);
        if(package.pu8CommandData[j+3]!=0x00)
        {
            u8retry--;
            continue;
        }
        j+=(package.pu8CommandData[j]+1);
        if(package.pu8CommandData[j+3]!=0x00)
        {
            u8retry--;
            continue;
        }
        break;
    }
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(TEXT("not support FIDTokenValue\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::EndIDPS()
{
    ST_PACKAGE package;
    U16 u16tid;
    U16 j=0;
    U8 u8retry=10;
    //1EndIDPS
    package.u8Marker = 0x05;
    package.u8LingoID = 0x00;
    package.u8CommandID = 0x3B;
    package.pu8CommandData[j++] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[j++] = (U8)(u16TransID&0xFF);
    package.pu8CommandData[j++] = 0x00;
    u16tid = u16TransID++;
    if(!WriteToIpod(&package))
    {
        return FALSE;
    }
    //1IDPSStatus
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8LingoID!=0x00||package.u8CommandID!=0x3C||(((U16)(package.pu8CommandData[0])<<8)|(U16)(package.pu8CommandData[1]))!=u16tid||package.u8Marker!=0x05)
        {
            u8retry--;
            continue;
        }
        if(package.pu8CommandData[2]!=0x00)
        {
            u8retry--;
            continue;
        }
        break;
    }
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("EndIDPS fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::RetDevAuthenticationInfo()
{
    ST_PACKAGE package;
    U16 j=0;
    U8 u8retry=10;
    //1GetDevAuthenticationInfo
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8LingoID!=0x00||package.u8CommandID!=0x14||package.u8Marker!=0x04)
        {
            u8retry--;
            continue;
        }
        break;
    }
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("GetDevAuthenticationInfo fail\r\n")));
        return FALSE;
    }
    ReadI2c(AUTH_PRO_MAJOR_VER,&u8MajorVersion,1);
    ReadI2c(AUTH_PRO_MINOR_VER,&u8MinorVersion,1);
    U8 pu8data[1920]={0};
    U16 len,u16now=0,k;
    U8 u8secnum,i;
    len = ReadAccCerData(pu8data);
    if(!len) return FALSE;
    //1RetDevAuthenticationInfo
    u8secnum = len/500;
    if(0==len%500) u8secnum--;
    for(i=0;i<u8secnum;i++)
    {
        j=2;
        package.u8LingoID = 0x00;
        package.u8CommandID = 0x15;
        package.pu8CommandData[j++] = u8MajorVersion;
        package.pu8CommandData[j++] = u8MinorVersion;
        package.pu8CommandData[j++] = i;
        package.pu8CommandData[j++] = u8secnum;
        for(k=0;k<500;k++)
        {
            package.pu8CommandData[j++] = pu8data[u16now++];
        }
        package.u8Marker = 0x00;
        package.u8PackageLenH = 0x01;
        package.u8PackageLenL = 0xFC;
        if(!WriteToIpod(&package))
        {
            return FALSE;
        }
        u8retry = 10;
        while(u8retry)
        {
            Sleep(50);
            if(!ReadFromIpod(&package))
            {
                u8retry--;
                continue;
            }
            if(package.u8LingoID!=0||package.u8CommandID!=2)
            {
                u8retry--;
                continue;
            }
            break;
        }
        if(0==u8retry)
        {
            RETAILMSG(IPODLOG_EER,(_T("RetDevAuthenticationInfo fail\r\n")));
            return FALSE;
        }
    }
    j=2;
    package.u8LingoID = 0x00;
    package.u8CommandID = 0x15;
    package.pu8CommandData[j++] = u8MajorVersion;
    package.pu8CommandData[j++] = u8MinorVersion;
    package.pu8CommandData[j++] = u8secnum;
    package.pu8CommandData[j++] = u8secnum;
    while(u16now<len)
    {
        package.pu8CommandData[j++] = pu8data[u16now++];
    }
    j+=2;
    if(j>255)
    {
        package.u8Marker = 0x00;
        package.u8PackageLenH = (U8)((j>>8)&0xFF);
        package.u8PackageLenL = (U8)(j&0xFF);
    }
    else
    {
        package.u8Marker = (U8)j;
    }
    if(!WriteToIpod(&package))
    {
        return FALSE;
    }
    //1AckDevAuthenticationInfo
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x05||package.u8LingoID!=0x00||package.u8CommandID!=0x16||package.pu8CommandData[2]!=0x00)
        {
            u8retry--;
            continue;
        }
        break;
    }
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("AckDevAuthenticationInfo fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::RetDevAuthenticationSignature()
{
    ST_PACKAGE package;
    U16 j=0,len;
    U8 u8retry=10;
    U8 u8tmp,pu8tmp[2]={0};
    U8 challengedata[22];
    //1GetDevAuthenticationSignature
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8LingoID!=0x00||package.u8CommandID!=0x17)
        {
            u8retry--;
            continue;
        }
        break;
    }
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("GetDevAuthenticationSignature fail\r\n")));
        return FALSE;
    }
    challengedata[0]=0x00;
    challengedata[1]=20;
    for(j=2;j<22;j++)
    {
        challengedata[j] = package.pu8CommandData[j];
    }
    //1RetDevAuthenticationSignature
    WriteI2c(CHALLENGE_DATA_LEN,challengedata,22);
    //WriteI2c(CHALLENGE_DATA,challengedata,challengelen);
    u8tmp = 1;
    WriteI2c(AUTH_CONTR_STATUS,&u8tmp,1);
    package.u8LingoID = 0x00;
    package.u8CommandID = 0x18;
    while(1)
    {
        Sleep(50);
        ReadI2c(AUTH_CONTR_STATUS,&u8tmp,1);
        if((u8tmp&(0x70)) == 0x10) break;
    }
    ReadI2c(SIG_DATA_LEN,pu8tmp,2);
    len = ((U16)(pu8tmp[0])<<8)+(U16)(pu8tmp[1]);
    ReadI2c(SIG_DATA,package.pu8CommandData+2,len);
    //package.pu8CommandData[0]=(U8)((u16TransID>>8)&0xFF);
    //package.pu8CommandData[1]=(U8)((u16TransID)&0xFF);
    package.u8Marker = len+4;
    if(!WriteToIpod(&package))
    {
        return FALSE;
    }
    //1AckDevAuthenticationStatus
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x05||package.u8LingoID!=0x00||package.u8CommandID!=0x19||package.pu8CommandData[2]!=0x00)
        {
            u8retry--;
            continue;
        }
        break;
    }
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("AckDevAuthenticationStatus fail\r\n")));
        return FALSE;
    }
    //1RetAccSampleRateCaps
    package.u8Marker = 0x10;
    package.u8LingoID = 0x0A;
    package.u8CommandID =0x03;
    j=2;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x7D;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0xAC;
    package.pu8CommandData[j++] = 0x44;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0xBB;
    package.pu8CommandData[j++] = 0x80;
    if(!WriteToIpod(&package))
    {
        return FALSE;
    }
    //1TrackNewAudioAttributes
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8LingoID!=0x0A||package.u8CommandID!=0x04)
        {
            u8retry--;
            continue;
        }
        u32SampleRate = ((U32)package.pu8CommandData[2]<<24)+((U32)package.pu8CommandData[3]<<16)+((U32)package.pu8CommandData[4]<<8)+((U32)package.pu8CommandData[5]);
		printf("+++++++++++++++++u32SampleRate = %d++++++++\r\n",u32SampleRate);
        break;
    }
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("TrackNewAudioAttributes fail\r\n")));
        return FALSE;
    }
    //1ACK
    j=2;
    package.u8Marker = 0x06;
    package.u8LingoID = 0x0A;
    package.u8CommandID =0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x04;
    if(!WriteToIpod(&package))
    {
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::GetiPodAuthenticationInfo()
{
    ST_PACKAGE package;
    U16 j=0,i;
    U16 len;
    U8 u8secnum=0;
    U8 u8tmp,pu8tmp[2]={0};
    U8 u8retry=10;
    U8 pu8data[1024];
    //1GetiPodAuthenticationInfo
    package.u8Marker = 0x02;
    package.u8LingoID = 0x00;
    package.u8CommandID = 0x1A;
    if(!WriteToIpod(&package))
    {
        return FALSE;
    }
    //1RetiPodAuthenticationInfo
    while(1)
    {
        u8retry = 10;
        while(u8retry)
        {
            Sleep(50);
            if(ReadFromIpod(&package)) break;
            u8retry--;
        }
        if(0==u8retry)
        {
            RETAILMSG(IPODLOG_EER,(_T("RetiPodAuthenticationInfo fail\r\n")));
            return FALSE;
        }
        if(package.u8LingoID!=0x00||package.u8CommandID!=0x1B||package.pu8CommandData[0]!=0x02||package.pu8CommandData[1]!=0x00||package.pu8CommandData[2]!=u8secnum)
        {
            return FALSE;
        }
        if(package.u8Marker)
        {
            len = package.u8Marker;
        }
        else
        {
            len = ((U16)(package.u8PackageLenH)<<8)|(U16)(package.u8PackageLenL);
        }
        for(i=0;i<len;i++)
        {
            pu8data[j++] = package.pu8CommandData[i+4];
        }
        u8secnum++;
        if(package.pu8CommandData[2]==package.pu8CommandData[3]) break;
    }
    pu8tmp[0] = (U8)(j>>8);
    pu8tmp[1] = (U8)(j&0xFF);
    WriteI2c(IPOD_CERTI_DATA_LEN,pu8tmp,2);
    i=0;
    u8secnum=0;
    while(j)
    {
        if(j>128)
        {
            WriteI2c(IPOD_CERTI_DATA+u8secnum,pu8data+i,128);
            i+=128;
            j-=128;
            u8secnum++;
        }
        else
        {
            WriteI2c(IPOD_CERTI_DATA+u8secnum,pu8data+i,j);
            i+=j;
            j=0;
            u8secnum++;
        }
    }
    u8tmp = 4;
    WriteI2c(AUTH_CONTR_STATUS,&u8tmp,1);
    while(1)
    {
        Sleep(50);
        ReadI2c(AUTH_CONTR_STATUS,&u8tmp,1);
        if((u8tmp&(0x70)) == 0x40) break;
    }
    //1AckiPodAuthenticationInfo
    package.u8Marker = 0x03;
    package.u8LingoID = 0x00;
    package.u8CommandID = 0x1C;
    package.pu8CommandData[0]=0x00;
    if(!WriteToIpod(&package))
    {
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::GetiPodAuthenticationSignature()
{
    ST_PACKAGE package;
    U16 j=0;
    U8 u8tmp;
    U8 u8retry=10;
    U8 pu8challenge[20];
    u8tmp = 2;
    WriteI2c(AUTH_CONTR_STATUS,&u8tmp,1);
    while(1)
    {
        Sleep(50);
        ReadI2c(AUTH_CONTR_STATUS,&u8tmp,1);
        if((u8tmp&(0x70)) == 0x20) break;
    }
    ReadI2c(CHALLENGE_DATA,pu8challenge,20);
    for(j=0;j<20;j++)
    {
        package.pu8CommandData[j] = pu8challenge[j];
    }
    //1GetiPodAuthenticationSignature
    package.u8Marker = 0x17;
    package.u8LingoID = 0x00;
    package.u8CommandID = 0x1D;
    package.pu8CommandData[20] = 0x00;
    if(!WriteToIpod(&package))
    {
        return FALSE;
    }
    //1RetiPodAuthenticationSignature
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(ReadFromIpod(&package)) break;
        u8retry--;
    }
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("RetiPodAuthenticationSignature fail\r\n")));
        return FALSE;
    }
    if(package.u8LingoID!=0x00||package.u8CommandID!=0x1E)
    {
        return FALSE;
    }
    if(package.u8Marker)
    {
        u8tmp = package.u8Marker-2;
    }
    else
    {
        u8tmp = (((U16)(package.u8PackageLenH)<<8)|(U16)(package.u8PackageLenL))-2;
    }
    WriteI2c(SIG_DATA_LEN,&u8tmp,1);
    WriteI2c(SIG_DATA,package.pu8CommandData,u8tmp);
    u8tmp = 20;
    WriteI2c(CHALLENGE_DATA_LEN,&u8tmp,1);
    WriteI2c(CHALLENGE_DATA,pu8challenge,20);
    u8tmp = 3;
    WriteI2c(AUTH_CONTR_STATUS,&u8tmp,1);
    while(1)
    {
        Sleep(50);
        ReadI2c(AUTH_CONTR_STATUS,&u8tmp,1);
        if((u8tmp&(0x70)) == 0x30) break;
    }
    //1AckiPodAuthenticationStatus
    package.u8LingoID = 0x00;
    package.u8CommandID = 0x1F;
    package.u8Marker = 0x03;
    package.pu8CommandData[0] = 0x00;
    if(!WriteToIpod(&package))
    {
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::SetUIMode()
{
    ST_PACKAGE package;
    U8 u8retry;
    //1SetUIMode
    package.u8Marker = 0x05;
    package.u8LingoID = 0x00;
    package.u8CommandID = 0x37;
    package.pu8CommandData[0] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[1] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[2] = 0x01;
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ACK
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x06||package.u8LingoID!=0x00||package.u8CommandID!=0x02)
        {
            u8retry--;
            continue;
        }
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:SetUIMode fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::GetCurrentPlayingTrackChapterInfo(U32* pu32CurChapterIdx,U32* pu32ChapterCnt)
{
    ST_PACKAGE package;
    U8 u8retry;
    if(NULL==pu32CurChapterIdx||NULL==pu32ChapterCnt)
    {
        return FALSE;
    }
    //1GetCurrentPlayingTrackChapterInfo
    package.u8Marker = 0x05;
    package.u8LingoID = 0x04;
    package.u8CommandID = 0x00;
    package.pu8CommandData[0] = 0x02;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ReturnCurrentPlayingTrackChapterInfo
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x0D||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x03)
        {
            u8retry--;
            continue;
        }
        *pu32CurChapterIdx = ((U32)(package.pu8CommandData[3])<<24)+((U32)(package.pu8CommandData[4])<<16)+((U32)(package.pu8CommandData[5])<<8)+(U32)(package.pu8CommandData[6]);
        *pu32ChapterCnt = ((U32)(package.pu8CommandData[7])<<24)+((U32)(package.pu8CommandData[8])<<16)+((U32)(package.pu8CommandData[9])<<8)+(U32)(package.pu8CommandData[10]);
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:ReturnCurrentPlayingTrackChapterInfo fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::SetCurrentPlayingTrackChapter(U32 u32CurChapterIdx)
{
    ST_PACKAGE package;
    U8 u8retry;
    //1SetCurrentPlayingTrackChapter
    package.u8Marker = 0x09;
    package.u8LingoID = 0x04;
    package.u8CommandID = 0x00;
    package.pu8CommandData[0] = 0x04;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[3] = (U8)((u32CurChapterIdx>>24)&0xFF);
    package.pu8CommandData[4] = (U8)((u32CurChapterIdx>>16)&0xFF);
    package.pu8CommandData[5] = (U8)((u32CurChapterIdx>>8)&0xFF);
    package.pu8CommandData[6] = (U8)((u32CurChapterIdx)&0xFF);
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ACK
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x08||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x01)
        {
            u8retry--;
            continue;
        }
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:SetCurrentPlayingTrackChapter fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::GetAudiobookSpeed(U8* pu8Playspeed)
{
    ST_PACKAGE package;
    U8 u8retry;
    if(NULL==pu8Playspeed)
    {
        return FALSE;
    }
    //1GetAudiobookSpeed
    package.u8Marker = 0x05;
    package.u8LingoID = 0x04;
    package.u8CommandID = 0x00;
    package.pu8CommandData[0] = 0x09;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ReturnAudiobookSpeed
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x06||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x0A)
        {
            u8retry--;
            continue;
        }
        *pu8Playspeed = package.pu8CommandData[3];
        if(*pu8Playspeed!=PLAYSPEED_NORMAL&&*pu8Playspeed!=PLAYSPEED_FASTER&&*pu8Playspeed!=PLAYSPEED_SLOWER)
        {
            u8retry--;
            continue;
        }
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:SetCurrentPlayingTrackChapter fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::SetAudiobookSpeed(U8 u8Playspeed)
{
    ST_PACKAGE package;
    U8 u8retry;
    //1SetAudiobookSpeed
    package.u8Marker = 0x06;
    package.u8LingoID = 0x04;
    package.u8CommandID = 0x00;
    package.pu8CommandData[0] = 0x0B;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[3] = u8Playspeed;
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ACK
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x08||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x01)
        {
            u8retry--;
            continue;
        }
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0>u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:SetAudiobookSpeed fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::GetIndexedPlayingTrackInfoPodcastName(U32 u32TrackIdx,U32 u32ChapterIdx,WCHAR* pPodcastName)
{
    ST_PACKAGE package;
    U8 u8retry;
    if(NULL==pPodcastName)
    {
        return FALSE;
    }
    //1GetIndexedPlayingTrackInfo
    package.u8Marker = 0x0C;
    package.u8LingoID = 0x04;
    package.u8CommandID = 0x00;
    package.pu8CommandData[0] = 0x0C;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[3] = 0x01;
    package.pu8CommandData[4] = (U8)((u32TrackIdx>>24)&0xFF);
    package.pu8CommandData[5] = (U8)((u32TrackIdx>>16)&0xFF);
    package.pu8CommandData[6] = (U8)((u32TrackIdx>>8)&0xFF);
    package.pu8CommandData[7] = (U8)((u32TrackIdx)&0xFF);
    package.pu8CommandData[8] = (U8)((u32ChapterIdx>>8)&0xFF);
    package.pu8CommandData[9] = (U8)((u32ChapterIdx)&0xFF);
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ReturnIndexedPlayingTrackInfo
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8LingoID!=0x06||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x0D||package.pu8CommandData[3]!=0x01)
        {
            u8retry--;
            continue;
        }
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:ReturnIndexedPlayingTrackInfo fail\r\n")));
        return FALSE;
    }
    Utf8ToUnicode(pPodcastName, (char *)package.pu8CommandData+4, package.u8Marker-6);
    return TRUE;
}
BOOL TestIpod::ResetDBSelection()
{
    ST_PACKAGE package;
    U8 u8retry;
    //1ResetDBSelection
    package.u8Marker = 0x05;
    package.u8LingoID = 0x04;
    package.u8CommandID = 0x00;
    package.pu8CommandData[0] = 0x16;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ACK
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x08||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x01)
        {
            u8retry--;
            continue;
        }
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:ResetDBSelection fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::SelectDBRecord(U8 u8CategoryTypes,U32 u32Index)
{
    ST_PACKAGE package;
    U8 u8retry;
    //1SelectDBRecord
    package.u8Marker = 0x0A;
    package.u8LingoID = 0x04;
    package.u8CommandID = 0x00;
    package.pu8CommandData[0] = 0x17;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[3] = u8CategoryTypes;
    package.pu8CommandData[4] = (U8)(u32Index>>24)&0xFF;
    package.pu8CommandData[5] = (U8)(u32Index>>16)&0xFF;
    package.pu8CommandData[6] = (U8)(u32Index>>8)&0xFF;
    package.pu8CommandData[7] = (U8)(u32Index)&0xFF;
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ACK
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x08||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x01)
        {
            u8retry--;
            continue;
        }
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0>u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:SelectDBRecord fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::GetNumberCategorizedDBRecords(U8 u8CategoryTypes,U32* pu32Num)//0x00 Top-Level 0x01 Playlist 0x02 Artist 0x03 Album 0x04 Genre 0x05 Track 0x06 Composer 0x07 AudioBook 0x08 Podcase 0x09Nested playlist  0x0a Genius Mixes 0x0b iTunesU 
{
    ST_PACKAGE package;
    U8 u8retry;
    if(NULL==pu32Num)
    {
        return FALSE;
    }
    //1GetNumberCategorizedDBRecords
    package.u8Marker = 0x06;
    package.u8LingoID = 0x04;
    package.u8CommandID = 0x00;
    package.pu8CommandData[0] = 0x18;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[3] = u8CategoryTypes;
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ReturnNumberCategorizedDBRecords
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x09||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x19)
        {
            u8retry--;
            continue;
        }
        *pu32Num = ((U32)(package.pu8CommandData[3])<<24)|((U32)(package.pu8CommandData[4])<<16)|((U32)(package.pu8CommandData[5])<<8)|((U32)(package.pu8CommandData[6]));
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:ReturnNumberCategorizedDBRecords fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::GetPlayStatus(U32* pu32TrackLen,U32* pu32TrackPos,U8* pu8State)
{
    ST_PACKAGE package;
    U8 u8retry;
    if(NULL==pu32TrackLen||NULL==pu32TrackPos||NULL==pu8State)
    {
        return FALSE;
    }
    //1GetPlayStatus
    package.u8Marker = 0x05;
    package.u8LingoID = 0x04;
    package.u8CommandID = 0x00;
    package.pu8CommandData[0] = 0x1C;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ReturnPlayStatus
    u8retry = 10;
	bool bFirst = true;
    while(u8retry)
    {
		if(bFirst)
		{
			bFirst = false;
		}
		else
		{
			Sleep(50);
		}
       // Sleep(50);//º”—” ± 6
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x0E||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x1D)
        {
            u8retry--;
            continue;
        }
        *pu32TrackLen = ((U32)(package.pu8CommandData[3])<<24)|((U32)(package.pu8CommandData[4])<<16)|((U32)(package.pu8CommandData[5])<<8)|((U32)(package.pu8CommandData[6]));
        *pu32TrackPos = ((U32)(package.pu8CommandData[7])<<24)|((U32)(package.pu8CommandData[8])<<16)|((U32)(package.pu8CommandData[9])<<8)|((U32)(package.pu8CommandData[10]));
        *pu8State = package.pu8CommandData[11];
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:ReturnPlayStatus fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::GetCurrentPlayingTrackIndex(U32* pu32Trackidx)
{
    ST_PACKAGE package;
    U8 u8retry;
    if(NULL==pu32Trackidx)
    {
        return FALSE;
    }
    //1GetCurrentPlayingTrackIndex
    package.u8Marker = 0x05;
    package.u8LingoID = 0x04;
    package.u8CommandID = 0x00;
    package.pu8CommandData[0] = 0x1E;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ReturnCurrentPlayingTrackIndex
    u8retry = 10;
	bool bFirst = true;
    while(u8retry)
    {
		if(bFirst)
		{
			bFirst = false;
		}
		else
		{
			  Sleep(50);
		}
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x09||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x1F)
        {
            u8retry--;
            continue;
        }
        *pu32Trackidx =((U32)(package.pu8CommandData[3])<<24)|((U32)(package.pu8CommandData[4])<<16)|((U32)(package.pu8CommandData[5])<<8)|((U32)(package.pu8CommandData[6]));
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:ReturnCurrentPlayingTrackIndex fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::GetIndexedPlayingTrackTitle(U32 u32TrackIdx,WCHAR* pTrackTitle)
{
    ST_PACKAGE package;
    U8 u8retry;
    if(NULL==pTrackTitle)
    {
        return FALSE;
    }
    //1GetIndexedPlayingTrackTitle
    package.u8Marker = 0x09;
    package.u8LingoID = 0x04;
    package.u8CommandID = 0x00;
    package.pu8CommandData[0] = 0x20;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[3] = (U8)((u32TrackIdx>>24)&0xFF);
    package.pu8CommandData[4] = (U8)((u32TrackIdx>>16)&0xFF);
    package.pu8CommandData[5] = (U8)((u32TrackIdx>>8)&0xFF);
    package.pu8CommandData[6] = (U8)((u32TrackIdx)&0xFF);
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ReturnIndexedPlayingTrackTitle
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x21)
        {
            u8retry--;
            continue;
        }
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:ReturnIndexedPlayingTrackTitle fail\r\n")));
        return FALSE;
    }
    Utf8ToUnicode(pTrackTitle, (char *)package.pu8CommandData+3, package.u8Marker-5);
    return TRUE;
}
BOOL TestIpod::GetIndexedPlayingTrackArtistName(U32 u32TrackIdx,WCHAR* pArtistName)
{
    ST_PACKAGE package;
    U8 u8retry;
    if(NULL==pArtistName)
    {
        return FALSE;
    }
    //1GetIndexedPlayingTrackArtistName
    package.u8Marker = 0x09;
    package.u8LingoID = 0x04;
    package.u8CommandID = 0x00;
    package.pu8CommandData[0] = 0x22;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[3] = (U8)((u32TrackIdx>>24)&0xFF);
    package.pu8CommandData[4] = (U8)((u32TrackIdx>>16)&0xFF);
    package.pu8CommandData[5] = (U8)((u32TrackIdx>>8)&0xFF);
    package.pu8CommandData[6] = (U8)((u32TrackIdx)&0xFF);
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ReturnIndexedPlayingTrackArtistName
    u8retry = 10;
    while(u8retry)
    {
		bool bFirst = true;
		if(bFirst)
		{
			bFirst = false;
		}
		else
		{
			Sleep(50);
		}
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x23)
        {
            u8retry--;
            continue;
        }
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:ReturnIndexedPlayingTrackArtistName fail\r\n")));
        return FALSE;
    }
    Utf8ToUnicode(pArtistName, (char *)package.pu8CommandData+3, package.u8Marker-5);
    return TRUE;
}
BOOL TestIpod::GetIndexedPlayingTrackAlbumName(U32 u32TrackIdx,WCHAR* pAlbumName)
{
    ST_PACKAGE package;
    U8 u8retry;
    if(NULL==pAlbumName)
    {
        return FALSE;
    }
    //1GetIndexedPlayingTrackAlbumName
    package.u8Marker = 0x09;
    package.u8LingoID = 0x04;
    package.u8CommandID = 0x00;
    package.pu8CommandData[0] = 0x24;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[3] = (U8)((u32TrackIdx>>24)&0xFF);
    package.pu8CommandData[4] = (U8)((u32TrackIdx>>16)&0xFF);
    package.pu8CommandData[5] = (U8)((u32TrackIdx>>8)&0xFF);
    package.pu8CommandData[6] = (U8)((u32TrackIdx)&0xFF);
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ReturnIndexedPlayingTrackAlbumName
    u8retry = 10;
    while(u8retry)
    {
		bool bFirst = true;
		if(bFirst)
		{
			bFirst = false;
		}
		else
		{
			Sleep(50);
		}
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x25)
        {
            u8retry--;
            continue;
        }
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:ReturnIndexedPlayingTrackAlbumName fail\r\n")));
        return FALSE;
    }
    Utf8ToUnicode(pAlbumName, (char *)package.pu8CommandData+3, package.u8Marker-5);
    return TRUE;
}
BOOL TestIpod::SetPlayStatusChangeNotification(BOOL enable,U32 u32StatusChangeMask)
{
    ST_PACKAGE package;
    U8 u8retry;
    //1SetPlayStatusChangeNotification-4BYTE
    package.u8Marker = 0x09;
    package.u8LingoID = 0x04;
    package.u8CommandID = 0x00;
    package.pu8CommandData[0] = 0x26;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[3] = (U8)((u32StatusChangeMask>>24)&0xFF);
    package.pu8CommandData[4] = (U8)((u32StatusChangeMask>>16)&0xFF);
    package.pu8CommandData[5] = (U8)((u32StatusChangeMask>>8)&0xFF);
    package.pu8CommandData[6] = (U8)((u32StatusChangeMask)&0xFF);
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ACK
    u8retry = 10;
    while(u8retry)
    {
		bool bFirst = true;
		if(bFirst)
		{
			bFirst = false;
		}
		else
		{
			Sleep(50);
		}
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x08||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x01)
        {
            u8retry--;
            continue;
        }
        break;
    }
    
    if(0==u8retry)
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:SetPlayStatusChangeNotification fail\r\n")));
        return FALSE;
    }
    if(0 == package.pu8CommandData[3])
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return TRUE;
    }
    //1SetPlayStatusChangeNotification-1BYTE
    package.u8Marker = 0x06;
    package.u8LingoID = 0x04;
    package.u8CommandID = 0x00;
    package.pu8CommandData[0] = 0x26;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[3] = enable?0X01:0X00;
    u16TransID++;
   //EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ACK
    u8retry = 10;
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x08||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x01)
        {
            u8retry--;
            continue;
        }
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0>u8retry)
    {
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::PlayCurrentSelection(U32 u32TrackIdx)
{
    ST_PACKAGE package;
    U8 u8retry;
    //1PlayCurrentSelection
    package.u8Marker = 0x09;
    package.u8LingoID = 0x04;
    package.u8CommandID =0x00;
    package.pu8CommandData[0] = 0x28;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[3] = (U8)((u32TrackIdx>>24)&0xFF);
    package.pu8CommandData[4] = (U8)((u32TrackIdx>>16)&0xFF);
    package.pu8CommandData[5] = (U8)((u32TrackIdx>>8)&0xFF);
    package.pu8CommandData[6] = (U8)((u32TrackIdx)&0xFF);
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ACK
    u8retry = 10;
    while(u8retry)
    {
        Sleep(50);
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x08||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x01)
        {
            u8retry--;
            continue;
        }
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:PlayCurrentSelection fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::PlayControl(U8 u8Control)
{
    ST_PACKAGE package;
    U8 u8retry;
    //1PlayControl
    package.u8Marker = 0x06;
    package.u8LingoID = 0x04;
    package.u8CommandID =0x00;
    package.pu8CommandData[0] = 0x29;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[3] = u8Control;
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ACK
    u8retry = 10;
    while(u8retry)
    {
		bool bFirst = true;
		if(bFirst)
		{
			bFirst = false;
		}
		else
		{
			Sleep(50);
		}
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x08||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x01)
        {
            u8retry--;
            continue;
        }
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:PlayControl fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::GetShuffle(U8* pu8ShuffleType)
{
    ST_PACKAGE package;
    U8 u8retry;
    //1GetShuffle
    package.u8Marker = 0x05;
    package.u8LingoID = 0x04;
    package.u8CommandID =0x00;
    package.pu8CommandData[0] = 0x2C;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ReturnShuffle
    u8retry = 10;
    while(u8retry)
    {
		bool bFirst = true;
		if(bFirst)
		{
			bFirst = false;
		}
		else
		{
			Sleep(50);
		}
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x06||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x2D)
        {
			//LeaveCsReadCriticalSection(&csIpodRead);
           // return FALSE;
			u8retry--;
			continue;
        }
        *pu8ShuffleType = package.pu8CommandData[3];
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:ReturnShuffle fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::SetShuffle(U8 u8ShuffleType)
{
    ST_PACKAGE package;
    U8 u8retry;
    //1SetShuffle
    package.u8Marker = 0x07;
    package.u8LingoID = 0x04;
    package.u8CommandID =0x00;
    package.pu8CommandData[0] = 0x2E;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[3] = u8ShuffleType;
    package.pu8CommandData[4] = 0x01;
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ACK
    u8retry = 10;
    while(u8retry)
    {
		bool bFirst = true;
		if(bFirst)
		{
			bFirst = false;
		}
		else
		{
			Sleep(50);
		}
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x08||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x01)
        {
            u8retry--;
            continue;
        }
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:SetShuffle fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::GetRepeat(U8* pu8RepeatType)
{
    ST_PACKAGE package;
    U8 u8retry;
    //1GetRepeat
    package.u8Marker = 0x05;
    package.u8LingoID = 0x04;
    package.u8CommandID =0x00;
    package.pu8CommandData[0] = 0x2F;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ReturnRepeat
    u8retry = 10;
    while(u8retry)
    {
		bool bFirst = true;
		if(bFirst)
		{
			bFirst = false;
		}
		else
		{
			Sleep(50);
		}
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x06||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x30)
        {
           // return FALSE;
			 u8retry--;
			continue;
        }
        *pu8RepeatType = package.pu8CommandData[3];
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:ReturnRepeat fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::SetRepeat(U8 u8RepeatType)
{
    ST_PACKAGE package;
    U8 u8retry;
    //1SetRepeat
    package.u8Marker = 0x07;
    package.u8LingoID = 0x04;
    package.u8CommandID =0x00;
    package.pu8CommandData[0] = 0x31;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[3] = u8RepeatType;
    package.pu8CommandData[4] = 0x01;
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ACK
    u8retry = 10;
    while(u8retry)
    {
		bool bFirst = true;
		if(bFirst)
		{
			bFirst = false;
		}
		else
		{
			Sleep(50);
		}
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x08||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x01)
        {
            u8retry--;
            continue;
        }
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:SetRepeat fail\r\n")));
        return FALSE;
    }
	if(package.pu8CommandData[3] == 0)
	{
        return TRUE;
	}
	else
	{
		printf("SetRepeat::Fail= %d",package.pu8CommandData[3]);
		return FALSE;
	}
    
}
BOOL TestIpod::GetNumPlayingTracks(U32* pu32TrackNum)
{
    ST_PACKAGE package;
    U8 u8retry;
    //1GetNumPlayingTracks
    package.u8Marker = 0x05;
    package.u8LingoID = 0x04;
    package.u8CommandID =0x00;
    package.pu8CommandData[0] = 0x35;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ReturnNumPlayingTracks
    u8retry = 10;
	bool bFirst = true;
    while(u8retry)
    {
		if(bFirst)
		{
			bFirst = false;
		}
		else
		{
           Sleep(50);
		}
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x09||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x36)
        {
            u8retry--;
            continue;
        }
        *pu32TrackNum = ((U32)(package.pu8CommandData[3])<<24)+((U32)(package.pu8CommandData[4])<<16)+((U32)(package.pu8CommandData[5])<<8)+(U32)(package.pu8CommandData[6]);
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:ReturnNumPlayingTracks fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::SetCurrentPlayingTrack(U32 u32TrackIdx)
{
    ST_PACKAGE package;
    U8 u8retry;
    //1SetCurrentPlayingTrack
    package.u8Marker = 0x09;
    package.u8LingoID = 0x04;
    package.u8CommandID =0x00;
    package.pu8CommandData[0] = 0x37;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[3] = (U8)((u32TrackIdx>>24)&0xFF);
    package.pu8CommandData[4] = (U8)((u32TrackIdx>>16)&0xFF);
    package.pu8CommandData[5] = (U8)((u32TrackIdx>>8)&0xFF);
    package.pu8CommandData[6] = (U8)((u32TrackIdx)&0xFF);
    u16TransID++;
    nnIpodRead++;printf("11111111+++++csIpodRead = %d+++++\r\n",nnIpodRead);EnterCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ACK
    u8retry = 10;
    while(u8retry)
    {
		bool bFirst = true;
		if(bFirst)
		{
			bFirst = false;
		}
		else
		{
			Sleep(50);
		}
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8Marker!=0x08||package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x01)
        {
            u8retry--;
            continue;
        }
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:SetCurrentPlayingTrack fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::GetArtworkFormats()
{
    ST_PACKAGE package;
    U8 u8retry;
    //1GetArtworkFormats
    package.u8Marker = 0x05;
    package.u8LingoID = 0x04;
    package.u8CommandID =0x00;
    package.pu8CommandData[0] = 0x0E;
    package.pu8CommandData[1] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[2] = (U8)((u16TransID)&0xFF);
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1RetArtworkFormats
    u8retry = 10;
    while(u8retry)
    {
		bool bFirst = true;
		if(bFirst)
		{
			bFirst = false;
		}
		else
		{
			Sleep(50);
		}
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8LingoID!=0x04||package.u8CommandID!=0x00||package.pu8CommandData[0]!=0x0F)
        {
            u8retry--;
            continue;
        }
        break;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    if(0==u8retry)
    {
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:RetArtworkFormats fail\r\n")));
        return FALSE;
    }
    return TRUE;
}
BOOL TestIpod::GetTrackArtworkData(U8 *pu8artwork,U32 u32TrackIndex,U8 u8Format)
{
    ST_PACKAGE package;
    U8 u8retry;
    U16 j=0,len;
    if(NULL==pu8artwork) return FALSE;
    //1GetTrackArtworkData
    package.u8Marker = 0x0F;
    package.u8LingoID = 0x04;
    package.u8CommandID =0x00;
    package.pu8CommandData[j++] = 0x10;
    package.pu8CommandData[j++] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[j++] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[j++] = (U8)((u32TrackIndex>>24)&0xFF);
    package.pu8CommandData[j++] = (U8)((u32TrackIndex>>16)&0xFF);
    package.pu8CommandData[j++] = (U8)((u32TrackIndex>>8)&0xFF);
    package.pu8CommandData[j++] = (U8)((u32TrackIndex)&0xFF);
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = u8Format;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x01;
    u16TransID++;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1RetTrackArtworkData
    if(!(len=RetTrackArtworkData(pu8artwork)))
    {
        LeaveCsReadCriticalSection(&csIpodRead);
        RETAILMSG(IPODLOG_EER,(_T("IPODERR:RetTrackArtworkData fail\r\n")));
        return FALSE;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    return TRUE;
}
BOOL TestIpod::RetrieveCategorizedDatabaseRecords(unsigned char cType,unsigned long iStart,unsigned long iCount,unsigned char *pOut)
{
	ST_PACKAGE package;
	U8 u8retry;
	U16 j=0,len;
	if(NULL== pOut) return FALSE;
	//1RetrieveCategorizedDatabaseRecords
	package.u8Marker = 0x0e;
	package.u8LingoID = 0x04;
	package.u8CommandID =0x00;
	package.pu8CommandData[j++] = 0x1A;
	package.pu8CommandData[j++] = (U8)((u16TransID>>8)&0xFF);
	package.pu8CommandData[j++] = (U8)((u16TransID)&0xFF);
	package.pu8CommandData[j++] = cType;
	package.pu8CommandData[j++] = (U8)((iStart>>24)&0xFF);
	package.pu8CommandData[j++] = (U8)((iStart>>16)&0xFF);
	package.pu8CommandData[j++] = (U8)((iStart>>8)&0xFF);
	package.pu8CommandData[j++] = (U8)((iStart)&0xFF);
	package.pu8CommandData[j++] = (U8)((iCount>>24)&0xFF);
	package.pu8CommandData[j++] = (U8)((iCount>>16)&0xFF);
	package.pu8CommandData[j++] = (U8)((iCount>>8)&0xFF);
	package.pu8CommandData[j++] = (U8)((iCount)&0xFF);
	//package.pu8CommandData[j++] = 0x00;
	//package.pu8CommandData[j++] = u8Format;
	//package.pu8CommandData[j++] = 0x00;
	//package.pu8CommandData[j++] = 0x00;
	//package.pu8CommandData[j++] = 0x00;
	//package.pu8CommandData[j++] = 0x01;
	u16TransID++;
	nnIpodRead++;printf("+++++csIpodRead = %d+++++\r\n",nnIpodRead);EnterCriticalSection(&csIpodRead);
	if(!WriteToIpod(&package))
	{
		LeaveCsReadCriticalSection(&csIpodRead);
		return FALSE;
	}
	//Sleep(150);
	//1ReturnCategorizedDatabaseRecords
	if(!(len=ReturnCategorizedDatabaseRecords(pOut)))
	{
		LeaveCsReadCriticalSection(&csIpodRead);
		//RETAILMSG(IPODLOG_EER,(_T("IPODERR:RetTrackArtworkData fail\r\n")));
		return FALSE;
	}
	LeaveCsReadCriticalSection(&csIpodRead);
	return TRUE;
}

BOOL TestIpod::RetAccSampleRateCaps(U32 *pu32SampleRate)
{
    ST_PACKAGE package;
    U8 u8retry;
    U16 j=0;
    if(NULL==pu32SampleRate) return FALSE;
    //1RetAccSampleRateCaps
    package.u8Marker = 0x0E;
    package.u8LingoID = 0x0A;
    package.u8CommandID =0x03;
    package.pu8CommandData[j++] = (U8)((u16TransID>>8)&0xFF);
    package.pu8CommandData[j++] = (U8)((u16TransID)&0xFF);
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x7D;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0xAC;
    package.pu8CommandData[j++] = 0x44;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0xBB;
    package.pu8CommandData[j++] = 0x80;
   EnterCsReadCriticalSection(&csIpodRead);
    if(!WriteToIpod(&package))
    {
		LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1TrackNewAudioAttributes
    u8retry = 10;
    while(u8retry)
    {
		bool bFirst = true;
		if(bFirst)
		{
			bFirst = false;
		}
		else
		{
			Sleep(50);
		}
        if(!ReadFromIpod(&package))
        {
            u8retry--;
            continue;
        }
        if(package.u8LingoID!=0x0A||package.u8CommandID!=0x04)
        {
            u8retry--;
            continue;
        }
        *pu32SampleRate = ((U32)package.pu8CommandData[2]<<24)+((U32)package.pu8CommandData[3]<<16)+((U32)package.pu8CommandData[4]<<8)+((U32)package.pu8CommandData[5]);
        break;
    }
    if(0==u8retry)
    {
        LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    //1ACK
    j=2;
    package.u8Marker = 0x0E;
    package.u8LingoID = 0x0A;
    package.u8CommandID =0x03;
    package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = 0x04;
    if(!WriteToIpod(&package))
    {
        LeaveCsReadCriticalSection(&csIpodRead);
        return FALSE;
    }
    LeaveCsReadCriticalSection(&csIpodRead);
    return TRUE;
}

BOOL TestIpod::GetDBiTunesInfo(unsigned char cType)
{
	ST_PACKAGE package;
	U8 u8retry;
	U16 j=0;
	//if(NULL==pu32SampleRate) return FALSE;
	//1RetAccSampleRateCaps
	unsigned char pu8Data[1300] = {0};
	unsigned long u32read = 0;
	 char tmpBuf[1400] = {0};
	package.u8Marker = 0x07;
	package.u8LingoID = 0x04;
	package.u8CommandID =0x00;
	package.pu8CommandData[j++] = 0x3c;
	package.pu8CommandData[j++] = (U8)((u16TransID>>8)&0xFF);
	package.pu8CommandData[j++] = (U8)((u16TransID)&0xFF);
	package.pu8CommandData[j++] = 0x00;
    package.pu8CommandData[j++] = cType;
	nnIpodRead++;printf("+++++csIpodRead = %d+++++\r\n",nnIpodRead);EnterCriticalSection(&csIpodRead);
	if(!WriteToIpod(&package))
	{
		LeaveCsReadCriticalSection(&csIpodRead);
		return FALSE;
	}
	//1TrackNewAudioAttributes
	u8retry = 10;
	while(u8retry)
	{
		memset(pu8Data,0,sizeof(pu8Data));
		if(!ReadFile(hIpodhid,pu8Data,1026,&u32read,0))
		{
			u8retry--;
			continue;
		}
		if(0==u32read)
		{
			u8retry--;
			continue;
		}
	/*	if(pu8Data[j++]!=0x55)
		{
			u8retry--;
			continue;
		}*/
		if(pu8Data[0] != 0x55 && pu8Data[2] != 0x04 && pu8Data[3] != 0x00 && pu8Data[0] != 0x3d)
		{
			u8retry--;
			continue;
		}
		printf("Gettickit() = %d,ReadFromIpod+++++ ::",GetTickCount());
		for(int k = 0; k < u32read;k++)
		{
			sprintf_s(tmpBuf, 1100, "%s %02x", tmpBuf, pu8Data[k]);
		}
		printf("%s\r\n",tmpBuf);
		//sp->u8Marker = pu8Data[j++];
		//sp->u8PackageLenH = pu8Data[j++];
		
		unsigned char lIndex = pu8Data[7];
		unsigned long uCount = 0;

		WCHAR szTemp[1300] = {0};
		switch (cType)
		{
			case 0:
			{

			}
			break;
			case 1:
			{

			}
			break;
			case 2:
			{

			}
			break;
			case 3:
			{

			}
			break;
			case 4:
			{

			}
			break;
			case 5:
			{

			}
			break;
		}
		//if(len > 9)
		//{
		//// Utf8ToUnicode(szTemp, (char*)(pu8Data+11), len - 9);
		//wprintf(L"++++index = %d,+++++name::::: %s\r\n",lIndex,szTemp);
		//}
		break;
		if(0==u8retry)
		{
			LeaveCsReadCriticalSection(&csIpodRead);
			return FALSE;
		}
	}
	LeaveCsReadCriticalSection(&csIpodRead);
	return TRUE;
}
void TestIpod::SetIpodReadyEvent()
{
	if(m_hIpodReady != NULL)
	{
		SetEvent(m_hIpodReady);
	}
}
void TestIpod::ResetIpodReadyEvent()
{
    if(m_hIpodReady != NULL)
	{
		ResetEvent(m_hIpodReady);
	}
}
U16 TestIpod::RetTrackArtworkData(U8 *pu8artwork)
{
    ST_PACKAGE package;
    U16 len=0,packlen,i;
    if(!ReadIpodArtwork(&package))
    {
        return 0;
    }
    packlen = ((U16)(package.u8PackageLenH)<<8)|(U16)(package.u8PackageLenL)-2;
    for(i=22;i<packlen;i++)
    {
        pu8artwork[len++] = package.pu8CommandData[i];
    }
    while(ReadIpodArtwork(&package))
    {
        packlen = ((U16)(package.u8PackageLenH)<<8)|(U16)(package.u8PackageLenL)-2;
        for(i=5;i<packlen;i++)
        {
            pu8artwork[len++] = package.pu8CommandData[i];
        }
    }
    return len;
}
BOOL TestIpod::ReturnCategorizedDatabaseRecords(unsigned char *pOut)
{
  if(pOut == NULL)
  {
	  return FALSE;
  }
  ST_PACKAGE package;
  U16 len=0,packlen,i;
  if(!ReadCategorizedDatabaseRecords(&package))
  {
	  return 0;
  }
}
BOOL TestIpod::ReadI2c(U8 u8RegAddr,U8 *pu8ReadValue, U32 u32ReadCnt)
{
    I2C_IO_INFO stI2C_IO_Info;
    BOOL bRet = FALSE;
    DWORD dwBytesReturned;
    if(hI2c!= NULL)
    {
        stI2C_IO_Info.u8SlaveId     = i2cReadAdd;
        stI2C_IO_Info.pu8RegAddr    = &u8RegAddr;
        stI2C_IO_Info.pu8Data = pu8ReadValue;
        stI2C_IO_Info.u32RegAddrCnt = 1;
        bRet = DeviceIoControl (hI2c, IOCTL_I2C_READ, (LPVOID)&stI2C_IO_Info, sizeof(I2C_IO_INFO),
                                (LPVOID)pu8ReadValue, u32ReadCnt, &dwBytesReturned, 0);
    }
    if(!bRet) RETAILMSG(IPODLOG_EER,(_T("read i2c fail add: %x %x %x\r\n"),u8RegAddr,*(U32*)stI2C_IO_Info.pu8Data,*(U32*)pu8ReadValue));
    return bRet;
}
BOOL TestIpod::WriteI2c(U8 u8RegAddr,U8 *pu8WriteValue, U32 u32WriteCnt)
{
    I2C_IO_INFO stI2C_IO_Info;
    BOOL bRet = FALSE;
    DWORD dwBytesReturned;
    if(hI2c != NULL)
    {
        stI2C_IO_Info.u8SlaveId     = i2cWriteAdd;
        stI2C_IO_Info.pu8RegAddr    = &u8RegAddr;
        stI2C_IO_Info.u32RegAddrCnt = 1;
        stI2C_IO_Info.pu8Data       = pu8WriteValue;
        stI2C_IO_Info.u32DataCnt    = u32WriteCnt;
        bRet = DeviceIoControl (hI2c, IOCTL_I2C_WRITE, (LPVOID)&stI2C_IO_Info, sizeof(I2C_IO_INFO),
                                NULL, 0, &dwBytesReturned, 0);
    }
    if(!bRet) RETAILMSG(IPODLOG_EER,(_T("write i2c fail add: %x\r\n"),u8RegAddr));
    return bRet;
}
BOOL ReadFromIpod(PST_PACKAGE sp)
{
    U32 u32read;
    U16 j=0,i,len;
    U8 pu8Data[1100]={0};
    if(!ReadFile(hIpodhid,pu8Data,1026,&u32read,0)) 
	return FALSE;
	//printf("ReadFromIpod:%s",pu8Data);
#if DEBUGIPODDATA
	printf("Gettick() = %d,ReadFromIpod:",GetTickCount());
	char tmpBuf[1200] = {0};
	for(int k = 0; k < u32read;k++)
	{
		sprintf_s(tmpBuf, 1100, "%s %02x", tmpBuf, pu8Data[k]);
	}
	printf("%s\r\n",tmpBuf);
#endif
    if(0==u32read) return FALSE;
    if(pu8Data[6]==0x11&&pu8Data[4]==0x04)
    {
        for(int i=16;i<u32read+10;i++)RETAILMSG(1,(_T("%x "),pu8Data[i]));
    }
    if(pu8Data[j++]!=0x55)
    {
        return FALSE;
    }
	HandleTarckNewAttributesEx(pu8Data,u32read);
	//HandleTarckNewAttributes()
    sp->u8Marker = pu8Data[j++];
    if(0==sp->u8Marker)
    {
        sp->u8PackageLenH = pu8Data[j++];
        sp->u8PackageLenL = pu8Data[j++];
        len = ((U16)(sp->u8PackageLenH)<<8)|((U16)(sp->u8PackageLenL))-2;
    }
    else
    {
        len = sp->u8Marker-2;
    }
    sp->u8LingoID = pu8Data[j++];
    sp->u8CommandID = pu8Data[j++];
    for(i=0;i<len;i++)
    {
        sp->pu8CommandData[i] = pu8Data[j++];
    }
    return TRUE;
}
BOOL WriteToIpod(PST_PACKAGE sp)
{
    U16 i,j=0,len;
    U32 u32written;
    U16 u16checksum=0;
    U8 pu8Data[1100]={0};
    pu8Data[j++] = 0x55;
    if(0==sp->u8Marker)
    {
        pu8Data[j++] = sp->u8Marker;
        pu8Data[j++] = sp->u8PackageLenH;
        u16checksum += sp->u8PackageLenH;
        pu8Data[j++] = sp->u8PackageLenL;
        u16checksum += sp->u8PackageLenL;
        len = ((U16)(sp->u8PackageLenH)<<8)|((U16)(sp->u8PackageLenL))-2;
    }
    else
    {
        pu8Data[j++] = sp->u8Marker;
        u16checksum += sp->u8Marker;
        len = sp->u8Marker-2;
    }
    pu8Data[j++] = sp->u8LingoID;
    u16checksum += sp->u8LingoID;
    pu8Data[j++] = sp->u8CommandID;
    u16checksum += sp->u8CommandID;
    for(i=0;i<len;i++)
    {
        pu8Data[j++] = sp->pu8CommandData[i];
        u16checksum += sp->pu8CommandData[i];
    }
    u16checksum &= 0xFF;
    pu8Data[j++] = (U8)(0x100-u16checksum);
#if DEBUGIPODDATA
	printf("WriteToIpod:");
	char tmpBuf[2400] = {0};
	printf("++%d:",j);
	for(int k = 0; k < j;k++)
	{
		sprintf_s(tmpBuf, 2200, "%s %02x", tmpBuf, pu8Data[k]);
	}
	printf("%s\r\n",tmpBuf);
#endif
    if(WriteFile(hIpodhid,pu8Data,j,&u32written,0)) return TRUE;
    return FALSE;
}
BOOL ReadIpodArtwork(PST_PACKAGE sp)
{
    U8 pu8Data[1100]={0};
    U8 u8retry;
    U32 u32read;
    U32 len;
    U16 j=0,i=0;
    u8retry = 10;
    while(u8retry)
    {
        j=0;
        i=0;
        if(!ReadFile(hIpodhid,pu8Data,1026,&u32read,0))
        {
            u8retry--;
            continue;
        }
        if(0==u32read)
        {
            u8retry--;
            continue;
        }
        if(pu8Data[j++]!=0x55)
        {
            u8retry--;
            continue;
        }
        sp->u8Marker = pu8Data[j++];
        sp->u8PackageLenH = pu8Data[j++];
        sp->u8PackageLenL = pu8Data[j++];
        sp->u8LingoID = pu8Data[j++];
        sp->u8CommandID = pu8Data[j++];
        if(sp->u8LingoID!=0x04||sp->u8CommandID!=0x00||pu8Data[j]!=0x11)
        {
            u8retry--;
            continue;
        }
        len = ((U16)sp->u8PackageLenH<<8)+(U16)sp->u8PackageLenL;
        len-=2;
        while(j<u32read)
        {
            sp->pu8CommandData[i++] = pu8Data[j++];
            len--;
        }
        break;
    }
    while(u8retry)
    {
        if(!ReadFile(hIpodhid,pu8Data,1026,&u32read,0))
        {
            u8retry--;
            continue;
        }
        if(0==u32read)
        {
            u8retry--;
            continue;
        }
        j=0;
        while(len)
        {
            sp->pu8CommandData[i++] = pu8Data[j++];
            len--;
        }
        break;
    }
    if(0==u8retry)
    {
        return FALSE;
    }
    return TRUE;
}


BOOL TestIpod::ReadCategorizedDatabaseRecords(PST_PACKAGE sp)
{
	U8 pu8Data[1100]={0};
	U8 u8retry;
	U32 u32read;
	U32 len;
	U16 j=0,i=0;
	u8retry = 10;
	char tmpBuf[1200] = {0};
	nnIpodRead++;printf("+++++csIpodRead = %d+++++\r\n",nnIpodRead);EnterCriticalSection(&csIpodRead);
	while(u8retry)
	{
		j=0;
		i=0;
		memset(pu8Data,0,sizeof(pu8Data));
		if(!ReadFile(hIpodhid,pu8Data,1026,&u32read,0))
		{
			u8retry--;
			continue;
		}
		if(0==u32read)
		{
			u8retry--;
			continue;
		}
	/*	if(pu8Data[j++]!=0x55)
		{
			u8retry--;
			continue;
		}*/
		if(pu8Data[0] != 0x55 && pu8Data[2] != 0x04 && pu8Data[3] != 0x00 && pu8Data[0] != 0x1B)
		{
			u8retry--;
			continue;
		}
		printf("Gettickit() = %d,ReadFromIpod+++++ ::",GetTickCount());
		for(int k = 0; k < u32read;k++)
		{
			sprintf_s(tmpBuf, 1100, "%s %02x", tmpBuf, pu8Data[k]);
		}
		printf("%s\r\n",tmpBuf);
		//sp->u8Marker = pu8Data[j++];
		//sp->u8PackageLenH = pu8Data[j++];
       len = pu8Data[1];
		
		unsigned long lIndex = (pu8Data[7]<<24) + (pu8Data[8]<<16) +(pu8Data[9]<<8) +(pu8Data[10]);
        printf("+++++++len = %d,lIndex = %d",len,lIndex);
		WCHAR szTemp[1300] = {0};
		if(len > 9)
		{
		 Utf8ToUnicode(szTemp, (char*)(pu8Data+11), len - 9);
		wprintf(L"++++index = %d,+++++name::::: %s\r\n",lIndex,szTemp);
		}
		break;
		if(0==u8retry)
		{
			LeaveCsReadCriticalSection(&csIpodRead);
			return FALSE;
		}
	}
	LeaveCsReadCriticalSection(&csIpodRead);
	return TRUE;
}
void TestIpod::Utf8ToUnicode(WCHAR* pBufOut,char* pBufIn,U16  u16Len)
{
    int i,j=0;
    U8 u8tmp;
    if(u16Len==0)
    {
        pBufOut[0] = 0;
    }
    for(i=0;i<u16Len;)
    {
        u8tmp = (U8)(pBufIn[i]);
        if(u8tmp<0x80)
        {
            pBufOut[j++] = pBufIn[i]&0xFF;
            i++;
        }
        else if(u8tmp<0xE0)
        {
            pBufOut[j++] = (((WCHAR)(pBufIn[i])&0x1F)<<6)|((WCHAR)(pBufIn[i+1])&0x3F);
            i+=2;
        }
        else if(u8tmp<0xF0)
        {
            pBufOut[j++] = (((WCHAR)(pBufIn[i])&0x0F)<<12)|(((WCHAR)(pBufIn[i+1])&0x3F)<<6)|((WCHAR)(pBufIn[i+2])&0x3F);
            i+=3;
        }
        else if(u8tmp<0xF8)
        {
            pBufOut[j++] = (((WCHAR)(pBufIn[i])&0x07)<<18)|(((WCHAR)(pBufIn[i+1])&0x3F)<<12)|(((WCHAR)(pBufIn[i+2])&0x3F)<<6)|((WCHAR)(pBufIn[i+3])&0x3F);
            i+=4;
        }
    }
}
BOOL TestIpod::HandleTarckNewAttributes(unsigned char *Command,unsigned long nLen)
{
	unsigned long uRate = 0;
   if(Command == NULL || nLen < 15)
   {
	   return FALSE;
   }
   int i = 0;
   while (Command[i] != 0x55 && i < nLen)
   {
        i++;
   }
   unsigned nLeft = nLen - i - 1;
   if(nLeft < 15)
   {
     return FALSE;
   }
   else
   {
	   if(Command[i + 3] == 0x04 && Command[i + 2] == 0x0a)
	   {
		   uRate = Command[6]<< 24 + Command[7]<< 16 << Command[8]<< 8 +Command[9];
	   }

	   if(uRate != u32SampleRate && uRate > 0)
	   {
		   u32SampleRate = uRate;
		   U32 dwBytesReturned;
		   U16 j;
		   WAVEFORMATEX waveform;
		   waveform.wFormatTag=1;
		   waveform.nChannels=2;
		   waveform.nSamplesPerSec=u32SampleRate;
		   waveform.nAvgBytesPerSec=0x2b110;
		   waveform.nBlockAlign=4;
		   waveform.wBitsPerSample=0x10;
		   waveform.cbSize=0;
		   ST_PACKAGE package;
		   package.u8Marker = 0x06;//accessoryack
		   package.u8LingoID = 0x0A;
		   package.u8CommandID =0x00;
		   package.pu8CommandData[0] = Command[i +4];
		   package.pu8CommandData[1] = Command[i +5];
		   package.pu8CommandData[2] = 0x00;
		   package.pu8CommandData[3] = 0x04;
		   WriteToIpod(&package);
		   if(hIpoduac != NULL)
		   {
			   DeviceIoControl (hIpoduac, IOCTL_IAPL_PCM_SETFORMAT, (LPVOID)&waveform, sizeof(WAVEFORMATEX),NULL, 0, &dwBytesReturned, 0);
		   }  
		   //DeviceIoControl (hIpoduac, IOCTL_IAPL_PCM_SETFORMAT, (LPVOID)&waveform, sizeof(WAVEFORMATEX),NULL, 0, &dwBytesReturned, 0);
		   return TRUE;
	   }
   }
}
bool TestIpod::GetDBTrackinfo(unsigned long nStart,unsigned long nCount,unsigned char cBitMask)
{
   
	ST_PACKAGE package;
	U8 u8retry;
	int j = 0;
	//1SetUIMode
	
	package.u8LingoID = 0x04;
	package.u8CommandID = 0x00;
    package.pu8CommandData[j++] = 40;
	package.pu8CommandData[j++] = (U8)((u16TransID>>8)&0xFF);
	package.pu8CommandData[j++] = (U8)((u16TransID)&0xFF);
	package.pu8CommandData[j++] = 0xff & (nStart>>24);
	package.pu8CommandData[j++] = 0xff & (nStart>>16);
	package.pu8CommandData[j++] = 0xff & (nStart>>8);
	package.pu8CommandData[j++] = 0xff & (nStart);
	package.pu8CommandData[j++] = 0xff & (nCount>>24);
	package.pu8CommandData[j++] = 0xff & (nCount>>16);
	package.pu8CommandData[j++] = 0xff & (nCount>>8);
	package.pu8CommandData[j++] = 0xff & (nCount);
	package.pu8CommandData[j++] = cBitMask;
	package.u8Marker = 2 +j;
	u16TransID++;
	EnterCsReadCriticalSection(&csIpodRead);
	if(!WriteToIpod(&package))
	{
		LeaveCsReadCriticalSection(&csIpodRead);
		return FALSE;
	}
	//1ACK
	u8retry = 10;
	while(u8retry)
	{
		Sleep(50);
		if(!ReadFromIpod(&package))
		{
			u8retry--;
			continue;
		}
		if(package.u8LingoID!=0x04 && package.u8CommandID!=0x00 && package.pu8CommandData[0] != 0x42)
		{
			u8retry--;
			continue;
		}
		break;
	}
	LeaveCsReadCriticalSection(&csIpodRead);
}