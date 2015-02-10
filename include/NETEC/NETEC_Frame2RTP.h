//NETEC_Frame2RTP.h
#ifndef __NETEC_FRAME2RTP_H__
#define __NETEC_FRAME2RTP_H__

#include <NETEC/NETEC_Export.h>

class NETEC_API NETEC_Frame2RTP;
class NETEC_Frame2RTPCallback
{
public:
	NETEC_Frame2RTPCallback(void){};
	virtual~NETEC_Frame2RTPCallback(void){};
public:
	virtual void OnNETEC_Frame2RTPCallbackRTPPacketData(NETEC_Frame2RTP*pFrame2RTP,unsigned char*pRTPPacketData,int nRTPPacketLen)=0;
};

class NETEC_API NETEC_Frame2RTP
{
public:
	NETEC_Frame2RTP(void){};
	virtual~NETEC_Frame2RTP(void){};
public:
	virtual int Open(void)=0;
	virtual void Close(void)=0;
	virtual void SetRTPPayloadType(int nPayloadType)=0;
	virtual int GetRTPPayloadType(void)=0;
	virtual void SetMaxBitrate(int nMaxBitrate)=0;
	virtual void SetFrameRate(int nFrameRate)=0;
	virtual int SetFrameData(const void*pData,int nLen)=0;

	static NETEC_Frame2RTP*Create(NETEC_Frame2RTPCallback&rCallback,const char*cszName);
	static NETEC_Frame2RTP*CreateJitter(NETEC_Frame2RTPCallback&rCallback,const char*cszName);
};

#endif
