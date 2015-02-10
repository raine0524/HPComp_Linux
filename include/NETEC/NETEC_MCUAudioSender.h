//NETEC_MCUAudioSender.h
#ifndef __NETEC_MCUAUDIOSENDER_H__
#define __NETEC_MCUAUDIOSENDER_H__

#include <NETEC/NETEC_Export.h>

class NETEC_API NETEC_MCUAudioSender
{
public:
	NETEC_MCUAudioSender(void){};
	virtual~NETEC_MCUAudioSender(void){};
public:
	virtual int Open(void)=0;
	virtual void Close(void)=0;
	virtual int SendAudio(unsigned char*pData,int nLen)=0;
	virtual unsigned long GetAudioID(void)=0;
	virtual int IsEnable(void)=0;

	static NETEC_MCUAudioSender*Create(unsigned long nAudioID);
};

#endif
