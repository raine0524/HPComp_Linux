//VIDEC_Transcode.h
#ifndef __VIDEC_TRANSCODE_H__
#define __VIDEC_TRANSCODE_H__

#include <VIDEC/VIDEC_Export.h>

class VIDEC_API VIDEC_Transcode;
class VIDEC_TranscodeCallback
{
public:
	virtual void OnVIDEC_TranscodeCallbackPacketData(VIDEC_Transcode*pTranscode,void*pPacketData,int nPacketLen){};
};

class VIDEC_API VIDEC_Transcode
{
public:
	VIDEC_Transcode(void){};
	virtual~VIDEC_Transcode(void){};
public:
	virtual int Open(int nBitrate,int nBitrateControlType)=0;
	virtual void Close(void)=0;
	virtual int TranscodePacketData(void*pPacketData,int nPacketLen)=0;
	virtual void RequestKeyFrame(void)=0;

	static VIDEC_Transcode*Create(VIDEC_TranscodeCallback&rCallback);
};

#endif
