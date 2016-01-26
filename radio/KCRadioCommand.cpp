#include "KCRadioCommand.h"
HUINT  RadioCommandParseBuffer(HBYTE *pBuffer, HUINT nBufferLen,sRadioCommandPacket *pPacket)
{
	HUINT nTotalParsedLen = 0;
	if(pBuffer != NULL && pPacket !=NULL )
	{
		HBYTE *pt = pBuffer;
		HUINT nptLen = nBufferLen;
		HBYTE *ptEnd = pt+ nBufferLen;
//		HUSHORT nCheckSum = 0;

		while(pt < ptEnd && pPacket->eState < eRADIOCOMMANDPARSEFINISH )
		{
			switch(pPacket->eState)
			{
				case     eCOMMANDPARSEHEADSYN:
				{
			
					pPacket->eCommandType = eRADIOUNKNOW;
					pPacket->nCurrentLen = 0;
					pPacket->nBufferLen = 0;
					pPacket->nPacketLen = 0;
					if(eCOMMANDHEAD == *pt)
					{
						pPacket->eState = eRADIOCOMMANDPARSEDATALENGTH;
						pPacket->pRadioCommand->CommandHead =*pt;
						pPacket->nBufferLen +=1;
					}
					nTotalParsedLen += 1;
					pt += 1;
					nptLen -=1;
				}
				break;
				case  eRADIOCOMMANDPARSEDATALENGTH:
				{
					pPacket->pRadioCommand->RadioCommandLen = *pt;
					pPacket->eState = eRADIOCOMMANDPARSEID;
					pPacket->nBufferLen +=1;
					pPacket->nPacketLen =*pt;
					nTotalParsedLen +=1;
					pt +=1;
					nptLen  -=1;
				}
				break;
				case  eRADIOCOMMANDPARSEID:
				{
					if(eRADIOCOMMANDPARSEID != *pt)
					{
						PacketReset(pPacket);
						pPacket->eState = eCOMMANDPARSEHEADSYN;
					}
					else
					{
						pPacket->pRadioCommand->RadioCommandSYN = *pt;
						pPacket->eState = eRADIOCOMMANDPARSETYPE;
					}
					nTotalParsedLen +=1;
					pt +=1;
					nptLen  -=1;
				}
				break;
				case  eRADIOCOMMANDPARSETYPE:
				{
					pPacket->pRadioCommand->RadioCommandType = *pt;
					pPacket->eCommandType = ParseRadioCommandType(*pt);
					if(pPacket->eCommandType == eRADIOUNKNOW)
					{
						PacketReset(pPacket);
						pPacket->eState = eCOMMANDPARSEHEADSYN;
					}
					else
					{
						pPacket->eState = eRADIOCOMMANDPARSEDATA;
						pPacket->nBufferLen +=1;
						pPacket->nCurrentLen = 0;
					}
					nTotalParsedLen +=1;
					pt +=1;
					nptLen  -=1;
				}
				break;
				case  eRADIOCOMMANDPARSEDATA:
				{
					HUINT nBytesToCopy = PacketGetPlayloadLen(pPacket) -pPacket->nCurrentLen;
					if( nBytesToCopy > 0)
					{
						if(nptLen < nBytesToCopy)
						{
							nBytesToCopy = nptLen;
						}
						memcpy(&(PacketGetPlayload(pPacket)[pPacket->nCurrentLen]),pt,nBytesToCopy);
						pPacket->nCurrentLen += nBytesToCopy;
						pPacket->nBufferLen +=nBytesToCopy;
						nTotalParsedLen +=nBytesToCopy;
						pt +=nBytesToCopy;
						nptLen -=nBytesToCopy;
					}
					if(pPacket->nCurrentLen == PacketGetPlayloadLen(pPacket))
					{
						pPacket->eState = eRADIOCOMMANDPARSECHECKSUM;
					}
				}
				break;
				case  eRADIOCOMMANDPARSECHECKSUM:
				{
					PacketGetPlayload(pPacket)[pPacket->nCurrentLen] = *pt;
					pPacket->nBufferLen += 1;
					nTotalParsedLen +=1;
					pt +=1;
					nptLen  -=1;
					if(pPacket->nPacketLen == pPacket->nBufferLen)
					{
						HBYTE * cPlayload = PacketGetPlayload(pPacket);
						HUINT nPlayloadLen = PacketGetPlayloadLen(pPacket);
						if(PacketCalcCheckNum(cPlayload,nPlayloadLen))
						{
							pPacket->eState = eRADIOCOMMANDPARSEFINISH;
						}
						else
						{
							PacketReset(pPacket);
						}
					}
				}
				break;
				case  eRADIOCOMMANDPARSEFINISH:
				case  eRADIOCOMMANDPARSEDETECT:
				case  eRADIOCOMMANDPARSEDETECTBAD:
				break;
			}			
		}
	}
	return nTotalParsedLen;
}


