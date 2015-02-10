//NETEC_MCUVideoSender.h
#ifndef __NETEC_MCUVIDEOSENDER_H__
#define __NETEC_MCUVIDEOSENDER_H__

#include <NETEC/NETEC_Export.h>

class NETEC_API NETEC_MCUVideoSender
{
public:
	NETEC_MCUVideoSender(void){};
	virtual~NETEC_MCUVideoSender(void){};
public:
	virtual int Open(void)=0;
	virtual void Close(void)=0;
	virtual int SendVideo(unsigned char*pData,int nLen)=0;
	virtual unsigned long GetVideoID(void)=0;
	virtual int IsEnable(int nFrameType)=0;
	virtual int IsRequestKeyFrame(int nFrameType)=0;
	virtual void SetMaxBitrate(int nMaxBitrate)=0;

	static NETEC_MCUVideoSender*Create(unsigned long nVideoID);
};

#endif
