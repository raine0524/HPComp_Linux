//VIDEC_MJPGDecoder.h
#ifndef __VIDEC_MJPGDECODER_H__
#define __VIDEC_MJPGDECODER_H__

#include "VIDEC.h"

class VIDEC_API VIDEC_MJPGDecoder;

class VIDEC_MJPGDecoderCallback
{
public:
	VIDEC_MJPGDecoderCallback(void){};
	virtual~VIDEC_MJPGDecoderCallback(void){};
public:
	virtual void OnVIDEC_MJPGDecoderCallbackImage(VIDEC_MJPGDecoder*pMJPGEncoder,VIDEC_Image*pImage)=0;
};

class VIDEC_API VIDEC_MJPGDecoder
{
public:
	VIDEC_MJPGDecoder(void){};
	virtual~VIDEC_MJPGDecoder(void){};
public:
	virtual int Open(void)=0;
	virtual void Close(void)=0;
	virtual int InputPacketData(const void*pPacketData,int nPacketDataLen)=0;

	static VIDEC_MJPGDecoder*Create(VIDEC_MJPGDecoderCallback&rCallback);
};

#endif