eRADIOCOMMANDTYPE ParseRadioCommandType(HBYTE *cCommand,HINT nLen)
{
	switch((*cCommand))
	{
		case   0x00 :
		{
			return eENTERRADIOINTERFACE;
		}
		break;
		case   0x01 :
		{
			return eRADIOCHANNELCHANGE;
		}
		break;
		case   0x02 :
		{
			return eRADIOAMFMCHANNGE;
		}
		break;
		case   0x03 :
		{
			return eRADIOCHANNELSEARCH;
		}
		break;
		case   0x04 :
		{
			return eRADIOON;
		}
		break;
		case   0x05 :
		{
			return eRADIOCHANNELSTORE;
		}
		break;
		case   0x06 :
		{
			return eRADIOADJUST;
		}
		break;
		case   0x07 :
		{
			return eRADIOAUTOCHANNELSEARCH;
		}
		break;
		case   0x08 :
		{
			return eRADIOSCAN;
		}
		break;
		case   0x09 :
		{
			return eRADIOCHANNNELLISTS;
		}
		break;
		case   0x0A :
		{
			return eRADIOCHANNNELADJUST;
		}
		break;
		case   0x0B :
		{
			return eRADIOSTOPAUTOCHANNELSEARCH;
		}
		break;
		default :
		{
			return eRADIOUNKNOW;
		}
			break;
	}
}
HINT HandRadioData(HBYTE *cCommand,HINT nLen)
{
	eRADIOCOMMANDTYPE eCMDType = ParseRadioCommandType(*cCommand);
	switch (eCMDType)
	{
	case  eENTERRADIOINTERFACE :
		{
			HandelEnterRadioInterface(cCommand,nLen);
		}
		break;
	case  eRADIOCHANNELCHANGE :
		{
			HandelRadioChannelChange(cCommand,nLen);
		}
		break;
	case  eRADIOAMFMCHANNGE :
		{
			HandelRadioAMFMChange(cCommand,nLen);
		}
		break;
	case  eRADIOCHANNELSEARCH :
		{
			HandelRadioChannelSearch(cCommand,nLen);
		}
		break;
	case  eRADIOON :
		{
			HandelRadioOn(cCommand,nLen);
		}
		break;
	case  eRADIOCHANNELSTORE :
		{
			HandelRadioChannelStore(cCommand,nLen);
		}
		break;
	case  eRADIOADJUST :
		{
			HandelRadioAdjust(cCommand,nLen);
		}
		break;
	case  eRADIOAUTOCHANNELSEARCH :
		{
			HandelRadioAutoSearch(cCommand,nLen);
		}
		break;
	case  eRADIOSCAN :
		{
			HandelRadioScan(cCommand,nLen);
		}
		break;
	case  eRADIOCHANNNELLISTS :
		{
			HandelRadioChannelLists(cCommand,nLen);
		}
		break;
	case  eRADIOCHANNNELADJUST :
		{
			HandelRadioChannelAdjust(cCommand,nLen);
		}
		break;
	case  eRADIOSTOPAUTOCHANNELSEARCH :
		{
			HandelRadioStopAutoSearch(cCommand,nLen);
		}
		break;
	default:
		break;
	}
	return 0;
}


void PacketReset(sRadioCommandPacket *pPacket)
{
	if(pPacket != NULL && pPacket->pRadioCommand !=NULL)
	{
		pPacket->eCommandType =eRADIOUNKNOW;
		pPacket->eState = eCOMMANDPARSEHEADSYN;
		pPacket->nCurrentLen = 0;
		pPacket->nBufferLen = 0;
		pPacket->nPacketLen = 0;
		memset(pPacket->pRadioCommand,0,sizeof(sRadioCommand)+eRADIOCOMMANDMAXPLAYLOADLEN+eRADIOCOMMANDCHECKSUMLEN);
	}
	
}
HBYTE*  PacketGetPlayload(sRadioCommandPacket *pPacket)
{
	if(pPacket !=NULL)
	{
		return pPacket->pRadioCommand->RadioPlayLoadData;
	}
	else
		return NULL;
}

