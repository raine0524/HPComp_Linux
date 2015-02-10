//NETEC_RTPJBuf.h
#ifndef __NETEC_RTPJBUF_H__
#define __NETEC_RTPJBUF_H__

#include <NETEC/NETEC_Export.h>

class NETEC_API NETEC_RTPJBuf;
class NETEC_RTPJBufCallback
{
public:
	virtual void OnNETEC_RTPJBufCallbackRTPPacket(NETEC_RTPJBuf*pRTPJBuf,unsigned char*pRTPPacketData,int nRTPPacketLen,int nPayloadType,int nRTPHeaderLen,unsigned short nSeqNo,unsigned long nTimestamp)=0;
};

class NETEC_API NETEC_RTPJBuf
{
public:
	NETEC_RTPJBuf(void){};
	virtual~NETEC_RTPJBuf(void){};
public:
	virtual int Open(void)=0;
	virtual void Close(void)=0;

	virtual int OnRecvdPacket(unsigned char*pRTPPacketData,int nRTPPacketLen,int nPayloadType,int nRTPHeaderLen,unsigned short nSeqNo,unsigned long nTimestamp)=0;

	static NETEC_RTPJBuf*Create(NETEC_RTPJBufCallback&rCallback);
};

#endif
