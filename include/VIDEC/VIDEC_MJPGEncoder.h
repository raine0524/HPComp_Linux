//VIDEC_MJPGEncoder.h
#ifndef __VIDEC_MJPGENCODER_H__
#define __VIDEC_MJPGENCODER_H__

#include "VIDEC.h"

class VIDEC_API VIDEC_MJPGEncoder;

class VIDEC_MJPGEncoderCallback
{
public:
	VIDEC_MJPGEncoderCallback(void){};
	virtual~VIDEC_MJPGEncoderCallback(void){};
public:
	virtual void OnVIDEC_MJPGEncoderCallbackStreamPacket(VIDEC_MJPGEncoder*pMJPGEncoder,unsigned char*pPacketData,int nPacketLen)=0;
	virtual void OnVIDEC_MJPGEncoderCallbackPreEncode(VIDEC_MJPGEncoder*pMJPGEncoder,int&nSkip)=0;
};

class VIDEC_API VIDEC_MJPGEncoder
	: public VIDEC_ImageSink
{
public:
	VIDEC_MJPGEncoder(void){};
	virtual~VIDEC_MJPGEncoder(void){};
public:
	virtual int Open(void)=0;
	virtual void Close(void)=0;

	static VIDEC_MJPGEncoder*Create(VIDEC_MJPGEncoderCallback&rCallback);
};

#endif