HUINT PacketGetPlayloadLen(sRadioCommandPacket *pPacket)
{
	HUINT nPlayloadLen = 0;
	if(pPacket->nPacketLen > (eRADIOCOMMANDIDLEN +eRADIOCOMMANDTYPELEN))
	{
		nPlayloadLen = pPacket->nPacketLen -eRADIOCOMMANDTYPELEN -eRADIOCOMMANDIDLEN;
	}
	return nPlayloadLen;
}
HBYTE PacketCalcCheckNum(HBYTE *pBuffer,HUINT nBufferLen)
{
	HBYTE cChecksum = 0;
	if(pBuffer != NULL && nBufferLen > 0)
	{
		HBYTE * pBufferEnd = pBuffer + nBufferLen;
		while(pBuffer != pBufferEnd)
		{
			cChecksum = *pBuffer;
			pBuffer++;
		}
		cChecksum = (HBYTE)(0x100 - cChecksum);
	}
	return cChecksum;
}

sRadioCommandPacket *CreateEmptyRecvPacket(void)
{
	sRadioCommandPacket *pPacket = new sRadioCommandPacket;
	pPacket->pRadioCommand =(sRadioCommand*) new CHAR[sizeof(sRadioCommand)+eRADIOCOMMANDMAXPLAYLOADLEN+eRADIOCOMMANDCHECKSUMLEN];
	if(pPacket !=NULL && pPacket->pRadioCommand !=NULL)
	{
		return pPacket;
	}
	return NULL;
}
HBOOL PacketIsComlete(sRadioCommandPacket* pPacket)
{
	HBOOL bResult = false;
	if(pPacket)
	{
		bResult = (eRADIOCOMMANDPARSEFINISH <= pPacket->eState);
	}
	return bResult;
}
void ParesePacketData(sRadioCommandPacket* pPacket)
{
	if(pPacket !=NULL)
	{
		switch (pPacket->eCommandType)
		{
			case  eENTERRADIOINTERFACE :
			{
					HandelEnterRadioInterface(pPacket);
			}
			break;
			case  eRADIOCHANNELCHANGE :
				{
					HandelRadioChannelChange(pPacket);
				}
				break;
			case  eRADIOAMFMCHANNGE :
				{
					HandelRadioAMFMChange(pPacket);
				}
				break;
			case  eRADIOCHANNELSEARCH :
				{
					HandelRadioChannelSearch(pPacket);
				}
				break;
			case  eRADIOON :
				{
					HandelRadioOn(pPacket);
				}
				break;
			case  eRADIOCHANNELSTORE :
				{
					HandelRadioChannelStore(pPacket);
				}
				break;
			case  eRADIOADJUST :
				{
					HandelRadioAdjust(pPacket);
				}
				break;
			case  eRADIOAUTOCHANNELSEARCH :
				{
					HandelRadioAutoSearch(pPacket);
				}
				break;
			case  eRADIOSCAN :
				{
					HandelRadioScan(pPacket);
				}
				break;
			case  eRADIOCHANNNELLISTS :
				{
					HandelRadioChannelLists(pPacket);
				}
				break;
			case  eRADIOCHANNNELADJUST :
				{
					HandelRadioChannelAdjust(pPacket);
				}
				break;
			case  eRADIOSTOPAUTOCHANNELSEARCH :
				{
					HandelRadioStopAutoSearch(pPacket);
				}
				break;
			default:
				break;
		}
	}
}

void HandelEnterRadioInterface(sRadioCommandPacket* pPacket)
{
	
}
void HandelRadioChannelChange(sRadioCommandPacket* pPacket)
{

}
void HandelRadioAMFMChange(sRadioCommandPacket* pPacket)
{

}
void HandelRadioChannelSearch(sRadioCommandPacket* pPacket)
{

}
void HandelRadioOn(sRadioCommandPacket* pPacket)
{

}
void HandelRadioChannelStore(sRadioCommandPacket* pPacket)
{

}
void HandelRadioAdjust(sRadioCommandPacket* pPacket)
{

}
void HandelRadioAutoSearch(sRadioCommandPacket* pPacket)
{

}
void HandelRadioScan(sRadioCommandPacket* pPacket)
{

}
void HandelRadioChannelLists(sRadioCommandPacket* pPacket)
{

}
void HandelRadioChannelAdjust(sRadioCommandPacket* pPacket)
{

}
void HandelRadioStopAutoSearch(sRadioCommandPacket* pPacket)
{

}







