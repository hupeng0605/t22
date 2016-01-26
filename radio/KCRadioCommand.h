 #include "Type.h"
#include "stdafx.h"

//HUINT  RadioCommandParseBuffer(HBYTE *pBuffer, HUINT nBufferLen,sRadioCommandPacket *pPacket);
eRADIOCOMMANDTYPE ParseRadioCommandType(HBYTE cCommand);
//HUINT GetPacketLoadDataLen(sRadioCommandPacket *pPacket);

void PacketReset(sRadioCommandPacket *pPacket);
HBYTE*  PacketGetPlayload(sRadioCommandPacket *pPacket);
HUINT PacketGetPlayloadLen(sRadioCommandPacket *pPacket);
HBYTE PacketCalcCheckNum(HBYTE *pBuffer,HUINT nBufferLen);
sRadioCommandPacket *CreateEmptyRecvPacket(void);
HBOOL PacketIsComlete(sRadioCommandPacket* pPacket);
void ParesePacketData(sRadioCommandPacket* pPacket);
void HandelEnterRadioInterface(sRadioCommandPacket* pPacket);
void HandelRadioChannelChange(sRadioCommandPacket* pPacket);
void HandelRadioAMFMChange(sRadioCommandPacket* pPacket);
void HandelRadioChannelSearch(sRadioCommandPacket* pPacket);
void HandelRadioOn(sRadioCommandPacket* pPacket);
void HandelRadioChannelStore(sRadioCommandPacket* pPacket);
void HandelRadioAdjust(sRadioCommandPacket* pPacket);
void HandelRadioAutoSearch(sRadioCommandPacket* pPacket);
void HandelRadioScan(sRadioCommandPacket* pPacket);
void HandelRadioChannelLists(sRadioCommandPacket* pPacket);
void HandelRadioChannelAdjust(sRadioCommandPacket* pPacket);
void HandelRadioStopAutoSearch(sRadioCommandPacket* pPacket);
void  HandelEnterRadioInterface(HBYTE *cCommand,HUINT nLen);
void  HandelRadioChannelChange(HBYTE *cCommand,HUINT nLen);
void HandelRadioAMFMChange(HBYTE *cCommand,HUINT nLen);
void HandelRadioChannelSearch(HBYTE *cCommand,HUINT nLen);
void HandelRadioOn(HBYTE *cCommand,HUINT nLen);
void HandelRadioChannelStore(HBYTE *cCommand,HUINT nLen);
void HandelRadioAdjust(HBYTE *cCommand,HUINT nLen);
void HandelRadioAutoSearch(HBYTE *cCommand,HUINT nLen);
void HandelRadioScan(HBYTE *cCommand,HUINT nLen);
void HandelRadioChannelLists(HBYTE *cCommand,HUINT nLen);
void HandelRadioChannelAdjust(HBYTE *cCommand,HUINT nLen);
void HandelRadioStopAutoSearch(HBYTE *cCommand,HUINT nLen);



