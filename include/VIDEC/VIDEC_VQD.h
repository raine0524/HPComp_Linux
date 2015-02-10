//VIDEC_VQD.h
#ifndef __VIDEC_VQD_H__
#define __VIDEC_VQD_H__

#include <VIDEC/VIDEC.h>
#include <VIDECVQD/VIDECVQDAPI.h>

class VIDEC_VQDCallback
{
public:
	VIDEC_VQDCallback(void){};
	virtual~VIDEC_VQDCallback(void){};
public:
	virtual void OnVIDEC_VQDCallbackResult(unsigned long nDetectResult)=0;
};

class VIDEC_API VIDEC_VQD
	: public VIDEC_ImageSink
{
public:
	VIDEC_VQD(void){};
	virtual~VIDEC_VQD(void){};
public:
	virtual int Open(int nDetectFlags)=0;
	virtual void Close(void)=0;

	static VIDEC_VQD*Create(VIDEC_VQDCallback&rCallback);
	static void SetParams(unsigned long nDetectFlag,int nThreshold);
};

#endif
