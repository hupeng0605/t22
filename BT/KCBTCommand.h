#pragma once
#include "define.h"
#include "KCBTSerialPort.h"
#include "CShareMemory.h"
#include "CommandPool.h"
#include "GetFirstLeterFromName.h"
#include <queue>
class CBTCommand:public CSerialPort
{
public:
	virtual~CBTCommand();
	static CBTCommand* Instance( );
	static void DeleteInstance();
	void SetLangue(HINT nType);
	HINT GetLangue();
	void ReadDeviceNameFromFile();
	virtual sPostion CEPotionToPhonePotion(sPostion Postion,int nWidth,int Hight);
	virtual int  CExToPhonex(int x,int nWidth);
	virtual int CEyToPhoney(int y,int nHight);
	virtual int GetMaxCeAviablex(int nAvailbleWidth);
	virtual int GetMinCeAviablex(int nAvailbleWidth);
	virtual int GetMaxCeAviabley(int nAvailbleHight);
	virtual int GetMinCeAviabley(int nAvailbleHight);
	virtual int SendBTCommand(BTPacketDataType_t eType,sCommandData *pData);
	virtual int SendBTCommandBlock(BTPacketDataType_t eType,Block *pBlock);
	virtual void SendBTCommandToQueue(BTPacketDataType_t eType,sCommandData *pData);
	virtual void SendBTCommandBlockToQueue(BTPacketDataType_t eType,Block *pBlock);
	virtual bool IsPositionAvaiable(int x,int y,int nAvaibleWidth,int nAvaiblHight);
	virtual int CexToCeAviablex(int nCex,int nAvailbleWidth);//负数不在有效区域内
	virtual int CeyToCeAviabley(int nCey,int nAvailbleHight);//负数不在有效区域内
	void SetMyhWnd(HWND hhand);
	 HINT OnInit(DWORD dwPort, DWORD dwBaudRate);
	 HINT OpenBT(DWORD dwPort, DWORD dwBaudRate);
	 HINT LowBTPower();
	 HINT UpBTPower();
	 HINT CloseBT();
	 virtual void ClearBookData();
	 virtual void ClearMyPhoneData();
     void AddContactToList(sContact* pContact,NameListGroup &ListGrp);
	 void MessageBtclose();
	 void SetBTSetting(BTSETTING setting);
	 sMyPhoneInfo *GetMyPhoneInfo();
	 BTSETTING GetBTSetting();
	 int ReadUsefulNum(sUsefulContact *pUsefulContact,HUINT nMax);//读取常用号码
	// void StartCloseBT();
	 static BOOL ReadSerialData(void* pData, UINT uMsg, WPARAM wParam, LPARAM lParam,void *pthis);
	 static BOOL WriteSerialData(void* pData, UINT uMsg, WPARAM wParam, LPARAM lParam,void *pthis);
	 BOOL ReadSerialData(void* pData, UINT uMsg, WPARAM wParam, LPARAM lParam);
	 BOOL WriteSerialData(void* pData, UINT uMsg, WPARAM wParam, LPARAM lParam);
	 sBTCommandData* GetBTCommandData(void);
	 sBTPacketDataBuffer *GetBTPacketBuffer(void);
	 void SendCommand(queue<sCommamdItem*> queCommand);
	//BOOL ReadData(void* pData, UINT uMsg, WPARAM wParam, LPARAM lParam);
	 HBYTE CalcChecksum(HBYTE *pBuffer,HUINT nLen);
	 sBTPacketDataBuffer *CreatBTEmptyPacket();
	 void ResetCallHistoryData(sCallHistory *pData);
	 void ResetBTPacket(sBTPacketDataBuffer * pPacket);
	 void ResetBTGeneralData(sBTGeneralData *pData);
	 void ResetBTSPPData(sBTSPPData* pData);
	 void ResetBTHFPData(sBTHFPData *pData);
	 void ResetGATTData(sBTGATTData *pData);
	 void ResetBTHIDData(sBTHIDData *pData);
	 void ResetContactData(sContact *pData);
	 void ResetBTAVRCPData(sBTAVRCPData *pData);
	 void ResetBTPBAPCData(sBTPBAPCData *pData);
	 void ResetBTCommandData(sBTCommandData * pData);
	 void ResetNameListGrp(NameListGroup &NameGrp);
	 NameListGroup GetNameListGrp(void);
	 NameListGroup* GetNameListGrpp(void);
	 eBTPATLOADDATATYPE JudgeDataType(sBTPacketDataBuffer * pPacket);
	 HUINT ParsePacketStep1(HBYTE *pBuffer,HUINT nBufferlen,sBTPacketDataBuffer *pPacketDataBuffer);
	 HUINT ParsePacketCommand(sBTPacketDataBuffer *pPacketDataBuffer);
	 HUINT ParsePacketPayloadData(sBTPacketDataBuffer *pPacketDataBuffer);
	 HUINT ParsePacketGATTData(sBTPacketDataBuffer *pPacketDataBuffer);
	 HUINT ParsePacketSPPData(sBTPacketDataBuffer *pPacketDataBuffer);
	 HUINT ParsePacketPBDNData(sBTPacketDataBuffer *pPacketDataBuffer);
	 HUINT ParsePacketMEDIAINFOData(sBTPacketDataBuffer *pPacketDataBuffer);
	 HUINT HandleErrorData(sBTPacketDataBuffer *pPacketDataBuffer);
	 bool BTPacketParseComplete(sBTPacketDataBuffer *pPacketDataBuffer);
	 HUINT CompareChar(HBYTE *str1,HBYTE *str2,HUINT len);
	//GATT事件
	HUINT HandleBLE(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	//触摸屏事件
	 HUINT HandleSPPHomeKeyUp(void);
	 HUINT HandleSPPHomeKeyDown(void);
	 HUINT HandleSPPMenuKeyUp(void);
	 HUINT HandleSPPMenuKeyDown(void);
	 HUINT HandleSPPBackKeyUp(void);
	 HUINT HandleSPPBackKeyDown(void);
	 HUINT HandleSPPNextKeyUp(void);
	 HUINT HandleSPPNextKeyDown(void);
	 HUINT HandleSPPPreviousKeyUp(void);
	 HUINT HandleSPPPreviousKeyDown(void);
	 //PBAPC事件&HFP事件
	 HUINT HandlePBState(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandlePBDNEND(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandlePABConn(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleHFPState(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleHFPDial(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleHFPAnswer(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleHFPAudo(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleHFPDTMF(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleHFPMute(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleHFPRecall(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleHFPDealIncomeCall(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleHFPIncomeCall(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleHFPIncomeCallNum(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleHFPSecNum(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandlePBDISC(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleCannelDownload(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleHFPHangUp(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleHFPOutGoingCall(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 //通用事件处理
	 HUINT HandleReadSoftVersion(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos); 
	 HUINT HandleReadLocalAddress(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT	HandleReadLocalDeviceName(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleReadPairedCode(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleGetGATT(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleSetLocalDeviceName(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleCurrentSPK(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleSetPairCode(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandelPairedLists(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT	HandelPairedListsStart(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT	HandelPairedListsEnd(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleDeletePairedDevices(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleDisConnectCurrentDevice(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleEnterPairMode(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleEnterTestMode(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleLoadFactoryDefaults(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleInit(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandlePairResult(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandlePairEnd(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleCurrentConnectDevice(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandlePairState(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 //SPP事件
	 HUINT HandleGetSPPState(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleConnectPhoneInitiative(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleDisconnectHID(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleSPP(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleSendSPPData(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleSTOP(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	//HID事件
	 HUINT HandleHIDState(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleHIDDISC(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleHID(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandHIDHome(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 //AVRCP事件处理
	 HUINT HandleA2DPState(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleConnectA2DP(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleDisconnectA2DP(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleConnectAVRCP(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleAVRCPPlayState(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleA2DPMute(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleFWD(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleBACK(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandlePP(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 //SPP数据处理
	 HUINT HandleSPPPhoneScreenInfo(sBTPacketDataBuffer *pPacketDataBuffer);
	 HUINT HandleSPPPhoneKeyControl(sBTPacketDataBuffer *pPacketDataBuffer);
	 HUINT HandleSPPPhoneTouchEvents(sBTPacketDataBuffer *pPacketDataBuffer);
	 HUINT HandleSPPPhoneSystemInfo(sBTPacketDataBuffer *pPacketDataBuffer);
     HUINT HandleSPPPhoneStreachScreen(sBTPacketDataBuffer *pPacketDataBuffer);
	 HUINT HandleSPPPhoneDPI(sBTPacketDataBuffer *pPacketDataBuffer);
     HUINT HandleSPPPhoneHIDConnectState(sBTPacketDataBuffer *pPacketDataBuffer);
	 HUINT HandleSPPPhoneEnableBackAndMenu(sBTPacketDataBuffer *pPacketDataBuffer);
	 HUINT HandleSPPPhoneLockInfo(sBTPacketDataBuffer *pPacketDataBuffer);
	 HUINT HandleSPPPhoneTime(sBTPacketDataBuffer *pPacketDataBuffer);
	 HUINT HandleSPPDAParaPacket(sBTPacketDataBuffer *pPacketDataBuffer);
	 HUINT HandleSPPRunState(sBTPacketDataBuffer *pPacketDataBuffer);
	 void AddCommand(sCommamdItem*pItem,queue<sCommamdItem*> queCommand);
	 //蓝牙音乐信息
	 HUINT HandleMediaInfoStart(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HUINT HandleMediaInfoEnd(sBTPacketDataBuffer *pPacketDataBuffer,HUINT nPos);
	 HINT FindContactPhoneNum(HBYTE *pBeg,HBYTE *pEnd,sContact* pContact);
	 bool FindContactname(HBYTE *pBeg,HBYTE *pEnd,sContact* pContact);
	 int DecodeQuoted(const char* pSrc,  char* pDst, int nSrcLen) ;
	 HINT DownAddressBook();
	 sCommamdItem* CreatCommandItem(HBYTE *cCMD,HUINT nlen);
	 void AddDisPBDACommand(queue<sCommamdItem*> queCommand);
	 bool DeleteCommandItem(queue<sCommamdItem*> queCommand);
	 HUINT FindCallHistoryTime(HBYTE *pBeg,HBYTE *pEnd,sCallHistory *pCallHistory);
	 bool FindNameFromAddressBookByNum(sContact *pBookBeg,HUINT nTotal,sContact *p);
	 bool ComparePhoneNum(sTelNumber* pNum1,sTelNumber* pNum2);
	 void SetPBDACState(ePBAPCSTATE estate);
     bool ReadBtParamFromSHM();
	 void GetAvailableArea(int CeWidth,int CeHight,int PhoneWidth,int PhoneHight);
	 HINSTANCE GetDriverDLL();
	 void SaveBTLastMem();
	 void DisCurrentConnectDevice();
	 HWND GetMyHandel();
	 //字母排序
	 HINT GetLetterFromNameGrp(HINT index,NameListGroup &sNameGrp);
	 void TotalCountNameGrp(NameListGroup &sNameGrp);
	 void TotalCountNameGrp(NameListGroup &sNameGrp,HINT nBeg,HINT nEnd);
	 HINT GetListGrpIndex(HINT iStart,HINT &nCurrentList);
	// void AddContactToList(sContact* pContact,NameListGroup &ListGrp);
	 void SetHDMI(bool bIN);
	 bool GetHDMI();
	  bool IsNumberLegal(HBYTE *pBeg,HINT nLen);
	  void SendGetBTInfo();
private:
	CBTCommand();
	static CBTCommand* s_pBTCommand;
	sBTPacketDataBuffer* m_pPacket;//解析数据包Buffer
	sBTCommandData* m_pBTCommandData;
	NameListGroup m_szNameList;
	sSystemInfo*	 m_pSystemInfo;
	sMyPhoneInfo *m_pPhoneInfo;
	//sDeviceINFO* m_pDeviceINFO;
	HWND m_hWnd;
	HINSTANCE m_DriverDll;
	queue<sCommamdItem*> m_quepCommand;
	HANDLE m_eveCommand;
	CRITICAL_SECTION m_crsCommand;
	CRITICAL_SECTION m_csNameList;
	HANDLE m_semCommand;
	HANDLE m_eveReadyToDown;
	HANDLE m_eveDownComplete;
	HANDLE m_eveCMDQUE;
	HINT m_nCurrentLangue;//0 中文 1 英文
	sRestOfPacketData *m_pRestPBDNData;
	//CShareMemory m_sBtParam;
	BTParam m_sBtParam;
	BTSETTING m_sBTSetting;
	bool m_bBTOpen;
	bool m_bInHDMI;
	bool m_bBookDataBeCleared;
	bool m_bMyPhoneInfoCleared;
	eSCREENTYPE m_eScreenType;
	ePBAPCSTATE m_ePBAPCState;
	HANDLE m_hBTReset;
	bool m_bMacGet;
#if BTSerialPortData
	ofstream  m_BTSerialDataLogfile;
#endif  
};