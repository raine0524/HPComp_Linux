//NETEC_MCUVideoReceiver.h
#ifndef __NETEC_MCUVIDEORECEIVER_H__
#define __NETEC_MCUVIDEORECEIVER_H__

#include <NETEC/NETEC_Export.h>
#include <NETEC/NETEC.h>

class NETEC_API NETEC_MCUVideoReceiver;
class NETEC_MCUVideoReceiverCallback
{
public:
	virtual void OnNETEC_MCUVideoReceiverCallbackPacket(NETEC_MCUVideoReceiver*pReceiver,unsigned char*pPacketData,int nPacketLen)=0;
};

class NETEC_API NETEC_MCUVideoReceiver
{
public:
	NETEC_MCUVideoReceiver(void){};
	virtual~NETEC_MCUVideoReceiver(void){};
public:
	virtual void Close(void)=0;
	virtual int EnableVideo(int nEnable)=0;
	virtual int IsVideoEnable(void)=0;
	virtual int RequestKeyFrame(void)=0;
	virtual int SetFrameTypeControlMode(FRAME_TYPE_CONTROL_MODE nMode)=0;

	static NETEC_MCUVideoReceiver*Create(NETEC_MCUVideoReceiverCallback&rCallback,unsigned long nVideoID,const char*cszPeerMCUID,const char*cszPeerMCUIP,unsigned short nPeerMCUPort);
};


#endif
